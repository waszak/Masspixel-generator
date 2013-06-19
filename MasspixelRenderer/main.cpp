#include <GL/glew.h>
#include <GL/glfw.h>

#include <string>
#include <fstream>
#include <sstream>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 720;

const GLfloat vboData[] = 
{
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   1.0f,  1.0f, 0.0f,
   -1.0f, -1.0f, 0.0f,
   1.0f, 1.0f, 0.0f,
   -1.0f, 1.0f, 0.0f
};

GLuint programId = 0;
GLuint vboId = 0;
GLuint vaoId = 0;

GLuint loadShaders(const char * vertex_file_path,const char * fragment_file_path) {
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertex_file_path, std::ios::in);
	if(vertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(vertexShaderStream, Line))
			vertexShaderCode += "\n" + Line;
		vertexShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		return 0;
	}

	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragment_file_path, std::ios::in);
	if(fragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(fragmentShaderStream, Line))
			fragmentShaderCode += "\n" + Line;
		fragmentShaderStream.close();
	}

	printf("Compiling shader : %s\n", vertex_file_path);
	char const *vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderId, 1, &vertexSourcePointer , NULL);
	glCompileShader(vertexShaderId);

	printf("Compiling shader : %s\n", fragment_file_path);
	char const *fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderId, 1, &fragmentSourcePointer , NULL);
	glCompileShader(fragmentShaderId);

	printf("Linking program\n");
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
	return programId;
}

int main() {
	glfwInit();
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 8, 8, 8, 8, 16, 0, GLFW_WINDOW);
	glewExperimental = true;
	glewInit();

	programId = loadShaders("vert.vert", "spoko-efekt.frag");

	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vboData), vboData, GL_STATIC_DRAW);

	do {
		glClearColor(0.2, 0.5, 0.5, 1);
		glDisable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(programId);
		glUniform1f(glGetUniformLocation(programId, "time"), glfwGetTime());
		glUniform2f(glGetUniformLocation(programId, "resolution"), WINDOW_WIDTH, WINDOW_HEIGHT);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glVertexAttribPointer(0, 3,  GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, 6); 
		glDisableVertexAttribArray(0);

		glUseProgram(0);

		glfwSwapBuffers();
	} while(!glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED));

	glfwTerminate();
	glDeleteBuffers(1, &vboId);
	glDeleteVertexArrays(1, &vaoId);
}