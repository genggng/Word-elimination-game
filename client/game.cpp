#include "game.h"
#include"file.h"
#include"client.h"
#include<cstdlib>
#include<ctime>
#include<Windows.h>

extern  vector<Word> Vocabulary;
extern  vector<Player> PlayerList;
extern  vector<Qmaker> QmakerList;
extern int wordper[15];

int Game::Register()
{
	string name;
	string password1;
	string password2;
	Player player;
	Qmaker qmaker;
	vector<string>ToSever;
	vector<string>FromSever;
	char flag;     //'1'表示成功 '0'表示失败
	cout << "#######################################" << endl;
	if (JudgeUser)
	{
		cout << "           注册出题者！" << endl;
	}
	else
	{
		cout << "           注册闯关者者！" << endl;
	}
	cout << endl;
	cout << "用户名：";
	cin >> name;
	cout << "密码：";
	cin >> password1;
	cout << "再输入一遍密码：";
	cin >> password2;
	while (password1 != password2)
	{
		cout << "两次输入密码不一致！请重新输入：" << endl;
		cout << "密码：";
		cin >> password1;
		cout << "再输入一遍密码：";
		cin >> password2;
	}
	ToSever.push_back(name);
	ToSever.push_back(password1);
	if (JudgeUser)
	{
		flag = Request('c', ToSever, FromSever);
		cout << flag << endl;
		while (flag != '1')
		{
			cout << "用户名已存在，请重新输入！" << endl;
			cout << "用户名： ";
			cin >> name;
			ToSever[0] = name;
			flag = Request('c', ToSever, FromSever);
		}
	}
	else
	{
		flag = Request('a', ToSever, FromSever);
		while (flag != '1')
		{
			cout << "用户名已存在，请重新输入！" << endl;
			cout << "用户名： ";
			cin >> name;
			ToSever[0] = name;
			flag = Request('a', ToSever, FromSever);
		}
	}

	cout << "注册成功！" << endl;
	Sleep(1000);
	return 0;

}

int Game::Login()
{
	string name;
	string password;
	vector<string>ToSever;
	vector<string>FromSever;
	char flag;
	cout << "#######################################" << endl;
	if (JudgeUser) {
		cout << "          出题者登录！" << endl<<endl;
		cout << "请输入用户名：";
		cin >> name;
		cout << "请输入密码：";
		cin >> password;

		ToSever.push_back(name);
		ToSever.push_back(password);
		flag = Request('d', ToSever, FromSever);
		while (flag != '1')
		{
			cout << "用户名不存在或者密码错误" << endl;
			cout << "用户名： ";
			cin >> name;
			cout << "请输入密码：";
			cin >> password;
			ToSever.clear();
			FromSever.clear();
			ToSever.push_back(name);
			ToSever.push_back(password);
			flag = Request('d', ToSever, FromSever);
		}
		GetQmaker(FromSever);//将字符串整合为出题者
	}
	else
	{
		cout << "             闯关者登录！" << endl<<endl;
		cout << "请输入用户名：";
		cin >> name;
		cout << "请输入密码：";
		cin >> password;

		ToSever.push_back(name);
		ToSever.push_back(password);
		flag = Request('b', ToSever, FromSever);
		while (flag != '1')
		{
			cout << "用户名不存在或者密码错误" << endl;
			cout << "用户名： ";
			cin >> name;
			cout << "请输入密码：";
			cin >> password;
			ToSever.clear();
			FromSever.clear();
			ToSever.push_back(name);
			ToSever.push_back(password);
			flag = Request('b', ToSever, FromSever);
		}
		GetPlayer(FromSever);//将字符串整合为闯关者
	}
	cout << endl;
	cout << "###登录成功！" << endl;
	Sleep(1000);
	if (JudgeUser)
	{
		MakeQusetion();
	}
	else
	{
		int PlayGo = 1;
		while (PlayGo)
		{
			PlaySelect(PlayGo);
		}
			

	}
	cout << "@@@退出登录！！！" << endl;
	Sleep(2000);
	
	return 0;
}

