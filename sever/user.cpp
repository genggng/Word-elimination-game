#include "user.h"



void User::SetLevel(int level=0)
{
	Level = level;
}

void User::SetName(string name)
{
	Name = name;
}

void User::SetPassWord(string password)
{
	PassWord = password;
}


int User::GetLevel()
{
	return Level;
}

string User::GetName()
{
	return Name;
}

string User::GetPassWord()
{
	return PassWord;
}

bool User::operator==(const string& name)
{
	return this->Name == name;
}

User::User(int level)
{
	Level = level;
}