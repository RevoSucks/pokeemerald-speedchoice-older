#include "global.h"
#include "start_menu.h"
#include "menu.h"
#include "safari_zone.h"
#include "event_data.h"
#include "window.h"
#include "string_util.h"
#include "text.h"
#include "strings.h"
#include "bg.h"
#include "task.h"
#include "speedchoice.h"
#include "overworld.h"
#include "new_menu_helpers.h"

extern struct MapObjectTimerBackup gMapObjectTimerBackup[MAX_SPRITES];
extern u8 gSpeedchoiceEscapeText[];

extern u8 GetStartMenuWindowId(void);
extern void ItemUseOutOfBattle_EscapeRope(u8 taskId);

// Menu actions
enum
{
    MENU_ACTION_POKEDEX,
    MENU_ACTION_POKEMON,
    MENU_ACTION_BAG,
    MENU_ACTION_POKENAV,
    MENU_ACTION_PLAYER,
    MENU_ACTION_SAVE,
    MENU_ACTION_OPTION,
    MENU_ACTION_EXIT,
    MENU_ACTION_RETIRE_SAFARI,
    MENU_ACTION_PLAYER_LINK,
    MENU_ACTION_REST_FRONTIER,
    MENU_ACTION_RETIRE_FRONTIER,
    MENU_ACTION_PYRAMID_BAG,
	MENU_ACTION_ESCAPE,
};

extern bool32 is_c1_link_related_active(void);
extern bool32 InUnionRoom(void);
extern bool8 InBattlePike(void);
extern bool8 InBattlePyramid(void);
extern bool8 InMultiBattleRoom(void);
extern void sub_81973FC(u8 windowId, u8 a1);
extern void sub_8198070(u8 windowId, u8 a1);

// this file's functions
static void BuildStartMenuActions_LinkMode(void);
static void BuildStartMenuActions_UnionRoom(void);
static void BuildStartMenuActions_SafariZone(void);
static void BuildStartMenuActions_BattlePike(void);
static void BuildStartMenuActions_BattlePyramid(void);
static void BuildStartMenuActions_MultiBattleRoom(void);
static void BuildStartMenuActions_Normal(void);
bool8 StartMenu_Pokedex(void);
bool8 StartMenu_Pokemon(void);
bool8 StartMenu_Bag(void);
bool8 StartMenu_PokeNav(void);
bool8 StartMenu_PlayerName(void);
bool8 StartMenu_Save(void);
bool8 StartMenu_Option(void);
bool8 StartMenu_Exit(void);
bool8 StartMenu_SafariZoneRetire(void);
bool8 StartMenu_LinkModePlayerName(void);
bool8 StartMenu_BattlePyramidRetire(void);
bool8 StartMenu_BattlePyramidBag(void);
bool8 StartMenu_EscapeCallback(void);

// EWRAM vars
EWRAM_DATA u8 sSafariBallsWindowId = 0;
EWRAM_DATA u8 sBattlePyramidFloorWindowId = 0;
EWRAM_DATA u8 sStartMenuCursorPos = 0;
EWRAM_DATA u8 sNumStartMenuActions = 0;
EWRAM_DATA u8 sCurrentStartMenuActions[9] = {0};
EWRAM_DATA bool8 sUsedEscapeOption = FALSE;

// const rom data
static const struct WindowTemplate gSafariBallsWindowTemplate = {0, 1, 1, 9, 4, 0xF, 8};

static const u8* const sPyramindFloorNames[] =
{
    gText_Floor1,
    gText_Floor2,
    gText_Floor3,
    gText_Floor4,
    gText_Floor5,
    gText_Floor6,
    gText_Floor7,
    gText_Peak
};

static const struct WindowTemplate gPyramidFloorWindowTemplate_2 = {0, 1, 1, 0xA, 4, 0xF, 8};
static const struct WindowTemplate gPyramidFloorWindowTemplate_1 = {0, 1, 1, 0xC, 4, 0xF, 8};

const struct MenuAction sStartMenuItems[] =
{
    {gText_MenuPokedex, {.u8_void = StartMenu_Pokedex}},
    {gText_MenuPokemon, {.u8_void = StartMenu_Pokemon}},
    {gText_MenuBag, {.u8_void = StartMenu_Bag}},
    {gText_MenuPokenav, {.u8_void = StartMenu_PokeNav}},
    {gText_MenuPlayer, {.u8_void = StartMenu_PlayerName}},
    {gText_MenuSave, {.u8_void = StartMenu_Save}},
    {gText_MenuOption, {.u8_void = StartMenu_Option}},
    {gText_MenuExit, {.u8_void = StartMenu_Exit}},
    {gText_MenuRetire, {.u8_void = StartMenu_SafariZoneRetire}},
    {gText_MenuPlayer, {.u8_void = StartMenu_LinkModePlayerName}},
    {gText_MenuRest, {.u8_void = StartMenu_Save}},
    {gText_MenuRetire, {.u8_void = StartMenu_BattlePyramidRetire}},
    {gText_MenuBag, {.u8_void = StartMenu_BattlePyramidBag}},
	{gSpeedchoiceEscapeText, {.u8_void = StartMenu_EscapeCallback}},
};