void Game::PlayGame()
{

	int chapter = player.GetChapter();
	int level = player.GetLevel();
	int exp = player.GetExp();
	string guessword;
	string answer;
	string Schapter;
	char cchapter[10];
	bool go = true;  //表示继续游戏
	vector<string>ToSever;
	vector<string>FromSever;
	char flag;

	cout << "游戏开始！！" << endl;
	while (go)
	{
		system("cls");
		cout << "#######################################" << endl;
		cout << "闯关者：" << player.GetName() << "  " << "等级：" << player.GetLevel() << "  " << "经验值：" << player.GetExp() << endl<<endl;
		cout << "游戏开始！！" << endl;
		cout << "##########################" << endl;
		cout << "CHAPTER  " << chapter << " Good Luck!" << endl;
		cout << "##########################" << endl;
		cout << endl;
		ToSever.clear();
		FromSever.clear();
		ToSever.push_back(iTOa(chapter));
		flag = Request('e', ToSever, FromSever);
		if (flag == '1')
		{
			guessword = FromSever[0];
		}
		cout << "你有5s的时间记下这个单词： " << guessword << '\r';
		Sleep(5000);
		cout << "时间到!                                                        " << endl;
		cout << "请给出你的答案： ";
		cin >> answer;
		if (answer == guessword)
		{
			cout << "恭喜你，答对啦！！！你获得了" << 10 * chapter << "点经验值！" << endl;
			exp = exp + 10 * chapter;
			while (exp >= level * (level + 1) * (2 * level + 1) + 10 * level)
			{
				level++;
				cout << "恭喜你，升级啦！你达到了 lv" << level << endl;
			}
			chapter++;
			if (chapter == 11)
			{
				chapter = 10;
				cout << "太厉害了，你已经通过了所有关卡，并获得了一次重新选关的机会！" << endl;
				cout << "请输入想要选择的关卡：";
				LegalInput(chapter, 1, 10);

			}
			cout << "$$进入下一关请输入1，结束闯关输入0 :";
			LegalInput(go);
		}
		else
		{
			cout << "很遗憾，你答错了，正确答案是： " << guessword << endl;
			cout << "$$重新开始本关请输入1，结束闯关请输入0：";
			LegalInput(go);
		}
		player.SetLevel(level);
		player.SetExp(exp);
		player.SetChapter(chapter);
	}
	ToSever.clear();
	FromSever.clear();
	PutPlayer(ToSever, player);
	flag = Request('k', ToSever, FromSever);
	if (flag == '0')
	{
		cout << "更新数据失败！" << endl;
	}
}

int Game::PlaySelect(int &PlayGo)
{
	int select;
	system("cls");
	cout << "#######################################" << endl;
	cout << "请选择游戏模式：" << endl;
	cout << " 0.退出闯关" << endl;
	cout << " 1.单人模式" << endl;
	cout << " 2.双人匹配对战模式" << endl<<endl;
	cout << "您的选择：";
	LegalInput(select,0, 2);//数字合法化输入
	switch (select)
	{
	case 0:
		PlayGo = 0;
		break;
	case 1:
		PlayGame();
		break;
	case 2:
		OnlinePlay();
		break;
	}
	return 0;
}

int Game::OnlinePlay()
{
	int chapter = player.GetChapter();
	int level = player.GetLevel();
	int exp = player.GetExp();
	string guessword;
	string answer;
	char cchapter[10];
	vector<string>ToSever;
	vector<string>FromSever;
	int AddExp; //增加或减少的经验
	char flag;
	system("cls");
	cout << "#######################################" << endl;
	cout << "闯关者：" << player.GetName() << "  " << "等级：" << player.GetLevel() << "  " << "经验值：" << player.GetExp() << endl<<endl;
	cout << "欢迎进行双人网络对战！！！" << endl;
	cout << "正在匹配玩家。。。。。。" << endl;
	ToSever.push_back(iTOa(chapter));
	flag = Request('m', ToSever, FromSever);
	if (flag == '1')
	{
		cout << "匹配成功！！" << endl;
		Sleep(1000);
		guessword = FromSever[0];
	}
	else
	{
		cout << "未匹配到玩家！";
		Sleep(3000);
		return -1;
	}
	cout << "你有5s的时间记下这个单词： " << guessword << '\r';
	Sleep(5000);
	cout << "时间到!                                                        " << endl;
	cout << "请给出你的答案： ";
	cin >> answer;
	if (answer == guessword)
	{

		ToSever.clear();
		FromSever.clear();
		flag = Request('n', ToSever, FromSever);
		if (flag == '1')
		{
			AddExp = 120;
			cout << "恭喜你率先答对，获得120点经验值！！！" << endl;
		}
		else
		{
			AddExp = 50;
			cout << "恭喜你答对了，可惜对方下手更快呢~~获得50点经验值！" << endl;
		}

	}
	else
	{
		flag = Request('n', ToSever, FromSever);//只是告诉服务器，答题结束。
		AddExp = 0;
		cout << "真可惜呀，你答错了，啥也没捞着！啧啧。。" << endl;
		cout << "正确答案是： " << guessword << endl;
	}
	exp = exp + AddExp;
	while (exp >= level * (level + 1) * (2 * level + 1) + 10 * level)
	{
		level++;
		cout << "恭喜你，升级啦！你达到了 lv" << level << endl;
	}



	player.SetLevel(level);
	player.SetExp(exp);
	player.SetChapter(chapter);
	ToSever.clear();
	FromSever.clear();
	PutPlayer(ToSever, player);
	flag = Request('k', ToSever, FromSever);
	if (flag == '0')
	{
		cout << "更新数据失败！" << endl;
	}
	Sleep(3000);
}

