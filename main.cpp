#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include<iostream>
#include<math.h>
#include<ctime>
#include<sys/time.h>


using namespace std;
double canvasWidth=30;
double canvasHeight=25;
//game related variables
boolean gameRunning=true;
boolean cannonFired=false;
double cannonFiringTime=0;
double gameTime=0;
bool win=false;
bool loss=false;
bool eggIsInBasketRegion=false;
bool collidedWithTheChicken=false;
bool fellOnGround=false;
//canon related variables
double canonAngle=15;

double v0=15;
double T=0;
double R=0;
double PI=3.1416;
double g=9.8;
double t=0;
double vx=v0*cos( (canonAngle*PI)/180 );
double vy=v0*sin( (canonAngle*PI)/180 );

//basket related variables
double basketX=15;
double basketY=-15;
double basketPushBackX=12;
//chicken wing related variables
boolean wingWillRise=true;
boolean chickenSwitch=false;
double chickenWingAngle=0;

//chicken leg rotation related variables
double chickenLegAngle=0;
double Sx=0;
double Sy=0;
//chicken flight related variables
boolean chickenWillRise=true;
double chickenHeight=0;
//egg related variables
double eggAngle=0;

//cloud relate variables
double cloudTimer=0;

double cloudPositionX1=-10;
double cloudPositionX2=10;
double cloudPositionX3=25;
double cloudPositionX4=-25;
double cloudPositionX5=10;

//sound related variables
bool hasBeenInWinPart=false;
bool hasBeenInLosePart=false;

