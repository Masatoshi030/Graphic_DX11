#include "IniFileManager.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <unordered_map>

using namespace std;

namespace FileLoader
{

	std::unordered_map<std::string, const char*> IniFileList;

	void AddIniFilePath(const char* _filePath, const char* _elementName)
	{
		//日本語表示の設定
		wcout.imbue(locale("", locale::ctype));

		//iniファイルパスをリストに追加
		IniFileList[_elementName] = _filePath;
	}

	//整数型の書き込み処理
	void IniWrite(const char* _section, const char* _key, int _value, const char* _IniFileName)
	{
		//intをchar型に変換
		const char* char_value;

		string str_value = to_string(_value);

		char_value = str_value.c_str();

		//書き込み
		WritePrivateProfileString(_section, _key, char_value, IniFileList[_IniFileName]);
	}

	//浮動小数点型の書き込み処理
	void IniWrite(const char* _section, const char* _key, float _value, const char* _IniFileName)
	{
		//intをchar型に変換
		const char* char_value;

		string str_value = to_string(_value);

		char_value = str_value.c_str();

		//書き込み
		WritePrivateProfileString(_section, _key, char_value, IniFileList[_IniFileName]);
	}

	//文字列の書き込み処理
	void IniWrite(const char* _section, const char* _key, const char* _value, const char* _IniFileName)
	{
		//書き込み
		WritePrivateProfileString(_section, _key, _value, IniFileList[_IniFileName]);
	}

	//文字列の読み取り
	const char* IniLoad_Word(const char* _section, const char* _key, const char* _IniFileName)
	{
		char returnValue[256];

		GetPrivateProfileString(_section, _key, "", returnValue, sizeof(char) * 256, IniFileList[_IniFileName]);
	
		return returnValue;
	}

	int IniLoad_Int(const char* _section, const char* _key, const char* _IniFileName)
	{
		char returnValue[256];

		GetPrivateProfileString(_section, _key, "0", returnValue, sizeof(char) * 256, IniFileList[_IniFileName]);

		return stoi(returnValue);
	}

	float IniLoad_Float(const char* _section, const char* _key, const char* _IniFileName)
	{
		char returnValue[256];

		GetPrivateProfileString(_section, _key, "0.0", returnValue, sizeof(char) * 256, IniFileList[_IniFileName]);

		return stof(returnValue);
	}
}