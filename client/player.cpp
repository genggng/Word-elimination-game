#include "player.h"

void Player::SetChapter(int chapter)
{
	Chapter = chapter;
}

int Player::GetChapter()
{
	return Chapter;
}
void Player::SetExp(int exp = 0)
{
	Exp = exp;
}
int Player::GetExp()
{
	return Exp;
}

Player::Player(int exp,int chapter)
{
	Exp = exp;
	Chapter = chapter;
}