void init(){
    eggAngle=canonAngle;
    glOrtho(-canvasWidth,canvasWidth,-canvasHeight,canvasHeight,-canvasWidth,canvasWidth);
    glClearColor(0,0,0,0);
    basketPushBackX=(rand()%13);
    //basketPushBackX=0;

}
void myKeyBoardFunction(unsigned char button,int x,int y){
    switch(button){
        case 'a':
            //Sx-=02;
            if(cannonFired==false){
                    canonAngle+=5;
                if(canonAngle>90){
                    canonAngle=90;
                }
                eggAngle=canonAngle;
                vx=v0*cos( (canonAngle*PI)/180 );
                vy=v0*sin( (canonAngle*PI)/180 );
                glutPostRedisplay();
            }
        break;
        case 'd':
           // Sx+=02;
            if(cannonFired==false){
                canonAngle-=5;
                if(canonAngle<15){
                    canonAngle=15;
                }
                eggAngle=canonAngle;
                vx=v0*cos( (canonAngle*PI)/180 );
                vy=v0*sin( (canonAngle*PI)/180 );
                glutPostRedisplay();
            }
        break;
        case 's':
                //Sy-=2;
                v0=v0-0.2;
                if(v0<=15){
                    v0=15;
                }
                vx=v0*cos( (canonAngle*PI)/180 );
                vy=v0*sin( (canonAngle*PI)/180 );
        break;
        case 'w':
               // Sy+=2;
                v0=v0+0.2;
                if(v0>=30){
                    v0=30;
                }
                vx=v0*cos( (canonAngle*PI)/180 );
                vy=v0*sin( (canonAngle*PI)/180 );
        break;
        case 32://space
                {
                if(cannonFired==false){
                    cannonFired=true;
                    PlaySound("cannonSound.wav",NULL, SND_FILENAME|SND_ASYNC);
                    gameTime=0;
                    glutPostRedisplay();
                }
                }
        break;
        //GAME CONTROL
        case 'r':
                if(gameRunning==false){
                    //sound variable flag control starts
                    hasBeenInWinPart=false;
                    hasBeenInLosePart=false;
                    //sound variable flag control ends
                    //cannon body relate variable reseting starts
                    cannonFired=false;
                    canonAngle=15;
                    eggAngle=canonAngle;
                    //cannon body relate variable reseting ends
                    gameTime=0;
                    //Reseting canon angle starts
                    v0=15;
                    vx=v0*cos( (canonAngle*PI)/180 );
                    vy=v0*sin( (canonAngle*PI)/180 );
                    //Reseting canon angle ends
                    Sx=0;
                    Sy=0;
                    gameRunning=true;
                    collidedWithTheChicken=false;
                    fellOnGround=false;
                    PlaySound("cluckingSound.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);

                    basketPushBackX=(rand()%13);
                }
        break;
        case 'R':
                if(gameRunning==false){
                    //sound variable flag control starts
                    hasBeenInWinPart=false;
                    hasBeenInLosePart=false;
                    //sound variable flag control ends

                    //cannon body relate variable reseting starts
                    cannonFired=false;
                    canonAngle=15;
                    eggAngle=canonAngle;
                    //cannon body relate variable reseting ends
                    gameTime=0;
                    //Reseting canon angle starts
                    v0=15;
                    vx=v0*cos( (canonAngle*PI)/180 );
                    vy=v0*sin( (canonAngle*PI)/180 );
                    //Reseting canon angle ends
                    Sx=0;
                    Sy=0;
                    gameRunning=true;
                    collidedWithTheChicken=false;
                    fellOnGround=false;
                    PlaySound("cluckingSound.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);

                    basketPushBackX=(rand()%13);
                }
        break;

        //TESTING PURPOSE
//        case 'i'://up
//            Sy+=0.2;
//            glutPostRedisplay();
//            PlaySound("winSound.wav",NULL, SND_FILENAME|SND_ASYNC);
//        break;
//        case 'k'://down
//            Sy-=0.2;
//            glutPostRedisplay();
//            PlaySound("loseSound.wav",NULL, SND_FILENAME|SND_ASYNC);
//        break;
//        case 'j'://left
//            Sx-=0.2;
//            glutPostRedisplay();
//        break;
//        case 'l'://right
//            Sx+=0.2;
//            glutPostRedisplay();
//        break;
//        case 'c':
//            chickenSwitch=!chickenSwitch;
        //TESTING PURPOSE

    }
}

void drawEllipse(float a, float b,float colorR,float colorG,float colorB){
    glBegin(GL_POLYGON);
    glColor3f(colorR,colorG,colorB);glVertex3f(-a,0,0);
    for(float x=-a;x<=a;x+=0.005){
        float y=sqrt(1-(x*x)/(a*a))*b;
        glColor3f(colorR,colorG,colorB);glVertex3f(x,y,0);
    }
    for(float x=a;x>=-a;x-=0.005){
        float y=-sqrt(1-(x*x)/(a*a))*b;
        glColor3f(colorR,colorG,colorB);glVertex3f(x,y,0);
    }
    glColor3f(colorR,colorG,colorB);glVertex3f(a,0,0);
    glEnd();
}

void drawHalfEllipse(float a, float b,float colorR,float colorG,float colorB){
    glBegin(GL_POLYGON);
    glColor3f(colorR,colorG,colorB);glVertex3f(-a,0,0);
    for(float x=-a;x<=a;x+=0.005){
        float y=sqrt(1-(x*x)/(a*a))*b;
        glColor3f(colorR,colorG,colorB);glVertex3f(x,y,0);
    }

    glColor3f(colorR,colorG,colorB);glVertex3f(a,0,0);
    glEnd();
}

void drawRectangle(float x1,float y1,float x2,float y2,float colorArray[]){
    glBegin(GL_QUADS);
    glColor3f(colorArray[0],colorArray[1],colorArray[2]);glVertex3f(x1,y1,0);
    glColor3f(colorArray[3],colorArray[4],colorArray[5]);glVertex3f(x1,y2,0);
    glColor3f(colorArray[6],colorArray[7],colorArray[8]);glVertex3f(x2,y2,0);
    glColor3f(colorArray[9],colorArray[10],colorArray[11]);glVertex3f(x2,y1,0);
    glEnd();
}

void drawGrassPatch(){
    float r=0.3;
    glBegin(GL_TRIANGLES);
    glColor3f(0,0.5,0);glVertex3f(0,0,0);
    glColor3f(0,1,0);glVertex3f(0,2-r,0);
    glColor3f(0,0,0);glVertex3f(0.5,0,0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0,0.5,0);glVertex3f(0.5,0,0);
    glColor3f(0,1,0);glVertex3f(0.75,2-r,0);
    glColor3f(0,0.5,0);glVertex3f(1,0,0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0,0.5,0);glVertex3f(0.5+0.5,0,0);
    glColor3f(0,1,0);glVertex3f(0.75+0.5,2-r,0);
    glColor3f(1,1,0);glVertex3f(1+0.5,0,0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0,0.5,0);glVertex3f(1+0.5,0,0);
    glColor3f(0,1,0);glVertex3f(2,2-r,0);
    glColor3f(0,0.5,0);glVertex3f(2,0,0);
    glEnd();

}

void drawHalfEllipse(float a,float b,boolean chickenHouse,boolean canonStand){
    float color1=0;
    float color2=0;
    float color3=0;
    if(chickenHouse){
        color1=0.3;
        color2=0.5;
    }else{
        color1=0.7;
        color2=1;
    }

    if(canonStand){
        color1=0.812;
        color2=0.447;
        color3=0.188;
    }

    glBegin(GL_POLYGON);
    for(float x=-a;x<=a;x+=0.005){
        float y=sqrt(1-(x*x)/(a*a))*b;
        if(canonStand){
            glColor3f(color1,color2,color3);glVertex3f(x,y,0);
        }else{
            if(x<=-a/4){
            glColor3f(color1,color1,color3);glVertex3f(x,y,0);

            }else{
            glColor3f(color2,color2,color3);glVertex3f(x,y,0);
        }
        }
    }
    glColor3f(color2,color2,0);glVertex3f(a,0,0);
    glEnd();

}


void drawCanonStand(){
    glPushMatrix();
    glTranslatef(-15,-12.6,0);

    float canonStandColor[]={0.812, 0.447, 0.188,   0.812, 0.447, 0.188,    0.812, 0.447, 0.188,    0.812, 0.447, 0.188};
    drawRectangle(-0.3,3,0.3,0,canonStandColor);
    glPushMatrix();
    glTranslatef(0,3,0);
    drawHalfEllipse(0.3,1,false,true);
    glPopMatrix();
    //drawRectangle(-10,-10,10,10,canonStandColor);

    glPopMatrix();
}

void drawCannon(){
    float a=1.5;
    float b=3;
    glPushMatrix();
    glTranslatef(-15,-10,0);
    glScalef(0.75,0.75,0.75);
    glRotatef(90+canonAngle,0,0,1);
    //drawing the behind part of the cannon
    glBegin(GL_POLYGON);
    for(float x=-a;x<=a;x+=0.005){
        float y=sqrt(1-(x*x)/(a*a))*b;
        glColor3f(0.2,0.2,0.2);glVertex3f(x,y,0);

    }
    glColor3f(0,0,0);glVertex3f(a,0,0);
    glEnd();

    //drawing the middle part of the cannon
    glBegin(GL_QUADS);
    glColor3f(0.1,0.1,0.1);glVertex3f(-a,0,0);
    glColor3f(0.1,0.1,0.1);glVertex3f(-a+0.25,-a-2,0);
    glColor3f(0.7,0.7,0.7);glVertex3f(a-0.25,-a-2,0);
    glColor3f(0.7,0.7,0.7);glVertex3f(a,0,0);
    glEnd();

    //drawing the mouth of the cannon
    glBegin(GL_QUADS);
    glColor3f(0.1,0.1,0.1);glVertex3f(-a+0.25,-a-2,0);
    glColor3f(0.7,0.7,0.7);glVertex3f(-a+0.25,-a-3,0);
    glColor3f(0.7,0.7,0.7);glVertex3f(+a-0.25,-a-3,0);
    glColor3f(0.7,0.7,0.7);glVertex3f(+a-0.25,-a-2,0);
    glEnd();

    glPopMatrix();

}

void drawCannonBase(){

    glPushMatrix();
    glTranslatef(-15,-12,0);

    float canonBaseColor[]={0.2,0.2,0.2,    0,0,0,   0.7,0.7,0.7,   1,1,1};
    drawRectangle(-3,0,3,-2-3,canonBaseColor);
    drawEllipse(3,1,0.5,0.5,0.5);

    //drawing canon base grass
    glPushMatrix();
    glTranslatef(1,-2-3,0);
    drawGrassPatch();
    glPopMatrix();
    //drawing canon base grass
    glPushMatrix();
    glTranslatef(-4.0,-2-3,0);
    drawGrassPatch();
    glPopMatrix();

    //drawing canon base grass
    glPushMatrix();
    glTranslatef(-3.0,-2-3,0);
    drawGrassPatch();
    glPopMatrix();

    glPopMatrix();
}

void drawEggBasket(){
    glPushMatrix();
    glTranslatef(basketX+7 -(basketPushBackX),basketY-1,0);
    glScalef(3.3 ,1.3,1.3);
    glBegin(GL_QUADS);
    glColor3f(1,0.1,0);glVertex3f(-1.25,0,0);
    glColor3f(1,0.1,0);glVertex3f(-0.5,-2.5,0);
    glColor3f(0.8,0.1,0);glVertex3f(0.5,-2.5,0);
    glColor3f(1,1,0);glVertex3f(1.25,0,0);
    glEnd();

    drawEllipse(1.25,1,0.961, 0.808, 0.039);
    drawEllipse(1.0,0.40,1.761, 0.608, 0.039);
    glPopMatrix();
}
void drawEggBasketWithEgg(){
    glPushMatrix();
    glTranslatef(basketX+7-(basketPushBackX),basketY-1,0);
    glScalef(3.3 ,1.3,1.3);
    glBegin(GL_QUADS);
    glColor3f(1,0.1,0);glVertex3f(-1.25,0,0);
    glColor3f(1,0.1,0);glVertex3f(-0.5,-2.5,0);
    glColor3f(0.8,0.1,0);glVertex3f(0.5,-2.5,0);
    glColor3f(1,1,0);glVertex3f(1.25,0,0);
    glEnd();

    drawEllipse(1.25,1,0.961, 0.808, 0.039);
    drawEllipse(1.0,0.40,1.761, 0.608, 0.039);
    glPushMatrix();
    glTranslatef(0.2,0.2,0);
    glRotatef(90+45,0,0,1);
    drawEllipse(0.5,0.4,    1,1,1);
    glPopMatrix();
    glPopMatrix();
}


void drawFeather(float colorR,float colorG, float colorB){
    glPushMatrix();
    glScalef(0.2,0.2,0.2);
    glPushMatrix();
    glRotatef(180,0,0,1);
    drawHalfEllipse(3,3,    colorR,colorG,colorB);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0.5,0);
    drawEllipse(1,1,        colorR,colorG,colorB);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5,0.75,0);
    drawEllipse(1,1,        colorR,colorG,colorB);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5,0.75,0);
    drawEllipse(1,1,        colorR,colorG,colorB);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,0,0);
    drawEllipse(2,1,        colorR,colorG,colorB);
    glPopMatrix();
    glPopMatrix();
}

