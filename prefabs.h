class Ball{
    Vector2 vel;
public:
    Vector2 temp;
    Vector2 center;
    float radius;
    Color color; 
    bool stop;   
    Ball(Vector2 pos,float radius, Color color, int k){
        this->stop = false;
        this->center = pos;
        this->radius = radius;
        this->color = color;
        this->vel.y = rand()%2-0.5f;
        this->vel.x = -0.5*k;
    }
    void velocity(){
        if(IsKeyPressed(KEY_SPACE) && vel.x==0 && vel.y==0) {vel = temp; temp = {0, 0}; stop = false;}
        center.x += vel.x; center.y += vel.y;
        if(vel.x>0 && center.x<=50) {temp = vel; vel = {0, 0}; stop= true;}
    }
    void bounce(Rectangle rec, int k){
        vel.x = -(vel.x);
        vel.y = k*vel.x*(center.y - (rec.y+rec.height/2))/(rec.height/2); 
    }
    void bounceY(){
        vel.y = -vel.y;
    }
    void resume(){
        vel = temp;
        this->stop= false;
    }
    void init(Vector2 pos,float radius, Color color, int k){
        this->stop = false;
        this->center = pos;
        this->radius = radius;
        this->color = color;
        this->vel.y = rand()%2-0.5f;
        this->vel.x = -0.5*k;
    }
};
class Rec{
public:
    Rectangle rec;
    Rec(Rectangle rec){this->rec = rec;}
};