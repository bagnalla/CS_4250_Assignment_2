/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the FpsTracker class. This is a static class
					that is responsible for keeping track of the game FPS as well as
					the elapsed ms since the last update (FrameTimeMs) which is used
					to scale all movement and time related things in the game.

Date:				October 16, 2015

*************************************************************************************/

#ifndef FPSTRACKER_H
#define FPSTRACKER_H

namespace Bagnall
{
	class FpsTracker
	{
	public:
		static int FrameTimeMs; // elapsed milliseconds since previous frame

		/**********************************************************************
		Function:		Update
		Purpose:		Update the FpsTracker. Updates FrameTimeMs and keeps
						track of the FPS.
		**********************************************************************/
		static void Update();
	private:
		static int last_frame_time, // timestamp of the previous frame
			frame_counter, // frame counter for tracking fps
			frame_time_accum, // time accumulator for tracking fps
			fps; // frames per second
	};
}

#endif
