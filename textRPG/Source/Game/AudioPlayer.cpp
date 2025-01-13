#include "AudioPlayer.h"
#include <windows.h>
#include <string>
#include <algorithm>
#include <limits>
#include "LogicHelper.h"
#pragma comment(lib,"winmm.lib")

std::unordered_set<std::string> AudioPlayer::AudioNameSet;
std::list<AudioInfo> AudioPlayer::AudioInfos;


std::string AudioPlayer::Play(const std::string& FilePath, float Volume)
{
    for (int i = 0; i < 100; ++i)
    {
        int AudioIndex = LogicHelper::GetRandomNumberMaxRange();

        std::string AudioName = "Audio" + std::to_string(AudioIndex);

        if (AudioNameSet.find(AudioName) != AudioNameSet.end() || IsPlaying(AudioName))
        {
            continue;
        }

        AudioNameSet.insert(AudioName);

        PlayInternal(FilePath, AudioName, Volume);
        return AudioName;
    }

    std::cout << "AudioPlayer, Play, Fail to play Audio : " << FilePath << std::endl;
    return "";
}

void AudioPlayer::Play(const std::string& FilePath, const std::string& AudioName, float Volume)
{
    if (AudioNameSet.find(AudioName) != AudioNameSet.end() || IsPlaying(AudioName))
    {
        std::cout << "AudioPlayer, Play Fail to play Audio : " << FilePath << std::endl;
        return;
    }

    PlayInternal(FilePath, AudioName, Volume);
}

void AudioPlayer::Stop(const std::string& AudioName)
{
    const std::string& Command = "close " + AudioName;

    mciSendStringA(Command.c_str(), NULL, 0, NULL);
}

void AudioPlayer::StopAll()
{
    auto node = AudioInfos.begin();

    while (node != AudioInfos.end())
    {
        Stop(node->Name);
        AudioNameSet.erase(node->Name);

        if (std::next(node) == AudioInfos.end())
        {
            AudioInfos.erase(node);
            break;
        }
        else
        {
            node++;
            AudioInfos.erase(std::prev(node));
        }
    }
}

void AudioPlayer::SetVolume(const std::string& AudioName, float Volume)
{
    int ActualVolume = (int)std::clamp<float>(Volume * 1000, 0, 1000);
    
    const std::string Command = "setaudio " + AudioName + " volume to " + std::to_string(ActualVolume);

    if (mciSendStringA(Command.c_str(), NULL, 0, NULL) != 0)
    {
        std::cerr << "Failed to set volume for: " << AudioName << std::endl;
    }
}

bool AudioPlayer::IsPlaying(const std::string& AudioName)
{
    // 재생 중인지 확인
    char Buffer[32];
    const std::string Command = "status " + AudioName + " mode"; // 상태 확인: 재생 중인지 여부
    mciSendStringA(Command.c_str(), Buffer, sizeof(Buffer), NULL);

    if (std::string(Buffer) == "playing")
    {
        return true;
    }

    return false;
}

void AudioPlayer::ClearRetiredAudios()
{
    auto node = AudioInfos.begin();

    while (node != AudioInfos.end())
    {
        if (node->IsRetired())
        {
            Stop(node->Name);
            AudioNameSet.erase(node->Name);

            if (std::next(node) == AudioInfos.end())
            {
                AudioInfos.erase(node);
                break;
            }
            else
            {
                node++;
                AudioInfos.erase(std::prev(node));
                continue;
            }
        }

        node++;
    }
}

void AudioPlayer::PlayInternal(const std::string& FilePath, const std::string& AudioName, float Volume)
{
    // 미디어 파일 열기
    std::string Command = "open \"" + FilePath + "\" type mpegvideo alias " + AudioName;
    if (mciSendStringA(Command.c_str(), NULL, 0, NULL) != 0)
    {
        std::cerr << "Failed to open sound file: " << FilePath << std::endl;
        return;
    }

    Command = "status " + AudioName + " length";

    // 재생 길이 가져오기 (밀리초 단위로 반환)
    char Buffer[32]; // 길이를 담을 버퍼
    mciSendStringA(Command.c_str(), Buffer, sizeof(Buffer), NULL);

    // 길이를 정수로 변환
    int lengthInMilliseconds = std::stoi(Buffer);
    //std::cout << "Audio length: " << lengthInMilliseconds << " milliseconds." << std::endl;

    Command = "play " + AudioName;
    // 미디어 파일 재생
    if (mciSendStringA(Command.c_str(), NULL, 0, NULL) != 0)
    {
        std::cerr << "Failed to play sound file: " << FilePath << std::endl;
        return;
    }

    SetVolume(AudioName, Volume);

    AudioInfos.push_back(AudioInfo(AudioName, lengthInMilliseconds / 1000.0f));
}

//AudioPlayer::~AudioPlayer()
//{
//    StopAll();
//    std::cout << "Audio Destroyed" << std::endl;
//}

