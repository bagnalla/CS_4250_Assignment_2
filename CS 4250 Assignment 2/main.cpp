#define _CRT_SECURE_NO_DEPRECATE
#define GLUT_DISABLE_ATEXIT_HACK

#include "Angel.h"
#include "Game.h"
#include "Util.h"
#include "FpsTracker.h"
#include "Circle.h"
#include "Bomber.h"
#include "Person.h"
#include "Blob.h"
#include "FoodCrate.h"
#include "Tree.h"
#include <vector>
#include <time.h>
#include <string>
#include <iostream>

using namespace Bagnall;

GLuint buffer;
GLuint vao;

Bomber *bomber;
Blob  *ground;

void startRound1();
void startRound2();
void startRound3();
void endGame();

void init(void)
{
	srand(time(NULL));

	Game::DebugMode = false;
	Line::Init();
	Circle::Init();
	Bomber::Init();
	Person::Init();
	FoodCrate::Init();

	for (int i = 0; i < 5; i++)
	{
		Tree *tree = new Tree();
		tree->SetScale(25);
		tree->RandomizePosition();
		tree->SetColor(vec4(0, 75.0/255.0, 0, 1.0));
	}

	bomber = new Bomber(0.2);
	bomber->SetScaleX(15);
	bomber->SetScaleY(100);
	bomber->SetColor(vec4(0.25, 0.25, 0.25, 1.0));

	std::vector<vec4> groundVertices;
	groundVertices.push_back(vec4(-0.25, 0.23, 50, 1));
	groundVertices.push_back(vec4(-0.20, 0.25, 50, 1));
	groundVertices.push_back(vec4(-0.15, 0.26, 50, 1));
	groundVertices.push_back(vec4(-0.10, 0.25, 50, 1));
	groundVertices.push_back(vec4(-0.05, 0.26, 50, 1));
	groundVertices.push_back(vec4(0.0, 0.25, 50, 1));
	groundVertices.push_back(vec4(0.05, 0.26, 50, 1));
	groundVertices.push_back(vec4(0.10, 0.25, 50, 1));
	groundVertices.push_back(vec4(0.15, 0.26, 50, 1));
	groundVertices.push_back(vec4(0.20, 0.25, 50, 1));
	groundVertices.push_back(vec4(0.25, 0.23, 50, 1));
	groundVertices.push_back(vec4(0.25, 0.0, 50, 1));
	groundVertices.push_back(vec4(-0.25, 0.0, 50, 1));
	ground = new Blob(groundVertices, 1000);
	ground->SetScaleY(1300);
	ground->SetScaleX(2100);
	ground->SetPosition(vec4(500, 1000, 0.5, 1));
	ground->SetColor(vec4(244.0 / 255.0, 164.0 / 255.0, 96.0 / 255.0, 1.0));

	startRound1();

	// Create a vertex array object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec4)*Game::Vertices.size(), &Game::Vertices[0], GL_STATIC_DRAW);

	// Load shaders and use the resulting shader program
	GLuint program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);

	// Initialize attributes from the vertex shader
	Game::WindowSizeLoc = glGetUniformLocation(program, "windowSize");
	if (Game::WindowSizeLoc == -1) {
		std::cerr << "Unable to find windowSizeLoc parameter" << std::endl;
	}
	Game::ColorLoc = glGetUniformLocation(program, "color");
	if (Game::ColorLoc == -1) {
		std::cerr << "Unable to find colorLoc parameter" << std::endl;
	}
	Game::TransformLoc = glGetUniformLocation(program, "transform");
	if (Game::TransformLoc == -1) {
		std::cerr << "Unable to find transformLoc parameter" << std::endl;
	}
	Game::ProjectionLoc = glGetUniformLocation(program, "projection");
	if (Game::ProjectionLoc == -1) {
		std::cerr << "Unable to find projectionLoc parameter" << std::endl;
	}
	GLuint vPositionLoc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPositionLoc);
	glVertexAttribPointer(vPositionLoc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnable(GL_DEPTH_TEST);

	// enable color transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//glClearColor(1.0, 1.0, 1.0, 1.0); // white background
	//glClearColor(0, 0, 0, 1.0);
	glClearColor(100.0/255.0, 149.0/255.0, 237.0/255.0, 1.0);

	glutSetCursor(GLUT_CURSOR_CROSSHAIR);

	glLineWidth(1.5);

	glUniformMatrix4fv(Game::ProjectionLoc, 1, GL_TRUE, Game::Projection);
}

