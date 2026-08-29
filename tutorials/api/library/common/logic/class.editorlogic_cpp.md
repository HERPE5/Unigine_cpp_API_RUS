# Unigine::EditorLogic Class (CPP)

**Header:** #include <UnigineLogic.h>


Класс EditorLogic используется для управления логикой редактора. Методы этого класса вызываются после соответствующих методов скрипта редактора.


Методы класса EditorLogic вызываются только если загружен [UnigineEditor](../../../../editor2/index.md).


## EditorLogic Class

### Методы класса

---

## virtual int init ( )

Движок вызывает эту функцию при инициализации редактора. Аналогична функции init() скрипта редактора.
### Возвращаемое значение

**1**, если редактор успешно инициализирован; иначе **0**.
## virtual int shutdown ( )

Движок вызывает эту функцию при завершении работы редактора. Аналогична функции *shutdown()* скрипта редактора.
### Возвращаемое значение

**1**, если завершение работы редактора выполнено успешно; иначе **0**.
## virtual int update ( )

Движок вызывает эту функцию перед обновлением каждого кадра рендеринга, когда редактор загружен. Аналогична функции *update()* скрипта редактора.
### Возвращаемое значение

**1**, если во время обновления редактора не было ошибок; иначе **0**.
## virtual int postUpdate ( )

Движок вызывает эту функцию после обновления каждого кадра рендеринга, когда редактор загружен. Аналогична функции *postUpdate()* скрипта редактора.
### Возвращаемое значение

**1**, если во время постобновления редактора не было ошибок; иначе **0**.
## virtual int render ( const EngineWindowViewportPtr& window )

Движок вызывает эту функцию перед рендерингом каждого кадра для указанного окна движка, когда редактор загружен. Аналогична функции *render()* скрипта редактора.
### Аргументы

- *const EngineWindowViewportPtr&* **window** - Целевой видовой экран окна движка.

### Возвращаемое значение

**1**, если во время рендеринга редактора не было ошибок; иначе **0**.
## virtual int worldInit ( )

Движок вызывает эту функцию при инициализации мира, когда редактор загружен. Эта функция аналогична функции *worldInit()* скрипта редактора.
### Возвращаемое значение

**1**, если во время инициализации мира не было ошибок; иначе **0**.
## virtual int worldShutdown ( )

Движок вызывает эту функцию при завершении работы мира, когда редактор загружен. Аналогична функции *worldShutdown()* скрипта редактора.
### Возвращаемое значение

**1**, если во время завершения работы мира не было ошибок; иначе **0**.
## virtual int worldSave ( )

Движок вызывает эту функцию при сохранении мира, когда редактор загружен. Аналогична функции *worldSave()* скрипта редактора.
### Возвращаемое значение

**1**, если во время сохранения мира не было ошибок; иначе **0**.
## virtual void clear ( )

Обратный вызов при перезагрузке мира и очистке списка узлов.
## virtual void nodeReparented ( const Node Ptr & node )

Обратный вызов при изменении родителя узла.
```cpp
void nodeReparented(conat NodePtr &node) override {
	if(node->getName() == "my_node") {
		Log::message("The parent of the node my_node has been changed\n");
	}
}

```


### Аргументы

- *const [Node](../../../../api/library/nodes/class.node_cpp.md)Ptr &* **node** - Умный указатель на узел.

## virtual void nodeReordered ( const Node Ptr & node )

Обратный вызов при изменении порядка узла.
```cpp
void nodeReordered(const NodePtr &node) override {
	if(node->getName() == "my_node") {
		Log::message("The node my_node is reordered\n");
	}
}

```


### Аргументы

- *const [Node](../../../../api/library/nodes/class.node_cpp.md)Ptr &* **node** - Умный указатель на узел.

## virtual void nodeRenamed ( const Node Ptr & node , const char * old_name )

Обратный вызов при переименовании узла.
```cpp
void nodeRenamed(const NodePtr &node, const char *old_name) override {
	if (old_name == "my_node") {
		Log::message("The node my_node has been renamed\n");
		Log::message("The new name of the node is %s\n",node->getName());
	}
}

```


