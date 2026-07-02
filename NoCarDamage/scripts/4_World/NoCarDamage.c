bool NCD_IsGlassZone(string dmgZone)
{
	if (dmgZone == "")
		return false;

	string dz = dmgZone;
	dz.ToLower();

	return (dz.IndexOf("glass") != -1) || (dz.IndexOf("window") != -1) || (dz.IndexOf("windscreen") != -1);
}

Transport NCD_GetPlayerTransport(PlayerBase p)
{
	if (!p) return null;

	HumanCommandVehicle cmd = p.GetCommand_Vehicle();
	if (cmd)
	{
		Transport cmdTransport = cmd.GetTransport();
		if (cmdTransport)
			return cmdTransport;
	}

	EntityAI root = EntityAI.Cast(p.GetHierarchyRoot());
	if (root && root != p && root.IsKindOf("Transport"))
		return Transport.Cast(root);

	return null;
}

bool NCD_IsPlayerInVehicle(PlayerBase p)
{
	return (NCD_GetPlayerTransport(p) != null);
}

bool NCD_IsHumanPlayer(PlayerBase player)
{
	if (!player)
		return false;
	if (NCD_IsExpansionAI(player))
		return false;
	return (player.GetIdentity() != null);
}

bool NCD_IsExpansionAI(PlayerBase player)
{
	if (!player) return false;
	
	if (player.IsKindOf("eAIBase")) return true;

	string scriptCls = player.ClassName();
	scriptCls.ToLower();
	if (scriptCls.IndexOf("eaibase") != -1 || scriptCls.IndexOf("expansionai") != -1 || scriptCls == "eai")
		return true;

	return false;
}

static const int NCD_PLAYER_KIND_NONE = 0;
static const int NCD_PLAYER_KIND_HUMAN = 1;
static const int NCD_PLAYER_KIND_EXPANSION_AI = 2;

int NCD_GetProtectedPlayerKind(PlayerBase player)
{
	if (NCD_IsExpansionAI(player))
		return NCD_PLAYER_KIND_EXPANSION_AI;

	if (NCD_IsHumanPlayer(player))
		return NCD_PLAYER_KIND_HUMAN;

	return NCD_PLAYER_KIND_NONE;
}

bool NCD_ShouldApplyHumanOrAIProtection(PlayerBase player, int humanEnabled, int aiEnabled)
{
	int playerKind = NCD_GetProtectedPlayerKind(player);

	if (playerKind == NCD_PLAYER_KIND_HUMAN)
		return (humanEnabled == 1);

	if (playerKind == NCD_PLAYER_KIND_EXPANSION_AI)
		return (aiEnabled == 1);

	return false;
}


bool NCD_ShouldProtectJumpOutForPlayer(PlayerBase player)
{
	return NCD_ShouldApplyHumanOrAIProtection(player, NCD_Eff_Player_NoDamageAfterJumpFromVehicle(), NCD_Eff_ExpansionAI_NoDamageAfterJumpFromVehicle());
}

bool NCD_ShouldIgnoreTransportHitForPlayer(PlayerBase player, string vt)
{
	int playerKind = NCD_GetProtectedPlayerKind(player);
	if (playerKind == NCD_PLAYER_KIND_HUMAN)
		return (NCD_Eff_Vehicle_NoDamageToPlayers(vt) == 1);
	if (playerKind == NCD_PLAYER_KIND_EXPANSION_AI)
		return (NCD_Eff_Vehicle_NoDamageToExpansionAI(vt) == 1);
	return false;
}

int NCD_Eff_Occupant_NoDmgInVehicle(PlayerBase player, string vt)
{
	int playerKind = NCD_GetProtectedPlayerKind(player);
	if (playerKind == NCD_PLAYER_KIND_HUMAN)
		return NCD_Eff_Player_NoDmgInVehicle(vt);
	if (playerKind == NCD_PLAYER_KIND_EXPANSION_AI)
		return NCD_Eff_ExpansionAI_NoDmgInVehicle(vt);
	return 0;
}

int NCD_Eff_Occupant_BlockAllInVehicle(PlayerBase player, string vt)
{
	int playerKind = NCD_GetProtectedPlayerKind(player);
	if (playerKind == NCD_PLAYER_KIND_HUMAN)
		return NCD_Eff_Player_BlockAllInVehicle(vt);
	if (playerKind == NCD_PLAYER_KIND_EXPANSION_AI)
		return NCD_Eff_ExpansionAI_BlockAllInVehicle(vt);
	return 0;
}

int NCD_Eff_Occupant_BlockBulletsInVehicle(PlayerBase player, string vt)
{
	int playerKind = NCD_GetProtectedPlayerKind(player);
	if (playerKind == NCD_PLAYER_KIND_HUMAN)
		return NCD_Eff_Player_BlockBulletsInVehicle(vt);
	if (playerKind == NCD_PLAYER_KIND_EXPANSION_AI)
		return NCD_Eff_ExpansionAI_BlockBulletsInVehicle(vt);
	return 0;
}

int NCD_Eff_Occupant_BlockExplosionsInVehicle(PlayerBase player, string vt)
{
	int playerKind = NCD_GetProtectedPlayerKind(player);
	if (playerKind == NCD_PLAYER_KIND_HUMAN)
		return NCD_Eff_Player_BlockExplosionsInVehicle(vt);
	if (playerKind == NCD_PLAYER_KIND_EXPANSION_AI)
		return NCD_Eff_ExpansionAI_BlockExplosionsInVehicle(vt);
	return 0;
}

int NCD_Eff_Occupant_BlockMeleeInVehicle(PlayerBase player, string vt)
{
	int playerKind = NCD_GetProtectedPlayerKind(player);
	if (playerKind == NCD_PLAYER_KIND_HUMAN)
		return NCD_Eff_Player_BlockMeleeInVehicle(vt);
	if (playerKind == NCD_PLAYER_KIND_EXPANSION_AI)
		return NCD_Eff_ExpansionAI_BlockMeleeInVehicle(vt);
	return 0;
}

