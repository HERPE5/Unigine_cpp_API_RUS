// Рендерит обзор камеры в текстуру каждый кадр и применяет её как albedo
// к объекту. Полезно для камер безопасности, зеркал заднего вида, порталов.

#include "CameraToTexture.h"

#include <UnigineTextures.h>
#include <UnigineViewport.h>

REGISTER_COMPONENT(CameraToTexture);

using namespace Unigine;
using namespace Math;

// Создаёт текстуру render target и вьюпорт, наследует материал от прикреплённого объекта
// и назначает текстуру как albedo с коррекцией UV-трансформации для переворота платформы.
void CameraToTexture::init()
{
	player = checked_ptr_cast<Player>(player_camera.get());
	texture = Texture::create();
	texture->create2D(256, 256, Texture::FORMAT_RG11B10F,
		Texture::SAMPLER_FILTER_LINEAR | Texture::SAMPLER_ANISOTROPY_16
			| Texture::FORMAT_USAGE_RENDER);
	viewport = Viewport::create();
	auto obj = checked_ptr_cast<Object>(node);
	auto mat = obj->getMaterial(0);
	mat = mat->inherit();
	mat->setTexture(mat->findTexture("albedo"), texture);
	mat->setParameterFloat4("uv_transform", vec4(-1.f, Render::isFlipped() ? -1.f : 1.f, 0.f, 0.f));
	obj->setMaterial(mat, 0);
}

// Рендерит обзор камеры в текстуру каждый кадр.
void CameraToTexture::update()
{
	viewport->renderTexture2D(player->getCamera(), texture);
}
