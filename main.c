#include "raylib.h"
#include <stdio.h>
#include <math.h>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Silly Knight");

    Texture2D black = LoadTexture("../resources/black.png");
    Texture2D background = LoadTexture("../resources/map.png");
    Texture2D scarfy = LoadTexture("../resources/knight.png");
    Texture2D sword = LoadTexture("../resources/sword.png");

    Vector2 position = { 350.0f, 280.0f };
    Rectangle frameRec = { 0.0f, 0.0f, (float)scarfy.width/9, (float)scarfy.height };
    int currentFrame = 0;

    int framesCounter = 0;
    int framesSpeed = 8;

    int dashCount = 0;

    SetTargetFPS(60);
    bool isFacingLeft = false;

    Vector2 velocity = { 0 };
    float dashSpeed = 10.0f;
    float maxDashDistance = 100.0f;

    // Main game loop
    while (!WindowShouldClose())
    {

        framesCounter++;

        //LOGICA DE LES TECLES

        if (IsKeyDown(KEY_A) && position.x > 0) {
            position.x -= 2.0f;
            isFacingLeft = true;
        }
        if (IsKeyDown(KEY_D) && position.x < screenWidth -40) {
            position.x += 2.0f;
            isFacingLeft = false;
        }
        if (IsKeyDown(KEY_W) && position.y > 40) {
            position.y -= 2.0f;
        }
        if (IsKeyDown(KEY_S) && position.y + scarfy.height < screenHeight) {
            position.y += 2.0f;
        }

        if(IsKeyDown(KEY_A) && scarfy.width > 0){
                scarfy.width = -scarfy.width;
                isFacingLeft = true;
            }
        if(IsKeyDown(KEY_D) && scarfy.width < 0){
                scarfy.width = -scarfy.width;
                isFacingLeft = false;
            }




        //ANIMACIO SPRITE
        if (framesCounter >= (60 / framesSpeed) && (IsKeyDown(KEY_A) || IsKeyDown(KEY_D) || IsKeyDown(KEY_S) || IsKeyDown(KEY_W))){
            if(isFacingLeft){
                framesCounter = 4;
                currentFrame++;

                if (currentFrame > 8) currentFrame = 4;

                frameRec.x = (float)currentFrame * (float)scarfy.width / 9;

            }else{
                framesCounter = 4;
                currentFrame++;

                if (currentFrame > 7) currentFrame = 4;

                frameRec.x = (float)currentFrame * (float)scarfy.width / 9;
            }

        }
        else if (framesCounter >= (60 / framesSpeed) && !(IsKeyDown(KEY_A) || IsKeyDown(KEY_D) || IsKeyDown(KEY_S) || IsKeyDown(KEY_W))){

            if(isFacingLeft){

                framesCounter = 1;
                currentFrame++;

                if (currentFrame > 5) currentFrame = 1;

                frameRec.x = (float)currentFrame * (float)scarfy.width / 9;

            }else{

                framesCounter = 0;
                currentFrame++;

                if (currentFrame > 4) currentFrame = 0;

                frameRec.x = (float)currentFrame * (float)scarfy.width / 9;
            }


        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            dashCount = 0;
            Vector2 mousePosition = GetMousePosition();
            Vector2 direction = { mousePosition.x - position.x, mousePosition.y - position.y };
            float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
            if (length > 0) // Avoid division by zero
            {
                velocity.x = (direction.x / length) * dashSpeed;
                velocity.y = (direction.y / length) * dashSpeed;
            }
        }

        dashCount++;

        if(dashCount > 10){
            velocity.x = 0;
            velocity.y = 0;
        }

        position.x += velocity.x;
        position.y += velocity.y;



        BeginDrawing();
        DrawTexture(black, 0.0f, 0.0f,  LIGHTGRAY);
        DrawTexture(background, -280.0f, 0.0f,  WHITE);

        ClearBackground(RAYWHITE);

        DrawTextureRec(scarfy, frameRec, position, WHITE);
        if(isFacingLeft){
            DrawTexture(sword, position.x - 15, position.y , WHITE);
        }
        else{
            DrawTexture(sword, position.x + 30, position.y , WHITE);
        }

        EndDrawing();

    }

    UnloadTexture(scarfy);

    CloseWindow();

    return 0;
}