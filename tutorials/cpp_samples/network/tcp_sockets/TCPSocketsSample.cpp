// Демонстрирует работу с TCP-сокетами в архитектуре клиент-сервер.
// Сервер принимает несколько клиентских подключений и рассылает состояние камеры.
// Клиенты получают обновления камеры и синхронизируют свой обзор с позицией сервера.
// Сообщения сериализуются с заголовком (тип + размер), за которым следуют данные полезной нагрузки.

#include "TCPSocketsSample.h"

#include <UnigineConsole.h>
#include <UnigineGame.h>

#include "../../utils/Utils.h"

using namespace Unigine;

REGISTER_COMPONENT(TCPSocketsSample);

namespace
{
	constexpr const char *DEFAULT_SERVER_HOSTNAME = "127.0.0.1";
	constexpr unsigned short DEFAULT_SERVER_PORT = 64'000;

	constexpr int SEND_BUFFER_SIZE = 4096;
	constexpr int RECV_BUFFER_SIZE = 4096;

	constexpr int MAX_CLIENT_CONNECTIONS = 8;

	constexpr int CLIENT_CONNECTION_TIMEOUT_MS = 10'000;
	constexpr int CLIENT_WRITE_TIMEOUT_US = 1'000;
	constexpr int CLIENT_READ_TIMEOUT_US = 1'000;
}

// GUI инициализируется; хост (Client или Server) создаётся по нажатию кнопки.
void TCPSocketsSample::init()
{
	gui.init(this);
}

// Активный хост (Client или Server) обновляется; GUI отражает состояние подключения.
void TCPSocketsSample::update()
{
	if (host)
		host->update();

	gui.update();
}

// Активный хост уничтожается, GUI очищается.
void TCPSocketsSample::shutdown()
{
	if (host)
	{
		delete host;
		host = nullptr;
	}

	gui.shutdown();
}

// =================================================================================
// CLIENT IMPLEMENTATION
// =================================================================================

// TCP-сокет создаётся, настраивается как неблокирующий, сетевой поток запускается.
TCPSocketsSample::Client::Client(const Unigine::String &hostname, unsigned short port)
{
	// Сокет создаётся с адресом целевого сервера для последующего вызова connect().
	// Примечание: собственный адрес сокета назначается автоматически операционной системой.
	SocketPtr socket = Socket::create(Socket::SOCKET_TYPE_STREAM, hostname, port);

	if (!socket->isOpened())
	{
		Log::warning("Could not resolve specified hostname (%s)!\n", hostname.get());
		return;
	}

	// Размеры буферов отправки и приёма настраиваются
	socket->send(SEND_BUFFER_SIZE);
	socket->recv(RECV_BUFFER_SIZE);

	// Неблокирующий режим позволяет опрашивать сокет без остановки потока
	socket->nonblock();

	thread.start(socket, true);

	// Управление игроком отключается, чтобы камера могла синхронизироваться с сервером
	if (PlayerPtr player = Game::getPlayer())
		player->setControlled(false);

	Console::addCommand(
		"send_msg",
		"[Network Sockets Sample] Send a text message to peer.",
		MakeCallback(this, &TCPSocketsSample::Client::on_message_send_cmd)
	);
}

// Управление игроком восстанавливается, консольная команда удаляется из регистрации.
TCPSocketsSample::Client::~Client()
{
	if (PlayerPtr player = Game::getPlayer())
		player->setControlled(true);

	Console::removeCommand("send_msg");
}

// Входящие сообщения от сервера обрабатываются; камера синхронизируется при получении CameraMessage.
void TCPSocketsSample::Client::update()
{
	if (!thread.isRunning())
		return;

	Message *message = thread.receive();
	int processed = 0;

	// Сообщения обрабатываются до предела за кадр во избежание задержек
	while (message && processed < message_process_limit)
	{
		switch (message->getType())
		{
			case Message::TEXT:
			{
				// Текстовое сообщение выводится в консоль
				TextMessage *text_msg = dynamic_cast<TextMessage *>(message);

				if (text_msg->text.get() && !text_msg->text.empty())
					Log::message("Received a text message from Server: %s\n", text_msg->text.get());

				break;
			}

			case Message::CAMERA:
			{
				// Трансформация камеры применяется к локальному игроку
				CameraMessage *camera_msg = dynamic_cast<CameraMessage *>(message);

				if (camera_msg)
				{
					PlayerPtr player = Game::getPlayer();

					if (player)
					{
						player->setWorldPosition(camera_msg->position);
						player->setWorldRotation(camera_msg->rotation);
					}
				}

				break;
			}
		}

		delete message;
		message = thread.receive();
		processed += 1;
	}
}

