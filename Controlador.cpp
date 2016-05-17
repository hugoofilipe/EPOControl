/*Author: Hugo Filipe, UNINOVA*/
#define _CRT_SECURE_NO_WARNINGS 

#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include "Controlador.h"
#include "edk.h"
#include "net_types.h"
#include <istream>
#include <math.h>
#include "edkErrorCode.h"
#include "EmoStateDLL.h"
#include "clienteSocket.h"

using std::string;
#define MAX_ACTIONS 14

bool outOfBound = false; //Fora do Limite
float currX = 0, currY = 0;
double maxRadius = 5000; //limite do raio desejado estava 10000
float xmax = 0, ymax = 0;
float preX = 0, preY = 0;
int instVarX=0, instVarY = 0;
int incOrDec = 10;
float oldXVal = 0, oldYVal = 0;
unsigned long pass = 0, globalElapsed = 0;
int count = 0;
float x;
int actualX = 0, actualY = 0;
int nChoice = 0;
bool fimDoTreino = true;
int number;
int NEUTRAL,PUSH,PULL,LIFT,DROP,LEFT,RIGHT,ROTATE_LEFT,ROTATE_RIGHT,ROTATE_CLOCKWISE,ROTATE_COUNTER_CLOCKWISE,ROTATE_FORWARDS,ROTATE_REVERSE,DISAPPEAR;
char ResetMsg[10] = "000000000";

const  string m_actions[MAX_ACTIONS] = { "NEUTRAL","PUSH","PULL","LIFT","DROP","LEFT","RIGHT","ROTATE_LEFT","ROTATE_RIGHT","ROTATE_CLOCKWISE","ROTATE_COUNTER_CLOCKWISE","ROTATE_FORWARDS","ROTATE_REVERSE","DISAPPEAR" };
EE_CognitivAction_t m_activeActions[] = { COG_NEUTRAL,COG_PUSH,COG_PULL,COG_LIFT,COG_DROP,COG_LEFT,COG_RIGHT,COG_ROTATE_LEFT,COG_ROTATE_RIGHT,COG_ROTATE_CLOCKWISE,COG_ROTATE_COUNTER_CLOCKWISE,COG_ROTATE_FORWARDS,COG_ROTATE_REVERSE,COG_DISAPPEAR };
EE_CognitivAction_t set_activeActions[3];

EmoEngineEventHandle hEvent = EE_EmoEngineEventCreate();  // inicializa uma variavel identificador de eventos
EmoEngineEventHandle eProfile = EE_ProfileEventCreate();
EmoStateHandle eState = EE_EmoStateCreate(); // inicializa uma variavel identificador de estados
unsigned int profileSize;
unsigned char * profileBuffer = new unsigned char[profileSize];
int result;
unsigned int userID = -1; //isto acontece quando o epoc não está ligado 

void InitEpoc(void) {
	EE_EngineConnect();	
	
	EE_GetBaseProfile(eProfile);
	CapaceteOn();
	load();
	loadUser();	
	if (EE_EmoEngineEventGetUserId(hEvent, &userID) == EDK_OK) {
		printf("\n user = %d\n", userID);
	}
	//EE_EngineRemoteConnect("127.0.1.1",3008);
}

void loadUser() {
	if (EE_EmoEngineEventGetUserId(hEvent, &userID) == EDK_OK) {
		printf("\nuser = %d\n", userID);
	}	

	if (EE_LoadUserProfile(userID, "test.emu") != EDK_OK) {
		printf("\nloaduserprofile: ERROR\n");
		getchar();
	}
	if (EE_GetUserProfileSize(eProfile, &profileSize) != EDK_OK)
	{
		printf("\ngetuserprofileSize: ERROR\n");
		getchar();
	}
	
	if (EE_GetUserProfile(userID, eProfile) != EDK_OK) {
		printf("\ngetuserprofile: ERROR\n)");
		getchar();
	}
		
	result = EE_GetUserProfileBytes(eProfile, profileBuffer, profileSize);
	//unsigned int profileSize = 0;
	//unsigned char* profileBuf = NULL;
	if (EE_SetUserProfile(userID, profileBuffer, profileSize) != EDK_OK) {
		printf("\nsetuserprofile: error\n");
		getchar();
	}
}

void Menu() {
	printf("Done.\n\n\nMENU:\n1-Blink\n2-Blink Twice\n3-wink left\n4-Wink right\n5-Look left\n6-Look right\n7-Look Up\n8-Look Down\n9-Eyes Open\n10-Smile\n11- Upper face \n12- Lower face\n13- horizontal eyes position\n14- vertical eyes position \n15- eyelid olho esquerdo\n16- eyelid olho direito\n17- eyebrow\n18- ação cognitiva \n19- nivel de frustracao\n20- nivel de meditação\n(Choose one to start...)\n");
}
void load() {
	printf("Start after 5 seconds\n");
	Sleep(1000);
	system("CLS"); // clean screenprintf("Start after 5 seconds\n");
	printf("Start after 4 seconds\n");
	Sleep(1000);
	system("CLS"); // clean screenprintf("Start after 5 seconds\n");
	printf("Start after 3 seconds\n");
	Sleep(1000);
	system("CLS"); // clean screenprintf("Start after 5 seconds\n");
	printf("Start after 2 seconds\n");
	Sleep(1000);
	system("CLS"); // clean screenprintf("Start after 5 seconds\n");
	printf("Start after 1 seconds\n");
	Sleep(1000);
	system("CLS"); // clean screenprintf("Start after 5 seconds\n");
				   //printf("Done.\n");
				   //Menu();
				   /*std::cin >> *ptr;	*/
}

void ResetInputs(Gyro_Project_InputSignals *inputs) {
	// escrerver aqui as variaveis de entrada da rede do sistema que queremos fazer RESET
	inputs->In_X = 0;
	inputs->In_Y = 0;
	//inputs->In_Blink=0;
}

int shutdown() {
	if (GetAsyncKeyState(VK_END)) //Tecla "END"
	{
		closeSocket(); //só necessário quando é usado sockets, mas não deve dar problemas...
		stopEpoc();
		return 1;
	}
	return 0;
}

