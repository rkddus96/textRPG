#pragma once

#include <iostream>
#include <unordered_set>
#include <list>
#include <chrono>
#include "LogicHelper.h"

struct AudioInfo
{
public:

	AudioInfo(const std::string& InName, float InLength)
	{
		Name = InName;
		Length = InLength;
		StartTimeSeceond = LogicHelper::GetTimeSecond();
	}

	~AudioInfo()
	{

	}

	bool IsRetired()
	{
		return (LogicHelper::GetTimeSecond() - StartTimeSeceond) >= Length;
	}

public:

	std::string Name;
	float Length;

private:

	float StartTimeSeceond;

};

class AudioPlayer
{
public:

	/// <param name="FilePath">파일 경로</param>
	/// <param name="Volume"></param>
	/// <returns></returns>
	static std::string Play(const std::string& FilePath, float Volume = 1);

	/// <param name="FilePath">파일 경로</param>
	/// <param name="AudioName">오디오 이름, 이름을 정해서 Stop하거나 볼륨 줄이거나 현재 재생 중인지 알 수 있음</param>
	/// <param name="Volume"></param>
	static void Play(const std::string& FilePath, const std::string& AudioName, float Volume = 1);
	static void Stop(const std::string& AudioName);
	static void StopAll();

	static void SetVolume(const std::string& AudioName, float Volume);

	static bool IsPlaying(const std::string& AudioName);

	static void ClearRetiredAudios();

private:

	AudioPlayer() = delete;
	AudioPlayer(const AudioPlayer&) = delete;
	AudioPlayer& operator=(const AudioPlayer&) = delete;
	AudioPlayer(AudioPlayer&&) = delete;
	AudioPlayer& operator=(AudioPlayer&&) = delete;

	static void PlayInternal(const std::string& FilePath, const std::string& AudioName, float Volume);

private:

	/*int AudioIndex = 0;*/
	static std::unordered_set<std::string> AudioNameSet;
	static std::list<AudioInfo> AudioInfos;

};