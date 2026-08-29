# Unigine::AnimationCurve Class (CPP)

**Header:** #include <UnigineAnimation.h>


Это базовый класс для всех [animation curves](../../../../principles/animations/index.md#animation_curve). Кривые анимации определяют изменение значений определённых типов (*bool, float, integer, quat* и т.д.) во времени.


## AnimationCurve Class

### Перечисления

## TYPE

Тип кривой анимации.
| Имя | Описание |
|---|---|
| **ANIMATION_CURVE** = 0 | Кривая анимации, хранящая значения. |
| **ANIMATION_CURVE_INT** = 1 | Кривая анимации, хранящая значения типа *integer* (см. класс *[AnimationCurveInt](../../../../api/library/animations/timeline/class.animationcurveint_cpp.md)*). |
| **ANIMATION_CURVE_FLOAT** = 2 | Кривая анимации, хранящая значения типа *float* (см. класс *[AnimationCurveIntFloat](../../../../api/library/animations/timeline/class.animationcurvefloat_cpp.md)*). |
| **ANIMATION_CURVE_DOUBLE** = 3 | Кривая анимации, хранящая значения типа *double* (см. класс *[AnimationCurveDouble](../../../../api/library/animations/timeline/class.animationcurvedouble_cpp.md)*). |
| **ANIMATION_CURVE_BOOL** = 4 | Кривая анимации, хранящая значения типа *boolean* (см. класс *[AnimationCurveBool](../../../../api/library/animations/timeline/class.animationcurvebool_cpp.md)*). |
| **ANIMATION_CURVE_SCALAR** = 5 | Кривая анимации, хранящая значения типа *scalar* (см. класс *[AnimationCurveScalar](../../../../api/library/animations/timeline/class.animationcurvescalar_cpp.md)*). |
| **ANIMATION_CURVE_QUAT** = 6 | Кривая анимации, хранящая значения типа *quaternion* (см. класс *[AnimationCurveQuat](../../../../api/library/animations/timeline/class.animationcurvequat_cpp.md)*). |
| **ANIMATION_CURVE_STRING** = 7 | Кривая анимации, хранящая значения типа *string* (см. класс *[AnimationCurveString](../../../../api/library/animations/timeline/class.animationcurvestring_cpp.md)*). |
| **ANIMATION_CURVE_UGUID** = 8 | Кривая анимации, хранящая значения типа *UGUID* (см. класс *[AnimationCurveUGUID](../../../../api/library/animations/timeline/class.animationcurveuguid_cpp.md)*). |

## KEY_TYPE

Тип интерполяции между соседними ключами.
| Имя | Описание |
|---|---|
| **KEY_TYPE_CONSTANT** = 0 | Значение левого ключа используется на всём сегменте между двумя ключами. |
| **KEY_TYPE_LINEAR** = 1 | Используется линейная интерполяция между двумя ключами. |
| **KEY_TYPE_SMOOTH** = 2 | Для интерполяции используется кривая Безье, где левая и правая касательные каждого ключа симметричны относительно начала координат. |
| **KEY_TYPE_BREAK** = 3 | Для интерполяции используется кривая Безье, с возможностью независимой настройки левой и правой касательных каждого ключа. |
| **NUM_KEY_TYPES** = 4 | Общее число типов интерполяции между ключами. |

### Методы класса

## AnimationCurve::TYPE getType () const

Возвращает текущий тип кривой анимации.
### Возвращаемое значение

Текущий тип кривой анимации.
## const char * getTypeName () const

Возвращает текущее имя типа кривой анимации.
### Возвращаемое значение

Текущее имя типа кривой анимации.
