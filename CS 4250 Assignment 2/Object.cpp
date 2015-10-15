/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Implementation file for the Object class.

Date:				October 16, 2015

*************************************************************************************/

#include "Object.h"
#include "Util.h"

namespace Bagnall
{

	// PUBLIC

	Object::Object()
	{
		position = vec4();
		color = vec4(0.0, 0.0, 0.0, 1.0);
		theta = vec3();
		scale = vec3(1.0, 1.0, 1.0);
		computeModelView();
	}

	Object::~Object() {}

	void Object::Draw()
	{
		glUniformMatrix4fv(Game::TransformLoc, 1, GL_TRUE, modelView);
		glUniform4fv(Game::ColorLoc, 1, color);
	};

	vec4 Object::GetColor()
	{
		return color;
	}
	void Object::SetColor(vec4 c)
	{
		this->color = c;
	}

	vec4 Object::GetPosition()
	{
		return position;
	}
	void Object::SetPosition(vec4 p)
	{
		vec4 translation = p - position;
		Translate(translation);
	}
	void Object::Translate(vec4 translation)
	{
		modelView = Angel::Translate(Util::NormalizeWorldVector(translation)) * modelView;
		position += translation;
	}

	float Object::GetRotationX()
	{
		return theta.x;
	}
	void Object::SetRotationX(float rotX)
	{
		float x = rotX - theta.x;
		RotateX(x);
	}
	void Object::RotateX(float x)
	{
		modelView = Angel::Translate(Util::NormalizeWorldCoordinates(position))
			* Angel::RotateZ(theta.z) * Angel::RotateY(theta.y) * Angel::RotateX(theta.x + x)
			* Angel::RotateX(-theta.x) * Angel::RotateY(-theta.y) * Angel::RotateZ(-theta.z)
			* Angel::Translate(-Util::NormalizeWorldCoordinates(position))
			* modelView;
		theta.x += x;
		theta.x = Util::WrapAngle(theta.x);
	}

	float Object::GetRotationY()
	{
		return theta.y;
	}
	void Object::SetRotationY(float rotY)
	{
		float y = rotY - theta.y;
		RotateY(y);
	}
	void Object::RotateY(float y)
	{
		modelView = Angel::Translate(Util::NormalizeWorldCoordinates(position))
			* Angel::RotateZ(theta.z) * Angel::RotateY(theta.y + y)
			* Angel::RotateY(-theta.y) * Angel::RotateZ(-theta.z)
			* Angel::Translate(-Util::NormalizeWorldCoordinates(position))
			* modelView;
		theta.y += y;
	}

	float Object::GetRotationZ()
	{
		return theta.z;
	}
	void Object::SetRotationZ(float rotZ)
	{
		float z = rotZ - theta.z;
		RotateZ(z);
	}
	void Object::RotateZ(float z)
	{
		modelView = Angel::Translate(Util::NormalizeWorldCoordinates(position))
			* Angel::RotateZ(theta.z + z)
			* Angel::RotateZ(-theta.z)
			* Angel::Translate(-Util::NormalizeWorldCoordinates(position))
			* modelView;
		theta.z += z;
	}

	float Object::GetScaleX()
	{
		return scale.x;
	}
	void Object::SetScaleX(float x)
	{
		scale.x = x;
		computeModelView();
	}
	void Object::ScaleX(float scaleFactorX)
	{
		SetScaleX(scale.x * scaleFactorX);
	}

	float Object::GetScaleY()
	{
		return scale.y;
	}
	void Object::SetScaleY(float y)
	{
		scale.y = y;
		computeModelView();
	}
	void Object::ScaleY(float scaleFactorY)
	{
		SetScaleY(scale.y * scaleFactorY);
	}

	float Object::GetScaleZ()
	{
		return scale.z;
	}
	void Object::SetScaleZ(float z)
	{
		scale.z = z;
		computeModelView();
	}
	void Object::ScaleZ(float scaleFactorZ)
	{
		SetScaleZ(scale.z * scaleFactorZ);
	}

	void Object::SetScale(float s)
	{
		scale.x = scale.y = scale.z = s;
		computeModelView();
	}
	void Object::SetScale(float x, float y)
	{
		scale.x = x;
		scale.y = y;
		computeModelView();
	}
	void Object::Scale(float scaleFactor)
	{
		scale.x *= scaleFactor;
		scale.y *= scaleFactor;
		computeModelView();
	}

	mat4 Object::GetTransform()
	{
		return modelView;
	}

	// PROTECTED

	void Object::computeModelView()
	{
		modelView = 
			Angel::Translate(Util::NormalizeWorldCoordinates(position))
			* Angel::RotateZ(theta.z) * Angel::RotateY(theta.y) * Angel::RotateX(theta.x)
			* Angel::Scale(scale.x / (Game::WORLD_SIZE.x / 2.0), scale.y / (Game::WORLD_SIZE.y / 2.0), scale.z / (Game::WORLD_SIZE.z / 2.0));
	}
}
