#pragma once
#include "HookIncludes.h"
#include <string>

float flColor[3];
float flVColor[3];


IMaterial* GetCurrentMaterial(int mati)
{
	static IMaterial* mat;

	switch (mati)
	{
	case 3:
		mat = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", nullptr);
		break;
	case 4:
		mat = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/gold", nullptr);
		break;
	case 5:
		mat = Interfaces::MaterialSystem()->FindMaterial("models/player/ct_fbi/ct_fbi_glass", nullptr);
		break;
	case 6:
		mat = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/gloss", nullptr);
		break;
	case 7:
		mat = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_blue", nullptr);
		break;
	default:
		mat = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", nullptr);
		return mat;
		break;
	}
	return mat;
}

IMaterial* GetCurrentZMaterial(int mati)
{
	static IMaterial* zmat;

	switch (mati)
	{
	case 3:
		zmat = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", nullptr);
		zmat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, g_Options.Visuals.XQZ);
		return zmat;
		break;
	case 4:
		zmat = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/gold", nullptr);
		zmat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, g_Options.Visuals.XQZ);
		return zmat;
		break;
	case 5:
		zmat = Interfaces::MaterialSystem()->FindMaterial("models/player/ct_fbi/ct_fbi_glass", nullptr);
		zmat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, g_Options.Visuals.XQZ);
		return zmat;
		break;
	case 6:
		zmat = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/gloss", nullptr);
		zmat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, g_Options.Visuals.XQZ);
		return zmat;
		break;
	case 7:
		zmat = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_blue", nullptr);
		zmat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, g_Options.Visuals.XQZ);
		return zmat;
		break;
	default:
		zmat = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", nullptr);
		return zmat;
		break;
	}
}




