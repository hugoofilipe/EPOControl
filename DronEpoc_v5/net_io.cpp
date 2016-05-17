/* Net Gyro_Project - IOPT */
/* Automatic code generated by IOPT2C XSLT transformation. */
/* Please fill the necessary code to perform hardware IO. */

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

#ifdef ARDUINO
#include <Arduino.h>
#define ANALOG_IN_MAX  1023
#define ANALOG_OUT_MAX 255
#else
#define INPUT    0
#define OUTPUT   1
#define ANALOG_IN_MAX  1023
#define ANALOG_OUT_MAX 1023
extern void pinMode( int, int );
extern int  digitalRead( int );
extern void digitalWrite( int, int );
extern int  analogRead( int );
extern void analogWrite( int, int );
#endif


// Remote IcE/Debug forced values:
#ifdef HTTP_SERVER
iopt_param_info *input_fv = NULL, *output_fv = NULL;
#endif


/* Executed just once, before net execution starts: */
void Gyro_Project_InitializeIO()
{
	InitEpoc();
	initSocket();
}



/* Read all hardware input signals and fill data-structure */
void Gyro_Project_GetInputSignals(
            Gyro_Project_InputSignals* inputs,
            Gyro_Project_InputSignalEvents* events )
{
	interrupt();
	newAction();

    inputs->In_Y = UpdateY();
    inputs->In_X = UpdateX();
    inputs->In_Signal1 = lookLeft();
    inputs->In_Signal2 = lookRight();
    inputs->In_Signal3 = Winkright();
    inputs->In_Signal4 = LIFT;
    inputs->In_Signal5 = DROP;
    inputs->In_Signal6 = Winkleft();
    inputs->In_Signal7 = Blink();
#ifdef HTTP_SERVER
    if( input_fv != NULL ) force_Gyro_Project_Inputs( input_fv, inputs );
#endif
}


/* Write all output values to physical hardware outputs */
void Gyro_Project_PutOutputSignals(
            Gyro_Project_PlaceOutputSignals* place_out,
            Gyro_Project_EventOutputSignals* event_out,
            Gyro_Project_OutputSignalEvents* events )
{
#ifdef HTTP_SERVER
    if( output_fv != NULL )
        force_Gyro_Project_Outputs( output_fv, place_out, event_out );
#endif
    /* place_out->Out_TakeOffLand */
    /* place_out->Out_Foward */
    /* place_out->Out_Backward */
    /* place_out->Out_Left */
    /* place_out->Out_Right */
    /* place_out->Out_Up */
    /* place_out->Out_Down */
    /* place_out->Out_RotateLeft */
    /* place_out->Out_RotateRight */
    /* place_out->Out_TakePhoto */
	printf("\nT/L: %d|Up: %d|Down: %d|Left: %d|Right: %d|Rot.L: %d|Rot.R: %d|Foward: %d|Back: %d|Photo: %d|", place_out->Out_TakeOffLand, place_out->Out_Up, place_out->Out_Down, place_out->Out_Left, place_out->Out_Right, place_out->Out_RotateLeft, place_out->Out_RotateRight, place_out->Out_Foward, place_out->Out_Backward, place_out->Out_TakePhoto);

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
}


/* Delay between loop iterations to save CPU and power consumption */
void Gyro_Project_LoopDelay()
{
	Sleep(15);
}

/* Must return 1 to finish net execution */
int Gyro_Project_FinishExecution( Gyro_Project_NetMarking* marking )
{
    return shutdown();
}