void interrupt() {
	
	if (GetAsyncKeyState(0x4D))   //tabela ascii letra "M" 4 LEVEL 
	{	
		send(cliente, ResetMsg, strlen(ResetMsg), 0);
		send(cliente, ResetMsg, strlen(ResetMsg), 0);
		send(cliente, ResetMsg, strlen(ResetMsg), 0);
		system("CLS"); // clean screenprintf
		cognitivGet4Level();
		cognitivActivation4Level();
	}

	if (GetAsyncKeyState(0x50))   //tabela ascii letra "P" PAUSE
	{
		send(cliente, ResetMsg, strlen(ResetMsg), 0);
		send(cliente, ResetMsg, strlen(ResetMsg), 0);
		send(cliente, ResetMsg, strlen(ResetMsg), 0);
		getchar();
	}
	
	if (GetAsyncKeyState(0x54))   //tabela ascii letra "T" TRAINING
	{
		send(cliente, ResetMsg, strlen(ResetMsg), 0);
		send(cliente, ResetMsg, strlen(ResetMsg), 0);
		send(cliente, ResetMsg, strlen(ResetMsg), 0);
		training();
	}

	if (GetAsyncKeyState(0x4E))      //tabela ascii letra "N" ALL LEVEL'S
	{
		send(cliente, ResetMsg, strlen(ResetMsg), 0);
		send(cliente, ResetMsg, strlen(ResetMsg), 0);
		send(cliente, ResetMsg, strlen(ResetMsg), 0);
		system("CLS"); // clean screenprintf
		cognitivGetAllLevel();
		cognitivActivationAllLevel();
	}

	if (GetAsyncKeyState(0x42))		//tabela ascii letra "B" BATTERY
	{
		send(cliente, ResetMsg, strlen(ResetMsg), 0);
		send(cliente, ResetMsg, strlen(ResetMsg), 0);
		send(cliente, ResetMsg, strlen(ResetMsg), 0);
		system("CLS"); // clean screenprintf
		getBattery();
		Sleep(2000);
	}
	if (GetAsyncKeyState(0x56))		//tabela ascii letra "V" WIRELESS SIGNAL
	{
		send(cliente, ResetMsg, strlen(ResetMsg), 0);
		send(cliente, ResetMsg, strlen(ResetMsg), 0);
		send(cliente, ResetMsg, strlen(ResetMsg), 0);
		system("CLS"); // clean screenprintf
		WirelessSignal();
		Sleep(2000);
	}
}

void changeXY(int x) // x = 0 : idle
{
	if (currX >0)
	{
		float temp = currY / currX;
		currX -= incOrDec;
		currY = temp*currX;
	}
	else if (currX < 0)
	{
		float temp = currY / currX;
		currX += incOrDec;
		currY = temp*currX;
	}
	else
	{
		if (currY > 0) currY -= incOrDec;
		else if (currY <0) currY += incOrDec;
	}
	if (x == 0)
	{
		if ((abs(currX) <= incOrDec) && (abs(currY) <= incOrDec))
		{
			xmax = 0;
			ymax = 0;
		}
		else
		{
			xmax = currX;
			ymax = currY;
		}
	}
	else
	{
		if ((abs(currX) <= incOrDec) && (abs(currY) <= incOrDec))
		{
			xmax = 0;
			ymax = 0;
		}
	}
}

void updateXY()
{
	int gyroX = 0, gyroY = 0;
	int ciclo = 0;

	EE_HeadsetGetGyroDelta(0, &gyroX, &gyroY);
	/*printf("x=%d y=%d", gyroX, gyroY);*/
	instVarX = gyroX + 4000;
	instVarY = gyroY + 4000;

	xmax += gyroX + 0;
	ymax += gyroY + 0;

	if (outOfBound)
	{
		if (preX != gyroX && preY != gyroY)
		{
			xmax = currX;
			ymax = currY;
		}
	}
	double val = sqrt((float)(xmax*xmax + ymax*ymax)); //hipotenusa

	//std::cout << "xmax: " << xmax << " ; ymax: " << ymax << std::endl;   //imprime
	actualX = xmax + 4000;
	actualY = ymax + 4000;
	//printf("x: %f  ", xmax );

	if (val >= maxRadius)
	{
		changeXY(1);
		outOfBound = true;
		preX = gyroX;
		preY = gyroY;
	}
	else
	{
		outOfBound = false;
		if (oldXVal == gyroX && oldYVal == gyroY)
		{
			++count;
			if (count > 10) // acho que é o tempo que demora a posicionar a nova coordenada (0,0)
			{
				changeXY(0);
			}
		}
		else
		{
			count = 0;
			currX = xmax;
			currY = ymax;
			oldXVal = gyroX;
			oldYVal = gyroY;
		}
	}
	/*experiemtnar
	return xmax + 4000, ymax + 4000;*/
	//Sleep(15); // Sem Drone -> sleep 15 || Com drone -> sleep 70
}

int UpdateX() {
	updateXY();
	return actualX;
}

int UpdateY() {
	updateXY();
	return actualY;
}

int instX() {
	updateXY();
	return instVarX;
}
int instY() {
	return instVarY;
}

int Blink() {
	int state = EE_EngineGetNextEvent(hEvent);
	// New event needs to be handled
	if (state == EDK_OK) {
		EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
		EE_EmoEngineEventGetUserId(hEvent, &userID);
		// Log the EmoState if it has been updated
		if (eventType == EE_EmoStateUpdated) {
			EE_EmoEngineEventGetEmoState(hEvent, eState);
		}
	}
	if (ES_ExpressivIsBlink(eState)) {
		printf("Blinking...");
		return 1;
	}
	else return 0;
}

void newAction() {

	int state = EE_EngineGetNextEvent(hEvent);
	// New event needs to be handled
	if (state == EDK_OK) {

		EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
		EE_EmoEngineEventGetUserId(hEvent, &userID);
		switch (eventType) {
		case EE_UserAdded:
		{
			printf("\nAdd new user = %d", userID); // << userID << std::endl;
			getchar();
			break;
		}
		case EE_UserRemoved:
		{
			printf("\nUser has been removed"); // << userID << " has been removed." << std::endl;
			Sleep(1000);
			break;
		}
		case EE_ProfileEvent:
		{
			printf("\nprofile event detected\n");
		}
		// Log the EmoState if it has been updated
		case EE_EmoStateUpdated:
		{
			//printf("\nEE_EmoStateUpdated detected.");
			EE_EmoEngineEventGetEmoState(hEvent, eState);
			EE_CognitivAction_t actionType = ES_CognitivGetCurrentAction(eState);
			float				actionPower = ES_CognitivGetCurrentActionPower(eState);
			/*if (EE_CognitivGetTrainedSignatureActions(userID, &actionType) == EDK_OK)
			{
				printf("\nEE_CognitivGetTrainedSignatureActions done \n");
				getchar();
			}*/
			switch (actionType) {
			case COG_PUSH:
				printf(" - PUSH with %f power", actionPower);
				PUSH = 1;
				break;
			case COG_PULL:
				printf(" - PULL with %f power", actionPower);
				PULL = 1;
				break;
			case COG_LIFT:
				if (actionPower > 0.3) {
					printf(" - LIFT with %f power", actionPower);
					LIFT = 1;
				}
				break;
			case COG_DROP:
				if (actionPower > 0.3) {
					printf(" - DROP with %f power", actionPower);
					DROP = 1;
				}
				break;
			case COG_LEFT:
				printf(" - LEFT with %f power", actionPower);
				LEFT = 1;
				break;
			case COG_RIGHT:
				printf(" - RIGHT with %f power", actionPower);
				RIGHT = 1;
				break;
			case COG_ROTATE_LEFT:
				printf(" - ROTATE_LEFT with %f power", actionPower);
				ROTATE_LEFT = 1;
				break;
			case COG_ROTATE_RIGHT:
				printf(" - ROTATE_RIGHT with %f power", actionPower);
				ROTATE_RIGHT = 1;
				break;
			case COG_ROTATE_CLOCKWISE:
				printf(" - ROTATE_CLOCKWISE with %f power", actionPower);
				ROTATE_CLOCKWISE = 1;
				break;
			case COG_ROTATE_COUNTER_CLOCKWISE:
				printf(" - ROTATE_COUNTER_CLOCKWISE with %f power", actionPower);
				ROTATE_COUNTER_CLOCKWISE = 1;
				break;
			case COG_ROTATE_FORWARDS:
				printf(" - ROTATE_FORWARDS with %f power", actionPower);
				ROTATE_FORWARDS = 1;
				break;
			case COG_ROTATE_REVERSE:
				printf(" - ROTATE_REVERSE with %f power", actionPower);
				ROTATE_REVERSE = 1;
				break;
			case COG_DISAPPEAR:
				printf(" - DISAPPEAR with %f power", actionPower);
				DISAPPEAR = 1;
				/*if (actionPower>0.8)
				{
				printf(" MOVE RIGHT");
				}	*/
				break;
			case COG_NEUTRAL:
				printf(" - NEUTRAL");
				break;
			default:
				printf(" - No action with %f power", actionPower);
				break;
			}
			break;
		}
		case EE_CognitivEvent:
		{
			handleCognitivEvent(hEvent);
			break;
		}

		default:
			break;
		}
	}
	else if (state != EDK_NO_EVENT)
	{
		printf("\nInternal error in Emotiv Engine! ");
		getchar();
	}
}