void drawChickenFeet(){
    //Making the ankle structure
    glPushMatrix();
    //glScalef(3,3,3);
    glTranslatef(-0.50,1,0);
    float feetAnkleColor[]={1,1,0,   1,1,0,     1,1,0,      1,1,0};
    drawRectangle(-1,-1,1,1,feetAnkleColor);

    glPopMatrix();
    //Making the ankle structure


    //Making the feet structure
    glPushMatrix();
    glRotatef(190,0,0,1);
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glColor3f(1,1,0);glVertex3f(0,0,0);
    glColor3f(1,1,0);glVertex3f(10,0,0);
    glColor3f(1,1,0);glVertex3f(3.5,-1,0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(1,1,0);glVertex3f(5,0,0);
    glColor3f(1,1,0);glVertex3f(12,-2,0);
    glColor3f(1,1,0);glVertex3f(3.5,-1,0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(1,1,0);glVertex3f(5,0,0);
    glColor3f(1,1,0);glVertex3f(0,0,0);
    glColor3f(1,1,0);glVertex3f(8,-3,0);
    glEnd();
    glPopMatrix();
    glPopMatrix();

}

void drawWing(){
        //Chicken Wing Base ends


    //Chicken wing starts
    //starting push matrix for wing
    glPushMatrix();
    glTranslatef(4.3,-3.8,0);
    glRotatef(chickenWingAngle,0,0,1);
    //starting push matrix for wing

    //outer wing starts
    glPushMatrix();
    glRotatef(180,0,0,1);
    drawHalfEllipse(3,3,   0.878, 0.792, 0.616);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0.5,0);
    drawEllipse(1,1,     0.878, 0.792, 0.616);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5,0.75,0);
    drawEllipse(1,1,    0.878, 0.792, 0.616);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5,0.75,0);
    drawEllipse(1,1,    0.878, 0.792, 0.616);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,0,0);
    drawEllipse(2,1,    0.878, 0.792, 0.616);
    glPopMatrix();
    //outer wing ends

    //inner feathers starts
    glPushMatrix();glTranslatef(1,1,0);drawFeather(0.588, 0.506, 0.329);glPopMatrix();
    glPushMatrix();glTranslatef(0,0,0);drawFeather(0.588, 0.506, 0.329);glPopMatrix();
    glPushMatrix();glTranslatef(-1,-1,0);drawFeather(0.588, 0.506, 0.329);glPopMatrix();
    glPushMatrix();glTranslatef(-1,1,0);drawFeather(0.588, 0.506, 0.329);glPopMatrix();
    glPushMatrix();glTranslatef(-1,0,0);drawFeather(0.588, 0.506, 0.329);glPopMatrix();
    glPushMatrix();glTranslatef(-1,0,0);drawFeather(0.588, 0.506, 0.329);glPopMatrix();
    glPushMatrix();glTranslatef(1,0,0);drawFeather(0.588, 0.506, 0.329);glPopMatrix();
    glPushMatrix();glTranslatef(2.5,0,0);drawFeather(0.588, 0.506, 0.329);glPopMatrix();
    glPushMatrix();glTranslatef(3,1.5,0);drawFeather(0.588, 0.506, 0.329);glPopMatrix();
    glPushMatrix();glTranslatef(3.2,0.5,0);drawFeather(0.588, 0.506, 0.329);glPopMatrix();
    glPushMatrix();glTranslatef(-1,-1,0);drawFeather(0.588, 0.506, 0.329);glPopMatrix();
    glPushMatrix();glTranslatef(-0.5,-1.9,0);drawFeather(0.588, 0.506, 0.329);glPopMatrix();
    glPushMatrix();glTranslatef(1,-1.9,0);drawFeather(0.588, 0.506, 0.329);glPopMatrix();
    glPushMatrix();glTranslatef(1.5,-1.4,0);drawFeather(0.588, 0.506, 0.329);glPopMatrix();
    glPushMatrix();glTranslatef(-2,0,0);drawFeather(0.588, 0.506, 0.329);glPopMatrix();
    //inner feathers end
    glPopMatrix();
}

