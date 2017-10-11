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
	class chase_camera : public camera
	{
		private:
			//position of target
			glm::vec3 target_pos;
			//the offset of the camera position
			glm::vec3 pos_offset;
			//the rostaiom of the target
			glm::vec3 target_rotaion;
			//the rotaion of the camera 
			glm::vec3 rot_offset;
			//offset of the camera
			glm::vec3 target_offset;
			//the "springiness" of the camera (thats the technical term dont blame me for the shit name)
			float springiness;

		public:
			//constructor
			chase_camera() {}
			//destructor
			~chase_camera() {}

	};
}