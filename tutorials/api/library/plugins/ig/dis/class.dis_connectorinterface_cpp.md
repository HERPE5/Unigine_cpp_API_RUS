# IG::DIS::Connector Class (CPP)

**Header:** #include <plugins/Unigine/DISConnector/UnigineDISConnector.h>


## IG::DIS::Connector Class

### Методы класса

---

## void init ( String ip , int site , int exercise , int app , int port )

Инициализирует коннектор DIS с использованием указанных параметров.
### Аргументы

- *[String](../../../../../api/library/common/class.string_cpp.md)* **ip** - Широковещательный адрес серверного компьютера, используемый для рассылки сообщений IG по сети
- *int* **site** - Site ID этого экземпляра приложения.
- *int* **exercise** - Exercise ID DIS.
- *int* **app** - Application ID этого экземпляра приложения. Если не задан, будет сгенерирован автоматически.
- *int* **port** - Порт соединения. Этот аргумент необязателен, значение по умолчанию — 3000.

## void init ( KDIS::NETWORK::Connection* newConnection )

Инициализирует коннектор DIS с использованием пользовательского соединения.
### Аргументы

- *KDIS::NETWORK::Connection** **newConnection** - Пользовательское соединение.

## void shutdown ( )

Завершает работу коннектора DIS. Если соединение DIS инициализировано с использованием пользовательского соединения, этот метод не очищает и не останавливает пользовательское соединение.
## void * addConnectCallback ( Unigine:: CallbackBase * func )

Задаёт параметр, вызываемый при установлении соединения.
### Аргументы