const struct BgTemplate gUnknown_085105A8[] =
{
    {
        .bg = 0,
        .charBaseIndex = 2,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    }
};

const struct WindowTemplate gUnknown_085105AC[] =
{
    {0, 2, 0xF, 0x1A, 4, 0xF, 0x194},
    DUMMY_WIN_TEMPLATE
};

const struct WindowTemplate gUnknown_085105BC = {0, 1, 1, 0xE, 0xA, 0xF, 8};

void DoMapObjectTimerBackup(void)
{
    u8 i;

    for(i = 0; i < MAX_SPRITES; i++)
    {
        gMapObjectTimerBackup[i].backedUp = TRUE;
        gMapObjectTimerBackup[i].timer = gSprites[i].data[3];
    }
}

bool8 CanUseFly(void)
{
    if(Overworld_MapTypeAllowsTeleportAndFly(gMapHeader.mapType) == TRUE)
        return TRUE;
    else
        return FALSE;
}

bool8 IsMapEscapeOption(void)
{
    u8 i;

    for(i = 0; i < 16; i++)
        if((gMapObjects[i].trainerType == 1 || gMapObjects[i].trainerType == 3) && CanUseFly() == FALSE)
            return TRUE;

    return FALSE;
}

// code
void BuildStartMenuActions(void)
{
    sNumStartMenuActions = 0;
    if (is_c1_link_related_active() == TRUE)
        BuildStartMenuActions_LinkMode();
    else if (InUnionRoom() == TRUE)
        BuildStartMenuActions_UnionRoom();
    else if (GetSafariZoneFlag() == TRUE)
        BuildStartMenuActions_SafariZone();
    else if (InBattlePike())
        BuildStartMenuActions_BattlePike();
    else if (InBattlePyramid())
        BuildStartMenuActions_BattlePyramid();
    else if (InMultiBattleRoom())
        BuildStartMenuActions_MultiBattleRoom();
    else
        BuildStartMenuActions_Normal();
}

void AddStartMenuAction(u8 action)
{
    AppendToList(sCurrentStartMenuActions, &sNumStartMenuActions, action);
}

static void BuildStartMenuActions_Normal(void)
{
    if (FlagGet(FLAG_SYS_POKEDEX_GET) == TRUE)
        AddStartMenuAction(MENU_ACTION_POKEDEX);
    if (FlagGet(FLAG_SYS_POKEMON_GET) == TRUE)
        AddStartMenuAction(MENU_ACTION_POKEMON);
    AddStartMenuAction(MENU_ACTION_BAG);
    if (FlagGet(FLAG_SYS_POKENAV_GET) == TRUE)
        AddStartMenuAction(MENU_ACTION_POKENAV);
    AddStartMenuAction(MENU_ACTION_PLAYER);
    AddStartMenuAction(MENU_ACTION_SAVE);
    AddStartMenuAction(MENU_ACTION_OPTION);
    if(IsMapEscapeOption() == TRUE)
        AddStartMenuAction(MENU_ACTION_ESCAPE);
    else
        AddStartMenuAction(MENU_ACTION_EXIT);
}

static void BuildStartMenuActions_SafariZone(void)
{
    AddStartMenuAction(MENU_ACTION_RETIRE_SAFARI);
    AddStartMenuAction(MENU_ACTION_POKEDEX);
    AddStartMenuAction(MENU_ACTION_POKEMON);
    AddStartMenuAction(MENU_ACTION_BAG);
    AddStartMenuAction(MENU_ACTION_PLAYER);
    AddStartMenuAction(MENU_ACTION_OPTION);
    AddStartMenuAction(MENU_ACTION_EXIT);
}

static void BuildStartMenuActions_LinkMode(void)
{
    AddStartMenuAction(MENU_ACTION_POKEMON);
    AddStartMenuAction(MENU_ACTION_BAG);
    if (FlagGet(FLAG_SYS_POKENAV_GET) == TRUE)
        AddStartMenuAction(MENU_ACTION_POKENAV);
    AddStartMenuAction(MENU_ACTION_PLAYER_LINK);
    AddStartMenuAction(MENU_ACTION_OPTION);
    AddStartMenuAction(MENU_ACTION_EXIT);
}

