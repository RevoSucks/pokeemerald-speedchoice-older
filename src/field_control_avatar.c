#include "global.h"
#include "metatile_behavior.h"
#include "event_data.h"
#include "constants/flags.h"
#include "script.h"
#include "speedchoice.h"

extern u8 EventScript_271EA0[];
extern u8 EventScript_290A49[];
extern u8 EventScript_290A83[];
extern u8 EventScript_290B0F[];
extern u8 EventScript_290B5A[];

extern bool8 PartyHasMonWithSurf(void);
extern bool8 IsPlayerFacingSurfableFishableWater(void);
extern bool8 IsPlayerSurfingNorth(void);

u8 *TryGetFieldMoveScript(int unused, u8 tileNum)
{
	if((FlagGet(FLAG_BADGE05_GET) == TRUE || (CheckSpeedchoiceOption(EARLYSURF, YES) && FlagGet(FLAG_BADGE03_GET))) && PartyHasMonWithSurf() == TRUE && IsPlayerFacingSurfableFishableWater() == TRUE)
		return EventScript_271EA0;

	if(MetatileBehavior_IsWaterfall(tileNum) == TRUE)
	{
		if(FlagGet(FLAG_BADGE08_GET) == TRUE && IsPlayerSurfingNorth() == TRUE)
			return EventScript_290A49;
		else
			return EventScript_290A83;
	}
	return NULL;
}

extern u8 sub_809D1E8(void);

bool32 sub_809C868(void)
{
	if((FlagGet(FLAG_BADGE07_GET) || CheckSpeedchoiceOption(PLOTLESS, KEEP_2) != FALSE) && sub_809D1E8() == 2)
	{
		ScriptContext1_SetupScript(EventScript_290B0F);
		return TRUE;
	}
	return FALSE;
}

bool32 sub_809C89C(void)
{
	if((FlagGet(FLAG_BADGE07_GET) || CheckSpeedchoiceOption(PLOTLESS, KEEP_2) != FALSE) && gMapHeader.mapType == 5 && sub_809D1E8() == 1)
	{
		ScriptContext1_SetupScript(EventScript_290B5A);
		return TRUE;
	}
	return FALSE;
}