int NCD_Eff_Occupant_BlockContaminatedInVehicle(PlayerBase player, string vt)
{
	int playerKind = NCD_GetProtectedPlayerKind(player);
	if (playerKind == NCD_PLAYER_KIND_HUMAN)
		return NCD_Eff_Player_BlockContaminatedInVehicle(vt);
	if (playerKind == NCD_PLAYER_KIND_EXPANSION_AI)
		return NCD_Eff_ExpansionAI_BlockContaminatedInVehicle(vt);
	return 0;
}

int NCD_Eff_Occupant_DoorOpenDisablesProtectionInContaminated(PlayerBase player, string vt)
{
	int playerKind = NCD_GetProtectedPlayerKind(player);
	if (playerKind == NCD_PLAYER_KIND_HUMAN)
		return NCD_Eff_Player_DoorOpenDisablesProtectionInContaminated(vt);
	if (playerKind == NCD_PLAYER_KIND_EXPANSION_AI)
		return NCD_Eff_ExpansionAI_DoorOpenDisablesProtectionInContaminated(vt);
	return 0;
}

bool NCD_IsOccupantSealedForToxic(PlayerBase player, string vt)
{
	if (vt == "")
		return false;

	if (NCD_Eff_Vehicle_BlockContaminated(vt) == 1)
		return true;

	return (NCD_Eff_Occupant_BlockContaminatedInVehicle(player, vt) == 1);
}

bool NCD_ShouldSuppressContaminatedAreaForPlayer(PlayerBase player, Transport t)
{
	if (!player || !t)
		return false;

	string vt = t.GetType();
	if (!NCD_IsOccupantSealedForToxic(player, vt))
		return false;

	bool doorRule = false;
	if (NCD_Eff_Occupant_DoorOpenDisablesProtectionInContaminated(player, vt) == 1)
		doorRule = NCD_IsAnyDoorOpen(t);

	return !doorRule;
}

bool NCD_ShouldBlockCrewCrashDamage(Transport t, string vt)
{
	if (!t)
		return false;

	if (vt == "")
		vt = t.GetType();

	if (vt == "")
		return false;

	if (NCD_IsEntityProtectionBypassed(t))
		return false;

	if (NCD_Eff_Vehicle_BlockCrewCrashDamage(vt) != 1)
		return false;

	return NCD_IsCrashProtectionActive(t, vt);
}

bool NCD_ShouldBlockOccupantCrashDamage(PlayerBase player, int damageType, string ammo)
{
	if (!player || damageType != DamageType.CUSTOM)
		return false;

	if (!NCD_IsAttachmentCustomCrashDamage(ammo))
		return false;

	Transport t = NCD_GetPlayerTransport(player);
	if (!t)
		return false;

	return NCD_ShouldBlockCrewCrashDamage(t, t.GetType());
}

bool NCD_IsVehicleRootEntity(EntityAI root)
{
	if (!root)
		return false;

	if (root.IsKindOf("Transport") || root.IsKindOf("CarScript") || root.IsKindOf("BoatScript") || root.IsKindOf("HelicopterScript"))
		return true;

	if (root.IsKindOf("ExpansionVehicleBase") || root.IsKindOf("ExpansionVehicleHelicopterBase") || root.IsKindOf("ExpansionHelicopterScript"))
		return true;

	string cls = root.ClassName();
	cls.ToLower();
	if (cls.IndexOf("expansionvehicle") != -1 || cls.IndexOf("expansionhelicopter") != -1)
		return true;

	return false;
}

string NCD_PlayerKey(PlayerBase p)
{
	if (!p) return "";
	PlayerIdentity id = p.GetIdentity();
	if (id) return id.GetId();
	return p.ToString();
}

bool NCD_IsToxicAmmo(string ammo)
{
	if (ammo == "") return false;
	string am = ammo;
	am.ToLower();
	return (am.IndexOf("contamin") != -1) || (am.IndexOf("toxic") != -1) || (am.IndexOf("gas") != -1) || (am.IndexOf("chemical") != -1);
}

static ref map<string, ref array<string>> NCD_DoorSlotCache_W = new map<string, ref array<string>>();
static ref map<string, ref array<string>> NCD_DoorAnimCache_W = new map<string, ref array<string>>();
static ref map<string, int> NCD_DoorOpenCacheTime_W = new map<string, int>();
static ref map<string, bool> NCD_DoorOpenCacheVal_W = new map<string, bool>();
static const int NCD_DOOR_OPEN_CACHE_MS = 2000;

static bool NCD_IsDoorLikeName(string s)
{
	if (s == "") return false;
	string low = s;
	low.ToLower();

	if (low.IndexOf("door")   != -1) return true;
	if (low.IndexOf("doors")  != -1) return true;
	if (low.IndexOf("hatch")  != -1) return true;
	if (low.IndexOf("ramp")   != -1) return true;
	if (low.IndexOf("gate")   != -1) return true;
	if (low.IndexOf("hood")   != -1) return true;
	if (low.IndexOf("bonnet") != -1) return true;
	if (low.IndexOf("trunk")  != -1) return true;
	if (low.IndexOf("boot")   != -1) return true;
	if (low.IndexOf("canopy") != -1) return true;
	if (low.IndexOf("dver")   != -1) return true;
	return false;
}

static array<string> NCD_GetDoorSlotNames_W(string vt)
{
	if (vt == "") return null;

	ref array<string> cached;
	if (NCD_DoorSlotCache_W.Find(vt, cached))
		return cached;

	ref array<string> slots = new array<string>();

	string path = "CfgVehicles " + vt + " attachments";
	if (g_Game && g_Game.ConfigIsExisting(path))
	{
		ref array<string> tmp = new array<string>();
		g_Game.ConfigGetTextArray(path, tmp);
		for (int i = 0; i < tmp.Count(); i++)
		{
			string s = tmp[i];
			if (NCD_IsDoorLikeName(s))
				slots.Insert(s);
		}
	}

	NCD_DoorSlotCache_W.Set(vt, slots);
	return slots;
}

