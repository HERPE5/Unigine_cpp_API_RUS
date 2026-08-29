# VideoSourceComponent


**VideoSourceComponent** — это [property](../../../../principles/properties/index.md), предоставляющее способ добавления воспроизведения видео на объекты в редакторе UNIGINE без написания кода. Оно автоматически загружает медиа, применяет текстуру видео к указанной поверхности и управляет жизненным циклом плеера.


> **Notice:** Это свойство добавляется автоматически при загрузке плагина. После активации плагина **VideoSourceComponent** становится доступным в редакторе и может быть добавлено к любому объекту сцены.


Свойство поддерживает два режима работы:


- **Уникальный режим** (unique = true): компонент создаёт собственный экземпляр медиаплеера и загружает медиа из файла или URL.
- **Общий режим** (unique = false): компонент переиспользует текстуру от другого VideoSourceComponent, позволяя нескольким объектам отображать одно и то же видео, оптимизируя производительность и устраняя дополнительные затраты на декодирование.


Чтобы использовать компонент:


1. Добавьте компонент к объекту (например, плоскости [ObjectMeshStatic](../../../../api/library/objects/class.objectmeshstatic_cpp.md)).
2. Задайте *surface_name* — имя поверхности, на которой должно отображаться видео.
3. Задайте *texture_name* — имя слота текстуры материала (например, *"albedo"*).
4. Настройте источник медиа (путь к файлу или URL) и параметры воспроизведения.


### Параметры компонента


| Параметр | Тип | По умолчанию | Описание |
|---|---|---|---|
| unique | bool | true | Режим компонента. Если true, создаёт собственный медиаплеер. Если false, переиспользует текстуру из указанного параметра *source*. |
| file | bool | true | Тип источника медиа. Если true, загружает из *file_path*. Если false, загружает из *url*. |
| file_path | String | "" | Путь к локальному медиафайлу. Используется, когда *file = true*. |
| url | String | "" | URL для сетевого медиапотока (*http://*, *https://*, *rtsp://* и другие протоколы, поддерживаемые [libVLC](https://wiki.videolan.org/Documentation:Streaming_HowTo_New/#Streaming)). Используется, когда *file = false*. |
| sound | bool | false | Включает воспроизведение звука. |
| start_from | float | 0.0 | Начальная позиция воспроизведения в диапазоне [0.0; 1.0]. |
| rate | float | 1.0 | Множитель скорости воспроизведения. |
| loop | bool | false | Включает зацикленное воспроизведение. |
| texture_filter | int | 0 | Режим фильтрации текстуры: [POINT](../../../../api/library/rendering/class.texture_cpp.md#SAMPLER_FILTER_POINT), [LINEAR](../../../../api/library/rendering/class.texture_cpp.md#SAMPLER_FILTER_LINEAR), [BILINEAR](../../../../api/library/rendering/class.texture_cpp.md#SAMPLER_FILTER_BILINEAR), [TRILINEAR](../../../../api/library/rendering/class.texture_cpp.md#SAMPLER_FILTER_TRILINEAR). |
| source | Node | null | Ссылка на узел с **VideoSourceComponent** для совместного использования текстуры (только в общем режиме). |
| surface_name | String | "" | Имя поверхности объекта для текстуры видео. |
| texture_name | String | "" | Имя слота текстуры материала (например, "albedo"). |


### См. также


- **[MediaPlayer::Manager](../../../../api/library/plugins/mediaplayer/class.mediaplayer_manager_cpp.md)**
- **[MediaPlayer::VideoSource](../../../../api/library/plugins/mediaplayer/class.mediaplayer_videosource_cpp.md)**
