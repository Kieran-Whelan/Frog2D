#include "Transformation.hpp";

glm::mat4 getTransformationMatrix(glm::vec2 position)
{
	glm::mat4 transformationMatrix = glm::mat4(1.0f);
	transformationMatrix = glm::translate(transformationMatrix, glm::vec3(position.x, position.y, 0.0f));
	//transformationMatrix = glm::scale(transformationMatrix, glm::vec3(scale.x, scale.y, 0.0f));
	return transformationMatrix;
}

glm::mat4 getTransformationMatrix(glm::vec2 position, glm::vec2 scale)
{
	glm::mat4 transformationMatrix = glm::mat4(1.0f);
	transformationMatrix = glm::translate(transformationMatrix, glm::vec3(position.x, position.y, 0.0f));
	transformationMatrix = glm::scale(transformationMatrix, glm::vec3(scale.x, scale.y, 0.0f));
	return transformationMatrix;
}
