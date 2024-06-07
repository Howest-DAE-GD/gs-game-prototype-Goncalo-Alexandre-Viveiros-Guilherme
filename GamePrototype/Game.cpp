#include "pch.h"
#include "Game.h"

#include <iostream>

#include "Player.h"
#include "Elf.h"
#include "Deposits.h"
#include "SVGParser.h"
#include "utils.h"


Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_Player = new Player(Point2f(425, 250), Color4f(0, 1, 0, 1));
	m_Elf = new Elf(Point2f(407,478 ), Color4f(1, 0, 0, 1));
	m_Elf2 = new Elf(Point2f(997, 1381), Color4f(1, 0, 0, 1));
	m_Elf3 = new Elf(Point2f(672, 1330), Color4f(1, 0, 0, 1));
	m_Elf4 = new Elf(Point2f(-15, 1408), Color4f(1, 0, 0, 1));
	m_Elf5 = new Elf(Point2f(-1154, -820), Color4f(1, 0, 0, 1));
	m_Elf6 = new Elf(Point2f(-1627, -630), Color4f(1, 0, 0, 1));
	m_Elf7 = new Elf(Point2f(1666, -490), Color4f(1, 0, 0, 1));

	m_Deposit = new Deposits(Point2f(450, 450), Color4f(1, 1, 0, 1));
	m_Deposit2 = new Deposits(Point2f(1176, 1071), Color4f(1, 1, 0, 1));
	m_Deposit3 = new Deposits(Point2f(1289, -480), Color4f(1, 1, 0, 1));
	m_Deposit4 = new Deposits(Point2f(-1664, -883), Color4f(1, 1, 0, 1));
	m_Deposit5 = new Deposits(Point2f(1081, 1731), Color4f(1, 1, 0, 1));

	m_DepositsVector.push_back(m_Deposit);
	m_DepositsVector.push_back(m_Deposit2);
	m_DepositsVector.push_back(m_Deposit3);
	m_DepositsVector.push_back(m_Deposit4);
	m_DepositsVector.push_back(m_Deposit5);

	SVGParser::GetVerticesFromSvgFile("map.svg", m_LvlVertices);

	m_1stPatrolRoute.push_back(Point2f(997, 1381));
	m_1stPatrolRoute.push_back(Point2f(1076, 1529));
	m_1stPatrolRoute.push_back(Point2f(897, 1728));
	m_1stPatrolRoute.push_back(Point2f(602, 1893));
	m_1stPatrolRoute.push_back(Point2f(602, 2106));

	m_2ndPatrolRoute.push_back(Point2f(-1627, -630));
	m_2ndPatrolRoute.push_back(Point2f(-1911, -347));
	m_2ndPatrolRoute.push_back(Point2f(-1981, 257));
	m_2ndPatrolRoute.push_back(Point2f(-1993, 588));
	m_2ndPatrolRoute.push_back(Point2f(-1914, 1457));
	m_2ndPatrolRoute.push_back(Point2f(-1727, 1627));

	m_3rdPatrolRoute.push_back(Point2f(1666, -490));
	m_3rdPatrolRoute.push_back(Point2f(924, -356));
	m_3rdPatrolRoute.push_back(Point2f(497, -179));

}

void Game::Cleanup( )
{
	delete m_Player;
	m_Player = nullptr;
	delete m_Elf;
	m_Elf = nullptr;

	delete m_Elf2;
	m_Elf2 = nullptr;

	delete m_Elf3;
	m_Elf3 = nullptr;

	delete m_Elf4;
	m_Elf4 = nullptr;

	delete m_Elf5;
	m_Elf5 = nullptr;

	delete m_Elf6;
	m_Elf6 = nullptr;

	delete m_Elf7;
	m_Elf7 = nullptr;

	delete m_Deposit;
	m_Deposit = nullptr;
}

void Game::Update( float elapsedSec )
{
	m_Player->Update(m_LvlVertices,elapsedSec,m_DepositsVector,safeCircle);

	m_Elf->Update(elapsedSec, m_Player,m_emptyPatrolRoute);
	m_Elf2->Update(elapsedSec, m_Player,m_1stPatrolRoute);
	m_Elf3->Update(elapsedSec, m_Player, m_emptyPatrolRoute);
	m_Elf4->Update(elapsedSec, m_Player, m_emptyPatrolRoute);
	m_Elf5->Update(elapsedSec, m_Player, m_emptyPatrolRoute);
	m_Elf6->Update(elapsedSec, m_Player, m_2ndPatrolRoute);
	m_Elf7->Update(elapsedSec, m_Player, m_3rdPatrolRoute);
	m_Player->Controls();

}

void Game::Draw( ) const
{
	glPushMatrix();
	{
		glTranslatef(-m_Player->GetPlayerPosition().x +425, -m_Player->GetPlayerPosition().y+250, 0);


		ClearBackground();
		for (int idx = 0; idx < m_LvlVertices.size(); idx++)
		{
			utils::DrawPolygon(m_LvlVertices[idx]);
		}

		m_Player->Draw();
		m_Elf->Draw();
		m_Elf2->Draw();
		m_Elf3->Draw();
		m_Elf4->Draw();
		m_Elf5->Draw();
		m_Elf6->Draw();
		m_Elf7->Draw();

		m_Deposit->Draw();
		m_Deposit2->Draw();
		m_Deposit3->Draw();
		m_Deposit4->Draw();
		m_Deposit5->Draw();

		utils::SetColor(Color4f(1, 0, 1, 1));
		utils::DrawEllipse(safeCircle.center, safeCircle.radius, safeCircle.radius, 1);
		
	}
	glPopMatrix();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;

}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
