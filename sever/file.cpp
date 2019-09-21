#include<fstream>
#include"file.h"

using namespace std;

vector<Word> Vocabulary;
vector<Player> PlayerList;
vector<Qmaker> QmakerList;
struct DEBUG TEST; //用于测试维护
int wordper[15] = { 0,1,2,36,163,322,496,657,783,873,935,970,985,996,1000 };//用于平衡词汇表的重要参数 只有测试人员有权限修改

void GetVacabulary()
{
	ifstream fin("Vocabulary.txt");
	struct Word stemp;
	stemp.len = 0;
	for (int i = 0; fin.peek() != EOF; i++)
	{
		fin >> stemp.info;
		Vocabulary.push_back(stemp);
		Vocabulary[i].len = Vocabulary[i].info.length();
		TEST.wordlen[Vocabulary[i].len]++; //维护使用
	}
	fin.close();

}

void UpdateVacabulary()
{
	ofstream fout("Vocabulary.txt");
	for (int i=0; i< Vocabulary.size(); i++)
	{
		fout << Vocabulary[i].info;
		if (i != (Vocabulary.size() - 1))
		{
			fout<<endl;
		}
	}
	fout.close();

}


void GetPlayerList()
{
	ifstream fin("PlayerList.txt");
	int itemp;
	string stemp;
	Player player;
	for (int i = 0; fin.peek() != EOF; i++)
	{
		fin >> stemp;
		player.SetName(stemp);
		fin >> stemp;
		player.SetPassWord(stemp);
		fin >> itemp;
		player.SetLevel(itemp);
		fin >> itemp;
		player.SetExp(itemp);
		fin >> itemp;
		player.SetChapter(itemp);
		PlayerList.push_back(player);

	}
	fin.close();

}
void UpdatePlayerList()
{
	ofstream fout("PlayerList.txt");
	for (int i = 0; i < PlayerList.size(); i++)
	{
		fout << PlayerList[i].GetName() << ' ';
		fout << PlayerList[i].GetPassWord() << ' ';
		fout << PlayerList[i].GetLevel() << ' ';
		fout << PlayerList[i].GetExp() << ' ';
		fout << PlayerList[i].GetChapter();
		if (i != (PlayerList.size() - 1))
		{
			fout << endl;
		}
	}
	fout.close();

}
void GetQmakerList()
{
	ifstream fin("QmakerList.txt");
	int itemp;
	string stemp;
	Qmaker qmaker;
	for (int i = 0; fin.peek() != EOF; i++)
	{
		fin >> stemp;
		qmaker.SetName(stemp);
		fin >> stemp;
		qmaker.SetPassWord(stemp);
		fin >> itemp;
		qmaker.SetLevel(itemp);
		fin >> itemp;
		qmaker.SetQNumber(itemp);
		QmakerList.push_back(qmaker);

	}
	fin.close();

}

void UpdateQmakerList()
{
	ofstream fout("QmakerList.txt");
	for (int i = 0; i < QmakerList.size(); i++)
	{
		fout << QmakerList[i].GetName() << ' ';
		fout << QmakerList[i].GetPassWord() << ' ';
		fout << QmakerList[i].GetLevel() << ' ';
		fout << QmakerList[i].GetQNumber();
		if (i != (QmakerList.size() - 1))
		{
			fout << endl;
		}
	}
	fout.close();

}
bool operator ==(const struct Word& word1, const string& word2)
{
	return word1.info == word2;
}

bool compword(const Word& a, const Word& b)
{

	return a.len < b.len;

}
bool compplayer(Player& a, Player& b)
{
	return a.GetExp() > b.GetExp();
}
bool compqmaker(Qmaker& a, Qmaker& b)
{
	return a.GetQNumber() > b.GetQNumber();
}