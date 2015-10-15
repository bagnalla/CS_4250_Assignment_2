/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Implementation file for the Util class.

Date:				October 16, 2015

*************************************************************************************/

#include "Util.h"

namespace Bagnall
{
	// PUBLIC

	std::vector<vec4> Util::CreateCatmullCurve(vec4 p0, vec4 p1, vec4 p2, vec4 p3, float curviness)
	{
		float weightIncrement = 1.0 / curviness;

		std::vector<vec4> vectors;
		for (float s = weightIncrement; s < 1.0; s += weightIncrement)
		{
			vectors.push_back(CRSpline::Eq(s, p0, p1, p2, p3));
		}

		vectors.push_back(p2);

		return vectors;
	}

	// need at least 3 vertices
	std::vector<vec4> Util::CreateBlob(float curviness, vec4 verts[], int numOfVerts)
	{
		std::vector<vec4> vertices;

		std::vector<vec4> curve = CreateCatmullCurve(verts[numOfVerts - 1], verts[0], verts[1], verts[2], curviness);
		vertices.insert(vertices.end(), curve.begin(), curve.end());

		for (int i = 1; i < numOfVerts - 2; i++)
		{
			curve = CreateCatmullCurve(verts[i - 1], verts[i], verts[i + 1], verts[i + 2], curviness);
			vertices.insert(vertices.end(), curve.begin(), curve.end());
		}

		curve = CreateCatmullCurve(verts[numOfVerts - 3], verts[numOfVerts - 2], verts[numOfVerts - 1], verts[0], curviness);
		vertices.insert(vertices.end(), curve.begin(), curve.end());

		curve = CreateCatmullCurve(verts[numOfVerts - 2], verts[numOfVerts - 1], verts[0], verts[1], curviness);
		vertices.insert(vertices.end(), curve.begin(), curve.end());

		vertices.push_back(vertices[0]);

		return vertices;
	}

	std::vector<vec4> Util::CreateCircle(vec4 position, float radius, int numberOfVertices)
	{
		std::vector<vec4> vertices;
		float increment = (2 * M_PI) / (numberOfVertices - 1);
		for (float theta = 0.0f; theta <= 2 * M_PI; theta += increment)
			vertices.push_back(position + vec4(radius*cos(theta), radius*sin(theta), 0, 1));
		vertices.push_back(position + vec4(radius, 0, 0, 1));
		return vertices;
	}

	std::vector<vec4> Util::CreateCube(float size)
	{
		// taken from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/
		vec4 verts[] = { vec4(-size / 2.0, -size / 2.0, -size / 2.0, 1.0),
			vec4(-size / 2.0, -size / 2.0, size / 2.0, 1.0),
			vec4(-size / 2.0, size / 2.0, size / 2.0, 1.0),
			vec4(size / 2.0, size / 2.0, -size / 2.0, 1.0),
			vec4(-size / 2.0, -size / 2.0, -size / 2.0, 1.0),
			vec4(-size / 2.0, size / 2.0, -size / 2.0, 1.0),
			vec4(size / 2.0, -size / 2.0, size / 2.0, 1.0),
			vec4(-size / 2.0, -size / 2.0, -size / 2.0, 1.0),
			vec4(size / 2.0, -size / 2.0, -size / 2.0, 1.0),
			vec4(size / 2.0, size / 2.0, -size / 2.0, 1.0),
			vec4(size / 2.0, -size / 2.0, -size / 2.0, 1.0),
			vec4(-size / 2.0, -size / 2.0, -size / 2.0, 1.0),
			vec4(-size / 2.0, -size / 2.0, -size / 2.0, 1.0),
			vec4(-size / 2.0, size / 2.0, size / 2.0, 1.0),
			vec4(-size / 2.0, size / 2.0, -size / 2.0, 1.0),
			vec4(size / 2.0, -size / 2.0, size / 2.0, 1.0),
			vec4(-size / 2.0, -size / 2.0, size / 2.0, 1.0),
			vec4(-size / 2.0, -size / 2.0, -size / 2.0, 1.0),
			vec4(-size / 2.0, size / 2.0, size / 2.0, 1.0),
			vec4(-size / 2.0, -size / 2.0, size / 2.0, 1.0),
			vec4(size / 2.0, -size / 2.0, size / 2.0, 1.0),
			vec4(size / 2.0, size / 2.0, size / 2.0, 1.0),
			vec4(size / 2.0, -size / 2.0, -size / 2.0, 1.0),
			vec4(size / 2.0, size / 2.0, -size / 2.0, 1.0),
			vec4(size / 2.0, -size / 2.0, -size / 2.0, 1.0),
			vec4(size / 2.0, size / 2.0, size / 2.0, 1.0),
			vec4(size / 2.0, -size / 2.0, size / 2.0, 1.0),
			vec4(size / 2.0, size / 2.0, size / 2.0, 1.0),
			vec4(size / 2.0, size / 2.0, -size / 2.0, 1.0),
			vec4(-size / 2.0, size / 2.0, -size / 2.0, 1.0),
			vec4(size / 2.0, size / 2.0, size / 2.0, 1.0),
			vec4(-size / 2.0, size / 2.0, -size / 2.0, 1.0),
			vec4(-size / 2.0, size / 2.0, size / 2.0, 1.0),
			vec4(size / 2.0, size / 2.0, size / 2.0, 1.0),
			vec4(-size / 2.0, size / 2.0, size / 2.0, 1.0),
			vec4(size / 2.0, -size / 2.0, size / 2.0, 1.0)
		};

		std::vector<vec4> v;
		v.assign(verts, verts + 36);
		return v;
		//return std::vector<vec4>(verts, std::end(verts));
	}

