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
