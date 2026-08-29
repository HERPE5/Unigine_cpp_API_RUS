// Пример работы с UDP-сокетами, демонстрирующий связь между собеседниками без установления соединения.
// Sender рассылает трансформацию камеры Receiver'у по фиксированному адресу каждый кадр.
// Receiver привязывается к адресу и синхронизирует свою камеру с входящими данными.
// В отличие от TCP, UDP не имеет состояния соединения - датаграммы отправляются независимо.
// Сообщения используют бинарный протокол: заголовок (тип + размер), за которым следует полезная нагрузка.

#pragma once

#include <UnigineCallback.h>
#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>
#include <UnigineStreams.h>
#include <UnigineThread.h>

#include "../../menu_ui/SampleDescriptionWindow.h"

using namespace Unigine;

// Основной компонент, управляющий жизненным циклом примера UDP-сети.
class UDPSocketsSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(UDPSocketsSample, Unigine::ComponentBase);

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

private:
	// Базовый класс для сетевых сообщений.
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

	// Потокобезопасная очередь сетевых сообщений.
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

	// Простой абстрактный класс для Sender и Receiver, используемый для упрощения логики примера.
	struct IPeer
	{
		virtual void update() = 0;
		virtual ~IPeer() = default;
	};

	// 'Sender'. Отправляет сообщения сетевому собеседнику (Receiver) по указанному адресу.
	class Sender : public IPeer
	{
	public:
		Sender(const Unigine::String &hostname, unsigned short port);
		~Sender() override;

		void update() override;

	private:
		void on_message_send_cmd(int argc, char **argv);

		// Сетевой поток Sender. Отправляет сообщения собеседнику Receiver.
		struct NetworkThread : public Unigine::Thread
		{
			~NetworkThread() { reset(); }
			bool start(const Unigine::String &hostname, unsigned short port);
			void send(Message *message);

		private:
			void process() override;
			void reset();

			Unigine::SocketPtr socket;
			MessageQueue queue;
		} thread;
	};

	// 'Receiver'. Привязывается к указанному адресу и получает сообщения от сетевого собеседника (Sender).
	class Receiver : public IPeer
	{
	public:
		Receiver(const Unigine::String &hostname, unsigned short port);
		~Receiver() override;

		void update() override;

	private:

		// Сетевой поток Receiver. Получает сообщения от собеседника.
		struct NetworkThread : public Unigine::Thread
		{
			~NetworkThread() { reset(); }
			bool start(const Unigine::String &hostname, unsigned short port);

			Message *receive();

		private:
			void process() override;
			void reset();

			Message *extract_message(Unigine::BlobPtr blob); // Извлекает сообщение из переданного необработанного бинарного blob.

			Unigine::SocketPtr socket;
			MessageQueue queue;
		} thread;

		int message_process_limit = 8; // максимум сообщений, обрабатываемых за одно обновление движка
	};

	// ================================================================

	struct SampleGui : Unigine::EventConnections
	{
		void init(UDPSocketsSample *sample);
		void shutdown();

		void on_start_sender_btn_clicked(const Unigine::WidgetPtr &widget, int mouse);
		void on_start_recver_btn_clicked(const Unigine::WidgetPtr &widget, int mouse);

		bool is_onscreen;
		UDPSocketsSample *sample = nullptr;
		Unigine::WidgetEditLinePtr recv_host_el;
		Unigine::WidgetEditLinePtr recv_port_el;
		Unigine::WidgetButtonPtr start_sender_btn;
		Unigine::WidgetButtonPtr start_recver_btn;
		SampleDescriptionWindow sample_description_window;
	};

	// ================================================================

	void init();
	void update();
	void shutdown();

	IPeer *peer = nullptr;
	SampleGui gui;
};
