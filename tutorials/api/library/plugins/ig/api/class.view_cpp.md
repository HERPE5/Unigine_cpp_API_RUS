# Unigine::Plugins::IG::View Class (CPP)

**Header:** #include <plugins/Unigine/IG/UnigineIG.h>


Этот класс представляет интерфейс View IG.

> **Notice:** Плагин IG должен быть загружен.


## View Class

### Перечисления

## MIRROR

| Name | Description |
|---|---|
| **MIRROR_NONE** = 0 | Режим зеркалирования view отсутствует. |
| **MIRROR_HORIZONTAL** = 1 | Горизонтальный режим зеркалирования view. |
| **MIRROR_VERTICAL** = 2 | Вертикальный режим зеркалирования view. |
| **MIRROR_BOTH** = 3 | Горизонтальный и вертикальный режим зеркалирования view. |

## PROJECTION

| Name | Description |
|---|---|
| **PROJECTION_PERSPECTIVE** = 0 | Перспективная проекция view. |
| **PROJECTION_ORTHOGRAPHIC** = 1 | Ортографическая проекция view. |

## REPLICATION

| Name | Description |
|---|---|
| **REPLICATION_MODE_1_1** = 0 | Функция репликации пикселей, применяемая к view: отсутствует. Эта возможность обычно используется в сенсорных приложениях для выполнения электронного зума (т.е. удвоения пикселей и строк). |
| **REPLICATION_MODE_1_2** = 1 | Функция репликации пикселей, применяемая к view: 1 x 2. Эта возможность обычно используется в сенсорных приложениях для выполнения электронного зума (т.е. удвоения пикселей и строк). |
| **REPLICATION_MODE_2_1** = 2 | Функция репликации пикселей, применяемая к view: 2 x 1. Эта возможность обычно используется в сенсорных приложениях для выполнения электронного зума (т.е. удвоения пикселей и строк). |
| **REPLICATION_MODE_2_2** = 3 | Функция репликации пикселей, применяемая к view: 2 x 2. Эта возможность обычно используется в сенсорных приложениях для выполнения электронного зума (т.е. удвоения пикселей и строк). |

### Методы класса

---

## int getID ( )

Возвращает ID view.
### Возвращаемое значение

ID view.
## void setParentGroup ( ViewGroup * view_group )

Присоединяет view как дочерний к указанной родительской [view group](../../../../../api/library/plugins/ig/api/class.viewgroup_cpp.md).
### Аргументы

- *[ViewGroup](../../../../../api/library/plugins/ig/api/class.viewgroup_cpp.md) ** **view_group** - Родительская группа view.

## int getParentGroupID ( )

Возвращает ID родительской группы для view.
### Возвращаемое значение

ID родительской группы view.
## void setDefinition ( float near , float far , float left_deg , float right_deg , float top_deg , float bottom_deg )

Задаёт параметры объёма просмотра (проекции) для view с использованием указанных значений.
### Аргументы

- *float* **near** - Расстояние до ближней плоскости отсечения, в единицах.
- *float* **far** - Расстояние до дальней плоскости отсечения, в единицах.
- *float* **left_deg** - Левый полуугол, в градусах.
- *float* **right_deg** - Правый полуугол, в градусах.
- *float* **top_deg** - Верхний полуугол, в градусах.
- *float* **bottom_deg** - Нижний полуугол, в градусах.

## void setDefinition ( float near , float far , float fov )

Задаёт параметры объёма просмотра (проекции) для view с использованием указанных значений.
### Аргументы

- *float* **near** - Расстояние до ближней плоскости отсечения, в единицах.
- *float* **far** - Расстояние до дальней плоскости отсечения, в единицах.
- *float* **fov** - Угол поля зрения, в градусах.

## void copyDefinitionFromPlayer ( const Ptr < Player > & player )

Задаёт параметры объёма просмотра (проекции) для view, копируя их из указанного Player.
> **Notice:** *Маску viewport* следует копировать отдельно.

### Аргументы

- *const [Ptr](../../../../../api/library/common/class.ptr_cpp.md)<[Player](../../../../../api/library/players/class.player_cpp.md)> &* **player** - Исходный Player, из которого копируются параметры объёма просмотра (проекции).

