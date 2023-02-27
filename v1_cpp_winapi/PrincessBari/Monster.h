#ifndef _MONSTER_H_
#define _MONSTER_H_
#include "Character.h"

class Monster : public Character
{
private:
	HBITMAP hMonsterHpGage;
public:
	Monster(HINSTANCE hInst, int foothold[][3]);
	~Monster();
	HBITMAP GetMonsterHpGage();
};

#endif