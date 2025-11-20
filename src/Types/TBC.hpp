#pragma once

// Tension, bias, continuity. 
struct TBC
{
	float t; // Tension
	float b; // Bias
	float c; // Continuity
	TBC() : t(0.0f), b(0.0f), c(0.0f) {}
	TBC(float t, float b, float c) : t(t), b(b), c(c) {}
};