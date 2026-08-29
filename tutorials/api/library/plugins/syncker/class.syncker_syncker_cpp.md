# Unigine::Plugins::Syncker::Syncker Class (CPP)

**Header:** #include <plugins/Unigine/Syncker/UnigineSyncker.h>


Этот класс представляет базовый интерфейс Syncker, от которого наследуются интерфейсы Master и Slave. Он содержит все общие функции, доступные как для Slave, так и для Master.


> **Notice:** Плагин [Syncker](../../../../code/plugins/syncker/index.md) должен быть загружен.


## Syncker Class

### Перечисления

## DELIVERY_METHOD

[Delivery mode](../../../../code/plugins/syncker/index.md#delivery_modes), используемый Syncker.
| Name | Description |
|---|---|
| **UNRELIABLE** = 0 | [Unreliable delivery mode](../../../../code/plugins/syncker/index.md#delivery_unreliable). Чистый UDP. Пакеты могут теряться, дублироваться или приходить в порядке, отличном от порядка отправки. Пакеты не сжимаются, не фрагментируются и не объединяются. |
| **SEQUENCED** = 1 | [Sequenced delivery mode](../../../../code/plugins/syncker/index.md#delivery_sequenced). Пакеты могут теряться, но никогда не дублируются, они приходят в точном порядке отправки. |
| **RELIABLE** = 2 | [Reliable delivery mode](../../../../code/plugins/syncker/index.md#delivery_reliable). Надёжный и последовательный режим, включён по умолчанию. Все пакеты доставляются получателю в точном порядке отправки. |

## ADDRESSING_METHOD

[Addressing mode](../../../../code/plugins/syncker/index.md#addressing_modes), используемый Syncker.
| Name | Description |
|---|---|
| **BROADCAST** = 0 | [Broadcast addressing mode](../../../../code/plugins/syncker/index.md#addressing_broadcast) (один-ко-всем): узлы имеют разные IP-адреса, но единый порт. |
| **UNICAST** = 1 | [Unicast addressing mode](../../../../code/plugins/syncker/index.md#addressing_unicast) (один-к-одному): узлы имеют разные IP-адреса (некоторые могут совпадать) и разные порты. |
| **MULTICAST** = 2 | [Multicast addressing mode](../../../../code/plugins/syncker/index.md#addressing_multicast) (один-ко-многим): узлы имеют разные IP-адреса, но единый порт. |

## SWAP_SYNC_MODE

Режим синхронизации swap буфера.
| Name | Description |
|---|---|
| **DEFAULT** = 0 | Стандартная синхронизация swap буфера. |
| **NVIDIA** = | Синхронизация swap буфера NVIDIA. Подробная информация о текущем статусе синхронизации отображается в консоли. > **Notice:** Этот режим доступен только для GPU NVIDIA Quadro с поддержкой G-SYNC. |

### Методы класса

---

## void setInterpolation ( bool interpolation )

***Консоль*:**`syncker_interpolation`Задаёт значение, указывающее, должны ли быть включены [interpolation and extrapolation](../../../../code/plugins/syncker/index.md#interpolation) для компьютера для решения проблемы потерянных пакетов между master и slave.
### Аргументы

- *bool* **interpolation** - true, чтобы включить [interpolation and extrapolation](../../../../code/plugins/syncker/index.md#interpolation) для компьютера; false - чтобы отключить.

## bool isInterpolation ( ) const

***Консоль*:**`syncker_interpolation`Возвращает значение, указывающее, включены ли [interpolation and extrapolation](../../../../code/plugins/syncker/index.md#interpolation) для компьютера для решения проблемы потерянных пакетов между master и slave.
### Возвращаемое значение

true, если [interpolation and extrapolation](../../../../code/plugins/syncker/index.md#interpolation) включены для компьютера; иначе false.
## bool isInterpolation ( const Ptr < Node > & node ) const

Возвращает значение, указывающее, [interpolated](../../../../code/plugins/syncker/index.md#interpolation) ли указанный узел Syncker.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел для проверки.

### Возвращаемое значение

true, если указанный узел [interpolated](../../../../code/plugins/syncker/index.md#interpolation) Syncker; иначе false.
## void setInterpolationPeriod ( double period )

***Консоль*:**`syncker_interpolation_period`
Задаёт значение периода [interpolation](../../../../code/plugins/syncker/index.md#interpolation) для компьютера. Рекомендуется использовать этот метод при задании [frequency of sending packets](../../../../api/library/plugins/syncker/class.syncker_master_cpp.md#getSendRate_float) Slave.


```cpp
//На Master
master->setSendRate(15.0f); // отправлять пакеты 15 раз в секунду

//Как на Master, так и на всех Slave
syncker->setInterpolationPeriod(0.1f); // задержка 100 мс

```


### Аргументы

- *double* **period** - Значение периода интерполяции, в секундах. Значение по умолчанию — 0.04. > **Notice:** Значение не должно быть меньше ***1 / [getSendRate()](../../../../api/library/plugins/syncker/class.syncker_master_cpp.md#getSendRate_float)***, иначе изображение будет "дёргаться".

## double getInterpolationPeriod ( ) const

***Консоль*:**`syncker_interpolation_period`Возвращает текущее значение периода [interpolation](../../../../code/plugins/syncker/index.md#interpolation) для компьютера.
### Возвращаемое значение

Значение периода интерполяции, в секундах. Значение по умолчанию — 0.04.
## void setExtrapolationPeriod ( double period )

***Консоль*:**`syncker_extrapolation_period`Задаёт значение периода [extrapolation](../../../../code/plugins/syncker/index.md#interpolation) для компьютера.
### Аргументы

- *double* **period** - Значение периода экстраполяции, в секундах. Значение по умолчанию — 0.0.

## double getExtrapolationPeriod ( ) const

***Консоль*:**`syncker_extrapolation_period`Возвращает текущее значение периода [extrapolation](../../../../code/plugins/syncker/index.md#interpolation) для компьютера.
### Возвращаемое значение

Значение периода экстраполяции, в секундах. Значение по умолчанию — 0.0.
## void setComputerName ( double period )

Задаёт имя компьютера, используемое при назначении отображаемого viewport (см. плагин *[SpiderVision](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md)*). Это имя можно задать при запуске приложения через аргумент командной строки [`computer_name`](../../../../code/plugins/syncker/options.md#computer_name). Если не указано, имя получается из плагина *[SpiderVision](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md)*, а если он недоступен, имя берётся из настроек операционной системы.
### Аргументы

- *double* **period** - Имя компьютера.

## double getComputerName ( ) const

Возвращает текущее значение периода [extrapolation](../../../../code/plugins/syncker/index.md#interpolation) для компьютера.
### Возвращаемое значение

Значение периода экстраполяции, в секундах. Значение по умолчанию — 0.0.
## void setDebug ( bool enabled , int x , int y , int align_mask )

***Консоль*:**`syncker_debug`Включает или отключает отображение отладочной информации в указанной позиции на экране.
### Аргументы

- *bool* **enabled** - true, чтобы отображать отладочную информацию; false - чтобы скрыть её.
- *int* **x** - Горизонтальный отступ блока отладочной информации. Значение по умолчанию — 10.
- *int* **y** - Вертикальный отступ блока отладочной информации. Значение по умолчанию — 10.
- *int* **align_mask** - Маска выравнивания. Одна из переменных [Gui::ALIGN_*](../../../../api/library/gui/class.gui_cpp.md#ALIGN_BOTTOM) или их комбинация. Значение по умолчанию — Gui::ALIGN_RIGHT | Gui::ALIGN_BOTTOM.

## bool isDebug ( )

***Консоль*:**`syncker_debug`Возвращает значение, указывающее, должна ли отображаться отладочная информация.
### Возвращаемое значение

true, если отладочная информация должна отображаться; иначе false.
## Syncker::ADDRESSING_METHOD getAddressingMethod ( ) const

Возвращает используемый в данный момент Syncker для связи [addressing method](../../../../code/plugins/syncker/index.md#addressing_modes) пакетов.
### Возвращаемое значение

Режим адресации пакетов, используемый в данный момент Syncker.
## void setDisconnectTimeout ( float timeout )

Задаёт период тайм-аута, после которого Slave считается отключённым.
### Аргументы

- *float* **timeout** - Продолжительность периода тайм-аута, в секундах.

## float getDisconnectTimeout ( ) const

Возвращает текущий период тайм-аута, после которого Slave считается отключённым.
### Возвращаемое значение

Продолжительность периода тайм-аута, в секундах.
## bool sendMessage ( const char * channel , const Ptr < Blob > & message , Syncker::DELIVERY_METHOD delivery_method = DELIVERY_METHOD.RELIABLE )

Отправляет пользовательское сообщение, содержащееся в указанном буфере, используя заданный метод доставки, в указанный именованный канал через протокол UDP.
### Аргументы

- *const char ** **channel** - Имя канала. Несколько систем могут одновременно использовать сеть Syncker (например, [IG](../../../../ig/index.md) и приложение пользователя). Для удобства все сообщения отправляются и принимаются через именованные каналы.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Blob](../../../../api/library/common/class.blob_cpp.md)> &* **message** - Буфер, содержащий пользовательское сообщение.
- *Syncker::DELIVERY_METHOD* **delivery_method** - [Delivery mode](../../../../code/plugins/syncker/index.md#delivery_modes), используемый Syncker, одно из значений [DELIVERY_METHOD](#DELIVERY_METHOD).

### Возвращаемое значение

true, если сообщение было успешно отправлено; иначе false.
## void setMessageReceivedCallback ( const char * channel , Unigine:: CallbackBase * func )

Задаёт функцию callback, вызываемую при отправке пользовательского сообщения UDP. Callback выполняется в главном потоке, но неопределено, в какой именно момент — в *update()*, *postUpdate()* или *swap()*. Чтобы отписаться от этого callback, задайте указатель на callback равным nullptr.
### Аргументы

- *const char ** **channel** - Имя канала. Несколько систем могут одновременно использовать сеть Syncker (например, [IG](../../../../ig/index.md) и приложение пользователя). Для удобства все сообщения отправляются и принимаются через именованные каналы. Если указанный канал не существует, он будет создан.
- *Unigine::[CallbackBase](../../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **func** - Указатель на callback. Чтобы очистить callback, задайте этот аргумент равным nullptr.

## void removeMessageReceivedCallback ( const char * channel )

Удаляет функцию callback, вызываемую при получении пользовательского сообщения UDP.
### Аргументы

- *const char ** **channel** - Имя канала. Несколько систем могут одновременно использовать сеть Syncker (например, [IG](../../../../ig/index.md) и приложение пользователя). Для удобства все сообщения отправляются и принимаются через именованные каналы. Если указанный канал не существует, он будет создан.

## Syncker::SWAP_SYNC_MODE getSwapSyncMode ( ) const

Возвращает используемый в данный момент Syncker режим синхронизации swap буфера.
### Возвращаемое значение

Текущий режим синхронизации swap, используемый Syncker. Одно из следующих значений:
- **DEFAULT** - стандартный режим синхронизации.
- **NVIDIA** - синхронизация swap буфера NVIDIA. Подробная информация о текущем статусе синхронизации отображается в консоли (доступно только для GPU NVIDIA Quadro с поддержкой G-SYNC).


## double getTime ( ) const

Возвращает текущее время кадра Master (даже если вызвано с компьютера Slave), это время последней операции swap буфера (т.е. начала следующего кадра). Этот метод точнее одноимённого метода класса [Game](../../../../api/library/engine/class.game_cpp.md#getTime_float) и возвращает значение с двойной точностью.
### Возвращаемое значение

Текущее время кадра Master, в секундах.
## double getIFps ( ) const

Возвращает продолжительность последнего кадра. Этот метод точнее одноимённого метода класса [Game](../../../../api/library/engine/class.game_cpp.md#getIFps_float) и возвращает значение с двойной точностью.
### Возвращаемое значение

Продолжительность предыдущего кадра, в секундах.
