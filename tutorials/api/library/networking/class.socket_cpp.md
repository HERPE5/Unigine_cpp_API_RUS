# Unigine::Socket Class (CPP)

**Header:** #include <UnigineStreams.h>

**Inherits from:** Stream


Этот класс предоставляет базовую функциональность для сетевого взаимодействия с использованием потоковых сокетов.


### Пример использования


В этом примере мы создаём UDP-сокеты: сервер и пять клиентов.

- Сервер отправляет широковещательные пакеты, содержащие ID клиента-получателя.
- Каждый клиент обрабатывает только те сообщения, которые были адресованы ему.
- В методе *update()* мира сервер отправляет сообщения, адресованные клиентам **2** и **5**.


В заголовочном файле `AppWorldLogic.h` мы описываем наш клиент и сервер и объявляем сервер и массив клиентов.


```cpp
#ifndef __APP_WORLD_LOGIC_H__
#define __APP_WORLD_LOGIC_H__

#include <UnigineLogic.h>
#include <UnigineStreams.h>
#include <UnigineInput.h>
#include <UnigineGame.h>

 // используемый UDP-порт
const int UDP_PORT = 8889;

// размер буфера приёма UDP
const int RECV_SIZE = 7;

// размер буфера отправки UDP
const int SEND_SIZE = 7;

/* ... */

/// Класс, представляющий серверный сокет
class ServerSocket
{
public:
	/// Конструктор сервера
	ServerSocket()
	{
		// создание UDP-сокета
		socket = Unigine::Socket::create(Unigine::Socket::SOCKET_TYPE_DGRAM);

		// открытие сокета на указанном порту с указанным широковещательным адресом
		socket->open("127.255.255.255", UDP_PORT);

		// задание размера буфера отправки
		socket->send(SEND_SIZE);

		// задание сокета как широковещательного
		socket->broadcast();

		// задание сокета как неблокирующего
		socket->nonblock();
	}

	/// Деструктор сервера
	~ServerSocket()
	{
		// закрытие сокета
		socket->close();

		// очистка сокета
		socket.clear();
	}

	/// метод отправки сообщения определённому клиенту
	void send_message(int client_num, const char* message)
	{
		// подготовка сообщения для получения клиентом с заданным client_id
		Unigine::BlobPtr blob = Unigine::Blob::create();
		blob->clear();
		blob->writeShort(client_num);
		blob->write(message, strlen(message));
		int size = blob->getSize();

		// отправка сообщения
		socket->write(blob->getData(), size);
		blob.clear();
	}

private:
	// указатель на сокет
	Unigine::SocketPtr socket;
};

/// Класс, представляющий клиентский сокет
class ClientSocket {

public:

	/// Конструктор клиента
	ClientSocket()
	{
		// создание UDP-сокета
		socket = Unigine::Socket::create(Unigine::Socket::SOCKET_TYPE_DGRAM);

		// открытие сокета на указанном порту

		socket->open(UDP_PORT);

		// задание размера буфера приёма
		socket->recv(RECV_SIZE);

		// привязка сокета к адресу, определённому из хоста, использованного при инициализации сокета
		socket->bind();

		// задание сокета как неблокирующего
		socket->nonblock();
	}

	/// Деструктор клиента
	~ClientSocket()
	{
		// закрытие сокета
		socket->close();

		// очистка сокета
		socket.clear();
	}

	void setID(int num)
	{
		// задание ID клиента
		id = num;
	}

	/// метод проверки полученных от сервера пакетов
	int update()
	{
		// подготовка blob для чтения сообщения
		Unigine::BlobPtr temp_blob = Unigine::Blob::create();
		temp_blob->clear();

		// чтение данных из сокета
		socket->readStream(temp_blob, RECV_SIZE);

		if (temp_blob->getSize() > 0) {

			// установка текущей позиции в начало
			temp_blob->seekSet(0);

			// получение ID клиента
			int num_client = temp_blob->readShort();

			// проверка, адресовано ли полученное сообщение именно этому клиенту, и его обработка
			if (num_client == id) {
				Unigine::Log::message("\nClient[%d] - OPERATION_CODE: %s", id, temp_blob->readLine().get());
			}
		}
		return 1;
	}
private:
	// указатель на сокет
	Unigine::SocketPtr socket;

	// ID клиента
	int id = 0;
};

class AppWorldLogic : public Unigine::WorldLogic
{

public:
	AppWorldLogic();
	virtual ~AppWorldLogic();

	int init() override;

	int update() override;
	int postUpdate() override;
	int updatePhysics() override;

	int shutdown() override;

	int save(const Unigine::StreamPtr &stream) override;
	int restore(const Unigine::StreamPtr &stream) override;
private:

	// объявление клиентского и серверного сокетов
	ServerSocket server_socket;
	ClientSocket clients[5];
};

#endif // __APP_WORLD_LOGIC_H__

```


