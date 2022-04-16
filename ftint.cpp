#include "Ftint.hpp"
int ftint(float Float) {
	int Int = int(Float + 0.5f - (Float < 0));
	return Int;
}