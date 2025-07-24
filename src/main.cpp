
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

		DrawCube((Vector3){0.0f, 1.0f, 0.0f}, 2.0f, 2.0f, 2.0f, BLUE);
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

		BoundingBox objectBoundingBoxM = (BoundingBox){(Vector3){0.0f - 1.0f - 0.25f,
																1.0f - 1.0f - 0.5f,
																0.0f - 1.0f - 0.25f},
													  (Vector3){0.0f + 1.0f + 0.25f,
																1.0f + 1.0f + 0.5f,
																0.0f + 1.0f + 0.25f}};

		
		DrawBoundingBox(objectBoundingBox, BLUE);

		DrawBoundingBox(objectBoundingBoxM, RED);

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
		bool collision = CheckCollisionBoxes(playerBoundingBox, objectBoundingBox);

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

		RayCollision collisionInfo2 = GetRayCollisionBox(ray, objectBoundingBoxM);

		DrawCube(collisionInfo2.point, 0.1f, 0.1f, 0.1f, DARKBROWN);

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

		if (IsKeyDown(KEY_G))
		{

			Vector3 direction = Vector3Subtract(
			collisionInfo2.point,
			player.getCamera().position);

			direction.y = 0.0f;

			printf("TESTE: (%.2f, %.2f, %.2f)\n", direction.x, direction.y, direction.z);

			UpdateCameraPro(
				player.getCameraPointer(),
				Vector3Normalize(direction),
				(Vector3){
					0.0f, // Rotation: yaw
					0.0f, // Rotation: pitch
					0.0f  // Rotation: roll
				},
				0.0f // Move to target (zoom)
			);
		}

		if (collision)
		{
			Vector3 movement = player.getLastMovement();

			// Calculate overlaps
			float overlapX = fmin(playerBoundingBox.max.x, objectBoundingBox.max.x) - fmax(playerBoundingBox.min.x, objectBoundingBox.min.x);
			float overlapY = fmin(playerBoundingBox.max.y, objectBoundingBox.max.y) - fmax(playerBoundingBox.min.y, objectBoundingBox.min.y);
			float overlapZ = fmin(playerBoundingBox.max.z, objectBoundingBox.max.z) - fmax(playerBoundingBox.min.z, objectBoundingBox.min.z);

			// Find the axis with the smallest overlap
			float minOverlap = overlapX;
			char axis = 'x';
			if (overlapY < minOverlap)
			{
				minOverlap = overlapY;
				axis = 'y';
			}
			if (overlapZ < minOverlap)
			{
				minOverlap = overlapZ;
				axis = 'z';
			}

			// Determine direction
			if (axis == 'x')
			{
				//player.getCameraPointer()->position.x = collisionInfo2.point.x;
				printf("x\n");
				// player.getCameraPointer()->position.x = collisionInfo.point.x;
			}
			else if (axis == 'y')
			{
				printf("y\n");
				if (movement.y > 0)
				{ /* Collision from below */
				}
				else if (movement.y < 0)
				{ /* Collision from above */
				}
			}
			else if (axis == 'z')
			{
				//player.getCameraPointer()->position.z = collisionInfo2.point.z;
				printf("z\n");
				// player.getCameraPointer()->position.y = collisionInfo.point.z;
				if (movement.z > 0)
				{ /* Collision from back */
				}
				else if (movement.z < 0)
				{ /* Collision from front */
				}
			}

			printf("Movement: (%.2f, %.2f, %.2f)\n", player.getLastMovement().x, player.getLastMovement().y, player.getLastMovement().z);
			printf("collision Point: (%.2f, %.2f, %.2f)\n", collisionInfo.point.x, collisionInfo.point.y, collisionInfo.point.z);
			printf("collision Point 2: (%.2f, %.2f, %.2f)\n", collisionInfo2.point.x, collisionInfo2.point.y, collisionInfo2.point.z);

			/*
			Vector3 invertedMovement = (Vector3){
				player.getLastMovement().x * -1,
				player.getLastMovement().y * -1,
				player.getLastMovement().z * -1,
			};

			UpdateCameraPro(
				player.getCameraPointer(),
				invertedMovement,
				(Vector3){
					0.0f, // Rotation: yaw
					0.0f, // Rotation: pitch
					0.0f  // Rotation: roll
				},
				0.0f // Move to target (zoom)
			);
			*/
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