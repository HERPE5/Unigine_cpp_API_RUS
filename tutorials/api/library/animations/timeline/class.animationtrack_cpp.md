# Unigine::AnimationTrack Class (CPP)

**Header:** #include <UnigineAnimation.h>


Этот класс используется для управления [animation tracks](../../../../principles/animations/index.md#animation_track) из кода.


## AnimationTrack Class

### Методы класса

## UGUID getGUID () const

Возвращает текущий GUID трека анимации.
### Возвращаемое значение

Текущий GUID трека.
## void setName ( const char * name )

Задаёт новое имя трека анимации.
### Аргументы

- *const char ** **name** - Имя трека.

## const char * getName () const

Возвращает текущее имя трека анимации.
### Возвращаемое значение

Текущее имя трека.
## getNumObjects () const

Возвращает текущее общее количество [animation objects](../../../../principles/animations/index.md#animation_object), управляемых [track](../../../../principles/animations/index.md#animation_track).
### Возвращаемое значение

Текущее количество объектов анимации, управляемых треком.
## getDuration () const

Возвращает текущую общую длительность трека, в секундах.
### Возвращаемое значение

Текущая длительность трека, в секундах.
## getManualDuration () const

Возвращает текущее
### Возвращаемое значение

Текущее
## const char * getPath () const

Возвращает текущий путь к файлу трека.
### Возвращаемое значение

Текущий путь к файлу трека.
## void setEventCurve ( const Ptr < AnimationCurveInt >& curve )

Задаёт новую кривую событий для трека. События позволяют вызывать функцию или метод непосредственно из анимации в определённом кадре/времени, которое вы указываете. События можно использовать, например, для воспроизведения звукового эффекта или выполнения любых других действий в любой момент временной шкалы. Значения ключей на этой кривой определяют, какие события должны быть вызваны в соответствующие моменты. Вы определяете желаемый список событий в виде перечисления, а затем просто добавляете ключи с определёнными значениями перечисления на кривую в те моменты, когда должно происходить соответствующее событие.
```cpp
// перечисление, определяющее все доступные события
enum
{
	EVENT_PLAY_SOUND = 0, 		// при этом событии мы воспроизводим звук
	EVENT_CONSOLE_MESSAGE,		// при этом событии мы выводим сообщение в консоль
	//...
};

// функция-обработчик, используемая для обработки всех событий по их идентификаторам
void on_event(int id)
{
	if (id == EVENT_PLAY_SOUND)
	{
		sound->stop();
		sound->play();
	}

	if (id == EVENT_CONSOLE_MESSAGE)
	{
		Console::onscreenMessageLine(vec4_blue, "A message.");
	}

	// ...
}

// создаём трек для событий
AnimationTrackPtr event_track = AnimationTrack::create();

// создаём трек для событий
AnimationCurveIntPtr event_curve = AnimationCurveInt::create();
event_curve->addKey(1.25f, EVENT_PLAY_SOUND);
event_curve->addKey(2.07f, EVENT_CONSOLE_MESSAGE);
event_curve->addKey(2.75f, EVENT_PLAY_SOUND);
event_track->setEventCurve(event_curve);

// добавляем трек в воспроизведение
playback->addLayer(event_track);

// добавляем обработчик обратного вызова для обработки событий
event_track->addEventCallback(MakeCallback(on_event));


```


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationCurveInt](../../../../api/library/animations/timeline/class.animationcurveint_cpp.md)>&* **curve** - Кривая событий для трека.

## Ptr < AnimationCurveInt > getEventCurve () const

Возвращает текущую кривую событий для трека. События позволяют вызывать функцию или метод непосредственно из анимации в определённом кадре/времени, которое вы указываете. События можно использовать, например, для воспроизведения звукового эффекта или выполнения любых других действий в любой момент временной шкалы. Значения ключей на этой кривой определяют, какие события должны быть вызваны в соответствующие моменты. Вы определяете желаемый список событий в виде перечисления, а затем просто добавляете ключи с определёнными значениями перечисления на кривую в те моменты, когда должно происходить соответствующее событие.
```cpp
// перечисление, определяющее все доступные события
enum
{
	EVENT_PLAY_SOUND = 0, 		// при этом событии мы воспроизводим звук
	EVENT_CONSOLE_MESSAGE,		// при этом событии мы выводим сообщение в консоль
	//...
};

// функция-обработчик, используемая для обработки всех событий по их идентификаторам
void on_event(int id)
{
	if (id == EVENT_PLAY_SOUND)
	{
		sound->stop();
		sound->play();
	}

	if (id == EVENT_CONSOLE_MESSAGE)
	{
		Console::onscreenMessageLine(vec4_blue, "A message.");
	}

	// ...
}

// создаём трек для событий
AnimationTrackPtr event_track = AnimationTrack::create();

// создаём трек для событий
AnimationCurveIntPtr event_curve = AnimationCurveInt::create();
event_curve->addKey(1.25f, EVENT_PLAY_SOUND);
event_curve->addKey(2.07f, EVENT_CONSOLE_MESSAGE);
event_curve->addKey(2.75f, EVENT_PLAY_SOUND);
event_track->setEventCurve(event_curve);

// добавляем трек в воспроизведение
playback->addLayer(event_track);

// добавляем обработчик обратного вызова для обработки событий
event_track->addEventCallback(MakeCallback(on_event));


```


### Возвращаемое значение

Текущая кривая событий для трека.
---

## AnimationTrack ( )

Конструктор. Создаёт пустой трек с настройками по умолчанию.
## AnimationTrack ( const char * name )

Конструктор. Создаёт пустой трек с настройками по умолчанию и указанным именем.
### Аргументы

- *const char ** **name** - Имя трека анимации.

## void copy ( const Ptr < AnimationTrack > & track )

Копирует все данные из указанного исходного трека в этот трек.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationTrack](../../../../api/library/animations/timeline/class.animationtrack_cpp.md)> &* **track** - Исходный трек анимации.

