#pragma once

#include <AL/alc.h>

#include <scene/Scene.h>

class cAudioHandler
{
private:
    ALCdevice* pptAudioDevice = nullptr;
    ALCcontext* pptOpenALContext = nullptr;

    cScene* ppScene = nullptr;

public:
    cAudioHandler();
    ~cAudioHandler();

    void SetScene(cScene* pScene);

    void Update();

private:
    void CreateContext();

    static void CheckAndReportErrors();
};