void handleCognitivEvent(EmoEngineEventHandle cognitivEvent) {
	unsigned int userID = 0;
	EE_EmoEngineEventGetUserId(cognitivEvent, &userID);
	EE_CognitivEvent_t eventType = EE_CognitivEventGetType(cognitivEvent); //deveria se mudar o nome de eventType para cognitivEventType

	switch (eventType) {

	case EE_CognitivTrainingStarted:
	{
		printf("\nCognitiv training for user STARTED!\n");
		break;
	}

	case EE_CognitivTrainingSucceeded:
	{

		printf("\nCognitiv training for user SUCCEEDED!");
		if (EE_CognitivSetTrainingControl(userID, COG_ACCEPT) != EDK_OK) {
			printf("\nError trying to accept the session");
		}
		else
		{
			Sleep(3000);
			//EE_CognitivSetTrainingControl(userID, COG_NONE);
		}
		break;
		/*if (EE_CognitivSetTrainingControl(userID, COG_REJECT) != EDK_OK) {
		printf("\nError trying to reject the session");
		Sleep(2000);
		break;
		}*/
	}

	case EE_CognitivTrainingFailed:
	{
		printf("\nCognitiv training for user FAILED!");
		break;
	}

	case EE_CognitivTrainingCompleted:
	{
		printf("\nCognitiv training for user COMPLETED!");
		EE_CognitivAction_t   pActionOut, pActiveActionsOut;
		EE_CognitivGetTrainingAction(userID, &pActionOut);
		//EE_CognitivGetActiveActions(userID, &pActiveActionsOut)
		/*
		for (int i = 0; i< 2000; i++) {
			if (m_activeActions[i] == pActionOut) {
				printf("\nsignal '%s' has been trained ", m_actions[i].c_str());
			}
		}*/
		/*EE_CognitivSetTrainingControl(userID, COG_ACCEPT);
		EE_CognitivSetTrainingControl(userID, COG_NONE);*/
		EE_SaveUserProfile(0, "test.emu");

		fimDoTreino = false;
		break;
	}

	case EE_CognitivTrainingDataErased:
	{
		printf("\nCognitiv training for user ERASED!");
		break;
	}

	case EE_CognitivTrainingRejected:
	{
		printf("\nCognitiv training for user REJECTED!");
		break;
	}

	case EE_CognitivTrainingReset:
	{
		printf("\nCognitiv training for user RESET!");
		break;
	}

	case EE_CognitivAutoSamplingNeutralCompleted:
	{
		printf("\nCognitiv training for user COMPLETED!     EE_CognitivAutoSamplingNeutralCompleted");
		break;
	}

	case EE_CognitivSignatureUpdated:
	{
		printf("\nCognitiv training for user UPDATED!");

		break;
	}
	case EE_CognitivNoEvent:
		break;

	default:
		printf("\nCognitiv training: Unhandled event");
		break;
	}
}

