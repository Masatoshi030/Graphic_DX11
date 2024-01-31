#pragma once
#pragma once
#include "ImGUIWindowBase.h"
#include "Direct3D11.h"
#include "Time.h"

class  ImGUI_DisneyMaterialEditWindow : public ImGUIWindowBase
{
public:

	void Init();
	~ImGUI_DisneyMaterialEditWindow();

	void Draw_WindowSetting();
	void Draw_ItemSetting();


	//=== ï\é¶çÄñ⁄ ===//

	DISNEY_MATERIAL Disney_Material;
};