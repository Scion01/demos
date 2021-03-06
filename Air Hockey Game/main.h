
/*
    Arturo Cepeda P�rez

    AirHockey3d - Using the Air Hockey Game Library

    --- main.h ---
*/

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "AHAI.h"

//#define _KINECT_            // defined: use Kinect sensor, undefined: don't use Kinect sensor
//#define _KINECT_OPENNI_     // defined: OpenNI, undefined: Kinect SDK

#define STATE_MENU      1
#define STATE_MATCH     2

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void StateChange(unsigned int iNewState);
void DefaultSettings();

struct SGlobal
{
    // window values
    HWND hWnd;
    int ScreenSizeX;
    int ScreenSizeY;

    // game loop
    int iFPS;

    // interface
    int iHumanPlayers;
    bool bSplit;
    bool bKinect;

    // settings
    int iGameMaxMinutes;
    int iGameMaxGoals;
    bool bTableAir;
    AHAILevel cPlayer2AILevel;
    bool bAutomaticReplay;

    // multiplayer
    bool bMultiplayer;
    bool bServer;
    char sIPServer[16];
    unsigned int iPort;

    // Kinect calibration
    float fKinectWidth;
    float fKinectMinimumDistance;
    float fKinectMaximumDistance;
    bool bPlayer1RightHanded;
    bool bPlayer2RightHanded;
};