В файле реализации `AppWorldLogic.cpp` мы делаем следующее:


- В методе *AppWorldLogic::init()* мы инициализируем наших клиентов.
- В *AppWorldLogic::update()* мы проверяем, какие клавиши были нажаты, и отправляем сообщения соответствующим клиентам. Здесь же мы вызываем метод *update()* для всех клиентов для обработки сообщений сервера.

  - **Клиент 2** - по клавише ENTER
  - **Клиент 5** - по клавишам WASD


Вот методы *AppWorldLogic::init()* и *AppWorldLogic::update()*:


```cpp
// AppWorldLogic.cpp

using namespace Unigine;

/* ... */

int AppWorldLogic::init()
{
	//инициализация ID клиентов
	for (int i = 0; i < 5; i++)
		clients[i].setID(i+1);

	return 1;
}

int AppWorldLogic::update()
{
	// отправка сообщений клиентам 2 и 5 при нажатии клавиш
	if (Input::isKeyDown(Input::KEY_E))
		server_socket.send_message(2, "E");
	else if (Input::isKeyDown(Input::KEY_W))
		server_socket.send_message(5, "W");
	else if (Input::isKeyDown(Input::KEY_A))
		server_socket.send_message(5, "A");
	else if (Input::isKeyDown(Input::KEY_S))
		server_socket.send_message(5, "S");
	else if (Input::isKeyDown(Input::KEY_D))
		server_socket.send_message(5, "D");

	// обновление клиентов
	for (int i = 0; i < 5; i++)
		clients[i].update();

	return 1;
}
/* ... */

```


### См. также


Примеры API, демонстрирующие управление сокетами через API.


- **C++**:

  -
  -
- **UnigineScript**:

  -
  -
  -
  -
  -


## Класс Socket

### Перечисления

## SOCKET_TYPE

| Название | Описание |
|---|---|
| **SOCKET_TYPE_STREAM** = 0 | Сокет для TCP-пакетов. |
| **SOCKET_TYPE_DGRAM** = 1 | Сокет для UDP-пакетов. |

### Методы класса

---

## static SocketPtr create ( Socket::SOCKET_TYPE type )

Создаёт сокет указанного типа. При получении данных сокетом будут приниматься пакеты со всех сетевых интерфейсов. При отправке данных сокетом будет использоваться IP-адрес по умолчанию.
### Аргументы

