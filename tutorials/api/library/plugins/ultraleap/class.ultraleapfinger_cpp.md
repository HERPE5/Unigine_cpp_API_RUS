# Unigine::Plugins::UltraleapFinger Class (CPP)

**Header:** #include <plugins/Unigine/Ultraleap/UnigineUltraleap.h>


Эта структура представляет [finger](../../../../code/plugins/ultraleap/index_cpp.md#fingers) [hand](../../../../api/library/plugins/ultraleap/class.ultraleaphand_cpp.md).


> **Notice:** Плагин [Ultraleap](../../../../code/plugins/ultraleap/index_cpp.md) должен быть загружен.


## UltraleapFinger Class

### Перечисления

## TYPE

| Name | Description |
|---|---|
| **TYPE_THUMB** = 0 | Большой палец. |
| **TYPE_INDEX** = 1 | Указательный палец. |
| **TYPE_MIDDLE** = 2 | Средний палец. |
| **TYPE_RING** = 3 | Безымянный палец. |
| **TYPE_PINKY** = 4 | Мизинец. |
| **NUM_TYPES** = 5 | Общее количество типов пальцев. |

### Методы класса

---

## UltraleapFinger::TYPE getType ( ) const

Возвращает тип пальца.
### Возвращаемое значение

Тип пальца. Одно из значений [UltraleapFinger::TYPE_*](#TYPE_THUMB).
## bool isExtended ( ) const

Возвращает значение, указывающее, разогнут ли палец.
### Возвращаемое значение

true, если палец разогнут; иначе false.
## double getLength ( ) const

Возвращает длину пальца, в метрах.
### Возвращаемое значение

Длина пальца, в метрах.
## UltraleapHand * getHand ( ) const

Возвращает объект руки (кисти).
### Возвращаемое значение

Объект руки (кисти).
## UltraleapBone * getBoneMetacarpal ( ) const

Возвращает объект пястной кости.
### Возвращаемое значение

Объект пястной кости.
## UltraleapBone * getBoneProximal ( ) const

Возвращает объект проксимальной фаланги.
### Возвращаемое значение

Объект проксимальной фаланги.
## UltraleapBone * getBoneIntermediate ( ) const

Возвращает объект средней фаланги.
### Возвращаемое значение

Объект средней фаланги.
## UltraleapBone * getBoneDistal ( ) const

Возвращает объект дистальной фаланги.
### Возвращаемое значение

Объект дистальной фаланги.
