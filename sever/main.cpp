#include<iostream>
#include<algorithm>
#include"file.h"
#include"game.h"
#include"sever.h"

using namespace std;

int main()
{
	extern  vector<Word> Vocabulary;
    extern  vector<Player> PlayerList;
    extern  vector<Qmaker> QmakerList;
	extern struct DEBUG TEST;

	GetVacabulary();
	GetPlayerList();
	GetQmakerList();
	Sever();
	return 0;

}
