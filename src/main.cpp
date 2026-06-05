#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <cstddef>
#include <cstdlib>
#include <ctime>
const float circle_radius = 200.0f;
const float square_length = 2 * circle_radius;
const float screen_height = 450;
const float screen_width = 800;
using namespace std;
int main() {
  srand(time(nullptr));
  InitWindow(800, 450, "Monte Carlo Simulation PI Estimation");
  SetTargetFPS(12);
  float num_itr = 10000;
  double pi;
  // rectangle
  int offsetRec = square_length / 2;
  int recX = screen_width / 2 - offsetRec;
  int recY = screen_height / 2 - offsetRec;
  // circle
  float centerX = screen_width / 2;
  float centerY = screen_height / 2;
  size_t inside = 0;
  while (!WindowShouldClose()) {
    inside = 0;
    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangleLines(recX, recY, square_length, square_length, WHITE);
    DrawCircleLinesV({centerX, centerY}, circle_radius, WHITE);

    GuiSlider((Rectangle){20.0f, 50.0f, 100, 20}, "100", "20000", &num_itr, 100,
              20000);
    int itr = (int)num_itr;

    DrawText(TextFormat("Iterations: %d", itr), 10, 30, 10, WHITE);
    DrawText(TextFormat("PI=%.6f", pi), 10, 10, 10, WHITE);

    for (size_t i = 0; i < itr; i++) {
      Vector2 points;
      points.x = (float)rand() / RAND_MAX * square_length;
      points.y = (float)rand() / RAND_MAX * square_length;
      float dx = points.x + (centerX)-offsetRec;
      float dy = points.y + (centerY)-offsetRec;
      float posX = dx - centerX;
      float posY = dy - centerY;
      bool isInside =
          (posX * posX + posY * posY <= circle_radius * circle_radius);
      if (isInside) {
        inside++;
      }
      DrawPixelV({dx, dy}, isInside ? GREEN : RED);
      // DrawCircleV({dx, dy}, 2.0f, isInside ? RED : BLUE);
    }
    pi = 4.0 * double(inside) / double(itr);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