// Сетевой поток запускается с переданным сокетом; опциональный флаг connect для клиентов.
void TCPSocketsSample::Client::NetworkThread::start(Unigine::SocketPtr socket, bool connect)
{
	reset();
	this->socket = socket;
	this->connect = connect;
	run();
}

// Поток останавливается, сокет закрывается, очереди сообщений очищаются.
void TCPSocketsSample::Client::NetworkThread::reset()
{
	shutdown();

	if (socket)
	{
		socket->close();
		socket.clear();
	}

	send_queue.clear();
	recv_queue.clear();
}

// Сообщение ставится в очередь для отправки в сетевом потоке.
void TCPSocketsSample::Client::NetworkThread::send(Message *message)
{
	send_queue.push(message);
}

// Возвращается следующее полученное сообщение; nullptr, если очередь пуста.
TCPSocketsSample::Message *TCPSocketsSample::Client::NetworkThread::receive()
{
	return recv_queue.pop();
}

// Основной сетевой цикл, обрабатывающий двунаправленную потоковую передачу TCP-сообщений.
// TCP ориентирован на поток, поэтому границы сообщений отслеживаются через конечный автомат:
// RECEIVE_HEADER -> RECEIVE_PAYLOAD -> UNPACK_MESSAGE -> повтор.
// Формат протокола: [Header(type:4B, size:4B)] [Payload(переменный размер)].
void TCPSocketsSample::Client::NetworkThread::process()
{
	enum { RECEIVE_HEADER, RECEIVE_PAYLOAD, UNPACK_MESSAGE } recv_state = RECEIVE_HEADER;

	int recv_size = 0;
	int send_size = 0;

	BlobPtr send_blob = Blob::create();
	BlobPtr recv_blob = Blob::create();

	// Выполняет подключение сокета, если это запрошено (используется только Client).
	if (connect)
	{
		if (socket->connect(CLIENT_CONNECTION_TIMEOUT_MS))
		{
			Log::message("[Client::NetworkThread] Successfully connected to the server (%s:%d).\n", socket->getHost(), socket->getPort());
		}
		else
		{
			Log::warning("[Client::NetworkThread] Could not connect to the server at the specified address (%s:%d)!\n", socket->getHost(), socket->getPort());
			return;
		}
	}

	while (isRunning())
	{
		// ==================== Отправка исходящих сообщений ====================

		{
			if (send_blob->getSize() == 0)
			{
				Message *send_message = send_queue.pop();
				if (send_message)
				{
					send_size = send_message->pack(send_blob);
					send_blob->seekSet(0);

					delete send_message;
					send_message = nullptr;
				}
			}

			if (send_blob->getSize())
			{
				if (socket->isReadyToWrite(CLIENT_WRITE_TIMEOUT_US))
				{
					int written = socket->writeStream(send_blob, send_size);

					if (written != send_size)
					{
						// Не удалось отправить сообщение полностью. Должно быть, что-то пошло не так с соединением.

						Log::message("[Client::NetworkThread] The remote connection was closed or an error has occured. Closing the socket.\n");

						socket->close();
						return;
					}

					send_blob->clear();
				}
			}
		}

		// ==================== Приём входящих сообщений ====================

		{
			switch (recv_state)
			{
				case RECEIVE_HEADER:
				{
					// Далее читаем заголовок следующего сообщения.

					recv_blob->resize(sizeof(Message::Header));
					recv_blob->seekSet(0);

					recv_size = sizeof(Message::Header);
					break;
				}

				case RECEIVE_PAYLOAD:
				{
					// Заголовок сообщения получен, далее читаем следующую за ним полезную нагрузку.
					// Здесь мы распаковываем заголовок, проверяем его на валидность и сохраняем размер полезной нагрузки сообщения.

					Message::Header header;

					recv_blob->seekSet(0);
					recv_blob->read(&header, sizeof(Message::Header));

					// Мы не сбрасываем курсор blob обратно в начало после Blob::read,
					// чтобы следующий вызов Socket::recvStream с этим blob
					// не перезаписал заголовок.

					int type = header.type;
					int size = header.size;

					bool valid = (size >= 0 && size <= RECV_BUFFER_SIZE) && (type >= 0 && type < Message::TYPE::NUM_TYPES);

					if (valid)
					{
						recv_blob->resize(size);
						recv_size = Math::max(0, size - int(sizeof(Message::Header)));
					}
					else
					{
						// Размер или тип сообщения недействительны.

						// Вероятно, это связано с тем, что мы каким-то образом потеряли отслеживание начала и конца сообщений
						// во входящем потоке данных. Наша позиция в потоке теперь неопределена,
						// и на этом этапе мы мало что можем сделать. Закрываем соединение.

						if (size > RECV_BUFFER_SIZE)
							Log::message("[Client::NetworkThread] The message payload size was too large (%d)!\n", size);

						if (type < 0 || type >= Message::TYPE::NUM_TYPES)
							Log::message("[Client::NetworkThread] The message type was invalid (%d)!\n", type);

						Log::message("[Client::NetworkThread] Closing the connection.\n");
						socket->close();
						return;
					}

					break;
				}

				case UNPACK_MESSAGE:
				{
					// Сообщение получено полностью. Распаковываем его и сохраняем в очередь.

					recv_blob->seekSet(0); // Сбрасываем курсор blob в начало, чтобы прочитать всё сообщение, включая заголовок.
					Message *message = extract_message(recv_blob);

					if (message)
						recv_queue.push(message);

					recv_state = RECEIVE_HEADER;
					recv_blob->clear();
					recv_size = 0;

					break;
				}
			}

			if (recv_size > 0)
			{
				// Читаем следующую часть (заголовок или полезную нагрузку) сообщения из сокета.

				if (socket->isReadyToRead(CLIENT_READ_TIMEOUT_US))
				{
					int read = socket->readStream(recv_blob, recv_size);

					if (read == 0 || read != recv_size)
					{
						// Соединение было закрыто/сброшено/прервано, или произошла ошибка.

						Log::message("[Client::NetworkThread] The remote connection was terminated or an error has occured. Closing the socket.\n");

						socket->close();
						return;
					}

					switch (recv_state)
					{
						case RECEIVE_HEADER: recv_state = RECEIVE_PAYLOAD; break;
						case RECEIVE_PAYLOAD: recv_state = UNPACK_MESSAGE; break;
						default: break;
					}
				}
			}
		}
	}
}

