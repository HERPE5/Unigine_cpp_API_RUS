# Unigine::Plugins::Sql::SqlRequest Class (CPP)

**Header:** #include <plugins/Unigine/Sql/UnigineSql.h>


Этот класс управляет запросами к SQL-базе данных.


## SqlRequest Class

### Методы класса

## void setQuery ( const char * query )

Задаёт новую строку запроса с синтаксисом, соответствующим SQL-базе данных, к которой выполняется запрос.
### Аргументы

- *const char ** **query** - Строка запроса с синтаксисом, соответствующим SQL-базе данных, к которой выполняется запрос.

## String getQuery () const

Возвращает текущую строку запроса с синтаксисом, соответствующим SQL-базе данных, к которой выполняется запрос.
### Возвращаемое значение

Текущая строка запроса с синтаксисом, соответствующим SQL-базе данных, к которой выполняется запрос.
## void setNumericalPrecisionPolicy ( Sql::NUMERICAL_PRECISION_POLICY policy )

Задаёт новую политику числовой точности.
### Аргументы

- *[Sql::NUMERICAL_PRECISION_POLICY](../../../../api/library/plugins/sql/class.sql_cpp.md#NUMERICAL_PRECISION_POLICY)* **policy** - Политика числовой точности, одно из значений [NUMERICAL_PRECISION_POLICY](../../../../api/library/plugins/sql/class.sql_cpp.md#NUMERICAL_PRECISION_POLICY).

## Sql::NUMERICAL_PRECISION_POLICY getNumericalPrecisionPolicy () const

Возвращает текущую политику числовой точности.
### Возвращаемое значение

Текущая политика числовой точности, одно из значений [NUMERICAL_PRECISION_POLICY](../../../../api/library/plugins/sql/class.sql_cpp.md#NUMERICAL_PRECISION_POLICY).
## void setBatchExecutionMode ( Sql::BATCH_EXECUTION_MODE mode )

Задаёт новый режим пакетного выполнения.
### Аргументы

- *[Sql::BATCH_EXECUTION_MODE](../../../../api/library/plugins/sql/class.sql_cpp.md#BATCH_EXECUTION_MODE)* **mode** - Режим пакетного выполнения, одно из значений [BATCH_EXECUTION_MODE](../../../../api/library/plugins/sql/class.sql_cpp.md#BATCH_EXECUTION_MODE).

## Sql::BATCH_EXECUTION_MODE getBatchExecutionMode () const

Возвращает текущий режим пакетного выполнения.
### Возвращаемое значение

Текущий режим пакетного выполнения, одно из значений [BATCH_EXECUTION_MODE](../../../../api/library/plugins/sql/class.sql_cpp.md#BATCH_EXECUTION_MODE).
---

## void bindValue ( int i , const Variable & value )

Привязывает значение к позиционному параметру в подготовленном SQL-выражении. После вызова *bindValue*, когда выполняется *[*exec*()](../../../../api/library/plugins/sql/class.sqldatabase_cpp.md#exec_SqlRequest_SqlResponse)*, движок подставляет заданное значение вместо заполнителя ? в SQL-выражении.
### Аргументы

- *int* **i** - Индекс заполнителя в запросе, начиная с 0.
- *const [Variable](../../../../api/library/common/class.variable_cpp.md) &* **value** - Значение для привязки.

## void bindValue ( const char * placeholder , const Variable & value )

Задаёт заполнитель, который должен быть привязан к значению в подготовленном выражении.
### Аргументы

- *const char ** **placeholder** - Заполнитель.
- *const [Variable](../../../../api/library/common/class.variable_cpp.md) &* **value** - Значение для привязки.

## void addBindValue ( const Vector < Variable > & value )

Привязывает значение к следующей доступной позиции в текущей записи (строке).
### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<[Variable](../../../../api/library/common/class.variable_cpp.md) > &* **value** - Значение для привязки.

## void clearBindings ( )

Очищает все привязки.
## void clear ( )

Очищает запрос.