void drawChicken(){


    //STARTING TRANSFORM CODE
    glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(0,chickenHeight-7,0);
    //STARTING TRANSFORM CODE

    //chicken wing2 starts
    glPushMatrix();
    glScalef(0.5,1,1);
    glTranslatef(2,0.5,0);
    drawWing();
    glPopMatrix();
    //chicken wing 2 ends

    //Chicken Throat Starts
    glPushMatrix();
    glTranslatef(-0.5,-1,0);
    glRotatef(23,0,0,1);
    glBegin(GL_QUADS);
    glColor3f(0.9,0.9,0.9);glVertex3f(0,0,0);
    glColor3f(0.9,0.9,0.9);glVertex3f(-0.25,-4,0);
    glColor3f(0.9,0.9,0.9);glVertex3f(2.50,-4,0);
    glColor3f(0.9,0.9,0.9);glVertex3f(1.5,0,0);
    glEnd();
    glPopMatrix();
    //Chicken Throat Ends


    //Chicken Head  Starts
    //chicken head base
    glPushMatrix();
    glScalef(0.10,0.10,0.10);
    glTranslatef(0.5,-6,0);
    drawEllipse(7,10,       0.9,0.9,0.9);
    glPushMatrix();
    glTranslatef(-6,0,0);
    drawEllipse(1.5,3,0,0,0);
    drawEllipse(1,2,1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1,0,0);
    drawEllipse(1.5,3,0,0,0);
    drawEllipse(1,2,1,1,1);
    glPopMatrix();
    //chicken Beak
    glPushMatrix();
    glRotatef(90,0,0,1);
    glScalef(2,0.75,1);
    glTranslatef(-3,1,0);
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0.6, 0);glVertex3f(0,0,0);
    glColor3f(1, 0.6, 0);glVertex3f(4,0,0);
    glColor3f(1, 0.6, 0);glVertex3f(0,13,0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.8, 0.3, 0);glVertex3f(0,8,0);
    glColor3f(0.8, 0.3, 0);glVertex3f(0,0,0);
    glColor3f(0.8, 0.3, 0);glVertex3f(-2,0,0);
    glEnd();
    glPopMatrix();
    //chicken cap
    glPushMatrix();
    glTranslatef(-3,6,0);
    glRotatef(-10,0,0,1);
    glBegin(GL_POLYGON);

    glColor3f(1, 0, 0);glVertex3f(5,6,0);
    glColor3f(0.4, 0, 0);glVertex3f(2,10,0);
    glColor3f(0.6, 0, 0);glVertex3f(0,6,0);
    glColor3f(0.8, 0, 0);glVertex3f(-4,10,0);
    glColor3f(0.4, 0.2, 0);glVertex3f(-2,0,0);
    glColor3f(1, 0, 0);glVertex3f(2,0.5,0);
    glColor3f(1, 0, 0);glVertex3f(6,0,0);
    glColor3f(1, 0, 0);glVertex3f(8,10,0);
    glEnd();
    glPopMatrix();
    glPopMatrix();
    //Chicken Head Ends

    //Chicken body ellipse starts
    glPushMatrix();
    glTranslatef(3.5,-5,0);
    glRotatef(-60,0,0,1);
    drawEllipse(3.5,3,0.9,0.9,0.9);
    glPopMatrix();
    //Chicken body ellipse ends

    //Chicken tail starts
    //tail part 1
    glPushMatrix();
    glTranslatef(5.8,-5,0);
    glRotated(-45,0,1,0);

    drawEllipse(1.5,2,0.9,0.9,0.9);
    glBegin(GL_TRIANGLES);
    glColor3f(0.9,0.9,0.9);glVertex3f(1.5,4,0);
    glColor3f(0.9,0.9,0.9);glVertex3f(1.5,0,0);
    glColor3f(0.9,0.9,0.9);glVertex3f(-2,0,0);
    glEnd();
    glPopMatrix();
    //tail part 2
    glPushMatrix();
    glTranslatef(6.8,-5,0);
    glRotated(-45,0,1,0);

    drawEllipse(1.5,2,0.9,0.9,0.9);
    glBegin(GL_TRIANGLES);
    glColor3f(0.9,0.9,0.9);glVertex3f(1.5,4,0);
    glColor3f(0.9,0.9,0.9);glVertex3f(1.5,0,0);
    glColor3f(0.9,0.9,0.9);glVertex3f(-2,0,0);
    glEnd();
    glPopMatrix();
    //Chicken tail ends

    //Chicken Wing Base starts
    glPushMatrix();
    glTranslatef(2,-4.5,0);
    drawEllipse(1,1,     0.878, 0.792, 0.616);
    //drawEllipse(1,1,     0, 0,0);
    glPopMatrix();

    //chicken wing1 starts
    drawWing();
    //chicken wing 1 ends



    //*************************************CHICKEN LEGS START***************************************//
    glPushMatrix();
    //glRotatef(90,0,0,1);
    //Chicken Leg starts
    //the leg stand starts
    glPushMatrix();
    glTranslatef(4,-7,0);
    glScalef(0.25,0.5,1);
    glRotatef(chickenLegAngle,0,0,1);
    //the chicken feet base starts
    glPushMatrix();
    glTranslatef(0.5,-7,0);
    drawChickenFeet();
    glPopMatrix();
    //the chicken feet base ends

    glBegin(GL_QUADS);
    glColor3f(0.9,0.9,0.9);glVertex3f(-3,0,0);
    glColor3f(0.9,0.9,0.9);glVertex3f(-1.0,-6,0);
    glColor3f(0.9,0.9,0.9);glVertex3f(1.0,-6,0);
    glColor3f(0.9,0.9,0.9);glVertex3f(3,0,0);
    glEnd();
    //the leg stand ends

    glPopMatrix();
    //Chicken Leg ends


    //Chicken Leg starts(PART2)
    //the leg stand starts
    glPushMatrix();
    glTranslatef(2.5,-6,0);
    glScalef(0.25,0.5,1);
    glRotatef(chickenLegAngle,0,0,1);
    //the chicken feet base starts
    glPushMatrix();
    glTranslatef(0.5,-7,0);
    drawChickenFeet();
    glPopMatrix();
    //the chicken feet base ends

    glBegin(GL_QUADS);
    glColor3f(0.9,0.9,0.9);glVertex3f(-2,-2,0);
    glColor3f(0.9,0.9,0.9);glVertex3f(-1.0,-6,0);
    glColor3f(0.9,0.9,0.9);glVertex3f(1.0,-6,0);
    glColor3f(0.9,0.9,0.9);glVertex3f(3,-2,0);
    glEnd();
    //the leg stand ends

    glPopMatrix();
    //Chicken Leg ends (PART 2)
    glPopMatrix();
    //*************************************CHICKEN LEGS END***************************************//



    //ending pop matrix for wing
    glPopMatrix();
    //ending pop matrix for wing

    //Chicken wing ends

    //ENDING TRANSFORM CODE
     glPopMatrix();
    //ENDING TRANSFORM CODE


}


