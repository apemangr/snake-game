#include <stdio.h>
#include <raylib.h>

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   800 
#define COLUMNS SCREEN_WIDTH/50
#define ROWS SCREEN_HEIGHT/50
#define SNAKE_HEIGHT 50 
#define SNAKE_WIDTH SNAKE_HEIGHT 
#define SNAKE_SPAWN_X 250
#define SNAKE_SPAWN_Y 250



float floatModulo(float dividend, float divisor) {
    int intDividend = (int)dividend;
    int intDivisor = (int)divisor;
    
    int intResult = intDividend % intDivisor;
    float floatResult = (float)intResult;
    
    return floatResult;
}



int main()
{

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game in C");

    Vector2 circleCenter = {250, 250};
    Rectangle snake = {SNAKE_SPAWN_X, SNAKE_SPAWN_Y, SNAKE_WIDTH, SNAKE_HEIGHT}; 
    char lastPosition = 'R'; // U->Up, D->Down, R->Right, L->Left 
    char previousPosition = '0';
    SetTargetFPS(60);
    char Coords[100];
    while (!WindowShouldClose())
    {

        printf("\nSnake X = %f\nSnake Y = %f\nLast = %c Previous = %c",snake.x, snake.y, lastPosition, previousPosition);

        switch(lastPosition){
            case 'U':
                if (floatModulo(snake.x, 50) == 0)
                    snake.y -= 5.0f;
                else{

                    switch (previousPosition) {
                        case 'R':
                            snake.x += 5.0f;
                            break;

                        case 'L':
                            snake.x -= 5.0f;
                            break;

                        case 'D':
                            snake.y += 5.0f; 
                            break;
                        default:
                            break;
                    }

                }
                break; 

            case 'D':
                previousPosition = 'D';
                snake.y += 5.0f;
                break;

            case 'L':
                previousPosition = 'L';
                snake.x -= 5.0f;
                break;

            case 'R':
                previousPosition = 'R';
                snake.x += 5.0f;
                break;

            case '0':
                snake.x = 0;
                snake.y = 0;
                break;

            default:
                printf("Error\n");
        }
        
        if (IsKeyDown(KEY_UP)){
            if(previousPosition != lastPosition){
                previousPosition = lastPosition;
                lastPosition = 'U'; 
            }
        }

        if (IsKeyDown(KEY_DOWN)){

            if(previousPosition != lastPosition)
                previousPosition = lastPosition;
            lastPosition = 'D'; 
        }
        if (IsKeyDown(KEY_LEFT)){

            if(previousPosition != lastPosition)
                previousPosition = lastPosition;
            lastPosition = 'L'; 
        }
        if (IsKeyDown(KEY_RIGHT)){

            if(previousPosition != lastPosition)
                previousPosition = lastPosition;
            lastPosition = 'R'; 
        }


        BeginDrawing();

        ClearBackground(RAYWHITE);


        for (int i = 0; i < COLUMNS; i++) {
            for (int j = 0; j < ROWS; j++) {
                DrawRectangleLines(i * SNAKE_WIDTH, j * SNAKE_HEIGHT, SNAKE_WIDTH, SNAKE_HEIGHT, BLACK); 
            }
        }


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
