#include "../inc/raylib.h"
#include "../inc/game.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define BALL_START_POS (Vector2)\
{\
    state->config.screenWidth/2,\
    state->config.screenHeight/2\
}

#define BALL_START_VEL (Vector2)\
{\
    -5.0f,0.0f\
}
#define P1_START_POS (Vector2)\
{\
    0,\
    state->config.screenHeight/2-state->config.PADDLE_HEIGHT/2\
}
#define P2_START_POS (Vector2)\
{\
    state->config.screenWidth-state->config.PADDLE_WIDTH,\
    state->config.screenHeight/2-state->config.PADDLE_HEIGHT/2\
}

void initGame(GameState *state, Menu *menu)
{
    state->config.screenHeight      = 600;
    state->config.screenWidth       = 800;
    state->config.BALL_RADIUS       = 10;
    state->config.PADDLE_WIDTH      = 10;
    state->config.PADDLE_HEIGHT     = 50;
    state->config.TEXT_SIZE         = 30;
    state->config.PLAYER_SPEED      = 4.0f;
    state->config.BOT_DIFFICULTY    = BOT_EASY;

    menu->buttons = malloc(sizeof(Button)*NUM_BUTTONS);
    createButton(menu->buttons, 100, 100, 60, 25, "EASY", DARKGRAY, WHITE, 20);

    restartGameState(state);
}

void closeGame(Menu *menu)
{
    for(uint8_t i = 0; i < NUM_BUTTONS; i++)
        destroyButton(&menu->buttons[i]);
}

void restartGameState(GameState *state)
{
    state->ball.speed = BALL_START_VEL;
    state->ball.position = BALL_START_POS;
    state->p1.position = P1_START_POS;
    state->p2.position = P2_START_POS;

    state->currentScene = PAUSED;

    state->p1.score = 0;
    state->p2.score = 0;
}

void playerScored(bool player1, GameState *state)
{
    state->ball.speed = BALL_START_VEL;
    state->ball.position = BALL_START_POS;
    state->p1.position = P1_START_POS;
    state->p2.position = P2_START_POS;
    if(player1)
        state->p1.score++;
    else
    state->p2.score++;
}

void drawButton(const Button *button)
{
    DrawRectangle(button->bounds.x,
        button->bounds.y,
        button->bounds.width,
        button->bounds.height,
        button->color);
    DrawText(button->text.str,
        button->bounds.x,
        button->bounds.y,
        button->text.fontSize,
        button->text.color);
}

void createButton(Button *button, int x, int y, int w, int h, char *text, Color color, Color textColor, int textSize)
{
    button->bounds = (Rectangle){x, y, w, h};
    button->color = color;
    button->text.color = textColor;
    button->text.fontSize = textSize;
    button->text.strSize = strlen(text);
    button->text.str = malloc(button->text.strSize + 1);
    strncpy(button->text.str, text, button->text.strSize + 1);
}

void destroyButton(Button *button)
{
    if(NULL) return;
    free(button->text.str);
}