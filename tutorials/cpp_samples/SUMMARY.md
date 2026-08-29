# C++ Code Samples


## Animation Characters

- [Bones: Constraints](animation_characters/bones_constraints/README.md): Применение ограничений вращения костей.
- [Bones: Foot Placement](animation_characters/bones_foot_placement/README.md): Этот пример демонстрирует упрощённый вариант размещения ступней на поверхности с использованием цепочек IK.
- [Bones: Inverse Kinematics](animation_characters/bones_inverse_kinematics/README.md): Управление костями с помощью обратной кинематики.
- [Bones: Look At Chains](animation_characters/bones_look_at_chains/README.md): Использование цепочек LookAt для наведения на цель.
- [Bones: Masks](animation_characters/bones_masks/README.md): Использование масок для назначения выборочной логики разным костям.
- [Bones: Retargeting [Animation Graph]](animation_characters/bones_retargeting/README.md): Этот пример демонстрирует, как одна и та же анимация может использоваться на скелетах с разными пропорциями.
- [Bones: Root Motion [Animation Graph]](animation_characters/bones_root_motion/README.md): Этот пример демонстрирует реализацию техники root motion.
- [Bones: Sandbox](animation_characters/bones_sandbox/README.md): Этот пример предоставляет интерфейс, позволяющий визуализировать и опробовать настройку всех доступных параметров для цепочек IK, цепочек LookAt и ограничений вращения костей.
- [Bones: State Machine [Animation Graph]](animation_characters/bones_state_machine/README.md): Этот пример демонстрирует, как создать анимированную машину состояний на основе ObjectMeshSkinned.

## Animation Generic

- [Animation Layers Playback](animation_generic/animation_layers_playback/README.md): Демонстрация использования нескольких слоёв при воспроизведении анимации.
- [Curve2D Animation](animation_generic/curve2d_animation/README.md): Анимация трансформаций и материалов в реальном времени с использованием Curve2D для гибкого нелинейного движения.
- [Global Engine Parameters Animation](animation_generic/global_engine_parameters_animation/README.md): Анимация глобальных параметров движка с использованием модификаторов анимации-синглтонов.
- [Material Parameters Animation](animation_generic/material_parameters_animation/README.md): Анимация параметров масштаба свечения и цвета материала.
- [Node Parameters Animation](animation_generic/node_parameters_animation/README.md): Анимация позиции, поворота и масштаба узла.
- [Physics-Based Animation](animation_generic/physics_based_animation/README.md): Анимация движений на основе физики с использованием различных функций плавности (easing).
- [Property Animation](animation_generic/property_animation/README.md): Анимация параметра свойства.
- [Tracker: Playback](animation_generic/tracker_playback/README.md): Использование Tracker для анимации объектов (позиция, поворот и масштаб).
- [Widget Animation](animation_generic/widget_animation/README.md): Этот пример показывает, как анимировать виджеты с помощью объектов анимации во время выполнения.

## App Logic

