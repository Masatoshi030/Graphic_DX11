#include "ImGUIWindowBase.h"

#include <stdio.h>

void ImGUIWindowBase::SetWindowName(const char* _WindowName)
{
	std::strcpy(WindowName, _WindowName);
}