#include "raylib.h"

// Function to handle jumping logic
void jump(Vector2 &position, bool &isJumping, float &jumpSpeed, const float gravity, const float groundLevel) {
    // Jumping logic
    if (isJumping) {
        // Apply gravity to jump speed
        jumpSpeed += gravity;

        // Move the character up or down based on jump speed
        position.y -= jumpSpeed;

        // If character reaches the ground, stop jumping
        if (position.y >= groundLevel) {
            position.y = groundLevel;  // Prevent falling below ground level
            isJumping = false;         // Stop jumping
            jumpSpeed = 0.0f;          // Reset jump speed
        }
    }
}
void moveRight(Vector2 &position, const float &moveSpeed) {
    position.x += moveSpeed;
}

void moveLeft(Vector2 &position, const float &moveSpeed) {
    position.x -= moveSpeed;
}


int main() {
    // Initialize the window
    const int screenWidth = 800;
    const int screenHeight = 600;
    const float moveSpeed = 1.0f;
    InitWindow(screenWidth, screenHeight, "Game Window");

    // Define character properties
    Texture2D characterTexture = LoadTexture("character.png"); // Your character texture
    Vector2 position = { 400.0f, 500.0f };  // Starting position of the character
    bool isJumping = false;
    float jumpSpeed = 0.05f;  // Vertical speed during the jump
    const float jumpHeight = 200.0f;  // Maximum height of the jump
    const float gravity = -0.05f;  // Gravity force (negative pulls down)
    const float groundLevel = 500.0f;  // Ground Y position

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        if (IsKeyPressed(KEY_SPACE) && !isJumping) {
            isJumping = true;  // Start jumping
            jumpSpeed = 5.0f;  // Initial jump speed
        }

        if (IsKeyDown(KEY_RIGHT)) {
            moveRight(position, moveSpeed);
        }

        if (IsKeyDown(KEY_LEFT)) {
            moveLeft(position, moveSpeed);
        }

        // Call the jump function to update position and handle gravity
        jump(position, isJumping, jumpSpeed, gravity, groundLevel);

        // Begin drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the character texture at its current position
        DrawTexture(characterTexture, position.x, position.y, WHITE);

        
        

        EndDrawing();
    }

    // Unload texture and close window
    UnloadTexture(characterTexture);
    CloseWindow();

    return 0;
}
