# Unigine::WidgetSpriteNode Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** WidgetSprite


Этот класс используется для отображения отдельных узлов вместе со всеми их дочерними узлами. Этот виджет поддерживает маскирование по альфа-каналу. Но, в отличие от [WidgetSpriteViewport](../../../api/library/gui/class.widgetspriteviewport_cpp.md), он не поддерживает постпроцессы движка (такие как HDR, DOF, motion blur, glow и т.д.); к нему можно применять только [postprocess-материалы](../../../content/materials/library/postprocess/index.md).


## WidgetSpriteNode Class

### Методы класса

---

## static WidgetSpriteNodePtr create ( const Ptr < Gui > & gui , int width , int height )

Конструктор. Создаёт новый спрайт с заданными свойствами и добавляет его в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - [GUI](../../../api/library/gui/class.gui_cpp.md), которому будет принадлежать новый спрайт.
- *int* **width** - Ширина спрайта.
- *int* **height** - Высота спрайта.

## static WidgetSpriteNodePtr create ( int width , int height )

Конструктор. Создаёт новый спрайт с заданными свойствами и добавляет его в GUI движка.
### Аргументы

- *int* **width** - Ширина спрайта.
- *int* **height** - Высота спрайта.

## void setAspectCorrection ( bool correction )

Задаёт коррекцию соотношения сторон для WidgetSpriteNode. true включает коррекцию, false отключает.
### Аргументы

- *bool* **correction** - true включает коррекцию соотношения сторон, false отключает.

## bool isAspectCorrection ( ) const

Возвращает значение, указывающее, включена ли коррекция соотношения сторон для WidgetSpriteNode.
### Возвращаемое значение

true, если коррекция соотношения сторон включена, иначе false.
## void setCamera ( const Ptr < Camera > & camera )

Копирует параметры заданного экземпляра Camera.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera** - Копируемая камера.

## Ptr < Camera > getCamera ( ) const

Копирует экземпляр камеры.
### Возвращаемое значение

Экземпляр камеры.
## void setEnvironmentTexturePath ( const char * path )

Задаёт указанный путь для текстуры Environment.
### Аргументы

- *const char ** **path** - Устанавливаемый путь к текстуре.

## const char * getEnvironmentTexturePath ( ) const

Возвращает путь к текстуре Environment.
### Возвращаемое значение

Путь к текстуре.
## void setIFps ( float ifps )

Задаёт постоянную длительность кадра, используемую для рендеринга viewport WidgetSpriteNode. Например, это можно использовать для снижения частоты кадров с целью повышения производительности.
### Аргументы

- *float* **ifps** - Длительность кадра в секундах (*1/FPS*). Если задано слишком маленькое значение, вместо него будет использовано **1E-6**.

## float getIFps ( ) const

Возвращает текущую длительность кадра, используемую для рендеринга viewport WidgetSpriteNode.
### Возвращаемое значение

Длительность кадра в секундах (*1/FPS*).
## void setLightUsage ( int usage )

Задаёт тип освещения для WidgetSpriteNode.
### Аргументы

