# Класс Unigine.DecalOrtho (CPP)

**Заголовочный файл:** #include <UnigineDecals.h>

**Наследуется от:** Decal


Этот класс описывает, как создавать и изменять [orthographic decals](../../../objects/decals/ortho/index.md).


### Создание Orthographic Decal


Следующий код иллюстрирует, как создать ортографическую декаль, задать её параметры и добавить узел в UnigineEditor.


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
	Unigine::DecalOrthoPtr decal_ortho;
};

```


```cpp
// AppWorldLogic.cpp

#include "AppWorldLogic.h";

using namespace Unigine;

int AppWorldLogic::init()
{

	// создаём ортографическую декаль и задаём её радиус равным 10, ширину и высоту равными 2
	decal_ortho = DecalOrtho::create();
	decal_ortho->setRadius(10.0f);
	decal_ortho->setWidth(2.0f);
	decal_ortho->setHeight(2.0f);

	// задаём имя и позицию декали
	decal_ortho->setName("Ortho Decal");
	decal_ortho->setWorldPosition(Math::Vec3(0.0f, 0.0f, 5.0f));

	return 1;
}

```


## Класс DecalOrtho

### Методы класса

---

## static DecalOrthoPtr create ( )

Конструктор. Создаёт новую ортографическую декаль с параметрами по умолчанию.
## void setHeight ( float height )

Задаёт новую длину проекционного бокса вдоль оси Y.
### Аргументы

- *float* **height** - Длина проекционного бокса вдоль оси Y, в единицах. Если задано отрицательное значение, вместо него будет использовано 0.

## float getHeight ( ) const

Возвращает текущую длину проекционного бокса вдоль оси Y.
### Возвращаемое значение

Длина проекционного бокса вдоль оси Y, в единицах.
## Math:: mat4 getProjection ( ) const

Возвращает матрицу проекции.
### Возвращаемое значение

Матрица проекции декали.
## void setWidth ( float width )

Задаёт новую длину проекционного бокса вдоль оси X.
### Аргументы

- *float* **width** - Длина проекционного бокса вдоль оси X, в единицах. Если задано отрицательное значение, вместо него будет использовано 0.

## float getWidth ( ) const

Возвращает текущую длину проекционного бокса вдоль оси X, в единицах.
### Возвращаемое значение

Длина проекционного бокса вдоль оси X, в единицах.
## void setZNear ( float znear )

Задаёт новое значение ближней плоскости отсечения.
### Аргументы

- *float* **znear** - Значение ближней плоскости отсечения, в диапазоне от 0 до 1. Если задано отрицательное значение, вместо него будет использовано 0.

## float getZNear ( ) const

Возвращает значение ближней плоскости отсечения.
### Возвращаемое значение

Значение ближней плоскости отсечения, в диапазоне от 0 до 1.
## static int type ( )

Возвращает идентификатор типа.
### Возвращаемое значение

Идентификатор типа.
