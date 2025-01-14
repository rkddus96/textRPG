#pragma once

#include <iostream>
#include <unordered_map>
#include <list>
#include <chrono>
#include "LogicHelper.h"

struct AudioInfo
{
public:

	AudioInfo(const std::string& InName, float InLength, const std::string& InFilePath, float InVolume, float bInIsLoop) :
		Name(InName),
		Length(InLength),
		bIsLoop(bInIsLoop),
		FileName(InFilePath),
		Volume(InVolume)
	{
		StartTimeSeceond = LogicHelper::GetTimeSecond();
	}

	~AudioInfo()
	{

	}

	bool IsRetired()
	{
		double CurrentTime = LogicHelper::GetTimeSecond();
		double ElapsedTime = (CurrentTime - StartTimeSeceond);
		return  ElapsedTime >= Length;
	}

	bool GetIsLoop() const
	{
		return bIsLoop;
	}

	void SetIsLooping(bool bShouldLoop)
	{
		bIsLoop = bShouldLoop;
	}

	const std::string& GetFileName() const
	{
		return FileName;
	}

	float GetVolume() const
	{
		return Volume;
	}

	void InitStartTimeSeceond()
	{
		StartTimeSeceond = LogicHelper::GetTimeSecond();
	}

	bool operator == (const AudioInfo& Other) const
	{
		return Name == Other.Name;
	}

public:

	std::string Name;
	float Length;

private:

	bool bIsLoop;
	double StartTimeSeceond;
	const std::string FileName;
	float Volume;

};

class AudioPlayer
{
public:

	/// <param name="FilePath">파일 이름, wav 파일만 실행 가능</param>
	/// <param name="Volume"></param>
	/// <returns></returns>
	static std::string Play(const std::string& FileName, float Volume = 1);

	/// <param name="FilePath">파일 이름, wav 파일만 실행 가능</param>
	/// <param name="AudioName">오디오 이름, 이름을 정해서 Stop하거나 볼륨 줄이거나 현재 재생 중인지 알 수 있음</param>
	/// <param name="Volume"></param>
	static void Play(const std::string& FileName, const std::string& AudioName, float Volume = 1);
	static void Stop(const std::string& AudioName);
	static void StopAll();

	static std::string PlayLoop(const std::string& FileName, float Volume = 1);

	static void SetVolume(const std::string& AudioName, float Volume);

	static bool IsPlaying(const std::string& AudioName);

	static void ClearRetiredAudios();

private:

	AudioPlayer() = delete;
	AudioPlayer(const AudioPlayer&) = delete;
	AudioPlayer& operator=(const AudioPlayer&) = delete;
	AudioPlayer(AudioPlayer&&) = delete;
	AudioPlayer& operator=(AudioPlayer&&) = delete;

	static void PlayInternal(const std::string& FileName, const std::string& AudioName, float Volume, bool bShouldLoop);

	static void ReplayLoop();

	static void Tick(double DeltaTime);

	static void StopInternal(const std::string& AudioName);

private:

	static std::unordered_map<std::string, std::shared_ptr<AudioInfo>> AudioNameMap;
	static std::list<std::shared_ptr<AudioInfo>> AudioInfos;

};