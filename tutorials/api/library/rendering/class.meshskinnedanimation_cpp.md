# MeshSkinnedAnimation Class (CPP)

**Header:** #include <UnigineMesh.h>


Этот класс представляет данные скелетной анимации - последовательность ключевых кадров, хранящих трансформации суставов, которые могут быть применены к скелету. Он заменяет устаревший класс *MeshAnimation*.


Данные анимации состоят из:


- Source joints - полная иерархия суставов (имена и отношения родитель-потомок), хранящаяся в файле анимации.
- Animated joints - подмножество source joints, имеющих ключевые кадры анимации.
- Frames (кадры) - данные ключевых кадров, хранящие трансформации суставов в локальном пространстве для каждого кадра анимации.
- Sync markers (маркеры синхронизации) - именованные временные позиции внутри анимации, используемые для синхронизации воспроизведения между разными анимациями (например, для совмещения касаний ног земли между циклами ходьбы и бега). Каждый маркер имеет имя, значение времени и опциональный целочисленный ID.


Используйте [getPoseByFrame()](#getPoseByFrame_SkeletonPoseDecomposed_float_int_int) / [getPoseByTime()](#getPoseByTime_SkeletonPoseDecomposed_float_int_int) / [getPoseByNormalizedTime()](#getPoseByNormalizedTime_SkeletonPoseDecomposed_float_int_int) для извлечения полной позы в заданное время, или варианты updatePose*() для обновления только animated joints существующей позы. Используйте [getMarkerSyncInterval()](#getMarkerSyncInterval_float_int_uint_uint_float_VECuint_int) и [getTimeFromMarkerSyncInterval()](#getTimeFromMarkerSyncInterval_uint_uint_float_float_int_VECuint_float) для синхронизации позиций воспроизведения между анимациями, имеющими общие sync markers.


## MeshSkinnedAnimation Class

### Методы класса

## getSharedSkeleton () const

Возвращает текущий экземпляр скелета, связанный с этой анимацией, загруженный из общего пути или GUID скелета.
### Возвращаемое значение

Текущий экземпляр общего скелета.
## void setSharedSkeletonFileGUID ( )

Задаёт новый GUID файла скелета, связанного с этой анимацией.
### Аргументы

- **guid** - GUID файла общего скелета.

## getSharedSkeletonFileGUID () const

Возвращает текущий GUID файла скелета, связанного с этой анимацией.
### Возвращаемое значение

Текущий GUID файла общего скелета.
## void setSharedSkeletonPath ( )

Задаёт новый путь к файлу скелета, связанного с этой анимацией.
### Аргументы

- **path** - Путь к файлу общего скелета.

## const char * getSharedSkeletonPath () const

Возвращает текущий путь к файлу скелета, связанного с этой анимацией.
### Возвращаемое значение

Текущий путь к файлу общего скелета.
## getMemoryUsage () const

Возвращает текущий общий объём памяти, используемой этой анимацией, в байтах.
### Возвращаемое значение

Текущее использование памяти в байтах.
## getNumSrcJoints () const

Возвращает текущее общее количество source joints, хранящихся в этой анимации.
### Возвращаемое значение

Текущее количество source joints.
## getNumAnimatedJoints () const

Возвращает текущее количество animated joints - подмножества source joints, имеющих ключевые кадры анимации.
### Возвращаемое значение

Текущее количество animated joints.
## void setFps ( )

Задаёт новую частоту кадров (кадров в секунду) этой анимации.
### Аргументы

- **fps** - Частота кадров анимации.

## getFps () const

Возвращает текущую частоту кадров (кадров в секунду) этой анимации.
### Возвращаемое значение

Текущая частота кадров анимации.
## getDuration () const

Возвращает текущую длительность этой анимации в секундах, вычисленную из количества кадров и FPS.
### Возвращаемое значение

Текущая длительность анимации в секундах.
## void setRootMotionPresent ( )

Задаёт новое значение, указывающее, присутствуют ли в этой анимации данные root motion.
### Аргументы

- **present** - Признак наличия данных root motion в этой анимации.

## isRootMotionPresent () const

Возвращает текущее значение, указывающее, присутствуют ли в этой анимации данные root motion.
### Возвращаемое значение

Текущий признак наличия данных root motion в этой анимации.
## void setNumFrames ( )

Задаёт новое количество кадров анимации (ключевых кадров).
### Аргументы

- **frames** - Количество кадров анимации.

## getNumFrames () const

Возвращает текущее количество кадров анимации (ключевых кадров).
### Возвращаемое значение

Текущее количество кадров анимации.
## getNumMarkerSyncs () const

Возвращает текущее количество sync markers в этой анимации.
### Возвращаемое значение

Текущее количество sync markers.
---

## static MeshSkinnedAnimationPtr create ( )

Создаёт пустую skinned-анимацию.
## static MeshSkinnedAnimationPtr create ( const Ptr <ConstMeshSkinnedAnimation> & src )

Создаёт skinned-анимацию путём копирования данных из заданной исходной анимации.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<ConstMeshSkinnedAnimation> &* **src** - Экземпляр исходной анимации, из которого копируются данные.

## static MeshSkinnedAnimationPtr create ( const char * path )

Создаёт skinned-анимацию и загружает данные из заданного файла.
### Аргументы

- *const char ** **path** - Путь к файлу анимации.

## void initSourceSkeleton ( const Ptr <ConstSkeleton> & skeleton )

Инициализирует иерархию source joints из заданного экземпляра скелета. Это настраивает имена суставов и отношения родитель-потомок, используемые этой анимацией.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<ConstSkeleton> &* **skeleton** - Экземпляр скелета, из которого инициализируются source joints.

## void initSourceSkeleton ( const char * path )

Инициализирует иерархию source joints из скелета, загруженного из заданного пути к файлу.
### Аргументы

- *const char ** **path** - Путь к файлу скелета.

## void assignFrom ( const Ptr < MeshSkinnedAnimation > & src )

Копирует все данные анимации из источника: source joints, animated joints и кадры анимации.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[MeshSkinnedAnimation](../../../api/library/rendering/class.meshskinnedanimation_cpp.md)> &* **src** - Экземпляр исходной анимации.

## void clear ( )

Очищает все данные анимации: source joints, animated joints и кадры анимации.
## void flipYZ ( )

Меняет местами оси Y и Z для анимации:
- Ось Y становится равной -Z
- Ось Z становится равной Y


## int info ( const char * path ) const

Считывает метаданные (иерархию суставов, количество кадров и т.д.) из заданного файла анимации без загрузки полных данных кадров.
### Аргументы

- *const char ** **path** - Путь к файлу анимации.

### Возвращаемое значение

1, если метаданные файла успешно считаны; иначе 0.
## int load ( const char * path )

Загружает полные данные анимации (иерархию суставов и все кадры) из заданного файла.
### Аргументы

- *const char ** **path** - Путь к файлу анимации.

### Возвращаемое значение

1, если анимация успешно загружена; иначе 0.
## int loadJoints ( const char * path )

Загружает только иерархию суставов (имена и индексы родителей) из заданного файла анимации, без загрузки данных кадров.
### Аргументы

- *const char ** **path** - Путь к файлу анимации.

### Возвращаемое значение

1, если данные суставов успешно загружены; иначе 0.
## int save ( const char * path ) const

Сохраняет данные анимации в заданный файл. Создаёт файл и все необходимые подкаталоги, если они не существуют.
### Аргументы

- *const char ** **path** - Путь к выходному файлу, включая имя файла и расширение.

### Возвращаемое значение

1, если анимация успешно сохранена; иначе 0.
## int findSrcJoint ( const char * name ) const

Ищет source joint с заданным именем и возвращает его индекс.
### Аргументы

- *const char ** **name** - Искомое имя сустава.

### Возвращаемое значение

Индекс source joint, или -1, если не найден.
## const char * getSrcJointName ( int bone ) const

Возвращает имя source joint по заданному индексу.
### Аргументы

- *int* **bone** - Индекс source joint.

### Возвращаемое значение

Имя сустава.
## int getSrcJointParent ( int bone ) const

Возвращает индекс родительского сустава для заданного source joint.
### Аргументы

- *int* **bone** - Индекс source joint.

### Возвращаемое значение

Индекс родительского сустава, или -1, если у сустава нет родителя.
## void setAnimatedJointID ( int index , int src_joint_id )

Задаёт индекс source joint для заданного animated joint.
### Аргументы

- *int* **index** - Индекс в списке animated joints.
- *int* **src_joint_id** - Назначаемый индекс source joint.

## int getAnimatedJointID ( int index ) const

Возвращает индекс source joint для заданного animated joint.
### Аргументы

- *int* **index** - Индекс в списке animated joints.

### Возвращаемое значение

Индекс source joint.
## void getAnimatedJoints ( Vector <int> & joints ) const

Возвращает индексы source joint для всех animated joints.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **joints** - Массив для получения индексов source joint всех animated joints.

## void setAnimatedJoints ( const Vector <int> & joints )

Задаёт список animated joints, используя заданные индексы source joint.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **joints** - Массив индексов source joint, задаваемых как animated.

## void addAnimatedJoint ( int src_joint )

Добавляет source joint в список animated joints.
### Аргументы

- *int* **src_joint** - Индекс source joint, добавляемого в список animated joints.

## void removeAnimatedJoint ( int index )

Удаляет animated joint по заданному индексу из списка.
### Аргументы

- *int* **index** - Индекс в списке animated joints.

## const char * getAnimatedJointName ( int index ) const

Возвращает имя animated joint по заданному индексу.
### Аргументы

- *int* **index** - Индекс в списке animated joints.

### Возвращаемое значение

Имя сустава.
## int findAnimatedJointByID ( int src_joint_id ) const

Ищет animated joint по индексу его source joint и возвращает его позицию в списке animated joints.
### Аргументы

- *int* **src_joint_id** - Искомый индекс source joint.

### Возвращаемое значение

Индекс в списке animated joints, или -1, если не найден.
## int findAnimatedJointByName ( const char * name ) const

Ищет animated joint по имени и возвращает его позицию в списке animated joints.
### Аргументы

- *const char ** **name** - Искомое имя сустава.

### Возвращаемое значение

Индекс в списке animated joints, или -1, если не найден.
## Math::Transform getFrameJointTransform ( int frame , int joint ) const

Возвращает трансформацию в локальном пространстве заданного animated joint в заданном кадре.
### Аргументы

- *int* **frame** - Номер кадра.
- *int* **joint** - Индекс в списке animated joints.

### Возвращаемое значение

Трансформация в локальном пространстве для заданного сустава в заданном кадре.
## void setFrame ( int frame , const Vector < Math:: mat4 > & joints )

Задаёт матрицы трансформации для всех animated joints в заданном кадре. Количество матриц должно совпадать с количеством animated joints.
### Аргументы

- *int* **frame** - Номер кадра.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[mat4](../../../api/library/math/class.mat4_cpp.md)> &* **joints** - Массив матриц трансформации в локальном пространстве для всех animated joints.

## void setFrame ( int frame , int index , const Math:: mat4 & joint )

Задаёт матрицу трансформации для одного animated joint в заданном кадре.
### Аргументы

- *int* **frame** - Номер кадра.
- *int* **index** - Индекс в списке animated joints.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **joint** - Матрица трансформации в локальном пространстве.

## void getFrame ( int frame , Vector < Math:: mat4 > & joints ) const

Возвращает матрицы трансформации для всех animated joints в заданном кадре.
### Аргументы

- *int* **frame** - Номер кадра.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[mat4](../../../api/library/math/class.mat4_cpp.md)> &* **joints** - Массив для получения матриц трансформации в локальном пространстве для всех animated joints.

## bool getPoseByFrame ( const Ptr < SkeletonPoseDecomposed > & out_pose , float frame , bool is_loop = false ) const

Извлекает полную декомпозированную позу в заданном кадре. Все суставы выходной позы задаются из данных анимации.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SkeletonPoseDecomposed](../../../api/library/animations/skeletal/class.skeletonposedecomposed_cpp.md)> &* **out_pose** - Выходная поза, получающая результат.
- *float* **frame** - Номер кадра (может быть дробным для интерполяции между кадрами).
- *bool* **is_loop** - true - включить зацикливание (значение кадра оборачивается); false - для ограничения (clamping).

