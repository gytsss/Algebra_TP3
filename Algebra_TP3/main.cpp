#include <iostream>
#include "raylib.h"

using namespace std;

void input();
void drawBox();
void drawPause();

//Model model = LoadModel("../res/FinalBaseMesh.obj");

//Texture2D tex = LoadTexture("../res/casita.png");

Camera3D camera;

struct Face
{
	Vector3 startPosition;
	Vector3 endPosition;
	float width;
	float height;
	float length;
	Color color;

};


Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };

bool pause = false;

int main()
{
	const int windowWidth = 800;
	const int windowHeight = 450;

	InitWindow(windowWidth, windowHeight, "Algebra EJ3");

	//model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tex;

	camera.position = Vector3{ 4.0f, 2.0f, 4.0f };
	camera.target = Vector3{ 0.0f, 1.0f, 0.0f };
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
	camera.fovy = 90.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	SetCameraMode(camera, CAMERA_FIRST_PERSON);



	float distance = 20.0f; // Set the distance from camera.target to camera.position

	float verticalAngle = 45.0f; // The Y/XZ angle

	float horizontalAngle = 90.0f; // The X/Z angle, y is considered as 0

	float horizontalDistance = distance * cosf(verticalAngle * PI / 180.0f); // Horizontal distance, the magnitude

	camera.position.x = horizontalDistance * cosf(horizontalAngle * PI / 180.0f); // Calculate the position of camera.position x based on distance 

	camera.position.z = horizontalDistance * sinf(horizontalAngle * PI / 180.0f);

	camera.position.y = distance * sinf(verticalAngle * PI / 180.0f);

	//Vector3 pos = { 0.0f,0.0f,0.0f };
	///Vector3 pos2 = { 200.0f,1.0f,0.0f };
	//BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);




	while (!WindowShouldClose())
	{
		UpdateCamera(&camera);


		if (IsKeyDown(KEY_D))
		{
			horizontalAngle -= 0.10f;

			camera.position.x = horizontalDistance * cosf(horizontalAngle * PI / 180.0f);

			camera.position.z = horizontalDistance * sinf(horizontalAngle * PI / 180.0f);


		}
		else if (IsKeyDown(KEY_A))
		{
			horizontalAngle += 0.10f;

			camera.position.x = horizontalDistance * cosf(horizontalAngle * PI / 180.0f);

			camera.position.z = horizontalDistance * sinf(horizontalAngle * PI / 180.0f);


		}

		input();

		//Frustrum faces
		Face bottomFace = { Vector3{ camera.position.x + 1, camera.position.y - 1, camera.position.z  }, Vector3{ bottomFace.startPosition.x + 4, bottomFace.startPosition.y - 3, bottomFace.startPosition.z - 20   }, 4.0f, 1.0f, 32.0f, RED };
		Face bottomLFace = { Vector3{ camera.position.x - 1, camera.position.y - 1, camera.position.z  },Vector3{ bottomLFace.startPosition.x - 4, bottomLFace.startPosition.y - 3, bottomLFace.startPosition.z - 20 }, 4.0f, 1.0f, 32.0f, RED };
		Face rightFace = { Vector3{ camera.position.x + 1, camera.position.y + 1, camera.position.z  }, Vector3{ rightFace.startPosition.x + 4, rightFace.startPosition.y + 3, rightFace.startPosition.z - 20 }, 1.0f, 10.0f, 32.0f, RED };
		Face leftFace = { Vector3{ camera.position.x - 1, camera.position.y + 1, camera.position.z }, Vector3{ leftFace.startPosition.x - 4, leftFace.startPosition.y + 3, leftFace.startPosition.z - 20 }, 1.0f, 10.0f, 32.0f, RED };

		Face farFaceUp = { Vector3{ leftFace.endPosition.x, leftFace.endPosition.y, leftFace.endPosition.z }, Vector3{ rightFace.endPosition.x, rightFace.endPosition.y,rightFace.endPosition.z }, 1.0f, 10.0f, 32.0f, RED };
		Face farFaceDown = { Vector3{ bottomLFace.endPosition.x, bottomLFace.endPosition.y, bottomLFace.endPosition.z }, Vector3{ bottomFace.endPosition.x, bottomFace.endPosition.y,bottomFace.endPosition.z }, 1.0f, 10.0f, 32.0f, RED };
		Face farFaceRight = { Vector3{ rightFace.endPosition.x, rightFace.endPosition.y, rightFace.endPosition.z }, Vector3{ bottomFace.endPosition.x, bottomFace.endPosition.y,bottomFace.endPosition.z }, 1.0f, 10.0f, 32.0f, RED };
		Face farFaceLeft = { Vector3{ leftFace.endPosition.x, leftFace.endPosition.y, leftFace.endPosition.z }, Vector3{ bottomLFace.endPosition.x, bottomLFace.endPosition.y,bottomLFace.endPosition.z }, 1.0f, 10.0f, 32.0f, RED };

		Face nearFaceUp = { Vector3{ leftFace.startPosition.x, leftFace.startPosition.y, leftFace.startPosition.z }, Vector3{ rightFace.startPosition.x, rightFace.startPosition.y,rightFace.startPosition.z }, 1.0f, 10.0f, 32.0f, RED };
		Face nearFaceDown = { Vector3{ bottomLFace.startPosition.x, bottomLFace.startPosition.y, bottomLFace.startPosition.z }, Vector3{ bottomFace.startPosition.x, bottomFace.startPosition.y,bottomFace.startPosition.z }, 1.0f, 10.0f, 32.0f, RED };
		Face nearFaceRight = { Vector3{ rightFace.startPosition.x, rightFace.startPosition.y, rightFace.startPosition.z }, Vector3{ bottomFace.startPosition.x, bottomFace.startPosition.y,bottomFace.startPosition.z }, 1.0f, 10.0f, 32.0f, RED };
		Face nearFaceLeft = { Vector3{ leftFace.startPosition.x, leftFace.startPosition.y, leftFace.startPosition.z }, Vector3{ bottomLFace.startPosition.x, bottomLFace.startPosition.y,bottomLFace.startPosition.z }, 1.0f, 10.0f, 32.0f, RED };




		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode3D(camera);

		if (cubePosition.z <= 8)
		{
			if (cubePosition.y + 8.0f < farFaceUp.endPosition.y)
			{
				if (cubePosition.x - 7.50f <= rightFace.endPosition.x && cubePosition.x + 7.50f >= leftFace.endPosition.x &&
					cubePosition.z + 5.50f >= farFaceDown.endPosition.z && cubePosition.z - 5.50f <= nearFaceDown.endPosition.z &&
					cubePosition.y <= farFaceUp.endPosition.y && cubePosition.y + 8.0f >= farFaceDown.endPosition.y)
				{
					drawBox();
				}
			}
			else
			{
				if (cubePosition.x - 4.50f <= rightFace.endPosition.x && cubePosition.x + 4.50f >= leftFace.endPosition.x &&
					cubePosition.z + 2.50f >= farFaceDown.endPosition.z && cubePosition.z - 2.50f <= nearFaceDown.endPosition.z &&
					cubePosition.y <= farFaceUp.endPosition.y && cubePosition.y + 8.0f >= farFaceDown.endPosition.y)
				{
					drawBox();
				}
			}

		}
		else
		{
			if (cubePosition.y + 8.0f < nearFaceUp.endPosition.y)
			{

				if (cubePosition.x - 7.50f <= rightFace.startPosition.x && cubePosition.x + 7.50f >= leftFace.startPosition.x &&
					cubePosition.z + 5.50f >= farFaceDown.endPosition.z && cubePosition.z - 5.50f <= nearFaceDown.endPosition.z &&
					cubePosition.y <= nearFaceUp.endPosition.y && cubePosition.y + 8.0f >= nearFaceDown.endPosition.y)
				{
					drawBox();
				}
			}
			else
			{
				if (cubePosition.x - 4.50f <= rightFace.startPosition.x && cubePosition.x + 5.50f >= leftFace.startPosition.x &&
					cubePosition.z + 2.50f >= farFaceDown.endPosition.z && cubePosition.z - 2.50f <= nearFaceDown.endPosition.z &&
					cubePosition.y <= nearFaceUp.endPosition.y && cubePosition.y + 8.0f >= nearFaceDown.endPosition.y)
				{
					drawBox();
				}
			}
		}




		DrawGrid(32, 1.0f);

		DrawLine3D(rightFace.startPosition, rightFace.endPosition, rightFace.color);
		DrawLine3D(leftFace.startPosition, leftFace.endPosition, leftFace.color);
		DrawLine3D(bottomFace.startPosition, bottomFace.endPosition, bottomFace.color);
		DrawLine3D(bottomLFace.startPosition, bottomLFace.endPosition, bottomLFace.color);

		DrawLine3D(farFaceUp.startPosition, farFaceUp.endPosition, farFaceUp.color);
		DrawLine3D(farFaceDown.startPosition, farFaceDown.endPosition, farFaceDown.color);
		DrawLine3D(farFaceRight.startPosition, farFaceRight.endPosition, farFaceRight.color);
		DrawLine3D(farFaceLeft.startPosition, farFaceLeft.endPosition, farFaceLeft.color);

		DrawLine3D(nearFaceUp.startPosition, nearFaceUp.endPosition, nearFaceUp.color);
		DrawLine3D(nearFaceDown.startPosition, nearFaceDown.endPosition, nearFaceDown.color);
		DrawLine3D(nearFaceRight.startPosition, nearFaceRight.endPosition, nearFaceRight.color);
		DrawLine3D(nearFaceLeft.startPosition, nearFaceLeft.endPosition, nearFaceLeft.color);




		//DrawModel(model, pos, 1.0f, WHITE);
		//DrawBoundingBox(bounds, GREEN);

		EndMode3D();

		DrawText("'P' pause", 10, GetScreenHeight() - 20, 20, RED);

		if (pause)
		{
			drawPause();
		}
		EndDrawing();

	}

	//UnloadModel(model);
	CloseWindow();

	return 0;
}

