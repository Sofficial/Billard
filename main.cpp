#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <ctime>
#include <cstdio>
#include <map>
#include <string>
#include <vector>


#include "vec3.hpp"
#include "obj3.h"


using namespace std;
using std::map;


static bool mute = false;
static bool cylMode = false;
static bool quaMode = false;
static bool ballMode = false;
static double alpha_ = 0;
static double beta_ = 0;
static double hilfe = 0;
static double x = 0;
static double cylRadius = 1;
static double cylHeight = 1;
static double quaLength = 1;
static double quaWidth = 1;
static double quaHeight = 1;
static double quaRotation = 0;

static double z = 0;
static double bx = 0;
static double by = 0;
static double bz = 0;
static double window_width_ = 1024;
static double window_height_ = 768;
static double scale = 1;
static bool collision = false;
static bool move = false;
static bool drop = false;
//static int timer;
double mposx;
double mposy;
Vec3 dragstart, dragend, vDistance, nDirection;
bool dragged;
bool dragended;

//map fuer kugel-zust�nde (geschwindigkeit, ausrichtung etc.)
Vec3 direction;


std::vector<obj3> allObst;

obj3* theBall = new obj3('b');
obj3* theQuad = new obj3('q');




void initObsticals(){

//	int conePoints[totalCones][3];
//	conePoints[1][0] = 1;

	theBall->buildSphere(Vec3(0,1,0), 0.5);


	obj3* theEnd = new obj3('e');
	theEnd->buildEnd(1.5, 0.5, -8.5, 0.5,3);
	allObst.push_back(*theEnd);


	//tischbeine
	obj3* theCone1 = new obj3('c');
	obj3* theCone2 = new obj3('c');
	obj3* theCone3 = new obj3('c');
	obj3* theCone4 = new obj3('c');

	theCone4->buildCone(0.5, 4.0, 12,0,7);
	allObst.push_back(*theCone4);

	theCone1->buildCone(0.5, 4.0, -12,0,7);
	allObst.push_back(*theCone1);

	theCone2->buildCone(0.5, 4.0, -12,0,-7);
	allObst.push_back(*theCone2);

	theCone3->buildCone(0.5, 4.0, 12,0,-7);
	allObst.push_back(*theCone3);


	//das einzige kollidierende ding!
	obj3* theOnlyCone = new obj3('c');
	theOnlyCone->buildCone(1.25, 1, 4, 1, -4);
	allObst.push_back(*theOnlyCone);




//
//	obj3* quadWall1 = new obj3('q');
//	quadWall1->buildQuader(Vec3(-2,0,2), 2, 4, 3);
//	allObst.push_back(*quadWall1);


//	theQuad->buildQuaderByPoints(Vec3(2,0,2), Vec3(1,0,3), Vec3(2,0,4), Vec3(3,0,3), 1.0);
//	theQuad->buildQuader(Vec3(-6,0,-2), 2, 2, 1);
	theQuad->buildQuader(Vec3(10,0,0), Vec3(3,0,0), Vec3(0,0,3), 4);
	allObst.push_back(*theQuad);

//	obj3* reverseQuad = new obj3('q');
//	reverseQuad->buildQuader(Vec3(-2, -7, 2), 2, 4, 3);
//	allObst.push_back(*reverseQuad);


}

void drawAllObsticals(){

	allObst.begin();
	int num = allObst.size();

	for(int i = 0; i<num; i++){
		allObst.at(i).draw();
	}
	allObst.begin();
}

bool checkAllCollisions(){

	bool erg = false;
	allObst.begin();
	for(int i = 0; i<allObst.size(); i++)
	{
		theBall->checkCollision(allObst.at(i));

	}
	allObst.begin();

//	theQuad->calcCollisionEquasions(*theBall);

	return erg;
}



//void initball1Array(){
//
//
//
//	direction = Vec3(0,0,0);
//
//	ball1["curSpeed"] = 0;
//	ball1["speed"] = 80;
//	ball1["step"] =  0.1;
//	ball1["x"] = 0;
//	ball1["y"] = 0;
//	ball1["z"] = 0;
//	ball1["move"] = 0;
//	ball1["a"] = 0;
//	ball1["b"] = 0;
//
//	printf("ready filling the ball1-array");
//}

