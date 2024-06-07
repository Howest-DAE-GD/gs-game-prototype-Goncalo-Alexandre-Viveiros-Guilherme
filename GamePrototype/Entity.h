#pragma once
class Entity
{
public:
	Entity(Point2f Position, Color4f color);
	~Entity();
	void Draw() const;
	void Update(float elapsedSec);

protected:
	Point2f m_Position;
	Point2f m_Velocity;
	Color4f m_Color;

private:
	
};