// Сообщение создаётся на основе типа заголовка и десериализуется из blob.
TCPSocketsSample::Message *TCPSocketsSample::Client::NetworkThread::extract_message(Unigine::BlobPtr blob)
{
	Message *message = nullptr;
	Message::Header header;

	blob->read(&header, sizeof(Message::Header));
	blob->seekSet(0);

	// Соответствующий подкласс сообщения создаётся на основе типа
	switch (header.type)
	{
		case Message::TEXT: message = new TextMessage(); break;
		case Message::CAMERA: message = new CameraMessage(); break;
		default: message = nullptr; break;
	}

	if (message)
		message->unpack(blob);

	return message;
}

// Обработчик консольной команды: текстовое сообщение отправляется на сервер.
void TCPSocketsSample::Client::on_message_send_cmd(int argc, char **argv)
{
	StringStack<> text;

	// Аргументы объединяются в одну строку сообщения
	for (int i = 1; i < argc; i += 1)
	{
		text += argv[i];
		if (i != (argc - 1))
			text += " ";
	}

	thread.send(new TextMessage(text));
}

// =================================================================================
// SERVER IMPLEMENTATION
// =================================================================================

// Слушающий сокет создаётся, привязывается к адресу, поток приёма подключений запускается.
TCPSocketsSample::Server::Server(const Unigine::String &hostname, unsigned short port)
{
	SocketPtr socket = Socket::create(Socket::SOCKET_TYPE_STREAM, hostname, port);

	if (!socket->isOpened())
	{
		Log::warning("Could not resolve specified hostname (%s)!\n", hostname.get());
		return;
	}

	// Неблокирующий режим для операций приёма подключений
	socket->nonblock();

	// Сокет привязывается к указанному адресу
	if (!socket->bind())
	{
		Log::warning("Could not bind socket to the specified address (%s:%d)!\n", hostname.get(), int(port));
		return;
	}

	// Сокет переводится в режим прослушивания с ограничением очереди подключений
	socket->listen(MAX_CLIENT_CONNECTIONS);

	clients.reserve(MAX_CLIENT_CONNECTIONS);

	thread.start(socket);

	Console::addCommand(
		"send_msg",
		"[Network Sockets Sample] Send a text message to peer.",
		MakeCallback(this, &TCPSocketsSample::Server::on_message_send_cmd)
	);
}

