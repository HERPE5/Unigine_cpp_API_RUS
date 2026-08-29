# Unigine::Plugins::IG::IGIntersection Structure

> **Warning:** Функциональность, описанная в этой статье, недоступна в редакции Community SDK.
> Для её использования следует перейти на редакцию SDK [**Sim**](https://l.unigine.com/SdhugY462).


Эта структура данных хранит результат пересечения (координаты точки пересечения, а также нормаль и текстурные координаты, пересечённый объект и индекс поверхности, маску пересечения) и имеет следующий набор параметров:

| **surface** | Номер пересечённой поверхности. |
|---|---|
| **mask** | Маска пересечения. |
| **object** | Пересечённый объект. |
| **point** | Координаты точки пересечения. |
| **normal** | Нормаль точки пересечения. |
| **texcoord** | Текстурные координаты точки пересечения. |

 Структура **IGIntersection** объявляется следующим образом:
```cpp
struct IGIntersection
{
	int surface;
	unsigned int mask;
	Unigine::ObjectPtr object;
	Unigine::Math::Vec3 point;
	Unigine::Math::vec3 normal;
	Unigine::Math::vec4 texcoord;
};

```
