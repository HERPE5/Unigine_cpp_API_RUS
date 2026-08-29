// Пример-заготовка, демонстрирующая методы жизненного цикла Component System. Показаны все
// доступные коллбэки: init, update_async_thread, update_sync_thread, update,
// post_update, update_physics, swap и shutdown. Фактическая логика определена в заголовке.

#include "ComponentParametersSample.h"

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(ComponentParameters);

// Вызывается при инициализации мира; здесь инициализируются ресурсы для сцены мира.
void ComponentParameters::init()
{

}

// Вызывается перед updateSyncThread в параллельных потоках; выполняется вместе с postUpdate и updatePhysics.
// Подходит для тяжёлых вычислений (поиск пути, процедурные текстуры), не блокирующих основной поток.
void ComponentParameters::update_async_thread()
{

}

// Вызывается перед update и postUpdate в параллельных потоках; блокирует основной поток до завершения.
// Подходит для сложных вычислений, применяемых к текущему узлу, с более строгими гарантиями безопасности.
void ComponentParameters::update_sync_thread()
{

}

// Вызывается перед каждым кадром рендеринга; здесь указываются все функции, связанные с логикой.
void ComponentParameters::update()
{

}

// Вызывается перед рендерингом каждого кадра; поведение можно скорректировать после обновления состояния узла.
void ComponentParameters::post_update()
{

}

// Вызывается с фиксированной частотой физики (по умолчанию 60 раз в секунду) независимо от частоты кадров.
void ComponentParameters::update_physics()
{

}

// Вызывается после завершения рендеринга, физики, поиска пути, GUI и всех асинхронных потоков.
// Результаты updateAsyncThread можно безопасно обработать здесь до запуска очереди удаления.
void ComponentParameters::swap()
{

}

// Вызывается при завершении работы мира; здесь удаляются ресурсы, созданные во время выполнения, чтобы избежать утечек памяти.
void ComponentParameters::shutdown()
{

}