- [Advanced Event Connection Patterns](app_logic/advanced_event_connection_patterns/README.md): Продвинутые способы подписки на события в UNIGINE: использование дополнительных аргументов, отбрасывание параметров и хранение дескрипторов подключения для отписки.
- [Component Parameters In Editor](app_logic/component_parameters_in_editor/README.md): Демонстрация типов параметров компонентов и опций настройки.
- [Component System Example](app_logic/component_system_example/README.md): Демонстрация компонентной архитектуры C++ UNIGINE с использованием пользовательских игровых компонентов с динамическим созданием объектов и взаимодействием.
- [Console Interaction](app_logic/console_interaction/README.md): Взаимодействие со встроенной консолью движка и добавление пользовательских консольных команд и переменных через API с использованием классов Console и ConsoleVariable.
- [Custom Stream](app_logic/custom_stream/README.md): Создание собственного класса потока путём наследования от StreamBase и его использование для чтения из файлов и записи в них.
- [Euler Angle Composition And Decomposition](app_logic/euler_angle_composition_and_decomposition/README.md): Демонстрация того, как порядок углов влияет на поворот.
- [Event Connection Patterns](app_logic/event_connection_patterns/README.md): Демонстрация четырёх различных паттернов подписки на события UNIGINE через C++ API, показывающая, как время жизни и управление обработчиком событий могут различаться в зависимости от подхода.
- [File Operations](app_logic/file_operations/README.md): Демонстрация базовых операций ввода-вывода файлов.
- [File System External Package](app_logic/filesystem_external_package/README.md): Демонстрация работы с внешними файлами пакетов через класс Package.
- [File System Mount Points](app_logic/filesystem_mount_points/README.md): Создание и использование точек монтирования в файловой системе для доступа к внешним папкам и файлам пакетов (например, *.zip, *.ung).
- [Inverse FPS Usage](app_logic/inverse_fps_usage/README.md): Использование Game::getIFps() для реализации логики движения, независимой от частоты кадров.
- [JSON](app_logic/json/README.md): Генерация структурированного JSON-документа, содержащего объекты, массивы и различные типы данных, такие как строки, числа, булевы значения и значения null, с последующим обходом и выводом в отформатированном виде.
- [Materials And Properties Enumeration](app_logic/materials_and_properties_enumeration/README.md): Работа с Property Manager и Material Manager для доступа ко всем материалам и свойствам в проекте через API.
- [Type Safe Callbacks](app_logic/type_safe_callbacks/README.md): Использование класса CallbackBase для обёртывания и вызова функций и методов класса с различным количеством аргументов.
- [XML](app_logic/xml/README.md): Демонстрирует, как создавать и изменять XML-документ с помощью класса Xml.

## Input Handling

- [Gamepad](input_handling/gamepad/README.md): Этот пример демонстрирует простое использование ввода с геймпада.
- [Joystick](input_handling/joystick/README.md): Этот пример демонстрирует, как добавить продвинутую обработку ввода с джойстика с поддержкой нескольких контроллеров с мониторингом осей/кнопок в реальном времени и эффектами обратной связи (force feedback).
- [Keyboard And Mouse](input_handling/keyboard_and_mouse/README.md): Этот пример демонстрирует, как добавить мониторинг ввода с клавиатуры и мыши, отслеживание состояний клавиш, движений мыши, событий колеса и позиций курсора в разных системах координат. Он отображает данные ввода в реальном времени, включая нажатия клавиш, дельты мыши и текстовый ввод.
- [Touch](input_handling/touch/README.md): Этот пример демонстрирует, как добавить многосенсорный ввод с сенсорного экрана, визуализируя позиции пальцев динамическими кругами и отображая координаты в реальном времени в проекте.

## Multi Threading Performance Optimization

- [Asynchronous Meshes And Textures Loading](multi_threading_performance_optimization/asynchronous_meshes_and_textures_loading/README.md): Загрузка мешей и текстур в отдельном потоке с использованием класса AsyncQueue.
- [Asynchronous Nodes Loading Stress-Test](multi_threading_performance_optimization/asynchronous_nodes_loading_stress_test/README.md): Асинхронная загрузка узлов через AsyncQueue с пространственной интеграцией в главном потоке.
- [Asynchronous Tasks Scheduler Configuration](multi_threading_performance_optimization/asynchronous_tasks_scheduler_configuration/README.md): Управление задачами через класс AsyncQueue с различными типами потоков, параллельным выполнением и контролем кадров.
- [CPU Shader Usage](multi_threading_performance_optimization/cpu_shader_usage/README.md): Многопоточное обновление нескольких экземпляров ObjectMeshCluster на стороне CPU с использованием класса CPUShader.
- [Custom Threads](multi_threading_performance_optimization/custom_threads/README.md): Создание и запуск пользовательских потоков с использованием класса Unigine::Thread.
- [Microprofiler Custom Counters](multi_threading_performance_optimization/microprofiler_custom_counters/README.md): Использование Microprofile, продвинутого профилировщика CPU/GPU, для отслеживания производительности и оценки времени, затраченного на разные участки кода.
- [Multiple Async Raycast Requests](multi_threading_performance_optimization/multiple_async_raycast_requests/README.md): Запуск и управление большим количеством асинхронных запросов пересечения на основе лучей одновременно.
- [Single Async Raycast Request](multi_threading_performance_optimization/single_async_raycast_request/README.md): Выполнение одиночного асинхронного запроса пересечения на основе позиции курсора мыши пользователя в сцене.

## Navigation

