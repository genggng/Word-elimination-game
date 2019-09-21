#include "game.h"
#include"file.h"
#include<cstdlib>
#include<ctime>
#include<Windows.h>

extern  vector<Word> Vocabulary;
extern  vector<Player> PlayerList;
extern  vector<Qmaker> QmakerList;
extern int ClientNumber;
extern int Finish;
extern string OnlineWord;

extern int wordper[15];

int Game::Register(char* recvbuf,char* sendbuf)
{

	vector<string>FromClient; //客户端的请求
	string name;
	string password;
	Player player;
	Qmaker qmaker;

	FromClient = split(recvbuf);
	name = FromClient[0];
	password = FromClient[1];

	if (JudgeUser)
	{
		auto p1 = find(QmakerList.begin(), QmakerList.end(), name);
		if(p1 != QmakerList.end())
		{
			sendbuf[0] = '0';
			sendbuf[1] = '\0';
			return -1;
		}
	}
	else
	{
		auto p2 = find(PlayerList.begin(), PlayerList.end(), name);
		if (p2 != PlayerList.end())
		{
			sendbuf[0] = '0';
			sendbuf[1] = '\0';
			return -1;
		}
	}
	if (JudgeUser)
	{
		qmaker.SetName(name);
		qmaker.SetPassWord(password);
		QmakerList.push_back(qmaker);
		sendbuf[0] = '1';
		sendbuf[1] = '\0';
		return QmakerList.size() - 1;
	}
	else
	{
		player.SetName(name);
		player.SetPassWord(password);
		PlayerList.push_back(player);
		sendbuf[0] = '1';
		sendbuf[1] = '\0';
		return PlayerList.size() - 1;
	}

}

int Game::Login(char* recvbuf,char* sendbuf)
{
	string name;
	string password;
	vector<string>FromClient; //客户端的请求
	vector<string>ToClient; //回复客户端

	FromClient = split(recvbuf);
	name = FromClient[0];
	password = FromClient[1];
	if (JudgeUser) {
		auto p1 = find(QmakerList.begin(), QmakerList.end(), name);
		if (p1 == QmakerList.end())
		{
			sendbuf[0] = '0';
			sendbuf[1] = '\0';
			return -1;
		}
		if (password != p1->GetPassWord())
		{
			sendbuf[0] = '0';
			sendbuf[1] = '\0';
			return -1;
		}
		PutQmaker(ToClient, *p1);
		sendbuf[0] = '1';
		merge(ToClient, &sendbuf[1]);

		ID= p1 - QmakerList.begin();
		return ID;
	}
	else
	{
		auto p2 = find(PlayerList.begin(), PlayerList.end(), name);
		if (p2 == PlayerList.end())
		{
			sendbuf[0] = '0';
			sendbuf[1] = '\0';
			return -1;
		}
		if (password != p2->GetPassWord())
		{
			sendbuf[0] = '0';
			sendbuf[1] = '\0';
			return -1;
		}

		PutPlayer(ToClient, *p2);
		sendbuf[0] = '1';
		merge(ToClient, &sendbuf[1]);

		ID= p2 - PlayerList.begin();
		return ID;
	}

}

void Game::Getword(char* recvbuf, char* sendbuf)
{
	string Schapter;
	int chapter;
	string guessword;
	vector<string>FromClient; //客户端的请求
	vector<string>ToClient; //回复客户端

	FromClient = split(recvbuf);
	Schapter = FromClient[0];

	chapter = atoi(Schapter.c_str());
	guessword = Vocabulary[RadomWord(chapter) - 1].info;
	OnlineWord = guessword;
	ToClient.push_back(guessword);
	sendbuf[0] = '1';
	merge(ToClient, &sendbuf[1]);
}