// Inicio do treinamento de uma ação
void training()
{
	EE_EmoEngineEventGetUserId(hEvent, &userID);

	if (EE_CognitivSetTrainingAction(userID, COG_NEUTRAL) != EDK_OK) {
		printf("\nError in the 'NEUTRAL' training initiation");
		getchar();
	}
	else {
		printf("\nThe 'NEUTRAL' training last 8 seconds.\n\nPRESS ENTER...");
		getchar();
		Sleep(1000);

		if (EE_CognitivSetTrainingControl(userID, COG_START) != EDK_OK) {
			printf("\nError in the training start");
			getchar();
		}
		else {
			fimDoTreino = true;
			printf("\nStart Training...");

			while (fimDoTreino) {
				newAction();
			}
			printf("\nFinished 'NEUTRAL' training.\nLoading...");
			Sleep(5000);
		}
	}
	printf("\nQuantos tipos de treino Cognitivo se pretende fazer?\n");
	scanf_s("%d", &number); getchar();

	switch (number) {
	case 1: {
		system("CLS"); // clean screenprintf
		printf("TRAINNIG...\n|1 = PUSH\n|2 = PULL\n|3 = LIFT\n|4 = DROP\n|5 = LEFT\n|6 = RIGHT\n|7 = ROTATE_LEFT\n|8 = ROTATE_RIGHT\n|9 = ROTATE_CLOCKWISE\n|9 = ROTATE_COUNTER_CLOCKWISE\n|10 = ROTATE_FORWARDS\n|11 = ROTATE_REVERSE\n|12 = DISAPPEAR\nCHOOSE ONE:  ");
		scanf_s("%d", &nChoice); getchar();
		printf("\nSetting Cognitiv training action for user '%d' to %s  ...", userID, m_actions[nChoice].c_str());

		if (EE_CognitivSetActiveActions(userID, m_activeActions[nChoice]) != EDK_OK) {  //set active actions
			printf("Error in the supported action activation");
			//getchar();
		}
		if (EE_CognitivSetTrainingAction(userID, m_activeActions[nChoice]) != EDK_OK) {  //set training action
			printf("\nError in the training initiation");
			getchar();
		}
		else {
			printf("\nThe training last 10 seconds.\n\nPRESS ENTER...");
			getchar();
			Sleep(2000);

			if (EE_CognitivSetTrainingControl(userID, COG_START) != EDK_OK) {  //set training control
				printf("\nError in the training start");
				getchar();
			}
			else {
				fimDoTreino = true;
				printf("\nStart Training...");

				while (fimDoTreino) {
					newAction();
				}
				printf("\nFinished training.\nLoading...");
				Sleep(5000);
			}
		}
		break;
	}
	case 2: {
		system("CLS"); // clean screenprintf
		printf("TRAINNIG...\n|1 = PUSH\n|2 = PULL\n|3 = LIFT\n|4 = DROP\n|5 = LEFT\n|6 = RIGHT\n|7 = ROTATE_LEFT\n|8 = ROTATE_RIGHT\n|9 = ROTATE_CLOCKWISE\n|9 = ROTATE_COUNTER_CLOCKWISE\n|10 = ROTATE_FORWARDS\n|11 = ROTATE_REVERSE\n|12 = DISAPPEAR\nCHOOSE ONE:  ");
		for (int i = 0; i < 2; i++)
		{
			scanf_s("%d", &nChoice); getchar();
			set_activeActions[i] = m_activeActions[nChoice];
		}
		if (EE_CognitivSetActiveActions(userID, set_activeActions[0] | set_activeActions[1]) != EDK_OK) {  //set active actions
			printf("Error in the supported action activation");
		}

		for (int x = 0; x < 2; x++)
		{
			if (EE_CognitivSetTrainingAction(userID, set_activeActions[x]) != EDK_OK) {  //set training action
				printf("\nError in the training initiation");
				getchar();
			}
			else {
				printf("\nThe training %s last 8 seconds.\n\nPRESS ENTER..."/*, m_actions[x+1].c_str()*/);
				getchar();
				Sleep(1000);

				if (EE_CognitivSetTrainingControl(userID, COG_START) != EDK_OK) {  //set training control
					printf("\nError in the training start");
					getchar();
				}
				else {
					fimDoTreino = true;
					printf("\nStart Training...");

					while (fimDoTreino) {
						newAction();
					}
					printf("\nFinished training.\nLoading...");
					Sleep(5000);
				}
			}
		}
		break;
	}
	case 3:
	{
		system("CLS"); // clean screenprintf
		printf("TRAINNIG...\n|1 = PUSH\n|2 = PULL\n|3 = LIFT\n|4 = DROP\n|5 = LEFT\n|6 = RIGHT\n|7 = ROTATE_LEFT\n|8 = ROTATE_RIGHT\n|9 = ROTATE_CLOCKWISE\n|9 = ROTATE_COUNTER_CLOCKWISE\n|10 = ROTATE_FORWARDS\n|11 = ROTATE_REVERSE\n|12 = DISAPPEAR\nCHOOSE ONE:  ");
		for (int i = 0; i < 3; i++)
		{
			scanf_s("%d", &nChoice); getchar();
			set_activeActions[i] = m_activeActions[nChoice];
		}
		if (EE_CognitivSetActiveActions(userID, set_activeActions[0] | set_activeActions[1] | set_activeActions[2]) != EDK_OK) {  //set active actions
			printf("Error in the supported action activation");
		}

		for (int x = 0; x < 3; x++)
		{
			if (EE_CognitivSetTrainingAction(userID, set_activeActions[x]) != EDK_OK) {  //set training action
				printf("\nError in the training initiation");
				getchar();
			}
			else {
				printf("\nThe training '%s' last 8 seconds.\n\nPRESS ENTER...",m_actions[x+1].c_str());
				getchar();
				Sleep(1000);

				if (EE_CognitivSetTrainingControl(userID, COG_START) != EDK_OK) {  //set training control
					printf("\nError in the training start");
					getchar();
				}
				else {
					fimDoTreino = true;
					printf("\nStart Training...");

					while (fimDoTreino) {
						newAction();
					}
					printf("\nFinished training.\nLoading...");
					Sleep(5000);
				}
			}
		}
		break;
	}
	case 4:
	{
		system("CLS"); // clean screenprintf
		printf("TRAINNIG...\n|1 = PUSH\n|2 = PULL\n|3 = LIFT\n|4 = DROP\n|5 = LEFT\n|6 = RIGHT\n|7 = ROTATE_LEFT\n|8 = ROTATE_RIGHT\n|9 = ROTATE_CLOCKWISE\n|9 = ROTATE_COUNTER_CLOCKWISE\n|10 = ROTATE_FORWARDS\n|11 = ROTATE_REVERSE\n|12 = DISAPPEAR\nCHOOSE ONE:  ");
		for (int i = 0; i < 4; i++)
		{
			scanf_s("%d", &nChoice); getchar();
			set_activeActions[i] = m_activeActions[nChoice];
		}
		if (EE_CognitivSetActiveActions(userID, set_activeActions[0] | set_activeActions[1] | set_activeActions[2] | set_activeActions[3]) != EDK_OK) {  //set active actions
			printf("Error in the supported action activation");
		}

		for (int x = 0; x < 4; x++)
		{
			if (EE_CognitivSetTrainingAction(userID, set_activeActions[x]) != EDK_OK) {  //set training action
				printf("\nError in the training initiation");
				getchar();
			}
			else {
				printf("\nThe training '%s' last 8 seconds.\n\nPRESS ENTER...", m_actions[x + 1].c_str());
				getchar();
				Sleep(1000);

				if (EE_CognitivSetTrainingControl(userID, COG_START) != EDK_OK) {  //set training control
					printf("\nError in the training start");
					getchar();
				}
				else {
					fimDoTreino = true;
					printf("\nStart Training...");

					while (fimDoTreino) {
						newAction();
					}
					printf("\nFinished training.\nLoading...");
					Sleep(5000);
				}
			}
		}
		break;
	}
	
	default:
		break;
	}
	printf("\nTREINO COMPLETO...\n"); getchar();
}




void cognitivResetActions() {
	EE_EmoEngineEventGetUserId(hEvent, &userID);
	EE_CognitivSetTrainingControl(userID, COG_ERASE);
	EE_CognitivSetTrainingControl(userID, COG_RESET);
}



void cognitivActivationAllLevel() {
	int level;
	printf("Choose level of actions activation (sensitivity level of all actions (lowest: 1, highest: 7):  ");
	scanf_s("%d", &level); getchar();
	EE_EmoEngineEventGetUserId(hEvent, &userID);
	if (EE_CognitivSetActivationLevel(userID, level) != EDK_OK)
	{
		printf("ERROR in activation level");
		getchar();
	}
}

void cognitivActivation4Level() {
	int Level1, Level2, Level3, Level4;
	printf("Choose level of actions activation (sensitivity level of actions (lowest: 1, highest: 10)");
	printf("\nAction 1: ");	scanf_s("%d", &Level1); getchar();
	printf("\nAction 2: "); scanf_s("%d", &Level2); getchar();
	printf("\nAction 3: "); scanf_s("%d", &Level3); getchar();
	printf("\nAction 4: "); scanf_s("%d", &Level4); getchar();
	EE_EmoEngineEventGetUserId(hEvent, &userID);
	if (EE_CognitivSetActionSensitivity( userID,Level1, Level2,Level3,Level4) != EDK_OK) //sensitivity of action  (min: 1, max: 10)
	{
		printf("ERROR in activation level");
		getchar();
	}
}

void cognitivGetAllLevel() {
	int pLevelOut;
	if (EE_CognitivGetActivationLevel(userID, &pLevelOut) != EDK_OK) {
		printf("ERROR reading level of actions\n");
		getchar();
	}
	printf("Level of all actions activation (sensitivity level of actions (lowest: 1, highest: 7)");
	printf("\nAll Action: %d\n", pLevelOut);

}

