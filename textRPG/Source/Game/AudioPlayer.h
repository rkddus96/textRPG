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

private:

	/*float GetTimeSecond()
	{
		auto Now = std::chrono::system_clock::now();
		long long Milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(Now.time_since_epoch()).count();
		return Milliseconds / 1000.0f;
	}*/

public:

	std::string Name;
	float Length;

private:

	float StartTimeSeceond;

};

class AudioPlayer
{
public:

	AudioPlayer();

	~AudioPlayer();

	/// <param name="FilePath">파일 경로</param>
	/// <param name="Volume"></param>
	/// <returns></returns>
	std::string Play(const std::string& FilePath, int Volume = 500);

	/// <param name="FilePath">파일 경로</param>
	/// <param name="AudioName">오디오 이름, 이름을 정해서 Stop하거나 볼륨 줄이거나 현재 재생 중인지 알 수 있음</param>
	/// <param name="Volume"></param>
	void Play(const std::string& FilePath, const std::string& AudioName, int Volume = 500);
	void Stop(const std::string& AudioName);
	void StopAll();

	void SetVolume(const std::string& AudioName, int Volume);

	bool IsPlaying(const std::string& AudioName);

	void ClearRetiredAudios();

private:

	void PlayInternal(const std::string& FilePath, const std::string& AudioName, int Volume);

private:

	int AudioIndex = 0;
	static std::unordered_set<std::string> AudioNameSet;
	static std::list<AudioInfo> AudioInfos;

};