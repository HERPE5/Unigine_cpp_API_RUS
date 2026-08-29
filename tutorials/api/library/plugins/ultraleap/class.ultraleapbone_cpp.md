# Unigine::Plugins::UltraleapBone Class (CPP)

**Header:** #include <plugins/Unigine/Ultraleap/UnigineUltraleap.h>


Этот класс представляет [bone](../../../../code/plugins/ultraleap/index_cpp.md#bones) [finger](../../../../api/library/plugins/ultraleap/class.ultraleapfinger_cpp.md).


> **Notice:** Плагин [Ultraleap](../../../../code/plugins/ultraleap/index_cpp.md) должен быть загружен.


## UltraleapBone Class

### Перечисления

## TYPE

| Name | Description |
|---|---|
| **TYPE_METACARPAL** = 0 | Пястная [bone](../../../../code/plugins/ultraleap/index_cpp.md#bones). |
| **TYPE_PROXIMAL** = 1 | Проксимальная фаланга ([bone](../../../../code/plugins/ultraleap/index_cpp.md#bones)). |
| **TYPE_INTERMEDIATE** = 2 | Средняя фаланга ([bone](../../../../code/plugins/ultraleap/index_cpp.md#bones)). |
| **TYPE_DISTAL** = 3 | Дистальная фаланга ([bone](../../../../code/plugins/ultraleap/index_cpp.md#bones)). Кость на кончике пальца. |
| **NUM_TYPES** = 4 | Общее количество типов костей. |

### Методы класса

---

## UltraleapFinger * getFinger ( ) const

Возвращает объект пальца.
### Возвращаемое значение

Объект пальца.
## UltraleapBone::TYPE getType ( ) const

Возвращает тип кости.
### Возвращаемое значение

Тип кости. Одно из значений [Bone::TYPE_*](#TYPE_METACARPAL).
## double getLength ( ) const

Возвращает длину кости.
### Возвращаемое значение

Длина кости, в метрах.
## double getWidth ( ) const

Возвращает ширину кости, в метрах.
### Возвращаемое значение

Ширина кости, в метрах.
## Math:: Vec3 getJointBeginPosition ( ) const

Возвращает координаты конца кости, ближайшего к запястью (проксимальный конец).
### Возвращаемое значение

Координаты конца кости, ближайшего к запястью (проксимальный конец).
## Math:: Vec3 getJointEndPosition ( ) const

Возвращает координаты конца кости, ближайшего к кончику пальца (дистальный конец).
### Возвращаемое значение

Координаты конца кости, ближайшего к кончику пальца (дистальный конец).
## Math:: Vec3 getCenter ( ) const

Возвращает координаты центра кости.
### Возвращаемое значение

Координаты центра кости.
## Math:: vec3 getDirection ( ) const

Возвращает нормализованное направление кости от запястья к кончику.
### Возвращаемое значение

Нормализованное направление кости от запястья к кончику.
