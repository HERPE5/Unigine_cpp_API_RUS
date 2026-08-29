# VRPN Plugin

> **Warning:** Функциональность, описанная в этой статье, недоступна в редакции Community SDK.
> Для её использования следует перейти на редакцию SDK [**Sim**](https://l.unigine.com/SdhugY462).


Этот раздел содержит функции, доступные при загруженном [VRPN Plugin](../../../../code/plugins/vrpn/index_cpp.md).


Если плагин загружен вместе с движком, задаётся определение `HAS_VRPN_CLIENT`. Это определение можно использовать, например, чтобы избежать ошибок, если плагин не загружен: код, в котором выполняются функции плагина, можно обернуть следующим образом:

```cpp
#ifdef HAS_VRPN_CLIENT
	// функции плагина VRPN
#endif

```


### См. также


- Статья о [VRPN Plugin](../../../../code/plugins/vrpn/index_cpp.md)
- Примеры UnigineScript:

  -
  -


## Статьи в этом разделе



- [VrpnClient Class (CPP)](../../../../api/library/plugins/vrpn/class.vrpnclient_cpp.md)



- [VrpnAnalogDevice Class (CPP)](../../../../api/library/plugins/vrpn/vrpnanalogdevice.class_cpp.md)



- [VrpnButtonDevice Class (CPP)](../../../../api/library/plugins/vrpn/vrpnbuttondevice.class_cpp.md)



- [VrpnTrackerDevice Class (CPP)](../../../../api/library/plugins/vrpn/vrpntrackerdevice.class_cpp.md)
