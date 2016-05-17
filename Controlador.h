/*
Author: Hugo Filipe, UNINOVA

Nota: No inicio do ficheiro net_io.cpp colocar 

//********************* INCLUDES *********************
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
#pragma comment (lib, "Ws2_32.lib")

//********************* INICIALIZATION *********************
InitEpoc();
initSocket();
training();

//********************* INPUTS *********************
interrupt();
newAction();
 
//SENSOR GIROSC�PICO: updateX(), UpdateY(), updateXY(), instX(), insty()
//SINAIS FACIAIS: blink(), Winkleft(), lookLeft(), Winkright( ), lookRight(), Smile()
//SINAIS NEURONAIS: NEUTRAL, PUSH, PULL, LIFT, DROP, LEFT, RIGHT, ROTATE_LEFT, ROTATE_RIGHT, ROTATE_CLOCKWISE, ROTATE_COUNTER_CLOCKWISE, ROTATE_FORWARDS, ROTATE_REVERSE, DISAPPEAR;


//********************* OUTPUTS *********************
printf("\nT/L: %d|Up: %d|Down: %d|Left: %d|Right: %d|Rot.L: %d|Rot.R: %d|Foward: %d|Back: %d|Photo: %d|", place_out->Out_TakeOffLand, place_out->Out_Up, place_out->Out_Down, place_out->Out_Left, place_out->Out_Right, place_out->Out_RotateLeft, place_out->Out_RotateRight, place_out->Out_Foward, place_out->Out_Backward, place_out->Out_TakePhoto);

SOCKETS
if (place_out->Out_Up == 1) message[0] = '1'; else message[0] = '0'; //comando I
if (place_out->Out_Down == 1) message[1] = '1'; else message[1] = '0';  //comando K
if (place_out->Out_Left == 1) message[2] = '1'; else message[2] = '0';   //comando A
if (place_out->Out_Right == 1) message[3] = '1'; else message[3] = '0';    // comando D
if (place_out->Out_TakeOffLand == 1) message[4] = '1'; else message[4] = '0';    // comando Space
if (place_out->Out_RotateLeft == 1) message[5] = '1'; else message[5] = '0';    // comando J
if (place_out->Out_RotateRight == 1) message[6] = '1'; else message[6] = '0';    // comando L
if (place_out->Out_Foward == 1) message[7] = '1'; else message[7] = '0';    // comando W
if (place_out->Out_Backward == 1) message[8] = '1'; else message[8] = '0';    // comando S
send(cliente, message, strlen(message), 0);

PUSH = 0;
PULL = 0;
LIFT = 0;
DROP = 0;
LEFT = 0;
RIGHT = 0;
ROTATE_LEFT = 0;
ROTATE_RIGHT = 0;
ROTATE_CLOCKWISE = 0;
ROTATE_COUNTER_CLOCKWISE = 0;
ROTATE_FORWARDS = 0;
ROTATE_REVERSE = 0;
DISAPPEAR = 0;

//********************* Delay *********************
Sleep(15);

//********************* Finish NET*************
return shutdown();

*/
#pragma once
#include "net_types.h"
#include "edk.h"

#define PI 3.1418
#define TimeBlinkTwice 5

extern int NEUTRAL, PUSH, PULL, LIFT, DROP, LEFT, RIGHT, ROTATE_LEFT, ROTATE_RIGHT, ROTATE_CLOCKWISE, ROTATE_COUNTER_CLOCKWISE, ROTATE_FORWARDS, ROTATE_REVERSE, DISAPPEAR;


/*
Fun��o: Faz correr a fun��o EE_EngineConnect()
retorna: (void)
A funcionar
*/
extern void InitEpoc(void);

void loadUser();

/*
Fun��o: Faz o programa esperar 8 segundos e mostra o Menu de Op��es.
param: operacao -- devolve o valor da operacao por apontador
retorna: (void)
A funcionar
*/
void Menu();
extern void load(/*int *operacao*/);

/*
Funcao: torna ZERO todos os valores dos inputs da rede de petri.
Return: (void)
N�o est� a funcionar
*/
extern void ResetInputs(Gyro_Project_InputSignals *inputs);

int shutdown();

void interrupt();


extern void changeXY(int x);

/*
fun��o: calcula xmax e ymax que corresponde � dire��o do gyroscopio
param: inputs corresponde � variavel com estrutura de 1 input da rede  
return: void
EST� A FUNCIONAR
*/
extern void updateXY();

int UpdateX();

int UpdateY();

int instX();

int instY();



/*
fun��o: verifica se os olhos est�o a piscar (devolve um se estiverem a piscar, devolve zero se n�o estiverem
param: t representa o tempo que j� passou desde  inicio do programa
 inputs corresponde � variavel com estrutura de 1 input da rede
return: 1 ou zero
EST� A FUNCIONAR
*/
extern int Blink();



