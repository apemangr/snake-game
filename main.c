#include <stdio.h>
#include <raylib.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   800 
#define COLUMNS SCREEN_WIDTH/50
#define ROWS SCREEN_HEIGHT/50
#define SNAKE_HEIGHT 50 
#define SNAKE_WIDTH SNAKE_HEIGHT 
#define SNAKE_SPAWN_X 250
#define SNAKE_SPAWN_Y 250
#define RAND_X_LIMIT 800
#define RAND_Y_LIMIT 800

int randomGenerator(int limit){
    return (rand() % ((limit-25) / 50 + 1)) * 50 + 25;
}

int main()
{
    srand(time(NULL)); // Set the seed of the random generator    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game in C");
    int points = 0;
    char coords[50]; 
    char pointsString[50];
    Vector2 circleCenter = {randomGenerator(RAND_X_LIMIT),
                            randomGenerator(RAND_Y_LIMIT)};

    Rectangle snake = {SNAKE_SPAWN_X, SNAKE_SPAWN_Y, SNAKE_WIDTH, SNAKE_HEIGHT}; 
    char lastPosition = 'R'; // U->Up, D->Down, R->Right, L->Left 
    char previousPosition = 'R';
    float speed = 5.0f;
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {

        //printf("\nSnake X = %f\nSnake Y = %f\nLast = %c Previous = %c",snake.x, snake.y, lastPosition, previousPosition);
        
        switch(lastPosition){
            case 'U':
                if ((int)snake.x % 50 == 0){
                    previousPosition = lastPosition;
                    snake.y -= speed;
                }
                else{

                    switch (previousPosition) {
                        case 'R':
                            snake.x += speed;
                            break;

                        case 'L':
                            snake.x -= speed;
                            break;

                        case 'D':
                            snake.y += speed; 
                            break;
                        default:
                            printf("\nError lastPosition\n");
                    }

                }
                break; 

            case 'D':
                if ((int)snake.x % 50 == 0){
                    previousPosition = lastPosition;
                    snake.y += speed;
                }
                else{

                    switch (previousPosition) {
                        case 'R':
                            snake.x += speed;
                            break;

                        case 'L':
                            snake.x -= speed;
                            break;

                        case 'U':
                            snake.y -= speed; 
                            break;
                        default:
                            printf("\nError lastPosition\n");
                    }

                }
                break;

            case 'L':
                if ((int)snake.y% 50 == 0){
                    previousPosition = lastPosition;
                    snake.x -= speed;
                }
                else{

                    switch (previousPosition) {
                        case 'R':
                            snake.x += speed;
                            break;

                        case 'D':
                            snake.y += speed;
                            break;

                        case 'U':
                            snake.y -= speed; 
                            break;
                        default:
                            printf("\nError lastPosition\n");
                    }

                }
                break;


            case 'R':
                if ((int)snake.y% 50 == 0){
                    previousPosition = lastPosition;
                    snake.x += speed;
                }
                else{

                    switch (previousPosition) {
                        case 'L':
                            snake.x -= speed;
                            break;

                        case 'D':
                            snake.y += speed;
                            break;

                        case 'U':
                            snake.y -= speed; 
                            break;
                        default:
                            printf("\nError lastPosition\n");
                    }

                }
                break;

            case '0':
                snake.x = 0;
                snake.y = 0;
                break;

            default:
                printf("Error\n");
        }
        
        if (IsKeyDown(KEY_UP)){
            lastPosition = 'U'; 
        }

        if (IsKeyDown(KEY_DOWN)){
            lastPosition = 'D'; 
        }

        if (IsKeyDown(KEY_LEFT)){
            lastPosition = 'L'; 
        }

        if (IsKeyDown(KEY_RIGHT)){
            lastPosition = 'R'; 
        }


        BeginDrawing();

        ClearBackground(RAYWHITE);


        for (int i = 0; i < COLUMNS; i++) {
            for (int j = 0; j < ROWS; j++) {
                DrawRectangleLines( i * SNAKE_WIDTH,
                                    j * SNAKE_HEIGHT,
                                    SNAKE_WIDTH,
                                    SNAKE_HEIGHT,
                                    GRAY); 
            }
        }


        DrawRectangleRec(snake, GREEN);

        sprintf(pointsString, "Points: %d", points);
        DrawText(pointsString, 10, 0, 25, BLACK);
        DrawCircle(circleCenter.x,circleCenter.y,25, RED);
        DrawFPS(200,200);
        if(CheckCollisionCircleRec(circleCenter, 25, snake)){
            DrawText("Collided", 5,5,25, BLACK);
            circleCenter.x = randomGenerator(RAND_X_LIMIT);
            circleCenter.y = randomGenerator(RAND_Y_LIMIT);
            points++; 
        }

        sprintf(coords, "X: %f, Y: %f", snake.x, snake.y);
        DrawText(coords, 100, 30,25, BLACK);
        EndDrawing();

    }

    CloseWindow();

    return 0;
}