static array<string> NCD_GetDoorAnimSourceNames_W(string vt)
{
	if (vt == "") return null;

	ref array<string> cached;
	if (NCD_DoorAnimCache_W.Find(vt, cached))
		return cached;

	ref array<string> sources = new array<string>();

	string path = "CfgVehicles " + vt + " AnimationSources";
	if (g_Game && g_Game.ConfigIsExisting(path))
	{
		int c = g_Game.ConfigGetChildrenCount(path);
		for (int i = 0; i < c; i++)
		{
			string child;
			g_Game.ConfigGetChildName(path, i, child);
			if (NCD_IsDoorLikeName(child))
				sources.Insert(child);
		}
	}

	NCD_DoorAnimCache_W.Set(vt, sources);
	return sources;
}

static void NCD_SetDoorOpenCache(string key, bool val)
{
	if (key == "" || !g_Game) return;
	NCD_DoorOpenCacheVal_W.Set(key, val);
	NCD_DoorOpenCacheTime_W.Set(key, g_Game.GetTime());
}

static void NCD_InvalidateDoorCache(Transport t)
{
	if (!t) return;
	string key = t.ToString();
	if (key == "") return;
	NCD_DoorOpenCacheVal_W.Remove(key);
	NCD_DoorOpenCacheTime_W.Remove(key);
}

bool NCD_IsAnyDoorOpen(Transport t)
{
	if (!t) return false;

	string key = t.ToString();
	if (g_Game)
	{
		int last;
		bool cached;
		if (NCD_DoorOpenCacheTime_W.Find(key, last) && NCD_DoorOpenCacheVal_W.Find(key, cached))
		{
			if ((g_Game.GetTime() - last) < NCD_DOOR_OPEN_CACHE_MS)
				return cached;
		}
	}

	string vt = t.GetType();

	array<string> sources = NCD_GetDoorAnimSourceNames_W(vt);
	if (!sources)
	{
		NCD_SetDoorOpenCache(key, false);
		return false;
	}

	for (int k = 0; k < sources.Count(); k++)
	{
		string s = sources[k];
		if (s == "") continue;

		float ph = t.GetAnimationPhase(s);
		if (ph > 0.5)
		{
			NCD_SetDoorOpenCache(key, true);
			return true;
		}
	}

	NCD_SetDoorOpenCache(key, false);
	return false;
}

bool NCD_IsTransportFlipped(Transport t)
{
	if (!t) return false;

	vector mat[4];
	t.GetTransform(mat);
	vector up = mat[1];

	return (up[1] < 0.2);
}

void NCD_FlipTransportUpright(Transport t)
{
	if (!t) return;

	vector ori = t.GetOrientation();
	ori[0] = 0;
	ori[2] = 0;

	vector pos = t.GetPosition();
	pos[1] = pos[1] + 1.0;

	t.SetPosition(pos);
	t.SetOrientation(ori);
}