- [Navigation Mesh](navigation/navigation_mesh/README.md): Настройка поиска пути между двумя точками с препятствиями с использованием Navigation Mesh.
- [Navigation Mesh Demo](navigation/navigation_mesh_demo/README.md): Настройка поиска пути к нескольким целям на плоскости с препятствиями с использованием Navigation Mesh.
- [Navigation Sectors](navigation/navigation_sectors/README.md): Настройка поиска пути между двумя точками с препятствиями с использованием Navigation Sectors.
- [Navigation Sectors Demo](navigation/navigation_sectors_demo/README.md): Настройка поиска пути к нескольким целям в кубе с препятствиями с использованием Navigation Sector.

## Network

- [HTTP Image request](network/http_image_request/README.md): Этот пример показывает, как реализовать асинхронный HTTP-запрос к REST API для загрузки файлов изображений и применения их к объектам сцены во время выполнения.
- [HTTP Request Handling](network/http_request_handling/README.md): Реализация асинхронных HTTP GET-запросов к внешнему REST API и отображение полученных данных в пользовательском интерфейсе.
- [TCP Sockets](network/tcp_sockets/README.md): Установка и управление TCP-соединениями сокетов между сервером и несколькими клиентами, каждый из которых представлен приложением на UNIGINE. Клиенты могут подключаться к серверу, обмениваться текстовыми сообщениями через консоль и получать обновления трансформации камеры от сервера.
- [UDP Sockets](network/udp_sockets/README.md): Использование API сокетов для отправки и получения UDP-сообщений в сети между двумя узлами, каждый из которых представлен приложением на UNIGINE.

## Nodes

- [Cluster](nodes/cluster/README.md): Динамическое манипулирование ObjectMeshCluster в UNIGINE, демонстрирующее добавление/удаление экземпляров меша во время выполнения через взаимодействие с пользователем.
- [Lights](nodes/lights/README.md): Этот пример демонстрирует, как создавать источники света (World Light, Projected Light, Omni Light) и изменять их параметры во время выполнения.
- [Node Extern](nodes/node_extern/README.md): Добавление пользовательских узлов, созданных через API, в мир с использованием NodeExtern. Реализация визуализации ограничивающего бокса и настройки узла во время выполнения с сохранением интеграции с движком.
- [Object Extern](nodes/object_extern/README.md): Добавление пользовательских объектов, созданных через API, в мир с использованием ObjectExtern. Реализация пользовательского рендеринга, физики и свойств с сохранением полной интеграции с движком.
- [Player Types](nodes/players_types/README.md): Создание и настройка четырёх доступных типов Player (PlayerDummy, PlayerPersecutor, PlayerSpectator, PlayerActor).
- [Spline Graph](nodes/spline_graph/README.md): Создание и визуализация сплайнового графа (SplineGraph) и перемещение объекта вдоль него.
- [Water Surface Parameters Fetch](nodes/water_surface_parameters_fetch/README.md): Этот пример демонстрирует, как различные параметры влияют на точность операций fetch и пересечения для объекта Global Water на разных уровнях по шкале Бофорта.
- [Water Waves Customization Gerstner](nodes/water_waves_customization_gerstner/README.md): Этот пример демонстрирует, как управлять спектром волн Global Water в ручном режиме через API
- [Water Waves Generation Field Height](nodes/water_waves_generation_field_height/README.md): Создание динамического Field Height с динамической текстурой на основе функции синуса с использованием C++ API.
- [World Spline Graph](nodes/world_spline_graph/README.md): Генерация геометрии на основе сплайнов путём создания WorldSplineGraph из файла *.spl и применения геометрии *.node в режиме растяжения для размещения объектов вдоль сплайнов.

## Physics

- [Body Events](physics/body_events/README.md): Демонстрация использования событий Frozen, Position и ContactEnter класса Body через C++ API.
- [Body Fracture Explosion](physics/body_fracture_explosion/README.md): Симуляция радиального взрыва, который заставляет объект BodyFracture расколоться и применяет силы к его частям.
- [Body Fracture Falling Spheres](physics/body_fracture_falling_spheres/README.md): Непрерывно падающие объекты, разрушающиеся при столкновении, реализованные с использованием класса BodyFracture.
- [Body Fracture Shooting Gallery](physics/body_fracture_shooting_gallery/README.md): Реализация базового физического тира с использованием Fracture Body.
- [Joint Events](physics/joint_events/README.md): Демонстрация использования события Broken класса Joint.
- [Physics Movement](physics/physics_movement/README.md): Простая логика перемещения объекта физическими методами (силой или импульсом).
- [Update Physics](physics/update_physics/README.md): Демонстрация разницы между реализацией движения на основе физики в методах update() и updatePhysics().

