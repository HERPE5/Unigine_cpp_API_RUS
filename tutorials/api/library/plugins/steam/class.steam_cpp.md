# Unigine::Plugins::Steam Class (CPP)

**Header:** #include <plugins/Unigine/Steam/UnigineSteam.h>

> **Notice:** Этот класс является одиночкой (singleton).


## Steam Class

### Перечисления

## CALLBACK_INDEX

| Name | Description |
|---|---|
| **CALLBACK_OVERLAY_SHOWN** = 0 |  |
| **CALLBACK_LEADERBOARD_FOUND** = 1 |  |
| **CALLBACK_LEADERBOARD_SCORES_UPLOADED** = 2 |  |
| **CALLBACK_LEADERBOARD_SCORES_DOWNLOADED** = 3 |  |

## PERSONA_STATE

| Name | Description |
|---|---|
| **PERSONA_STATE_OFFLINE** = 0 | Друг в данный момент не в сети. |
| **PERSONA_STATE_ONLINE** = 1 | Друг в сети. |
| **PERSONA_STATE_BUSY** = 2 | Пользователь в сети, но занят. |
| **PERSONA_STATE_AWAY** = 3 | Функция автоматического отсутствия. |
| **PERSONA_STATE_SNOOZE** = 4 | Автоматическое отсутствие в течение долгого времени. |
| **PERSONA_STATE_LOOKING_TO_TRADE** = 5 | В сети, торговля. |
| **PERSONA_STATE_LOOKING_TO_PLAY** = 6 | В сети, желает играть. |

## FRIEND_FLAG

| Name | Description |
|---|---|
| **FRIEND_FLAG_NONE** = 0 | Нет. |
| **FRIEND_FLAG_BLOCKED** = 1 | Пользователи, которых текущий пользователь заблокировал для связи. |
| **FRIEND_FLAG_FRIENDSHIP_REQUESTED** = 2 | Пользователи, отправившие приглашение в друзья текущему пользователю. |
| **FRIEND_FLAG_IMMEDIATE** = 4 | "Обычные" друзья текущего пользователя. |
| **FRIEND_FLAG_CLAN_MEMBER** = 8 | Пользователи, состоящие в одной из тех же (небольших) групп Steam, что и текущий пользователь. |
| **FRIEND_FLAG_ON_GAME_SERVER** = 16 | Пользователи, находящиеся на том же игровом сервере. |
| **FRIEND_FLAG_REQUESTING_FRIENDSHIP** = 128 | Пользователи, которым текущий пользователь отправил приглашения в друзья. |
| **FRIEND_FLAG_REQUESTING_INFO** = 256 | Пользователи, в данный момент отправляющие дополнительную информацию о себе. |
| **FRIEND_FLAG_IGNORED** = 512 | Пользователи, для связи с которыми текущий пользователь установил игнорирование. |
| **FRIEND_FLAG_IGNORED_FRIEND** = 1024 | Пользователи, которые игнорируют текущего пользователя, но текущий пользователь всё ещё знает о них. |
| **FRIEND_FLAG_ALL** = 65535 | Все флаги друзей. |

## FRIEND_RELATIONSHIP

| Name | Description |
|---|---|
| **FRIEND_RELATIONSHIP_NONE** = 0 | У пользователей нет отношений. |
| **FRIEND_RELATIONSHIP_BLOCKED** = 1 | Пользователь только что нажал "Игнорировать" на приглашении в друзья. Это не сохраняется. |
| **FRIEND_RELATIONSHIP_REQUEST_RECIPIENT** = 2 | Пользователь запросил дружбу с текущим пользователем. |
| **FRIEND_RELATIONSHIP_FRIEND** = 3 | "Обычный" друг. |
| **FRIEND_RELATIONSHIP_REQUEST_INITIATOR** = 4 | Текущий пользователь отправил приглашение в друзья. |
| **FRIEND_RELATIONSHIP_IGNORED** = 5 | Текущий пользователь явно заблокировал этого другого пользователя от комментариев/чата и т.д. Это сохраняется. |
| **FRIEND_RELATIONSHIP_IGNORED_FRIEND** = 6 | Пользователь проигнорировал текущего пользователя. |

## OVERLAY_TO_STORE

| Name | Description |
|---|---|
| **OVERLAY_TO_STORE_FLAG_NONE** = 0 | Нет. |
| **OVERLAY_TO_STORE_ADD_TO_CART** = 1 | Добавить указанный app ID в корзину пользователя. |
| **OVERLAY_TO_STORE_ADD_TO_CART_AND_SHOW** = 2 | Добавить указанный app ID в корзину пользователя и показать страницу магазина. |

## OVERLAY_POSITION