void cognitivGet4Level() {
	
	int pAction1SensitivityOut, pAction2SensitivityOut, pAction3SensitivityOut, pAction4SensitivityOut;
	if (EE_CognitivGetActionSensitivity(userID, &pAction1SensitivityOut, &pAction2SensitivityOut, &pAction3SensitivityOut, &pAction4SensitivityOut) != EDK_OK) {
		printf("ERROR reading level of actions\n");
		getchar();
	}
	printf("Level of actions activation (sensitivity level of actions (lowest: 1, highest: 10)");
	printf("\nAction 1: %d\nAction 2: %d\nAction3: %d\nAction 4: %d\n", pAction1SensitivityOut, pAction2SensitivityOut, pAction3SensitivityOut, pAction4SensitivityOut);
}


int Winkleft() {
	int state = EE_EngineGetNextEvent(hEvent);
	// New event needs to be handled
	if (state == EDK_OK) {
		EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
		EE_EmoEngineEventGetUserId(hEvent, &userID);
		// Log the EmoState if it has been updated
		if (eventType == EE_EmoStateUpdated) {
			EE_EmoEngineEventGetEmoState(hEvent, eState);
		}
	}
	if (ES_ExpressivIsLeftWink(eState)) {
		printf("left wink...");
		return 1;
	}
	else return 0;
}

int Winkright() {
	int state = EE_EngineGetNextEvent(hEvent);
	// New event needs to be handled
	if (state == EDK_OK) {
		EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
		EE_EmoEngineEventGetUserId(hEvent, &userID);
		// Log the EmoState if it has been updated
		if (eventType == EE_EmoStateUpdated) {
			EE_EmoEngineEventGetEmoState(hEvent, eState);
		}
	}
	if (ES_ExpressivIsRightWink(eState)) {
		printf("right Wink...");
		return 1;
	}
	else return 0;
}

int lookLeft() {
	int state = EE_EngineGetNextEvent(hEvent);
	// New event needs to be handled
	if (state == EDK_OK) {
		EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
		EE_EmoEngineEventGetUserId(hEvent, &userID);
		// Log the EmoState if it has been updated
		if (eventType == EE_EmoStateUpdated) {
			EE_EmoEngineEventGetEmoState(hEvent, eState);
		}
	}
	if (ES_ExpressivIsLookingLeft(eState)) {
		printf("Look Left...");
		return 1;
	}
	else return 0;
}

int lookRight() {
	int state = EE_EngineGetNextEvent(hEvent);
	// New event needs to be handled
	if (state == EDK_OK) {
		EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
		EE_EmoEngineEventGetUserId(hEvent, &userID);
		// Log the EmoState if it has been updated
		if (eventType == EE_EmoStateUpdated) {
			EE_EmoEngineEventGetEmoState(hEvent, eState);
		}
	}
	if (ES_ExpressivIsLookingRight(eState)) {
		printf("look Right...");		
		return 1;
	}
	else return 0;
}




float Smile() {
	int state = EE_EngineGetNextEvent(hEvent);
	// New event needs to be handled
	if (state == EDK_OK) {
		EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
		EE_EmoEngineEventGetUserId(hEvent, &userID);
		// Log the EmoState if it has been updated
		if (eventType == EE_EmoStateUpdated) {
			EE_EmoEngineEventGetEmoState(hEvent, eState);
		}
	}
	if (ES_ExpressivGetSmileExtent(eState)>0.6) {
		printf("Smiling...");
		return 1;
	}
	else return 0;

}

int EyesOpen(int t, int *a, Gyro_Project_InputSignals *inputs) {
	EmoEngineEventHandle hEvent = EE_EmoEngineEventCreate();
	EmoStateHandle eState = EE_EmoStateCreate();
	unsigned int userID = -1;
	//int tempo = 0;
	//int status=0;
	int state = EE_EngineGetNextEvent(hEvent);
	// New event needs to be handled
	if (state == EDK_OK) {
		EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
		EE_EmoEngineEventGetUserId(hEvent, &userID);
		// Log the EmoState if it has been updated
		if (eventType == EE_EmoStateUpdated) {
			EE_EmoEngineEventGetEmoState(hEvent, eState);
		}
	}
	if (ES_ExpressivIsEyesOpen(eState)) {
		printf("Eyes Open...");
		return 1;
		/*if ((t - *a) >= 5)
		{
		inputs->In_Blink = 1;
		*a = 0;
		printf("looking Down ...");
		}
		else *a = t;*/
	}
	else {
		printf("Eyes close...");
		return 0;
	}
}

float upperFace(int t, Gyro_Project_InputSignals *inputs) {
	EmoEngineEventHandle hEvent = EE_EmoEngineEventCreate();
	EmoStateHandle eState = EE_EmoStateCreate();
	unsigned int userID = -1;
	//int tempo = 0;
	//int status=0;
	int state = EE_EngineGetNextEvent(hEvent);
	// New event needs to be handled
	if (state == EDK_OK) {
		EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
		EE_EmoEngineEventGetUserId(hEvent, &userID);
		// Log the EmoState if it has been updated
		if (eventType == EE_EmoStateUpdated) {
			EE_EmoEngineEventGetEmoState(hEvent, eState);
		}
	}
	return ES_ExpressivGetUpperFaceActionPower(eState);

}

float LowerFace(int t, Gyro_Project_InputSignals *inputs) {
	EmoEngineEventHandle hEvent = EE_EmoEngineEventCreate();
	EmoStateHandle eState = EE_EmoStateCreate();
	unsigned int userID = -1;
	//int tempo = 0;
	//int status=0;
	int state = EE_EngineGetNextEvent(hEvent);
	// New event needs to be handled
	if (state == EDK_OK) {
		EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
		EE_EmoEngineEventGetUserId(hEvent, &userID);
		// Log the EmoState if it has been updated
		if (eventType == EE_EmoStateUpdated) {
			EE_EmoEngineEventGetEmoState(hEvent, eState);
		}
	}
	return   ES_ExpressivGetLowerFaceActionPower(eState);
}

float eyesPositionX(int t, Gyro_Project_InputSignals *inputs) {
	EmoEngineEventHandle hEvent = EE_EmoEngineEventCreate();
	EmoStateHandle eState = EE_EmoStateCreate();
	unsigned int userID = -1;
	//int tempo = 0;
	//int status=0;
	float x = 0, y = 0;
	int state = EE_EngineGetNextEvent(hEvent);
	// New event needs to be handled
	if (state == EDK_OK) {
		EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
		EE_EmoEngineEventGetUserId(hEvent, &userID);
		// Log the EmoState if it has been updated
		if (eventType == EE_EmoStateUpdated) {
			EE_EmoEngineEventGetEmoState(hEvent, eState);
		}
	}
	ES_ExpressivGetEyeLocation(eState, &x, &y);
	return x;
}

