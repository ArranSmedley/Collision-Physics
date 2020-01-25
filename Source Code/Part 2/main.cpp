#pragma region Includes
#pragma once
// Math constants
#define _USE_MATH_DEFINES
#include <cmath>  
#include <random>

// Std. Includes
#include <string>
#include <time.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include "glm/ext.hpp"

// Other Libs
#include "SOIL2/SOIL2.h"

// project includes
#include "Application.h"
#include "Shader.h"
#include "Mesh.h"
#include "Particle.h"
#include "RigidBody.h"

#include <iostream>
#include <random>
#include <chrono>
#include "Quadtree.h"

#include "Object.h"
using namespace glm;


#pragma endregion

void integrate(RigidBody& rb, double time, double deltaTime);
void impulse(RigidBody& rb, vec3 impulse, vec3 point);


Gravity g = Gravity(vec3(0, -9.8f, 0));
Quadtree quadtree(30.0f, 30.0f, 30.0f,30.0f, 3, 3);

vector<RigidBody*> objects;


const int maxballs = 50;
GLfloat distanceSquared(vec2 v);

// main function
int main()
{
	// create application

	Application app = Application::Application();
	app.initRender();
	Application::camera.setCameraPosition(glm::vec3(0.0f, 80.0f, 20.0f));

	/*Mesh walls = Mesh::Mesh(Mesh::CUBE);
	walls.setPos(vec3(0, 0, 0));
	walls.scale(glm::vec3(30.0f, 30.0f, 10.0f));
	Shader SHAD = Shader("resources/shaders/physics.vert", "resources/shaders/physics.frag");
	walls.setShader(SHAD);*/

	Mesh plane = Mesh::Mesh(Mesh::QUAD);

	Mesh wall = Mesh::Mesh(Mesh::CUBE);

	RigidBody rb[maxballs];
	RigidBody sphere;
	RigidBody rb2;
	Shader	rbShaderw = Shader("resources/shaders/physics.vert", "resources/shaders/solid_blue.frag");

	//Shader	rbShaderz = Shader("resources/shaders/physics.vert", "resources/shaders/solid_red.frag");
	//sphere.setMesh(Mesh("resources/models/sphere.obj"));
	//sphere.setPos(vec3(0, 0.5, 0));
	//sphere.getMesh().setShader(rbShaderw);
	//sphere.setMass(2.0f);
	////rb[i].addForce(&g);
	//sphere.translate(vec3(sphere.getPos().x, 0.5f, sphere.getPos().z));
	//sphere.setVel(vec3(3.0f, 0.0f, 3.0f));
	//sphere.setAngVel(vec3(0.5f, 0.5f, 0.5f));
	//sphere.setRadius(float(1.0f));
	//mat3 inertiamatrix = mat3(((sphere.getMass() * (pow(sphere.getRadius(), 2))) / 0.4), 0, 0, 0, (sphere.getMass() * (pow(sphere.getRadius(), 2)) / 0.4), 0, 0, 0, (sphere.getRadius() * (pow(1, 2)) / 0.4));
	//sphere.setInvInertia(inertiamatrix);

	//rb2.setMesh(Mesh("resources/models/sphere.obj"));
	//rb2.setPos(vec3(15, 0.5, 15));
	//rb2.getMesh().setShader(rbShaderz);
	//rb2.setMass(2.0f);
	////rb[i].addForce(&g);
	//rb2.translate(vec3(rb2.getPos().x, 0.5f, rb2.getPos().z));
	//rb2.setVel(vec3(0.0f, 0.0f, 0.0f));
	//rb2.setAngVel(vec3(0.5f, 0.5f, 0.5f));
	//rb2.setRadius(float(1.0f));
	//inertiamatrix = mat3(((rb2.getMass() * (pow(rb2.getRadius(), 2))) / 0.4), 0, 0, 0, (rb2.getMass() * (pow(rb2.getRadius(), 2)) / 0.4), 0, 0, 0, (rb2.getMass() * (pow(rb2.getRadius(), 2)) / 0.4));
	//rb2.setInvInertia(inertiamatrix);

	Shader	rbShader = Shader("resources/shaders/physics.vert", "resources/shaders/physics.frag");

	for (int i = 0; i < maxballs; i++)
	{

		rb[i].setMesh(Mesh("resources/models/sphere.obj"));
		rb[i].setPos(vec3(rand() % 15, 0.5, rand() % -15));
		rb[i].getMesh().setShader(rbShader);
		rb[i].setMass(2.0f);
		//rb[i].addForce(&g);
		rb[i].translate(vec3(rb[i].getPos().x, 0.5f, rb[i].getPos().z));
		rb[i].setVel(vec3(rand() % 20 - 20, 0, rand() % 20 - 20));
		rb[i].setAngVel(vec3(0.5f, 0.5f, 0.5f));
		rb[i].setRadius(float(1.0f));
		mat3 inertiamatrix = mat3(((rb[i].getMass() * (pow(rb[i].getRadius(), 2))) * 0.4), 0, 0, 0, (rb[i].getMass() * (pow(rb[i].getRadius(), 2)) * 0.4), 0, 0, 0, (rb[i].getMass() * (pow(rb[i].getRadius(), 2)) * 0.4));
		rb[i].setInvInertia(inertiamatrix);

		for (int i = 0; i < maxballs; i++)
		{
			for (int j = 0; j < maxballs; j++)
			{
				if (i != j)
				{
					if (distance(rb[i].getPos(), rb[j].getPos()) <= 2.5)
					{
						
						rb[i].setPos(vec3(rand() % 15, 0.5, rand() % -15));
					}
				}
			}

		}

		objects.push_back(rb);
	}





	// scale it up x5
	plane.setPos(vec3(0, 0, 0));
	plane.scale(glm::vec3(1000.0f, 30.0f, 1000.0f));
	Shader lambert = Shader("resources/shaders/physics.vert", "resources/shaders/physics.frag");
	plane.setShader(lambert);

	//Mesh m = Mesh::Mesh(Mesh::CUBE);

	//RigidBody rb = RigidBody();
	//m.scale(vec3(1, 3, 1));
	//rb.setMesh(sphere[0]);

	//Shader rbShader = Shader("resources/shaders/physics.vert", "resources/shaders/physics.frag");
	//rb.getMesh().setShader(rbShader);


	//rb.addForce(&g);

	//mat3 inertiamatrix = mat3(((rb.getMass() * (pow(2, 2) + pow(6, 2))) / 12), 0, 0,0, (rb.getMass() * (pow(2, 2) + pow(2, 2)) / 12), 0, 0, 0, (rb.getMass() * (pow(6, 2) + pow(2, 2)) / 12));

	//rb.setInvInertia(inertiamatrix);

	//std::cout << to_string(rb.getInvInertia()) << std::endl;

	bool impulseApplied = false;

	double time = 0.0f;
	double deltaTime = 0.001f;

	double currentTime = glfwGetTime();
	double accumulator = 0.0f;



	// Game loop
	while (!glfwWindowShouldClose(app.getWindow()))
	{
		double newTime = glfwGetTime();
		double frameTime = newTime - currentTime;
		currentTime = newTime;
		accumulator += frameTime;

		for (int i = 0; i < maxballs; i++)
		{

			if (rb[i].getPos().x >= 30|| rb[i].getPos().x <= -30 || rb[i].getPos().z >= 30 || rb[i].getPos().z <= -30)
			{
				rb[i].setVel(-rb[i].getVel());

			}
			for (int j = 0; j < maxballs; j++)
			{
				if (i != j)
				{
					if (distance(rb[i].getPos(), rb[j].getPos()) <= 2.5)
					{
	
						rb[i].setVel(-rb[i].getVel());
						rb[j].setVel(rb[j].getVel());
					}
				}
			}

		}

		while (accumulator >= deltaTime)
		{

			for (int i = 0; i < maxballs; i++)
			{
				rb[i].setInvInertia((rb[i].getRotate() * inverse(rb[i].getInvInertia()) * transpose(rb[i].getRotate())));

				integrate(rb[i], time, deltaTime);
			}
		



			//std::cout << "Collision Detected" << std::endl;


//for (int i = 0; i < maxballs; i++)
//{
//	float r0sqr = rb[0].getRadius() * rb[i].getRadius();
//	float r1sqr = rb[i].getRadius() * rb[i].getRadius();

//	float distX = rb[0].getPos().x - rb[i].getPos().x;
//	float distY = rb[0].getPos().y - rb[i].getPos().y;
//	float distZ = rb[0].getPos().z - rb[i].getPos().z;

//	// Since we already need to square these, we won't need to take the absolute value
//	// to accurately compare them to the radii
//	distX *= distX;
//	distY *= distY;
//	distZ *= distZ;

//	float sqrDist = (distX + distY + distZ);

//	float totalRadius = rb[0].getRadius()+ rb[i].getRadius();// the sum of the two spheres' radii
//	float dist = sqrt(sqrDist);// the actual distance between the two shapes' centers         
//	float minMovement = (totalRadius - dist);// the difference between the total radius and the actual distance tells us how far they intersect.

//	minMovement /= dist;// Divide by the distance to "scale" this movement so we can "scale" our distance vector (distX, distY, and distZ)

//	float mvmtX = distX * minMovement * 0.5f;// The minimum movement on the x-axis to resolve the collision
//	float mvmtY = distY * minMovement * 0.5f;// The minimum movement on the y-axis to resolve the collision
//	float mvmtZ = distZ * minMovement * 0.5f;// The minimum movement on the z-axis to resolve the collision

//	// For the sake of simplicity, we'll just have them "pop" out of each other, and won't
//	// be doing any interpolation to "smooth" the spheres' interaction.
//	//
//	// However, to ensure that we move the correct collider in the correct direction, we 
//	// need to see which one is on which side of the other, along the three axes.
//	if (rb[0].getPos().x == rb[i].getPos().x)
//	{
//		rb[0].getPos().x -= mvmtX;
//		rb[i].getPos().x += mvmtX;
//	}
//	else
//	{
//		rb[0].getPos().x += mvmtX;
//		rb[i].getPos().x -= mvmtX;
//	}

//
//	if (rb[0].getPos().z == rb[i].getPos().z)
//	{
//		rb[0].getPos().z -= mvmtZ;
//		rb[i].getPos().z += mvmtZ;
//	}
//	else
//	{
//		rb[0].getPos().z += mvmtZ;
//		rb[i].getPos().z -= mvmtZ;
//	}

//}



			accumulator -= deltaTime;
			time += deltaTime;
		}


		app.doMovement(deltaTime * 100);
		app.clear();
		app.draw(plane);

		
		for (int n = 0; n < maxballs; ++n) {

			quadtree.AddObject(&rb[n]);

	
			app.draw(rb[n].getMesh());

			
		}
		vector<RigidBody*> returnObjects = quadtree.GetObjectsAt(30, 30);
		cout << returnObjects.size() << endl;

		quadtree.Clear();

		app.display();
	}

	app.terminate();

	return EXIT_SUCCESS;
}



