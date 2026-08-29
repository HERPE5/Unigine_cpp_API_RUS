# Creating C++ Application


> **Warning:** Видеоурок создан для **SDK версии 2.12**. Применимо для версий **до 2.21**.


Приложение на основе UNIGINE можно реализовать исключительно средствами C++, без использования UnigineScript.


Эта статья описывает, как добавить логику в ваш проект с помощью языка C++. Код, написанный на C++, одинаков для всех поддерживаемых платформ: Windows и Linux. Различие заключается в способе компиляции проекта.


### См. также


- Статьи в разделе [Development for Different Platforms](../../code/environment/index.md), чтобы узнать больше о подготовке среды разработки, установке UNIGINE SDK и сборке приложения для разных платформ.
- Примеры, расположенные в папках `<UnigineSDK>/source/samples/Api` и `<UnigineSDK>/source/samples/App`.


## Создание пустого приложения на C++


Начать собственный проект на C++ с помощью UNIGINE SDK Browser очень просто:


1. Откройте UNIGINE SDK Browser.
2. Перейдите на вкладку *[Templates](../../sdk/index.md#templates)* и нажмите кнопку *Create Project* на карточке шаблона *C++ Empty*. ![](../../sdk/projects/create_project_cpp.png)
3. Укажите следующие параметры: ![](cpp_parameters.png) > **Notice:** Подробнее об этих параметрах см. [this article](../../sdk/projects/index_cpp.md)

  - **Project name** — укажите имя вашего проекта.
  - **Location** — укажите путь к папке вашего проекта.
  - **SDK** — выберите редакцию UNIGINE SDK.
  - **API+IDE** — выберите *C++*, чтобы начать работу с C++ API. Этот параметр зависит от платформы: также можно создать проект **C++ CMake**

    - На **Windows** можно создать проект **C++ Visual Studio 2022**.
    - На **Linux** можно создать проект **C++ GNU make**.
  - **Precision** - укажите точность. В этом примере мы будем использовать [double precision](../../code/double_precision/index.md).
4. Нажмите кнопку *CREATE NEW PROJECT*. Проект появится в списке вкладки *My Projects*. ![](project_created.png)


Вы можете [run](../../sdk/projects/index_cpp.md#run) свой проект, нажав кнопку *Run*.


> **Notice:** По умолчанию в файле [world script](../../code/fundamentals/execution_sequence/app_logic_system.md#world_script) создаются WorldLight и PlayerSpectator. Вы можете оставить функции скрипта мира пустыми и создать собственные источники света и игроков с помощью C++.


## Реализация логики на C++


В этом разделе мы добавим логику в пустой проект приложения на C++.


Следующий пример показывает, как вращать материальный шар, который по умолчанию создаётся в вашем проекте.


1. Если вы создали **проект C++ для Visual Studio**: Если вы создали **проект C++ GNU make**:

  1. Выберите ваш проект C++ в UNIGINE SDK Browser и нажмите кнопку *Open Code IDE*, чтобы открыть проект в IDE. ![](../../sdk/projects/edit_code.png)

  1. В созданном проекте C++ нажмите кнопку *Other Actions*, затем кнопку *Open Folder*. ![](other_actions.png)
  2. Перейдите в папку `<YOUR PROJECT>\source\` и откройте файл `AppWorldLogic.cpp` в любом текстовом редакторе.
2. Напишите (или скопируйте) следующий код в файл `AppWorldLogic.cpp` вашего проекта. ```cpp #include "AppWorldLogic.h" #include <UnigineWorld.h> #include <UnigineGame.h> using namespace Unigine; // указатель на узел NodePtr node; AppWorldLogic::AppWorldLogic() { } AppWorldLogic::~AppWorldLogic() { } int AppWorldLogic::init() { // получаем узел материального шара node = World::getNodeByName("material_ball"); return 1; } int AppWorldLogic::shutdown() { return 1; } int AppWorldLogic::update() { // получаем длительность кадра float ifps = Game::getIFps(); // задаём угол поворота double angle = ifps * 90.0f; // задаём угол в матрице трансформации Unigine::Math::Mat4 transform = node->getTransform(); transform.setRotateZ(angle); // задаём новую трансформацию узлу node->setTransform(node->getTransform() * transform); return 1; } int AppWorldLogic::postUpdate() { return 1; } int AppWorldLogic::updatePhysics() { return 1; } ```
3. Если вы используете **Visual Studio**, выполните следующее: Если вы создали **проект GNU Make**:

  1. Перед компиляцией кода убедитесь, что для вашего проекта правильно заданы соответствующие настройки платформы и конфигурации. ![](ide_project_settings.png)
  2. Соберите проект, нажав *Build -> Build Solution* в *Visual Studio*. ![](cpp_build.png)
  3. Запустите проект, нажав *Debug -> Start* в подходящем режиме в *Visual Studio*. ![](cpp_run.png)

  1. Выполните команду make в терминале для компиляции приложения. ```bash make ```
  2. Запустите приложение с помощью скрипта *run*.


> **Notice:** Чтобы запустить отладочную версию вашего проекта из SDK Browser, включите режим *Debug* в *[Customize Run Options.](../../sdk/projects/index_cpp.md#customize_run)*
