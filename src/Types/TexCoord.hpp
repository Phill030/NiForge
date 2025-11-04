#pragma once

struct TexCoord
{
	float u, v;
	TexCoord() : u(0.0f), v(0.0f) {}
	TexCoord(float u, float v) : u(u), v(v) {}
};