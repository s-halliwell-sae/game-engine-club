#ifndef SPRITE_H
#define SPRITE_H

#include "renderable.h"
#include "common.h"

class Sprite : public Renderable {
protected:
	u32 vbo;

public:
	Sprite(std::string);

	void Render(RenderSystem*) override;
};

#endif