## void clear ( )

Очищает трек анимации, удаляя из него все объекты анимации и модификаторы. Этот метод также сбрасывает длительность трека до 0.
## bool containsObject ( const Ptr < AnimationObject > & anim_obj )

Возвращает значение, указывающее, содержит ли трек анимации указанный [animation object](../../../../principles/animations/index.md#animation_object).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationObject](../../../../api/library/animations/timeline/class.animationobject_cpp.md)> &* **anim_obj** - Объект анимации для проверки.

### Возвращаемое значение

true, если воспроизведение анимации содержит указанный объект анимации; иначе false.
## Ptr < AnimationObject > getObject ( int index ) const

Возвращает [animation object](../../../../principles/animations/index.md#animation_object) по его индексу.
### Аргументы

- *int* **index** - Индекс объекта анимации.

### Возвращаемое значение

Объект анимации с указанным индексом.
## int addObject ( const Ptr < AnimationObject > & anim_obj )

Добавляет указанный [animation object](../../../../principles/animations/index.md#animation_object) в трек.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationObject](../../../../api/library/animations/timeline/class.animationobject_cpp.md)> &* **anim_obj** - Объект анимации для добавления.

### Возвращаемое значение

Индекс нового добавленного объекта анимации при успехе; иначе -1.
## void removeObject ( const Ptr < AnimationObject > & anim_obj )

Удаляет указанный [animation object](../../../../principles/animations/index.md#animation_object) вместе со всеми модификаторами, добавленными для него.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationObject](../../../../api/library/animations/timeline/class.animationobject_cpp.md)> &* **anim_obj** - Объект анимации для удаления.

## void addObjectModifier ( const Ptr < AnimationObject > & anim_obj , const Ptr < AnimationModifier > & modifier )

Добавляет указанный [modifier](../../../../principles/animations/index.md#animation_modifier) к указанному [animation object](../../../../principles/animations/index.md#animation_object) для управления изменениями определённого параметра во времени.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationObject](../../../../api/library/animations/timeline/class.animationobject_cpp.md)> &* **anim_obj** - Целевой объект анимации, к которому следует добавить модификатор.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationModifier](../../../../api/library/animations/timeline/class.animationmodifier_cpp.md)> &* **modifier** - Модификатор анимации для добавления.

## bool updateObjectModifier ( const Ptr < AnimationObject > & anim_obj , const Ptr < AnimationModifier > & modifier )

Обновляет указанный [modifier](../../../../principles/animations/index.md#animation_modifier) для указанного [animation object](../../../../principles/animations/index.md#animation_object).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationObject](../../../../api/library/animations/timeline/class.animationobject_cpp.md)> &* **anim_obj** - Целевой объект анимации, к которому следует добавить модификатор.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationModifier](../../../../api/library/animations/timeline/class.animationmodifier_cpp.md)> &* **modifier** - Новый исходный модификатор анимации для использования.

### Возвращаемое значение

true, если указанный модификатор был успешно обновлён для объекта анимации; иначе false.
## void removeObjectModifier ( const Ptr < AnimationObject > & anim_obj , const Ptr < AnimationModifier > & modifier )

Удаляет указанный [modifier](../../../../principles/animations/index.md#animation_modifier) из указанного [animation object](../../../../principles/animations/index.md#animation_object).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationObject](../../../../api/library/animations/timeline/class.animationobject_cpp.md)> &* **anim_obj** - Целевой объект анимации, из которого следует удалить модификатор.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationModifier](../../../../api/library/animations/timeline/class.animationmodifier_cpp.md)> &* **modifier** - Модификатор анимации для удаления.

## int getObjectModifiers ( const Ptr < AnimationObject > & anim_obj , Vector < Ptr < AnimationModifier >> & OUT_out_modifiers ) const

Собирает все модификаторы для указанного [animation object](../../../../principles/animations/index.md#animation_object) и помещает их в буфер **out_modifiers**.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationObject](../../../../api/library/animations/timeline/class.animationobject_cpp.md)> &* **anim_obj** - Объект анимации.
- *[Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationModifier](../../../../api/library/animations/timeline/class.animationmodifier_cpp.md)>> &* **OUT_out_modifiers** - Выходной буфер для списка всех модификаторов указанного объекта. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

### Возвращаемое значение

Количество модификаторов для указанного объекта.
## void addObjectModifier ( const char * anim_obj_name , const Ptr < AnimationModifier > & modifier )

Добавляет указанный [modifier](../../../../principles/animations/index.md#animation_modifier) к [animation object](../../../../principles/animations/index.md#animation_object) с указанным именем для управления изменениями определённого параметра во времени.
### Аргументы

- *const char ** **anim_obj_name** - Имя целевого объекта анимации, к которому следует добавить модификатор.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationModifier](../../../../api/library/animations/timeline/class.animationmodifier_cpp.md)> &* **modifier** - Модификатор анимации для добавления.

## void addSingletonModifier ( const Ptr < AnimationModifier > & modifier )

Добавляет указанный одиночный [modifier](../../../../principles/animations/index.md#animation_modifier) анимации для управления изменениями определённого параметра какого-либо синглтон-класса движка, например *[Physics](../../../../api/library/physics/class.physics_cpp.md), [Render](../../../../api/library/rendering/class.render_cpp.md)* и т.п.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationModifier](../../../../api/library/animations/timeline/class.animationmodifier_cpp.md)> &* **modifier** - Одиночный модификатор анимации для добавления.

## bool updateSingletonModifier ( const Ptr < AnimationModifier > & modifier )

Обновляет указанный одиночный [modifier](../../../../principles/animations/index.md#animation_modifier) анимации, используемый для управления изменениями определённого параметра какого-либо синглтон-класса движка, например *[Physics](../../../../api/library/physics/class.physics_cpp.md), [Render](../../../../api/library/rendering/class.render_cpp.md)* и т.п.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationModifier](../../../../api/library/animations/timeline/class.animationmodifier_cpp.md)> &* **modifier** - Одиночный модификатор анимации для обновления.

### Возвращаемое значение

true, если указанный одиночный модификатор был успешно обновлён; иначе false.
## void removeSingletonModifier ( const Ptr < AnimationModifier > & modifier )

Удаляет указанный одиночный [modifier](../../../../principles/animations/index.md#animation_modifier) анимации из трека.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationModifier](../../../../api/library/animations/timeline/class.animationmodifier_cpp.md)> &* **modifier** - Одиночный модификатор анимации для удаления.

## int getSingletonModifiers ( Vector < Ptr < AnimationModifier >> & OUT_out_modifiers ) const

Собирает все одиночные модификаторы анимации трека и помещает их в буфер **out_modifiers**.
### Аргументы

- *[Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../../api/library/common/class.ptr_cpp.md)<[AnimationModifier](../../../../api/library/animations/timeline/class.animationmodifier_cpp.md)>> &* **OUT_out_modifiers** - Выходной буфер для списка всех одиночных модификаторов трека. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

### Возвращаемое значение

Количество одиночных модификаторов анимации трека.
## Ptr < AnimationFrame > getFrame ( float time )

Возвращает [animation frame](../../../../principles/animations/index.md#animation_frame) для указанного момента времени. Кадр можно представить как вертикальный срез значений всех треков и модификаторов, проигрываемых в указанный момент.
### Аргументы

- *float* **time** - Время (в секундах), для которого необходимо получить кадр.

### Возвращаемое значение

Кадр анимации для указанного времени.
## Ptr < AnimationFrame > getFrameByNormalizedTime ( float time )

Возвращает [animation frame](../../../../principles/animations/index.md#animation_frame) для указанного момента времени (нормализованного). Кадр можно представить как вертикальный срез значений всех треков и модификаторов, проигрываемых в указанный момент.
### Аргументы

- *float* **time** - Нормализованное значение времени (в диапазоне [0.0f, 1.0f]), для которого необходимо получить кадр.

### Возвращаемое значение

Кадр анимации для указанного времени.
