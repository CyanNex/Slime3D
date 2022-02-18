#pragma once

#include <scene/object/BaseObject.h>
#include <audio/AudioSample.h>

class cAudioSource : public cBaseObject
{
public:
    float pfPitch;
    float pfGain;

    cAudioSource(cMesh* pMesh, cCollider* pCollider, bool bStatic,
                 float fPitch = 1.0f, float fGain = 1.0f);
    ~cAudioSource();

    void Load(cAudioSample* pSample, bool bLooping = false);

    void Play() const;
    void Pause() const;
    void Stop() const;

    void Update();

private:
    uint puiSourceId;
};
