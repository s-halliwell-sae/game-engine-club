#include "sprite.h"
#include "rendersystem.h"

Sprite::Sprite(std::string name): Renderable(name){
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	vec2 data[] = {
		vec2(0, 	0.33),
		vec2(-0.33,-0.33),
		vec2(0.33, -0.33),
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::Render(RenderSystem* rs) {
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}