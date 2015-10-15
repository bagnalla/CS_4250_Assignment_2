/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Util class. This class is a container
					for static utility functions.

Date:				October 16, 2015

*************************************************************************************/

#ifndef UTIL_H
#define UTIL_H

#include "Angel.h"
#include "CRSpline.h"
#include "Game.h"
#include <sstream>
#include <iomanip>

namespace Bagnall
{
	class Util
	{
	public:
		/**********************************************************************
		Function:		CreateCatmullCurve
		Purpose:		Generate vertices along a curve using a Catmull-Rom
						spline function.
		Parameters:		vec4 previousPoint - control point 0
						vec4 point1 - control point 1
						vec4 point2 - control point 2
						vec4 afterPoint - control point 3
						float curviness - determines the number of points along
											the curve to generate
		Calls:			CRSpline::Eq
		**********************************************************************/
		static std::vector<vec4> CreateCatmullCurve(vec4 p0, vec4 p1, vec4 p2, vec4 p3, float curviness);

		/**********************************************************************
		Function:		CreateBlob
		Purpose:		Generate a "blob" of vertices based on a set of input
						vertices. The resulting set of vertices will be similar
						to the input but with extra points along curves around
						them.
		Parameters:		float curviness - determines the number of points along
											the curves to generate
						vec4 verts[] - the input vertices
						int numOfVerts - the number of input vertices
		Preconditions:	There must be at least three input vertices.
		Calls:			CRSpline::Eq
		**********************************************************************/
		static std::vector<vec4> CreateBlob(float curviness, vec4 verts[], int numOfVerts);

		/**********************************************************************
		Function:		CreateCircle
		Purpose:		Generate a circle of vertices around a given point
						with a given radius.
		Parameters:		vec4 position - center position of the circle
						float radius - radius of the circle
						int numberOfVertices - the # of vertices to generate
		**********************************************************************/
		static std::vector<vec4> CreateCircle(vec4 position, float radius, int numberOfVertices);

		/**********************************************************************
		Function:		CreateCircle
		Purpose:		Generate the vertices for a cube.
		Parameters:		float size - the height/width/depth of the cube
		**********************************************************************/
		static std::vector<vec4> CreateCube(float size);

		/**********************************************************************
		Function:		ChopZ
		Purpose:		Return a copy of the input vector with the Z component
						set to zero.
		Parameters:		vec4 v - input vector
		**********************************************************************/
		static vec4 ChopZ(vec4 v);

		/**********************************************************************
		Function:		NormalizeWorldCoordinates
		Purpose:		Convert a point in world coordinates to OpenGL
						coordinates between -1 and 1.
		Parameters:		vec4 position - input point
		**********************************************************************/
		static vec4 NormalizeWorldCoordinates(vec4 position);

		/**********************************************************************
		Function:		NormalizeWorldVector
		Purpose:		Convert a vector in world space to its equivalent
						in OpenGL space.
		Parameters:		vec4 vec - input vector
		**********************************************************************/
		static vec4 NormalizeWorldVector(vec4 vec);

		/**********************************************************************
		Function:		WorldScale
		Purpose:		Returns a scale matrix that scales down from world
						space to OpenGl space.
		**********************************************************************/
		static mat4 WorldScale();

		/**********************************************************************
		Function:		Distance
		Purpose:		Compute the distance between two given points.
		Parameters:		vec4 p1 - point 1
						vec4 p2 - point 2
		**********************************************************************/
		static float Distance(vec4 p1, vec4 p2);

		/**********************************************************************
		Function:		DistanceSquared
		Purpose:		Compute the distance between two given points squared.
		Parameters:		vec4 p1 - point 1
						vec4 p2 - point 2
		**********************************************************************/
		static float DistanceSquared(vec4 p1, vec4 p2);

		/**********************************************************************
		Function:		Identity
		Purpose:		Returns a 4x4 identity matrix.
		**********************************************************************/
		static mat4 Identity();

		/**********************************************************************
		Function:		TimeToString
		Purpose:		Converts a time value in milliseconds to a formatted
						string.
		Parameters:		int time - time value in milliseconds
		**********************************************************************/
		static std::string TimeToString(int time);

		/**********************************************************************
		Function:		WrapAngle
		Purpose:		Wrap an angle to the range [0, 2*PI)
		Parameters:		float theta - angle in radians
		**********************************************************************/
		static float WrapAngle(float theta);

		template<class T>
		static std::string ToString(T value)
		{
			std::stringstream sstream;
			sstream << value;
			return sstream.str();
		}

		template<class T>
		static std::string ToStringWithLeadingZeroes(T value, int numOfZeroes)
		{
			std::stringstream sstream;
			sstream << std::setfill('0') << std::setw(numOfZeroes) << value;
			return sstream.str();
		}

		template <typename T>
		static T Clamp(const T& n, const T& lower, const T& upper)
		{
			return std::max(lower, std::min(n, upper));
		}
	};
}

#endif
