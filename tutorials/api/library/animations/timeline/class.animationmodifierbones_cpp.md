# Unigine::AnimationModifierBones Class (CPP)

**Header:** #include <UnigineAnimation.h>

**Inherits from:** AnimationModifier


Этот класс позволяет анимировать все кости для [ObjectMeshSkinnedLegacy](../../../../api/library/objects/class.objectmeshskinnedlegacy_cpp.md).


## AnimationModifierBones Class

### Методы класса

## void setNumBones ( )

Задаёт новое количество костей, затрагиваемых модификатором анимации.
### Аргументы

- **bones** - Количество костей, затрагиваемых модификатором анимации.

## getNumBones () const

Возвращает текущее количество костей, затрагиваемых модификатором анимации.
### Возвращаемое значение

Текущее количество костей, затрагиваемых модификатором анимации.
---

## AnimationModifierBones ( )

Конструктор. Создаёт новый модификатор анимации для костей.
## void copy ( const Ptr < AnimationModifierBones > & modifier )

Копирует все данные из указанного исходного модификатора анимации.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationModifierBones](../../../../api/library/animations/timeline/class.animationmodifierbones_cpp.md)> &* **modifier** - Исходный модификатор анимации.

## int getValueByTime ( float time , Vector < Math:: mat4 > & OUT_transforms )

Возвращает количество костей, затрагиваемых модификатором анимации, и сохраняет значения преобразований модификатора в указанный момент времени.
### Аргументы

- *float* **time** - Время ключа на временной шкале, в секундах.
- *[Vector](../../../../api/library/containers/vector/class.vector_cpp.md)< Math::[mat4](../../../../api/library/math/class.mat4_cpp.md)> &* **OUT_transforms** - Матрицы преобразований для сохранения возвращаемых значений. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

### Возвращаемое значение

Количество костей, затрагиваемых модификатором анимации.
## void addValue ( float time , Vector < Math:: mat4 > & OUT_transforms )

Добавляет значения преобразований в модификатор в указанный момент времени.
### Аргументы

- *float* **time** - Время ключа на временной шкале, в секундах.
- *[Vector](../../../../api/library/containers/vector/class.vector_cpp.md)< Math::[mat4](../../../../api/library/math/class.mat4_cpp.md)> &* **OUT_transforms** - Матрицы преобразований. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void setCurvePosX ( int bone_index , const Ptr < AnimationCurveFloat > & in_curve )

Задаёт кривую, хранящую позиции кости вдоль оси X.
### Аргументы

- *int* **bone_index** - Индекс кости.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveFloat](../../../../api/library/animations/timeline/class.animationcurvefloat_cpp.md)> &* **in_curve** - Кривая анимации, хранящая позиции кости вдоль оси X.

## Ptr < AnimationCurveFloat > getCurvePosX ( int bone_index ) const

Возвращает кривую, хранящую позиции кости вдоль оси X.
### Аргументы

- *int* **bone_index** - Индекс кости.

### Возвращаемое значение

Кривая анимации, хранящая позиции кости вдоль оси X.
## void setCurvePosY ( int bone_index , const Ptr < AnimationCurveFloat > & in_curve )

Задаёт кривую, хранящую позиции кости вдоль оси Y.
### Аргументы

- *int* **bone_index** - Индекс кости.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveFloat](../../../../api/library/animations/timeline/class.animationcurvefloat_cpp.md)> &* **in_curve** - Кривая анимации, хранящая позиции кости вдоль оси Y.

## Ptr < AnimationCurveFloat > getCurvePosY ( int bone_index ) const

Возвращает кривую, хранящую позиции кости вдоль оси Y.
### Аргументы

- *int* **bone_index** - Индекс кости.

### Возвращаемое значение

Кривая анимации, хранящая позиции кости вдоль оси Y.
## void setCurvePosZ ( int bone_index , const Ptr < AnimationCurveFloat > & in_curve )

Задаёт кривую, хранящую позиции кости вдоль оси Z.
### Аргументы

- *int* **bone_index** - Индекс кости.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveFloat](../../../../api/library/animations/timeline/class.animationcurvefloat_cpp.md)> &* **in_curve** - Кривая анимации, хранящая позиции кости вдоль оси Z.

## Ptr < AnimationCurveFloat > getCurvePosZ ( int bone_index ) const

Возвращает кривую, хранящую позиции кости вдоль оси Z.
### Аргументы

- *int* **bone_index** - Индекс кости.

### Возвращаемое значение

Кривая анимации, хранящая позиции кости вдоль оси Z.
## void setCurveRot ( int bone_index , const Ptr < AnimationCurveQuat > & in_curve )

Задаёт кривую, хранящую преобразования кости.
### Аргументы

- *int* **bone_index** - Индекс кости.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveQuat](../../../../api/library/animations/timeline/class.animationcurvequat_cpp.md)> &* **in_curve** - Кривая анимации, хранящая преобразования кости.

## Ptr < AnimationCurveQuat > getCurveRot ( int bone_index ) const

Возвращает кривую, хранящую преобразования кости.
### Аргументы

- *int* **bone_index** - Индекс кости.

### Возвращаемое значение

Кривая анимации, хранящая преобразования кости.
## void setCurveScaleX ( int bone_index , const Ptr < AnimationCurveFloat > & in_curve )

Задаёт кривую анимации, хранящую масштабирование кости вдоль оси X.
### Аргументы

- *int* **bone_index** - Индекс кости.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveFloat](../../../../api/library/animations/timeline/class.animationcurvefloat_cpp.md)> &* **in_curve** - Кривая анимации, хранящая масштабирование кости вдоль оси X.

## Ptr < AnimationCurveFloat > getCurveScaleX ( int bone_index ) const

Возвращает кривую анимации, хранящую масштабирование кости вдоль оси X.
### Аргументы

- *int* **bone_index** - Индекс кости.

### Возвращаемое значение

Кривая анимации, хранящая масштабирование кости вдоль оси X.
## void setCurveScaleY ( int bone_index , const Ptr < AnimationCurveFloat > & in_curve )

Задаёт кривую анимации, хранящую масштабирование кости вдоль оси Y.
### Аргументы

- *int* **bone_index** - Индекс кости.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveFloat](../../../../api/library/animations/timeline/class.animationcurvefloat_cpp.md)> &* **in_curve** - Кривая анимации, хранящая масштабирование кости вдоль оси Y.

## Ptr < AnimationCurveFloat > getCurveScaleY ( int bone_index ) const

Возвращает кривую анимации, хранящую масштабирование кости вдоль оси Y.
### Аргументы

- *int* **bone_index** - Индекс кости.

### Возвращаемое значение

Кривая анимации, хранящая масштабирование кости вдоль оси Y.
## void setCurveScaleZ ( int bone_index , const Ptr < AnimationCurveFloat > & in_curve )

Задаёт кривую анимации, хранящую масштабирование кости вдоль оси Z.
### Аргументы

- *int* **bone_index** - Индекс кости.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveFloat](../../../../api/library/animations/timeline/class.animationcurvefloat_cpp.md)> &* **in_curve** - Кривая анимации, хранящая масштабирование кости вдоль оси Z.

## Ptr < AnimationCurveFloat > getCurveScaleZ ( int bone_index ) const

Возвращает кривую анимации, хранящую масштабирование кости вдоль оси Z.
### Аргументы

- *int* **bone_index** - Индекс кости.

### Возвращаемое значение

Кривая анимации, хранящая масштабирование кости вдоль оси Z.
