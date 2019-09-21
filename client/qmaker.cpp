#include "qmaker.h"

void Qmaker::SetQNumber(int qnumber)
{
	QNumber = qnumber;
}

int Qmaker::GetQNumber()
{
	return QNumber;
}

Qmaker::Qmaker(int qnumber)
{
	QNumber = qnumber;
}
