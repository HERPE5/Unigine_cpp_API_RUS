# Unigine::Plugins::VrpnClient Class (CPP)

**Header:** #include <plugins/Unigine/VrpnClient/UnigineVrpnClient.h>

> **Notice:** Этот класс является одиночкой (singleton).


Класс для [VRPN Plugin](../../../../code/plugins/vrpn/index_cpp.md), позволяющий управлять различными устройствами ввода.


### См. также


- Статья о [VRPN Plugin](../../../../code/plugins/vrpn/index_cpp.md)
- Примеры UnigineScript:

  -
  -


## VrpnClient Class

### Методы класса

---

## VrpnAnalogDeviceInterface * createAnalogDevice ( const char * name )

Создаёт объект, позволяющий получать данные о стиках устройства ввода (например, стики геймпада).
### Аргументы

- *const char ** **name** - Путь к устройству в формате device_name@server_address.

### Возвращаемое значение

Вновь созданный VrpnAnalogDevice.
## void deleteAnalogDevice ( VrpnAnalogDeviceInterface * OUT_device )

Удаляет объект VrpnAnalogDevice.
### Аргументы

- *VrpnAnalogDeviceInterface ** **OUT_device** - VrpnAnalogDevice для удаления. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## VrpnButtonDeviceInterface * createButtonDevice ( const char * name )

Создаёт объект, позволяющий получать данные о состояниях кнопок устройства ввода.
### Аргументы

- *const char ** **name** - Путь к устройству в формате device_name@server_address.

### Возвращаемое значение

Вновь созданный VrpnButtonDevice.
## void deleteButtonDevice ( VrpnButtonDeviceInterface * OUT_device )

Удаляет объект VrpnButtonDevice.
### Аргументы

- *VrpnButtonDeviceInterface ** **OUT_device** - VrpnButtonDevice для удаления. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## VrpnTrackerDeviceInterface * createTrackerDevice ( const char * name )

Создаёт объект, позволяющий получать данные о позиции, ориентации, скорости и ускорении отслеживаемых объектов от 3D-сенсоров трекинга.
### Аргументы

- *const char ** **name** - Путь к устройству в формате device_name@server_address.

### Возвращаемое значение

Вновь созданный VrpnTrackerDevice.
## void deleteTrackerDevice ( VrpnTrackerDeviceInterface * OUT_device )

Удаляет объект VrpnTrackerDevice.
### Аргументы

- *VrpnTrackerDeviceInterface ** **OUT_device** - VrpnTrackerDevice для удаления. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