// Все клиентские потоки уничтожаются, консольная команда удаляется из регистрации.
TCPSocketsSample::Server::~Server()
{
	for (int i = 0; i < clients.size(); i += 1)
	{
		if (Client::NetworkThread *client = clients[i])
			delete client;
	}

	Console::removeCommand("send_msg");
}

// Отключённые клиенты удаляются; новые подключения принимаются; сообщения обмениваются.
void TCPSocketsSample::Server::update()
{
	// Прерванные клиентские подключения очищаются
	for (int i = 0; i < clients.size(); i += 1)
	{
		Client::NetworkThread *client = clients[i];

		if (!client->isConnectionActive())
		{
			clients.removeFast(i--);
			delete client;
		}
	}

	// Новые подключения принимаются из очереди слушающего потока
	while (SocketPtr connection = thread.accept())
	{
		Client::NetworkThread *client = new Client::NetworkThread(connection, false);
		Log::message("[Server] Accepted a client connection (%s:%d).\n", client->getHostname(), client->getPort());
		clients.push_back(client);
	};

	// Сообщения обмениваются с каждым подключённым клиентом
	for (int i = 0; i < clients.size(); i += 1)
	{
		Client::NetworkThread *client = clients[i];

		// Входящие текстовые сообщения логируются
		if (Message *message = client->receive())
		{
			TextMessage *text_msg = dynamic_cast<TextMessage *>(message);
			if (text_msg && text_msg->text.get() && !text_msg->text.empty())
				Log::message("Received a text message from Client [%d]: %s\n", i, text_msg->text.get());
		}

		// Трансформация камеры рассылается всем клиентам каждый кадр
		if (PlayerPtr player = Game::getPlayer())
			client->send(new CameraMessage(player->getWorldPosition(), player->getWorldRotation()));
	}
}

// Поток приёма подключений запускается со слушающим сокетом.
void TCPSocketsSample::Server::NetworkThread::start(Unigine::SocketPtr socket)
{
	reset();

	this->socket = socket;

	run();
}

// Поток останавливается, слушающий сокет закрывается.
void TCPSocketsSample::Server::NetworkThread::reset()
{
	shutdown();

	if (socket)
	{
		socket->close();
		socket.clear();
	}
}

// Возвращается следующее принятое подключение; nullptr, если очередь пуста.
SocketPtr TCPSocketsSample::Server::NetworkThread::accept()
{
	ScopedLock lock(mutex);
	SocketPtr connection;

	if (connections.size())
		connection = connections.takeFirst();

	return connection;
}

// Входящие подключения принимаются и ставятся в очередь для обработки в основном потоке.
void TCPSocketsSample::Server::NetworkThread::process()
{
	while (isRunning())
	{
		SocketPtr client = Socket::create(Socket::SOCKET_TYPE_STREAM);

		// Принятое соединение добавляется в потокобезопасную очередь
		if (socket->accept(client))
		{
			ScopedLock lock(mutex);
			connections.push_back(client);
		}
	}
}

// Обработчик консольной команды: текстовое сообщение рассылается всем подключённым клиентам.
void TCPSocketsSample::Server::on_message_send_cmd(int argc, char **argv)
{
	StringStack<> text;

	for (int i = 1; i < argc; i += 1)
	{
		text += argv[i];
		if (i != (argc - 1))
			text += " ";
	}

	// Сообщение отправляется каждому подключённому клиенту
	for (int i = 0; i < clients.size(); i += 1)
		clients[i]->send(new TextMessage(text));
}

// =================================================================================
// MESSAGE SERIALIZATION
// =================================================================================

