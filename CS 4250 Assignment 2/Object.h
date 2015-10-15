/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface file for the Object class. This is an abstract base
					class for objects in the game which can be translated, rotated,
					and scaled.

Date:				October 16, 2015

*************************************************************************************/

#ifndef OBJECT_H
#define OBJECT_H

#include "Angel.h"
#include "Game.h"

namespace Bagnall
{
	class Object
	{
	public:
		/**********************************************************************
		Function:		Object constructor
		Purpose:		Create an Object object.
		**********************************************************************/
		Object();

		/**********************************************************************
		Function:		Object destructor
		Purpose:		Perform necessary cleanup of the Object when it
						is destroyed.
		**********************************************************************/
		virtual ~Object();

		/**********************************************************************
		Function:		Update
		Purpose:		Virtual update method to be overridden by a subclass.
		**********************************************************************/
		virtual void Update() = 0;

		/**********************************************************************
		Function:		Draw
		Purpose:		Draw the Object object.
		Parameters:		bool select - draw id color if true
		**********************************************************************/
		virtual void Draw(bool select);

		/**********************************************************************
		Function:		GetIdColor
		Purpose:		Getter for idColor member variable.
		**********************************************************************/
		vec4 GetIdColor();

		/**********************************************************************
		Function:		SetIdColor
		Purpose:		Setter for idColor member variable.
		Parameters:		vec4 color - new idColor value
		**********************************************************************/
		void SetIdColor(vec4 color);

		/**********************************************************************
		Function:		GetColor
		Purpose:		Getter for color member variable.
		**********************************************************************/
		vec4 GetColor();

		/**********************************************************************
		Function:		SetColor
		Purpose:		Setter for color member variable.
		Parameters:		vec4 color - new color value
		**********************************************************************/
		void SetColor(vec4 color);

		/**********************************************************************
		Function:		GetPosition
		Purpose:		Getter for position member variable.
		**********************************************************************/
		vec4 GetPosition();

		/**********************************************************************
		Function:		SetPosition
		Purpose:		Setter for position member variable.
		Parameters:		vec4 position - new position value
		**********************************************************************/
		void SetPosition(vec4 position);

		/**********************************************************************
		Function:		Translate
		Purpose:		Perform translation on the object.
		Parameters:		vec4 translation - translation vector
		**********************************************************************/
		void Translate(vec4 translation);

		/**********************************************************************
		Function:		GetRotationX
		Purpose:		Getter for rotationX member variable.
		**********************************************************************/
		float GetRotationX();

		/**********************************************************************
		Function:		SetRotationX
		Purpose:		Setter for rotationX member variable.
		Parameters:		float rotationX - new rotationX value
		**********************************************************************/
		void SetRotationX(float rotationX);

		/**********************************************************************
		Function:		RotateX
		Purpose:		Perform rotation on the object about the X axis.
		Parameters:		float x - rotation amount
		**********************************************************************/
		void RotateX(float x);

		/**********************************************************************
		Function:		GetRotationY
		Purpose:		Getter for rotationY member variable.
		**********************************************************************/
		float GetRotationY();

		/**********************************************************************
		Function:		SetRotationY
		Purpose:		Setter for rotationY member variable.
		Parameters:		float rotationY - new rotationY value
		**********************************************************************/
		void SetRotationY(float rotationY);

		/**********************************************************************
		Function:		RotateY
		Purpose:		Perform rotation on the object about the Y axis.
		Parameters:		float y - rotation amount
		**********************************************************************/
		void RotateY(float y);

		/**********************************************************************
		Function:		GetRotationZ
		Purpose:		Getter for rotationZ member variable.
		**********************************************************************/
		float GetRotationZ();

		/**********************************************************************
		Function:		SetRotationZ
		Purpose:		Setter for rotationZ member variable.
		Parameters:		float rotationZ - new rotationZ value
		**********************************************************************/
		void SetRotationZ(float rotationZ);

		/**********************************************************************
		Function:		RotateZ
		Purpose:		Perform rotation on the object about the Z axis.
		Parameters:		float z - rotation amount
		**********************************************************************/
		void RotateZ(float z);

		/**********************************************************************
		Function:		GetScaleX
		Purpose:		Getter for scaleX member variable.
		**********************************************************************/
		float GetScaleX();

		/**********************************************************************
		Function:		SetScaleX
		Purpose:		Setter for scaleX member variable.
		Parameters:		float scaleX - new scaleX value
		**********************************************************************/
		virtual void SetScaleX(float scaleX);

		/**********************************************************************
		Function:		ScaleX
		Purpose:		Perform scaling on the object in the X axis.
		Parameters:		float scaleFactorX - scale amount
		**********************************************************************/
		void ScaleX(float scaleFactorX);

		/**********************************************************************
		Function:		GetScaleY
		Purpose:		Getter for scaleY member variable.
		**********************************************************************/
		float GetScaleY();

		/**********************************************************************
		Function:		SetScaleY
		Purpose:		Setter for scaleY member variable.
		Parameters:		float scaleY - new scaleY value
		**********************************************************************/
		virtual void SetScaleY(float scaleY);

		/**********************************************************************
		Function:		ScaleY
		Purpose:		Perform scaling on the object in the Y axis.
		Parameters:		float scaleFactorY - scale amount
		**********************************************************************/
		void ScaleY(float scaleFactorY);

		/**********************************************************************
		Function:		GetScaleZ
		Purpose:		Getter for scaleZ member variable.
		**********************************************************************/
		float GetScaleZ();

		/**********************************************************************
		Function:		SetScaleZ
		Purpose:		Setter for scaleZ member variable.
		Parameters:		float scaleZ - new scaleZ value
		**********************************************************************/
		virtual void SetScaleZ(float scaleZ);

		/**********************************************************************
		Function:		ScaleZ
		Purpose:		Perform scaling on the object in the Z axis.
		Parameters:		float scaleFactorZ - scale amount
		**********************************************************************/
		void ScaleZ(float scaleFactorZ);

		/**********************************************************************
		Function:		SetScale
		Purpose:		Setter for scaleX, scaleY, and scaleZ.
		Parameters:		float scale - new scale value
		**********************************************************************/
		virtual void SetScale(float scale);

		/**********************************************************************
		Function:		SetPosition
		Purpose:		Setter for position member variable.
		Parameters:		vec4 position - new position value
		**********************************************************************/
		virtual void SetScale(float scaleX, float scaleY);

		/**********************************************************************
		Function:		Scale
		Purpose:		Perform scaling on the object in the X, Y, and Z axes.
		Parameters:		float scaleFactor - scale amount
		**********************************************************************/
		void Scale(float scaleFactor);

		/**********************************************************************
		Function:		GetPosition
		Purpose:		Getter for position member variable.
		**********************************************************************/
		mat4 GetTransform();

	protected:
		static int idCounter;
		int id;
		vec4 idColor;
		vec4 color; // color of the object
		vec4 position; // position of the object in world space
		vec3 theta; // rotation about the three axes
		vec3 scale; // scale in the three axes
		mat4 modelView; // model-view matrix

		/**********************************************************************
		Function:		computeTransform
		Purpose:		Compute the model view matrix by concatenating 
						translation, rotation, and scale matrices that are 
						generated from their corresponding scalar value
						members.
		**********************************************************************/
		void computeModelView();
	};
}

#endif
