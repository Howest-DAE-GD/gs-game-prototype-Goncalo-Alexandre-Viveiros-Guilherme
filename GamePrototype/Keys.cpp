#include "pch.h"
#include "Keys.h"

#include "utils.h"

Keys::Keys(Point2f position):Entity(position,Color4f(1,1,0,1))
{
}

Keys::~Keys()
{
}

void Keys::Draw()
{
	utils::SetColor(Color4f(1, 1, 0, 1));
	utils::DrawTriangle(Point2f(m_Position.x +10,m_Position.y - 5), Point2f(m_Position.x - 10, m_Position.y - 5), Point2f(m_Position.x, m_Position.y +10), 1);
}

void Keys::Update(Circlef safecircle)
{
	if (utils::IsOverlapping(m_Position, m_Position, safecircle))
	{
		isSafe = true;
	}
}

bool Keys::GetIsSafe()
{
	return isSafe;
}

Point2f Keys::GetPosition()
{
	return m_Position;
}

void Keys::SetPosition(float xAxis,float yAxis)
{
	m_Position.x = xAxis;
	m_Position.y = yAxis;
}

void Keys::SetIsSafeFalse()
{
	isSafe = false;
}