// TextMessage сериализуется: header + text_size + text_data.
size_t TCPSocketsSample::TextMessage::pack(Unigine::BlobPtr dst_blob)
{
	size_t cursor = dst_blob->tell();
	size_t packed = 0;

	// Заголовок записывается первым (будет обновлён с итоговым размером)
	packed += dst_blob->write(&header, sizeof(header));

	// Длина текста записывается, за ней следуют необработанные строковые данные
	size_t text_size = text.size();
	packed += dst_blob->write(&text_size, sizeof(text_size));
	packed += dst_blob->write(text.get(), text_size);

	// Заголовок обновляется с фактическим типом и размером
	header.type = getType();
	header.size = packed;

	dst_blob->seekSet(cursor);
	dst_blob->write(&header, sizeof(header));

	dst_blob->seekSet(cursor + packed);

	return packed;
}

// TextMessage десериализуется из blob.
size_t TCPSocketsSample::TextMessage::unpack(Unigine::BlobPtr src_blob)
{
	size_t unpacked = 0;

	unpacked += src_blob->read(&header, sizeof(header));

	size_t text_size = 0;

	unpacked += src_blob->read(&text_size, sizeof(text_size));

	if (text_size)
	{
		text.resize(text_size);
		unpacked += src_blob->read(text.getRaw(), text_size);
	}

	return unpacked;
}

// CameraMessage сериализуется: header + position (Vec3) + rotation (quat).
size_t TCPSocketsSample::CameraMessage::pack(Unigine::BlobPtr dst_blob)
{
	size_t cursor = dst_blob->tell();
	size_t packed = 0;

	packed += dst_blob->write(&header, sizeof(header));
	packed += dst_blob->write(&position, sizeof(position));
	packed += dst_blob->write(&rotation, sizeof(rotation));

	header.type = getType();
	header.size = packed;

	dst_blob->seekSet(cursor);
	dst_blob->write(&header, sizeof(header));

	dst_blob->seekSet(cursor + packed);

	return packed;
}

// CameraMessage десериализуется из blob.
size_t TCPSocketsSample::CameraMessage::unpack(Unigine::BlobPtr src_blob)
{
	size_t unpacked = 0;

	unpacked += src_blob->read(&header, sizeof(header));
	unpacked += src_blob->read(&position, sizeof(position));
	unpacked += src_blob->read(&rotation, sizeof(rotation));

	return unpacked;
}

// =================================================================================
// GUI IMPLEMENTATION
// =================================================================================

// UI-окно создаётся с кнопками Client/Server и полями ввода адреса.
void TCPSocketsSample::SampleGui::init(TCPSocketsSample *sample)
{
	this->sample = sample;
	is_onscreen = Console::isOnscreen();
	Console::setOnscreen(true);

	sample_description_window.createWindow(Gui::ALIGN_RIGHT);

	auto const &group_box = sample_description_window.getParameterGroupBox();

	auto vbox = WidgetVBox::create();
	auto buttons_hbox = WidgetHBox::create();

	start_client_btn = WidgetButton::create("Client");
	start_client_btn->setToggleable(true);
	start_client_btn->setToggled(false);
	start_client_btn->setHeight(24);
	start_client_btn->getEventClicked().connect(this, &SampleGui::on_start_client_btn_clicked);
	buttons_hbox->addChild(start_client_btn);

	start_server_btn = WidgetButton::create("Server");
	start_server_btn->setToggleable(true);
	start_server_btn->setToggled(false);
	start_server_btn->setHeight(24);
	start_server_btn->getEventClicked().connect(this, &SampleGui::on_start_server_btn_clicked);
	buttons_hbox->addChild(start_server_btn);

	auto spacer = WidgetSpacer::create();
	spacer->setOrientation(0);
	buttons_hbox->addChild(spacer);

	server_hostname_el = WidgetEditLine::create(DEFAULT_SERVER_HOSTNAME);
	server_hostname_el->setWidth(100);
	server_hostname_el->setHeight(18);
	server_hostname_el->setFontVOffset(-2);
	buttons_hbox->addChild(server_hostname_el);

	buttons_hbox->addChild(WidgetLabel::create(":"));

	server_port_el = WidgetEditLine::create(String::itoa(DEFAULT_SERVER_PORT).get());
	server_port_el->setWidth(45);
	server_port_el->setHeight(18);
	server_port_el->setFontVOffset(-2);
	server_port_el->setValidator(Gui::VALIDATOR_UINT);
	buttons_hbox->addChild(server_port_el);

	vbox->addChild(buttons_hbox);
	vbox->addChild(WidgetVBox::create(0, 5));

	client_connections_gbox = WidgetGroupBox::create("", 0, 5);
	vbox->addChild(client_connections_gbox);

	group_box->addChild(vbox, Gui::ALIGN_TOP);
	group_box->arrange();

	for (int i = 0; i < Engine::get()->getNumArgs(); i++)
	{
		String str = Engine::get()->getArg(i);
		if (str == "-server")
			start_server_btn->setToggled(true);
		else if (str == "-client")
			start_client_btn->setToggled(true);
	}
}