//void initball2Array(){
//
//
//
//	direction = Vec3(0,0,0);
//
//	ball2["curSpeed"] = 0;
//	ball2["speed"] = 80;
//	ball2["step"] =  0.1;
//	ball2["x"] = -2;
//	ball2["y"] = 0;
//	ball2["z"] = -2;
//	ball2["move"] = 0;
//	ball2["a"] = 0;
//	ball2["b"] = 0;
//
//	printf("ready filling the ball1-array");
//}



static void key_callback(GLFWwindow* window, int key, int scancode, int action,
        int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key == GLFW_KEY_RIGHT)

        	   x += 0.2;


    if (key == GLFW_KEY_V)
        collision = false;
    if (key == GLFW_KEY_LEFT)

    	        	x -= 0.2;

    if (key == GLFW_KEY_UP)


            	  z += 0.2;


    if (key == GLFW_KEY_DOWN)

                	  z -= 0.2;

    if (key == GLFW_KEY_U)
    		{cylRadius += 0.2;
       		  quaLength += 0.2;}
    if (key == GLFW_KEY_J)
    { cylRadius -= 0.2;
 	  	  	  	  	  quaLength -= 0.2;}
    if (key == GLFW_KEY_Z)
    {cylHeight += 0.2;
	  	  	  	  quaHeight += 0.2;}
    if (key == GLFW_KEY_H)
    { cylHeight -= 0.2;
       				  quaHeight -= 0.2;}
    if (key == GLFW_KEY_T)
    	quaWidth += 0.2;
    if (key == GLFW_KEY_G)
    	quaWidth -= 0.2;
    if (key == GLFW_KEY_K)
    	quaRotation += 0.1;
    if (key == GLFW_KEY_I)
    	quaRotation -= 0.1;
    if (key == GLFW_KEY_A)
        alpha_ += 1;
    if (key == GLFW_KEY_D)
        alpha_ -= 1;
    if (key == GLFW_KEY_W)
        beta_ += 1;
    if (key == GLFW_KEY_S)
        beta_ -= 1;
    if (key == GLFW_KEY_C)
    	cylMode = true;
    if (key == GLFW_KEY_Q)
    	quaMode = true;
    if (key == GLFW_KEY_B)
    	ballMode = true;
    if (key == GLFW_KEY_Y)
         drop = true;
    if (key == GLFW_KEY_KP_SUBTRACT)

    scale -= 0.1;
    if (key == GLFW_KEY_KP_ADD)

    scale += 0.1;

}


static void cursor_callback(GLFWwindow* window, double mode, double value) {
    glfwGetCursorPos(window, &mposx, &mposy);

    //steuerung des zielfadens in die mitte bringen
    mposx = mposx - window_width_ / 2;
    mposy = mposy - window_height_ / 2;
    //printf("MPOS: X: %d Y: %d \n", (char)mposx, (char)mposy);
}

