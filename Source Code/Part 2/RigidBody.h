#pragma once
#include "Body.h"

class RigidBody : 
	public Body
{
public: RigidBody();
	  ~RigidBody();

	  void setAngVel(const glm::vec3& omega) { m_angVel = omega; } 
	  void setAngAccl(const glm::vec3& alpha) { m_angAcc = alpha; } 
	  void setInvInertia(const glm::mat3& invInertia) { m_invInertia = invInertia; }
	  void setRadius(const float &radius) { m_radius = radius; }

	  glm::vec3 getAngVel() { return m_angVel; } 
	  glm::vec3 getAngAcc() { return m_angAcc; } 
	  glm::mat3 getInvInertia() { return m_invInertia; } 

	  float getRadius() { return m_radius; }
	  void scale(glm::vec3 vect);

private: 
	float m_density; 
	glm::mat3 m_invInertia; // Inverse Inertia 
	glm::vec3 m_angVel; // angular velocity 
	glm::vec3 m_angAcc; // angular acceleration 

	float  m_radius;


};