void Game::MakeQusetion()
{
	string word; //添加的单词
	int expectlen;
	struct Word Nword; //新单词
	bool go = true; //是否继续
	int qnumber = qmaker.GetQNumber(); //出题数
	int level = qmaker.GetLevel(); //等级
	vector<string>ToSever;
	vector<string>FromSever;
	char flag;


	while (go)
	{
		system("cls");
		cout << "#######################################" << endl;
		cout << "出题者：" << qmaker.GetName() << "  " << "等级：" << qmaker.GetLevel() << "  " << "出题数：" << qmaker.GetQNumber()<<endl<<endl;
		ToSever.clear();
		FromSever.clear();
		expectlen = ExpectWordLen();
		cout << "哇！今天你的幸运数字是 " << expectlen << ",只有添加长度为 " << expectlen << " 的单词，才会被记录成绩哟！"<<endl;
		cout << "请输入您想要添加的新单词：";
		cin >> word;
		while (word.size() != expectlen)
		{
			cout << "您输入的新单词长度不对，添加失败！" << endl;
			cout << "请输入长度为 " << expectlen << " 的新单词：";
			cin >> word;

		}
		ToSever.push_back(word);
		flag = Request('f', ToSever, FromSever);
		if (flag == '0')
		{
			cout << "该单词已存在，添加失败！！！" << endl<<endl;
			cout << "继续添加请输入1，退出添加请输入0：";
			LegalInput(go);
		}
		else
		{
			qnumber++;
			cout << "单词添加成功，您累计添加了" << qnumber << "个单词！！！" << endl;
			while (qnumber >= level * 5)
			{
				level++;
				cout << "恭喜您，升级啦！你达到了 lv" << level << endl;
			}
			cout << endl;
			cout << "$$继续添加请输入1，退出添加请输入0：";
			LegalInput(go);
		}
		qmaker.SetQNumber(qnumber); //更新出题数
		qmaker.SetLevel(level);  //更新等级
	}


	ToSever.clear();
	FromSever.clear();
	PutQmaker(ToSever, qmaker);
	flag = Request('k', ToSever, FromSever);
	if (flag == '0')
	{
		cout << "更新数据失败！" << endl;
	}
}