static void BuildStartMenuActions_UnionRoom(void)
{
    AddStartMenuAction(MENU_ACTION_POKEMON);
    AddStartMenuAction(MENU_ACTION_BAG);
    if (FlagGet(FLAG_SYS_POKENAV_GET) == TRUE)
        AddStartMenuAction(MENU_ACTION_POKENAV);
    AddStartMenuAction(MENU_ACTION_PLAYER);
    AddStartMenuAction(MENU_ACTION_OPTION);
    AddStartMenuAction(MENU_ACTION_EXIT);
}

static void BuildStartMenuActions_BattlePike(void)
{
    AddStartMenuAction(MENU_ACTION_POKEDEX);
    AddStartMenuAction(MENU_ACTION_POKEMON);
    AddStartMenuAction(MENU_ACTION_PLAYER);
    AddStartMenuAction(MENU_ACTION_OPTION);
    AddStartMenuAction(MENU_ACTION_EXIT);
}

static void BuildStartMenuActions_BattlePyramid(void)
{
    AddStartMenuAction(MENU_ACTION_POKEMON);
    AddStartMenuAction(MENU_ACTION_PYRAMID_BAG);
    AddStartMenuAction(MENU_ACTION_PLAYER);
    AddStartMenuAction(MENU_ACTION_REST_FRONTIER);
    AddStartMenuAction(MENU_ACTION_RETIRE_FRONTIER);
    AddStartMenuAction(MENU_ACTION_OPTION);
    AddStartMenuAction(MENU_ACTION_EXIT);
}

static void BuildStartMenuActions_MultiBattleRoom(void)
{
    AddStartMenuAction(MENU_ACTION_POKEMON);
    AddStartMenuAction(MENU_ACTION_PLAYER);
    AddStartMenuAction(MENU_ACTION_OPTION);
    AddStartMenuAction(MENU_ACTION_EXIT);
}

void DisplaySafariBallsWindow(void)
{
    sSafariBallsWindowId = AddWindow(&gSafariBallsWindowTemplate);
    PutWindowTilemap(sSafariBallsWindowId);
    sub_81973FC(sSafariBallsWindowId, 0);
    ConvertIntToDecimalStringN(gStringVar1, gNumSafariBalls, STR_CONV_MODE_RIGHT_ALIGN, 2);
    StringExpandPlaceholders(gStringVar4, gText_SafariBallStock);
    PrintTextOnWindow(sSafariBallsWindowId, 1, gStringVar4, 0, 1, 0xFF, NULL);
    CopyWindowToVram(sSafariBallsWindowId, 2);
}

void DisplayPyramidFloorWindow(void)
{
    // TODO: fix location
    if (gSaveBlock2Ptr->field_CAA[4] == 7)
        sBattlePyramidFloorWindowId = AddWindow(&gPyramidFloorWindowTemplate_1);
    else
        sBattlePyramidFloorWindowId = AddWindow(&gPyramidFloorWindowTemplate_2);
    PutWindowTilemap(sBattlePyramidFloorWindowId);
    sub_81973FC(sBattlePyramidFloorWindowId, 0);
    StringCopy(gStringVar1, sPyramindFloorNames[gSaveBlock2Ptr->field_CAA[4]]);
    StringExpandPlaceholders(gStringVar4, gText_BattlePyramidFloor);
    PrintTextOnWindow(sBattlePyramidFloorWindowId, 1, gStringVar4, 0, 1, 0xFF, NULL);
    CopyWindowToVram(sBattlePyramidFloorWindowId, 2);
}

void RemoveExtraStartMenuWindows(void)
{
    if (GetSafariZoneFlag())
    {
        sub_8198070(sSafariBallsWindowId, 0);
        CopyWindowToVram(sSafariBallsWindowId, 2);
        RemoveWindow(sSafariBallsWindowId);
    }
    if (InBattlePyramid())
    {
        sub_8198070(sBattlePyramidFloorWindowId, 0);
        RemoveWindow(sBattlePyramidFloorWindowId);
    }
}

/*
	thumb_func_start sub_80A0914
sub_80A0914: @ 80A0914
	push {lr}
	bl GetStartMenuWindowId
	lsls r0, 24
	lsrs r0, 24
	movs r1, 0x1
	bl sub_819746C
	bl remove_start_menu_window_maybe
	bl sub_80984F4
	bl ScriptContext2_Disable
	pop {r0}
	bx r0
	thumb_func_end sub_80A0914
*/