float eyesPositionY(int t, Gyro_Project_InputSignals *inputs) {
	EmoEngineEventHandle hEvent = EE_EmoEngineEventCreate();
	EmoStateHandle eState = EE_EmoStateCreate();
	unsigned int userID = -1;
	//int tempo = 0;
	//int status=0;
	float x = 0, y = 0;
	int state = EE_EngineGetNextEvent(hEvent);
	// New event needs to be handled
	if (state == EDK_OK) {
		EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
		EE_EmoEngineEventGetUserId(hEvent, &userID);
		// Log the EmoState if it has been updated
		if (eventType == EE_EmoStateUpdated) {
			EE_EmoEngineEventGetEmoState(hEvent, eState);
		}
	}
	ES_ExpressivGetEyeLocation(eState, &x, &y);
	return y;
}

float eyeLidLeft(int t, Gyro_Project_InputSignals *inputs) {
	EmoEngineEventHandle hEvent = EE_EmoEngineEventCreate();
	EmoStateHandle eState = EE_EmoStateCreate();
	unsigned int userID = -1;
	//int tempo = 0;
	//int status=0;
	float left = 0, right = 0;
	int state = EE_EngineGetNextEvent(hEvent);
	// New event needs to be handled
	if (state == EDK_OK) {
		EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
		EE_EmoEngineEventGetUserId(hEvent, &userID);
		// Log the EmoState if it has been updated
		if (eventType == EE_EmoStateUpdated) {
			EE_EmoEngineEventGetEmoState(hEvent, eState);
		}
	}
	ES_ExpressivGetEyelidState(eState, &left, &right);
	return left;
}

float eyeLidRight(int t, Gyro_Project_InputSignals *inputs) {
	EmoEngineEventHandle hEvent = EE_EmoEngineEventCreate();
	EmoStateHandle eState = EE_EmoStateCreate();
	unsigned int userID = -1;
	//int tempo = 0;
	//int status=0;
	float left = 0, right = 0;
	int state = EE_EngineGetNextEvent(hEvent);
	// New event needs to be handled
	if (state == EDK_OK) {
		EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
		EE_EmoEngineEventGetUserId(hEvent, &userID);
		// Log the EmoState if it has been updated
		if (eventType == EE_EmoStateUpdated) {
			EE_EmoEngineEventGetEmoState(hEvent, eState);
		}
	}
	ES_ExpressivGetEyelidState(eState, &left, &right);
	return right;
}

float eyeBrow(int t, Gyro_Project_InputSignals *inputs) {
	EmoEngineEventHandle hEvent = EE_EmoEngineEventCreate();
	EmoStateHandle eState = EE_EmoStateCreate();
	unsigned int userID = -1;
	int state = EE_EngineGetNextEvent(hEvent);
	// New event needs to be handled
	if (state == EDK_OK) {
		EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
		EE_EmoEngineEventGetUserId(hEvent, &userID);
		// Log the EmoState if it has been updated
		if (eventType == EE_EmoStateUpdated) {
			EE_EmoEngineEventGetEmoState(hEvent, eState);
		}
	}

	return ES_ExpressivGetEyebrowExtent(eState);
}

void callProfile() {

	//int state = EE_EngineGetNextEvent(hEvent);
	//if (state == EDK_OK) {
	//	EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
	//	EE_EmoEngineEventGetUserId(hEvent, &userID);
	//
	//	if (eventType == EE_EmoStateUpdated) {
	//		if (EE_LoadUserProfile(userID, "test.emu") == EDK_OK) {
	//			if (EE_CognitivGetTrainedSignatureActions(userID, &activeActions) == EDK_OK) {
	//				cout << "Active actions: " << endl;
	//				if (activeActions & 0x0001) cout << " Neutral" << endl;
	//				if (activeActions & 0x0002) cout << " Push" << endl;
	//				if (activeActions & 0x0004) cout << " Pull" << endl;
	//				// .... 
	//			}
	//		}
	//	}
}


void ShowCognitivSignal() {
	int state = EE_EngineGetNextEvent(hEvent);
	/*EE_CognitivAction_t actionType = COG_NEUTRAL;
	printf("8 segundos\n");
	Sleep(8000);*/
	//printf("Start program\n");

	printf("||user: %d||", userID);
	// New event needs to be handled
	if (state == EDK_OK) {

		EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
		EE_EmoEngineEventGetUserId(hEvent, &userID);
		printf("state = %d||", state);
		// Log the EmoState if it has been updated
		printf("eventType: %d", eventType);
		if (eventType == EE_UserAdded) {
			printf("eventType == EE_UserAdded ||");
			EE_EmoEngineEventGetEmoState(hEvent, eState);
		}
		if (eventType == EE_CognitivEvent) {
			printf("STOP");
			getchar();
		}
		//if (eventType == EE_EmoStateUpdated) {
		//	if (EE_LoadUserProfile(userID, "test.emu") == EDK_OK) {
		//		if (EE_CognitivGetTrainedSignatureActions(userID, &activeActions) == EDK_OK) {
		//			cout << "Active actions: " << endl;
		//			if (activeActions & 0x0001) cout << " Neutral" << endl;
		//			if (activeActions & 0x0002) cout << " Push" << endl;
		//			if (activeActions & 0x0004) cout << " Pull" << endl;
		//			// .... 
		//		}
		//	}
		//}
		if (eventType == EE_EmoStateUpdated) {
			printf("eventType == EE_EmoStateUpdated ||");
			EE_EmoEngineEventGetEmoState(hEvent, eState);

			//eu acho que e aqui que se fazem as coisas
			printf("||power {0 - 1}: %f ||", ES_CognitivGetCurrentActionPower(eState));
			printf("||Type: %d||", ES_CognitivGetCurrentAction(eState));

			if (ES_CognitivGetCurrentAction(eState) != 1)
			{
				printf("\ndiferente action type\n");
				getchar();

			}
		}
	}


	//EmoState es = e.emoState;
	EE_CognitivAction_t currentAction = ES_CognitivGetCurrentAction(eState);
	float power = ES_CognitivGetCurrentActionPower(eState);


	printf("||state = %d||", state);
	printf("||teste Cognitivo||");
	printf("||power {0 - 1}: %f ||", power);
	printf("||Type: %d||", ES_CognitivGetCurrentAction(eState));
	printf("\n");
	if (ES_CognitivGetCurrentAction(eState) != 1)
	{
		printf("\ndiferente action type\n");
		getchar();

	}
	if (ES_CognitivGetCurrentActionPower(eState) != 0)
	{
		printf("\ndiferente action power\n");
		getchar();

	}
	/*if (currentAction.tostring().equals("cog_neutral"))
	{
	printf("Teste 1 ;");
	}*/

	//if (currentaction.tostring().equals("cog_push"))
	//{
	//	console.writeline("current action is cog_push");
	//}


	Sleep(10);
}

float frustrationLevel() {

	int state = EE_EngineGetNextEvent(hEvent);
	// New event needs to be handled
	if (state == EDK_OK) {
		EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
		EE_EmoEngineEventGetUserId(hEvent, &userID);
		// Log the EmoState if it has been updated
		if (eventType == EE_EmoStateUpdated) {
			EE_EmoEngineEventGetEmoState(hEvent, eState);
		}
	}
	printf("user : %d||\n", userID);
	return ES_AffectivGetFrustrationScore(eState);
}

