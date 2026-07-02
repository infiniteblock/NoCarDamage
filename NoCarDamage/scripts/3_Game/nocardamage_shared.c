static const string NCD_CFG_DIR  = "$profile:NoCarDamage";
static const string NCD_CFG_PATH = "$profile:NoCarDamage\\NoCarDamage_Config.json";
static const int NCD_CFG_VERSION = 22;
static const int NCD_RPC_FLIP = 4000971;
static const int NCD_PRECRASH_CACHE_MS = 1000;

ref map<string, int> NCD_ToxicPresence = new map<string, int>();

int NCD_MapGet(map<string, int> m, string k)
{
	if (!m || k == "") return 0;
	int v = 0;
	if (m.Find(k, v)) return v;
	return 0;
}

void NCD_MapSet(map<string, int> m, string k, int v)
{
	if (!m || k == "") return;
	m.Set(k, v);
}

int NCD_NormalizeBool01(int v, int fallback)
{
	if (v == 0 || v == 1)
		return v;
	return fallback;
}

int NCD_NormalizeTriState(int v, int fallback)
{
	if (v == -1 || v == 0 || v == 1)
		return v;
	return fallback;
}

class NCD_VehicleOverride
{
	string ClassName = "";

	int Vehicle_BlockBullets = -1;
	int Vehicle_BlockExplosions = -1;
	int Vehicle_BlockMelee = -1;
	int Vehicle_AllowGlassDamage = -1;
	int Vehicle_DisableCrashDamage = -1;
	int Vehicle_DisableWaterDamage = -1;
	int Vehicle_BlockContaminated = -1;
	int Player_BlockContaminatedWhileInVehicle = -1;
	int Player_DoorOpenDisablesProtectionInContaminated = -1;
	int Vehicle_DisableRedlineDamage = -1;
	int Vehicle_BlockCrewCrashDamage = -1;
	int Vehicle_EnableCrashSounds = -1;
	int Vehicle_NoDamageToZombies = -1;
	int Vehicle_NoDamageToAnimals = -1;
	int Vehicle_NoDamageToPlayers = -1;
	int Vehicle_NoDamageToExpansionAI = -1;
	int Vehicle_AutoFlip = -1;
	float Vehicle_DisableCrash_MaxSpeedKmh = -1.0;
	int Player_NoDamageWhileInVehicle = -1;
	int Player_BlockAllDamageWhileInVehicle = -1;
	int Player_BlockBulletsWhileInVehicle = -1;
	int Player_BlockExplosionsWhileInVehicle = -1;
	int Player_BlockMeleeWhileInVehicle = -1;
	int ExpansionAI_NoDamageWhileInVehicle = -1;
	int ExpansionAI_BlockAllDamageWhileInVehicle = -1;
	int ExpansionAI_BlockBulletsWhileInVehicle = -1;
	int ExpansionAI_BlockExplosionsWhileInVehicle = -1;
	int ExpansionAI_BlockMeleeWhileInVehicle = -1;
	int ExpansionAI_BlockContaminatedWhileInVehicle = -1;
	int ExpansionAI_DoorOpenDisablesProtectionInContaminated = -1;
	int ExpansionAI_NoDamageAfterJumpFromVehicle = -1;
	int Protect_AttachmentsOnVehicle = -1;
	int Protect_PlayerClothingInVehicle = -1;
}

class NCD_Config
{
	int Version = NCD_CFG_VERSION;
	int Vehicle_BlockBullets = 1;
	int Vehicle_BlockExplosions = 1;
	int Vehicle_BlockMelee = 0;
	int Vehicle_AllowGlassDamage = 0;
	int Vehicle_DisableCrashDamage = 1;
	float Vehicle_DisableCrash_MaxSpeedKmh = -1.0;
	int Vehicle_DisableWaterDamage = 1;
	int Vehicle_BlockContaminated = 0;
	int Player_BlockContaminatedWhileInVehicle = 0;
	int Player_DoorOpenDisablesProtectionInContaminated = 0;
	int Player_NoDamageWhileInVehicle = 1;
	int Player_BlockAllDamageWhileInVehicle = 0;
	int Player_BlockBulletsWhileInVehicle = 1;
	int Player_BlockExplosionsWhileInVehicle = 1;
	int Player_BlockMeleeWhileInVehicle = 0;
	int Protect_PlayerClothingInVehicle = 1;
	int Protect_AttachmentsOnVehicle = 1;
	int Vehicle_DisableRedlineDamage = 1;
	int Vehicle_BlockCrewCrashDamage = 1;
	int Vehicle_EnableCrashSounds = 1;
	int Vehicle_NoDamageToZombies = 0;
	int Vehicle_NoDamageToAnimals = 0;
	int Vehicle_NoDamageToPlayers = 0;
	int Vehicle_NoDamageToExpansionAI = 0;
	int Vehicle_AutoFlip = 0;
	int Vehicle_AutoFlipWithButton = 0;
	int Player_NoDamageAfterJumpFromVehicle = 0;
	float Player_NoDamageAfterJump_MinSpeedKmh = 8.0;
	float Player_NoDamageAfterJump_MaxSpeedKmh = -1.0;
	int Player_NoDamageAfterJump_WindowMS = 1500;
	int ExpansionAI_NoDamageWhileInVehicle = 0;
	int ExpansionAI_BlockAllDamageWhileInVehicle = 0;
	int ExpansionAI_BlockBulletsWhileInVehicle = 0;
	int ExpansionAI_BlockExplosionsWhileInVehicle = 0;
	int ExpansionAI_BlockMeleeWhileInVehicle = 0;
	int ExpansionAI_BlockContaminatedWhileInVehicle = 0;
	int ExpansionAI_DoorOpenDisablesProtectionInContaminated = 0;
	int ExpansionAI_NoDamageAfterJumpFromVehicle = 0;
	int EnableVehicleOverrides = 1;
	int AutoExtendVehicleOverrides = 0;
	ref array<ref NCD_VehicleOverride> VehicleOverrides;

	void NCD_Config()
	{
		VehicleOverrides = new array<ref NCD_VehicleOverride>;
	}
}

static ref NCD_Config g_NCD_Cfg;
static bool g_NCD_CfgInit = false;
static bool g_NCD_CfgDiskLoaded = false;
static ref map<string, ref NCD_VehicleOverride> g_NCD_OverrideMap;
static ref map<string, ref NCD_ResolvedVehicleRules> g_NCD_ResolvedRulesMap;
static bool g_NCD_HasToxicOverrides = false;
static int g_NCD_ExpansionVehiclesState = -1;
static int g_NCD_ExpansionDisableVehicleDamageState = -1;
static ref map<int, ref array<float>> g_NCD_PreCrashSpeedCache;
static ref map<int, int> g_NCD_PreCrashCacheTime;

class NCD_ExpansionVehicleSettingsLite
{
	int m_Version = 0;
	int DisableVehicleDamage = 0;
}

bool NCD_IsExpansionVehiclesPresent()
{
	if (g_NCD_ExpansionVehiclesState != -1)
		return g_NCD_ExpansionVehiclesState == 1;

	if (!g_Game)
	{
		g_NCD_ExpansionVehiclesState = 0;
		return false;
	}

	bool present = false;

	if (g_Game.ConfigIsExisting("CfgPatches DayZExpansion_Vehicles"))
		present = true;
	else if (g_Game.ConfigIsExisting("CfgPatches DayZExpansion_Core"))
		present = true;
	else if (g_Game.ConfigIsExisting("CfgVehicles ExpansionVehicleBase"))
		present = true;
	else if (g_Game.ConfigIsExisting("CfgVehicles ExpansionHelicopterScript"))
		present = true;

	if (present)
		g_NCD_ExpansionVehiclesState = 1;
	else
		g_NCD_ExpansionVehiclesState = 0;
	return present;
}

bool NCD_IsExpansionVehicleDamageDisabled()
{
	if (g_NCD_ExpansionDisableVehicleDamageState != -1)
		return g_NCD_ExpansionDisableVehicleDamageState == 1;

	if (!g_Game || !g_Game.IsServer())
	{
		g_NCD_ExpansionDisableVehicleDamageState = 0;
		return false;
	}

	if (!NCD_IsExpansionVehiclesPresent())
	{
		g_NCD_ExpansionDisableVehicleDamageState = 0;
		return false;
	}

	ref array<string> candidatePaths = new array<string>();
	candidatePaths.Insert("$profile:ExpansionMod\\Settings\\VehicleSettings.json");
	candidatePaths.Insert("$profile:Expansion\\Settings\\VehicleSettings.json");
	candidatePaths.Insert("$profile:DayZExpansion\\Settings\\VehicleSettings.json");

	for (int i = 0; i < candidatePaths.Count(); i++)
	{
		string p = candidatePaths[i];
		if (!FileExist(p))
			continue;

		NCD_ExpansionVehicleSettingsLite settings = new NCD_ExpansionVehicleSettingsLite();
		JsonFileLoader<NCD_ExpansionVehicleSettingsLite>.JsonLoadFile(p, settings);

		if (settings && settings.DisableVehicleDamage == 1)
		{
			g_NCD_ExpansionDisableVehicleDamageState = 1;
			Print("[NoCarDamage] Expansion VehicleSettings detected: DisableVehicleDamage=1 -> using Expansion crash/water protection fast path");
			return true;
		}

		g_NCD_ExpansionDisableVehicleDamageState = 0;
		Print("[NoCarDamage] Expansion VehicleSettings detected: DisableVehicleDamage!=1 -> keeping NoCarDamage crash/water logic active");
		return false;
	}

	g_NCD_ExpansionDisableVehicleDamageState = 0;
	return false;
}

bool NCD_IsOverrideNoOp(NCD_VehicleOverride o)
{
	if (!o)
		return true;

	if (o.Vehicle_BlockBullets != -1) return false;
	if (o.Vehicle_BlockExplosions != -1) return false;
	if (o.Vehicle_BlockMelee != -1) return false;
	if (o.Vehicle_AllowGlassDamage != -1) return false;
	if (o.Vehicle_DisableCrashDamage != -1) return false;
	if (o.Vehicle_DisableWaterDamage != -1) return false;
	if (o.Vehicle_BlockContaminated != -1) return false;
	if (o.Player_BlockContaminatedWhileInVehicle != -1) return false;
	if (o.Player_DoorOpenDisablesProtectionInContaminated != -1) return false;
	if (o.Vehicle_DisableRedlineDamage != -1) return false;
	if (o.Vehicle_BlockCrewCrashDamage != -1) return false;
	if (o.Vehicle_EnableCrashSounds != -1) return false;
	if (o.Vehicle_NoDamageToZombies != -1) return false;
	if (o.Vehicle_NoDamageToAnimals != -1) return false;
	if (o.Vehicle_NoDamageToPlayers != -1) return false;
	if (o.Vehicle_NoDamageToExpansionAI != -1) return false;
	if (o.Vehicle_AutoFlip != -1) return false;
	if (o.Vehicle_DisableCrash_MaxSpeedKmh != -1.0) return false;
	if (o.Player_NoDamageWhileInVehicle != -1) return false;
	if (o.Player_BlockAllDamageWhileInVehicle != -1) return false;
	if (o.Player_BlockBulletsWhileInVehicle != -1) return false;
	if (o.Player_BlockExplosionsWhileInVehicle != -1) return false;
	if (o.Player_BlockMeleeWhileInVehicle != -1) return false;
	if (o.ExpansionAI_NoDamageWhileInVehicle != -1) return false;
	if (o.ExpansionAI_BlockAllDamageWhileInVehicle != -1) return false;
	if (o.ExpansionAI_BlockBulletsWhileInVehicle != -1) return false;
	if (o.ExpansionAI_BlockExplosionsWhileInVehicle != -1) return false;
	if (o.ExpansionAI_BlockMeleeWhileInVehicle != -1) return false;
	if (o.ExpansionAI_BlockContaminatedWhileInVehicle != -1) return false;
	if (o.ExpansionAI_DoorOpenDisablesProtectionInContaminated != -1) return false;
	if (o.ExpansionAI_NoDamageAfterJumpFromVehicle != -1) return false;
	if (o.Protect_AttachmentsOnVehicle != -1) return false;
	if (o.Protect_PlayerClothingInVehicle != -1) return false;

	return true;
}