void impulse(RigidBody& rb, vec3 impulse, vec3 point)
{
	rb.setVel(impulse / rb.getMass());
	vec3 r = point - rb.getPos();
	rb.setAngVel(rb.getInvInertia() * (cross(r, impulse)));
}


void integrate(RigidBody& rb ,double time, double deltaTime)
{


	//Elasticity
	float e = 0.7f;

	//Calculate forces
	vec3 f = rb.applyForces(rb.getPos(), rb.getVel(), time, deltaTime);

	vec3 v = rb.getVel() + f / rb.getMass() * deltaTime;

	vec3 v2 = rb.getVel() + f / rb.getMass() * deltaTime;

	//Calculate position
	vec3 r = rb.getPos() + v * deltaTime;

	rb.setAngVel(rb.getAngVel() + deltaTime * rb.getAngAcc());

	//Calculate rotate matrix
	mat3 angVelSkew = matrixCross3(rb.getAngVel());
	mat3 R = mat3(rb.getRotate());
	R += deltaTime * angVelSkew * R;
	R = orthonormalize(R);

	rb.translate(r - rb.getPos());
	rb.setPos(r);
	rb.setVel(v);
	rb.setRotate(mat4(R));

	//Check for collision
	std::vector<Vertex> vert = rb.getMesh().getVertices();
	mat4 m = rb.getMesh().getModel();
	bool colResponce = false;
	std::vector<Vertex> vertices = std::vector<Vertex>();
	vec3 average = vec3();


	


	
	
	//int distance;
	//
	//	distance = sqrt((rb.getPos().x - rb2.getPos().x) * (rb.getPos().x - rb2.getPos().x) +
	//		(rb.getPos().y - rb2.getPos().y) * (rb.getPos().y - rb2.getPos().y) +
	//		(rb.getPos().z - rb2.getPos().z) * (rb.getPos().z - rb2.getPos().z));
	//	//std::cout << distance << std::endl;

	//
	//	if (distance < rb.getRadius() + rb2.getRadius())
	//	{
	//		rb.setVel(vec3(0, 0, 0));
	//	

	//			//position collision equals the average take away the position
	//			vec3 rcol = rb2.getPos();

	//			//speed collition equals the velocity + the cross product of the angular and position collision
	//			vec3 vcol = rb2.getVel() + cross(rb2.getAngVel(), rcol);

	//			//normal vec3
	//			vec3 n = vec3(0, 1, 0);

	//			//jr equation
	//			float jr = dot(-(1 + e) * vcol, n) / (rb.getMass() + rb2.getMass());

	//			vec3 vaftercol = rb2.getVel() + jr / rb2.getMass() * n;
	//			vec3 waftercol = rb2.getAngVel() - jr * rb2.getInvInertia() * cross(r, n);

	//			rb2.setVel(vaftercol);
	//			rb2.setAngVel(waftercol);
	//		
	//	}
}