## float getNear ( )

Возвращает текущее расстояние до ближней плоскости отсечения.
### Возвращаемое значение

Расстояние до ближней плоскости отсечения, в единицах.
## float getFar ( )

Возвращает текущее расстояние до дальней плоскости отсечения.
### Возвращаемое значение

Расстояние до дальней плоскости отсечения, в единицах.
## float getLeftDeg ( )

Возвращает текущий левый полуугол усечённой пирамиды видимости view.
### Возвращаемое значение

Левый полуугол, в градусах.
## float getRightDeg ( )

Возвращает текущий правый полуугол усечённой пирамиды видимости view.
### Возвращаемое значение

Правый полуугол, в градусах.
## float getTopDeg ( )

Возвращает текущий верхний полуугол усечённой пирамиды видимости view.
### Возвращаемое значение

Верхний полуугол, в градусах.
## float getBottomDeg ( )

Возвращает текущий нижний полуугол усечённой пирамиды видимости view.
### Возвращаемое значение

Нижний полуугол, в градусах.
## void setReplicationMode ( View::REPLICATION mode )

Задаёт режим репликации для view.
### Аргументы

- *[View::REPLICATION](../../../../../api/library/plugins/ig/api/class.view_cpp.md#REPLICATION)* **mode** - Задаваемый режим репликации. Одно из значений [REPLICATION_*](#REPLICATION_MODE_1_1).

## View::REPLICATION getReplicationMode ( ) const

Возвращает текущий режим репликации для view.
### Возвращаемое значение

Режим репликации. Одно из значений [REPLICATION_*](#REPLICATION_MODE_1_1).
## void setMirrorMode ( View::MIRROR mode )

Задаёт режим зеркалирования для view.
### Аргументы

- *[View::MIRROR](../../../../../api/library/plugins/ig/api/class.view_cpp.md#MIRROR)* **mode** - Задаваемый режим зеркалирования. Одно из значений [MIRROR_*](#MIRROR_NONE).

## View::MIRROR getMirrorMode ( ) const

Возвращает текущий режим зеркалирования для view.
### Возвращаемое значение

Режим зеркалирования. Одно из значений [MIRROR_*](#MIRROR_NONE).
## void setProjection ( View::PROJECTION type )

Задаёт тип проекции для view.
### Аргументы

- *[View::PROJECTION](../../../../../api/library/plugins/ig/api/class.view_cpp.md#PROJECTION)* **type** - Задаваемый тип проекции. Одно из значений [PROJECTION_*](#PROJECTION_PERSPECTIVE).

## View::PROJECTION getProjection ( ) const

Возвращает текущий тип проекции для view.
### Возвращаемое значение

Тип проекции. Одно из значений [PROJECTION_*](#PROJECTION_PERSPECTIVE).
## void setViewType ( int type )

Задаёт тип view. Значение этого параметра указывает определённый в IG тип для view.
### Аргументы

- *int* **type** - Задаваемый тип view.

## int getViewType ( ) const

Возвращает текущий тип view. Тип view, определённый в IG.
### Возвращаемое значение

Тип view.
## void setEnabled ( bool value )

true, чтобы включить view; false - чтобы отключить.
### Аргументы

- *bool* **value** - true, если view включён; иначе false.

## bool isEnabled ( ) const

Возвращает значение, указывающее, включён ли view.
### Возвращаемое значение

true, если view включён; иначе false.
## void setSynckerProjectionEnable ( bool value )

Задаёт значение, указывающее, подвержен ли view влиянию [Syncker's projections](../../../../../code/plugins/syncker/index.md#screen_configs).
### Аргументы

- *bool* **value** - true, чтобы view был подвержен влиянию [Syncker's projections](../../../../../code/plugins/syncker/index.md#screen_configs); false, чтобы view игнорировал их.

## bool isSynckerProjectionEnable ( ) const

Возвращает значение, указывающее, подвержен ли view влиянию [Syncker's projections](../../../../../code/plugins/syncker/index.md#screen_configs).
### Возвращаемое значение

true, если view подвержен влиянию [Syncker's projections](../../../../../code/plugins/syncker/index.md#screen_configs); иначе false.
