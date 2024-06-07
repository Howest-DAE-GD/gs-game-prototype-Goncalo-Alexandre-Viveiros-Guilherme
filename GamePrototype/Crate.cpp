#include "pch.h"
#include "Crate.h"

#include "Texture.h"

Crate::Crate(Point2f position, const std::string& texturePath):Entity(position,Color4f(1,1,1,1)),
m_Texture(new Texture{ texturePath })
{
}

Crate::~Crate()
{
}

void Crate::Draw()
{
	m_Texture->Draw(Rectf(m_Position.x, m_Position.y, 100, 100),
		Rectf(0, 0, 100, 100));
}

Point2f Crate::GetPosition()
{
	return m_Position;
}