- *int* **usage** - Тип освещения. Может быть одним из следующих:

  - [USAGE_WORLD_LIGHT](../../../api/library/rendering/class.viewport_cpp.md#USAGE_WORLD_LIGHT)
  - [USAGE_AUX_LIGHT](../../../api/library/rendering/class.viewport_cpp.md#USAGE_AUX_LIGHT)
  - [USAGE_NODE_LIGHT](../../../api/library/rendering/class.viewport_cpp.md#USAGE_NODE_LIGHT)

## int getLightUsage ( ) const

Возвращает тип освещения для WidgetSpriteNode.
### Возвращаемое значение

Тип освещения. Может быть одним из следующих:
- [USAGE_WORLD_LIGHT](../../../api/library/rendering/class.viewport_cpp.md#USAGE_WORLD_LIGHT)
- [USAGE_AUX_LIGHT](../../../api/library/rendering/class.viewport_cpp.md#USAGE_AUX_LIGHT)
- [USAGE_NODE_LIGHT](../../../api/library/rendering/class.viewport_cpp.md#USAGE_NODE_LIGHT)


## void setModelview ( const Math:: Mat4 & modelview )

Задаёт видовую матрицу.
### Аргументы

- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **modelview** - Видовая матрица.

## Math:: Mat4 getModelview ( ) const

Возвращает текущую видовую матрицу.
### Возвращаемое значение

Видовая матрица.
## void setNode ( const Ptr < Node > & node )

Задаёт узел для отображения.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел.

## Ptr < Node > getNode ( ) const

Возвращает текущий узел, заданный для отображения.
### Возвращаемое значение

Узел.
## void setProjection ( const Math:: mat4 & projection )

Задаёт матрицу проекции.
### Аргументы

- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **projection** - Матрица проекции.

## Math:: mat4 getProjection ( ) const

Возвращает текущую матрицу проекции.
### Возвращаемое значение

Матрица проекции.
## void setReflectionViewportMask ( int mask )

Задаёт битовую маску для рендеринга отражений в viewport. Отражения рендерятся в viewport спрайта, если маски отражающих материалов совпадают с этой (хотя бы один бит).
### Аргументы

- *int* **mask** - Целое число, каждый бит которого является маской.

## int getReflectionViewportMask ( ) const

Возвращает текущую битовую маску для рендеринга отражений в viewport. Отражения рендерятся в viewport спрайта, если маски отражающих материалов совпадают с этой (хотя бы один бит).
### Возвращаемое значение

Целое число, каждый бит которого является маской.
## void setSkipFlags ( int flags )

Задаёт [skip flag](../../../api/library/rendering/class.viewport_cpp.md#SKIP_SHADOWS) для viewport WidgetSpriteViewport.
### Аргументы

- *int* **flags** - [Skip flag.](../../../api/library/rendering/class.viewport_cpp.md#SKIP_SHADOWS) Доступные флаги:

  - SKIP_SHADOWS
  - SKIP_VISUALIZER
  - SKIP_POSTEFFECTS
  - SKIP_DYNAMIC_REFLECTIONS
  - SKIP_VELOCITY_BUFFER
  - SKIP_SRGB

## int getSkipFlags ( ) const

Возвращает [skip flag](../../../api/library/rendering/class.viewport_cpp.md#SKIP_SHADOWS), заданный для текущего viewport.
### Возвращаемое значение

[Skip flag.](../../../api/library/rendering/class.viewport_cpp.md#SKIP_SHADOWS) Доступные флаги:
- SKIP_SHADOWS
- SKIP_VISUALIZER
- SKIP_POSTEFFECTS
- SKIP_DYNAMIC_REFLECTIONS
- SKIP_VELOCITY_BUFFER
- SKIP_SRGB


## void setTextureHeight ( int height )

Задаёт высоту буфера текстуры, используемого для виджета. Это соответственно влияет на размер виджета.
### Аргументы

- *int* **height** - Высота размера буфера текстуры.

## int getTextureHeight ( ) const

Возвращает высоту буфера текстуры, используемого для виджета, что влияет на размер виджета.
### Возвращаемое значение

Высота размера буфера текстуры.
## void setTextureWidth ( int width )

Задаёт ширину буфера текстуры, используемого для виджета. Это соответственно влияет на размер виджета.
### Аргументы

- *int* **width** - Ширина размера буфера текстуры.

## int getTextureWidth ( ) const

Возвращает ширину буфера текстуры, используемого для виджета, что влияет на размер виджета.
### Возвращаемое значение

Ширина размера буфера текстуры.
## void setUseTAAOffset ( bool offset )

Задаёт значение, указывающее, включён ли пропуск проверки режима рендеринга для использования TAA. Может использоваться для обеспечения корректного расчёта TAA, когда режим рендеринга для *Viewport* установлен в [RENDER_DEPTH](../../../api/library/rendering/class.viewport_cpp.md#RENDER_DEPTH).
### Аргументы

- *bool* **offset** - true включает пропуск проверки режима рендеринга и использование TAA; иначе false.

## bool isUseTAAOffset ( ) const

Возвращает значение, указывающее, включён ли пропуск проверки режима рендеринга для использования TAA. Может использоваться для обеспечения корректного расчёта TAA, когда режим рендеринга для *Viewport* установлен в [RENDER_DEPTH](../../../api/library/rendering/class.viewport_cpp.md#RENDER_DEPTH).
### Возвращаемое значение

true, если пропуск проверки режима рендеринга для использования TAA включён; иначе false.
## void setViewportMask ( int mask )

Задаёт битовую маску для рендеринга в viewport. Узел рендерится в viewport спрайта, если его маска совпадает с этой.
### Аргументы

- *int* **mask** - Целое число, каждый бит которого является маской.

## int getViewportMask ( ) const

Возвращает текущую битовую маску для рендеринга в viewport. Узел рендерится в viewport спрайта, если его маска совпадает с этой.
### Возвращаемое значение

Целое число, каждый бит которого является маской.
## void appendSkipFlags ( int flags )

Добавляет новый [skip flag](../../../api/library/rendering/class.viewport_cpp.md#SKIP_SHADOWS) без перезаписи уже установленных.
### Аргументы

- *int* **flags** - [Skip flag.](../../../api/library/rendering/class.viewport_cpp.md#SKIP_SHADOWS) Доступные флаги:

  - SKIP_SHADOWS
  - SKIP_VISUALIZER
  - SKIP_POSTEFFECTS
  - SKIP_DYNAMIC_REFLECTIONS
  - SKIP_VELOCITY_BUFFER
  - SKIP_SRGB

## int checkSkipFlags ( int flags )

Проверяет, установлены ли уже заданные флаги.
### Аргументы

- *int* **flags** - [Skip flag.](../../../api/library/rendering/class.viewport_cpp.md#SKIP_SHADOWS) Доступные флаги:

  - SKIP_SHADOWS
  - SKIP_VISUALIZER
  - SKIP_POSTEFFECTS
  - SKIP_DYNAMIC_REFLECTIONS
  - SKIP_VELOCITY_BUFFER
  - SKIP_SRGB

### Возвращаемое значение

**1**, если флаг/флаги уже установлены, иначе **0**.
## void removeSkipFlags ( int flags )

Удаляет заданный skip flag, не затрагивая другие установленные флаги.
### Аргументы

- *int* **flags** - [Skip flag](../../../api/library/rendering/class.viewport_cpp.md#SKIP_SHADOWS) для удаления. Доступные флаги:

  - SKIP_SHADOWS
  - SKIP_VISUALIZER
  - SKIP_POSTEFFECTS
  - SKIP_DYNAMIC_REFLECTIONS
  - SKIP_VELOCITY_BUFFER
  - SKIP_SRGB

## void renderTexture ( const Ptr < Texture > & texture )

Рендерит sprite node в указанную целевую текстуру.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Целевая текстура.