	vec4 Util::ChopZ(vec4 v)
	{
		return vec4(v.x, v.y, 0.0, v.w);
	}

	vec4 Util::NormalizeWorldCoordinates(vec4 position)
	{
		//return vec4(position.x / (Game::WORLD_SIZE.x / 2.0) - 1, (Game::WORLD_SIZE.y - position.y) / (Game::WORLD_SIZE.y / 2) - 1, position.z - position.y / Game::WORLD_SIZE.y, position.w);
		return vec4(position.x / (Game::WORLD_SIZE.x / 2.0) - 1, (Game::WORLD_SIZE.y - position.y) / (Game::WORLD_SIZE.y / 2) - 1, position.z / (Game::WORLD_SIZE.z / 2.0), position.w);
	}

	vec4 Util::NormalizeWorldVector(vec4 vec)
	{
		//return vec4(vec.x / (Game::WORLD_SIZE.x / 2.0), -vec.y / (Game::WORLD_SIZE.y / 2.0), vec.z - vec.y / Game::WORLD_SIZE.y, vec.w);
		return vec4(vec.x / (Game::WORLD_SIZE.x / 2.0), -vec.y / (Game::WORLD_SIZE.y / 2.0), vec.z / (Game::WORLD_SIZE.z/2.0), vec.w);
	}

	mat4 Util::WorldScale()
	{
		return Angel::Scale(1.0 / (Game::WORLD_SIZE.x / 2.0), 1.0 / (Game::WORLD_SIZE.y / 2.0), 1.0 / (Game::WORLD_SIZE.z / 2.0));
	}

	float Util::Distance(vec4 p1, vec4 p2)
	{
		return length(p1 - p2);
	}

	float Util::DistanceSquared(vec4 p1, vec4 p2)
	{
		vec4 displacement = p2 - p1;
		return dot(displacement, displacement);
	}

	mat4 Util::Identity()
	{
		mat4 c;
		for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			c[i][j] = 0.0;
		for (int i = 0; i < 4; i++)
			c[i][i] = 1.0;
		return c;
	}

	std::string Util::TimeToString(int time)
	{
		time /= 1000;

		int seconds = time % 60;
		time /= 60;

		int minutes = time % 60;
		time /= 60;

		return (time != 0 ? ToStringWithLeadingZeroes(time, 2) + ":" : "")
			+ ToStringWithLeadingZeroes(minutes, 2) + ":"
			+ ToStringWithLeadingZeroes(seconds, 2);
	}
}
