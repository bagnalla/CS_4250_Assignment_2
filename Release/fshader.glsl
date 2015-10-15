/*************************************************************************************

Program:			CS 4250 Assignment 1: Drone

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Fragment shader file. Simple pass-through shader.

Date:				September 28, 2015

*************************************************************************************/

#version 150

varying vec4 fcolor; // incoming color

void main()
{
	// pass-through
	gl_FragColor = fcolor;
}
