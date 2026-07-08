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
static const string NCD_INPUT_GROUP = "NCD";
static const string NCD_INPUT_FLIP = "UANCDFlipVehicle";
static bool g_NCD_KeybindsInit = false;

void NCD_RegisterKeybinds()
{
	if (g_NCD_KeybindsInit)
		return;

	if (!g_Game || g_Game.IsDedicatedServer())
		return;

	UAInputAPI api = GetUApi();
	if (!api)
		return;

	bool created = false;
	UAInput existing = api.GetInputByName(NCD_INPUT_FLIP);
	if (!existing)
	{
		api.RegisterGroup(NCD_INPUT_GROUP, "#STR_NCD_CATEGORY");
		api.RegisterInput(NCD_INPUT_FLIP, "#STR_NCD_FLIP_VEHICLE", NCD_INPUT_GROUP);
		created = true;
	}

	if (created)
	{
		UAInput flipInput = api.GetInputByName(NCD_INPUT_FLIP);
		if (flipInput)
			flipInput.BindCombo("kH");
	}

	api.UpdateControls();
	InputUtils.InitInputMetadata();
	g_NCD_KeybindsInit = true;
}
