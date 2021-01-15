#pragma once

#pragma once

#include <stdlib.h>
#include <string>

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
		float x = 0.f,
		float y = 0.f)
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
		float x = 0.f,
		float y = 0.f,
		float z = 0.f)
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
		float x = 0.f,
		float y = 0.f,
		float z = 0.f,
		float w = 0.f)
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

#pragma region COLORS

struct Color
{
	Color(
		float r = 0.f,
		float g = 0.f,
		float b = 0.f,
		float a = 1.f)
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

/*
struct COLOR_LIST
{
	static const Color RED;
	static const Color BLUE;
	static const Color GREEN;
	static const Color PURPLE;
	static const Color YELLOW;
	static const Color CYAN;
	static const Color WHITE;
	static const Color BLACK;
	static const Color GRAY;

	static void Init()
	{
		RED		= const Color(1.0f, 0.0f, 0.0f);
		BLUE	= const Color(0.0f, 1.0f, 0.0f);
		GREEN	= const Color(0.0f, 0.0f, 1.0f);
		PURPLE	= const Color(1.0f, 0.0f, 1.0f);
		YELLOW	= const Color(1.0f, 1.0f, 0.0f);
		CYAN	= const Color(0.0f, 1.0f, 1.0f);
		WHITE	= const Color(1.0f, 1.0f, 1.0f);
		BLACK	= const Color(0.0f, 0.0f, 0.0f);
		GRAY	= const Color(0.5f, 0.5f, 0.5f);
	}
};
*/

#pragma endregion COLORS

/* ------ */

#pragma region RECT(s)

struct uRect
{
	uRect(
		unsigned int left	= 0,
		unsigned int top	= 0,
		unsigned int width	= 0,
		unsigned int height = 0)
		:
		position(top, left),
		size(width, height)
	{}

	vec2u position;
	vec2u size;
};

struct iRect
{
	iRect(
		int left	= 0,
		int top		= 0,
		int width	= 0,
		int height	= 0)
		:
		position(top, left),
		size(width, height)
	{}

	vec2i position;
	vec2i size;
};

struct fRect
{
	fRect(
		float left   = 0.f,
		float top	 = 0.f,
		float width  = 0.f,
		float height = 0.f)
		:
		position(top, left),
		size(width, height)
	{}

	vec2f position;
	vec2f size;
};

struct dRect
{
	dRect(
		double left   = 0.0,
		double top    = 0.0,
		double width  = 0.0,
		double height = 0.0)
		:
		position(top, left),
		size(width, height)
	{}

	vec2d position;
	vec2d size;
};

#pragma endregion RECT(s)

/* ------ */

#pragma endregion VERTEX

struct Vertex
{
	Vertex(
		float x = 0.f,
		float y = 0.f,
		float z = 0.f,
		float w = 1.f)
		:
		position(x, y, z, w),
		color(0.f, 0.f, 0.f, 1.f)
	{}

	void setPosition(
		float x, 
		float y, 
		float z, 
		float w = 1.f)
	{
		position.x = x;
		position.y = y;
		position.z = z;
		position.w = w;
	}

	void setColor(
		float r, 
		float g, 
		float b, 
		float a = 1.f)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	UINT getBufferSize()
	{
		return sizeof(this);
	}

	vec4f	position;
	Color	color;
};

#pragma endregion VERTEX

/* ------ */

#pragma region COMMON VERTEX STUCTURES

struct Vertex2
{
	Vertex2(
		Vertex v0 = Vertex(0.f, 0.f, 0.f, 1.f),
		Vertex v1 = Vertex(0.f, 0.f, 0.f, 1.f))
	{
		vertices[0] = v0;
		vertices[1] = v1;
	}

	UINT getBufferSize()
	{
		return sizeof(vertices);
	}

	Vertex vertices[2];
};

struct Vertex3
{
	Vertex3(
		Vertex v0 = Vertex(0.f, 0.f, 0.f, 1.f),
		Vertex v1 = Vertex(0.f, 0.f, 0.f, 1.f),
		Vertex v2 = Vertex(0.f, 0.f, 0.f, 1.f))
	{
		vertices[0] = v0;
		vertices[1] = v1;
		vertices[2] = v2;
	}

	UINT getBufferSize()
	{
		return sizeof(vertices);
	}

	Vertex vertices[3];
};

struct Vertex4
{
	Vertex4(
		Vertex v0 = Vertex(0.f, 0.f, 0.f, 1.f),
		Vertex v1 = Vertex(0.f, 0.f, 0.f, 1.f),
		Vertex v2 = Vertex(0.f, 0.f, 0.f, 1.f),
		Vertex v3 = Vertex(0.f, 0.f, 0.f, 1.f))
	{
		vertices[0] = v0;
		vertices[1] = v1;
		vertices[2] = v2;
		vertices[3] = v3;
	}

	UINT getBufferSize()
	{
		return sizeof(vertices[0].getBufferSize()) * 4;
	}

	Vertex vertices[4];
};

#pragma endregion COMMON VERTEX STUCTURES

/* ------ */

class StringConverter
{
public:

	static std::wstring StringToWide(std::string str)
	{
		std::wstring wStr(str.begin(), str.end());
		return wStr;
	}

};

/* ------ */

//#pragma region SHAPES
//
//class Rectangle2D
//{
//public:
//
//	Rectangle2D(fRect rect)
//		:
//		form(rect)
//	{
//		alignVertices(form);
//	}
//
//private:
//
//	void alignVertices(fRect rect)
//	{
//		vertices.v1 = Vertex(rect.position.x, rect.position.y);
//		/*
//
//			[*]- - - - |
//			 |         |
//			 |         |
//			 | - - - - |
//
//		*/
//
//		vertices.v2 = Vertex(rect.position.x, rect.size.y);
//		/*
//
//			 | - - - - |
//			 |         |
//			 |         |
//			[*]- - - - |
//
//		*/
//
//		vertices.v3 = Vertex(rect.size.x, rect.position.y);
//		/*
//
//			 | - - - -[*]
//			 |         |
//			 |         |
//			 | - - - - |
//
//		*/
//
//		vertices.v4 = Vertex(rect.size.x, rect.size.y);
//		/*
//
//			 | - - - - |
//			 |         |
//			 |         |
//			 | - - - -[*]
//
//		*/
//	}
//
//public:
//
//	vec2f getPosition()
//	{
//		return form.position;
//	}
//
//	vec2f getSize()
//	{
//		form.size;
//	}
//
//public:
//
//	void setPosition(vec2u position)
//	{
//		form.position = vec2f((float)position.x, (float)position.y);
//		alignVertices(form);
//	}
//
//	void setSize(vec2u size)
//	{
//		form.size = vec2f((float)size.x, (float)size.y);
//		alignVertices(form);
//	}
//
//private:
//
//	fRect	form;
//	Vertex4 vertices;
//
//};
//
//#pragma endregion SHAPES