static void mouse_callback(GLFWwindow* window, int button, int action,
        int mods) {

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
	        if(cylMode == true)
	        {
	        	obj3* cone2 = new obj3('c');
	        	    	cone2->buildCone(cylRadius/2, cylHeight, mposx * .04, cylHeight, mposy * .04);
	        	    	allObst.push_back(*cone2);

	        }
	        else if(quaMode == true)
	        {
	        	obj3* quader2 = new obj3('q');
	        		    	//quader2->buildQuader(Vec3(mposx * .04, 0, mposy * .04), quaWidth, quaLength, quaHeight);
//	        				Vec3 einheitsvektor = Vec3(1,0,1);
//	        				einheitsvektor.p[0] = einheitsvektor.p[0] * cos(quaRotation) - einheitsvektor.p[2] * sin(quaRotation);
//							einheitsvektor.p[2] = einheitsvektor.p[0] * sin(quaRotation) + einheitsvektor.p[2] * cos(quaRotation);
//
//
//
//	        				Vec3 leX = Vec3(0,0,quaWidth);
//	        				Vec3 leZ = Vec3(quaLength, 0,0);

//	        				leX.p[2] += quaWidth;
//	        				leZ.p[0] += quaLength;
//
//
//
//
//	        				Vec3 leX = Vec3(0,0,quaWidth);
//	        				Vec3 leZ = Vec3(quaLength, 0,0);
//
//	        				leX.p[0] = leX.p[0] * cos(quaRotation) - leX.p[2] * sin(quaRotation);
//	        				leX.p[2] = leX.p[0] * sin(quaRotation) + leX.p[2] * cos(quaRotation);
//
//	        				leZ =
//
//	        				leZ.p[0] = leZ.p[0] * cos(quaRotation) - leZ.p[2] * sin(quaRotation);
//							leZ.p[2] = leZ.p[0] * sin(quaRotation) + leZ.p[2] * cos(quaRotation);

	        		    	quader2->buildQuader(Vec3(mposx * .04, 0, mposy * .04), Vec3(quaRotation,0,quaWidth), Vec3(quaLength,0,-quaRotation), quaHeight);
//							quader2->buildQuader(Vec3(mposx * .04, 0, mposy * .04), (leX+einheitsvektor), (leZ+einheitsvektor), quaHeight);

	        		    	allObst.push_back(*quader2);

	        }

	        else {
			dragstart = Vec3(mposx, 0, mposy);
	        //printf("MPOS: X: %d Y: %d \n", (char) mposx, (char) mposy);
	        dragged = true;
	        //printf("gedr?ckt \n");
	        }



	    }

	    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && ballMode == true) {

	    	theBall->specs["x"] = mposx * .04;
	    	theBall->specs["y"] = mposy * .04;
	    	ballMode = false;

	       }


	    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {

	    	if(cylMode == false && quaMode ==false)
	    	{
	    		//printf("distanceResult: %d \n", (char)distanceResult);
	    		dragged = false;
	    		//printf("losgelassen \n");
	    		dragended = true;
	    	}

	     	cylMode = false;
	    	quaMode = false;
	    }




}

double calculateDistance(Vec3 dragstart, Vec3 dragend) {

    vDistance = dragstart - dragend;
    double dDistance = vDistance.LengthXY();
    nDirection = vDistance; //normalenvektor
    nDirection.Normalize();

    printf("dragged the distance between :%d %d %d and %d %d %d \n",
            (char) dragstart.p[0], (char) dragstart.p[1], (char) dragstart.p[2],
            (char) dragend.p[0], (char) dragend.p[1], (char) dragend.p[2]);
    printf("nDirection: %d %d %d \n", (char) nDirection.p[0],
            (char) nDirection.p[1], (char) nDirection.p[2]);
    return dDistance;
}

Vec3 calculateDirection() {

	dragstart = Vec3(theBall->specs["x"],theBall->specs["y"],theBall->specs["z"]);
	dragend = Vec3(mposx, 0, mposy);

    vDistance = dragstart - dragend;

    nDirection = vDistance; //normalenvektor
    nDirection.Normalize(); //n-vektor mit l�nge 1

    return nDirection;
}

void DrawDirArrow() {
    glBegin(GL_LINES);
    glVertex3d(theBall->specs["x"], 0.5, theBall->specs["z"]);
    glVertex3d(mposx * .05, 0, mposy * .05);
    glEnd();
}

// draw a sphere composed of triangles
void DrawSphere(const Vec3& ctr, double r) {


	int i, j, n1 = 32, n2 = 32;
    Vec3 normal, v1;
    double a1, a1d = M_PI / n1, a2, a2d = M_PI / n2, s1, s2, c1, c2;

    glShadeModel(GL_SMOOTH);
    for (i = 0; i < n1; i++) {
        a1 = i * a1d;

        glBegin(GL_TRIANGLE_STRIP);
        for (j = 0; j <= n2; j++) {
            a2 = (j + .5 * (i % 2)) * 2 * a2d;

            s1 = sin(a1);
            c1 = cos(a1);
            s2 = sin(a2);
            c2 = cos(a2);
            normal = c1 * XVec3 + s1 * (c2 * YVec3 + s2 * ZVec3);
            v1 = ctr + r * normal;
            glNormal3dv(normal.p);
            glVertex3dv(v1.p);

            s1 = sin(a1 + a1d);
            c1 = cos(a1 + a1d);
            s2 = sin(a2 + a2d);
            c2 = cos(a2 + a2d);
            normal = c1 * XVec3 + s1 * (c2 * YVec3 + s2 * ZVec3);
            v1 = ctr + r * normal;
            glNormal3dv(normal.p);
            glVertex3dv(v1.p);
        }
        glEnd();
    }
}

