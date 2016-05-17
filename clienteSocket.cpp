/*Author: Hugo Filipe, UNINOVA*/

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <stdlib.h>
#include "net_types.h"
#include <iostream>
#include "Controlador.h"
#include "edk.h"
#include "EmoStateDLL.h"
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <windows.h> // before winsock2.h
#include "clienteSocket.h"
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")

/******************************** PIPE MESSAGE ***************************************************/
//HANDLE hPipe = CreateFile(TEXT("\\\\.\\pipe\\pipe"),
//	GENERIC_READ | GENERIC_WRITE,
//	0,
//	NULL,
//	OPEN_EXISTING,
//	0,
//	NULL); // Comunicação via-pipe
//DWORD dwWritten; // Comunicação via-pipe
//char PipeMessage[10] = "000000000"; // Comunicação via-pipe
//int operacao = 0;
//int time = TimeBlinkTwice + 1;
//int var_bt = 0, var_Wr = 0, var_Wl = 0, var_ll = 0, var_lr = 0, var_lu = 0, var_ld = 0, var_eo = 0;
/******************************** PIPE MESSAGE ***************************************************/

/******************************** SOCKETS ***************************************************/
//struct sockaddr_in {
//	short            sin_family;   // e.g. AF_INET, AF_INET6
//	unsigned short   sin_port;     // e.g. htons(3490)
//	struct in_addr   sin_addr;     // see struct in_addr, below
//	char             sin_zero[8];  // zero this if you want to
//};
struct sockaddr_in server;
WSADATA wsa;
SOCKET cliente;
WORD version = MAKEWORD(2, 0);
int PORT=8888;
char IP[] = "127.0.0.1";
int error;
char message[10] = "000000000";
/******************************** SOCKETS ***************************************************/

void initSocket() {

	error = WSAStartup(version, &wsa);
	if (error != 0) {
		printf("WSA Initialization failed.\n");
		getchar();
	}
	
	cliente = socket(AF_INET, SOCK_STREAM, 0);
	if (cliente == INVALID_SOCKET) {
		printf("socket creation failed.\n");
		getchar();
	}
	else
	{
		printf("socket created.\n");
	}

	server.sin_addr.s_addr = inet_addr(IP);// inet_addr("127.0.0.1") 
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT); 

	if (connect(cliente, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		perror("\nSocket connect failed: Error\n");
		getchar();
		system("CLS"); // clean screen
	}
	else
	{
		printf("Cliente Connected...\n");
	}
	/******************************** SOCKETS ***************************************************/


}
void closeSocket() {
	closesocket(cliente);
}