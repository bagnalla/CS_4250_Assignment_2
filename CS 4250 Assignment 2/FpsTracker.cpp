/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Implementation file for the FpsTracker class.

Date:				October 16, 2015

*************************************************************************************/

#include "FpsTracker.h"
#include "Angel.h"
#include "Game.h"

namespace Bagnall
{
	void FpsTracker::Update()
	{
		// calculate milliseconds elapsed since last call
		int current_time = glutGet(GLUT_ELAPSED_TIME);
		FrameTimeMs = current_time - last_frame_time;
		last_frame_time = current_time;

		// increment frame counter, update fps once per second
		frame_counter++;
		frame_time_accum += FrameTimeMs;
		if (frame_time_accum >= 1000)
		{
			fps = frame_counter;
			frame_counter = frame_time_accum = 0;
			std::cout << fps << std::endl;
			//std::cout << Game::WindowSize.x << " " << Game::WindowSize.y << std::endl;
		}
	}

	int FpsTracker::FrameTimeMs;

	int FpsTracker::last_frame_time = 0;
	int FpsTracker::frame_counter = 0;
	int FpsTracker::frame_time_accum = 0;
	int FpsTracker::fps = 0;
}
