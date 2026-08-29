# IG::HLA::Connector Class (CPP)

**Header:** #include <plugins/Unigine/HLAConnector/UnigineHLAConnector.h>


## IG::HLA::Connector Class

### Методы класса

---

## int init ( int version , const char * fom_path , const char * federate_name , const char * federation_execution_name )

Инициализирует коннектор HLA с использованием указанных параметров.
### Аргументы

- *int* **version** - Тип колбэка. Одно из следующих значений: [RTI13](#RTI13), [RTI1516](#RTI1516) или [RTI1516E](#RTI1516E).
- *const char ** **fom_path** - путь к файлу FOM (.fed или .xml, в зависимости от версии)
- *const char ** **federate_name** - имя текущего экземпляра
- *const char ** **federation_execution_name** - имя группы федератов с одинаковым FOM. > **Notice:** OpenRTI использует имена вида "*rti://fedExecName*", Pitch RTI использует простое "*fedExecName*".

### Возвращаемое значение

1, если коннектор HLA успешно инициализирован; иначе 0.
## void setTimeRegulation ( bool start_constrained , bool start_regulating )

Задаёт режим управления временем для федерата. В общем случае федерат может быть "regulating", "constrained", "regulating and constrained" или "neither regulating nor constrained".
### Аргументы

- *bool* **start_constrained** - Флаг constrained: true, если федерат является constrained (может получать сообщения TSO); иначе false.
- *bool* **start_regulating** - Флаг regulating: true, если федерат является regulating (может отправлять сообщения TSO); иначе false.

## int isConstrained ( )

Возвращает значение, указывающее, является ли федерат constrained, т.е. может ли он получать сообщения TSO (time-stamped order).
### Возвращаемое значение

1, если федерат является constrained; иначе 0.
## int isRegulating ( )

Возвращает значение, указывающее, является ли федерат regulating, т.е. может ли он отправлять сообщения TSO (time-stamped order).
### Возвращаемое значение

1, если федерат является regulating; иначе 0.
## void setTimeStep ( double time_step )

Задаёт значение lookahead для regulating федерата; это значение определяет частоту вызова метода [*timeAdvanceRequest()*](#timeAdvanceRequest_double_void).
### Аргументы

- *double* **time_step** - Флаг включения. Используйте 1, чтобы показать [debug window](../../../../../code/plugins/syncker/index.md#debug_window), или 0 - чтобы скрыть его.

## double getLocalTime ( )

Возвращает локальное время текущего федерата.
### Возвращаемое значение

Локальное время текущего федерата.
## void registerFederationSynchronizationPoint ( const char * label , const char * tag )

Регистрирует новую точку синхронизации для всех федератов.
### Аргументы

- *const char ** **label** - Строка, однозначно идентифицирующая точку синхронизации.
- *const char ** **tag** - Пользовательский тег.

## void registerFederationSynchronizationPoint ( const char * label , const char * tag , const Vector <unsigned long> & sync_set )

Регистрирует новую точку синхронизации.
### Аргументы

- *const char ** **label** - Строка, однозначно идентифицирующая точку синхронизации.
- *const char ** **tag** - Пользовательский тег.
- *const [Vector](../../../../../api/library/containers/vector/class.vector_cpp.md)<unsigned long> &* **sync_set** - Список, содержащий дескрипторы синхронизируемых федератов.

## void synchronizationPointAchieved ( const char * label )

Отправляет сообщение о том, что указанная точка синхронизации успешно достигнута со всеми выполненными требованиями.
### Аргументы

- *const char ** **label** - Строка, однозначно идентифицирующая точку синхронизации.

## unsigned long getInteractionClassHandle ( const char * name )

Возвращает дескриптор класса взаимодействия.
### Аргументы

- *const char ** **name** - Имя класса взаимодействия.

### Возвращаемое значение

Дескриптор класса взаимодействия.
## unsigned long getParameterHandle ( const char * name , unsigned long which_class )

Возвращает дескриптор параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *unsigned long* **which_class** - Класс, которому принадлежит параметр.

### Возвращаемое значение

Дескриптор указанного параметра.
## unsigned long getObjectClassHandle ( const char * name )

Возвращает дескриптор класса объекта.
### Аргументы

- *const char ** **name** - Имя класса объекта

### Возвращаемое значение

Дескриптор указанного класса объекта.
## unsigned long getAttributeHandle ( const char * name , unsigned long which_class )

Возвращает дескриптор атрибута.
### Аргументы

- *const char ** **name** - Имя атрибута.
- *unsigned long* **which_class** - Класс, которому принадлежит атрибут.

### Возвращаемое значение

Дескриптор указанного атрибута.
## void publishAndSubscribeObject ( unsigned long handle_id , const int & attributes )

Публикация и подписка на указанный класс объекта.
### Аргументы

- *unsigned long* **handle_id** - ID дескриптора.
- *const int &* **attributes** - Список атрибутов.

## void publishObject ( unsigned long handle_id , const int & attributes )

Публикация указанного класса объекта.
### Аргументы

- *unsigned long* **handle_id** - ID дескриптора.
- *const int &* **attributes** - Список атрибутов.

## void subscribeObject ( unsigned long handle_id , const int & attributes )

Подписка на указанный класс объекта.
### Аргументы

- *unsigned long* **handle_id** - ID дескриптора.
- *const int &* **attributes** - Список атрибутов.

## void publishAndSubscribeInteraction ( unsigned long handle_id )

Публикация и подписка на указанный класс взаимодействия.
### Аргументы

- *unsigned long* **handle_id** - ID дескриптора класса.

## void publishInteraction ( unsigned long handle_id )

Публикация указанного класса взаимодействия.
### Аргументы

- *unsigned long* **handle_id** - ID дескриптора класса.

## void subscribeInteraction ( unsigned long handle_id )

Подписка на указанный класс взаимодействия.
### Аргументы

- *unsigned long* **handle_id** - ID дескриптора класса.

## unsigned long registerObjectInstance ( unsigned long class_handle_id , const char * name )

Регистрирует новый экземпляр объекта с указанным именем.
### Аргументы

- *unsigned long* **class_handle_id** - ID дескриптора класса.
- *const char ** **name** - Имя объекта.

### Возвращаемое значение

Дескриптор объекта.
## int updateAttributeValues ( unsigned long object_id , const int & attributes , const char * tag )

Обновляет значения атрибутов указанного экземпляра объекта.
### Аргументы

- *unsigned long* **object_id** - ID объекта.
- *const int &* **attributes** - Список атрибутов.
- *const char ** **tag** - Пользовательский тег.

### Возвращаемое значение

1, если значения указанных атрибутов успешно обновлены; иначе 0.
## int updateAttributeValues ( unsigned long object_id , const int & attributes , double time , const char * tag )

Обновляет значения атрибутов указанного экземпляра объекта.
### Аргументы

- *unsigned long* **object_id** - ID объекта.
- *const int &* **attributes** - Список атрибутов.
- *double* **time** - Время федерации.
- *const char ** **tag** - Пользовательский тег.

### Возвращаемое значение

1, если значения указанных атрибутов успешно обновлены; иначе 0.
## int deleteObjectInstance ( unsigned long object_id , const char * tag )

Удаляет указанный экземпляр объекта.
### Аргументы

- *unsigned long* **object_id** - ID объекта.
- *const char ** **tag** - Пользовательский тег.

### Возвращаемое значение

1, если указанный экземпляр объекта успешно удалён; иначе 0.
## int deleteObjectInstance ( unsigned long object_id , double time , const char * tag )

Удаляет указанный экземпляр объекта.
### Аргументы

- *unsigned long* **object_id** - ID объекта.
- *double* **time** - Время федерации.
- *const char ** **tag** - Пользовательский тег.

### Возвращаемое значение

1, если указанный экземпляр объекта успешно удалён; иначе 0.
## int sendInteraction ( unsigned long handle_id , const int & parameters , const char * tag )

Отправляет взаимодействие с указанными параметрами.
### Аргументы

- *unsigned long* **handle_id** - ID дескриптора.
- *const int &* **parameters** - Список параметров.
- *const char ** **tag** - Пользовательский тег.

### Возвращаемое значение

1, если взаимодействие успешно отправлено; иначе 0.
## int sendInteraction ( unsigned long handle_id , const int & parameters , double time , const char * tag )

Отправляет взаимодействие с указанными параметрами.
### Аргументы

- *unsigned long* **handle_id** - ID дескриптора.
- *const int &* **parameters** - Список параметров.
- *double* **time** - Время федерации.
- *const char ** **tag** - Пользовательский тег.

### Возвращаемое значение

1, если взаимодействие успешно отправлено; иначе 0.
## void enableTimeRegulation ( double federate_time , double lookahead )

Включает режим регулирования времени для федерата.
### Аргументы

- *double* **federate_time** - Время федерата.
- *double* **lookahead** - Значение lookahead для regulating федерата; это значение определяет частоту вызова метода [*timeAdvanceRequest()*](#timeAdvanceRequest_double_void).

## void disableTimeRegulation ( )

Отключает режим регулирования времени для федерата.
## void enableTimeConstrained ( )

Включает режим time-constrained для федерата.
## void disableTimeConstrained ( )

Отключает режим time-constrained для федерата.
## void timeAdvanceRequest ( double time )

Выдаёт запрос Time Advance Request для федерата.
> **Notice:** Этот метод используется федератами с пошаговым временем.


### Аргументы

- *double* **time** - Значение времени.

## void timeAdvanceRequestAvailable ( double time )

Включает режим регулирования времени для федерата.
> **Notice:** Этот метод используется федератами с пошаговым временем.


### Аргументы

- *double* **time** - Значение времени.

## void nextEventRequest ( double time )

Продвигает логическое время федерата до временной метки следующего значимого события TSO в федерации.
> **Notice:** Этот метод используется событийно-ориентированными федератами.


### Аргументы

- *double* **time** - Временная метка следующего локального события, к которому федерат хочет продвинуться.

## void nextEventRequestAvailable ( double time )

Продвигает логическое время федерата до временной метки следующего значимого события TSO в федерации. The method is similar to [*nextEventRequest()*](#nextEventRequest_double_void), except that a time advance might be granted before all TSO events at the grant time have been delivered to the federate.
> **Notice:** Этот метод используется событийно-ориентированными федератами.


### Аргументы

- *double* **time** - Временная метка следующего локального события, к которому федерат хочет продвинуться.

## void flushQueueRequest ( double time )

Обрабатывает все события федерации независимо от времени.
### Аргументы

- *double* **time** - Значение времени.

## void enableAsynchronousDelivery ( )

Указывает LRC начать доставку событий в порядке получения федерату, даже если в данный момент не выполняется служба продвижения времени.
## void disableAsynchronousDelivery ( )

Указывает LRC не доставлять события в порядке получения при отсутствии выполняемой службы продвижения времени. Это имеет значение только для time-constrained федератов, так как non-constrained федераты получают все события в порядке получения.
## void modifyLookahead ( double lookahead )

Задаёт новое окно lookahead для федерата.
### Аргументы

- *double* **lookahead** - Новый размер интервала, простирающегося вперёд от логического времени федерата в данной точке выполнения, в течение которого федерат не будет генерировать события, упорядоченные по временной метке.

## void queryLookahead ( double lookahead )

Возвращает текущее окно lookahead, используемое для федерата.
### Аргументы

- *double* **lookahead** - Time value.

## Unigine:: CallbackBase * addCallback ( int callback , Unigine:: CallbackBase * func )

Добавляет функцию колбэка указанного типа.
### Аргументы

- *int* **callback** - Тип колбэка. Одна из переменных [CALLBACK_*](#CALLBACK_DISCOVER_OBJECT_INSTANCE).
- *Unigine::[CallbackBase](../../../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **func** - Указатель на колбэк.

### Возвращаемое значение

Указатель на добавленный колбэк.
## void removeCallback ( int callback , Unigine:: CallbackBase * func )

Удаляет указанную функцию колбэка указанного типа.
### Аргументы

- *int* **callback** - Тип колбэка. Одна из переменных [CALLBACK_*](#CALLBACK_DISCOVER_OBJECT_INSTANCE).
- *Unigine::[CallbackBase](../../../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **func** - Указатель на колбэк.

## void clearCallbacks ( int callback )

Очищает все функции колбэка указанного типа.
### Аргументы

- *int* **callback** - Тип колбэка. Одна из переменных [CALLBACK_*](#CALLBACK_DISCOVER_OBJECT_INSTANCE).

## int shutdown ( )

Завершает работу коннектора HLA.
### Возвращаемое значение

1, если работа коннектора HLA успешно завершена; иначе 0.
