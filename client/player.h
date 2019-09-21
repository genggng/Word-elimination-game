#pragma once
#include"user.h"

class  Player : public User //闯关者
{
private:
	int Exp;    //经验值
	int Chapter;  //游戏关卡

public:
	void SetChapter(int chapter );
	int GetChapter();
	void SetExp(int exp);
	int GetExp();
	Player(int exp = 0, int chapter = 1);

};