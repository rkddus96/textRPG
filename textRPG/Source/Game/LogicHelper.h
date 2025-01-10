#pragma once

#include <string>
#include <chrono>

class LogicHelper
{
public: // 문자 관련

	static std::string WStringToString(const std::wstring& WStr);
	static std::string WCharToString(wchar_t WChar);
	static std::wstring StringToWString(const std::string& Str);
	static wchar_t CharToWChar(char Char);
	static void PrintWStringFast(const std::wstring& WString);

	static bool IsHangul(wchar_t WChar)
	{
		return (WChar >= 0xAC00 && WChar <= 0xD7A3) ||  // 한글 음절
			(WChar >= 0x1100 && WChar <= 0x11FF) ||  // 현대 한글 자모
			(WChar >= 0x3130 && WChar <= 0x318F);    // 호환용 한글 자모
	}

	static bool IsHanja(wchar_t WChar)
	{
		return (WChar >= 0x4E00 && WChar <= 0x9FFF) ||  // CJK 통합 한자
			(WChar >= 0x3400 && WChar <= 0x4DBF);    // CJK 확장 A
	}

public: //콘솔 관련

	static void GetConsoleSize(int& OutWidth, int& OutHeight);
	static void ClearConsole();
	static void SetFixedConsoleSize(int Width, int Height);


public: // 시간


	static float GetTimeSecond()
	{
		auto Now = std::chrono::system_clock::now();
		long long Milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(Now.time_since_epoch()).count();
		return Milliseconds / 1000.0f;
	}

public: // 랜덤

	/// <summary>
	/// 범위는 [Min, Max)
	/// </summary>
	static double GetRandomNumber(double Min, double Max);

	/// <summary>
	/// 범위는 [Min, Max]
	/// </summary>
	static int GetRandomNumber(int Min, int Max);

	/// <summary>
	/// 범위는 [-2147483648, 2147483647]
	/// </summary>
	static int GetRandomNumberMaxRange();
};