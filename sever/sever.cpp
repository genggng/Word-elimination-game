#include"sever.h"
#include"file.h"
#include"game.h"

using namespace std;
const int PORT = 8000;
int ClientNumber = 0;    //游戏玩家数
int Finish = 0;        //一名玩家已经完成
string OnlineWord;   //在线游戏单词
extern  vector<Word> Vocabulary;
extern  vector<Player> PlayerList;
extern  vector<Qmaker> QmakerList;

//服务线程
DWORD WINAPI ServerThread(LPVOID lpParameter) {
	SOCKET* ClientSocket = (SOCKET*)lpParameter;
	int receByt = 0;
	char RecvBuf[MaxBufSize];
	char SendBuf[MaxBufSize];
	Game  game;

	while (true) {
		receByt = recv(*ClientSocket, RecvBuf, sizeof(RecvBuf), 0);  //接收到字节数
		if (receByt > 0) {
			cout << "接收到的消息是：" << RecvBuf << "            来自客户端:" << *ClientSocket << endl;
		}
		else
		{
			cout << "与"<< *ClientSocket <<"客户端连接关闭！" << endl;
			break;
		}
		Reply(RecvBuf, SendBuf,game);  //对接收的请求进行应答
		memset(RecvBuf, 0, sizeof(RecvBuf));
		int k = 0;
		k = send(*ClientSocket, SendBuf, sizeof(SendBuf), 0);
		if (k < 0)
		{
			cout << "发送失败" << endl;
		}
		memset(SendBuf, 0, sizeof(SendBuf));
	}
	closesocket(*ClientSocket);
	free(ClientSocket);
	UpdateVacabulary();
	UpdatePlayerList();
	UpdateQmakerList();
	return 0;
}

void Sever() 
{
	WSAData wsd;
	WSAStartup(MAKEWORD(2, 2), &wsd);
	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN ListenAddr;       //监听地址
	HANDLE Client[10];  //客户端句柄

	ListenAddr.sin_family = AF_INET;
	ListenAddr.sin_addr.S_un.S_addr = INADDR_ANY;//表示填入本机ip
	ListenAddr.sin_port = htons(PORT);

	int n;
	n = bind(ListenSocket, (LPSOCKADDR)& ListenAddr, sizeof(ListenAddr));
	if (n == SOCKET_ERROR) {
		cout << "端口绑定失败！" << endl;
	}
	else {
		cout << "端口绑定成功：" << PORT << endl;
	}
	int l = listen(ListenSocket, 20);  //无错误返回0 有错误返回-1
	cout << "服务端准备就绪，等待连接请求" << endl;

	while (true)
	{
		//循环接收客户端连接请求并创建服务线程
		SOCKET* ClientSocket = new SOCKET;
		ClientSocket = (SOCKET*)malloc(sizeof(SOCKET));
		//接收客户端连接请求
		int SockAddrlen = sizeof(sockaddr);
		*ClientSocket = accept(ListenSocket, 0, 0); //从欲建立链接队列中取出一个与监听套接口绑定 返回该套接口 队列空时休眠
		CreateThread(NULL, 0, &ServerThread, ClientSocket, 0, NULL);
	}
	closesocket(ListenSocket);
	WSACleanup();

}

void Reply(char* RecvBuf, char* SendBuf,Game &game)
{
	char flag; //请求标志位
	flag = RecvBuf[0];

	switch (flag)
	{
	case 'a':
		game.SetJudgeUse(0);
		game.Register(&RecvBuf[1], SendBuf);
		break;
	case'b':
		game.SetJudgeUse(0);
		game.Login(&RecvBuf[1], SendBuf);
		break;
	case 'c':
		game.SetJudgeUse(1);  //出题者
		game.Register(&RecvBuf[1], SendBuf);
		break;
	case'd':
		game.SetJudgeUse(1);
		game.Login(&RecvBuf[1], SendBuf);
		break;
	case 'e':
		game.Getword(&RecvBuf[1], SendBuf);
		break;
	case'f':
		game.MakeQusetion(&RecvBuf[1], SendBuf);
		break;
	case'g':
	case'h':
	case'i':
	case'j':
		game.Query(RecvBuf, SendBuf); //查询需要将标识位读入
		break;
	case'k':
		game.UpdateUser(RecvBuf, SendBuf); //更新需要把表示为读入
		break;
	case'm':
		game.OnlineGetWord(&RecvBuf[1], SendBuf);
		break;
	case'n':
		game.JudegeSuccess(SendBuf);
	}
}





