# NoCarDamage
The readme includes Admin config guide and API description for modders

This is a DayZ Mod that aims to make vehicles customizable

You can disable or fine-tune damage for vehicles and players while inside vehicles.
Stop vehicles from taking crash damage, bullet damage, explosion damage, and more — and protect passengers and vehicle attachments as well.

The mod generates a config file on first start, so you can quickly enable/disable features globally and override them per vehicle class.
If you want player not drown from water damage, change Vanilla drown settings in cfggameplaysettings.json.
_______________________________________________________________
Full Credit For the original Mod: 
Fabian Baldensperger
baldensperger@gmx.ch
_______________________________________________________________
How the config works

On first run the mod generates:
$profile:NoCarDamage\NoCarDamage_Config.json

You can:
- Set global rules (apply to all vehicles)
- Enable VehicleOverrides to override rules per vehicle class
- Use AutoExtendVehicleOverrides to automatically populate overrides for new vehicles, do your changes and set it to 0 and it will delete all unneeded entries, to reduce impact on server perfomance.

Override values:
1 = enabled
0 = disabled
-1 = inherit the global setting
_______________________________________________________________


Installation / Server Notes

Load it on the server like any other Workshop mod.

Works with vanilla vehicles and modded vehicles (using class names).
After the first start it generates a config file.
Change the settings how you like and restart the server.

Monetization
You are allowed to use this mod on monetized severs, as long as you follow BI rules. No pay to win.

Repack, unpack, change, etc. is allowed

You are not allowed to sell any part of this code.




NoCarDamage Admin Config Guide
==============================

This file explains every option in:

$profile:NoCarDamage\NoCarDamage_Config.json

The explanations are written for server admins.


Basic Value Rules
=================

Most settings use:

0 = off / disabled / allow damage
1 = on / enabled / block damage

VehicleOverrides use a third value:

-1 = inherit the global setting from the main config
 0 = force this setting off for this vehicle class
 1 = force this setting on for this vehicle class

Speed values are in km/h.

For max-speed settings:

-1 = unlimited / no max speed limit
 0 or higher = protection only applies up to this speed


Main Config Options
===================

Version
-------

Internal config version.
Do not edit this manually unless you know exactly why.
NoCarDamage uses this to upgrade older config files automatically.


Vehicle_BlockBullets
--------------------

Blocks bullet damage to vehicles.

0 = bullets can damage vehicles
1 = bullets do not damage vehicles


Vehicle_BlockExplosions
-----------------------

Blocks explosion damage to vehicles.

0 = explosions can damage vehicles
1 = explosions do not damage vehicles


Vehicle_BlockMelee
------------------

Blocks melee damage to vehicles.

0 = melee hits can damage vehicles
1 = melee hits do not damage vehicles


Vehicle_AllowGlassDamage
------------------------

Allows glass/window damage even when bullet protection is enabled.

0 = glass is protected like the rest of the vehicle
1 = glass/windows can still be damaged by bullets

This only matters when Vehicle_BlockBullets is enabled.


Vehicle_DisableCrashDamage
--------------------------

Blocks crash/contact damage to vehicles.

0 = vehicles can take crash damage
1 = vehicles do not take crash damage


Vehicle_DisableCrash_MaxSpeedKmh
--------------------------------

Maximum speed for crash damage protection.

-1 = protect at every speed
Example: 120.0 = protect crash damage only up to 120 km/h

If the vehicle crashes faster than this value, crash damage is allowed.

This setting only matters when Vehicle_DisableCrashDamage is enabled.


Vehicle_DisableWaterDamage
--------------------------

Blocks water damage to vehicles.

0 = water can damage/destroy vehicles
1 = water damage is blocked


Vehicle_BlockContaminated
-------------------------

Blocks contaminated/toxic/gas damage to the vehicle itself.

0 = contaminated areas can damage the vehicle
1 = contaminated damage to the vehicle is blocked


