# Unigine.Viewport Class (CPP)

**Header:** #include <UnigineViewport.h>


Класс **Viewport** используется для рендеринга сцены с указанными настройками.


Основные варианты использования класса Viewport:


1. Интеграция движка со сторонним рендерером (или наоборот) и рендеринг изображения в произвольное место (с помощью метода [render()](#render_Camera_void)): во внешнюю библиотеку, интерфейс [CustomSystemProxy](../../../api/library/engine/class.customsystemproxy_cpp.md), интерфейс [RenderTarget](../../../api/library/rendering/class.rendertarget_cpp.md) (абстракция буферов кадра) и т.д.

  - Чтобы рендерить изображение в интерфейс [RenderTarget](../../../api/library/rendering/class.rendertarget_cpp.md), выполните следующее: ```cpp // моно-рендеринг ViewportPtr viewport; TexturePtr texture; CameraPtr camera; int AppWorldLogic::init() { viewport = Viewport::create(); texture = Texture::create(); // создаём рендер-таргет 512 x 512 texture->create2D(512, 512, Texture::FORMAT_RGBA8, Texture::FORMAT_USAGE_RENDER); camera = Camera::create(); return 1; } int AppWorldLogic::update() { // задаём матрицы modelview и projection экземпляру камеры // ... // рендеринг RenderTargetPtr render_target = Render::getTemporaryRenderTarget(); render_target->bindColorTexture(0, texture); render_target->enable(); { viewport->render(camera); } render_target->disable(); render_target->unbindAll(); Render::releaseTemporaryRenderTarget(render_target); return 1; } ``` Чтобы рендерить изображение в интерфейс [RenderTarget](../../../api/library/rendering/class.rendertarget_cpp.md) в стереорежиме, выполните следующее: ```cpp // стереорендеринг ViewportPtr viewport; TexturePtr left_texture; TexturePtr right_texture; CameraPtr left_eye; CameraPtr right_eye; int AppWorldLogic::init() { viewport = Viewport::create(); left_texture = Texture::create(); right_texture = Texture::create(); // создаём два рендер-таргета 512 x 512, по одному для каждого глаза left_texture->create2D(512, 512, Texture::FORMAT_RGBA8, Texture::FORMAT_USAGE_RENDER); right_texture->create2D(512, 512, Texture::FORMAT_RGBA8, Texture::FORMAT_USAGE_RENDER); left_eye = Camera::create(); right_eye = Camera::create(); return 1; } int AppWorldLogic::update() { // задаём матрицы modelview и projection экземпляру камеры // ... // рендеринг RenderTargetPtr render_target = Render::getTemporaryRenderTarget(); render_target->bindColorTexture(0, left_texture); render_target->bindColorTexture(1, right_texture); render_target->enable(); { // используем материал "post_stereo_separate", чтобы рендерить в обе текстуры viewport->renderStereo(left_eye, right_eye, "Unigine::post_stereo_separate"); } render_target->disable(); render_target->unbindAll(); Render::releaseTemporaryRenderTarget(render_target); return 1; } ```
  - Чтобы рендерить изображение в интерфейс [CustomSystemProxy](../../../api/library/engine/class.customsystemproxy_cpp.md), см. примеры в разделе [3rd Party](../../../sdk/api_samples/third_party/qt.md): `source -> samples -> 3rdparty -> ViewportQt`. > **Notice:** Пример **ViewportQt** доступен только для редакций Engineering и Sim UNIGINE SDK.
2. Рендеринг сцены в [texture](../../../api/library/rendering/class.texture_cpp.md) (данные остаются в памяти GPU).

  - Чтобы рендерить сцену в интерфейс [Texture](../../../api/library/rendering/class.texture_cpp.md), используйте следующие методы: ```cpp ViewportPtr viewport; TexturePtr texture; CameraPtr camera; int AppWorldLogic::init() { // инициализация viewport = Viewport::create(); texture = Texture::create(); // создаём рендер-таргет 512 x 512 texture->create2D(512, 512, Texture::FORMAT_RGBA8, Texture::FORMAT_USAGE_RENDER); camera = Camera::create(); return 1; } int AppWorldLogic::update() { // задаём матрицы modelview и projection экземпляру камеры // ... // рендеринг // // сохраняем текущее состояние рендеринга и очищаем его RenderState::saveState(); RenderState::clearStates(); { viewport->renderTexture2D(camera, texture); } RenderState::restoreState(); return 1; } ```

    - *[renderTexture2D(camera,texture)](#renderTexture2D_Camera_Texture_void)*
    - *[renderTexture2D(camera,texture,width,height,hdr)](#renderTexture2D_Camera_Texture_int_int_int_void)*
    - *[renderTextureCube(camera,texture,local_space)](#renderTextureCube_Camera_Texture_int_void)*
    - *[renderTextureCube(camera,texture,size,hdr,local_space)](#renderTextureCube_Camera_Texture_int_int_int_void)*
3. Рендеринг узла в [texture](../../../api/library/rendering/class.texture_cpp.md) (данные остаются в памяти GPU).

  - Чтобы рендерить узел (или узлы) в интерфейс [Texture](../../../api/library/rendering/class.texture_cpp.md), используйте следующие методы:

    - *[renderNodeTexture2D(camera,node,texture)](#renderNodeTexture2D_Camera_Node_Texture_void)*
    - *[renderNodeTexture2D(camera,node,texture,width,height,hdr)](#renderNodeTexture2D_Camera_Node_Texture_int_int_int_void)*
    - *[renderNodesTexture2D(camera,nodes,texture)](#renderNodesTexture2D_Camera_VECNode_Texture_void)*
    - *[renderNodesTexture2D(camera,nodes,texture,width,height,hdr)](#renderNodesTexture2D_Camera_VECNode_Texture_int_int_int_void)*


Вы можете подписываться на события до и после любого прохода рендеринга с помощью **[getEvent***()](../../...md#getEventBegin_Event)**: таким образом, получая доступ к промежуточному состоянию буферов рендеринга и матриц. Некоторые из них доступны только для чтения, но большинство можно изменять на лету. Обработчик события может получить указатель на [Renderer](../../../api/library/rendering/class.renderer_cpp.md).


![](render_callbacks.jpg)


Благодаря этой возможности вы можете получить прямой доступ к G-Buffer, SSAO, источникам света или любому другому эффекту. Ещё один пример: вы можете создать пользовательский постпроцесс и применить его перед TAA, тем самым получив корректное сглаженное изображение в результате. Вы даже можете создавать собственные пользовательские источники света, декали и т.д. Эта возможность также может быть полезна для пользовательских видов датчиков.


Класс Viewport имеет различные режимы рендеринга: [RENDER_DEPTH](#RENDER_DEPTH) (только глубина), [RENDER_DEPTH_GBUFFER](#RENDER_DEPTH_GBUFFER) (глубина + G-buffer), [RENDER_DEPTH_GBUFFER_FINAL](#RENDER_DEPTH_GBUFFER_FINAL) (глубина + G-buffer + итоговое изображение). Это может дать дополнительный прирост производительности, если, например, требуется только информация о глубине.


> **Notice:** Чтобы установить любой вьюпорт в качестве главного, используйте метод [setViewport()](../../../api/library/rendering/class.render_cpp.md#setViewport_Viewport_void) класса *Render*.
>
>
> **Один вьюпорт должен использоваться с одной камерой**, иначе это может вызвать визуальные артефакты. Чтобы избежать артефактов при использовании нескольких камер с одним вьюпортом, все постэффекты должны быть отключены с помощью метода *[setSkipFlags()](#setSkipFlags_int_void)* с флагом *[SKIP_POSTEFFECTS](../../...md#SKIP_POSTEFFECTS)*. См. пример использования ниже.


<details>
<summary>Пример: один вьюпорт и несколько камер | Скрыть</summary>

```cpp
void setupMultipleCamerasWithSingleViewport()
{
    // создаём общий вьюпорт для нескольких камер
    ViewportPtr shared_viewport = Viewport::create();

    // КРИТИЧНО: отключаем постэффекты, чтобы избежать визуальных артефактов
    // при использовании нескольких камер с одним вьюпортом
    shared_viewport->setSkipFlags(Viewport::SKIP_POSTEFFECTS);

    shared_viewport->setNodeLightUsage(Viewport::USAGE_WORLD_LIGHT);

    // создаём несколько камер
    CameraPtr camera1 = Camera::create();
    CameraPtr camera2 = Camera::create();

    // размещаем камеры по-разному
    camera1->setPosition(Vec3(0.0f, 0.0f, 5.0f));
    camera2->setPosition(Vec3(10.0f, 0.0f, 5.0f));

    // создаём текстуры для вывода каждой камеры
    TexturePtr texture1 = Texture::create();
    TexturePtr texture2 = Texture::create();

    texture1->create2D(1920, 1080, Texture::FORMAT_RGBA8,
        Texture::FORMAT_USAGE_RENDER);
    texture2->create2D(1920, 1080, Texture::FORMAT_RGBA8,
        Texture::FORMAT_USAGE_RENDER);

    // рендерим с разных камер, используя один и тот же вьюпорт
    // постэффекты отключены, поэтому артефактов не будет
    shared_viewport->renderTexture2D(camera1, texture1);
    shared_viewport->renderTexture2D(camera2, texture2);
}

```

</details>


### См. также


- Примеры на C++:

  -
  -
  -
  -
- Пример использования на C++/C#: [Creating Mirrors Using Viewports (Rendering to Texture) or a Standard Material](../../../code/usage/mirrors_viewports_materials/index_cpp.md)


## Viewport Class

### Методы класса

## void setNodeLightUsage ( int usage )

Задаёт новый тип освещения рендерящегося узла.
### Аргументы

- *int* **usage** - Тип освещения. Может быть одним из следующих:

  - 0 - *[USAGE_WORLD_LIGHT](../../...md#USAGE_WORLD_LIGHT)* (использовать освещение от [LightWorld](../../../api/library/lights/class.lightworld_cpp.md), заданного в текущем загруженном мире).
  - 1 - *[USAGE_AUX_LIGHT](../../...md#USAGE_AUX_LIGHT)* (использовать освещение от вспомогательной виртуальной сцены, содержащей один LightWorld с углами наклона 45 градусов по всем осям, рассеивание не используется).
  - 2 - *[USAGE_NODE_LIGHT](../../...md#USAGE_NODE_LIGHT)* (использовать освещение узла).

## int getNodeLightUsage () const

Возвращает текущий тип освещения рендерящегося узла.
### Возвращаемое значение

Текущий тип освещения. Может быть одним из следующих:
- 0 - *[USAGE_WORLD_LIGHT](../../...md#USAGE_WORLD_LIGHT)* (использовать освещение от [LightWorld](../../../api/library/lights/class.lightworld_cpp.md), заданного в текущем загруженном мире).
- 1 - *[USAGE_AUX_LIGHT](../../...md#USAGE_AUX_LIGHT)* (использовать освещение от вспомогательной виртуальной сцены, содержащей один LightWorld с углами наклона 45 градусов по всем осям, рассеивание не используется).
- 2 - *[USAGE_NODE_LIGHT](../../...md#USAGE_NODE_LIGHT)* (использовать освещение узла).


## void setStereoOffset ( float offset )

Задаёт новое смещение виртуальной камеры (смещение после перспективной проекции).
### Аргументы

- *float* **offset** - Смещение виртуальной камеры, в единицах.

## float getStereoOffset () const

Возвращает текущее смещение виртуальной камеры (смещение после перспективной проекции).
### Возвращаемое значение

Текущее смещение виртуальной камеры, в единицах.
## void setStereoRadius ( float radius )

Задаёт новый радиус стерео - половину дистанции разделения между камерами (т.е. между глазами).
### Аргументы

- *float* **radius** - Радиус стерео, в единицах. Если передано отрицательное значение, вместо него будет использовано 0.

## float getStereoRadius () const

Возвращает текущий радиус стерео - половину дистанции разделения между камерами (т.е. между глазами).
### Возвращаемое значение

Текущий радиус стерео, в единицах. Если передано отрицательное значение, вместо него будет использовано 0.
## void setStereoDistance ( float distance )

Задаёт новое фокусное расстояние для стереорендеринга (расстояние в мировом пространстве до точки, в которой совмещаются два вида, т.е. до плоскости нулевого параллакса).
### Аргументы

- *float* **distance** - Фокусное расстояние, в единицах.

## float getStereoDistance () const

Возвращает текущее фокусное расстояние для стереорендеринга (расстояние в мировом пространстве до точки, в которой совмещаются два вида, т.е. до плоскости нулевого параллакса).
### Возвращаемое значение

Текущее фокусное расстояние, в единицах.
## bool isStereo () const

Возвращает текущее значение, указывающее, включён ли стереорендеринг для текущего вьюпорта (установлен один из [stereo modes](../../../api/library/rendering/class.render_cpp.md#VIEWPORT_MODE_STEREO_ANAGLYPH)).
### Возвращаемое значение

**true**, если стереорендеринг для текущего вьюпорта (один из [stereo modes](../../../api/library/rendering/class.render_cpp.md#VIEWPORT_MODE_STEREO_ANAGLYPH)) включён; иначе **false**.
## bool isPanorama () const

Возвращает текущее значение, указывающее, включён ли панорамный рендеринг.
### Возвращаемое значение

**true**, если панорамный рендеринг включён; иначе **false**.
## void setRenderMode ( int mode )

Задаёт новый режим рендеринга. Режим определяет набор рендерящихся буферов.
### Аргументы

- *int* **mode** - Режим рендеринга, один из следующих:

  - *[RENDER_DEPTH](../../...md#RENDER_DEPTH)*
  - *[RENDER_DEPTH_GBUFFER](../../...md#RENDER_DEPTH_GBUFFER)*
  - *[RENDER_DEPTH_GBUFFER_FINAL](../../...md#RENDER_DEPTH_GBUFFER_FINAL)*

## int getRenderMode () const

Возвращает текущий режим рендеринга. Режим определяет набор рендерящихся буферов.
### Возвращаемое значение

Текущий режим рендеринга, один из следующих:
- *[RENDER_DEPTH](../../...md#RENDER_DEPTH)*
- *[RENDER_DEPTH_GBUFFER](../../...md#RENDER_DEPTH_GBUFFER)*
- *[RENDER_DEPTH_GBUFFER_FINAL](../../...md#RENDER_DEPTH_GBUFFER_FINAL)*


## void setMode ( Render::VIEWPORT_MODE mode )

Задаёт новый режим рендеринга для текущего вьюпорта.
### Аргументы

- *[Render::VIEWPORT_MODE](../../../api/library/rendering/class.render_cpp.md#VIEWPORT_MODE)* **mode** - Режим рендеринга, устанавливаемый для текущего вьюпорта. Может быть одним из [stereo](../../../api/library/rendering/class.render_cpp.md#VIEWPORT_MODE_STEREO_ANAGLYPH) или [panoramic](../../../api/library/rendering/class.render_cpp.md#VIEWPORT_MODE_PANORAMA_CURVED_180) режимов или [default](../../../api/library/rendering/class.render_cpp.md#VIEWPORT_MODE_DEFAULT).

## Render::VIEWPORT_MODE getMode () const

Возвращает текущий режим рендеринга для текущего вьюпорта.
### Возвращаемое значение

Текущий режим рендеринга, установленный для текущего вьюпорта. Может быть одним из [stereo](../../../api/library/rendering/class.render_cpp.md#VIEWPORT_MODE_STEREO_ANAGLYPH) или [panoramic](../../../api/library/rendering/class.render_cpp.md#VIEWPORT_MODE_PANORAMA_CURVED_180) режимов или [default](../../../api/library/rendering/class.render_cpp.md#VIEWPORT_MODE_DEFAULT).
## void setSkipFlags ( int flags )

Задаёт новый набор [skip flags](#SKIP_SHADOWS) для текущего вьюпорта.
### Аргументы

- *int* **flags** - Набор [skip flags](#SKIP_SHADOWS) для текущего вьюпорта.

## int getSkipFlags () const

Возвращает текущий набор [skip flags](#SKIP_SHADOWS) для текущего вьюпорта.
### Возвращаемое значение

Текущий набор [skip flags](#SKIP_SHADOWS) для текущего вьюпорта.
## void setFirstFrame ( int frame )

Задаёт новое значение, указывающее, включён ли первый кадр поверх текущего кадра.
### Аргументы

- *int* **frame** - Значение, указывающее, включён ли первый кадр поверх текущего кадра: 1 для флага первого кадра; иначе 0.

## int getFirstFrame () const

Возвращает текущее значение, указывающее, включён ли первый кадр поверх текущего кадра.
### Возвращаемое значение

Текущее значение, указывающее, включён ли первый кадр поверх текущего кадра: 1 для флага первого кадра; иначе 0.
## void setAspectCorrection ( bool correction )

Задаёт новое значение, указывающее, включена ли коррекция соотношения сторон для текущего вьюпорта.
### Аргументы

- *bool* **correction** - **true**, чтобы включить коррекцию соотношения сторон; **false** - чтобы отключить её.

## bool isAspectCorrection () const

Возвращает текущее значение, указывающее, включена ли коррекция соотношения сторон для текущего вьюпорта.
### Возвращаемое значение

**true**, если коррекция соотношения сторон включена; иначе **false**.
## int getID () const

Возвращает текущий ID вьюпорта.
### Возвращаемое значение

Текущий ID вьюпорта.
## void setPanoramaFisheyeFov ( float fov )

Задаёт новый угол поля зрения, используемый для панорамного режима рендеринга.
### Аргументы

- *float* **fov** - Угол поля зрения, используемый для панорамного режима рендеринга, в градусах.

## float getPanoramaFisheyeFov () const

Возвращает текущий угол поля зрения, используемый для панорамного режима рендеринга.
### Возвращаемое значение

Текущий угол поля зрения, используемый для панорамного режима рендеринга, в градусах.
## void setEnvironmentTexture ( const Ptr < Texture >& texture )

Задаёт новую кубическую текстуру, определяющую цвет окружения.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)>&* **texture** - Кубическая текстура, определяющая цвет окружения.

## Ptr < Texture > getEnvironmentTexture () const

Возвращает текущую кубическую текстуру, определяющую цвет окружения.
### Возвращаемое значение

Текущая кубическая текстура, определяющая цвет окружения.
## void setUseTAAOffset ( bool taaoffset )

Задаёт новое значение, указывающее, включён ли пропуск проверки режима рендеринга для использования TAA. Может использоваться для обеспечения корректного вычисления TAA, когда режим рендеринга для *Viewport* установлен в *[RENDER_DEPTH](../../...md#RENDER_DEPTH)*.
### Аргументы

- *bool* **taaoffset** - **true**, чтобы включить пропуск проверки режима рендеринга при использовании TAA; **false** - чтобы отключить это.

## bool isUseTAAOffset () const

Возвращает текущее значение, указывающее, включён ли пропуск проверки режима рендеринга для использования TAA. Может использоваться для обеспечения корректного вычисления TAA, когда режим рендеринга для *Viewport* установлен в *[RENDER_DEPTH](../../...md#RENDER_DEPTH)*.
### Возвращаемое значение

**true**, если пропуск проверки режима рендеринга при использовании TAA включён; иначе **false**.
## void setLifetime ( int lifetime )

Задаёт новое значение, указывающее, сколько кадров временные ресурсы вьюпорта доступны после того, как вьюпорт прекращает рендеринг.
### Аргументы

- *int* **lifetime** - Количество кадров, в течение которых временные ресурсы вьюпорта доступны после того, как вьюпорт прекращает рендеринг

## int getLifetime () const

Возвращает текущее значение, указывающее, сколько кадров временные ресурсы вьюпорта доступны после того, как вьюпорт прекращает рендеринг.
### Возвращаемое значение

Текущее количество кадров, в течение которых временные ресурсы вьюпорта доступны после того, как вьюпорт прекращает рендеринг
## Event<> getEventBegin () const

событие, генерируемое перед началом рендеринга кадра. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Begin
void begin_event_handler()
{
	Log::message("\Обработка события Begin\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections begin_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBegin().connect(begin_event_connections, begin_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBegin().connect(begin_event_connections, []() {
		Log::message("\Обработка события Begin (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
begin_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection begin_event_connection;

// подписываемся на событие Begin с функцией-обработчиком, сохраняя соединение
publisher->getEventBegin().connect(begin_event_connection, begin_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
begin_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
begin_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Begin через соединение
begin_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события Begin, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события Begin\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBegin().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId begin_handler_id;

// подписываемся на событие Begin с лямбда-обработчиком, сохраняя идентификатор соединения
begin_handler_id = publisher->getEventBegin().connect(e_connections, []() {
		Log::message("\Обработка события Begin (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBegin().disconnect(begin_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Begin при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBegin().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBegin().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginEnvironment () const

событие, генерируемое перед этапом рендеринга Environment. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginEnvironment
void beginenvironment_event_handler()
{
	Log::message("\Обработка события BeginEnvironment\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginenvironment_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginEnvironment().connect(beginenvironment_event_connections, beginenvironment_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginEnvironment().connect(beginenvironment_event_connections, []() {
		Log::message("\Обработка события BeginEnvironment (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginenvironment_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginenvironment_event_connection;

// подписываемся на событие BeginEnvironment с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginEnvironment().connect(beginenvironment_event_connection, beginenvironment_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginenvironment_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginenvironment_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginEnvironment через соединение
beginenvironment_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginEnvironment, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginEnvironment\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginEnvironment().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginenvironment_handler_id;

// подписываемся на событие BeginEnvironment с лямбда-обработчиком, сохраняя идентификатор соединения
beginenvironment_handler_id = publisher->getEventBeginEnvironment().connect(e_connections, []() {
		Log::message("\Обработка события BeginEnvironment (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginEnvironment().disconnect(beginenvironment_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginEnvironment при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginEnvironment().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginEnvironment().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndEnvironment () const

событие, генерируемое после этапом рендеринга Environment. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndEnvironment
void endenvironment_event_handler()
{
	Log::message("\Обработка события EndEnvironment\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endenvironment_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndEnvironment().connect(endenvironment_event_connections, endenvironment_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndEnvironment().connect(endenvironment_event_connections, []() {
		Log::message("\Обработка события EndEnvironment (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endenvironment_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endenvironment_event_connection;

// подписываемся на событие EndEnvironment с функцией-обработчиком, сохраняя соединение
publisher->getEventEndEnvironment().connect(endenvironment_event_connection, endenvironment_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endenvironment_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endenvironment_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndEnvironment через соединение
endenvironment_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndEnvironment, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndEnvironment\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndEnvironment().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endenvironment_handler_id;

// подписываемся на событие EndEnvironment с лямбда-обработчиком, сохраняя идентификатор соединения
endenvironment_handler_id = publisher->getEventEndEnvironment().connect(e_connections, []() {
		Log::message("\Обработка события EndEnvironment (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndEnvironment().disconnect(endenvironment_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndEnvironment при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndEnvironment().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndEnvironment().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginShadows () const

событие, генерируемое перед этапом рендеринга теней. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginShadows
void beginshadows_event_handler()
{
	Log::message("\Обработка события BeginShadows\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginshadows_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginShadows().connect(beginshadows_event_connections, beginshadows_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginShadows().connect(beginshadows_event_connections, []() {
		Log::message("\Обработка события BeginShadows (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginshadows_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginshadows_event_connection;

// подписываемся на событие BeginShadows с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginShadows().connect(beginshadows_event_connection, beginshadows_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginshadows_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginshadows_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginShadows через соединение
beginshadows_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginShadows, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginShadows\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginShadows().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginshadows_handler_id;

// подписываемся на событие BeginShadows с лямбда-обработчиком, сохраняя идентификатор соединения
beginshadows_handler_id = publisher->getEventBeginShadows().connect(e_connections, []() {
		Log::message("\Обработка события BeginShadows (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginShadows().disconnect(beginshadows_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginShadows при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginShadows().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginShadows().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginWorldShadow () const

событие, генерируемое перед этапом рендеринга теней от источников света World. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginWorldShadow
void beginworldshadow_event_handler()
{
	Log::message("\Обработка события BeginWorldShadow\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginworldshadow_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginWorldShadow().connect(beginworldshadow_event_connections, beginworldshadow_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginWorldShadow().connect(beginworldshadow_event_connections, []() {
		Log::message("\Обработка события BeginWorldShadow (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginworldshadow_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginworldshadow_event_connection;

// подписываемся на событие BeginWorldShadow с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginWorldShadow().connect(beginworldshadow_event_connection, beginworldshadow_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginworldshadow_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginworldshadow_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginWorldShadow через соединение
beginworldshadow_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginWorldShadow, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginWorldShadow\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginWorldShadow().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginworldshadow_handler_id;

// подписываемся на событие BeginWorldShadow с лямбда-обработчиком, сохраняя идентификатор соединения
beginworldshadow_handler_id = publisher->getEventBeginWorldShadow().connect(e_connections, []() {
		Log::message("\Обработка события BeginWorldShadow (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginWorldShadow().disconnect(beginworldshadow_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginWorldShadow при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginWorldShadow().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginWorldShadow().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndWorldShadow () const

событие, генерируемое после этапом рендеринга теней от источников света World. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndWorldShadow
void endworldshadow_event_handler()
{
	Log::message("\Обработка события EndWorldShadow\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endworldshadow_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndWorldShadow().connect(endworldshadow_event_connections, endworldshadow_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndWorldShadow().connect(endworldshadow_event_connections, []() {
		Log::message("\Обработка события EndWorldShadow (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endworldshadow_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endworldshadow_event_connection;

// подписываемся на событие EndWorldShadow с функцией-обработчиком, сохраняя соединение
publisher->getEventEndWorldShadow().connect(endworldshadow_event_connection, endworldshadow_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endworldshadow_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endworldshadow_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndWorldShadow через соединение
endworldshadow_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndWorldShadow, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndWorldShadow\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndWorldShadow().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endworldshadow_handler_id;

// подписываемся на событие EndWorldShadow с лямбда-обработчиком, сохраняя идентификатор соединения
endworldshadow_handler_id = publisher->getEventEndWorldShadow().connect(e_connections, []() {
		Log::message("\Обработка события EndWorldShadow (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndWorldShadow().disconnect(endworldshadow_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndWorldShadow при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndWorldShadow().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndWorldShadow().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginProjShadow () const

событие, генерируемое перед этапом рендеринга теней от источников света Projected. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginProjShadow
void beginprojshadow_event_handler()
{
	Log::message("\Обработка события BeginProjShadow\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginprojshadow_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginProjShadow().connect(beginprojshadow_event_connections, beginprojshadow_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginProjShadow().connect(beginprojshadow_event_connections, []() {
		Log::message("\Обработка события BeginProjShadow (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginprojshadow_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginprojshadow_event_connection;

// подписываемся на событие BeginProjShadow с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginProjShadow().connect(beginprojshadow_event_connection, beginprojshadow_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginprojshadow_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginprojshadow_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginProjShadow через соединение
beginprojshadow_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginProjShadow, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginProjShadow\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginProjShadow().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginprojshadow_handler_id;

// подписываемся на событие BeginProjShadow с лямбда-обработчиком, сохраняя идентификатор соединения
beginprojshadow_handler_id = publisher->getEventBeginProjShadow().connect(e_connections, []() {
		Log::message("\Обработка события BeginProjShadow (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginProjShadow().disconnect(beginprojshadow_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginProjShadow при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginProjShadow().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginProjShadow().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndProjShadow () const

событие, генерируемое после этапом рендеринга теней от источников света Projected. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndProjShadow
void endprojshadow_event_handler()
{
	Log::message("\Обработка события EndProjShadow\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endprojshadow_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndProjShadow().connect(endprojshadow_event_connections, endprojshadow_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndProjShadow().connect(endprojshadow_event_connections, []() {
		Log::message("\Обработка события EndProjShadow (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endprojshadow_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endprojshadow_event_connection;

// подписываемся на событие EndProjShadow с функцией-обработчиком, сохраняя соединение
publisher->getEventEndProjShadow().connect(endprojshadow_event_connection, endprojshadow_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endprojshadow_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endprojshadow_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndProjShadow через соединение
endprojshadow_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndProjShadow, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndProjShadow\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndProjShadow().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endprojshadow_handler_id;

// подписываемся на событие EndProjShadow с лямбда-обработчиком, сохраняя идентификатор соединения
endprojshadow_handler_id = publisher->getEventEndProjShadow().connect(e_connections, []() {
		Log::message("\Обработка события EndProjShadow (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndProjShadow().disconnect(endprojshadow_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndProjShadow при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndProjShadow().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndProjShadow().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginOmniShadow () const

событие, генерируемое перед этапом рендеринга теней от источников света Omni. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginOmniShadow
void beginomnishadow_event_handler()
{
	Log::message("\Обработка события BeginOmniShadow\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginomnishadow_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginOmniShadow().connect(beginomnishadow_event_connections, beginomnishadow_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginOmniShadow().connect(beginomnishadow_event_connections, []() {
		Log::message("\Обработка события BeginOmniShadow (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginomnishadow_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginomnishadow_event_connection;

// подписываемся на событие BeginOmniShadow с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginOmniShadow().connect(beginomnishadow_event_connection, beginomnishadow_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginomnishadow_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginomnishadow_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginOmniShadow через соединение
beginomnishadow_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginOmniShadow, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginOmniShadow\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginOmniShadow().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginomnishadow_handler_id;

// подписываемся на событие BeginOmniShadow с лямбда-обработчиком, сохраняя идентификатор соединения
beginomnishadow_handler_id = publisher->getEventBeginOmniShadow().connect(e_connections, []() {
		Log::message("\Обработка события BeginOmniShadow (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginOmniShadow().disconnect(beginomnishadow_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginOmniShadow при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginOmniShadow().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginOmniShadow().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndOmniShadow () const

событие, генерируемое после этапом рендеринга теней от источников света Omni. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndOmniShadow
void endomnishadow_event_handler()
{
	Log::message("\Обработка события EndOmniShadow\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endomnishadow_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndOmniShadow().connect(endomnishadow_event_connections, endomnishadow_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndOmniShadow().connect(endomnishadow_event_connections, []() {
		Log::message("\Обработка события EndOmniShadow (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endomnishadow_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endomnishadow_event_connection;

// подписываемся на событие EndOmniShadow с функцией-обработчиком, сохраняя соединение
publisher->getEventEndOmniShadow().connect(endomnishadow_event_connection, endomnishadow_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endomnishadow_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endomnishadow_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndOmniShadow через соединение
endomnishadow_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndOmniShadow, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndOmniShadow\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndOmniShadow().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endomnishadow_handler_id;

// подписываемся на событие EndOmniShadow с лямбда-обработчиком, сохраняя идентификатор соединения
endomnishadow_handler_id = publisher->getEventEndOmniShadow().connect(e_connections, []() {
		Log::message("\Обработка события EndOmniShadow (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndOmniShadow().disconnect(endomnishadow_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndOmniShadow при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndOmniShadow().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndOmniShadow().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndShadows () const

событие, генерируемое после этапом рендеринга теней. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndShadows
void endshadows_event_handler()
{
	Log::message("\Обработка события EndShadows\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endshadows_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndShadows().connect(endshadows_event_connections, endshadows_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndShadows().connect(endshadows_event_connections, []() {
		Log::message("\Обработка события EndShadows (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endshadows_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endshadows_event_connection;

// подписываемся на событие EndShadows с функцией-обработчиком, сохраняя соединение
publisher->getEventEndShadows().connect(endshadows_event_connection, endshadows_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endshadows_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endshadows_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndShadows через соединение
endshadows_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndShadows, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndShadows\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndShadows().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endshadows_handler_id;

// подписываемся на событие EndShadows с лямбда-обработчиком, сохраняя идентификатор соединения
endshadows_handler_id = publisher->getEventEndShadows().connect(e_connections, []() {
		Log::message("\Обработка события EndShadows (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndShadows().disconnect(endshadows_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndShadows при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndShadows().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndShadows().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginScreen () const

событие, генерируемое перед этапом рендеринга каждого экрана (стереоизображение имеет 2 экрана, а кубическая карта - 6). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginScreen
void beginscreen_event_handler()
{
	Log::message("\Обработка события BeginScreen\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginscreen_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginScreen().connect(beginscreen_event_connections, beginscreen_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginScreen().connect(beginscreen_event_connections, []() {
		Log::message("\Обработка события BeginScreen (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginscreen_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginscreen_event_connection;

// подписываемся на событие BeginScreen с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginScreen().connect(beginscreen_event_connection, beginscreen_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginscreen_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginscreen_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginScreen через соединение
beginscreen_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginScreen, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginScreen\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginScreen().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginscreen_handler_id;

// подписываемся на событие BeginScreen с лямбда-обработчиком, сохраняя идентификатор соединения
beginscreen_handler_id = publisher->getEventBeginScreen().connect(e_connections, []() {
		Log::message("\Обработка события BeginScreen (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginScreen().disconnect(beginscreen_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginScreen при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginScreen().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginScreen().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginMixedRealityBlendMaskColor () const

событие, генерируемое перед рендерингом маски для Mixed Reality (после Common Camera для облаков и до Opacity GBuffer). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginMixedRealityBlendMaskColor
void beginmixedrealityblendmaskcolor_event_handler()
{
	Log::message("\Обработка события BeginMixedRealityBlendMaskColor\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginmixedrealityblendmaskcolor_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginMixedRealityBlendMaskColor().connect(beginmixedrealityblendmaskcolor_event_connections, beginmixedrealityblendmaskcolor_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginMixedRealityBlendMaskColor().connect(beginmixedrealityblendmaskcolor_event_connections, []() {
		Log::message("\Обработка события BeginMixedRealityBlendMaskColor (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginmixedrealityblendmaskcolor_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginmixedrealityblendmaskcolor_event_connection;

// подписываемся на событие BeginMixedRealityBlendMaskColor с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginMixedRealityBlendMaskColor().connect(beginmixedrealityblendmaskcolor_event_connection, beginmixedrealityblendmaskcolor_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginmixedrealityblendmaskcolor_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginmixedrealityblendmaskcolor_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginMixedRealityBlendMaskColor через соединение
beginmixedrealityblendmaskcolor_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginMixedRealityBlendMaskColor, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginMixedRealityBlendMaskColor\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginMixedRealityBlendMaskColor().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginmixedrealityblendmaskcolor_handler_id;

// подписываемся на событие BeginMixedRealityBlendMaskColor с лямбда-обработчиком, сохраняя идентификатор соединения
beginmixedrealityblendmaskcolor_handler_id = publisher->getEventBeginMixedRealityBlendMaskColor().connect(e_connections, []() {
		Log::message("\Обработка события BeginMixedRealityBlendMaskColor (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginMixedRealityBlendMaskColor().disconnect(beginmixedrealityblendmaskcolor_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginMixedRealityBlendMaskColor при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginMixedRealityBlendMaskColor().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginMixedRealityBlendMaskColor().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndMixedRealityBlendMaskColor () const

событие, генерируемое после рендерингом маски для Mixed Reality (после Common Camera для облаков и до Opacity GBuffer). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndMixedRealityBlendMaskColor
void endmixedrealityblendmaskcolor_event_handler()
{
	Log::message("\Обработка события EndMixedRealityBlendMaskColor\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endmixedrealityblendmaskcolor_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndMixedRealityBlendMaskColor().connect(endmixedrealityblendmaskcolor_event_connections, endmixedrealityblendmaskcolor_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndMixedRealityBlendMaskColor().connect(endmixedrealityblendmaskcolor_event_connections, []() {
		Log::message("\Обработка события EndMixedRealityBlendMaskColor (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endmixedrealityblendmaskcolor_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endmixedrealityblendmaskcolor_event_connection;

// подписываемся на событие EndMixedRealityBlendMaskColor с функцией-обработчиком, сохраняя соединение
publisher->getEventEndMixedRealityBlendMaskColor().connect(endmixedrealityblendmaskcolor_event_connection, endmixedrealityblendmaskcolor_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endmixedrealityblendmaskcolor_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endmixedrealityblendmaskcolor_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndMixedRealityBlendMaskColor через соединение
endmixedrealityblendmaskcolor_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndMixedRealityBlendMaskColor, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndMixedRealityBlendMaskColor\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndMixedRealityBlendMaskColor().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endmixedrealityblendmaskcolor_handler_id;

// подписываемся на событие EndMixedRealityBlendMaskColor с лямбда-обработчиком, сохраняя идентификатор соединения
endmixedrealityblendmaskcolor_handler_id = publisher->getEventEndMixedRealityBlendMaskColor().connect(e_connections, []() {
		Log::message("\Обработка события EndMixedRealityBlendMaskColor (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndMixedRealityBlendMaskColor().disconnect(endmixedrealityblendmaskcolor_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndMixedRealityBlendMaskColor при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndMixedRealityBlendMaskColor().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndMixedRealityBlendMaskColor().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginOpacityGBuffer () const

событие, генерируемое перед заполнением Gbuffer. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginOpacityGBuffer
void beginopacitygbuffer_event_handler()
{
	Log::message("\Обработка события BeginOpacityGBuffer\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginopacitygbuffer_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginOpacityGBuffer().connect(beginopacitygbuffer_event_connections, beginopacitygbuffer_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginOpacityGBuffer().connect(beginopacitygbuffer_event_connections, []() {
		Log::message("\Обработка события BeginOpacityGBuffer (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginopacitygbuffer_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginopacitygbuffer_event_connection;

// подписываемся на событие BeginOpacityGBuffer с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginOpacityGBuffer().connect(beginopacitygbuffer_event_connection, beginopacitygbuffer_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginopacitygbuffer_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginopacitygbuffer_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginOpacityGBuffer через соединение
beginopacitygbuffer_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginOpacityGBuffer, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginOpacityGBuffer\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginOpacityGBuffer().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginopacitygbuffer_handler_id;

// подписываемся на событие BeginOpacityGBuffer с лямбда-обработчиком, сохраняя идентификатор соединения
beginopacitygbuffer_handler_id = publisher->getEventBeginOpacityGBuffer().connect(e_connections, []() {
		Log::message("\Обработка события BeginOpacityGBuffer (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginOpacityGBuffer().disconnect(beginopacitygbuffer_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginOpacityGBuffer при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginOpacityGBuffer().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginOpacityGBuffer().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<> getEventBeginAuxiliarySurfaces () const

событие, генерируемое перед рендерингом вспомогательных поверхностей. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginAuxiliarySurfaces
void beginauxiliarysurfaces_event_handler()
{
	Log::message("\Обработка события BeginAuxiliarySurfaces\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginauxiliarysurfaces_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Viewport::getEventBeginAuxiliarySurfaces().connect(beginauxiliarysurfaces_event_connections, beginauxiliarysurfaces_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Viewport::getEventBeginAuxiliarySurfaces().connect(beginauxiliarysurfaces_event_connections, []() {
		Log::message("\Обработка события BeginAuxiliarySurfaces (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginauxiliarysurfaces_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginauxiliarysurfaces_event_connection;

// подписываемся на событие BeginAuxiliarySurfaces с функцией-обработчиком, сохраняя соединение
Viewport::getEventBeginAuxiliarySurfaces().connect(beginauxiliarysurfaces_event_connection, beginauxiliarysurfaces_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginauxiliarysurfaces_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginauxiliarysurfaces_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginAuxiliarySurfaces через соединение
beginauxiliarysurfaces_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginAuxiliarySurfaces, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginAuxiliarySurfaces\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Viewport::getEventBeginAuxiliarySurfaces().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginauxiliarysurfaces_handler_id;

// подписываемся на событие BeginAuxiliarySurfaces с лямбда-обработчиком, сохраняя идентификатор соединения
beginauxiliarysurfaces_handler_id = Viewport::getEventBeginAuxiliarySurfaces().connect(e_connections, []() {
		Log::message("\Обработка события BeginAuxiliarySurfaces (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Viewport::getEventBeginAuxiliarySurfaces().disconnect(beginauxiliarysurfaces_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginAuxiliarySurfaces при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Viewport::getEventBeginAuxiliarySurfaces().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Viewport::getEventBeginAuxiliarySurfaces().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<> getEventEndAuxiliarySurfaces () const

событие, генерируемое после рендерингом вспомогательных поверхностей. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndAuxiliarySurfaces
void endauxiliarysurfaces_event_handler()
{
	Log::message("\Обработка события EndAuxiliarySurfaces\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endauxiliarysurfaces_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Viewport::getEventEndAuxiliarySurfaces().connect(endauxiliarysurfaces_event_connections, endauxiliarysurfaces_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Viewport::getEventEndAuxiliarySurfaces().connect(endauxiliarysurfaces_event_connections, []() {
		Log::message("\Обработка события EndAuxiliarySurfaces (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endauxiliarysurfaces_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endauxiliarysurfaces_event_connection;

// подписываемся на событие EndAuxiliarySurfaces с функцией-обработчиком, сохраняя соединение
Viewport::getEventEndAuxiliarySurfaces().connect(endauxiliarysurfaces_event_connection, endauxiliarysurfaces_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endauxiliarysurfaces_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endauxiliarysurfaces_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndAuxiliarySurfaces через соединение
endauxiliarysurfaces_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndAuxiliarySurfaces, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndAuxiliarySurfaces\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Viewport::getEventEndAuxiliarySurfaces().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endauxiliarysurfaces_handler_id;

// подписываемся на событие EndAuxiliarySurfaces с лямбда-обработчиком, сохраняя идентификатор соединения
endauxiliarysurfaces_handler_id = Viewport::getEventEndAuxiliarySurfaces().connect(e_connections, []() {
		Log::message("\Обработка события EndAuxiliarySurfaces (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Viewport::getEventEndAuxiliarySurfaces().disconnect(endauxiliarysurfaces_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndAuxiliarySurfaces при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Viewport::getEventEndAuxiliarySurfaces().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Viewport::getEventEndAuxiliarySurfaces().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndOpacityGBuffer () const

событие, генерируемое после заполнением Gbuffer. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndOpacityGBuffer
void endopacitygbuffer_event_handler()
{
	Log::message("\Обработка события EndOpacityGBuffer\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endopacitygbuffer_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndOpacityGBuffer().connect(endopacitygbuffer_event_connections, endopacitygbuffer_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndOpacityGBuffer().connect(endopacitygbuffer_event_connections, []() {
		Log::message("\Обработка события EndOpacityGBuffer (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endopacitygbuffer_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endopacitygbuffer_event_connection;

// подписываемся на событие EndOpacityGBuffer с функцией-обработчиком, сохраняя соединение
publisher->getEventEndOpacityGBuffer().connect(endopacitygbuffer_event_connection, endopacitygbuffer_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endopacitygbuffer_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endopacitygbuffer_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndOpacityGBuffer через соединение
endopacitygbuffer_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndOpacityGBuffer, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndOpacityGBuffer\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndOpacityGBuffer().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endopacitygbuffer_handler_id;

// подписываемся на событие EndOpacityGBuffer с лямбда-обработчиком, сохраняя идентификатор соединения
endopacitygbuffer_handler_id = publisher->getEventEndOpacityGBuffer().connect(e_connections, []() {
		Log::message("\Обработка события EndOpacityGBuffer (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndOpacityGBuffer().disconnect(endopacitygbuffer_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndOpacityGBuffer при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndOpacityGBuffer().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndOpacityGBuffer().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginOpacityDecals () const

событие, генерируемое перед этапом рендеринга непрозрачных декалей. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginOpacityDecals
void beginopacitydecals_event_handler()
{
	Log::message("\Обработка события BeginOpacityDecals\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginopacitydecals_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginOpacityDecals().connect(beginopacitydecals_event_connections, beginopacitydecals_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginOpacityDecals().connect(beginopacitydecals_event_connections, []() {
		Log::message("\Обработка события BeginOpacityDecals (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginopacitydecals_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginopacitydecals_event_connection;

// подписываемся на событие BeginOpacityDecals с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginOpacityDecals().connect(beginopacitydecals_event_connection, beginopacitydecals_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginopacitydecals_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginopacitydecals_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginOpacityDecals через соединение
beginopacitydecals_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginOpacityDecals, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginOpacityDecals\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginOpacityDecals().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginopacitydecals_handler_id;

// подписываемся на событие BeginOpacityDecals с лямбда-обработчиком, сохраняя идентификатор соединения
beginopacitydecals_handler_id = publisher->getEventBeginOpacityDecals().connect(e_connections, []() {
		Log::message("\Обработка события BeginOpacityDecals (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginOpacityDecals().disconnect(beginopacitydecals_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginOpacityDecals при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginOpacityDecals().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginOpacityDecals().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndOpacityDecals () const

событие, генерируемое после этапом рендеринга непрозрачных декалей. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndOpacityDecals
void endopacitydecals_event_handler()
{
	Log::message("\Обработка события EndOpacityDecals\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endopacitydecals_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndOpacityDecals().connect(endopacitydecals_event_connections, endopacitydecals_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndOpacityDecals().connect(endopacitydecals_event_connections, []() {
		Log::message("\Обработка события EndOpacityDecals (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endopacitydecals_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endopacitydecals_event_connection;

// подписываемся на событие EndOpacityDecals с функцией-обработчиком, сохраняя соединение
publisher->getEventEndOpacityDecals().connect(endopacitydecals_event_connection, endopacitydecals_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endopacitydecals_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endopacitydecals_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndOpacityDecals через соединение
endopacitydecals_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndOpacityDecals, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndOpacityDecals\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndOpacityDecals().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endopacitydecals_handler_id;

// подписываемся на событие EndOpacityDecals с лямбда-обработчиком, сохраняя идентификатор соединения
endopacitydecals_handler_id = publisher->getEventEndOpacityDecals().connect(e_connections, []() {
		Log::message("\Обработка события EndOpacityDecals (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndOpacityDecals().disconnect(endopacitydecals_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndOpacityDecals при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndOpacityDecals().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndOpacityDecals().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<> getEventBeginAuxiliaryDecals () const

событие, генерируемое перед этапом рендеринга вспомогательных декалей. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginAuxiliaryDecals
void beginauxiliarydecals_event_handler()
{
	Log::message("\Обработка события BeginAuxiliaryDecals\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginauxiliarydecals_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Viewport::getEventBeginAuxiliaryDecals().connect(beginauxiliarydecals_event_connections, beginauxiliarydecals_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Viewport::getEventBeginAuxiliaryDecals().connect(beginauxiliarydecals_event_connections, []() {
		Log::message("\Обработка события BeginAuxiliaryDecals (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginauxiliarydecals_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginauxiliarydecals_event_connection;

// подписываемся на событие BeginAuxiliaryDecals с функцией-обработчиком, сохраняя соединение
Viewport::getEventBeginAuxiliaryDecals().connect(beginauxiliarydecals_event_connection, beginauxiliarydecals_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginauxiliarydecals_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginauxiliarydecals_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginAuxiliaryDecals через соединение
beginauxiliarydecals_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginAuxiliaryDecals, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginAuxiliaryDecals\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Viewport::getEventBeginAuxiliaryDecals().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginauxiliarydecals_handler_id;

// подписываемся на событие BeginAuxiliaryDecals с лямбда-обработчиком, сохраняя идентификатор соединения
beginauxiliarydecals_handler_id = Viewport::getEventBeginAuxiliaryDecals().connect(e_connections, []() {
		Log::message("\Обработка события BeginAuxiliaryDecals (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Viewport::getEventBeginAuxiliaryDecals().disconnect(beginauxiliarydecals_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginAuxiliaryDecals при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Viewport::getEventBeginAuxiliaryDecals().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Viewport::getEventBeginAuxiliaryDecals().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<> getEventEndAuxiliaryDecals () const

событие, генерируемое после этапом рендеринга вспомогательных декалей. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndAuxiliaryDecals
void endauxiliarydecals_event_handler()
{
	Log::message("\Обработка события EndAuxiliaryDecals\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endauxiliarydecals_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Viewport::getEventEndAuxiliaryDecals().connect(endauxiliarydecals_event_connections, endauxiliarydecals_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Viewport::getEventEndAuxiliaryDecals().connect(endauxiliarydecals_event_connections, []() {
		Log::message("\Обработка события EndAuxiliaryDecals (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endauxiliarydecals_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endauxiliarydecals_event_connection;

// подписываемся на событие EndAuxiliaryDecals с функцией-обработчиком, сохраняя соединение
Viewport::getEventEndAuxiliaryDecals().connect(endauxiliarydecals_event_connection, endauxiliarydecals_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endauxiliarydecals_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endauxiliarydecals_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndAuxiliaryDecals через соединение
endauxiliarydecals_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndAuxiliaryDecals, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndAuxiliaryDecals\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Viewport::getEventEndAuxiliaryDecals().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endauxiliarydecals_handler_id;

// подписываемся на событие EndAuxiliaryDecals с лямбда-обработчиком, сохраняя идентификатор соединения
endauxiliarydecals_handler_id = Viewport::getEventEndAuxiliaryDecals().connect(e_connections, []() {
		Log::message("\Обработка события EndAuxiliaryDecals (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Viewport::getEventEndAuxiliaryDecals().disconnect(endauxiliarydecals_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndAuxiliaryDecals при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Viewport::getEventEndAuxiliaryDecals().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Viewport::getEventEndAuxiliaryDecals().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginCurvature () const

событие, генерируемое перед этапом рендеринга эффекта [SSBevel](../../../editor2/settings/render_settings/ssbevel/index.md). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginCurvature
void begincurvature_event_handler()
{
	Log::message("\Обработка события BeginCurvature\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections begincurvature_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginCurvature().connect(begincurvature_event_connections, begincurvature_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginCurvature().connect(begincurvature_event_connections, []() {
		Log::message("\Обработка события BeginCurvature (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
begincurvature_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection begincurvature_event_connection;

// подписываемся на событие BeginCurvature с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginCurvature().connect(begincurvature_event_connection, begincurvature_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
begincurvature_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
begincurvature_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginCurvature через соединение
begincurvature_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginCurvature, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginCurvature\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginCurvature().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId begincurvature_handler_id;

// подписываемся на событие BeginCurvature с лямбда-обработчиком, сохраняя идентификатор соединения
begincurvature_handler_id = publisher->getEventBeginCurvature().connect(e_connections, []() {
		Log::message("\Обработка события BeginCurvature (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginCurvature().disconnect(begincurvature_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginCurvature при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginCurvature().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginCurvature().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndCurvature () const

событие, генерируемое после этапом рендеринга эффекта [SSBevel](../../../editor2/settings/render_settings/ssbevel/index.md). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndCurvature
void endcurvature_event_handler()
{
	Log::message("\Обработка события EndCurvature\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endcurvature_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndCurvature().connect(endcurvature_event_connections, endcurvature_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndCurvature().connect(endcurvature_event_connections, []() {
		Log::message("\Обработка события EndCurvature (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endcurvature_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endcurvature_event_connection;

// подписываемся на событие EndCurvature с функцией-обработчиком, сохраняя соединение
publisher->getEventEndCurvature().connect(endcurvature_event_connection, endcurvature_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endcurvature_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endcurvature_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndCurvature через соединение
endcurvature_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndCurvature, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndCurvature\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndCurvature().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endcurvature_handler_id;

// подписываемся на событие EndCurvature с лямбда-обработчиком, сохраняя идентификатор соединения
endcurvature_handler_id = publisher->getEventEndCurvature().connect(e_connections, []() {
		Log::message("\Обработка события EndCurvature (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndCurvature().disconnect(endcurvature_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndCurvature при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndCurvature().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndCurvature().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginCurvatureComposite () const

событие, генерируемое перед этапом рендеринга кривизны для эффекта [SSDirt](../../../editor2/settings/render_settings/ssdirt/index.md). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginCurvatureComposite
void begincurvaturecomposite_event_handler()
{
	Log::message("\Обработка события BeginCurvatureComposite\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections begincurvaturecomposite_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginCurvatureComposite().connect(begincurvaturecomposite_event_connections, begincurvaturecomposite_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginCurvatureComposite().connect(begincurvaturecomposite_event_connections, []() {
		Log::message("\Обработка события BeginCurvatureComposite (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
begincurvaturecomposite_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection begincurvaturecomposite_event_connection;

// подписываемся на событие BeginCurvatureComposite с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginCurvatureComposite().connect(begincurvaturecomposite_event_connection, begincurvaturecomposite_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
begincurvaturecomposite_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
begincurvaturecomposite_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginCurvatureComposite через соединение
begincurvaturecomposite_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginCurvatureComposite, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginCurvatureComposite\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginCurvatureComposite().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId begincurvaturecomposite_handler_id;

// подписываемся на событие BeginCurvatureComposite с лямбда-обработчиком, сохраняя идентификатор соединения
begincurvaturecomposite_handler_id = publisher->getEventBeginCurvatureComposite().connect(e_connections, []() {
		Log::message("\Обработка события BeginCurvatureComposite (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginCurvatureComposite().disconnect(begincurvaturecomposite_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginCurvatureComposite при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginCurvatureComposite().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginCurvatureComposite().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndCurvatureComposite () const

событие, генерируемое после этапом рендеринга кривизны для эффекта [SSDirt](../../../editor2/settings/render_settings/ssdirt/index.md). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndCurvatureComposite
void endcurvaturecomposite_event_handler()
{
	Log::message("\Обработка события EndCurvatureComposite\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endcurvaturecomposite_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndCurvatureComposite().connect(endcurvaturecomposite_event_connections, endcurvaturecomposite_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndCurvatureComposite().connect(endcurvaturecomposite_event_connections, []() {
		Log::message("\Обработка события EndCurvatureComposite (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endcurvaturecomposite_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endcurvaturecomposite_event_connection;

// подписываемся на событие EndCurvatureComposite с функцией-обработчиком, сохраняя соединение
publisher->getEventEndCurvatureComposite().connect(endcurvaturecomposite_event_connection, endcurvaturecomposite_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endcurvaturecomposite_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endcurvaturecomposite_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndCurvatureComposite через соединение
endcurvaturecomposite_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndCurvatureComposite, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndCurvatureComposite\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndCurvatureComposite().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endcurvaturecomposite_handler_id;

// подписываемся на событие EndCurvatureComposite с лямбда-обработчиком, сохраняя идентификатор соединения
endcurvaturecomposite_handler_id = publisher->getEventEndCurvatureComposite().connect(e_connections, []() {
		Log::message("\Обработка события EndCurvatureComposite (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndCurvatureComposite().disconnect(endcurvaturecomposite_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndCurvatureComposite при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndCurvatureComposite().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndCurvatureComposite().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginSSRTGI () const

событие, генерируемое перед этапом рендеринга SSRTGI. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginSSRTGI
void beginssrtgi_event_handler()
{
	Log::message("\Обработка события BeginSSRTGI\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginssrtgi_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginSSRTGI().connect(beginssrtgi_event_connections, beginssrtgi_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginSSRTGI().connect(beginssrtgi_event_connections, []() {
		Log::message("\Обработка события BeginSSRTGI (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginssrtgi_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginssrtgi_event_connection;

// подписываемся на событие BeginSSRTGI с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginSSRTGI().connect(beginssrtgi_event_connection, beginssrtgi_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginssrtgi_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginssrtgi_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginSSRTGI через соединение
beginssrtgi_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginSSRTGI, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginSSRTGI\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginSSRTGI().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginssrtgi_handler_id;

// подписываемся на событие BeginSSRTGI с лямбда-обработчиком, сохраняя идентификатор соединения
beginssrtgi_handler_id = publisher->getEventBeginSSRTGI().connect(e_connections, []() {
		Log::message("\Обработка события BeginSSRTGI (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginSSRTGI().disconnect(beginssrtgi_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginSSRTGI при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginSSRTGI().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginSSRTGI().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndSSRTGI () const

событие, генерируемое после этапом рендеринга SSRTGI. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndSSRTGI
void endssrtgi_event_handler()
{
	Log::message("\Обработка события EndSSRTGI\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endssrtgi_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndSSRTGI().connect(endssrtgi_event_connections, endssrtgi_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndSSRTGI().connect(endssrtgi_event_connections, []() {
		Log::message("\Обработка события EndSSRTGI (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endssrtgi_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endssrtgi_event_connection;

// подписываемся на событие EndSSRTGI с функцией-обработчиком, сохраняя соединение
publisher->getEventEndSSRTGI().connect(endssrtgi_event_connection, endssrtgi_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endssrtgi_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endssrtgi_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndSSRTGI через соединение
endssrtgi_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndSSRTGI, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndSSRTGI\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndSSRTGI().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endssrtgi_handler_id;

// подписываемся на событие EndSSRTGI с лямбда-обработчиком, сохраняя идентификатор соединения
endssrtgi_handler_id = publisher->getEventEndSSRTGI().connect(e_connections, []() {
		Log::message("\Обработка события EndSSRTGI (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndSSRTGI().disconnect(endssrtgi_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndSSRTGI при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndSSRTGI().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndSSRTGI().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginOpacityLights () const

событие, генерируемое перед этапом рендеринга непрозрачных источников света. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginOpacityLights
void beginopacitylights_event_handler()
{
	Log::message("\Обработка события BeginOpacityLights\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginopacitylights_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginOpacityLights().connect(beginopacitylights_event_connections, beginopacitylights_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginOpacityLights().connect(beginopacitylights_event_connections, []() {
		Log::message("\Обработка события BeginOpacityLights (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginopacitylights_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginopacitylights_event_connection;

// подписываемся на событие BeginOpacityLights с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginOpacityLights().connect(beginopacitylights_event_connection, beginopacitylights_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginopacitylights_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginopacitylights_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginOpacityLights через соединение
beginopacitylights_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginOpacityLights, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginOpacityLights\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginOpacityLights().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginopacitylights_handler_id;

// подписываемся на событие BeginOpacityLights с лямбда-обработчиком, сохраняя идентификатор соединения
beginopacitylights_handler_id = publisher->getEventBeginOpacityLights().connect(e_connections, []() {
		Log::message("\Обработка события BeginOpacityLights (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginOpacityLights().disconnect(beginopacitylights_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginOpacityLights при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginOpacityLights().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginOpacityLights().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndOpacityLights () const

событие, генерируемое после этапом рендеринга непрозрачных источников света. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndOpacityLights
void endopacitylights_event_handler()
{
	Log::message("\Обработка события EndOpacityLights\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endopacitylights_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndOpacityLights().connect(endopacitylights_event_connections, endopacitylights_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndOpacityLights().connect(endopacitylights_event_connections, []() {
		Log::message("\Обработка события EndOpacityLights (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endopacitylights_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endopacitylights_event_connection;

// подписываемся на событие EndOpacityLights с функцией-обработчиком, сохраняя соединение
publisher->getEventEndOpacityLights().connect(endopacitylights_event_connection, endopacitylights_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endopacitylights_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endopacitylights_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndOpacityLights через соединение
endopacitylights_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndOpacityLights, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndOpacityLights\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndOpacityLights().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endopacitylights_handler_id;

// подписываемся на событие EndOpacityLights с лямбда-обработчиком, сохраняя идентификатор соединения
endopacitylights_handler_id = publisher->getEventEndOpacityLights().connect(e_connections, []() {
		Log::message("\Обработка события EndOpacityLights (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndOpacityLights().disconnect(endopacitylights_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndOpacityLights при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndOpacityLights().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndOpacityLights().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginOpacityVoxelProbes () const

событие, генерируемое перед этапом рендеринга непрозрачных воксельных пробников. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginOpacityVoxelProbes
void beginopacityvoxelprobes_event_handler()
{
	Log::message("\Обработка события BeginOpacityVoxelProbes\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginopacityvoxelprobes_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginOpacityVoxelProbes().connect(beginopacityvoxelprobes_event_connections, beginopacityvoxelprobes_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginOpacityVoxelProbes().connect(beginopacityvoxelprobes_event_connections, []() {
		Log::message("\Обработка события BeginOpacityVoxelProbes (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginopacityvoxelprobes_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginopacityvoxelprobes_event_connection;

// подписываемся на событие BeginOpacityVoxelProbes с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginOpacityVoxelProbes().connect(beginopacityvoxelprobes_event_connection, beginopacityvoxelprobes_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginopacityvoxelprobes_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginopacityvoxelprobes_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginOpacityVoxelProbes через соединение
beginopacityvoxelprobes_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginOpacityVoxelProbes, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginOpacityVoxelProbes\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginOpacityVoxelProbes().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginopacityvoxelprobes_handler_id;

// подписываемся на событие BeginOpacityVoxelProbes с лямбда-обработчиком, сохраняя идентификатор соединения
beginopacityvoxelprobes_handler_id = publisher->getEventBeginOpacityVoxelProbes().connect(e_connections, []() {
		Log::message("\Обработка события BeginOpacityVoxelProbes (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginOpacityVoxelProbes().disconnect(beginopacityvoxelprobes_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginOpacityVoxelProbes при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginOpacityVoxelProbes().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginOpacityVoxelProbes().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndOpacityVoxelProbes () const

событие, генерируемое после этапом рендеринга непрозрачных воксельных пробников. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndOpacityVoxelProbes
void endopacityvoxelprobes_event_handler()
{
	Log::message("\Обработка события EndOpacityVoxelProbes\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endopacityvoxelprobes_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndOpacityVoxelProbes().connect(endopacityvoxelprobes_event_connections, endopacityvoxelprobes_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndOpacityVoxelProbes().connect(endopacityvoxelprobes_event_connections, []() {
		Log::message("\Обработка события EndOpacityVoxelProbes (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endopacityvoxelprobes_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endopacityvoxelprobes_event_connection;

// подписываемся на событие EndOpacityVoxelProbes с функцией-обработчиком, сохраняя соединение
publisher->getEventEndOpacityVoxelProbes().connect(endopacityvoxelprobes_event_connection, endopacityvoxelprobes_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endopacityvoxelprobes_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endopacityvoxelprobes_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndOpacityVoxelProbes через соединение
endopacityvoxelprobes_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndOpacityVoxelProbes, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndOpacityVoxelProbes\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndOpacityVoxelProbes().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endopacityvoxelprobes_handler_id;

// подписываемся на событие EndOpacityVoxelProbes с лямбда-обработчиком, сохраняя идентификатор соединения
endopacityvoxelprobes_handler_id = publisher->getEventEndOpacityVoxelProbes().connect(e_connections, []() {
		Log::message("\Обработка события EndOpacityVoxelProbes (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndOpacityVoxelProbes().disconnect(endopacityvoxelprobes_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndOpacityVoxelProbes при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndOpacityVoxelProbes().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndOpacityVoxelProbes().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginOpacityEnvironmentProbes () const

событие, генерируемое перед этапом рендеринга непрозрачных пробников окружения. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginOpacityEnvironmentProbes
void beginopacityenvironmentprobes_event_handler()
{
	Log::message("\Обработка события BeginOpacityEnvironmentProbes\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginopacityenvironmentprobes_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginOpacityEnvironmentProbes().connect(beginopacityenvironmentprobes_event_connections, beginopacityenvironmentprobes_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginOpacityEnvironmentProbes().connect(beginopacityenvironmentprobes_event_connections, []() {
		Log::message("\Обработка события BeginOpacityEnvironmentProbes (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginopacityenvironmentprobes_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginopacityenvironmentprobes_event_connection;

// подписываемся на событие BeginOpacityEnvironmentProbes с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginOpacityEnvironmentProbes().connect(beginopacityenvironmentprobes_event_connection, beginopacityenvironmentprobes_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginopacityenvironmentprobes_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginopacityenvironmentprobes_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginOpacityEnvironmentProbes через соединение
beginopacityenvironmentprobes_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginOpacityEnvironmentProbes, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginOpacityEnvironmentProbes\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginOpacityEnvironmentProbes().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginopacityenvironmentprobes_handler_id;

// подписываемся на событие BeginOpacityEnvironmentProbes с лямбда-обработчиком, сохраняя идентификатор соединения
beginopacityenvironmentprobes_handler_id = publisher->getEventBeginOpacityEnvironmentProbes().connect(e_connections, []() {
		Log::message("\Обработка события BeginOpacityEnvironmentProbes (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginOpacityEnvironmentProbes().disconnect(beginopacityenvironmentprobes_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginOpacityEnvironmentProbes при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginOpacityEnvironmentProbes().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginOpacityEnvironmentProbes().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndOpacityEnvironmentProbes () const

событие, генерируемое после этапом рендеринга непрозрачных пробников окружения. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndOpacityEnvironmentProbes
void endopacityenvironmentprobes_event_handler()
{
	Log::message("\Обработка события EndOpacityEnvironmentProbes\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endopacityenvironmentprobes_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndOpacityEnvironmentProbes().connect(endopacityenvironmentprobes_event_connections, endopacityenvironmentprobes_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndOpacityEnvironmentProbes().connect(endopacityenvironmentprobes_event_connections, []() {
		Log::message("\Обработка события EndOpacityEnvironmentProbes (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endopacityenvironmentprobes_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endopacityenvironmentprobes_event_connection;

// подписываемся на событие EndOpacityEnvironmentProbes с функцией-обработчиком, сохраняя соединение
publisher->getEventEndOpacityEnvironmentProbes().connect(endopacityenvironmentprobes_event_connection, endopacityenvironmentprobes_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endopacityenvironmentprobes_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endopacityenvironmentprobes_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndOpacityEnvironmentProbes через соединение
endopacityenvironmentprobes_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndOpacityEnvironmentProbes, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndOpacityEnvironmentProbes\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndOpacityEnvironmentProbes().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endopacityenvironmentprobes_handler_id;

// подписываемся на событие EndOpacityEnvironmentProbes с лямбда-обработчиком, сохраняя идентификатор соединения
endopacityenvironmentprobes_handler_id = publisher->getEventEndOpacityEnvironmentProbes().connect(e_connections, []() {
		Log::message("\Обработка события EndOpacityEnvironmentProbes (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndOpacityEnvironmentProbes().disconnect(endopacityenvironmentprobes_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndOpacityEnvironmentProbes при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndOpacityEnvironmentProbes().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndOpacityEnvironmentProbes().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginOpacityPlanarProbes () const

событие, генерируемое перед этапом рендеринга непрозрачных плоских пробников. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginOpacityPlanarProbes
void beginopacityplanarprobes_event_handler()
{
	Log::message("\Обработка события BeginOpacityPlanarProbes\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginopacityplanarprobes_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginOpacityPlanarProbes().connect(beginopacityplanarprobes_event_connections, beginopacityplanarprobes_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginOpacityPlanarProbes().connect(beginopacityplanarprobes_event_connections, []() {
		Log::message("\Обработка события BeginOpacityPlanarProbes (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginopacityplanarprobes_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginopacityplanarprobes_event_connection;

// подписываемся на событие BeginOpacityPlanarProbes с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginOpacityPlanarProbes().connect(beginopacityplanarprobes_event_connection, beginopacityplanarprobes_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginopacityplanarprobes_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginopacityplanarprobes_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginOpacityPlanarProbes через соединение
beginopacityplanarprobes_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginOpacityPlanarProbes, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginOpacityPlanarProbes\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginOpacityPlanarProbes().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginopacityplanarprobes_handler_id;

// подписываемся на событие BeginOpacityPlanarProbes с лямбда-обработчиком, сохраняя идентификатор соединения
beginopacityplanarprobes_handler_id = publisher->getEventBeginOpacityPlanarProbes().connect(e_connections, []() {
		Log::message("\Обработка события BeginOpacityPlanarProbes (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginOpacityPlanarProbes().disconnect(beginopacityplanarprobes_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginOpacityPlanarProbes при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginOpacityPlanarProbes().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginOpacityPlanarProbes().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndOpacityPlanarProbes () const

событие, генерируемое после этапом рендеринга непрозрачных плоских пробников. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndOpacityPlanarProbes
void endopacityplanarprobes_event_handler()
{
	Log::message("\Обработка события EndOpacityPlanarProbes\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endopacityplanarprobes_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndOpacityPlanarProbes().connect(endopacityplanarprobes_event_connections, endopacityplanarprobes_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndOpacityPlanarProbes().connect(endopacityplanarprobes_event_connections, []() {
		Log::message("\Обработка события EndOpacityPlanarProbes (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endopacityplanarprobes_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endopacityplanarprobes_event_connection;

// подписываемся на событие EndOpacityPlanarProbes с функцией-обработчиком, сохраняя соединение
publisher->getEventEndOpacityPlanarProbes().connect(endopacityplanarprobes_event_connection, endopacityplanarprobes_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endopacityplanarprobes_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endopacityplanarprobes_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndOpacityPlanarProbes через соединение
endopacityplanarprobes_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndOpacityPlanarProbes, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndOpacityPlanarProbes\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndOpacityPlanarProbes().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endopacityplanarprobes_handler_id;

// подписываемся на событие EndOpacityPlanarProbes с лямбда-обработчиком, сохраняя идентификатор соединения
endopacityplanarprobes_handler_id = publisher->getEventEndOpacityPlanarProbes().connect(e_connections, []() {
		Log::message("\Обработка события EndOpacityPlanarProbes (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndOpacityPlanarProbes().disconnect(endopacityplanarprobes_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndOpacityPlanarProbes при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndOpacityPlanarProbes().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndOpacityPlanarProbes().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginRefractionBuffer () const

событие, генерируемое перед заполнением буфера преломления. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginRefractionBuffer
void beginrefractionbuffer_event_handler()
{
	Log::message("\Обработка события BeginRefractionBuffer\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginrefractionbuffer_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginRefractionBuffer().connect(beginrefractionbuffer_event_connections, beginrefractionbuffer_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginRefractionBuffer().connect(beginrefractionbuffer_event_connections, []() {
		Log::message("\Обработка события BeginRefractionBuffer (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginrefractionbuffer_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginrefractionbuffer_event_connection;

// подписываемся на событие BeginRefractionBuffer с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginRefractionBuffer().connect(beginrefractionbuffer_event_connection, beginrefractionbuffer_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginrefractionbuffer_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginrefractionbuffer_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginRefractionBuffer через соединение
beginrefractionbuffer_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginRefractionBuffer, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginRefractionBuffer\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginRefractionBuffer().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginrefractionbuffer_handler_id;

// подписываемся на событие BeginRefractionBuffer с лямбда-обработчиком, сохраняя идентификатор соединения
beginrefractionbuffer_handler_id = publisher->getEventBeginRefractionBuffer().connect(e_connections, []() {
		Log::message("\Обработка события BeginRefractionBuffer (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginRefractionBuffer().disconnect(beginrefractionbuffer_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginRefractionBuffer при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginRefractionBuffer().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginRefractionBuffer().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndRefractionBuffer () const

событие, генерируемое после заполнением буфера преломления. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndRefractionBuffer
void endrefractionbuffer_event_handler()
{
	Log::message("\Обработка события EndRefractionBuffer\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endrefractionbuffer_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndRefractionBuffer().connect(endrefractionbuffer_event_connections, endrefractionbuffer_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndRefractionBuffer().connect(endrefractionbuffer_event_connections, []() {
		Log::message("\Обработка события EndRefractionBuffer (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endrefractionbuffer_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endrefractionbuffer_event_connection;

// подписываемся на событие EndRefractionBuffer с функцией-обработчиком, сохраняя соединение
publisher->getEventEndRefractionBuffer().connect(endrefractionbuffer_event_connection, endrefractionbuffer_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endrefractionbuffer_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endrefractionbuffer_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndRefractionBuffer через соединение
endrefractionbuffer_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndRefractionBuffer, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndRefractionBuffer\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndRefractionBuffer().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endrefractionbuffer_handler_id;

// подписываемся на событие EndRefractionBuffer с лямбда-обработчиком, сохраняя идентификатор соединения
endrefractionbuffer_handler_id = publisher->getEventEndRefractionBuffer().connect(e_connections, []() {
		Log::message("\Обработка события EndRefractionBuffer (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndRefractionBuffer().disconnect(endrefractionbuffer_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndRefractionBuffer при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndRefractionBuffer().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndRefractionBuffer().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginTransparentBlurBuffer () const

событие, генерируемое перед заполнением буфера размытия прозрачности. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginTransparentBlurBuffer
void begintransparentblurbuffer_event_handler()
{
	Log::message("\Обработка события BeginTransparentBlurBuffer\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections begintransparentblurbuffer_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginTransparentBlurBuffer().connect(begintransparentblurbuffer_event_connections, begintransparentblurbuffer_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginTransparentBlurBuffer().connect(begintransparentblurbuffer_event_connections, []() {
		Log::message("\Обработка события BeginTransparentBlurBuffer (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
begintransparentblurbuffer_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection begintransparentblurbuffer_event_connection;

// подписываемся на событие BeginTransparentBlurBuffer с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginTransparentBlurBuffer().connect(begintransparentblurbuffer_event_connection, begintransparentblurbuffer_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
begintransparentblurbuffer_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
begintransparentblurbuffer_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginTransparentBlurBuffer через соединение
begintransparentblurbuffer_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginTransparentBlurBuffer, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginTransparentBlurBuffer\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginTransparentBlurBuffer().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId begintransparentblurbuffer_handler_id;

// подписываемся на событие BeginTransparentBlurBuffer с лямбда-обработчиком, сохраняя идентификатор соединения
begintransparentblurbuffer_handler_id = publisher->getEventBeginTransparentBlurBuffer().connect(e_connections, []() {
		Log::message("\Обработка события BeginTransparentBlurBuffer (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginTransparentBlurBuffer().disconnect(begintransparentblurbuffer_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginTransparentBlurBuffer при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginTransparentBlurBuffer().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginTransparentBlurBuffer().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndTransparentBlurBuffer () const

событие, генерируемое после заполнением буфера размытия прозрачности. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndTransparentBlurBuffer
void endtransparentblurbuffer_event_handler()
{
	Log::message("\Обработка события EndTransparentBlurBuffer\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endtransparentblurbuffer_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndTransparentBlurBuffer().connect(endtransparentblurbuffer_event_connections, endtransparentblurbuffer_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndTransparentBlurBuffer().connect(endtransparentblurbuffer_event_connections, []() {
		Log::message("\Обработка события EndTransparentBlurBuffer (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endtransparentblurbuffer_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endtransparentblurbuffer_event_connection;

// подписываемся на событие EndTransparentBlurBuffer с функцией-обработчиком, сохраняя соединение
publisher->getEventEndTransparentBlurBuffer().connect(endtransparentblurbuffer_event_connection, endtransparentblurbuffer_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endtransparentblurbuffer_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endtransparentblurbuffer_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndTransparentBlurBuffer через соединение
endtransparentblurbuffer_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndTransparentBlurBuffer, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndTransparentBlurBuffer\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndTransparentBlurBuffer().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endtransparentblurbuffer_handler_id;

// подписываемся на событие EndTransparentBlurBuffer с лямбда-обработчиком, сохраняя идентификатор соединения
endtransparentblurbuffer_handler_id = publisher->getEventEndTransparentBlurBuffer().connect(e_connections, []() {
		Log::message("\Обработка события EndTransparentBlurBuffer (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndTransparentBlurBuffer().disconnect(endtransparentblurbuffer_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndTransparentBlurBuffer при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndTransparentBlurBuffer().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndTransparentBlurBuffer().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginSSSS () const

событие, генерируемое перед этапом рендеринга Screen-Space Shadow Shafts. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginSSSS
void beginssss_event_handler()
{
	Log::message("\Обработка события BeginSSSS\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginssss_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginSSSS().connect(beginssss_event_connections, beginssss_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginSSSS().connect(beginssss_event_connections, []() {
		Log::message("\Обработка события BeginSSSS (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginssss_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginssss_event_connection;

// подписываемся на событие BeginSSSS с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginSSSS().connect(beginssss_event_connection, beginssss_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginssss_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginssss_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginSSSS через соединение
beginssss_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginSSSS, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginSSSS\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginSSSS().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginssss_handler_id;

// подписываемся на событие BeginSSSS с лямбда-обработчиком, сохраняя идентификатор соединения
beginssss_handler_id = publisher->getEventBeginSSSS().connect(e_connections, []() {
		Log::message("\Обработка события BeginSSSS (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginSSSS().disconnect(beginssss_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginSSSS при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginSSSS().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginSSSS().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndSSSS () const

событие, генерируемое после этапом рендеринга Screen-Space Shadow Shafts. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndSSSS
void endssss_event_handler()
{
	Log::message("\Обработка события EndSSSS\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endssss_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndSSSS().connect(endssss_event_connections, endssss_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndSSSS().connect(endssss_event_connections, []() {
		Log::message("\Обработка события EndSSSS (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endssss_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endssss_event_connection;

// подписываемся на событие EndSSSS с функцией-обработчиком, сохраняя соединение
publisher->getEventEndSSSS().connect(endssss_event_connection, endssss_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endssss_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endssss_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndSSSS через соединение
endssss_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndSSSS, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndSSSS\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndSSSS().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endssss_handler_id;

// подписываемся на событие EndSSSS с лямбда-обработчиком, сохраняя идентификатор соединения
endssss_handler_id = publisher->getEventEndSSSS().connect(e_connections, []() {
		Log::message("\Обработка события EndSSSS (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndSSSS().disconnect(endssss_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndSSSS при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndSSSS().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndSSSS().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginSSR () const

событие, генерируемое перед этапом рендеринга SSR. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginSSR
void beginssr_event_handler()
{
	Log::message("\Обработка события BeginSSR\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginssr_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginSSR().connect(beginssr_event_connections, beginssr_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginSSR().connect(beginssr_event_connections, []() {
		Log::message("\Обработка события BeginSSR (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginssr_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginssr_event_connection;

// подписываемся на событие BeginSSR с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginSSR().connect(beginssr_event_connection, beginssr_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginssr_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginssr_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginSSR через соединение
beginssr_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginSSR, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginSSR\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginSSR().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginssr_handler_id;

// подписываемся на событие BeginSSR с лямбда-обработчиком, сохраняя идентификатор соединения
beginssr_handler_id = publisher->getEventBeginSSR().connect(e_connections, []() {
		Log::message("\Обработка события BeginSSR (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginSSR().disconnect(beginssr_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginSSR при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginSSR().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginSSR().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndSSR () const

событие, генерируемое после этапом рендеринга SSR. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndSSR
void endssr_event_handler()
{
	Log::message("\Обработка события EndSSR\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endssr_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndSSR().connect(endssr_event_connections, endssr_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndSSR().connect(endssr_event_connections, []() {
		Log::message("\Обработка события EndSSR (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endssr_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endssr_event_connection;

// подписываемся на событие EndSSR с функцией-обработчиком, сохраняя соединение
publisher->getEventEndSSR().connect(endssr_event_connection, endssr_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endssr_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endssr_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndSSR через соединение
endssr_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndSSR, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndSSR\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndSSR().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endssr_handler_id;

// подписываемся на событие EndSSR с лямбда-обработчиком, сохраняя идентификатор соединения
endssr_handler_id = publisher->getEventEndSSR().connect(e_connections, []() {
		Log::message("\Обработка события EndSSR (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndSSR().disconnect(endssr_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndSSR при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndSSR().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndSSR().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginSSAO () const

событие, генерируемое перед этапом рендеринга SSAO. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginSSAO
void beginssao_event_handler()
{
	Log::message("\Обработка события BeginSSAO\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginssao_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginSSAO().connect(beginssao_event_connections, beginssao_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginSSAO().connect(beginssao_event_connections, []() {
		Log::message("\Обработка события BeginSSAO (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginssao_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginssao_event_connection;

// подписываемся на событие BeginSSAO с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginSSAO().connect(beginssao_event_connection, beginssao_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginssao_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginssao_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginSSAO через соединение
beginssao_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginSSAO, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginSSAO\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginSSAO().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginssao_handler_id;

// подписываемся на событие BeginSSAO с лямбда-обработчиком, сохраняя идентификатор соединения
beginssao_handler_id = publisher->getEventBeginSSAO().connect(e_connections, []() {
		Log::message("\Обработка события BeginSSAO (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginSSAO().disconnect(beginssao_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginSSAO при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginSSAO().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginSSAO().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndSSAO () const

событие, генерируемое после этапом рендеринга SSAO. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndSSAO
void endssao_event_handler()
{
	Log::message("\Обработка события EndSSAO\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endssao_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndSSAO().connect(endssao_event_connections, endssao_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndSSAO().connect(endssao_event_connections, []() {
		Log::message("\Обработка события EndSSAO (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endssao_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endssao_event_connection;

// подписываемся на событие EndSSAO с функцией-обработчиком, сохраняя соединение
publisher->getEventEndSSAO().connect(endssao_event_connection, endssao_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endssao_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endssao_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndSSAO через соединение
endssao_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndSSAO, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndSSAO\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndSSAO().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endssao_handler_id;

// подписываемся на событие EndSSAO с лямбда-обработчиком, сохраняя идентификатор соединения
endssao_handler_id = publisher->getEventEndSSAO().connect(e_connections, []() {
		Log::message("\Обработка события EndSSAO (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndSSAO().disconnect(endssao_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndSSAO при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndSSAO().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndSSAO().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginSSGI () const

событие, генерируемое перед этапом рендеринга SSGI. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginSSGI
void beginssgi_event_handler()
{
	Log::message("\Обработка события BeginSSGI\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginssgi_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginSSGI().connect(beginssgi_event_connections, beginssgi_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginSSGI().connect(beginssgi_event_connections, []() {
		Log::message("\Обработка события BeginSSGI (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginssgi_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginssgi_event_connection;

// подписываемся на событие BeginSSGI с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginSSGI().connect(beginssgi_event_connection, beginssgi_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginssgi_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginssgi_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginSSGI через соединение
beginssgi_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginSSGI, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginSSGI\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginSSGI().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginssgi_handler_id;

// подписываемся на событие BeginSSGI с лямбда-обработчиком, сохраняя идентификатор соединения
beginssgi_handler_id = publisher->getEventBeginSSGI().connect(e_connections, []() {
		Log::message("\Обработка события BeginSSGI (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginSSGI().disconnect(beginssgi_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginSSGI при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginSSGI().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginSSGI().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndSSGI () const

событие, генерируемое после этапом рендеринга SSGI. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndSSGI
void endssgi_event_handler()
{
	Log::message("\Обработка события EndSSGI\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endssgi_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndSSGI().connect(endssgi_event_connections, endssgi_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndSSGI().connect(endssgi_event_connections, []() {
		Log::message("\Обработка события EndSSGI (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endssgi_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endssgi_event_connection;

// подписываемся на событие EndSSGI с функцией-обработчиком, сохраняя соединение
publisher->getEventEndSSGI().connect(endssgi_event_connection, endssgi_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endssgi_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endssgi_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndSSGI через соединение
endssgi_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndSSGI, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndSSGI\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndSSGI().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endssgi_handler_id;

// подписываемся на событие EndSSGI с лямбда-обработчиком, сохраняя идентификатор соединения
endssgi_handler_id = publisher->getEventEndSSGI().connect(e_connections, []() {
		Log::message("\Обработка события EndSSGI (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndSSGI().disconnect(endssgi_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndSSGI при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndSSGI().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndSSGI().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginSky () const

событие, генерируемое перед этапом рендеринга неба. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginSky
void beginsky_event_handler()
{
	Log::message("\Обработка события BeginSky\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginsky_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginSky().connect(beginsky_event_connections, beginsky_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginSky().connect(beginsky_event_connections, []() {
		Log::message("\Обработка события BeginSky (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginsky_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginsky_event_connection;

// подписываемся на событие BeginSky с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginSky().connect(beginsky_event_connection, beginsky_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginsky_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginsky_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginSky через соединение
beginsky_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginSky, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginSky\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginSky().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginsky_handler_id;

// подписываемся на событие BeginSky с лямбда-обработчиком, сохраняя идентификатор соединения
beginsky_handler_id = publisher->getEventBeginSky().connect(e_connections, []() {
		Log::message("\Обработка события BeginSky (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginSky().disconnect(beginsky_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginSky при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginSky().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginSky().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndSky () const

событие, генерируемое после этапом рендеринга неба. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndSky
void endsky_event_handler()
{
	Log::message("\Обработка события EndSky\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endsky_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndSky().connect(endsky_event_connections, endsky_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndSky().connect(endsky_event_connections, []() {
		Log::message("\Обработка события EndSky (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endsky_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endsky_event_connection;

// подписываемся на событие EndSky с функцией-обработчиком, сохраняя соединение
publisher->getEventEndSky().connect(endsky_event_connection, endsky_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endsky_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endsky_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndSky через соединение
endsky_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndSky, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndSky\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndSky().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endsky_handler_id;

// подписываемся на событие EndSky с лямбда-обработчиком, сохраняя идентификатор соединения
endsky_handler_id = publisher->getEventEndSky().connect(e_connections, []() {
		Log::message("\Обработка события EndSky (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndSky().disconnect(endsky_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndSky при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndSky().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndSky().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginCompositeDeferred () const

событие, генерируемое перед этапом отложенной композиции облаков. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginCompositeDeferred
void begincompositedeferred_event_handler()
{
	Log::message("\Обработка события BeginCompositeDeferred\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections begincompositedeferred_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginCompositeDeferred().connect(begincompositedeferred_event_connections, begincompositedeferred_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginCompositeDeferred().connect(begincompositedeferred_event_connections, []() {
		Log::message("\Обработка события BeginCompositeDeferred (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
begincompositedeferred_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection begincompositedeferred_event_connection;

// подписываемся на событие BeginCompositeDeferred с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginCompositeDeferred().connect(begincompositedeferred_event_connection, begincompositedeferred_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
begincompositedeferred_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
begincompositedeferred_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginCompositeDeferred через соединение
begincompositedeferred_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginCompositeDeferred, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginCompositeDeferred\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginCompositeDeferred().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId begincompositedeferred_handler_id;

// подписываемся на событие BeginCompositeDeferred с лямбда-обработчиком, сохраняя идентификатор соединения
begincompositedeferred_handler_id = publisher->getEventBeginCompositeDeferred().connect(e_connections, []() {
		Log::message("\Обработка события BeginCompositeDeferred (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginCompositeDeferred().disconnect(begincompositedeferred_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginCompositeDeferred при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginCompositeDeferred().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginCompositeDeferred().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndCompositeDeferred () const

событие, генерируемое после этапом отложенной композиции облаков. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndCompositeDeferred
void endcompositedeferred_event_handler()
{
	Log::message("\Обработка события EndCompositeDeferred\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endcompositedeferred_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndCompositeDeferred().connect(endcompositedeferred_event_connections, endcompositedeferred_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndCompositeDeferred().connect(endcompositedeferred_event_connections, []() {
		Log::message("\Обработка события EndCompositeDeferred (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endcompositedeferred_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endcompositedeferred_event_connection;

// подписываемся на событие EndCompositeDeferred с функцией-обработчиком, сохраняя соединение
publisher->getEventEndCompositeDeferred().connect(endcompositedeferred_event_connection, endcompositedeferred_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endcompositedeferred_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endcompositedeferred_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndCompositeDeferred через соединение
endcompositedeferred_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndCompositeDeferred, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndCompositeDeferred\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndCompositeDeferred().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endcompositedeferred_handler_id;

// подписываемся на событие EndCompositeDeferred с лямбда-обработчиком, сохраняя идентификатор соединения
endcompositedeferred_handler_id = publisher->getEventEndCompositeDeferred().connect(e_connections, []() {
		Log::message("\Обработка события EndCompositeDeferred (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndCompositeDeferred().disconnect(endcompositedeferred_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndCompositeDeferred при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndCompositeDeferred().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndCompositeDeferred().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginTransparent () const

событие, генерируемое перед этапом рендеринга прозрачных объектов. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginTransparent
void begintransparent_event_handler()
{
	Log::message("\Обработка события BeginTransparent\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections begintransparent_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginTransparent().connect(begintransparent_event_connections, begintransparent_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginTransparent().connect(begintransparent_event_connections, []() {
		Log::message("\Обработка события BeginTransparent (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
begintransparent_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection begintransparent_event_connection;

// подписываемся на событие BeginTransparent с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginTransparent().connect(begintransparent_event_connection, begintransparent_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
begintransparent_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
begintransparent_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginTransparent через соединение
begintransparent_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginTransparent, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginTransparent\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginTransparent().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId begintransparent_handler_id;

// подписываемся на событие BeginTransparent с лямбда-обработчиком, сохраняя идентификатор соединения
begintransparent_handler_id = publisher->getEventBeginTransparent().connect(e_connections, []() {
		Log::message("\Обработка события BeginTransparent (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginTransparent().disconnect(begintransparent_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginTransparent при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginTransparent().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginTransparent().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginClouds () const

событие, генерируемое перед этапом рендеринга облаков. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginClouds
void beginclouds_event_handler()
{
	Log::message("\Обработка события BeginClouds\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginclouds_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginClouds().connect(beginclouds_event_connections, beginclouds_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginClouds().connect(beginclouds_event_connections, []() {
		Log::message("\Обработка события BeginClouds (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginclouds_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginclouds_event_connection;

// подписываемся на событие BeginClouds с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginClouds().connect(beginclouds_event_connection, beginclouds_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginclouds_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginclouds_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginClouds через соединение
beginclouds_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginClouds, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginClouds\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginClouds().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginclouds_handler_id;

// подписываемся на событие BeginClouds с лямбда-обработчиком, сохраняя идентификатор соединения
beginclouds_handler_id = publisher->getEventBeginClouds().connect(e_connections, []() {
		Log::message("\Обработка события BeginClouds (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginClouds().disconnect(beginclouds_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginClouds при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginClouds().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginClouds().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndClouds () const

событие, генерируемое после этапом рендеринга облаков. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndClouds
void endclouds_event_handler()
{
	Log::message("\Обработка события EndClouds\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endclouds_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndClouds().connect(endclouds_event_connections, endclouds_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndClouds().connect(endclouds_event_connections, []() {
		Log::message("\Обработка события EndClouds (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endclouds_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endclouds_event_connection;

// подписываемся на событие EndClouds с функцией-обработчиком, сохраняя соединение
publisher->getEventEndClouds().connect(endclouds_event_connection, endclouds_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endclouds_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endclouds_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndClouds через соединение
endclouds_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndClouds, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndClouds\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndClouds().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endclouds_handler_id;

// подписываемся на событие EndClouds с лямбда-обработчиком, сохраняя идентификатор соединения
endclouds_handler_id = publisher->getEventEndClouds().connect(e_connections, []() {
		Log::message("\Обработка события EndClouds (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndClouds().disconnect(endclouds_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndClouds при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndClouds().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndClouds().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginWater () const

событие, генерируемое перед этапом рендеринга воды. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginWater
void beginwater_event_handler()
{
	Log::message("\Обработка события BeginWater\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginwater_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginWater().connect(beginwater_event_connections, beginwater_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginWater().connect(beginwater_event_connections, []() {
		Log::message("\Обработка события BeginWater (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginwater_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginwater_event_connection;

// подписываемся на событие BeginWater с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginWater().connect(beginwater_event_connection, beginwater_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginwater_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginwater_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginWater через соединение
beginwater_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginWater, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginWater\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginWater().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginwater_handler_id;

// подписываемся на событие BeginWater с лямбда-обработчиком, сохраняя идентификатор соединения
beginwater_handler_id = publisher->getEventBeginWater().connect(e_connections, []() {
		Log::message("\Обработка события BeginWater (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginWater().disconnect(beginwater_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginWater при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginWater().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginWater().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginWaterGBuffer () const

событие, генерируемое перед этапом рендеринга Water G-Buffer. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginWaterGBuffer
void beginwatergbuffer_event_handler()
{
	Log::message("\Обработка события BeginWaterGBuffer\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginwatergbuffer_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginWaterGBuffer().connect(beginwatergbuffer_event_connections, beginwatergbuffer_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginWaterGBuffer().connect(beginwatergbuffer_event_connections, []() {
		Log::message("\Обработка события BeginWaterGBuffer (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginwatergbuffer_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginwatergbuffer_event_connection;

// подписываемся на событие BeginWaterGBuffer с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginWaterGBuffer().connect(beginwatergbuffer_event_connection, beginwatergbuffer_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginwatergbuffer_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginwatergbuffer_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginWaterGBuffer через соединение
beginwatergbuffer_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginWaterGBuffer, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginWaterGBuffer\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginWaterGBuffer().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginwatergbuffer_handler_id;

// подписываемся на событие BeginWaterGBuffer с лямбда-обработчиком, сохраняя идентификатор соединения
beginwatergbuffer_handler_id = publisher->getEventBeginWaterGBuffer().connect(e_connections, []() {
		Log::message("\Обработка события BeginWaterGBuffer (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginWaterGBuffer().disconnect(beginwatergbuffer_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginWaterGBuffer при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginWaterGBuffer().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginWaterGBuffer().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndWaterGBuffer () const

событие, генерируемое после этапом рендеринга Water G-Buffer. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndWaterGBuffer
void endwatergbuffer_event_handler()
{
	Log::message("\Обработка события EndWaterGBuffer\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endwatergbuffer_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndWaterGBuffer().connect(endwatergbuffer_event_connections, endwatergbuffer_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndWaterGBuffer().connect(endwatergbuffer_event_connections, []() {
		Log::message("\Обработка события EndWaterGBuffer (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endwatergbuffer_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endwatergbuffer_event_connection;

// подписываемся на событие EndWaterGBuffer с функцией-обработчиком, сохраняя соединение
publisher->getEventEndWaterGBuffer().connect(endwatergbuffer_event_connection, endwatergbuffer_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endwatergbuffer_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endwatergbuffer_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndWaterGBuffer через соединение
endwatergbuffer_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndWaterGBuffer, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndWaterGBuffer\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndWaterGBuffer().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endwatergbuffer_handler_id;

// подписываемся на событие EndWaterGBuffer с лямбда-обработчиком, сохраняя идентификатор соединения
endwatergbuffer_handler_id = publisher->getEventEndWaterGBuffer().connect(e_connections, []() {
		Log::message("\Обработка события EndWaterGBuffer (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndWaterGBuffer().disconnect(endwatergbuffer_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndWaterGBuffer при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndWaterGBuffer().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndWaterGBuffer().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginWaterDecals () const

событие, генерируемое перед этапом рендеринга декалей воды. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginWaterDecals
void beginwaterdecals_event_handler()
{
	Log::message("\Обработка события BeginWaterDecals\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginwaterdecals_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginWaterDecals().connect(beginwaterdecals_event_connections, beginwaterdecals_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginWaterDecals().connect(beginwaterdecals_event_connections, []() {
		Log::message("\Обработка события BeginWaterDecals (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginwaterdecals_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginwaterdecals_event_connection;

// подписываемся на событие BeginWaterDecals с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginWaterDecals().connect(beginwaterdecals_event_connection, beginwaterdecals_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginwaterdecals_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginwaterdecals_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginWaterDecals через соединение
beginwaterdecals_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginWaterDecals, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginWaterDecals\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginWaterDecals().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginwaterdecals_handler_id;

// подписываемся на событие BeginWaterDecals с лямбда-обработчиком, сохраняя идентификатор соединения
beginwaterdecals_handler_id = publisher->getEventBeginWaterDecals().connect(e_connections, []() {
		Log::message("\Обработка события BeginWaterDecals (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginWaterDecals().disconnect(beginwaterdecals_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginWaterDecals при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginWaterDecals().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginWaterDecals().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndWaterDecals () const

событие, генерируемое после этапом рендеринга декалей воды. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndWaterDecals
void endwaterdecals_event_handler()
{
	Log::message("\Обработка события EndWaterDecals\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endwaterdecals_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndWaterDecals().connect(endwaterdecals_event_connections, endwaterdecals_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndWaterDecals().connect(endwaterdecals_event_connections, []() {
		Log::message("\Обработка события EndWaterDecals (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endwaterdecals_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endwaterdecals_event_connection;

// подписываемся на событие EndWaterDecals с функцией-обработчиком, сохраняя соединение
publisher->getEventEndWaterDecals().connect(endwaterdecals_event_connection, endwaterdecals_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endwaterdecals_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endwaterdecals_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndWaterDecals через соединение
endwaterdecals_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndWaterDecals, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndWaterDecals\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndWaterDecals().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endwaterdecals_handler_id;

// подписываемся на событие EndWaterDecals с лямбда-обработчиком, сохраняя идентификатор соединения
endwaterdecals_handler_id = publisher->getEventEndWaterDecals().connect(e_connections, []() {
		Log::message("\Обработка события EndWaterDecals (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndWaterDecals().disconnect(endwaterdecals_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndWaterDecals при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndWaterDecals().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndWaterDecals().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginWaterLights () const

событие, генерируемое перед этапом рендеринга источников света воды. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginWaterLights
void beginwaterlights_event_handler()
{
	Log::message("\Обработка события BeginWaterLights\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginwaterlights_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginWaterLights().connect(beginwaterlights_event_connections, beginwaterlights_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginWaterLights().connect(beginwaterlights_event_connections, []() {
		Log::message("\Обработка события BeginWaterLights (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginwaterlights_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginwaterlights_event_connection;

// подписываемся на событие BeginWaterLights с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginWaterLights().connect(beginwaterlights_event_connection, beginwaterlights_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginwaterlights_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginwaterlights_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginWaterLights через соединение
beginwaterlights_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginWaterLights, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginWaterLights\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginWaterLights().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginwaterlights_handler_id;

// подписываемся на событие BeginWaterLights с лямбда-обработчиком, сохраняя идентификатор соединения
beginwaterlights_handler_id = publisher->getEventBeginWaterLights().connect(e_connections, []() {
		Log::message("\Обработка события BeginWaterLights (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginWaterLights().disconnect(beginwaterlights_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginWaterLights при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginWaterLights().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginWaterLights().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndWaterLights () const

событие, генерируемое после этапом рендеринга источников света воды. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndWaterLights
void endwaterlights_event_handler()
{
	Log::message("\Обработка события EndWaterLights\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endwaterlights_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndWaterLights().connect(endwaterlights_event_connections, endwaterlights_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndWaterLights().connect(endwaterlights_event_connections, []() {
		Log::message("\Обработка события EndWaterLights (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endwaterlights_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endwaterlights_event_connection;

// подписываемся на событие EndWaterLights с функцией-обработчиком, сохраняя соединение
publisher->getEventEndWaterLights().connect(endwaterlights_event_connection, endwaterlights_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endwaterlights_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endwaterlights_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndWaterLights через соединение
endwaterlights_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndWaterLights, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndWaterLights\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndWaterLights().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endwaterlights_handler_id;

// подписываемся на событие EndWaterLights с лямбда-обработчиком, сохраняя идентификатор соединения
endwaterlights_handler_id = publisher->getEventEndWaterLights().connect(e_connections, []() {
		Log::message("\Обработка события EndWaterLights (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndWaterLights().disconnect(endwaterlights_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndWaterLights при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndWaterLights().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndWaterLights().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginWaterVoxelProbes () const

событие, генерируемое перед этапом рендеринга воксельных пробников воды. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginWaterVoxelProbes
void beginwatervoxelprobes_event_handler()
{
	Log::message("\Обработка события BeginWaterVoxelProbes\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginwatervoxelprobes_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginWaterVoxelProbes().connect(beginwatervoxelprobes_event_connections, beginwatervoxelprobes_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginWaterVoxelProbes().connect(beginwatervoxelprobes_event_connections, []() {
		Log::message("\Обработка события BeginWaterVoxelProbes (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginwatervoxelprobes_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginwatervoxelprobes_event_connection;

// подписываемся на событие BeginWaterVoxelProbes с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginWaterVoxelProbes().connect(beginwatervoxelprobes_event_connection, beginwatervoxelprobes_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginwatervoxelprobes_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginwatervoxelprobes_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginWaterVoxelProbes через соединение
beginwatervoxelprobes_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginWaterVoxelProbes, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginWaterVoxelProbes\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginWaterVoxelProbes().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginwatervoxelprobes_handler_id;

// подписываемся на событие BeginWaterVoxelProbes с лямбда-обработчиком, сохраняя идентификатор соединения
beginwatervoxelprobes_handler_id = publisher->getEventBeginWaterVoxelProbes().connect(e_connections, []() {
		Log::message("\Обработка события BeginWaterVoxelProbes (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginWaterVoxelProbes().disconnect(beginwatervoxelprobes_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginWaterVoxelProbes при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginWaterVoxelProbes().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginWaterVoxelProbes().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndWaterVoxelProbes () const

событие, генерируемое после этапом рендеринга воксельных пробников воды. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndWaterVoxelProbes
void endwatervoxelprobes_event_handler()
{
	Log::message("\Обработка события EndWaterVoxelProbes\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endwatervoxelprobes_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndWaterVoxelProbes().connect(endwatervoxelprobes_event_connections, endwatervoxelprobes_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndWaterVoxelProbes().connect(endwatervoxelprobes_event_connections, []() {
		Log::message("\Обработка события EndWaterVoxelProbes (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endwatervoxelprobes_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endwatervoxelprobes_event_connection;

// подписываемся на событие EndWaterVoxelProbes с функцией-обработчиком, сохраняя соединение
publisher->getEventEndWaterVoxelProbes().connect(endwatervoxelprobes_event_connection, endwatervoxelprobes_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endwatervoxelprobes_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endwatervoxelprobes_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndWaterVoxelProbes через соединение
endwatervoxelprobes_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndWaterVoxelProbes, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndWaterVoxelProbes\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndWaterVoxelProbes().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endwatervoxelprobes_handler_id;

// подписываемся на событие EndWaterVoxelProbes с лямбда-обработчиком, сохраняя идентификатор соединения
endwatervoxelprobes_handler_id = publisher->getEventEndWaterVoxelProbes().connect(e_connections, []() {
		Log::message("\Обработка события EndWaterVoxelProbes (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndWaterVoxelProbes().disconnect(endwatervoxelprobes_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndWaterVoxelProbes при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndWaterVoxelProbes().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndWaterVoxelProbes().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginWaterEnvironmentProbes () const

событие, генерируемое перед этапом рендеринга пробников окружения воды. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginWaterEnvironmentProbes
void beginwaterenvironmentprobes_event_handler()
{
	Log::message("\Обработка события BeginWaterEnvironmentProbes\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginwaterenvironmentprobes_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginWaterEnvironmentProbes().connect(beginwaterenvironmentprobes_event_connections, beginwaterenvironmentprobes_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginWaterEnvironmentProbes().connect(beginwaterenvironmentprobes_event_connections, []() {
		Log::message("\Обработка события BeginWaterEnvironmentProbes (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginwaterenvironmentprobes_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginwaterenvironmentprobes_event_connection;

// подписываемся на событие BeginWaterEnvironmentProbes с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginWaterEnvironmentProbes().connect(beginwaterenvironmentprobes_event_connection, beginwaterenvironmentprobes_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginwaterenvironmentprobes_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginwaterenvironmentprobes_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginWaterEnvironmentProbes через соединение
beginwaterenvironmentprobes_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginWaterEnvironmentProbes, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginWaterEnvironmentProbes\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginWaterEnvironmentProbes().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginwaterenvironmentprobes_handler_id;

// подписываемся на событие BeginWaterEnvironmentProbes с лямбда-обработчиком, сохраняя идентификатор соединения
beginwaterenvironmentprobes_handler_id = publisher->getEventBeginWaterEnvironmentProbes().connect(e_connections, []() {
		Log::message("\Обработка события BeginWaterEnvironmentProbes (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginWaterEnvironmentProbes().disconnect(beginwaterenvironmentprobes_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginWaterEnvironmentProbes при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginWaterEnvironmentProbes().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginWaterEnvironmentProbes().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndWaterEnvironmentProbes () const

событие, генерируемое после этапом рендеринга пробников окружения воды. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndWaterEnvironmentProbes
void endwaterenvironmentprobes_event_handler()
{
	Log::message("\Обработка события EndWaterEnvironmentProbes\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endwaterenvironmentprobes_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndWaterEnvironmentProbes().connect(endwaterenvironmentprobes_event_connections, endwaterenvironmentprobes_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndWaterEnvironmentProbes().connect(endwaterenvironmentprobes_event_connections, []() {
		Log::message("\Обработка события EndWaterEnvironmentProbes (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endwaterenvironmentprobes_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endwaterenvironmentprobes_event_connection;

// подписываемся на событие EndWaterEnvironmentProbes с функцией-обработчиком, сохраняя соединение
publisher->getEventEndWaterEnvironmentProbes().connect(endwaterenvironmentprobes_event_connection, endwaterenvironmentprobes_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endwaterenvironmentprobes_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endwaterenvironmentprobes_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndWaterEnvironmentProbes через соединение
endwaterenvironmentprobes_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndWaterEnvironmentProbes, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndWaterEnvironmentProbes\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndWaterEnvironmentProbes().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endwaterenvironmentprobes_handler_id;

// подписываемся на событие EndWaterEnvironmentProbes с лямбда-обработчиком, сохраняя идентификатор соединения
endwaterenvironmentprobes_handler_id = publisher->getEventEndWaterEnvironmentProbes().connect(e_connections, []() {
		Log::message("\Обработка события EndWaterEnvironmentProbes (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndWaterEnvironmentProbes().disconnect(endwaterenvironmentprobes_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndWaterEnvironmentProbes при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndWaterEnvironmentProbes().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndWaterEnvironmentProbes().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginWaterPlanarProbes () const

событие, генерируемое перед этапом рендеринга плоских пробников воды. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginWaterPlanarProbes
void beginwaterplanarprobes_event_handler()
{
	Log::message("\Обработка события BeginWaterPlanarProbes\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginwaterplanarprobes_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginWaterPlanarProbes().connect(beginwaterplanarprobes_event_connections, beginwaterplanarprobes_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginWaterPlanarProbes().connect(beginwaterplanarprobes_event_connections, []() {
		Log::message("\Обработка события BeginWaterPlanarProbes (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginwaterplanarprobes_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginwaterplanarprobes_event_connection;

// подписываемся на событие BeginWaterPlanarProbes с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginWaterPlanarProbes().connect(beginwaterplanarprobes_event_connection, beginwaterplanarprobes_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginwaterplanarprobes_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginwaterplanarprobes_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginWaterPlanarProbes через соединение
beginwaterplanarprobes_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginWaterPlanarProbes, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginWaterPlanarProbes\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginWaterPlanarProbes().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginwaterplanarprobes_handler_id;

// подписываемся на событие BeginWaterPlanarProbes с лямбда-обработчиком, сохраняя идентификатор соединения
beginwaterplanarprobes_handler_id = publisher->getEventBeginWaterPlanarProbes().connect(e_connections, []() {
		Log::message("\Обработка события BeginWaterPlanarProbes (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginWaterPlanarProbes().disconnect(beginwaterplanarprobes_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginWaterPlanarProbes при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginWaterPlanarProbes().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginWaterPlanarProbes().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndWaterPlanarProbes () const

событие, генерируемое после этапом рендеринга плоских пробников воды. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndWaterPlanarProbes
void endwaterplanarprobes_event_handler()
{
	Log::message("\Обработка события EndWaterPlanarProbes\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endwaterplanarprobes_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndWaterPlanarProbes().connect(endwaterplanarprobes_event_connections, endwaterplanarprobes_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndWaterPlanarProbes().connect(endwaterplanarprobes_event_connections, []() {
		Log::message("\Обработка события EndWaterPlanarProbes (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endwaterplanarprobes_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endwaterplanarprobes_event_connection;

// подписываемся на событие EndWaterPlanarProbes с функцией-обработчиком, сохраняя соединение
publisher->getEventEndWaterPlanarProbes().connect(endwaterplanarprobes_event_connection, endwaterplanarprobes_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endwaterplanarprobes_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endwaterplanarprobes_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndWaterPlanarProbes через соединение
endwaterplanarprobes_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndWaterPlanarProbes, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndWaterPlanarProbes\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndWaterPlanarProbes().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endwaterplanarprobes_handler_id;

// подписываемся на событие EndWaterPlanarProbes с лямбда-обработчиком, сохраняя идентификатор соединения
endwaterplanarprobes_handler_id = publisher->getEventEndWaterPlanarProbes().connect(e_connections, []() {
		Log::message("\Обработка события EndWaterPlanarProbes (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndWaterPlanarProbes().disconnect(endwaterplanarprobes_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndWaterPlanarProbes при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndWaterPlanarProbes().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndWaterPlanarProbes().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndWater () const

событие, генерируемое после этапом рендеринга воды. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndWater
void endwater_event_handler()
{
	Log::message("\Обработка события EndWater\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endwater_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndWater().connect(endwater_event_connections, endwater_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndWater().connect(endwater_event_connections, []() {
		Log::message("\Обработка события EndWater (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endwater_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endwater_event_connection;

// подписываемся на событие EndWater с функцией-обработчиком, сохраняя соединение
publisher->getEventEndWater().connect(endwater_event_connection, endwater_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endwater_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endwater_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndWater через соединение
endwater_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndWater, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndWater\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndWater().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endwater_handler_id;

// подписываемся на событие EndWater с лямбда-обработчиком, сохраняя идентификатор соединения
endwater_handler_id = publisher->getEventEndWater().connect(e_connections, []() {
		Log::message("\Обработка события EndWater (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndWater().disconnect(endwater_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndWater при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndWater().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndWater().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndTransparent () const

событие, генерируемое после этапом рендеринга прозрачных объектов. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndTransparent
void endtransparent_event_handler()
{
	Log::message("\Обработка события EndTransparent\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endtransparent_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndTransparent().connect(endtransparent_event_connections, endtransparent_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndTransparent().connect(endtransparent_event_connections, []() {
		Log::message("\Обработка события EndTransparent (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endtransparent_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endtransparent_event_connection;

// подписываемся на событие EndTransparent с функцией-обработчиком, сохраняя соединение
publisher->getEventEndTransparent().connect(endtransparent_event_connection, endtransparent_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endtransparent_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endtransparent_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndTransparent через соединение
endtransparent_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndTransparent, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndTransparent\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndTransparent().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endtransparent_handler_id;

// подписываемся на событие EndTransparent с лямбда-обработчиком, сохраняя идентификатор соединения
endtransparent_handler_id = publisher->getEventEndTransparent().connect(e_connections, []() {
		Log::message("\Обработка события EndTransparent (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndTransparent().disconnect(endtransparent_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndTransparent при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndTransparent().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndTransparent().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginSrgbCorrection () const

событие, генерируемое перед этапом коррекции sRGB. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginSrgbCorrection
void beginsrgbcorrection_event_handler()
{
	Log::message("\Обработка события BeginSrgbCorrection\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginsrgbcorrection_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginSrgbCorrection().connect(beginsrgbcorrection_event_connections, beginsrgbcorrection_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginSrgbCorrection().connect(beginsrgbcorrection_event_connections, []() {
		Log::message("\Обработка события BeginSrgbCorrection (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginsrgbcorrection_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginsrgbcorrection_event_connection;

// подписываемся на событие BeginSrgbCorrection с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginSrgbCorrection().connect(beginsrgbcorrection_event_connection, beginsrgbcorrection_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginsrgbcorrection_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginsrgbcorrection_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginSrgbCorrection через соединение
beginsrgbcorrection_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginSrgbCorrection, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginSrgbCorrection\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginSrgbCorrection().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginsrgbcorrection_handler_id;

// подписываемся на событие BeginSrgbCorrection с лямбда-обработчиком, сохраняя идентификатор соединения
beginsrgbcorrection_handler_id = publisher->getEventBeginSrgbCorrection().connect(e_connections, []() {
		Log::message("\Обработка события BeginSrgbCorrection (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginSrgbCorrection().disconnect(beginsrgbcorrection_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginSrgbCorrection при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginSrgbCorrection().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginSrgbCorrection().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndSrgbCorrection () const

событие, генерируемое после этапом коррекции sRGB. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndSrgbCorrection
void endsrgbcorrection_event_handler()
{
	Log::message("\Обработка события EndSrgbCorrection\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endsrgbcorrection_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndSrgbCorrection().connect(endsrgbcorrection_event_connections, endsrgbcorrection_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndSrgbCorrection().connect(endsrgbcorrection_event_connections, []() {
		Log::message("\Обработка события EndSrgbCorrection (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endsrgbcorrection_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endsrgbcorrection_event_connection;

// подписываемся на событие EndSrgbCorrection с функцией-обработчиком, сохраняя соединение
publisher->getEventEndSrgbCorrection().connect(endsrgbcorrection_event_connection, endsrgbcorrection_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endsrgbcorrection_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endsrgbcorrection_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndSrgbCorrection через соединение
endsrgbcorrection_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndSrgbCorrection, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndSrgbCorrection\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndSrgbCorrection().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endsrgbcorrection_handler_id;

// подписываемся на событие EndSrgbCorrection с лямбда-обработчиком, сохраняя идентификатор соединения
endsrgbcorrection_handler_id = publisher->getEventEndSrgbCorrection().connect(e_connections, []() {
		Log::message("\Обработка события EndSrgbCorrection (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndSrgbCorrection().disconnect(endsrgbcorrection_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndSrgbCorrection при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndSrgbCorrection().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndSrgbCorrection().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginAdaptationColorAverage () const

событие, генерируемое перед вычислением автоматической экспозиции и коррекции баланса белого. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginAdaptationColorAverage
void beginadaptationcoloraverage_event_handler()
{
	Log::message("\Обработка события BeginAdaptationColorAverage\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginadaptationcoloraverage_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginAdaptationColorAverage().connect(beginadaptationcoloraverage_event_connections, beginadaptationcoloraverage_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginAdaptationColorAverage().connect(beginadaptationcoloraverage_event_connections, []() {
		Log::message("\Обработка события BeginAdaptationColorAverage (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginadaptationcoloraverage_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginadaptationcoloraverage_event_connection;

// подписываемся на событие BeginAdaptationColorAverage с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginAdaptationColorAverage().connect(beginadaptationcoloraverage_event_connection, beginadaptationcoloraverage_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginadaptationcoloraverage_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginadaptationcoloraverage_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginAdaptationColorAverage через соединение
beginadaptationcoloraverage_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginAdaptationColorAverage, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginAdaptationColorAverage\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginAdaptationColorAverage().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginadaptationcoloraverage_handler_id;

// подписываемся на событие BeginAdaptationColorAverage с лямбда-обработчиком, сохраняя идентификатор соединения
beginadaptationcoloraverage_handler_id = publisher->getEventBeginAdaptationColorAverage().connect(e_connections, []() {
		Log::message("\Обработка события BeginAdaptationColorAverage (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginAdaptationColorAverage().disconnect(beginadaptationcoloraverage_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginAdaptationColorAverage при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginAdaptationColorAverage().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginAdaptationColorAverage().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndAdaptationColorAverage () const

событие, генерируемое после вычислением автоматической экспозиции и коррекции баланса белого. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndAdaptationColorAverage
void endadaptationcoloraverage_event_handler()
{
	Log::message("\Обработка события EndAdaptationColorAverage\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endadaptationcoloraverage_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndAdaptationColorAverage().connect(endadaptationcoloraverage_event_connections, endadaptationcoloraverage_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndAdaptationColorAverage().connect(endadaptationcoloraverage_event_connections, []() {
		Log::message("\Обработка события EndAdaptationColorAverage (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endadaptationcoloraverage_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endadaptationcoloraverage_event_connection;

// подписываемся на событие EndAdaptationColorAverage с функцией-обработчиком, сохраняя соединение
publisher->getEventEndAdaptationColorAverage().connect(endadaptationcoloraverage_event_connection, endadaptationcoloraverage_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endadaptationcoloraverage_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endadaptationcoloraverage_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndAdaptationColorAverage через соединение
endadaptationcoloraverage_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndAdaptationColorAverage, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndAdaptationColorAverage\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndAdaptationColorAverage().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endadaptationcoloraverage_handler_id;

// подписываемся на событие EndAdaptationColorAverage с лямбда-обработчиком, сохраняя идентификатор соединения
endadaptationcoloraverage_handler_id = publisher->getEventEndAdaptationColorAverage().connect(e_connections, []() {
		Log::message("\Обработка события EndAdaptationColorAverage (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndAdaptationColorAverage().disconnect(endadaptationcoloraverage_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndAdaptationColorAverage при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndAdaptationColorAverage().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndAdaptationColorAverage().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginAdaptationColor () const

событие, генерируемое перед этапом рендеринга цветовой адаптации (автоматическая экспозиция и коррекция баланса белого). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginAdaptationColor
void beginadaptationcolor_event_handler()
{
	Log::message("\Обработка события BeginAdaptationColor\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginadaptationcolor_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginAdaptationColor().connect(beginadaptationcolor_event_connections, beginadaptationcolor_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginAdaptationColor().connect(beginadaptationcolor_event_connections, []() {
		Log::message("\Обработка события BeginAdaptationColor (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginadaptationcolor_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginadaptationcolor_event_connection;

// подписываемся на событие BeginAdaptationColor с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginAdaptationColor().connect(beginadaptationcolor_event_connection, beginadaptationcolor_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginadaptationcolor_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginadaptationcolor_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginAdaptationColor через соединение
beginadaptationcolor_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginAdaptationColor, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginAdaptationColor\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginAdaptationColor().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginadaptationcolor_handler_id;

// подписываемся на событие BeginAdaptationColor с лямбда-обработчиком, сохраняя идентификатор соединения
beginadaptationcolor_handler_id = publisher->getEventBeginAdaptationColor().connect(e_connections, []() {
		Log::message("\Обработка события BeginAdaptationColor (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginAdaptationColor().disconnect(beginadaptationcolor_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginAdaptationColor при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginAdaptationColor().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginAdaptationColor().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndAdaptationColor () const

событие, генерируемое после этапом рендеринга цветовой адаптации (автоматическая экспозиция и коррекция баланса белого). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndAdaptationColor
void endadaptationcolor_event_handler()
{
	Log::message("\Обработка события EndAdaptationColor\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endadaptationcolor_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndAdaptationColor().connect(endadaptationcolor_event_connections, endadaptationcolor_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndAdaptationColor().connect(endadaptationcolor_event_connections, []() {
		Log::message("\Обработка события EndAdaptationColor (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endadaptationcolor_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endadaptationcolor_event_connection;

// подписываемся на событие EndAdaptationColor с функцией-обработчиком, сохраняя соединение
publisher->getEventEndAdaptationColor().connect(endadaptationcolor_event_connection, endadaptationcolor_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endadaptationcolor_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endadaptationcolor_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndAdaptationColor через соединение
endadaptationcolor_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndAdaptationColor, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndAdaptationColor\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndAdaptationColor().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endadaptationcolor_handler_id;

// подписываемся на событие EndAdaptationColor с лямбда-обработчиком, сохраняя идентификатор соединения
endadaptationcolor_handler_id = publisher->getEventEndAdaptationColor().connect(e_connections, []() {
		Log::message("\Обработка события EndAdaptationColor (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndAdaptationColor().disconnect(endadaptationcolor_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndAdaptationColor при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndAdaptationColor().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndAdaptationColor().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginTAA () const

событие, генерируемое перед проходом Temporal Anti-Aliasing (TAA). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginTAA
void begintaa_event_handler()
{
	Log::message("\Обработка события BeginTAA\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections begintaa_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginTAA().connect(begintaa_event_connections, begintaa_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginTAA().connect(begintaa_event_connections, []() {
		Log::message("\Обработка события BeginTAA (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
begintaa_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection begintaa_event_connection;

// подписываемся на событие BeginTAA с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginTAA().connect(begintaa_event_connection, begintaa_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
begintaa_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
begintaa_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginTAA через соединение
begintaa_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginTAA, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginTAA\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginTAA().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId begintaa_handler_id;

// подписываемся на событие BeginTAA с лямбда-обработчиком, сохраняя идентификатор соединения
begintaa_handler_id = publisher->getEventBeginTAA().connect(e_connections, []() {
		Log::message("\Обработка события BeginTAA (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginTAA().disconnect(begintaa_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginTAA при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginTAA().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginTAA().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndTAA () const

событие, генерируемое после проходом Temporal Anti-Aliasing (TAA). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndTAA
void endtaa_event_handler()
{
	Log::message("\Обработка события EndTAA\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endtaa_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndTAA().connect(endtaa_event_connections, endtaa_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndTAA().connect(endtaa_event_connections, []() {
		Log::message("\Обработка события EndTAA (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endtaa_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endtaa_event_connection;

// подписываемся на событие EndTAA с функцией-обработчиком, сохраняя соединение
publisher->getEventEndTAA().connect(endtaa_event_connection, endtaa_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endtaa_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endtaa_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndTAA через соединение
endtaa_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndTAA, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndTAA\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndTAA().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endtaa_handler_id;

// подписываемся на событие EndTAA с лямбда-обработчиком, сохраняя идентификатор соединения
endtaa_handler_id = publisher->getEventEndTAA().connect(e_connections, []() {
		Log::message("\Обработка события EndTAA (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndTAA().disconnect(endtaa_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndTAA при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndTAA().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndTAA().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginCameraEffects () const

событие, генерируемое перед этапом эффектов камеры. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginCameraEffects
void begincameraeffects_event_handler()
{
	Log::message("\Обработка события BeginCameraEffects\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections begincameraeffects_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginCameraEffects().connect(begincameraeffects_event_connections, begincameraeffects_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginCameraEffects().connect(begincameraeffects_event_connections, []() {
		Log::message("\Обработка события BeginCameraEffects (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
begincameraeffects_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection begincameraeffects_event_connection;

// подписываемся на событие BeginCameraEffects с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginCameraEffects().connect(begincameraeffects_event_connection, begincameraeffects_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
begincameraeffects_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
begincameraeffects_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginCameraEffects через соединение
begincameraeffects_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginCameraEffects, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginCameraEffects\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginCameraEffects().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId begincameraeffects_handler_id;

// подписываемся на событие BeginCameraEffects с лямбда-обработчиком, сохраняя идентификатор соединения
begincameraeffects_handler_id = publisher->getEventBeginCameraEffects().connect(e_connections, []() {
		Log::message("\Обработка события BeginCameraEffects (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginCameraEffects().disconnect(begincameraeffects_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginCameraEffects при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginCameraEffects().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginCameraEffects().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndCameraEffects () const

событие, генерируемое после этапом эффектов камеры. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndCameraEffects
void endcameraeffects_event_handler()
{
	Log::message("\Обработка события EndCameraEffects\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endcameraeffects_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndCameraEffects().connect(endcameraeffects_event_connections, endcameraeffects_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndCameraEffects().connect(endcameraeffects_event_connections, []() {
		Log::message("\Обработка события EndCameraEffects (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endcameraeffects_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endcameraeffects_event_connection;

// подписываемся на событие EndCameraEffects с функцией-обработчиком, сохраняя соединение
publisher->getEventEndCameraEffects().connect(endcameraeffects_event_connection, endcameraeffects_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endcameraeffects_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endcameraeffects_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndCameraEffects через соединение
endcameraeffects_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndCameraEffects, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndCameraEffects\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndCameraEffects().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endcameraeffects_handler_id;

// подписываемся на событие EndCameraEffects с лямбда-обработчиком, сохраняя идентификатор соединения
endcameraeffects_handler_id = publisher->getEventEndCameraEffects().connect(e_connections, []() {
		Log::message("\Обработка события EndCameraEffects (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndCameraEffects().disconnect(endcameraeffects_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndCameraEffects при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndCameraEffects().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndCameraEffects().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginPostMaterials () const

событие, генерируемое перед этапом рендеринга пост-материалов. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginPostMaterials
void beginpostmaterials_event_handler()
{
	Log::message("\Обработка события BeginPostMaterials\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginpostmaterials_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginPostMaterials().connect(beginpostmaterials_event_connections, beginpostmaterials_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginPostMaterials().connect(beginpostmaterials_event_connections, []() {
		Log::message("\Обработка события BeginPostMaterials (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginpostmaterials_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginpostmaterials_event_connection;

// подписываемся на событие BeginPostMaterials с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginPostMaterials().connect(beginpostmaterials_event_connection, beginpostmaterials_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginpostmaterials_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginpostmaterials_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginPostMaterials через соединение
beginpostmaterials_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginPostMaterials, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginPostMaterials\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginPostMaterials().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginpostmaterials_handler_id;

// подписываемся на событие BeginPostMaterials с лямбда-обработчиком, сохраняя идентификатор соединения
beginpostmaterials_handler_id = publisher->getEventBeginPostMaterials().connect(e_connections, []() {
		Log::message("\Обработка события BeginPostMaterials (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginPostMaterials().disconnect(beginpostmaterials_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginPostMaterials при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginPostMaterials().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginPostMaterials().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndPostMaterials () const

событие, генерируемое после этапом рендеринга пост-материалов. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndPostMaterials
void endpostmaterials_event_handler()
{
	Log::message("\Обработка события EndPostMaterials\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endpostmaterials_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndPostMaterials().connect(endpostmaterials_event_connections, endpostmaterials_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndPostMaterials().connect(endpostmaterials_event_connections, []() {
		Log::message("\Обработка события EndPostMaterials (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endpostmaterials_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endpostmaterials_event_connection;

// подписываемся на событие EndPostMaterials с функцией-обработчиком, сохраняя соединение
publisher->getEventEndPostMaterials().connect(endpostmaterials_event_connection, endpostmaterials_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endpostmaterials_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endpostmaterials_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndPostMaterials через соединение
endpostmaterials_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndPostMaterials, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndPostMaterials\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndPostMaterials().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endpostmaterials_handler_id;

// подписываемся на событие EndPostMaterials с лямбда-обработчиком, сохраняя идентификатор соединения
endpostmaterials_handler_id = publisher->getEventEndPostMaterials().connect(e_connections, []() {
		Log::message("\Обработка события EndPostMaterials (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndPostMaterials().disconnect(endpostmaterials_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndPostMaterials при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndPostMaterials().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndPostMaterials().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginDebugMaterials () const

событие, генерируемое перед этапом отладочных материалов. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginDebugMaterials
void begindebugmaterials_event_handler()
{
	Log::message("\Обработка события BeginDebugMaterials\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections begindebugmaterials_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginDebugMaterials().connect(begindebugmaterials_event_connections, begindebugmaterials_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginDebugMaterials().connect(begindebugmaterials_event_connections, []() {
		Log::message("\Обработка события BeginDebugMaterials (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
begindebugmaterials_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection begindebugmaterials_event_connection;

// подписываемся на событие BeginDebugMaterials с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginDebugMaterials().connect(begindebugmaterials_event_connection, begindebugmaterials_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
begindebugmaterials_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
begindebugmaterials_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginDebugMaterials через соединение
begindebugmaterials_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginDebugMaterials, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginDebugMaterials\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginDebugMaterials().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId begindebugmaterials_handler_id;

// подписываемся на событие BeginDebugMaterials с лямбда-обработчиком, сохраняя идентификатор соединения
begindebugmaterials_handler_id = publisher->getEventBeginDebugMaterials().connect(e_connections, []() {
		Log::message("\Обработка события BeginDebugMaterials (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginDebugMaterials().disconnect(begindebugmaterials_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginDebugMaterials при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginDebugMaterials().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginDebugMaterials().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndDebugMaterials () const

событие, генерируемое после этапом отладочных материалов. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndDebugMaterials
void enddebugmaterials_event_handler()
{
	Log::message("\Обработка события EndDebugMaterials\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections enddebugmaterials_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndDebugMaterials().connect(enddebugmaterials_event_connections, enddebugmaterials_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndDebugMaterials().connect(enddebugmaterials_event_connections, []() {
		Log::message("\Обработка события EndDebugMaterials (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
enddebugmaterials_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection enddebugmaterials_event_connection;

// подписываемся на событие EndDebugMaterials с функцией-обработчиком, сохраняя соединение
publisher->getEventEndDebugMaterials().connect(enddebugmaterials_event_connection, enddebugmaterials_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
enddebugmaterials_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
enddebugmaterials_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndDebugMaterials через соединение
enddebugmaterials_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndDebugMaterials, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndDebugMaterials\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndDebugMaterials().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId enddebugmaterials_handler_id;

// подписываемся на событие EndDebugMaterials с лямбда-обработчиком, сохраняя идентификатор соединения
enddebugmaterials_handler_id = publisher->getEventEndDebugMaterials().connect(e_connections, []() {
		Log::message("\Обработка события EndDebugMaterials (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndDebugMaterials().disconnect(enddebugmaterials_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndDebugMaterials при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndDebugMaterials().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndDebugMaterials().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventBeginVisualizer () const

событие, генерируемое перед этапом рендеринга визуализатора. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginVisualizer
void beginvisualizer_event_handler()
{
	Log::message("\Обработка события BeginVisualizer\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginvisualizer_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginVisualizer().connect(beginvisualizer_event_connections, beginvisualizer_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginVisualizer().connect(beginvisualizer_event_connections, []() {
		Log::message("\Обработка события BeginVisualizer (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginvisualizer_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginvisualizer_event_connection;

// подписываемся на событие BeginVisualizer с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginVisualizer().connect(beginvisualizer_event_connection, beginvisualizer_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginvisualizer_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginvisualizer_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginVisualizer через соединение
beginvisualizer_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginVisualizer, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginVisualizer\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginVisualizer().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginvisualizer_handler_id;

// подписываемся на событие BeginVisualizer с лямбда-обработчиком, сохраняя идентификатор соединения
beginvisualizer_handler_id = publisher->getEventBeginVisualizer().connect(e_connections, []() {
		Log::message("\Обработка события BeginVisualizer (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginVisualizer().disconnect(beginvisualizer_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginVisualizer при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginVisualizer().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginVisualizer().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndVisualizer () const

событие, генерируемое после этапом рендеринга визуализатора. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndVisualizer
void endvisualizer_event_handler()
{
	Log::message("\Обработка события EndVisualizer\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endvisualizer_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndVisualizer().connect(endvisualizer_event_connections, endvisualizer_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndVisualizer().connect(endvisualizer_event_connections, []() {
		Log::message("\Обработка события EndVisualizer (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endvisualizer_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endvisualizer_event_connection;

// подписываемся на событие EndVisualizer с функцией-обработчиком, сохраняя соединение
publisher->getEventEndVisualizer().connect(endvisualizer_event_connection, endvisualizer_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endvisualizer_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endvisualizer_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndVisualizer через соединение
endvisualizer_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndVisualizer, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndVisualizer\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndVisualizer().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endvisualizer_handler_id;

// подписываемся на событие EndVisualizer с лямбда-обработчиком, сохраняя идентификатор соединения
endvisualizer_handler_id = publisher->getEventEndVisualizer().connect(e_connections, []() {
		Log::message("\Обработка события EndVisualizer (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndVisualizer().disconnect(endvisualizer_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndVisualizer при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndVisualizer().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndVisualizer().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndScreen () const

событие, генерируемое после этапом рендеринга каждого экрана (стереоизображение имеет 2 экрана, а кубическая карта - 6). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndScreen
void endscreen_event_handler()
{
	Log::message("\Обработка события EndScreen\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endscreen_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndScreen().connect(endscreen_event_connections, endscreen_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndScreen().connect(endscreen_event_connections, []() {
		Log::message("\Обработка события EndScreen (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endscreen_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endscreen_event_connection;

// подписываемся на событие EndScreen с функцией-обработчиком, сохраняя соединение
publisher->getEventEndScreen().connect(endscreen_event_connection, endscreen_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endscreen_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endscreen_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndScreen через соединение
endscreen_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndScreen, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndScreen\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndScreen().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endscreen_handler_id;

// подписываемся на событие EndScreen с лямбда-обработчиком, сохраняя идентификатор соединения
endscreen_handler_id = publisher->getEventEndScreen().connect(e_connections, []() {
		Log::message("\Обработка события EndScreen (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndScreen().disconnect(endscreen_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndScreen при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndScreen().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndScreen().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEnd () const

событие, генерируемое после завершения рендеринга кадра. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события End
void end_event_handler()
{
	Log::message("\Обработка события End\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections end_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEnd().connect(end_event_connections, end_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEnd().connect(end_event_connections, []() {
		Log::message("\Обработка события End (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
end_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection end_event_connection;

// подписываемся на событие End с функцией-обработчиком, сохраняя соединение
publisher->getEventEnd().connect(end_event_connection, end_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
end_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
end_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие End через соединение
end_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события End, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события End\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEnd().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId end_handler_id;

// подписываемся на событие End с лямбда-обработчиком, сохраняя идентификатор соединения
end_handler_id = publisher->getEventEnd().connect(e_connections, []() {
		Log::message("\Обработка события End (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEnd().disconnect(end_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий End при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEnd().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEnd().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<> getEventEndVRQuadComposeEyeSwapchains () const

Event triggered after composing VR viewports, enabling you to subscribe and perform certain actions (e.g. implement a binoculars effect using post-materials). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndVRQuadComposeEyeSwapchains
void endvrquadcomposeeyeswapchains_event_handler()
{
	Log::message("\Обработка события EndVRQuadComposeEyeSwapchains\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endvrquadcomposeeyeswapchains_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndVRQuadComposeEyeSwapchains().connect(endvrquadcomposeeyeswapchains_event_connections, endvrquadcomposeeyeswapchains_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndVRQuadComposeEyeSwapchains().connect(endvrquadcomposeeyeswapchains_event_connections, []() {
		Log::message("\Обработка события EndVRQuadComposeEyeSwapchains (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endvrquadcomposeeyeswapchains_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endvrquadcomposeeyeswapchains_event_connection;

// подписываемся на событие EndVRQuadComposeEyeSwapchains с функцией-обработчиком, сохраняя соединение
publisher->getEventEndVRQuadComposeEyeSwapchains().connect(endvrquadcomposeeyeswapchains_event_connection, endvrquadcomposeeyeswapchains_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endvrquadcomposeeyeswapchains_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endvrquadcomposeeyeswapchains_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndVRQuadComposeEyeSwapchains через соединение
endvrquadcomposeeyeswapchains_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndVRQuadComposeEyeSwapchains, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndVRQuadComposeEyeSwapchains\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndVRQuadComposeEyeSwapchains().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endvrquadcomposeeyeswapchains_handler_id;

// подписываемся на событие EndVRQuadComposeEyeSwapchains с лямбда-обработчиком, сохраняя идентификатор соединения
endvrquadcomposeeyeswapchains_handler_id = publisher->getEventEndVRQuadComposeEyeSwapchains().connect(e_connections, []() {
		Log::message("\Обработка события EndVRQuadComposeEyeSwapchains (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndVRQuadComposeEyeSwapchains().disconnect(endvrquadcomposeeyeswapchains_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndVRQuadComposeEyeSwapchains при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndVRQuadComposeEyeSwapchains().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndVRQuadComposeEyeSwapchains().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## static ViewportPtr create ( )

Создаёт новый вьюпорт с настройками по умолчанию.
> **Notice:** Не рекомендуется создавать вьюпорт каждый кадр, так как такой подход неоптимален и расходует ресурсы GPU. Вместо этого создавайте вьюпорты в **init()**, чтобы они были закэшированы для дальнейшего использования.


## void appendSkipFlags ( int flags )

Добавляет указанные [skip flags](#SKIP_SHADOWS) к списку текущих используемых.
### Аргументы

- *int* **flags** - [Skip flags](#SKIP_SHADOWS) для добавления.

## int checkSkipFlags ( int flags )

Возвращает значение, указывающее, установлены ли указанные [skip flags](#SKIP_SHADOWS) для текущего вьюпорта.
### Аргументы

- *int* **flags** - [Skip flags](#SKIP_SHADOWS) для проверки.

### Возвращаемое значение

1, если флаги пропуска установлены; иначе 0.
## void removeSkipFlags ( int flags )

Удаляет указанные [skip flags](#SKIP_SHADOWS) из списка текущих используемых.
### Аргументы

- *int* **flags** - [Skip flags](#SKIP_SHADOWS) для удаления.

## void render ( const Ptr < Camera > & camera )


Рендерит изображение с указанной камеры. Этот метод используется для интеграции движка со сторонним рендерером.


Чтобы рендерить изображение с камеры в интерфейс [RenderTarget](../../../api/library/rendering/class.rendertarget_cpp.md), выполните следующее:


```cpp
camera = Camera::create();

render_target->enable();
{
	viewport->render(camera);
}
render_target->disable();

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera** - Камера, с которой должно рендериться изображение.

## void render ( const Ptr < Camera > & camera , int width , int height )

Рендерит изображение указанного размера с указанной камеры в текущий рендер-таргет.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera** - Камера, с которой должно рендериться изображение.
- *int* **width** - Ширина изображения, в пикселях.
- *int* **height** - Высота изображения, в пикселях.

## void renderEngine ( const Ptr < Camera > & camera )

Рендерит вьюпорт движка для указанной камеры в текущий рендер-таргет. Этот метод рендерит заставку (splash screen) и предоставляет изображение в соответствии с настройками панорамного и стереорендеринга.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera** - Камера, с которой должно рендериться изображение.

## void renderTexture2D ( const Ptr < Camera > & camera , const Ptr < Texture > & texture )

Рендерит изображение с камеры в указанную 2D-текстуру.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera** - Камера, с которой должно рендериться изображение.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Целевая 2D-[texture](../../../api/library/rendering/class.texture_cpp.md) для сохранения результата.

## void renderTexture2D ( const Ptr < Camera > & camera , const Ptr < Texture > & texture , int width , int height , bool hdr = 0 )

Рендерит изображение указанного размера с камеры в 2D-текстуру.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera** - Камера, с которой должно рендериться изображение.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Целевая 2D-[texture](../../../api/library/rendering/class.texture_cpp.md) для сохранения результата.
- *int* **width** - Ширина текстуры, в пикселях.
- *int* **height** - Высота текстуры, в пикселях.
- *bool* **hdr** - Флаг HDR. > **Notice:** Этот параметр определяет формат 2D-текстуры: > - **1** - формат текстуры будет установлен в [**RGBA16F**](../../../api/library/rendering/class.texture_cpp.md#FORMAT_RGBA16F) > - **0** - формат текстуры будет установлен в [**RGBA8**](../../../api/library/rendering/class.texture_cpp.md#FORMAT_RGBA8)

## void renderTextureCube ( const Ptr < Camera > & camera , const Ptr < Texture > & texture , bool local_space = false )

Рендерит изображение с камеры в кубическую текстуру.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera** - Камера, с которой должно рендериться изображение.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Целевая кубическая [texture](../../../api/library/rendering/class.texture_cpp.md) для сохранения результата.
- *bool* **local_space** - Флаг, указывающий, следует ли использовать угол камеры для рендеринга кубической карты.

## void renderTextureCube ( const Ptr < Camera > & camera , const Ptr < Texture > & texture , int size , bool hdr = 0 , bool local_space = 0 )

Рендерит изображение с камеры в кубическую карту указанного размера.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera** - Камера, с которой должно рендериться изображение.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Целевая кубическая карта для сохранения результата.
- *int* **size** - Размер грани кубической карты.
- *bool* **hdr** - Флаг HDR. > **Notice:** Этот параметр определяет формат 2D-текстуры: > - **1** - формат текстуры будет установлен в [**RGBA16F**](../../../api/library/rendering/class.texture_cpp.md#FORMAT_RGBA16F) > - **0** - формат текстуры будет установлен в [**RGBA8**](../../../api/library/rendering/class.texture_cpp.md#FORMAT_RGBA8)
- *bool* **local_space** - Флаг, указывающий, следует ли использовать угол камеры для рендеринга кубической карты.

## void renderNode ( const Ptr < Camera > & camera , const Ptr < Node > & node )

Рендерит заданный узел со всеми потомками в текущий рендер-таргет.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera** - Камера, с которой должно рендериться изображение.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел для рендеринга.

## void renderNode ( const Ptr < Camera > & camera , const Ptr < Node > & node , int width , int height )

Рендерит заданный узел со всеми потомками в текущий рендер-таргет.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera** - Камера, с которой должно рендериться изображение.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел для рендеринга.
- *int* **width** - Ширина изображения, в пикселях.
- *int* **height** - Высота изображения, в пикселях.

## void renderNodeTexture2D ( const Ptr < Camera > & camera , const Ptr < Node > & node , const Ptr < Texture > & texture , int width , int height , bool hdr )

Рендерит заданный узел со всеми потомками в 2D-текстуру указанного размера.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera** - Камера, с которой должно рендериться изображение.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **node** - Указатель на узел для рендеринга.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Целевая 2D-[texture](../../../api/library/rendering/class.texture_cpp.md) для сохранения результата.
- *int* **width** - Ширина текстуры, в пикселях.
- *int* **height** - Высота текстуры, в пикселях.
- *bool* **hdr** - Флаг HDR. > **Notice:** Этот параметр определяет формат 2D-текстуры: > - **1** - формат текстуры будет установлен в [**RGBA16F**](../../../api/library/rendering/class.texture_cpp.md#FORMAT_RGBA16F) > - **0** - формат текстуры будет установлен в [**RGBA8**](../../../api/library/rendering/class.texture_cpp.md#FORMAT_RGBA8)

## void renderNodeTexture2D ( const Ptr < Camera > & camera , const Ptr < Node > & node , const Ptr < Texture > & texture )

Рендерит заданный узел со всеми потомками в указанную 2D-текстуру.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera** - Камера, с которой должно рендериться изображение.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **node** - Указатель на узел для рендеринга.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Целевая 2D-[texture](../../../api/library/rendering/class.texture_cpp.md) для сохранения результата.

## void renderNodes ( const Ptr < Camera > & camera , const Vector < Ptr < Node >> & nodes )

Рендерит заданные узлы со всеми их потомками в текущий рендер-таргет.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera** - Камера, с которой должно рендериться изображение.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **nodes** - Список узлов для рендеринга.

## void renderNodes ( const Ptr < Camera > & camera , const Vector < Ptr < Node >> & nodes , int width , int height )

Рендерит заданные узлы со всеми их потомками в текущий рендер-таргет указанного размера.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera** - Камера, с которой должно рендериться изображение.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **nodes** - Список узлов для рендеринга.
- *int* **width** - Ширина изображения, в пикселях.
- *int* **height** - Высота изображения, в пикселях.

## void renderNodesTexture2D ( const Ptr < Camera > & camera , const Vector < Ptr < Node >> & nodes , const Ptr < Texture > & texture , int width , int height , int hdr )

Рендерит заданные узлы со всеми их потомками в 2D-текстуру указанного размера.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera** - Камера, с которой должно рендериться изображение.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **nodes** - Список узлов для рендеринга.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Целевая 2D-[texture](../../../api/library/rendering/class.texture_cpp.md) для сохранения результата.
- *int* **width** - Ширина текстуры, в пикселях.
- *int* **height** - Высота текстуры, в пикселях.
- *int* **hdr** - Флаг HDR. > **Notice:** Этот параметр определяет формат 2D-изображения: > - **1** - формат текстуры будет установлен в [**RGBA16F**](../../../api/library/rendering/class.texture_cpp.md#FORMAT_RGBA16F) > - **0** - формат текстуры будет установлен в [**RGBA8**](../../../api/library/rendering/class.texture_cpp.md#FORMAT_RGBA8)

## void renderNodesTexture2D ( const Ptr < Camera > & camera , const Vector < Ptr < Node >> & nodes , const Ptr < Texture > & texture )

Рендерит заданные узлы со всеми их потомками в указанную 2D-текстуру.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera** - Камера, с которой должно рендериться изображение.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **nodes** - Список узлов для рендеринга.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Целевая 2D-[texture](../../../api/library/rendering/class.texture_cpp.md) для сохранения результата.

## void renderStereo ( const Ptr < Camera > & camera_left , const Ptr < Camera > & camera_right , const char * stereo_material )

Рендерит стереоизображение в текущем вьюпорте.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera_left** - Камера, рендерящая изображение для левого глаза.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera_right** - Камера, рендерящая изображение для правого глаза.
- *const char ** **stereo_material** - Список имён используемых стереоматериалов.

## void renderStereoPeripheral ( const Ptr < Camera > & camera_left , const Ptr < Camera > & camera_right , const Ptr < Camera > & camera_focus_left , const Ptr < Camera > & camera_focus_right , const Ptr < Texture > & texture_left , const Ptr < Texture > & texture_right , const Ptr < Texture > & texture_focus_left , const Ptr < Texture > & texture_focus_right , const char * stereo_material )

Рендерит стереоизображение для HMD-устройств, имеющих контекстный (периферийный) и фокусный дисплеи. Этот метод экономит производительность на тенях и отражениях наряду с другими оптимизациями, снижающими нагрузку рендеринга, такими как сниженные разрешения текстур.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera_left** - Камера, рендерящая изображение для левого контекстного (низкого разрешения) дисплея.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera_right** - Камера, рендерящая изображение для правого контекстного (низкого разрешения) дисплея.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera_focus_left** - Камера, рендерящая изображение для левого фокусного (высокого разрешения) дисплея.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera_focus_right** - Камера, рендерящая изображение для правого фокусного (высокого разрешения) дисплея.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture_left** - Текстура для сохранения изображения, отрендеренного для левого контекстного (низкого разрешения) дисплея.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture_right** - Текстура для сохранения изображения, отрендеренного для правого контекстного (низкого разрешения) дисплея.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture_focus_left** - Текстура для сохранения изображения, отрендеренного для левого фокусного (высокого разрешения) дисплея.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture_focus_right** - Текстура для сохранения изображения, отрендеренного для правого фокусного (высокого разрешения) дисплея.
- *const char ** **stereo_material** - Список имён используемых стереоматериалов.

## void setStereoHiddenAreaMesh ( const Ptr < Mesh > & hidden_area_mesh_left , const Ptr < Mesh > & hidden_area_mesh_right )

Задаёт пользовательские меши, используемые для отсечения пикселей, невидимых в VR.
> **Notice:** Требует [render_stereo_hidden_area](../../../code/console/index.md#render_stereo_hidden_area) = 2


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **hidden_area_mesh_left** - [Mesh](../../../api/library/rendering/class.mesh_cpp.md), представляющий скрытую область для левого глаза.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **hidden_area_mesh_right** - [Mesh](../../../api/library/rendering/class.mesh_cpp.md), представляющий скрытую область для правого глаза.

## void clearStereoHiddenAreaMesh ( )

Очищает меши, представляющие скрытые области для обоих глаз - левого и правого. Скрытые области используются для отсечения пикселей, невидимых в VR
## void setEnvironmentTexturePath ( const char * name )

Задаёт путь к [cubemap defining the environment color](../../../editor2/settings/render_settings/environment/index.md#env_texture), для вьюпорта. Эта текстура используется для имитации отражений и освещения ландшафта в соответствии с маской земли.
### Аргументы

- *const char ** **name** - Путь к кубической текстуре, определяющей цвет окружения.

## const char * getEnvironmentTexturePath ( )

Возвращает путь к [cubemap defining the environment color](../../../editor2/settings/render_settings/environment/index.md#env_texture), установленной для вьюпорта. Эта текстура используется для имитации отражений и освещения ландшафта в соответствии с маской земли.
### Возвращаемое значение

Путь к кубической текстуре, определяющей цвет окружения.
## void resetEnvironmentTexture ( )

Сбрасывает текущую текстуру окружения на значение по умолчанию.
## void renderVREngine ( )

Рендерит VR-вьюпорт, если VR включён, с учётом установленного [vr mirror mode](../../../api/library/vr/class.vr_cpp.md#MirrorMode).
## void lockResources ( )

Блокирует ресурсы (такие как временные старые текстуры) в текущем вьюпорте, чтобы они не были переиспользованы или освобождены.
## void unlockResources ( )

Разблокирует ресурсы (такие как временные старые текстуры) в текущем вьюпорте, чтобы они могли быть переиспользованы и освобождены движком.
## bool isLockedResources ( ) const

Возвращает значение, указывающее, заблокированы ли ресурсы (такие как временные старые текстуры) в текущем вьюпорте и не будут переиспользованы или освобождены.
### Возвращаемое значение

true, если ресурсы заблокированы; иначе false.
