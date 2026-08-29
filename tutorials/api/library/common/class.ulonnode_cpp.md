# Unigine::UlonNode Class (CPP)

**Header:** #include <UnigineUlon.h>


Этот класс используется для представления узла [ULON](../../../code/formats/ulon_format.md).


Каждый узел ULON имеет **тип**, **имя** и **значение**. Он также может иметь дочерние узлы ULON и родительский узел, образуя таким образом иерархию.


Узел объявляется следующим образом:

```text
NodeType node_name = node_value
```


Узлы ULON могут быть следующих типов:

- ***Логический*** *Node node = true*
- ***Целое число*** *Node node = 1234*
- ***Число с плавающей точкой*** *Node node = 3.1459*
- ***Строка***

  - Строка в кавычках со стандартными escape-символами: *Node node = "word word"*
  - Обычное слово, начинающееся со строчной буквы, содержащее только буквы, цифры и подчёркивания "_": *Node node = word1_word2*
  - Строка heredoc, заключённая в *#{ ... #}* (используется для фрагментов кода): *Node node = #{C++ C# USC HLSL USSL#}*
- ***Массив***, содержащий конечное количество элементов *integer, float* и *string* *Node node = [100, 0.2, str str "str str str", #{vec4 asd = vec4_zero;#}]* Этот массив имеет следующие **6** элементов:

  - 100
  - 0.2
  - str
  - str
  - str str str
  - vec4 asd = vec4_zero;


### Условия


Для каждого узла может быть указано условие; если условие не выполняется, узел ULON со всеми его дочерними элементами игнорируется. Таким образом можно динамически строить иерархию узлов ULON с высокой степенью гибкости.

> **Notice:** Условия не разбираются и не выполняются автоматически, обработка условий является обязанностью пользователя формата ULON (например, в случае материалов используются [UnigineScript](../../../code/uniginescript/index.md) и [UUSL](../../../code/uusl/index.md)).

Условия указываются после имени узла, начиная с ключевого слова **if**, само условие заключается в скобки **[ ... ]**.
Условие родительского узла добавляется к условию дочернего: **(parent_conditon) && (child_conditon)**


**Пример:**

```text
Node parent if[var == 10 || var == 5]
{
    Node child_0  if[var == 3]
    Node child_1  if[var == 4]
    {
        Node child_2 if[var != 11]
        Node child_3 if[var != 25]
	}
}

```

 Итоговые условия для каждого узла следующие:
- условие **parent**: (var1 == 10 || var1 == 5)
- условие **child_0**: (var1 == 10 || var1 == 5) && (var2 == 3)
- условие **child_1**: (var1 == 10 || var1 == 5) && (var2 == 4)
- условие **child_2**: (var1 == 10 || var1 == 5) && (var2 == 4) && (var3 != 11)
- условие **child_3**: (var1 == 10 || var1 == 5) && (var2 == 4) && (var3 != 25)


## UlonNode Class

### Методы класса

## const char * getType () const

Возвращает текущий тип узла ULON.
### Возвращаемое значение

Текущий тип узла ULON.
## const char * getName () const

Возвращает текущее имя узла ULON.
### Возвращаемое значение

Текущее имя узла ULON.
## const char * getCondition () const

Возвращает текущее [condition](#conditions), заданное для узла ULON.
> **Notice:** Условия не разбираются и не выполняются автоматически, обработка условий является обязанностью пользователя формата ULON (например, в случае материалов используются [UnigineScript](../../../code/uniginescript/index.md) и [UUSL](../../../code/uusl/index.md)).

### Возвращаемое значение

Текущее [condition](#conditions), заданное для узла ULON.
## Ptr < UlonValue > getValue () const

Возвращает текущее [value](../../../api/library/common/class.ulonvalue_cpp.md) узла ULON.
### Возвращаемое значение

Текущее [value](../../../api/library/common/class.ulonvalue_cpp.md) узла ULON.
---

## static UlonNodePtr create ( )

Конструктор. Создаёт узел ULON.
## bool load ( const char * path )

Загружает данные ULON из указанного файла и делает текущий узел ULON корнем разобранной иерархии.
### Аргументы

- *const char ** **path** - Путь к файлу, содержащему описание ULON.

### Возвращаемое значение

**true**, если данные ULON из указанного файла успешно прочитаны; иначе **false**.
## bool parse ( const char * str )

Разбирает указанную строку в узел ULON.
### Аргументы

- *const char ** **str** - Строка для разбора.

### Возвращаемое значение

true, если строка успешно разобрана; иначе false.
## Vector < Ptr < UlonNode > > getChildren ( ) const

Возвращает список всех дочерних элементов узла ULON.
### Возвращаемое значение

Список всех дочерних элементов узла ULON.
## Vector < Ptr < UlonArg > > getArgs ( ) const

Возвращает список всех [arguments](../../../api/library/common/class.ulonarg_cpp.md) узла ULON.
### Возвращаемое значение

Список всех [arguments](../../../api/library/common/class.ulonarg_cpp.md) узла ULON.
## bool isArg ( const char * name ) const

Проверяет, существует ли [argument](../../../api/library/common/class.ulonarg_cpp.md) с указанным именем.
### Аргументы

- *const char ** **name** - Имя проверяемого аргумента.

### Возвращаемое значение

**true**, если аргумент с указанным именем существует; иначе **false**.
## float getArgFloat ( const char * name , float ret = 0 ) const

Возвращает значение [argument](../../../api/library/common/class.ulonarg_cpp.md) узла ULON с указанным именем как float.
> **Notice:** Чтобы проверить, существует ли аргумент, используйте метод [*isArg()*](#isArg_cstr_int).


### Аргументы

- *const char ** **name** - Имя аргумента.
- *float* **ret** - Значение по умолчанию, возвращаемое, если аргумент узла ULON с указанным именем не найден.

### Возвращаемое значение

Значение float аргумента узла ULON, если он существует; иначе значение по умолчанию, заданное параметром *ret*.
## int getArgInt ( const char * name , int ret = 0 ) const

Возвращает значение [argument](../../../api/library/common/class.ulonarg_cpp.md) узла ULON с указанным именем как целое число.
> **Notice:** Чтобы проверить, существует ли аргумент, используйте метод [*isArg()*](#isArg_cstr_int).


### Аргументы

- *const char ** **name** - Имя аргумента.
- *int* **ret** - Значение по умолчанию, возвращаемое, если аргумент узла ULON с указанным именем не найден.

### Возвращаемое значение

Целочисленное значение аргумента узла ULON, если он существует; иначе значение по умолчанию, заданное параметром *ret*.
## long long getArgLong ( const char * name , long long ret = 0 ) const

Возвращает значение [argument](../../../api/library/common/class.ulonarg_cpp.md) узла ULON с указанным именем как 64-битное long long.
> **Notice:** Чтобы проверить, существует ли аргумент, используйте метод [*isArg()*](#isArg_cstr_int).


### Аргументы

- *const char ** **name** - Имя аргумента.
- *long long* **ret** - Значение по умолчанию, возвращаемое, если аргумент узла ULON с указанным именем не найден.

### Возвращаемое значение

64-битное значение long long аргумента узла ULON, если он существует; иначе значение по умолчанию, заданное параметром *ret*.
## bool getArgBool ( const char * name , bool ret = false ) const

Возвращает значение [argument](../../../api/library/common/class.ulonarg_cpp.md) узла ULON с указанным именем как логическое значение.
> **Notice:** Чтобы проверить, существует ли аргумент, используйте метод [*isArg()*](#isArg_cstr_int).


### Аргументы

- *const char ** **name** - Имя аргумента.
- *bool* **ret** - Значение по умолчанию, возвращаемое, если аргумент узла ULON с указанным именем не найден.

### Возвращаемое значение

Логическое значение аргумента узла ULON, если он существует; иначе значение по умолчанию, заданное параметром *ret*.
## char getArgChar ( const char * name , char ret = 0 ) const

Возвращает значение [argument](../../../api/library/common/class.ulonarg_cpp.md) узла ULON с указанным именем как char.
> **Notice:** Чтобы проверить, существует ли аргумент, используйте метод [*isArg()*](#isArg_cstr_int).


### Аргументы

- *const char ** **name** - Имя аргумента.
- *char* **ret** - Значение по умолчанию, возвращаемое, если аргумент узла ULON с указанным именем не найден.

### Возвращаемое значение

Значение char аргумента узла ULON, если он существует; иначе значение по умолчанию, заданное параметром *ret*.
## const char * getArgStr ( const char * name , const char * ret = "" ) const

Возвращает значение [argument](../../../api/library/common/class.ulonarg_cpp.md) узла ULON с указанным именем как строку.
> **Notice:** Чтобы проверить, существует ли аргумент, используйте метод [*isArg()*](#isArg_cstr_int).


### Аргументы

- *const char ** **name** - Имя аргумента.
- *const char ** **ret** - Значение по умолчанию, возвращаемое, если аргумент узла ULON с указанным именем не найден.

### Возвращаемое значение

Строковое значение аргумента узла ULON, если он существует; иначе значение по умолчанию, заданное параметром *ret*.
## Vector < String > getArgArray ( const char * name ) const

Возвращает значение [argument](../../../api/library/common/class.ulonarg_cpp.md) узла ULON с указанным именем как массив строк.
> **Notice:** Чтобы проверить, существует ли аргумент, используйте метод [*isArg()*](#isArg_cstr_int).


### Аргументы

- *const char ** **name** - Имя аргумента.

### Возвращаемое значение

Массив строк, представляющих элементы значения-массива, если он существует; иначе пустой массив строк.
## void printUnusedData ( const char * name ) const

Выводит предупреждения о неиспользуемых данных ([values](../../../api/library/common/class.ulonvalue_cpp.md) и [arguments](../../../api/library/common/class.ulonarg_cpp.md) узлов) для файла с указанным именем в консоль для отладки.
### Аргументы

- *const char ** **name** - Имя файла.

## void clearUnusedData ( ) const

Очищает все неиспользуемые данные узлов ([values](../../../api/library/common/class.ulonvalue_cpp.md) и [arguments](../../../api/library/common/class.ulonarg_cpp.md)).
