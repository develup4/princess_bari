#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#define NUMBEROFMOTION 16
#define RIGHT 0
#define LEFT 8
#include <windows.h>

class Character
{
protected:
	enum {Stop, Move, Stun, Dead, Combo1, Combo2, Jump};
	int x;
	int y;
	int mhp;
	int hp;
	int att;
	int state;
	int direction;
	int index;
	int numberOfSprite[NUMBEROFMOTION / 2]; //�¿찡 �����ϹǷ�
	HBITMAP hMotion[NUMBEROFMOTION];
	HBITMAP hHpGage;
public:
	int GetX();
	int GetY();
	int GetMhp();
	int GetHp();
	int GetAtt();
	int GetState();
	int GetDirection();
	int GetIndex();
	int GetNumberOfSprite();
	HBITMAP GetBitmap();
	HBITMAP GetHpGage();
	void ChangeX(int amount);
	void ChangeY(int amount); //���� ȭ���� ��ǥ�� �ƴ� ���� ��ǥ
	void HpMinus(int amount);
	void ChangeState(int state);
	void ChangeDirection(int direction);
	void IncreaseIndex();
};

#endif