## Player Controllers

- [Camera Zoom](player_controllers/camera_zoom/README.md): Создание интерактивной системы камеры с настраиваемым зумом и фокусировкой на выбираемых целях сцены.
- [First-Person Controller](player_controllers/first_person_controller/README.md): Реализация контроллера персонажа от первого лица с продвинутой системой движения и обнаружением столкновений.
- [Observer Controller](player_controllers/observer_controller/README.md): Реализация свободно летающей камеры, аналогичной используемой в UnigineEditor (с зумом, панорамированием, фокусировкой и управлением скоростью).
- [Orbit Camera Controller](player_controllers/orbit_camera_controller/README.md): Создание орбитальной камеры, вращающейся вокруг цели.
- [Persecutor Controller](player_controllers/persecutor_controller/README.md): Создание пользовательской камеры следования за целью с использованием PlayerDummy, воспроизводящей логику PlayerPersecutor с настраиваемым смещением, обработкой столкновений и несколькими режимами следования.
- [Spectator Controller](player_controllers/spectator_controller/README.md): Реализация настраиваемой камеры наблюдателя от первого лица с настраиваемым движением и обнаружением физических столкновений.
- [Top-Down Controller](player_controllers/top_down_controller/README.md): Реализация некоторых элементов стратегии с видом сверху, таких как выбор одного или нескольких юнитов, панорамирование обзора, поворот камеры и плавная фокусировка на текущем выборе.
- [Two-Point Perspective](player_controllers/two_point_perspective/README.md): Симуляция двухточечной перспективной проекции с использованием техники сдвига линзы, реализованной через вспомогательного Dummy Player.

## Procedural Generation Placement

- [Clutter-To-Cluster Converter](procedural_generation_placement/clutter_to_cluster_converter/README.md): Динамическая генерация Mesh Clutter и его преобразование в оптимизированный по производительности Mesh Cluster во время выполнения.
- [Grid-Based Node Spawning](procedural_generation_placement/grid_based_node_spawning/README.md): Порождение узлов по сетке.
- [Procedural Mesh Generation](procedural_generation_placement/procedural_mesh_generation/README.md): Демонстрация процедурной генерации меша во время выполнения вместе с визуализацией того, как разные процедурные режимы влияют на использование памяти при создании и рендеринге.
- [Procedural Mesh Modification](procedural_generation_placement/procedural_mesh_modification/README.md): Демонстрация процедурной модификации меша во время выполнения вместе с визуализацией того, как разные процедурные режимы влияют на потоковую передачу и использование памяти при создании и рендеринге.
- [Procedural Mesh Updates Mesh Clusters](procedural_generation_placement/procedural_mesh_updates_mesh_clusters/README.md): Минимальный пример, показывающий, как сгенерировать и применить процедурный меш во время выполнения, используя правильную последовательность обновления.
- [Procedural Spline Mesh Generation](procedural_generation_placement/procedural_spline_mesh_generation/README.md): Процедурная генерация мешей на основе сплайнов из точек мира с управлением параметрами в реальном времени.
- [Real-Time Mesh Editing Marching Cubes](procedural_generation_placement/real_time_mesh_editing_marching_cubes/README.md): Симуляция процесса рытья земли на основе модификации геометрии меша.
- [Timer-Based Node Spawning](procedural_generation_placement/timer_based_node_spawning/README.md): Настройка простого генератора узлов, создающего узлы с заданной частотой появления.

## Rendering

