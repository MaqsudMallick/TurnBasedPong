#include <bits/stdc++.h>
#include "include/raylib.h" 
class Ball{
    Vector2 vel;
    bool plturn;
public:
    Vector2 temp;
    Vector2 center;
    float radius;
    Color color; 
    bool stop;   
    Ball(Vector2 pos,float radius, Color color, int k){
        this->stop = false;
        this->plturn= false;
        this->center = pos;
        this->radius = radius;
        this->color = color;
        this->vel.y = rand()%2-0.5f;
        this->vel.x = (rand()%2-0.5f)*k;
    }
    void velocity(){
        if(IsKeyPressed(KEY_SPACE)) {vel = temp; temp = {0, 0};}
        center.x += vel.x; center.y += vel.y;
        if(vel.x>0 && center.x<=50) {temp = vel; vel = {0, 0};}
    }
    void bounce(Rectangle rec, int k){
        vel.x = -(vel.x);
        vel.y = k*vel.x*(center.y - (rec.y+rec.height/2))/(rec.height/2); 
        // if(k>0) { temp = vel; vel = {0, 0}; plturn= false; stop = true;}
        // if(k<0) plturn = true;
    }
    void bounceY(){
        vel.y = -vel.y;
    }
    void resume(){
        vel = temp;
        this->stop= false;
    }
};
int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 900;
    srand(time(0));
    int steps=5; float shift = (float)screenHeight/steps;
    InitWindow(screenWidth, screenHeight, "Turn Based Pong");
    //Gameobjects
    Ball *ball = new Ball( {(float)screenWidth/2, (float)(rand()%screenHeight)}, 15.0, BLACK, 20);
    Rectangle player; player.x = (float)screenWidth -20.0f; player.y = 10.0f; player.width = 9.0f; player.height = (float)screenHeight/steps-20.0f;
    Rectangle opponent; opponent.x = (float)20.0f; opponent.y = 10.0f; opponent.width = 9.0f; opponent.height = (float)screenHeight/steps-20.0f;
    //Frames
    SetTargetFPS(60);  
    while (!WindowShouldClose()){
        //Rules
        ball->velocity();
        if (IsKeyPressed(KEY_UP) && player.y-shift>0) player.y -= shift;
        if (IsKeyPressed(KEY_DOWN) && player.y+shift<screenHeight) player.y += shift;
       // if(IsKeyPressed(KEY_SPACE)) ball->resume();
        if(ball->center.y>opponent.y+opponent.height && opponent.y+shift<screenHeight) opponent.y +=shift;
        if(ball->center.y<opponent.y && opponent.y-shift>0) opponent.y -=shift;
        if(ball->center.y<=ball->radius) ball->bounceY();
        if(ball->center.y>=screenHeight-ball->radius) ball->bounceY();
        BeginDrawing(); ClearBackground(RAYWHITE);
        //Background
        for(int i=0; i<steps; i++) {DrawRectangle(screenWidth -20.0f,i*screenHeight/steps+10, 10, screenHeight/steps-20, LIGHTGRAY);
        DrawRectangle(20.0f,i*screenHeight/steps+10, 10, screenHeight/steps-20, LIGHTGRAY);} 
        DrawText("Stage 1", screenWidth/2-50, screenHeight/4, 40, LIGHTGRAY);//Background
        //Gameobjects Drawings
        DrawRectangleRec(player,MAROON);
        DrawRectangleRec(opponent,MAROON);
        DrawCircleV(ball->center, ball->radius, ball->color); //gameObjects
        DrawLineEx(ball->center, {ball->center.x + 50*ball->temp.x, ball->center.y + 50*ball->temp.y}, 2.0f,YELLOW);
        EndDrawing();
        //Collisions
        if(CheckCollisionCircleRec(ball->center, ball->radius, player)) ball->bounce(player, -1);
        if(CheckCollisionCircleRec(ball->center, ball->radius, opponent) && !ball->stop) {ball->bounce(opponent, 1);}
    }
    CloseWindow();
    return 0;
}