modded class CarScript
{
	protected float m_NCD_AutoFlipTimer = 0;
	protected float m_NCD_WaterCheckTimer = 0;
	protected float m_NCD_WaterCheckInterval = 0.5;
	protected bool m_NCD_WaterUnderwater = false;
	protected float m_NCD_WaterEngineBefore = 0;
	protected bool m_NCD_DoCrashDisable = false;
	protected bool m_NCD_DoCrashSounds = false;
	protected bool m_NCD_DoCrewCrashBlock = false;
	protected int m_NCD_LastCrashCacheClearMS = 0;
	protected int m_NCD_LastCrashIdleClearMS = 0;
	protected bool m_NCD_RuntimeFlagsInit = false;
	protected bool m_NCD_HasRuntimeWork = false;
	protected bool m_NCD_DoWaterProtection = false;
	protected bool m_NCD_DoPassiveAutoFlip = false;
	protected bool m_NCD_UseExpansionCrashWaterPath = false;
	protected string m_NCD_VehicleTypeCached = "";

	override void EEDelete(EntityAI parent)
	{
		if (g_Game && g_Game.IsServer())
		{
			NoCarDamageAPI.RemoveBypass(this);
			NCD_UnregisterTransport(this);
		}

		super.EEDelete(parent);
	}

	protected string NCD_GetVehicleTypeCached()
	{
		if (m_NCD_VehicleTypeCached == "")
			m_NCD_VehicleTypeCached = GetType();

		return m_NCD_VehicleTypeCached;
	}

	protected void NCD_InitRuntimeFlags()
	{
		if (m_NCD_RuntimeFlagsInit)
			return;

		m_NCD_RuntimeFlagsInit = true;

		if (!g_Game || !g_Game.IsServer())
			return;

		if (NCD_IsEntityProtectionBypassed(this))
		{
			m_NCD_DoWaterProtection = false;
			m_NCD_DoPassiveAutoFlip = false;
			m_NCD_DoCrashDisable = false;
			m_NCD_DoCrashSounds = false;
			m_NCD_DoCrewCrashBlock = false;
			m_NCD_UseExpansionCrashWaterPath = false;
			m_NCD_HasRuntimeWork = false;
			return;
		}

		string vt = NCD_GetVehicleTypeCached();
		m_NCD_DoWaterProtection = (NCD_Eff_Vehicle_DisableWater(vt) == 1);
		m_NCD_DoPassiveAutoFlip = (NCD_Eff_Vehicle_AutoFlip(vt) == 1 && NCD_AutoFlipButtonEnabled() == 0);
		m_NCD_DoCrashDisable = (NCD_Eff_Vehicle_DisableCrash(vt) == 1);
		m_NCD_DoCrashSounds = (NCD_Eff_Vehicle_EnableCrashSounds(vt) == 1);
		m_NCD_DoCrewCrashBlock = (NCD_Eff_Vehicle_BlockCrewCrashDamage(vt) == 1);
		m_NCD_UseExpansionCrashWaterPath = NCD_IsExpansionVehicleDamageDisabled() && (m_NCD_DoCrashDisable || m_NCD_DoWaterProtection);

		if (m_NCD_UseExpansionCrashWaterPath)
		{
			m_NCD_DoCrashDisable = false;
			m_NCD_DoWaterProtection = false;
		}

		m_NCD_HasRuntimeWork = (m_NCD_DoWaterProtection || m_NCD_DoPassiveAutoFlip);
	}

	void NCD_ResetRuntimeFlags()
	{
		m_NCD_RuntimeFlagsInit = false;
	}

	override void OnVehicleJumpOutServer(GetOutTransportActionData gotActionData)
	{
		PlayerBase jumpOutPlayer = null;
		if (gotActionData)
		{
			jumpOutPlayer = PlayerBase.Cast(gotActionData.m_Player);
			if (jumpOutPlayer && !NCD_IsEntityProtectionBypassed(this) && !NCD_IsEntityProtectionBypassed(jumpOutPlayer) && NCD_ShouldProtectJumpOutForPlayer(jumpOutPlayer))
			{
				if (jumpOutPlayer.NCD_ArmNoJumpDamageWindowKmh(NCD_GetVehicleSpeedKmh(this)))
					return;
			}
		}

		super.OnVehicleJumpOutServer(gotActionData);
		if (jumpOutPlayer)
			jumpOutPlayer.NCD_MarkJumpOutVehicleDamageHandled();
	}

	override void OnAnimationPhaseStarted(string animSource, float phase)
	{
		super.OnAnimationPhaseStarted(animSource, phase);

		if (NCD_IsDoorLikeName(animSource))
			NCD_InvalidateDoorCache(this);
	}

	override bool EEOnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (NCD_IsEntityProtectionBypassed(this))
			return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		string vt = NCD_GetVehicleTypeCached();

		if (damageType == DamageType.CUSTOM && ammo != "" && dmgZone == "Engine")
		{
			if (NCD_Eff_Vehicle_DisableRedlineDamage(vt) == 1 && EngineIsOn() && EngineGetRPM() >= EngineGetRPMRedline())
			{
				string am = ammo;
				am.ToLower();
				if (am.IndexOf("enviro") != -1)
					return false;
			}
		}

		if (NCD_Eff_Vehicle_BlockContaminated(vt) == 1 && NCD_IsToxicAmmo(ammo))
			return false;

		if (damageType == DamageType.FIRE_ARM && NCD_Eff_Vehicle_BlockBullets(vt) == 1)
		{
			if (NCD_Eff_Vehicle_AllowGlassDamage(vt) == 1 && NCD_IsGlassZone(dmgZone))
				return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
			return false;
		}

		if (damageType == DamageType.EXPLOSION && NCD_Eff_Vehicle_BlockExplosions(vt) == 1) return false;
		if (damageType == DamageType.CLOSE_COMBAT && NCD_Eff_Vehicle_BlockMelee(vt) == 1) return false;

		return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}

	override void CheckContactCache()
	{
		NCD_InitRuntimeFlags();
		if (m_NCD_DoCrashDisable && NCD_IsCrashProtectionActive(this, NCD_GetVehicleTypeCached()))
		{
			if (g_Game)
			{
				int nowMS = g_Game.GetTime();
				bool hasCrew = (CrewSize() > 0);
				bool engineOn = EngineIsOn();
				bool idle = (!hasCrew && !engineOn);

				if (idle)
				{
					if ((nowMS - m_NCD_LastCrashIdleClearMS) >= 15000)
					{
						m_NCD_LastCrashIdleClearMS = nowMS;
						m_ContactCache.Clear();
					}
					return;
				}

				if ((nowMS - m_NCD_LastCrashCacheClearMS) >= 4000)
				{
					m_NCD_LastCrashCacheClearMS = nowMS;
					m_ContactCache.Clear();
				}
			}
			else
			{
				m_ContactCache.Clear();
			}
			return;
		}

		super.CheckContactCache();
	}

	override void SynchCrashLightSound(bool play)
	{
		NCD_InitRuntimeFlags();
		if (!m_NCD_DoCrashSounds && NCD_IsCrashProtectionActive(this, NCD_GetVehicleTypeCached()))
			return;
		super.SynchCrashLightSound(play);
	}

	override void SynchCrashHeavySound(bool play)
	{
		NCD_InitRuntimeFlags();
		if (!m_NCD_DoCrashSounds && NCD_IsCrashProtectionActive(this, NCD_GetVehicleTypeCached()))
			return;
		super.SynchCrashHeavySound(play);
	}

	override void DamageCrew(float dmg)
	{
		NCD_InitRuntimeFlags();
		if (m_NCD_DoCrewCrashBlock && NCD_ShouldBlockCrewCrashDamage(this, NCD_GetVehicleTypeCached()))
			return;

		super.DamageCrew(dmg);
	}

	override void OnUpdate(float dt)
	{
		NCD_InitRuntimeFlags();

		if (g_Game && g_Game.IsServer())
		{
			NCD_UpdatePreCrashSpeedCache(this);
			NCD_RegisterTransport(this);
		}

		if (!g_Game || !g_Game.IsServer() || !m_NCD_HasRuntimeWork)
		{
			super.OnUpdate(dt);
			return;
		}

		bool hasCrew = (CrewSize() > 0);

		if (m_NCD_DoWaterProtection)
		{
			m_NCD_WaterCheckTimer += dt;
			if (m_NCD_WaterCheckTimer >= m_NCD_WaterCheckInterval)
			{
				m_NCD_WaterCheckTimer = 0;
				m_NCD_WaterUnderwater = (g_Game.GetWaterDepth(GetEnginePosWS()) > 0);
				if (m_NCD_WaterUnderwater)
				{
					m_NCD_WaterEngineBefore = GetHealth("Engine", "Health");
					m_NCD_WaterCheckInterval = 0.5;
				}
				else if (!hasCrew)
				{
					m_NCD_WaterCheckInterval = m_NCD_WaterCheckInterval + 1.0;
					if (m_NCD_WaterCheckInterval > 30.0)
						m_NCD_WaterCheckInterval = 30.0;
				}
				else
				{
					m_NCD_WaterCheckInterval = 0.5;
				}
			}
		}

		super.OnUpdate(dt);

		if (m_NCD_DoWaterProtection && m_NCD_WaterUnderwater)
		{
			float engineAfter = GetHealth("Engine", "Health");
			if (engineAfter < m_NCD_WaterEngineBefore)
				SetHealth("Engine", "Health", m_NCD_WaterEngineBefore);

			m_DrownTime = 0;
		}

		if (m_NCD_DoPassiveAutoFlip)
		{
			if (!hasCrew)
			{
				m_NCD_AutoFlipTimer = 0;
				return;
			}

			m_NCD_AutoFlipTimer += dt;
			if (m_NCD_AutoFlipTimer >= 5.0)
			{
				m_NCD_AutoFlipTimer = 0;

				if (GetSpeedometer() < 1.0 && NCD_IsTransportFlipped(this))
					NCD_FlipTransportUpright(this);
			}
		}
	}
};

