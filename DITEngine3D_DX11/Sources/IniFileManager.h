#pragma once

namespace FileLoader
{
	//==========================================
	//Iniファイルのロード
	void AddIniFilePath(const char* _filePath, const char* _elementName);

	//==========================================
	//Iniファイルに値を書き込む　（文字列）
	void IniWrite(const char* _section, const char* _key, const char* _value, const char* _IniFileName);

	//==========================================
	//Iniファイルに値を書き込む　（数字）
	void IniWrite(const char* _section, const char* _key, int _value, const char* _IniFileName);

	//==========================================
	//Iniファイルに値を書き込む　（数字）
	void IniWrite(const char* _section, const char* _key, float _value, const char* _IniFileName);

	//==========================================
	//Iniファイルから値を読み込む　（文字列）
	const char* IniLoad_Word(const char* _section, const char* _key, const char* _IniFileName);

	//==========================================
	//Iniファイルから値を読み込む　（文字列）
	int IniLoad_Int(const char* _section, const char* _key, const char* _IniFileName);

	//==========================================
	//Iniファイルから値を読み込む　（文字列）
	float IniLoad_Float(const char* _section, const char* _key, const char* _IniFileName);
}