### Возвращаемое значение

true, если поза успешно извлечена; иначе false.
## bool getPoseByTime ( const Ptr < SkeletonPoseDecomposed > & out_pose , float time , bool is_loop = false ) const

Извлекает полную декомпозированную позу в заданное время в секундах. Все суставы выходной позы задаются из данных анимации.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SkeletonPoseDecomposed](../../../api/library/animations/skeletal/class.skeletonposedecomposed_cpp.md)> &* **out_pose** - Выходная поза, получающая результат.
- *float* **time** - Время в секундах.
- *bool* **is_loop** - true - включить зацикливание; false - для ограничения (clamping).

### Возвращаемое значение

true, если поза успешно извлечена; иначе false.
## bool getPoseByNormalizedTime ( const Ptr < SkeletonPoseDecomposed > & out_pose , float normalized_time , bool is_loop = false ) const

Извлекает полную декомпозированную позу в заданное нормализованное время. Все суставы выходной позы задаются из данных анимации.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SkeletonPoseDecomposed](../../../api/library/animations/skeletal/class.skeletonposedecomposed_cpp.md)> &* **out_pose** - Выходная поза, получающая результат.
- *float* **normalized_time** - Нормализованное время в диапазоне [0.0, 1.0], где 0.0 - начало, а 1.0 - конец анимации.
- *bool* **is_loop** - true - включить зацикливание; false - для ограничения (clamping).

