/*************************************************************************************

Program:			CS 4250 Assignment 2: UN Syrian Food Drop

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Implementation file for the Bomber class.

Date:				October 16, 2015

*************************************************************************************/

#include "Bomber.h"

namespace Bagnall
{
	// PUBLIC

	void Bomber::Init()
	{
		createPrototypeVertices();
		createWaypoints();
	}

	Bomber::Bomber()
	{
		Bomber(0.0);
	}
	Bomber::Bomber(float vel) : Object()
	{
		velocity = vel;
		SetPosition(waypoints[0]);
		currentWaypoint = waypoints[0];
		currentWaypointIndex = 0;
		currentTarget = NULL;
	}

	void Bomber::Update() 
	{
		move(velocity * Game::GameSpeedFactor());
		rotate();

		checkIfAboveTarget();
	}

	void Bomber::Draw()
	{
		Object::Draw();
		glDrawArrays(GL_TRIANGLE_FAN, globalVertexOffsetBody, vertexCountBody);
		glDrawArrays(GL_TRIANGLE_FAN, globalVertexOffsetWing1, vertexCountWing);
		glDrawArrays(GL_TRIANGLE_FAN, globalVertexOffsetWing2, vertexCountWing);
		glDrawArrays(GL_TRIANGLE_FAN, globalVertexOffsetTail, vertexCountTail);
		glUniform4fv(Game::ColorLoc, 1, vec4(0.7, 0.7, 0.7, 1.0));
		glDrawArrays(GL_TRIANGLE_FAN, globalVertexOffsetEngine1, vertexCountEngine);
		glDrawArrays(GL_TRIANGLE_FAN, globalVertexOffsetEngine2, vertexCountEngine);

		if (currentTarget != NULL)
		{
			line.P1 = position + vec4(0, 0, 10, 0);
			line.P2 = currentTarget->GetPosition();
			line.Draw();
		}

		if (Game::DebugMode)
		{
			drawWayPoints();
		}
	}

	void Bomber::SetTarget(Person *p)
	{
		if (Game::FoodRemaining <= 0)
			return;

		UnTarget();

		currentTarget = p;
		p->SetIsTarget(true);
	}
	void Bomber::UnTarget()
	{
		if (currentTarget != NULL)
		{
			currentTarget->SetIsTarget(false);
			currentTarget = NULL;
		}
	}

	// PRIVATE

	int Bomber::vertexCountBody, Bomber::vertexCountWing, Bomber::vertexCountTail, Bomber::vertexCountEngine;
	int Bomber::globalVertexOffsetBody, Bomber::globalVertexOffsetWing1, Bomber::globalVertexOffsetWing2, Bomber::globalVertexOffsetTail;
	int Bomber::globalVertexOffsetEngine1, Bomber::globalVertexOffsetEngine2, Bomber::globalVertexOffsetWaypoints;
	std::vector<vec4> Bomber::waypoints;

	void Bomber::createPrototypeVertices()
	{
		// BODY
		globalVertexOffsetBody = Game::Vertices.size();

		vec4 verts[4];

		verts[0] = vec4(-1, -1, 0, 1);
		verts[1] = vec4(1, -1, 0, 1);
		verts[2] = vec4(1, 1, 0, 1);
		verts[3] = vec4(-1, 1, 0, 1);

		std::vector<vec4> blob = Util::CreateBlob(10.0, verts, 4);

		Game::Vertices.push_back(vec4(0, 0, 0, 1));
		Game::Vertices.insert(Game::Vertices.end(), blob.begin(), blob.end());

		vertexCountBody = blob.size() + 1;

		// WING 1
		globalVertexOffsetWing1 = Game::Vertices.size();

		verts[0] = vec4(0.0, -0.35, 0, 1);
		verts[1] = vec4(4.5, -0.15, 0, 1);
		verts[2] = vec4(4.5, 0.1, 0, 1);
		verts[3] = vec4(0.0, -0.05, 0, 1);

		blob = Util::CreateBlob(10.0, verts, 4);

		Game::Vertices.push_back(vec4(0, 0, 0, 1));
		Game::Vertices.insert(Game::Vertices.end(), blob.begin(), blob.end());

		// WING 2
		globalVertexOffsetWing2 = Game::Vertices.size();

		verts[0] = vec4(0.0, -0.35, 0, 1);
		verts[1] = vec4(-4.5, -0.15, 0, 1);
		verts[2] = vec4(-4.5, 0.1, 0, 1);
		verts[3] = vec4(0.0, -0.05, 0, 1);

		blob = Util::CreateBlob(10.0, verts, 4);

		Game::Vertices.push_back(vec4(0, 0, 0, 1));
		Game::Vertices.insert(Game::Vertices.end(), blob.begin(), blob.end());

		vertexCountWing = blob.size() + 1;

		// TAIL
		globalVertexOffsetTail = Game::Vertices.size();

		verts[0] = vec4(-2.0, 1.1, 0, 1);
		verts[1] = vec4(2.0, 1.1, 0, 1);
		verts[2] = vec4(2.0, 1.15, 0, 1);
		verts[3] = vec4(-2.0, 1.15, 0, 1);

		blob = Util::CreateBlob(10.0, verts, 4);

		Game::Vertices.push_back(vec4(0, 0.8, 0, 1));
		Game::Vertices.insert(Game::Vertices.end(), blob.begin(), blob.end());

		vertexCountTail = blob.size() + 1;

		// ENGINE 1
		globalVertexOffsetEngine1 = Game::Vertices.size();

		verts[0] = vec4(-2.8, -0.13, 0.1, 1);
		verts[1] = vec4(-1.8, -0.13, 0.1, 1);
		verts[2] = vec4(-1.8, 0.13, 0.1, 1);
		verts[3] = vec4(-2.8, 0.13, 0.1, 1);

		blob = Util::CreateBlob(10.0, verts, 4);

		Game::Vertices.push_back(vec4(-2.3, 0.03, 0.1, 1));
		Game::Vertices.insert(Game::Vertices.end(), blob.begin(), blob.end());

		// ENGINE 2
		globalVertexOffsetEngine2 = Game::Vertices.size();

		verts[0] = vec4(1.8, -0.13, 0.1, 1);
		verts[1] = vec4(2.8, -0.13, 0.1, 1);
		verts[2] = vec4(2.8, 0.13, 0.1, 1);
		verts[3] = vec4(1.8, 0.13, 0.1, 1);

		blob = Util::CreateBlob(10.0, verts, 4);

		Game::Vertices.push_back(vec4(2.2, 0.03, 0.1, 1));
		Game::Vertices.insert(Game::Vertices.end(), blob.begin(), blob.end());

		vertexCountEngine = blob.size() + 1;
	}

