#ifndef SPRITE_H
#define SPRITE_H

#include "renderable.h"
#include "common.h"

class Texture;

class Sprite : public Renderable {
protected:
	static u32 uvbo;
	u32 vbo;

	Texture* texture;

public:
	Sprite(std::string);

	void SetTexture(Texture*);
	void Render(RenderSystem*) override;
};

#endif