### Возвращаемое значение

true, если поза успешно извлечена; иначе false.
## bool updatePoseByFrame ( const Ptr < SkeletonPoseDecomposed > & out_pose , float frame , bool is_loop = false ) const

Обновляет только animated joints в существующей позе в заданном кадре, оставляя неанимированные суставы без изменений.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SkeletonPoseDecomposed](../../../api/library/animations/skeletal/class.skeletonposedecomposed_cpp.md)> &* **out_pose** - Обновляемая поза. Изменяются только animated joints.
- *float* **frame** - Номер кадра (может быть дробным для интерполяции между кадрами).
- *bool* **is_loop** - true - включить зацикливание; false - для ограничения (clamping).

### Возвращаемое значение

true, если поза успешно обновлена; иначе false.
## bool updatePoseByTime ( const Ptr < SkeletonPoseDecomposed > & out_pose , float time , bool is_loop = false ) const

Обновляет только animated joints в существующей позе в заданное время в секундах, оставляя неанимированные суставы без изменений.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SkeletonPoseDecomposed](../../../api/library/animations/skeletal/class.skeletonposedecomposed_cpp.md)> &* **out_pose** - Обновляемая поза. Изменяются только animated joints.
- *float* **time** - Время в секундах.
- *bool* **is_loop** - true - включить зацикливание; false - для ограничения (clamping).