void DrawBillTableFloor() {

    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);

    glVertex3f(12.5, 0, -7.5);
    glVertex3f(12.5, 0, 7.5);
    glVertex3f(-12.5, 0, 7.5);
    glVertex3f(-12.5, 0, -7.5);


//    glNormal3f(0.26, 0, -0.96);
//    glVertex3f(-4, 1, 2);
//    glVertex3f(-4, 0, 2);
//    glVertex3f(12, 0, 5);
//    glVertex3f(12, 1, 5);

    glVertex3f(-12.5, -4, -7.5);
    glVertex3f(-12.5, -4, 7.5);
    glVertex3f(12.5, -4, 7.5);
    glVertex3f(12.5, -4, -7.5);
















    glEnd();

}

void DrawHole() {

    glBegin(GL_QUADS);


    glVertex3f(-12.5, 0.01, 1);
    glVertex3f(-5.5, 0.01, 1);
    glVertex3f(-5.5, 0.01, -1);
    glVertex3f(-12.5, 0.01, -1);



    glEnd();

}

void DrawBillTableWalls() {

    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glVertex3f(-12, 1, 7);
    glVertex3f(-12, 0, 7);
    glVertex3f(12, 0, 7);
    glVertex3f(12, 1, 7);

    glNormal3f(0, 0, 1);
    glVertex3f(-12.5, 2, 7.5);
    glVertex3f(-12.5, 0, 7.5);
    glVertex3f(12.5, 0, 7.5);
    glVertex3f(12.5, 2, 7.5);

    glNormal3f(0, -0.45, -0.89);
    glVertex3f(-12.5, 2, 7.5);
    glVertex3f(-12, 1, 7);
    glVertex3f(12, 1, 7);
    glVertex3f(12.5, 2, 7.5);



    glNormal3f(1, 0, 0);
    glVertex3f(-12, 1, -7);
    glVertex3f(-12, 0, -7);
    glVertex3f(-12, 0, 7);
    glVertex3f(-12, 1, 7);

    glNormal3f(1, 0, 0);
    glVertex3f(-12.5, 2, -7.5);
    glVertex3f(-12.5, 0, -7.5);
    glVertex3f(-12.5, 0, 7.5);
    glVertex3f(-12.5, 2, 7.5);

    glNormal3f(-0.89, -0.45, 0);
    glVertex3f(-12.5, 2, -7.5);
    glVertex3f(-12, 1, -7);
    glVertex3f(-12, 1, 7);
    glVertex3f(-12.5, 2, 7.5);



    glNormal3f(0, 0, -1);
    glVertex3f(12, 1, -7);
    glVertex3f(12, 0, -7);
    glVertex3f(-12, 0, -7);
    glVertex3f(-12, 1, -7);

    glNormal3f(0, 0, -1);
    glVertex3f(12.5, 2, -7.5);
    glVertex3f(12.5, 0, -7.5);
    glVertex3f(-12.5, 0, -7.5);
    glVertex3f(-12.5, 2, -7.5);

    glNormal3f(0, -0.45, -0.89);
    glVertex3f(12.5, 2, -7.5);
    glVertex3f(12, 1, -7);
    glVertex3f(-12, 1, -7);
    glVertex3f(-12.5, 2, -7.5);


    glNormal3f(-1, 0, 0);
    glVertex3f(12, 1, 7);
    glVertex3f(12, 0, 7);
    glVertex3f(12, 0, -7);
    glVertex3f(12, 1, -7);

    glNormal3f(-1, 0, 0);
    glVertex3f(12.5, 2, 7.5);
    glVertex3f(12.5, 0, 7.5);
    glVertex3f(12.5, 0, -7.5);
    glVertex3f(12.5, 2, -7.5);

    glNormal3f(0.89, 0.45, 0);
    glVertex3f(12.5, 2, 7.5);
    glVertex3f(12, 1, 7);
    glVertex3f(12, 1, -7);
    glVertex3f(12.5, 2, -7.5);














    glNormal3f(0, 0, 1);
        glVertex3f(-12, -5, 7);
        glVertex3f(-12, -4, 7);
        glVertex3f(12, -4, 7);
        glVertex3f(12, -5, 7);

        glNormal3f(0, 0, 1);
        glVertex3f(-12.5, -6, 7.5);
        glVertex3f(-12.5, -4, 7.5);
        glVertex3f(12.5, -4, 7.5);
        glVertex3f(12.5, -6, 7.5);

        glNormal3f(0, -0.45, -0.89);
        glVertex3f(-12.5, -6, 7.5);
        glVertex3f(-12, -5, 7);
        glVertex3f(12, -5, 7);
        glVertex3f(12.5, -6, 7.5);



        glNormal3f(1, 0, 0);
        glVertex3f(-12, -5, -7);
        glVertex3f(-12, -4, -7);
        glVertex3f(-12, -4, 7);
        glVertex3f(-12, -5, 7);

        glNormal3f(1, 0, 0);
        glVertex3f(-12.5, -6, -7.5);
        glVertex3f(-12.5, -4, -7.5);
        glVertex3f(-12.5, -4, 7.5);
        glVertex3f(-12.5, -6, 7.5);

        glNormal3f(-0.89, -0.45, 0);
        glVertex3f(-12.5, -6, -7.5);
        glVertex3f(-12, -5, -7);
        glVertex3f(-12, -5, 7);
        glVertex3f(-12.5, -6, 7.5);



        glNormal3f(0, 0, -1);
        glVertex3f(12, -5, -7);
        glVertex3f(12, -4, -7);
        glVertex3f(-12, -4, -7);
        glVertex3f(-12, -5, -7);

        glNormal3f(0, 0, -1);
        glVertex3f(12.5, -6, -7.5);
        glVertex3f(12.5, -4, -7.5);
        glVertex3f(-12.5, -4, -7.5);
        glVertex3f(-12.5, -6, -7.5);

        glNormal3f(0, -0.45, -0.89);
        glVertex3f(12.5, -6, -7.5);
        glVertex3f(12, -5, -7);
        glVertex3f(-12, -5, -7);
        glVertex3f(-12.5, -6, -7.5);


        glNormal3f(-1, 0, 0);
        glVertex3f(12, -5, 7);
        glVertex3f(12, -4, 7);
        glVertex3f(12, -4, -7);
        glVertex3f(12, -5, -7);

        glNormal3f(-1, 0, 0);
        glVertex3f(12.5, -6, 7.5);
        glVertex3f(12.5, -4, 7.5);
        glVertex3f(12.5, -4, -7.5);
        glVertex3f(12.5, -6, -7.5);

        glNormal3f(0.89, 0.45, 0);
        glVertex3f(12.5, -6, 7.5);
        glVertex3f(12, -5, 7);
        glVertex3f(12, -5, -7);
        glVertex3f(12.5, -6, -7.5);


    glEnd();

}