modded class BoatScript
{
	protected float m_NCD_AutoFlipTimer = 0;
	protected bool m_NCD_RuntimeFlagsInit = false;
	protected bool m_NCD_DoPassiveAutoFlip = false;
	protected bool m_NCD_DoCrashDisable = false;
	protected string m_NCD_VehicleTypeCached = "";

	override void EEDelete(EntityAI parent)
	{
		if (g_Game && g_Game.IsServer())
		{
			NoCarDamageAPI.RemoveBypass(this);
			NCD_UnregisterTransport(this);
		}

		super.EEDelete(parent);
	}

	protected string NCD_GetVehicleTypeCached()
	{
		if (m_NCD_VehicleTypeCached == "")
			m_NCD_VehicleTypeCached = GetType();
		return m_NCD_VehicleTypeCached;
	}

	protected void NCD_InitRuntimeFlags()
	{
		if (m_NCD_RuntimeFlagsInit)
			return;

		m_NCD_RuntimeFlagsInit = true;

		if (!g_Game || !g_Game.IsServer())
			return;

		if (NCD_IsEntityProtectionBypassed(this))
		{
			m_NCD_DoPassiveAutoFlip = false;
			m_NCD_DoCrashDisable = false;
			return;
		}

		string vt = NCD_GetVehicleTypeCached();
		m_NCD_DoPassiveAutoFlip = (NCD_Eff_Vehicle_AutoFlip(vt) == 1 && NCD_AutoFlipButtonEnabled() == 0);
		m_NCD_DoCrashDisable = (NCD_Eff_Vehicle_DisableCrash(vt) == 1);
	}

	void NCD_ResetRuntimeFlags()
	{
		m_NCD_RuntimeFlagsInit = false;
	}

	override void OnUpdate(float dt)
	{
		NCD_InitRuntimeFlags();

		if (g_Game && g_Game.IsServer())
		{
			NCD_UpdatePreCrashSpeedCache(this);
			NCD_RegisterTransport(this);
		}

		if (g_Game && g_Game.IsServer() && m_NCD_DoPassiveAutoFlip)
		{
			if (CrewSize() == 0)
			{
				m_NCD_AutoFlipTimer = 0;
			}
			else
			{
				m_NCD_AutoFlipTimer += dt;
				if (m_NCD_AutoFlipTimer >= 5.0)
				{
					m_NCD_AutoFlipTimer = 0;
					
					vector vel = GetVelocity(this);
					if (vel.Length() < 1.0 && NCD_IsTransportFlipped(this))
						NCD_FlipTransportUpright(this);
				}
			}
		}
		
		super.OnUpdate(dt);
	}

	override bool EEOnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (NCD_IsEntityProtectionBypassed(this))
			return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		string vt = NCD_GetVehicleTypeCached();

		if (NCD_IsCrashProtectionActive(this, vt) && damageType == DamageType.CUSTOM)
		{
			string am = ammo;
			am.ToLower();
			if (am == "" || am.IndexOf("crash") != -1 || am.IndexOf("enviro") != -1)
				return false;
		}

		if (NCD_Eff_Vehicle_BlockContaminated(vt) == 1 && NCD_IsToxicAmmo(ammo))
			return false;

		if (damageType == DamageType.FIRE_ARM && NCD_Eff_Vehicle_BlockBullets(vt) == 1)
		{
			if (NCD_Eff_Vehicle_AllowGlassDamage(vt) == 1 && NCD_IsGlassZone(dmgZone))
				return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
			return false;
		}

		if (damageType == DamageType.EXPLOSION && NCD_Eff_Vehicle_BlockExplosions(vt) == 1) return false;
		if (damageType == DamageType.CLOSE_COMBAT && NCD_Eff_Vehicle_BlockMelee(vt) == 1) return false;

		return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}
};