void drawCharacter(char ch,float R,float G,float B)
{
  glPushMatrix();


  glColor3f(R,G,B);
  glTranslatef(-10,-10,0);
  glScalef(0.025,0.025,0.025);

  glutStrokeCharacter(GLUT_STROKE_ROMAN, ch);

  glPopMatrix();
}

void printWord(char  charArray[],int length ,float R,float G,float B){
    float x=0;

    for(int cNo=0;cNo<length;cNo++){

            glPushMatrix();
            glTranslatef(x,0,0);
            drawCharacter(charArray[cNo]    ,R,G,B);
            glPopMatrix();
            x=x+2.5;
    }

}

void printWinningMessage(){
    glPushMatrix();
    //*******************************
    glTranslatef(1,0,0);
    glPushMatrix();
    glTranslatef(-10,25,0);
    char Congratulations[]={'C','o','n','g','r','a','t','u','l','a','t','i','o','n','s','!'};
    printWord(Congratulations,16,1,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3,20,0);
    char You[]={'Y','o','u'};
    printWord(You,3,1,0.5,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,15,0);
    char Earned[]={'E','a','r','n','e','d'};
    printWord(Earned,6,1,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2,10,0);
    char Your[]={'Y','o','u','r'};
    printWord(Your,4,1,0,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4,5,0);
    char Breakfast[]={'B','r','e','a','k','f','a','s','t'};
    printWord(Breakfast,9,1,1,0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15,0,0);
    char replay[]={'P','r','e','s','s',' ','R',' ','t','o',' ','p','l','a','y',' ','a','g','a','i','n'};
    printWord(replay,21,    0,0,1);
    glPopMatrix();
    //*******************************
    glPopMatrix();


}


void printLosingMessageChicken(){
    char losingMessage1[]={'S','o','r','r','y',' ','Y','o','u',' ', 'C','o','u','l','d',' ','N','o','t'};
    char losingMessage2[]={'G','e','t',' ', 'T','h', 'e', ' ','E','g','g',' ','F','r','o','m'};
    char losingMessage3[]={'T','h','e',' ','C','h','i','c','k','e','n'};
    glPushMatrix();
    glTranslatef(-10,15,0);
    printWord(losingMessage1,19, 1,0,0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-8,10,0);
    printWord(losingMessage2,16, 1,0.5,0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-2,5,0);
    printWord(losingMessage3,11, 1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15,0,0);
    char replay[]={'P','r','e','s','s',' ','R',' ','t','o',' ','p','l','a','y',' ','a','g','a','i','n'};
    printWord(replay,21,    0,0,1);
    glPopMatrix();

}

void printLosingMessageGround(){
    char losingMessage1[]={'T','h','e',' ','E','g','g',' ','F','e','l','l',' ','O','n'};
    char losingMessage2[]={'T','h','e',' ','G','r','o','u','n','d'};

    glPushMatrix();
    glTranslatef(-10,15,0);
    printWord(losingMessage1,15, 0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2,10,0);
    printWord(losingMessage2,10, 1,0.5,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15,0,0);
    char replay[]={'P','r','e','s','s',' ','R',' ','t','o',' ','p','l','a','y',' ','a','g','a','i','n'};
    printWord(replay,21,    0,0,1);
    glPopMatrix();

}

//CLOUD RELATED FUNCTIONS START
void drawClouds(){

    glPushMatrix();
    glTranslatef(0,0,0);
    //**************************ALL CLOUDS START********************//


    //cloud 1 starts

    glPushMatrix();

    glTranslatef(cloudPositionX1,12,0);
    //**********************
    glPushMatrix();
    drawEllipse(4,2,0.99,0.99,0.99);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(3,0,0);
    drawEllipse(3.5,2,0.99,0.99,0.99);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(01,2,0);
    drawEllipse(3.5,2,0.99,0.99,0.99);
    glPopMatrix();
    //**********************
    glPopMatrix();
    //cloud 1 ends


    //cloud 2 starts
    glPushMatrix();

    glTranslatef(cloudPositionX2,5,0);
    glScalef(0.6,0.6,0.6);
    //**********************
    glPushMatrix();
    drawEllipse(5,4,0.99,0.99,0.99);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(3,0,0);
    drawEllipse(5.5,2,0.99,0.99,0.99);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-6,3,0);
    drawEllipse(4,3,0.99,0.99,0.99);
    glPopMatrix();
    //**********************
    glPopMatrix();
    //cloud 2 ends


    //cloud 3 starts
    glPushMatrix();

    glTranslatef(cloudPositionX3,15,0);
    glScalef(0.8,0.8,0.8);
    //**********************

    glPushMatrix();
    glTranslatef(3,0,0);
    drawEllipse(5.5,4,0.99,0.99,0.99);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(5,3,0);
    drawEllipse(3,3,0.99,0.99,0.99);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1,-3,0);
    drawEllipse(4,3,0.99,0.99,0.99);
    glPopMatrix();
    //**********************
    glPopMatrix();
    //cloud 3 ends


    //cloud 4 starts
    glPushMatrix();

    glTranslatef(cloudPositionX4,15,0);
    glScalef(0.8,0.8,0.8);
    //**********************
    glPushMatrix();
    glTranslatef(3,0,0);
    drawEllipse(10,4,0.99,0.99,0.99);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(5,3,0);
    drawEllipse(3,3,0.99,0.99,0.99);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1,-3,0);
    drawEllipse(4,3,0.99,0.99,0.99);
    glPopMatrix();
    //**********************
    glPopMatrix();
    //cloud 4 ends


    //cloud 5 starts
    glPushMatrix();

    glTranslatef(cloudPositionX5,22,0);
    glScalef(0.8,0.8,0.8);
    //**********************

    glPushMatrix();
    glTranslatef(3,0,0);
    drawEllipse(5.5,4,0.99,0.99,0.99);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(5,3,0);
    drawEllipse(3,3,0.99,0.99,0.99);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1,-3,0);
    drawEllipse(4,3,0.99,0.99,0.99);
    glPopMatrix();
    //**********************
    glPopMatrix();
    //cloud 5 ends

    //**************************ALL CLOUDS END********************//
    glPopMatrix();
}

