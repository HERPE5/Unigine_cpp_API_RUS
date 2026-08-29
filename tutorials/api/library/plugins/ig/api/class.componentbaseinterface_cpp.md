# Unigine::Plugins::IG::ComponentBaseInterface Class (CPP)

**Header:** #include <plugins/Unigine/IG/UnigineIG.h>


Все компоненты, которым требуется работать в IG, должны наследоваться от этого класса. Его методы [saveState()](#saveState_const_BlobPtr_ref_void) и [restoreState()](#restoreState_const_BlobPtr_ref_void) используются только для ExtraSlave, которые подключаются не с самого начала и должны начать работу где-то в середине симуляции. Эти методы следует переопределить для синхронизации между каналами Syncker.


### Пример использования


Компонент *WaterDropAircraftController*, описанный [here](../../../../../ig/custom_component.md), иллюстрирует использование [saveState()](#saveState_const_BlobPtr_ref_void) и [restoreState()](#restoreState_const_BlobPtr_ref_void): если Master уже сбросил определённую часть воды, а затем подключается Slave, Slave не будет сбрасывать весь объём заново — Master сохраняет текущую полезную нагрузку и отправляет её Slave, а Slave сбрасывает только оставшийся объём воды.


```cpp
// WaterDropAircraftController.cpp

/.../

void WaterDropAircraftController::saveState(const BlobPtr &blob)
{
	// логика мастера
	// при подключении нового слейва
	blob->writeBool(open > 0);
	blob->writeFloat(normalize_flow);
	blob->writeFloat(current_payload);
}

void WaterDropAircraftController::restoreState(const BlobPtr &blob)
{
	// логика слейва
	// новый слейв получил эти параметры
	open = blob->readBool();
	normalize_flow = blob->readFloat();
	current_payload = blob->readFloat();
}

```


Полный код компонента *WaterDropAircraftController* приведён [here](../../../../../ig/custom_component.md).


## ComponentBaseInterface Class

### Методы класса

---

## void saveState ( const Blob Ptr & blob )


Сохраняет состояние компонента. Используется в коде, записывающем синхронизируемые данные компонента в blob на Master. Этот метод используется для синхронизации ExtraSlave, подключаемых после начала симуляции, и вызывается один раз при подключении Slave. Пример из компонента *[WaterDropAircraftController](../../../../../ig/custom_component.md)*:


```cpp
void WaterDropAircraftController::saveState(const BlobPtr &blob)
{
	// логика мастера
	// при подключении нового слейва
	blob->writeBool(open > 0);
	blob->writeFloat(normalize_flow);
	blob->writeFloat(current_payload);
}

```


### Аргументы

- *const [Blob](../../../../../api/library/common/class.blob_cpp.md)Ptr &* **blob** - Целевой Blob, в который сохраняются текущие данные компонента (его внутреннее состояние, любые параметры, команды и т.д.).

## void restoreState ( const Blob Ptr & blob )

Восстанавливает состояние компонента. Используется в коде, читающем данные из blob на Slave. Этот метод используется для синхронизации ExtraSlave, подключаемых после начала симуляции, и вызывается один раз при подключении Slave. Пример из компонента *[WaterDropAircraftController](../../../../../ig/custom_component.md)*:


```cpp
void WaterDropAircraftController::restoreState(const BlobPtr &blob)
{
	// логика слейва
	// новый слейв получил эти параметры
	open = blob->readBool();
	normalize_flow = blob->readFloat();
	current_payload = blob->readFloat();
}

```


### Аргументы

- *const [Blob](../../../../../api/library/common/class.blob_cpp.md)Ptr &* **blob** - Исходный Blob, из которого загружаются текущие данные компонента (его внутреннее состояние, любые параметры, команды и т.д.).
