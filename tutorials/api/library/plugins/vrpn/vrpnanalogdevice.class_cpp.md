# Unigine::Plugins::VrpnAnalogDevice Class (CPP)

**Header:** #include <plugins/Unigine/VrpnClient/UnigineVrpnClient.h>


Класс для [VRPN Plugin](../../../../code/plugins/vrpn/index_cpp.md), позволяющий получать данные о стиках устройств ввода (например, стики геймпада).


### См. также


- Статья о [VRPN Plugin](../../../../code/plugins/vrpn/index_cpp.md)
- Примеры UnigineScript:

  -
  -


## VrpnAnalogDevice Class

### Методы класса

---

## void setAnalogCallback ( const char * name )

Задаёт функцию callback скрипта мира, получающую данные о стиках устройства ввода.
> **Notice:** Функция callback должна быть определена в скрипте мира и принимать **1** аргумент - экземпляр класса *VrpnAnalogDevice*.
> ```cpp
> void callback_func(VrpnAnalogDevice device) {
>     // логика функции
> }
>
> ```


### Аргументы

- *const char ** **name** - Имя функции callback.

### Примеры


```cpp
VrpnAnalogDevice vrpn_analog;

int init() {
	// создаём экземпляр VrpnAnalogDevice
    vrpn_analog = new VrpnAnalogDevice("device_name@server_addr");
	// задаём callback
    vrpn_analog.setAnalogCallback("analog_callback");
}

int shutdown() {
    delete vrpn_analog;
    return 1;
}

int update() {
    vrpn_analog.update();
    return 1;
}

// функция callback
void analog_callback(VrpnAnalogDevice device) {
    forloop(int i = 0; device.getNumChannels()) {
        log.message("Device analog channel %d: %lf\n",i,device.getChannel(i));
    }
}

```


## const char * getAnalogCallback ( )

Возвращает имя функции callback скрипта мира, получающей данные о стиках устройства ввода. Функция callback должна быть определена в скрипте мира и принимать **1** аргумент - экземпляр класса *VrpnAnalogDevice*.
```cpp
void callback_func(VrpnAnalogDevice device) {
    // логика функции
}

```


### Возвращаемое значение

Имя функции callback.
## double getChannel ( int channel )

Возвращает данные, полученные аналоговым стиком с указанным номером.
> **Notice:** Если указанный стик не получил данных, произойдёт ассерт движка.


### Аргументы

- *int* **channel** - Номер аналогового стика в диапазоне [0;number_of_sticks - 1].

### Возвращаемое значение

Данные, полученные аналоговым стиком с указанным номером.
## int getNumChannels ( )

Возвращает количество аналоговых стиков, получивших данные.
### Возвращаемое значение

Количество аналоговых стиков, получивших данные. Если ни один стик не получил данных, будет возвращено 0.
## void update ( )

Обновляет внутреннее состояние устройства и получает данные ввода.
> **Notice:** Эта функция должна вызываться каждый кадр.


## bool hasChanges ( ) const

Возвращает значение, указывающее, были ли зарегистрированы какие-либо изменения аналоговых значений.
### Возвращаемое значение

true, если были зарегистрированы какие-либо изменения аналоговых значений; иначе false.
## VrpnAnalogDevice ( const char * name )

Конструктор.
### Аргументы

- *const char ** **name** - Путь к устройству в формате *device_name@server_address*.