//CLOUD RELATED FUNCTIONS END

//TREE RELATED FUNCTIONS START


void drawBranch(int currentLevel,float width,float height){
    if(currentLevel==0){
        return;
    }
    //main branch starts

    if(currentLevel==1||currentLevel==2){
        float colorArray[]={ 0.5,0.5,0,  1,1,0,   0.5,1,0,  0.5,1,0.3};
        glPushMatrix();
        drawRectangle(0-width/2,height,0+width/2,0,     colorArray );
        glPopMatrix();
    }else{
        float colorArray[]={ 0.678, 0.494, 0.016,   0.678, 0.494, 0.016,
        0.678, 0.494, 0.016,    0.678, 0.494, 0.016};
        glPushMatrix();
        drawRectangle(0-width/2,height,0+width/2,0,     colorArray );
        glPopMatrix();
    }

    //main branch ends

    //sub branches
    if(currentLevel==3 || currentLevel==2){
                //Drawing rotating branch 1
                glPushMatrix();
                glTranslatef(0,height,0);
                glRotatef(30,0,0,1);
                drawBranch(currentLevel-1,width*0.8,height*0.8);
                glPopMatrix();
                //Drawing rotating branch 2
                glPushMatrix();
                glTranslatef(0,height,0);
                glRotatef(-30,0,0,1);
                drawBranch(currentLevel-1,width*0.8,height*0.8);
                glPopMatrix();


                //Drawing rotating branch 3
                glPushMatrix();
                glTranslatef(0,height,0);
                glRotatef(45,0,0,1);
                drawBranch(currentLevel-1,width*0.8,height*0.8);
                glPopMatrix();
                //Drawing rotating branch 4
                glPushMatrix();
                glTranslatef(0,height,0);
                glRotatef(-45,0,0,1);
                drawBranch(currentLevel-1,width*0.8,height*0.8);
                glPopMatrix();

                //Drawing rotating branch 5
                glPushMatrix();
                glTranslatef(0,height,0);
                glRotatef(0,0,0,1);
                drawBranch(currentLevel-1,width*0.8,height*0.8);
                glPopMatrix();

    }else{
        //Drawing rotating branch 1
        glPushMatrix();
        glTranslatef(0,height,0);
        glRotatef(30,0,0,1);
        drawBranch(currentLevel-1,width*0.8,height*0.8);
        glPopMatrix();
        //Drawing rotating branch 2
        glPushMatrix();
        glTranslatef(0,height,0);
        glRotatef(-30,0,0,1);
        drawBranch(currentLevel-1,width*0.8,height*0.8);
        glPopMatrix();
    }



}

void drawTree(int totalLevels,float width,float height){
    drawBranch(totalLevels,width,height);
}

void drawForest(){
    float treeX=-10;

    glPushMatrix();
    glTranslatef(treeX,0,0);
    drawTree(10,1,5);
    glPopMatrix();

//    treeX=20;
//    glPushMatrix();

//    glTranslatef(treeX,0,0);
//    drawTree(8,1.0,7.5);
//   glPopMatrix();

}

//TREE RELATED FUNCTIONS END

void drawBushes(){
    glPushMatrix();
    glTranslatef(0,-1,0);
    int y=0;
    for (int x=-30;x<=30;x+=5){
            y=((y+2)%6)+1;
            float yFloat=y*0.3;


            glPushMatrix();
            glTranslatef(x,1,0);
            drawHalfEllipse(3,yFloat,    0,0.4,0);
            glPopMatrix();


    }

    glPopMatrix();
}

void drawWindows(){


    //Drawing the first window starts
    glPushMatrix();
    glTranslatef(-3.5,-2,0);
    glScalef(0.7,1,1);
    glBegin(GL_QUADS);
    glColor3f(0, 0,0);glVertex3f(-1.1,1.1,0);
    glColor3f(0, 0,0);glVertex3f(-1.1,-1.1,0);
    glColor3f(0, 0,0);glVertex3f(1.1,-1.1,0);
    glColor3f(0, 0,0);glVertex3f(1.1,1.1,0);
    glEnd();
    glPopMatrix();
    //************************************
    glPushMatrix();
    glTranslatef(-3.5,-2,0);
    glScalef(0.7,1,1);
    glBegin(GL_QUADS);
    glColor3f(0.671, 0.294, 0.235);glVertex3f(-1.0,1.0,0);
    glColor3f(0.671, 0.294, 0.235);glVertex3f(-1.0,-1.0,0);
    glColor3f(0.671, 0.294, 0.235);glVertex3f(1.0,-1.0,0);
    glColor3f(0.671, 0.294, 0.235);glVertex3f(1.0,1.0,0);
    glEnd();
    glPopMatrix();
    //Drawing the first window ends

    //Drawing the second window starts
    glPushMatrix();
    glTranslatef(3.3,-2,0);
    glScalef(0.7,1,1);
    glBegin(GL_QUADS);
    glColor3f(0, 0,0);glVertex3f(-1.1,1.1,0);
    glColor3f(0, 0,0);glVertex3f(-1.1,-1.1,0);
    glColor3f(0, 0,0);glVertex3f(1.1,-1.1,0);
    glColor3f(0, 0,0);glVertex3f(1.1,1.1,0);
    glEnd();
    glPopMatrix();
    //*********************************************
    glPushMatrix();
    glTranslatef(3.3,-2,0);
    glScalef(0.7,1,1);
    glBegin(GL_QUADS);
    glColor3f(0.671, 0.294, 0.235);glVertex3f(-1.0,1.0,0);
    glColor3f(0.671, 0.294, 0.235);glVertex3f(-1.0,-1.0,0);
    glColor3f(0.671, 0.294, 0.235);glVertex3f(1.0,-1.0,0);
    glColor3f(0.671, 0.294, 0.235);glVertex3f(1.0,1.0,0);
    glEnd();
    glPopMatrix();
    //Drawing the second window starts

}