class NCD_ResolvedVehicleRules
{
	int Vehicle_BlockBullets;
	int Vehicle_BlockExplosions;
	int Vehicle_BlockMelee;
	int Vehicle_AllowGlassDamage;
	int Vehicle_DisableCrashDamage;
	int Vehicle_DisableWaterDamage;
	int Vehicle_BlockContaminated;
	int Vehicle_DisableRedlineDamage;
	int Vehicle_BlockCrewCrashDamage;
	int Vehicle_EnableCrashSounds;
	int Vehicle_NoDamageToZombies;
	int Vehicle_NoDamageToAnimals;
	int Vehicle_NoDamageToPlayers;
	int Vehicle_NoDamageToExpansionAI;
	int Vehicle_AutoFlip;
	float Vehicle_DisableCrash_MaxSpeedKmh = -1.0;

	int Player_NoDamageWhileInVehicle;
	int Player_BlockAllDamageWhileInVehicle;
	int Player_BlockBulletsWhileInVehicle;
	int Player_BlockExplosionsWhileInVehicle;
	int Player_BlockMeleeWhileInVehicle;
	int Player_BlockContaminatedWhileInVehicle;
	int Player_DoorOpenDisablesProtectionInContaminated;

	int ExpansionAI_NoDamageWhileInVehicle;
	int ExpansionAI_BlockAllDamageWhileInVehicle;
	int ExpansionAI_BlockBulletsWhileInVehicle;
	int ExpansionAI_BlockExplosionsWhileInVehicle;
	int ExpansionAI_BlockMeleeWhileInVehicle;
	int ExpansionAI_BlockContaminatedWhileInVehicle;
	int ExpansionAI_DoorOpenDisablesProtectionInContaminated;

	int Protect_AttachmentsOnVehicle;
	int Protect_PlayerClothingInVehicle;
}

bool NCD_MigrateConfig()
{
	if (!g_NCD_Cfg)
		return false;

	bool changed = false;

	if (g_NCD_Cfg.Version <= 0)
	{
		g_NCD_Cfg.Version = 1;
		changed = true;
	}

	if (g_NCD_Cfg.Version < 7)
	{
		g_NCD_Cfg.Vehicle_DisableRedlineDamage = 1;
		g_NCD_Cfg.Vehicle_NoDamageToZombies = 0;
		g_NCD_Cfg.Vehicle_NoDamageToAnimals = 0;
		g_NCD_Cfg.Vehicle_NoDamageToPlayers = 0;
		g_NCD_Cfg.Vehicle_AutoFlip = 0;
		g_NCD_Cfg.Player_NoDamageAfterJumpFromVehicle = 0;

		for (int oi = 0; oi < g_NCD_Cfg.VehicleOverrides.Count(); oi++)
		{
			NCD_VehicleOverride ov = g_NCD_Cfg.VehicleOverrides[oi];
			if (!ov) continue;

			ov.Vehicle_DisableRedlineDamage = -1;
			ov.Vehicle_NoDamageToZombies = -1;
			ov.Vehicle_NoDamageToAnimals = -1;
			ov.Vehicle_NoDamageToPlayers = -1;
			ov.Vehicle_AutoFlip = -1;
		}

		g_NCD_Cfg.Version = 7;
		changed = true;
	}

	if (g_NCD_Cfg.Version < 8)
	{
		g_NCD_Cfg.Vehicle_BlockCrewCrashDamage = 1;

		for (int oj = 0; oj < g_NCD_Cfg.VehicleOverrides.Count(); oj++)
		{
			NCD_VehicleOverride ov2 = g_NCD_Cfg.VehicleOverrides[oj];
			if (!ov2) continue;
			ov2.Vehicle_BlockCrewCrashDamage = -1;
		}

		g_NCD_Cfg.Version = 8;
		changed = true;
	}

	if (g_NCD_Cfg.Version < 9)
	{
		g_NCD_Cfg.Vehicle_EnableCrashSounds = 1;

		for (int ok = 0; ok < g_NCD_Cfg.VehicleOverrides.Count(); ok++)
		{
			NCD_VehicleOverride ov3 = g_NCD_Cfg.VehicleOverrides[ok];
			if (!ov3) continue;
			ov3.Vehicle_EnableCrashSounds = -1;
		}

		g_NCD_Cfg.Version = 9;
		changed = true;
	}


	if (g_NCD_Cfg.Version < 10)
	{
		g_NCD_Cfg.Vehicle_NoDamageToExpansionAI = 0;
		g_NCD_Cfg.ExpansionAI_NoDamageWhileInVehicle = 0;
		g_NCD_Cfg.ExpansionAI_BlockAllDamageWhileInVehicle = 0;
		g_NCD_Cfg.ExpansionAI_BlockBulletsWhileInVehicle = 0;
		g_NCD_Cfg.ExpansionAI_BlockExplosionsWhileInVehicle = 0;
		g_NCD_Cfg.ExpansionAI_BlockMeleeWhileInVehicle = 0;
		g_NCD_Cfg.ExpansionAI_BlockContaminatedWhileInVehicle = 0;
		g_NCD_Cfg.ExpansionAI_DoorOpenDisablesProtectionInContaminated = 0;
		g_NCD_Cfg.ExpansionAI_NoDamageAfterJumpFromVehicle = 0;

		for (int ol = 0; ol < g_NCD_Cfg.VehicleOverrides.Count(); ol++)
		{
			NCD_VehicleOverride ov4 = g_NCD_Cfg.VehicleOverrides[ol];
			if (!ov4) continue;

			ov4.Vehicle_NoDamageToExpansionAI = -1;
			ov4.ExpansionAI_NoDamageWhileInVehicle = -1;
			ov4.ExpansionAI_BlockAllDamageWhileInVehicle = -1;
			ov4.ExpansionAI_BlockBulletsWhileInVehicle = -1;
			ov4.ExpansionAI_BlockExplosionsWhileInVehicle = -1;
			ov4.ExpansionAI_BlockMeleeWhileInVehicle = -1;
			ov4.ExpansionAI_BlockContaminatedWhileInVehicle = -1;
			ov4.ExpansionAI_DoorOpenDisablesProtectionInContaminated = -1;
			ov4.ExpansionAI_NoDamageAfterJumpFromVehicle = -1;
		}

		g_NCD_Cfg.Version = 10;
		changed = true;
	}

	if (g_NCD_Cfg.Version < 11)
	{
		g_NCD_Cfg.AutoExtendVehicleOverrides = 0;
		g_NCD_Cfg.Version = 11;
		changed = true;
	}

	if (g_NCD_Cfg.Version < 20)
	{
		g_NCD_Cfg.Protect_PlayerClothingInVehicle = 1;

		g_NCD_Cfg.Vehicle_DisableCrash_MaxSpeedKmh = -1.0;
		g_NCD_Cfg.Player_NoDamageAfterJump_MaxSpeedKmh = -1.0;
		g_NCD_Cfg.Player_NoDamageAfterJump_WindowMS = 1500;

		for (int om = 0; om < g_NCD_Cfg.VehicleOverrides.Count(); om++)
		{
			NCD_VehicleOverride ov5 = g_NCD_Cfg.VehicleOverrides[om];
			if (!ov5) continue;
			ov5.Protect_PlayerClothingInVehicle = -1;
			ov5.Vehicle_DisableCrash_MaxSpeedKmh = -1.0;
		}

		g_NCD_Cfg.Version = 20;
		changed = true;
	}

	if (g_NCD_Cfg.Version < 21)
	{
		g_NCD_Cfg.Version = 21;
		changed = true;
	}

	if (g_NCD_Cfg.Version < 22)
	{
		g_NCD_Cfg.Player_NoDamageAfterJump_MinSpeedKmh = 8.0;
		g_NCD_Cfg.Version = 22;
		changed = true;
	}

	if (g_NCD_Cfg.Version < NCD_CFG_VERSION)
	{
		g_NCD_Cfg.Version = NCD_CFG_VERSION;
		changed = true;
	}

	return changed;
}

bool NCD_ConfigFileHasKey(string key)
{
	if (!FileExist(NCD_CFG_PATH))
		return false;

	FileHandle handle = OpenFile(NCD_CFG_PATH, FileMode.READ);
	if (!handle)
		return false;

	string line;
	string needle = "\"" + key + "\"";
	while (FGets(handle, line) >= 0)
	{
		if (line.IndexOf(needle) != -1)
		{
			CloseFile(handle);
			return true;
		}
	}

	CloseFile(handle);
	return false;
}

