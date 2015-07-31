#ifndef TEXTURE_H
#define TEXTURE_H

#include "common.h"

class Texture {
	friend class RenderSystem;
public:
	enum Filter {
		Linear = GL_LINEAR,
		Nearest = GL_NEAREST,
	};

	enum Wrap {
		Repeat = GL_REPEAT,
		Clamp = GL_CLAMP_TO_EDGE,
	};

protected:
	u32 texture;

public:
	Texture();
	~Texture();

	bool IsValid();
	void LoadFromMemory(vec3*, u32, u32, u32 format);

	void SetFiltering(Filter);
	void SetWrapping(Wrap);
};

#endif
