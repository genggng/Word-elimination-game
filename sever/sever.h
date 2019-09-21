#pragma once
#include<iostream>
#include<string>
#include<WinSock2.h>
#include<stdlib.h>
#include"game.h"
#pragma comment(lib,"ws2_32.lib")
#define MaxClient 10
#define MaxBufSize 1024
#define _CRT_SECURE_NO_WARINGS


DWORD WINAPI ServerThread(LPVOID lpParameter);
void Sever();
void Reply(char* RecvBuf,char* SendBuf,Game &game);