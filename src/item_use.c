#include "global.h"
#include "battle.h"
#include "berry.h"
#include "bike.h"
#include "coins.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/songs.h"
#include "constants/vars.h"
#include "data2.h"
#include "event_data.h"
#include "fieldmap.h"
#include "field_map_obj.h"
#include "field_player_avatar.h"
#include "field_screen.h"
#include "field_weather.h"
#include "item.h"
#include "field_map_obj_helpers.h"
#include "mail.h"
#include "metatile_behavior.h"
#include "overworld.h"
#include "palette.h"
#include "pokemon.h"
#include "rom_818CFC8.h"
#include "script.h"
#include "sound.h"
#include "string_util.h"
#include "task.h"
#include "text.h"

extern u16 gSpecialVar_ItemId;
extern void(**gUnknown_0203CE54)(void);
extern void(**gUnknown_0203CF2C)(void);
extern void(*gUnknown_0203A0F4)(u8 taskId);
extern void(*gUnknown_085920D8[])(void);
extern void (*gUnknown_03006328)(u8, u16, TaskFunc);
extern void unknown_ItemMenu_Confirm(u8 taskId);
extern void sub_81C5B14(u8 taskId);
extern u8 gText_DadsAdvice[];
extern u8 gText_CantDismountBike[];
extern void sub_8197434(u8 a, u8 b);
extern void sub_80984F4(void);
extern void ItemUseOutOfBattle_TMHM(u8 a);
extern void ItemUseOutOfBattle_EvolutionStone(u8 b);
extern void bag_menu_mail_related(void);
extern void OpenPokeblockCase(u8 a, void(*b)(void));
extern void overworld_free_bg_tilemaps(void);
extern bool32 sav1_map_is_biking_allowed(void);
extern bool8 IsPlayerFacingSurfableFishableWater(void);
extern bool8 sub_81221AC(void);
extern u8 gText_ItemFinderNothing[];
extern u8 gText_ItemFinderNearby[];
extern u8 gText_ItemFinderOnTop[];
extern u8 gText_CoinCase[];
extern u8 gText_PowderQty[];
extern u8 gUnknown_085920E4[];
extern u8 Route102_EventScript_274482[];
extern u8 Route102_EventScript_2744C0[];
extern u8 BattleFrontier_OutsideEast_EventScript_242CFC[];
extern u8 gText_BootedUpHM[];
extern u8 gText_BootedUpTM[];
extern u8 gText_TMHMContainedVar1[];
extern u8 gText_PlayerUsedVar2[];
extern u8 gText_RepelEffectsLingered[];
extern u8 gText_UsedVar2WildLured[];
extern u8 gText_UsedVar2WildRepelled[];
extern u8 gText_BoxFull[];
extern u8 gText_WontHaveEffect[];
extern int sub_80247BC(void);
extern struct MapHeader* mapconnection_get_mapheader(struct MapConnection *connection);
extern void SetUpItemUseCallback(u8 taskId);
extern void ItemUseCB_Medicine(u8, u16, TaskFunc);
extern void sub_81B67C8(u8, u16, TaskFunc);
extern void sub_81B79E8(u8, u16, TaskFunc);
extern void dp05_ether(u8, u16, TaskFunc);
extern void dp05_pp_up(u8, u16, TaskFunc);
extern void dp05_rare_candy(u8, u16, TaskFunc);
extern void sub_81B6DC4(u8, u16, TaskFunc);
extern void sub_81B7C74(u8, u16, TaskFunc);
extern u16 ItemIdToBattleMoveId(u16);
extern void bag_menu_yes_no(u8, u8, void(**)(u8 taskId));
extern void (*gUnknown_085920E8[])(u8 taskId);
extern void sub_81C5924(void);
extern void sub_81C59BC(void);
extern void sub_81AB9A8(u8);
extern void sub_81ABA88(u8);
extern void sub_80B7CC8(void);
extern void flagmods_08054D70(void);
extern u8* sub_806CF78(u16);
extern bool8 ExecuteTableBasedItemEffect_(struct Pokemon*, u16, u8, u8);
extern u8 gBankInMenu;
extern u16 gBattlePartyID[];
extern void sub_81B89F0(void);
extern u8 GetItemEffectType(u16);

void MapPostLoadHook_UseItem(void);
extern void sub_80AF6D4(void);
void Task_CallItemUseOnFieldCallback(u8 taskId);
void bag_menu_inits_lists_menu(u8 taskId);
void ItemUseOnFieldCB_Bike(u8 taskId);
void ItemUseOnFieldCB_Rod(u8 taskId);
void ItemUseOnFieldCB_Itemfinder(u8 taskId);
void sub_80FD504(u8 taskId);
void sub_80FD5CC(u8 taskId);
void sub_80FDA94(u8 taskId);
void sub_80FDADC(u8 taskId);
void sub_80FD7C8(u8 taskId);
void sub_80FDC00(u8 taskId);
void sub_80FDD74(u8 taskId);
void sub_80FDE08(u8 taskId);
void sub_80FDE7C(u8 taskId);
void sub_80FDF90(u8 taskId);
void task08_0809AD8C(u8 taskId);
void sub_80FE024(u8 taskId);
void sub_80FE124(u8 taskId);
void sub_80FE164(u8 taskId);