### Возвращаемое значение

true, если поза успешно обновлена; иначе false.
## bool updatePoseByNormalizedTime ( const Ptr < SkeletonPoseDecomposed > & out_pose , float normalized_time , bool is_loop = false ) const

Обновляет только animated joints в существующей позе в заданное нормализованное время, оставляя неанимированные суставы без изменений.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SkeletonPoseDecomposed](../../../api/library/animations/skeletal/class.skeletonposedecomposed_cpp.md)> &* **out_pose** - Обновляемая поза. Изменяются только animated joints.
- *float* **normalized_time** - Нормализованное время в диапазоне [0.0, 1.0].
- *bool* **is_loop** - true - включить зацикливание; false - для ограничения (clamping).

### Возвращаемое значение

true, если поза успешно обновлена; иначе false.
## Math::Transform extractRootMotionByFrames ( float begin_frame , float end_frame , bool is_forward ) const

Извлекает трансформацию root motion, накопленную между двумя кадрами. Направление воспроизведения определяет, как обходится диапазон.
### Аргументы

- *float* **begin_frame** - Начальный кадр.
- *float* **end_frame** - Конечный кадр.
- *bool* **is_forward** - true - для прямого направления воспроизведения; false - для обратного.

### Возвращаемое значение

Трансформация root motion, накопленная между заданными кадрами.
## Math::Transform extractRootMotionByTimes ( float begin_time , float end_time , bool is_forward ) const

Извлекает трансформацию root motion, накопленную между двумя моментами времени в секундах. Направление воспроизведения определяет, как обходится диапазон.
### Аргументы

- *float* **begin_time** - Начальное время в секундах.
- *float* **end_time** - Конечное время в секундах.
- *bool* **is_forward** - true - для прямого направления воспроизведения; false - для обратного.

### Возвращаемое значение

Трансформация root motion, накопленная между заданными моментами времени.
## int addMarkerSync ( const char * name , float time )

Добавляет sync marker с заданным именем в заданной временной позиции.
### Аргументы

