# Unigine::Plugins::SpiderVision::WallGroupData Class (CPP)

**Header:** #include <plugins/Unigine/SpiderVision/UnigineSpiderVision.h>


Экземпляр этого класса представляет группу viewport, расположенных в заданном количестве строк и столбцов с указанным расстоянием между viewport и ориентацией viewport, тем самым создавая [wall](../../../../principles/render/output/multi_monitor/spidervision_plugin/presets.md#wall).


## WallGroupData Class

### Методы класса

## void setSize ( const Math:: ivec2 & size )

Задаёт новый размер стены, количество столбцов и строк.
### Аргументы

- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md)&* **size** - Количество столбцов и строк в стене.

## Math:: ivec2 getSize () const

Возвращает текущий размер стены, количество столбцов и строк.
### Возвращаемое значение

Текущее количество столбцов и строк в стене.
## void setOffset ( const Math:: vec2 & offset )

Задаёт новые горизонтальное и вертикальное расстояния между краями соседних viewport в стене.
### Аргументы

- *const  Math::[vec2](../../../../api/library/math/class.vec2_cpp.md)&* **offset** - Горизонтальное и вертикальное расстояния между соседними viewport.

## Math:: vec2 getOffset () const

Возвращает текущие горизонтальное и вертикальное расстояния между краями соседних viewport в стене.
### Возвращаемое значение

Текущие горизонтальное и вертикальное расстояния между соседними viewport.
## void setDisplaySize ( const Math:: vec2 & size )

Задаёт новые фактические ширину и высоту дисплея в группе Wall. Предполагается, что стена состоит из идентичных дисплеев. Если размеры дисплеев различаются, можно рассмотреть создание конфигурации с несколькими группами Wall.
### Аргументы

- *const  Math::[vec2](../../../../api/library/math/class.vec2_cpp.md)&* **size** - Ширина и высота дисплея.

## Math:: vec2 getDisplaySize () const

Возвращает текущие фактические ширину и высоту дисплея в группе Wall. Предполагается, что стена состоит из идентичных дисплеев. Если размеры дисплеев различаются, можно рассмотреть создание конфигурации с несколькими группами Wall.
### Возвращаемое значение

Текущие ширина и высота дисплея.
## void setWindowSize ( const Math:: ivec2 & size )

Задаёт новые ширину и высоту окна на экране дисплея.
### Аргументы

- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md)&* **size** - Ширина и высота окна на экране, в пикселях.

## Math:: ivec2 getWindowSize () const

Возвращает текущие ширину и высоту окна на экране дисплея.
### Возвращаемое значение

Текущие ширина и высота окна на экране, в пикселях.
## void setDistanceToViewer ( float viewer )

Задаёт новое расстояние от точки наблюдателя до центра группы.
### Аргументы

- *float* **viewer** - Расстояние от точки наблюдателя до центра группы, в единицах.

## float getDistanceToViewer () const

Возвращает текущее расстояние от точки наблюдателя до центра группы.
### Возвращаемое значение

Текущее расстояние от точки наблюдателя до центра группы, в единицах.
## void setAngle ( float angle )

Задаёт новый угол между соседними дисплеями в плоскости XY (т.е. вокруг оси Z).
### Аргументы

- *float* **angle** - Угол между соседними дисплеями в плоскости XY.

## float getAngle () const

Возвращает текущий угол между соседними дисплеями в плоскости XY (т.е. вокруг оси Z).
### Возвращаемое значение

Текущий угол между соседними дисплеями в плоскости XY.
## void setAutoArrange ( bool arrange )

Задаёт новое значение, указывающее, включено ли автоматическое позиционирование окон на дисплеях. Если отключено, все окна создаются в одном и том же месте с позицией (0, 0) и должны позиционироваться вручную.
### Аргументы

- *bool* **arrange** - Установите **true**, чтобы включить автоматическое позиционирование окон на дисплеях; **false** - чтобы отключить его.

## bool isAutoArrange () const

Возвращает текущее значение, указывающее, включено ли автоматическое позиционирование окон на дисплеях. Если отключено, все окна создаются в одном и том же месте с позицией (0, 0) и должны позиционироваться вручную.
### Возвращаемое значение

**true**, если автоматическое позиционирование окон на дисплеях включено; иначе **false**.
## void setAspect ( float aspect )

Задаёт новое
### Аргументы

- *float* **aspect** -

## float getAspect () const

Возвращает текущее
### Возвращаемое значение

Текущее
## void setVFov ( float vfov )

Задаёт новое
### Аргументы

- *float* **vfov** -

## float getVFov () const

Возвращает текущее
### Возвращаемое значение

Текущее
## void setTransformType ( ViewportData::DISPLAY_TRANSFORM_TYPE type )

Задаёт новый
### Аргументы

- *[ViewportData::DISPLAY_TRANSFORM_TYPE](../../../../api/library/plugins/spidervision/class.viewportdata_cpp.md#DISPLAY_TRANSFORM_TYPE)* **type** -

## ViewportData::DISPLAY_TRANSFORM_TYPE getTransformType () const

Возвращает текущий
### Возвращаемое значение

Текущий
---

## void generate ( )

Генерирует группу viewport, используя метод [createViewport()](../../../../api/library/plugins/spidervision/class.displaysconfig_cpp.md#createViewport_int_ViewportData).
## void refresh ( )

Обновляет позицию и ориентацию viewport на основе указанных значений [size](#setSize_ivec2_void), [offset](#setOffset_vec2_void), [distance to viewer](#setDistanceToViewer_float_void) и [angle](#setAngle_float_void).
