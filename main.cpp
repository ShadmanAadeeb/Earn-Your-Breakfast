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
//chicken wing related variables
boolean wingWillRise=true;
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


void init(){
    eggAngle=canonAngle;
    glOrtho(-canvasWidth,canvasWidth,-canvasHeight,canvasHeight,-canvasWidth,canvasWidth);
    glClearColor(0,0,0,0);
}
void myKeyBoardFunction(unsigned char button,int x,int y){
    switch(button){
        case 'a':
            //Sx-=02;
            canonAngle+=5;
            if(canonAngle>90){
                canonAngle=90;
            }
            eggAngle=canonAngle;
            vx=v0*cos( (canonAngle*PI)/180 );
            vy=v0*sin( (canonAngle*PI)/180 );
            glutPostRedisplay();
        break;
        case 'd':
           // Sx+=02;
            canonAngle-=5;
            if(canonAngle<15){
                canonAngle=15;
            }
            eggAngle=canonAngle;
            vx=v0*cos( (canonAngle*PI)/180 );
            vy=v0*sin( (canonAngle*PI)/180 );
            glutPostRedisplay();
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
                cannonFired=true;
//                time_t cannonFiringTimeVar=time(NULL);
//                cannonFiringTime=(long)cannonFiringTimeVar;
//                Sx=R;
                gameTime=0;
                glutPostRedisplay();
                }
        break;
        //TESTING PURPOSE
        case 38://up
            Sy+=02;
            glutPostRedisplay();
        break;
        case 40://down
            Sy-=02;
            glutPostRedisplay();
        break;
        case 37://left
            Sx-=02;
            glutPostRedisplay();
        break;
        case 39://right
            Sx+=02;
            glutPostRedisplay();
        break;
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
    drawRectangle(-3,0,3,-2,canonBaseColor);
    drawEllipse(3,1,0.5,0.5,0.5);

    //drawing canon base grass
    glPushMatrix();
    glTranslatef(1,-2,0);
    drawGrassPatch();
    glPopMatrix();
    //drawing canon base grass
    glPushMatrix();
    glTranslatef(-4.0,-2,0);
    drawGrassPatch();
    glPopMatrix();

        //drawing canon base grass
    glPushMatrix();
    glTranslatef(-3.0,-2,0);
    drawGrassPatch();
    glPopMatrix();

    glPopMatrix();
}

void drawEggBasket(){
    glPushMatrix();
    glTranslatef(basketX+7,basketY-1,0);
    glScalef(3.3 ,1.3,1.3);
    glBegin(GL_QUADS);
    glColor3f(0.5,0.5,0);glVertex3f(-1.25,0,0);
    glColor3f(0.3,0.3,0);glVertex3f(-0.5,-1.5,0);
    glColor3f(0.8,0.8,0);glVertex3f(0.5,-1.5,0);
    glColor3f(1,1,0);glVertex3f(1.25,0,0);
    glEnd();

    drawEllipse(1.25,0.5,0.961, 0.808, 0.039);
    drawEllipse(1,0.25,0.761, 0.608, 0.039);
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


void myDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    //STATIC DRAWINGS START
    //Drawing the field
    float colorArray[]={ 0.5,0.5,0,  1,1,0,   0.5,1,0,  0.5,1,0.3};
    drawRectangle(-canvasWidth,0,canvasWidth,-canvasWidth,colorArray );
    //drawing the sky
    float colorArray2[]={ 0.5,0.5,1,  0,0,1,   0,0,1,  1,1,1};
    drawRectangle(-canvasWidth,canvasWidth,canvasWidth,0,colorArray2 );
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

    glPopMatrix();

    //STATIC DRAWINGS END

    //DYNAMIC CODE STARTS

    //drawing the cannon
    glPushMatrix();
    glTranslatef(-5,0,0);
    glScalef(1.2,1.2,1.2);
    drawCannonBase();
    drawCannon();
    drawCanonStand();

    glPopMatrix();
    //drawing the egg basket
    glPushMatrix();
    glTranslatef(2,0,0);
    drawEggBasket();
    glPopMatrix();
    //drawing the chicken
    drawChicken();
    //drawing the velocity bar
    glPushMatrix();
    glScalef(1,3,1);
    glTranslatef(-29,-3,0);
    float velocityBarBackGroundColor[]={0,0,0,  0,0,0,  0,0,0,  0,0,0};
    drawRectangle(0-0.25,10+0.25,2+0.25,0-0.25,velocityBarBackGroundColor);
    float velocityBarColor[]={1,0,0,  1,0,0,  1,0,0,  1,0,0};
    drawRectangle(0,v0/3-3,2,0,velocityBarColor);
    glPopMatrix();

    //drawing the egg starts
    glPushMatrix();
    glTranslatef(-23+Sx,-11.75+Sy,0);
    glScalef(0.75,0.75,0.75);
    glRotatef(eggAngle,0,0,1);
    drawEllipse(1.75,1.4,1,1,1);
    glPopMatrix();
    //drawing the egg ends
    //DYNAMIC CODE ENDS
    glPushMatrix();
    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3f(1,0,0);glVertex3f(-25,-17,0);
    glColor3f(0,1,0);glVertex3f(15,-17,0);
    glEnd();
    glPopMatrix();

    //*********************************CONTROLLING CODE STARTS**************************************//
    if(gameRunning){
        //Technical and Physics code starts
        gameTime+=0.05;
        if(cannonFired){

            Sx=vx*gameTime;
            Sy=vy*gameTime-0.5*g*pow(gameTime,2);
            if(Sy<=-5){
                Sy=-5;
                gameRunning=false;
            }

        }
        T= (2*v0*sin( (PI*canonAngle)/180 ) )/g;
        R= ((v0*v0)*sin( (2*PI*canonAngle)/180 ))/g;
        system("CLS");
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
        cout << " ******************************************\n";
        //Technical and Physics code ends
        //flap wings code starts
        if(wingWillRise){
            chickenWingAngle+=5;
            if(chickenWingAngle>=30){
                wingWillRise=false;
            }
        }else{
            chickenWingAngle-=5;
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
           chickenHeight+=0.3;
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
           chickenHeight-=0.3;
           if(chickenHeight<=0){
                chickenWillRise=true;
           }
        }
        //chicken flight code ends
    }else{


    }
    //*********************************CONTROLLING CODE ENDS**************************************//


    glFlush();
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInitWindowSize(1000,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("EARN YOUR BREAKFAST");
    init();
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyBoardFunction);
    glutMainLoop();

    return 0;
}
