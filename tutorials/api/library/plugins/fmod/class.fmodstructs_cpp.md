# Unigine::Plugins::FMOD::FMODStructs Class (CPP)

**Header:** #include <plugins/Unigine/FMOD/UnigineFMOD.h>


> **Notice:** Этот набор функций доступен, если загружен плагин [FMOD](../../../../code/plugins/fmod/index.md).


Структуры, используемые в API плагина FMOD.


## struct DSP_PARAMETER_FLOAT_MAPPING_PIECEWISE_LINEAR

### Поля

- *int* **numpoints** - Количество пар в кусочном отображении (минимум 2).
- *float** **pointparamvalues** - Значения в единицах параметра для каждой точки.
- *float** **pointpositions** - Позиции вдоль шкалы регулятора (например, угол поворота диска), соответствующие каждому значению параметра. Диапазон шкалы произвольный. Все позиции задаются относительно минимального и максимального значений. Если этот массив пуст, *pointparamvalues* будут распределены с равным интервалом.


## struct DSP_PARAMETER_FLOAT_MAPPING

### Поля

- *[FMODEnums::DSP_PARAMETER_FLOAT_MAPPING_TYPE](../../../../api/library/plugins/fmod/class.fmodenums_cpp.md#DSP_PARAMETER_FLOAT_MAPPING_TYPE)* **type** - Тип отображения.
- *[FMODStructs::DSP_PARAMETER_FLOAT_MAPPING_PIECEWISE_LINEAR](../../../../api/library/plugins/fmod/class.fmodstructs_cpp.md#DSP_PARAMETER_FLOAT_MAPPING_PIECEWISE_LINEAR)* **piecewiselinearmapping** - Тип кусочно-линейного отображения.


## struct DSP_PARAMETER_DESC_FLOAT

### Поля

- *float* **min** - Минимальное значение.
- *float* **max** - Максимальное значение.
- *float* **defaultval** - Значение по умолчанию.
- *[FMODStructs::DSP_PARAMETER_FLOAT_MAPPING](../../../../api/library/plugins/fmod/class.fmodstructs_cpp.md#DSP_PARAMETER_FLOAT_MAPPING)* **mapping** - Типы отображения и кусочно-линейного отображения, определяющие распределение значений по регуляторам и кривым автоматизации.


## struct DSP_PARAMETER_DESC_INT

### Поля

- *float* **min** - Минимальное значение.
- *float* **max** - Максимальное значение.
- *float* **defaultval** - Значение по умолчанию.
- *bool* **goestoinf** - Значение, указывающее, представляет ли последнее значение бесконечность.
- *const char* const** **valuenames** - Имена значений (строка UTF-8). Количество строк должно соответствовать количеству возможных значений (max - min + 1).


## struct DSP_PARAMETER_DESC_BOOL

### Поля

- *bool* **defaultval** - Значение параметра по умолчанию.
- *const char* const** **valuenames** - Имена значений (для false и true соответственно), строка UTF-8. Должно быть две строки.


## struct DSP_PARAMETER_DESC_DATA

### Поля

- *int* **datatype** - Тип данных.


## struct DSP_PARAMETER_DESC

### Поля

- *[FMODEnums::DSP_PARAMETER_TYPE](../../../../api/library/plugins/fmod/class.fmodenums_cpp.md#DSP_PARAMETER_TYPE)* **type** - Тип параметра.
- *char[]* **name** - Имя параметра.
- *char[]* **label** - Метка типа единицы измерения.
- *const char** **description** - Описание параметра.
- *union*  -

  - *[FMODStructs::DSP_PARAMETER_DESC_FLOAT](#DSP_PARAMETER_DESC_FLOAT)* **floatdesc** - Описание формата с плавающей точкой, используемое, когда тип — *FMOD_DSP_PARAMETER_TYPE_FLOAT*.
  - *[FMODStructs::DSP_PARAMETER_DESC_INT](#DSP_PARAMETER_DESC_INT)* **intdesc** - Описание целочисленного формата, используемое, когда тип — *FMOD_DSP_PARAMETER_TYPE_INT*.
  - *[FMODStructs::DSP_PARAMETER_DESC_BOOL](#DSP_PARAMETER_DESC_BOOL)* **booldesc** - Описание булева формата, используемое, когда тип — *FMOD_DSP_PARAMETER_TYPE_BOOL*.
  - *[FMODStructs::DSP_PARAMETER_DESC_DATA](#DSP_PARAMETER_DESC_DATA)* **datadesc** - Описание формата данных, используемое, когда тип — *FMOD_DSP_PARAMETER_TYPE_DATA*.
