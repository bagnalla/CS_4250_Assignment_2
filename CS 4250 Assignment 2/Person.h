/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Person class. The static Init method
					creates the prototype vertices of the head, body, and gun
					of a person. There is a 'good' flag which denotes whether the
					person is a good guy or a bad guy. The gun is only drawn for
					bad guys. There is a significant amount of repeated code in this
					class from other classes (mostly Circle) so maybe it could be
					refactored to be a subclass of Circle.

Date:				October 16, 2015

*************************************************************************************/

#ifndef PERSON_H
#define PERSON_H

#include "Angel.h"
#include "Object.h"
#include "Circle.h"
#include "FoodCrate.h"
#include "Tree.h"
#include "Line.h"

namespace Bagnall
{
	class Person : public Object
	{
	public:
		/**********************************************************************
		Function:		Init
		Purpose:		Create the prototype vertices and waypoints for the
						Person class.
		**********************************************************************/
		static void Init();

		static std::vector<Person*> People; // static list of Person objects

		/**********************************************************************
		Function:		ClearPeople
		Purpose:		Clear the static list of Person objects.
		**********************************************************************/
		static void ClearPeople();

		/**********************************************************************
		Function:		Person constructor
		Purpose:		Create a Person object.
		**********************************************************************/
		Person();

		/**********************************************************************
		Function:		Person constructor
		Purpose:		Create a Person object.
		Parameters:		vec4 position - initial position of the Person
		**********************************************************************/
		Person(vec4 position);

		/**********************************************************************
		Function:		Person destructor
		Purpose:		Perform necessary cleanup of the Person when it
						is destroyed. Removes the Person from the static
						list of Person objects.
		**********************************************************************/
		~Person();

		/**********************************************************************
		Function:		Update
		Purpose:		Update the Person object.
		Calls:			lookForNearestFoodCrate, moveTowardCurrentDestination,
						checkForPersonCollision, checkForTreeCollision
		**********************************************************************/
		void Update();

		/**********************************************************************
		Function:		Draw
		Purpose:		Draw the Person object.
		Calls:			Object::Draw
		**********************************************************************/
		void Draw();

		/**********************************************************************
		Function:		Contains
		Purpose:		Determines whether the Person contains a given point.
		Parameters:		vec4 point - the given point
		**********************************************************************/
		bool Contains(vec4 point);

		/**********************************************************************
		Function:		IsWithinRange
		Purpose:		Determines whether a given point is within a given
						range of the Person's center.
		Parameters:		vec4 point - the given point
						float range - the radius around the center to check
		**********************************************************************/
		bool IsWithinRange(vec4 point, float range);

		/**********************************************************************
		Function:		Intersects
		Purpose:		Determines whether the Person intersects another Person.
		Parameters:		Person *p - the other Person
		**********************************************************************/
		bool Intersects(Person *p);

		/**********************************************************************
		Function:		Intersects
		Purpose:		Determines whether the Person intersects a Circle.
		Parameters:		Circle *c - the Circle
		**********************************************************************/
		bool Intersects(Circle *c);

		/**********************************************************************
		Function:		SetGood
		Purpose:		Setter for good member variable.
		Parameters:		bool good - new value
		**********************************************************************/
		void SetGood(bool good);

		/**********************************************************************
		Function:		GetVelocity
		Purpose:		Getter for velocity member variable.
		**********************************************************************/
		float GetVelocity();

		/**********************************************************************
		Function:		SetVelocity
		Purpose:		Setter for velocity member variable.
		Parameters:		float velocity - new velocity value
		**********************************************************************/
		void SetVelocity(float velocity);

		/**********************************************************************
		Function:		GetIsTarget
		Purpose:		Getter for isTarget member variable.
		**********************************************************************/
		bool GetIsTarget();

		/**********************************************************************
		Function:		SetIsTarget
		Purpose:		Setter for isTarget member variable.
		Parameters:		bool isTarget - new velocity isTarget
		**********************************************************************/
		void SetIsTarget(bool isTarget);

		/**********************************************************************
		Function:		SetScaleY
		Purpose:		Setter for scaleY member variable.
		Parameters:		float scaleY - new scaleY value
		**********************************************************************/
		void SetScaleY(float scaleY);

		/**********************************************************************
		Function:		SetScale
		Purpose:		Setter for scaleX, scaleY, and scaleZ member variables.
		Parameters:		float scale - new scale value
		**********************************************************************/
		void SetScale(float scale);

