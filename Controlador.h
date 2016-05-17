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
 
//SENSOR GIROSCÓPICO: updateX(), UpdateY(), updateXY(), instX(), insty()
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
Função: Faz correr a função EE_EngineConnect()
retorna: (void)
A funcionar
*/
extern void InitEpoc(void);

void loadUser();

/*
Função: Faz o programa esperar 8 segundos e mostra o Menu de Opções.
param: operacao -- devolve o valor da operacao por apontador
retorna: (void)
A funcionar
*/
void Menu();
extern void load(/*int *operacao*/);

/*
Funcao: torna ZERO todos os valores dos inputs da rede de petri.
Return: (void)
Não está a funcionar
*/
extern void ResetInputs(Gyro_Project_InputSignals *inputs);

int shutdown();

void interrupt();


extern void changeXY(int x);

/*
função: calcula xmax e ymax que corresponde à direção do gyroscopio
param: inputs corresponde à variavel com estrutura de 1 input da rede  
return: void
ESTÁ A FUNCIONAR
*/
extern void updateXY();

int UpdateX();

int UpdateY();

int instX();

int instY();



/*
função: verifica se os olhos estão a piscar (devolve um se estiverem a piscar, devolve zero se não estiverem
param: t representa o tempo que já passou desde  inicio do programa
 inputs corresponde à variavel com estrutura de 1 input da rede
return: 1 ou zero
ESTÁ A FUNCIONAR
*/
extern int Blink();



/*
função:
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
função: verifica se o olho esquerdo pisca (devolve um se true, devolve zero se não piscar)
param: t representa o tempo que já passou desde inicio do programa
inputs corresponde à variavel com estrutura de 1 input da rede
return: 1 ou zero
Não ESTÁ A FUNCIONAR
*/
extern int Winkleft();

/*
função: verifica se o olho direito pisca (devolve um se true, devolve zero se não piscar)
param: t representa o tempo que já passou desde inicio do programa
 inputs corresponde à variavel com estrutura de 1 input da rede
return: 1 ou zero
Não ESTÁ A FUNCIONAR
*/
extern int Winkright();

/*
função: verifica se os olhos apontam para a esquerda (devolve um se true, devolve zero se não olharem)
param: t representa o tempo que já passou desde inicio do programa
var_ll representa o numero de vezes que olhou para a esquerda dentro de um entervalo de tempo
inputs corresponde à variavel com estrutura de 1 input da rede
return: 1 ou zero
Não ESTÁ A FUNCIONAR
*/
extern int lookLeft();

/*
função: verifica se os olhos apontam para a direita (devolve um se true, devolve zero se não olharem)
param: t representa o tempo que já passou desde inicio do programa
var_lr representa o numero de vezes que olhou para a direita dentro de um entervalo de tempo
inputs corresponde à variavel com estrutura de 1 input da rede
return: 1 ou zero
Não ESTÁ A FUNCIONAR
*/
extern int lookRight();


/*
função: verifica o estado do smile (devolve um valor de 0.0 a 1.0)
param: t representa o tempo que já passou desde inicio do programa
 inputs corresponde à variavel com estrutura de 1 input da rede
return: (float) entre 0.0 a 1.0
Não ESTÁ A FUNCIONAR
*/
float Smile();

/*
função: verifica se os olhos estão abertos ou não (devolve um se estiver aberto, devolve zero se estiverem fechados
param: t representa o tempo que já passou desde inicio do programa
var_eo representa o numero de vezes que os olhos estivera abertos dentro de um entervalo de tempo
inputs corresponde à variavel com estrutura de 1 input da rede
return: 1 ou zero
Não ESTÁ A FUNCIONAR
*/
extern int EyesOpen(int t, int * var_eo, Gyro_Project_InputSignals * inputs);

/*
função: detecta a accao expressiva da parte de cima da cara (devolve 0.0 a 1.0)
param: t representa o tempo que já passou desde inicio do programa
inputs corresponde à variavel com estrutura de 1 input da rede
return: 0.0 a 1.0
Não ESTÁ A FUNCIONAR
*/
float upperFace(int t, Gyro_Project_InputSignals * inputs);

/*
função: detecta a accao expressiva da parte debaixo da cara (devolve 0.0 a 1.0)
param: t representa o tempo que já passou desde inicio do programa
inputs corresponde à variavel com estrutura de 1 input da rede
return: 0.0 a 1.0
Não ESTÁ A FUNCIONAR
*/
float LowerFace(int t, Gyro_Project_InputSignals * inputs);

/*
função: guarda a posição horizontal dos olhos no parametro x  (-1.0 a 1.0)
param: t representa o tempo que já passou desde inicio do programa
inputs corresponde à variavel com estrutura de 1 input da rede
return: float -1.0 a 1.0
Não ESTÁ A FUNCIONAR
*/
float eyesPositionX(int t, Gyro_Project_InputSignals * inputs);


/*
função: guarda a posição vertical dos olhos no parametro y (-1.0 a 1.0)
param: t representa o tempo que já passou desde inicio do programa
 inputs corresponde à variavel com estrutura de 1 input da rede
return: float -1.0 a 1.0
Não ESTÁ A FUNCIONAR
*/
float eyesPositionY(int t, Gyro_Project_InputSignals * inputs);

