#ifndef OBJ3_H_
#define OBJ3_H_


#include <map>
#include <string>
#include <iostream>
#include <cmath>
#include <vector>

#include "vec3.hpp"


using namespace std;
using std::map;


class obj3 {
public:
	map<string, double> specs;
	char mode;
	Vec3 moveDirection;
	Vec3 pCenter;

	std::vector<Vec3> qLow;
	std::vector<Vec3> qHigh;

	struct CollisionResult
	{
	      bool isCollided;
	      Vec3 collisionPoint;
	      double distanceSq;
	};


	obj3(char mode);
	virtual ~obj3();

	void buildSphere(Vec3 p, double r);
	void buildQuader(Vec3 p, double width, double length, double height);
	void buildQuader(Vec3 p, Vec3 width, Vec3 length, double height);
	void buildCone(float rad, float h, double x, double y, double z);
	void buildEnd(float r, float h, double x, double y, double z);


	obj3::CollisionResult calcCollisionEquasions(obj3 kreis);
	Vec3 PointLineDist(Vec3 point, Vec3 linestart, Vec3 lineend);
	Vec3 calcReflection(Vec3 base);
	Vec3 weirdCollision(Vec3 base);
	void rotate(double alpha);

	bool checkCollision(obj3 toCheck);
	void moveAccordingToSpecs();

	void draw();


	Vec3 getBallCenter();
};



#endif /* OBJ3_H_ */