- [CAD-Like View](rendering/cad_like_view/README.md): Реализация CAD-подобного вида с несколькими синхронизированными видовыми окнами для видов сверху, сбоку, спереди и в перспективе.
- [Camera To Texture](rendering/camera_to_texture/README.md): Захват вывода камеры в реальном времени и проецирование его на текстуру альбедо материала с помощью Viewport::renderTexture2D().
- [Compute Shader](rendering/compute_shader/README.md): Реализация системы частиц на GPU с использованием вычислительных шейдеров.
- [Compute Shader Image](rendering/compute_shader_image/README.md): Создание вычислительного шейдера, обрабатывающего текстуру для чтения-записи на GPU (без CPU).
- [FFP Depth-Tested Line Rendering](rendering/ffp_depth_tested_line_rendering/README.md): Рендеринг пользовательских визуальных элементов (линий) с использованием FFP с включённым тестом глубины.
- [FFP Triangle Fan Rendering](rendering/ffp_triangle_fan_rendering/README.md): Использование функциональности FFP для отрисовки простых 2D-фигур поверх отрендеренного изображения без дополнительных шейдеров.
- [Gbuffer Read](rendering/gbuffer_read/README.md): Доступ к текстурам G-buffer на разных этапах процесса рендеринга путём настройки пользовательского Viewport и перехвата его вывода на этапе рендеринга G-buffer.
- [Gbuffer Write](rendering/gbuffer_write/README.md): Модификация текстур G-buffer на разных этапах процесса рендеринга путём внедрения пользовательского материала в конце прохода G-buffer.
- [Gui To Texture](rendering/gui_to_texture/README.md): Рендеринг элементов GUI в текстуру с использованием Gui::render() и применение результирующей текстуры к материалам.
- [Mesh To Mask Texture](rendering/mesh_to_mask_texture/README.md): Рендеринг меша в текстуру с использованием пользовательского материала для генерации маски.
- [Node To Texture](rendering/node_to_texture/README.md): Рендеринг узла в текстуру с использованием Viewport::renderNodeTexture2D() и установка этой текстуры в качестве текстуры альбедо материала
- [Procedural 3D Volume Texture Generation](rendering/procedural_3d_volume_texture_generation/README.md): Процедурная генерация данных 3D-изображения и использование их как текстуры плотности для объёмного материала в реальном времени.
- [Render Target](rendering/render_target/README.md): Рендеринг всплесков краски в текстуру с использованием класса RenderTarget.
- [Screenshot](rendering/screenshot/README.md): Простая демонстрация того, как сделать скриншот, захватив финальное изображение из последовательности рендеринга.
- [Split-Screen Texture](rendering/split_screen_texture/README.md): Рендеринг видов с двух камер в текстуры и реализация режима разделённого экрана.
- [Structured Buffer](rendering/structured_buffer/README.md): Создание сжатия DXT с использованием структурированных буферов
- [Textures](rendering/textures/README.md): Обновление текстуры альбедо меша с использованием процедурно сгенерированных данных изображения.
- [Visualizer](rendering/visualizer/README.md): Демонстрация полного набора возможностей, предоставляемых классом Visualizer для визуальной отладки.
- [Weapon Clipping](rendering/weapon_clipping/README.md): Рендеринг оружия со второй камеры в текстуру для избежания проблем с отсечением (клиппингом).

## Scene Management

- [Bounding Volume Object Detection](scene_management/bounding_volume_object_detection/README.md): Поиск пересечений между определёнными объёмами (усечённая пирамида, сфера и бокс) и ограничивающими боксами узлов.
- [Control Elements](scene_management/control_elements/README.md): Демонстрация различных типов интерактивных кнопок и рычагов.
- [Create And Modify Objects](scene_management/create_and_modify_objects/README.md): Основы работы с объектами: создание и модификация через API.
- [Create Mesh Primitives](scene_management/create_mesh_primitives/README.md): Создание параметрических 3D-примитивов во время выполнения.
- [Day-Night Cycle](scene_management/day_night_cycle/README.md): Реализация автоматизированной системы смены дня и ночи с переключением освещения и материалов.
- [Move By Trajectory](scene_management/move_by_trajectory/README.md): Три типа движения вдоль заданного пути: линейная интерполяция, сплайновая интерполяция и траектория, загруженная из файла *.path.
- [Node Movement](scene_management/node_movement/README.md): Реализация перемещения и поворота объекта в 3D-пространстве тремя различными методами.
- [Node State Save-Restore](scene_management/node_state_save_restore/README.md): Этот пример демонстрирует, как сохранить и восстановить состояние произвольного узла, что можно использовать для реализации таких вещей, как сериализация сцены, системы отмены/повтора действий (Undo/Redo) или сохранения игры.
- [Nodes And Widgets Lifetime Control](scene_management/nodes_and_widgets_lifetime_control/README.md): Реализация настраиваемого времени жизни узлов и виджетов с сохранением между разными мирами.
- [Raycast Detection And Bitmasking](scene_management/raycast_detection_and_bitmasking/README.md): Использование трассировки лучей для выборочного (на основе маски) обнаружения пересечений.
- [Raycast From Mouse Position](scene_management/raycast_from_mouse_position/README.md): Поиск пересечения между лучом, пущенным от камеры через курсор мыши, и геометрией.
- [Trigger System Examples](scene_management/trigger_system_examples/README.md): Реализация различных типов триггеров.

