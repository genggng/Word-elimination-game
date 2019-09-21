#include"client.h"
#include"file.h"
#include"game.h"

using namespace std;
const int PORT = 8000;


void Client()
{
	WSADATA wsd;
	WSAStartup(MAKEWORD(2, 2), &wsd);
	SOCKET SocketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN  ClientAddr;

	ClientAddr.sin_family = AF_INET;
	ClientAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	ClientAddr.sin_port = htons(PORT);

	int n = 0;
	int HadConnect = 1;
	n = connect(SocketClient, (struct sockaddr*) & ClientAddr, sizeof(ClientAddr));
	if (n == SOCKET_ERROR) {
		cout << "连接失败,请重启客户端！！" << endl;
		HadConnect = 0;
	}
	else
	{
		cout << "########################" << endl;
		cout << " 成功连接到服务器！" << endl;
		cout << "########################" << endl;
		Sleep(1000);
	}

	/******************用户服务程序********************/
	Game game;
	game.SetSocket(SocketClient);
	int go = 1;
	while (go && HadConnect)
	{
		InitGame(game, go);
	}
	closesocket(SocketClient);
	WSACleanup();

}

char InitGame(Game& game, int& go)
{
	system("cls");
	char select;
	cout << "#########################################" << endl;
	cout << " 欢迎使用单词消消乐游戏系统3.0   制作者：程序员老王" << endl;
	cout << " 按下对应功能前的序号，请选择：" << endl << endl;
	cout << " 1.注册闯关者" << endl << endl;
	cout << " 2.注册出题者" << endl << endl;
	cout << " 3.登录闯关者" << endl << endl;
	cout << " 4.登录出题者" << endl << endl;
	cout << " 5.查询系统" << endl << endl;
	cout << " q.退出游戏" << endl << endl;
	cout << "#########################################" << endl;
	select = getchar();
	system("cls");
	switch (select)
	{
	case '1':
		game.SetJudgeUser(0);
		game.Register();
		break;
	case'2':
		game.SetJudgeUser(1);
		game.Register();
		break;
	case'3':
		game.SetJudgeUser(0);
		game.Login();
		break;
	case'4':
		game.SetJudgeUser(1);
		game.Login();
		break;
	case'5':
		game.Query();
		break;
	case'q':
		go = 0;
		break;

	}
	return select;
}