Player_BlockContaminatedWhileInVehicle
--------------------------------------

Blocks contaminated/toxic/gas damage to players while they are inside a
protected vehicle.

0 = players can take contaminated damage in vehicles
1 = contaminated damage to players in vehicles is blocked


Player_DoorOpenDisablesProtectionInContaminated
-----------------------------------------------

Controls contaminated-area protection when a vehicle door is open.

0 = door state does not matter
1 = if a door is open, contaminated protection for players in the vehicle is disabled

This is useful if you want sealed vehicles to protect players, but open
doors/windows to make contaminated zones dangerous again.


Player_NoDamageWhileInVehicle
-----------------------------

Main switch for player protection while inside a vehicle.

0 = players inside vehicles are not protected by the player-in-vehicle rules
1 = player-in-vehicle rules can protect players

The detailed damage types below decide what is blocked.


Player_BlockAllDamageWhileInVehicle
-----------------------------------

Blocks all damage to players while they are inside a vehicle.

0 = do not block all damage
1 = block all damage

This is the strongest player-in-vehicle protection.


Player_BlockBulletsWhileInVehicle
---------------------------------

Blocks bullet damage to players while they are inside a vehicle.

0 = bullets can damage players in vehicles
1 = bullets do not damage players in vehicles

Only matters when Player_NoDamageWhileInVehicle is enabled.


Player_BlockExplosionsWhileInVehicle
------------------------------------

Blocks explosion damage to players while they are inside a vehicle.

0 = explosions can damage players in vehicles
1 = explosions do not damage players in vehicles

Only matters when Player_NoDamageWhileInVehicle is enabled.


Player_BlockMeleeWhileInVehicle
-------------------------------

Blocks melee damage to players while they are inside a vehicle.

0 = melee hits can damage players in vehicles
1 = melee hits do not damage players in vehicles

Only matters when Player_NoDamageWhileInVehicle is enabled.


Protect_PlayerClothingInVehicle
-------------------------------

Protects player clothing/items while the player is inside a protected vehicle.

0 = clothing/items can be damaged normally
1 = clothing/items are protected according to the vehicle/player protection rules


Protect_AttachmentsOnVehicle
----------------------------

Protects vehicle attachments.

Examples:
- spark plugs
- glow plugs
- attached vehicle parts/items

0 = attachments can be damaged normally
1 = attachments are protected


Vehicle_DisableRedlineDamage
----------------------------

Blocks engine damage from driving at redline RPM.

0 = engine can take redline damage
1 = redline damage is blocked


Vehicle_BlockCrewCrashDamage
----------------------------

Blocks crash damage to the crew/occupants.

0 = occupants can take crash damage
1 = occupant crash damage is blocked

This is separate from Vehicle_DisableCrashDamage. That means you can protect
the vehicle, the crew, or both.


Vehicle_EnableCrashSounds
-------------------------

Controls crash sounds when crash protection is active.

0 = suppress crash sounds while crash protection is active
1 = allow normal crash sounds


Vehicle_NoDamageToZombies
-------------------------

Controls damage from vehicles to zombies/infected.

0 = vehicles can damage zombies/infected
1 = vehicles do not damage zombies/infected


Vehicle_NoDamageToAnimals
-------------------------

Controls damage from vehicles to animals.

0 = vehicles can damage animals
1 = vehicles do not damage animals


Vehicle_NoDamageToPlayers
-------------------------

Controls damage from vehicles to players.

0 = vehicles can damage players
1 = vehicles do not damage players

This is about the vehicle hitting a player, not about a player sitting
inside the vehicle.


Vehicle_NoDamageToExpansionAI
-----------------------------

Controls damage from vehicles to Expansion AI.

0 = vehicles can damage Expansion AI
1 = vehicles do not damage Expansion AI

Only relevant on servers using Expansion AI.


Vehicle_AutoFlip
----------------

Enables automatic vehicle flip/upright behavior.

