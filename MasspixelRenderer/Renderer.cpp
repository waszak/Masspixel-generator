#include "Renderer.h"
#include "RenderTask.h"
#include "lodepng.h"

#include <string>
#include <fstream>
#include <sstream>

const GLfloat vboData[] = 
{
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   1.0f,  1.0f, 0.0f,
   -1.0f, -1.0f, 0.0f,
   1.0f, 1.0f, 0.0f,
   -1.0f, 1.0f, 0.0f
};

void Renderer::init(int _windowWidth, int _windowHeight) {
	windowWidth = _windowWidth;
	windowHeight = _windowHeight;
	glfwInit();
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindow(windowWidth, windowHeight, 8, 8, 8, 8, 16, 0, GLFW_WINDOW);
	glewExperimental = true;
	glewInit();
	initFBO();
}

void Renderer::loadTask(RenderTask *newTask) {
	currentTask = newTask;
}

void Renderer::loadEffect(const char *vertShaderFilename, const char *fragShaderFilename) {
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertShaderFilename, std::ios::in);
	if(vertexShaderStream.is_open()) {
		std::string Line = "";
		while(getline(vertexShaderStream, Line)) {
			vertexShaderCode += "\n" + Line;
		}
		vertexShaderStream.close();
		printf("Vertex shader loaded: %s\n", vertShaderFilename);
	} 
	else {
		printf("Impossible to open %s.\n", vertShaderFilename);
	}

	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragShaderFilename, std::ios::in);
	if(fragmentShaderStream.is_open()) {
		std::string Line = "";
		while(getline(fragmentShaderStream, Line)) {
			fragmentShaderCode += "\n" + Line;
		}
		fragmentShaderStream.close();
		printf("Fragment shader loaded: %s\n", fragShaderFilename);
	}
	else {
		printf("Impossible to open %s.\n", fragShaderFilename);
	}

	char const *vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderId, 1, &vertexSourcePointer , NULL);
	glCompileShader(vertexShaderId);

	char const *fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderId, 1, &fragmentSourcePointer , NULL);
	glCompileShader(fragmentShaderId);

	programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
}

void Renderer::renderCurrent() {
	//do {
		glBindFramebuffer(GL_FRAMEBUFFER, fboId);
		glDisable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(programId);
		glUniform1f(glGetUniformLocation(programId, "time"), currentTask->time);
		glUniform2f(glGetUniformLocation(programId, "resolution"), currentTask->resolutionWidth, currentTask->resolutionHeight);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glVertexAttribPointer(0, 3,  GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, 6); 
		glDisableVertexAttribArray(0);
		glfwSwapBuffers();
	//} while(!glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED));
}

void Renderer::saveToPNGFIle(const char *filename) {
	GLubyte *pixels = new GLubyte[windowWidth * windowHeight * 4];
	glReadPixels(0, 0, windowWidth, windowHeight, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	lodepng::encode(filename, pixels, windowWidth, windowHeight);
	delete[] pixels;
}

void Renderer::terminate() {
	glUseProgram(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glfwTerminate();
	glDeleteBuffers(1, &vboId);
	glDeleteVertexArrays(1, &vaoId);
}

// -------------------------------
void Renderer::initFBO() {
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vboData), vboData, GL_STATIC_DRAW);

	glGenFramebuffers(1, &fboId);
	glBindFramebuffer(GL_FRAMEBUFFER, fboId);

	GLuint renderTargetId = 0;
	glGenTextures(1, &renderTargetId);
	glBindTexture(GL_TEXTURE_2D, renderTargetId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowWidth, windowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderTargetId, 0);

	GLenum drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, drawBuffers);
}