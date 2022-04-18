#include "Camera.hpp"
#include <iostream>
#include <math.h>
Camera::Camera(float camera_x, float camera_y) 
	: x(camera_x), y(camera_y) {

	// Distance to the position the camera want to be at (the player's position)
	dX = 0;
	dY = 0;
}

void Camera::cameraUpdate(float xW, float yW, double speed) {
	// Calculate distance and move the camera according to the distance, bigger = faster, smaller = slower
	dX = xW - x;
	x += dX * speed;

	dY = yW - y;
	y += dY * speed;
}