#pragma once
#include "Entity.h"

class Texture;

class Crate:public Entity
{
public:
	Crate(Point2f position, const std::string& texturePath);
	~Crate();
	void Draw();
	Point2f GetPosition();
private:
	Texture* m_Texture;
};

