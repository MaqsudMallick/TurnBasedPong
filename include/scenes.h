
#include <string>
#include <cstring>
void init(Ball*);
void Game(Ball* ball, Rec* player, Rec* opponent, Sound beep, Sound peep)
{
        //Rules
        float shift = (float)screenHeight/steps;
        ball->velocity();
        if(ball->stop){
        if (IsKeyPressed(KEY_UP) && player->rec.y-shift>0) player->rec.y -= shift;
        if (IsKeyPressed(KEY_DOWN) && player->rec.y+shift<screenHeight) player->rec.y += shift;}
        if(ball->center.x>screenHeight) { PlaySound(peep); winnertext = "Opponent wins"; }
        else if(ball->center.x<0){ winnertext = "You win"; PlaySound(peep); }
        if(ball->center.y>opponent->rec.y+opponent->rec.height && opponent->rec.y+shift<screenHeight) opponent->rec.y +=shift;
        if(ball->center.y<opponent->rec.y && opponent->rec.y-shift>0) opponent->rec.y -=shift;
        if(ball->center.y<=ball->radius) {ball->bounceY(); PlaySound(beep);}
        if(ball->center.y>=screenHeight-ball->radius) {ball->bounceY(); PlaySound(beep); }
        if(frames>100) {sceneno-=2; frames = 0; steps = 5; score= 0; }
        BeginDrawing(); ClearBackground(RAYWHITE);
        //Background
        for(int i=0; i<steps; i++) {DrawRectangle(screenWidth -20.0f,i*screenHeight/steps+10, 10, screenHeight/steps-20, LIGHTGRAY);
        DrawRectangle(20.0f,i*screenHeight/steps+10, 10, screenHeight/steps-20, LIGHTGRAY);} 
        if(winnertext) { DrawText(winnertext, (screenWidth-MeasureText(winnertext,40))/2, screenHeight/2, 40, LIGHTGRAY);
        frames++; }
        else DrawText(to_string(score).c_str(), (screenWidth-MeasureText("1",fontsize*2))/2, screenHeight/2, fontsize*2, LIGHTGRAY);
        //Background
        //Gameobjects Drawings
        DrawRectangleRec(player->rec,MAROON);
        DrawRectangleRec(opponent->rec,MAROON);
        DrawCircleV(ball->center, ball->radius, ball->color); //gameObjects
        DrawLineEx(ball->center, {ball->center.x + 50*ball->temp.x, ball->center.y + 50*ball->temp.y}, 2.0f,YELLOW);
        EndDrawing();
        //Collisions
        if(CheckCollisionCircleRec(ball->center, ball->radius, player->rec)) {ball->bounce(player->rec, -1); score++; PlaySound(beep);}
        if(CheckCollisionCircleRec(ball->center, ball->radius, opponent->rec) && !ball->stop) {ball->bounce(opponent->rec, 1); PlaySound(beep);}
}

void Menu(int* y, int* c, Ball* ball, Sound beep, Sound peep){
    if(IsKeyPressed(KEY_DOWN) && *c!=2) { *y+= screenHeight/5; (*c)++; PlaySound(beep);}
     if(IsKeyPressed(KEY_UP) && *c!=1) {*y-= screenHeight/5; (*c)--; PlaySound(beep);}
     if(IsKeyPressed(KEY_ENTER)) { sceneno+= *c==1?*c:4; init(ball); PlaySound(peep);}
      BeginDrawing();
      ClearBackground(RAYWHITE);
      DrawCircle((screenWidth-MeasureText("Start Game", fontsize))/2-30.0f, *y, ball->radius, ball->color);
      if(*c==1) DrawText("Start Game", (screenWidth-MeasureText("Start Game", fontsize))/2, 2*screenHeight/5, fontsize, DARKGRAY);
      else DrawText("Start Game", (screenWidth-MeasureText("Start Game", fontsize))/2, 2*screenHeight/5, fontsize, LIGHTGRAY);
      if(*c==2) DrawText("How to Play", (screenWidth-MeasureText("How to Play", fontsize))/2, 3*screenHeight/5, fontsize, DARKGRAY); 
      else DrawText("How to Play", (screenWidth-MeasureText("How to Play", fontsize))/2, 3*screenHeight/5, fontsize, LIGHTGRAY);
      EndDrawing();

}
bool inside(int x1, int x2, int y1, int y2){
        return GetMouseX()>=x1 && GetMouseX()<=x2 && GetMouseY()>=y1 && GetMouseY()<=y2;
}

