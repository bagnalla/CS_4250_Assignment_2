/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Circle class. The static Init method
					creates the prototype vertices of a unit circle. This represents
					a simple planar circle.

Date:				October 16, 2015

*************************************************************************************/

#ifndef CIRCLE_H
#define CIRCLE_H

#include "Angel.h"
#include "Object.h"
#include "Game.h"
#include "Util.h"

namespace Bagnall
{
	class Circle : public Object
	{
	public:
		/**********************************************************************
		Function:		Init
		Purpose:		Create the prototype vertices for the Circle class.
		**********************************************************************/
		static void Init();

		/**********************************************************************
		Function:		Circle constructor
		Purpose:		Create a Circle object.
		**********************************************************************/
		Circle();

		/**********************************************************************
		Function:		Update
		Purpose:		Update the Circle object.
		Calls:			move, rotate, checkIfAboveTarget
		**********************************************************************/
		void Update();

		/**********************************************************************
		Function:		Draw
		Purpose:		Draw the Circle object.
		Parameters:		bool select - draw id color if true
		**********************************************************************/
		void Draw(bool select);

		/**********************************************************************
		Function:		Contains
		Purpose:		Determines whether the Circle contains a given point.
		Parameters:		vec4 point - the given point
		**********************************************************************/
		bool Contains(vec4 point);

		/**********************************************************************
		Function:		IsWithinRange
		Purpose:		Determines whether a given point is within a given
						range of the Circle's center.
		Parameters:		vec4 point - the given point
						float range - the radius around the center to check
		**********************************************************************/
		bool IsWithinRange(vec4 point, float range);

		/**********************************************************************
		Function:		Intersects
		Purpose:		Determines whether the Circle intersects another Circle.
		Parameters:		Circle *c - the other Circle
		**********************************************************************/
		bool Intersects(Circle *c);

	private:
		static const int VERTEX_COUNT; // # of prototype vertices
		static int globalVertexOffset; // position of vertices in global vertex array
	};
}

#endif