0 = auto flip is disabled
1 = vehicles can be flipped upright automatically by the mod


Vehicle_AutoFlipWithButton
--------------------------

Controls whether auto flip is done by button instead of passive automatic
handling.

0 = passive auto flip behavior can be used when Vehicle_AutoFlip is enabled
1 = auto flip is triggered by the mod's flip button/keybind system


Player_NoDamageAfterJumpFromVehicle
-----------------------------------

Enables short protection after jumping out of a moving vehicle.

0 = no special jump-out protection
1 = jump-out protection can be used

The speed range and time window below decide when it applies.


Player_NoDamageAfterJump_MinSpeedKmh
------------------------------------

Minimum vehicle speed for jump-out protection.

Example:
8.0 = protection only starts when the vehicle is at least 8 km/h fast

If the vehicle is slower than this, vanilla jump-out damage is allowed.


Player_NoDamageAfterJump_MaxSpeedKmh
------------------------------------

Maximum vehicle speed for jump-out protection.

-1 = no maximum speed limit
Example: 120.0 = protect jump-out damage only up to 120 km/h

If the vehicle is faster than this, vanilla jump-out damage is allowed.


Player_NoDamageAfterJump_WindowMS
---------------------------------

Protection time after jumping out, in milliseconds.

Example:
1500 = 1.5 seconds

Allowed range:
0 to 10000

0 = disabled
10000 = 10 seconds

This window should usually be short. It only needs to cover the moment where
DayZ applies fall/jump-out damage after leaving the vehicle.


ExpansionAI_NoDamageWhileInVehicle
----------------------------------

Main switch for Expansion AI protection while inside a vehicle.

0 = Expansion AI inside vehicles is not protected by these rules
1 = Expansion AI in vehicles can be protected

Only relevant on servers using Expansion AI.


ExpansionAI_BlockAllDamageWhileInVehicle
----------------------------------------

Blocks all damage to Expansion AI while inside a vehicle.

0 = do not block all damage
1 = block all damage


ExpansionAI_BlockBulletsWhileInVehicle
--------------------------------------

Blocks bullet damage to Expansion AI while inside a vehicle.

0 = bullets can damage Expansion AI in vehicles
1 = bullets do not damage Expansion AI in vehicles


ExpansionAI_BlockExplosionsWhileInVehicle
-----------------------------------------

Blocks explosion damage to Expansion AI while inside a vehicle.

0 = explosions can damage Expansion AI in vehicles
1 = explosions do not damage Expansion AI in vehicles


ExpansionAI_BlockMeleeWhileInVehicle
------------------------------------

Blocks melee damage to Expansion AI while inside a vehicle.

0 = melee hits can damage Expansion AI in vehicles
1 = melee hits do not damage Expansion AI in vehicles


ExpansionAI_BlockContaminatedWhileInVehicle
-------------------------------------------

Blocks contaminated/toxic/gas damage to Expansion AI while inside a vehicle.

0 = contaminated damage can affect Expansion AI in vehicles
1 = contaminated damage is blocked


ExpansionAI_DoorOpenDisablesProtectionInContaminated
----------------------------------------------------

Controls contaminated-area protection for Expansion AI when a vehicle door is
open.

0 = door state does not matter
1 = if a door is open, contaminated protection for Expansion AI is disabled


ExpansionAI_NoDamageAfterJumpFromVehicle
----------------------------------------

Enables jump-out protection for Expansion AI.

0 = no jump-out protection for Expansion AI
1 = jump-out protection can apply to Expansion AI

Uses the same min speed, max speed, and window settings as player jump-out
protection.


EnableVehicleOverrides
----------------------

Enables the VehicleOverrides section.

0 = ignore vehicle-specific overrides
1 = use vehicle-specific overrides

If disabled, only the global settings are used.


AutoExtendVehicleOverrides
--------------------------

Automatically scans vehicle classes and adds missing vehicles to
VehicleOverrides.