//----------------------------------------------------------------------------

// glutDisplayFunc
extern "C" void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the window

	if (ground != NULL)
		ground->Draw();

	if (bomber != NULL)
		bomber->Draw();
	
	for (std::vector<Person*>::iterator it = Person::People.begin(); it != Person::People.end(); it++)
		(*it)->Draw();

	for (std::vector<FoodCrate*>::iterator it = FoodCrate::FoodCrates.begin(); it != FoodCrate::FoodCrates.end(); it++)
		(*it)->Draw();

	for (std::vector<Tree*>::iterator it = Tree::Trees.begin(); it != Tree::Trees.end(); it++)
		(*it)->Draw();

	glutSwapBuffers();
	glFlush();
}

// Maintains the mapping from screen to world coordinates.
// TAKEN FROM CODE-EGS CHELBERG CS4250 OHIO UNIVERSITY
// glutReshapeFunc
extern "C" void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	Game::WindowSize = vec2(w, h);
	glUniform2f(Game::WindowSizeLoc, w, h);       // Pass the window size
	// size
	glutPostRedisplay();
}

// glutIdleFunc
extern "C" void idle(void)
{
	// update FpsTracker before everything else
	FpsTracker::Update();

	Game::Time += Game::GameSpeedFactor();

	if (Game::CurrentRound >= 0
		&& Game::CurrentRoundDuration - Game::Time <= 0 || (Game::FoodRemaining <= 0 && FoodCrate::FoodCrates.size() == 0))
	{
		if (Game::CurrentRound == 1)
			startRound2();
		else if (Game::CurrentRound == 2 || Game::DebugMode)
			startRound3();
		else
			endGame();
		return;
	}

	if (bomber != NULL)
		bomber->Update();

	for (std::vector<Person*>::iterator it = Person::People.begin(); it != Person::People.end(); it++)
		(*it)->Update();
	
	for (std::vector<FoodCrate*>::iterator it = FoodCrate::FoodCrates.begin(); it != FoodCrate::FoodCrates.end(); it++)
		(*it)->Update();

	if (Game::CurrentRound >= 0)
	{
		Game::StatusMessage = "Time remaining: " + Util::TimeToString(Game::CurrentRoundDuration - Game::Time)
			+ ". Round " + Util::ToString(Game::CurrentRound)
			+ ". Food: " + Util::ToString(Game::FoodRemaining)
			+ ". Score: " + Util::ToString(Game::CurrentRoundScore)
			+ ". Game speed: " + Util::ToString(Game::GameSpeed);
	}
	else
	{
		Game::StatusMessage = "Final score: " + Util::ToString(Game::TotalScore);
	}

	glutSetWindowTitle(Game::StatusMessage.c_str());

	glutPostRedisplay();
}

// glutMouseFunc
extern "C" void mouseClick(int button, int state, int x, int y)
{
	//mouseMotion(x, y);
	if (state != GLUT_DOWN)
		return;

	if (button == GLUT_LEFT_BUTTON)
	{
		vec4 normal = vec4(x / (float)Game::WindowSize.x, y / (float)Game::WindowSize.y, 0, 1);

		vec4 world = vec4(normal.x * Game::WORLD_SIZE.x, normal.y * Game::WORLD_SIZE.y, 0.0, 1.0);

		//vec4 camera = Game::Projection * world;

		for (std::vector<Person*>::iterator it = Person::People.begin(); it != Person::People.end(); it++)
		{
			//if ((*it)->Contains(vec4(world_x, world_y, 0, 1)))
			if ((*it)->IsWithinRange(vec4(world.x, world.y, 0, 1), (*it)->GetScaleY()))
			{
				bomber->SetTarget(*it);
				return;
			}
		}
	}
	else
	{
		bomber->UnTarget();
	}
}

