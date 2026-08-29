# UnigineScript Extension Examples for C++

> **Warning:** Область применения UnigineScript ограничена реализацией логики, связанной с материалами (material expressions, scriptable materials, brush materials). Не используйте UnigineScript как язык логики приложения, вместо этого рассмотрите C#/C++, поскольку именно эти API являются предпочтительными. Доступность новых функций движка в UnigineScript (за пределами области его применения) не гарантируется, поскольку текущий уровень поддержки подразумевает только исправление критических проблем.


UnigineScript можно легко расширить с помощью Unigine API. Исходный код примеров предоставляется в составе исходной и бинарной версий UNIGINE SDK.


Идея заключается в том, что часть функциональности реализуется средствами C++ части приложения, и её необходимо зарегистрировать в системе UnigineScript, чтобы использовать внутри скриптов.


Дополнительную информацию см. в общих примерах использования:

- [Library Namespace](../../../../code/cpp/usage/script/namespace.md)
- [Variable Export](../../../../code/cpp/usage/script/variables.md)
- [Constant Export](../../../../code/cpp/usage/script/constants.md)
- [Function Export](../../../../code/cpp/usage/script/functions.md)
- [Class Export](../../../../code/cpp/usage/script/classes.md)
- [Callbacks](../../../../code/cpp/usage/script/callbacks.md)
- [Serialization](../../../../code/cpp/usage/script/serialization.md)
- [UnigineScript Containers](../../../../code/cpp/usage/script/arrays.md)