modded class HelicopterScript
{
	protected float m_NCD_AutoFlipTimer = 0;
	protected bool m_NCD_RuntimeFlagsInit = false;
	protected bool m_NCD_DoPassiveAutoFlip = false;
	protected bool m_NCD_DoCrashDisable = false;
	protected string m_NCD_VehicleTypeCached = "";

	override void EEDelete(EntityAI parent)
	{
		if (g_Game && g_Game.IsServer())
		{
			NoCarDamageAPI.RemoveBypass(this);
			NCD_UnregisterTransport(this);
		}

		super.EEDelete(parent);
	}

	protected string NCD_GetVehicleTypeCached()
	{
		if (m_NCD_VehicleTypeCached == "")
			m_NCD_VehicleTypeCached = GetType();
		return m_NCD_VehicleTypeCached;
	}

	protected void NCD_InitRuntimeFlags()
	{
		if (m_NCD_RuntimeFlagsInit)
			return;

		m_NCD_RuntimeFlagsInit = true;

		if (!g_Game || !g_Game.IsServer())
			return;

		if (NCD_IsEntityProtectionBypassed(this))
		{
			m_NCD_DoPassiveAutoFlip = false;
			m_NCD_DoCrashDisable = false;
			return;
		}

		string vt = NCD_GetVehicleTypeCached();
		m_NCD_DoPassiveAutoFlip = (NCD_Eff_Vehicle_AutoFlip(vt) == 1 && NCD_AutoFlipButtonEnabled() == 0);
		m_NCD_DoCrashDisable = (NCD_Eff_Vehicle_DisableCrash(vt) == 1);
	}

	void NCD_ResetRuntimeFlags()
	{
		m_NCD_RuntimeFlagsInit = false;
	}

	override void OnUpdate(float dt)
	{
		NCD_InitRuntimeFlags();

		if (g_Game && g_Game.IsServer())
		{
			NCD_UpdatePreCrashSpeedCache(this);
			NCD_RegisterTransport(this);
		}

		if (g_Game && g_Game.IsServer() && m_NCD_DoPassiveAutoFlip)
		{
			if (CrewSize() == 0)
			{
				m_NCD_AutoFlipTimer = 0;
			}
			else
			{
				m_NCD_AutoFlipTimer += dt;
				if (m_NCD_AutoFlipTimer >= 5.0)
				{
					m_NCD_AutoFlipTimer = 0;
					
					vector vel = GetVelocity(this);
					if (vel.Length() < 1.0 && NCD_IsTransportFlipped(this))
						NCD_FlipTransportUpright(this);
				}
			}
		}
		
		super.OnUpdate(dt);
	}

	override bool EEOnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (NCD_IsEntityProtectionBypassed(this))
			return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		string vt = NCD_GetVehicleTypeCached();

		if (NCD_IsCrashProtectionActive(this, vt))
		{
			string dz = dmgZone;
			dz.ToLower();
			if (dz.IndexOf("rotor") != -1)
				return false;
				
			if (damageType == DamageType.CUSTOM)
			{
				string am = ammo;
				am.ToLower();
				if (am == "" || am.IndexOf("crash") != -1 || am.IndexOf("enviro") != -1)
					return false;
			}
		}

		if (NCD_Eff_Vehicle_BlockContaminated(vt) == 1 && NCD_IsToxicAmmo(ammo))
			return false;

		if (damageType == DamageType.FIRE_ARM && NCD_Eff_Vehicle_BlockBullets(vt) == 1)
		{
			if (NCD_Eff_Vehicle_AllowGlassDamage(vt) == 1 && NCD_IsGlassZone(dmgZone))
				return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
			return false;
		}

		if (damageType == DamageType.EXPLOSION && NCD_Eff_Vehicle_BlockExplosions(vt) == 1) return false;
		if (damageType == DamageType.CLOSE_COMBAT && NCD_Eff_Vehicle_BlockMelee(vt) == 1) return false;

		return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}
};

modded class ActionGetOutTransport
{
	override void OnEndServer(ActionData action_data)
	{
		GetOutTransportActionData gotActionData = GetOutTransportActionData.Cast(action_data);
		if (!gotActionData || !gotActionData.m_Player || !gotActionData.m_WasJumpingOut)
		{
			super.OnEndServer(action_data);
			return;
		}

		PlayerBase jumpOutPlayer = PlayerBase.Cast(gotActionData.m_Player);
		if (!jumpOutPlayer)
		{
			super.OnEndServer(action_data);
			return;
		}

		if (jumpOutPlayer.NCD_IsNoJumpDamageActive())
		{
			jumpOutPlayer.OnJumpOutVehicleFinish(gotActionData.m_CarSpeed);
			if (gotActionData.m_Car)
			{
				CarScript activeCar;
				if (Class.CastTo(activeCar, gotActionData.m_Car))
					activeCar.ForceUpdateLightsEnd();
			}
			return;
		}

		if (jumpOutPlayer.NCD_ConsumeJumpOutVehicleDamageHandled())
		{
			jumpOutPlayer.OnJumpOutVehicleFinish(gotActionData.m_CarSpeed);
			if (gotActionData.m_Car)
			{
				CarScript handledCar;
				if (Class.CastTo(handledCar, gotActionData.m_Car))
					handledCar.ForceUpdateLightsEnd();
			}
			return;
		}

		// Check bypasses first
		if (gotActionData.m_Car && NCD_IsEntityProtectionBypassed(gotActionData.m_Car))
		{
			super.OnEndServer(action_data);
			return;
		}

		if (NCD_IsEntityProtectionBypassed(jumpOutPlayer))
		{
			super.OnEndServer(action_data);
			return;
		}

		// Check if jump protection is enabled for this player type
		if (!NCD_ShouldProtectJumpOutForPlayer(jumpOutPlayer))
		{
			super.OnEndServer(action_data);
			return;
		}

		// THE DECISION POINT:
		// NCD_ArmNoJumpDamageWindowKmh() returns true if protection window was armed
		// Returns false if speed is out of range or protection is disabled
		float jumpSpeedKmh = NCD_GetJumpOutSpeedKmh(gotActionData.m_CarSpeed);
		Transport jumpTransport = Transport.Cast(gotActionData.m_Car);
		if (jumpTransport)
			jumpSpeedKmh = NCD_GetVehicleSpeedKmh(jumpTransport);

		bool armed = jumpOutPlayer.NCD_ArmNoJumpDamageWindowKmh(jumpSpeedKmh);
		
		if (armed)
		{
			jumpOutPlayer.OnJumpOutVehicleFinish(gotActionData.m_CarSpeed);
			if (gotActionData.m_Car)
			{
				CarScript car;
				if (Class.CastTo(car, gotActionData.m_Car))
					car.ForceUpdateLightsEnd();
			}
		}
		else
		{
			// Protection NOT active: apply vanilla jump damage exactly once
			super.OnEndServer(action_data);
		}
	}
};

