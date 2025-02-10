#include "../inc/raylib.h"
#include "../inc/game.h"
#include <stdbool.h>

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

void initGame(GameState *state)
{
    state->config.screenHeight      = 600;
    state->config.screenWidth       = 800;
    state->config.BALL_RADIUS       = 10;
    state->config.PADDLE_WIDTH      = 10;
    state->config.PADDLE_HEIGHT     = 50;
    state->config.TEXT_SIZE         = 30;
    state->config.PLAYER_SPEED      = 4.0f;
    
    restartGameState(state);
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