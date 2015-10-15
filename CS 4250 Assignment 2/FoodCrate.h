/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the FoodCrate class. The static Init method
					creates the prototype vertices of a cube-shaped crate. When
					created, a FoodCrate object will move toward its destination
					and stop moving and rotating upon reaching it.

Date:				October 16, 2015

*************************************************************************************/

#ifndef FOODCRATE_H
#define FOODCRATE_H

#include "Angel.h"
#include "Object.h"
#include "Util.h"
#include <algorithm>

namespace Bagnall
{
	class FoodCrate : public Object
	{
	public:
		/**********************************************************************
		Function:		Init
		Purpose:		Create the prototype vertices and waypoints for the
						FoodCrate class.
		**********************************************************************/
		static void Init();

		static std::vector<FoodCrate*> FoodCrates; // static list of FoodCrates

		/**********************************************************************
		Function:		ClearFoodCrates
		Purpose:		Clear the static list of FoodCrates.
		**********************************************************************/
		static void ClearFoodCrates();

		/**********************************************************************
		Function:		FoodCrate constructor
		Purpose:		Create a FoodCrate object.
		**********************************************************************/
		FoodCrate();

		/**********************************************************************
		Function:		FoodCrate constructor
		Purpose:		Create a FoodCrate object.
		Parameters:		float velocity - movement velocity
						vec4 destination - destination point
						float deltaRotationX - amount to rotate X each update
						float deltaRotationY - amount to rotate Y each update
						float deltaRotationZ - amount to rotate Z each update
		**********************************************************************/
		FoodCrate(float velocity, vec4 destination, vec3 deltaTheta);

		/**********************************************************************
		Function:		FoodCrate destructor
		Purpose:		Perform necessary cleanup of the FoodCrate when it
						is destroyed. Removes the FoodCrate from the static
						list of FoodCrates.
		**********************************************************************/
		~FoodCrate();

		/**********************************************************************
		Function:		Update
		Purpose:		Update the FoodCrate object.
		Calls:			RotateX, RotateY, RotateZ, moveTowardDestination
		**********************************************************************/
		void Update();

		/**********************************************************************
		Function:		Draw
		Purpose:		Draw the FoodCrate object.
		Parameters:		bool select - draw id color if true
		Calls:			Object::Draw
		**********************************************************************/
		void Draw(bool select);

		/**********************************************************************
		Function:		GetFalling
		Purpose:		Getter for falling member variable.
		**********************************************************************/
		bool GetFalling();

		/**********************************************************************
		Function:		SetFalling
		Purpose:		Setter for falling member variable.
		Parameters:		bool falling - new value
		**********************************************************************/
		void SetFalling(bool falling);

	private:
		static int vertexCount; // # of prototype vertices
		static int globalVertexOffset; // position of vertices in global vertex array

		bool falling; // falling or not (resting)
		vec3 deltaTheta; // amount to rotate about each axis each update
		float velocity; // movement velocity
		vec4 destination; // destination point

		/**********************************************************************
		Function:		moveTowardDestination
		Purpose:		Move toward the destination point and stop falling
						upon reaching it.
		**********************************************************************/
		void moveTowardDestination();
	};
}

#endif