modded class ItemBase
{
	override bool EEOnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (damageType != DamageType.FIRE_ARM && damageType != DamageType.EXPLOSION && damageType != DamageType.CLOSE_COMBAT && damageType != DamageType.CUSTOM)
			return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		PlayerBase itemOwner = null;
		EntityAI current = this;
		while (current)
		{
			PlayerBase pb = PlayerBase.Cast(current);
			if (pb)
			{
				itemOwner = pb;
				break;
			}
			current = current.GetHierarchyParent();
		}

		if (itemOwner)
		{
			if (NCD_IsEntityProtectionBypassed(itemOwner))
				return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
			
			Transport t = NCD_GetPlayerTransport(itemOwner);
			if (t)
			{
				if (NCD_IsEntityProtectionBypassed(t))
					return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
				
				string vtPlayer = t.GetType();
				if (NCD_Eff_Protect_PlayerClothingInVehicle(vtPlayer) == 1)
				{
					bool sealedForToxic = NCD_IsOccupantSealedForToxic(itemOwner, vtPlayer);
					bool doorRule = false;
					if (sealedForToxic && NCD_Eff_Occupant_DoorOpenDisablesProtectionInContaminated(itemOwner, vtPlayer) == 1)
						doorRule = NCD_IsAnyDoorOpen(t);

					if (!doorRule)
					{
						if (NCD_Eff_Occupant_NoDmgInVehicle(itemOwner, vtPlayer) == 1)
						{
							if (NCD_Eff_Occupant_BlockAllInVehicle(itemOwner, vtPlayer) == 1) return false;
							if (damageType == DamageType.FIRE_ARM && NCD_Eff_Occupant_BlockBulletsInVehicle(itemOwner, vtPlayer) == 1) return false;
							if (damageType == DamageType.EXPLOSION && NCD_Eff_Occupant_BlockExplosionsInVehicle(itemOwner, vtPlayer) == 1) return false;
							if (damageType == DamageType.CLOSE_COMBAT && NCD_Eff_Occupant_BlockMeleeInVehicle(itemOwner, vtPlayer) == 1) return false;
						}

						if (sealedForToxic && NCD_IsToxicAmmo(ammo))
							return false;
					}
				}
			}
		}

		else
		{
			EntityAI root = EntityAI.Cast(GetHierarchyRoot());
			if (NCD_IsVehicleRootEntity(root))
			{
				if (NCD_IsEntityProtectionBypassed(root))
					return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

				string vt = root.GetType();
				Transport rootTransport = Transport.Cast(root);
				bool crashProtectionActive = NCD_IsCrashProtectionActive(rootTransport, vt);

				if ((IsKindOf("SparkPlug") || IsKindOf("GlowPlug")) && damageType == DamageType.CUSTOM)
				{
					if (crashProtectionActive && NCD_IsAttachmentCustomCrashDamage(ammo))
						return false;
					else
						return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
				}

				if (damageType == DamageType.CUSTOM)
				{
					if (!NCD_IsAttachmentCustomCrashDamage(ammo))
						return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
					
					if (!crashProtectionActive)
						return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
					
					return false;
				}

				if (NCD_Eff_ProtectAttachments(vt) == 1)
				{
					if (damageType == DamageType.FIRE_ARM) return false;
					if (damageType == DamageType.EXPLOSION) return false;
					if (damageType == DamageType.CLOSE_COMBAT) return false;
					if (damageType == DamageType.CUSTOM && NCD_IsAttachmentCustomCrashDamage(ammo)) return false;
				}
			}
		}

		return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}
};

