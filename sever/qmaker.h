#pragma once
#include"user.h"

class Qmaker : public User //出题者
{
private:
	int QNumber; //出题数

public:
	void SetQNumber(int qnumber);
	int GetQNumber();
	Qmaker(int qnumber=0);
};

