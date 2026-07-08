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
modded class AreaExposureMdfr
{
	override void OnActivate(PlayerBase player)
	{
		if (!NCD_IsAnyToxicProtectionEnabled())
		{
			super.OnActivate(player);
			return;
		}

		if (NCD_IsEntityProtectionBypassed(player))
		{
			super.OnActivate(player);
			return;
		}

		Transport t = NCD_GetPlayerTransport(player);
		if (t)
		{
			if (NCD_IsEntityProtectionBypassed(t))
			{
				super.OnActivate(player);
				return;
			}

			if (NCD_ShouldSuppressContaminatedAreaForPlayer(player, t))
				return;
		}

		super.OnActivate(player);
	}

	override void OnTick(PlayerBase player, float deltaT)
	{
		if (!NCD_IsAnyToxicProtectionEnabled())
		{
			super.OnTick(player, deltaT);
			return;
		}

		if (NCD_IsEntityProtectionBypassed(player))
		{
			super.OnTick(player, deltaT);
			return;
		}

		Transport t = NCD_GetPlayerTransport(player);
		if (t)
		{
			if (NCD_IsEntityProtectionBypassed(t))
			{
				super.OnTick(player, deltaT);
				return;
			}

			if (NCD_ShouldSuppressContaminatedAreaForPlayer(player, t))
				return;
		}

		super.OnTick(player, deltaT);
	}
};