0 = do not auto-add vehicles
1 = auto-add detected vehicle classes to VehicleOverrides

Recommended:
Leave this off unless you want the config to automatically grow with detected
vehicle classes.


VehicleOverrides
================

VehicleOverrides lets you set different rules for specific vehicle classes.

Each entry starts with:

"ClassName": "VehicleClassNameHere"

Example:

{
    "ClassName": "OffroadHatchback",
    "Vehicle_DisableCrashDamage": 1,
    "Vehicle_DisableCrash_MaxSpeedKmh": 80.0,
    "Player_NoDamageWhileInVehicle": -1
}

In VehicleOverrides:

-1 = use the global value
 0 = force off for this vehicle
 1 = force on for this vehicle

For speed values:

-1.0 = use the global/unlimited behavior
80.0 = use 80 km/h for this vehicle


VehicleOverride Fields
======================

Every VehicleOverride entry can use these fields:

ClassName
---------

The DayZ class name of the vehicle.

Example:
"OffroadHatchback"


Vehicle_BlockBullets
--------------------

Override for Vehicle_BlockBullets.


Vehicle_BlockExplosions
-----------------------

Override for Vehicle_BlockExplosions.


Vehicle_BlockMelee
------------------

Override for Vehicle_BlockMelee.


Vehicle_AllowGlassDamage
------------------------

Override for Vehicle_AllowGlassDamage.


Vehicle_DisableCrashDamage
--------------------------

Override for Vehicle_DisableCrashDamage.


Vehicle_DisableWaterDamage
--------------------------

Override for Vehicle_DisableWaterDamage.


Vehicle_BlockContaminated
-------------------------

Override for Vehicle_BlockContaminated.


Player_BlockContaminatedWhileInVehicle
--------------------------------------

Override for Player_BlockContaminatedWhileInVehicle.


Player_DoorOpenDisablesProtectionInContaminated
-----------------------------------------------

Override for Player_DoorOpenDisablesProtectionInContaminated.


Vehicle_DisableRedlineDamage
----------------------------

Override for Vehicle_DisableRedlineDamage.


Vehicle_BlockCrewCrashDamage
----------------------------

Override for Vehicle_BlockCrewCrashDamage.


Vehicle_EnableCrashSounds
-------------------------

Override for Vehicle_EnableCrashSounds.


Vehicle_NoDamageToZombies
-------------------------

Override for Vehicle_NoDamageToZombies.


Vehicle_NoDamageToAnimals
-------------------------

Override for Vehicle_NoDamageToAnimals.


Vehicle_NoDamageToPlayers
-------------------------

Override for Vehicle_NoDamageToPlayers.


Vehicle_NoDamageToExpansionAI
-----------------------------

Override for Vehicle_NoDamageToExpansionAI.


Vehicle_AutoFlip
----------------

Override for Vehicle_AutoFlip.


Vehicle_DisableCrash_MaxSpeedKmh
--------------------------------

Override for Vehicle_DisableCrash_MaxSpeedKmh.

Use -1.0 to inherit the global setting.


Player_NoDamageWhileInVehicle
-----------------------------

Override for Player_NoDamageWhileInVehicle.


Player_BlockAllDamageWhileInVehicle
-----------------------------------

Override for Player_BlockAllDamageWhileInVehicle.


Player_BlockBulletsWhileInVehicle
---------------------------------

Override for Player_BlockBulletsWhileInVehicle.


Player_BlockExplosionsWhileInVehicle
------------------------------------

Override for Player_BlockExplosionsWhileInVehicle.


Player_BlockMeleeWhileInVehicle
-------------------------------

Override for Player_BlockMeleeWhileInVehicle.


ExpansionAI_NoDamageWhileInVehicle
----------------------------------

Override for ExpansionAI_NoDamageWhileInVehicle.


ExpansionAI_BlockAllDamageWhileInVehicle
----------------------------------------