modded class PlayerBase
{
	protected int m_NCD_NoJumpDamageUntilMS = 0;
	protected int m_NCD_JumpOutVehicleDamageHandledUntilMS = 0;
	protected int m_NCD_LastFlipRpcMS = 0;

	override void EEDelete(EntityAI parent)
	{
		if (g_Game && g_Game.IsServer())
			NoCarDamageAPI.RemoveBypass(this);

		super.EEDelete(parent);
	}

	void NCD_MarkJumpOutVehicleDamageHandled()
	{
		if (!g_Game || !g_Game.IsServer())
			return;

		m_NCD_JumpOutVehicleDamageHandledUntilMS = g_Game.GetTime() + 2000;
	}

	bool NCD_ConsumeJumpOutVehicleDamageHandled()
	{
		if (!g_Game || !g_Game.IsServer())
			return false;

		if (m_NCD_JumpOutVehicleDamageHandledUntilMS <= 0)
			return false;

		if (g_Game.GetTime() > m_NCD_JumpOutVehicleDamageHandledUntilMS)
		{
			m_NCD_JumpOutVehicleDamageHandledUntilMS = 0;
			return false;
		}

		m_NCD_JumpOutVehicleDamageHandledUntilMS = 0;
		return true;
	}

	bool NCD_ArmNoJumpDamageWindow(float carSpeed)
	{
		return NCD_ArmNoJumpDamageWindowKmh(NCD_GetJumpOutSpeedKmh(carSpeed));
	}

	bool NCD_ArmNoJumpDamageWindowKmh(float currentKmh)
	{
		if (!g_Game || !g_Game.IsServer())
			return false;

		if (NCD_IsEntityProtectionBypassed(this))
			return false;

		if (!NCD_ShouldProtectJumpOutForPlayer(this))
			return false;

		NCD_Config cfg = NCD_Cfg();
		if (!cfg)
			return false;

		float minKmh = cfg.Player_NoDamageAfterJump_MinSpeedKmh;
		float maxKmh = cfg.Player_NoDamageAfterJump_MaxSpeedKmh;
		int windowMS = cfg.Player_NoDamageAfterJump_WindowMS;

		if (currentKmh < minKmh)
			return false;

		if (maxKmh >= 0 && currentKmh > maxKmh)
			return false;

		if (windowMS < 0) windowMS = 0;
		if (windowMS > 10000) windowMS = 10000;
		if (windowMS <= 0)
			return false;

		int newUntil = g_Game.GetTime() + windowMS;
		if (newUntil > m_NCD_NoJumpDamageUntilMS)
			m_NCD_NoJumpDamageUntilMS = newUntil;

		return true;
	}

	bool NCD_IsNoJumpDamageActive()
	{
		return (NCD_ShouldProtectJumpOutForPlayer(this) && m_NCD_NoJumpDamageUntilMS > 0 && g_Game && g_Game.GetTime() <= m_NCD_NoJumpDamageUntilMS);
	}

	override bool EEOnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (NCD_IsEntityProtectionBypassed(this))
			return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		if (NCD_IsNoJumpDamageActive())
		{
			if (!source)
				return false;

			if (damageType == DamageType.CUSTOM)
			{
				string am0 = ammo;
				am0.ToLower();
				if (am0 == "" || am0.IndexOf("fall") != -1 || am0.IndexOf("land") != -1 || am0.IndexOf("enviro") != -1 || am0.IndexOf("shock") != -1 || am0.IndexOf("bleed") != -1)
					return false;
			}
		}

		if (source && source.IsKindOf("Transport"))
		{
			if (NCD_IsEntityProtectionBypassed(source))
				return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

			string vtSrc = source.GetType();
			if (NCD_ShouldIgnoreTransportHitForPlayer(this, vtSrc))
				return false;
		}

		if (damageType == DamageType.CUSTOM)
		{
			string am = ammo;
			am.ToLower();
			if (am == "" || am.IndexOf("crash") != -1 || am.IndexOf("enviro") != -1)
			{
				if (NCD_ShouldBlockOccupantCrashDamage(this, damageType, ammo))
					return false;

				Transport tCrash = NCD_GetPlayerTransport(this);
				if (tCrash && !NCD_IsCrashProtectionActive(tCrash, tCrash.GetType()))
					return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
			}
		}

		Transport t = NCD_GetPlayerTransport(this);
		if (t)
		{
			if (NCD_IsEntityProtectionBypassed(t))
				return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

			string vt = t.GetType();

			bool sealedForToxic = NCD_IsOccupantSealedForToxic(this, vt);
			bool doorRule = false;
			if (sealedForToxic && NCD_Eff_Occupant_DoorOpenDisablesProtectionInContaminated(this, vt) == 1)
				doorRule = NCD_IsAnyDoorOpen(t);

			if (!doorRule)
			{
				if (NCD_Eff_Occupant_NoDmgInVehicle(this, vt) == 1)
				{
					if (NCD_Eff_Occupant_BlockAllInVehicle(this, vt) == 1) return false;
					if (damageType == DamageType.FIRE_ARM && NCD_Eff_Occupant_BlockBulletsInVehicle(this, vt) == 1) return false;
					if (damageType == DamageType.EXPLOSION && NCD_Eff_Occupant_BlockExplosionsInVehicle(this, vt) == 1) return false;
					if (damageType == DamageType.CLOSE_COMBAT && NCD_Eff_Occupant_BlockMeleeInVehicle(this, vt) == 1) return false;
				}

				if (sealedForToxic && NCD_IsToxicAmmo(ammo))
					return false;
			}
		}

		return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}

	override void OnJumpOutVehicleFinish(float carSpeed)
	{
		super.OnJumpOutVehicleFinish(carSpeed);
	}

	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);
		if (!g_Game || !g_Game.IsServer())
			return;
		if (rpc_type != NCD_RPC_FLIP)
			return;
		int nowMS = g_Game.GetTime();
		if ((nowMS - m_NCD_LastFlipRpcMS) < 250)
			return;
		m_NCD_LastFlipRpcMS = nowMS;
		if (!sender || !GetIdentity() || sender.GetId() != GetIdentity().GetId())
			return;

		HumanCommandVehicle cmd = GetCommand_Vehicle();
		if (!cmd)
			return;

		Transport t = cmd.GetTransport();
		if (!t)
			return;

		if (t.CrewDriver() != this)
			return;

		if (NCD_IsEntityProtectionBypassed(t))
			return;

		string vt = t.GetType();
		if (NCD_AutoFlipButtonEnabled() == 0)
			return;

		if (!NCD_IsTransportFlipped(t))
			return;

		float speed = 0;
		CarScript cs = CarScript.Cast(t);
		if (cs)
			speed = cs.GetSpeedometer();
		else
		{
			vector vel = GetVelocity(t);
			speed = vel.Length();
		}

		if (speed > 1.0)
			return;

		NCD_FlipTransportUpright(t);
	}
};

modded class DayZPlayerImplementFallDamage
{
	override void HandleFallDamage(FallDamageData pData)
	{
		PlayerBase pb = PlayerBase.Cast(m_Player);
		if (pb && pb.NCD_IsNoJumpDamageActive())
			return;

		super.HandleFallDamage(pData);
	}
};

modded class ZombieBase
{
	override bool EEOnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (source && source.IsKindOf("Transport"))
		{
			if (NCD_IsEntityProtectionBypassed(source))
				return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

			string vt = source.GetType();
			if (NCD_Eff_Vehicle_NoDamageToZombies(vt) == 1)
				return false;
		}

		return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}
};

modded class AnimalBase
{
	override bool EEOnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (source && source.IsKindOf("Transport"))
		{
			if (NCD_IsEntityProtectionBypassed(source))
				return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

			string vt = source.GetType();
			if (NCD_Eff_Vehicle_NoDamageToAnimals(vt) == 1)
				return false;
		}

		return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}
};
