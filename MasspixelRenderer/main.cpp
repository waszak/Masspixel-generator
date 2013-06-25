#include "Renderer.h"
#include "RenderTask.h"

#include <cstdio>
#include <cstdlib>

int main(int argc, char *argv[]) {
	if(argc < 6) {
		printf("Too few arguments!\n");
		return 1;
	}
	char *resultFilename = argv[1];
	char *fragmentShaderFilename = argv[2];
	int width = atoi(argv[3]);
	int height = atoi(argv[4]);
	float time = atof(argv[5]);
	Renderer renderer;
	renderer.init();
	renderer.loadEffect("vert.vert", fragmentShaderFilename);
	RenderTask task(width, height, time);
	renderer.loadTask(&task);
	renderer.renderCurrent();
	renderer.saveToPNGFIle(resultFilename);
	renderer.terminate();
	return 0;
}