Override for ExpansionAI_BlockAllDamageWhileInVehicle.


ExpansionAI_BlockBulletsWhileInVehicle
--------------------------------------

Override for ExpansionAI_BlockBulletsWhileInVehicle.


ExpansionAI_BlockExplosionsWhileInVehicle
-----------------------------------------

Override for ExpansionAI_BlockExplosionsWhileInVehicle.


ExpansionAI_BlockMeleeWhileInVehicle
------------------------------------

Override for ExpansionAI_BlockMeleeWhileInVehicle.


ExpansionAI_BlockContaminatedWhileInVehicle
-------------------------------------------

Override for ExpansionAI_BlockContaminatedWhileInVehicle.


ExpansionAI_DoorOpenDisablesProtectionInContaminated
----------------------------------------------------

Override for ExpansionAI_DoorOpenDisablesProtectionInContaminated.


ExpansionAI_NoDamageAfterJumpFromVehicle
----------------------------------------

Override for ExpansionAI_NoDamageAfterJumpFromVehicle.


Protect_AttachmentsOnVehicle
----------------------------

Override for Protect_AttachmentsOnVehicle.


Protect_PlayerClothingInVehicle
-------------------------------

Override for Protect_PlayerClothingInVehicle.


Recommended Admin Setups
========================

Classic No Vehicle Damage
-------------------------

Use this if you want vehicles to be very protected:

Vehicle_BlockBullets = 1
Vehicle_BlockExplosions = 1
Vehicle_DisableCrashDamage = 1
Vehicle_DisableCrash_MaxSpeedKmh = -1.0
Vehicle_DisableWaterDamage = 1
Vehicle_BlockCrewCrashDamage = 1


Low-Speed Crash Protection Only
-------------------------------

Use this if small accidents should be forgiven, but high-speed crashes should
still hurt:

Vehicle_DisableCrashDamage = 1
Vehicle_DisableCrash_MaxSpeedKmh = 120.0
Vehicle_BlockCrewCrashDamage = 1

Result:
Crashes up to 120 km/h are protected.
Crashes above 120 km/h can cause damage.


Jump-Out Protection With Admin Speed Limit
------------------------------------------

Example:

Player_NoDamageAfterJumpFromVehicle = 1
Player_NoDamageAfterJump_MinSpeedKmh = 8.0
Player_NoDamageAfterJump_MaxSpeedKmh = 120.0
Player_NoDamageAfterJump_WindowMS = 1500

Result:
Players are protected when jumping out between 8 and 120 km/h.
Above 120 km/h, vanilla damage is allowed.


Expansion Servers
=================

NoCarDamage does not require Expansion.

If you use Expansion Bundle / Expansion Vehicles, load NoCarDamage after
Expansion in the server mod order.

NoCarDamage detects Expansion vehicle settings softly and keeps the main mod
standalone.
But if you have deleted Expansion Vehicles and run still Expansion Core, you must delete the Vehicle settings from Expansion. Otherwise the mod will not work properly.

Important Admin Notes
=====================

- Make a backup before editing the JSON.
- Restart the server after changing core vehicle protection settings.
- Runtime config reloads are not the intended main update path.
- Existing older configs are upgraded automatically on server start.
- Invalid boolean values are corrected back to safe defaults.
- Player_NoDamageAfterJump_WindowMS is clamped between 0 and 10000.
- Speed values are km/h.
- For VehicleOverrides, use -1 if you want the vehicle to inherit the global
  setting.


NoCarDamage API - Information for Modders
=========================================

This file describes the public NoCarDamage API for other DayZ modders.
The main use case is simple: another mod can temporarily disable
NoCarDamage protection for a specific player, vehicle, helicopter, boat,
or other EntityAI.

Typical examples:
- Safezone mod: allow damage again when a player abuses a protected zone.
- No-fly-zone mod: allow helicopter/player damage inside a forbidden area.
- Event/arena mod: disable NoCarDamage protection only during an event.
- Admin/tool mod: reload or inspect NoCarDamage config on the server.