- *[Socket::SOCKET_TYPE](../../../api/library/networking/class.socket_cpp.md#SOCKET_TYPE)* **type** - Тип сокета для TCP- или UDP-соединений.

## static SocketPtr create ( Socket::SOCKET_TYPE type , int port )

Создаёт сокет для TCP- или UDP-соединений и открывает его на заданном порту. При получении данных сокетом будут приниматься пакеты со всех сетевых интерфейсов. При отправке данных сокетом будет использоваться IP-адрес по умолчанию.
### Аргументы

- *[Socket::SOCKET_TYPE](../../../api/library/networking/class.socket_cpp.md#SOCKET_TYPE)* **type** - Тип сокета для TCP- или UDP-соединений.
- *int* **port** - Порт, на котором будет открыт сокет.

## static SocketPtr create ( Socket::SOCKET_TYPE type , const char * host , int port )

Создаёт сокет для TCP- или UDP-соединений и открывает его на заданном хосте и заданном порту. Хост задаёт адрес, с которого и на который будут отправляться данные.
### Аргументы

- *[Socket::SOCKET_TYPE](../../../api/library/networking/class.socket_cpp.md#SOCKET_TYPE)* **type** - Тип сокета для TCP- или UDP-соединений.
- *const char ** **host** - Хост, на котором будет открыт сокет.
- *int* **port** - Порт, на котором будет открыт сокет.

## int getFD ( ) const

Возвращает файловый дескриптор сокета.
### Возвращаемое значение

Файловый дескриптор сокета.
## const char * getHost ( ) const

Возвращает имя хоста, на котором открыт сокет.
### Возвращаемое значение

Имя хоста.
## int getPort ( ) const

Возвращает номер порта, на котором открыт сокет.
### Возвращаемое значение

Номер порта.
## bool accept ( const Ptr < Socket > & socket )

Принимает соединение на сокете.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Socket](../../../api/library/networking/class.socket_cpp.md)> &* **socket** - Сокет, привязанный к адресу и прослушивающий соединения.

### Возвращаемое значение

**true**, если соединение принято; иначе **false**.
## bool bind ( )

Привязывает сокет к адресу, определённому из хоста, использованного при инициализации сокета.
### Возвращаемое значение

true, если адрес привязан; иначе false.
## bool block ( )

Настраивает блокирующий сокет.
### Возвращаемое значение

true, если сокет является блокирующим; иначе false.
## bool broadcast ( )

Настраивает широковещательный сокет. Чтобы создать широковещательный сокет, сначала нужно создать его с широковещательным адресом хоста, а затем использовать эту функцию.
### Возвращаемое значение

true, если сокет настроен успешно; иначе возвращается false.
## void close ( )

Закрывает сокет.
## bool connect ( )

Инициирует соединение на сокете. Если сокет переключён в [non-blocking mode](#nonblock_int), этот метод будет ожидать соединения до 10 секунд. Если сокет блокирующий (по умолчанию или [set](#block_int) намеренно), период таймаута определяется ОС. Этот метод блокирует поток, в котором он вызван, независимо от того, задан ли сокет как блокирующий или неблокирующий.
### Возвращаемое значение

true, если соединение инициализировано; иначе false.
## bool connect ( size_t timeout_ms )

Инициирует соединение на сокете. Этот метод будет ожидать соединения до времени, заданного аргументом. Этот метод блокирует поток, в котором он вызван, независимо от того, задан ли сокет как блокирующий или неблокирующий.
### Аргументы

- *size_t* **timeout_ms** - Таймаут, в течение которого поток блокируется этим методом, в мс.

### Возвращаемое значение

true, если соединение инициализировано; иначе false.
## bool listen ( int num )

Заставляет сокет прослушивать соединения.
### Аргументы

- *int* **num** - Максимальное количество ожидающих соединений.

### Возвращаемое значение

true, если сокет начал прослушивание; иначе false.
## bool listenMulticastGroup ( )

Присоединяет сокет к multicast-группе. Доступно только для [UDP-сокетов](#SOCKET_TYPE_DGRAM).
> **Notice:** Класс сокета не позволяет создавать multicast-сервер.


```cpp
const int PORT = 8888;
SocketPtr socket = Socket::create(Socket::SOCKET_TYPE_DGRAM, PORT);
socket->listenMulticastGroup();

```


### Возвращаемое значение

true, если сокет успешно присоединён; иначе false.
## bool nodelay ( )

Включает алгоритм Нейгла.
### Возвращаемое значение

true, если алгоритм успешно включён; иначе false.
## bool nonblock ( )

Делает сокет неблокирующим.
### Возвращаемое значение

true, если сокет стал неблокирующим; иначе false.
## bool open ( int port )

Открывает сокет на заданном порту. При получении данных сокетом будут приниматься пакеты со всех сетевых интерфейсов. При отправке данных сокетом будет использоваться IP-адрес по умолчанию.
### Аргументы

- *int* **port** - Номер порта, на котором будет открыт сокет.

### Возвращаемое значение

true, если сокет успешно открыт; иначе false.
## bool open ( const char * host , int port )

Открывает сокет на заданном порту. При получении данных сокетом будут приниматься пакеты со всех сетевых интерфейсов. При отправке данных сокетом будет использоваться IP-адрес по умолчанию.
### Аргументы

- *const char ** **host** - Имя хоста, на котором будет открыт сокет.
- *int* **port** - Номер порта, на котором будет открыт сокет.

### Возвращаемое значение

true, если сокет успешно открыт; иначе false.
## bool recv ( int size )

Изменяет размер внутреннего буфера приёма сокета.
### Аргументы

- *int* **size** - Размер буфера приёма в байтах.

### Возвращаемое значение

true, если размер буфера успешно изменён; иначе false.
## bool send ( int size )

Изменяет размер внутреннего буфера отправки сокета.
### Аргументы

- *int* **size** - Размер буфера отправки в байтах.

### Возвращаемое значение

true, если размер буфера успешно изменён; иначе false.
## bool isReadyToRead ( int timeout_usec = 0 ) const

Возвращает значение, указывающее, готов ли сокет к чтению данных, при необходимости ожидая заданный период таймаута для выполнения синхронного ввода-вывода.
### Аргументы

- *int* **timeout_usec** - Максимальное время ожидания ответа сокета, в микросекундах. По умолчанию таймаут равен **0**.

### Возвращаемое значение

true, если сокет готов к чтению данных; иначе false.
## bool isReadyToWrite ( int timeout_usec = 0 ) const

Возвращает значение, указывающее, готов ли сокет к записи данных, при необходимости ожидая заданный период таймаута для выполнения синхронного ввода-вывода.
### Аргументы

- *int* **timeout_usec** - Максимальное время ожидания ответа сокета, в микросекундах. По умолчанию таймаут равен **0**

### Возвращаемое значение

true, если сокет готов к записи данных; иначе false.
