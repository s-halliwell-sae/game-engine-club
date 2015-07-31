#include "sprite.h"
#include "rendersystem.h"

u32 Sprite::uvbo = 0;

Sprite::Sprite(std::string name): Renderable(name){
	if(uvbo == 0){
		glGenBuffers(1, &uvbo);
		glBindBuffer(GL_ARRAY_BUFFER, uvbo);

		vec2 data[] = {
			vec2( 0, 1),
			vec2( 1, 1),
			vec2( 1, 0),
			vec2( 0, 0),
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	vec2 data[] = {
		// vec2(cos(0*M_PI/3), sin(0*M_PI/3)) * 0.5f,
		// vec2(cos(2*M_PI/3), sin(2*M_PI/3)) * 0.5f,
		// vec2(cos(4*M_PI/3), sin(4*M_PI/3)) * 0.5f,
		vec2(-1,-1) * 0.25f,
		vec2( 1,-1) * 0.25f,
		vec2( 1, 1) * 0.25f,
		vec2(-1, 1) * 0.25f,
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::SetTexture(Texture* ntex){
	texture = ntex;
}

void Sprite::Render(RenderSystem* rs) {
	if(texture){
		rs->BindTexture(texture);
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0 /* vertex */, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, uvbo);
	glVertexAttribPointer(1 /* uv */, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}