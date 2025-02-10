#ifndef _GAME_H
#define _GAME_H

#include "raylib.h"
#include <stdbool.h>
#include <stdint.h>

#define PLAYER_1_SCORED  1
#define PLAYER_2_SCORED  0

typedef enum _scene 
{
    PAUSED,
    GAMEPLAY,
    ENDCARD
}Scene;

typedef struct _configs
{
    uint32_t screenHeight;
    uint32_t screenWidth;
    uint8_t  BALL_RADIUS;
    uint8_t  PADDLE_WIDTH;
    uint8_t  PADDLE_HEIGHT;
    uint8_t  TEXT_SIZE;
    float    PLAYER_SPEED;
}Configs;

typedef struct _player
{
    uint8_t score;
    Vector2 position;
}Player;

typedef struct _ball
{
    Vector2 position;
    Vector2 speed;
}Ball;

typedef struct _gamestate
{
    Player p1;
    Player p2;
    Ball ball;
    Configs config;
    Scene currentScene;
}GameState;

void initGame(GameState *state);
void restartGameState(GameState *state);
void playerScored(bool player1, GameState *state);

#endif