void DisplayItemMessage(u8 taskId, u8 a, u8* str, void(*callback)(u8 taskId));
void DisplayItemMessageInBattlePyramid(u8 taskId, u8* str, void(*callback)(u8 taskId));
void DisplayItemMessageOnField(u8 taskId, u8* str, void(*callback)(u8 taskId));
void sub_81C6714(u8 taskId);
void CleanUpAfterFailingToUseRegisteredKeyItemOnField(u8 taskId);
void StartFishing(u8 a);
bool8 ItemfinderCheckForHiddenItems(struct MapEvents *, u8);
u8 sub_80FD9B0(s16 a, s16 b);
void sub_80FDA24(u8 a);
void sub_80FD8E0(u8 taskId, s16 x, s16 y);
void sub_80FDBEC(void);
bool8 sub_80FDE2C(void);
void ItemUseOutOfBattle_CannotUse(u8 taskId);

void SetUpItemUseCallback(u8 taskId)
{
    u8 type;
    if (gSpecialVar_ItemId == ITEM_ENIGMA_BERRY)
        type = gTasks[taskId].data[4] - 1;
    else
        type = ItemId_GetType(gSpecialVar_ItemId) - 1;
    if (!InBattlePyramid())
    {
        *gUnknown_0203CE54 = gUnknown_085920D8[type];
        unknown_ItemMenu_Confirm(taskId);
    }
    else
    {
        *gUnknown_0203CF2C = gUnknown_085920D8[type];
        sub_81C5B14(taskId);
    }
}

void SetUpItemUseOnFieldCallback(u8 taskId)
{
    if (gTasks[taskId].data[3] != 1)
    {
        gFieldCallback = MapPostLoadHook_UseItem;
        SetUpItemUseCallback(taskId);
    }
    else
        gUnknown_0203A0F4(taskId);
}

void MapPostLoadHook_UseItem(void)
{
    pal_fill_black();
    CreateTask(Task_CallItemUseOnFieldCallback, 8);
}

void Task_CallItemUseOnFieldCallback(u8 taskId)
{
    if (sub_80ABDFC() == 1)
        gUnknown_0203A0F4(taskId);
}

void DisplayCannotUseItemMessage(u8 taskId, bool8 isUsingRegisteredKeyItemOnField, const u8 *str)
{
    StringExpandPlaceholders(gStringVar4, str);
    if (!isUsingRegisteredKeyItemOnField)
    {
        if (!InBattlePyramid())
            DisplayItemMessage(taskId, 1, gStringVar4, bag_menu_inits_lists_menu);
        else
            DisplayItemMessageInBattlePyramid(taskId, gText_DadsAdvice, sub_81C6714);
    }
    else
        DisplayItemMessageOnField(taskId, gStringVar4, CleanUpAfterFailingToUseRegisteredKeyItemOnField);
}

void DisplayDadsAdviceCannotUseItemMessage(u8 taskId, bool8 isUsingRegisteredKeyItemOnField)
{
    DisplayCannotUseItemMessage(taskId, isUsingRegisteredKeyItemOnField, gText_DadsAdvice);
}

void DisplayCannotDismountBikeMessage(u8 taskId, bool8 isUsingRegisteredKeyItemOnField)
{
    DisplayCannotUseItemMessage(taskId, isUsingRegisteredKeyItemOnField, gText_CantDismountBike);
}

void CleanUpAfterFailingToUseRegisteredKeyItemOnField(u8 taskId)
{
    sub_8197434(0, 1);
    DestroyTask(taskId);
    sub_80984F4();
    ScriptContext2_Disable();
}

u8 CheckIfItemIsTMHMOrEvolutionStone(u16 itemId)
{
    if (ItemId_GetFieldFunc(itemId) == ItemUseOutOfBattle_TMHM)
        return 1;
    else if (ItemId_GetFieldFunc(itemId) == ItemUseOutOfBattle_EvolutionStone)
        return 2;
    else
        return 0;
}

void sub_80FD254()
{
    struct MailStruct mail;
    mail.itemId = gSpecialVar_ItemId;
    ReadMail(&mail, bag_menu_mail_related, 0);
}

void ItemUseOutOfBattle_Mail(u8 taskId)
{
    *gUnknown_0203CE54 = sub_80FD254;
    unknown_ItemMenu_Confirm(taskId);
}

void ItemUseOutOfBattle_Bike(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    s16 coordsY;
    s16 coordsX;
    u8 behavior;
    PlayerGetDestCoords(&coordsX, &coordsY);
    behavior = MapGridGetMetatileBehaviorAt(coordsX, coordsY);
    if (FlagGet(FLAG_SYS_CYCLING_ROAD) == TRUE || MetatileBehavior_IsVerticalRail(behavior) == TRUE || MetatileBehavior_IsHorizontalRail(behavior) == TRUE || MetatileBehavior_IsIsolatedVerticalRail(behavior) == TRUE || MetatileBehavior_IsIsolatedHorizontalRail(behavior) == TRUE)
        DisplayCannotDismountBikeMessage(taskId, data[3]);
    else
    {
        if (sav1_map_is_biking_allowed() == TRUE && IsBikingDisallowedByPlayer() == 0)
        {
            gUnknown_0203A0F4 = ItemUseOnFieldCB_Bike;
            SetUpItemUseOnFieldCallback(taskId);
        }
        else
            DisplayDadsAdviceCannotUseItemMessage(taskId, data[3]);
    }
}

