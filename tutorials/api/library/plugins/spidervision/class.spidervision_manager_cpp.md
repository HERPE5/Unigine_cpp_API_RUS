# Unigine::Plugins::SpiderVision::Manager Class (CPP)

**Header:** #include <plugins/Unigine/SpiderVision/UnigineSpiderVision.h>

> **Notice:** Этот класс является одиночкой (singleton).


Этот класс предоставляет вспомогательные функции для настройки плагина, а также доступ к объекту класса [DisplaysConfig](../../../../api/library/plugins/spidervision/class.displaysconfig_cpp.md).


## Manager Class

### Методы класса

## DisplaysConfig * getConfig () const

Возвращает текущий экземпляр класса *[DisplaysConfig](../../../../api/library/plugins/spidervision/class.displaysconfig_cpp.md)*, хранящий полные данные конфигурации.
### Возвращаемое значение

Текущий экземпляр класса *[DisplaysConfig](../../../../api/library/plugins/spidervision/class.displaysconfig_cpp.md)*, хранящий полные данные конфигурации.
## void setComputerName ( const char * name )

Задаёт новое имя компьютера, на котором должен отображаться viewport. Если этот параметр не задан, viewport может отображаться на любом ПК. Если задан, viewport отображается только на ПК с совпадающим именем.
### Аргументы

- *const char ** **name** - Имя компьютера, на котором должен отображаться viewport.

## String getComputerName () const

Возвращает текущее имя компьютера, на котором должен отображаться viewport. Если этот параметр не задан, viewport может отображаться на любом ПК. Если задан, viewport отображается только на ПК с совпадающим именем.
### Возвращаемое значение

Текущее имя компьютера, на котором должен отображаться viewport.
## void setEnabled ( bool enabled )

Задаёт новое значение, указывающее, включён ли плагин SpiderVision.
### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить плагин SpiderVision; **false** - чтобы отключить его.

## bool isEnabled () const

Возвращает текущее значение, указывающее, включён ли плагин SpiderVision.
### Возвращаемое значение

**true**, если плагин SpiderVision включён; иначе **false**.
## void setConfiguratorEnabled ( bool enabled )

Задаёт новое значение, указывающее, открыто ли окно конфигуратора.
### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить интерфейс конфигуратора; **false** - чтобы отключить его.

## bool isConfiguratorEnabled () const

Возвращает текущее значение, указывающее, открыто ли окно конфигуратора.
### Возвращаемое значение

**true**, если интерфейс конфигуратора включён; иначе **false**.
## static Event<> getEventComputerNameChanged () const

событие, вызываемое при изменении имени компьютера. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Для удобства также можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события ComputerNameChanged
void computernamechanged_event_handler()
{
	Log::message("\Обработка события ComputerNameChanged\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections computernamechanged_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Manager::getEventComputerNameChanged().connect(computernamechanged_event_connections, computernamechanged_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Manager::getEventComputerNameChanged().connect(computernamechanged_event_connections, []() {
		Log::message("\Обработка события ComputerNameChanged (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
computernamechanged_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection computernamechanged_event_connection;

// подписываемся на событие ComputerNameChanged с функцией-обработчиком, сохраняя соединение
Manager::getEventComputerNameChanged().connect(computernamechanged_event_connection, computernamechanged_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
computernamechanged_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
computernamechanged_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие ComputerNameChanged через соединение
computernamechanged_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события ComputerNameChanged, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события ComputerNameChanged\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Manager::getEventComputerNameChanged().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId computernamechanged_handler_id;

// подписываемся на событие ComputerNameChanged с лямбда-обработчиком, сохраняя идентификатор соединения
computernamechanged_handler_id = Manager::getEventComputerNameChanged().connect(e_connections, []() {
		Log::message("\Обработка события ComputerNameChanged (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Manager::getEventComputerNameChanged().disconnect(computernamechanged_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий ComputerNameChanged при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Manager::getEventComputerNameChanged().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Manager::getEventComputerNameChanged().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## int findViewportID ( const char * viewport_name )

Возвращает ID окна viewport с указанным именем.
### Аргументы

- *const char ** **viewport_name** - Имя viewport.

### Возвращаемое значение

ID окна viewport с указанным именем, если оно существует; иначе -1.
## int findGroupID ( const char * group_name )

Возвращает ID группы viewport с указанным именем.
### Аргументы

- *const char ** **group_name** - Имя группы viewport.

### Возвращаемое значение

ID группы viewport с указанным именем, если она существует; иначе -1.
## void setProjectionEnabled ( int viewport_id , bool enabled )

Задаёт значение, указывающее, включена ли проекция для указанного viewport (коррекция изображения в соответствии с проекцией). Если отключена, изображение отрисовывается как видно с точки обзора без каких-либо искажений (т.е. независимо от положения плоскости viewport в пространстве конфигурации). Если включена, изображение учитывает угол проекции (т.е. положение плоскости viewport относительно точки обзора в пространстве конфигурации) и соответствующим образом искажает отрисовываемое изображение.
### Аргументы

- *int* **viewport_id** - ID окна viewport.
- *bool* **enabled** - true, чтобы включить [projection for the specified viewport](../../../../ig/index.md#interpolation); false - чтобы отключить.

## void setViewportCustomPlayer ( int viewport_id , const Ptr < Player > & player )

Назначает камеру для указанного viewport.
### Аргументы

- *int* **viewport_id** - ID окна viewport.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Player](../../../../api/library/players/class.player_cpp.md)> &* **player** - Камера.

## void setViewportViewOffset ( int viewport_id , const Math:: Vec3 & offset )

Задаёт смещение точки обзора камеры (положение глаза) для viewport с указанным ID.
### Аргументы

- *int* **viewport_id** - ID окна viewport.
- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **offset** - Координаты смещения точки обзора камеры по соответствующим осям.

## void setGroupCustomPlayer ( int group_id , const Ptr < Player > & player )

Назначает камеру для указанной группы viewport.
### Аргументы

- *int* **group_id** - ID группы viewport.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Player](../../../../api/library/players/class.player_cpp.md)> &* **player** - Камера.

## void setGroupViewOffset ( int group_id , const Math:: Vec3 & offset )

Задаёт смещение точки обзора камеры (положение глаза) для группы viewport с указанным ID.
### Аргументы

- *int* **group_id** - ID группы viewport.
- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **offset** - Координаты смещения точки обзора камеры по соответствующим осям.

## Ptr < EngineWindowViewport > getEngineWindow ( int viewport_id ) const

Возвращает engine window viewport для указанного viewport.
### Аргументы

- *int* **viewport_id** - ID окна viewport.

### Возвращаемое значение

Engine window viewport.
