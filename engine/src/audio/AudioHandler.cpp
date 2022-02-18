#include <pch.h>

#include <AL/alut.h>

#include <audio/AudioHandler.h>
#include <audio/AudioSource.h>

cAudioHandler::cAudioHandler()
{
    CreateContext();
    CheckAndReportErrors();

    int argc = 1;
    char* argv[0];
    alutInitWithoutContext(&argc, argv);
    CheckAndReportErrors();
}

cAudioHandler::~cAudioHandler()
{
    // if we have a context, destroy it
    if (pptOpenALContext)
    {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(pptOpenALContext);
    }

    // if we have an open device, close it
    if (pptAudioDevice)
    {
        alcCloseDevice(pptAudioDevice);
    }
}

void cAudioHandler::CreateContext()
{
    // we cannot create the context if it's already been created
    assert(!pptOpenALContext);
    assert(!pptAudioDevice);

    // get the specifier for the default audio device
    const char* pcDeviceSpecifier = alcGetString(nullptr, ALC_DEVICE_SPECIFIER);

    // open the audio device
    pptAudioDevice = alcOpenDevice(pcDeviceSpecifier);
    if (!pptAudioDevice) throw std::runtime_error("cannot open audio device");
    ENGINE_LOG("Using audio device '" << pcDeviceSpecifier << "'");

    // create a new context for the device and make it the current context
    pptOpenALContext = alcCreateContext(pptAudioDevice, nullptr);
    if (!alcMakeContextCurrent(pptOpenALContext))
    {
        throw std::runtime_error("failed to make the alc context current");
    }
}

void cAudioHandler::SetScene(cScene* pScene)
{
    ppScene = pScene;
}

void cAudioHandler::Update()
{
    if (ppScene)
    {
        // get the camera properties
        cCamera& pCamera = ppScene->GetCamera();
        glm::vec3 tCameraPos = pCamera.cameraPos;
        glm::vec3 tCameraDirection = pCamera.direction;
        ALfloat afCameraOrientation[] = {
                tCameraDirection.x, tCameraDirection.y, tCameraDirection.z,
                0.0f, 1.0f, 0.0f // UP vector
        };

        // set the listener to be the camera
        alListener3f(AL_POSITION, tCameraPos.x, tCameraPos.y, tCameraPos.z);
        alListenerfv(AL_ORIENTATION, afCameraOrientation);
        alListener3f(AL_VELOCITY, 0, 0, 0);

        // update any audio sources in the scene
        for (const auto& oObject : ppScene->GetObjects())
        {
            auto* pSource = dynamic_cast<cAudioSource*>(oObject.second);
            if (pSource)
            {
                pSource->Update();
            }
        }
    }
}

void cAudioHandler::CheckAndReportErrors()
{
    ALenum eError;

    eError = alGetError();
    if (eError != AL_NO_ERROR)
    {
        ENGINE_ERROR("OpenAL error: " << eError);
        exit(EXIT_FAILURE);
    }

    eError = alutGetError();
    if (eError != ALUT_ERROR_NO_ERROR)
    {
        const char* pcErrorString = alutGetErrorString(eError);
        ENGINE_ERROR("ALUT error: " << pcErrorString);
        exit(EXIT_FAILURE);
    }
}
