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
class CfgPatches
{
	class NoCarDamage
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Scripts"};
	};
};
class CfgMods
{
	class NoCarDamage
	{
		dir = "NoCarDamage";
		name = "NoCarDamage";
		credits="Original mod by blubberdiblupp";
        author="SchmickZ";
        authorID="76561198110186268";
        version="0.1";
		type = "mod";
		inputs = "NoCarDamage/data/inputs.xml";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"NoCarDamage/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"NoCarDamage/scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"NoCarDamage/scripts/5_Mission"};
			};
		};
	};
};