/*
fun��o:
return:

*/
extern void  newAction();
extern void handleCognitivEvent(EmoEngineEventHandle cognitivEvent);

void training();

void cognitivResetActions();

void cognitivActivationAllLevel();

void cognitivActivation4Level();

void cognitivGetAllLevel();

void cognitivGet4Level();




/*
fun��o: verifica se o olho esquerdo pisca (devolve um se true, devolve zero se n�o piscar)
param: t representa o tempo que j� passou desde inicio do programa
inputs corresponde � variavel com estrutura de 1 input da rede
return: 1 ou zero
N�o EST� A FUNCIONAR
*/
extern int Winkleft();

/*
fun��o: verifica se o olho direito pisca (devolve um se true, devolve zero se n�o piscar)
param: t representa o tempo que j� passou desde inicio do programa
 inputs corresponde � variavel com estrutura de 1 input da rede
return: 1 ou zero
N�o EST� A FUNCIONAR
*/
extern int Winkright();

/*
fun��o: verifica se os olhos apontam para a esquerda (devolve um se true, devolve zero se n�o olharem)
param: t representa o tempo que j� passou desde inicio do programa
var_ll representa o numero de vezes que olhou para a esquerda dentro de um entervalo de tempo
inputs corresponde � variavel com estrutura de 1 input da rede
return: 1 ou zero
N�o EST� A FUNCIONAR
*/
extern int lookLeft();

/*
fun��o: verifica se os olhos apontam para a direita (devolve um se true, devolve zero se n�o olharem)
param: t representa o tempo que j� passou desde inicio do programa
var_lr representa o numero de vezes que olhou para a direita dentro de um entervalo de tempo
inputs corresponde � variavel com estrutura de 1 input da rede
return: 1 ou zero
N�o EST� A FUNCIONAR
*/
extern int lookRight();


/*
fun��o: verifica o estado do smile (devolve um valor de 0.0 a 1.0)
param: t representa o tempo que j� passou desde inicio do programa
 inputs corresponde � variavel com estrutura de 1 input da rede
return: (float) entre 0.0 a 1.0
N�o EST� A FUNCIONAR
*/
float Smile();

/*
fun��o: verifica se os olhos est�o abertos ou n�o (devolve um se estiver aberto, devolve zero se estiverem fechados
param: t representa o tempo que j� passou desde inicio do programa
var_eo representa o numero de vezes que os olhos estivera abertos dentro de um entervalo de tempo
inputs corresponde � variavel com estrutura de 1 input da rede
return: 1 ou zero
N�o EST� A FUNCIONAR
*/
extern int EyesOpen(int t, int * var_eo, Gyro_Project_InputSignals * inputs);

/*
fun��o: detecta a accao expressiva da parte de cima da cara (devolve 0.0 a 1.0)
param: t representa o tempo que j� passou desde inicio do programa
inputs corresponde � variavel com estrutura de 1 input da rede
return: 0.0 a 1.0
N�o EST� A FUNCIONAR
*/
float upperFace(int t, Gyro_Project_InputSignals * inputs);

/*
fun��o: detecta a accao expressiva da parte debaixo da cara (devolve 0.0 a 1.0)
param: t representa o tempo que j� passou desde inicio do programa
inputs corresponde � variavel com estrutura de 1 input da rede
return: 0.0 a 1.0
N�o EST� A FUNCIONAR
*/
float LowerFace(int t, Gyro_Project_InputSignals * inputs);

/*
fun��o: guarda a posi��o horizontal dos olhos no parametro x  (-1.0 a 1.0)
param: t representa o tempo que j� passou desde inicio do programa
inputs corresponde � variavel com estrutura de 1 input da rede
return: float -1.0 a 1.0
N�o EST� A FUNCIONAR
*/
float eyesPositionX(int t, Gyro_Project_InputSignals * inputs);


/*
fun��o: guarda a posi��o vertical dos olhos no parametro y (-1.0 a 1.0)
param: t representa o tempo que j� passou desde inicio do programa
 inputs corresponde � variavel com estrutura de 1 input da rede
return: float -1.0 a 1.0
N�o EST� A FUNCIONAR
*/
float eyesPositionY(int t, Gyro_Project_InputSignals * inputs);

/*
fun��o: guarda a altura vertical da pestana do olho esquerdo (0.0 a 1.0)
param: t representa o tempo que j� passou desde inicio do programa
inputs corresponde � variavel com estrutura de 1 input da rede
return: float 0.0 a 1.0
N�o EST� A FUNCIONAR
*/
float eyeLidLeft(int t, Gyro_Project_InputSignals * inputs);

