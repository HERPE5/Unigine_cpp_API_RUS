// Демонстрирует работу с UDP-сокетами для связи между собеседниками. Sender
// рассылает состояние камеры получателю по фиксированному адресу. Receiver синхронизирует свой
// обзор с полученными данными камеры. Протокол сообщений использует заголовки type+size.

#include "UDPSocketsSample.h"

#include <UnigineConsole.h>
#include <UnigineGame.h>

using namespace Unigine;

REGISTER_COMPONENT(UDPSocketsSample);

namespace
{
	constexpr const char *DEFAULT_RECEIVER_HOSTNAME = "127.0.0.1";
	constexpr unsigned short DEFAULT_RECEIVER_PORT = 64'000;

	constexpr int SEND_BUFFER_SIZE = 4096;
	constexpr int RECV_BUFFER_SIZE = 4096;
}

// GUI инициализируется; собеседник (Sender или Receiver) создаётся по нажатию кнопки.
void UDPSocketsSample::init()
{
	gui.init(this);
}

// Активный собеседник (Sender или Receiver) обновляется каждый кадр.
void UDPSocketsSample::update()
{
	if (peer)
		peer->update();
}

// Активный собеседник уничтожается, GUI очищается.
void UDPSocketsSample::shutdown()
{
	if (peer)
	{
		delete peer;
		peer = nullptr;
	}

	gui.shutdown();
}

// ================================================================
// SENDER IMPLEMENTATION
// ================================================================

// Сетевой поток запускается, консольная команда регистрируется.
UDPSocketsSample::Sender::Sender(const Unigine::String &hostname, unsigned short port)
{
	thread.start(hostname, port);

	Console::addCommand(
		"send_msg",
		"[Network Sockets Sample] Send a text message to peer.",
		MakeCallback(this, &UDPSocketsSample::Sender::on_message_send_cmd)
	);
}

// Консольная команда удаляется из регистрации.
UDPSocketsSample::Sender::~Sender()
{
	Console::removeCommand("send_msg");
}

// Трансформация камеры отправляется получателю каждый кадр.
void UDPSocketsSample::Sender::update()
{
	if (!thread.isRunning())
		return;

	// Текущие позиция и вращение камеры рассылаются
	PlayerPtr player = Game::getPlayer();
	if (player)
	{
		thread.send(new CameraMessage(
			player->getWorldPosition(),
			player->getWorldRotation())
		);
	}
}

// Обработчик консольной команды: текстовое сообщение отправляется получателю.
void UDPSocketsSample::Sender::on_message_send_cmd(int argc, char **argv)
{
	BlobPtr message = Blob::create();
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

// ================================================================

// UDP-сокет создаётся с целевым адресом; поток запускается.
bool UDPSocketsSample::Sender::NetworkThread::start(const String &hostname, unsigned short port)
{
	// UDP-сокет создаётся - целевой адрес используется для последующих вызовов send.
	// Собственный адрес сокета назначается автоматически операционной системой.
	socket = Socket::create(Socket::SOCKET_TYPE_DGRAM, hostname, port);

	if (!socket->isOpened())
	{
		Log::warning("Could not resolve specified hostname (%s)!\n", hostname.get());
		return false;
	}

	// Размер буфера отправки настраивается
	socket->send(SEND_BUFFER_SIZE);

	run();
	return true;
}

// Сообщение ставится в очередь для отправки в сетевом потоке.
void UDPSocketsSample::Sender::NetworkThread::send(Message *message)
{
	queue.push(message);
}

// Поток останавливается, сокет закрывается.
void UDPSocketsSample::Sender::NetworkThread::reset()
{
	shutdown();

	if (socket)
	{
		socket->close();
		socket = {};
	}

	queue.clear();
}

// Исходящие сообщения сериализуются и отправляются как UDP-датаграммы.
void UDPSocketsSample::Sender::NetworkThread::process()
{
	BlobPtr blob = Blob::create();

	while (isRunning())
	{
		// Следующее сообщение извлекается из очереди
		Message *message = queue.pop();

		if (message)
		{
			// Сообщение сериализуется в blob
			message->pack(blob);
			blob->seekSet(0);
			delete message;
		}

		// Датаграмма отправляется получателю
		if (blob->getSize())
		{
			socket->writeStream(blob, blob->getSize());
			blob->clear();
		}
	}
}

// ================================================================
// RECEIVER IMPLEMENTATION
// ================================================================

// Сетевой поток запускается; управление игроком отключается для синхронизации камеры.
UDPSocketsSample::Receiver::Receiver(const Unigine::String &hostname, unsigned short port)
{
	thread.start(hostname, port);

	// Управление игроком отключается, чтобы камера могла синхронизироваться с sender
	PlayerPtr player = Game::getPlayer();
	if (player)
		player->setControlled(false);
}

// Управление игроком восстанавливается.
UDPSocketsSample::Receiver::~Receiver()
{
	PlayerPtr player = Game::getPlayer();
	if (player)
		player->setControlled(true);
}

// Входящие сообщения обрабатываются; камера синхронизируется при получении CameraMessage.
void UDPSocketsSample::Receiver::update()
{
	if (!thread.isRunning())
		return;

	Message *message = thread.receive();
	int processed = 0;

	// Сообщения обрабатываются с ограничением на кадр, чтобы избежать зависаний
	while (message && processed < message_process_limit)
	{
		switch (message->getType())
		{
			case Message::TEXT:
			{
				// Текстовое сообщение выводится в консоль
				TextMessage *text_msg = dynamic_cast<TextMessage *>(message);

				if (text_msg)
					Log::message("Received a text message from peer: \"%s\".\n", text_msg->text.get());

			} break;

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

			} break;

			default: break;
		}

		delete message;
		message = thread.receive();
		processed += 1;
	}
}

