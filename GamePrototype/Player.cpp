#include "pch.h"
#include "Player.h"

#include <iostream>

#include "Crate.h"
#include "Hammer.h"
#include "Deposits.h"
#include "utils.h"

Player::Player(const Point2f position, const Color4f color):Entity(position,color), m_StartPosition{position}
{
	m_KeysVec.push_back(new Keys(Point2f( - 207, 1492)));
	m_KeysVec.push_back(new Keys(Point2f( -1166, 1773)));
	m_KeysVec.push_back(new Keys(Point2f( 1795, -886)));
	m_KeysVec.push_back(new Keys(Point2f( 318, 248)));
	
	m_Hammer = new Hammer(Point2f(658, 2172), "Hammer.png");
	m_Crate = new Crate(Point2f(700, 300), "Crate.png");
}

Player::~Player()
{
}

void Player::Update(const std::vector<std::vector<Point2f>>& platforms,const float elapsedSec, std::vector<Deposits*>& deposits, const Circlef safeCircle)
{
	Entity::Update(elapsedSec);

	//Collision
	utils::HitInfo hit_info;

	for (int idx{ 0 }; idx < platforms.size(); idx++)
	{

		if (utils::Raycast(platforms[idx], Point2f{ m_Position.x,m_Position.y +10},
			Point2f{ m_Position.x,m_Position.y - 10 }, hit_info))
		{
			m_Velocity.x *= -1.f;
			m_Velocity.y *= -1.f;
			break;
		}

		else if (utils::Raycast(platforms[idx], Point2f{ m_Position.x + 10 ,m_Position.y},
			Point2f{ m_Position.x - 10 ,m_Position.y}, hit_info))
		{
			m_Velocity.x *= -1.f;
			m_Velocity.y *= -1.f;
			break;
		}
	}

	for (int idx{ 0 }; idx < deposits.size(); idx++)
	{
		m_DistanceToDeposit.x = deposits[idx]->GetPosition().x - m_Position.x;
		m_DistanceToDeposit.y = deposits[idx]->GetPosition().y - m_Position.y;

		if (m_DistanceToDeposit.x < 40 && m_DistanceToDeposit.y < 40 && m_DistanceToDeposit.x > -40 && m_DistanceToDeposit.y > -40)
		{
			if (m_IsInteracting == true)
			{
				m_IsWorking = true;

				m_Color = Color4f(1, 1, 1, 1);
			}

			else
			{
				m_IsWorking = false;
				m_Color = Color4f(0, 1, 0, 1);
			}
		}
	}
	

	if (m_Velocity.x > 1 || m_Velocity.y > 1 || m_Velocity.x < -1 || m_Velocity.y < -1)
	{
		m_IsWorking = false;
		m_IsInteracting = false;
		m_Color = Color4f(0, 1, 0, 1);
	}

	for (int idx = 0; idx < m_KeysVec.size(); idx++)
	{
		m_KeysVec[idx]->Update(safeCircle);
	}
	

	//crate
	if (m_IsHoldingHammer == true)
	{
		if (m_IsDestroyed == false)
		{
			if (utils::IsOverlapping(Rectf(m_Crate->GetPosition().x, m_Crate->GetPosition().y, 100, 100), Circlef(m_Position, 10)))
			{
				m_KeysVec.push_back(new Keys(m_Crate->GetPosition()));
				m_IsHoldingHammer = false;
				m_IsDestroyed = true;
			}
		}
	}
	

	//Hammer stuff


		if (m_IsDestroyed == false)
		{
			if (utils::IsOverlapping(Rectf(m_Hammer->GetPosition().x, m_Hammer->GetPosition().y, 50, 50), Circlef(m_Position, 10)))
			{
				m_Hammer->SetPosition(m_Position.x, m_Position.y);
				m_IsDoingIllegal = true;
				m_IsHoldingHammer = true;
			}
		}
		
	
	


	//key stuff
	for (int idx = 0; idx < m_KeysVec.size(); idx++)
	{
		if (m_IsHoldingHammer == false)
		{
			if (utils::IsOverlapping(m_KeysVec[idx]->GetPosition(), m_KeysVec[idx]->GetPosition(), Circlef(m_Position, 10)))
			{
				if (m_KeysVec[idx]->GetIsSafe() == false)
				{
					m_KeysVec[idx]->SetPosition(m_Position.x, m_Position.y);
					m_IsDoingIllegal = true;
					break;
				}

			}
			
			else
			{
				m_IsDoingIllegal = false;
			}
		}
		
	}

	
	if (m_KeysVec.size() > 4)
	{
		for (int idx = 0; idx < m_KeysVec.size(); idx++)
		{
			if (m_KeysVec[idx]->GetIsSafe() == true)
			{
				m_AllKeysSafe = true;
			}
			else
			{
				m_AllKeysSafe = false;
				break;
			}
		}
	}
	


	
	if (m_AllKeysSafe == true)
	{
		std::cout << "YOU WON!";

	}


	
}

void Player::Draw() const
{
	utils::SetColor(m_Color);
	utils::DrawEllipse(m_Position.x, m_Position.y, 10, 10, 2);

	//draws Keys
	for (int idx = 0; idx < m_KeysVec.size(); idx++)
	{
		m_KeysVec[idx]->Draw();
	}

	if (m_IsDestroyed == false)
	{
		m_Hammer->Draw();
		m_Crate->Draw();
	}
	
	
}

void Player::Controls()
{
	const Uint8* pKeyStates = SDL_GetKeyboardState(nullptr);
	if (pKeyStates[SDL_SCANCODE_LEFT])
	{
		m_Velocity.x -= 9;
	}
	if (pKeyStates[SDL_SCANCODE_RIGHT])
	{
		m_Velocity.x += 9;
	}
	if (pKeyStates[SDL_SCANCODE_UP])
	{
		m_Velocity.y += 9;
	}
	if (pKeyStates[SDL_SCANCODE_DOWN])
	{
		m_Velocity.y -= 9;
	}
	if (pKeyStates[SDL_SCANCODE_E])
	{
		m_IsInteracting = true;
	}
	
}


bool Player::GetIsWorking()
{
	return m_IsWorking;
}

bool Player::GetIsDoingIllegal()
{
	return m_IsDoingIllegal;
}

Point2f Player::GetPlayerPosition()
{
	return m_Position;
}

void Player::Reset()
{
	m_Position = m_StartPosition;
	m_IsDoingIllegal = false;
	m_IsInteracting = false;
	m_IsWorking = false;
	m_AllKeysSafe = false;
	m_IsHoldingHammer = false;
	for (int idx = 0; idx < m_KeysVec.size(); idx++)
	{
		m_KeysVec[idx]->SetIsSafeFalse();
	}
	m_KeysVec[0]->SetPosition(-207, 1492);
	m_KeysVec[1]->SetPosition(-1166, 1773);
	m_KeysVec[2]->SetPosition(1795, -886);
	m_KeysVec[3]->SetPosition(318, 248);
	if (m_KeysVec.size() > 4)
	{
		m_KeysVec.pop_back();
	}
	m_IsDestroyed = false;
	m_Hammer->SetPosition(658, 2172);


	
}