void myDisplay(){




    glClear(GL_COLOR_BUFFER_BIT);
    //STATIC DRAWINGS START
    //Drawing the field
    float colorArray[]={ 0.5,0.5,0,  1,1,0,   0.5,1,0,  0.5,1,0.3};
    drawRectangle(-canvasWidth,0,canvasWidth,-canvasWidth,colorArray );
    //drawing the sky
    float colorArray2[]={ 0.5,0.5,1,  0,0,1,   0,0,1,  1,1,1};
    drawRectangle(-canvasWidth,canvasWidth,canvasWidth,0,colorArray2 );
//    cout<<"********************CLOUDS DATA BEGINS******************\n";
//    cout<<"cloud1X1:"<<cloudPositionX1<<endl;
//    cout<<"cloud2X:"<<cloudPositionX2<<endl;
//    cout<<"cloud3X:"<<cloudPositionX3<<endl;
//    cout<<"cloud4X:"<<cloudPositionX4<<endl;
//    cout<<"cloud5X:"<<cloudPositionX5<<endl;
//    cout<<"********************CLOUDS DATA ENDS******************";
    cloudPositionX1=cloudPositionX1+0.02;
    if(cloudPositionX1>=34){
        cloudPositionX1=-34;
    }
    cloudPositionX2=cloudPositionX2+0.02;
    if(cloudPositionX2>=36){
        cloudPositionX2=-34;
    }
    cloudPositionX3=cloudPositionX3+0.02;
    if(cloudPositionX3>=34){
        cloudPositionX3=-36;
    }
    cloudPositionX4=cloudPositionX4+0.02;
    if(cloudPositionX4>35){
        cloudPositionX4=-36;
    }
    cloudPositionX5=cloudPositionX5+0.02;
    if(cloudPositionX5>=36){
        cloudPositionX5=-36;
    }
    drawClouds();
    //drawing and controlling the clouds end

    //Drawing the trees start
    drawForest();
    //Drawing the trees ends

    //*****************************FINISHING TOUCH STARTS 1***********************//
    drawBushes();
    //*****************************FINISHING TOUCH ENDS 1***********************//

    //drawing the haystack
    glPushMatrix();
    glScalef(1.5,1,1);
    glTranslatef(12,0,0);
    drawHalfEllipse(4,10,false,false);
    glPopMatrix();


    //drawing the grass oatches
    for(int x=-canvasWidth;x<=canvasWidth;x+=7){
            for(int y=0;y>=-20;y-=5){

                glPushMatrix();
                glTranslatef(x,y,0);
                drawGrassPatch();
                glPopMatrix();
            }
    }



    //Drawing the chicken house
    glPushMatrix();
    glTranslatef(-15,5.5,0);
    glScalef(1.2,1.2,1.2);
    //chicken house roof
    drawHalfEllipse(6,2,true,false);
    //chicken house body
    float colorArrayHouseBody[]={ 1-0.10,0.9921-0.10,0.8157-0.10,  1-0.30,0.9921-0.30,0.8157-0.30,   1-0.10,0.9921-0.10,0.8157-0.10,  1,1,1};
    drawRectangle(-5.5,0,5.5,-5.5 ,colorArrayHouseBody);
    //chicken house door
    float colorArrayHouseDoor[]={0.671, 0.294, 0.235,0.671, 0.294, 0.235,0.671, 0.294, 0.235,0.671, 0.294, 0.235 };
    drawRectangle(-1,-1.75,1,-5.5 ,colorArrayHouseDoor);
    //chicken house base
    float colorArrayHouseBase[]={0.729, 0.588, 0.196,   0.729, 0.588, 0.196,    0.729, 0.588, 0.196,    0.729, 0.588, 0.196};
    drawRectangle(-5.5,-5.5,5.5,-6.0 ,colorArrayHouseBase);
    //Drawing the windows
    drawWindows();
    //Drawing the chicken house ends

    glPopMatrix();

    //STATIC DRAWINGS END

    //DYNAMIC CODE STARTS


    //drawing the egg basket starts
    glPushMatrix();
    glTranslatef(2,0,0);
    drawEggBasket();
    glPopMatrix();
    //drawing the egg basket ends

    //drawing the chicken starts
    drawChicken();
    //drawing the chicken ends

    //drawing the egg starts
    glPushMatrix();
    glTranslatef(-23+Sx,-11.75+Sy,0);
    glScalef(0.75,0.75,0.75);
    glRotatef(eggAngle,0,0,1);
    drawEllipse(1.75,1.4,1,1,1);
    glPopMatrix();
    //drawing the egg ends


    //drawing the cannon starts
    glPushMatrix();
    glTranslatef(-5,0,0);
    glScalef(1.2,1.2,1.2);
    drawCannonBase();
    drawCannon();
    drawCanonStand();
    glPopMatrix();
    //drawing the cannon ends



    //drawing the velocity bar starts
    glPushMatrix();
    glScalef(1,3,1);
    glTranslatef(-29,-3,0);
    float velocityBarBackGroundColor[]={0,0,0,  0,0,0,  0,0,0,  0,0,0};
    drawRectangle(0-0.25,10+0.25,2+0.25,0-0.25,velocityBarBackGroundColor);
    float velocityBarColor[]={1,0,0,  1,0,0,  1,0,0,  1,0,0};
    drawRectangle(0,v0/3-3,2,0,velocityBarColor);
    glPopMatrix();
    //drawing the velocity bar ends

    //DYNAMIC CODE ENDS
   // glPushMatrix();
    glLineWidth(8);//for the message letter lines
   // glBegin(GL_LINES);
   // glColor3f(1,0,0);glVertex3f(-25,-17,0);
    //glColor3f(0,1,0);glVertex3f(15,-17,0);
   // glEnd();
    //glPopMatrix();

    //*********************************CONTROLLING CODE STARTS**************************************//
    if(gameRunning){
        //Technical and Physics code starts
        gameTime+=0.073;
        if(cannonFired){

            Sx=vx*gameTime;
            Sy=vy*gameTime-0.5*g*pow(gameTime,2);
            if(Sy<=-5.6){

                gameRunning=false;
                win=false;
                loss=true;
                fellOnGround=true;
            }

        }
        T= (2*v0*sin( (PI*canonAngle)/180 ) )/g;
        R= ((v0*v0)*sin( (2*PI*canonAngle)/180 ))/g;

        //flap wings code starts
        if(wingWillRise){
            chickenWingAngle+=7;
            if(chickenWingAngle>=30){
                wingWillRise=false;
            }
        }else{
            chickenWingAngle-=7;
            if(chickenWingAngle<=0){
                wingWillRise=true;
            }
        }
        //flap wings code ends

        //chicken flight code starts

                if(chickenWillRise){
                   //controlling leg rotation
                   chickenLegAngle-=0.5;
                   if(chickenLegAngle<=-20){
                        chickenLegAngle=-20;
                   }
                   //controlling height
                   chickenHeight+=0.9;
                   if(chickenHeight>=25){
                        chickenWillRise=false;
                   }
                }else{
                   //controlling leg rotation
                   chickenLegAngle+=0.5;
                   if(chickenLegAngle>=00){
                        chickenLegAngle=0;
                   }
                   //controlling height
                   chickenHeight-=0.9;
                   if(chickenHeight<=0){
                        chickenWillRise=true;
                   }
                }

        //chicken flight code ends

        //CHICKEN EGG COLLISION CONTROL STARTS
        if( (Sy-chickenHeight)>=-5 && (Sy-chickenHeight)<-3){
            if(Sx>=25.2 && Sx<=27){
                gameRunning=false;
                win=false;
                loss=true;
                collidedWithTheChicken=true;

            }
        }else if( (Sy-chickenHeight)>=-3 && (Sy-chickenHeight)<-2){
            if(Sx>=25 && Sx<=29){
                gameRunning=false;
                win=false;
                loss=true;
                collidedWithTheChicken=true;

            }

        }else if( (Sy-chickenHeight)>=-2 && (Sy-chickenHeight)<2.2){
            if(Sx>=24.2 && Sx<=30){
                gameRunning=false;
                win=false;
                loss=true;
                collidedWithTheChicken=true;
            }

        }else if( (Sy-chickenHeight)>=2.2 && (Sy-chickenHeight)<4.4){
            if(Sx>=22.6 && Sx<=24.2){
                gameRunning=false;
                win=false;
                loss=true;
                collidedWithTheChicken=true;
            }

        }
        //CHICKEN EGG COLLISION CONTROL ENDS

        //BASKET EGG COLLISION CONTROL STARTS
        if((Sx>=(44.4-basketPushBackX) && Sx<=(49.4-basketPushBackX))
           && ( Sy >=-4.4 && Sy<=-3)){
            gameRunning=false;
            eggIsInBasketRegion=true;
            win=true;
            loss=false;
            Sy=500;
        }else{

            eggIsInBasketRegion=false;
        }
        //BASKET EGG COLLISION CONTROL ENDS

        //CONSOLE CODE STARTS
        //system("CLS");
        cout << " ******************************************\n";
        cout << "gametime   :"<<gameTime << " seconds \n";
        cout << "fire time   :"<<cannonFiringTime << " seconds \n";

        cout << "v0   :"<<v0 << " ms-1 \n";
        cout << "theta   :"<<canonAngle << " degree \n";
        cout << "vx   :"<<vx << " ms-1 \n";
        cout << "vy   :"<<vy << " ms-1 \n";
        cout << "Sx   :"<<Sx << " ms-1 \n";
        cout << "Sy   :"<<Sy << " ms-1 \n";
        cout << "Chicken Height   :"<<chickenHeight << "m  \n";
        cout <<"Time of Flight: "<< T << " seconds \n";
        cout <<"Range : "<< R << " meters \n";
        cout<<"EggHeight-ChickenHeight="<<Sy-chickenHeight<<endl;
        if(win==true && loss==false){
            cout << "Game Won \n";
        }else if(loss==true && win==false){
            cout << "Game Lost \n";
        }else{
            cout << "Game Running \n";
        }
        if(eggIsInBasketRegion==true){
            cout<<"THE GAME IS IN THE BASKET REGION!!!!!!!!!"<<endl;
        }

        cout << " ******************************************\n";
        ////CONSOLE CODE ENDS

    }else{
        //Game has stopped


        //THE GAME HAS HALTED FOR SOME REASON
        //HERE THE VARIABLES WILL BE ANALYZED TO SEE THE RESULT
        if(win==true && loss==false){
            //drawEggBasketWithEgg();
            if(hasBeenInWinPart==false){
                PlaySound("winSound.wav",NULL, SND_FILENAME|SND_ASYNC);
                hasBeenInWinPart=true;
            }

            cout<<"CONGRATULATIONS YOU WON!!!!!!!!"<<endl;
            glPushMatrix();
            glTranslatef(2,0,0);

            drawEggBasketWithEgg();
            glPopMatrix();
            printWinningMessage();


        }

        if(win==false && loss==true){
            if(hasBeenInLosePart==false){
                PlaySound("loseSound.wav",NULL, SND_FILENAME|SND_ASYNC);
                hasBeenInLosePart=true;
            }

            cout<<"REALLY SORRY YOU LOST!!!!"<<endl;
            if(collidedWithTheChicken==true){
                printLosingMessageChicken();
            }else if(fellOnGround==true){
                printLosingMessageGround();
            }


        }



    }
    //*********************************CONTROLLING CODE ENDS**************************************//



    glFlush();
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{

    PlaySound("cluckingSound.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
    glutInitWindowSize(1000,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("EARN YOUR BREAKFAST");
    init();
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyBoardFunction);
    glutMainLoop();

    return 0;
}
