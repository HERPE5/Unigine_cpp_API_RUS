# Класс Unigine::Editor (CPP)

**Заголовочный файл:** #include <UnigineEditor.h>

> **Примечание:** Этот класс является одиночкой (singleton).


Этот класс предоставляет функциональность для [editor script](../../../code/fundamentals/execution_sequence/app_logic_system.md#editor_logic), который загружает и управляет иерархией узлов, отображаемой в редакторе.


> **Примечание:** Методы C++, выполняющие функции скрипта редактора, описаны в справочнике класса [Engine](../../../api/library/engine/class.engine_cpp.md).


## Класс Editor

### Методы класса

## void setPlayer ( const Ptr < Player >& player )

Устанавливает нового игрока, используемого в данный момент в режиме редактора.
> **Примечание:** Игрок редактора обрабатывается иначе, чем игровые игроки. Параметры, заданные напрямую для игрока, игнорируются; вместо этого игрок редактора использует параметры [Camera](../../../editor2/camera_settings/index.md), заданные через интерфейс. (См. скрипты редактора в папке `data/core/editor` для реализации.)


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Player](../../../api/library/players/class.player_cpp.md)>&* **player** - Игрок редактора.

## Ptr < Player > getPlayer () const

Возвращает текущего игрока, используемого в данный момент в режиме редактора.
> **Примечание:** Игрок редактора обрабатывается иначе, чем игровые игроки. Параметры, заданные напрямую для игрока, игнорируются; вместо этого игрок редактора использует параметры [Camera](../../../editor2/camera_settings/index.md), заданные через интерфейс. (См. скрипты редактора в папке `data/core/editor` для реализации.)


### Возвращаемое значение

Текущий игрок редактора.
## void setVRPlayer ( const Ptr < Player >& vrplayer )

Устанавливает нового игрока, используемого в данный момент для рендеринга VR в режиме редактора. Если VR Player не задан, VR рендерится для [Editor Player](#getPlayer_Player); если Editor Player тоже не задан, для рендеринга используется [Game Player](../../../api/library/engine/class.game_cpp.md#getPlayer_Player).
> **Примечание:** Игрок редактора обрабатывается иначе, чем игровые игроки. Параметры, заданные напрямую для игрока, игнорируются; вместо этого игрок редактора использует параметры [Camera](../../../editor2/camera_settings/index.md), заданные через интерфейс. (См. скрипты редактора в папке `data/core/editor` для реализации.)


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Player](../../../api/library/players/class.player_cpp.md)>&* **vrplayer** - Игрок для рендеринга VR.

## Ptr < Player > getVRPlayer () const

Возвращает текущего игрока, используемого в данный момент для рендеринга VR в режиме редактора. Если VR Player не задан, VR рендерится для [Editor Player](#getPlayer_Player); если Editor Player тоже не задан, для рендеринга используется [Game Player](../../../api/library/engine/class.game_cpp.md#getPlayer_Player).
> **Примечание:** Игрок редактора обрабатывается иначе, чем игровые игроки. Параметры, заданные напрямую для игрока, игнорируются; вместо этого игрок редактора использует параметры [Camera](../../../editor2/camera_settings/index.md), заданные через интерфейс. (См. скрипты редактора в папке `data/core/editor` для реализации.)


### Возвращаемое значение

Текущий игрок для рендеринга VR.
## void setData ( const char * data )

Устанавливает новые пользовательские строковые данные, связанные с миром. Эта строка записывается непосредственно в тег data файла `*.world`.
### Аргументы

- *const char ** **data** - Пользовательские строковые данные.

## const char * getData () const

Возвращает текущие пользовательские строковые данные, связанные с миром. Эта строка записывается непосредственно в тег data файла `*.world`.
### Возвращаемое значение

Текущие пользовательские строковые данные.
## void setEnabled ( bool enabled )

Устанавливает новое значение параметра *Enabled*. Параметр *Enabled* управляет всей внутренней дополнительной обработкой движка (например, перезагрузкой текстур при изменении времени их записи и т.д.). Например, параметр *Enabled* можно установить в 0 при использовании Syncker для повышения производительности движка (так как Syncker работает внутри среды редактора и может снижать производительность движка).
### Аргументы

- *bool* **enabled** - **true** — включить параметр *Enabled*; **false** — отключить.

## bool isEnabled () const

Возвращает текущее значение параметра *Enabled*. Параметр *Enabled* управляет всей внутренней дополнительной обработкой движка (например, перезагрузкой текстур при изменении времени их записи и т.д.). Например, параметр *Enabled* можно установить в 0 при использовании Syncker для повышения производительности движка (так как Syncker работает внутри среды редактора и может снижать производительность движка).
### Возвращаемое значение

**true**, если параметр *Enabled* включён; иначе **false**.
## bool isLoaded () const

Возвращает текущее значение, указывающее, загружен ли уже редактор.
### Возвращаемое значение

**true**, если редактор загружен; иначе **false**.
---

## void load ( const char * script = "editor/editor.usc" )

Загружает редактор из указанного скрипта.
### Аргументы

- *const char ** **script** - Путь к скрипту.

## void quit ( )

Завершает работу редактора.
## void reload ( )

Перезагружает UnigineEditor. Эта функция обновляет иерархию узлов, обновляет загруженные текстуры, если они были изменены, и т.д.
## int needReload ( )

Возвращает значение, указывающее, следует ли перезагрузить UnigineEditor.
### Возвращаемое значение

**1**, если редактор следует перезагрузить; иначе **0**.
## void addEditorPlayer ( const Ptr < Player > & player )

Добавляет ещё одного игрока редактора.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Player](../../../api/library/players/class.player_cpp.md)> &* **player** - Указатель на Player.

