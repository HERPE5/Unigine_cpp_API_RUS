# Unigine::WidgetSpriteViewport Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** WidgetSprite


Этот класс используется для создания виртуальных мониторов, отображающих данные с произвольных камер в мире. Этот виджет используется для рендеринга всей сцены со всеми постпроцессами движка, такими как HDR, DOF, motion blur, glow и т.д. В отличие от [WidgetSpriteNode](../../../api/library/gui/class.widgetspritenode_cpp.md), этот виджет не поддерживает маскирование по альфа-каналу.


> **Notice:** По умолчанию viewport спрайта рендерится с той же частотой кадров, что и главный viewport Unigine. Чтобы он рендерился с другой частотой кадров (например, более низкой для снижения нагрузки на рендеринг), используйте [*setIFps()*](#setIFps_float_void).


### См. также


- C++ sample


## WidgetSpriteViewport Class

### Методы класса

---

## static WidgetSpriteViewportPtr create ( const Ptr < Gui > & gui , int width , int height )

Конструктор. Создаёт новый спрайт viewport с заданными свойствами и добавляет его в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - [GUI](../../../api/library/gui/class.gui_cpp.md), которому будет принадлежать новый спрайт.
- *int* **width** - Ширина спрайта.
- *int* **height** - Высота спрайта.

## static WidgetSpriteViewportPtr create ( int width , int height )

Конструктор. Создаёт новый спрайт viewport с заданными свойствами и добавляет его в GUI движка.
### Аргументы

- *int* **width** - Ширина спрайта.
- *int* **height** - Высота спрайта.

## void setAspectCorrection ( bool correction )

Задаёт коррекцию соотношения сторон для WidgetSpriteViewport. true включает коррекцию, false отключает.
### Аргументы

- *bool* **correction** - true включает коррекцию соотношения сторон, false отключает.

## bool isAspectCorrection ( ) const

Возвращает значение, указывающее, включена ли коррекция соотношения сторон для WidgetSpriteViewport.
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
## void setIFps ( float ifps )

Задаёт постоянную длительность кадра, используемую для рендеринга viewport спрайта. Это можно использовать для снижения частоты кадров с целью повышения производительности. (Например, если виджет используется для создания телевизора, пониженная частота кадров не даёт визуальной разницы, но позволяет быстрее рендерить сцену.)
### Аргументы

- *float* **ifps** - Длительность кадра в секундах (*1/FPS*). Если задано слишком маленькое значение, вместо него будет использовано **1E-6**. **0** означает, что виджет рендерится с той же частотой кадров, что и главное окно приложения.

## float getIFps ( ) const

Возвращает текущую постоянную длительность кадра, используемую для рендеринга viewport WidgetSpriteViewport.
### Возвращаемое значение

Длительность кадра в секундах (1 / FPS).
## void setModelview ( const Math:: Mat4 & modelview )

Задаёт видовую матрицу для связанной камеры.
### Аргументы

- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **modelview** - Видовая матрица.

## Math:: Mat4 getModelview ( ) const

Возвращает текущую видовую матрицу связанной камеры.
### Возвращаемое значение

Видовая матрица.
## void setProjection ( const Math:: mat4 & projection )

Задаёт матрицу проекции для связанной камеры.
### Аргументы

- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **projection** - Матрица проекции.

## Math:: mat4 getProjection ( ) const

Возвращает текущую матрицу проекции связанной камеры.
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

- *int* **flags** - [Skip flag](../../../api/library/rendering/class.viewport_cpp.md#SKIP_SHADOWS). Доступные флаги:

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
## void setViewportMask ( int mask )

Задаёт битовую маску для рендеринга в viewport. Узлы рендерятся в этом viewport спрайта, если их маски совпадают с этой.
### Аргументы

- *int* **mask** - Целое число, каждый бит которого является маской.

## int getViewportMask ( ) const

Возвращает текущую битовую маску для рендеринга в viewport. Узлы рендерятся в viewport спрайта, если их маски совпадают с этой.
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

Рендерит viewport спрайта в указанную целевую текстуру.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Целевая текстура.

## void setUseTAAOffset ( bool offset )

Задаёт значение, указывающее, включён ли пропуск проверки режима рендеринга для использования TAA. Может использоваться для обеспечения корректного расчёта TAA, когда режим рендеринга для *Viewport* установлен в [RENDER_DEPTH](../../../api/library/rendering/class.viewport_cpp.md#RENDER_DEPTH).
### Аргументы

- *bool* **offset** - true включает пропуск проверки режима рендеринга и использование TAA; иначе false.

## bool isUseTAAOffset ( ) const

Возвращает значение, указывающее, включён ли пропуск проверки режима рендеринга для использования TAA. Может использоваться для обеспечения корректного расчёта TAA, когда режим рендеринга для *Viewport* установлен в [RENDER_DEPTH](../../../api/library/rendering/class.viewport_cpp.md#RENDER_DEPTH).
### Возвращаемое значение

true, если пропуск проверки режима рендеринга для использования TAA включён; иначе false.
