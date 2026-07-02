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
