
/*
    Arturo Cepeda P�rez

    AirHockey3d - Using the Air Hockey Game Library

    --- stateMenu.h ---
*/

#pragma once

#include "main.h"
#include "States/GEState.h"

#define MAX_OPTIONS     8

#define MENU_MAIN                   1
#define MENU_PLAY                   2
#define MENU_SETTINGS               3
#define MENU_MULTIPLAYER            4
#define MENU_MULTIPLAYER_SERVER     5
#define MENU_MULTIPLAYER_CLIENT     6
#define MENU_SETTINGS_DIFFICULTY    7
#define MENU_SETTINGS_KINECT        8
#define MENU_KINECT_INFO            9

#define GAME_MAX_GOALS      30
#define GAME_MAX_MINUTES    15

#define AI_SHOOTING_MAX     AH_PUCK_MAXSPEED
#define AI_SHOOTING_MIN     100.0f
#define AI_DEFENDING_MAX    30.0f
#define AI_DEFENDING_MIN    5.0f
#define AI_CLEARING_MAX     AH_PUCK_MAXSPEED
#define AI_CLEARING_MIN     60.0f
#define AI_ATTACK_MAX       120.0f
#define AI_ATTACK_MIN       40.0f

#define KINECT_WIDTH_MIN    500.0f
#define KINECT_WIDTH_MAX    1000.0f
#define KINECT_MINDIST_MIN  1000.0f
#define KINECT_MINDIST_MAX  3000.0f
#define KINECT_MAXDIST_MIN  1500.0f
#define KINECT_MAXDIST_MAX  4000.0f

class CStateMenu : public GE::States::State
{
private:
    GE::Rendering::RenderSystem* cRender;
    GE::Audio::AudioSystem* cAudio;

    // global data
    SGlobal* sGlobal;

    // options
    char sOptionText[64];
    int iNumOptions;
    int iSelectedOption;
    int iCurrentMenu;

    // aux settings
    char sPort[8];
    int iPercentShooting;
    int iPercentDefending;
    int iPercentClearing;
    int iPercentAttack;

    // kinect info text
    static char sKinectInfo[];

    // camera
    GE::Rendering::Camera* cCamera;
    float fCameraOrbitTheta;

    // meshes (background)
    GE::Rendering::Mesh* mMeshMallet1;
    GE::Rendering::Mesh* mMeshMallet2;
    GE::Rendering::Mesh* mMeshTable;
    GE::Rendering::Mesh* mMeshRoom;

    // color
    GE::Color cColorOption;
    GE::Color cColorSelected;
    bool bColorSelectedInc;

    // fonts
    unsigned int iFontOption;
    unsigned int iFontSelected;
    unsigned int iFontText;

    // labels
    GE::Rendering::Label* lLabelOption[MAX_OPTIONS];
    GE::Rendering::Label* lLabelKinectInfo;

    void playSounds();

    void initRenderObjects();
    void releaseRenderObjects();

    void initSoundObjects();
    void releaseSoundObjects();

    void enterMenu(int iMenu);
    void selectOption(int iOption);

    void refreshSettings();
    void calculateDifficultyPercentages();
    void calculateDifficultyValues();

public:
    CStateMenu(GE::Rendering::RenderSystem* Render, GE::Audio::AudioSystem* Audio, void* GlobalData);
    ~CStateMenu();

    void internalInit();
    void update(float DeltaTime);
    void render();
    void release();

    void inputKeyPress(char Key);
};