// Список подключений обновляется для отображения активных подключений клиента/сервера.
void TCPSocketsSample::SampleGui::update()
{
	auto add_connection_gui = [this](const char *hostname, unsigned short port)
	{
		auto hbox = WidgetHBox::create();
		hbox->addChild(WidgetLabel::create(String::format("%s:%d", hostname, int(port)).get()));
		client_connections_gbox->addChild(hbox);
	};

	// Предыдущие записи подключений очищаются
	while (client_connections_gbox->getNumChildren())
	{
		auto child = client_connections_gbox->getChild(0);
		client_connections_gbox->removeChild(child);
	}

	// Режим Client: отображается единственное подключение к серверу
	if (auto client = dynamic_cast<TCPSocketsSample::Client *>(sample->host))
	{
		if (client->isConnectionActive())
			add_connection_gui(client->getHostname(), client->getPort());
	}

	// Режим Server: перечисляются все подключённые клиенты
	else if (auto server = dynamic_cast<TCPSocketsSample::Server *>(sample->host))
	{
		auto const& clients = server->getClients();
		for (int i = 0; i < clients.size(); i += 1)
			add_connection_gui(clients[i]->getHostname(), clients[i]->getPort());
	}
}

// UI очищается, состояние консоли восстанавливается.
void TCPSocketsSample::SampleGui::shutdown()
{
	sample_description_window.shutdown();
	Console::setOnscreen(is_onscreen);
	sample = nullptr;
}

// Запускается режим Server; предыдущий хост уничтожается, если он существует.
void TCPSocketsSample::SampleGui::on_start_server_btn_clicked(const WidgetPtr &widget, int mouse)
{
	if (sample->host)
	{
		delete sample->host;
		sample->host = nullptr;
	}

	MUTE_EVENT(start_server_btn->getEventClicked());
	MUTE_EVENT(start_client_btn->getEventClicked());

	if (start_server_btn->isToggled())
	{
		// Server создаётся с адресом из полей ввода
		StringStack<> hostname;
		unsigned short port = 0;

		hostname = server_hostname_el->getText();
		port = (unsigned short) String::atoi(server_port_el->getText());

		sample->host = new Server(hostname, port);

		// Поля адреса блокируются, пока сервер работает
		server_hostname_el->setEnabled(false);
		server_port_el->setEnabled(false);

		start_client_btn->setToggled(false);
	}

	else
	{
		server_hostname_el->setEnabled(true);
		server_port_el->setEnabled(true);
	}
}

// Запускается режим Client; инициируется подключение к серверу.
void TCPSocketsSample::SampleGui::on_start_client_btn_clicked(const WidgetPtr &widget, int mouse)
{
	if (sample->host)
	{
		delete sample->host;
		sample->host = nullptr;
	}

	MUTE_EVENT(start_server_btn->getEventClicked());
	MUTE_EVENT(start_client_btn->getEventClicked());

	if (start_client_btn->isToggled())
	{
		// Client подключается к серверу по указанному адресу
		StringStack<> hostname;
		unsigned short port = 0;

		hostname = server_hostname_el->getText();
		port = (unsigned short) String::atoi(server_port_el->getText());

		sample->host = new Client(hostname, port);

		// Поля адреса блокируются, пока клиент подключён
		server_hostname_el->setEnabled(false);
		server_port_el->setEnabled(false);

		start_server_btn->setToggled(false);
	}

	else
	{
		server_hostname_el->setEnabled(true);
		server_port_el->setEnabled(true);
	}
}
