/*Author: Hugo Filipe, UNINOVA*/

extern SOCKET cliente;
extern char message[10];

void initSocket();

void closeSocket();



// OUTPUT FOR net.io.cpp

/******************************** Pipe message ***************************************************/
//if (place_out->Out_Up == 1) PipeMessage[0] = '1'; else PipeMessage[0] = '0'; //comando I
//if (place_out->Out_Down == 1) PipeMessage[1] = '1'; else PipeMessage[1] = '0';  //comando K
//if (place_out->Out_Left == 1) PipeMessage[2] = '1'; else PipeMessage[2] = '0';   //comando A
//if (place_out->Out_Right == 1) PipeMessage[3] = '1'; else PipeMessage[3] = '0';    // comando D
//if (place_out->Out_TakeOffLand == 1) PipeMessage[4] = '1'; else PipeMessage[4] = '0';    // comando Space
//WriteFile(hPipe, PipeMessage, 10, &dwWritten, NULL);
/******************************** Pipe message ***************************************************/

/******************************** SOCKETS ***************************************************/
//if (place_out->Out_Up == 1) message[0] = '1'; else message[0] = '0'; //comando I
//if (place_out->Out_Down == 1) message[1] = '1'; else message[1] = '0';  //comando K
//if (place_out->Out_Left == 1) message[2] = '1'; else message[2] = '0';   //comando A
//if (place_out->Out_Right == 1) message[3] = '1'; else message[3] = '0';    // comando D
//if (place_out->Out_TakeOffLand == 1) message[4] = '1'; else message[4] = '0';    // comando Space
//if (place_out->Out_RotateLeft == 1) message[5] = '1'; else message[5] = '0';    // comando Space
//if (place_out->Out_RotateRight == 1) message[6] = '1'; else message[6] = '0';    // comando Space
//send(cliente, message, strlen(message), 0);
/******************************** SOCKETS ***************************************************/
