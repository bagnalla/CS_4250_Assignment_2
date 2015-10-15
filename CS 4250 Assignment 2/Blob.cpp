/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Implementation file for the Blob class.

Date:				October 16, 2015

*************************************************************************************/

#include "Blob.h"

namespace Bagnall
{
	// PUBLIC

	Blob::Blob(std::vector<vec4> initial_vertices, float curviness) : Object()
	{
		createVertices(initial_vertices, curviness);
	}

	void Blob::Update() {}

	void Blob::Draw(bool select)
	{
		Object::Draw(select);
		glDrawArrays(GL_POLYGON, globalVertexOffset, vertexCount);
	}

	// PRIVATE

	void Blob::createVertices(std::vector<vec4> initial_vertices, float curviness)
		{
			globalVertexOffset = Game::Vertices.size();

			std::vector<vec4> blob = Util::CreateBlob(curviness, &initial_vertices[0], initial_vertices.size());

			vertexCount = blob.size();

			Game::Vertices.insert(Game::Vertices.end(), blob.begin(), blob.end());
		}
}
