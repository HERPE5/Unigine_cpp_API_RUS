// Пример работы с TCP-сокетами, демонстрирующий архитектуру клиент-сервер.
// Сервер прослушивает подключения, принимает несколько клиентов и рассылает
// трансформацию камеры каждый кадр. Клиенты подключаются, получают обновления камеры и
// синхронизируют свой обзор с позицией сервера. Текстовыми сообщениями можно обмениваться
// через консольную команду "send_msg". Сообщения используют бинарный протокол с
// заголовком (тип + размер), за которым следуют данные полезной нагрузки.

#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>
#include <UnigineStreams.h>
#include <UnigineThread.h>

#include "../../menu_ui/SampleDescriptionWindow.h"

// Основной компонент, управляющий жизненным циклом примера TCP-сети.
class TCPSocketsSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(TCPSocketsSample, Unigine::ComponentBase);

	COMPONENT_INIT(init)
	COMPONENT_UPDATE(update)
	COMPONENT_SHUTDOWN(shutdown)

private:
	// Базовый класс для сообщений, которыми обмениваются собеседники.
	struct Message
	{
		enum TYPE { TEXT, CAMERA, NUM_TYPES };

		struct Header
		{
			int type = TEXT;
			int size = 0; // Размер сообщения (включая заголовок).
		};

		virtual ~Message() = default;

		virtual int getType() const = 0;
		virtual Message *copy() const = 0;
		virtual size_t pack(Unigine::BlobPtr dst_blob) = 0;
		virtual size_t unpack(Unigine::BlobPtr src_blob) = 0;

		Header header;
	};

	// Простое текстовое сообщение.
	struct TextMessage : public Message
	{
		TextMessage() = default;
		TextMessage(TextMessage const &) = default;
		~TextMessage() override = default;

		TextMessage(const Unigine::StringStack<> &text): text { text } {}

		int getType() const override { return TEXT; }
		virtual Message *copy() const override { return new TextMessage(*this); }
		virtual size_t pack(Unigine::BlobPtr dst_blob) override;
		virtual size_t unpack(Unigine::BlobPtr src_blob) override;

		Unigine::StringStack<> text;
	};

	// Сообщение, содержащее трансформацию камеры.
	struct CameraMessage : public Message
	{
		CameraMessage() = default;
		~CameraMessage() override = default;

		CameraMessage(const Unigine::Math::Vec3 &position, const Unigine::Math::quat &rotation):
			position { position },
			rotation { rotation }
		{}

		int getType() const override { return CAMERA; }
		virtual Message *copy() const override { return new CameraMessage(*this); }
		virtual size_t pack(Unigine::BlobPtr dst_blob) override;
		virtual size_t unpack(Unigine::BlobPtr src_blob) override;

		Unigine::Math::Vec3 position;
		Unigine::Math::quat rotation;
	};

	// ================================================================

	// Потокобезопасная очередь для сетевых сообщений.
	class MessageQueue
	{
	public:
		void push(Message *message)
		{
			Unigine::ScopedLock lock(mutex);

			queue.push_back(message);

			if (queue.size() >= max_size)
			{
				Message *new_message = queue.takeFirst();

				if (new_message)
					delete new_message;
			}
		}

		Message *pop()
		{
			Unigine::ScopedLock lock(mutex);
			Message *message = nullptr;

			if (queue.size() && (message = queue.takeFirst()) != nullptr)
			{
				Message *original = message;
				message = original->copy();
				delete original;
			}

			return message;
		}

		void clear()
		{
			while (queue.size())
			{
				Message *message = queue.takeLast();
				if (message)
					delete message;
			}
		}

	private:
		Unigine::Vector<Message *> queue;
		Unigine::Mutex mutex;
		int max_size = 8;
	};

	// ================================================================

	// Простой абстрактный класс для Client и Server, вспомогательный элемент для упрощения логики примера.
	struct IHost
	{
		virtual void update() = 0;
		virtual ~IHost() = default;
	};

	// Клиент, который может отправлять и получать сообщения от сервера.
	class Client : public IHost
	{
	public:

		// Сетевой поток клиента. Обрабатывает исходящие и входящие сообщения от/к серверу.
		class NetworkThread : public Unigine::Thread
		{
		public:
			NetworkThread() = default;
			NetworkThread(Unigine::SocketPtr socket, bool connect) { start(socket, connect); }
			~NetworkThread() { reset(); }

			void start(Unigine::SocketPtr socket, bool connect); // Запускает сетевой поток с использованием указанного сокета. Опционально выполняет "connect" к сокету.
			void send(Message *message); // Помещает сообщение в очередь исходящих сообщений. Оно будет отправлено позже в методе `process` потока.
			Message *receive(); // Извлекает сообщение из очереди входящих сообщений. Если очередь пуста, возвращается нулевой указатель.

			bool isConnectionActive() const { return isRunning(); }
			char const *getHostname() const { return socket ? socket->getHost() : ""; }
			unsigned short getPort() const { return socket ? socket->getPort() : 0; }

		private:
			void process() override; // Метод потока, содержащий всю логику обработки сетевых сообщений.
			void reset(); // Останавливает поток и очищает его состояние.

			Message *extract_message(Unigine::BlobPtr blob); // Извлекает сообщение из необработанного бинарного blob.

			MessageQueue recv_queue;
			MessageQueue send_queue;
			Unigine::SocketPtr socket;
			bool connect = false;
		};

		Client(const Unigine::String &hostname, unsigned short port);
		~Client() override;

		bool isConnectionActive() const { return thread.isConnectionActive(); }

		char const *getHostname() const { return thread.getHostname(); }
		unsigned short getPort() const { return thread.getPort(); }

		void update() override; // Функция обновления клиента. Здесь обрабатываются входящие сообщения от сервера и новые сообщения добавляются в очередь исходящих сообщений.

	private:
		void on_message_send_cmd(int argc, char **argv);

		NetworkThread thread;
		int message_process_limit = 8;
	};

	// ================================================================

	// Сервер. Управляет несколькими клиентскими подключениями и обрабатывает входящие и исходящие сообщения от/к клиентам.
	class Server : public IHost
	{
	public:
		Server(const Unigine::String &hostname, unsigned short port);
		~Server() override;

		void update() override; // Функция обновления сервера. Здесь обновляются клиентские подключения и обрабатываются входящие/исходящие сообщения.

		const Unigine::Vector<Client::NetworkThread *> &getClients() const { return clients; }

	private:

		// Сетевой поток сервера. Просто принимает новые клиентские подключения.
		class NetworkThread : public Unigine::Thread
		{
		public:
			~NetworkThread() { reset(); }

			void start(Unigine::SocketPtr socket);
			Unigine::SocketPtr accept(); // Забирает новое принятое клиентское подключение как сокет.

		private:
			void process() override; // Метод потока, содержащий всю логику обработки сети.
			void reset();

			Unigine::Vector<Unigine::SocketPtr> connections; // Очередь принятых подключений.
			Unigine::SocketPtr socket; // Слушающий сокет сервера.
			Unigine::Mutex mutex;
		};

		void on_message_send_cmd(int argc, char **argv);

		Unigine::Vector<Client::NetworkThread *> clients; // Сетевые потоки клиентов для каждого принятого клиентского подключения.
		NetworkThread thread;
	};

	// ================================================================

	struct SampleGui : Unigine::EventConnections
	{
		void init(TCPSocketsSample *sample);
		void update();
		void shutdown();

		void on_start_server_btn_clicked(const Unigine::WidgetPtr &widget, int mouse);
		void on_start_client_btn_clicked(const Unigine::WidgetPtr &widget, int mouse);

		bool is_onscreen = false;
		TCPSocketsSample *sample = nullptr;
		Unigine::WidgetButtonPtr start_client_btn;
		Unigine::WidgetButtonPtr start_server_btn;
		Unigine::WidgetEditLinePtr server_port_el;
		Unigine::WidgetEditLinePtr server_hostname_el;
		Unigine::WidgetGroupBoxPtr client_connections_gbox;
		SampleDescriptionWindow sample_description_window;
	};

	void init();
	void update();
	void shutdown();

	IHost *host = nullptr;
	SampleGui gui;
};
