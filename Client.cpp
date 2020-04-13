#include<iostream>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
void Error(const char message[]);
int main() {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		Error("套接字启动失败.");
	}
	//1.创建套接字
	SOCKET client = socket(PF_INET, SOCK_STREAM, 0);
	if (client == INVALID_SOCKET) {
		Error("Creat client socket Error.\a");
	}
	//2.连接服务器
	SOCKADDR_IN SerAddr;
	memset(&SerAddr, 0, sizeof(SerAddr));	//初始化
	SerAddr.sin_family = AF_INET;
	SerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	SerAddr.sin_port = htons(8080);
	std::cout << "正在连接服务端.... \n";
	if (connect(client, (SOCKADDR*)&SerAddr, sizeof(SerAddr)) == SOCKET_ERROR) {
		Error("连接服务端失败.\a");
	}
	std::cout << "连接服务端完成.... \n";
	char buf[20];
	memset(&buf,'\0', sizeof(buf));
	if (recv(client, buf, sizeof(buf), 0) == SOCKET_ERROR){
		Error("接收数据失败\a");
	}
	std::cout << buf << ' ';
	closesocket(client);
	WSACleanup();
}
void Error(const char message[]) {
	fputs(message, stderr);
	fputs("\n", stderr);
	exit(0);
}