void SetMaterialColor(int side, double r, double g, double b) {
    float amb[4], dif[4], spe[4];
    int mat;

    dif[0] = r;
    dif[1] = g;
    dif[2] = b;

    for (int i = 0; i < 3; i++) {
        amb[i] = .1 * dif[i];
        spe[i] = .5;
    }
    amb[3] = dif[3] = spe[3] = 1.0;

    switch (side) {
    case 1:
        mat = GL_FRONT;
        break;
    case 2:
        mat = GL_BACK;
        break;
    default:
        mat = GL_FRONT_AND_BACK;
    }

    glMaterialfv(mat, GL_AMBIENT, amb);
    glMaterialfv(mat, GL_DIFFUSE, dif);
    glMaterialfv(mat, GL_SPECULAR, spe);
    glMaterialf(mat, GL_SHININESS, 20);
}

// set viewport transformations and draw objects
void InitLighting() {
    GLfloat lp1[4] = { 10, 5, 10, 0 };
    GLfloat lp2[4] = { -5, 5, -10, 0 };
    GLfloat red[4] = { 1.0, .8, .8, 1 };
    GLfloat blue[4] = { .8, .8, 1.0, 1 };

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glShadeModel(GL_SMOOTH);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT1, GL_POSITION, lp1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, red);
    glLightfv(GL_LIGHT1, GL_SPECULAR, red);
    glEnable(GL_LIGHT1);

    glLightfv(GL_LIGHT2, GL_POSITION, lp2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, blue);
    glLightfv(GL_LIGHT2, GL_SPECULAR, blue);
    glEnable(GL_LIGHT2);

    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // init viewport to canvassize
    glViewport(0, 0, window_width_, window_height_);

    // init coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-15, 15, -10, 10, 0, 29);
    glFrustum(-4, 4, -4, 4, 4, 30);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//void checkAndApplyCollision(){