extern void remove_start_menu_window_maybe(void);
extern void sub_80984F4(void);
extern void re_escape_rope(u8 taskId);

extern void(*gUnknown_0203A0F4)(u8 taskId);

void CloseMenuWithoutScriptContext(void)
{
	sub_819746C(GetStartMenuWindowId(), 1);
	remove_start_menu_window_maybe();
	sub_80984F4();
}

static void ItemUseInEscape_EscapeRope(u8 taskId)
{
    sUsedEscapeOption = TRUE;
    gUnknown_0203A0F4 = re_escape_rope; // do escape rope attempt.
    gTasks[taskId].data[3] = 1; // dont fade to black! Not in a submenu.
    SetUpItemUseOnFieldCallback(taskId);
}

bool8 StartMenu_EscapeCallback(void)
{
	CloseMenuWithoutScriptContext();
    CreateTask(ItemUseInEscape_EscapeRope, 0xFF);
    return TRUE;
}

__attribute__((naked))
bool32 PrintStartMenuActions(s16 *index, u32 n)
{
	asm(".syntax unified\n\
	push {r4-r7,lr}\n\
	mov r7, r10\n\
	mov r6, r9\n\
	mov r5, r8\n\
	push {r5-r7}\n\
	sub sp, 0xC\n\
	mov r8, r0\n\
	adds r6, r1, 0\n\
	ldrb r2, [r0]\n\
	ldr r0, =sStartMenuItems\n\
	mov r9, r0\n\
	ldr r1, =gStringVar4\n\
	mov r10, r1\n\
_0809F7DA:\n\
	ldr r0, =sCurrentStartMenuActions\n\
	lsls r2, 24\n\
	asrs r4, r2, 24\n\
	adds r5, r4, r0\n\
	ldrb r0, [r5]\n\
	lsls r3, r0, 3\n\
	mov r0, r9\n\
	adds r0, 0x4\n\
	adds r0, r3, r0\n\
	ldr r1, [r0]\n\
	ldr r0, =StartMenu_PlayerName\n\
	adds r7, r2, 0\n\
	cmp r1, r0\n\
	bne _0809F828\n\
	bl GetStartMenuWindowId\n\
	lsls r0, 24\n\
	lsrs r0, 24\n\
	ldrb r1, [r5]\n\
	lsls r1, 3\n\
	add r1, r9\n\
	ldr r1, [r1]\n\
	lsls r3, r4, 4\n\
	adds r3, 0x9\n\
	lsls r3, 16\n\
	lsrs r3, 16\n\
	movs r2, 0x8\n\
	bl sub_819A024\n\
	b _0809F858\n\
	.pool\n\
_0809F828:\n\
	mov r1, r9\n\
	adds r0, r3, r1\n\
	ldr r1, [r0]\n\
	mov r0, r10\n\
	bl StringExpandPlaceholders\n\
	bl GetStartMenuWindowId\n\
	lsls r0, 24\n\
	lsrs r0, 24\n\
	lsls r1, r4, 4\n\
	adds r1, 0x9\n\
	lsls r1, 24\n\
	lsrs r1, 24\n\
	str r1, [sp]\n\
	movs r1, 0xFF\n\
	str r1, [sp, 0x4]\n\
	movs r1, 0\n\
	str r1, [sp, 0x8]\n\
	movs r1, 0x1\n\
	mov r2, r10\n\
	movs r3, 0x8\n\
	bl PrintTextOnWindow\n\
_0809F858:\n\
	movs r0, 0x80\n\
	lsls r0, 17\n\
	adds r1, r7, r0\n\
	lsrs r2, r1, 24\n\
	asrs r1, 24\n\
	ldr r0, =sNumStartMenuActions\n\
	ldrb r0, [r0]\n\
	cmp r1, r0\n\
	bge _0809F87C\n\
	subs r6, 0x1\n\
	cmp r6, 0\n\
	bne _0809F7DA\n\
	mov r1, r8\n\
	strb r2, [r1]\n\
	movs r0, 0\n\
	b _0809F882\n\
	.pool\n\
_0809F87C:\n\
	mov r0, r8\n\
	strb r2, [r0]\n\
	movs r0, 0x1\n\
_0809F882:\n\
	add sp, 0xC\n\
	pop {r3-r5}\n\
	mov r8, r3\n\
	mov r9, r4\n\
	mov r10, r5\n\
	pop {r4-r7}\n\
	pop {r1}\n\
	bx r1\n\
	.syntax divided");
}

