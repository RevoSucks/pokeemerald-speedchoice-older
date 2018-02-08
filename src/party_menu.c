#include "global.h"
#include "menu.h"
#include "text.h"
#include "task.h"
#include "menu_helpers.h"
#include "sound.h"
#include "event_data.h"
#include "link.h"
#include "overworld.h"
#include "string_util.h"
#include "speedchoice.h"
#include "constants/flags.h"

extern void (*gUnknown_0203CEC8)(void);

struct PokeMenuFieldMoveFunc
{
    bool8 (*func)(void);
    u8 field_1;
};

struct SomeStruct
{
    u8 filler[0xC];
    u8 unkC;
    u8 unkD;
    u8 fillerE;
    u8 arr[0x208]; // unknown size
 /*0x218*/ u16 unkFoo;
};

extern struct SomeStruct *gUnknown_0203CEC4;
//extern u8 **gUnknown_0203CEC4[];
extern struct PokeMenuFieldMoveFunc gUnknown_08615D9C[];
extern void display_pokemon_menu_message(u8 field_1);
extern void sub_81B1B5C(u8 *str, int var);
extern void sub_8161560(u8 taskId);
extern void sub_81B5674(u8 taskId);
extern void sub_81B12C0(u8 taskId);
extern void sub_81B1C1C(u8 taskId);
extern void task_brm_cancel_1_on_keypad_a_or_b(u8 taskId);
extern u8 *sub_81245DC(u8 *dest, int mapSecId);
extern void sub_81B302C(u8 *ptr);
extern void sub_81B57DC(void);
extern void sub_81B5864(void);

extern u8 gText_CantUseUntilNewBadge[];
extern u8 gText_ReturnToHealingSpot[];
extern u8 gText_EscapeFromHere[];

extern void MCB2_FlyMap(void);
extern void c2_exit_to_overworld_2_switch(void);

void sub_81B5470(u8 taskId)
{
    const struct MapHeader *mapHeader; // this variable must be declared earlier and not when it is assigned much later in order for the function to match.
    int menuPos = GetMenuCursorPos();
    u8 flag = gUnknown_0203CEC4->arr[(u8)menuPos] - 0x13;

    PlaySE(5);

    if(gUnknown_08615D9C[flag].func != NULL)
    {
        sub_81B302C(&gUnknown_0203CEC4->unkC);
        sub_81B302C(&gUnknown_0203CEC4->unkD);

        if(sub_81221AC() == TRUE || InUnionRoom() == TRUE)
        {
            if((u8)(flag - 0xB) < 2)
                display_pokemon_menu_message(0xD);
            else
                display_pokemon_menu_message(gUnknown_08615D9C[flag].field_1);
            gTasks[taskId].func = task_brm_cancel_1_on_keypad_a_or_b;
        }
        else // _081B54E8
        {
			// field moves are 0 indexed, so the 5th HM field move (Surf) is 4, and so on.
            if(flag < 8 && (FlagGet(flag + FLAG_BADGE01_GET) != TRUE && !(flag == 4 && CheckSpeedchoiceOption(EARLYSURF, YES) == TRUE && FlagGet(FLAG_BADGE03_GET)) && !(flag == 5 && CheckSpeedchoiceOption(EARLYFLY, YES) == TRUE) && !(flag == 6 && CheckSpeedchoiceOption(PLOTLESS, KEEP_2) == FALSE)))
            {
                // the player cannot use the HM move due to a lack of the correct badge.
                sub_81B1B5C(gText_CantUseUntilNewBadge, 1);
                gTasks[taskId].func = sub_81B1C1C;
                return;
            }
            else // _081B5524
            {
                if(gUnknown_08615D9C[flag].func() == TRUE)
                {
                    switch(flag - 5)
                    {
                        case 6:
                        case 7:
                            sub_8161560(taskId);
                            break;
                        case 3:
                            mapHeader = get_mapheader_by_bank_and_number(gSaveBlock1Ptr->warp3.mapGroup, gSaveBlock1Ptr->warp3.mapNum);
                            sub_81245DC(gStringVar1, mapHeader->regionMapSectionId);
                            StringExpandPlaceholders(gStringVar4, gText_ReturnToHealingSpot);
                            sub_81B5674(taskId);
                            gUnknown_0203CEC4->unkFoo = flag;
                            break;
                        case 4:
                            mapHeader = get_mapheader_by_bank_and_number(gSaveBlock1Ptr->warp4.mapGroup, gSaveBlock1Ptr->warp4.mapNum);
                            sub_81245DC(gStringVar1, mapHeader->regionMapSectionId);
                            StringExpandPlaceholders(gStringVar4, gText_EscapeFromHere);
                            sub_81B5674(taskId);
                            gUnknown_0203CEC4->unkFoo = flag;
                            break;
                        case 0:
                            gUnknown_0203CEC8 = MCB2_FlyMap;
                            sub_81B12C0(taskId);
                            break;
                        default:
                        case 1:
                        case 2:
                        case 5:
                            gUnknown_0203CEC8 = c2_exit_to_overworld_2_switch;
                            sub_81B12C0(taskId);
                            break;
                    }
                    return;
                }
                else // _081B563C
                {
                    switch(flag)
                    {
                        case 4:
                            sub_81B5864();
                            break;
                        case 1:
                            sub_81B57DC();
                            break;                        
                        default:
                            display_pokemon_menu_message(gUnknown_08615D9C[flag].field_1);
                            break;
                    }
                }
            }
            gTasks[taskId].func = task_brm_cancel_1_on_keypad_a_or_b;
        }
        // _081B5656
    }
}
