//-------------------------------------------------------------------------------------------------
// NkFileManager.h
// �������� ���������
// ������
//-------------------------------------------------------------------------------------------------

#pragma once

#include "NkCore.h"

class NkFileManager : NkMemory
{
public:
	static NkFileManager& Get();
	static bool IsInitialized();

	static void Init();
	static void Shutdown();

protected:
	NkFileManager() {};
	NkFileManager(const NkFileManager&) {};

	static NkFileManager* ms_pkFileManager;

};