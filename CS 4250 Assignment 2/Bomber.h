/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Bomber class. The static Init method
					creates the prototype vertices for the body, wings, tail, and
					engines as well as the waypoints. The bomber moves through the
					waypoints in a loop. A Person object can be set as the target of
					the bomber, and the bomber will drop a FoodCrate object aimed at
					the target when their x coordinates are equal (the bomber is
					directly above the target).

Date:				October 16, 2015

*************************************************************************************/

#ifndef BOMBER_H
#define BOMBER_H

#include "Angel.h"
#include "Object.h"
#include "Game.h"
#include "Util.h"
#include "Person.h"
#include "FoodCrate.h"
#include "Line.h"

namespace Bagnall
{
	class Bomber : public Object
	{
	public:
		/**********************************************************************
		Function:		Init
		Purpose:		Create the prototype vertices and waypoints for the
						Bomber class.
		**********************************************************************/
		static void Init();

		/**********************************************************************
		Function:		Bomber constructor
		Purpose:		Create a Bomber object.
		**********************************************************************/
		Bomber();

		/**********************************************************************
		Function:		Bomber constructor
		Purpose:		Create a Bomber object.
		Parameters:		float velocity - movement rate of the bomber
		**********************************************************************/
		Bomber(float velocity);

		/**********************************************************************
		Function:		Update
		Purpose:		Update the Bomber object.
		Calls:			move, rotate, checkIfAboveTarget
		**********************************************************************/
		void Update();

		/**********************************************************************
		Function:		Draw
		Purpose:		Draw the Bomber object.
		Calls:			Object::Draw, drawWayPoints
		**********************************************************************/
		void Draw();

		/**********************************************************************
		Function:		SetTarget
		Purpose:		Set the target Person of the Bomber.
		Parameters:		Person *p - the Person object to target
		**********************************************************************/
		void SetTarget(Person *p);

		/**********************************************************************
		Function:		UnTarget
		Purpose:		Notify the current target that it is no longer targeted
						and stop targeting it.
		**********************************************************************/
		void UnTarget();

	private:
		static std::vector<vec4> waypoints; // flight path waypoints
		static int vertexCountBody, // # of vertices of body
			vertexCountWing, // # of vertices of each wing
			vertexCountTail, // # of vertices of tail
			vertexCountEngine; // # of vertices of each engsine
		static int globalVertexOffsetBody, // position of body in global vertex array
			globalVertexOffsetWing1, // position of wing 1 in global vertex array
			globalVertexOffsetWing2, // position of wing 2 in global vertex array
			globalVertexOffsetTail, // position of tail in global vertex array
			globalVertexOffsetEngine1, // position of engine 1 in global vertex array
			globalVertexOffsetEngine2, // position of engine 2 in global vertex array
			globalVertexOffsetWaypoints; // position of waypoints in global vertex array

		float velocity; // movement rate of bomber
		vec4 currentWaypoint; // waypoint currently moving toward
		int currentWaypointIndex; // index of current waypoint in waypoints array
		Person *currentTarget; // current Person target
		Line line; // used to draw line to the current target

		/**********************************************************************
		Function:		createPrototypeVertices
		Purpose:		Create the prototype vertices for the Bomber. All
						Bomber objects use instance transformations on these
						vertices.
		**********************************************************************/
		static void createPrototypeVertices();

		/**********************************************************************
		Function:		createWaypoints
		Purpose:		Create the waypoints for the Bomber. All Bomber objects
						use these waypoints.
		**********************************************************************/
		static void createWaypoints();

		/**********************************************************************
		Function:		move
		Purpose:		Perform the movement of the Bomber each update frame.
		Parameters:		float real_move_amount - amount to move
		**********************************************************************/
		void move(float real_move_amount);

		/**********************************************************************
		Function:		rotate
		Purpose:		Perform the rotation of the Bomber each update frame.
		**********************************************************************/
		void rotate();

		/**********************************************************************
		Function:		checkIfAboveTarget
		Purpose:		Performs a check to see if the Bomber is directly
						above the target Person and drops a food crate if
						it is.
		Calls:			dropFoodCrate
		**********************************************************************/
		void checkIfAboveTarget();

		/**********************************************************************
		Function:		dropFoodCrate
		Purpose:		Drop a FoodCrate at the current target. Then untargets
						the Person.
		Calls:			Untarget
		**********************************************************************/
		void dropFoodCrate();

		/**********************************************************************
		Function:		drawWayPoints
		Purpose:		Draws the waypoints. Only used in debug mode.
		**********************************************************************/
		void drawWayPoints();
	};
}

#endif
