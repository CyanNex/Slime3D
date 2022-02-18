#include <audio/AudioSample.h>

#include <AL/al.h>
#include <AL/alut.h>

cAudioSample* cAudioSample::FromFile(const string& sFileName)
{
    uint uiBufferId = alutCreateBufferFromFile(sFileName.c_str());
    return new cAudioSample(uiBufferId);
}

cAudioSample::cAudioSample(uint uiBufferId)
        : puiBufferId(uiBufferId)
{
}

cAudioSample::~cAudioSample()
{
    if (puiBufferId > 0)
    {
        alDeleteBuffers(1, &puiBufferId);
    }
}
