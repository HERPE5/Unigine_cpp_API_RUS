# Unigine::Noise Class (CPP)

**Header:** #include <UnigineMathLibNoise.h>


Этот класс используется для генерации текстур турбулентности (с поддержкой тайлинга).


## Noise Class

### Методы класса

---

## static NoisePtr create ( )

Конструктор. Инициализирует генератор шума.
## static NoisePtr create ( unsigned int seed_ )

Конструктор. Инициализирует генератор шума, задавая новое начальное значение (seed).
### Аргументы

- *unsigned int* **seed_** - Новое начальное значение (seed).

## void setSeed ( unsigned int seed_ )

Задаёт новое начальное значение (seed) для генератора шума.
### Аргументы

- *unsigned int* **seed_** - Новое начальное значение (seed).

## unsigned int getSeed ( ) const

Возвращает текущее начальное значение (seed).
### Возвращаемое значение

Текущее начальное значение (seed).
## float get1 ( float x ) const

Возвращает одномерный белый шум.
### Аргументы

- *float* **x** - Начальное значение.

### Возвращаемое значение

Одномерный белый шум.
## float get2 ( float x , float y ) const

Возвращает двумерный белый шум.
### Аргументы

- *float* **x** - Начальное значение 1.
- *float* **y** - Начальное значение 2.

### Возвращаемое значение

Двумерный белый шум.
## float get3 ( float x , float y , float z ) const

Возвращает трёхмерный (3D) белый шум.
### Аргументы

- *float* **x** - Начальное значение 1.
- *float* **y** - Начальное значение 2.
- *float* **z** - Начальное значение 3.

### Возвращаемое значение

Трёхмерный (3D) белый шум.
## float getTurbulence1 ( float x , int frequency ) const

Возвращает одномерный шум турбулентности.
### Аргументы

- *float* **x** - Начальное значение.
- *int* **frequency** - Частота.

### Возвращаемое значение

Одномерный шум турбулентности.
## float getTurbulence2 ( float x , float y , int frequency ) const

Возвращает двумерный шум турбулентности.
### Аргументы

- *float* **x** - Начальное значение 1.
- *float* **y** - Начальное значение 2.
- *int* **frequency** - Частота.

### Возвращаемое значение

Двумерный шум турбулентности.
## float getTurbulence3 ( float x , float y , float z , int frequency ) const

Возвращает трёхмерный (3D) шум турбулентности.
### Аргументы

- *float* **x** - Начальное значение 1.
- *float* **y** - Начальное значение 2.
- *float* **z** - Начальное значение 3.
- *int* **frequency** - Частота.

### Возвращаемое значение

Трёхмерный (3D) шум турбулентности.
## float getTileable1 ( float x , float width ) const

Возвращает одномерный тайловый шум.
### Аргументы

- *float* **x** - Начальное значение.
- *float* **width** - Ширина тайла.

### Возвращаемое значение

Одномерный тайловый шум.
## float getTileable2 ( float x , float y , float width , float height ) const

Возвращает двумерный тайловый шум.
### Аргументы

- *float* **x** - Начальное значение 1.
- *float* **y** - Начальное значение 2.
- *float* **width** - Ширина тайла.
- *float* **height** - Высота тайла.

### Возвращаемое значение

Двумерный тайловый шум.
## float getTileable3 ( float x , float y , float z , float width , float height , float depth ) const

Возвращает трёхмерный (3D) тайловый шум.
### Аргументы

- *float* **x** - Начальное значение 1.
- *float* **y** - Начальное значение 2.
- *float* **z** - Начальное значение 3.
- *float* **width** - Ширина тайла.
- *float* **height** - Высота тайла.
- *float* **depth** - Глубина тайла.

### Возвращаемое значение

Трёхмерный (3D) тайловый шум.
## float getTileableTurbulence1 ( float x , float width , int frequency ) const

Возвращает одномерный тайловый шум турбулентности.
### Аргументы

- *float* **x** - Начальное значение 1.
- *float* **width** - Ширина тайла.
- *int* **frequency** - Частота.

### Возвращаемое значение

Одномерный тайловый шум турбулентности.
## float getTileableTurbulence2 ( float x , float y , float width , float height , int frequency ) const

Возвращает двумерный тайловый шум турбулентности.
### Аргументы

- *float* **x** - Начальное значение 1.
- *float* **y** - Начальное значение 2.
- *float* **width** - Ширина тайла.
- *float* **height** - Высота тайла.
- *int* **frequency** - Частота.

### Возвращаемое значение

Двумерный тайловый шум турбулентности.
## float getTileableTurbulence3 ( float x , float y , float z , float width , float height , float depth , int frequency ) const

Возвращает трёхмерный (3D) тайловый шум турбулентности.
### Аргументы

- *float* **x** - Начальное значение 1.
- *float* **y** - Начальное значение 2.
- *float* **z** - Начальное значение 3.
- *float* **width** - Ширина тайла.
- *float* **height** - Высота тайла.
- *float* **depth** - Глубина тайла.
- *int* **frequency** - Частота.

### Возвращаемое значение

Трёхмерный (3D) тайловый шум турбулентности.
