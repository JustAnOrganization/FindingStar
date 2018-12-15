//
// Created by shrimp on 2018/12/3.
//

#include "Player.h"
#include "Game.h"

void Player::processEvent(SDL_Event& windowEvent, float deltaTime)
{
    glm::vec2 movement(0, 0);
    if (windowEvent.type == SDL_KEYDOWN && (windowEvent.key.keysym.sym == SDLK_UP
                                            || windowEvent.key.keysym.sym == SDLK_w))
    {
        //if (windowEvent.key.keysym.mod & KMOD_SHIFT) playerPosition.x -= .1; //Is shift pressed?
        movement.y = 1;
    }
    if (windowEvent.type == SDL_KEYDOWN && (windowEvent.key.keysym.sym == SDLK_DOWN
                                            || windowEvent.key.keysym.sym == SDLK_s))
    {
        movement.y = -1;
    }
    if (windowEvent.type == SDL_KEYDOWN && (windowEvent.key.keysym.sym == SDLK_LEFT
                                            || windowEvent.key.keysym.sym == SDLK_a))
    {
        movement.x = -1;
    }
    if (windowEvent.type == SDL_KEYDOWN && (windowEvent.key.keysym.sym == SDLK_RIGHT
                                            || windowEvent.key.keysym.sym == SDLK_d))
    {
        movement.x = 1;
    }

    if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_SPACE)
    {
        if (!isJumping)
        {
            isJumping = true;
            jumpVelocity = 1;
        }
        //cout << "jumping" << endl;
    }

    //todo
    if (windowEvent.type == SDL_MOUSEBUTTONDOWN)
        switch (windowEvent.button.button)
        {
            case SDL_BUTTON_LEFT:
            case SDL_BUTTON_RIGHT:
                //SDL_ShowSimpleMessageBox(0, "Mouse", "todo: hit test", window);
                break;
        }

    int mx, my;
    SDL_GetRelativeMouseState(&mx, &my);
    if (mx != 0 || my != 0)
    {
        mx = -mx;
        my = -my;

        const float rotSpeed = 1/2.0f;
        mat4 rotMat = glm::rotate(mat4(), mx * rotSpeed * deltaTime, vec3(0, 1, 0));

        pitchAngle += my * rotSpeed * deltaTime;
        if (pitchAngle > 85 / 180.0 * M_PI) pitchAngle = 85 / 180.0 * M_PI;
        else if (pitchAngle < -85 / 180.0 * M_PI) pitchAngle = -85 / 180.0 * M_PI;

        vec4 newDirection = rotMat * vec4(direction, 0);
        newDirection.y = 0;
        newDirection = normalize(newDirection);
        newDirection.y = sin(pitchAngle);//sin(pitch);

        direction = (vec3)normalize(newDirection);

        right = cross(direction, vec3(0, 1, 0));
        right = normalize(right);

        //cout << mx <<", " << my << endl;
        //cout << "right:" << right.x <<", " <<right.y << ", " << right.z << endl;
    }

    if (movement != vec2(0, 0))
    {
        const float moveSpeed = 30.0f;
        movement *= moveSpeed * deltaTime;

        vec3 newPosition = playerPosition;
        newPosition += movement.x * right;
        vec3 forward = cross(vec3(0, 1, 0), right);
        newPosition += movement.y * forward;

        if (game.checkCollision(newPosition))
        {
            playerPosition = newPosition;
        }

        //cout << playerPosition.x <<", " <<playerPosition.y << ", " << playerPosition.z << endl;
    }

    //update view matrix
    vec3 lookPoint = playerPosition + direction;
    viewMat = lookAt(playerPosition, lookPoint, vec3(0, 1, 0));
}

void Player::update(float deltaTime)
{
    if (isJumping)
    {
        const double g = 9.8/5;
        double endVelocity = jumpVelocity - g * deltaTime;
        playerPosition.y += (jumpVelocity*jumpVelocity - endVelocity*endVelocity) / 2 * g;
        jumpVelocity = endVelocity;
        //ground
        if (playerPosition.y < 0)
        {
            playerPosition.y = 0;
            jumpVelocity = 0;
            isJumping = false;
        }

        //update view matrix
        vec3 lookPoint = playerPosition + direction;
        viewMat = lookAt(playerPosition, lookPoint, vec3(0, 1, 0));
    }
}