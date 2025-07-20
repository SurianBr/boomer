
#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

enum Stance
{
    STANCE_UPRIGHT,
    STANCE_CROUCH,
    STANCE_GROUND,
    STANCE_CROUCHING,
    STANCE_STANDING_UP,
    STANCE_UPRIGHT_LAYING_ON_GROUND,
    STANCE_LAYING_ON_GROUND,
    STANCE_GROUND_STANDING_UP
};

class Player
{
private:
    Camera camera;
    float walkingVelocity;
    float mouseVelocity;
    enum Stance stance;
    float stanceBuffer;
    float stanceTimer;

public:
    Player();
    Camera getCamera();
    void updateCamera(float frameTime);
    float updateStance(float frameTime);
};

#endif // PLAYER_H