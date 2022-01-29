#ifndef JOYMAP_H
#define JOYMAP_H


namespace JoyMap
{
    
    
    //Start semi Autonomy
    static const int SemiAutonomyToggle = 0; // A

    // Motor Toggle Function
    //static const int AugerToggle = 3; // Y
    static const int AugerToggleUp = 5;
    static const int AugerToggleDown = 4;
    static const int LinActToggle = 0; // A

    // Left/Right Drive
    static const int LeftDrive = 1; // Up/Down Axis stick left
    static const int RightDrive = 4; // Up/Down Axis stick right


    // DumperMotor
    static const int CW = 0; // A
    static const int CCW = 1; // B
    

    //Auger Position Adjust - Axes
    static const int LeftTrigger = 2; // Auger Down
    static const int RightTrigger = 5; // Auger Up

    //Servo Toggle
    static const int Servo = 6; // Back
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
    8       power/Xbox button
    9       Button stick left
    10      Button stick right

    joy.axes:
    Index   Axis
    0       Left/Right Axis stick left
    1       Up/Down Axis stick left
    2       LT
    3       Left/Right Axis stick right
    4       Up/Down Axis stick right
    5       RT
    6       cross key left/right
    7       cross key up/down 
****************************************/