/*
função: guarda a altura vertical da pestana do olho esquerdo (0.0 a 1.0)
param: t representa o tempo que já passou desde inicio do programa
inputs corresponde à variavel com estrutura de 1 input da rede
return: float 0.0 a 1.0
Não ESTÁ A FUNCIONAR
*/
float eyeLidLeft(int t, Gyro_Project_InputSignals * inputs);

/*
função: guarda a altura vertical da pestana do olho direito (0.0 a 1.0)
param: t representa o tempo que já passou desde inicio do programa
inputs corresponde à variavel com estrutura de 1 input da rede
return: float 0.0 a 1.0
Não ESTÁ A FUNCIONAR
*/
float eyeLidRight(int t, Gyro_Project_InputSignals * inputs);

/*
função: (obsoleto) emite o valor da altura media das sobrancelhas (0.0 a 1.0)
param: t representa o tempo que já passou desde inicio do programa
inputs corresponde à variavel com estrutura de 1 input da rede
return: float 0.0 a 1.0
Não ESTÁ A FUNCIONAR
*/
float eyeBrow(int t, Gyro_Project_InputSignals * inputs);

void callProfile();

void CognitiveTraining();

void CognitiveTrainingNeutral();

void CognitiveTrainingPush();

void ShowCognitive();

void ShowCognitivSignal();


/*
função: nivel de frustracao (0.0 a 1.0)
return: float 0.0 a 1.0
Não ESTÁ A FUNCIONAR
*/
float frustrationLevel();

/*
função: nivel de meditaçao (0.0 a 1.0)
return: float 0.0 a 1.0
Não ESTÁ A FUNCIONAR
*/
float meditationLevel();

/*
função: verifica se existe ou não ruido ao detectar o sinal de Smile  (devolve uma mensagem de activa ou não activa)
return: void
Não ESTÁ A FUNCIONAR
*/
void Q_Expressive_Smile();

/*
função: verifica se existe ou não ruido ao detectar o sinal de blink  (devolve uma mensagem de activa ou não activa)
return: void
Não ESTÁ A FUNCIONAR
*/
void Q_Expressive_Blink();

/*
função: verifica se existe ou não ruido ao detectar o sinal de Piscar de olhos esquerdo  (devolve uma mensagem de activa ou não activa)
return: void
Não ESTÁ A FUNCIONAR
*/
void Q_Expressive_Wink_Left();

/*
função: verifica se existe ou não ruido ao detectar o sinal de piscar de olho direito  (devolve uma mensagem de activa ou não activa)
return: void
Não ESTÁ A FUNCIONAR
*/
void Q_Expressive_Wink_Right();

/*
função: verifica se existe ou não ruido ao detectar o sinal da emoção de excitamento  (devolve uma mensagem de activa ou não activa)
return: void
Não ESTÁ A FUNCIONAR
*/
void Effective_Excitement();

/*
função: verifica se existe ou não ruido ao detectar o sinal da emoção de meditação  (devolve uma mensagem de activa ou não activa)
return: void
Não ESTÁ A FUNCIONAR
*/
void Effective_meditation();

/*
função: verifica se existe ou não ruido ao detectar o sinal da emoção de frustração  (devolve uma mensagem de activa ou não activa)
return: void
Não ESTÁ A FUNCIONAR
*/
void Effective_Frustration();

/*
função: devolve o nivel de bateria instantaneo numa mensagem e o nivel maximo de carga da bateria
return: void
ESTÁ A FUNCIONAR
*/
void getBattery();

void NumContactQuality();


/*
função: devolve o nivel de sinal de qireless
return: void
ESTÁ A FUNCIONAR
*/
void WirelessSignal();

void CapaceteOn();

/*
Função: recebe o numero da operação pretendida (1 = blink / 2 = blinkTwice / 3 = winkright / 4 = winkLeft / 5 = LookRight / 6 = LookLeft) e executa esse modo juntamente com o modo updateXY
param: operacao -- operacao pretendida
param: time -- variavel que encrementa ao fim de cada ciclo (tempo total passado)
param: inputs -- variavel criada pela Rede de petri com a estrutura (Gyro_Project_InputSignals)
param: *var_b -- variavel correspondente ao modo blink que conta a ultima vez que foi detectado um blink
param: *var_bt -- variavel correspondente ao modo blinktwice que conta a ultima vez que foi detectado um blink
param: *var_wl -- variavel correspondente ao modo winkleft que conta a ultima vez que foi detectado um piscar esquerdo (axo que esta ao contrario)
param: *var_wr -- variavel correspondente ao modo winkright que conta a ultima vez que foi detectado um piscar direito (axo que esta ao contrario)
param: va_ll  -- variavel correspondente ao modo Lookleft que conta a ultima vez que foi detectado um olhar prá esquerda
return: (void)
*/
extern void Control(int operacao,int time, Gyro_Project_InputSignals *inputs, int *var_bt,int *var_ll, int *var_lr, int *var_lu, int *var_ld, int *var_eo);


/*
Função: faz disconnect do Epoc
return: (void)
não está a funcionar
*/
extern void stopEpoc();

/*
função: Menu que mostra funções inbound do sistema 
return: void
*/
void StateSystem();


