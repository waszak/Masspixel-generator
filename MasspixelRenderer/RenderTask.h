#ifndef RENDER_TASK_H
#define RENDER_TASK_H

class RenderTask {
public:
	int resolutionWidth, resolutionHeight;
	float time;

	RenderTask() : resolutionWidth(0), resolutionHeight(0), time(0.0f) { };
	RenderTask(int _resWidth, int _resHeight, float _time) : resolutionWidth(_resWidth), resolutionHeight(_resHeight), time(_time) { };
	~RenderTask() { };
};

#endif