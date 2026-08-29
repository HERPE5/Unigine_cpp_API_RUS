# Класс Unigine.DecalProj (CPP)

**Заголовочный файл:** #include <UnigineDecals.h>

**Наследуется от:** Decal


Этот класс описывает, как создавать и изменять [projected decals](../../../objects/decals/proj/index.md).


### Создание Projected Decal


Следующий код иллюстрирует, как создать проекционную декаль, задать её параметры и добавить узел в UnigineEditor.


```cpp
// AppWorldLogic.h

#include <UnigineLogic.h>
#include <UnigineEditor.h>
#include <UnigineDecals.h>

class AppWorldLogic : public Unigine::WorldLogic {

public:
	AppWorldLogic();
	virtual ~AppWorldLogic();

	virtual int init();

	virtual int update();
	virtual int postUpdate();
	virtual int updatePhysics();

	virtual int shutdown();

	virtual int save(const Unigine::StreamPtr &stream);
	virtual int restore(const Unigine::StreamPtr &stream);

private:
	Unigine::DecalProjPtr decal_proj;
};

```


```cpp
// AppWorldLogic.cpp

#include "AppWorldLogic.h";

using namespace Unigine;

int AppWorldLogic::init()
{

	// создаём проекционную декаль и задаём её радиус равным 10, fov равным 60, aspect равным 1.0f, материал "decal_base"
	decal_proj = DecalProj::create();
	decal_proj->setRadius(10.0f);
	decal_proj->setFov(60.0f);
	decal_proj->setAspect(1.0f);

	// задаём имя и позицию декали
	decal_proj->setName("Proj Decal");
	decal_proj->setWorldPosition(Math::Vec3(0.0f, 0.0f, 5.0f));

	return 1;
}

```


## Класс DecalProj

### Методы класса

---

## static DecalProjPtr create ( )

Конструктор. Создаёт новую проекционную декаль с параметрами по умолчанию.
## void setAspect ( float aspect )

Задаёт новое соотношение сторон декали, в единицах.
### Аргументы

- *float* **aspect** - Соотношение сторон декали, в единицах. Если задано отрицательное значение, вместо него будет использовано 0.

## float getAspect ( ) const

Возвращает текущее соотношение сторон декали.
### Возвращаемое значение

Соотношение сторон декали, в единицах.
## void setFov ( float fov )

Задаёт новый угол обзора проектора декали.
### Аргументы

- *float* **fov** - Угол обзора проектора декали, в градусах. Заданное значение будет ограничено диапазоном [1;90].

## float getFov ( ) const

Возвращает текущий угол обзора проектора декали.
### Возвращаемое значение

Угол обзора проектора декали, в градусах.
## Math:: mat4 getProjection ( ) const

Возвращает матрицу проекции.
### Возвращаемое значение

Матрица проекции декали.
## void setZNear ( float znear )

Задаёт дистанцию до ближней плоскости отсечения декали.
### Аргументы

- *float* **znear** - Новая дистанция до ближней плоскости отсечения, в единицах. Если задано отрицательное значение, вместо него будет использовано 0.

## float getZNear ( ) const

Возвращает дистанцию до ближней плоскости отсечения декали.
### Возвращаемое значение

Дистанция до ближней плоскости отсечения, в единицах.
## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [Decal](../../../api/library/decals/class.decal_cpp.md).
