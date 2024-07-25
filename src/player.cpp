#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "player.h"

//Private:

//Public:

Player::Player(Vector3 position, Vector3 target, float fov)
{
    // Define camera (position, target, up vector)
    camera.position = position;    // Camera position
    camera.target = target;      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = fov;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    DisableCursor();
}

Player::Player(Vector3 position, float fov)
{
    // Define camera (position, target, up vector)
    camera.position = position;    // Camera position
    camera.target = (Vector3){position.x - 1, position.y, position.z};      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = fov;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    DisableCursor();
}

Player::~Player()
{
}

void Player::update()
{
    UpdateCameraPro(&camera,
        Vector3{
            (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))*0.1f - (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))*0.1f,                                  // Move forward-backward
            (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))*0.1f - (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))*0.1f,                               // Move right-left
            (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_RIGHT_SHIFT))*0.1f - (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_CONTROL))*0.1f    // Move up-down
        },
        Vector3{
            GetMouseDelta().x * 0.05f,                            // Rotation: yaw
            GetMouseDelta().y * 0.05f,                            // Rotation: pitch
            0.0f                                                // Rotation: roll
        },
        GetMouseWheelMove()*2.0f);                              // Move to target (zoom)
    
    hit_ray.position = camera.position;
    hit_ray.direction = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
}

Ray Player::get_Hit_Ray()
{
    return hit_ray;
}