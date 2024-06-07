#pragma once
class Deposits
{
public:
	Deposits(Point2f position,Color4f color);
	~Deposits();
	void Draw() const;
	Point2f GetPosition();

private:
	Color4f color;
	Point2f position;
};

