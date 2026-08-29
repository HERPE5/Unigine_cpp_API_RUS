# Функции цветовых моделей (CPP)

**Header:** #include <UnigineMathLibColorSpaces.h>


## Класс Math

### Методы класса

---

## vec3 hueToRgb ( float hue )

Преобразует значение цвета Hue в значения цвета RGB (Red, Green, Blue).
### Аргументы

- *float* **hue** - Значение цвета Hue.

### Возвращаемое значение

Значения цвета RGB (Red, Green, Blue).
## vec3 rgbToHcv ( vec3 rgb )

Преобразует значения цвета RGB (Red, Green, Blue) в значения цвета HCV (Hue, Chroma, Value).
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md)* **rgb** - Значения цвета RGB (Red, Green, Blue).

### Возвращаемое значение

Значения цвета HCV (Hue, Chroma, Value).
## vec3 rgbToHsv ( vec3 rgb )

Преобразует значения цвета RGB (Red, Green, Blue) в значения цвета HSV (Hue, Saturation, Value).
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md)* **rgb** - Значения цвета RGB (Red, Green, Blue).

### Возвращаемое значение

Значения HSV (Hue, Saturation, Value).
## vec3 hsvToRgb ( vec3 hsv )

Преобразует значения цвета HSV (Hue, Saturation, Value) в значения цвета RGB (Red, Green, Blue).
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md)* **hsv** - Значения HSV (Hue, Saturation, Value).

### Возвращаемое значение

Значения цвета RGB (Red, Green, Blue).
## vec3 rgbToHcy ( vec3 rgb )

Преобразует значения цвета RGB (Red, Green, Blue) в значения цвета HCY (Hue, Chroma, Luma).
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md)* **rgb** - Значения цвета RGB (Red, Green, Blue).

### Возвращаемое значение

Значения цвета HCY (Hue, Chroma, Luma).
## vec3 hcyToRgb ( vec3 hcy )

Преобразует значения HCY (Hue, Chroma, Luma) в значения цвета RGB (Red, Green, Blue).
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md)* **hcy** - Значения цвета HCY (Hue, Chroma, Luma).

### Возвращаемое значение

Значения цвета RGB (Red, Green, Blue).
## vec3 rgbToHcl ( vec3 rgb )

Преобразует значения цвета RGB (Red, Green, Blue) в значения цвета HCL (Hue, Chroma, Luminance).
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md)* **rgb** - Значения цвета RGB (Red, Green, Blue).

### Возвращаемое значение

Значения цвета HCL (Hue, Chroma, Luminance).
## vec3 hclToRgb ( vec3 hcl )

Преобразует значения HCL (Hue, Chroma, Luminance) в значения цвета RGB (Red, Green, Blue).
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md)* **hcl** - Значения цвета HCL (Hue, Chroma, Luminance).

### Возвращаемое значение

Значения цвета RGB (Red, Green, Blue).
## vec3 rgbToHsl ( vec3 rgb )

Преобразует значения цвета RGB (Red, Green, Blue) в значения цвета HSL (Hue, Saturation, Lightness).
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md)* **rgb** - Значения цвета RGB (Red, Green, Blue).

### Возвращаемое значение

Значения цвета HSL (Hue, Saturation, Lightness).
## vec3 hslToRgb ( vec3 hsl )

Преобразует значения HSL (Hue, Saturation, Lightness) в значения цвета RGB (Red, Green, Blue).
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md)* **hsl** - Значения цвета HSL (Hue, Saturation, Lightness).

### Возвращаемое значение

Значения цвета RGB (Red, Green, Blue).
## vec3 rgbToYuv ( vec3 rgb )

Преобразует значения цвета RGB (Red, Green, Blue) в значения цвета YUV (Luminance, Delta Blue, Delta Red).
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md)* **rgb** - Значения цвета RGB (Red, Green, Blue).

### Возвращаемое значение

Значения цвета YUV (Luminance, Delta Blue, Delta Red).
## vec3 yuvToRgb ( vec3 yuv )

Преобразует значения YUV (Luminance, Delta Blue, Delta Red) в значения цвета RGB (Red, Green, Blue).
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md)* **yuv** - Значения цвета YUV (Luminance, Delta Blue, Delta Red).

### Возвращаемое значение

Значения цвета RGB (Red, Green, Blue).
## vec3 rgbToYcbcr ( vec3 rgb )

Преобразует значения цвета RGB (Red, Green, Blue) в значения цвета YCbCr (Luma, Chrominance Blue, Chrominance Red).
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md)* **rgb** - Значения цвета RGB (Red, Green, Blue).

### Возвращаемое значение

Значения цвета YCbCr (Luma, Chrominance Blue, Chrominance Red).
## vec3 ycbcrToRgb ( vec3 ycc )

Преобразует значения YCbCr (Luma, Chrominance Blue, Chrominance Red) в значения цвета RGB (Red, Green, Blue).
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md)* **ycc** - Значения цвета YCbCr (Luma, Chrominance Blue, Chrominance Red).

### Возвращаемое значение

Значения цвета RGB (Red, Green, Blue).
## vec3 rgbToYcgco ( vec3 rgb )

Преобразует значения цвета RGB (Red, Green, Blue) в значения цвета YCgCo (Luma, Chrominance Green, Chrominance Orange).
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md)* **rgb** - Значения цвета RGB (Red, Green, Blue).

### Возвращаемое значение

Значения цвета YCgCo (Luma, Chrominance Green, Chrominance Orange).
## vec3 ycgcoToRgb ( vec3 ycc )

Преобразует значения цвета YCgCo (Luma, Chrominance Green, Chrominance Orange) в значения цвета RGB (Red, Green, Blue).
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md)* **ycc** - Значения цвета YCgCo (Luma, Chrominance Green, Chrominance Orange).

### Возвращаемое значение

Значения цвета RGB (Red, Green, Blue).
