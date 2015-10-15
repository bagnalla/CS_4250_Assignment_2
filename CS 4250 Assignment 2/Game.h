/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Game class. This is basically just a
					container for global variables of the program.

Date:				October 16, 2015

*************************************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Angel.h"

namespace Bagnall
{
	class Game
	{
	public:
		static const int TIME_PER_ROUND; // time per round in milliseconds

		static bool DebugMode; // debug mode toggle
		static float GameSpeed; // game speed multiplier
		static std::string StatusMessage; // message to display in window title bar
		static int Time; // current clock time
		static int CurrentRound; // current round number
		static int CurrentRoundDuration; // current round duration
		static int CurrentRoundScore; // current round score
		static int TotalScore; // total score
		static int FoodRemaining; // food crates remaining for current round

		static GLuint WindowSizeLoc; // location of windowSize in vshader
		static GLuint ColorLoc; // location of color in vshader
		static GLuint TransformLoc; // location of transform in vshader
		static GLuint ProjectionLoc; // location of projection in vshader

		static std::vector<vec4> Vertices; // global vertices array

		static const vec3 WORLD_SIZE; // dimensions of world space
		static const float GROUND_COORDINATE_Y; // Y coordinate of top of ground
		static vec2 WindowSize; // size of window x, y

		static mat4 Projection; // projection matrix

		/**********************************************************************
		Function:		GameSpeedFactor
		Purpose:		Returns FpsTracker::FrameTimeMs * GameSpeed. All time
						and movement related things in the game should be 
						scaled by the return value of this function.
		**********************************************************************/
		static float GameSpeedFactor();
	};
}

#endif
