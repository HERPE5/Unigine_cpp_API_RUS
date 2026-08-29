# Unigine::AnimationFrame Class (CPP)

**Header:** #include <UnigineAnimation.h>


Этот класс позволяет управлять [animation frames](../../../../principles/animations/index.md#animation_frame). Кадр можно представить как вертикальный срез значений всех модификаторов всех дорожек, воспроизводимых в определённый момент времени.


## AnimationFrame Class

---

## AnimationFrame ( )

Конструктор. Создаёт пустой кадр анимации.
## void copy ( const Ptr < AnimationFrame > & frame )

Копирует данные из указанного исходного кадра в данный кадр.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationFrame](../../../../api/library/animations/timeline/class.animationframe_cpp.md)> &* **frame** - Исходный кадр.

## void clear ( )

Очищает данные кадра анимации.
## int getModifierInfos ( Vector < Ptr < AnimationModifierInfo >> & OUT_infos )

Собирает информацию обо всех [modifiers](../../../../principles/animations/index.md#animation_modifier), активных в этом кадре, и помещает её в указанный выходной буфер.
### Аргументы

- *[Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationModifierInfo](../../../../api/library/animations/timeline/class.animationmodifierinfo_cpp.md)>> &* **OUT_infos** - Выходной буфер для информации обо всех модификаторах, активных в этом кадре. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

### Возвращаемое значение

Количество модификаторов.
## void interpolate ( const Ptr < AnimationFrame > & frame , float k )

Интерполирует значения всех модификаторов кадра между текущим кадром и указанным с заданным коэффициентом интерполяции и обновляет все модификаторы кадра интерполированными значениями: **`val = interpolate(val, frame_val, k)`**.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationFrame](../../../../api/library/animations/timeline/class.animationframe_cpp.md)> &* **frame** - Целевой кадр анимации.
- *float* **k** - Коэффициент интерполяции.

## void interpolate ( const Ptr < AnimationFrame > & frame , float k , const Ptr < AnimationMask > & exclude_mask )

Интерполирует значения всех модификаторов кадра между текущим кадром и указанным с заданным коэффициентом интерполяции. Значения модификаторов, принадлежащих указанной маске исключения, игнорируются и остаются неизменными. Все модификаторы кадра обновляются интерполированными значениями: **`val = interpolate(val, frame_val, k)`**.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationFrame](../../../../api/library/animations/timeline/class.animationframe_cpp.md)> &* **frame** - Целевой кадр анимации.
- *float* **k** - Коэффициент интерполяции.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationMask](../../../../api/library/animations/timeline/class.animationmask_cpp.md)> &* **exclude_mask** - Маска анимации, исключаемая из интерполяции.
