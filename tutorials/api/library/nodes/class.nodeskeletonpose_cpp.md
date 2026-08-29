# Класс NodeSkeletonPose (CPP)

**Header:** #include <UnigineNodes.h>

**Inherits from:** Node


Этот класс представляет узел-контроллер скелетной анимации. Он отделяет логику анимации от рендеринга, вычисляя скелетную позу и управляя одним или несколькими объектами [ObjectMeshSkinned](../../../api/library/objects/class.objectmeshskinned_cpp.md).


NodeSkeletonPose может работать в двух режимах:


- [MODE_ANIM_SCRIPT](#MODE_ANIM_SCRIPT) - поза вычисляется [animation script](../../../api/library/animations/skeletal/class.animscript_cpp.md) (скомпилированным графом анимации).
- [MODE_ANIM_LAYERS](#MODE_ANIM_LAYERS) - поза вычисляется вручную через слои анимации. Каждый слой содержит полный набор трансформаций суставов и может быть смешан с другими слоями с помощью [lerpLayer()](#lerpLayer_int_int_int_float_void), [mulLayer()](#mulLayer_int_int_int_float_void), или маскированного смешивания через [lerpLayerByMask()](#lerpLayerByMask_int_int_int_int_float_void).


Управляемыми объектами можно управлять либо в виде плоского списка ([CONTROL_TYPE_LIST](#CONTROL_TYPE_LIST)), либо через иерархию узлов ([CONTROL_TYPE_HIERARCHY](#CONTROL_TYPE_HIERARCHY)).


Используйте [play()](#play_void) / [pause()](#pause_void) для управления воспроизведением, [updatePose()](#updatePose_float_void) для принудительного ручного обновления позы, и [getPose()](#getPose_SkeletonPoseDecomposed_void) для получения текущей вычисленной позы. Каждый слой также предоставляет извлечение root motion через [extractLayerRootMotionByFrames()](#extractLayerRootMotionByFrames_int_float_float_int_Transform) / [extractLayerRootMotionByTimes()](#extractLayerRootMotionByTimes_int_float_float_int_Transform) и запросы sync-маркеров для синхронизации воспроизведения между анимациями.


## Класс NodeSkeletonPose

### Перечисления

## CONTROL_TYPE

Тип управления, определяющий, как узел находит и управляет своими управляемыми объектами ObjectMeshSkinned.
| Название | Описание |
|---|---|
| **CONTROL_TYPE_HIERARCHY** = 0 | Управляемые объекты находятся автоматически путём обхода иерархии узлов (дочерних узлов). |
| **CONTROL_TYPE_LIST** = 1 | Управляемые объекты задаются явно через плоский список. |

## MODE

Режим работы, определяющий, как вычисляется скелетная поза.
| Название | Описание |
|---|---|
| **MODE_ANIM_SCRIPT** = 0 | Поза вычисляется скриптом анимации (скомпилированным графом анимации). |
| **MODE_ANIM_LAYERS** = 1 | Поза вычисляется вручную с использованием слоёв анимации. |

### Методы класса

## Ptr <ConstSkeleton> getSkeleton () const

Возвращает текущий скелет, назначенный этому узлу.
### Возвращаемое значение

Текущий скелет, назначенный этому узлу.
## void setSkeletonPath ( const char * path )

Задаёт новый путь к файлу ассета скелета.
### Аргументы

- *const char ** **path** - Путь к файлу ассета скелета.

## const char * getSkeletonPath () const

Возвращает текущий путь к файлу ассета скелета.
### Возвращаемое значение

Текущий путь к файлу ассета скелета.
## void setMode ( NodeSkeletonPose::MODE mode )

Задаёт новый режим работы этого узла.
### Аргументы

- *[NodeSkeletonPose::MODE](../../../api/library/nodes/class.nodeskeletonpose_cpp.md#MODE)* **mode** - Режим работы этого узла.

## NodeSkeletonPose::MODE getMode () const

Возвращает текущий режим работы этого узла.
### Возвращаемое значение

Текущий режим работы этого узла.
## void setControlType ( NodeSkeletonPose::CONTROL_TYPE type )

Задаёт новый тип управления, определяющий, как узел находит свои управляемые объекты.
### Аргументы

- *[NodeSkeletonPose::CONTROL_TYPE](../../../api/library/nodes/class.nodeskeletonpose_cpp.md#CONTROL_TYPE)* **type** - Тип управления, определяющий, как узел находит свои управляемые объекты.

## NodeSkeletonPose::CONTROL_TYPE getControlType () const

Возвращает текущий тип управления, определяющий, как узел находит свои управляемые объекты.
### Возвращаемое значение

Текущий тип управления, определяющий, как узел находит свои управляемые объекты.
## int getNumControlledObjects () const

Возвращает текущее количество управляемых объектов ObjectMeshSkinned.
### Возвращаемое значение

Текущее количество управляемых объектов ObjectMeshSkinned.
## void setAnimScriptFileGUID ( const UGUID & guid )

Задаёт новый GUID файла ассета AnimGraph (`.agraph`), используемого в режиме MODE_ANIM_SCRIPT.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - GUID файла ассета AnimGraph (`.agraph`).

## const UGUID & getAnimScriptFileGUID () const

Возвращает текущий GUID файла ассета AnimGraph (`.agraph`), используемого в режиме MODE_ANIM_SCRIPT.
### Возвращаемое значение

Текущий GUID файла ассета AnimGraph (`.agraph`).
## void setAnimScriptPath ( const char * path )

Задаёт новый путь к файлу ассета AnimGraph (`.agraph`), используемому в режиме MODE_ANIM_SCRIPT.
### Аргументы

- *const char ** **path** - Путь к файлу ассета AnimGraph (`.agraph`).

## const char * getAnimScriptPath () const

Возвращает текущий путь к файлу ассета AnimGraph (`.agraph`), используемому в режиме MODE_ANIM_SCRIPT.
### Возвращаемое значение

Текущий путь к файлу ассета AnimGraph (`.agraph`).
## void setAnimPath ( const char * path )

Задаёт новый путь к файлу анимации по умолчанию, используемому в режиме MODE_ANIM_LAYERS.
### Аргументы

- *const char ** **path** - Путь к файлу анимации по умолчанию.

## const char * getAnimPath () const

Возвращает текущий путь к файлу анимации по умолчанию, используемому в режиме MODE_ANIM_LAYERS.
### Возвращаемое значение

Текущий путь к файлу анимации по умолчанию.
## bool isPlaying () const

Возвращает текущее значение, указывающее, воспроизводится ли анимация в данный момент.
### Возвращаемое значение

**true**, если анимация воспроизводится в данный момент; иначе **false**.
## void setNumLayers ( int layers )

Задаёт новое количество слоёв анимации.
### Аргументы

- *int* **layers** - Количество слоёв анимации.

## int getNumLayers () const

Возвращает текущее количество слоёв анимации.
### Возвращаемое значение

Текущее количество слоёв анимации.
---

## static NodeSkeletonPosePtr create ( )

Конструктор NodeSkeletonPose.
## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [Node](../../../api/library/nodes/class.node_cpp.md).
## void setSkeletonFileGUID ( const UGUID & guid )

Задаёт ассет скелета по GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - GUID файла ассета скелета.

## void addControlledObject ( const Ptr < ObjectMeshSkinned > & controlled_object )

Добавляет [ObjectMeshSkinned](../../../api/library/objects/class.objectmeshskinned_cpp.md) в список объектов, управляемых этим узлом. Используется только в режиме [CONTROL_TYPE_LIST](#CONTROL_TYPE_LIST).
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[ObjectMeshSkinned](../../../api/library/objects/class.objectmeshskinned_cpp.md)> &* **controlled_object** - ObjectMeshSkinned, управляемый этим узлом.

## void removeControlledObject ( int index )

Удаляет управляемый объект с указанным индексом из списка.
### Аргументы

- *int* **index** - Индекс удаляемого управляемого объекта.

## int findControlledObject ( const Ptr < ObjectMeshSkinned > & controlled_object ) const

Ищет указанный объект в списке управляемых объектов и возвращает его индекс.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[ObjectMeshSkinned](../../../api/library/objects/class.objectmeshskinned_cpp.md)> &* **controlled_object** - Искомый ObjectMeshSkinned.

### Возвращаемое значение

Индекс управляемого объекта, или -1, если не найден.
## void setControlledObject ( int index , const Ptr < ObjectMeshSkinned > & controlled_object )

Заменяет управляемый объект с указанным индексом.
### Аргументы

- *int* **index** - Индекс заменяемого управляемого объекта.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[ObjectMeshSkinned](../../../api/library/objects/class.objectmeshskinned_cpp.md)> &* **controlled_object** - Новый ObjectMeshSkinned, задаваемый по указанному индексу.

## Ptr < ObjectMeshSkinned > getControlledObject ( int index ) const

Возвращает управляемый объект с указанным индексом.
### Аргументы

- *int* **index** - Индекс управляемого объекта.

### Возвращаемое значение

Управляемый ObjectMeshSkinned с указанным индексом.
## void play ( )

Запускает или возобновляет воспроизведение анимации.
## void pause ( )

Приостанавливает воспроизведение анимации. Текущая позиция воспроизведения сохраняется, чтобы можно было возобновить воспроизведение с этой же точки.
## void updatePose ( float ifps )

Вручную обновляет скелетную позу и передаёт результат всем управляемым объектам. Используйте это, когда требуется принудительно обновить позу вне обычного цикла обновления.
### Аргументы

- *float* **ifps** - Длительность кадра (обратная величина FPS), в секундах.

## void getPose ( const Ptr < SkeletonPoseDecomposed > & out_pose ) const

Записывает текущую вычисленную скелетную позу этого узла в заданный [SkeletonPoseDecomposed](../../../api/library/animations/skeletal/class.skeletonposedecomposed_cpp.md).
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SkeletonPoseDecomposed](../../../api/library/animations/skeletal/class.skeletonposedecomposed_cpp.md)> &* **out_pose** - Выходная поза, получающая текущую скелетную позу.

## int addLayer ( )

Добавляет новый слой анимации. Слои используются в режиме [MODE_ANIM_LAYERS](#MODE_ANIM_LAYERS) для смешивания нескольких анимаций вместе.
### Возвращаемое значение

Индекс вновь добавленного слоя анимации.
## void removeLayer ( int layer )

Удаляет слой анимации с указанным индексом.
### Аргументы

- *int* **layer** - Индекс слоя анимации.

## void setLayer ( int layer , bool enable , float weight )

Задаёт состояние включения и вес смешивания для указанного слоя анимации за один вызов.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *bool* **enable** - true, чтобы включить слой, false, чтобы отключить.
- *float* **weight** - Вес смешивания для слоя.

## void setLayerEnabled ( int layer , bool enable )

Включает или отключает указанный слой анимации.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *bool* **enable** - true, чтобы включить слой, false, чтобы отключить.

## bool isLayerEnabled ( int layer ) const

Возвращает значение, указывающее, включён ли указанный слой анимации.
### Аргументы

- *int* **layer** - Индекс слоя анимации.

### Возвращаемое значение

true, если слой включён; иначе false.
## void setLayerWeight ( int layer , float weight )

Задаёт вес смешивания для указанного слоя анимации.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *float* **weight** - Вес смешивания для слоя.

## float getLayerWeight ( int layer ) const

Возвращает вес смешивания указанного слоя анимации.
### Аргументы

- *int* **layer** - Индекс слоя анимации.

### Возвращаемое значение

Вес смешивания слоя.
## void clearLayer ( int layer )

Очищает все трансформации суставов в указанном слое анимации, сбрасывая их к единичным.
### Аргументы

- *int* **layer** - Индекс слоя анимации.

## void importLayer ( int layer )

Импортирует данные текущего кадра анимации в указанный слой.
### Аргументы

- *int* **layer** - Индекс слоя анимации.

## void copyLayer ( int dest , int src )

Копирует все трансформации суставов из исходного слоя в целевой слой.
### Аргументы

- *int* **dest** - Индекс целевого слоя.
- *int* **src** - Индекс исходного слоя.

## void inverseLayer ( int dest , int src )

Копирует обратные трансформации суставов из исходного слоя в целевой слой.
### Аргументы

- *int* **dest** - Индекс целевого слоя.
- *int* **src** - Индекс исходного слоя.

## void lerpLayer ( int dest , int layer0 , int layer1 , float weight )

Копирует интерполированные трансформации суставов из двух исходных слоёв в целевой слой.
### Аргументы

- *int* **dest** - Индекс целевого слоя.
- *int* **layer0** - Индекс первого исходного слоя.
- *int* **layer1** - Индекс второго исходного слоя.
- *float* **weight** - Вес интерполяции. При 0 результат равен layer0; при 1 результат равен layer1.

## void lerpLayerByMask ( int dest , int layer0 , int layer1 , int mask_index , float weight )

Копирует интерполированные трансформации суставов из двух исходных слоёв в целевой слой, используя указанную маску суставов (по индексу) для управления весами смешивания по каждому суставу.
### Аргументы

- *int* **dest** - Индекс целевого слоя.
- *int* **layer0** - Индекс первого исходного слоя.
- *int* **layer1** - Индекс второго исходного слоя.
- *int* **mask_index** - Индекс маски суставов для весов смешивания по каждому суставу.
- *float* **weight** - Вес интерполяции.

## void lerpLayerByMask ( int dest , int layer0 , int layer1 , const char * mask_name , float weight )

Копирует интерполированные трансформации суставов из двух исходных слоёв в целевой слой, используя указанную маску суставов (по имени) для управления весами смешивания по каждому суставу.
### Аргументы

- *int* **dest** - Индекс целевого слоя.
- *int* **layer0** - Индекс первого исходного слоя.
- *int* **layer1** - Индекс второго исходного слоя.
- *const char ** **mask_name** - Имя маски суставов для весов смешивания по каждому суставу.
- *float* **weight** - Вес интерполяции.

## void mulLayer ( int dest , int layer0 , int layer1 , float weight = 1.0f )

Копирует перемноженные трансформации суставов из двух исходных слоёв в целевой слой.
### Аргументы

- *int* **dest** - Индекс целевого слоя.
- *int* **layer0** - Индекс первого исходного слоя.
- *int* **layer1** - Индекс второго исходного слоя.
- *float* **weight** - Вес интерполяции.

## int getLayerNumFrames ( int layer ) const

Возвращает количество кадров анимации для указанного слоя.
### Аргументы

- *int* **layer** - Индекс слоя анимации.

### Возвращаемое значение

Количество кадров анимации в слое.
## float setLayerFrame ( int layer , float frame , int from = -1 , int to = -1 )

Задаёт текущий кадр анимации для указанного слоя в пределах заданного диапазона кадров.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *float* **frame** - Номер кадра в интервале "from-to". Значения с плавающей точкой вызывают интерполяцию между соседними кадрами.
- *int* **from** - Начальный кадр. -1 означает первый кадр анимации.
- *int* **to** - Конечный кадр. -1 означает последний кадр анимации.

### Возвращаемое значение

Результирующий номер кадра после ограничения/зацикливания.
## float getLayerFrame ( int layer ) const

Возвращает текущий кадр анимации для указанного слоя.
### Аргументы

- *int* **layer** - Индекс слоя анимации.

### Возвращаемое значение

Номер текущего кадра.
## int getLayerFrameFrom ( int layer ) const

Возвращает начальный кадр, переданный в аргументе from при последнем вызове [setLayerFrame()](#setLayerFrame_int_float_int_int_float).
### Аргументы

- *int* **layer** - Индекс слоя анимации.

### Возвращаемое значение

Начальный кадр.
## int getLayerFrameTo ( int layer ) const

Возвращает конечный кадр, переданный в аргументе to при последнем вызове [setLayerFrame()](#setLayerFrame_int_float_int_int_float).
### Аргументы

- *int* **layer** - Индекс слоя анимации.

### Возвращаемое значение

Конечный кадр.
## float getLayerDuration ( int layer ) const

Возвращает длительность анимации, назначенной указанному слою, в секундах.
### Аргументы

- *int* **layer** - Индекс слоя анимации.

### Возвращаемое значение

Длительность в секундах.
## void setLayerTime ( int layer , float time )

Задаёт текущее время воспроизведения для указанного слоя анимации, в секундах.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *float* **time** - Время воспроизведения, в секундах.

## float getLayerTime ( int layer ) const

Возвращает текущее время воспроизведения для указанного слоя анимации, в секундах.
### Аргументы

- *int* **layer** - Индекс слоя анимации.

### Возвращаемое значение

Текущее время воспроизведения, в секундах.
## void setLayerJointTransform ( int layer , int joint , const Math:: mat4 & transform )

Задаёт матрицу трансформации для указанного сустава в заданном слое анимации.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *int* **joint** - Индекс сустава.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации сустава.

## Math:: mat4 getLayerJointTransform ( int layer , int joint ) const

Возвращает матрицу трансформации указанного сустава в заданном слое анимации.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *int* **joint** - Индекс сустава.

### Возвращаемое значение

Матрица трансформации сустава.
## void setLayerJointPosition ( int layer , int joint , const Math:: vec3 & position )

Задаёт позицию для указанного сустава в заданном слое анимации.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *int* **joint** - Индекс сустава.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **position** - Позиция сустава.

## Math:: vec3 getLayerJointPosition ( int layer , int joint ) const

Возвращает позицию указанного сустава в заданном слое анимации.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *int* **joint** - Индекс сустава.

### Возвращаемое значение

Позиция сустава.
## void setLayerJointRotation ( int layer , int joint , const Math:: quat & rotation )

Задаёт вращение для указанного сустава в заданном слое анимации.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *int* **joint** - Индекс сустава.
- *const  Math::[quat](../../../api/library/math/class.quat_cpp.md) &* **rotation** - Кватернион вращения сустава.

## Math:: quat getLayerJointRotation ( int layer , int joint ) const

Возвращает вращение указанного сустава в заданном слое анимации.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *int* **joint** - Индекс сустава.

### Возвращаемое значение

Кватернион вращения сустава.
## void setLayerJointScale ( int layer , int joint , const Math:: vec3 & scale )

Задаёт масштаб для указанного сустава в заданном слое анимации.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *int* **joint** - Индекс сустава.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **scale** - Масштаб сустава.

## Math:: vec3 getLayerJointScale ( int layer , int joint ) const

Возвращает масштаб указанного сустава в заданном слое анимации.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *int* **joint** - Индекс сустава.

### Возвращаемое значение

Масштаб сустава.
## void setLayerFrameUsesEnabled ( int layer , bool enabled )

Включает или отключает маскирование компонентов кадра по каждому суставу для указанного слоя. Когда включено, можно управлять тем, какие компоненты трансформации (позиция, вращение, масштаб) используются для каждого сустава через [setLayerJointFrameUses()](#setLayerJointFrameUses_int_int_int_void).
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *bool* **enabled** - true, чтобы включить маскирование компонентов кадра по каждому суставу, false, чтобы отключить.

## bool isLayerFrameUsesEnabled ( int layer ) const

Возвращает значение, указывающее, включено ли маскирование компонентов кадра по каждому суставу для указанного слоя.
### Аргументы

- *int* **layer** - Индекс слоя анимации.

### Возвращаемое значение

true, если маскирование компонентов кадра по каждому суставу включено; иначе false.
## void setLayerJointFrameUses ( int layer , int joint , int uses )

Задаёт, какие компоненты трансформации (позиция, вращение, масштаб) кадра анимации применяются к указанному суставу в заданном слое.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *int* **joint** - Индекс сустава.
- *int* **uses** - Битовая маска используемых компонентов кадра (комбинация флагов ANIM_FRAME_USES_*).

## int getLayerJointFrameUses ( int layer , int joint ) const

Возвращает битовую маску, указывающую, какие компоненты трансформации кадра анимации применяются к указанному суставу в заданном слое.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *int* **joint** - Индекс сустава.

### Возвращаемое значение

Битовая маска используемых компонентов кадра.
## void setLayerPose ( int layer , const Ptr <ConstSkeletonPoseDecomposed> & pose )

Задаёт все трансформации суставов в указанном слое анимации из заданного [SkeletonPoseDecomposed](../../../api/library/animations/skeletal/class.skeletonposedecomposed_cpp.md).
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<ConstSkeletonPoseDecomposed> &* **pose** - Поза для применения к слою.

## void getLayerPose ( int layer , const Ptr < SkeletonPoseDecomposed > & out_pose ) const

Записывает трансформации суставов указанного слоя анимации в заданный [SkeletonPoseDecomposed](../../../api/library/animations/skeletal/class.skeletonposedecomposed_cpp.md).
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SkeletonPoseDecomposed](../../../api/library/animations/skeletal/class.skeletonposedecomposed_cpp.md)> &* **out_pose** - Выходная поза для получения трансформаций суставов слоя.

## void resetLayerToBindPose ( int layer )

Сбрасывает все трансформации суставов в указанном слое к базовой (rest) позе скелета.
### Аргументы

- *int* **layer** - Индекс слоя анимации.

## void renderLayerJoints ( int layer , const Math:: Mat4 & world_offset , float basis_length = 0.03f , bool depth_test = false ) const

Отображает отладочную визуализацию позиций и ориентаций суставов (осей координатного базиса) для указанного слоя анимации.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **world_offset** - Смещение трансформации в мировом пространстве, применяемое к визуализируемым суставам.
- *float* **basis_length** - Длина осей координатного базиса, отображаемых в каждой позиции сустава.
- *bool* **depth_test** - true, чтобы включить проверку глубины для отладочной визуализации; false, чтобы отображать поверх всего.

## void renderLayerJointNames ( int layer , const Math:: Mat4 & world_offset , const Math:: vec4 & color , int outline = 0 , int font_size = -1 ) const

Отображает отладочную визуализацию имён суставов в виде текстовых меток для указанного слоя анимации.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **world_offset** - Смещение трансформации в мировом пространстве, применяемое к визуализируемым именам.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет текста (RGBA).
- *int* **outline** - Флаг обводки текста. 0 - без обводки, 1 - с обводкой.
- *int* **font_size** - Размер шрифта в пикселях. -1 использует размер по умолчанию.

## void renderLayerBones ( int layer , const Math:: Mat4 & world_offset , const Math:: vec4 & color , float radius = 0.01f , bool depth_test = false ) const

Отображает отладочную визуализацию соединений костей (линий между родительскими и дочерними суставами) для указанного слоя анимации.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **world_offset** - Смещение трансформации в мировом пространстве, применяемое к визуализируемым костям.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет кости (RGBA).
- *float* **radius** - Радиус форм костей.
- *bool* **depth_test** - true, чтобы включить проверку глубины для отладочной визуализации; false, чтобы отображать поверх всего.

## long long getAnimationResourceID ( const char * anim_path ) const

Возвращает уникальный ID ресурса анимации для указанного пути. Этот метод также загружает анимацию, если она ещё не была загружена.
### Аргументы

- *const char ** **anim_path** - Путь к файлу анимации или его GUID.

### Возвращаемое значение

Уникальный ID ресурса анимации.
## void setLayerAnimationFilePath ( int layer , const char * path )

Задаёт файл анимации для указанного слоя по пути.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *const char ** **path** - Путь к файлу анимации или его GUID.

## const char * getLayerAnimationFilePath ( int layer ) const

Возвращает путь к файлу анимации, назначенному указанному слою.
### Аргументы

- *int* **layer** - Индекс слоя анимации.

### Возвращаемое значение

Путь к файлу анимации, назначенному слою.
## void setLayerAnimationFileGUID ( int layer , const UGUID & guid )

Задаёт файл анимации для указанного слоя по GUID.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - GUID файла анимации.

## UGUID getLayerAnimationFileGUID ( int layer ) const

Возвращает GUID файла анимации, назначенного указанному слою.
### Аргументы

- *int* **layer** - Индекс слоя анимации.

### Возвращаемое значение

GUID файла анимации, назначенного слою.
## void setLayerAnimationResourceID ( int layer , long long resource_id )

Задаёт анимацию для указанного слоя по ID ресурса. Используйте [getAnimationResourceID()](#getAnimationResourceID_cstr_llong), чтобы получить ID из пути к файлу.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *long long* **resource_id** - ID ресурса анимации, полученный через [getAnimationResourceID()](#getAnimationResourceID_cstr_llong).

## long long getLayerAnimationResourceID ( int layer ) const

Возвращает ID ресурса анимации, назначенного указанному слою.
### Аргументы

- *int* **layer** - Индекс слоя анимации.

### Возвращаемое значение

ID ресурса анимации, назначенного слою.
## bool isLayerAnimationRootMotionPresent ( int layer ) const

Возвращает значение, указывающее, содержит ли анимация, назначенная указанному слою, данные root motion.
### Аргументы

- *int* **layer** - Индекс слоя анимации.

### Возвращаемое значение

true, если анимация содержит данные root motion; иначе false.
## Math::Transform extractLayerRootMotionByFrames ( int layer , float begin_frame , float end_frame , bool is_forward ) const

Извлекает трансформацию root motion, накопленную между двумя кадрами для указанного слоя.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *float* **begin_frame** - Начальный кадр.
- *float* **end_frame** - Конечный кадр.
- *bool* **is_forward** - true для прямого направления воспроизведения; false для обратного.

### Возвращаемое значение

Трансформация root motion, накопленная между указанными кадрами.
## Math::Transform extractLayerRootMotionByTimes ( int layer , float begin_time , float end_time , bool is_forward ) const

Извлекает трансформацию root motion, накопленную между двумя моментами времени в секундах для указанного слоя.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *float* **begin_time** - Начальное время, в секундах.
- *float* **end_time** - Конечное время, в секундах.
- *bool* **is_forward** - true для прямого направления воспроизведения; false для обратного.

### Возвращаемое значение

Трансформация root motion, накопленная между указанными моментами времени.
## void removeLayerRootMotion ( int layer )

Удаляет данные root motion из анимации, назначенной указанному слою.
### Аргументы

- *int* **layer** - Индекс слоя анимации.

## int getLayerNumMarkerSyncs ( int layer ) const

Возвращает количество sync-маркеров в анимации, назначенной указанному слою.
### Аргументы

- *int* **layer** - Индекс слоя анимации.

### Возвращаемое значение

Количество sync-маркеров в анимации слоя.
## const char * getLayerMarkerSyncName ( int layer , int index ) const

Возвращает имя sync-маркера с указанным индексом в анимации слоя.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *int* **index** - Индекс sync-маркера.

### Возвращаемое значение

Имя sync-маркера.
## unsigned int getLayerMarkerSyncNameHash ( int layer , int index ) const

Возвращает хэш имени sync-маркера с указанным индексом в анимации слоя.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *int* **index** - Индекс sync-маркера.

### Возвращаемое значение

Хэш имени sync-маркера.
## float getLayerMarkerSyncTime ( int layer , int index ) const

Возвращает позицию по времени sync-маркера с указанным индексом в анимации слоя.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *int* **index** - Индекс sync-маркера.

### Возвращаемое значение

Позиция по времени sync-маркера.
## bool getLayerMarkerSyncInterval ( int layer , float current_time , bool is_loop , unsigned int & prev_hash , unsigned int & next_hash , float & ratio , const Vector <unsigned int> & common_hashes ) const

Находит интервал sync-маркеров вокруг указанного времени в анимации слоя, учитывая только маркеры, хэши имён которых входят в общий набор.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *float* **current_time** - Текущее время воспроизведения.
- *bool* **is_loop** - true, чтобы включить зацикливание; false для ограничения.
- *unsigned int &* **prev_hash** - Выход: хэш имени предыдущего sync-маркера.
- *unsigned int &* **next_hash** - Выход: хэш имени следующего sync-маркера.
- *float &* **ratio** - Выход: коэффициент интерполяции между предыдущим и следующим маркерами.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<unsigned int> &* **common_hashes** - Набор хэшей имён маркеров для учёта при поиске интервала.

### Возвращаемое значение

true, если допустимый sync-интервал найден; иначе false.
## float getLayerTimeFromMarkerSyncInterval ( int layer , unsigned int prev_hash , unsigned int next_hash , float ratio , float current_time , bool is_loop , const Vector <unsigned int> & common_hashes ) const

Вычисляет позицию по времени в анимации слоя, которая соответствует sync-интервалу из другой анимации. Используется для синхронизации воспроизведения между слоями.
### Аргументы

- *int* **layer** - Индекс слоя анимации.
- *unsigned int* **prev_hash** - Хэш имени предыдущего sync-маркера.
- *unsigned int* **next_hash** - Хэш имени следующего sync-маркера.
- *float* **ratio** - Коэффициент интерполяции между предыдущим и следующим маркерами.
- *float* **current_time** - Текущее время воспроизведения, используется для разрешения неоднозначности при совпадении нескольких интервалов.
- *bool* **is_loop** - true, чтобы включить зацикливание; false для ограничения.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<unsigned int> &* **common_hashes** - Набор хэшей имён маркеров для учёта.

### Возвращаемое значение

Позиция по времени, соответствующая указанному sync-интервалу.
## void setJointTransform ( int joint , const Math:: mat4 & transform )

Задаёт полную матрицу трансформации для указанного сустава в текущей позе.
### Аргументы

- *int* **joint** - Индекс сустава.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации сустава.

## Math:: mat4 getJointTransform ( int joint ) const

Возвращает полную матрицу трансформации указанного сустава в текущей позе.
### Аргументы

- *int* **joint** - Индекс сустава.

### Возвращаемое значение

Матрица трансформации сустава.
## void setJointPosition ( int joint , const Math:: vec3 & position )

Задаёт позицию указанного сустава в текущей позе.
### Аргументы

- *int* **joint** - Индекс сустава.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **position** - Позиция сустава.

## Math:: vec3 getJointPosition ( int joint ) const

Возвращает позицию указанного сустава в текущей позе.
### Аргументы

- *int* **joint** - Индекс сустава.

### Возвращаемое значение

Позиция сустава.
## void setJointRotation ( int joint , const Math:: quat & rotation )

Задаёт вращение указанного сустава в текущей позе.
### Аргументы

- *int* **joint** - Индекс сустава.
- *const  Math::[quat](../../../api/library/math/class.quat_cpp.md) &* **rotation** - Вращение сустава.

## Math:: quat getJointRotation ( int joint ) const

Возвращает вращение указанного сустава в текущей позе.
### Аргументы

- *int* **joint** - Индекс сустава.

### Возвращаемое значение

Вращение сустава.
## void setJointScale ( int joint , const Math:: vec3 & scale )

Задаёт масштаб указанного сустава в текущей позе.
### Аргументы

- *int* **joint** - Индекс сустава.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **scale** - Масштаб сустава.

## Math:: vec3 getJointScale ( int joint ) const

Возвращает масштаб указанного сустава в текущей позе.
### Аргументы

- *int* **joint** - Индекс сустава.

### Возвращаемое значение

Масштаб сустава.
## void forceApplyPose ( )

Немедленно применяет текущую позу ко всем управляемым скиннированным мешам, минуя обычный цикл обновления. Используйте это, когда требуется, чтобы визуальный результат сразу отражал изменения позы (например, после ручной установки трансформаций суставов).
## Ptr < AnimScript > getAnimScript ( ) const

Возвращает экземпляр [AnimScript](../../../api/library/animations/skeletal/class.animscript_cpp.md), используемый этим узлом в режиме [MODE_ANIM_SCRIPT](#MODE_ANIM_SCRIPT).
### Возвращаемое значение

Экземпляр AnimScript, или null, если узел не в режиме MODE_ANIM_SCRIPT или AnimGraph не назначен этому узлу.
