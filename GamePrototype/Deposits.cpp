#include "pch.h"
#include "Deposits.h"

#include "utils.h"

Deposits::Deposits(Point2f position, Color4f color):position{position},color{color}
{
}

Deposits::~Deposits()
{
}

void Deposits::Draw() const
{
	utils::SetColor(color);
	utils::DrawRect(position.x, position.y, 20, 20, 1);
}

Point2f Deposits::GetPosition()
{
	return position;
}