//	
//
//	//billard abmessungen
//	double upperBorder, lowerBorder, leftBorder, rightBorder;
//	upperBorder = 4.5;
//	lowerBorder = -4.5;
//	rightBorder = 6.5;
//	leftBorder = -6.5;
//
//	//for ball1 in ball1s:
//
//	if(ball1["x"] > rightBorder){
//		direction.p[0] = -direction.p[0];
//		ball1["x"] = rightBorder;
////		ball1["speedX"] = -ball1["speed"];
//		if(mute==false){printf("colision: x -rB \n");}
//	}
//	if(ball1["x"] < leftBorder){
//		direction.p[0] = -direction.p[0];
//		ball1["x"] = leftBorder;
////		ball1["speedX"] = ball1["speed"];
//		if(mute==false){printf("colision: x -lB \n");}
//	}
//	if(ball1["z"] > upperBorder){
//		direction.p[2] = -direction.p[2];
//		ball1["z"] = upperBorder;
////		ball1["speedZ"] = -ball1["speed"];
//		if(mute==false){printf("colision: z -uB\n");}
//	}
//	if(ball1["z"] < lowerBorder){
//		direction.p[2] = -direction.p[2];
//		ball1["z"] = lowerBorder;
////		ball1["speedZ"] = ball1["speed"];
//		if(mute==false){printf("colision: z -lB\n");}
//
//	}
//
//	if(ball2["x"] > rightBorder){
//			direction.p[0] = -direction.p[0];
//			ball2["x"] = rightBorder;
//		}
//		if(ball2["x"] < leftBorder){
//			direction.p[0] = -direction.p[0];
//			ball2["x"] = leftBorder;
//		}
//		if(ball2["z"] > upperBorder){
//			direction.p[2] = -direction.p[2];
//			ball2["z"] = upperBorder;
//		}
//		if(ball2["z"] < lowerBorder){
//			direction.p[2] = -direction.p[2];
//			ball2["z"] = lowerBorder;
//
//		}
//
//
//		double x = ball1["x"]-ball2["x"];
//		double y = ball1["z"]-ball2["z"];
//		double distance = sqrt(x*x+y*y);
//
//
//		if(distance<1){
//			if(ball1["curSpeed"] != 0){
//				ball2["curSpeed"] = ball1["curSpeed"];
//				ball1["curSpeed"] = 0;
//				}
//			else{
//				ball1["curSpeed"] = ball2["curSpeed"];
//				ball2["curSpeed"] = 0;
//				}
//		}
//
//
//
//
//
//};

void wait ( int seconds )
{
  clock_t endwait;
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}

