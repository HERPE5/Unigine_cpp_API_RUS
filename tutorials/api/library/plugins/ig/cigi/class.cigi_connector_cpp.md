# IG::CIGI::Connector Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>


Этот класс реализует связь между плагином IG и протоколом CIGI.

> **Notice:** Плагин [IG](../../../../../api/library/plugins/ig/api/index.md) должен быть загружен.


## IG::CIGI::Connector Class

### Перечисления

## CIGI_MODE

| Name | Description |
|---|---|
| **CIGI_MODE_STANDBY** = 0 | Режим ожидания (Standby) IG. Это обычный режим работы IG в реальном времени. Все пакеты, отправленные Host, будут обработаны IG. В этом режиме IG не должен выполнять диагностику. |
| **CIGI_MODE_OPERATE** = 1 | Рабочий режим (Operate) IG. Это обычный режим работы IG в реальном времени. Все пакеты, отправленные Host, будут обработаны IG. В этом режиме IG не должен выполнять диагностику. |
| **CIGI_MODE_DEBUG** = 2 | Режим отладки (Debug) IG. Этот режим похож на режим Operate, но предоставляет журналирование данных и/или ошибок, а также другие отладочные возможности для помощи в интеграции или устранении неполадок интерфейса Host и IG. Из-за накладных расходов этих отладочных возможностей IG может не всегда работать в режиме жёсткого реального времени. |
| **CIGI_MODE_OFFLINE** = 3 | Автономный режим обслуживания (Offline Maintenance) IG. В этом режиме IG игнорирует все данные от Host и отправляет только пакеты Start of Frame. Этот режим может быть активирован только со стороны IG. Поскольку пакеты IG Control от Host игнорируются IG, IG должен быть переведён в режим Reset/Standby, прежде чем Host сможет инициировать дальнейшие изменения режима. |

### Методы класса

---

## int init ( int version , const char * host , int send , int recv , int size = 1432 )

Инициализирует коннектор CIGI с использованием указанных параметров.
### Аргументы