/*
fun��o: guarda a altura vertical da pestana do olho direito (0.0 a 1.0)
param: t representa o tempo que j� passou desde inicio do programa
inputs corresponde � variavel com estrutura de 1 input da rede
return: float 0.0 a 1.0
N�o EST� A FUNCIONAR
*/
float eyeLidRight(int t, Gyro_Project_InputSignals * inputs);

/*
fun��o: (obsoleto) emite o valor da altura media das sobrancelhas (0.0 a 1.0)
param: t representa o tempo que j� passou desde inicio do programa
inputs corresponde � variavel com estrutura de 1 input da rede
return: float 0.0 a 1.0
N�o EST� A FUNCIONAR
*/
float eyeBrow(int t, Gyro_Project_InputSignals * inputs);

void callProfile();

void CognitiveTraining();

void CognitiveTrainingNeutral();

void CognitiveTrainingPush();

void ShowCognitive();

void ShowCognitivSignal();


/*
fun��o: nivel de frustracao (0.0 a 1.0)
return: float 0.0 a 1.0
N�o EST� A FUNCIONAR
*/
float frustrationLevel();

/*
fun��o: nivel de medita�ao (0.0 a 1.0)
return: float 0.0 a 1.0
N�o EST� A FUNCIONAR
*/
float meditationLevel();

/*
fun��o: verifica se existe ou n�o ruido ao detectar o sinal de Smile  (devolve uma mensagem de activa ou n�o activa)
return: void
N�o EST� A FUNCIONAR
*/
void Q_Expressive_Smile();

/*
fun��o: verifica se existe ou n�o ruido ao detectar o sinal de blink  (devolve uma mensagem de activa ou n�o activa)
return: void
N�o EST� A FUNCIONAR
*/
void Q_Expressive_Blink();

/*
fun��o: verifica se existe ou n�o ruido ao detectar o sinal de Piscar de olhos esquerdo  (devolve uma mensagem de activa ou n�o activa)
return: void
N�o EST� A FUNCIONAR
*/
void Q_Expressive_Wink_Left();

/*
fun��o: verifica se existe ou n�o ruido ao detectar o sinal de piscar de olho direito  (devolve uma mensagem de activa ou n�o activa)
return: void
N�o EST� A FUNCIONAR
*/
void Q_Expressive_Wink_Right();

/*
fun��o: verifica se existe ou n�o ruido ao detectar o sinal da emo��o de excitamento  (devolve uma mensagem de activa ou n�o activa)
return: void
N�o EST� A FUNCIONAR
*/
void Effective_Excitement();

/*
fun��o: verifica se existe ou n�o ruido ao detectar o sinal da emo��o de medita��o  (devolve uma mensagem de activa ou n�o activa)
return: void
N�o EST� A FUNCIONAR
*/
void Effective_meditation();

/*
fun��o: verifica se existe ou n�o ruido ao detectar o sinal da emo��o de frustra��o  (devolve uma mensagem de activa ou n�o activa)
return: void
N�o EST� A FUNCIONAR
*/
void Effective_Frustration();

/*
fun��o: devolve o nivel de bateria instantaneo numa mensagem e o nivel maximo de carga da bateria
return: void
EST� A FUNCIONAR
*/
void getBattery();

void NumContactQuality();


/*
fun��o: devolve o nivel de sinal de qireless
return: void
EST� A FUNCIONAR
*/
void WirelessSignal();

void CapaceteOn();

/*
Fun��o: recebe o numero da opera��o pretendida (1 = blink / 2 = blinkTwice / 3 = winkright / 4 = winkLeft / 5 = LookRight / 6 = LookLeft) e executa esse modo juntamente com o modo updateXY
param: operacao -- operacao pretendida
param: time -- variavel que encrementa ao fim de cada ciclo (tempo total passado)
param: inputs -- variavel criada pela Rede de petri com a estrutura (Gyro_Project_InputSignals)
param: *var_b -- variavel correspondente ao modo blink que conta a ultima vez que foi detectado um blink
param: *var_bt -- variavel correspondente ao modo blinktwice que conta a ultima vez que foi detectado um blink
param: *var_wl -- variavel correspondente ao modo winkleft que conta a ultima vez que foi detectado um piscar esquerdo (axo que esta ao contrario)
param: *var_wr -- variavel correspondente ao modo winkright que conta a ultima vez que foi detectado um piscar direito (axo que esta ao contrario)
param: va_ll  -- variavel correspondente ao modo Lookleft que conta a ultima vez que foi detectado um olhar pr� esquerda
return: (void)
*/
extern void Control(int operacao,int time, Gyro_Project_InputSignals *inputs, int *var_bt,int *var_ll, int *var_lr, int *var_lu, int *var_ld, int *var_eo);


/*
Fun��o: faz disconnect do Epoc
return: (void)
n�o est� a funcionar
*/
extern void stopEpoc();

/*
fun��o: Menu que mostra fun��es inbound do sistema 
return: void
*/
void StateSystem();