// glutKeyboardFunc
extern "C" void keyPress(unsigned char k, int x, int y)
{
	switch (k)
	{
	case '-': case '_':
		Game::GameSpeed = std::max(0.0, Game::GameSpeed - 0.1);
		break;
	case '=': case '+':
		Game::GameSpeed = Game::GameSpeed + 0.1;
		break;
	case '/':
		Game::DebugMode = !Game::DebugMode;
		break;
	case 'q':
		Game::Projection = Angel::RotateX(-0.01 * M_PI / DegreesToRadians) * Game::Projection;
		glUniformMatrix4fv(Game::ProjectionLoc, 1, GL_TRUE, Game::Projection);
		break;
	case 'w':
		Game::Projection = Angel::RotateX(0.01 * M_PI / DegreesToRadians) * Game::Projection;
		glUniformMatrix4fv(Game::ProjectionLoc, 1, GL_TRUE, Game::Projection);
		break;
	case 'a':
		Game::Projection = Angel::RotateY(-0.01 * M_PI / DegreesToRadians) * Game::Projection;
		glUniformMatrix4fv(Game::ProjectionLoc, 1, GL_TRUE, Game::Projection);
		break;
	case 's':
		Game::Projection = Angel::RotateY(0.01 * M_PI / DegreesToRadians) * Game::Projection;
		glUniformMatrix4fv(Game::ProjectionLoc, 1, GL_TRUE, Game::Projection);
		break;
	case 'z':
		Game::Projection = Angel::RotateZ(-0.01 * M_PI / DegreesToRadians) * Game::Projection;
		glUniformMatrix4fv(Game::ProjectionLoc, 1, GL_TRUE, Game::Projection);
		break;
	case 'x':
		Game::Projection = Angel::RotateZ(0.01 * M_PI / DegreesToRadians) * Game::Projection;
		glUniformMatrix4fv(Game::ProjectionLoc, 1, GL_TRUE, Game::Projection);
		break;
	case ',':
		Game::Projection = Angel::Scale(vec3(0.9, 0.9, 0.9)) * Game::Projection;
		glUniformMatrix4fv(Game::ProjectionLoc, 1, GL_TRUE, Game::Projection);
		break;
	case '.':
		Game::Projection = Angel::Scale(vec3(1.1, 1.1, 1.1)) * Game::Projection;
		glUniformMatrix4fv(Game::ProjectionLoc, 1, GL_TRUE, Game::Projection);
		break;
	case 'r':
		Game::Projection = Util::Identity();
		glUniformMatrix4fv(Game::ProjectionLoc, 1, GL_TRUE, Game::Projection);
		break;
	// EXIT
	case 033:
		exit(EXIT_SUCCESS);
		break;
	}
}

extern "C" void specialKeyPress(int k, int x, int y)
{
	switch (k)
	{
	case GLUT_KEY_LEFT:
		Game::Projection = Angel::Translate(vec4(0.1, 0.0, 0.0, 0.0)) * Game::Projection;
		glUniformMatrix4fv(Game::ProjectionLoc, 1, GL_TRUE, Game::Projection);
		break;
	case GLUT_KEY_RIGHT:
		Game::Projection = Angel::Translate(vec4(-0.1, 0.0, 0.0, 0.0)) * Game::Projection;
		glUniformMatrix4fv(Game::ProjectionLoc, 1, GL_TRUE, Game::Projection);
		break;
	case GLUT_KEY_UP:
		Game::Projection = Angel::Translate(vec4(0.0, -0.1, 0.0, 0.0)) * Game::Projection;
		glUniformMatrix4fv(Game::ProjectionLoc, 1, GL_TRUE, Game::Projection);
		break;
	case GLUT_KEY_DOWN:
		Game::Projection = Angel::Translate(vec4(0.0, 0.1, 0.0, 0.0)) * Game::Projection;
		glUniformMatrix4fv(Game::ProjectionLoc, 1, GL_TRUE, Game::Projection);
		break;
	}
}

