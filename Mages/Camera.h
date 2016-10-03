#pragma once
#include <glm/glm.hpp>
class Camera
{
public:
	Camera();
	~Camera();
	glm::vec3 position_;
	float roll_, pitch_, yaw_;
};

