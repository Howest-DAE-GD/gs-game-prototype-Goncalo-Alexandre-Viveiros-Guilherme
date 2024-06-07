#pragma once
#include "Entity.h"

class Texture;
class Hammer:public Entity
{
public:
	Hammer(Point2f position, const std::string& texturePath);
	~Hammer();
	void Draw();
	Point2f GetPosition();
	void SetPosition(float xAxis, float yAxis);

private:
	Texture* m_Texture;

};