bool NCD_BackfillMissingConfigKeys()
{
	if (!g_NCD_Cfg)
		return false;

	bool hasRedline = NCD_ConfigFileHasKey("Vehicle_DisableRedlineDamage");
	bool hasNoDmgZeds = NCD_ConfigFileHasKey("Vehicle_NoDamageToZombies");
	bool hasNoDmgAnimals = NCD_ConfigFileHasKey("Vehicle_NoDamageToAnimals");
	bool hasNoDmgPlayers = NCD_ConfigFileHasKey("Vehicle_NoDamageToPlayers");
	bool hasNoDmgExpansionAI = NCD_ConfigFileHasKey("Vehicle_NoDamageToExpansionAI");
	bool hasAutoFlip = NCD_ConfigFileHasKey("Vehicle_AutoFlip");
	bool hasNoJumpDmg = NCD_ConfigFileHasKey("Player_NoDamageAfterJumpFromVehicle");
	bool hasExpansionAINoDmgInVehicle = NCD_ConfigFileHasKey("ExpansionAI_NoDamageWhileInVehicle");
	bool hasExpansionAIBlockAllInVehicle = NCD_ConfigFileHasKey("ExpansionAI_BlockAllDamageWhileInVehicle");
	bool hasExpansionAIBlockBulletsInVehicle = NCD_ConfigFileHasKey("ExpansionAI_BlockBulletsWhileInVehicle");
	bool hasExpansionAIBlockExplosionsInVehicle = NCD_ConfigFileHasKey("ExpansionAI_BlockExplosionsWhileInVehicle");
	bool hasExpansionAIBlockMeleeInVehicle = NCD_ConfigFileHasKey("ExpansionAI_BlockMeleeWhileInVehicle");
	bool hasExpansionAIBlockContaminatedInVehicle = NCD_ConfigFileHasKey("ExpansionAI_BlockContaminatedWhileInVehicle");
	bool hasExpansionAIDoorOpenDisablesProtectionInContaminated = NCD_ConfigFileHasKey("ExpansionAI_DoorOpenDisablesProtectionInContaminated");
	bool hasExpansionAINoJumpDmg = NCD_ConfigFileHasKey("ExpansionAI_NoDamageAfterJumpFromVehicle");
	bool hasCrewCrash = NCD_ConfigFileHasKey("Vehicle_BlockCrewCrashDamage");
	bool hasCrashSounds = NCD_ConfigFileHasKey("Vehicle_EnableCrashSounds");
	bool hasProtectClothing = NCD_ConfigFileHasKey("Protect_PlayerClothingInVehicle");
	bool hasMaxSpeed = NCD_ConfigFileHasKey("Vehicle_DisableCrash_MaxSpeedKmh");
	bool hasJumpMinKmh = NCD_ConfigFileHasKey("Player_NoDamageAfterJump_MinSpeedKmh");
	bool hasJumpMaxKmh = NCD_ConfigFileHasKey("Player_NoDamageAfterJump_MaxSpeedKmh");
	bool hasJumpWindow = NCD_ConfigFileHasKey("Player_NoDamageAfterJump_WindowMS");

	NCD_Config defaults = new NCD_Config();
	bool changed = false;

	if (!hasMaxSpeed)
	{
		g_NCD_Cfg.Vehicle_DisableCrash_MaxSpeedKmh = defaults.Vehicle_DisableCrash_MaxSpeedKmh;
		changed = true;
	}
	if (!hasRedline)
	{
		g_NCD_Cfg.Vehicle_DisableRedlineDamage = defaults.Vehicle_DisableRedlineDamage;
		changed = true;
	}
	if (!hasNoDmgZeds)
	{
		g_NCD_Cfg.Vehicle_NoDamageToZombies = defaults.Vehicle_NoDamageToZombies;
		changed = true;
	}
	if (!hasNoDmgAnimals)
	{
		g_NCD_Cfg.Vehicle_NoDamageToAnimals = defaults.Vehicle_NoDamageToAnimals;
		changed = true;
	}
	if (!hasNoDmgPlayers)
	{
		g_NCD_Cfg.Vehicle_NoDamageToPlayers = defaults.Vehicle_NoDamageToPlayers;
		changed = true;
	}
	if (!hasNoDmgExpansionAI)
	{
		g_NCD_Cfg.Vehicle_NoDamageToExpansionAI = defaults.Vehicle_NoDamageToExpansionAI;
		changed = true;
	}
	if (!hasAutoFlip)
	{
		g_NCD_Cfg.Vehicle_AutoFlip = defaults.Vehicle_AutoFlip;
		changed = true;
	}
	if (!hasNoJumpDmg)
	{
		g_NCD_Cfg.Player_NoDamageAfterJumpFromVehicle = defaults.Player_NoDamageAfterJumpFromVehicle;
		changed = true;
	}
	if (!hasExpansionAINoDmgInVehicle)
	{
		g_NCD_Cfg.ExpansionAI_NoDamageWhileInVehicle = defaults.ExpansionAI_NoDamageWhileInVehicle;
		changed = true;
	}
	if (!hasExpansionAIBlockAllInVehicle)
	{
		g_NCD_Cfg.ExpansionAI_BlockAllDamageWhileInVehicle = defaults.ExpansionAI_BlockAllDamageWhileInVehicle;
		changed = true;
	}
	if (!hasExpansionAIBlockBulletsInVehicle)
	{
		g_NCD_Cfg.ExpansionAI_BlockBulletsWhileInVehicle = defaults.ExpansionAI_BlockBulletsWhileInVehicle;
		changed = true;
	}
	if (!hasExpansionAIBlockExplosionsInVehicle)
	{
		g_NCD_Cfg.ExpansionAI_BlockExplosionsWhileInVehicle = defaults.ExpansionAI_BlockExplosionsWhileInVehicle;
		changed = true;
	}
	if (!hasExpansionAIBlockMeleeInVehicle)
	{
		g_NCD_Cfg.ExpansionAI_BlockMeleeWhileInVehicle = defaults.ExpansionAI_BlockMeleeWhileInVehicle;
		changed = true;
	}
	if (!hasExpansionAIBlockContaminatedInVehicle)
	{
		g_NCD_Cfg.ExpansionAI_BlockContaminatedWhileInVehicle = defaults.ExpansionAI_BlockContaminatedWhileInVehicle;
		changed = true;
	}
	if (!hasExpansionAIDoorOpenDisablesProtectionInContaminated)
	{
		g_NCD_Cfg.ExpansionAI_DoorOpenDisablesProtectionInContaminated = defaults.ExpansionAI_DoorOpenDisablesProtectionInContaminated;
		changed = true;
	}
	if (!hasExpansionAINoJumpDmg)
	{
		g_NCD_Cfg.ExpansionAI_NoDamageAfterJumpFromVehicle = defaults.ExpansionAI_NoDamageAfterJumpFromVehicle;
		changed = true;
	}
	if (!hasCrewCrash)
	{
		g_NCD_Cfg.Vehicle_BlockCrewCrashDamage = defaults.Vehicle_BlockCrewCrashDamage;
		changed = true;
	}
	if (!hasCrashSounds)
	{
		g_NCD_Cfg.Vehicle_EnableCrashSounds = defaults.Vehicle_EnableCrashSounds;
		changed = true;
	}
	if (!hasProtectClothing)
	{
		g_NCD_Cfg.Protect_PlayerClothingInVehicle = defaults.Protect_PlayerClothingInVehicle;
		changed = true;
	}
	if (!hasMaxSpeed)
	{
		g_NCD_Cfg.Vehicle_DisableCrash_MaxSpeedKmh = defaults.Vehicle_DisableCrash_MaxSpeedKmh;
		changed = true;
	}
	if (!hasJumpMinKmh)
	{
		g_NCD_Cfg.Player_NoDamageAfterJump_MinSpeedKmh = defaults.Player_NoDamageAfterJump_MinSpeedKmh;
		changed = true;
	}
	if (!hasJumpMaxKmh)
	{
		g_NCD_Cfg.Player_NoDamageAfterJump_MaxSpeedKmh = -1.0;
		changed = true;
	}
	if (!hasJumpWindow)
	{
		g_NCD_Cfg.Player_NoDamageAfterJump_WindowMS = 1500;
		changed = true;
	}

	g_NCD_Cfg.Vehicle_BlockBullets = NCD_NormalizeBool01(g_NCD_Cfg.Vehicle_BlockBullets, defaults.Vehicle_BlockBullets);
	g_NCD_Cfg.Vehicle_BlockExplosions = NCD_NormalizeBool01(g_NCD_Cfg.Vehicle_BlockExplosions, defaults.Vehicle_BlockExplosions);
	g_NCD_Cfg.Vehicle_BlockMelee = NCD_NormalizeBool01(g_NCD_Cfg.Vehicle_BlockMelee, defaults.Vehicle_BlockMelee);
	g_NCD_Cfg.Vehicle_AllowGlassDamage = NCD_NormalizeBool01(g_NCD_Cfg.Vehicle_AllowGlassDamage, defaults.Vehicle_AllowGlassDamage);
	g_NCD_Cfg.Vehicle_DisableCrashDamage = NCD_NormalizeBool01(g_NCD_Cfg.Vehicle_DisableCrashDamage, defaults.Vehicle_DisableCrashDamage);
	g_NCD_Cfg.Vehicle_DisableWaterDamage = NCD_NormalizeBool01(g_NCD_Cfg.Vehicle_DisableWaterDamage, defaults.Vehicle_DisableWaterDamage);
	g_NCD_Cfg.Vehicle_BlockContaminated = NCD_NormalizeBool01(g_NCD_Cfg.Vehicle_BlockContaminated, defaults.Vehicle_BlockContaminated);
	g_NCD_Cfg.Vehicle_DisableRedlineDamage = NCD_NormalizeBool01(g_NCD_Cfg.Vehicle_DisableRedlineDamage, defaults.Vehicle_DisableRedlineDamage);
	g_NCD_Cfg.Vehicle_BlockCrewCrashDamage = NCD_NormalizeBool01(g_NCD_Cfg.Vehicle_BlockCrewCrashDamage, defaults.Vehicle_BlockCrewCrashDamage);
	g_NCD_Cfg.Vehicle_EnableCrashSounds = NCD_NormalizeBool01(g_NCD_Cfg.Vehicle_EnableCrashSounds, defaults.Vehicle_EnableCrashSounds);
	g_NCD_Cfg.Vehicle_NoDamageToZombies = NCD_NormalizeBool01(g_NCD_Cfg.Vehicle_NoDamageToZombies, defaults.Vehicle_NoDamageToZombies);
	g_NCD_Cfg.Vehicle_NoDamageToAnimals = NCD_NormalizeBool01(g_NCD_Cfg.Vehicle_NoDamageToAnimals, defaults.Vehicle_NoDamageToAnimals);
	g_NCD_Cfg.Vehicle_NoDamageToPlayers = NCD_NormalizeBool01(g_NCD_Cfg.Vehicle_NoDamageToPlayers, defaults.Vehicle_NoDamageToPlayers);
	g_NCD_Cfg.Vehicle_NoDamageToExpansionAI = NCD_NormalizeBool01(g_NCD_Cfg.Vehicle_NoDamageToExpansionAI, defaults.Vehicle_NoDamageToExpansionAI);
	g_NCD_Cfg.Vehicle_AutoFlip = NCD_NormalizeBool01(g_NCD_Cfg.Vehicle_AutoFlip, defaults.Vehicle_AutoFlip);
	g_NCD_Cfg.Vehicle_AutoFlipWithButton = NCD_NormalizeBool01(g_NCD_Cfg.Vehicle_AutoFlipWithButton, defaults.Vehicle_AutoFlipWithButton);

	g_NCD_Cfg.Player_BlockContaminatedWhileInVehicle = NCD_NormalizeBool01(g_NCD_Cfg.Player_BlockContaminatedWhileInVehicle, defaults.Player_BlockContaminatedWhileInVehicle);
	g_NCD_Cfg.Player_DoorOpenDisablesProtectionInContaminated = NCD_NormalizeBool01(g_NCD_Cfg.Player_DoorOpenDisablesProtectionInContaminated, defaults.Player_DoorOpenDisablesProtectionInContaminated);
	g_NCD_Cfg.Player_NoDamageWhileInVehicle = NCD_NormalizeBool01(g_NCD_Cfg.Player_NoDamageWhileInVehicle, defaults.Player_NoDamageWhileInVehicle);
	g_NCD_Cfg.Player_BlockAllDamageWhileInVehicle = NCD_NormalizeBool01(g_NCD_Cfg.Player_BlockAllDamageWhileInVehicle, defaults.Player_BlockAllDamageWhileInVehicle);
	g_NCD_Cfg.Player_BlockBulletsWhileInVehicle = NCD_NormalizeBool01(g_NCD_Cfg.Player_BlockBulletsWhileInVehicle, defaults.Player_BlockBulletsWhileInVehicle);
	g_NCD_Cfg.Player_BlockExplosionsWhileInVehicle = NCD_NormalizeBool01(g_NCD_Cfg.Player_BlockExplosionsWhileInVehicle, defaults.Player_BlockExplosionsWhileInVehicle);
	g_NCD_Cfg.Player_BlockMeleeWhileInVehicle = NCD_NormalizeBool01(g_NCD_Cfg.Player_BlockMeleeWhileInVehicle, defaults.Player_BlockMeleeWhileInVehicle);
	g_NCD_Cfg.Player_NoDamageAfterJumpFromVehicle = NCD_NormalizeBool01(g_NCD_Cfg.Player_NoDamageAfterJumpFromVehicle, defaults.Player_NoDamageAfterJumpFromVehicle);
	
	if (g_NCD_Cfg.Player_NoDamageAfterJump_MinSpeedKmh < 0)
	{
		g_NCD_Cfg.Player_NoDamageAfterJump_MinSpeedKmh = 8.0;
		changed = true;
	}

	if (g_NCD_Cfg.Player_NoDamageAfterJump_MaxSpeedKmh < -1.0)
	{
		g_NCD_Cfg.Player_NoDamageAfterJump_MaxSpeedKmh = -1.0;
		changed = true;
	}

	if (g_NCD_Cfg.Vehicle_DisableCrash_MaxSpeedKmh < -1.0)
	{
		g_NCD_Cfg.Vehicle_DisableCrash_MaxSpeedKmh = -1.0;
		changed = true;
	}

	if (g_NCD_Cfg.Player_NoDamageAfterJump_WindowMS < 0)
	{
		g_NCD_Cfg.Player_NoDamageAfterJump_WindowMS = 0;
		changed = true;
	}
	else if (g_NCD_Cfg.Player_NoDamageAfterJump_WindowMS > 10000)
	{
		g_NCD_Cfg.Player_NoDamageAfterJump_WindowMS = 10000;
		changed = true;
	}

	if (g_NCD_Cfg.Protect_PlayerClothingInVehicle < 0 || g_NCD_Cfg.Protect_PlayerClothingInVehicle > 1)
	{
		g_NCD_Cfg.Protect_PlayerClothingInVehicle = 1;
		changed = true;
	}

	g_NCD_Cfg.Protect_AttachmentsOnVehicle = NCD_NormalizeBool01(g_NCD_Cfg.Protect_AttachmentsOnVehicle, defaults.Protect_AttachmentsOnVehicle);
	g_NCD_Cfg.EnableVehicleOverrides = NCD_NormalizeBool01(g_NCD_Cfg.EnableVehicleOverrides, defaults.EnableVehicleOverrides);
	g_NCD_Cfg.AutoExtendVehicleOverrides = NCD_NormalizeBool01(g_NCD_Cfg.AutoExtendVehicleOverrides, defaults.AutoExtendVehicleOverrides);

	g_NCD_Cfg.ExpansionAI_NoDamageWhileInVehicle = NCD_NormalizeBool01(g_NCD_Cfg.ExpansionAI_NoDamageWhileInVehicle, defaults.ExpansionAI_NoDamageWhileInVehicle);
	g_NCD_Cfg.ExpansionAI_BlockAllDamageWhileInVehicle = NCD_NormalizeBool01(g_NCD_Cfg.ExpansionAI_BlockAllDamageWhileInVehicle, defaults.ExpansionAI_BlockAllDamageWhileInVehicle);
	g_NCD_Cfg.ExpansionAI_BlockBulletsWhileInVehicle = NCD_NormalizeBool01(g_NCD_Cfg.ExpansionAI_BlockBulletsWhileInVehicle, defaults.ExpansionAI_BlockBulletsWhileInVehicle);
	g_NCD_Cfg.ExpansionAI_BlockExplosionsWhileInVehicle = NCD_NormalizeBool01(g_NCD_Cfg.ExpansionAI_BlockExplosionsWhileInVehicle, defaults.ExpansionAI_BlockExplosionsWhileInVehicle);
	g_NCD_Cfg.ExpansionAI_BlockMeleeWhileInVehicle = NCD_NormalizeBool01(g_NCD_Cfg.ExpansionAI_BlockMeleeWhileInVehicle, defaults.ExpansionAI_BlockMeleeWhileInVehicle);
	g_NCD_Cfg.ExpansionAI_BlockContaminatedWhileInVehicle = NCD_NormalizeBool01(g_NCD_Cfg.ExpansionAI_BlockContaminatedWhileInVehicle, defaults.ExpansionAI_BlockContaminatedWhileInVehicle);
	g_NCD_Cfg.ExpansionAI_DoorOpenDisablesProtectionInContaminated = NCD_NormalizeBool01(g_NCD_Cfg.ExpansionAI_DoorOpenDisablesProtectionInContaminated, defaults.ExpansionAI_DoorOpenDisablesProtectionInContaminated);
	g_NCD_Cfg.ExpansionAI_NoDamageAfterJumpFromVehicle = NCD_NormalizeBool01(g_NCD_Cfg.ExpansionAI_NoDamageAfterJumpFromVehicle, defaults.ExpansionAI_NoDamageAfterJumpFromVehicle);

	if (!g_NCD_Cfg.VehicleOverrides)
		return changed;

	for (int i = 0; i < g_NCD_Cfg.VehicleOverrides.Count(); i++)
	{
		NCD_VehicleOverride ov = g_NCD_Cfg.VehicleOverrides[i];
		if (!ov)
			continue;

		if (!hasRedline) ov.Vehicle_DisableRedlineDamage = -1;
		if (!hasNoDmgZeds) ov.Vehicle_NoDamageToZombies = -1;
		if (!hasNoDmgAnimals) ov.Vehicle_NoDamageToAnimals = -1;
		if (!hasNoDmgPlayers) ov.Vehicle_NoDamageToPlayers = -1;
		if (!hasNoDmgExpansionAI) ov.Vehicle_NoDamageToExpansionAI = -1;
		if (!hasAutoFlip) ov.Vehicle_AutoFlip = -1;
		if (!hasExpansionAINoDmgInVehicle) ov.ExpansionAI_NoDamageWhileInVehicle = -1;
		if (!hasExpansionAIBlockAllInVehicle) ov.ExpansionAI_BlockAllDamageWhileInVehicle = -1;
		if (!hasExpansionAIBlockBulletsInVehicle) ov.ExpansionAI_BlockBulletsWhileInVehicle = -1;
		if (!hasExpansionAIBlockExplosionsInVehicle) ov.ExpansionAI_BlockExplosionsWhileInVehicle = -1;
		if (!hasExpansionAIBlockMeleeInVehicle) ov.ExpansionAI_BlockMeleeWhileInVehicle = -1;
		if (!hasExpansionAIBlockContaminatedInVehicle) ov.ExpansionAI_BlockContaminatedWhileInVehicle = -1;
		if (!hasExpansionAIDoorOpenDisablesProtectionInContaminated) ov.ExpansionAI_DoorOpenDisablesProtectionInContaminated = -1;
		if (!hasExpansionAINoJumpDmg) ov.ExpansionAI_NoDamageAfterJumpFromVehicle = -1;
		if (!hasCrewCrash) ov.Vehicle_BlockCrewCrashDamage = -1;
		if (!hasCrashSounds) ov.Vehicle_EnableCrashSounds = -1;
		if (!hasMaxSpeed) ov.Vehicle_DisableCrash_MaxSpeedKmh = -1.0;
		if (!hasProtectClothing) ov.Protect_PlayerClothingInVehicle = -1;

		ov.Vehicle_BlockBullets = NCD_NormalizeTriState(ov.Vehicle_BlockBullets, -1);
		ov.Vehicle_BlockExplosions = NCD_NormalizeTriState(ov.Vehicle_BlockExplosions, -1);
		ov.Vehicle_BlockMelee = NCD_NormalizeTriState(ov.Vehicle_BlockMelee, -1);
		ov.Vehicle_AllowGlassDamage = NCD_NormalizeTriState(ov.Vehicle_AllowGlassDamage, -1);
		ov.Vehicle_DisableCrashDamage = NCD_NormalizeTriState(ov.Vehicle_DisableCrashDamage, -1);
		ov.Vehicle_DisableWaterDamage = NCD_NormalizeTriState(ov.Vehicle_DisableWaterDamage, -1);
		ov.Vehicle_BlockContaminated = NCD_NormalizeTriState(ov.Vehicle_BlockContaminated, -1);
		ov.Vehicle_DisableRedlineDamage = NCD_NormalizeTriState(ov.Vehicle_DisableRedlineDamage, -1);
		ov.Vehicle_BlockCrewCrashDamage = NCD_NormalizeTriState(ov.Vehicle_BlockCrewCrashDamage, -1);
		ov.Vehicle_EnableCrashSounds = NCD_NormalizeTriState(ov.Vehicle_EnableCrashSounds, -1);
		ov.Vehicle_NoDamageToZombies = NCD_NormalizeTriState(ov.Vehicle_NoDamageToZombies, -1);
		ov.Vehicle_NoDamageToAnimals = NCD_NormalizeTriState(ov.Vehicle_NoDamageToAnimals, -1);
		ov.Vehicle_NoDamageToPlayers = NCD_NormalizeTriState(ov.Vehicle_NoDamageToPlayers, -1);
		ov.Vehicle_NoDamageToExpansionAI = NCD_NormalizeTriState(ov.Vehicle_NoDamageToExpansionAI, -1);
		ov.Vehicle_AutoFlip = NCD_NormalizeTriState(ov.Vehicle_AutoFlip, -1);
		if (!hasMaxSpeed) ov.Vehicle_DisableCrash_MaxSpeedKmh = -1.0;
		if (ov.Vehicle_DisableCrash_MaxSpeedKmh < -1.0)
		{
			ov.Vehicle_DisableCrash_MaxSpeedKmh = -1.0;
			changed = true;
		}
		if (!hasProtectClothing) ov.Protect_PlayerClothingInVehicle = -1;
		if (ov.Protect_PlayerClothingInVehicle < -1 || ov.Protect_PlayerClothingInVehicle > 1)
		{
			ov.Protect_PlayerClothingInVehicle = -1;
			changed = true;
		}

		ov.Player_BlockContaminatedWhileInVehicle = NCD_NormalizeTriState(ov.Player_BlockContaminatedWhileInVehicle, -1);
		ov.Player_DoorOpenDisablesProtectionInContaminated = NCD_NormalizeTriState(ov.Player_DoorOpenDisablesProtectionInContaminated, -1);
		ov.Player_NoDamageWhileInVehicle = NCD_NormalizeTriState(ov.Player_NoDamageWhileInVehicle, -1);
		ov.Player_BlockAllDamageWhileInVehicle = NCD_NormalizeTriState(ov.Player_BlockAllDamageWhileInVehicle, -1);
		ov.Player_BlockBulletsWhileInVehicle = NCD_NormalizeTriState(ov.Player_BlockBulletsWhileInVehicle, -1);
		ov.Player_BlockExplosionsWhileInVehicle = NCD_NormalizeTriState(ov.Player_BlockExplosionsWhileInVehicle, -1);
		ov.Player_BlockMeleeWhileInVehicle = NCD_NormalizeTriState(ov.Player_BlockMeleeWhileInVehicle, -1);

		ov.Protect_AttachmentsOnVehicle = NCD_NormalizeTriState(ov.Protect_AttachmentsOnVehicle, -1);
		if (!hasProtectClothing) ov.Protect_PlayerClothingInVehicle = -1;

		ov.ExpansionAI_NoDamageWhileInVehicle = NCD_NormalizeTriState(ov.ExpansionAI_NoDamageWhileInVehicle, -1);
		ov.ExpansionAI_BlockAllDamageWhileInVehicle = NCD_NormalizeTriState(ov.ExpansionAI_BlockAllDamageWhileInVehicle, -1);
		ov.ExpansionAI_BlockBulletsWhileInVehicle = NCD_NormalizeTriState(ov.ExpansionAI_BlockBulletsWhileInVehicle, -1);
		ov.ExpansionAI_BlockExplosionsWhileInVehicle = NCD_NormalizeTriState(ov.ExpansionAI_BlockExplosionsWhileInVehicle, -1);
		ov.ExpansionAI_BlockMeleeWhileInVehicle = NCD_NormalizeTriState(ov.ExpansionAI_BlockMeleeWhileInVehicle, -1);
		ov.ExpansionAI_BlockContaminatedWhileInVehicle = NCD_NormalizeTriState(ov.ExpansionAI_BlockContaminatedWhileInVehicle, -1);
		ov.ExpansionAI_DoorOpenDisablesProtectionInContaminated = NCD_NormalizeTriState(ov.ExpansionAI_DoorOpenDisablesProtectionInContaminated, -1);
		ov.ExpansionAI_NoDamageAfterJumpFromVehicle = NCD_NormalizeTriState(ov.ExpansionAI_NoDamageAfterJumpFromVehicle, -1);
		
		if (ov.Vehicle_DisableCrash_MaxSpeedKmh < -1.0) ov.Vehicle_DisableCrash_MaxSpeedKmh = -1.0;
		if (ov.Protect_PlayerClothingInVehicle < -1 || ov.Protect_PlayerClothingInVehicle > 1) ov.Protect_PlayerClothingInVehicle = -1;
	}

	return changed;
}

