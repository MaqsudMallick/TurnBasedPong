
//#include <windows.h>
void init(Ball*);
void Game(Ball* ball, Rec* player, Rec* opponent)
{
        //Rules
        float shift = (float)screenHeight/steps;
        ball->velocity();
        if(ball->stop){
        if (IsKeyPressed(KEY_UP) && player->rec.y-shift>0) player->rec.y -= shift;
        if (IsKeyPressed(KEY_DOWN) && player->rec.y+shift<screenHeight) player->rec.y += shift;}
        if(ball->center.x>screenHeight) { winnertext = "Opponent wins by default"; }
        else if(ball->center.x<0) winnertext = "You win by default";
        if(ball->center.y>opponent->rec.y+opponent->rec.height && opponent->rec.y+shift<screenHeight) opponent->rec.y +=shift;
        if(ball->center.y<opponent->rec.y && opponent->rec.y-shift>0) opponent->rec.y -=shift;
        if(ball->center.y<=ball->radius) ball->bounceY();
        if(ball->center.y>=screenHeight-ball->radius) ball->bounceY();
        if(frames>100) {sceneno-=2; frames = 0; steps = 5; }
        BeginDrawing(); ClearBackground(RAYWHITE);
        //Background
        for(int i=0; i<steps; i++) {DrawRectangle(screenWidth -20.0f,i*screenHeight/steps+10, 10, screenHeight/steps-20, LIGHTGRAY);
        DrawRectangle(20.0f,i*screenHeight/steps+10, 10, screenHeight/steps-20, LIGHTGRAY);} 
        if(winnertext) { DrawText(winnertext, (screenWidth-MeasureText(winnertext,40))/2, screenHeight/2, 40, LIGHTGRAY);
        frames++; }
        else DrawText("Stage 1", (screenWidth-MeasureText("Stage 1",40))/2, screenHeight/2, 40, LIGHTGRAY);
        //Background
        //Gameobjects Drawings
        DrawRectangleRec(player->rec,MAROON);
        DrawRectangleRec(opponent->rec,MAROON);
        DrawCircleV(ball->center, ball->radius, ball->color); //gameObjects
        DrawLineEx(ball->center, {ball->center.x + 50*ball->temp.x, ball->center.y + 50*ball->temp.y}, 2.0f,YELLOW);
        EndDrawing();
        //Collisions
        if(CheckCollisionCircleRec(ball->center, ball->radius, player->rec)) ball->bounce(player->rec, -1);
        if(CheckCollisionCircleRec(ball->center, ball->radius, opponent->rec) && !ball->stop) {ball->bounce(opponent->rec, 1);}
}

void Menu(int* y, int* c, Ball* ball){
    if(IsKeyPressed(KEY_DOWN) && *c!=2) { *y+= screenHeight/5; (*c)++;}
     if(IsKeyPressed(KEY_UP) && *c!=1) {*y-= screenHeight/5; (*c)--;}
     if(IsKeyPressed(KEY_ENTER)) { sceneno+= *c; init(ball);}
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

void chooseDifficulty(int* lvl, Rec* pl, Rec* op){
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