- *Unigine::[CallbackBase](../../../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **func** - Параметр, вызываемый при установлении соединения.

### Возвращаемое значение

ID последнего добавленного колбэка подключения, если колбэк был успешно добавлен; иначе **nullptr**. Этот ID можно использовать для [remove](#removeConnectCallback_void_ptr_bool) этого колбэка при необходимости.
## bool removeConnectCallback ( void * id )

Удаляет указанный колбэк из списка колбэков подключения.
### Аргументы

- *void ** **id** - ID колбэка подключения, полученный при его [adding](#addConnectCallback_CallbackBase_ptr_void_ptr).

### Возвращаемое значение

True, если колбэк подключения с указанным ID был успешно удалён; иначе false.
## void * addReceivePacketCallback ( int pdu_type , Unigine:: CallbackBase * func )

Добавляет функцию колбэка, вызываемую при получении пакета.
### Аргументы

- *int* **pdu_type** - Тип PDU.
- *Unigine::[CallbackBase](../../../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **func** - Функция колбэка, вызываемая при получении пакета. Сигнатура колбэка: void func(KDIS::PDU::Header *packet).

### Возвращаемое значение

ID последнего добавленного колбэка Receive Packet, если колбэк был успешно добавлен; иначе **nullptr**. Этот ID можно использовать для [remove](#removeReceivePacketCallback_void_ptr_bool) этого колбэка при необходимости.
## bool removeReceivePacketCallback ( void * id )

Удаляет указанный колбэк из списка колбэков Receive Packet.
### Аргументы

- *void ** **id** - ID колбэка Receive Packet, полученный при его [adding](#addReceivePacketCallback_int_CallbackBase_ptr_void_ptr).

### Возвращаемое значение

True, если колбэк Receive Packet с указанным ID был успешно удалён; иначе false.
## void setSiteID ( int site )

Задаёт Site ID для коннектора.
### Аргументы

- *int* **site** - Site ID экземпляра приложения.

## int getSiteID ( )

Возвращает текущий Site ID коннектора.
### Возвращаемое значение

Site ID текущего экземпляра приложения.
## void setAppID ( int app )

Задаёт Application ID для коннектора.
### Аргументы

- *int* **app** - Application ID экземпляра приложения.

## int getAppID ( )

Возвращает текущий Application ID коннектора.
### Возвращаемое значение

Application ID текущего экземпляра приложения.
## void setExerciseID ( int exercise )

Задаёт Exercise ID для коннектора.
### Аргументы

- *int* **exercise** - Exercise ID DIS.

## int getExerciseID ( )

Возвращает текущий Exercise ID коннектора.
### Возвращаемое значение

Exercise ID DIS.
## void sendPacket ( KDIS::PDU::Header packet )

Отправляет пользовательский пакет.
### Аргументы

- *KDIS::PDU::Header* **packet** - Пользовательский пакет.

## void installCustomPacketIDFilter ( PacketIDFilterInterface * filter )

Задаёт пользовательские правила фильтрации пакетов и сущностей с использованием параметров конфигурации коннектора (Site ID, Exercise ID, Application ID). Например, можно создать собственный фильтр пакетов и принимать только пакеты и сущности, у которых Site ID и Exercise ID совпадают с текущими, а Application ID не совпадает (фактически это поведение коннектора DIS по умолчанию):
```cpp
// наследуйте собственный класс от PacketIDFilterInterface
class CustomPacketIDFilter : public Unigine::Plugins::IG::DIS::PacketIDFilterInterface
{
public:
	// переопределите методы "check"
	virtual bool checkSiteID(int id) const override { return Unigine::Plugins::IG::DIS::Connector::get()->getSiteID() == id; }
	virtual bool checkExerciseID(int id) const override { return Unigine::Plugins::IG::DIS::Connector::get()->getExerciseID() == id; }
	virtual bool checkAppID(int id) const override { return Unigine::Plugins::IG::DIS::Connector::get()->getAppID() != id; }
};

// выполните следующее где-то на этапе init или update
CustomPacketIDFilter *filter = new CustomPacketIDFilter();
Unigine::Plugins::IG::DIS::Connector::get()->installCustomPacketIDFilter(filter);

```


### Аргументы

- *PacketIDFilterInterface ** **filter** - Пользовательский фильтр.

## void setProcessPacket ( int op_code , bool enabled )

Задаёт значение, указывающее, следует ли обрабатывать или пропускать полученные пакеты IG указанного типа.
### Аргументы

- *int* **op_code** - Идентификатор типа PDU.
- *bool* **enabled** - true, чтобы обрабатывать пакеты указанного типа, **false**, чтобы пропускать их.

## void setConnectionThreadCallbacks ( Unigine:: CallbackBase * on_connect , Unigine:: CallbackBase * on_disconnect )

Задаёт колбэки для настройки экземпляра соединения.
> **Warning:** Этот колбэк будет вызван в потоке, отличном от главного.


### Аргументы

- *Unigine::[CallbackBase](../../../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **on_connect** - Параметр, вызываемый в потоке соединения непосредственно после установления соединения. Сигнатура колбэка: void func(KDIS::NETWORK::Connection * connection).
- *Unigine::[CallbackBase](../../../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **on_disconnect** - Параметр, вызываемый после сбоя соединения или завершения работы. Сигнатура колбэка: void func(KDIS::NETWORK::Connection * connection). > **Notice:** Соединение может быть nullptr.

## void setDeadReckoningStatic ( Unigine::Plugins::IG::Entity * entity )

Задаёт алгоритм экстраполяции движения Static для использования указанной сущностью (сущность не движется).
 Алгоритмы экстраполяции движения (Dead Reckoning: *Static, FPW, RPW, RVW, FVW, FPB, RPB, RVB, FVB*) используются в Advanced Distributed Simulation для снижения необходимости постоянно обновлять информацию о состоянии симулируемой сущности путём оценки положения и ориентации сущности на основе ранее известного положения и ориентации, а также оценок прошедшего времени симуляции и движения.
### Аргументы

- *Unigine::Plugins::IG::Entity ** **entity** - Симулируемая сущность, для которой используется алгоритм экстраполяции движения Static.

## void setDeadReckoningFPW ( Unigine::Plugins::IG::Entity * entity , const Vec3 & linear_velocity )

Задаёт алгоритм экстраполяции движения FPW для использования указанной сущностью вместе с указанными постоянными скоростями. FPW означает: **F** - фиксированный поворот, **P** - скорость изменения положения постоянна (скорость), **B** - мировая система координат.
 Алгоритмы экстраполяции движения (Dead Reckoning: *Static, FPW, RPW, RVW, FVW, FPB, RPB, RVB, FVB*) используются в Advanced Distributed Simulation для снижения необходимости постоянно обновлять информацию о состоянии симулируемой сущности путём оценки положения и ориентации сущности на основе ранее известного положения и ориентации, а также оценок прошедшего времени симуляции и движения.
### Аргументы

- *Unigine::Plugins::IG::Entity ** **entity** - Симулируемая сущность, для которой используется алгоритм экстраполяции движения FPW с указанными значениями.
- *const [Vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **linear_velocity** - Вектор линейной скорости.

## void setDeadReckoningRPW ( Unigine::Plugins::IG::Entity * entity , const Vec3 & linear_velocity , const vec3 & angular_velocity_deg )

Задаёт алгоритм экстраполяции движения RPW для использования указанной сущностью вместе с указанными постоянными скоростями. RPW означает: **R** - вращение, **P** - скорость изменения положения постоянна (скорость), **B** - мировая система координат.
 Алгоритмы экстраполяции движения (Dead Reckoning: *Static, FPW, RPW, RVW, FVW, FPB, RPB, RVB, FVB*) используются в Advanced Distributed Simulation для снижения необходимости постоянно обновлять информацию о состоянии симулируемой сущности путём оценки положения и ориентации сущности на основе ранее известного положения и ориентации, а также оценок прошедшего времени симуляции и движения.
### Аргументы

- *Unigine::Plugins::IG::Entity ** **entity** - Симулируемая сущность, для которой используется алгоритм экстраполяции движения RPW с указанными значениями.
- *const [Vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **linear_velocity** - Вектор линейной скорости.
- *const [vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **angular_velocity_deg** - Вектор, содержащий значения угловой скорости для каждой оси, в градусах.

## void setDeadReckoningRVW ( Unigine::Plugins::IG::Entity * entity , const Vec3 & linear_velocity , const Vec3 & linear_acceleration , const vec3 & angular_velocity_deg )

Задаёт алгоритм экстраполяции движения RVW для использования указанной сущностью вместе с указанными постоянными скоростями. RVW означает: **R** - вращение, **V** - скорость изменения скорости постоянна (скорость + ускорение), **W** - мировая система координат.
 Алгоритмы экстраполяции движения (Dead Reckoning: *Static, FPW, RPW, RVW, FVW, FPB, RPB, RVB, FVB*) используются в Advanced Distributed Simulation для снижения необходимости постоянно обновлять информацию о состоянии симулируемой сущности путём оценки положения и ориентации сущности на основе ранее известного положения и ориентации, а также оценок прошедшего времени симуляции и движения.
### Аргументы

- *Unigine::Plugins::IG::Entity ** **entity** - Симулируемая сущность, для которой используется алгоритм экстраполяции движения RVW с указанными значениями.
- *const [Vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **linear_velocity** - Вектор линейной скорости.
- *const [Vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **linear_acceleration** - Вектор линейного ускорения.
- *const [vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **angular_velocity_deg** - Вектор, содержащий значения угловой скорости для каждой оси, в градусах.

## void setDeadReckoningFVW ( Unigine::Plugins::IG::Entity * entity , const Vec3 & linear_velocity , const Vec3 & linear_acceleration )

Задаёт алгоритм экстраполяции движения FVW для использования указанной сущностью вместе с указанными постоянными скоростями. FVW означает: **F** - фиксированный поворот, **V** - скорость изменения скорости постоянна (скорость + ускорение), **W** - мировая система координат.
 Алгоритмы экстраполяции движения (Dead Reckoning: *Static, FPW, RPW, RVW, FVW, FPB, RPB, RVB, FVB*) используются в Advanced Distributed Simulation для снижения необходимости постоянно обновлять информацию о состоянии симулируемой сущности путём оценки положения и ориентации сущности на основе ранее известного положения и ориентации, а также оценок прошедшего времени симуляции и движения.
### Аргументы

- *Unigine::Plugins::IG::Entity ** **entity** - Симулируемая сущность, для которой используется алгоритм экстраполяции движения FVW с указанными значениями.
- *const [Vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **linear_velocity** - Вектор линейной скорости.
- *const [Vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **linear_acceleration** - Вектор линейного ускорения.

## void setDeadReckoningFPB ( Unigine::Plugins::IG::Entity * entity , const Vec3 & linear_velocity , const vec3 & angular_velocity_deg )

Задаёт алгоритм экстраполяции движения FPB для использования указанной сущностью вместе с указанными постоянными скоростями. FPB означает: **F** - фиксированный поворот, **P** - скорость изменения положения постоянна (скорость), **B** - система координат, связанная с телом.
 Алгоритмы экстраполяции движения (Dead Reckoning: *Static, FPW, RPW, RVW, FVW, FPB, RPB, RVB, FVB*) используются в Advanced Distributed Simulation для снижения необходимости постоянно обновлять информацию о состоянии симулируемой сущности путём оценки положения и ориентации сущности на основе ранее известного положения и ориентации, а также оценок прошедшего времени симуляции и движения.
### Аргументы

- *Unigine::Plugins::IG::Entity ** **entity** - Симулируемая сущность, для которой используется алгоритм экстраполяции движения FPB с указанными значениями.
- *const [Vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **linear_velocity** - Вектор линейной скорости.
- *const [vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **angular_velocity_deg** - Вектор, содержащий значения угловой скорости для каждой оси, в градусах.

## void setDeadReckoningRPB ( Unigine::Plugins::IG::Entity * entity , const Vec3 & linear_velocity , const vec3 & angular_velocity_deg )

Задаёт алгоритм экстраполяции движения RPB для использования указанной сущностью вместе с указанными постоянными скоростями. RPB означает: **R** - вращение, **P** - скорость изменения положения постоянна (скорость), **B** - система координат, связанная с телом.
 Алгоритмы экстраполяции движения (Dead Reckoning: *Static, FPW, RPW, RVW, FVW, FPB, RPB, RVB, FVB*) используются в Advanced Distributed Simulation для снижения необходимости постоянно обновлять информацию о состоянии симулируемой сущности путём оценки положения и ориентации сущности на основе ранее известного положения и ориентации, а также оценок прошедшего времени симуляции и движения.
### Аргументы

- *Unigine::Plugins::IG::Entity ** **entity** - Симулируемая сущность, для которой используется алгоритм экстраполяции движения RPB с указанными значениями.
- *const [Vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **linear_velocity** - Вектор линейной скорости.
- *const [vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **angular_velocity_deg** - Вектор, содержащий значения угловой скорости для каждой оси, в градусах.

## void setDeadReckoningRVB ( Unigine::Plugins::IG::Entity * entity , const Vec3 & linear_velocity , const Vec3 & linear_acceleration , const vec3 & angular_velocity_deg )

Задаёт алгоритм экстраполяции движения RVB для использования указанной сущностью вместе с указанными постоянными скоростями. RVB означает: **R** - вращение, **V** - скорость изменения скорости постоянна (скорость + ускорение), **B** - система координат, связанная с телом.
 Алгоритмы экстраполяции движения (Dead Reckoning: *Static, FPW, RPW, RVW, FVW, FPB, RPB, RVB, FVB*) используются в Advanced Distributed Simulation для снижения необходимости постоянно обновлять информацию о состоянии симулируемой сущности путём оценки положения и ориентации сущности на основе ранее известного положения и ориентации, а также оценок прошедшего времени симуляции и движения.
### Аргументы

- *Unigine::Plugins::IG::Entity ** **entity** - Симулируемая сущность, для которой используется алгоритм экстраполяции движения RVB с указанными значениями.
- *const [Vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **linear_velocity** - Вектор линейной скорости.
- *const [Vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **linear_acceleration** - Вектор линейного ускорения.
- *const [vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **angular_velocity_deg** - Вектор, содержащий значения угловой скорости для каждой оси, в градусах.

## void setDeadReckoningFVB ( Unigine::Plugins::IG::Entity * entity , const Vec3 & linear_velocity , const Vec3 & linear_acceleration , const vec3 & angular_velocity_deg )

Задаёт алгоритм экстраполяции движения FVB для использования указанной сущностью вместе с указанными постоянными скоростями. FVB означает: **F** - фиксированный поворот, **V** - скорость изменения скорости постоянна (скорость + ускорение), **B** - система координат, связанная с телом.
 Алгоритмы экстраполяции движения (Dead Reckoning: *Static, FPW, RPW, RVW, FVW, FPB, RPB, RVB, FVB*) используются в Advanced Distributed Simulation для снижения необходимости постоянно обновлять информацию о состоянии симулируемой сущности путём оценки положения и ориентации сущности на основе ранее известного положения и ориентации, а также оценок прошедшего времени симуляции и движения.
### Аргументы

- *Unigine::Plugins::IG::Entity ** **entity** - Симулируемая сущность, для которой используется алгоритм экстраполяции движения FVB с указанными значениями.
- *const [Vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **linear_velocity** - Вектор линейной скорости.
- *const [Vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **linear_acceleration** - Вектор линейного ускорения.
- *const [vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **angular_velocity_deg** - Вектор, содержащий значения угловой скорости для каждой оси, в градусах.
