#define GLFW_DLL
#include <GLFW/glfw3.h>
#include "obj3.h"

//#include <GL/glu.h>

Vec3 startingPoint;

obj3::obj3(char mode) {
	this->mode = mode;
//
//	if(mode == 'b') //b = ball
////		buildSphere();
//
//	else if(mode == 'q') //quader
//		buildQuader();
//
//	//else if(mode == 'c') // cone
//		//buildCone(0.5, 4.0, 0,5,5);
}

obj3::~obj3() {
	// TODO Auto-generated destructor stub
}

void obj3::buildCone(float r, float h, double x, double y, double z) {

	moveDirection = Vec3(0,0,0);
	pCenter = Vec3(x-r, y,z);

	specs["curSpeed"] = 0;
	specs["speed"] = 80;
	specs["step"] =  0.1;
	specs["xcenter"] = x+r;
	specs["x"] = x;
	specs["y"] = y;
	specs["z"] = z;
	specs["radius"] = (double)r;
	specs["hight"] = (double)h;
	specs["alpha"] = 0;

}

void obj3::buildEnd(float r, float h, double x, double y, double z) {
	moveDirection = Vec3(0,0,0);

	specs["xcenter"] = x+r;
	specs["x"] = x;
	specs["y"] = y;
	specs["z"] = z;
	specs["radius"] = (double)r;
	specs["hight"] = (double)h;
}


void obj3::buildQuader(Vec3 p, double width, double length, double height) {

	Vec3 temp = p;
	qLow.push_back(p);

	temp.p[0] += length;
	qLow.push_back(temp);

	temp.p[2] += width;
	temp.p[0] -= length;
	qLow.push_back(temp);

	temp.p[0] += length;
	qLow.push_back(temp);

	qHigh = qLow;
	qLow.begin();
	for(int i = 0; i<qLow.size(); i++)
	{
		//y
		qHigh.at(i).p[1] += height;
	}
	qLow.begin();
	qHigh.begin();

	moveDirection = Vec3(0,0,0);

	specs["curSpeed"] = 0;
	specs["speed"] = 80;
	specs["step"] =  0.1;
	specs["x"] = 0;
	specs["y"] = 0;
	specs["z"] = 0;
	specs["move"] = 0;
	specs["a"] = 0;
	specs["b"] = 0;

//	glBegin(GL_QUADS);
//	glVertex3f(1,4,4);
//	glVertex3f(1,4,5);
//
//	glVertex3f(2,4,5);
//	glVertex3f(2,4,4);
//	glEnd();
}


void obj3::buildQuader(Vec3 p, Vec3 width, Vec3 length, double height) {


	Vec3 temp = p;
	qLow.push_back(p);

	temp = temp+length;
	qLow.push_back(temp);

	temp = temp + width;
	temp = temp - length;
	qLow.push_back(temp);

	temp = temp +  length;
	qLow.push_back(temp);

	qHigh = qLow;
	qLow.begin();
	for(int i = 0; i<qLow.size(); i++)
	{
		//y
		qHigh.at(i).p[1] += height;
	}
	qLow.begin();
	qHigh.begin();

}

void obj3::buildSphere(Vec3 p, double r) {
	moveDirection = Vec3(0,0,0);

	startingPoint = p;

	specs["curSpeed"] = 0;
	specs["speed"] = 60;
	specs["step"] =  0.04;
	specs["x"] = p.p[0];
	specs["y"] = p.p[1];
	specs["z"] = p.p[2];
	specs["move"] = 0;
	specs["radius"] = r;


}

