#include <audio/AudioSource.h>

#include <AL/al.h>

cAudioSource::cAudioSource(cMesh* pMesh, cCollider* pCollider, bool bStatic, float fPitch, float fGain)
        : cBaseObject(pMesh, pCollider, bStatic), pfPitch(fPitch), pfGain(fGain)
{
    puiSourceId = UINT_MAX;

    // create the source
    alGenSources(1, &puiSourceId);
}

cAudioSource::~cAudioSource()
{
    if (puiSourceId != UINT_MAX)
    {
        alDeleteSources(1, &puiSourceId);
    }
}

void cAudioSource::Load(cAudioSample* pSample, bool bLooping)
{
    // set source parameters
    alSourcei(puiSourceId, AL_LOOPING, bLooping);
    alSource3f(puiSourceId, AL_VELOCITY, 0, 0, 0); // we currently don't support velocity
    Update();

    // set source buffer
    alSourcei(puiSourceId, AL_BUFFER, (ALint) pSample->puiBufferId);
}

void cAudioSource::Play() const
{
    alSourcePlay(puiSourceId);
}

void cAudioSource::Pause() const
{
    alSourcePause(puiSourceId);
}

void cAudioSource::Stop() const
{
    alSourceStop(puiSourceId);
}

void cAudioSource::Update()
{
    alSourcef(puiSourceId, AL_PITCH, pfPitch);
    alSourcef(puiSourceId, AL_GAIN, pfGain);
    alSource3f(puiSourceId, AL_POSITION, poPosition.x, poPosition.y, poPosition.z);
}