## Simulation

- [Speed Boat](simulation/speed_boat/README.md): Симуляция динамического кильватерного следа за движущимся катером с использованием комбинации ортографических декалей и систем частиц.

## Sounds

- [3D Sound](sounds/3d_sound/README.md): Воспроизведение источника звука через код.
- [Ambient Sound](sounds/ambient_sound/README.md): Воспроизведение окружающих звуков через код.
- [FMOD Core](sounds/fmod_core/README.md): Интеграция FMOD Core для воспроизведения 2D и 3D звуков в реальном времени с управлением таймлайном и DSP-эффектами. ПРИМЕЧАНИЕ: требуются дополнительные библиотеки, запустите пример для подробностей.
- [FMOD Studio](sounds/fmod_studio/README.md): Интеграция FMOD Studio с интерактивными звуковыми эффектами в реальном времени, пространственным звуком и симуляцией эффекта Доплера. ПРИМЕЧАНИЕ: требуются дополнительные библиотеки, запустите пример для подробностей.
- [Reverberation Zone](sounds/reverberation_zone/README.md): Настройка зоны реверберации и её параметров через код.

## Terrain Modification Usage

- [Asynchronous Terrain Albedo Height Brushes](terrain_modification_usage/asynchronous_terrain_albedo_height_brushes/README.md): Этот пример демонстрирует модификацию ландшафта в реальном времени через прямое манипулирование Landscape Layer Map.
- [Asynchronous Terrain Data Fetch](terrain_modification_usage/asynchronous_terrain_data_fetch/README.md): Этот пример демонстрирует, как получить подробную информацию с поверхности объекта LandscapeTerrain с использованием LandscapeFetch.
- [Asynchronous Terrain Mask Brushes](terrain_modification_usage/asynchronous_terrain_mask_brushes/README.md): Этот пример демонстрирует рисование данных маски Landscape Layer Map в реальном времени с использованием настраиваемой системы кистей.
- [Creating Detail Layers](terrain_modification_usage/creating_detail_layers/README.md): Добавление и управление детализирующими слоями для объекта LandscapeTerrain с использованием методов getDetailMask() и addDetail().
- [Generating Mesh From Terrain](terrain_modification_usage/generating_mesh_from_terrain/README.md): Этот пример демонстрирует, как сгенерировать процедурный меш (ObjectMeshDynamic), представляющий выбранную область Landscape Terrain.
- [Generating Terrain From Textures](terrain_modification_usage/generating_terrain_from_textures/README.md): Этот пример демонстрирует, как динамически сгенерировать Landscape Layer Map с использованием плиточных текстур альбедо, высоты и маски.
- [Height Slicing](terrain_modification_usage/height_slicing/README.md): Этот пример демонстрирует гибридный подход к редактированию ландшафта с использованием как неразрушающих, так и разрушающих техник модификации Landscape Terrain.
- [Polygon-Based Procedural Modifications](terrain_modification_usage/polygon_based_procedural_modifications/README.md): Процедурная генерация полигональных объектов на основе точек мира для редактирования ландшафта и размещения объектов.
- [Real-Time Excavation](terrain_modification_usage/real_time_excavation/README.md): Этот пример демонстрирует разрушающую модификацию Landscape Layer Map в реальном времени с использованием 3D-объекта (например, трактора-грейдера) в качестве инструмента выемки грунта.
- [Real-Time Terrain Rut Deformation](terrain_modification_usage/real_time_terrain_rut_deformation/README.md): Неразрушающая модификация Landscape Terrain во время выполнения путём динамического порождения нескольких Landscape Layer Map под движущимися объектами для создания реалистичных следов колеи на местности.

