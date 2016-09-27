#pragma once
#include <glm/glm.hpp>
class Camera
{
public:
	Camera();
	~Camera();
	glm::vec3 position_;
	float yaw_, pitch_, roll_;
};