bool obj3::checkCollision(obj3 toCheck) {
	if(this->mode == 'b')
	{
//		checkAndApplyCollision(){

			//billard abmessungen

			double upperBorder, lowerBorder, leftBorder, rightBorder;
			double spaceing = 0.5;
			upperBorder = 7.5 - spaceing;
			lowerBorder = -7.5 + spaceing;
			rightBorder = 12.5 - spaceing;
			leftBorder = -12.5 + spaceing;

			if((this->specs["x"] +specs["radius"]) > rightBorder){
				this->moveDirection.p[0] = -this->moveDirection.p[0];
				this->specs["x"] = rightBorder-specs["radius"];
//				if(mute==false){printf("colision: x -rB \n");}
			}
			if((this->specs["x"]- specs["radius"]) < leftBorder){
				this->moveDirection.p[0] = -this->moveDirection.p[0];
				this->specs["x"] = leftBorder + specs["radius"];
//				if(mute==false){printf("colision: x -lB \n");}
			}
			if((this->specs["z"]+ specs["radius"]) > upperBorder){
				this->moveDirection.p[2] = -this->moveDirection.p[2];
				this->specs["z"] = upperBorder - specs["radius"];
//				if(mute==false){printf("colision: z -uB\n");}
			}
			if((this->specs["z"]- specs["radius"]) < lowerBorder){
				this->moveDirection.p[2] = -this->moveDirection.p[2];
				this->specs["z"] = lowerBorder + specs["radius"];
//				if(mute==false){printf("colision: z -lB\n");}

			}

		double minDistance, actDistance, dx, dz;
		switch(toCheck.mode)
		{
			case('b'):



			break;

			//check collision between "the" ball and a cone
			case('c'):

				minDistance = this->specs["radius"] + toCheck.specs["radius"];

				//pythagoras
				dx =toCheck.specs["x"] - this->specs["x"];
				dz =toCheck.specs["z"] - this->specs["z"];
				actDistance = sqrt(dx*dx + dz*dz);

				if(actDistance < minDistance)
				{
					Vec3 newDirection = this->calcReflection(toCheck.getBallCenter());

					moveDirection = newDirection;

					printf("collision!! with cone\n");
					return true;
				}
			break;

			case('e'):

				minDistance = this->specs["radius"] + toCheck.specs["radius"];

				//pythagoras
				dx =toCheck.specs["x"] - this->specs["x"];
				dz =toCheck.specs["z"] - this->specs["z"];
				actDistance = sqrt(dx*dx + dz*dz);

				if(actDistance < minDistance)
				{
					Vec3 newDirection = this->weirdCollision(toCheck.getBallCenter());

					moveDirection = newDirection;

					printf("collision!! with cone\n");
					return true;
				}
			break;


			case('q'):
				CollisionResult col = (toCheck.calcCollisionEquasions(*this));
				if(col.isCollided){
					Vec3 newDirection = this->calcReflection(col.collisionPoint);

					moveDirection = newDirection;
				}
				printf("checked the ball and the quad!");
			break;
		};
	}
	return false;
}


Vec3 obj3::PointLineDist(Vec3 point, Vec3 linestart, Vec3 lineend)

{
	Vec3 a = lineend - linestart;
	Vec3 b = point - linestart;
	double t = a.DotXZ(b)/a.DotXZ(a);
	if (t < 0) t = 0;

	if (t > 1) t = 1;

	glBegin(GL_LINES);
	glVertex3dv((linestart+a*t).p);
	glVertex3dv(point.p);
	glEnd();

	return linestart + a * t;
}


obj3::CollisionResult obj3::calcCollisionEquasions(obj3 kreis) {
	//funktion für den quader um ihn auf 4 strecken zu reduzuieren

	Vec3 kreisMittelpunkt = kreis.getBallCenter();
	vector<Vec3> temp = qLow;
	vector<Vec3> temp2 = qHigh;

	temp.at(2) = qLow.at(3);
	temp.at(3) = qLow.at(2);

	temp2.at(2) = qHigh.at(3);
	temp2.at(3) = qHigh.at(2);


	double distance;
	Vec3 base;
	Vec3 collisionWall;

	for(int i=0; i<4 ;i++)
	{
		base = PointLineDist(kreisMittelpunkt, temp.at(i), temp.at((i+1) %4 ));

		distance = (kreisMittelpunkt - base).LengthXZ();
		if(distance  <= kreis.specs["radius"] )
		{
			printf("Collision, cause %f <= %f \n", (kreisMittelpunkt - base).LengthXZ() ,kreis.specs["radius"]);
			Vec3 xz = temp.at(i)-temp.at((i+1) %4 );
			Vec3 xy = temp.at(i) -temp2.at(i);

//			collisionWall = temp.at((i+1) %4 ) - temp.at(i);

			return {true, base, distance};
		}
	}
	return {false,
			Vec3(0,0,0),
			100};

}