- *int* **version** - Версия протокола CIGI. Одно из значений [CIGI_VERSION_*](#CIGI_VERSION_30).
- *const char ** **host** - Адрес CIGI Host.
- *int* **send** - Номер TCP-порта, используемого для отправки пакетов на CIGI Host.
- *int* **recv** - Номер TCP-порта, используемого для получения пакетов от CIGI Host.
- *int* **size** - Размер пакета. Значение по умолчанию — 1432.

### Возвращаемое значение

1, если коннектор CIGI успешно инициализирован; иначе 0.
## int shutdown ( )

Возвращает значение, указывающее, успешно ли завершена работа коннектора CIGI.
### Возвращаемое значение

true, если работа коннектора CIGI успешно завершена; иначе false.
## bool isInitialized ( ) const

Возвращает значение, указывающее, успешно ли инициализирован коннектор CIGI.
### Возвращаемое значение

true, если коннектор CIGI успешно инициализирован; иначе false.
## void setIGMode ( CIGI::CIGI_MODE mode )

Задаёт текущий режим IG.
### Аргументы

- *CIGI::CIGI_MODE* **mode** - Режим IG. Одно из значений [CIGI_MODE_*](#CIGI_MODE_STANDBY).

## CIGI::CIGI_MODE getIGMode ( ) const

Возвращает текущий режим IG.
### Возвращаемое значение

Режим IG. Одно из значений [CIGI_MODE_*](#CIGI_MODE_STANDBY).
## void setIGStatus ( int status )

Задаёт текущий статус IG.
### Аргументы

- *int* **status** - Статус IG. Поддерживаются следующие значения:

  - 0 - нормальный
  - 1-255 - произошла ошибка

## int getIGStatus ( ) const

Возвращает текущий статус IG.
### Возвращаемое значение

Статус IG. Поддерживаются следующие значения:
- 0 - нормальный
- 1-255 - произошла ошибка


## void setSynchronous ( bool synchronous )

Задаёт значение, указывающее, включён ли в данный момент синхронный режим работы (при отключении используется асинхронный режим).
### Аргументы

- *bool* **synchronous** - true, чтобы включить синхронный режим работы; false - чтобы использовать асинхронный режим.

## bool isSynchronous ( ) const

Возвращает значение, указывающее, включён ли в данный момент синхронный режим работы (при отключении используется асинхронный режим).
### Возвращаемое значение

true, если синхронный режим работы включён в данный момент; иначе false.
## bool isInterpolation ( ) const

Возвращает значение, указывающее, включены ли интерполяция и экстраполяция.
### Возвращаемое значение

true, если интерполяция и экстраполяция включены; иначе false.
## unsigned int getIGFrame ( ) const

Возвращает номер текущего кадра для IG.
### Возвращаемое значение

Номер текущего кадра IG.
## unsigned int getHostFrame ( ) const

Возвращает номер текущего кадра для Host.
### Возвращаемое значение

Номер текущего кадра Host.
## double getTime ( ) const

Возвращает время симуляции IG.
### Возвращаемое значение

Время симуляции IG, в секундах.
## double getLastReceivedHostTime ( ) const

Возвращает последнее полученное время Host (значение *timestamp* в "IG Control").
### Возвращаемое значение

Последнее полученное время Host, в секундах.
## void * addOnConnectCallback ( Unigine:: CallbackBase * func )

Добавляет функцию колбэка, вызываемую при подключении Host.
### Аргументы

- *Unigine::[CallbackBase](../../../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **func** - Указатель на колбэк.

### Возвращаемое значение

ID последнего добавленного колбэка подключения, если колбэк был успешно добавлен; иначе **nullptr**. Этот ID можно использовать для [remove](#removeOnConnectCallback_void_ptr_bool) этого колбэка при необходимости.
## bool removeOnConnectCallback ( void * id )

Удаляет указанный колбэк из списка колбэков подключения.
### Аргументы

- *void ** **id** - ID колбэка подключения, полученный при его [adding](#addOnConnectCallback_CallbackBase_ptr_void_ptr).

### Возвращаемое значение

True, если колбэк подключения с указанным ID был успешно удалён; иначе false.
## void * addOnReceivePacketCallback ( int cigi_opcode , Unigine:: CallbackBase1 * func )

Задаёт функцию колбэка, вызываемую при получении пакета указанного типа от Host.
### Аргументы

- *int* **cigi_opcode** - Опкод пакета данных CIGI. Одно из значений [CIGI_OPCODE_*](#CIGI_OPCODE_IG_CONTROL).
- *Unigine::[CallbackBase1](../../../../../api/library/common/callbacks/class.callbackbase1_cpp.md) ** **func** - Указатель на колбэк. Функция колбэка должна иметь следующую сигнатуру: (*Unigine::Plugins::IG::CIGI::CigiHostPacket* ***packet**)

### Возвращаемое значение

ID последнего добавленного колбэка Receive Packet, если колбэк был успешно добавлен; иначе **nullptr**. Этот ID можно использовать для [remove](#removeOnReceivePacketCallback_void_ptr_bool) этого колбэка при необходимости.
## bool removeOnReceivePacketCallback ( void * id )

Удаляет указанный колбэк из списка колбэков Receive Packet.
### Аргументы

- *void ** **id** - ID колбэка Receive Packet, полученный при его [adding](#addOnReceivePacketCallback_int_CallbackBase1_ptr_void_ptr).

### Возвращаемое значение

true, если колбэк Receive Packet с указанным ID был успешно удалён; иначе false.
## void * addOnSendPacketCallback ( int cigi_opcode , Unigine:: CallbackBase4 * func )

Задаёт функцию колбэка, вызываемую непосредственно перед отправкой ответа на запрос. Это может использоваться для отправки дополнительных данных, требуемых host (например, скоростей точки пересечения для запросов LOS/HAT, что полезно в случае посадки на движущуюся платформу).
Функция колбэка имеет следующую сигнатуру:


(*bool* &**ret**, *IG::CIGI::CigiIGPacket* ***response**, *IG::CIGI::CigiHostPacket* ***request**, *IG::IGIntersection* ***intersection**)


- **ret** - булево значение, указывающее, следует ли отправлять пакет;
- **response** - отправляемый пакет;
- **request** - запрос, на который отправляется пакет как ответ (может быть nullptr);
- **intersection** - дополнительная информация о пересечении (при необходимости).


```cpp
void AppSystemLogic::init_cigi()
{
    int index = Engine::get()->findPlugin("CIGIConnector");
    // проверка загрузки плагина CIGIConnector
    if (index < 0)
        return;
    // получение интерфейса CIGI
    cigi = IG::CIGI::Connector::get();

    cigi->addOnSendPacketCallback(Plugins::IG::CIGI::CIGI_OPCODE_LOS_EXT_RESPONSE, MakeCallback(this, &AppSystemLogic::on_los_ext_send));
    cigi->addOnSendPacketCallback(Plugins::IG::CIGI::CIGI_OPCODE_LOS_RESPONSE, MakeCallback(this, &AppSystemLogic::on_los_ext_send));
}
void AppSystemLogic::on_los_ext_send(bool &ret, IG::CIGI::CigiIGPacket *response, IG::CIGI::CigiHostPacket *request, IG::IGIntersection *intersection)
{
    ret = false;
    Log::message("reject packet %d\n", response->getType());
    if (request)
        Log::message("request was %d\n", request->getType());
    if (intersection)
    {
        Log::message("intersection was\n");
        if (intersection->object)
            Log::message("intersection object %s\n", intersection->object->getName());
    }
}

```


### Аргументы

- *int* **cigi_opcode** - Опкод пакета данных CIGI. Одно из значений [CIGI_OPCODE_*](#CIGI_OPCODE_IG_CONTROL).
- *Unigine::[CallbackBase4](../../../../../api/library/common/callbacks/class.callbackbase4_cpp.md) ** **func** - Указатель на колбэк. Функция колбэка должна иметь следующую сигнатуру: (*bool* &**ret**, *IG::CIGI::CigiIGPacket* ***response**, *IG::CIGI::CigiHostPacket* ***request**, *IG::IGIntersection* ***intersection**)

### Возвращаемое значение

ID последнего добавленного колбэка Send Packet, если колбэк был успешно добавлен; иначе **nullptr**. Этот ID можно использовать для [remove](#removeOnSendPacketCallback_void_ptr_bool) этого колбэка при необходимости.
## bool removeOnSendPacketCallback ( void * id )

Удаляет указанный колбэк из списка колбэков Send Packet.
### Аргументы

- *void ** **id** - ID колбэка Send Packet, полученный при его [adding](#addOnSendPacketCallback_int_CallbackBase4_ptr_void).

### Возвращаемое значение

True, если колбэк Send Packet с указанным ID был успешно удалён; иначе false.
## int getNumHostPackets ( )

Возвращает общее количество пакетов, полученных от Host.
### Возвращаемое значение

Общее количество пакетов, полученных от Host.
## CigiHostPacket * getHostPacket ( int num )

Возвращает указанный [CIGI Host packet](../../../../../api/library/plugins/ig/cigi/class.icigihostpacket_cpp.md).
### Аргументы

- *int* **num** - ID пакета Host.

### Возвращаемое значение

Пакет CIGI Host.
## CigiIGPacket * createIGPacket ( int ig_opcode )

Создаёт пакет IG для отправки Host.
### Аргументы

- *int* **ig_opcode** - Опкод IG, одно из значений [CIGI_OPCODE_*](#CIGI_OPCODE_START_OF_FRAME).

### Возвращаемое значение

Пакет IG для отправки Host.
## void addIGPacket ( CigiIGPacket * packet )

Отправляет указанный [IG packet](../../../../../api/library/plugins/ig/cigi/class.icigiigpacket_cpp.md) Host.
### Аргументы

- *[CigiIGPacket](../../../../../api/library/plugins/ig/cigi/class.icigiigpacket_cpp.md) ** **packet** - Пакет IG для отправки Host.

## void setProcessPacket ( int op_code , bool enabled )

Задаёт значение, указывающее, следует ли обрабатывать или пропускать полученные пакеты IG указанного типа.
### Аргументы

- *int* **op_code** - Опкод IG, одно из значений [CIGI_OPCODE_*](#CIGI_OPCODE_START_OF_FRAME).
- *bool* **enabled** - true, чтобы обрабатывать пакеты указанного типа, **false**, чтобы пропускать их.

## void showDebug ( )

Отображает отладочную информацию.
## void setWeatherLayerType ( int id , const CigiWeatherLayerType& type )

### Аргументы

- *int* **id** - ID слоя погоды.
- *const CigiWeatherLayerType&* **type** - Тип слоя погоды, одно из следующих значений:

  - *Plugins::IG::WeatherLayerType::LAYER_BASE* - базовый слой.
  - *Plugins::IG::WeatherLayerType::LAYER_CLOUD* - [cloud layer](../../../../../api/library/plugins/weather/class.weatherlayercloud_cpp.md).
  - *Plugins::IG::WeatherLayerType::LAYER_PRECIPITATION* - [precipitation layer](../../../../../api/library/plugins/weather/class.weatherlayerprecipitation_cpp.md).

## const CigiWeatherLayerType & getWeatherLayerType ( int id ) const

### Аргументы

- *int* **id** - ID слоя погоды.

### Возвращаемое значение

Тип слоя погоды, одно из следующих значений:
- *Plugins::IG::WeatherLayerType::LAYER_BASE* - базовый слой.
- *Plugins::IG::WeatherLayerType::LAYER_CLOUD* - [cloud layer](../../../../../api/library/plugins/weather/class.weatherlayercloud_cpp.md).
- *Plugins::IG::WeatherLayerType::LAYER_PRECIPITATION* - [precipitation layer](../../../../../api/library/plugins/weather/class.weatherlayerprecipitation_cpp.md).
