/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Implementation file for the Circle class.

Date:				October 16, 2015

*************************************************************************************/

#include "Circle.h"

namespace Bagnall
{
	// PUBLIC

	void Circle::Init()
	{
		globalVertexOffset = Game::Vertices.size();
		Game::Vertices.push_back(vec4(0, 0, 0, 1));
		std::vector<vec4> circle = Util::CreateCircle(vec4(), 1.0, VERTEX_COUNT - 1);
		Game::Vertices.insert(Game::Vertices.end(), circle.begin(), circle.end());
	}

	Circle::Circle() : Object() {}

	void Circle::Update() {}

	void Circle::Draw()
	{
		Object::Draw();
		glDrawArrays(GL_TRIANGLE_FAN, globalVertexOffset, VERTEX_COUNT);
	}

	bool Circle::Contains(vec4 point)
	{
		return (Util::Distance(point, position) <= scale.x);
	}

	bool Circle::IsWithinRange(vec4 point, float range)
	{
		return (Util::Distance(position, point) <= range);
	}

	bool Circle::Intersects(Circle *c)
	{
		return (Util::Distance(position, c->position) <= scale.x + c->scale.x);
	}

	// PRIVATE

	const int Circle::VERTEX_COUNT = 100;
	int Circle::globalVertexOffset;
}