void ItemUseOnFieldCB_Bike(u8 taskId)
{
    if (!ItemId_GetSecondaryId(gSpecialVar_ItemId))
        GetOnOffBike(2);
    else
        GetOnOffBike(4);
    sub_80984F4();
    ScriptContext2_Disable();
    DestroyTask(taskId);
}

bool32 CanFish()
{
    s16 x, y;
    u16 tileBehavior;

    GetXYCoordsOneStepInFrontOfPlayer(&x, &y);
    tileBehavior = MapGridGetMetatileBehaviorAt(x, y);

    if (MetatileBehavior_IsWaterfall(tileBehavior))
        return FALSE;

    if (TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_4))
        return FALSE;

    if (!TestPlayerAvatarFlags(PLAYER_AVATAR_FLAG_SURFING))
    {
        if (IsPlayerFacingSurfableFishableWater())
            return TRUE;
    }
    else
    {
        if (MetatileBehavior_IsSurfableWaterOrUnderwater(tileBehavior) && !MapGridIsImpassableAt(x, y))
            return TRUE;
        if (MetatileBehavior_8089510(tileBehavior) == TRUE)
            return TRUE;
    }

    return FALSE;
}

void ItemUseOutOfBattle_Rod(u8 taskId)
{
    if (CanFish() == TRUE)
    {
        gUnknown_0203A0F4 = ItemUseOnFieldCB_Rod;
        SetUpItemUseOnFieldCallback(taskId);
    }
    else
        DisplayDadsAdviceCannotUseItemMessage(taskId, gTasks[taskId].data[3]);
}

void ItemUseOnFieldCB_Rod(u8 taskId)
{
    StartFishing(ItemId_GetSecondaryId(gSpecialVar_ItemId));
    DestroyTask(taskId);
}

void ItemUseOutOfBattle_Itemfinder(u8 var)
{
    IncrementGameStat(0x27);
    gUnknown_0203A0F4 = ItemUseOnFieldCB_Itemfinder;
    SetUpItemUseOnFieldCallback(var);
}

void ItemUseOnFieldCB_Itemfinder(u8 taskId)
{
    if (ItemfinderCheckForHiddenItems(gMapHeader.events, taskId) == TRUE)
        gTasks[taskId].func = sub_80FD504;
    else
        DisplayItemMessageOnField(taskId, gText_ItemFinderNothing, sub_80FD5CC);
}

void sub_80FD504(u8 taskId)
{
    u8 playerDir;
    u8 playerDirToItem;
    u8 i;
    s16* data = gTasks[taskId].data;
    if (!data[3])
    {
        if (data[4] == 4)
        {
            playerDirToItem = sub_80FD9B0(data[0], data[1]);
            if (playerDirToItem)
            {
                sub_80FDA24(gUnknown_085920E4[playerDirToItem - 1]);
                gTasks[taskId].func = sub_80FDA94;
            }
            else
            {
                playerDir = player_get_direction_lower_nybble();
                for (i = 0; i < 4; i++)
                {
                    if (playerDir == gUnknown_085920E4[i])
                        data[5] = (i + 1) & 3;
                }
                gTasks[taskId].func = sub_80FDADC;
                data[3] = 0;
                data[2] = 0;
            }
            return;
        }
        PlaySE(SE_DAUGI);
        data[4]++;
    }
    data[3] = (data[3] + 1) & 0x1F;
}

void sub_80FD5CC(u8 taskId)
{
    sub_8197434(0, 1);
    sub_80984F4();
    ScriptContext2_Disable();
    DestroyTask(taskId);
}

bool8 ItemfinderCheckForHiddenItems(struct MapEvents *events, u8 taskId)
{
    int distanceX, distanceY;
    s16 x, y, i, newDistanceX, newDistanceY;
    PlayerGetDestCoords(&x, &y);
    gTasks[taskId].data[2] = FALSE;
    for (i = 0; i < events->bgEventCount; i++)
    {
        if (events->bgEvents[i].kind == 7 && !FlagGet(events->bgEvents[i].bgUnion.hiddenItem.hiddenItemId + 0x1F4))
        {
            distanceX = (u16)events->bgEvents[i].x + 7;
            newDistanceX = distanceX - x;
            distanceY = (u16)events->bgEvents[i].y + 7;
            newDistanceY = distanceY - y;
            
            if ((u16)(newDistanceX + 7) < 15 && (newDistanceY >= -5) && (newDistanceY < 6))
                sub_80FD8E0(taskId, newDistanceX, newDistanceY);
        }
    }
    
    sub_80FD7C8(taskId);
    if (gTasks[taskId].data[2] == TRUE)
        return TRUE;
    else
        return FALSE;
}

bool8 sub_80FD6D4(struct MapEvents *events, s16 x, s16 y)
{
    u8 bgEventCount = events->bgEventCount;
    struct BgEvent *bgEvent = events->bgEvents;
    int i;

    for (i = 0; i < bgEventCount; i++)
    {
        if (bgEvent[i].kind == 7 && x == (u16)bgEvent[i].x && y == (u16)bgEvent[i].y) // hidden item and coordinates matches x and y passed?
        {
            if (!FlagGet(bgEvent[i].bgUnion.hiddenItem.hiddenItemId + 0x1F4))
                return TRUE;
            else
                return FALSE;
        }
    }
    return FALSE;
}