void NCD_EnsureConfig()
{
	if (!g_NCD_CfgInit)
	{
		g_NCD_Cfg = new NCD_Config();
		g_NCD_CfgInit = true;
	}
}

int NCD_ResolveInt(int overrideVal, int globalVal)
{
	if (overrideVal == -1) return globalVal;
	return overrideVal;
}

NCD_VehicleOverride NCD_FindVehicleOverride(string className)
{
	if (!g_NCD_Cfg || !g_NCD_Cfg.VehicleOverrides) return null;

	if (g_NCD_OverrideMap)
	{
		NCD_VehicleOverride ov;
		if (g_NCD_OverrideMap.Find(className, ov))
			return ov;
	}

	for (int i = 0; i < g_NCD_Cfg.VehicleOverrides.Count(); i++)
	{
		NCD_VehicleOverride o = g_NCD_Cfg.VehicleOverrides[i];
		if (o && o.ClassName == className)
			return o;
	}
	return null;
}

void NCD_RebuildOverrideMap()
{
	if (!g_NCD_Cfg || !g_NCD_Cfg.VehicleOverrides)
		return;

	if (!g_NCD_OverrideMap)
		g_NCD_OverrideMap = new map<string, ref NCD_VehicleOverride>();
	else
		g_NCD_OverrideMap.Clear();

	if (!g_NCD_ResolvedRulesMap)
		g_NCD_ResolvedRulesMap = new map<string, ref NCD_ResolvedVehicleRules>();
	else
		g_NCD_ResolvedRulesMap.Clear();

	g_NCD_HasToxicOverrides = false;

	for (int i = 0; i < g_NCD_Cfg.VehicleOverrides.Count(); i++)
	{
		NCD_VehicleOverride o = g_NCD_Cfg.VehicleOverrides[i];
		if (!o || o.ClassName == "")
			continue;

		bool noOp = NCD_IsOverrideNoOp(o);

		NCD_VehicleOverride existing;
		if (g_NCD_OverrideMap.Find(o.ClassName, existing))
		{
			if (NCD_IsOverrideNoOp(existing) && !noOp)
				g_NCD_OverrideMap.Set(o.ClassName, o);
		}
		else
		{
			g_NCD_OverrideMap.Set(o.ClassName, o);
		}

		if (!noOp && (o.Vehicle_BlockContaminated == 1 || o.Player_BlockContaminatedWhileInVehicle == 1 || o.ExpansionAI_BlockContaminatedWhileInVehicle == 1))
			g_NCD_HasToxicOverrides = true;
	}
}

