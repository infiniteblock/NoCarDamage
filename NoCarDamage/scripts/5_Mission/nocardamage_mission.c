/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Original mod: NoCarDamage by blubberdiblupp
 * Original source: https://github.com/Blubberdiblupp/NoCarDamage
 *
 * Modified by: Schmicky, 8/7/2026
 * source: https://github.com/infiniteblock/NoCarDamage
 * Changes: [Fix's for eAI,Toxic Zones,Player Damage"]
 */
 modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();

		Print("[NoCarDamage] MissionServer.OnInit scheduling config load+cleanup+scan+precrash-cache-cleanup");
		g_Game.GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(NCD_LoadConfigFromDisk, 1000, false);
		g_Game.GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(NCD_CleanupVehicleOverrides, 2000, false);
		g_Game.GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(NCD_ScanVehiclesAndExtendConfig, 3000, false);
		g_Game.GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(NCD_CleanupPreCrashCache, 5000, true);
	}
};

modded class MissionMainMenu
{
	override void OnInit()
	{
		super.OnInit();
		NCD_RegisterKeybinds();
	}

	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		NCD_RegisterKeybinds();
	}
};