bool8 sub_80FD730(struct MapConnection *connection, int x, int y)
{
    struct MapHeader *mapHeader;
    u16 localX, localY;
    u32 localOffset;
    s32 localLength;

    mapHeader = mapconnection_get_mapheader(connection);

    switch (connection->direction)
    {
    // same weird temp variable behavior seen in sub_80FD6D4
    case 2:
        localOffset = connection->offset + 7;
        localX = x - localOffset;
        localLength = mapHeader->mapData->height - 7;
        localY = localLength + y; // additions are reversed for some reason
        break;
    case 1:
        localOffset = connection->offset + 7;
        localX = x - localOffset;
        localLength = gMapHeader.mapData->height + 7;
        localY = y - localLength;
        break;
    case 3:
        localLength = mapHeader->mapData->width - 7;
        localX = localLength + x; // additions are reversed for some reason
        localOffset = connection->offset + 7;
        localY = y - localOffset;
        break;
    case 4:
        localLength = gMapHeader.mapData->width + 7;
        localX = x - localLength;
        localOffset = connection->offset + 7;
        localY = y - localOffset;
        break;
    default:
        return FALSE;
    }
    return sub_80FD6D4(mapHeader->events, localX, localY);
}

// weird math
#ifdef NONMATCHING
void sub_80FD7C8(u8 taskId)
{
    s16 x, y;
    s16 curX, curY;
    s16 width = gMapHeader.mapData->width + 7;
    s16 height = gMapHeader.mapData->height + 7;

    PlayerGetDestCoords(&x, &y);

    for (curX = x - 7; curX <= x + 7; curX++)
    {
        for (curY = y - 5; curY <= y + 5; curY++)
        {
            if (7 > curX
             || curX >= width
             || 7 > curY
             || curY >= height)
            {
                struct MapConnection *conn = sub_8088A8C(curX, curY);
                if (conn && sub_80FD730(conn, curX, curY) == TRUE)
                    sub_80FD8E0(taskId, curX - x, curY - y);
            }
        }
    }
}
#else
__attribute__((naked))
void sub_80FD7C8(u8 taskId)
{
    asm(".syntax unified\n\
    push {r4-r7,lr}\n\
	mov r7, r10\n\
	mov r6, r9\n\
	mov r5, r8\n\
	push {r5-r7}\n\
	sub sp, 0x14\n\
	lsls r0, 24\n\
	lsrs r0, 24\n\
	str r0, [sp, 0x4]\n\
	ldr r0, =gMapHeader\n\
	ldr r1, [r0]\n\
	ldr r0, [r1]\n\
	adds r0, 0x7\n\
	lsls r0, 16\n\
	lsrs r0, 16\n\
	str r0, [sp, 0x8]\n\
	ldr r0, [r1, 0x4]\n\
	adds r0, 0x7\n\
	lsls r0, 16\n\
	lsrs r0, 16\n\
	str r0, [sp, 0xC]\n\
	mov r4, sp\n\
	adds r4, 0x2\n\
	mov r0, sp\n\
	adds r1, r4, 0\n\
	bl PlayerGetDestCoords\n\
	mov r0, sp\n\
	ldrh r0, [r0]\n\
	subs r0, 0x7\n\
	lsls r0, 16\n\
	lsrs r3, r0, 16\n\
	asrs r0, 16\n\
	mov r1, sp\n\
	movs r2, 0\n\
	ldrsh r1, [r1, r2]\n\
	adds r1, 0x7\n\
	cmp r0, r1\n\
	bgt _080FD8CC\n\
_080FD816:\n\
	mov r5, sp\n\
	ldrh r0, [r5, 0x2]\n\
	subs r0, 0x5\n\
	lsls r0, 16\n\
	lsrs r4, r0, 16\n\
	lsls r2, r4, 16\n\
	asrs r1, r2, 16\n\
	movs r6, 0x2\n\
	ldrsh r0, [r5, r6]\n\
	adds r0, 0x5\n\
	lsls r3, 16\n\
	mov r8, r3\n\
	cmp r1, r0\n\
	bgt _080FD8B6\n\
	movs r0, 0x7\n\
	str r0, [sp, 0x10]\n\
	mov r1, r8\n\
	asrs r1, 16\n\
	mov r9, r1\n\
	mov r10, r0\n\
_080FD83E:\n\
	ldr r3, [sp, 0x10]\n\
	cmp r3, r9\n\
	bgt _080FD860\n\
	ldr r5, [sp, 0x8]\n\
	lsls r0, r5, 16\n\
	asrs r0, 16\n\
	cmp r9, r0\n\
	bge _080FD860\n\
	asrs r1, r2, 16\n\
	cmp r10, r1\n\
	bgt _080FD860\n\
	ldr r6, [sp, 0xC]\n\
	lsls r0, r6, 16\n\
	asrs r0, 16\n\
	lsls r7, r4, 16\n\
	cmp r1, r0\n\
	blt _080FD89E\n\
_080FD860:\n\
	mov r0, r8\n\
	asrs r5, r0, 16\n\
	lsls r4, 16\n\
	asrs r6, r4, 16\n\
	adds r0, r5, 0\n\
	adds r1, r6, 0\n\
	bl sub_8088A8C\n\
	adds r7, r4, 0\n\
	cmp r0, 0\n\
	beq _080FD89E\n\
	adds r1, r5, 0\n\
	adds r2, r6, 0\n\
	bl sub_80FD730\n\
	lsls r0, 24\n\
	lsrs r0, 24\n\
	cmp r0, 0x1\n\
	bne _080FD89E\n\
	mov r0, sp\n\
	ldrh r1, [r0]\n\
	subs r1, r5, r1\n\
	lsls r1, 16\n\
	asrs r1, 16\n\
	ldrh r2, [r0, 0x2]\n\
	subs r2, r6, r2\n\
	lsls r2, 16\n\
	asrs r2, 16\n\
	ldr r0, [sp, 0x4]\n\
	bl sub_80FD8E0\n\
_080FD89E:\n\
	movs r1, 0x80\n\
	lsls r1, 9\n\
	adds r0, r7, r1\n\
	lsrs r4, r0, 16\n\
	lsls r2, r4, 16\n\
	asrs r1, r2, 16\n\
	mov r3, sp\n\
	movs r5, 0x2\n\
	ldrsh r0, [r3, r5]\n\
	adds r0, 0x5\n\
	cmp r1, r0\n\
	ble _080FD83E\n\
_080FD8B6:\n\
	movs r1, 0x80\n\
	lsls r1, 9\n\
	add r1, r8\n\
	lsrs r3, r1, 16\n\
	asrs r1, 16\n\
	mov r0, sp\n\
	movs r6, 0\n\
	ldrsh r0, [r0, r6]\n\
	adds r0, 0x7\n\
	cmp r1, r0\n\
	ble _080FD816\n\
_080FD8CC:\n\
	add sp, 0x14\n\
	pop {r3-r5}\n\
	mov r8, r3\n\
	mov r9, r4\n\
	mov r10, r5\n\
	pop {r4-r7}\n\
	pop {r0}\n\
	bx r0\n\
	.pool\n\
    .syntax divided\n");
}
#endif

