/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Implementation file for the Line class.

Date:				October 16, 2015

*************************************************************************************/

#include "Line.h"

namespace Bagnall
{
	// PUBLIC

	void Line::Init()
	{
		globalVertexOffset = Game::Vertices.size();
		Game::Vertices.push_back(vec4(0, 0, 0, 1));
		Game::Vertices.push_back(vec4(0, 0, 0, 1));
	}

	Line::Line() {}

	void Line::Draw()
	{
		Game::Vertices[globalVertexOffset] = Angel::Translate(Util::NormalizeWorldCoordinates(P1)) * Util::WorldScale() * vec4(0, 0, 0, 1);
		Game::Vertices[globalVertexOffset + 1] = Angel::Translate(Util::NormalizeWorldCoordinates(P2)) * Util::WorldScale() * vec4(0, 0, 0, 1);

		glUniformMatrix4fv(Game::TransformLoc, 1, GL_TRUE, Util::Identity());
		glUniform4fv(Game::ColorLoc, 1, vec4(1, 1, 1, 0.25));

		glBufferSubData(GL_ARRAY_BUFFER, sizeof(vec4)*globalVertexOffset, sizeof(vec4)*2, &Game::Vertices[globalVertexOffset]);
		glDrawArrays(GL_LINES, globalVertexOffset, 2);
	}

	// PRIVATE

	int Line::globalVertexOffset;
}
