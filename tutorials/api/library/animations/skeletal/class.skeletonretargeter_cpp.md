# SkeletonRetargeter Class (CPP)

**Header:** #include <UnigineSkeleton.h>


Это базовый класс для ретаргетинга анимации — переноса поз скелетной анимации с одного скелета на другой. Различные стратегии ретаргетинга реализованы в подклассах:


- [SkeletonRetargeterEquals](../../../../api/library/animations/skeletal/class.skeletonretargeterequals_cpp.md) — для скелетов с идентичными иерархиями суставов.
- [SkeletonRetargeterNamesMatching](../../../../api/library/animations/skeletal/class.skeletonretargeternamesmatching_cpp.md) — сопоставляет суставы по совпадению их имён.
- [SkeletonRetargeterTranslations](../../../../api/library/animations/skeletal/class.skeletonretargetertranslations_cpp.md) — сопоставляет суставы по совпадению их перемещений.


Используйте статический метод [findRetargeter()](#findRetargeter_ConstSkeleton_ConstSkeleton_SkeletonRetargeter) для автоматического поиска зарегистрированного ретаргетера между двумя скелетами, или создавайте экземпляры подклассов напрямую для пользовательской конфигурации.


## SkeletonRetargeter Class

### Перечисления

## TYPE

Идентификатор типа подкласса ретаргетера.
| Имя | Описание |
|---|---|
| **SKELETON_RETARGETER** = 0 | Базовый тип ретаргетера. |
| **SKELETON_RETARGETER_EQUALS** = 1 | Ретаргетер для скелетов с идентичными иерархиями суставов. |
| **SKELETON_RETARGETER_NAMES_MATCHING** = 2 | Ретаргетер, сопоставляющий суставы по совпадению имён. |
| **SKELETON_RETARGETER_TRANSLATIONS** = 3 | Ретаргетер, сопоставляющий суставы по совпадению перемещений. |

## RETARGET_DIRECTION

Направление ретаргетинга между двумя скелетами.
| Имя | Описание |
|---|---|
| **RETARGET_DIRECTION_FORWARD** = 0 | Ретаргетинг от первого скелета ко второму. |
| **RETARGET_DIRECTION_BACKWARD** = 1 | Ретаргетинг от второго скелета к первому. |

### Методы класса

## getType () const

Возвращает текущий тип этого экземпляра ретаргетера, определяющий, какую стратегию подкласса он реализует.
### Возвращаемое значение

Текущий тип ретаргетера.
## const char * getTypeName () const

Возвращает текущее человекочитаемое имя типа ретаргетера.
### Возвращаемое значение

Текущее имя типа ретаргетера.
---

## void retarget ( SkeletonRetargeter::RETARGET_DIRECTION retarget_direction , const Ptr < SkeletonPoseDecomposed > & out_pose , const Ptr < SkeletonPoseDecomposed > & compatible_pose ) const

Выполняет ретаргетинг декомпозированной позы с одного скелета на другой. compatible_pose предоставляет исходные трансформации суставов, а out_pose получает результат ретаргетинга.
### Аргументы

- *[SkeletonRetargeter::RETARGET_DIRECTION](../../../../api/library/animations/skeletal/class.skeletonretargeter_cpp.md#RETARGET_DIRECTION)* **retarget_direction** - Направление ретаргетинга.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[SkeletonPoseDecomposed](../../../../api/library/animations/skeletal/class.skeletonposedecomposed_cpp.md)> &* **out_pose** - Выходная поза, получающая результат ретаргетинга.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[SkeletonPoseDecomposed](../../../../api/library/animations/skeletal/class.skeletonposedecomposed_cpp.md)> &* **compatible_pose** - Исходная поза, от которой выполняется ретаргетинг.

## void retarget ( SkeletonRetargeter::RETARGET_DIRECTION retarget_direction , const Ptr < SkeletonPoseMatrix > & out_pose , const Ptr < SkeletonPoseMatrix > & compatible_pose ) const

Выполняет ретаргетинг матричной позы с одного скелета на другой. compatible_pose предоставляет исходные трансформации суставов, а out_pose получает результат ретаргетинга.
### Аргументы

- *[SkeletonRetargeter::RETARGET_DIRECTION](../../../../api/library/animations/skeletal/class.skeletonretargeter_cpp.md#RETARGET_DIRECTION)* **retarget_direction** - Направление ретаргетинга.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[SkeletonPoseMatrix](../../../../api/library/animations/skeletal/class.skeletonposematrix_cpp.md)> &* **out_pose** - Выходная поза, получающая результат ретаргетинга.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[SkeletonPoseMatrix](../../../../api/library/animations/skeletal/class.skeletonposematrix_cpp.md)> &* **compatible_pose** - Исходная поза, от которой выполняется ретаргетинг.

## void scaleRootMotion ( SkeletonRetargeter::RETARGET_DIRECTION retarget_direction , Math::Transform & delta ) const

Масштабирует дельта-позицию root motion для пропорционального ретаргетинга между двумя скелетами. Применяется только к ретаргетерам типа TRANSLATIONS — остальные типы оставляют дельту без изменений. В режиме ретаргетинга BIND дельта-позиция обнуляется. В режиме PROPORTION дельта-позиция масштабируется по соотношению длин корневых костей исходного и целевого скелетов.
### Аргументы

- *[SkeletonRetargeter::RETARGET_DIRECTION](../../../../api/library/animations/skeletal/class.skeletonretargeter_cpp.md#RETARGET_DIRECTION)* **retarget_direction** - Направление ретаргетинга.
- *Math::Transform &* **delta** - Дельта-трансформация root motion, подлежащая масштабированию.

## static Ptr < SkeletonRetargeter > findRetargeter ( const Ptr <ConstSkeleton> & skeleton_0 , const Ptr <ConstSkeleton> & skeleton_1 , int & out_retarget_direction )

Выполняет поиск зарегистрированного ретаргетера между двумя скелетами и возвращает направление ретаргетинга через выходной параметр.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<ConstSkeleton> &* **skeleton_0** - Первый скелет.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<ConstSkeleton> &* **skeleton_1** - Второй скелет.
- *int &* **out_retarget_direction** - Выходная переменная, получающая направление ретаргетинга для этой пары скелетов.

### Возвращаемое значение

Экземпляр ретаргетера, если найден; иначе null.
## static Ptr < SkeletonRetargeter > findRetargeter ( const Ptr <ConstSkeleton> & skeleton_0 , const Ptr <ConstSkeleton> & skeleton_1 )

Выполняет поиск зарегистрированного ретаргетера между двумя скелетами.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<ConstSkeleton> &* **skeleton_0** - Первый скелет.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<ConstSkeleton> &* **skeleton_1** - Второй скелет.

### Возвращаемое значение

Экземпляр ретаргетера, если найден; иначе null.
## static Ptr < SkeletonRetargeter > findRetargeter ( const UGUID & skeleton_file_guid_0 , const UGUID & skeleton_file_guid_1 , int & out_retarget_direction )

Выполняет поиск зарегистрированного ретаргетера между двумя скелетами, идентифицированными их файловыми GUID, и возвращает направление ретаргетинга через выходной параметр.
### Аргументы

- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **skeleton_file_guid_0** - GUID файла первого скелета.
- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **skeleton_file_guid_1** - GUID файла второго скелета.
- *int &* **out_retarget_direction** - Выходная переменная, получающая направление ретаргетинга для этой пары скелетов.

### Возвращаемое значение

Экземпляр ретаргетера, если найден; иначе null.
## static Ptr < SkeletonRetargeter > findRetargeter ( const UGUID & skeleton_file_guid_0 , const UGUID & skeleton_file_guid_1 )

Выполняет поиск зарегистрированного ретаргетера между двумя скелетами, идентифицированными их файловыми GUID.
### Аргументы

- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **skeleton_file_guid_0** - GUID файла первого скелета.
- *const [UGUID](../../../../api/library/filesystem/class.uguid_cpp.md) &* **skeleton_file_guid_1** - GUID файла второго скелета.

### Возвращаемое значение

Экземпляр ретаргетера, если найден; иначе null.