float meditationLevel() {
	int state = EE_EngineGetNextEvent(hEvent);
	// New event needs to be handled
	if (state == EDK_OK) {
		EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
		EE_EmoEngineEventGetUserId(hEvent, &userID);
		// Log the EmoState if it has been updated
		if (eventType == EE_EmoStateUpdated) {
			EE_EmoEngineEventGetEmoState(hEvent, eState);
		}
	}
	printf("user : %d\n||", userID);
	return ES_AffectivGetMeditationScore(eState);
}

void Q_Expressive_Smile() {

	int state = EE_EngineGetNextEvent(hEvent);
	// New event needs to be handled
	if (state == EDK_OK) {
		EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
		EE_EmoEngineEventGetUserId(hEvent, &userID);
		// Log the EmoState if it has been updated
		if (eventType == EE_EmoStateUpdated) {
			EE_EmoEngineEventGetEmoState(hEvent, eState);
		}
	}
	printf("||user: %d||", userID);
	if (ES_ExpressivIsActive(eState, EXP_SMILE))
	{
		printf("||Smile: Active\n");
	}
	else
	{
		printf("||Smile: Not Active\n");
	}

}

void Q_Expressive_Blink() {
	while (true)
	{
		int state = EE_EngineGetNextEvent(hEvent);
		// New event needs to be handled
		if (state == EDK_OK) {
			EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
			EE_EmoEngineEventGetUserId(hEvent, &userID);
			// Log the EmoState if it has been updated
			if (eventType == EE_EmoStateUpdated) {
				EE_EmoEngineEventGetEmoState(hEvent, eState);
			}
		}
		printf("||user: %d||", userID);
		if (ES_ExpressivIsActive(eState, EXP_BLINK))
		{
			printf("||Blink: Active\n");
		}
		else
		{
			printf("||Blink: Not Active\n");
		}
	}
}

void Q_Expressive_Wink_Left() {

	int state = EE_EngineGetNextEvent(hEvent);
	// New event needs to be handled
	if (state == EDK_OK) {
		EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
		EE_EmoEngineEventGetUserId(hEvent, &userID);
		// Log the EmoState if it has been updated
		if (eventType == EE_EmoStateUpdated) {
			EE_EmoEngineEventGetEmoState(hEvent, eState);
		}
	}
	printf("||user: %d||", userID);
	if (ES_ExpressivIsActive(eState, EXP_WINK_LEFT))
	{
		printf("Active\n");
	}
	else
	{
		printf("Not Active\n");
	}

}

void Q_Expressive_Wink_Right() {
	while (true)
	{

		int state = EE_EngineGetNextEvent(hEvent);
		// New event needs to be handled
		if (state == EDK_OK) {
			EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
			EE_EmoEngineEventGetUserId(hEvent, &userID);
			// Log the EmoState if it has been updated
			if (eventType == EE_EmoStateUpdated) {
				EE_EmoEngineEventGetEmoState(hEvent, eState);
			}
		}
		printf("||user: %d||", userID);
		if (ES_ExpressivIsActive(eState, EXP_WINK_RIGHT))
		{
			printf("||Wink right: Active\n");
		}
		else
		{
			printf("||Wink right: Not Active\n");
		}
	}
}

void Effective_Excitement() {
	while (true) {

		int state = EE_EngineGetNextEvent(hEvent);
		// New event needs to be handled
		if (state == EDK_OK) {
			EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
			EE_EmoEngineEventGetUserId(hEvent, &userID);
			// Log the EmoState if it has been updated
			if (eventType == EE_EmoStateUpdated) {
				EE_EmoEngineEventGetEmoState(hEvent, eState);
			}
		}
		printf("||user: %d||", userID);

		printf("||Score: %f", ES_AffectivGetExcitementShortTermScore(eState));
		if (ES_AffectivIsActive(eState, AFF_EXCITEMENT))
		{
			printf("||excitement: Active\n");
		}
		else
		{
			printf("||excitement: Not Active\n");
		}
	}
}

void Effective_meditation() {
	while (true)
	{
		int state = EE_EngineGetNextEvent(hEvent);
		// New event needs to be handled
		if (state == EDK_OK) {
			EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
			EE_EmoEngineEventGetUserId(hEvent, &userID);
			// Log the EmoState if it has been updated
			if (eventType == EE_EmoStateUpdated) {
				EE_EmoEngineEventGetEmoState(hEvent, eState);
			}
		}
		printf("||user: %d||", userID);
		if (ES_AffectivIsActive(eState, AFF_MEDITATION))
		{
			printf("||Meditation: Active\n");
		}
		else
		{
			printf("||Meditation: Not Active\n");
		}
	}
}

void Effective_Frustration() {
	while (true)
	{
		int state = EE_EngineGetNextEvent(hEvent);
		// New event needs to be handled
		if (state == EDK_OK) {
			EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
			EE_EmoEngineEventGetUserId(hEvent, &userID);
			// Log the EmoState if it has been updated
			if (eventType == EE_EmoStateUpdated) {
				EE_EmoEngineEventGetEmoState(hEvent, eState);
			}
		}
		printf("||user: %d||", userID);
		if (ES_AffectivIsActive(eState, AFF_FRUSTRATION))
		{
			printf("||Frustration: Active\n");
		}
		else
		{
			printf("||Frustration: Not Active\n");
		}
	}
}

void getBattery() {
	
		int chargeLevel = 0, MaxChargeLevel = 0;
		int state = EE_EngineGetNextEvent(hEvent);
		EE_EmoEngineEventGetEmoState(hEvent, eState);			
		ES_GetBatteryChargeLevel(eState, &chargeLevel, &MaxChargeLevel);		
		printf("Charge LEVEL: %d || MAX CHARGE LEVEL: %d||\n", chargeLevel, MaxChargeLevel);
	
}

void NumContactQuality() {
	int state = EE_EngineGetNextEvent(hEvent);
	if (state == EDK_OK) {
		EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
		EE_EmoEngineEventGetUserId(hEvent, &userID);
		// Log the EmoState if it has been updated
		if (eventType == EE_EmoStateUpdated) {
			EE_EmoEngineEventGetEmoState(hEvent, eState);
		}
	}
	printf("Numero de canais operacionais: %d", ES_GetNumContactQualityChannels(eState));

}

void TimeFromStart() {
	int state = EE_EngineGetNextEvent(hEvent);
	if (state == EDK_OK) {
		EE_Event_t eventType = EE_EmoEngineEventGetType(hEvent);
		EE_EmoEngineEventGetUserId(hEvent, &userID);
		// Log the EmoState if it has been updated
		if (eventType == EE_EmoStateUpdated) {
			EE_EmoEngineEventGetEmoState(hEvent, eState);
		}
	}
	printf("Tempo decorrido: %f", ES_GetTimeFromStart(eState));

}

