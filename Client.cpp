#include<iostream>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
void Error(const char message[]);
int main() {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		Error("�׽�������ʧ��.");
	}
	//1.�����׽���
	SOCKET client = socket(PF_INET, SOCK_STREAM, 0);
	if (client == INVALID_SOCKET) {
		Error("Creat client socket Error.\a");
	}
	//2.���ӷ�����
	SOCKADDR_IN SerAddr;
	memset(&SerAddr, 0, sizeof(SerAddr));	//��ʼ��
	SerAddr.sin_family = AF_INET;
	SerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	SerAddr.sin_port = htons(8080);
	std::cout << "�������ӷ����.... \n";
	if (connect(client, (SOCKADDR*)&SerAddr, sizeof(SerAddr)) == SOCKET_ERROR) {
		Error("���ӷ����ʧ��.\a");
	}
	std::cout << "���ӷ�������.... \n";
	char buf[20];
	memset(&buf,'\0', sizeof(buf));
	if (recv(client, buf, sizeof(buf), 0) == SOCKET_ERROR){
		Error("��������ʧ��\a");
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