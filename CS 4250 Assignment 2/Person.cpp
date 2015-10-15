/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Implementation file for the Person class.

Date:				October 16, 2015

*************************************************************************************/

#include "Person.h"
#include <cfloat>

namespace Bagnall
{
	// PUBLIC

	void Person::Init()
	{
		createPrototypeVertices();
	}

	std::vector<Person*> Person::People;

	void Person::ClearPeople()
	{
		for (int i = 0; i < People.size();)
			delete People[i];
	}

	Person::Person() : Object()
	{
		Person(vec4());
	}
	Person::Person(vec4 pos) : Object()
	{
		isTarget = false;
		velocity = 0;
		setCollisionRadius(scale.y);
		targetFoodCrate = NULL;
		SetPosition(pos);
		RandomizeDestination();

		People.push_back(this);
	}

	Person::~Person()
	{
		People.erase(std::find(People.begin(), People.end(), this));
	}

	void Person::Update()
	{	
		lookForNearestFoodCrate();

		moveTowardCurrentDestination();

		checkForPersonCollision();

		checkForTreeCollision();
	}

	void Person::Draw()
	{
		Object::Draw();
		glDrawArrays(GL_TRIANGLE_FAN, globalVertexOffsetHead, VERTEX_COUNT_HEAD);
		glDrawArrays(GL_TRIANGLE_STRIP, globalVertexOffsetBody, VERTEX_COUNT_BODY);

		if (isTarget)
		{
			glUniform4fv(Game::ColorLoc, 1, vec4(0.75, 0, 0, 0.75));
			glDrawArrays(GL_LINE_LOOP, globalVertexOffsetSelectionSquare, VERTEX_COUNT_SELECTION_SQUARE);
		}

		if (Game::DebugMode)
		{
			Line line;
			line.P1 = position + vec4(0, 0, 10, 1);
			line.P2 = currentDestination + vec4(0, 0, 10, 1);
			line.Draw();

			Circle circle;
			circle.SetPosition(position);
			circle.SetScale(collisionRadius);
			circle.SetColor(vec4(0, 0, 0, 0.25));
			circle.Draw();
		}

		if (!good)
		{
			glUniform4fv(Game::ColorLoc, 1, vec4(0, 0, 0, 1));
			glDrawArrays(GL_TRIANGLE_FAN, globalVertexOffsetGun, VERTEX_COUNT_GUN);
		}
	}

	bool Person::Contains(vec4 point)
	{
		return (Util::DistanceSquared(point, position) <= collisionRadiusSquared);
	}
	bool Person::IsWithinRange(vec4 point, float range)
	{
		return (Util::DistanceSquared(position, point) <= range * range);
	}

	bool Person::Intersects(Person *p)
	{
		return (Util::DistanceSquared(position, p->position) <= pow(collisionRadius + p->collisionRadius, 2));
	}
	bool Person::Intersects(Circle *c)
	{
		return (Util::Distance(position, c->GetPosition()) <= collisionRadius + c->GetScaleX());
	}

	void Person::SetGood(bool g)
	{
		if (good = g)
			SetColor(vec4(0, 1, 0, 1));
		else
			SetColor(vec4(1, 0, 0, 1));
	}

	float Person::GetVelocity()
	{
		return velocity;
	}
	void Person::SetVelocity(float v)
	{
		velocity = v;
	}

	bool Person::GetIsTarget()
	{
		return isTarget;
	}
	void Person::SetIsTarget(bool t)
	{
		isTarget = t;
	}

	void Person::SetScaleY(float y)
	{
		Object::SetScaleY(y);
		setCollisionRadius(y / 2.0);
	}
	void Person::SetScale(float s)
	{
		Object::SetScale(s);
		setCollisionRadius(s / 2.0);
	}
	void Person::SetScale(float x, float y)
	{
		Object::SetScale(x, y);
		setCollisionRadius(y / 2.0);
	}

	void Person::RandomizePosition()
	{
		float wall_buffer_x = Game::WORLD_SIZE.x * 0.05;
		float wall_buffer_y = Game::WORLD_SIZE.y * 0.05;

		float dest_x = wall_buffer_x + (rand() / (float)RAND_MAX) * (Game::WORLD_SIZE.x * 0.9);
		float dest_y = Game::GROUND_COORDINATE_Y/* + wall_buffer_y*/ + (rand() / (float)RAND_MAX) * (Game::WORLD_SIZE.y - Game::GROUND_COORDINATE_Y - wall_buffer_y);

		SetPosition(vec4(dest_x, dest_y, 0, 1));
	}

	// PRIVATE

	const int Person::VERTEX_COUNT_HEAD = 25, 
		Person::VERTEX_COUNT_BODY = 3, 
		Person::VERTEX_COUNT_SELECTION_SQUARE = 5, 
		Person::VERTEX_COUNT_GUN = 6;

	int Person::globalVertexOffsetHead,
		Person::globalVertexOffsetBody,
		Person::globalVertexOffsetSelectionSquare,
		Person::globalVertexOffsetGun;

	void Person::setCollisionRadius(float cr)
	{
		collisionRadius = cr;
		collisionRadiusSquared = cr * cr;
	}

