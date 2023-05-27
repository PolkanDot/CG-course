#pragma once
#include "Includes/glm/ext/matrix_clip_space.hpp"
#include "Includes/glm/ext/matrix_transform.hpp"
class Cube
{
public:
	explicit Cube(float size = 1);
	void Draw(int x, int y) const;

	void SetSize(float size);
	void SetSpecularColor(glm::vec4 color);
	void SetShininess(float shininess);

private:
	float m_size;
	glm::vec4 m_specularColor = { 0, 0, 0, 1 };
	float m_shininess = 1;
};