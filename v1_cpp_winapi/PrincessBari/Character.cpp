#include "Character.h"

int Character::GetX()
{
	return x;
}

int Character::GetY()
{
	return y;
}

int Character::GetMhp()
{
	return mhp;
}

int Character::GetHp()
{
	return hp;
}

int Character::GetAtt()
{
	return att;
}

int Character::GetState()
{
	return state;
}

int Character::GetDirection()
{
	return direction;
}

int Character::GetIndex()
{
	return index;
}

int Character::GetNumberOfSprite()
{
	return numberOfSprite[state];
}

HBITMAP Character::GetBitmap()
{
	return hMotion[state + direction];
}

HBITMAP Character::GetHpGage()
{
	return hHpGage;
}

void Character::HpMinus( int amount )
{
	hp -= amount;
}

void Character::ChangeState( int state )
{
	if (this->state != state)
	{
		this->state = state;
		index = 0;
	}
}

void Character::IncreaseIndex()
{
	index++;
	if (index >= numberOfSprite[state])
	{
		index = 0;
	}
}

void Character::ChangeDirection(int direction)
{
	this->direction = direction;
}

void Character::ChangeX( int amount )
{
	x += amount;
	if(x < 320) x = 320;
	if(x > 1600) x = 1600;
}

void Character::ChangeY( int amount )
{
	y += amount;
}