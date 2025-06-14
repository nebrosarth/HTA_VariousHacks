#include <Windows.h>
#include "ThirdParty/Injector/injector.hpp"
#include "ThirdParty/IniReader/IniReader.h"

#include "Gun.h"
#include "CVector.h"
#include "Player.h"
#include "DragDropItemsWnd.h"
#include "CMiracle3d.h"
#include "PrototypeManager.h"
#include "WareUse.h"
#include "GunRotation.h"
#include "LocationDebug.h"
#include "SkinFixes.h"
#include "GunLights.h"
#include "BlastWaveDamageType.h"
#include "CardanFix.h"
#include "ObjContUpgrade.h"
#include "PostEffectReloadFix.h"

void Init()
{
	CIniReader iniReader("VariousHacks.ini");

	GunsRotationTimeOut = iniReader.ReadFloat("GUNS_ROTATION", "TimeOut", 0);
	if (iniReader.ReadInteger("GUNS_ROTATION", "Enabled", 0) == 1 && GunsRotationTimeOut > 0)
	{
		WeaponGroupsToTrigger[0] = iniReader.ReadInteger("GUNS_ROTATION", "WeaponGroup_1", 0) == 1 ? 0x21 : 0;
		WeaponGroupsToTrigger[1] = iniReader.ReadInteger("GUNS_ROTATION", "WeaponGroup_2", 0) == 1 ? 0x22 : 0;
		WeaponGroupsToTrigger[2] = iniReader.ReadInteger("GUNS_ROTATION", "WeaponGroup_3", 0) == 1 ? 0x23 : 0;
		WeaponGroupsToTrigger[3] = iniReader.ReadInteger("GUNS_ROTATION", "WeaponGroup_4", 0) == 1 ? 0x24 : 0;
		WeaponGroupsToTrigger[4] = iniReader.ReadInteger("GUNS_ROTATION", "WeaponGroup_5", 0) == 1 ? 0x25 : 0;
		WeaponGroupsToTrigger[5] = iniReader.ReadInteger("GUNS_ROTATION", "WeaponGroup_All", 0) == 1 ? 0x26 : 0;

		InitGunRotation();
	}

	if (iniReader.ReadInteger("GENERAL", "AllowMoreQuestIcons", 0) == 1)
	{
		injector::WriteMemory<BYTE>(0x0056BF09, 0xEB);
	}

	if (iniReader.ReadInteger("WARE_USE", "Enabled", 0) == 1)
	{
		RepairWare = iniReader.ReadString("WARE_USE", "RepairWare", "");
		RepairUnits = iniReader.ReadInteger("WARE_USE", "RepairUnits", 0);

		RefuelWare = iniReader.ReadString("WARE_USE", "RefuelWare", "");
		RefuelUnits = iniReader.ReadInteger("WARE_USE", "RefuelUnits", 0);
		InitWareUse();
	}

	if (iniReader.ReadInteger("GENERAL", "FixLocationDebug", 0) == 1)
	{
		InitLocationDebug();
	}

	if (iniReader.ReadInteger("GENERAL", "SkinFixes", 0) == 1)
	{
		InitSkinFixes();
	}

	if (iniReader.ReadInteger("GENERAL", "CardanFix", 0) == 1)
	{
		InitCardanFix();
	}

	if (iniReader.ReadInteger("GENERAL", "ObjContUpgrade", 0) == 1)
	{
		InitObjContUpgrade();
	}

	if (iniReader.ReadInteger("DEVELOPER", "GunLights", 0) == 1)
	{
		InitGunLights();
	}

	if (iniReader.ReadInteger("DEVELOPER", "BlastWaveDamageType", 0) == 1)
	{
		InitBlastWaveDamageType();
	}

	if (iniReader.ReadInteger("DEVELOPER", "PlasmaBunchBarrelHack", 0) == 1)
	{
		injector::MakeNOP(0x00746198, 6);
	}

	if (iniReader.ReadInteger("DEVELOPER", "FixPostEffectReload", 0) == 1)
	{
		InitPostEffectReload();
	}

	if (iniReader.ReadInteger("DEVELOPER", "Ultrawide", 0) == 1)
	{
		injector::WriteMemory(0x7A6128, 0x3F800000);
	}
}

BOOL APIENTRY DllMain(HMODULE, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		Init();
	}

	return TRUE;
}