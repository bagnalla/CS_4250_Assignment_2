/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Blob class. This is the only class for
					which each object has its own set of vertices. The vertices
					are generated with the CRSpline function based on the initial
					vertices passed to the constructor.

Date:				October 16, 2015

*************************************************************************************/

#ifndef BLOB_H
#define BLOB_H

#include "Angel.h"
#include "Object.h"
#include "Game.h"
#include "Util.h"

namespace Bagnall
{
	class Blob : public Object
	{
	public:
		/**********************************************************************
		Function:		Blob constructor
		Purpose:		Create a blob object.
		Parameters:		std::vector<vec4> initial_vertices - used to make curve
						float curviness - determines # of points on curve
		**********************************************************************/
		Blob(std::vector<vec4> initial_vertices, float curviness);

		/**********************************************************************
		Function:		Update
		Purpose:		Update the blob. Not used at the moment.
		**********************************************************************/
		void Update();

		/**********************************************************************
		Function:		Draw
		Purpose:		Draw the blob.
		Parameters:		bool select - draw id color if true
		**********************************************************************/
		void Draw(bool select);

	private:
		int vertexCount; // number of vertices
		int globalVertexOffset; // position of vertices in global vertices array

		/**********************************************************************
		Function:		createVertices
		Purpose:		Create the verties of the blob.
		**********************************************************************/
		void createVertices(std::vector<vec4> initial_vertices, float curviness);
	};
}

#endif