void sub_80FD8E0(u8 taskId, s16 x, s16 y)
{
    s16 *data = gTasks[taskId].data;
    s16 var1, var2, var3, var4;

    if (data[2] == FALSE)
    {
        data[0] = x;
        data[1] = y;
        data[2] = TRUE;
    }
    else
    {
        // data[0] and data[1] contain the player's coordinates.
        // x and y contain the item's coordinates.
        if (data[0] < 0)
            var1 = data[0] * -1; // item is to the left
        else
            var1 = data[0]; // item is to the right

        if (data[1] < 0)
            var2 = data[1] * -1; // item is to the north
        else
            var2 = data[1]; // item is to the south

        if (x < 0)
            var3 = x * -1;
        else
            var3 = x;

        if (y < 0)
            var4 = y * -1;
        else
            var4 = y;

        if (var1 + var2 > var3 + var4)
        {
            data[0] = x;
            data[1] = y;
        }
        else
        {
            if (var1 + var2 == var3 + var4 && (var2 > var4 || (var2 == var4 && data[1] < y)))
            {
                data[0] = x;
                data[1] = y;
            }
        }
    }
}

u8 sub_80FD9B0(s16 itemX, s16 itemY)
{
    s16 abX, abY;

    if (itemX == 0 && itemY == 0)
        return DIR_NONE; // player is standing on the item.

    // get absolute X distance.
    if (itemX < 0)
        abX = itemX * -1;
    else
        abX = itemX;

    // get absolute Y distance.
    if (itemY < 0)
        abY = itemY * -1;
    else
        abY = itemY;

    if (abX > abY)
    {
        if (itemX < 0)
            return DIR_EAST;
        else
            return DIR_NORTH;
    }
    else
    {
        if (abX < abY)
        {
            if (itemY < 0)
                return DIR_SOUTH;
            else
                return DIR_WEST;
        }
        if (abX == abY)
        {
            if (itemY < 0)
                return DIR_SOUTH;
            else
                return DIR_WEST;
        }
        return DIR_NONE; // should never get here. return something so it doesnt crash.
    }
}

void sub_80FDA24(u8 direction)
{
    FieldObjectClearAnimIfSpecialAnimFinished(&gMapObjects[GetFieldObjectIdByLocalIdAndMap(0xFF, 0, 0)]);
    FieldObjectClearAnim(&gMapObjects[GetFieldObjectIdByLocalIdAndMap(0xFF, 0, 0)]);
    npc_sync_anim_pause_bits(&gMapObjects[GetFieldObjectIdByLocalIdAndMap(0xFF, 0, 0)]);
    PlayerTurnInPlace(direction);
}

void sub_80FDA94(u8 taskId)
{
    if (FieldObjectCheckIfSpecialAnimFinishedOrInactive(&gMapObjects[GetFieldObjectIdByLocalIdAndMap(0xFF, 0, 0)]) == TRUE)
        DisplayItemMessageOnField(taskId, gText_ItemFinderNearby, sub_80FD5CC);
}

void sub_80FDADC(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (FieldObjectCheckIfSpecialAnimFinishedOrInactive(&gMapObjects[GetFieldObjectIdByLocalIdAndMap(0xFF, 0, 0)]) == TRUE
    || data[2] == FALSE)
    {
        sub_80FDA24(gUnknown_085920E4[data[5]]);
        data[2] = 1;
        data[5] = (data[5] + 1) & 3;
        data[3]++;

        if (data[3] == 4)
            DisplayItemMessageOnField(taskId, gText_ItemFinderOnTop, sub_80FD5CC);
    }
}

