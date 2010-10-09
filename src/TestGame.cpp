#include "TestGame.h"

#include "tilegame/Tile.h"

TestGame::TestGame() : super()
{
	
}

TestGame::~TestGame() 
{
	UnloadResources();
}

void TestGame::LoadResources()
{	
	
	//_pResManager->GenerateTextures(Vector2i(MAX_TEXTURE_WIDTH, MAX_TEXTURE_HEIGHT));
}

void TestGame::UnloadResources()
{
	
}

void TestGame::Update()
{


}



void TestGame::Draw()
{	
	glClearColor(0.0f, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);


   
	const GLfloat points[] = 
	{
       -50.0, -50.0, 0.0,        0.5, 0.5, 1.0, 0.5, // First point
	};

	glLoadIdentity();
	glTranslatef(150.0, -220.0, 0.0);

	static float rot = 0.0f;
	glRotatef(rot += 0.5f, 0.0, 0.0, 1.0);

	glEnable(GL_POINT_SMOOTH);
	glPointSize(50.0);
	glVertexPointer(3, GL_FLOAT, 28, points);
	glColorPointer(4, GL_FLOAT, 28, &points[3]);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_POINTS, 0, 1);




}
