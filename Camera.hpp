#pragma once
class Camera {
public:
	Camera(float camera_x, float camera_y);
	void cameraUpdate(float xW, float yW, double speed);

	float x;
	float y;

	float dX;
	float dY;
};