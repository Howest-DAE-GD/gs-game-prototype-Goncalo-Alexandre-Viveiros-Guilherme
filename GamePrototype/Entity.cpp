#include "pch.h"
#include "Entity.h"

#include "utils.h"

Entity::Entity(Point2f Position,Color4f color):
	m_Position{Position},
	m_Color(color)
{
}

Entity::~Entity()
{
}

void Entity::Draw() const
{
	utils::SetColor(m_Color);
	utils::DrawEllipse(m_Position.x, m_Position.y, 10, 10, 2);
}

void Entity::Update(float elapsedSec)
{
	m_Position.y += m_Velocity.y * elapsedSec;
	m_Position.x += m_Velocity.x * elapsedSec;


	m_Velocity.x *= 0.98;
	m_Velocity.y *= 0.98;

	if (m_Velocity.x <3 && m_Velocity.x > -1 || m_Velocity.x > -3 && m_Velocity.x < 1)
	{
		m_Velocity.x = 0;
	}

	if (m_Velocity.y <3 && m_Velocity.y > -1 || m_Velocity.y > -3 && m_Velocity.y < 1)
	{
		m_Velocity.y = 0;
	}
}