#include <bits/stdc++.h>
using namespace std;
#include "include/raylib.h" 
const int screenWidth = 800, screenHeight = 900;
int steps=5;
const char* winnertext = NULL;
int sceneno = 1;
int frames = 0;
int score = 0;
const int fontsize = 40; 
#include "prefabs.h"
#include "scenes.h"
void init(Ball* ball){
    ball->init( {(float)screenWidth/2, (float)(rand()%screenHeight)}, 15.0, BLACK, 20);
    frames = 0;
    winnertext = NULL;
}
int main(void)
{
    
    srand(time(0));
    int y = 2*screenHeight/5 + 15.0f, c=1;
    int lvl = screenWidth/2 - MeasureText("Difficulty", fontsize)/2 -100;
    InitWindow(screenWidth, screenHeight, "Turn Based Pong");
    //Gameobjects
    Ball *ball = new Ball( {(float)screenWidth/2, (float)(rand()%screenHeight)}, 15.0, BLACK, 20);
    Rectangle player; player.x = (float)screenWidth -20.0f; player.y = 10.0f; player.width = 9.0f; player.height = (float)screenHeight/steps-20.0f;
    Rectangle opponent; opponent.x = (float)20.0f; opponent.y = 10.0f; opponent.width = 9.0f; opponent.height = (float)screenHeight/steps-20.0f;
    Rec *pl = new Rec(player);
    Rec *op = new Rec(opponent);
    Texture2D updown = LoadTexture("Textures/updown.png");
    Texture2D space = LoadTexture("Textures/space.png");
    
    //Frames
    SetTargetFPS(60);  
    while (!WindowShouldClose()){
        // Game(ball, pl, op, steps);
        
        switch(sceneno){
            case 1:  Menu(&y, &c, ball); break;
            case 2: chooseDifficulty(&lvl,pl,op); break;
            case 3:  Game(ball, pl, op); break;
            default:  HowtoPlay(updown, space); break;
        }
    }
    CloseWindow();
    return 0;
}