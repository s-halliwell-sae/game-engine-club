#include "texture.h"

Texture::Texture() : texture(0){
}

Texture::~Texture(){
	if(IsValid()){
		glDeleteTextures(1, &texture);
		texture = 0;
	}
}

bool Texture::IsValid(){
	return glIsTexture(texture);
}

void Texture::LoadFromMemory(vec3* data, u32 width, u32 height, u32 format){
	if(!IsValid()){
		glGenTextures(1, &texture);
	}

	SetFiltering(Nearest);
	SetWrapping(Repeat);
	
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA /*internal*/, width, height, 0, format, GL_FLOAT, data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetFiltering(Filter f){
	// Bad
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, f);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, f);	
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetWrapping(Wrap w){
	// Bad
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, w);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, w);	
	glBindTexture(GL_TEXTURE_2D, 0);
}