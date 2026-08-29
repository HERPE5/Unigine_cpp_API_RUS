# Unigine::Plugins::VrpnButtonDevice Class (CPP)

**Header:** #include <plugins/Unigine/VrpnClient/UnigineVrpnClient.h>


Класс для [VRPN Plugin](../../../../code/plugins/vrpn/index_cpp.md), позволяющий получать данные о состояниях кнопок устройства ввода.


### См. также


- Статья о [VRPN Plugin](../../../../code/plugins/vrpn/index_cpp.md)
- Примеры UnigineScript:

  -
  -


## VrpnButtonDevice Class

### Методы класса

---

## void setButtonCallback ( const char * name )

Задаёт функцию callback скрипта мира, получающую данные о кнопках устройства ввода.
> **Notice:** Функция callback должна быть определена в скрипте мира и принимать **2** аргумента - номер и состояние кнопки.
> ```cpp
> void callback_func(int button,int state) {
>     // логика функции
> }
>
> ```


### Аргументы

- *const char ** **name** - Имя функции callback.

### Примеры


```cpp
VrpnButtonDevice vrpn_button;

int init() {
	// создаём экземпляр VrpnButtonDevice
    vrpn_button = new VrpnButtonDevice("device_name@server_addr");
	// задаём callback
    vrpn_button.setButtonCallback("button_callback");
    return 1;
}

int shutdown() {
    delete vrpn_button;
    return 1;
}

int update() {
    vrpn_button.update();
    return 1;
}

// функция callback
void button_callback(int button,int state) {
    log.message("Device button %d: %d\n",button,state);
}

```


## const char * getButtonCallback ( )

Возвращает имя функции callback скрипта мира, получающей данные о кнопках устройства ввода. Функция callback должна быть определена в скрипте мира и принимать **2** аргумента - номер и состояние кнопки.
```cpp
void callback_func(int button,int state) {
    // логика функции
}

```


### Возвращаемое значение

Имя функции callback.
## void update ( )

Обновляет внутреннее состояние устройства и получает данные ввода.
> **Notice:** Эта функция должна вызываться каждый кадр.


## int getNumButtons ( ) const

Возвращает общее количество кнопок устройства ввода.
### Возвращаемое значение

Общее количество кнопок устройства ввода.
## int getButtonState ( int num ) const

Возвращает текущее состояние кнопки с указанным индексом.
### Аргументы

- *int* **num** - Индекс кнопки.

### Возвращаемое значение

Состояние кнопки.
## VrpnButtonDevice ( const char * name )

Конструктор.
### Аргументы

- *const char ** **name** - Путь к устройству в формате *device_name@server_address*.