void input()
{
	if (IsKeyPressed(KEY_RIGHT))
		cubePosition.x++;
	else if (IsKeyPressed(KEY_LEFT))
		cubePosition.x--;

	if (IsKeyPressed(KEY_UP))
		cubePosition.z--;
	else if (IsKeyPressed(KEY_DOWN))
		cubePosition.z++;

	if (IsKeyPressed(KEY_Y))
		cubePosition.y++;
	else if (IsKeyPressed(KEY_H))
		cubePosition.y--;

	if (IsKeyPressed(KEY_SPACE))
		cubePosition = { 0.0f, 1.0f, 0.0f };

	if (IsKeyPressed(KEY_R))
		camera.fovy++;
	else if (IsKeyPressed(KEY_F))
		camera.fovy--;

	if (IsKeyPressed(KEY_P))
		pause = !pause;
}

void drawBox()
{
	//DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, PURPLE);
	//DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, BLACK);
	//DrawSphere(cubePosition, 1.0f, BROWN);
	//DrawSphereWires(cubePosition, 1.0f, 5, 5, BLACK);

	DrawCylinder(cubePosition, 5.0f, 3.0f, 8.0f, 50, RED);
	DrawCylinderWires(cubePosition, 5.0f, 3.0f, 8.0f, 50, VIOLET);

}

void drawPause()
{
	DrawRectangle(GetScreenWidth() / 2 - 125, GetScreenHeight() / 2 - 125, 250, 250, WHITE);
	DrawText("Arrows to move the box", GetScreenWidth() / 2 - 120, GetScreenHeight() / 2 - 100, 20, BLACK);
	DrawText("Y/H to move vertically", GetScreenWidth() / 2 - 120, GetScreenHeight() / 2 - 50, 20, BLACK);
	DrawText("WASD to move the cam", GetScreenWidth() / 2 - 120, GetScreenHeight() / 2, 20, BLACK);
	DrawText("R/F to change FOV", GetScreenWidth() / 2 - 120, GetScreenHeight() / 2 + 50, 20, BLACK);
}