void chooseDifficulty(int* lvl, Rec* pl, Rec* op, Sound peep){
        if( IsMouseButtonDown(MOUSE_BUTTON_LEFT) && inside(screenWidth/2- MeasureText("Difficulty", fontsize)/2,screenWidth/2+MeasureText("Difficulty", fontsize)/2, 3*screenHeight/5-15,3*screenHeight/5+15))
                {
                        *lvl = GetMouseX();
                          }
        BeginDrawing(); ClearBackground(RAYWHITE); DrawText("Difficulty", (screenWidth-MeasureText("Difficulty", fontsize))/2, 2*screenHeight/5, fontsize, DARKGRAY);
        DrawLine(screenWidth/2- MeasureText("Difficulty", fontsize)/2 ,3*screenHeight/5,screenWidth/2+ MeasureText("Difficulty", fontsize)/2 ,3*screenHeight/5, MAROON);
        DrawCircle(*lvl,3*screenHeight/5, 15.0f,  BLACK);
        //winnertext= std::__cxx11::to_string(steps -5);
        //DrawText(winnertext, screenWidth/2- 25.0f, 3.25*screenHeight/5, fontsize, BLACK);
        if(IsKeyPressed(KEY_ENTER) || (inside(screenWidth/2- 50.0f, screenWidth/2+ 150.0f, 3.5*screenHeight/5, 3.5*screenHeight/5+100.0f) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {sceneno++; steps +=(int)10*(*lvl- screenWidth/2+ MeasureText("Difficulty", fontsize)/2)/MeasureText("Difficulty", fontsize);
        printf("Steps value = %d", steps);
        pl->rec = {(float)screenWidth -20.0f, 10.0f, 9.0f, (float)screenHeight/steps-20.0f}; 
        op->rec = {(float)20.0f, 10.0f, 9.0f, (float)screenHeight/steps-20.0f};
        PlaySound(peep);
        }
        //Button Implementation
        if(inside(screenWidth/2- 50.0f, screenWidth/2+ 150.0f, 3.5*screenHeight/5, 3.5*screenHeight/5+100.0f)){
        DrawRectangleRec({screenWidth/2- 50.0f, 3.5*screenHeight/5, 100.0f, 100.0f}, LIGHTGRAY);
        DrawText("OK", screenWidth/2- 25.0f, 3.75*screenHeight/5, fontsize, BLACK);
        }
        else {DrawRectangleRec({screenWidth/2- 50.0f, 3.5*screenHeight/5, 100.0f, 100.0f}, BLACK);
        DrawText("OK", screenWidth/2- 25.0f, 3.75*screenHeight/5, fontsize, WHITE);}
        EndDrawing();
}

void HowtoPlay(Texture2D updown, Texture space){
        if(IsKeyPressed(KEY_ENTER) || (inside(screenWidth/2- 50.0f, screenWidth/2+ 150.0f, 3.5*screenHeight/5, 3.5*screenHeight/5+100.0f) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) sceneno=1;
        BeginDrawing(); ClearBackground(RAYWHITE);
        DrawTexture(updown, updown.width, 2*screenHeight/5 - updown.height/2, WHITE);
        DrawText("Use up/down keys to move paddle when your \nturn/screen freezed",  3*updown.width, 2*screenHeight/5 - updown.height/2, fontsize/2, LIGHTGRAY);
        DrawTexture(space, updown.width, 2.5*screenHeight/5 - space.height/2, WHITE);
        DrawText("Use space to unfreeze/confirm choice", 2*updown.width + space.width, 2.5*screenHeight/5 - space.height/2, fontsize/2 ,LIGHTGRAY);
        if(inside(screenWidth/2- 50.0f, screenWidth/2+ 150.0f, 3.5*screenHeight/5, 3.5*screenHeight/5+100.0f)){
        DrawRectangleRec({screenWidth/2- 50.0f, 3.5*screenHeight/5, 100.0f, 100.0f}, LIGHTGRAY);
        DrawText("OK", screenWidth/2- 25.0f, 3.75*screenHeight/5, fontsize, BLACK);
        }
        else {DrawRectangleRec({screenWidth/2- 50.0f, 3.5*screenHeight/5, 100.0f, 100.0f}, BLACK);
        DrawText("OK", screenWidth/2- 25.0f, 3.75*screenHeight/5, fontsize, WHITE);}



        EndDrawing();
}