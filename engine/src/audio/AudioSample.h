#pragma once

#include <pch.h>

class cAudioSample
{
public:
    uint puiBufferId;

    static cAudioSample* FromFile(const string& sFileName);

    ~cAudioSample();

private:
    cAudioSample(uint uiBufferId);
};