void WirelessSignal() {
	int state = EE_EngineGetNextEvent(hEvent);
	EE_EmoEngineEventGetEmoState(hEvent, eState);
	EE_SignalStrength_enum Signal = ES_GetWirelessSignalStatus(eState);

	if (Signal == NO_SIGNAL)
	{
		printf("Sem Sinal...\nPor favor verifique a PEN de Comunicação com o capacete...");
	}
	else
	{
		if (Signal == BAD_SIGNAL)
		{
			printf("Sinal muito fraco...\nPor favor verifique a distancia à PEN de Comunicação com o capacete...");
		}
		else
		{
			if (Signal == GOOD_SIGNAL)
			{
				printf("Bom sinal...");
			}
			else
			{
				printf("Error getting battery level.");
			}
		}
	}
}

void CapaceteOn() {

	while (ES_GetHeadsetOn(eState) <= 0)
	{
		//shutdown();
		EE_EngineGetNextEvent(hEvent);
		EE_EmoEngineEventGetEmoState(hEvent, eState);
		system("CLS"); // clean screenprintf
		printf("Ligue o Capacete...\n");
		Sleep(500);
	}
}

//void Control(int operacao,int time, Gyro_Project_InputSignals *inputs, int *var_bt,int *var_ll,int *var_lr, int *var_lu, int*var_ld, int *var_eo) {
//	switch (operacao)
//	{
//	case 1:
//		// activar o gyroscopio e o modo blink
//		updateXY(inputs);
//		printf("||modo blink||");
//		inputs->In_Blink = Blink();
//		break;
//	case 2:
//		updateXY(inputs);
//		printf("||modo blink twice||");
//		inputs->In_Blink = BlinkTwice(time, var_bt, inputs);
//		break;
//	case 3:
//		updateXY(inputs);
//		printf("||modo wink left||");
//		inputs->In_Blink = 	Winkleft(time, inputs);
//		break;
//	case 4:
//		updateXY(inputs);
//		printf("||modo wink right||");
//		inputs->In_Blink = Winkright(time, inputs);
//		break;
//	case 5:
//		updateXY(inputs);
//		printf("||modo look left||");
//		inputs->In_Blink = lookLeft(time, var_ll, inputs);
//		break;
//	case 6:
//		updateXY(inputs);
//		printf("||modo look right||");
//		inputs->In_Blink = lookRight(time, var_lr, inputs);
//		break;
//	case 7:
//		updateXY(inputs);
//		printf("||modo look up||");
//		inputs->In_Blink = lookUp(time, var_lu, inputs);
//		break;
//	case 8:
//		updateXY(inputs);
//		printf("||modo look down||");
//		inputs->In_Blink = lookDown(time, var_ld, inputs);
//		break;
//	case 9:
//		updateXY(inputs);
//		printf("||modo eyes open||");
//		EyesOpen(time, var_eo, inputs);
//		break;
//	case 10:
//		// activar o gyroscopio e ler os valores do smile
//		updateXY(inputs);
//		printf("||modo Smile||");
//		printf("%f", Smile(time, inputs));
//		if (Smile(time, inputs))
//		{
//			inputs->In_Blink = 1;
//		}
//		break;
//	case 11:
//		updateXY(inputs);
//		printf("||modo UpperFace||");
//		printf("%f",upperFace(time, inputs));
//		break;
//	case 12:
//		updateXY(inputs);
//		printf("||modo LowerFace||");
//		printf("%f", LowerFace(time, inputs));
//		break;
//	case 13:
//		updateXY(inputs);
//		printf("||modo horizontal eyes position||");
//		printf("%f", eyesPositionX(time, inputs));
//		break;
//	case 14:
//		updateXY(inputs);
//		printf("||modo vertical eyes position||");
//		printf("%f", eyesPositionY(time, inputs));
//		break;
//	case 15:
//		updateXY(inputs);
//		printf("||modo pestana olho esquerdo||");
//		printf("%f", eyeLidLeft(time, inputs));
//		break;
//	case 16:
//		updateXY(inputs);
//		printf("||modo pestana olho direito||");
//		printf("%f", eyeLidRight(time, inputs));
//		break;
//	case 17:
//		updateXY(inputs);
//		printf("||modo sobrancelhas||");
//		printf("%f", eyeBrow(time, inputs));
//		break;
//	case 18:
//		//updateXY(inputs);
//		printf("||modo cognitivo||");
//		//CognitiveTeste();		
//		break;
//	case 19:
//		updateXY(inputs);
//		printf("||modo frustação||");
//		printf("%f", frustrationLevel());
//		break;
//	case 20:
//		updateXY(inputs);
//		printf("||modo meditação||");
//		printf("%f", meditationLevel());
//		break;
//	default: 
//		printf("||Modo XY||");
//		updateXY(inputs);
//		break;
//	}
//}

void stopEpoc() {
	if (EE_SaveUserProfile(0, "test.emu") == EDK_OK) {
		printf("\nsaveuserprofile Donne\n");
		getchar();
	}
	EE_EmoEngineEventFree(eProfile);
	EE_EngineDisconnect();
	EE_EmoStateFree(eState);
	EE_EmoEngineEventFree(hEvent);
	Sleep(6000);
}

void StateSystem() {
	int num = 0;
	do
	{
		printf("\n\nEstado do Sistema:\n1-Qualidade do sinal blink\n2-Qualidade do sinal Smile\n3-Qualidade do sinal Wink left\n4-Qualidade do sinal wink right\n5-Nivel de Bateria\n6-numero de sensores EEG a funcionar\n7-Tempo decorrido\n8-Potencia do sinal de wireless\n9-Posiçao do capacete\n10-The signal is too noisy for Cognitiv detection to be active\n11- detected Cognitiv action power of the user\n12- Qualidade do sinal de excitamento\n13- Qualidade do sinal de meditação\n14- Qualidade do sinal de frustração\n(Space enter to jump configurations...)\n\n");
		std::cin >> num;
		switch (num)
		{
		case 1:
			// qualidade do sinal para reconhecer a expressão facial Blink
			Q_Expressive_Blink();
			break;
		case 2:
			// qualidade do sinal para reconhecer a expressão facial Smile
			Q_Expressive_Smile();
			break;
		case 3:
			// qualidade do sinal para reconhecer a expressão wink left
			Q_Expressive_Wink_Left();
			break;
		case 4:
			// qualidade do sinal para reconhecer a expressão wink right
			Q_Expressive_Wink_Right();
			break;
		case 5:
			// nivel de bateria
			getBattery();
			break;
		case 6:
			//numero de canais operacionais
			NumContactQuality();
			break;
		case 7:
			//tempo decorrido
			TimeFromStart();
			break;
		case 8:
			//potencia do sinal wireless
			WirelessSignal();
			break;
		case 9:
			CapaceteOn();
			break;
		case 10:
			printf("Signal Cognitiv detection: %d", ES_CognitivIsActive(eState));
			break;
		case 11:
			printf("Cognitiv action power (0.0 to 1.0): %f", ES_CognitivGetCurrentActionPower(eState));
			break;
		case 12:
			// qualidade do sinal para reconhecer a emocão excitação
			Effective_Excitement();
			break;
		case 13:
			// qualidade do sinal para reconhecer a emocão de meditacao
			Effective_meditation();
			break;
		case 14:
			// qualidade do sinal para reconhecer a emocão de frustração
			Effective_Frustration();
			break;
		default:
			break;
		}
	} while (num);
}

