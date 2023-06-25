#include <stdio.h>
#include <raylib.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720 

int main()
{

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game in C");

    Vector2 circleCenter = {250, 250};
    Rectangle snake = {100, 100, 50, 50}; 
    char lastPosition = 'R'; // U->Up, D->Down, R->Right, L->Left 

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        switch(lastPosition){
            case 'U':
                snake.y -= 4.0f;
                break; 

            case 'D':
                snake.y += 4.0f;
                break;
                
            case 'L':
                snake.x -= 4.0f;
                break;

            case 'R':
                snake.x += 4.0f;
                break;
           
            case '0':
                snake.x = 0;
                snake.y = 0;
                break;

           default:
                printf("Error\n");
        }
        if (IsKeyDown(KEY_UP)) lastPosition = 'U'; 
        if (IsKeyDown(KEY_DOWN))lastPosition = 'D'; 
        if (IsKeyDown(KEY_LEFT)) lastPosition = 'L'; 
        if (IsKeyDown(KEY_RIGHT)) lastPosition = 'R'; 
 
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangleRec(snake, GREEN);
            DrawCircle(250,250,25, RED);
            
            if(CheckCollisionCircleRec(circleCenter, 25, snake)){
                DrawText("Collided", 5,5,25, BLACK);
            }

        EndDrawing();

    }

    CloseWindow();

    return 0;
}
