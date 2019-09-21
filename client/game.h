#pragma once
#include<iostream>
#include"qmaker.h"
#include"player.h"
#include"file.h"
#include<WinSock2.h>

class Game
{
public:
	int Register(); //注册
	int Login();   //登录
	void PlayGame();  //玩游戏
	int PlaySelect(int &PlayGo);//选择单机或是对战
	int OnlinePlay();//联机对战
	void MakeQusetion(); //出题
	void Query();   //查询功能
	void PutPlayer(vector<string>& ToClient, Player& player); //将闯关者信息整合为字符串
	void PutQmaker(vector<string>& ToClient, Qmaker& qmaker);
	void GetPlayer(vector<string>& FromClient);//将字符串整合为闯关者
	void GetQmaker(vector<string>& FromClient);
	void GetPlayer(vector<string>& FromClient,Player &temp);//将字符串整合为闯关者
	void GetQmaker(vector<string>& FromClient,Qmaker &temp);
	string iTOa(int x); //整数转换为string类
	bool GetJudegUser();
	void SetJudgeUser(bool judge);
	void SetSocket(SOCKET socket);
	SOCKET GetSocket();
	vector<string> split(char* str);  //分割字符串
	void merge(vector<string>& ToClient, char* str);    //合并字符串
	char Request(char flag, vector<string>&ToSever, vector<string>&FromSever);  //客户端请求
	void LegalInput(int& ExpectInput, int down, int up);//数字合法化输入
	void LegalInput(bool& ExpectInput);
private:
	bool JudgeUser;    //1代表出题者，0代表创关者
	Player player;
	Qmaker qmaker;
	int RadomWord(int chapter); //根据关卡随机选择单词
	int ExpectWordLen(); //随机产生期望单词长度
	SOCKET SocketClient;


};

