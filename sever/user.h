#pragma once
#include<string>
using namespace std;

class User     // 用户
{
protected:
	string Name;    //用户名
	string PassWord; //密码
	int Level; //等级

public:
	void SetName(string name);
	void SetPassWord(string password);
	void SetLevel(int level);
	int GetLevel();
	string GetName();
	string GetPassWord();
	bool operator ==(const string& name);
	User(int level = 1);

};
