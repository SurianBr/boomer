
#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"
#include "player.h"
#include <stdio.h>
#define MAX_COLUMNS 20

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 1280;
	const int screenHeight = 720;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera first person");

	// Define the camera to look into our 3d world (position, target, up vector)
	/*
	Camera camera = { 0 };
	camera.position = (Vector3){ 0.0f, 2.0f, 4.0f };    // Camera position
	camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 60.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
	*/

	int cameraMode = CAMERA_FIRST_PERSON;

	Player player = Player();

	float frameTime = 0.0f;

	// Generates some random columns
	float heights[MAX_COLUMNS] = {0};
	Vector3 positions[MAX_COLUMNS] = {0};
	Color colors[MAX_COLUMNS] = {0};

	for (int i = 0; i < MAX_COLUMNS; i++)
	{
		heights[i] = (float)GetRandomValue(1, 12);
		positions[i] = (Vector3){(float)GetRandomValue(-15, 15), heights[i] / 2.0f, (float)GetRandomValue(-15, 15)};
		colors[i] = (Color){GetRandomValue(20, 255), GetRandomValue(10, 55), 30, 255};
	}

	DisableCursor(); // Limit cursor to relative movement inside the window

	SetTargetFPS(60); // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{

		frameTime = GetFrameTime();

		player.updateCamera(frameTime);

		// Update
		//----------------------------------------------------------------------------------
		/*
		if (caracterStance == STANCE_CROUCHING || caracterStance == STANCE_UPING)
		{
			timer += GetFrameTime();

			if (timer > 0.1)
			{
				if (caracterStance == STANCE_CROUCHING)
				{
					caracterStance == STANCE_CROUCH;
				}

				if (caracterStance == STANCE_UPING)
				{
					caracterStance == STANCE_UP;
				}
			}
		}
		// Check bottons
		if (IsKeyPressed(KEY_LEFT_CONTROL))
		{
			if (caracterStance == STANCE_UP)
			{
				caracterStance = STANCE_CROUCHING;
				camera.position.y = 1.0f;
				camera.target.y = camera.target.y - 1.0f;
				timer = 0;
			}

			if (caracterStance == STANCE_CROUCH)
			{
				caracterStance = STANCE_UPING;
				camera.position.y = 2.0f;
				camera.target.y = camera.target.y + 1.0f;
				timer = 0;
			}
		}
		*/
		// Switch camera mode
		/*
		if (IsKeyPressed(KEY_ONE))
		{
			cameraMode = CAMERA_FREE;
			camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
		}

		if (IsKeyPressed(KEY_TWO))
		{
			cameraMode = CAMERA_FIRST_PERSON;
			camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
		}

		if (IsKeyPressed(KEY_THREE))
		{
			cameraMode = CAMERA_THIRD_PERSON;
			camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
		}

		if (IsKeyPressed(KEY_FOUR))
		{
			cameraMode = CAMERA_ORBITAL;
			camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
		}
		*/

		// Switch camera projection
		/*
		if (IsKeyPressed(KEY_P))
		{
			if (camera.projection == CAMERA_PERSPECTIVE)
			{
				// Create isometric view
				cameraMode = CAMERA_THIRD_PERSON;
				// Note: The target distance is related to the render distance in the orthographic projection
				camera.position = (Vector3){ 0.0f, 2.0f, -100.0f };
				camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };
				camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
				camera.projection = CAMERA_ORTHOGRAPHIC;
				camera.fovy = 20.0f; // near plane width in CAMERA_ORTHOGRAPHIC
				CameraYaw(&camera, -135 * DEG2RAD, true);
				CameraPitch(&camera, -45 * DEG2RAD, true, true, false);
			}
			else if (camera.projection == CAMERA_ORTHOGRAPHIC)
			{
				// Reset to default view
				cameraMode = CAMERA_THIRD_PERSON;
				camera.position = (Vector3){ 0.0f, 2.0f, 10.0f };
				camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };
				camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
				camera.projection = CAMERA_PERSPECTIVE;
				camera.fovy = 60.0f;
			}
		}
		*/
		// Update camera computes movement internally depending on the camera mode
		// Some default standard keyboard/mouse inputs are hardcoded to simplify use
		// For advanced camera controls, it's recommended to compute camera movement manually
		// UpdateCamera(&camera, cameraMode);                  // Update camera

		/*
				// Camera PRO usage example (EXPERIMENTAL)
				// This new camera function allows custom movement/rotation values to be directly provided
				// as input parameters, with this approach, rcamera module is internally independent of raylib inputs
				UpdateCameraPro(&camera,
					(Vector3){
						(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))*0.1f -      // Move forward-backward
						(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))*0.1f,
						(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))*0.1f -   // Move right-left
						(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))*0.1f,
						0.0f                                                // Move up-down
					},
					(Vector3){
						GetMouseDelta().x*0.05f,                            // Rotation: yaw
						GetMouseDelta().y*0.05f,                            // Rotation: pitch
						0.0f                                                // Rotation: roll
					},
					GetMouseWheelMove()*2.0f);                              // Move to target (zoom)
		*/
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		BeginMode3D(player.getCamera());

		DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){32.0f, 32.0f}, LIGHTGRAY); // Draw ground
		DrawCube((Vector3){-16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, BLUE);			// Draw a blue wall
		DrawCube((Vector3){16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, LIME);			// Draw a green wall
		DrawCube((Vector3){0.0f, 2.5f, 16.0f}, 32.0f, 5.0f, 1.0f, GOLD);			// Draw a yellow wall

		// Draw some cubes around
		/*
		for (int i = 0; i < MAX_COLUMNS; i++)
		{
			DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
			DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
		}
		*/

		//DrawCube((Vector3){0.0f, 1.0f, 0.0f}, 2.0f, 2.0f, 2.0f, BLUE);
		//DrawCubeWires((Vector3){0.0f, 1.0f, 0.0f}, 2.0f, 2.0f, 2.0f, DARKGRAY);

		BoundingBox playerBoundingBox = (BoundingBox){(Vector3){player.getCamera().position.x - 0.25f,
																player.getCamera().position.y - 0.5f,
																player.getCamera().position.z - 0.25f},
													  (Vector3){player.getCamera().position.x + 0.25f,
																player.getCamera().position.y + 0.5f,
																player.getCamera().position.z + 0.25f}};

		BoundingBox objectBoundingBox = (BoundingBox){(Vector3){0.0f - 1.0f,
																1.0f - 1.0f,
																0.0f - 1.0f},
													  (Vector3){0.0f + 1.0f,
																1.0f + 1.0f,
																0.0f + 1.0f}};


		DrawCube((Vector3){
			(objectBoundingBox.min.x + objectBoundingBox.max.x) / 2, 
			(objectBoundingBox.min.y + objectBoundingBox.max.y) / 2, 
			(objectBoundingBox.min.z + objectBoundingBox.max.z) / 2
		}, 1.0f, 1.0f, 1.0f, DARKBLUE);	

		
		DrawBoundingBox(objectBoundingBox, BLUE);

		/*
		// Calculate Minkowski sum of playerBoundingBox and objectBoundingBox
		Vector3 playerCenter = Vector3Scale(Vector3Add(playerBoundingBox.min, playerBoundingBox.max), 0.5f);
		Vector3 objectCenter = Vector3Scale(Vector3Add(objectBoundingBox.min, objectBoundingBox.max), 0.5f);

		Vector3 playerHalfSize = Vector3Scale(Vector3Subtract(playerBoundingBox.max, playerBoundingBox.min), 0.5f);
		Vector3 objectHalfSize = Vector3Scale(Vector3Subtract(objectBoundingBox.max, objectBoundingBox.min), 0.5f);

		Vector3 minkowskiCenter = Vector3Add(playerCenter, objectCenter);
		Vector3 minkowskiHalfSize = Vector3Add(playerHalfSize, objectHalfSize);

		BoundingBox minkowskiSum = {
			Vector3Subtract(minkowskiCenter, minkowskiHalfSize),
			Vector3Add(minkowskiCenter, minkowskiHalfSize)};

		// Optionally, draw the Minkowski sum box for visualization
		DrawBoundingBox(minkowskiSum, BLACK);
		*/
		//bool collision = CheckCollisionBoxes(playerBoundingBox, objectBoundingBox);

		Vector3 test = (Vector3){0.0f, 1.0f, 0.0f};

		Vector3 direction = Vector3Subtract(
			test,
			player.getCamera().position);

		Vector3 directionNormalized = Vector3Normalize(direction);

		Ray ray = (Ray){(Vector3){player.getCamera().position.x,
								  1.0f,
								  player.getCamera().position.z},
						direction};

		RayCollision collisionInfo = GetRayCollisionBox(ray, objectBoundingBox);

		DrawCube(collisionInfo.point, 0.1f, 0.1f, 0.1f, BLACK);
		// DrawPoint3D(collisionInfo.point, BLACK);

		DrawRay(ray, RED);

		/*
		Vector3 playerPos = player.getCamera().position;
		Vector3 cubePos = (Vector3){0.0f, 1.0f, 0.0f}; // Example: center of the blue cube

		Vector3 direction = Vector3Normalize((Vector3){
			cubePos.x - playerPos.x,
			cubePos.y - playerPos.y,
			cubePos.z - playerPos.z});

		Ray ray = {playerPos, direction};

		DrawRay(ray, RED);
		*/

		float intersectionMinX = fmax(playerBoundingBox.min.x, objectBoundingBox.min.x);
		float intersectionMinY = fmax(playerBoundingBox.min.y, objectBoundingBox.min.y);
		float intersectionMinZ = fmax(playerBoundingBox.min.z, objectBoundingBox.min.z);

		float intersectionMaxX = fmin(playerBoundingBox.max.x, objectBoundingBox.max.x);
		float intersectionMaxY = fmin(playerBoundingBox.max.y, objectBoundingBox.max.y);
		float intersectionMaxZ = fmin(playerBoundingBox.max.z, objectBoundingBox.max.z);

		float overlapX = intersectionMaxX - intersectionMinX;
		float overlapY = intersectionMaxY - intersectionMinY;
		float overlapZ = intersectionMaxZ - intersectionMinZ;

		bool xCollision = false;
		bool yCollision = false;
		bool zCollision = false;

		if (playerBoundingBox.min.x <= objectBoundingBox.max.x && playerBoundingBox.max.x >= objectBoundingBox.min.x)
		{
			xCollision = true;
		}

		if (playerBoundingBox.min.y <= objectBoundingBox.max.y && playerBoundingBox.max.y >= objectBoundingBox.min.y)
		{
			yCollision = true;
		}

		if (playerBoundingBox.min.z <= objectBoundingBox.max.z && playerBoundingBox.max.z >= objectBoundingBox.min.z)
		{
			zCollision = true;
		}

		if (xCollision && yCollision && zCollision)
		{	

			char overlapAxis = ' ';
			float direction = 0.0f;

			if (overlapX < overlapZ && overlapX < overlapY)
			{
				overlapAxis = 'x';
				direction = ((objectBoundingBox.min.x + objectBoundingBox.max.x) / 2) - ((playerBoundingBox.min.x + playerBoundingBox.max.x) / 2);
			}

			if (overlapZ < overlapX && overlapZ < overlapY)
			{
				overlapAxis = 'z';
				direction = ((objectBoundingBox.min.z + objectBoundingBox.max.z) / 2) - ((playerBoundingBox.min.z + playerBoundingBox.max.z) / 2);
			}

			if (overlapY < overlapZ && overlapY < overlapX)
			{
				overlapAxis = 'y';
				direction = ((objectBoundingBox.min.y + objectBoundingBox.max.y) / 2) - ((playerBoundingBox.min.y + playerBoundingBox.max.y) / 2);
			}

			if (direction > 0)
			{
				direction = -1.0f;
			}
			else
			{
				direction = 1.0f;
			}

			Vector3 movement = player.getLastMovement();

			Vector3 intersectionMin = (Vector3) {
				intersectionMinX,
				intersectionMinY,
				intersectionMinZ
			};

			Vector3 intersectionMax = (Vector3) {
				intersectionMaxX,
				intersectionMaxY,
				intersectionMaxZ
			};

			BoundingBox intersectionBoundingBox = (BoundingBox) {
				intersectionMin,
				intersectionMax
			};

			DrawBoundingBox(intersectionBoundingBox, YELLOW);

			Vector3 invertedMovement = (Vector3){
				0,0,0
			};

			if(overlapAxis == 'x'){
				player.getCameraPointer()->position.x += overlapX * direction;
				player.getCameraPointer()->target.x += overlapX * direction;
			}
			if(overlapAxis == 'y')
			{
				player.getCameraPointer()->position.y += overlapY * direction;
				player.getCameraPointer()->target.y += overlapY * direction;
			}
			if(overlapAxis == 'z')
			{
				player.getCameraPointer()->position.z += overlapZ * direction;
				player.getCameraPointer()->target.z += overlapZ * direction;
			}
			
			DrawBoundingBox(playerBoundingBox, RED);
		}
		else
		{
			DrawBoundingBox(playerBoundingBox, BLACK);
		}

		/* Draw player cube
		if (cameraMode == CAMERA_THIRD_PERSON)
		{
			DrawCube(camera.target, 0.5f, 0.5f, 0.5f, PURPLE);
			DrawCubeWires(camera.target, 0.5f, 0.5f, 0.5f, DARKPURPLE);
		}
		*/

		EndMode3D();

		// Draw info boxes
		DrawRectangle(5, 5, 330, 100, Fade(SKYBLUE, 0.5f));
		DrawRectangleLines(5, 5, 330, 100, BLUE);

		DrawText(TextFormat("overlapX %.2f", overlapX), 15, 150, 10, BLACK);
		DrawText(TextFormat("overlapY %.2f", overlapY), 15, 165, 10, BLACK);
		DrawText(TextFormat("overlapZ %.2f", overlapZ), 15, 180, 10, BLACK);

		DrawText("Camera controls:", 15, 15, 10, BLACK);
		DrawText("- Move keys: W, A, S, D, Space, Left-Ctrl", 15, 30, 10, BLACK);
		DrawText("- Look around: arrow keys or mouse", 15, 45, 10, BLACK);
		DrawText("- Camera mode keys: 1, 2, 3, 4", 15, 60, 10, BLACK);
		DrawText("- Zoom keys: num-plus, num-minus or mouse scroll", 15, 75, 10, BLACK);
		DrawText("- Camera projection key: P", 15, 90, 10, BLACK);

		DrawRectangle(600, 5, 195, 100, Fade(SKYBLUE, 0.5f));
		DrawRectangleLines(600, 5, 195, 100, BLUE);

		DrawText("Camera status:", 610, 15, 10, BLACK);
		DrawText(TextFormat("- Mode: %s", (cameraMode == CAMERA_FREE) ? "FREE" : (cameraMode == CAMERA_FIRST_PERSON) ? "FIRST_PERSON"
																			 : (cameraMode == CAMERA_THIRD_PERSON)	 ? "THIRD_PERSON"
																			 : (cameraMode == CAMERA_ORBITAL)		 ? "ORBITAL"
																													 : "CUSTOM"),
				 610, 30, 10, BLACK);
		DrawText(TextFormat("- Projection: %s", (player.getCamera().projection == CAMERA_PERSPECTIVE) ? "PERSPECTIVE" : (player.getCamera().projection == CAMERA_ORTHOGRAPHIC) ? "ORTHOGRAPHIC"
																																											   : "CUSTOM"),
				 610, 45, 10, BLACK);
		DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", player.getCamera().position.x, player.getCamera().position.y, player.getCamera().position.z), 610, 60, 10, BLACK);
		DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", player.getCamera().target.x, player.getCamera().target.y, player.getCamera().target.z), 610, 75, 10, BLACK);
		DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", player.getCamera().up.x, player.getCamera().up.y, player.getCamera().up.z), 610, 90, 10, BLACK);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow(); // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}