__attribute__((naked))
bool32 sub_809F894(void)
{
	asm(".syntax unified\n\
	push {r4,lr}\n\
	sub sp, 0xC\n\
	ldr r0, =gUnknown_02037619\n\
	movs r1, 0\n\
	ldrsb r1, [r0, r1]\n\
	adds r2, r0, 0\n\
	cmp r1, 0x5\n\
	bhi _0809F98C\n\
	lsls r0, r1, 2\n\
	ldr r1, =_0809F8B8\n\
	adds r0, r1\n\
	ldr r0, [r0]\n\
	mov pc, r0\n\
	.pool\n\
	.align 2, 0\n\
_0809F8B8:\n\
	.4byte _0809F8D0\n\
	.4byte _0809F8D8\n\
	.4byte _0809F8E4\n\
	.4byte _0809F90C\n\
	.4byte _0809F930\n\
	.4byte _0809F94C\n\
_0809F8D0:\n\
	ldrb r0, [r2]\n\
	adds r0, 0x1\n\
	strb r0, [r2]\n\
	b _0809F98C\n\
_0809F8D8:\n\
	bl BuildStartMenuActions\n\
	ldr r1, =gUnknown_02037619\n\
	b _0809F940\n\
	.pool\n\
_0809F8E4:\n\
	bl sub_81973A4\n\
	ldr r0, =sNumStartMenuActions\n\
	ldrb r0, [r0]\n\
	bl sub_81979C4\n\
	lsls r0, 24\n\
	lsrs r0, 24\n\
	movs r1, 0\n\
	bl sub_81973FC\n\
	ldr r1, =gUnknown_02037619\n\
	movs r0, 0\n\
	strb r0, [r1, 0x1]\n\
	b _0809F940\n\
	.pool\n\
_0809F90C:\n\
	bl GetSafariZoneFlag\n\
	cmp r0, 0\n\
	beq _0809F918\n\
	bl DisplaySafariBallsWindow\n\
_0809F918:\n\
	bl InBattlePyramid\n\
	lsls r0, 24\n\
	cmp r0, 0\n\
	beq _0809F926\n\
	bl DisplayPyramidFloorWindow\n\
_0809F926:\n\
	ldr r1, =gUnknown_02037619\n\
	b _0809F940\n\
	.pool\n\
_0809F930:\n\
	ldr r4, =gUnknown_0203761A\n\
	adds r0, r4, 0\n\
	movs r1, 0x2\n\
	bl PrintStartMenuActions\n\
	cmp r0, 0\n\
	beq _0809F98C\n\
	subs r1, r4, 0x1\n\
_0809F940:\n\
	ldrb r0, [r1]\n\
	adds r0, 0x1\n\
	strb r0, [r1]\n\
	b _0809F98C\n\
	.pool\n\
_0809F94C:\n\
	bl GetStartMenuWindowId\n\
	lsls r0, 24\n\
	lsrs r0, 24\n\
	movs r1, 0x10\n\
	str r1, [sp]\n\
	ldr r1, =sNumStartMenuActions\n\
	ldrb r1, [r1]\n\
	str r1, [sp, 0x4]\n\
	ldr r4, =sStartMenuCursorPos\n\
	ldrb r1, [r4]\n\
	str r1, [sp, 0x8]\n\
	movs r1, 0x1\n\
	movs r2, 0\n\
	movs r3, 0x9\n\
	bl sub_81983AC\n\
	strb r0, [r4]\n\
	bl GetStartMenuWindowId\n\
	lsls r0, 24\n\
	lsrs r0, 24\n\
	movs r1, 0x1\n\
	bl CopyWindowToVram\n\
	movs r0, 0x1\n\
	b _0809F98E\n\
	.pool\n\
_0809F98C:\n\
	movs r0, 0\n\
_0809F98E:\n\
	add sp, 0xC\n\
	pop {r4}\n\
	pop {r1}\n\
	bx r1\n\
	.syntax divided");
}

extern u8 gUnknown_02037619[];

void sub_809F998(void)
{
	gUnknown_02037619[0] = 0;
	gUnknown_02037619[1] = 0;

	while(!sub_809F894())
		;
}

void task50_startmenu(u8 taskId)
{
	if(sub_809F894() == TRUE)
		SwitchTaskToFollowupFunc(taskId);
}

// InitStartMenu
void sub_809F9D0(TaskFunc func)
{
	u8 taskId;

	gUnknown_02037619[0] = 0;
	gUnknown_02037619[1] = 0;

	taskId = CreateTask(task50_startmenu, 0x50);
	SetTaskFuncWithFollowupFunc(taskId, task50_startmenu, func);
}
