#include "raylib.h"
#include <random>

class MyRectangle {
public:
    int x, y;     // Position of the rectangle (top-left corner)
    int width, height;  // Size of the rectangle
    Color color;  // Color of the rectangle

    // Constructor to initialize the rectangle's properties
    MyRectangle(int x, int y, int width, int height, Color color)
        : x(x), y(y), width(width), height(height), color(color) {}

    // Method to draw the rectangle
    void draw() const {
        DrawRectangle(x, y, width, height, color);
    }

    // Method to move the rectangle to a new position
    void move(int dx, int dy, int minY, int maxY) {
        x += dx;
        y += dy;

        // Clamp the y value to ensure the rectangle stays within bounds
        if (y < minY) y = minY;  // Prevent going above the screen
        if (y + height > maxY) y = maxY - height;  // Prevent going below the screen
    }

    // Method to change the color of the rectangle
    void setColor(Color newColor) {
        color = newColor;
    }
};

bool CheckCollision(const MyRectangle& rect1, const MyRectangle& rect2) {
    return (rect1.x + rect1.width > rect2.x && 
            rect1.x < rect2.x + rect2.width &&
            rect1.y + rect1.height > rect2.y &&
            rect1.y < rect2.y + rect2.height);
    }

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(100, screenHeight - 100);
    InitWindow(screenWidth, screenHeight, "Shitty Bird");

    SetTargetFPS(60);
    int tempEnemyHeight = distribution(generator);

    // Create a MyRectangle instance
    MyRectangle rect(150, 150, 100, 50, GREEN);
    MyRectangle enemy(750, screenHeight - tempEnemyHeight, 50, tempEnemyHeight, RED);

    int minY = 0;
    int maxY = screenHeight;

    bool gameOver = false;
    Vector2 restartButtonPosition = { screenWidth / 2 - 100, screenHeight / 2 };  // Restart button position
    int restartButtonWidth = 200;
    int restartButtonHeight = 50;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (gameOver) {
            // display game-over text
            DrawText("GAME OVER", screenWidth / 2 - 70, screenHeight / 2 - 100, 30, RED);

            DrawRectangleV(restartButtonPosition, Vector2{ static_cast<float>(restartButtonWidth), static_cast<float>(restartButtonHeight) }, BLUE);
            DrawText("Restart", screenWidth / 2 - 40, screenHeight / 2 + 10, 20, WHITE);

            if (CheckCollisionPointRec(GetMousePosition(), { restartButtonPosition.x, restartButtonPosition.y, static_cast<float>(restartButtonWidth), static_cast<float>(restartButtonHeight) })) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    // Reset game state and positions
                    rect = MyRectangle(150, 150, 100, 50, GREEN);  // Reset player position
                    enemy = MyRectangle(750, screenHeight - tempEnemyHeight, 50, tempEnemyHeight, RED);  // Reset enemy position
                    gameOver = false;  // Reset game over state
                }
            }
        } else {
            // Draw the rectangle
        rect.draw();
        enemy.draw();

        // Move enemy left and loop
        if (enemy.x <= 0) {
            enemy.move(750, 0, minY, maxY);  // Reset enemy position
            enemy.height = distribution(generator);
            enemy.y = screenHeight - enemy.height;
        } else {
            enemy.move(-10, 0, minY, maxY);  // Move enemy left
        }

        if (IsKeyPressed(KEY_UP)) {
            rect.move(0, -100, minY, maxY);  // Move the rectangle 10 units up
        }
        
        

        rect.move(0, 3, minY, maxY);

        }

        if (CheckCollision(rect, enemy)) {
            gameOver = true;            
        }

        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
