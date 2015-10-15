/*************************************************************************************

Program:			CS 4250 Assignment 1: Drone

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Implementation file for the Game class.

Date:				September 28, 2015

*************************************************************************************/

#include "Game.h"
#include "Angel.h"
#include "FpsTracker.h"
#include "Util.h"

namespace Bagnall
{
	const int Game::TIME_PER_ROUND = 60000;

	bool Game::DebugMode;
	bool Game::PixelBufferSelectMode;
	float Game::GameSpeed = 1.0;
	std::string Game::StatusMessage = "Bomber";
	int Game::Time;
	int Game::CurrentRound;
	int Game::CurrentRoundDuration;
	int Game::CurrentRoundScore = 0;
	int Game::TotalScore = 0;
	int Game::FoodRemaining;

	GLuint Game::WindowSizeLoc;
	GLuint Game::ColorLoc;
	GLuint Game::TransformLoc;
	GLuint Game::ProjectionLoc;

	std::vector<vec4> Game::Vertices;

	const vec3 Game::WORLD_SIZE = vec3(1000.0, 1000.0, 1000.0);
	const float Game::GROUND_COORDINATE_Y = 700.0;
	vec2 Game::WindowSize;

	mat4 Game::Projection = Util::Identity();

	float Game::GameSpeedFactor()
	{
		return GameSpeed * FpsTracker::FrameTimeMs;
	}
}
