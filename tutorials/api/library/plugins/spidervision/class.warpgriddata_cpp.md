# Unigine::Plugins::SpiderVision::WarpGridData Class (CPP)

**Header:** #include <plugins/Unigine/SpiderVision/UnigineSpiderVision.h>


Экземпляр этого класса хранит информацию о warp grid — наборе точек и их указателей, создающих меш, на основе которого изменяется форма отображаемого изображения.


Искажение изображения требуется для отрисовки проецируемого изображения на искажённой поверхности таким образом, чтобы оно выглядело неискажённым.


Этот объект доступен через соответствующий метод класса [ViewportData](../../../../api/library/plugins/spidervision/class.viewportdata_cpp.md#getWarpGrid_WarpGridData).


Данные масок хранятся в [configuration file](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#config_file).


## WarpGridData Class

### Перечисления

## VIEWPORT_FLIP_TYPE

| Name | Description |
|---|---|
| **VIEWPORT_FLIP_TYPE_NONE** = 0 | Маска холста не отражается. |
| **VIEWPORT_FLIP_TYPE_VERTICAL** = 1 | Маска холста отражается по вертикали. |
| **VIEWPORT_FLIP_TYPE_HORIZONTAL** = 2 | Маска холста отражается по горизонтали. |
| **VIEWPORT_FLIP_TYPE_BOTH** = 3 | Маска холста отражается и по вертикали, и по горизонтали. |

## WARP_HANDLE_ROLE

| Name | Description |
|---|---|
| **WARP_HANDLE_ROLE_LEFT** = 0 | Левая контрольная точка-указатель контрольной точки искажения на сетке. |
| **WARP_HANDLE_ROLE_RIGHT** = 1 | Правая контрольная точка-указатель контрольной точки искажения на сетке. |
| **WARP_HANDLE_ROLE_UP** = 2 | Верхняя контрольная точка-указатель контрольной точки искажения на сетке. |
| **WARP_HANDLE_ROLE_DOWN** = 3 | Нижняя контрольная точка-указатель контрольной точки искажения на сетке. |
| **WARP_HANDLE_ROLE_NUM** = 4 | Общее количество контрольных точек-указателей контрольной точки искажения. |

### Методы класса

---

## void setGridSize ( int row , int column )

Задаёт количество столбцов и строк сетки искажения.
### Аргументы

- *int* **row** - Количество строк сетки.
- *int* **column** - Количество столбцов сетки.

## void setPoint ( int x , int y , const Math:: vec2 & point )

Задаёт координаты контрольной точки искажения на сетке.
### Аргументы

- *int* **x** - Позиция контрольной точки искажения в строке, начиная с 0 слева.
- *int* **y** - Позиция контрольной точки искажения в столбце, начиная с 0 снизу.
- *const  Math::[vec2](../../../../api/library/math/class.vec2_cpp.md) &* **point** - Экранные координаты точки.

## void setPoint ( int index , const Math:: vec2 & point )

Задаёт координаты контрольной точки искажения на сетке.
### Аргументы

- *int* **index** - Индекс контрольной точки искажения. Точка с индексом 0 находится в нижнем левом углу, далее движение идёт вверх, а затем к нижней точке следующего столбца.
- *const  Math::[vec2](../../../../api/library/math/class.vec2_cpp.md) &* **point** - Экранные координаты точки.

## Math:: vec2 getPoint ( int x , int y ) const

Возвращает координаты контрольной точки искажения на сетке.
### Аргументы

- *int* **x** - Позиция контрольной точки искажения в строке, начиная с 0 слева.
- *int* **y** - Позиция контрольной точки искажения в столбце, начиная с 0 снизу.

### Возвращаемое значение

Экранные координаты точки.
## Math:: vec2 getPoint ( int index ) const

Возвращает координаты контрольной точки искажения на сетке.
### Аргументы

- *int* **index** - Индекс контрольной точки искажения. Точка с индексом 0 находится в нижнем левом углу, далее движение идёт вверх, а затем к нижней точке следующего столбца.

### Возвращаемое значение

Экранные координаты точки.
## void setPointHandle ( int x , int y , WarpGridData::WARP_HANDLE_ROLE type , const Math:: vec2 & point )

Задаёт тип и позицию точки-указателя для указанной точки warp grid.
### Аргументы

- *int* **x** - Позиция контрольной точки искажения в строке, начиная с 0 слева.
- *int* **y** - Позиция контрольной точки искажения в столбце, начиная с 0 снизу.
- *[WarpGridData::WARP_HANDLE_ROLE](../../../../api/library/plugins/spidervision/class.warpgriddata_cpp.md#WARP_HANDLE_ROLE)* **type** - Тип контрольной точки-указателя контрольной точки искажения.
- *const  Math::[vec2](../../../../api/library/math/class.vec2_cpp.md) &* **point** - Экранные координаты точки.

## void setPointHandle ( int index , WarpGridData::WARP_HANDLE_ROLE type , const Math:: vec2 & point )

Задаёт тип и позицию точки-указателя для указанной точки warp grid.
### Аргументы

- *int* **index** - Индекс контрольной точки искажения. Точка с индексом 0 находится в нижнем левом углу, далее движение идёт вверх, а затем к нижней точке следующего столбца.
- *[WarpGridData::WARP_HANDLE_ROLE](../../../../api/library/plugins/spidervision/class.warpgriddata_cpp.md#WARP_HANDLE_ROLE)* **type** - Тип контрольной точки-указателя контрольной точки искажения.
- *const  Math::[vec2](../../../../api/library/math/class.vec2_cpp.md) &* **point** - Экранные координаты точки.

## Math:: vec2 getPointHandle ( int x , int y , WarpGridData::WARP_HANDLE_ROLE type ) const

Возвращает тип и позицию точки-указателя для указанной точки warp grid.
### Аргументы

- *int* **x** - Позиция контрольной точки искажения в строке, начиная с 0 слева.
- *int* **y** - Позиция контрольной точки искажения в столбце, начиная с 0 снизу.
- *[WarpGridData::WARP_HANDLE_ROLE](../../../../api/library/plugins/spidervision/class.warpgriddata_cpp.md#WARP_HANDLE_ROLE)* **type** - Тип контрольной точки-указателя контрольной точки искажения.

### Возвращаемое значение

Экранные координаты точки.
## Math:: vec2 getPointHandle ( int index , WarpGridData::WARP_HANDLE_ROLE type ) const

Возвращает тип и позицию точки-указателя для указанной точки warp grid.
### Аргументы

- *int* **index** - Индекс контрольной точки искажения. Точка с индексом 0 находится в нижнем левом углу, далее движение идёт вверх, а затем к нижней точке следующего столбца.
- *[WarpGridData::WARP_HANDLE_ROLE](../../../../api/library/plugins/spidervision/class.warpgriddata_cpp.md#WARP_HANDLE_ROLE)* **type** - Тип контрольной точки-указателя контрольной точки искажения.

### Возвращаемое значение

Экранные координаты точки.
## void setPointHandleSmoothType ( int x , int y , ViewportData::POINT_SMOOTH_TYPE smooth_type )

Задаёт тип изгиба линии для точки-указателя указанной точки warp grid.
### Аргументы

- *int* **x** - Позиция контрольной точки искажения в строке, начиная с 0 слева.
- *int* **y** - Позиция контрольной точки искажения в столбце, начиная с 0 снизу.
- *[ViewportData::POINT_SMOOTH_TYPE](../../../../api/library/plugins/spidervision/class.viewportdata_cpp.md#POINT_SMOOTH_TYPE)* **smooth_type** - Тип изгиба линии для точки-указателя.

## void setPointHandleSmoothType ( int index , ViewportData::POINT_SMOOTH_TYPE smooth_type )

Задаёт тип изгиба линии для точки-указателя указанной точки warp grid.
### Аргументы

- *int* **index** - Индекс контрольной точки искажения. Точка с индексом 0 находится в нижнем левом углу, далее движение идёт вверх, а затем к нижней точке следующего столбца.
- *[ViewportData::POINT_SMOOTH_TYPE](../../../../api/library/plugins/spidervision/class.viewportdata_cpp.md#POINT_SMOOTH_TYPE)* **smooth_type** - Тип изгиба линии для точки-указателя.

## ViewportData::POINT_SMOOTH_TYPE getPointHandleSmoothType ( int x , int y ) const

Возвращает тип изгиба линии для точки-указателя указанной точки warp grid.
### Аргументы

- *int* **x** - Позиция контрольной точки искажения в строке, начиная с 0 слева.
- *int* **y** - Позиция контрольной точки искажения в столбце, начиная с 0 снизу.

### Возвращаемое значение

Тип изгиба линии для точки-указателя.
## ViewportData::POINT_SMOOTH_TYPE getPointHandleSmoothType ( int index ) const

Возвращает тип изгиба линии для точки-указателя указанной точки warp grid.
### Аргументы

- *int* **index** - Индекс контрольной точки искажения. Точка с индексом 0 находится в нижнем левом углу, далее движение идёт вверх, а затем к нижней точке следующего столбца.

### Возвращаемое значение

Тип изгиба линии для точки-указателя.
## void saveXml ( const Ptr < Xml > & xml )

Сохраняет данные warp grid в указанный экземпляр класса Xml.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../../api/library/common/class.xml_cpp.md)> &* **xml** - Экземпляр [Xml class](../../../../api/library/common/class.xml_cpp.md), в который будут сохранены данные.

## bool restoreXml ( const Ptr < Xml > & xml )

Загружает данные warp grid из указанного экземпляра класса Xml.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../../api/library/common/class.xml_cpp.md)> &* **xml** - Экземпляр [Xml class](../../../../api/library/common/class.xml_cpp.md), из которого загружаются данные.

### Возвращаемое значение

true, если данные успешно загружены; иначе false.
## void save ( const Ptr < Stream > & stream )

Сохраняет данные warp grid в указанный поток.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, в который записываются данные.

## void restore ( const Ptr < Stream > & stream )

Загружает данные warp grid из указанного потока.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, из которого загружаются данные.