## void removeEditorPlayer ( const Ptr < Player > & player )

Удаляет заданного игрока из редактора.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Player](../../../api/library/players/class.player_cpp.md)> &* **player** - Указатель на Player.

## bool isEditorPlayer ( const Ptr < Player > & player ) const

Возвращает значение, указывающее, является ли заданный игрок игроком редактора.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Player](../../../api/library/players/class.player_cpp.md)> &* **player** - Умный указатель на экземпляр *Player*.

### Возвращаемое значение

true, если *Player* является игроком редактора; иначе false.
## Ptr < Node > getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , bool use_handlers = true )

Ищет все узлы, пересекаемые линией, проведённой от **p0** до **p1**. Возвращается узел, ближайший к начальной точке.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты начальной точки линии
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты конечной точки линии
- *bool* **use_handlers** - true, чтобы включить объекты, доступные только в редакторе (обработчики узлов), в список пересекаемых узлов; false — игнорировать обработчики.

### Возвращаемое значение

Первый найденный вдоль линии пересекаемый узел; иначе *nullptr*, если пересечения не было.
## Ptr < Node > getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , const Ptr < WorldIntersection > & intersection , bool use_handlers = true )

Ищет все узлы, пересекающие линию. Возвращается узел, ближайший к начальной точке. Результат пересечения будет представлен как экземпляр WorldIntersection.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты начальной точки линии.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты конечной точки линии.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[WorldIntersection](../../../api/library/worlds/class.worldintersection_cpp.md)> &* **intersection** - Экземпляр класса *WorldIntersection*, содержащий информацию о пересечении.
- *bool* **use_handlers** - true, чтобы включить объекты, доступные только в редакторе (обработчики узлов), в список пересекаемых узлов; false — игнорировать обработчики.

### Возвращаемое значение

Первый найденный вдоль линии пересекаемый узел; иначе *nullptr*, если пересечения не было.
## Ptr < Node > getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , const Ptr < WorldIntersectionNormal > & intersection , bool use_handlers = true )

Ищет все узлы, пересекающие линию. Возвращается узел, ближайший к начальной точке. Результат пересечения будет представлен как экземпляр WorldIntersectionNormal.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты начальной точки линии.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты конечной точки линии.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[WorldIntersectionNormal](../../../api/library/worlds/class.worldintersectionnormal_cpp.md)> &* **intersection** - Экземпляр класса *WorldIntersectionNormal*, содержащий информацию о пересечении.
- *bool* **use_handlers** - true, чтобы включить объекты, доступные только в редакторе (обработчики узлов), в список пересекаемых узлов; false — игнорировать обработчики.

### Возвращаемое значение

Первый найденный вдоль линии пересекаемый узел; иначе *nullptr*, если пересечения не было.
## Ptr < Node > getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , const Ptr < WorldIntersectionTexCoord > & intersection , bool use_handlers = true )

Ищет все узлы, пересекающие линию. Возвращается узел, ближайший к начальной точке. Результат пересечения будет представлен как узел WorldIntersectionTexCoord.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальная точка линии.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечная точка линии.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[WorldIntersectionTexCoord](../../../api/library/worlds/class.worldintersectiontexcoord_cpp.md)> &* **intersection** - Экземпляр класса *WorldIntersectionTexCoord*, содержащий информацию о пересечении.
- *bool* **use_handlers** - true, чтобы включить объекты, доступные только в редакторе (обработчики узлов), в список пересекаемых узлов; false — игнорировать обработчики.

