#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "../inc/raylib.h"
#include "../inc/raymath.h"
#include "../inc/game.h"

#define RAYATH_IMPLEMENTATION

#define CONFIG  state.config
#define BALL    state.ball
#define P1      state.p1
#define P2      state.p2

int main(void)
{
    GameState state = {};
    Menu menu = {};
    char scoreBuffer[3] = {};
    char congratsBuffer[15] = {};
    bool wasRestarted = false;

    initGame(&state, &menu);

    //init Window
    InitWindow(CONFIG.screenWidth, CONFIG.screenHeight, "Pong");
    SetExitKey(KEY_F7);
    SetTargetFPS(60); 

    //Game Loop
    while (!WindowShouldClose())
    {
    //==============================================
    //LOGIC
    //==============================================

        switch(state.currentScene)
        {
            case(PAUSED):
            {
                if(IsKeyPressed(KEY_ESCAPE))
                    state.currentScene = GAMEPLAY;
                for(uint8_t i = 0; i < NUM_BUTTONS; i++)
                    if(CheckCollisionPointRec(GetMousePosition(), menu.buttons[i].bounds)
                    && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                        switch(i)
                        {
                            case 0:
                            {
                                static bool buttonState = false;
                                buttonState = !buttonState;
                                CONFIG.BOT_DIFFICULTY = buttonState? BOT_HARD: BOT_EASY;
                                strcpy(menu.buttons[0].text.str, CONFIG.BOT_DIFFICULTY != 0? "hard":"easy");
                            }break;
                            default:
                                printf("[WARNING]: Invalid Button Value Pressed!!! (%d)\n", i);
                        }
            }break;
            case(GAMEPLAY):
            {
                //State Checks=========================================================
                if(wasRestarted)
                {
                    restartGameState(&state);
                    wasRestarted = false;
                }

                if(IsKeyPressed(KEY_ESCAPE))
                    state.currentScene = PAUSED;

                //Gameplay Updates=====================================================

                //Update Ball
                BALL.position = Vector2Add(BALL.position, BALL.speed);

                //Update P1 position
                if(IsKeyDown(KEY_W))
                    P1.position.y -= CONFIG.PLAYER_SPEED;
                if(IsKeyDown(KEY_S))
                    P1.position.y += CONFIG.PLAYER_SPEED;

                //Update P2 position
                if(BALL.position.y > (P2.position.y + ((CONFIG.PADDLE_HEIGHT/2) + CONFIG.BOT_DIFFICULTY)))
                    P2.position.y += CONFIG.PLAYER_SPEED;
                else if(BALL.position.y < (P2.position.y + ((CONFIG.PADDLE_HEIGHT/2) - CONFIG.BOT_DIFFICULTY)))
                    P2.position.y -= CONFIG.PLAYER_SPEED;

                //Gameplay Updates=====================================================
                
                //Check if hitting Floor or Ceiling
                if((BALL.position.y - (CONFIG.BALL_RADIUS/2)) <= 0 
                || (BALL.position.y + (CONFIG.BALL_RADIUS/2)) >= CONFIG.screenHeight)
                    BALL.speed.y *= -1.0f;

                //Check if hitting P1
                if(BALL.position.x - CONFIG.BALL_RADIUS <= CONFIG.PADDLE_WIDTH)
                {
                    int8_t diffY = BALL.position.y - (P1.position.y + CONFIG.PADDLE_HEIGHT/2);
                    if(abs(diffY) <= CONFIG.PADDLE_HEIGHT/2)
                    {
                        BALL.speed.x *= -1;
                        BALL.speed.y = diffY / 4;
                    }
                    else
                        playerScored(PLAYER_2_SCORED, &state);
                }
                
                //Check if hitting P2
                else if(BALL.position.x + CONFIG.BALL_RADIUS >= CONFIG.screenWidth - CONFIG.PADDLE_WIDTH)
                {
                    int8_t diffY = BALL.position.y - (P2.position.y + CONFIG.PADDLE_HEIGHT/2);
                    if(abs(diffY) <= CONFIG.PADDLE_HEIGHT/2)
                    {
                        BALL.speed.x *= -1;
                        BALL.speed.y = diffY / 4;
                    }
                    else
                        playerScored(PLAYER_1_SCORED, &state);
                }

                //Check Scores
                if(P1.score == 5 || P2.score == 5)
                    state.currentScene = ENDCARD;
            }break;
            case(ENDCARD):
            {
                if(IsKeyPressed(KEY_ENTER))
                {
                    wasRestarted = true;
                    state.currentScene = PAUSED;
                }
            }break;
        }

    //==============================================
    //RENDER
    //==============================================

        BeginDrawing();
        switch(state.currentScene)
        {
            case(PAUSED):
            {
                ClearBackground(LIGHTGRAY);
                DrawText("PONG", CONFIG.screenWidth/2 - 50, CONFIG.screenHeight/2 - 2*50, 50, BLACK);
                DrawText("Press [ESC] to unpause", CONFIG.screenWidth/2 - 5*CONFIG.TEXT_SIZE, CONFIG.screenHeight/2, CONFIG.TEXT_SIZE, DARKGRAY);
                for(uint8_t i = 0; i < NUM_BUTTONS; i++)
                    drawButton(&menu.buttons[i]);

            }break;
            case(GAMEPLAY):
            {
                ClearBackground(LIGHTGRAY);
                DrawText("Player 1 Score: ", 0, 0, CONFIG.TEXT_SIZE, BLACK);
                snprintf(scoreBuffer, 3, "%u", P1.score);
                DrawText(scoreBuffer, 8*CONFIG.TEXT_SIZE, 0, CONFIG.TEXT_SIZE,BLACK);
                DrawText("Player 2 Score: ", CONFIG.screenWidth - 10*CONFIG.TEXT_SIZE, 0, CONFIG.TEXT_SIZE, BLACK);
                snprintf(scoreBuffer, 3, "%u", P2.score);
                DrawText(scoreBuffer, CONFIG.screenWidth - 50, 0, CONFIG.TEXT_SIZE,BLACK);
                DrawRectangle(P1.position.x, P1.position.y, CONFIG.PADDLE_WIDTH, CONFIG.PADDLE_HEIGHT, BLACK);
                DrawRectangle(P2.position.x, P2.position.y, CONFIG.PADDLE_WIDTH, CONFIG.PADDLE_HEIGHT, BLACK);
                DrawCircle(BALL.position.x, BALL.position.y, CONFIG.BALL_RADIUS, BLACK);
            }break;
            case(ENDCARD):
            {
                if(P1.score == 5)
                    snprintf(congratsBuffer,15, "Player 1 Wins!");
                else
                    snprintf(congratsBuffer,15, "Player 2 Wins!");
                DrawText(congratsBuffer, CONFIG.screenWidth/2 - 50, CONFIG.screenHeight/2, 30, BLACK);
            }break;
        }
        EndDrawing();
    }
    closeGame(&menu);
    CloseWindow();
    return 0;
}