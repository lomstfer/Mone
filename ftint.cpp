#include "Ftint.hpp"

// Rounds a float to an int instead of truncating
int ftint(float Float) {
	int Int = int(Float + 0.5f - (Float < 0));
	return Int;
}