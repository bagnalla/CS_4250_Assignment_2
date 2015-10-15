/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Tree class. This class inherits from
					Circle. It is basically just a slightly special Circle so it
					is possible that it shouldn't even be its own class.

Date:				October 16, 2015

*************************************************************************************/

#ifndef TREE_H
#define TREE_H

#include "Angel.h"
#include "Game.h"
#include "Circle.h"

namespace Bagnall
{
	class Tree : public Circle
	{
	public:
		static std::vector<Tree*> Trees; // static list of Tree objects

		/**********************************************************************
		Function:		ClearTrees
		Purpose:		Clear the static list of Tree objects.
		**********************************************************************/
		static void ClearTrees();

		/**********************************************************************
		Function:		Tree constructor
		Purpose:		Create a Tree object.
		**********************************************************************/
		Tree();

		/**********************************************************************
		Function:		Tree destructor
		Purpose:		Perform necessary cleanup of the Tree when it
						is destroyed. Removes the Tree from the static
						list of Tree objects.
		**********************************************************************/
		~Tree();

		/**********************************************************************
		Function:		Update
		Purpose:		Update the Tree object. Currently does nothing.
		**********************************************************************/
		void Update();

		/**********************************************************************
		Function:		Draw
		Purpose:		Draw the Tree object.
		Calls:			Circle::Draw
		**********************************************************************/
		void Draw();

		/**********************************************************************
		Function:		RandomizePosition
		Purpose:		Assign a random value to the position member variable.
						It is guaranteed to be within the ground are and a
						comfortable distance away from any other Tree object.
		Calls:			SetPosition, RandomizePosition
		**********************************************************************/
		void RandomizePosition();
	};
}

#endif
