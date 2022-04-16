#include "Camera.hpp"
#include <iostream>
#include <math.h>
Camera::Camera(float camera_x, float camera_y) 
	: x(camera_x), y(camera_y) {

	dX = 0;
	dY = 0;
}

void Camera::cameraUpdate(float xW, float yW, double speed) {
	dX = xW - x;
	x += dX * speed;

	dY = yW - y;
	y += dY * speed;
}