	void Bomber::createWaypoints()
	{
		globalVertexOffsetWaypoints = Game::Vertices.size();
			
		vec4 verts[4];

		verts[0] = vec4(200, 100, 0, 1);
		verts[1] = vec4(800, 100, 0, 1);
		verts[2] = vec4(800, 200, 0, 1);
		verts[3] = vec4(200, 200, 0, 1);

		std::vector<vec4> blob = Util::CreateBlob(100.0, verts, 4);

		waypoints.insert(waypoints.end(), blob.begin(), blob.end());

		Game::Vertices.insert(Game::Vertices.end(), waypoints.begin(), waypoints.end());

		for (int i = globalVertexOffsetWaypoints; i < globalVertexOffsetWaypoints + waypoints.size(); i++)
			Game::Vertices[i] = Angel::Translate(Util::NormalizeWorldCoordinates(Game::Vertices[i])) * Util::WorldScale() * vec4(0, 0, 50, 1);
	}

	void Bomber::move(float real_move_amount)
	{
		vec4 displacement = Util::ChopZ(currentWaypoint - position);
		if (length(displacement) <= real_move_amount)
		{
			SetPosition(currentWaypoint);
			currentWaypointIndex = ++currentWaypointIndex % waypoints.size();
			currentWaypoint = waypoints[currentWaypointIndex];
			// recursive call until real_move_amount is used up
			move(real_move_amount - length(displacement));
			return;
		}

		vec4 direction = normalize(displacement);
		vec4 translation = direction * real_move_amount;
		Translate(translation);
	}

	void Bomber::rotate()
	{
		vec4 displacementDirection = normalize(currentWaypoint - position);
		float thetaZ = atan2(displacementDirection.y, displacementDirection.x);
		SetRotationZ((-thetaZ + M_PI / 2) / DegreesToRadians);

		/*vec4 left = vec4(-1, 0, 0, 0);
		vec4 right = vec4(1, 0, 0, 0);
		float thetaX = (dot(displacementDirection, left) * (M_PI/3.0)) / 2 + (dot(displacementDirection, right) * M_PI) / 2;
		SetRotationY(-thetaX / DegreesToRadians);*/

		/*float thetaY = thetaZ;
		if (position.x < Game::WORLD_SIZE.x / 2.0)
			SetRotationY((thetaZ * 2 + M_PI / 6) / DegreesToRadians);
		else
			SetRotationY((thetaZ - M_PI / 6) / DegreesToRadians);*/

		vec4 down = vec4(0, -1, 0, 0);
		float dp = dot(displacementDirection, down);
		SetRotationY((-dp * (M_PI/2.0)) / DegreesToRadians);
	}

	void Bomber::checkIfAboveTarget()
	{
		if (currentTarget == NULL)
			return;

		float real_velocity = velocity * Game::GameSpeedFactor();

		if (currentTarget->GetPosition().x >= position.x - real_velocity
			&& currentTarget->GetPosition().x <= position.x + real_velocity)
			dropFoodCrate();
	}

	void Bomber::dropFoodCrate()
	{
		FoodCrate *foodCrate = new FoodCrate(0.25, currentTarget->GetPosition(), vec3(rand() / (float)RAND_MAX * 0.25, rand() / (float)RAND_MAX * 0.25, rand() / (float)RAND_MAX * 0.25));
		foodCrate->SetScale(25);
		foodCrate->SetColor(vec4(139.0 / 255.0, 90.0 / 255.0, 0.0, 1.0));
		foodCrate->SetPosition(position);

		Game::FoodRemaining--;

		UnTarget();
	}

	void Bomber::drawWayPoints()
	{
		glUniformMatrix4fv(Game::TransformLoc, 1, GL_TRUE, Util::Identity());
		glUniform4fv(Game::ColorLoc, 1, vec4(1, 1, 1, 0.25));
		glDrawArrays(GL_LINE_LOOP, globalVertexOffsetWaypoints, waypoints.size());
	}
}
