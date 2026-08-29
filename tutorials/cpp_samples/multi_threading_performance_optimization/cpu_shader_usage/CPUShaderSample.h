#pragma once
#include <UnigineComponentSystem.h>
#include <UnigineVector.h>

#include <atomic>
#include <memory>

// Демонстрирует асинхронные обновления кластеров с помощью CPUShader.
// Использует двойную буферизацию кластеров: один отображается, другой обновляется в фоновых потоках.
// В конце кадра кластеры меняются местами, чтобы рендеринг всегда показывал актуальные данные без задержки.
class CPUShaderSample final : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(CPUShaderSample, ComponentBase)
	COMPONENT_DESCRIPTION("This component demonstrates asynchronous cluster updates using CPUShader.")

	COMPONENT_INIT(init)
	COMPONENT_SWAP(swap)

	// файл меша, используемый для создания экземпляров ObjectMeshCluster (задаётся в редакторе)
	PROP_PARAM(File, mesh)

private:

	// Представляет один кластер с видимой и асинхронной версиями
	struct AsyncCluster
	{
		Unigine::Math::Vec3 offset;
		int seed{0};
		Unigine::Math::Random random;

		Unigine::Math::Scalar timer{100.f};
		Unigine::Vector<Unigine::Math::Mat4> transforms;

		// Используются две версии каждого кластера:
		// - 'cluster' отображается в текущем кадре
		// - 'cluster_async' обновляется в фоне для следующего кадра
		// В конце кадра оба кластера меняются местами, чтобы видимый кластер
		// всегда показывал актуальные обновлённые данные без задержки рендеринга

		Unigine::ObjectMeshClusterPtr cluster;
		Unigine::ObjectMeshClusterPtr cluster_async;
		bool is_need_update{true};
		int frames{0};

		void update(const Unigine::ObjectMeshClusterPtr &cluster_);
		void swap();
		void update();
	};

	// Подкласс CPUShader, который будет асинхронно выполнять наш код.
	// Чтобы реализовать вашу асинхронную логику, переопределите метод process().
	// При вызове runSync() или runAsync() этот метод автоматически вызывается на рабочих потоках.
	struct UpdateClusterCPUShader final : Unigine::CPUShader
	{
		void process(int thread_num, int threads_count) override;
		void run();
		Unigine::Vector<AsyncCluster> clusters{};
		std::atomic<int> counter{};
	};

private:
	void init();         // создаёт кластеры и инициализирует CPUShader
	void swap() const;   // запускает асинхронное обновление кластера через CPUShader

private:
	std::unique_ptr<UpdateClusterCPUShader> shader;
};