int Game::OnlineGetWord(char* recvbuf, char* sendbuf)
{
	string word;
	vector<string>ToClient; //回复客户端

	if (ClientNumber == 1)
	{
		ClientNumber = 2;
		sendbuf[0] = '1';
		ToClient.push_back(OnlineWord);
		merge(ToClient, &sendbuf[1]);

		return 0;

	}
	else if(ClientNumber == 0)
	{
		Getword(recvbuf, sendbuf);
		ClientNumber = 1;
		for (int i = 0; i < 100; i++)
		{
			if (ClientNumber == 2)
			{
				sendbuf[0] = '1';
				return 0;
			}
			Sleep(100);
		}
	}
	ClientNumber = 0;
	sendbuf[0] = '0';
	sendbuf[1] = '\0';

	return -1;
	

}

int Game::JudegeSuccess( char* SendBuf)
{


	if ( Finish == 0)
	{
		SendBuf[0] = '1';
		SendBuf[1] = '\0';
		Finish = 1;
		return 0;
	}
	else 
	{
		SendBuf[0] = '0';
		SendBuf[1] = '\0';
		Finish = 0;
		ClientNumber = 0;
		return 0;
	}
}

int Game::MakeQusetion(char* recvbuf, char* sendbuf)
{
	struct Word word; //添加的单词
	vector<string>FromClient; //客户端的请求
	vector<string>ToClient; //回复客户端

	FromClient = split(recvbuf);
	word.info = FromClient[0];
	word.len = word.info.size();

	auto p1 = find(Vocabulary.begin(), Vocabulary.end(), word.info);

	if (p1 != Vocabulary.end())
	{
		sendbuf[0] = '0';
		sendbuf[1] = '\0';
		return -1;
	}
	sendbuf[0] = '1';

	Vocabulary.push_back(word);
	sort(Vocabulary.begin(), Vocabulary.end(), compword); //更新词汇表顺序
}

void Game::UpdateUser(char* recvbuf, char* sendbuf)
{
	vector<string>FromClient; //客户端的请求
	FromClient = split(&recvbuf[1]);

	if (JudgeUser)
	{
		GetQmaker(FromClient, QmakerList[ID]);
	}
	else
	{
		GetPlayer(FromClient, PlayerList[ID]);
	}
	sendbuf[0] = '1';
}

int Game::Query(char* recvbuf, char* sendbuf)
{
	int select = recvbuf[0] - 'g';  //0.查闯关者 1.查出题者 2.闯关排行 3.出题排行
	vector<string>FromClient; //客户端的请求
	vector<string>ToClient; //回复客户端
	string name;
	vector<Player>::iterator p1;
	vector<Qmaker>::iterator p2;

	FromClient = split(&recvbuf[1]);
	switch (select)
	{
	case 0:
		name = FromClient[0];
		p1 = find(PlayerList.begin(), PlayerList.end(), name);
		if (p1 == PlayerList.end())
		{
			sendbuf[0] = '0';
			sendbuf[1] = '\0';
			return -1;
		}
		else
		{
			PutPlayer(ToClient, *p1);
		}
		break;
	case 1:
		name = FromClient[0];
		p2 = find(QmakerList.begin(), QmakerList.end(), name);
		if (p2 == QmakerList.end())
		{
			sendbuf[0] = '0';
			sendbuf[1] = '\0';
			return -1;
		}
		else
		{
			PutQmaker(ToClient, *p2);
		}
		break;
	case 2:
		sort(PlayerList.begin(), PlayerList.end(), compplayer);
		for (int i = 0; i < PlayerList.size(); i++)
		{
			PutPlayer(ToClient, PlayerList[i]);
		}
		break;
	case 3:
		sort(QmakerList.begin(), QmakerList.end(), compqmaker);
		for (int i = 0; i < QmakerList.size(); i++)
		{
			PutQmaker(ToClient, QmakerList[i]);
		}
		break;
	}
		sendbuf[0] = '1';
		merge(ToClient, &sendbuf[1]);
}

