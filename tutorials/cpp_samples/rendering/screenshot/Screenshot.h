// Захватывает текущий кадр из окна движка в файл PNG.
// Использует подход на основе флага для захвата скриншотов по запросу во время
// callback рендеринга, сохраняя файлы с уникальными временными метками.

#pragma once
#include <UnigineComponentSystem.h>


// Захватывает скриншоты из окна движка по запросу с помощью триггера на основе флага.
class Screenshot final : public Unigine::EventConnections
{
public:
	// Связывает захват скриншота с конкретным окном движка
	void setWindow(const Unigine::EngineWindowPtr &window);

	// Устанавливает флаг для захвата скриншота при следующем рендеринге
	UNIGINE_INLINE void grab() { grab_flag = true;}
private:
	// Callback рендеринга, выполняющий фактический захват скриншота
	void render();

private:
	Unigine::EngineWindowPtr window_;
	// Если true, следующий callback рендеринга захватит и сохранит скриншот
	bool grab_flag{false};
};
