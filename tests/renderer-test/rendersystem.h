#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

struct SDL_Window;

class RenderSystem {
private:
	void* glctx;
	float aspect;

public:
	RenderSystem(SDL_Window*);
	~RenderSystem();

	float GetAspect() const;
	void NotifyResize(int w, int h);
};

#endif