bool NCD_CompactVehicleOverrides()
{
	if (!g_Game || !g_Game.IsServer())
		return false;

	if (!g_NCD_Cfg || !g_NCD_Cfg.VehicleOverrides)
		return false;

	bool dropNoOps = (g_NCD_Cfg.AutoExtendVehicleOverrides == 0);
	bool changed = false;

	ref array<ref NCD_VehicleOverride> compacted = new array<ref NCD_VehicleOverride>();
	ref map<string, int> classToIndex = new map<string, int>();

	for (int i = 0; i < g_NCD_Cfg.VehicleOverrides.Count(); i++)
	{
		NCD_VehicleOverride o = g_NCD_Cfg.VehicleOverrides[i];
		if (!o || o.ClassName == "")
		{
			changed = true;
			continue;
		}

		if (!g_Game.ConfigIsExisting("CfgVehicles " + o.ClassName))
		{
			changed = true;
			continue;
		}

		bool noOp = NCD_IsOverrideNoOp(o);
		if (dropNoOps && noOp)
		{
			changed = true;
			continue;
		}

		int existingIndex = -1;
		if (classToIndex.Find(o.ClassName, existingIndex))
		{
			NCD_VehicleOverride existing = compacted[existingIndex];
			bool existingNoOp = NCD_IsOverrideNoOp(existing);

			if (existingNoOp && !noOp)
				compacted[existingIndex] = o;

			changed = true;
			continue;
		}

		classToIndex.Set(o.ClassName, compacted.Count());
		compacted.Insert(o);
	}

	if (!changed && compacted.Count() == g_NCD_Cfg.VehicleOverrides.Count())
		return false;

	g_NCD_Cfg.VehicleOverrides = compacted;
	return true;
}

bool NCD_IsAnyToxicProtectionEnabled()
{
	NCD_Config cfg = NCD_Cfg();
	if (!cfg)
		return false;

	if (cfg.Vehicle_BlockContaminated == 1 || cfg.Player_BlockContaminatedWhileInVehicle == 1 || cfg.ExpansionAI_BlockContaminatedWhileInVehicle == 1)
		return true;

	if (cfg.EnableVehicleOverrides == 1 && g_NCD_HasToxicOverrides)
		return true;

	return false;
}

void NCD_LogConfigLoaded(bool created)
{
	string msg = "[NoCarDamage] Config ";
	if (created) msg = msg + "CREATED (defaults)";
	else msg = msg + "LOADED";
	msg = msg + " path=" + NCD_CFG_PATH;
	Print(msg);

	if (!g_NCD_Cfg) return;

	string v = "[NoCarDamage] Vehicle: bullets=" + g_NCD_Cfg.Vehicle_BlockBullets.ToString();
	v += " explosions=" + g_NCD_Cfg.Vehicle_BlockExplosions.ToString();
	v += " melee=" + g_NCD_Cfg.Vehicle_BlockMelee.ToString();
	v += " glassDamage=" + g_NCD_Cfg.Vehicle_AllowGlassDamage.ToString();
	v += " crashDisabled=" + g_NCD_Cfg.Vehicle_DisableCrashDamage.ToString();
	v += " crashMaxKmh=" + g_NCD_Cfg.Vehicle_DisableCrash_MaxSpeedKmh.ToString();
	v += " waterDisabled=" + g_NCD_Cfg.Vehicle_DisableWaterDamage.ToString();
	v += " redlineDisabled=" + g_NCD_Cfg.Vehicle_DisableRedlineDamage.ToString();
	v += " crewCrashBlock=" + g_NCD_Cfg.Vehicle_BlockCrewCrashDamage.ToString();
	v += " crashSounds=" + g_NCD_Cfg.Vehicle_EnableCrashSounds.ToString();
	v += " autoFlip=" + g_NCD_Cfg.Vehicle_AutoFlip.ToString();
	v += " autoFlipButton=" + g_NCD_Cfg.Vehicle_AutoFlipWithButton.ToString();
	v += " noDmgZeds=" + g_NCD_Cfg.Vehicle_NoDamageToZombies.ToString();
	v += " noDmgAnimals=" + g_NCD_Cfg.Vehicle_NoDamageToAnimals.ToString();
	v += " noDmgPlayers=" + g_NCD_Cfg.Vehicle_NoDamageToPlayers.ToString();
	v += " noDmgExpansionAI=" + g_NCD_Cfg.Vehicle_NoDamageToExpansionAI.ToString();
	v += " toxic=" + g_NCD_Cfg.Vehicle_BlockContaminated.ToString();
	v += " protectClothing=" + g_NCD_Cfg.Protect_PlayerClothingInVehicle.ToString();
	Print(v);

	string p = "[NoCarDamage] Player in Vehicle: enabled=" + g_NCD_Cfg.Player_NoDamageWhileInVehicle.ToString();
	p += " blockAll=" + g_NCD_Cfg.Player_BlockAllDamageWhileInVehicle.ToString();
	p += " bullets=" + g_NCD_Cfg.Player_BlockBulletsWhileInVehicle.ToString();
	p += " explosions=" + g_NCD_Cfg.Player_BlockExplosionsWhileInVehicle.ToString();
	p += " melee=" + g_NCD_Cfg.Player_BlockMeleeWhileInVehicle.ToString();
	p += " toxic=" + g_NCD_Cfg.Player_BlockContaminatedWhileInVehicle.ToString();
	p += " doorOpenDisablesInGas=" + g_NCD_Cfg.Player_DoorOpenDisablesProtectionInContaminated.ToString();
	p += " noJumpDmg=" + g_NCD_Cfg.Player_NoDamageAfterJumpFromVehicle.ToString();
	p += " noJumpMinKmh=" + g_NCD_Cfg.Player_NoDamageAfterJump_MinSpeedKmh.ToString();
	p += " noJumpMaxKmh=" + g_NCD_Cfg.Player_NoDamageAfterJump_MaxSpeedKmh.ToString();
	p += " noJumpWindowMS=" + g_NCD_Cfg.Player_NoDamageAfterJump_WindowMS.ToString();
	p += " protectClothing=" + g_NCD_Cfg.Protect_PlayerClothingInVehicle.ToString();
	Print(p);

	string a = "[NoCarDamage] ExpansionAI in Vehicle: enabled=" + g_NCD_Cfg.ExpansionAI_NoDamageWhileInVehicle.ToString();
	a += " blockAll=" + g_NCD_Cfg.ExpansionAI_BlockAllDamageWhileInVehicle.ToString();
	a += " bullets=" + g_NCD_Cfg.ExpansionAI_BlockBulletsWhileInVehicle.ToString();
	a += " explosions=" + g_NCD_Cfg.ExpansionAI_BlockExplosionsWhileInVehicle.ToString();
	a += " melee=" + g_NCD_Cfg.ExpansionAI_BlockMeleeWhileInVehicle.ToString();
	a += " toxic=" + g_NCD_Cfg.ExpansionAI_BlockContaminatedWhileInVehicle.ToString();
	a += " doorOpenDisablesInGas=" + g_NCD_Cfg.ExpansionAI_DoorOpenDisablesProtectionInContaminated.ToString();
	a += " noJumpDmg=" + g_NCD_Cfg.ExpansionAI_NoDamageAfterJumpFromVehicle.ToString();
	Print(a);

	Print("[NoCarDamage] VehicleOverrides count=" + g_NCD_Cfg.VehicleOverrides.Count().ToString() + " autoExtend=" + g_NCD_Cfg.AutoExtendVehicleOverrides.ToString());
}