void ItemUseOutOfBattle_PokeblockCase(u8 taskId)
{
    if (sub_81221AC() == TRUE)
    {
        DisplayDadsAdviceCannotUseItemMessage(taskId, gTasks[taskId].data[3]);
    }
    else if (gTasks[taskId].data[3] != TRUE)
    {
        *gUnknown_0203CE54 = sub_80FDBEC;
        unknown_ItemMenu_Confirm(taskId);
    }
    else
    {
        gFieldCallback = sub_80AF6D4;
        FadeScreen(1, 0);
        gTasks[taskId].func = sub_80FDC00;
    }
}

void sub_80FDBEC(void)
{
    OpenPokeblockCase(0, bag_menu_mail_related);
}

void sub_80FDC00(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        overworld_free_bg_tilemaps();
        OpenPokeblockCase(0, c2_exit_to_overworld_2_switch);
        DestroyTask(taskId);
    }
}

void ItemUseOutOfBattle_CoinCase(u8 taskId)
{
    ConvertIntToDecimalStringN(gStringVar1, GetCoins(), 0, 4);
    StringExpandPlaceholders(gStringVar4, gText_CoinCase);

    if (!gTasks[taskId].data[3])
    {
        DisplayItemMessage(taskId, 1, gStringVar4, bag_menu_inits_lists_menu);
    }
    else
    {
        DisplayItemMessageOnField(taskId, gStringVar4, CleanUpAfterFailingToUseRegisteredKeyItemOnField);
    }
}

void ItemUseOutOfBattle_PowderJar(u8 taskId)
{
    ConvertIntToDecimalStringN(gStringVar1, sub_80247BC(), 0, 5);
    StringExpandPlaceholders(gStringVar4, gText_PowderQty);

    if (!gTasks[taskId].data[3])
    {
        DisplayItemMessage(taskId, 1, gStringVar4, bag_menu_inits_lists_menu);
    }
    else
    {
        DisplayItemMessageOnField(taskId, gStringVar4, CleanUpAfterFailingToUseRegisteredKeyItemOnField);
    }
}

void sub_80FDD10(u8 taskId)
{
    if (IsPlayerFacingPlantedBerryTree() == TRUE)
    {
        gUnknown_0203A0F4 = sub_80FDD74;
        gFieldCallback = MapPostLoadHook_UseItem;
        *gUnknown_0203CE54 = c2_exit_to_overworld_2_switch;
        unknown_ItemMenu_Confirm(taskId);
    }
    else
    {
        ItemId_GetFieldFunc(gSpecialVar_ItemId)(taskId);
    }
}

void sub_80FDD74(u8 taskId)
{
    RemoveBagItem(gSpecialVar_ItemId, 1);
    ScriptContext2_Enable();
    ScriptContext1_SetupScript(Route102_EventScript_274482);
    DestroyTask(taskId);
}

void ItemUseOutOfBattle_WailmerPail(u8 taskId)
{
    if (sub_80FDE2C() == TRUE)
    {
        gUnknown_0203A0F4 = sub_80FDE7C;
        SetUpItemUseOnFieldCallback(taskId);
    }
    else if (TryToWaterBerryTree() == TRUE)
    {
        gUnknown_0203A0F4 = sub_80FDE08;
        SetUpItemUseOnFieldCallback(taskId);
    }
    else
    {
        DisplayDadsAdviceCannotUseItemMessage(taskId, gTasks[taskId].data[3]);
    }
}

void sub_80FDE08(u8 taskId)
{
    ScriptContext2_Enable();
    ScriptContext1_SetupScript(Route102_EventScript_2744C0);
    DestroyTask(taskId);
}

bool8 sub_80FDE2C(void)
{
    u16 x, y;
    u8 z;
    u8 objId;
    GetXYCoordsOneStepInFrontOfPlayer(&x, &y);
    z = PlayerGetZCoord();
    objId = GetFieldObjectIdByXYZ(x, y, z);
    if (objId == 16 || gMapObjects[objId].graphicsId != 0xE4)
        return FALSE;
    else
        return TRUE;
}

void sub_80FDE7C(u8 taskId)
{
    ScriptContext2_Enable();
    ScriptContext1_SetupScript(BattleFrontier_OutsideEast_EventScript_242CFC);
    DestroyTask(taskId);
}

void ItemUseOutOfBattle_Medicine(u8 taskId)
{
    gUnknown_03006328 = ItemUseCB_Medicine;
    SetUpItemUseCallback(taskId);
}

void ItemUseOutOfBattle_ReduceEV(u8 taskId)
{
    gUnknown_03006328 = sub_81B67C8;
    SetUpItemUseCallback(taskId);
}

void ItemUseOutOfBattle_SacredAsh(u8 taskId)
{
    gUnknown_03006328 = sub_81B79E8;
    SetUpItemUseCallback(taskId);
}

void ItemUseOutOfBattle_PPRecovery(u8 taskId)
{
    gUnknown_03006328 = dp05_ether;
    SetUpItemUseCallback(taskId);
}

void ItemUseOutOfBattle_PPUp(u8 taskId)
{
    gUnknown_03006328 = dp05_pp_up;
    SetUpItemUseCallback(taskId);
}

void ItemUseOutOfBattle_RareCandy(u8 taskId)
{
    gUnknown_03006328 = dp05_rare_candy;
    SetUpItemUseCallback(taskId);
}

void ItemUseOutOfBattle_TMHM(u8 taskId)
{
    if (gSpecialVar_ItemId >= ITEM_HM01)
        DisplayItemMessage(taskId, 1, gText_BootedUpHM, sub_80FDF90); // HM
    else
        DisplayItemMessage(taskId, 1, gText_BootedUpTM, sub_80FDF90); // TM
}

