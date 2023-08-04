#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define GRID_SIZE 20
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

typedef struct {
  int x;
  int y;
} Position;

typedef struct {
  Position position;
  Color color;
} SnakeSegment;

int main(void) {
  // Inicializar la ventana
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");

  // Inicializar la serpiente
  SnakeSegment snake[100];
  int snakeLength = 1;
  snake[0].position.x = SCREEN_WIDTH / (2 * GRID_SIZE);
  snake[0].position.y = SCREEN_HEIGHT / (2 * GRID_SIZE);
  snake[0].color = GREEN;

  // Inicializar la dirección de movimiento
  int directionX = 1;
  int directionY = 0;

  // Fotogramas
  int frameRate = 0;

  // Inicializar la posición de la comida
  Position food;
  food.x = GetRandomValue(0, SCREEN_WIDTH / GRID_SIZE - 1);
  food.y = GetRandomValue(0, SCREEN_HEIGHT / GRID_SIZE - 1);

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // Actualizar la dirección de la serpiente
    if (IsKeyPressed(KEY_RIGHT) && directionX != -1) {
      directionX = 1;
      directionY = 0;
    } else if (IsKeyPressed(KEY_LEFT) && directionX != 1) {
      directionX = -1;
      directionY = 0;
    } else if (IsKeyPressed(KEY_UP) && directionY != 1) {
      directionX = 0;
      directionY = -1;
    } else if (IsKeyPressed(KEY_DOWN) && directionY != -1) {
      directionX = 0;
      directionY = 1;
    }

    // Mover la serpiente
    if (frameRate > 2) {

      for (int i = snakeLength - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
      }
      snake[0].position.x += directionX;
      snake[0].position.y += directionY;
      frameRate = 0;
    }else{
        frameRate++;
    }
    // Comprobar colisión con los bordes de la pantalla
    if (snake[0].position.x < 0 ||
        snake[0].position.x >= SCREEN_WIDTH / GRID_SIZE ||
        snake[0].position.y < 0 ||
        snake[0].position.y >= SCREEN_HEIGHT / GRID_SIZE) {
      break; // Juego terminado
    }

    // Comprobar colisión con la comida
    if (snake[0].position.x == food.x && snake[0].position.y == food.y) {
      // Aumentar la longitud de la serpiente
      snakeLength++;

      // Generar una nueva posición para la comida
      food.x = GetRandomValue(0, SCREEN_WIDTH / GRID_SIZE - 1);
      food.y = GetRandomValue(0, SCREEN_HEIGHT / GRID_SIZE - 1);
    }

    // Comprobar colisión de la serpiente consigo misma
    for (int i = 1; i < snakeLength; i++) {
      if (snake[0].position.x == snake[i].position.x &&
          snake[0].position.y == snake[i].position.y) {
        break; // Juego terminado
      }
    }

    // Renderizar la escena
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawFPS(200, 200);
    // Dibujar la serpiente
    for (int i = 0; i < snakeLength; i++) {
      DrawRectangle(snake[i].position.x * GRID_SIZE,
                    snake[i].position.y * GRID_SIZE, GRID_SIZE, GRID_SIZE,
                    snake[i].color);
    }

    // Dibujar la comida
    DrawRectangle(food.x * GRID_SIZE, food.y * GRID_SIZE, GRID_SIZE, GRID_SIZE,
                  RED);

    EndDrawing();
  }

  // Cerrar la ventana y finalizar el juego
  CloseWindow();
  return 0;
}