void NCD_LoadConfigFromDisk()
{
	NCD_EnsureConfig();

	if (g_NCD_CfgDiskLoaded)
		return;

	if (!g_Game || !g_Game.IsServer())
		return;

	if (!FileExist(NCD_CFG_DIR))
		MakeDirectory(NCD_CFG_DIR);

	bool created = false;

	if (FileExist(NCD_CFG_PATH))
	{
		JsonFileLoader<NCD_Config>.JsonLoadFile(NCD_CFG_PATH, g_NCD_Cfg);
	}
	else
	{
		created = true;
		JsonFileLoader<NCD_Config>.JsonSaveFile(NCD_CFG_PATH, g_NCD_Cfg);
	}

	if (!g_NCD_Cfg.VehicleOverrides)
		g_NCD_Cfg.VehicleOverrides = new array<ref NCD_VehicleOverride>;

	bool backfilled = false;
	if (!created)
		backfilled = NCD_BackfillMissingConfigKeys();

	bool upgraded = NCD_MigrateConfig();
	bool compacted = NCD_CompactVehicleOverrides();
	if (upgraded || backfilled || compacted)
	{
		JsonFileLoader<NCD_Config>.JsonSaveFile(NCD_CFG_PATH, g_NCD_Cfg);
		if (upgraded)
			Print("[NoCarDamage] Config upgraded to Version=" + g_NCD_Cfg.Version.ToString() + " -> saved config");
		if (backfilled)
			Print("[NoCarDamage] Config backfilled missing keys -> saved config");
		if (compacted)
			Print("[NoCarDamage] Config compacted duplicate/empty no-op vehicle overrides -> saved config");
	}

	NCD_RebuildOverrideMap();

	g_NCD_CfgDiskLoaded = true;
	NCD_LogConfigLoaded(created);
}

NCD_Config NCD_Cfg()
{
	NCD_EnsureConfig();
	if (g_Game && g_Game.IsServer() && !g_NCD_CfgDiskLoaded)
		NCD_LoadConfigFromDisk();
	return g_NCD_Cfg;
}

NCD_ResolvedVehicleRules NCD_GetResolvedVehicleRules(string vt)
{
	if (vt == "")
		return null;

	if (!g_NCD_ResolvedRulesMap)
		g_NCD_ResolvedRulesMap = new map<string, ref NCD_ResolvedVehicleRules>();

	NCD_ResolvedVehicleRules cached;
	if (g_NCD_ResolvedRulesMap.Find(vt, cached))
		return cached;

	NCD_Config cfg = NCD_Cfg();
	if (!cfg)
		return null;

	NCD_VehicleOverride ov = null;
	if (cfg.EnableVehicleOverrides == 1)
		ov = NCD_FindVehicleOverride(vt);

	NCD_ResolvedVehicleRules rules = new NCD_ResolvedVehicleRules();

	if (ov)
	{
		rules.Vehicle_BlockBullets = NCD_ResolveInt(ov.Vehicle_BlockBullets, cfg.Vehicle_BlockBullets);
		rules.Vehicle_BlockExplosions = NCD_ResolveInt(ov.Vehicle_BlockExplosions, cfg.Vehicle_BlockExplosions);
		rules.Vehicle_BlockMelee = NCD_ResolveInt(ov.Vehicle_BlockMelee, cfg.Vehicle_BlockMelee);
		rules.Vehicle_AllowGlassDamage = NCD_ResolveInt(ov.Vehicle_AllowGlassDamage, cfg.Vehicle_AllowGlassDamage);
		rules.Vehicle_DisableCrashDamage = NCD_ResolveInt(ov.Vehicle_DisableCrashDamage, cfg.Vehicle_DisableCrashDamage);
		rules.Vehicle_DisableWaterDamage = NCD_ResolveInt(ov.Vehicle_DisableWaterDamage, cfg.Vehicle_DisableWaterDamage);
		rules.Vehicle_BlockContaminated = NCD_ResolveInt(ov.Vehicle_BlockContaminated, cfg.Vehicle_BlockContaminated);
		rules.Vehicle_DisableRedlineDamage = NCD_ResolveInt(ov.Vehicle_DisableRedlineDamage, cfg.Vehicle_DisableRedlineDamage);
		rules.Vehicle_BlockCrewCrashDamage = NCD_ResolveInt(ov.Vehicle_BlockCrewCrashDamage, cfg.Vehicle_BlockCrewCrashDamage);
		rules.Vehicle_EnableCrashSounds = NCD_ResolveInt(ov.Vehicle_EnableCrashSounds, cfg.Vehicle_EnableCrashSounds);
		rules.Vehicle_NoDamageToZombies = NCD_ResolveInt(ov.Vehicle_NoDamageToZombies, cfg.Vehicle_NoDamageToZombies);
		rules.Vehicle_NoDamageToAnimals = NCD_ResolveInt(ov.Vehicle_NoDamageToAnimals, cfg.Vehicle_NoDamageToAnimals);
		rules.Vehicle_NoDamageToPlayers = NCD_ResolveInt(ov.Vehicle_NoDamageToPlayers, cfg.Vehicle_NoDamageToPlayers);
		rules.Vehicle_NoDamageToExpansionAI = NCD_ResolveInt(ov.Vehicle_NoDamageToExpansionAI, cfg.Vehicle_NoDamageToExpansionAI);
		rules.Vehicle_AutoFlip = NCD_ResolveInt(ov.Vehicle_AutoFlip, cfg.Vehicle_AutoFlip);
		if (ov.Vehicle_DisableCrash_MaxSpeedKmh != -1.0)
			rules.Vehicle_DisableCrash_MaxSpeedKmh = ov.Vehicle_DisableCrash_MaxSpeedKmh;
		else
			rules.Vehicle_DisableCrash_MaxSpeedKmh = cfg.Vehicle_DisableCrash_MaxSpeedKmh;

		rules.Player_NoDamageWhileInVehicle = NCD_ResolveInt(ov.Player_NoDamageWhileInVehicle, cfg.Player_NoDamageWhileInVehicle);
		rules.Player_BlockAllDamageWhileInVehicle = NCD_ResolveInt(ov.Player_BlockAllDamageWhileInVehicle, cfg.Player_BlockAllDamageWhileInVehicle);
		rules.Player_BlockBulletsWhileInVehicle = NCD_ResolveInt(ov.Player_BlockBulletsWhileInVehicle, cfg.Player_BlockBulletsWhileInVehicle);
		rules.Player_BlockExplosionsWhileInVehicle = NCD_ResolveInt(ov.Player_BlockExplosionsWhileInVehicle, cfg.Player_BlockExplosionsWhileInVehicle);
		rules.Player_BlockMeleeWhileInVehicle = NCD_ResolveInt(ov.Player_BlockMeleeWhileInVehicle, cfg.Player_BlockMeleeWhileInVehicle);
		rules.Player_BlockContaminatedWhileInVehicle = NCD_ResolveInt(ov.Player_BlockContaminatedWhileInVehicle, cfg.Player_BlockContaminatedWhileInVehicle);
		rules.Player_DoorOpenDisablesProtectionInContaminated = NCD_ResolveInt(ov.Player_DoorOpenDisablesProtectionInContaminated, cfg.Player_DoorOpenDisablesProtectionInContaminated);

		rules.ExpansionAI_NoDamageWhileInVehicle = NCD_ResolveInt(ov.ExpansionAI_NoDamageWhileInVehicle, cfg.ExpansionAI_NoDamageWhileInVehicle);
		rules.ExpansionAI_BlockAllDamageWhileInVehicle = NCD_ResolveInt(ov.ExpansionAI_BlockAllDamageWhileInVehicle, cfg.ExpansionAI_BlockAllDamageWhileInVehicle);
		rules.ExpansionAI_BlockBulletsWhileInVehicle = NCD_ResolveInt(ov.ExpansionAI_BlockBulletsWhileInVehicle, cfg.ExpansionAI_BlockBulletsWhileInVehicle);
		rules.ExpansionAI_BlockExplosionsWhileInVehicle = NCD_ResolveInt(ov.ExpansionAI_BlockExplosionsWhileInVehicle, cfg.ExpansionAI_BlockExplosionsWhileInVehicle);
		rules.ExpansionAI_BlockMeleeWhileInVehicle = NCD_ResolveInt(ov.ExpansionAI_BlockMeleeWhileInVehicle, cfg.ExpansionAI_BlockMeleeWhileInVehicle);
		rules.ExpansionAI_BlockContaminatedWhileInVehicle = NCD_ResolveInt(ov.ExpansionAI_BlockContaminatedWhileInVehicle, cfg.ExpansionAI_BlockContaminatedWhileInVehicle);
		rules.ExpansionAI_DoorOpenDisablesProtectionInContaminated = NCD_ResolveInt(ov.ExpansionAI_DoorOpenDisablesProtectionInContaminated, cfg.ExpansionAI_DoorOpenDisablesProtectionInContaminated);

		rules.Protect_AttachmentsOnVehicle = NCD_ResolveInt(ov.Protect_AttachmentsOnVehicle, cfg.Protect_AttachmentsOnVehicle);
		rules.Protect_PlayerClothingInVehicle = NCD_ResolveInt(ov.Protect_PlayerClothingInVehicle, cfg.Protect_PlayerClothingInVehicle);
	}
	else
	{
		rules.Vehicle_BlockBullets = cfg.Vehicle_BlockBullets;
		rules.Vehicle_BlockExplosions = cfg.Vehicle_BlockExplosions;
		rules.Vehicle_BlockMelee = cfg.Vehicle_BlockMelee;
		rules.Vehicle_AllowGlassDamage = cfg.Vehicle_AllowGlassDamage;
		rules.Vehicle_DisableCrashDamage = cfg.Vehicle_DisableCrashDamage;
		rules.Vehicle_DisableWaterDamage = cfg.Vehicle_DisableWaterDamage;
		rules.Vehicle_BlockContaminated = cfg.Vehicle_BlockContaminated;
		rules.Vehicle_DisableRedlineDamage = cfg.Vehicle_DisableRedlineDamage;
		rules.Vehicle_BlockCrewCrashDamage = cfg.Vehicle_BlockCrewCrashDamage;
		rules.Vehicle_EnableCrashSounds = cfg.Vehicle_EnableCrashSounds;
		rules.Vehicle_NoDamageToZombies = cfg.Vehicle_NoDamageToZombies;
		rules.Vehicle_NoDamageToAnimals = cfg.Vehicle_NoDamageToAnimals;
		rules.Vehicle_NoDamageToPlayers = cfg.Vehicle_NoDamageToPlayers;
		rules.Vehicle_NoDamageToExpansionAI = cfg.Vehicle_NoDamageToExpansionAI;
		rules.Vehicle_AutoFlip = cfg.Vehicle_AutoFlip;
		rules.Vehicle_DisableCrash_MaxSpeedKmh = cfg.Vehicle_DisableCrash_MaxSpeedKmh;

		rules.Player_NoDamageWhileInVehicle = cfg.Player_NoDamageWhileInVehicle;
		rules.Player_BlockAllDamageWhileInVehicle = cfg.Player_BlockAllDamageWhileInVehicle;
		rules.Player_BlockBulletsWhileInVehicle = cfg.Player_BlockBulletsWhileInVehicle;
		rules.Player_BlockExplosionsWhileInVehicle = cfg.Player_BlockExplosionsWhileInVehicle;
		rules.Player_BlockMeleeWhileInVehicle = cfg.Player_BlockMeleeWhileInVehicle;
		rules.Player_BlockContaminatedWhileInVehicle = cfg.Player_BlockContaminatedWhileInVehicle;
		rules.Player_DoorOpenDisablesProtectionInContaminated = cfg.Player_DoorOpenDisablesProtectionInContaminated;

		rules.ExpansionAI_NoDamageWhileInVehicle = cfg.ExpansionAI_NoDamageWhileInVehicle;
		rules.ExpansionAI_BlockAllDamageWhileInVehicle = cfg.ExpansionAI_BlockAllDamageWhileInVehicle;
		rules.ExpansionAI_BlockBulletsWhileInVehicle = cfg.ExpansionAI_BlockBulletsWhileInVehicle;
		rules.ExpansionAI_BlockExplosionsWhileInVehicle = cfg.ExpansionAI_BlockExplosionsWhileInVehicle;
		rules.ExpansionAI_BlockMeleeWhileInVehicle = cfg.ExpansionAI_BlockMeleeWhileInVehicle;
		rules.ExpansionAI_BlockContaminatedWhileInVehicle = cfg.ExpansionAI_BlockContaminatedWhileInVehicle;
		rules.ExpansionAI_DoorOpenDisablesProtectionInContaminated = cfg.ExpansionAI_DoorOpenDisablesProtectionInContaminated;

		rules.Protect_AttachmentsOnVehicle = cfg.Protect_AttachmentsOnVehicle;
		rules.Protect_PlayerClothingInVehicle = cfg.Protect_PlayerClothingInVehicle;
	}

	g_NCD_ResolvedRulesMap.Set(vt, rules);
	return rules;
}

