#pragma once
#include <vector>

#include "Entity.h"
#include "Keys.h"

class Crate;
class Hammer;
class Keys;
class Deposits;

class Player:public Entity
{
public:
	Player(Point2f position,Color4f color);
	~Player();
	void Update(const std::vector<std::vector<Point2f>>& platforms,float elapsedSec, std::vector<Deposits*>& deposits, Circlef safeCircle);
	void Draw() const;
	void Controls();
	bool GetIsWorking();
	bool GetIsDoingIllegal();
	Point2f GetPlayerPosition();
	void Reset();

private:
	bool m_IsDestroyed{false};
	bool m_IsWorking;
	bool m_IsDoingIllegal;
	bool m_IsHoldingHammer{ false };
	bool m_IsHoldingKey{ false };
	Point2f m_DistanceToDeposit;
	bool m_IsInteracting{false};
	bool m_AllKeysSafe{ false };
	std::vector<Keys*> m_KeysVec;
	Hammer* m_Hammer;
	Crate* m_Crate;
	Point2f m_StartPosition;
};