Important Load/Dependency Notes
===============================

If your mod directly calls NoCarDamageAPI in script code, NoCarDamage must
be loaded before your mod.

Recommended for a mod that requires NoCarDamage:

1. Add NoCarDamage to your mod dependency/load order.
2. Add the NoCarDamage addon class to requiredAddons in your config.cpp.

Example:

class CfgPatches
{
	class MySafezoneMod
	{
		requiredAddons[] = {"DZ_Data", "DZ_Scripts", "NoCarDamage"};
	};
};

If your mod should remain fully optional and also run without NoCarDamage,
do not call NoCarDamageAPI directly from your main PBO. In that case, make
a small optional compatibility PBO which requires NoCarDamage and contains
only the NoCarDamage integration.


Public API
==========

class NoCarDamageAPI
{
	static bool IsActive();
	static NCD_Config GetConfig();
	static NCD_ResolvedVehicleRules GetVehicleRules(string vehicleType);
	static void ReloadConfig();
	static void AddBypass(EntityAI entity);
	static void RemoveBypass(EntityAI entity);
	static bool IsEntityBypassed(EntityAI entity);
}


NoCarDamageAPI.IsActive()
-------------------------

Returns true when the NoCarDamage API class is available.

Use this only as a simple sanity check. If your script directly references
NoCarDamageAPI, your PBO already needs NoCarDamage available at compile/load
time.

Example:

if (NoCarDamageAPI.IsActive())
{
	Print("[MyMod] NoCarDamage API is active");
}


NoCarDamageAPI.AddBypass(EntityAI entity)
-----------------------------------------

Server-only.

Adds an entity to the NoCarDamage bypass list.
While bypassed, NoCarDamage will not protect this entity.

Use this when your mod wants vanilla/other-mod damage to apply again.

Valid examples:
- PlayerBase player
- CarScript / Transport vehicle
- HelicopterScript helicopter
- BoatScript boat
- Other EntityAI objects handled by your gameplay logic

Important:
- Call this only on the server.
- Passing null does nothing.
- Calling it multiple times for the same entity is safe.
- The bypass is runtime-only and is not saved to disk.
- Remove the bypass again when your special condition ends.


NoCarDamageAPI.RemoveBypass(EntityAI entity)
--------------------------------------------

Server-only.

Removes an entity from the NoCarDamage bypass list.
After removal, NoCarDamage protection can apply again according to the
server JSON config.

Important:
- Call this only on the server.
- Passing null does nothing.
- Removing an entity that is not bypassed is safe.
- NoCarDamage also removes its own tracked players/vehicles on delete, but
  your mod should still clean up explicitly when your zone/event ends.


NoCarDamageAPI.IsEntityBypassed(EntityAI entity)
------------------------------------------------

Returns true if the entity is currently bypassed.

Example:

if (!NoCarDamageAPI.IsEntityBypassed(vehicle))
{
	NoCarDamageAPI.AddBypass(vehicle);
}


NoCarDamageAPI.GetConfig()
--------------------------

Returns the active NoCarDamage config object.

This is mainly useful for reading values. Other mods should not directly
edit the returned config object unless they fully understand NoCarDamage's
internal config flow.

For normal integrations, prefer AddBypass() and RemoveBypass().


NoCarDamageAPI.GetVehicleRules(string vehicleType)
--------------------------------------------------

Returns the resolved NoCarDamage vehicle rules for a vehicle type.

This includes global config plus vehicle-specific override resolution.

Example:

Transport t = player.GetCommand_Vehicle().GetTransport();
if (t)
{
	NCD_ResolvedVehicleRules rules = NoCarDamageAPI.GetVehicleRules(t.GetType());
	if (rules)
	{
		Print("[MyMod] DisableCrashDamage=" + rules.Vehicle_DisableCrashDamage.ToString());
	}
}


