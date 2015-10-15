/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Implementation file for the Tree class.

Date:				October 16, 2015

*************************************************************************************/

#include "Tree.h"
#include <algorithm>

namespace Bagnall
{
	// PUBLIC

	std::vector<Tree*> Tree::Trees;

	void Tree::ClearTrees()
	{
		for (int i = 0; i < Trees.size();)
			delete Trees[i];
	}

	Tree::Tree() : Circle()
	{
		Trees.push_back(this);
	}

	Tree::~Tree()
	{
		Trees.erase(std::find(Trees.begin(), Trees.end(), this));
	}

	void Tree::Update() {}

	void Tree::Draw()
	{
		Circle::Draw();
	}

	void Tree::RandomizePosition()
	{
		float wall_buffer_x = Game::WORLD_SIZE.x * 0.20;
		float wall_buffer_y = Game::WORLD_SIZE.y * 0.10;

		float dest_x = wall_buffer_x/2.0 + (rand() / (float)RAND_MAX) * (Game::WORLD_SIZE.x - wall_buffer_x);
		float dest_y = Game::GROUND_COORDINATE_Y + wall_buffer_y/2.0 + (rand() / (float)RAND_MAX) * (Game::WORLD_SIZE.y - Game::GROUND_COORDINATE_Y - wall_buffer_y);

		SetPosition(vec4(dest_x, dest_y, 0, 1));

		for (std::vector<Tree*>::iterator it = Trees.begin(); it != Trees.end(); it++)
		{
			//if (*it != this && Intersects(*it))
			if (*it != this && IsWithinRange((*it)->position, scale.x*5))
			{
				RandomizePosition();
				return;
			}
		}
	}
}