void Game::Query()
{
	int select; //闯关者1，出题者2，闯关排行榜3，出题排行榜4
	bool go = true;
	string name;
	Player playertemp;
	Qmaker qmakertemp;
	vector<string>ToSever;
	vector<string>FromSever;
	char flag;

	cout << "欢迎使用查询功能：" << endl;
	do
	{
		system("cls");
		cout << "#######################################" << endl;
		cout << "查询请输入功能序号： 1.闯关者  2.出题者  3.闯关排行榜  4.出题排行榜" << endl;
		cout << "请选择：（1-4）";
		LegalInput(select, 1, 4);
		switch (select)
		{
		case 1:
			cout << "请输入要查询的闯关者姓名：";
			cin >> name;
			ToSever.clear();
			FromSever.clear();
			ToSever.push_back(name);
			flag = Request('g', ToSever, FromSever);
			if (flag == '0')
			{
				cout << "该闯关者不存在！！！" << endl;
			}
			else
			{
				GetPlayer(FromSever, playertemp);
				cout << "查找到相关闯关者：" << endl;
				cout << "$姓名：" << playertemp.GetName() << endl;
				cout << "$等级：" << playertemp.GetLevel() << endl;
				cout << "$经验：" << playertemp.GetExp() << endl;
				cout << "$闯关数：" << playertemp.GetChapter() << endl << endl;
			}
			break;
		case 2:
			cout << "请输入要查询的出题者姓名：";
			cin >> name;
			ToSever.clear();
			FromSever.clear();
			ToSever.push_back(name);
			flag = Request('h', ToSever, FromSever);
			if (flag == '0')
			{
				cout << "该出题者不存在！！！" << endl;
			}
			else
			{
				GetQmaker(FromSever, qmakertemp);
				cout << "查找到相关出题者：" << endl;
				cout << "$姓名：" << qmakertemp.GetName() << endl;
				cout << "$等级：" << qmakertemp.GetLevel() << endl;
				cout << "$出题数：" << qmakertemp.GetQNumber() << endl << endl;
			}
			break;
		case 3:
			ToSever.clear();
			FromSever.clear();
			flag = Request('i', ToSever, FromSever);
			if (flag == '0')
			{
				cout << "获取排行榜数据失败！" << endl;
			}
			cout << "闯关者排行榜：" << endl;
			cout << "###############################" << endl;
			cout << "名次" << "\t姓名" << "\t等级" << "\t经验" << "\t闯关数" << endl;
			for (int i = 0; !FromSever.empty(); i++)
			{
				GetPlayer(FromSever, playertemp);
				cout << i + 1 << "\t" << playertemp.GetName() << "\t" << playertemp.GetLevel()
					<< "\t" << playertemp.GetExp() << "\t" << playertemp.GetChapter() << endl;
			}
			cout << "###############################" << endl;
			break;
		case 4:
			ToSever.clear();
			FromSever.clear();
			flag = Request('j', ToSever, FromSever);
			if (flag == '0')
			{
				cout << "获取排行榜数据失败！" << endl;
			}
			cout << "出题者排行榜：" << endl;
			cout << "###############################" << endl;
			cout << "名次" << "\t姓名" << "\t等级" << "\t出题数" << endl;
			for (int i = 0; !FromSever.empty(); i++)
			{
				GetQmaker(FromSever, qmakertemp);
				cout << i + 1 << "\t" << qmakertemp.GetName() << "\t" << qmakertemp.GetLevel()
					<< "\t" << qmakertemp.GetQNumber() << endl;
			}
			cout << "###############################" << endl;
			break;
		}
		cout << "$$继续查询请输入1，退出查询请输入0：";
		LegalInput(go);
	} while (go);
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

void Game::GetPlayer(vector<string>& ToClient)
{
	string name;
	int level;
	int exp;
	int chapter;

	name = ToClient[0];
	level = atoi(ToClient[1].c_str());
	exp = atoi(ToClient[2].c_str());
	chapter = atoi(ToClient[3].c_str());

	player.SetName(name);
	player.SetLevel(level);
	player.SetExp(exp);
	player.SetChapter(chapter);


}

void Game::GetQmaker(vector<string>& ToClient)
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

void Game::GetPlayer(vector<string>& FromClient, Player& temp)
{
	string name;
	int level;
	int exp;
	int chapter;

	name = FromClient[0];
	level = atoi(FromClient[1].c_str());
	exp = atoi(FromClient[2].c_str());
	chapter = atoi(FromClient[3].c_str());

	temp.SetName(name);
	temp.SetLevel(level);
	temp.SetExp(exp);
	temp.SetChapter(chapter);


	FromClient.erase(FromClient.begin(), FromClient.begin() + 4);
}

void Game::GetQmaker(vector<string> & FromClient, Qmaker & temp)
{
	string name;
	int level;
	int qnumber;

	name = FromClient[0];
	level = atoi(FromClient[1].c_str());
	qnumber = atoi(FromClient[2].c_str());

	temp.SetName(name);
	temp.SetLevel(level);
	temp.SetQNumber(qnumber);

	FromClient.erase(FromClient.begin(), FromClient.begin() + 3);
}

string Game::iTOa(int x)
{
	char str[10];
	itoa(x, str, 10);
	string ret(str);
	return ret;
}

bool Game::GetJudegUser()
{
	return JudgeUser;
}
void Game::SetJudgeUser(bool judge)
{
	JudgeUser = judge;
}
void Game::SetSocket(SOCKET socket)
{
	SocketClient = socket;
}
SOCKET Game::GetSocket()
{
	return SocketClient;
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

void Game::merge(vector<string> & ToClient, char* str)
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

int Game::RadomWord(int chapter)
{
	srand(int(time(0)));
	int random;//1-1000的随机整数
	int ret; //在难度区间内的一个随机数
	int len = Vocabulary.size() / 10; //词汇表的一个难度区间长度 共10个难度

	random = rand() % 1000 + 1;
	ret = random * len / 1000;
	return ret + (chapter - 1) * len;  //返回随机的单词序号
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
		cout << "请重新输入：（" << down << "-" << up << ")" << endl;
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

char Game::Request(char flag, vector<string> & ToSever, vector<string> & FromSever)
{
	char SendBuff[MaxBufSize], RecvBuff[MaxBufSize];
	int sflag, rflag;

	SendBuff[0] = flag;

	merge(ToSever, &SendBuff[1]);
	sflag = send(SocketClient, SendBuff, sizeof(SendBuff), 0);
	if (sflag < 0)
	{
		cout << "发送失败" << endl;
	}
	rflag = recv(SocketClient, RecvBuff, sizeof(RecvBuff), 0);
	if (rflag < 0)
	{
		cout << "与服务器连接异常！" << endl;
	}
//	cout << "接收到来自服务器的消息是：" << RecvBuff << endl;
	FromSever = split(&RecvBuff[1]);
	return RecvBuff[0];

}