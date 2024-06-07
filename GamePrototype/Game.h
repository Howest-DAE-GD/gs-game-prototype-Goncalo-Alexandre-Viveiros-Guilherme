#pragma once
#include <vector>

#include "BaseGame.h"
class Deposits;
class Elf;
class Player;

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;

	Player* m_Player;
	Elf* m_Elf;
	Elf* m_Elf2;
	Elf* m_Elf3;
	Elf* m_Elf4;
	Elf* m_Elf5;
	Elf* m_Elf6;
	Elf* m_Elf7;
	
	Deposits* m_Deposit;
	Deposits* m_Deposit2;
	Deposits* m_Deposit3;
	Deposits* m_Deposit4;
	Deposits* m_Deposit5;

	std::vector<Deposits*> m_DepositsVector;
	Circlef safeCircle{ Point2f(90,90),80 };
	std::vector<std::vector<Point2f>> m_LvlVertices;

	std::vector<Point2f> m_1stPatrolRoute;
	std::vector<Point2f> m_2ndPatrolRoute;
	std::vector<Point2f> m_3rdPatrolRoute;
	std::vector<Point2f> m_emptyPatrolRoute;

};
