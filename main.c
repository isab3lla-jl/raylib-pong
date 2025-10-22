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
    Vector2 ballSpeed = { 3.0f, 2.0f}; //limit 13.0f
    int ballRadius = 20;
    ballPosition.x = 400;
    ballPosition.y = 225;
    
    //Player variables
    Vector2 PlayerSize = { 10, 70 };

    Vector2 Player1Pos = {};
    Player1Pos.x = screenWidth - 50;
    Player1Pos.y = 225 - PlayerSize.y;
    bool canP1MoveUp = true;
    bool canP1MoveDown = true;
    int pointsP1 = 0;

    Vector2 Player2Pos = {};
    Player2Pos.x = 50;
    Player2Pos.y = 225 - PlayerSize.y;
    bool canP2MoveUp = true;
    bool canP2MoveDown = true;
    int pointsP2 = 0;

    //Other Variables
    bool lost = false;
    bool pause = false;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        //Player Movement & Limits
        if (!pause && !lost){
            if (Player1Pos.y >= (GetScreenHeight() - PlayerSize.y)) canP1MoveDown = false;
            if (Player1Pos.y <= 0) canP1MoveUp = false;
            if(canP1MoveUp){
                if (IsKeyDown(KEY_UP)) {
                    Player1Pos.y -= 7.0f;
                    canP1MoveDown = true;
                }
            }
            if(canP1MoveDown){
                if (IsKeyDown(KEY_DOWN)){
                    Player1Pos.y += 7.0f;
                    canP1MoveUp = true;
                }
            }

            if ((Player2Pos.y >= (GetScreenHeight() - PlayerSize.y))) canP2MoveDown = false;
            if (Player2Pos.y <= 0) canP2MoveUp = false;
            if(canP2MoveUp){
                if (IsKeyDown(KEY_W)) {
                    Player2Pos.y -= 7.0f;
                    canP2MoveDown = true;
                }
            }
            if(canP2MoveDown){
                if (IsKeyDown(KEY_S)){
                    Player2Pos.y += 7.0f;
                    canP2MoveUp = true;
                }
            }

            //Ball Movement
            ballPosition.x += ballSpeed.x;
            ballPosition.y += ballSpeed.y;
            if (ballSpeed.x >= 13.0f) ballSpeed.x *= 0.7f;
            if (ballSpeed.y >= 13.0f) ballSpeed.y *= 0.7f;
        }

        //Player Collision
        if ((ballPosition.x >= Player1Pos.x - ballRadius) && (ballPosition.y >= Player1Pos.y) && (ballPosition.y <= Player1Pos.y + 70)) ballSpeed.x *= -1.05f;
        if ((ballPosition.x <= Player2Pos.x + ballRadius) && (ballPosition.y >= Player2Pos.y) && (ballPosition.y <= Player2Pos.y + 70)) ballSpeed.x *= -1.05f;
        //Wall Collision
        if ((ballPosition.y >= (GetScreenHeight() - ballRadius)) || (ballPosition.y <= ballRadius)) ballSpeed.y *= -1.05f;

        //Point Count
        if ((ballPosition.x >= Player1Pos.x - ballRadius) && (ballPosition.y >= Player1Pos.y) && (ballPosition.y <= Player1Pos.y + 70)) pointsP1 ++;
        if ((ballPosition.x <= Player2Pos.x + ballRadius) && (ballPosition.y >= Player2Pos.y) && (ballPosition.y <= Player2Pos.y + 70)) pointsP2 ++;

        //Check for losing
        if ((ballPosition.x >= (GetScreenWidth() - ballRadius)) || (ballPosition.x <= ballRadius)) ballSpeed.x *= -0.95f;
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            DrawRectangleV(Player1Pos, PlayerSize, BLUE);
            DrawRectangleV(Player2Pos, PlayerSize, GREEN);
            DrawCircleV(ballPosition, (float)ballRadius, RED);
            DrawText(TextFormat("Points P1: %02i", pointsP1), 655, 20, 15, RAYWHITE);
            DrawText(TextFormat("Points P2: %02i", pointsP2), 65, 20, 15, RAYWHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}