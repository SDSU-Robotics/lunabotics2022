#ifndef JOYMAP_H
#define JOYMAP_H

namespace JoyMap
{
    //TPort - axes
	static const int TPortForwardAxis = 1; // up/down stick left
	static const int TPortTurnAxis = 4; // RT

    //Excv - axes
    static const int ExcvLeftAxis = 1; // up/down stick left
	static const int ExcvRightAxis = 4;	// RT
    static const int ExcvTrencherUp = 5; // LT
    static const int ExcvTrencherDown = 2; // left/right stick right

    //TPort - buttons
    static const int TPortConveyorToggle = 0; // A
    static const int TPortToggleExtension = 7; // start

    //Excv - buttons
    static const int ExcvConveyorToggle = 0; // A
    static const int ExcvTrencherToggle = 1; // B
    static const int ExcvTrencherDriveToggle = 2; // X
    static const int ExcvTrencherDriveDecrease = 4; // LB
    static const int ExcvTrencherDriveIncrease = 5; // RB
    static const int ExcvTrencherExtend = 7; // start

    //Start semi Autonomy
    static const int SemiAutonomyToggle = 0;

    // Motor Toggle Function
    static const int MotorToggle = 3; // Y
};

#endif
/***************************************
    joy.buttons:
    Index   Button
    0       A
    1       B
    2       X
    3       Y
    4       LB
    5       RB
    6       back
    7       start
    8       power
    9       Button stick left
    10      Button stick right

    joy.axes:
    Index   Axis
    0       Left/Right Axis stick left
    1       Up/Down Axis stick left
    2       Left/Right Axis stick right
    3       Up/Down Axis stick right
    4       RT
    5       LT
    6       cross key left/right
    7       cross key up/down 
****************************************/