#include "randomGenerator.h"

uint16_t RandomGenerator::seed_ = 42;

uint16_t RandomGenerator::u16() {
	seed_ ^= seed_ << 7;
	seed_ ^= seed_ >> 11;
	seed_ ^= seed_ << 2;
	return seed_;
}

float RandomGenerator::reciprocal() {
	return (1.f / 65535.f) * u16();
}
