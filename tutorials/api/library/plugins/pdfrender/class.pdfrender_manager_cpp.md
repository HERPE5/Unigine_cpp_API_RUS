# Unigine::Plugins::PDFRender::Manager Class (CPP)

**Header:** #include <plugins/Unigine/PDFRender/UniginePDFRender.h>

> **Notice:** Этот класс является синглтоном.


## Manager Class

---

## PDFFile * load ( const char * path )

Загружает файл PDF по указанному пути.
### Аргументы

- *const char ** **path** - Путь к загружаемому файлу PDF.

### Возвращаемое значение

Загруженный файл PDF.
## void unload ( PDFFile * file )

Выгружает указанный файл PDF.
### Аргументы

- *[PDFFile](../../../../api/library/plugins/pdfrender/class.pdffile_cpp.md) ** **file** - Выгружаемый файл PDF.
