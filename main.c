/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute 'raylib_compile_execute' script
*   Note that compiled executable is placed in the same folder as .c file
*
*   To test the examples on Web, press F6 and execute 'raylib_compile_execute_web' script
*   Web version of the program is generated in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib pong");
    
    //Ball variables
    Vector2 ballPosition = {};
    Vector2 ballSpeed = { 5.0f, 4.0f}; //limit 10.0f
    int ballRadius = 20;
    ballPosition.x = 400;
    ballPosition.y = 225;
    
    //Player variables
    Vector2 PlayerSize = { 10, 70 };

    Vector2 Player1Pos = {};
    Player1Pos.x = screenWidth - 50;
    Player1Pos.y = 225 - PlayerSize.y;

    Vector2 Player2Pos = {};
    Player2Pos.x = 50;
    Player2Pos.y = 225 - PlayerSize.y;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        //Player Movement
        if (IsKeyDown(KEY_UP)) Player1Pos.y -= 5.0f;
        if (IsKeyDown(KEY_DOWN)) Player1Pos.y += 5.0f;
        
        if (IsKeyDown(KEY_W)) Player2Pos.y -= 5.0f;
        if (IsKeyDown(KEY_S)) Player2Pos.y += 5.0f;
        
        //Player Limits
        //if ((Player1Pos.y >= (GetScreenHeight() + 35)) || (Player1Pos.y <= (GetScreenHeight() - 35)))

        //Ball Movement
        ballPosition.x += ballSpeed.x;
        ballPosition.y += ballSpeed.y;
        if (ballSpeed.x >= 13.0f) ballSpeed.x *= 0.7f;
        if (ballSpeed.y >= 13.0f) ballSpeed.y *= 0.7f;

        //Player Collision
        if ((ballPosition.x >= Player1Pos.x - ballRadius) && (ballPosition.y >= Player1Pos.y) && (ballPosition.y <= Player1Pos.y + 70)) ballSpeed.x *= -1.1f;
        if ((ballPosition.x <= Player2Pos.x + ballRadius) && (ballPosition.y >= Player2Pos.y) && (ballPosition.y <= Player2Pos.y + 70)) ballSpeed.x *= -1.1f;

        if ((ballPosition.y >= (GetScreenHeight() - ballRadius)) || (ballPosition.y <= ballRadius)) ballSpeed.y *= -0.95f;

        //Check for losing
        if ((ballPosition.x >= (GetScreenWidth() - ballRadius)) || (ballPosition.x <= ballRadius)) ballSpeed.x *= -1.1f;
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawRectangleV(Player1Pos, PlayerSize, DARKBLUE);
            DrawRectangleV(Player2Pos, PlayerSize, MAROON);
            DrawCircleV(ballPosition, (float)ballRadius, DARKPURPLE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}