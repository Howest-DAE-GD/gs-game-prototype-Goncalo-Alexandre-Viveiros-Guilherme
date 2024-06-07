#pragma once
#include "Entity.h"

class Keys:public Entity
{
public:
	Keys(Point2f position);
	~Keys();
	void Draw();
	void Update(Circlef safecircle);
	bool GetIsSafe();
	Point2f GetPosition();
	void SetPosition(float xAxis, float yAxis);
	void SetIsSafeFalse();

private:
	bool isSafe {false};
};