Vec3 obj3::calcReflection(Vec3 base) {

	Vec3 nKugel, nQuader;
	double alpha = 0;

	nKugel = moveDirection;
	nQuader = base - getBallCenter();


	alpha = (nKugel.DotXZ(nQuader) / (nKugel.LengthXZ() * nQuader.LengthXZ()));


	double BallMoveDistance = nQuader.LengthXZ()/alpha;
	Vec3 PunktMitteZuWand = nKugel*BallMoveDistance;

	glBegin(GL_LINES);
	glVertex3dv((PunktMitteZuWand+getBallCenter()).p);
	glVertex3dv(getBallCenter().p);
	glEnd();

	Vec3 ZweiterEinschlagspunkt = getBallCenter() + PunktMitteZuWand ;
	Vec3 GespieglterPunktMittelpunkt = getBallCenter() + nQuader + nQuader;

	Vec3 result = ZweiterEinschlagspunkt - GespieglterPunktMittelpunkt;
	result.Normalize();

	return result;
}

Vec3 obj3::weirdCollision(Vec3 base) {

		Vec3 nKugel, nQuader;
		double alpha, radAlpha = 0;

		nKugel = moveDirection;
		nQuader = base - getBallCenter();

		alpha = acos(nKugel.DotXZ(nQuader) / (nKugel.LengthXZ() * nQuader.LengthXZ()));
		printf("the alpha = %f\n", alpha);

		radAlpha = (3.14159265359 / 180) * alpha ;
		printf("the radAlpha = %f\n", radAlpha);

		nKugel.p[0] = nKugel.p[0] * cos(radAlpha) - nKugel.p[2] * sin(radAlpha);
		nKugel.p[2] = nKugel.p[0] * sin(radAlpha) + nKugel.p[2] * cos(radAlpha);
		nKugel.Normalize();

		return nKugel;
}

void obj3::rotate(double alpha) { //Vec3 axis

	Vec3 erg = Vec3(0,0,0);

	glRenderMode(GL_FEEDBACK);
	float bufferich[24];
	glFeedbackBuffer(24, GL_3D, bufferich);
	glRotated(40, 0,1,0);


}

