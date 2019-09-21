#pragma once
#include<iostream>
#include<string>
#include<WinSock2.h>
#include"game.h"
#include<stdlib.h>
#pragma comment(lib,"ws2_32.lib")
#define MaxBufSize 1024

void Client();
char InitGame(Game &game,int &go);
