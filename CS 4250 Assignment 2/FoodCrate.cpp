/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Implementation file for the FoodCrate class.

Date:				October 16, 2015

*************************************************************************************/

#include "FoodCrate.h"

namespace Bagnall
{
	// PUBLIC

	void FoodCrate::Init()
	{
		globalVertexOffset = Game::Vertices.size();
		std::vector<vec4> cube = Util::CreateCube(1.0);
		Game::Vertices.insert(Game::Vertices.end(), cube.begin(), cube.end());
		vertexCount = cube.size();
	}

	std::vector<FoodCrate*> FoodCrate::FoodCrates;

	void FoodCrate::ClearFoodCrates()
	{
		for (int i = 0; i < FoodCrates.size();)
			delete FoodCrates[i];
	}

	FoodCrate::FoodCrate()
	{
		FoodCrate(0.0, vec4(), vec3());
	}

	FoodCrate::FoodCrate(float vel, vec4 dest, vec3 dTheta) : Object()
	{
		velocity = vel;
		destination = dest;
		deltaTheta = dTheta;
		falling = true;

		FoodCrates.push_back(this);
	}

	FoodCrate::~FoodCrate()
	{
		FoodCrates.erase(std::find(FoodCrates.begin(), FoodCrates.end(), this));
	}

	void FoodCrate::Update()
	{
		if (falling)
		{
			RotateX(deltaTheta.x * Game::GameSpeedFactor());
			RotateY(deltaTheta.y * Game::GameSpeedFactor());
			RotateZ(deltaTheta.z * Game::GameSpeedFactor());
			moveTowardDestination();
		}
	}

	void FoodCrate::Draw(bool select)
	{
		Object::Draw(select);
		glDrawArrays(GL_TRIANGLES, globalVertexOffset, vertexCount);
		glUniform4fv(Game::ColorLoc, 1, vec4(139.0/255.0, 136.0/255.0, 120.0/255.0, 1.0));
		glDrawArrays(GL_LINE_STRIP, globalVertexOffset, vertexCount);
	}

	bool FoodCrate::GetFalling()
	{
		return falling;
	}
	void FoodCrate::SetFalling(bool f)
	{
		this->falling = f;
	}

	// PRIVATE

	int FoodCrate::vertexCount;
	int FoodCrate::globalVertexOffset;

	void FoodCrate::moveTowardDestination()
		{
			float real_velocity = velocity * Game::GameSpeedFactor();

			vec4 displacement = destination - position;
			if (length(displacement) <= real_velocity)
			{
				SetPosition(destination);
				falling = false;
				return;
			}

			displacement = destination - position;
			vec4 direction = normalize(displacement);
			vec4 translation = direction * real_velocity;
			Translate(translation);
		}
}
