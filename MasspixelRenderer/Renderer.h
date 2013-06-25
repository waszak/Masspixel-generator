#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GL/glfw.h>

const int DEFAULT_WINDOW_WIDTH = 800;
const int DEFAULT_WINDOW_HEIGHT = 600;

class RenderTask;

class Renderer {
private:
	GLuint programId, fboId, vboId, vaoId;
	int windowWidth, windowHeight;
	RenderTask *currentTask;

	void initFBO();
public:
	Renderer() : programId(0), fboId(0), vboId(0), vaoId(0) { };
	~Renderer() { };

	void init(int windowWidth = DEFAULT_WINDOW_WIDTH, int windowHeight = DEFAULT_WINDOW_HEIGHT);
	void loadTask(RenderTask *task);
	void loadEffect(const char *vertShaderFilename, const char *fragShaderFilename);
	void renderCurrent();
	void saveToPNGFIle(const char *filename);
	void terminate();
};

#endif