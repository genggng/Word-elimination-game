#pragma once
#include<iostream>
#include"qmaker.h"
#include"player.h"
#include"file.h"

class Game
{
public:
	int Register(char* recvbuf,char* sendbuf); //注册
	int Login(char* recvbuf, char* sendbuf);   //登录
	void Getword(char* recvbuf, char* sendbuf);  //获得单词
	int OnlineGetWord(char* recvbuf, char* sendbuf);//双人对战获取单词
	int JudegeSuccess(char* SendBuf);
	int MakeQusetion(char* recvbuf, char* sendbuf); //出题
	void UpdateUser(char* recvbuf, char* sendbuf);//更新用户
	int Query(char* recvbuf, char* sendbuf);   //查询功能
	void PutPlayer(vector<string>& ToClient, Player& player); //将闯关者信息整合为字符串
	void PutQmaker(vector<string>& ToClient, Qmaker& qmaker);
	void GetPlayer(vector<string>& FromClient, Player& player);//将字符串整合为闯关者
	void GetQmaker(vector<string>& FromClient, Qmaker& qmaker);
	bool GetJudegUser();
	void SetJudgeUse(bool judge);
	int GetID();
	void SetID(int id);
	vector<string> split(char* str);  //分割字符串
	void merge(vector<string>&ToClient,char* str);    //合并字符串
private:
	bool JudgeUser;    //1代表出题者，0代表创关者
	int ID; //出题者或者游戏玩家的ID

	int RadomWord(int chapter); //根据关卡随机选择单词
	int ExpectWordLen(); //随机产生期望单词长度
	void LegalInput(int& ExpectInput, int down, int up);//数字合法化输入
	void LegalInput(bool& ExpectInput);

};

