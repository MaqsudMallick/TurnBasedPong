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
#include "include/prefabs.h"
#include "include/scenes.h"
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
    InitAudioDevice();
    //Gameobjects
    Ball *ball = new Ball( {(float)screenWidth/2, (float)(rand()%screenHeight)}, 15.0, BLACK, 20);
    Rectangle player; player.x = (float)screenWidth -20.0f; player.y = 10.0f; player.width = 9.0f; player.height = (float)screenHeight/steps-20.0f;
    Rectangle opponent; opponent.x = (float)20.0f; opponent.y = 10.0f; opponent.width = 9.0f; opponent.height = (float)screenHeight/steps-20.0f;
    Rec *pl = new Rec(player);
    Rec *op = new Rec(opponent);
    Texture2D updown = LoadTexture("Textures/updown.png");
    Texture2D space = LoadTexture("Textures/space.png");
    Music music = LoadMusicStream("audio/tutorialmusic.mp3");
    Sound beep = LoadSound("audio/Pop.ogg");
    Sound peep2 = LoadSound("audio/plop2.ogg");
    Sound peep = LoadSound("audio/plop.ogg");
    //Sound plop = LoadSound("audio/Score.ogg");
    PlayMusicStream(music);
    //Frames
    SetTargetFPS(60);  
    while (!WindowShouldClose()){
        // Game(ball, pl, op, steps);
        UpdateMusicStream(music);
        switch(sceneno){
            case 1:  Menu(&y, &c, ball, beep, peep); break;
            case 2: chooseDifficulty(&lvl,pl,op, peep); break;
            case 3:  Game(ball, pl, op, beep, peep2); break;
            default:  HowtoPlay(updown, space); break;
        }
    }
    UnloadMusicStream(music);
    UnloadSound(beep);
    UnloadSound(peep2);
    UnloadSound(peep);
    CloseWindow();
    return 0;
}