## Unigine Script Interop

- [Usc Arrays](unigine_script_interop/usc_arrays/README.md): Интеграция между C++ и UnigineScript путём регистрации внешних C++ функций, манипулирующих типами массивов UnigineScript.
- [Usc Callbacks](unigine_script_interop/usc_callbacks/README.md): Вызов функций UnigineScript из кода C++ через callback-функции.
- [Usc Classes](unigine_script_interop/usc_classes/README.md): Экспорт классов из стороны C++ в UnigineScript.
- [Usc Functions](unigine_script_interop/usc_functions/README.md): Этот пример демонстрирует, как экспортировать функции из стороны C++ в UnigineScript. Он включает примеры экспорта обычных функций, обработки нескольких типов данных и регистрации членов класса для объекта, подобного синглтону.
- [Usc Inheritance](unigine_script_interop/usc_inheritance/README.md): Работа с контейнерами UnigineScript через C++ API.
- [Usc Stack](unigine_script_interop/usc_stack/README.md): Использование стека, реализованного через C++, в UnigineScript.
- [Usc Structures](unigine_script_interop/usc_structures/README.md): Предоставление структур C++ для UnigineScript с использованием класса Interpreter.
- [Usc Transfer](unigine_script_interop/usc_transfer/README.md): Передача сложных данных между UnigineScript и C++ с использованием класса Variable и утилиты TypeToVariable.
- [Usc Types](unigine_script_interop/usc_types/README.md): Обеспечение преобразования типов между пользовательскими типами C++ и UnigineScript с использованием класса Variable.
- [Usc Variable](unigine_script_interop/usc_variable/README.md): Работа с различными типами переменных в UnigineScript с использованием класса Variable из кода C++.

## User Interface

- [Object Frame](user_interface/object_frame/README.md): Использование класса WidgetCanvas для рендеринга пользовательских рамок вокруг объектов в видовом окне и сохранения метаданных рамки в формате JSON.
- [Object Text](user_interface/object_text/README.md): Демонстрация 3D текстовых объектов с настраиваемыми параметрами, анимированными цветами и расширенным форматированием с использованием класса ObjectText.
- [Target Marker](user_interface/target_marker/README.md): Реализация маркера, который всегда подсвечивает цель, когда она находится в поле зрения, или отображает стрелку, указывающую направление к цели, когда она вне видимости (выровненную по границам экрана).
- [User Interface](user_interface/user_interface/README.md): Генерация пользовательского интерфейса «на лету» из файла .ui и установка обработчиков событий для виджетов.
- [Widget Canvas](user_interface/widget_canvas/README.md): Использование класса WidgetCanvas для рисования векторных фигур и текста. Холст поддерживает добавление линий, многоугольников и текста путём задания их геометрии через позиции вершин. Элементы слоятся по порядку отрисовки и раскрашиваются индивидуально.
- [Widget Dialogs](user_interface/widget_dialogs/README.md): Создание диалоговых окон виджетов и назначение обработчиков через C++ API
- [Widget Extern](user_interface/widget_extern/README.md): Определение пользовательского виджета через C++ API с использованием WidgetExternBase с полным контролем над компоновкой, рендерингом и взаимодействием.
- [Widget Manipulators](user_interface/widget_manipulators/README.md): Этот пример демонстрирует использование манипуляторов. Вы можете блокировать оси для трансформаций и применять трансформацию в локальных или мировых координатах.
- [Widget Window](user_interface/widget_window/README.md): Создание базового WidgetWindow с использованием C++ API и обработка взаимодействий пользователя (события строки ввода и нажатия кнопки) через подключение функций-обработчиков.
- [Widgets](user_interface/widgets/README.md): Демонстрация различных UI-виджетов в UNIGINE, таких как слайдеры, скроллы, кнопки, чекбоксы, выпадающие списки и т.д.

## Utils

- [Intersection](utils/intersection/README.md)
- [Navigation](utils/navigation/README.md)
- [Network](utils/network/README.md)