void startRound1()
{
	Game::Time = 0;
	Game::CurrentRound = 1;
	Game::CurrentRoundDuration = Game::TIME_PER_ROUND;
	Game::FoodRemaining = 10;
	Game::TotalScore += Game::CurrentRoundScore;
	Game::CurrentRoundScore = 0;

	bomber->UnTarget();
	Person::ClearPeople();
	FoodCrate::ClearFoodCrates();

	for (int i = 0; i < 10; i++)
	{
		bool good = i % 4;

		Person *person = new Person(vec4(150 + i, 750, 0, 1));
		person->SetScale(25);
		person->SetGood(good);
		person->SetVelocity(0.05);
		person->RandomizePosition();
	}
}

void startRound2()
{
	Game::Time = 0;
	Game::CurrentRound = 2;
	Game::CurrentRoundDuration = Game::TIME_PER_ROUND;
	Game::FoodRemaining = 10;
	Game::TotalScore += Game::CurrentRoundScore;
	Game::CurrentRoundScore = 0;

	bomber->UnTarget();
	Person::ClearPeople();
	FoodCrate::ClearFoodCrates();

	for (int i = 0; i < 10; i++)
	{
		bool good = i % 3;

		Person *person = new Person(vec4(150 + i, 750, 0, 1));
		person->SetScale(25);
		person->SetGood(good);
		person->SetVelocity(0.05);
		person->RandomizePosition();
	}
}

void startRound3()
{
	Game::Time = 0;
	Game::CurrentRound = 3;
	Game::CurrentRoundDuration = Game::TIME_PER_ROUND;
	Game::FoodRemaining = 10;
	Game::TotalScore += Game::CurrentRoundScore;
	Game::CurrentRoundScore = 0;

	bomber->UnTarget();
	Person::ClearPeople();
	FoodCrate::ClearFoodCrates();

	for (int i = 0; i < 10; i++)
	{
		bool good = i % 2;

		Person *person = new Person(vec4(150 + i, 750, 0, 1));
		person->SetScale(25);
		person->SetGood(good);
		person->SetVelocity(good ? 0.05 : 0.075);
		person->RandomizePosition();
	}
}

void endGame()
{
	Game::CurrentRound = -1;
	Game::TotalScore += Game::CurrentRoundScore;

	bomber->UnTarget();
	Person::ClearPeople();
	FoodCrate::ClearFoodCrates();
	Tree::ClearTrees();

	int crateScale = 100;
	vec4 startPos = vec4(500.0 - crateScale*2.5, 500.0 - crateScale*2.0, 0.0, 1);
	for (int i = 0; i < Game::TotalScore; i++)
	{
		FoodCrate *foodCrate = new FoodCrate(0, vec4(1.0, 1.0, 1.0, 1.0), vec3(0.1, 0.1, 0.1));
		foodCrate->SetPosition(startPos + vec4((i % 6) * crateScale, (i / 6) * crateScale, 0.0, 1));
		foodCrate->SetScale(crateScale*0.85);
		foodCrate->SetColor(vec4(139.0 / 255.0, 90.0 / 255.0, 0.0, 1.0));
	}

	bomber = NULL;
	ground = NULL;
	Game::GameSpeed = 1.0;

	Game::Projection = Util::Identity();
	glUniformMatrix4fv(Game::ProjectionLoc, 1, GL_TRUE, Game::Projection);

	glutMouseFunc(NULL);

	glClearColor(0, 0, 0, 1.0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(512, 512);

	glutCreateWindow(Game::StatusMessage.c_str());
	glewInit();

	init();

	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	glutIdleFunc(idle);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(keyPress);
	glutSpecialFunc(specialKeyPress);

	glutMainLoop();
	return 0;
}