void obj3::draw() {

	if(mode == 'c'){
		int numPoints = 200;
		Vec3 points[numPoints];
		Vec3 pointsLow[numPoints];
		float Radius = (float)specs["radius"];
		float hight = (float)specs["hight"];
		float PI = 3.14159;

		glBegin( GL_QUAD_STRIP );

			for( int i=0; i<=numPoints; i++ )
			{
				float Angle = i * (2.0*PI/numPoints);
				float X = cos( Angle )*Radius + (float)specs["x"];
				float Y = (float)specs["y"];

				float Ylow = Y - hight;
				float Z = sin( Angle )*Radius + (float)specs["z"];
				points[i] = Vec3(X, Y, Z);
				glVertex3f( X, Y, Z);

				//normalenvektor der ebene berechnen
				if(i == 1 || i%2 == 1){
					Vec3 kreuz1 = points[i] - points[i-1];
					Vec3 kreuz2 = points[i-1] - pointsLow[i-1];
					Vec3 normal = kreuz1.CrossP(kreuz2);
					normal.Normalize();
					glNormal3f(normal.p[0], normal.p[1], normal.p[2]);

				}
				pointsLow[i]= Vec3(X, Ylow, Z);
				glVertex3f( X, Ylow, Z);
			}




		glEnd();

		glBegin( GL_POINTS);
			glVertex3f(this->specs["x"], this->specs["hight"], this->specs["z"]);
			glVertex3f(this->specs["x"], this->specs["hight"]/2, this->specs["z"]);
			glVertex3f(this->specs["x"], this->specs["hight"]/3, this->specs["z"]);
		glEnd();

	}

	if(mode == 'e'){
			int numPoints = 200;
			Vec3 points[numPoints];
			Vec3 pointsLow[numPoints];
			float Radius = (float)specs["radius"];
			float hight = (float)specs["hight"];
			float PI = 3.14159;

			glBegin( GL_QUAD_STRIP );

				for( int i=0; i<=numPoints; i++ )
				{
					float Angle = i * (2.0*PI/numPoints);
					float X = cos( Angle )*Radius + (float)specs["x"];
					float Y = (float)specs["y"];

					float Ylow = Y - hight;
					float Z = sin( Angle )*Radius + (float)specs["z"];
					points[i] = Vec3(X, Y, Z);
					glVertex3f( X, Y, Z);

					//normalenvektor der ebene berechnen
					if(i == 1 || i%2 == 1){
						Vec3 kreuz1 = points[i] - points[i-1];
						Vec3 kreuz2 = points[i-1] - pointsLow[i-1];
						Vec3 normal = kreuz1.CrossP(kreuz2);
						normal.Normalize();
						glNormal3f(normal.p[0], normal.p[1], normal.p[2]);

					}
					pointsLow[i]= Vec3(X, Ylow, Z);
					glVertex3f( X, Ylow, Z);
				}




			glEnd();

			glBegin( GL_POINTS);
				glVertex3f(this->specs["x"], this->specs["hight"], this->specs["z"]);
				glVertex3f(this->specs["x"], this->specs["hight"]/2, this->specs["z"]);
				glVertex3f(this->specs["x"], this->specs["hight"]/3, this->specs["z"]);
			glEnd();

		}


	if(mode == 'q'){

		Vec3 normal, axisX, axisY, axisZ;

		axisX = qLow.at(2) -qLow.at(0);		//a
		axisY = qHigh.at(0) - qLow.at(0);		//b
		axisZ = qLow.at(1) - qLow.at(0);		//e

		axisY.Normalize();
		axisX.Normalize();
		axisZ.Normalize();


		glBegin(GL_QUAD_STRIP);
//		glBegin(GL_LINE_STRIP);

//		glBegin(GL_POINTS);

		//unten
//		glNormal3f(0, -1, 0);
		glNormal3dv((axisY*(-1)).p);
		glVertex3dv(qLow.at(0).p);
		glVertex3dv(qLow.at(1).p);
		glVertex3dv(qLow.at(2).p);
		glVertex3dv(qLow.at(3).p);

		//rechts

//		glNormal3f(0,0,1);
		glNormal3dv(axisX.p);
//		Vec3 normal = (qLow.at(3)-qLow.at(2)).CrossP((qHigh.at(2)-qLow.at(2)));
//		glNormal3d(normal.p[0], normal.p[1], normal.p[2]);
		glVertex3dv(qHigh.at(2).p);
		glVertex3dv(qHigh.at(3).p);

		//oben
//		glNormal3f(0,-1,0);
		glNormal3dv(axisY.p);
//		normal = (qLow.at(3)-qLow.at(2)).CrossP((qHigh.at(2)-qLow.at(2)));
//		glNormal3d(normal.p[0], normal.p[1], normal.p[2]);
		glVertex3dv(qHigh.at(0).p);
		glVertex3dv(qHigh.at(1).p);

		glEnd();



		glBegin(GL_QUAD_STRIP);

//		glBegin(GL_LINES);
//		glBegin(GL_POINTS);

		glNormal3dv(axisZ.p);
		//vorne
		glVertex3dv(qHigh.at(3).p);
		glVertex3dv(qLow.at(3).p);

		glVertex3dv(qHigh.at(1).p);
		glVertex3dv(qLow.at(1).p) ;


		glNormal3dv((axisX*(-1)).p);
		//links
		glVertex3dv(qHigh.at(0).p);
		glVertex3dv(qLow.at(0).p);


		glNormal3dv((axisZ*(-1)).p);
		//hinten
		glVertex3dv(qHigh.at(2).p);
		glVertex3dv(qLow.at(2).p);

		glEnd();


	}

	if(mode == 'b'){
		// ---- sphere:
		double r = this->specs["radius"];
		const Vec3& ctr = Vec3(0,r,0);
		//params end

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
}

void obj3::moveAccordingToSpecs() {
	if(this->specs["curSpeed"] > 0){

		this->specs["curSpeed"] -= this->specs["step"];

		this->specs["x"] += this->moveDirection.p[0]/(100-this->specs["curSpeed"]);
		this->specs["z"] += this->moveDirection.p[2]/(100-this->specs["curSpeed"]);

//		printf("direction x: %f | y: %f \n", (float)direction.p[0], (float)direction.p[2]);
//		printf("moved to x: %f | y: %f \n", (float)this->specs["x"], (float)this->specs["z"]);
	}
}

Vec3 obj3::getBallCenter() {

	return Vec3(this->specs["x"],0,this->specs["z"] );
}