// draw the entire scene
void Preview() {
//speeda=speeda*.9995;
//speedb=speedb*.9995;
	//speed=speed*0.999;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // Reset The Current Modelview Matrix



    glPushMatrix();
    glTranslated(0, 0, -20.0); // Move 10 units backwards in z,  // since camera is at origin






    glRotated(alpha_, 0, 3, 0);
    //alpha_ += .1;
    glRotated(beta_, 1, 0, 0);

    glRotated(40, 1, 0, 0);



    if(drop==true){

    	if(hilfe<200){
    	glRotated(hilfe, 1, 0, 0);
    	 hilfe += 1;
    	}
    	if(hilfe==200){
    		glRotated(200, 1, 0, 0);
//    		theBall->specs["curSpeed"] = 0;t
    		theBall->specs["y"] = -4 - theBall->specs["radius"];

    		drop = false;
    		hilfe = 0;


    		for(int i = 0; i<allObst.size(); i++)
    		{
    			allObst.at(i).specs["y"] -= 4 + allObst.at(i).specs["hight"];
    		}

    	}

    }

    glTranslated(x, 0, z);
    glScaled(scale, scale, scale);
    glShadeModel(GL_SMOOTH);


  //  SetMaterialColor(1, 0, 0, 1);
  //  SetMaterialColor(2, 1, 0, 0);
 //   drawcube();

    SetMaterialColor(2, .05, .54, .13);
	SetMaterialColor(1, 0.6, 0, 0);
	DrawBillTableFloor();

//	SetMaterialColor(0, 0, 0, 0);
//		DrawHole();

	//SetMaterialColor(2, 0.1, 1.0, 0);
	//SetMaterialColor(1, 1, 0, 0);
	SetMaterialColor(0, .4, .4, .4);
	DrawBillTableWalls();

	SetMaterialColor(0, .8, .4, 0);
    drawAllObsticals();




    //koordinatenkreuzgimmik
    glPushMatrix();
    glTranslated(-12.5,3,-7.5);
    glRotated(quaRotation*30, 0,1,0);
    glTranslated(12.5,-3,7.5);


	SetMaterialColor(0, 1, 0, 0);
    glBegin(GL_QUADS);

    glVertex3f(-12.5, 3, -7.5);
    glVertex3f(-12.5, 3.5, -7.5);
    glVertex3f(-12.5+cylRadius, 3.5, -7.5);
    glVertex3f(-12.5+cylRadius, 3, -7.5);



    glEnd();

	SetMaterialColor(0, 0, 1, 0);
    glBegin(GL_QUADS);

    glVertex3f(-12.25, 3, -7.5);
    glVertex3f(-12.5, 3, -7.25);
    glVertex3f(-12.5, 3+cylHeight, -7.25);
    glVertex3f(-12.25, 3+cylHeight, -7.5);



    glEnd();


	SetMaterialColor(0, 0, 0, 1);
    glBegin(GL_QUADS);

    glVertex3f(-12.5, 3, -7.5);
    glVertex3f(-12.5, 3.5, -7.5);
    glVertex3f(-12.5, 3.5, -7.5+quaWidth);
    glVertex3f(-12.5, 3, -7.5+quaWidth);

//    glRotated(-quaRotation, -12,0,-7.5);


    glEnd();

    glPopMatrix();




	if (dragged) {
	 DrawDirArrow();
	}
	else if(dragended){
		theBall->moveDirection = calculateDirection();
		//vern�nftige einheit f�r geschwindigkeit wird gebraucht!!
		theBall->specs["curSpeed"] = theBall->specs["speed"];

	    dragended = false;

//	    move = true;
//	    ball1["speedX"] = (mposx * .01) - ball1["x"]*.01;
//	    ball1["speedZ"] = (mposy * .01) - ball1["z"]*.01;
	}




	glPushMatrix();

	SetMaterialColor(1, 0.3, 0.3, 0.3);
	checkAllCollisions();
	theBall->moveAccordingToSpecs();
	glTranslated(theBall->specs["x"], 0, theBall->specs["z"]);
	theBall->draw();

	glPopMatrix();



// 	glPushMatrix();
//
//
//
// //	if (move==true) {
// 	if(ball2["curSpeed"] > 0){
//
//     	ball2["curSpeed"] -= ball2["step"];
//
//     	ball2["x"] += direction.p[0]/(100-ball2["curSpeed"]);
//     	ball2["z"] += direction.p[2]/(100-ball2["curSpeed"]);
//
//
//
//     	checkAndApplyCollision();
//
// 	}
//
// 	glTranslated(ball2["x"], 0, ball2["z"]);
//
// 	SetMaterialColor(1, 1, 0, 0);
//      DrawSphere(Vec3(0, .5, 0), .5);
//
//
//
//      glPopMatrix();



    glPopMatrix();


}

int main() {
    GLFWwindow* window = NULL;

    printf("Here we go!\n");

    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(window_width_, window_height_,
            "Simple 3D Animation", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwSetCursorPosCallback(window, cursor_callback);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_callback);

//    initball1Array();
//    initball2Array();
    initObsticals();
    while (!glfwWindowShouldClose(window)) {
        // switch on lighting (or you don't see anything)
        InitLighting();

        // set background color
        glClearColor(0.8, 0.8, 0.8, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw the scene
        Preview();


        // make it appear (before this, it's hidden in the rear buffer)
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    printf("Goodbye!\n");

    return 0;
}
