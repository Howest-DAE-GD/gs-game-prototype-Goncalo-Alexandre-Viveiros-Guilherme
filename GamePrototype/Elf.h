#pragma once
#include <vector>

#include "Entity.h"

class Player;

class Elf :public Entity
{
public:
	Elf(Point2f position, Color4f color);
	~Elf();
	void Draw();
	void Update(float elapsedSec,Player* &playerobject, std::vector<Point2f> PatrolPoints);
	void Debug();
	void Reset();

private:
	enum class Cycle
	{
		Patrol,
		WalkPatrol,
		Watch,
		null
	};

	Cycle startCycle{Cycle::Patrol};
	Cycle currentCycle{};
	Cycle lastCycle{};
	std::vector<Point2f> Points{4};
	Point2f AnglePoint{};
	float m_Angle{0};
	float Timer{0};
	float Eyeline{40};
	bool opposite{ false };
	int m_CurrentPatrolPoint{ 0 };
	bool m_IsPatrolReversed{ false };
	Point2f startPosition;
};