	void Person::createPrototypeVertices()
	{
		// PERSON
		globalVertexOffsetHead = Game::Vertices.size();

		std::vector<vec4> head = Util::CreateCircle(vec4(0, 0.5, 0, 1), 0.5, VERTEX_COUNT_HEAD - 1);

		Game::Vertices.push_back(vec4(0, 0.5, 0, 1));
		Game::Vertices.insert(Game::Vertices.end(), head.begin(), head.end());

		globalVertexOffsetBody = Game::Vertices.size();

		std::vector<vec4> body;
		body.push_back(vec4(0, 0.5, 0, 1));
		body.push_back(vec4(-0.25, -0.5, 0, 1));
		body.push_back(vec4(0.25, -0.5, 0, 1));

		Game::Vertices.insert(Game::Vertices.end(), body.begin(), body.end());

		// SELECTION SQUARE
		globalVertexOffsetSelectionSquare = Game::Vertices.size();
		Game::Vertices.push_back(vec4(-0.9, -1.0, 0, 1));
		Game::Vertices.push_back(vec4(0.9, -1.0, 0, 1));
		Game::Vertices.push_back(vec4(0.9, 0.8, 0, 1));
		Game::Vertices.push_back(vec4(-0.9, 0.8, 0, 1));
		Game::Vertices.push_back(vec4(-0.9, -1.0, 0, 1));

		// GUN
		globalVertexOffsetGun = Game::Vertices.size();
		Game::Vertices.push_back(vec4(0.15, -0.2, -0.1, 1));
		Game::Vertices.push_back(vec4(0, -0.1, -0.1, 1));
		Game::Vertices.push_back(vec4(0.3, -0.1, -0.1, 1));
		Game::Vertices.push_back(vec4(0.3, -0.3, -0.1, 1));
		Game::Vertices.push_back(vec4(0, -0.3, -0.1, 1));
		Game::Vertices.push_back(vec4(0, -0.1, -0.1, 1));
	}

	void Person::moveTowardCurrentDestination()
	{
		float real_velocity = velocity * Game::GameSpeedFactor();

		if (targetFoodCrate != NULL)
		{
			if (Contains(targetFoodCrate->GetPosition()) || Util::Distance(position, targetFoodCrate->GetPosition()) <= real_velocity)
			{
				acquireTargetFoodCrate();
				RandomizeDestination();
				lookForNearestFoodCrate();
			}
		}

		vec4 displacement = Util::ChopZ(currentDestination - position);
		if (Contains(currentDestination) || Util::Distance(position, currentDestination) <= real_velocity)
		{
			RandomizeDestination();
			return;
		}
		vec4 direction = normalize(displacement);
		vec4 translation = direction * real_velocity;
		Translate(translation);
	}

	void Person::RandomizeDestination()
	{
		float wall_buffer_x = Game::WORLD_SIZE.x * 0.05;
		float wall_buffer_y = Game::WORLD_SIZE.y * 0.05;

		float dest_x = wall_buffer_x + (rand() / (float)RAND_MAX) * (Game::WORLD_SIZE.x * 0.9);
		float dest_y = Game::GROUND_COORDINATE_Y/* + wall_buffer_y*/ + (rand() / (float)RAND_MAX) * (Game::WORLD_SIZE.y - Game::GROUND_COORDINATE_Y - wall_buffer_y);

		currentDestination = vec4(dest_x, dest_y, 0, 1);

		for (std::vector<Tree*>::iterator it = Tree::Trees.begin(); it != Tree::Trees.end(); it++)
		{
			if ((*it)->Contains(currentDestination))
			{
				RandomizeDestination();
				break;
			}
		}
	}

	void Person::lookForNearestFoodCrate()
	{
		int nearestIndex = -1;
		float smallestDistance = FLT_MAX;

		for (int i = 0; i < FoodCrate::FoodCrates.size(); i++)
		{
			FoodCrate *foodCrate = FoodCrate::FoodCrates[i];

			if (foodCrate->GetFalling())
				continue;

			float distance = Util::Distance(position, foodCrate->GetPosition());
			if (distance < smallestDistance)
			{
				nearestIndex = i;
				smallestDistance = distance;
			}
		}

		if (nearestIndex != -1)
		{
			targetFoodCrate = FoodCrate::FoodCrates[nearestIndex];
			currentDestination = FoodCrate::FoodCrates[nearestIndex]->GetPosition();
		}
		else if (targetFoodCrate != NULL)
		{
			targetFoodCrate = NULL;
			RandomizeDestination();
		}
	}

	void Person::acquireTargetFoodCrate()
	{
		delete targetFoodCrate;
		targetFoodCrate = NULL;

		if (good)
			Game::CurrentRoundScore++;
	}

	void Person::checkForPersonCollision()
	{
		for (std::vector<Person*>::iterator it = People.begin(); it != People.end(); it++)
		{
			if (*it != this && Intersects(*it))
				personCollision(*it);
		}
	}

	void Person::personCollision(Person *person)
	{
		float distance = collisionRadius + person->collisionRadius;

		vec4 displacement = person->position - position;

		if (!good)
		{
			person->SetPosition(position + (distance * normalize(displacement)));
		}
		else
		{
			SetPosition(person->position + (-distance * normalize(displacement)));
		}
	}

	void Person::checkForTreeCollision()
	{
		for (std::vector<Tree*>::iterator it = Tree::Trees.begin(); it != Tree::Trees.end(); it++)
		{
			if (Intersects(*it))
				treeCollision(*it);
		}
	}

	void Person::treeCollision(Tree *tree)
	{
		float distance = collisionRadius + tree->GetScaleX();
		vec4 displacement = tree->GetPosition() - position;
		SetPosition(tree->GetPosition() + (-distance * normalize(displacement)));
	}
}