NoCarDamageAPI.ReloadConfig()
-----------------------------

Server-only.

Reloads the NoCarDamage JSON config from disk and rebuilds internal rule
maps/caches.

Important limitation:
Runtime vehicle flags on already spawned vehicles are not fully refreshed
by this call. For core vehicle protection changes, a server restart or
vehicle respawn is the safest path.

Jump-out protection reads the global config live and is less affected by
this limitation.


Recommended Usage: Safezone / No-Fly-Zone
=========================================

If a player or vehicle enters a zone where your mod wants normal damage to
apply, bypass both the player and the vehicle when possible.

Example:

void MyZone_SetNoCarDamageBypass(PlayerBase player, bool enable)
{
	if (!GetGame() || !GetGame().IsServer())
		return;

	if (!player)
		return;

	if (enable)
	{
		NoCarDamageAPI.AddBypass(player);

		HumanCommandVehicle cmd = player.GetCommand_Vehicle();
		if (cmd)
		{
			Transport t = cmd.GetTransport();
			if (t)
				NoCarDamageAPI.AddBypass(t);
		}
	}
	else
	{
		NoCarDamageAPI.RemoveBypass(player);

		HumanCommandVehicle cmd2 = player.GetCommand_Vehicle();
		if (cmd2)
		{
			Transport t2 = cmd2.GetTransport();
			if (t2)
				NoCarDamageAPI.RemoveBypass(t2);
		}
	}
}

Why bypass both?
- Bypassing the vehicle allows vehicle damage again.
- Bypassing the player allows player/occupant protection to be skipped.
- Some damage paths are attached to the vehicle, others to the player.


Recommended Usage: Temporary Punishment / Event Damage
======================================================

If your mod wants damage to apply only for a short time, add the bypass,
then remove it after the condition ends.

Example:

NoCarDamageAPI.AddBypass(player);
NoCarDamageAPI.AddBypass(vehicle);

// Later, when the event/penalty/zone condition ends:
NoCarDamageAPI.RemoveBypass(player);
NoCarDamageAPI.RemoveBypass(vehicle);


What The Bypass Affects
=======================

Bypassing an entity can affect NoCarDamage protection for:
- Vehicle crash protection
- Vehicle water protection
- Vehicle contaminated-area protection
- Vehicle bullet/explosion/melee/custom damage protection
- Player protection while inside a vehicle
- Player jump-out protection
- Player clothing/item protection while inside a vehicle
- Zombie/animal hit filtering when the source entity is bypassed

The exact result still depends on which entity is bypassed and which damage
path DayZ or another mod uses.


Best Practices
==============

- Use the API only on the server.
- Track your own zone/event state so you do not call AddBypass/RemoveBypass
  every frame unnecessarily.
- Always remove bypasses when your condition ends.
- If you bypass a player because of a vehicle/heli rule, also bypass the
  current vehicle/heli when possible.
- If your mod directly calls NoCarDamageAPI, declare the dependency/load
  order clearly.
- If your mod should support servers without NoCarDamage, use an optional
  compatibility PBO instead of direct calls in your main PBO.
- Do not use ReloadConfig as a general runtime vehicle-rule switch. It is
  mainly an admin/tool function.


Minimal Example
===============

modded class PlayerBase
{
	void MyMod_EnableNormalDamageInForbiddenZone(bool enable)
	{
		if (!GetGame() || !GetGame().IsServer())
			return;

		if (enable)
		{
			NoCarDamageAPI.AddBypass(this);
		}
		else
		{
			NoCarDamageAPI.RemoveBypass(this);
		}
	}
}


Support Notes
=============

For most integrations, you only need:

NoCarDamageAPI.AddBypass(entity);
NoCarDamageAPI.RemoveBypass(entity);
NoCarDamageAPI.IsEntityBypassed(entity);

If your modder use case is not covered here, prefer building your logic
around those three functions first.



