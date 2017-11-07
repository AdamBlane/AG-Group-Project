#pragma once
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
			glm::vec3 camera_rot;
			//offset of the camera
			glm::vec3 target_offset;
			//the "springiness" of the camera (thats the technical term dont blame me for the shit name)
			float springiness;

		public:
			//constructor
			chase_camera() {}
			//destructor
			~chase_camera() {}
			
			glm::vec3 get_target_pos() const { return target_pos; }
			void set_target_pos(const glm::vec3 &value) { target_pos = value; }

			glm::vec3 get_pos_offset() const { return pos_offset; }
			void set_pos_offset(const glm::vec3 &value) { pos_offset = value; }

			glm::vec3 get_target_rotation() const { return target_rotaion; }
			void set_target_roation(const glm::vec3 &value) { target_rotaion = value; }

			glm::vec3 get_target_offset() const { return target_offset; }
			void set_target_offset(const glm::vec3 &value) { target_offset = value; }

			glm::vec3 get_relative_rotation() const { return camera_rot; }
			void set_relative_rotation(const glm::vec3 &value) { camera_rot = value; }

			float get_springiness() const { return springiness; }
			void set_springiness(float value) { springiness = value; }

			void update(float delta_time);
			void move(const glm::vec3 &new_target_pos, const glm::vec3 &new_target_rotation);
			void rotate(const glm::vec3 &delta_rotation);
			void pitch_it(float rot, const glm::vec3 &target_location, const glm::vec3 &cam_location , float y_);
			void yaw_it(float rot);
			void neg_yaw_it(float rot);
			void neg_pitch_it(float rot, const glm::vec3 &target_location, const glm::vec3 &cam_location ,float y_ );
			void zoom_in(float rot);
			void zoom_out(float rot);
	};
}