void Game::PutPlayer(vector<string>& ToClient, Player& player)
{
	char level[10];
	char exp[10];
	char chapter[10];

	_itoa(player.GetLevel(), level, 10);
	_itoa(player.GetExp(), exp, 10);
	_itoa(player.GetChapter(), chapter, 10);

	string Slevel(level);
	string Sexp(exp);
	string Schapter(chapter);
	string name = player.GetName();

	ToClient.push_back(name);
	ToClient.push_back(Slevel);
	ToClient.push_back(Sexp);
	ToClient.push_back(Schapter);
}

void Game::PutQmaker(vector<string>& ToClient, Qmaker& qmaker)
{
	char level[10];
	char qnumber[10];

	_itoa(qmaker.GetLevel(), level, 10);
	_itoa(qmaker.GetQNumber(), qnumber, 10);


	string Slevel(level);
	string Sqnumber(qnumber);
	string name = qmaker.GetName();

	ToClient.push_back(name);
	ToClient.push_back(Slevel);
	ToClient.push_back(Sqnumber);

}

void Game::GetPlayer(vector<string>& ToClient, Player& player)
{
	string name;
	int level;
	int exp;
	int chapter;

	name = ToClient[0];
	level = atoi(ToClient[1].c_str());
	exp = atoi(ToClient[2].c_str());
	chapter = atoi(ToClient[3].c_str());
	//cout << name << level << exp << chapter << endl;
	player.SetName(name);
	player.SetLevel(level);
	player.SetExp(exp);
	player.SetChapter(chapter);

}

void Game::GetQmaker(vector<string>& ToClient, Qmaker& qmaker)
{
	string name;
	int level;
	int qnumber;

	name = ToClient[0];
	level = atoi(ToClient[1].c_str());
	qnumber = atoi(ToClient[2].c_str());


	qmaker.SetName(name);
	qmaker.SetLevel(level);
	qmaker.SetQNumber(qnumber);


}


bool Game::GetJudegUser()
{
	return JudgeUser;
}

void Game::SetJudgeUse(bool judge)
{
	JudgeUser = judge;
}

int Game::GetID()
{
	return ID;
}

void Game::SetID(int id)
{
	ID = id;
}

int Game::RadomWord(int chapter)
{
	srand(int(time(0)));
	int random;//1-1000的随机整数
	int ret; //在难度区间内的一个随机数
	int len = Vocabulary.size() / 10; //词汇表的一个难度区间长度 共10个难度

	random = rand() % 1000 + 1;
	ret = random * len / 1000;
	return ret + (chapter-1) * len;  //返回随机的单词序号
}

int Game::ExpectWordLen()
{
	srand(int(time(0)));
	int random;//1-1000的随机整数

	random = rand() % 1000 + 1;
	for (int i = 1; i < 15; i++)
	{
		if (random > wordper[i - 1] && random <= wordper[i])
			return i; //返回期望的单词长度
	}
}
void Game::LegalInput(int& ExpectInput, int down, int up)
{
	int number;

	while (!(cin >> number) || number < down || number>up) 
	{
		cout << "非法输入！" << endl;
		cin.clear();
		cin.ignore(1024, '\n');
		cout << "请重新输入：（"<<down<<"-"<<up<<")"<<endl;
	}
	ExpectInput = number;
}
void Game::LegalInput(bool& ExpectInput)
{
	int flag;
	while (!(cin >> flag) || (flag != 0 && flag != 1))
	{
		cout << "非法输入！" << endl;
		cin.clear();
		cin.ignore(1024, '\n');
		cout << "请重新输入：（ 0 或者 1)" << endl;
	}
	ExpectInput = flag;
}

vector<string> Game::split(char* str) 
{
	vector<string> res;
	char* temp = strtok(str, "#");
	while (temp != NULL)
	{
		res.push_back(string(temp));
		temp = strtok(NULL, "#");
	}
	return res;
}

void Game::merge(vector<string> &ToClient, char* str)
{
	string sstr;
	for (auto p = ToClient.begin(); p != ToClient.end(); p++)
	{
		sstr += *p;
		if (p < ToClient.end() - 1)
		{
			sstr.push_back('#');
		}
	}
	strcpy(str, sstr.c_str());
}
