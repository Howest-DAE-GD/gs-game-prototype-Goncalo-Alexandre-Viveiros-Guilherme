#include "pch.h"
#include "Hammer.h"
#include "Texture.h"

Hammer::Hammer(Point2f position, const std::string& texturePath):Entity(position,Color4f(1,1,1,1)),
m_Texture(new Texture{ texturePath })
{

}

Hammer::~Hammer()
{
	delete m_Texture;
}

void Hammer::Draw()
{

	m_Texture->Draw(Rectf(m_Position.x, m_Position.y, 50, 50),
		Rectf(0, 0,100,100));

}

Point2f Hammer::GetPosition()
{
	return m_Position;
}

void Hammer::SetPosition(float xAxis, float yAxis)
{
	m_Position.x = xAxis;
	m_Position.y = yAxis;
}
