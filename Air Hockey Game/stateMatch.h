
/*
    Arturo Cepeda P�rez

    AirHockey3d - Using the Air Hockey Game Library

    --- stateMatch.h ---
*/

#pragma once

#include "AH.h"
#include "AHAI.h"
#include "main.h"
#include "States/GEState.h"
#include "Multiplayer/GEMultiplayer.h"
#include "kinect.h"

#define SOUNDS_PUCK     10
#define SOUNDS_TABLE    10
#define SOUNDS_GOAL     6

#define AUDIO_RATIO     4.0f
#define AUDIO_UPDATE    4

#define SQSPEED_VERYSLOW    100.0f
#define SQSPEED_SLOW        500.0f

#define SLEEP_FRAMES    80

#define MULTIPLAYER_DATA_RATE   1

#define MSG_SIZE        16
#define MSG_REQ         1
#define MSG_ACK         2
#define MSG_TIME        3
#define MSG_EVENT       4
#define MSG_GOAL        5
#define MSG_MALLET      6
#define MSG_PUCK        7
#define MSG_END         8

#define REPLAY_CAMERAS      2
#define REPLAY_FRAMES       80
#define REPLAY_INTERPOL     3

union UFloatValue
{
    char CharValue[4];
    float FloatValue;
};

struct SReplayFrame
{
    AHPoint PositionPlayer1;
    AHPoint PositionPlayer2;
    AHPoint PositionPuck;
    bool PuckVisible;
    bool Interpolate;
};

class CStateMatch : public GE::States::State
{
private:
    // global data
    SGlobal* sGlobal;

    // game objects
    AHGame* cGame;
    AHAI* cPlayer1AI;
    AHAI* cPlayer2AI;

    // positions
    AHPoint pPlayer1Position;
    AHPoint pPlayer2Position;
    AHPoint pPuckPosition;

    // HUD positions
    float fPosX;
    float fPosY;

    // time
    int iTimeMin;
    int iTimeSec;

    // frame counter
    unsigned int iCurrentFrame;

    // sleep and restart
    unsigned int iSleepFrame;
    bool bPlayAgain;

    // multiplayer
    GE::Multiplayer::Server* cServer;
    GE::Multiplayer::Client* cClient;
    GE::Multiplayer::SRemoteAddress sClientAddress;
    char sUDPBuffer[MSG_SIZE];
    bool bClientReady;
    bool bServerReady;

    // kinect
    HANDLE hKinectThread;
    KinectHandPosition kHandPosition;
    KinectCalibration kCalibration;

    // replays
    bool bReplayMode;
    int iReplayFrame;
    int iCurrentReplayRecordFrame;
    int iCurrentReplayPlayFrame;
    int iCurrentReplayPlayFramePoint;
    SReplayFrame sReplayFrame[REPLAY_FRAMES];

    // lights
    unsigned int iLightRoom;

    // cameras
    GE::Rendering::Camera* mCameraPlayer1;
    GE::Rendering::Camera* mCameraPlayer2;
    GE::Rendering::Camera* mCameraReplay[REPLAY_CAMERAS];
        
    // meshes
    GE::Rendering::Mesh* mMeshMallet1;
    GE::Rendering::Mesh* mMeshMallet2;
    GE::Rendering::Mesh* mMeshPuck;
    GE::Rendering::Mesh* mMeshTable;
    GE::Rendering::Mesh* mMeshRoom;
    bool bPuckVisible;

    // sprites
    GE::Rendering::Sprite* sDisplay[10];
    GE::Rendering::Sprite* sDisplaySeparator;
    GE::Rendering::Sprite* sFrame;

    // fonts
    unsigned int iFontText;
    unsigned int iFontDebug;

    // labels
    GE::Rendering::Label* lLabelMessage;
    GE::Rendering::Label* lLabelDebug;

    // view ports (split)
    unsigned int iPortFullScreen;
    unsigned int iPortPlayer1;
    unsigned int iPortPlayer2;
    unsigned int iPortMessages;
    unsigned int iPortSpaceBelow;

    // text buffers
    char sMessage[256];
    char sBuffer[256];
    static char sKinectInfo[512];

    // colors
    GE::Color cColorMessage;
    GE::Color cColorDebug;

    // sound handlers
    unsigned int iChannelMallet1;
    unsigned int iChannelMallet2;
    unsigned int iChannelPuck;

    unsigned int iSoundPuckMallet[SOUNDS_PUCK];
    unsigned int iSoundPuckTable[SOUNDS_TABLE];
    unsigned int iSoundGoal[SOUNDS_GOAL];

    // sound aux data
    float fImpactSquareSpeed;
    int iSoundPlay;

    // rendering
    void initRenderObjects();
    void releaseRenderObjects();

    // sound
    void initSoundObjects();
    void releaseSoundObjects();
    void playSounds(int iEvent);

    // multiplayer
    void sendDataToClient();
    void updateClient();

    // replay
    void replayMode();
    void renderReplay();

    // match finished
    void playAgain();
    void endOfTheMatch();

public:
    CStateMatch(GE::Rendering::RenderSystem* Render, GE::Audio::AudioSystem* Audio, void* GlobalData);
    ~CStateMatch();

    void internalInit();
    void update(float DeltaTime);
    void render();
    void release();

    void inputKeyPress(char Key);
};
