#include "Renderer.h"
#include "RenderTask.h"

int main() {
	Renderer renderer;
	renderer.init();
	renderer.loadEffect("vert.vert", "spoko-efekt.frag");
	RenderTask task(1, 800, 600, 12.0);
	renderer.loadTask(&task);
	renderer.renderCurrent();
	renderer.saveToPNGFIle("render.png");
	renderer.terminate();
	return 0;
}