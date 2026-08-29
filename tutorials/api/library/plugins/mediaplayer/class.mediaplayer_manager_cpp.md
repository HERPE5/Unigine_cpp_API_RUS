# Unigine::Plugins::MediaPlayer::Manager Class (CPP)

**Header:** #include <plugins/Unigine/MediaPlayer/UnigineMediaPlayer.h>

> **Notice:** Этот класс является синглтоном.


**Manager** — это класс-синглтон, предоставляющий основной интерфейс плагина *MediaPlayer*. Он управляет жизненным циклом источников видео и предоставляет служебные функции для работы с медиафайлами.


Плагин использует библиотеку *libVLC* для декодирования видео и отрисовки кадров в GPU-текстуры, которые можно использовать в материалах UNIGINE.

 Лучшая практикаДля упрощённого управления воспроизведением видео используйте готовый **[VideoSourceComponent](../../../../api/library/plugins/mediaplayer/class.videosourcecomponent_cpp.md)**. Он позволяет добавить видео на объект сцены без написания кода — достаточно указать путь к файлу или URL, выбрать поверхность объекта и задать слот текстуры в материале. Компонент автоматически загружает видео, применяет текстуру и запускает воспроизведение при инициализации.
### См. также


- **[MediaPlayer::VideoSource](../../../../api/library/plugins/mediaplayer/class.mediaplayer_videosource_cpp.md)**
- **[VideoSourceComponent](../../../../api/library/plugins/mediaplayer/class.videosourcecomponent_cpp.md)**


## Unigine::Plugins::MediaPlayer::Manager Class

---

## static Manager * get ( )

Возвращает экземпляр-синглтон менеджера MediaPlayer. Экземпляр автоматически создаётся при загрузке плагина и уничтожается при выгрузке.
### Возвращаемое значение

Указатель на экземпляр Manager, или nullptr, если плагин не загружен.
## String getFileURL ( const char * path )

Преобразует локальный путь к файлу в URL **file:///**, который можно передать методу *[load()](../../../...md#load_cstr_int_VideoSourcePtr)*. Путь разрешается в абсолютный с использованием [UNIGINE File System](../../../../principles/filesystem/index_cpp.md).
### Аргументы

- *const char ** **path** - Относительный или абсолютный путь к локальному медиафайлу.

### Возвращаемое значение

URL файла в формате `file:///absolute/path/to/file`.
## VideoSource * load ( const char * URL , int flags = Texture::SAMPLER_FILTER_POINT )

Загружает медиа по указанному URL и создаёт новый экземпляр VideoSource. Источник видео должен быть освобождён с помощью *[unload()](../../../...md#unload_VideoSourcePtr_void)*, когда он больше не нужен.
### Аргументы

- *const char ** **URL** - URL медиа. Может быть URL **file:///** (используйте *[getFileURL()](../../../...md#getFileURL_cstr_String)* для преобразования локальных путей), **http://**, **https://**, **rtsp://** или любой другой протокол, поддерживаемый [libVLC](https://wiki.videolan.org/Documentation:Streaming_HowTo_New/#Streaming). <details> <summary>Примеры распространённых URL VLC</summary> - **Поток HTTP** (с другого экземпляра VLC) - `http://192.168.1.100:8080` - `http://localhost:8080/` (при воспроизведении на той же машине) - **RTSP** (IP-камеры/системы видеонаблюдения) - `rtsp://192.168.1.200:554/live` (без авторизации) - `rtsp://admin:password@192.168.1.200:554/stream` (с учётными данными) - **IPTV / плейлисты M3U** - `http://example.com/path/to/playlist.m3u` (прямой URL файла) - `http://example.com/path/to/stream.m3u8` (поток HLS) - **Локальные файлы / сетевые ресурсы** - `file:///C:/Users/YourName/Videos/movie.mp4` (локальный файл) - `smb://server/share/video.mp4` (сетевой ресурс). </details>
- *int* **flags** - Флаги сэмплера текстуры для выходной текстуры. По умолчанию [SAMPLER_FILTER_POINT](../../../../api/library/rendering/class.texture_cpp.md#SAMPLER_FILTER_POINT).

### Возвращаемое значение

Указатель на созданный экземпляр VideoSource, или nullptr, если загрузка не удалась.
## void unload ( VideoSource * file )

Выгружает указанный источник видео и освобождает все связанные ресурсы. После вызова этого метода указатель VideoSource становится недействительным и не должен использоваться.
### Аргументы

- *VideoSource ** **file** - Указатель на выгружаемый экземпляр [VideoSource](../../../../api/library/plugins/mediaplayer/class.mediaplayer_videosource_cpp.md).
