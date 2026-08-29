# CigiIGUserDefined Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>


## CigiIGUserDefined Class

### Методы класса

---

## void setPacketID ( int id )

Задаёт ID пользовательского пакета.
### Аргументы

- *int* **id** - ID пользовательского пакета.

## void setData ( const unsigned char * data , int size )

Задаёт [user-defined data](../../../../../ig/custom_packets.md#custom_cigi).
> **Notice:** Байты читаются и записываются начиная со 2-го байта (не с 4-го). Если требуется выровнять байты начиная с 4-го, следует добавить пару байтов в начале. CIGI ICD рекомендует начинать чтение/запись байтов с 4-го (см. данные перед **Data Block 1** на изображениях ниже), хотя упоминается, что можно начинать и со 2-го.


![General User-Defined Packet Structure](../../../../../ig/userpacket_cigi.png)


### Аргументы

- *const unsigned char ** **data** - Пользовательские данные.
- *int* **size** - Размер пакета.
