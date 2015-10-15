/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Line class. The static Init method
					creates the prototype vertices of a line. When drawn, the line
					vertices in the vertex buffer are actually modified and sent to
					the GPU and drawn with no shader-level transformation.

Date:				October 16, 2015

*************************************************************************************/

#ifndef LINE_H
#define LINE_H

#include "Angel.h"
#include "Game.h"
#include "Util.h"

namespace Bagnall
{
	class Line
	{
	public:
		/**********************************************************************
		Function:		Init
		Purpose:		Create the prototype vertices and waypoints for the
						Line class.
		**********************************************************************/
		static void Init();

		vec4 P1, // point 1 of the line
			P2; // point 2 of the line

		/**********************************************************************
		Function:		Line constructor
		Purpose:		Create a Line object.
		**********************************************************************/
		Line();

		/**********************************************************************
		Function:		Draw
		Purpose:		Draw the Line object.
		**********************************************************************/
		void Draw();

	private:
		static int globalVertexOffset; // position of vertices in global vertex array
	};
}

#endif
