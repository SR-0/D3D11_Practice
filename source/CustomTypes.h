#pragma once

#pragma once

#include <stdlib.h>

#pragma region VECTORS (unsigned int)s

struct vec2u
{
	vec2u(
		unsigned int x = 0,
		unsigned int y = 0)
		:
		x(x),
		y(x)
	{}

	unsigned int x;
	unsigned int y;
};

struct vec3u
{
	vec3u(
		unsigned int x = 0,
		unsigned int y = 0,
		unsigned int z = 0)
		:
		x(x),
		y(x),
		z(z)
	{}

	unsigned int x;
	unsigned int y;
	unsigned int z;
};

struct vec4u
{
	vec4u(
		unsigned int x = 0,
		unsigned int y = 0,
		unsigned int z = 0,
		unsigned int w = 0)
		:
		x(x),
		y(x),
		z(z),
		w(w)
	{}

	unsigned int x;
	unsigned int y;
	unsigned int z;
	unsigned int w;
};

#pragma endregion VECTORS (unsigned int)s

/* ------ */

#pragma region VECTORS (int)s

struct vec2i
{
	vec2i(
		int x = 0,
		int y = 0)
		:
		x(x),
		y(x)
	{}

	int x;
	int y;
};

struct vec3i
{
	vec3i(
		int x = 0,
		int y = 0,
		int z = 0)
		:
		x(x),
		y(x),
		z(z)
	{}

	int x;
	int y;
	int z;
};

struct vec4i
{
	vec4i(
		int x = 0,
		int y = 0,
		int z = 0,
		int w = 0)
		:
		x(x),
		y(x),
		z(z),
		w(w)
	{}

	int x;
	int y;
	int z;
	int w;
};

#pragma endregion VECTORS (int)s

/* ------ */

#pragma region VECTORS (float)s

struct vec2f
{
	vec2f(
		float x = 0.0f,
		float y = 0.0f)
		:
		x(x),
		y(x)
	{}

	float x;
	float y;
};

struct vec3f
{
	vec3f(
		float x = 0.0f,
		float y = 0.0f,
		float z = 0.0f)
		:
		x(x),
		y(x),
		z(z)
	{}

	float x;
	float y;
	float z;
};

struct vec4f
{
	vec4f(
		float x = 0.0f,
		float y = 0.0f,
		float z = 0.0f,
		float w = 0.0f)
		:
		x(x),
		y(y),
		z(z),
		w(w)
	{}

	float x;
	float y;
	float z;
	float w;
};

#pragma endregion VECTORS (float)s

/* ------ */

#pragma region VECTORS (double)s

struct vec2d
{
	vec2d(
		double x = 0.0,
		double y = 0.0)
		:
		x(x),
		y(x)
	{}

	double x;
	double y;
};

struct vec3d
{
	vec3d(
		double x = 0.0,
		double y = 0.0,
		double z = 0.0)
		:
		x(x),
		y(x),
		z(z)
	{}

	double x;
	double y;
	double z;
};

struct vec4d
{
	vec4d(
		double x = 0.0,
		double y = 0.0,
		double z = 0.0,
		double w = 0.0)
		:
		x(x),
		y(y),
		z(z),
		w(w)
	{}

	double x;
	double y;
	double z;
	double w;
};

#pragma endregion VECTORS (double)s

/* ------ */

#pragma region RECTANGLES

struct uRect
{
	uRect(
		unsigned int left = 0,
		unsigned int top = 0,
		unsigned int width = 0,
		unsigned int height = 0)
		:
		left(left),
		top(top),
		width(width),
		height(height)
	{}

	unsigned int left;
	unsigned int top;
	unsigned int width;
	unsigned int height;
};

struct iRect
{
	iRect(
		int left = 0,
		int top = 0,
		int width = 0,
		int height = 0)
		:
		left(left),
		top(top),
		width(width),
		height(height)
	{}

	int left;
	int top;
	int width;
	int height;
};

struct fRect
{
	fRect(
		float left = 0.f,
		float top = 0.f,
		float width = 0.f,
		float height = 0.f)
		:
		left(left),
		top(top),
		width(width),
		height(height)
	{}

	float left;
	float top;
	float width;
	float height;
};

struct dRect
{
	dRect(
		double left = 0.0,
		double top = 0.0,
		double width = 0.0,
		double height = 0.0)
		:
		left(left),
		top(top),
		width(width),
		height(height)
	{}

	double left;
	double top;
	double width;
	double height;
};

#pragma endregion RECTANGLES

/* ------ */

#pragma endregion VERTEXES

struct Vertex
{
	Vertex(
		float x = 0.f,
		float y = 0.f,
		float z = 0.f,
		float w = 1.f)
		:
		position(x, y, z, w)
	{}

	vec4f position;
};

#pragma endregion VERTEX

/* ------ */

#pragma region COLORS

struct Color
{
	Color(
		float r = 0.f,
		float g = 0.f,
		float b = 0.f,
		float a = 0.f)
		:
		r(r),
		g(g),
		b(b),
		a(a)
	{}

	float	r;
	float	g;
	float	b;
	float   a;
};

#pragma endregion COLORS