// ================================================================

// UDP-сокет создаётся, привязывается к адресу, поток запускается.
bool UDPSocketsSample::Receiver::NetworkThread::start(const String &hostname, unsigned short port)
{
	// UDP-сокет создаётся с локальным адресом привязки
	socket = Socket::create(Socket::SOCKET_TYPE_DGRAM, hostname, port);

	if (!socket->isOpened())
	{
		Log::warning("Could not resolve specified hostname (%s)!\n", hostname.get());
		return false;
	}

	// Размер буфера приёма настраивается
	socket->recv(RECV_BUFFER_SIZE);

	// Неблокирующий режим для опроса без остановки потока
	socket->nonblock();

	// Сокет привязывается для прослушивания входящих датаграмм
	if (!socket->bind())
	{
		Log::warning("Could not bind socket to the specified address (%s:%d)!\n", hostname.get(), port);
		return false;
	}

	run();
	return true;
}

// Поток останавливается, сокет закрывается.
void UDPSocketsSample::Receiver::NetworkThread::reset()
{
	shutdown();

	if (socket)
	{
		socket->close();
		socket = nullptr;
	}

	queue.clear();
}

// Возвращается следующее полученное сообщение; nullptr, если очередь пуста.
UDPSocketsSample::Message *UDPSocketsSample::Receiver::NetworkThread::receive()
{
	return queue.pop();
}

// Входящие UDP-датаграммы принимаются и разбираются в сообщения.
void UDPSocketsSample::Receiver::NetworkThread::process()
{
	BlobPtr blob = Blob::create();

	while (isRunning())
	{
		// Датаграмма считывается из сокета
		socket->readStream(blob, RECV_BUFFER_SIZE);
		blob->seekSet(0);

		// Сообщение извлекается и ставится в очередь для основного потока
		if (blob->getSize())
		{
			Message *message = extract_message(blob);

			if (message)
				queue.push(message);
		}

		blob->clear();
	}
}

// Сообщение создаётся на основе типа заголовка и десериализуется из blob.
UDPSocketsSample::Message *UDPSocketsSample::Receiver::NetworkThread::extract_message(Unigine::BlobPtr blob)
{
	Message::Header header = {};
	Message *message = nullptr;

	blob->read(&header, sizeof(header));
	blob->seekSet(0);

	// Соответствующий подкласс сообщения создаётся на основе типа
	switch (header.type)
	{
		case Message::TEXT: message = new TextMessage(); break;
		case Message::CAMERA: message = new CameraMessage(); break;
		default: break;
	}

	if (message)
		message->unpack(blob);

	return message;
}

// ================================================================
// MESSAGE SERIALIZATION
// ================================================================

