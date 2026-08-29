# Unigine Integration into Qt Application


В этой статье описывается пример, расположенный в папке `<UnigineSDK>/source/apps/main_qt`. Пример демонстрирует, как создать Qt Widget и встроить в него Unigine.


> **Notice:** Поддерживается Qt версии **6.5.3**.


В этом примере приложение Qt управляет главным циклом: функция движка *[iterate()](../../../../api/library/engine/class.engine_cpp.md#iterate_void)* вызывается при получении запроса на перерисовку всего Qt-виджета или его части (см. функцию *AppQt::timerEvent()*, определённую в файле `<UnigineSDK>/source/source/apps/main_qt/AppQt/AppQt.cpp`).
