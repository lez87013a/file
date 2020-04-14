//if (strstr(glowEnt->getEnt()->GetClientClass()->m_pNetworkName, ("CWeapon")))
#pragma once
#include "HookIncludes.h"

bool _fastcall hkDoPostScreenSpaceEffects(void* ecx, void* edx, CViewSetup* pSetup)
{
	static auto ofunc = hooks::clientmode.GetOriginalFunction<do_post_screen_space_effects_t>(44);

	IMaterial *pMatGlowColor = Interfaces::MaterialSystem()->FindMaterial("dev/glow_color", TEXTURE_GROUP_OTHER, true);
	Interfaces::ModelRender()->ForcedMaterialOverride(pMatGlowColor);

	if (Interfaces::g_GlowObjManager && Interfaces::Engine()->IsConnected())
	{
		auto local = Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
		if (local)
		{
			for (int i = 0; i < Interfaces::g_GlowObjManager->m_GlowObjectDefinitions.Count(); ++i)
			{
				Color color;

				if (Interfaces::g_GlowObjManager->m_GlowObjectDefinitions[i].IsUnused() || !Interfaces::g_GlowObjManager->m_GlowObjectDefinitions[i].getEnt())
					continue;

				CGlowObjectManager::GlowObjectDefinition_t* glowEnt = &Interfaces::g_GlowObjManager->m_GlowObjectDefinitions[i];

				auto class_id = glowEnt->getEnt()->GetClientClass()->m_ClassID;

				switch (class_id)
				{
				default:
					if (g_Options.Visuals.glow_Weapon && g_Options.Visuals.Enabled)
					{
						if (strstr(glowEnt->getEnt()->GetClientClass()->m_pNetworkName, ("CWeapon")))
							glowEnt->set(g_Options.Color.WeaponGlow[0], g_Options.Color.WeaponGlow[1], g_Options.Color.WeaponGlow[2], g_Options.Visuals.glow_WeaponAplha / 255.f);
					}
					break;

				case 1:
					if (g_Options.Visuals.glow_Weapon && g_Options.Visuals.Enabled)
					{
						glowEnt->set(g_Options.Color.WeaponGlow[0], g_Options.Color.WeaponGlow[1], g_Options.Color.WeaponGlow[2], g_Options.Visuals.glow_WeaponAplha / 255.f);
					}
				case 46:
					if (g_Options.Visuals.glow_Weapon && g_Options.Visuals.Enabled)
					{
						glowEnt->set(g_Options.Color.WeaponGlow[0], g_Options.Color.WeaponGlow[1], g_Options.Color.WeaponGlow[2], g_Options.Visuals.glow_WeaponAplha / 255.f);
					}
					break;


				case 40:
					if (g_Options.Visuals.glowplayer && g_Options.Visuals.Enabled)
					{
						if (!g_Options.Visuals.teamglow && glowEnt->getEnt()->GetTeamNum() == local->GetTeamNum())
							break;

						if (glowEnt->getEnt()->GetTeamNum() == local->GetTeamNum())
							glowEnt->set(g_Options.Color.TeamGlow[0], g_Options.Color.TeamGlow[1], g_Options.Color.TeamGlow[2], g_Options.Visuals.playerglowalpha / 255.f);
						else if (glowEnt->getEnt()->GetTeamNum() != local->GetTeamNum())
							glowEnt->set(g_Options.Color.EnemyGlow[0], g_Options.Color.EnemyGlow[1], g_Options.Color.EnemyGlow[2], g_Options.Visuals.playerglowalpha / 255.f);
					}
					break;
				case 34:
					if (g_Options.Visuals.glow_c4 && g_Options.Visuals.Enabled)
					{
						glowEnt->set(g_Options.Color.C4glow[0], g_Options.Color.C4glow[1], g_Options.Color.C4glow[2], g_Options.Visuals.glow_c4Alpha / 255.f);
					}
					break;
				case 128:
					if (g_Options.Visuals.glow_c4 && g_Options.Visuals.Enabled)
					{
						glowEnt->set(g_Options.Color.C4glow[0], g_Options.Color.C4glow[1], g_Options.Color.C4glow[2], g_Options.Visuals.glow_c4Alpha / 255.f);
					}
					break;
				}
			}
		}
	}

	return ofunc(ecx, pSetup);
}