// TextMessage сериализуется: header + text_size + text_data.
size_t UDPSocketsSample::TextMessage::pack(Unigine::BlobPtr dst_blob)
{
	size_t cursor = dst_blob->tell();
	size_t packed = 0;

	packed += dst_blob->write(&header, sizeof(header));

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
size_t UDPSocketsSample::TextMessage::unpack(Unigine::BlobPtr src_blob)
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
size_t UDPSocketsSample::CameraMessage::pack(Unigine::BlobPtr dst_blob)
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
size_t UDPSocketsSample::CameraMessage::unpack(Unigine::BlobPtr src_blob)
{
	size_t unpacked = 0;

	unpacked += src_blob->read(&header, sizeof(header));
	unpacked += src_blob->read(&position, sizeof(position));
	unpacked += src_blob->read(&rotation, sizeof(rotation));

	return unpacked;
}

// ================================================================
// GUI IMPLEMENTATION
// ================================================================

// Запускается режим Sender; предыдущий собеседник уничтожается, если он существует.
void UDPSocketsSample::SampleGui::on_start_sender_btn_clicked(const WidgetPtr &widget, int mouse)
{
	if (sample->peer)
	{
		delete sample->peer;
		sample->peer = nullptr;
	}

	// События кнопок временно отключаются для предотвращения повторного входа
	start_recver_btn->getEventClicked().setEnabled(false);
	start_sender_btn->getEventClicked().setEnabled(false);

	if (start_sender_btn->isToggled())
	{
		// Sender создаётся с адресом целевого получателя
		StringStack<> hostname;
		unsigned short port = 0;

		hostname = recv_host_el->getText();
		port = (unsigned short) String::atoi(recv_port_el->getText());

		sample->peer = new Sender(hostname, port);

		// Поля адреса блокируются, пока sender работает
		recv_host_el->setEnabled(false);
		recv_port_el->setEnabled(false);

		start_recver_btn->setToggled(false);
	}

	else
	{
		recv_host_el->setEnabled(true);
		recv_port_el->setEnabled(true);
	}

	start_recver_btn->getEventClicked().setEnabled(true);
	start_sender_btn->getEventClicked().setEnabled(true);
}

// Запускается режим Receiver; сокет привязывается к адресу прослушивания.
void UDPSocketsSample::SampleGui::on_start_recver_btn_clicked(const WidgetPtr &widget, int mouse)
{
	if (sample->peer)
	{
		delete sample->peer;
		sample->peer = nullptr;
	}

	start_recver_btn->getEventClicked().setEnabled(false);
	start_sender_btn->getEventClicked().setEnabled(false);

	if (start_recver_btn->isToggled())
	{
		// Receiver создаётся и привязывается к указанному адресу
		StringStack<> hostname;
		unsigned short port = 0;

		hostname = recv_host_el->getText();
		port = (unsigned short) String::atoi(recv_port_el->getText());

		sample->peer = new Receiver(hostname, port);

		// Поля адреса блокируются, пока receiver работает
		recv_host_el->setEnabled(false);
		recv_port_el->setEnabled(false);

		start_sender_btn->setToggled(false);
	}

	else
	{
		recv_host_el->setEnabled(true);
		recv_port_el->setEnabled(true);
	}

	start_recver_btn->getEventClicked().setEnabled(true);
	start_sender_btn->getEventClicked().setEnabled(true);
}

// UI-окно создаётся с кнопками Sender/Receiver и полями ввода адреса.
void UDPSocketsSample::SampleGui::init(UDPSocketsSample *sample)
{
	this->sample = sample;
	is_onscreen = Console::isOnscreen();
	Console::setOnscreen(true);

	sample_description_window.createWindow(Gui::ALIGN_RIGHT);

	auto const &group_box = sample_description_window.getParameterGroupBox();

	auto hbox = WidgetHBox::create();
	group_box->addChild(hbox, Gui::ALIGN_TOP);

	start_sender_btn = WidgetButton::create("Sender");
	start_sender_btn->setToggleable(true);
	start_sender_btn->setToggled(false);
	start_sender_btn->setHeight(24);
	start_sender_btn->getEventClicked().connect(this, &SampleGui::on_start_sender_btn_clicked);
	hbox->addChild(start_sender_btn);

	start_recver_btn = WidgetButton::create("Receiver");
	start_recver_btn->setToggleable(true);
	start_recver_btn->setToggled(false);
	start_recver_btn->setHeight(24);
	start_recver_btn->getEventClicked().connect(this, &SampleGui::on_start_recver_btn_clicked);
	hbox->addChild(start_recver_btn);

	auto spacer = WidgetSpacer::create();
	spacer->setOrientation(0);
	hbox->addChild(spacer);

	recv_host_el = WidgetEditLine::create(DEFAULT_RECEIVER_HOSTNAME);
	recv_host_el->setWidth(100);
	recv_host_el->setHeight(18);
	recv_host_el->setFontVOffset(-2);
	hbox->addChild(recv_host_el);

	hbox->addChild(WidgetLabel::create(":"));

	recv_port_el = WidgetEditLine::create(String::itoa(DEFAULT_RECEIVER_PORT).get());
	recv_port_el->setWidth(45);
	recv_port_el->setHeight(18);
	recv_port_el->setFontVOffset(-2);
	recv_port_el->setValidator(Gui::VALIDATOR_UINT);
	hbox->addChild(recv_port_el);

	for (int i = 0; i < Engine::get()->getNumArgs(); i++)
	{
		String str = Engine::get()->getArg(i);
		if (str == "-server")
			start_recver_btn->setToggled(true);
		else if (str == "-client")
			start_sender_btn->setToggled(true);
	}
}

// UI очищается, состояние консоли восстанавливается.
void UDPSocketsSample::SampleGui::shutdown()
{
	sample_description_window.shutdown();
	Console::setOnscreen(is_onscreen);
	sample = nullptr;
}
