#include "pch.h"
#include "Elf.h"

#include <iostream>

#include "Player.h"
#include "utils.h"

Elf::Elf(Point2f position, Color4f color) :Entity(position, color), startPosition{ position }
{
	m_Position = position;
}

Elf::~Elf()
{
}

void Elf::Draw()
{
	Entity::Draw();
	utils::DrawPolygon(Points);
}

void Elf::Update(float elapsedSec, Player*& player,std::vector<Point2f> PatrolPoints)
{
	Points[0] = m_Position;
	

	if (startCycle!= Cycle::null)
	{
		currentCycle = startCycle;

		startCycle = Cycle::null;	
	}
	


	Entity::Update(elapsedSec);

	if (player->GetIsWorking() == true)
	{
		Timer += elapsedSec;

		if (Timer > 4)
		{
			Timer = 0;
		}
	}

	if (utils::IsOverlapping(Points, Circlef(player->GetPlayerPosition(),10)))
	{
		if (player->GetIsDoingIllegal() == true) 
		{
			player->Reset();
			Reset();
		}

		if (player->GetIsWorking() == true)
		{
			Timer += elapsedSec;

			if (Timer >4)
			{
				if (PatrolPoints.size() == 0)
				{
					currentCycle = Cycle::Patrol;
					Timer = 0;
				}

				else
				{
					currentCycle = Cycle::WalkPatrol;
					Timer = 0;
				}
			}
		}

		if (player->GetIsWorking() == false)
		{
			currentCycle = Cycle::Watch;
		}
		
	}

	if (currentCycle == Cycle::Patrol)
	{
		if (PatrolPoints.size() == 0)
		{
			currentCycle = Cycle::Patrol;
		}

		else
		{
			currentCycle = Cycle::WalkPatrol;
		}

		Timer += elapsedSec;
		Eyeline = 250;

		m_Position = startPosition;

		Points[0] = m_Position;

		if (opposite == true)
		{
			m_Angle -= float(rand() % 6) / 1000;
		

			if (Timer > rand() % 5 + 10)
			{
				opposite = false;
				Timer = 0;
			}
			
		}
		else
		{
			m_Angle += float(rand() % 6) / 1000;
		}
		
		Points[0] = m_Position;
		Points[2] = m_Position + Vector2f(cos(m_Angle), sin(m_Angle)) * Eyeline;
		Points[1] = m_Position + Vector2f(cos(m_Angle + M_PI / 4), sin(m_Angle + M_PI / 4)) * Eyeline;
		Points[3] = m_Position + Vector2f(cos(m_Angle - M_PI / 4), sin(m_Angle - M_PI / 4)) * Eyeline;

		if (opposite == false)
		{
			if (Timer > rand() % 5 + 10)
			{
				opposite = true;
				Timer = 0;
			}
		}
		
		lastCycle = currentCycle;
	}

	if (currentCycle == Cycle::WalkPatrol)
	{
		Eyeline = 100;

		if (lastCycle != currentCycle)
		{
			m_CurrentPatrolPoint = 0;
			m_Position = PatrolPoints[0];
		}
	
	
		if (m_Position.x < PatrolPoints[m_CurrentPatrolPoint].x)
		{
			m_Velocity.x = 80;
		}

		else if (m_Position.x > PatrolPoints[m_CurrentPatrolPoint].x)
		{

			m_Velocity.x = -80 ;
		}


		if (m_Position.y < PatrolPoints[m_CurrentPatrolPoint].y)
		{

			m_Velocity.y = 80;
		}

		else if (m_Position.y > PatrolPoints[m_CurrentPatrolPoint].y)
		{

			m_Velocity.y = -80 ;
		}

		m_Angle = atan2f(m_Velocity.y,m_Velocity.x);
		Points[0] = m_Position;
		Points[2] = m_Position + Vector2f(cos(m_Angle), sin(m_Angle)) * Eyeline;
		Points[1] = m_Position + Vector2f(cos(m_Angle + M_PI / 4), sin(m_Angle + M_PI / 4)) * Eyeline;
		Points[3] = m_Position + Vector2f(cos(m_Angle - M_PI / 4), sin(m_Angle - M_PI / 4)) * Eyeline;

		if (m_Position.x + 10 > PatrolPoints[m_CurrentPatrolPoint].x && m_Position.x - 10 < PatrolPoints[m_CurrentPatrolPoint].x
			&& m_Position.y + 10 > PatrolPoints[m_CurrentPatrolPoint].y && m_Position.y - 10 < PatrolPoints[m_CurrentPatrolPoint].y)
		{
			if (m_IsPatrolReversed == true)
			{
				m_CurrentPatrolPoint -= 1;

				if (m_CurrentPatrolPoint == -1)
				{
					m_CurrentPatrolPoint = 0;
					m_IsPatrolReversed = false;
				}
			}
			else
			{
				m_CurrentPatrolPoint += 1;

				if (m_CurrentPatrolPoint == PatrolPoints.size() -1)
				{
					m_IsPatrolReversed = true;
				}
				
			}
		}

		lastCycle = currentCycle;
	}

	if (currentCycle == Cycle::Watch)
	{
		Eyeline = 70;

		// Calculate angle towards player
		Vector2f toPlayer = player->GetPlayerPosition() - m_Position;
		float angleToPlayer = atan2f(toPlayer.y, toPlayer.x);
		m_Angle = angleToPlayer; // Set the Elf's angle to face the player

		// Update points to draw the line
		Points[0] = m_Position;
		Points[2] = m_Position + Vector2f(cos(m_Angle), sin(m_Angle)) * Eyeline;
		Points[1] = m_Position + Vector2f(cos(m_Angle + M_PI / 4), sin(m_Angle + M_PI / 4)) * Eyeline;
		Points[3] = m_Position + Vector2f(cos(m_Angle - M_PI / 4), sin(m_Angle - M_PI / 4)) * Eyeline;

		if (player->GetPlayerPosition().x - 30 > m_Position.x)
		{
			m_Velocity.x += 10;
		}

		else if (player->GetPlayerPosition().x + 30 < m_Position.x)
		{
			m_Velocity.x -= 10;
		}

		if (player->GetPlayerPosition().y - 30 > m_Position.y)
		{
			m_Velocity.y += 10;
		}

		else if (player->GetPlayerPosition().y + 30 < m_Position.y)
		{
			m_Velocity.y -= 10;
		}

		lastCycle = currentCycle;

	}

	
}

void Elf::Debug()
{
	
}

void Elf::Reset()
{
	m_Position = startPosition;
	m_CurrentPatrolPoint = 0;
	m_IsPatrolReversed = false;
	startCycle = Cycle::Patrol;
	Timer = 0;

}
