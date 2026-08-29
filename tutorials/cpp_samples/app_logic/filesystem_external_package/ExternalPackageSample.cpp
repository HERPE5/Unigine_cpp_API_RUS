// Демонстрирует реализацию пользовательского внешнего пакета для интеграции с виртуальной файловой системой.
// Пользовательские пакеты расширяют класс Package и предоставляют возможности перечисления, выбора и
// чтения файлов. После регистрации через FileSystem::addExternPackage содержимое пакета
// становится доступным через виртуальные пути, позволяя загружать ресурсы во время выполнения из любого источника.

#include <UnigineComponentSystem.h>
#include <UnigineFileSystem.h>
#include <UnigineObjects.h>
#include <UnigineWorlds.h>
#include <UnigineGame.h>

#include "../../utils/Utils.h"

using namespace Unigine;
using namespace Math;

namespace
{
	// Генерируется случайный vec3 в заданных границах.
	vec3 random_vec3(const vec3 &from, const vec3 &to)
	{
		return {
			Game::getRandomFloat(from.x, to.x),
			Game::getRandomFloat(from.y, to.y),
			Game::getRandomFloat(from.z, to.z)
		};
	}

	// Генерируется случайный vec3 в симметричных границах (-size/2 до +size/2).
	vec3 random_vec3(const vec3 &size)
	{
		return random_vec3(- size * .5f, size * .5f);
	}
}

// Пользовательская реализация Package, генерирующая виртуальные файлы меша на лету.
// Все файлы используют одни и те же данные меша box, но представляются файловой системе
// как отдельные пронумерованные файлы меша (0.mesh, 1.mesh и т.д.).
class ExternalPackage : public Package
{
public:
	// Пакет инициализируется с заданным количеством файлов, данные меша box кешируются.
	ExternalPackage(int num_files)
	{
		this->num_files = num_files;
		file = File::create();

		// Создаём простой меш box и сохраняем его во временный файл.
		// Этот файл используется как источник данных для всех виртуальных мешей.
		MeshPtr mesh = Mesh::create();
		mesh->addBoxSurface("box", vec3 {1.f });

		StringStack<> path = joinPaths(getWorldRootPath(), ".temporary", "box.mesh");

		if (mesh->save(path))
		{
			file->open(path, "rb");
		}
	}

	virtual ~ExternalPackage() = default;

	// Возвращается общее количество виртуальных файлов в этом пакете.
	virtual int getNumFiles() override
	{
		return num_files;
	}

	// Виртуальный путь к файлу генерируется на основе индекса файла (например, "0.mesh", "1.mesh").
	virtual const char *getFilePath(int num) override
	{
		return String::format("%d.mesh", num);
	}

	// Файл выбирается для чтения; размер задаётся, если файл существует в этом пакете.
	virtual bool selectFile(const char *name, size_t &size) override
	{
		bool exists = findFile(name) > 0;

		if (exists)
			size = file->getSize();

		return exists;
	}

	// Данные файла считываются из кешированного меша box в предоставленный буфер.
	virtual bool readFile(unsigned char *data, size_t size) override
	{
		if (!file->isOpened())
			return false;

		// Сбрасываем в начало и считываем все данные меша
		file->seekSet(0);
		size_t written = file->read(data, size);

		return written == size;
	}

	// Существование файла проверяется сопоставлением имени со сгенерированными именами файлов.
	virtual int findFile(const char *name) const override
	{
		for (int i = 0; i < num_files; i += 1)
		{
			if (String::format("%d.mesh", i) == name)
				return 1;
		}

		return 0;
	}

	// Возвращается размер файла (одинаковый для всех файлов, так как они используют одни и те же данные меша).
	virtual size_t getFileSize(int num) const override
	{
		return file->getSize();
	}

private:
	int num_files = 0; // количество виртуальных файлов для предоставления
	FilePtr file;      // дескриптор кешированных данных меша box
};

// Компонент примера, регистрирующий пользовательский пакет и создающий из него меши.
// Демонстрирует интеграцию внешних пакетов с виртуальной файловой системой.
class ExternalPackageSample : public ComponentBase
{
public:
	COMPONENT_DEFINE(ExternalPackageSample, ComponentBase);
	COMPONENT_DESCRIPTION("This component demonstrates loading meshes from a custom " 
							"external package and spawning them randomly in the scene");

	COMPONENT_INIT(init);

private:
	// Внешний пакет регистрируется, меши создаются в случайных позициях.
	void init()
	{
		// Регистрируем пользовательский пакет в виртуальной файловой системе
		FileSystem::addExternPackage("package", new ExternalPackage(num_files));

		// Загружаем каждый виртуальный файл меша и размещаем его случайно на сцене
		for (int i = 0; i < num_files; i += 1)
		{
			ObjectMeshStaticPtr mesh_static = ObjectMeshStatic::create(String::format("%d.mesh", i));

			Vec3 position = Vec3(::random_vec3({ 4.f, 4.f, 2.f })) + Vec3_up * 2.f;
			quat rotation = quat(Game::getRandomFloat(0.f, 360.f), Game::getRandomFloat(0.f, 360.f), Game::getRandomFloat(0.f, 360.f));

			mesh_static->setWorldTransform(Mat4 { rotation, position });
		}
	}

	constexpr static int num_files = 64; // количество экземпляров меша для создания
};

REGISTER_COMPONENT(ExternalPackageSample);
