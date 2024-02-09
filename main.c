#include "raylib.h"

#define size_button_name 4

int x = 0;
int screen_widht = 1200;
int screen_height = 800;
int fontsize = 40;

typedef void (*ButtonDash)();

struct ButtonValue {
  char *key;
  ButtonDash func;
};

void home_dash() {
  ClearBackground(RAYWHITE);
  DrawText("Home", screen_widht / 2 - fontsize,
           screen_height / 2 - fontsize / 2, fontsize, GRAY);
}

void profile_dash() {
  ClearBackground(BLUE);
  DrawText("Profile", screen_widht / 2 - fontsize,
           screen_height / 2 - fontsize / 2, fontsize, WHITE);
}
void contact_dash() {
  ClearBackground(GREEN);
  DrawText("Contact", screen_widht / 2 - fontsize,
           screen_height / 2 - fontsize / 2, fontsize, WHITE);
}
void about_dash() {
  ClearBackground(YELLOW);
  DrawText("About", screen_widht / 2 - fontsize,
           screen_height / 2 - fontsize / 2, fontsize, BLACK);
}

struct ButtonValue button_sidebar[size_button_name] = {
    {"Home", home_dash},
    {"Profile", profile_dash},
    {"Contact", contact_dash},
    {"About", about_dash},
};

void sidebar_panel() {
  int sidebar_with = screen_widht * 0.2;
  int padding_left = sidebar_with * 0.1;
  int padding_top = sidebar_with * 0.28;
  int button_with = sidebar_with - padding_left * 2;
  int button_hieght = (sidebar_with - padding_top) * 0.30;
  DrawRectangle(0, 0, sidebar_with, screen_height, RED);
  DrawText("Hallo", padding_left, padding_left, 40, WHITE);
  for (int i = 0; i < size_button_name; i++) {
    Color colorBg = BLUE;
    Color colorFg = WHITE;
    int buttonX = (button_hieght + button_hieght * 0.35) * (i + 1);
    int text_widht = MeasureText(button_sidebar[i].key, 20);
    Rectangle rec_button = {
        .x = padding_left,
        .y = padding_top * (i + 1),
        .width = sidebar_with - padding_left * 2,
        .height = button_hieght,
    };
    if (CheckCollisionPointRec(GetMousePosition(), rec_button)) {
      colorBg = RAYWHITE;
      colorFg = GRAY;
      if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        button_sidebar[i].func();
        x = 1;
      }
    } else if (x == 0) {
      home_dash();
    }
    DrawRectangleRounded(rec_button, 0.25, 6, colorBg);

    DrawText(button_sidebar[i].key, (button_with * 0.6) - (text_widht * 0.5),
             buttonX + (button_hieght * 0.30), 20, colorFg);
  }
}

int main() {

  InitWindow(screen_widht, screen_height, "ui-probe");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    sidebar_panel();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