int NCD_Eff_Vehicle_BlockBullets(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Vehicle_BlockBullets;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Vehicle_BlockBullets;
}

int NCD_Eff_Vehicle_BlockExplosions(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Vehicle_BlockExplosions;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Vehicle_BlockExplosions;
}

int NCD_Eff_Vehicle_BlockMelee(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Vehicle_BlockMelee;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Vehicle_BlockMelee;
}

int NCD_Eff_Vehicle_AllowGlassDamage(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Vehicle_AllowGlassDamage;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Vehicle_AllowGlassDamage;
}

int NCD_Eff_Vehicle_DisableCrash(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Vehicle_DisableCrashDamage;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Vehicle_DisableCrashDamage;
}

int NCD_Eff_Vehicle_DisableWater(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Vehicle_DisableWaterDamage;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Vehicle_DisableWaterDamage;
}

int NCD_Eff_Vehicle_BlockContaminated(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Vehicle_BlockContaminated;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Vehicle_BlockContaminated;
}

int NCD_Eff_Vehicle_DisableRedlineDamage(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Vehicle_DisableRedlineDamage;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Vehicle_DisableRedlineDamage;
}

int NCD_Eff_Vehicle_BlockCrewCrashDamage(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Vehicle_BlockCrewCrashDamage;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Vehicle_BlockCrewCrashDamage;
}

int NCD_Eff_Vehicle_EnableCrashSounds(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Vehicle_EnableCrashSounds;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Vehicle_EnableCrashSounds;
}

int NCD_Eff_Vehicle_NoDamageToZombies(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Vehicle_NoDamageToZombies;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Vehicle_NoDamageToZombies;
}

int NCD_Eff_Vehicle_NoDamageToAnimals(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Vehicle_NoDamageToAnimals;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Vehicle_NoDamageToAnimals;
}

int NCD_Eff_Vehicle_NoDamageToPlayers(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Vehicle_NoDamageToPlayers;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Vehicle_NoDamageToPlayers;
}

int NCD_Eff_Vehicle_NoDamageToExpansionAI(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Vehicle_NoDamageToExpansionAI;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Vehicle_NoDamageToExpansionAI;
}

int NCD_Eff_Vehicle_AutoFlip(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Vehicle_AutoFlip;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Vehicle_AutoFlip;
}

int NCD_AutoFlipButtonEnabled()
{
	if (g_Game && g_Game.IsClient())
		return 1;

	NCD_Config cfg = NCD_Cfg();
	if (!cfg)
		return 0;
	return cfg.Vehicle_AutoFlipWithButton;
}

int NCD_Eff_Player_NoDmgInVehicle(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Player_NoDamageWhileInVehicle;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Player_NoDamageWhileInVehicle;
}

int NCD_Eff_Player_BlockAllInVehicle(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Player_BlockAllDamageWhileInVehicle;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Player_BlockAllDamageWhileInVehicle;
}

int NCD_Eff_Player_BlockBulletsInVehicle(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Player_BlockBulletsWhileInVehicle;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Player_BlockBulletsWhileInVehicle;
}

int NCD_Eff_Player_BlockExplosionsInVehicle(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Player_BlockExplosionsWhileInVehicle;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Player_BlockExplosionsWhileInVehicle;
}

int NCD_Eff_Player_BlockMeleeInVehicle(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Player_BlockMeleeWhileInVehicle;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Player_BlockMeleeWhileInVehicle;
}

int NCD_Eff_ExpansionAI_NoDmgInVehicle(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.ExpansionAI_NoDamageWhileInVehicle;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.ExpansionAI_NoDamageWhileInVehicle;
}

int NCD_Eff_ExpansionAI_BlockAllInVehicle(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.ExpansionAI_BlockAllDamageWhileInVehicle;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.ExpansionAI_BlockAllDamageWhileInVehicle;
}

int NCD_Eff_ExpansionAI_BlockBulletsInVehicle(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.ExpansionAI_BlockBulletsWhileInVehicle;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.ExpansionAI_BlockBulletsWhileInVehicle;
}

int NCD_Eff_ExpansionAI_BlockExplosionsInVehicle(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.ExpansionAI_BlockExplosionsWhileInVehicle;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.ExpansionAI_BlockExplosionsWhileInVehicle;
}

int NCD_Eff_ExpansionAI_BlockMeleeInVehicle(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.ExpansionAI_BlockMeleeWhileInVehicle;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.ExpansionAI_BlockMeleeWhileInVehicle;
}

int NCD_Eff_Player_BlockContaminatedInVehicle(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Player_BlockContaminatedWhileInVehicle;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Player_BlockContaminatedWhileInVehicle;
}

int NCD_Eff_Player_DoorOpenDisablesProtectionInContaminated(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Player_DoorOpenDisablesProtectionInContaminated;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Player_DoorOpenDisablesProtectionInContaminated;
}

int NCD_Eff_ExpansionAI_BlockContaminatedInVehicle(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.ExpansionAI_BlockContaminatedWhileInVehicle;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.ExpansionAI_BlockContaminatedWhileInVehicle;
}

int NCD_Eff_ExpansionAI_DoorOpenDisablesProtectionInContaminated(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.ExpansionAI_DoorOpenDisablesProtectionInContaminated;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.ExpansionAI_DoorOpenDisablesProtectionInContaminated;
}

int NCD_Eff_ProtectAttachments(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Protect_AttachmentsOnVehicle;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Protect_AttachmentsOnVehicle;
}

int NCD_Eff_Protect_PlayerClothingInVehicle(string vt)
{
	NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
	if (r) return r.Protect_PlayerClothingInVehicle;
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Protect_PlayerClothingInVehicle;
}

int NCD_Eff_Player_NoDamageAfterJumpFromVehicle()
{
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.Player_NoDamageAfterJumpFromVehicle;
}

int NCD_Eff_ExpansionAI_NoDamageAfterJumpFromVehicle()
{
	NCD_Config cfg = NCD_Cfg(); if (!cfg) return 0;
	return cfg.ExpansionAI_NoDamageAfterJumpFromVehicle;
}

bool NCD_IsVehicleSealedForToxic(string vt)
{
	if (vt == "") return false;
	if (NCD_Eff_Vehicle_BlockContaminated(vt) == 1) return true;
	if (NCD_Eff_Player_BlockContaminatedInVehicle(vt) == 1) return true;
	if (NCD_Eff_ExpansionAI_BlockContaminatedInVehicle(vt) == 1) return true;
	return false;
}

bool NCD_IsRealVehicleClass(string cls)
{
	if (!g_Game || cls == "") return false;

	string base = "CfgVehicles " + cls;
	if (!g_Game.ConfigIsExisting(base)) return false;

	string sim;
	if (!g_Game.ConfigIsExisting(base + " simulation")) return false;
	g_Game.ConfigGetText(base + " simulation", sim);

	sim.ToLower();

	if (sim.IndexOf("car") != -1) return true;
	if (sim.IndexOf("boat") != -1) return true;
	if (sim.IndexOf("helicopter") != -1) return true;
	if (sim.IndexOf("air") != -1) return true;
	return false;
}

void NCD_CleanupVehicleOverrides()
{
	if (!g_Game || !g_Game.IsServer())
		return;

	NCD_Config cfg = NCD_Cfg();
	if (!cfg || !cfg.VehicleOverrides)
		return;

	int before = cfg.VehicleOverrides.Count();
	if (NCD_CompactVehicleOverrides())
	{
		int removed = before - cfg.VehicleOverrides.Count();
		JsonFileLoader<NCD_Config>.JsonSaveFile(NCD_CFG_PATH, cfg);
		Print("[NoCarDamage] Cleanup compacted " + removed.ToString() + " invalid/duplicate/no-op override entries -> saved config");
		NCD_RebuildOverrideMap();
	}
}