### Аргументы

- *const [Node](../../../../api/library/nodes/class.node_cpp.md)Ptr &* **node** - Умный указатель на узел.
- *const char ** **old_name** - Старое имя переименованного узла.

## virtual void nodeShowInEditorChanged ( const Node Ptr & node )

Обратный вызов при изменении опции отображения узла в иерархии мира.
```cpp
void nodeShowInEditorChanged(const NodePtr &node) override {
	if(node->getName() == "my_node") {
		Log::message("Displaying in world hierarchy has changed for the my_node node\n");
	}
}

```


### Аргументы

- *const [Node](../../../../api/library/nodes/class.node_cpp.md)Ptr &* **node** - Умный указатель на узел.

## virtual void materialAdded ( const UGUID & guid )

Обратный вызов при добавлении материала.
### Аргументы

- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) материала.

## virtual void materialRemoved ( const UGUID & guid )

Обратный вызов при удалении материала.
### Аргументы

- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) материала.

## virtual void materialChanged ( const UGUID & guid )

Обратный вызов при изменении материала.
### Аргументы

- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) материала.

## virtual void materialReparented ( const UGUID & guid , const UGUID & old_parent , const UGUID & new_parent )

Обратный вызов при изменении родителя материала.
### Аргументы

- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) материала.
- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **old_parent** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) старого родительского материала.
- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **new_parent** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) нового родительского материала.

## virtual void propertyAdded ( const UGUID & guid )

Обратный вызов при добавлении свойства.
> **Notice:** Обратные вызовы срабатывают для всех свойств, включая [hidden](../../../../code/formats/property_format.md#property_hidden).

### Аргументы

- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) добавленного свойства.

## virtual void propertyRemoved ( const UGUID & guid )

Обратный вызов при удалении свойства.
> **Notice:** Обратные вызовы срабатывают для всех свойств, включая [hidden](../../../../code/formats/property_format.md#property_hidden).

### Аргументы

- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) удалённого свойства.

## virtual void propertyMoved ( const UGUID & guid )

Обратный вызов при перемещении свойства.
> **Notice:** Обратные вызовы срабатывают для всех свойств, включая [hidden](../../../../code/formats/property_format.md#property_hidden).

### Аргументы

- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) перемещённого свойства.

## virtual void propertyChanged ( const UGUID & guid )

Обратный вызов при изменении свойства.
> **Notice:** Обратные вызовы срабатывают для всех свойств, включая [hidden](../../../../code/formats/property_format.md#property_hidden).

### Аргументы

- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) изменённого свойства.

## virtual void propertyReparented ( const UGUID & guid , const UGUID & old_parent , const UGUID & new_parent )

Обратный вызов при изменении родителя свойства.
> **Notice:** Обратные вызовы срабатывают для всех свойств, включая [hidden](../../../../code/formats/property_format.md#property_hidden).

### Аргументы

- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) свойства, у которого изменён родитель.
- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **old_parent** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) старого родительского свойства.
- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **new_parent** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) нового родительского свойства.

## virtual void propertyReplaced ( const UGUID & guid , const UGUID & new_guid )

Обратный вызов при замене свойства другим.
> **Notice:** Обратные вызовы срабатывают для всех свойств, включая [hidden](../../../../code/formats/property_format.md#property_hidden).

### Аргументы

- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) заменяемого свойства.
- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **new_guid** - [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) свойства, на которое производится замена.

## virtual void materialCompileShadersBegin ( )

Обратный вызов при запуске процесса компиляции шейдеров.
## virtual void materialCompileShadersEnd ( )

Обратный вызов при завершении процесса компиляции шейдеров.
## virtual void materialCompileShaders ( const Material Ptr & material , int num )

Обратный вызов при завершении процесса компиляции шейдеров.
### Аргументы

- *const [Material](../../../../api/library/rendering/class.material_cpp.md)Ptr &* **material** - Текущий материал, для которого компилируются шейдеры.
- *int* **num** - Количество оставшихся материалов, для которых должны быть скомпилированы шейдеры.