| Name | Description |
|---|---|
| **OVERLAY_POSITION_TOP_LEFT** = 0 | Позиция всплывающего уведомления оверлея в верхнем левом углу. |
| **OVERLAY_POSITION_TOP_RIGHT** = 1 | Позиция всплывающего уведомления оверлея в верхнем правом углу. |
| **OVERLAY_POSITION_BOTTOM_LEFT** = 2 | Позиция всплывающего уведомления оверлея в нижнем левом углу. |
| **OVERLAY_POSITION_BOTTOM_RIGHT** = 3 | Позиция всплывающего уведомления оверлея в нижнем правом углу. |

## OVERLAY_TO_WEB_PAGE_MODE

Используемый режим оверлея.
| Name | Description |
|---|---|
| **OVERLAY_TO_WEB_PAGE_MODE_DEFAULT** = 0 |  |
| **OVERLAY_TO_WEB_PAGE_MODE_MODAL** = 1 |  |

### Методы класса

---

## int getAppID ( ) const

Возвращает Steam AppID.
### Возвращаемое значение

Steam AppID.
## bool isSubscribed ( ) const

Проверяет, разрешено ли пользователю запускать текущее приложение.
### Возвращаемое значение

true, если пользователю разрешено запускать текущее приложение; иначе false.
## bool isLowViolence ( ) const

Проверяет, предоставляет ли лицензия пользователя депо с пониженным уровнем насилия.
### Возвращаемое значение

true, если лицензия пользователя предоставляет депо с пониженным уровнем насилия; иначе false.
## bool isCybercafe ( ) const

Возвращает значение, указывающее, предназначено ли текущее приложение для интернет-кафе.
### Возвращаемое значение

true, если текущее приложение предназначено для интернет-кафе; иначе false.
## bool isVACBanned ( ) const

Проверяет, есть ли у пользователя VAC-бан на его аккаунте.
### Возвращаемое значение

true, если у пользователя есть VAC-бан на аккаунте; иначе false.
## const char * getCurrentGameLanguage ( ) const

Возвращает текущий язык, установленный пользователем.
### Возвращаемое значение

Язык, установленный пользователем.
## const char * getAvailableGameLanguages ( ) const

Возвращает разделённый запятыми список языков.
### Возвращаемое значение

Разделённый запятыми список языков.
## const char * getUserDataFolder ( ) const

Возвращает имя папки данных пользователя.
### Возвращаемое значение

Имя папки данных пользователя.
## void showOverlay ( const char * dialog )

Открывает оверлей Steam на указанном диалоге.
### Аргументы

- *const char ** **dialog** - Диалог для открытия. Допустимые значения: "friends", "community", "players", "settings", "officialgamegroup", "stats", "achievements".

## void showOverlayToWebPage ( const char * url , Steam::OVERLAY_TO_WEB_PAGE_MODE mode )

Активирует веб-браузер оверлея Steam непосредственно с указанным URL.
### Аргументы

