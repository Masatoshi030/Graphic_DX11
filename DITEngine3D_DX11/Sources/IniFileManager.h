#pragma once

namespace FileLoader
{
	//==========================================
	//Ini�t�@�C���̃��[�h
	void AddIniFilePath(const char* _filePath, const char* _elementName);

	//==========================================
	//Ini�t�@�C���ɒl���������ށ@�i������j
	void IniWrite(const char* _section, const char* _key, const char* _value, const char* _IniFileName);

	//==========================================
	//Ini�t�@�C���ɒl���������ށ@�i�����j
	void IniWrite(const char* _section, const char* _key, int _value, const char* _IniFileName);

	//==========================================
	//Ini�t�@�C���ɒl���������ށ@�i�����j
	void IniWrite(const char* _section, const char* _key, float _value, const char* _IniFileName);

	//==========================================
	//Ini�t�@�C������l��ǂݍ��ށ@�i������j
	const char* IniLoad_Word(const char* _section, const char* _key, const char* _IniFileName);

	//==========================================
	//Ini�t�@�C������l��ǂݍ��ށ@�i������j
	int IniLoad_Int(const char* _section, const char* _key, const char* _IniFileName);

	//==========================================
	//Ini�t�@�C������l��ǂݍ��ށ@�i������j
	float IniLoad_Float(const char* _section, const char* _key, const char* _IniFileName);
}