void sub_80FDF90(u8 taskId)
{
    PlaySE(SE_PC_LOGIN);
    gTasks[taskId].func = task08_0809AD8C;
}

void task08_0809AD8C(u8 taskId)
{
    if (gMain.newKeys & (A_BUTTON | B_BUTTON))
    {
        StringCopy(gStringVar1, gMoveNames[ItemIdToBattleMoveId(gSpecialVar_ItemId)]);
        StringExpandPlaceholders(gStringVar4, gText_TMHMContainedVar1);
        DisplayItemMessage(taskId, 1, gStringVar4, sub_80FE024);
    }
}

void sub_80FE024(u8 taskId)
{
    bag_menu_yes_no(taskId, 6, gUnknown_085920E8);
}

void sub_80FE03C(u8 taskId)
{
    gUnknown_03006328 = sub_81B6DC4;
    SetUpItemUseCallback(taskId);
}

extern bool32 sUsedEscapeOption;

void sub_80FE058(void)
{
	if(sUsedEscapeOption == TRUE)
	{
		CopyItemName(ITEM_ESCAPE_ROPE, gStringVar2);
		StringExpandPlaceholders(gStringVar4, gText_PlayerUsedVar2);
	}
	else
	{
		RemoveBagItem(gSpecialVar_ItemId, 1);
		CopyItemName(gSpecialVar_ItemId, gStringVar2);
		StringExpandPlaceholders(gStringVar4, gText_PlayerUsedVar2);
	}
	sUsedEscapeOption = FALSE;
    if (!InBattlePyramid())
    {
        sub_81AB9A8(ItemId_GetPocket(gSpecialVar_ItemId));
        sub_81ABA88(ItemId_GetPocket(gSpecialVar_ItemId));
    }
    else
    {
        sub_81C5924();
        sub_81C59BC();
    }
}

void ItemUseOutOfBattle_Repel(u8 taskId)
{
    if (VarGet(VAR_REPEL_STEP_COUNT) == 0)
        gTasks[taskId].func = sub_80FE124;
    else if (!InBattlePyramid())
        DisplayItemMessage(taskId, 1, gText_RepelEffectsLingered, bag_menu_inits_lists_menu);
    else
        DisplayItemMessageInBattlePyramid(taskId, gText_RepelEffectsLingered, sub_81C6714);
}

void sub_80FE124(u8 taskId)
{
    s16* data = gTasks[taskId].data;
    
    if (++data[8] > 7)
    {
        data[8] = 0;
        PlaySE(SE_TU_SAA);
        gTasks[taskId].func = sub_80FE164;
    }
}

void sub_80FE164(u8 taskId)
{
    if (!IsSEPlaying())
    {
        VarSet(VAR_REPEL_STEP_COUNT, ItemId_GetHoldEffectParam(gSpecialVar_ItemId));
        sub_80FE058();
        if (!InBattlePyramid())
            DisplayItemMessage(taskId, 1, gStringVar4, bag_menu_inits_lists_menu);
        else
            DisplayItemMessageInBattlePyramid(taskId, gStringVar4, sub_81C6714);
    }
}

void sub_80FE1D0(u8 taskId)
{
    if(++gTasks[taskId].data[8] > 7)
    {
        PlaySE(SE_BIDORO);
        if (!InBattlePyramid())
            DisplayItemMessage(taskId, 1, gStringVar4, bag_menu_inits_lists_menu);
        else
            DisplayItemMessageInBattlePyramid(taskId, gStringVar4, sub_81C6714);
    }
}

void ItemUseOutOfBattle_BlackWhiteFlute(u8 taskId)
{
    CopyItemName(gSpecialVar_ItemId, gStringVar2);
    if (gSpecialVar_ItemId == ITEM_WHITE_FLUTE)
    {
        FlagSet(FLAG_SYS_ENC_UP_ITEM);
        FlagClear(FLAG_SYS_ENC_DOWN_ITEM);
        StringExpandPlaceholders(gStringVar4, gText_UsedVar2WildLured);
    }
    else
    {
        FlagSet(FLAG_SYS_ENC_DOWN_ITEM);
        FlagClear(FLAG_SYS_ENC_UP_ITEM);
        StringExpandPlaceholders(gStringVar4, gText_UsedVar2WildRepelled);
    }
    gTasks[taskId].data[8] = 0;
    gTasks[taskId].func = sub_80FE1D0;
}

void task08_080A1C44(u8 taskId)
{
    player_avatar_init_params_reset();
    sub_80B7CC8();
    DestroyTask(taskId);
}

void re_escape_rope(u8 taskId)
{
    flagmods_08054D70();
    sub_80FE058();
    gTasks[taskId].data[0] = 0;
    DisplayItemMessageOnField(taskId, gStringVar4, task08_080A1C44);
}

bool8 sub_80FE314(void)
{
    if (gMapHeader.flags & 2)
        return TRUE;
    else
        return FALSE;
}

void ItemUseOutOfBattle_EscapeRope(u8 taskId)
{
    if (sub_80FE314() == TRUE)
    {
        gUnknown_0203A0F4 = re_escape_rope;
        SetUpItemUseOnFieldCallback(taskId);
    }
    else
    {
        DisplayDadsAdviceCannotUseItemMessage(taskId, gTasks[taskId].data[3]);
    }
}