- *const char ** **url** - Веб-страница для открытия (требуется полный адрес с протоколом).
- *[Steam::OVERLAY_TO_WEB_PAGE_MODE](../../../../api/library/plugins/steam/class.steam_cpp.md#OVERLAY_TO_WEB_PAGE_MODE)* **mode** - Устанавливаемый режим оверлея. Одно из значений *[OVERLAY_TO_WEB_PAGE_MODE_*](#OVERLAY_TO_WEB_PAGE_MODE_DEFAULT)*.

## void showOverlayToUser ( const char * dialog , unsigned long long steam_id )

Открывает оверлей Steam на указанном диалоге.
### Аргументы

- *const char ** **dialog** - Диалог для открытия. Допустимые значения: "steamid", "chat", "jointrade", "stats", "achievements", "friendadd", "friendremove", "friendrequestaccept", "friendrequestignore".
- *unsigned long long* **steam_id** - Steam ID контекста, для которого открывается этот диалог.

## void showOverlayToStore ( int app_id , Steam::OVERLAY_TO_STORE store_flag )

Активирует оверлей Steam на странице магазина Steam для указанного приложения.
### Аргументы

- *int* **app_id** - App ID, страницу магазина которого нужно показать.
- *[Steam::OVERLAY_TO_STORE](../../../../api/library/plugins/steam/class.steam_cpp.md#OVERLAY_TO_STORE)* **store_flag** - Флаг, изменяющий поведение при открытии страницы, одно из значений [OVERLAY_TO_STORE_*](#OVERLAY_TO_STORE_FLAG_NONE).

## void showOverlayInviteDialog ( unsigned long long steam_id_lobby )

Активирует оверлей Steam для открытия диалога приглашения. Приглашения, отправленные из этого диалога, будут для указанного лобби.
### Аргументы

- *unsigned long long* **steam_id_lobby** - Steam ID лобби, в которое будут приглашены выбранные пользователи.

## void setOverlayNotificationPosition ( Steam::OVERLAY_POSITION position )

Задаёт, в каком углу должно отображаться всплывающее уведомление оверлея Steam.
### Аргументы

- *[Steam::OVERLAY_POSITION](../../../../api/library/plugins/steam/class.steam_cpp.md#OVERLAY_POSITION)* **position** - Позиция всплывающего уведомления оверлея, одно из значений [OVERLAY_POSITION_*](#OVERLAY_POSITION_TOP_LEFT).

## bool isOverlayShown ( ) const

Проверяет, запущен ли оверлей Steam и может ли пользователь получить к нему доступ.
### Возвращаемое значение

true, если оверлей запущен и пользователь может получить к нему доступ; иначе false.
## unsigned long long getMyUserID ( ) const

Возвращает ID текущего пользователя.
### Возвращаемое значение

ID текущего пользователя.
## const char * getMyName ( ) const

Возвращает персональное (отображаемое) имя текущего пользователя. Это то же имя, что отображается на странице профиля пользователя в сообществе.
### Возвращаемое значение

Персональное (отображаемое) имя текущего пользователя.
## Steam::PERSONA_STATE getMyState ( ) const

Возвращает статус друга текущего пользователя.
### Возвращаемое значение

Статус друга текущего пользователя, одно из значений [PERSONA_STATE_*](#PERSONA_STATE_OFFLINE).
## const char * getUserName ( unsigned long long steam_id_friend )

Возвращает персональное (отображаемое) имя указанного пользователя.
### Аргументы

- *unsigned long long* **steam_id_friend** - Steam ID пользователя.

### Возвращаемое значение

Персональное имя текущего пользователя в формате UTF-8. Гарантированно не NULL. Возвращает пустую строку ("") или "[unknown]", если Steam ID недействителен или неизвестен вызывающей стороне.
## int getNumFriends ( int friend_flags )

Возвращает количество известных клиенту пользователей, которые соответствуют указанному критерию (друзья, заблокированные, пользователи на том же сервере и т.д.).
### Аргументы

- *int* **friend_flags** - Комбинированное объединение (побитовое "или") одного или нескольких значений [FRIEND_FLAG_*](#FRIEND_FLAG_NONE).

### Возвращаемое значение

Количество пользователей, соответствующих указанному критерию. Возвращает -1, если текущий пользователь не вошёл в систему.
## unsigned long long getFriendByIndex ( int ifriend , int ifriend_flags )

### Аргументы

- *int* **ifriend** - Индекс от 0 до GetFriendCountFromSource.
- *int* **ifriend_flags** - .

### Возвращаемое значение

.
## Steam::FRIEND_RELATIONSHIP getUserRelationship ( unsigned long long steam_id_friend )

Возвращает отношения с указанным пользователем.
### Аргументы

- *unsigned long long* **steam_id_friend** - Steam ID другого пользователя.

### Возвращаемое значение

Отношения с указанным пользователем, одно из значений [FRIEND_RELATIONSHIP_*](#FRIEND_RELATIONSHIP_NONE).
## Steam::PERSONA_STATE getUserPersonaState ( unsigned long long steam_id_friend )

Возвращает статус друга.
### Аргументы

- *unsigned long long* **steam_id_friend** - Steam ID пользователя.

### Возвращаемое значение

Статус друга, одно из значений [PERSONA_STATE_*](#PERSONA_STATE_OFFLINE).
## Variable getUserAvatarSmall ( unsigned long long id )

Возвращает дескриптор маленького аватара для указанного пользователя.
### Аргументы

- *unsigned long long* **id** - Steam ID пользователя.

### Возвращаемое значение

Steam-дескриптор маленького (32*32 px) изображения. Возвращает 0, если у пользователя не задан аватар.
## Variable getUserAvatarMedium ( unsigned long long id )

Возвращает дескриптор среднего аватара для указанного пользователя.
### Аргументы

- *unsigned long long* **id** - Steam ID пользователя.

### Возвращаемое значение

Steam-дескриптор среднего (64x64 px) изображения. Возвращает 0, если у пользователя не задан аватар.
## Variable getUserAvatarLarge ( unsigned long long id )

Возвращает дескриптор большого аватара для указанного пользователя.
### Аргументы

- *unsigned long long* **id** - Steam ID пользователя.

### Возвращаемое значение

Steam-дескриптор большого (128*128 px) изображения. Возвращает 0, если у пользователя не задан аватар.
## SteamLeaderboard * createLeaderboard ( const char * name )

Возвращает интерфейс таблицы лидеров.
### Аргументы

- *const char ** **name** - Имя создаваемой таблицы лидеров.

### Возвращаемое значение

Интерфейс таблицы лидеров.
## SteamLeaderboard * getLeaderboard ( int id )

Возвращает интерфейс таблицы лидеров.
### Аргументы

- *int* **id** - ID просматриваемой таблицы лидеров.

### Возвращаемое значение

Интерфейс таблицы лидеров.
## void deleteLeaderboard ( SteamLeaderboard * OUT_leaderboard )

Удаляет таблицу лидеров.
### Аргументы

- *[SteamLeaderboard](../../../../api/library/plugins/steam/class.steamleaderboard_cpp.md) ** **OUT_leaderboard** - Интерфейс таблицы лидеров. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