		/**********************************************************************
		Function:		SetScale
		Purpose:		Setter for scaleX and scaleY member variables.
		Parameters:		float scaleX - new scaleX value
						float scaleY - new scaleY value
		**********************************************************************/
		void SetScale(float scaleX, float scaleY);

		/**********************************************************************
		Function:		RandomizePosition
		Purpose:		Assign a random value to the position member variable.
						It is guaranteed to be within the ground area.
		**********************************************************************/
		void RandomizePosition();

	private:
		bool isTarget; // is person being targetted by a bomber
		bool good; // good or bad guy
		float velocity; // movement velocity
		float collisionRadius, // radius of collision circle
			collisionRadiusSquared; // radius of collision circle squared
		vec4 currentDestination; // current move destination
		FoodCrate *targetFoodCrate; // current target food crate

		static const int VERTEX_COUNT_HEAD, // # of vertices of head prototype
			VERTEX_COUNT_BODY, // # of vertices of body prototype
			VERTEX_COUNT_SELECTION_SQUARE, // # of vertices of selection square prototype
			VERTEX_COUNT_GUN; // # of vertices of gun prototype

		static int globalVertexOffsetHead, // position of head vertices in global vertex array
			globalVertexOffsetBody, // position of body vertices in global vertex array
			globalVertexOffsetSelectionSquare, // position of selection square vertices in global vertex array
			globalVertexOffsetGun; // position of gun vertices in global vertex array

		/**********************************************************************
		Function:		createPrototypeVertices
		Purpose:		Create the prototype vertices for the Person. All
						Person objects use instance transformations on these
						vertices.
		**********************************************************************/
		static void createPrototypeVertices();

		/**********************************************************************
		Function:		setCollisionRadius
		Purpose:		Private setter for collisionRadius member variable.
						Using this ensures that the collisionRadiusSquared
						member variable is always correct.
		**********************************************************************/
		void setCollisionRadius(float collisionRadius);

		/**********************************************************************
		Function:		moveTowardCurrentDestination
		Purpose:		Move the person toward their current destination.
		**********************************************************************/
		void moveTowardCurrentDestination();

		/**********************************************************************
		Function:		RandomizeDestination
		Purpose:		Choose a random destination point. It is guaranteed to
						be within the ground area and not inside of a tree.
		**********************************************************************/
		void RandomizeDestination();

		/**********************************************************************
		Function:		lookForNearestFoodCrate
		Purpose:		Scans the world for a food crate that is not falling
						and is nearest to the person. The nearest food crate
						will always become the target even if there is already
						a target food crate. This method will also detect when
						the current target food crate has been taken by another
						person and set a new random destination.
		**********************************************************************/
		void lookForNearestFoodCrate();

		/**********************************************************************
		Function:		acquireTargetFoodCrate
		Purpose:		This is called when the person reaches their target
						food crate. The food crate is destroyed and the
						player's score is incremented.
		**********************************************************************/
		void acquireTargetFoodCrate();

		/**********************************************************************
		Function:		checkForPersonCollision
		Purpose:		Scans all other Person objects to detect collisions.
						This is the simplest, most naive approach to collision
						detection. It does a linear pass through the static
						list of Person objects and is called once per Person
						so it exhibits quadratic time complexity overall.
		Calls:			Intersects(Person*), personCollision
		**********************************************************************/
		void checkForPersonCollision();

		/**********************************************************************
		Function:		personCollision
		Purpose:		This is called when a collision is detected in order to
						resolve the collision. If this person is good, it will
						adjust itself backward. If this person is bad, it will
						adjust the other person. This results in the bad guys
						being "stronger" and pushing the good guys out of the
						way.
		Parameters:		Person *person - the person we collided with
		Calls:			SetPosition
		**********************************************************************/
		void personCollision(Person *person);

		/**********************************************************************
		Function:		checkForTreeCollision
		Purpose:		Scans all Tree objects to detect collisions. This is
						also a naive implementation with O(n * r) time
						complexity where n is the # of Person objects and r is
						the # of Tree objects.
		Calls:			Intersects(Circle*), treeCollision
		**********************************************************************/
		void checkForTreeCollision();

		/**********************************************************************
		Function:		personCollision
		Purpose:		This is called when a tree collision is detected in
						order to resolve the collision.
		Parameters:		Tree *tree - the person we collided with
		Calls:			SetPosition
		**********************************************************************/
		void treeCollision(Tree *tree);
	};
}

#endif