### Возвращаемое значение

Первый найденный вдоль линии пересекаемый узел; иначе *nullptr*, если пересечения не было.
## bool getIntersection ( const Math:: WorldBoundFrustum & bs , Vector < Ptr < Node >> & OUT_nodes , bool use_handlers )

Находит все узлы, пересекаемые указанным ограничивающим усечённым конусом (frustum), и помещает их в указанный выходной буфер. По умолчанию этот метод получает объекты, доступные только в редакторе (обработчики узлов), вместе с узлами; чтобы игнорировать их, просто установите use_handlers в false.
### Аргументы

- *const  Math::[WorldBoundFrustum](../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bs** - Ограничивающий усечённый конус, в котором выполняется поиск пересечений.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **OUT_nodes** - Выходной буфер для хранения списка пересекаемых узлов (если есть). > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
- *bool* **use_handlers** - true, чтобы включить объекты, доступные только в редакторе (обработчики узлов), в список пересекаемых узлов; false — игнорировать обработчики.

### Возвращаемое значение

true, если пересекаемые узлы найдены; иначе false.
## Ptr < Node > getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , CallbackBase2 < Ptr < Node >, bool *> * node_filter , CallbackBase3 < Ptr < Object >, int, bool *> * surface_filter , bool use_handlers = true )

Ищет все узлы, пересекаемые линией, проведённой от **p0** до **p1**, игнорируя те, что определены указанными **фильтрами**. Возвращается узел, ближайший к начальной точке (если найден).
```cpp
// список исключаемых узлов
HashSet<NodePtr> excludes;

// пользовательская функция, определяющая, исключён ли заданный узел
bool exclude_node(NodePtr node)
{
	// ...
	return result;
}

// пользовательская функция, определяющая, исключена ли заданная поверхность
// в зависимости от заданной маски вьюпорта
bool test_viewport_mask(ObjectPtr object, int surface, int viewport_mask)
{
	// ...
	return result;
}

// ...

// обратный вызов, определяющий, следует ли исключить (пропустить) узел
CallbackBase2<NodePtr, bool *> *exclude_callback = MakeCallback(
	[&](NodePtr node, bool *exclude) {
		*exclude = !node->isEnabled() || excludes.contains(node) || exclude_node(node);
	});

// обратный вызов, определяющий, следует ли исключить (пропустить) поверхность объекта
CallbackBase3<ObjectPtr, int, bool *> *exclude_surface = MakeCallback(
	[this, viewport_mask](ObjectPtr object, int surface, bool *excluded) {
		*excluded = test_viewport_mask(object, surface, viewport_mask) == false;
	});

// поиск пересечения с применением фильтров на основе обратных вызовов для узлов
// и для поверхностей (когда установлен соответствующий флаг)
NodePtr node = Unigine::Editor::getIntersection(p0, p1, exclude_callback,
	use_viewport_mask ? exclude_surface : nullptr, true);

```


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты начальной точки линии
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты конечной точки линии
- *[CallbackBase2](../../../api/library/common/callbacks/class.callbackbase2_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>, bool *> ** **node_filter** - Функция обратного вызова, используемая для отфильтровывания (игнорирования) определённых узлов во время проверки пересечений. Передайте *nullptr*, если вам не нужны исключения узлов (нечего исключать). Функция обратного вызова должна иметь следующую сигнатуру: *filter_callback(**NodePtr** node, **bool *** excluded)*
- *[CallbackBase3](../../../api/library/common/callbacks/class.callbackbase3_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)>, int, bool *> ** **surface_filter** - Функция обратного вызова, используемая для отфильтровывания (игнорирования) определённых поверхностей во время проверки пересечений. Передайте *nullptr*, если вам не нужны исключения поверхностей (нечего исключать). Функция обратного вызова должна иметь следующую сигнатуру: *filter_callback(**ObjectPtr** obj, **int** num_surface, **bool *** excluded)*
- *bool* **use_handlers** - true, чтобы включить объекты, доступные только в редакторе (обработчики узлов), в список пересекаемых узлов; false — игнорировать обработчики.

### Возвращаемое значение

Первый найденный пересекаемый узел, если найден; иначе *nullptr*, если пересечения не было.
## Ptr < Node > getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , CallbackBase2 < Ptr < Node >, bool *> * node_filter , CallbackBase3 < Ptr < Object >, int, bool *> * surface_filter , const Ptr < WorldIntersection > & intersection , bool use_handlers = true )

Searches for all nodes intersected by the line traced from **p0** to **p1**, ignoring the ones defined by the specified **filters**. The node closest to the start point is returned (if any).
```cpp
// list of nodes to be excluded
HashSet<NodePtr> excludes;

// custom function that determines whether the specified node is excluded
bool exclude_node(NodePtr node)
{
	// ...
	return result;
}

// custom function that determines whether the specified surface is excluded
// depending on the given viewport mask
bool test_viewport_mask(ObjectPtr object, int surface, int viewport_mask)
{
	// ...
	return result;
}

// ...

WorldIntersectionPtr intersection = WorldIntersection::create();

// callback that determines whether a node is to be excluded (skipped)
CallbackBase2<NodePtr, bool *> *exclude_callback = MakeCallback(
	[&](NodePtr node, bool *exclude) {
		*exclude = !node->isEnabled() || excludes.contains(node) || exclude_node(node);
	});

// callback that determines whether a surface of an object is to be excluded (skipped)
CallbackBase3<ObjectPtr, int, bool *> *exclude_surface = MakeCallback(
	[this, viewport_mask](ObjectPtr object, int surface, bool *excluded) {
		*excluded = test_viewport_mask(object, surface, viewport_mask) == false;
	});

// searching for intersection applying callback-based filters for nodes
// and for surfaces (when the corresponding flag is set)
NodePtr node = Unigine::Editor::getIntersection(p0, p1, exclude_callback,
	use_viewport_mask ? exclude_surface : nullptr, intersection, true);

```


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты начальной точки линии
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты конечной точки линии
- *[CallbackBase2](../../../api/library/common/callbacks/class.callbackbase2_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>, bool *> ** **node_filter** - Функция обратного вызова, используемая для отфильтровывания (игнорирования) определённых узлов во время проверки пересечений. Передайте *nullptr*, если вам не нужны исключения узлов (нечего исключать). Функция обратного вызова должна иметь следующую сигнатуру: *filter_callback(**NodePtr** node, **bool *** excluded)*
- *[CallbackBase3](../../../api/library/common/callbacks/class.callbackbase3_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)>, int, bool *> ** **surface_filter** - Функция обратного вызова, используемая для отфильтровывания (игнорирования) определённых поверхностей во время проверки пересечений. Передайте *nullptr*, если вам не нужны исключения поверхностей (нечего исключать). Функция обратного вызова должна иметь следующую сигнатуру: *filter_callback(**ObjectPtr** obj, **int** num_surface, **bool *** excluded)*
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[WorldIntersection](../../../api/library/worlds/class.worldintersection_cpp.md)> &* **intersection** - *WorldIntersection* class instance containing the intersection information.
- *bool* **use_handlers** - true to include editor-only objects (node handlers) in the list of intersected nodes; false - to ignore handlers.

### Возвращаемое значение

Первый найденный пересекаемый узел, если найден; иначе *nullptr*, если пересечения не было.
## Ptr < Node > getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , CallbackBase2 < Ptr < Node >, bool *> * node_filter , CallbackBase3 < Ptr < Object >, int, bool *> * surface_filter , const Ptr < WorldIntersectionNormal > & intersection , bool use_handlers = true )

Searches for all nodes intersected by the line traced from **p0** to **p1**, ignoring the ones defined by the specified **filters**. The node closest to the start point is returned (if any).
```cpp
// list of nodes to be excluded
HashSet<NodePtr> excludes;

// custom function that determines whether the specified node is excluded
bool exclude_node(NodePtr node)
{
	// ...
	return result;
}

// custom function that determines whether the specified surface is excluded
// depending on the given viewport mask
bool test_viewport_mask(ObjectPtr object, int surface, int viewport_mask)
{
	// ...
	return result;
}

// ...

WorldIntersectionNormalPtr intersection = WorldIntersectionNormal::create();

// callback that determines whether a node is to be excluded (skipped)
CallbackBase2<NodePtr, bool *> *exclude_callback = MakeCallback(
	[&](NodePtr node, bool *exclude) {
		*exclude = !node->isEnabled() || excludes.contains(node) || exclude_node(node);
	});

// callback that determines whether a surface of an object is to be excluded (skipped)
CallbackBase3<ObjectPtr, int, bool *> *exclude_surface = MakeCallback(
	[this, viewport_mask](ObjectPtr object, int surface, bool *excluded) {
		*excluded = test_viewport_mask(object, surface, viewport_mask) == false;
	});

// searching for intersection applying callback-based filters for nodes
// and for surfaces (when the corresponding flag is set)
NodePtr node = Unigine::Editor::getIntersection(p0, p1, exclude_callback,
	use_viewport_mask ? exclude_surface : nullptr, intersection, true);

```


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты начальной точки линии
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты конечной точки линии
- *[CallbackBase2](../../../api/library/common/callbacks/class.callbackbase2_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>, bool *> ** **node_filter** - Функция обратного вызова, используемая для отфильтровывания (игнорирования) определённых узлов во время проверки пересечений. Передайте *nullptr*, если вам не нужны исключения узлов (нечего исключать). Функция обратного вызова должна иметь следующую сигнатуру: *filter_callback(**NodePtr** node, **bool *** excluded)*
- *[CallbackBase3](../../../api/library/common/callbacks/class.callbackbase3_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)>, int, bool *> ** **surface_filter** - Функция обратного вызова, используемая для отфильтровывания (игнорирования) определённых поверхностей во время проверки пересечений. Передайте *nullptr*, если вам не нужны исключения поверхностей (нечего исключать). Функция обратного вызова должна иметь следующую сигнатуру: *filter_callback(**ObjectPtr** obj, **int** num_surface, **bool *** excluded)*
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[WorldIntersectionNormal](../../../api/library/worlds/class.worldintersectionnormal_cpp.md)> &* **intersection** - *WorldIntersectionNormal* class instance containing the intersection information.
- *bool* **use_handlers** - true to include editor-only objects (node handlers) in the list of intersected nodes; false - to ignore handlers.

### Возвращаемое значение

Первый найденный пересекаемый узел, если найден; иначе *nullptr*, если пересечения не было.
## Ptr < Node > getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , CallbackBase2 < Ptr < Node >, bool *> * node_filter , CallbackBase3 < Ptr < Object >, int, bool *> * surface_filter , const Ptr < WorldIntersectionTexCoord > & intersection , bool use_handlers = true )

Searches for all nodes intersected by the line traced from **p0** to **p1**, ignoring the ones defined by the specified **filters**. The node closest to the start point is returned (if any).
```cpp
// list of nodes to be excluded
HashSet<NodePtr> excludes;

// custom function that determines whether the specified node is excluded
bool exclude_node(NodePtr node)
{
	// ...
}

// custom function that determines whether the specified surface is excluded
// depending on the given viewport mask
bool test_viewport_mask(ObjectPtr object, int surface, int viewport_mask)
{
	// ...
}

// ...

WorldIntersectionTexCoordPtr intersection = WorldIntersectionTexCoord::create();

// callback that determines whether a node is to be excluded (skipped)
CallbackBase2<NodePtr, bool *> *exclude_callback = MakeCallback(
	[&](NodePtr node, bool *exclude) {
		*exclude = !node->isEnabled() || excludes.contains(node) || exclude_node(node);
	});

// callback that determines whether a surface of an object is to be excluded (skipped)
CallbackBase3<ObjectPtr, int, bool *> *exclude_surface = MakeCallback(
	[this, viewport_mask](ObjectPtr object, int surface, bool *excluded) {
		*excluded = test_viewport_mask(object, surface, viewport_mask) == false;
	});

// searching for intersection applying callback-based filters for nodes
// and for surfaces (when the corresponding flag is set)
NodePtr node = Unigine::Editor::getIntersection(p0, p1, exclude_callback,
	use_viewport_mask ? exclude_surface : nullptr, intersection, true);

```


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты начальной точки линии
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты конечной точки линии
- *[CallbackBase2](../../../api/library/common/callbacks/class.callbackbase2_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>, bool *> ** **node_filter** - Функция обратного вызова, используемая для отфильтровывания (игнорирования) определённых узлов во время проверки пересечений. Передайте *nullptr*, если вам не нужны исключения узлов (нечего исключать). Функция обратного вызова должна иметь следующую сигнатуру: *filter_callback(**NodePtr** node, **bool *** excluded)*
- *[CallbackBase3](../../../api/library/common/callbacks/class.callbackbase3_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)>, int, bool *> ** **surface_filter** - Функция обратного вызова, используемая для отфильтровывания (игнорирования) определённых поверхностей во время проверки пересечений. Передайте *nullptr*, если вам не нужны исключения поверхностей (нечего исключать). Функция обратного вызова должна иметь следующую сигнатуру: *filter_callback(**ObjectPtr** obj, **int** num_surface, **bool *** excluded)*
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[WorldIntersectionTexCoord](../../../api/library/worlds/class.worldintersectiontexcoord_cpp.md)> &* **intersection** - *WorldIntersectionTexCoord* class instance containing the intersection information.
- *bool* **use_handlers** - true to include editor-only objects (node handlers) in the list of intersected nodes; false - to ignore handlers.

### Возвращаемое значение

Первый найденный пересекаемый узел, если найден; иначе *nullptr*, если пересечение не было найдено.