void NCD_ScanVehiclesAndExtendConfig()
{
	if (!g_Game || !g_Game.IsServer())
		return;

	NCD_Config cfg = NCD_Cfg();
	if (!cfg)
		return;

	if (cfg.AutoExtendVehicleOverrides == 0)
	{
		Print("[NoCarDamage] Vehicle scan skipped (AutoExtendVehicleOverrides=0)");
		return;
	}

	int added = 0;
	int total = g_Game.ConfigGetChildrenCount("CfgVehicles");

	ref map<string, int> known = new map<string, int>();
	for (int existingIndex = 0; existingIndex < g_NCD_Cfg.VehicleOverrides.Count(); existingIndex++)
	{
		NCD_VehicleOverride existingOverride = g_NCD_Cfg.VehicleOverrides[existingIndex];
		if (!existingOverride || existingOverride.ClassName == "")
			continue;
		known.Set(existingOverride.ClassName, 1);
	}

	for (int i = 0; i < total; i++)
	{
		string cls;
		g_Game.ConfigGetChildName("CfgVehicles", i, cls);
		if (cls == "") continue;

		string scopePath = "CfgVehicles " + cls + " scope";
		if (!g_Game.ConfigIsExisting(scopePath)) continue;

		int sc = g_Game.ConfigGetInt(scopePath);
		if (sc <= 0) continue;

		string lower = cls;
		lower.ToLower();
		if (lower.IndexOf("ruined") != -1 || lower.IndexOf("wreck") != -1) continue;

		if (!NCD_IsRealVehicleClass(cls)) continue;

		if (cls == "Transport" || cls == "Car" || cls == "Boat" || cls == "Helicopter") continue;

		if (NCD_MapGet(known, cls) == 1)
			continue;

		NCD_VehicleOverride o2 = new NCD_VehicleOverride();
		o2.ClassName = cls;
		g_NCD_Cfg.VehicleOverrides.Insert(o2);
		known.Set(cls, 1);
		added++;
	}

	if (added > 0)
	{
		JsonFileLoader<NCD_Config>.JsonSaveFile(NCD_CFG_PATH, g_NCD_Cfg);
		Print("[NoCarDamage] Vehicle scan added " + added.ToString() + " new entries -> saved config");
		NCD_RebuildOverrideMap();
	}
	else
	{
		Print("[NoCarDamage] Vehicle scan: no new entries");
	}
}

static ref array<EntityAI> g_NCD_BypassedEntities;
static ref array<Transport> g_NCD_ActiveTransports;

void NCD_RegisterTransport(Transport t)
{
	if (!t) return;
	if (!g_NCD_ActiveTransports)
		g_NCD_ActiveTransports = new array<Transport>();
	
	if (g_NCD_ActiveTransports.Find(t) == -1)
		g_NCD_ActiveTransports.Insert(t);
}

void NCD_UnregisterTransport(Transport t)
{
	if (!t || !g_NCD_ActiveTransports)
		return;
	
	int idx = g_NCD_ActiveTransports.Find(t);
	if (idx != -1)
		g_NCD_ActiveTransports.Remove(idx);
}

bool NCD_IsEntityProtectionBypassed(EntityAI e)
{
	if (!e) return false;
	return NoCarDamageAPI.IsEntityBypassed(e);
}

float NCD_GetVehicleSpeedKmh(Transport t)
{
	if (!t) return 0.0;
	
	vector vel = GetVelocity(t);
	return vel.Length() * 3.6;
}

void NCD_UpdatePreCrashSpeedCache(Transport t)
{
	if (!t || !g_Game) return;
	
	int key = t.GetID();
	if (key <= 0) return;
	
	int nowMS = g_Game.GetTime();
	
	if (!g_NCD_PreCrashSpeedCache)
		g_NCD_PreCrashSpeedCache = new map<int, ref array<float>>();
	if (!g_NCD_PreCrashCacheTime)
		g_NCD_PreCrashCacheTime = new map<int, int>();
	
	ref array<float> speeds;
	if (!g_NCD_PreCrashSpeedCache.Find(key, speeds))
	{
		speeds = new array<float>();
		g_NCD_PreCrashSpeedCache.Set(key, speeds);
	}
	
	float currentSpeedKmh = NCD_GetVehicleSpeedKmh(t);
	speeds.Insert(currentSpeedKmh);
	
	while (speeds.Count() > 20)
		speeds.Remove(0);
	
	g_NCD_PreCrashCacheTime.Set(key, nowMS);
}

float NCD_GetRecentVehicleCrashSpeedKmh(Transport t)
{
	if (!t) return 0.0;
	
	int key = t.GetID();
	if (key <= 0)
		return NCD_GetVehicleSpeedKmh(t);
	
	if (!g_NCD_PreCrashSpeedCache)
		return NCD_GetVehicleSpeedKmh(t);
	
	ref array<float> speeds;
	if (!g_NCD_PreCrashSpeedCache.Find(key, speeds))
		return NCD_GetVehicleSpeedKmh(t);
	
	if (speeds.Count() == 0)
		return NCD_GetVehicleSpeedKmh(t);
	
	float maxSpeed = 0.0;
	for (int i = 0; i < speeds.Count(); i++)
	{
		if (speeds[i] > maxSpeed)
			maxSpeed = speeds[i];
	}
	
	return maxSpeed;
}

void NCD_InvalidateVehicleRuntimeFlags(Transport t)
{
	// No-op: CarScript/BoatScript/HelicopterScript types are from mods and not available at compile time.
	// This means config reloads via NoCarDamageAPI.ReloadConfig() will NOT update runtime flags on already-spawned vehicles.
	// Vehicles must be deleted and recreated to pick up new config values for:
	// - DisableCrashDamage, DisableWaterDamage, AutoFlip, etc.
	// Jump-out protection uses global config and works immediately on reload.
	return;
}

void NCD_CleanupPreCrashCache()
{
	if (!g_NCD_PreCrashSpeedCache || !g_NCD_PreCrashCacheTime)
		return;
	
	if (!g_Game) return;
	
	int nowMS = g_Game.GetTime();
	ref array<int> toRemove = new array<int>();
	
	for (int i = 0; i < g_NCD_PreCrashCacheTime.Count(); i++)
	{
		int key = g_NCD_PreCrashCacheTime.GetKey(i);
		int lastTime = g_NCD_PreCrashCacheTime.GetElement(i);
		
		if ((nowMS - lastTime) > NCD_PRECRASH_CACHE_MS * 2)
			toRemove.Insert(key);
	}
	
	for (int j = 0; j < toRemove.Count(); j++)
	{
		int removeKey = toRemove[j];
		g_NCD_PreCrashSpeedCache.Remove(removeKey);
		g_NCD_PreCrashCacheTime.Remove(removeKey);
	}
}

class NoCarDamageAPI
{
	static bool IsActive()
	{
		return true;
	}

	static NCD_Config GetConfig()
	{
		return NCD_Cfg();
	}

	static NCD_ResolvedVehicleRules GetVehicleRules(string vehicleType)
	{
		return NCD_GetResolvedVehicleRules(vehicleType);
	}

	static void ReloadConfig()
	{
		if (!g_Game || !g_Game.IsServer())
		{
			Error("[NoCarDamageAPI] ReloadConfig() can only be called on server");
			return;
		}
		
		g_NCD_CfgDiskLoaded = false;
		
		if (g_NCD_ResolvedRulesMap)
			g_NCD_ResolvedRulesMap.Clear();
		
		if (g_NCD_OverrideMap)
			g_NCD_OverrideMap.Clear();
		
		if (g_NCD_PreCrashSpeedCache)
			g_NCD_PreCrashSpeedCache.Clear();
		if (g_NCD_PreCrashCacheTime)
			g_NCD_PreCrashCacheTime.Clear();
		
		g_NCD_ExpansionVehiclesState = -1;
		g_NCD_ExpansionDisableVehicleDamageState = -1;
		
		NCD_LoadConfigFromDisk();
		
		if (g_NCD_ActiveTransports)
		{
			for (int i = 0; i < g_NCD_ActiveTransports.Count(); i++)
			{
				Transport t = g_NCD_ActiveTransports[i];
				if (t)
					NCD_InvalidateVehicleRuntimeFlags(t);
			}
		}
	}

	static void AddBypass(EntityAI entity)
	{
		if (!entity) return;
		if (!g_Game || !g_Game.IsServer())
		{
			Error("[NoCarDamageAPI] AddBypass() can only be called on server. Entity: " + entity.GetType());
			return;
		}
		if (!g_NCD_BypassedEntities) g_NCD_BypassedEntities = new array<EntityAI>();
		if (g_NCD_BypassedEntities.Find(entity) == -1)
			g_NCD_BypassedEntities.Insert(entity);
	}

	static void RemoveBypass(EntityAI entity)
	{
		if (!entity || !g_NCD_BypassedEntities) return;
		if (!g_Game || !g_Game.IsServer())
		{
			Error("[NoCarDamageAPI] RemoveBypass() can only be called on server. Entity: " + entity.GetType());
			return;
		}
		int idx = g_NCD_BypassedEntities.Find(entity);
		if (idx != -1)
			g_NCD_BypassedEntities.Remove(idx);
	}

	static bool IsEntityBypassed(EntityAI entity)
	{
		if (!entity || !g_NCD_BypassedEntities) return false;
		return (g_NCD_BypassedEntities.Find(entity) != -1);
	}
}

float NCD_Eff_Vehicle_DisableCrash_MaxSpeedKmh(string vt)
{
    NCD_ResolvedVehicleRules r = NCD_GetResolvedVehicleRules(vt);
    if (r) return r.Vehicle_DisableCrash_MaxSpeedKmh;
    NCD_Config cfg = NCD_Cfg(); if (!cfg) return -1.0;
    return cfg.Vehicle_DisableCrash_MaxSpeedKmh;
}

float NCD_GetJumpOutSpeedKmh(float carSpeed)
{
	return carSpeed;
}

bool NCD_IsAttachmentCustomCrashDamage(string ammo)
{
	if (ammo == "") return true;
	string am = ammo;
	am.ToLower();

	if (am.IndexOf("crash") != -1) return true;
	if (am.IndexOf("enviro") != -1) return true;
	if (am.IndexOf("vehicle") != -1) return true;
	if (am.IndexOf("collision") != -1) return true;
	if (am.IndexOf("transport") != -1) return true;

	return false;
}

bool NCD_IsCrashProtectionActive(Transport t, string vt)
{
	if (!t) return false;
	if (vt == "") return false;

	if (NCD_IsEntityProtectionBypassed(t))
		return false;

	if (NCD_Eff_Vehicle_DisableCrash(vt) != 1)
		return false;

	float maxKmh = NCD_Eff_Vehicle_DisableCrash_MaxSpeedKmh(vt);
	if (maxKmh < 0)
		return true;

	float crashSpeedKmh = NCD_GetRecentVehicleCrashSpeedKmh(t);
	return crashSpeedKmh <= maxKmh;
}