void __fastcall hkDrawModelExecute(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
{
	static bool DontDraw = false;
	static auto ofunc = hooks::modelrender.GetOriginalFunction<dme_t>(21);

	IMaterial* zmat = GetCurrentZMaterial(g_Options.Visuals.matierial);
	IMaterial* mat = GetCurrentMaterial(g_Options.Visuals.matierial);

	IMaterial* hmat = GetCurrentMaterial(g_Options.Visuals.matierial);
	IMaterial* wmat = GetCurrentMaterial(g_Options.Visuals.matierial);



	static IMaterial* norm = CreateMaterial(false, true, false);
	static IMaterial* flat = CreateMaterial(false, false, false);
	static IMaterial* wire = CreateMaterial(false, false, true);

	static IMaterial* znorm = CreateMaterial(true, true, false);
	static IMaterial* zflat = CreateMaterial(true, false, false);
	static IMaterial* zwire = CreateMaterial(true, false, true);

	static IMaterial* Outline = CreateMaterial(true, false, true);
	DontDraw = false;

	const char * ModelName = Interfaces::ModelInfo()->GetModelName((model_t*)pInfo.pModel);
	C_BaseEntity* pModelEntity = (C_BaseEntity*)Interfaces::EntityList()->GetClientEntity(pInfo.entity_index);
	C_BaseEntity* pLocal = (C_BaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

	int HandsStyle = g_Options.Visuals.Hands;
	int Chamsweps = g_Options.Visuals.chamswphands;



	if (ModelName && strstr(ModelName, "models/player"))
	{

		if (pModelEntity && pLocal)
		{
			if ((g_Options.Visuals.Teamchams || pModelEntity->GetTeamNum() != pLocal->GetTeamNum()) && g_Options.Visuals.Chams)
			{
				pModelEntity = Interfaces::EntityList()->GetClientEntity(pInfo.entity_index);
				if (pModelEntity->GetTeamNum() != pLocal->GetTeamNum())
				{
					flColor[0] = g_Options.Color.EnemyChamsNVis[0];
					flColor[1] = g_Options.Color.EnemyChamsNVis[1];
					flColor[2] = g_Options.Color.EnemyChamsNVis[2];
					flVColor[0] = g_Options.Color.EnemyChamsVis[0];
					flVColor[1] = g_Options.Color.EnemyChamsVis[1];
					flVColor[2] = g_Options.Color.EnemyChamsVis[2];
				}
				if (pModelEntity->GetTeamNum() == pLocal->GetTeamNum())
				{
					flColor[0] = g_Options.Color.TeamChamsVis[0];
					flColor[1] = g_Options.Color.TeamChamsVis[1];
					flColor[2] = g_Options.Color.TeamChamsVis[2];
					flVColor[0] = g_Options.Color.TeamChamsVis[0];
					flVColor[1] = g_Options.Color.TeamChamsVis[1];
					flVColor[2] = g_Options.Color.TeamChamsVis[2];
				}
				if (pModelEntity)
				{
					if (pModelEntity->IsAlive() && pModelEntity->GetHealth() > 0)
					{
						if (g_Options.Visuals.matierial == 0)
						{
							if (g_Options.Visuals.XQZ)
							{

								Interfaces::RenderView()->SetColorModulation(flColor);
								Interfaces::RenderView()->SetBlend(g_Options.Visuals.champlayeralpha / 100.f);
								Interfaces::ModelRender()->ForcedMaterialOverride(znorm);
								ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
							}
							Interfaces::RenderView()->SetColorModulation(flVColor);
							Interfaces::RenderView()->SetBlend(g_Options.Visuals.champlayeralpha / 100.f);
							Interfaces::ModelRender()->ForcedMaterialOverride(norm);
							ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
						}
						else if (g_Options.Visuals.matierial == 1)
						{
							if (g_Options.Visuals.XQZ)
							{

								Interfaces::RenderView()->SetColorModulation(flColor);
								Interfaces::RenderView()->SetBlend(g_Options.Visuals.champlayeralpha / 100.f);
								Interfaces::ModelRender()->ForcedMaterialOverride(zflat);
								ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
							}
							Interfaces::RenderView()->SetColorModulation(flVColor);
							Interfaces::RenderView()->SetBlend(g_Options.Visuals.champlayeralpha / 100.f);
							Interfaces::ModelRender()->ForcedMaterialOverride(flat);
							ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
						}
						else if (g_Options.Visuals.matierial == 2)
						{
							if (g_Options.Visuals.XQZ)
							{

								Interfaces::RenderView()->SetColorModulation(flColor);
								Interfaces::RenderView()->SetBlend(g_Options.Visuals.champlayeralpha / 100.f);
								Interfaces::ModelRender()->ForcedMaterialOverride(zwire);
								ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
							}
							Interfaces::RenderView()->SetColorModulation(flVColor);
							Interfaces::RenderView()->SetBlend(g_Options.Visuals.champlayeralpha / 100.f);
							Interfaces::ModelRender()->ForcedMaterialOverride(wire);
							ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
						}
						else
						{
							if (g_Options.Visuals.XQZ)
							{

								Interfaces::RenderView()->SetColorModulation(flColor);
								Interfaces::RenderView()->SetBlend(g_Options.Visuals.champlayeralpha / 100.f);
								Interfaces::ModelRender()->ForcedMaterialOverride(zmat);
								ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
							}
							Interfaces::RenderView()->SetColorModulation(flVColor);
							Interfaces::RenderView()->SetBlend(g_Options.Visuals.champlayeralpha / 100.f);
							Interfaces::ModelRender()->ForcedMaterialOverride(mat);
							ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
						}
					}
				}
				if (g_Options.Visuals.chamsHp && g_Options.Visuals.Chams && g_Options.Visuals.Enabled)
				{
					float color1[3] = { 0.f, 1.f, 0.f };
					float color2[3] = { 1.f, 1.f, 0.f };
					float color3[3] = { 1.f, 0.f, 0.f };

					float alpha = 1.f;
					if (pModelEntity->HasGunGameImmunity())
						alpha = 0, 1.f;

					if (pModelEntity->IsAlive() && pModelEntity->GetHealth() > 0 && pModelEntity->GetTeamNum() != pLocal->GetTeamNum() && pModelEntity != pLocal)
					{

						if (pModelEntity->IsAlive() && pModelEntity->GetHealth() > 50)
						{
							Interfaces::RenderView()->SetColorModulation(color1);
							Interfaces::RenderView()->SetBlend(alpha);
							Interfaces::ModelRender()->ForcedMaterialOverride(norm);
							ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
						}
						else if (pModelEntity->IsAlive() && pModelEntity->GetHealth() < 50 && pModelEntity->GetHealth() > 25)
						{
							Interfaces::RenderView()->SetColorModulation(color2);
							Interfaces::RenderView()->SetBlend(alpha);
							Interfaces::ModelRender()->ForcedMaterialOverride(norm);
							ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
						}
						else if (pModelEntity->IsAlive() && pModelEntity->GetHealth() < 25)
						{
							Interfaces::RenderView()->SetColorModulation(color3);
							Interfaces::RenderView()->SetBlend(alpha);
							Interfaces::ModelRender()->ForcedMaterialOverride(norm);
							ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
						}

					}
					else if (pModelEntity->IsAlive() && pModelEntity->GetHealth() > 0 && g_Options.Visuals.Teamchams && pModelEntity != pLocal)
					{
						if (pModelEntity->GetTeamNum() == pLocal->GetTeamNum())
						{
							if (pModelEntity->IsAlive() && pModelEntity->GetHealth() > 50)
							{
								Interfaces::RenderView()->SetColorModulation(color1);
								Interfaces::RenderView()->SetBlend(alpha);
								Interfaces::ModelRender()->ForcedMaterialOverride(norm);
								ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
							}
							else if (pModelEntity->IsAlive() && pModelEntity->GetHealth() < 50 && pModelEntity->GetHealth() > 25)
							{
								Interfaces::RenderView()->SetColorModulation(color2);
								Interfaces::RenderView()->SetBlend(alpha);
								Interfaces::ModelRender()->ForcedMaterialOverride(norm);
								ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
							}
							else if (pModelEntity->IsAlive() && pModelEntity->GetHealth() < 25)
							{
								Interfaces::RenderView()->SetColorModulation(color3);
								Interfaces::RenderView()->SetBlend(alpha);
								Interfaces::ModelRender()->ForcedMaterialOverride(norm);
								ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
							}
						}
					}

				}
			}

		}


		if (pModelEntity == pLocal)
		{
			if (pLocal->IsScoped() && pModelEntity->EntIndex() == Interfaces::Engine()->GetLocalPlayer() && Interfaces::Input()->m_fCameraInThirdPerson  && g_Options.Misc.transparency)
			{
				Interfaces::RenderView()->SetBlend(0.7);
			}
		}

	}

	else if (HandsStyle != 0 && g_Options.Visuals.Enabled && strstr(ModelName, "arms"))
	{
		if (HandsStyle == 1)
		{
			DontDraw = true;
		}


		if (HandsStyle == 2)
		{
			Interfaces::RenderView()->SetBlend(0.3);
		}


		if (HandsStyle == 3)
		{
			IMaterial* WireFrameHands = Interfaces::MaterialSystem()->FindMaterial(ModelName, "Model textures");
			WireFrameHands->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
			Interfaces::ModelRender()->ForcedMaterialOverride(WireFrameHands);
		}

		if (HandsStyle == 4)
		{
			Color colorchamshands = Color(g_Options.Color.HandCham[0] * 255, g_Options.Color.HandCham[1] * 255, g_Options.Color.HandCham[2] * 255, g_Options.Color.HandCham[3] * 255);
			ForceMaterial(colorchamshands, norm);
			norm->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
		}


	}

	else if (Chamsweps != 0 && g_Options.Visuals.Enabled && strstr(ModelName, "weapons/v"))
	{
		if (!strstr(ModelName, "arms"))
		{

			if (Chamsweps == 1)
			{
				Interfaces::RenderView()->SetBlend(0.3);
			}

			if (Chamsweps == 2)
			{

				IMaterial* WireFrameWeps = Interfaces::MaterialSystem()->FindMaterial(ModelName, "Model textures");
				WireFrameWeps->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
				Interfaces::ModelRender()->ForcedMaterialOverride(WireFrameWeps);

			}

		}

	}


	if (!DontDraw)
		ofunc(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
		Interfaces::ModelRender()->ForcedMaterialOverride(NULL);

	

}
