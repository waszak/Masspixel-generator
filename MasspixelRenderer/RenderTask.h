#ifndef RENDER_TASK_H
#define RENDER_TASK_H

class RenderTask {
public:
	int id, resolutionWidth, resolutionHeight;
	float time;

	RenderTask() : id(0), resolutionWidth(0), resolutionHeight(0), time(0.0f) { };
	RenderTask(int _id, int _resWidth, int _resHeight, float _time) : id(_id), resolutionWidth(_resWidth), resolutionHeight(_resHeight), time(_time) { };
	~RenderTask() { };
};

#endif