- *const char ** **name** - Имя sync marker.
- *float* **time** - Временная позиция маркера.

### Возвращаемое значение

Индекс добавленного sync marker.
## void removeMarkerSync ( int index )

Удаляет sync marker по заданному индексу.
### Аргументы

- *int* **index** - Индекс sync marker.

## void clearMarkerSyncs ( )

Удаляет все sync markers из этой анимации.
## const char * getMarkerSyncName ( int index ) const

Возвращает имя sync marker по заданному индексу.
### Аргументы

- *int* **index** - Индекс sync marker.

### Возвращаемое значение

Имя sync marker.
## unsigned int getMarkerSyncNameHash ( int index ) const

Возвращает хэш имени sync marker по заданному индексу.
### Аргументы

- *int* **index** - Индекс sync marker.

### Возвращаемое значение

Хэш имени sync marker.
## void setMarkerSyncName ( int index , const char * name )

Задаёт имя sync marker по заданному индексу.
### Аргументы

- *int* **index** - Индекс sync marker.
- *const char ** **name** - Новое имя sync marker.

## float getMarkerSyncTime ( int index ) const

Возвращает временную позицию sync marker по заданному индексу.
### Аргументы

- *int* **index** - Индекс sync marker.

### Возвращаемое значение

Временная позиция sync marker.
## void setMarkerSyncTime ( int index , float time )

Задаёт временную позицию sync marker по заданному индексу.
### Аргументы

- *int* **index** - Индекс sync marker.
- *float* **time** - Новая временная позиция.

## int getMarkerSyncId ( int index ) const

Возвращает ID sync marker по заданному индексу.
### Аргументы

- *int* **index** - Индекс sync marker.

### Возвращаемое значение

ID sync marker.
## void setMarkerSyncId ( int index , int id )

Задаёт ID sync marker по заданному индексу.
### Аргументы

- *int* **index** - Индекс sync marker.
- *int* **id** - Новый ID sync marker.

## int findMarkerSyncById ( int id ) const

Ищет sync marker с заданным ID и возвращает его индекс.
### Аргументы

- *int* **id** - Искомый ID sync marker.

### Возвращаемое значение

Индекс sync marker, или -1, если не найден.
## bool getMarkerSyncInterval ( float current_time , bool is_loop , unsigned int & prev_hash , unsigned int & next_hash , float & ratio , const Vector <unsigned int> & common_hashes ) const

Находит интервал sync marker вокруг заданного времени, учитывая только маркеры, хэши имён которых входят в общий набор. Возвращает окружающие хэши маркеров и коэффициент интерполяции между ними.
### Аргументы

- *float* **current_time** - Текущее время воспроизведения.
- *bool* **is_loop** - true - включить зацикливание; false - для ограничения (clamping).
- *unsigned int &* **prev_hash** - Выход: хэш имени предыдущего sync marker.
- *unsigned int &* **next_hash** - Выход: хэш имени следующего sync marker.
- *float &* **ratio** - Выход: коэффициент интерполяции между предыдущим и следующим маркерами.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<unsigned int> &* **common_hashes** - Набор хэшей имён маркеров, учитываемых при поиске интервала.

### Возвращаемое значение

true, если найден корректный интервал синхронизации; иначе false.
## float getTimeFromMarkerSyncInterval ( unsigned int prev_hash , unsigned int next_hash , float ratio , float current_time , bool is_loop , const Vector <unsigned int> & common_hashes ) const

Вычисляет временную позицию в этой анимации, соответствующую интервалу синхронизации из другой анимации. Используется для синхронизации воспроизведения между анимациями с совпадающими sync markers.
### Аргументы

- *unsigned int* **prev_hash** - Хэш имени предыдущего sync marker.
- *unsigned int* **next_hash** - Хэш имени следующего sync marker.
- *float* **ratio** - Коэффициент интерполяции между предыдущим и следующим маркерами.
- *float* **current_time** - Текущее время воспроизведения, используемое для разрешения неоднозначности при совпадении нескольких интервалов.
- *bool* **is_loop** - true - включить зацикливание; false - для ограничения (clamping).
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<unsigned int> &* **common_hashes** - Набор хэшей имён маркеров для учёта.

### Возвращаемое значение

Временная позиция в этой анимации, соответствующая заданному интервалу синхронизации.
