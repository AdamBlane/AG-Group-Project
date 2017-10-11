#pragma once
//#include <glm-0.9.8.5\glm\glm\gtc\matrix_transform.hpp>
//#include <glm-0.9.8.5\glm\glm\gtc\quaternion.hpp>
//#include <glm-0.9.8.5\glm\glm\gtx\quaternion.hpp>
//#include <glm-0.9.8.5\glm\glm\gtx\euler_angles.hpp>
//#include <glm-0.9.8.5\glm\glm\glm.hpp>
//#include <glm-0.9.8.5\glm\glm\gtc\type_ptr.hpp>
#include "Camera.h"

namespace AllCamera 
{
	class target_camera : public camera
	{
		public:
			//constructor
			target_camera() : camera() {}
			//copy constructor
			target_camera(const target_camera &other) = default;
			//assignment operator
			target_camera& operator=(const target_camera &rhs) = default;
			//destructor
			~target_camera() {}
			//Updator
			void update(float delta_time);
	};
}