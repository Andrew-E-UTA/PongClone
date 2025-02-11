#ifndef _GAME_H
#define _GAME_H

#include "raylib.h"
#include <stdbool.h>
#include <stdint.h>

#define PLAYER_1_SCORED  1
#define PLAYER_2_SCORED  0

#define NUM_BUTTONS 1

typedef enum _scene 
{
    PAUSED,
    GAMEPLAY,
    ENDCARD
}Scene;

typedef enum _botDifficulty
{
    BOT_EASY = 0,
    BOT_HARD = 20
}BotDifficulty;

typedef struct _text
{
    Color color;
    uint8_t fontSize;
    uint8_t strSize;
    char *str;
}Text;

typedef struct _button
{
    Rectangle bounds;
    Color color;
    Text text;
}Button;

typedef struct _menu
{
    Button *buttons;
}Menu;

typedef struct _configs
{
    uint32_t screenHeight;
    uint32_t screenWidth;
    uint8_t  BALL_RADIUS;
    uint8_t  PADDLE_WIDTH;
    uint8_t  PADDLE_HEIGHT;
    uint8_t  TEXT_SIZE;
    int BOT_DIFFICULTY;
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

void initGame(GameState *state, Menu *menu);
void closeGame(Menu *menu);
void restartGameState(GameState *state);
void playerScored(bool player1, GameState *state);
void drawButton(const Button *button);
void createButton(Button *button, int x, int y, int w, int h, char *text, Color color, Color textColor, int textSize);
void destroyButton(Button *button);
#endif