void ItemUseOutOfBattle_EvolutionStone(u8 taskId)
{
    gUnknown_03006328 = sub_81B7C74;
    SetUpItemUseCallback(taskId);
}

void ItemUseInBattle_PokeBall(u8 taskId)
{
    if (IsPlayerPartyAndPokemonStorageFull() == FALSE) // have room for mon?
    {
        RemoveBagItem(gSpecialVar_ItemId, 1);
        if (!InBattlePyramid())
            unknown_ItemMenu_Confirm(taskId);
        else
            sub_81C5B14(taskId);
    }
    else if (!InBattlePyramid())
    {
        DisplayItemMessage(taskId, 1, gText_BoxFull, bag_menu_inits_lists_menu);
    }
    else
        DisplayItemMessageInBattlePyramid(taskId, gText_BoxFull, sub_81C6714);
}

void sub_80FE408(u8 taskId)
{
    if (gMain.newKeys & (A_BUTTON | B_BUTTON))
    {
        if (!InBattlePyramid())
            unknown_ItemMenu_Confirm(taskId);
        else
            sub_81C5B14(taskId);
    }
}

void sub_80FE440(u8 taskId)
{
    if(++gTasks[taskId].data[8] > 7)
    {
        PlaySE(SE_KAIFUKU);
        RemoveBagItem(gSpecialVar_ItemId, 1);
        if (!InBattlePyramid())
            DisplayItemMessage(taskId, 1, sub_806CF78(gSpecialVar_ItemId), sub_80FE408);
        else
            DisplayItemMessageInBattlePyramid(taskId, sub_806CF78(gSpecialVar_ItemId), sub_80FE408);
    }
}

void ItemUseInBattle_StatIncrease(u8 taskId)
{
    u16 partyId = gBattlePartyID[gBankInMenu];

    if (ExecuteTableBasedItemEffect_(&gPlayerParty[partyId], gSpecialVar_ItemId, partyId, 0) != FALSE)
    {
        if (!InBattlePyramid())
            DisplayItemMessage(taskId, 1, gText_WontHaveEffect, bag_menu_inits_lists_menu);
        else
            DisplayItemMessageInBattlePyramid(taskId, gText_WontHaveEffect, sub_81C6714);
    }
    else
    {
        gTasks[taskId].func = sub_80FE440;
        gTasks[taskId].data[8] = 0;
    }
}

void sub_80FE54C(u8 taskId)
{
    if (!InBattlePyramid())
    {
        *gUnknown_0203CE54 = sub_81B89F0;
        unknown_ItemMenu_Confirm(taskId);
    }
    else
    {
        *gUnknown_0203CF2C = sub_81B89F0;
        sub_81C5B14(taskId);
    }
}

void ItemUseInBattle_Medicine(u8 taskId)
{
    gUnknown_03006328 = ItemUseCB_Medicine;
    sub_80FE54C(taskId);
}

void sub_80FE5AC(u8 taskId)
{
    gUnknown_03006328 = sub_81B79E8;
    sub_80FE54C(taskId);
}

void ItemUseInBattle_PPRecovery(u8 taskId)
{
    gUnknown_03006328 = dp05_ether;
    sub_80FE54C(taskId);
}

void ItemUseInBattle_Escape(u8 taskId)
{

    if((gBattleTypeFlags & BATTLE_TYPE_TRAINER) == FALSE)
    {
        sub_80FE058();
        if (!InBattlePyramid())
            DisplayItemMessage(taskId, 1, gStringVar4, unknown_ItemMenu_Confirm);
        else
            DisplayItemMessageInBattlePyramid(taskId, gStringVar4, sub_81C5B14);
    }
    else
    {
        DisplayDadsAdviceCannotUseItemMessage(taskId, gTasks[taskId].data[3]);
    }
}

void ItemUseOutOfBattle_EnigmaBerry(u8 taskId)
{
    switch (GetItemEffectType(gSpecialVar_ItemId) - 1)
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
        gTasks[taskId].data[4] = 1;
        ItemUseOutOfBattle_Medicine(taskId);
        break;
    case 9:
        gTasks[taskId].data[4] = 1;
        ItemUseOutOfBattle_SacredAsh(taskId);
        break;
    case 0:
        gTasks[taskId].data[4] = 1;
        ItemUseOutOfBattle_RareCandy(taskId);
        break;
    case 18:
    case 19:
        gTasks[taskId].data[4] = 1;
        ItemUseOutOfBattle_PPUp(taskId);
        break;
    case 20:
        gTasks[taskId].data[4] = 1;
        ItemUseOutOfBattle_PPRecovery(taskId);
        break;
    default:
        gTasks[taskId].data[4] = 4;
        ItemUseOutOfBattle_CannotUse(taskId);
    }
}

void ItemUseInBattle_EnigmaBerry(u8 taskId)
{
    switch (GetItemEffectType(gSpecialVar_ItemId))
    {
    case 0:
        ItemUseInBattle_StatIncrease(taskId);
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 11:
        ItemUseInBattle_Medicine(taskId);
        break;
    case 21:
        ItemUseInBattle_PPRecovery(taskId);
        break;
    default:
        ItemUseOutOfBattle_CannotUse(taskId);
    }
}

void ItemUseOutOfBattle_CannotUse(u8 taskId)
{
    DisplayDadsAdviceCannotUseItemMessage(taskId, gTasks[taskId].data[3]);
}
