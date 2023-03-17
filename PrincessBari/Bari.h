#ifndef _BARI_H_
#define _BARI_H_
#define NEEDEDEXPFORLEVELUP 100
#include "Character.h"

class Bari : public Character
{
private:
	HBITMAP hBariHpGage;
	int level;
	int exp;
public:
	Bari(HINSTANCE hInst);
	~Bari();
	HBITMAP GetBariHpGage();
	int GetLevel();
	int GetExp();
	void ExpUp(int amount);
};

#endif