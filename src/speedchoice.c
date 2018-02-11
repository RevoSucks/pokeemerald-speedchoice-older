#include "global.h"
#include "main.h"
#include "menu.h"
#include "palette.h"
#include "sprite.h"
#include "task.h"
#include "sound.h"
#include "constants/songs.h"
#include "string_util.h"
#include "text.h"
#include "speedchoice.h"
#include "gpu_regs.h"
#include "bg.h"
#include "scanline_effect.h"
#include "text_window.h"
#include "field_message_box.h"
#include "text_window.h"
#include "new_menu_helpers.h"

extern u16 sUnknown_0855C604[16];
extern u16 sUnknown_0855C6A0[1];
extern u16 gMainMenuTextPal[16];

// Window Ids
enum
{
    SPD_WIN_TEXT_OPTION,
    SPD_WIN_OPTIONS,
    SPD_WIN_TOOLTIP,
    SPD_WIN_YESNO,
};

const struct BgTemplate sSpeedchoiceMenuBgTemplates[] =
{
   {
       .bg = 1,
       .charBaseIndex = 1,
       .mapBaseIndex = 30,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 1,
       .baseTile = 0
   },
   {
       .bg = 0,
       .charBaseIndex = 1,
       .mapBaseIndex = 31,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 2,
       .baseTile = 0
   },
   // 0x000001ec
   {
       .bg = 2,
       .charBaseIndex = 1,
       .mapBaseIndex = 29,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 0,
       .baseTile = 0
   }
};

const struct WindowTemplate sSpeedchoiceMenuWinTemplates[] =
{
    {1, 2, 1, 0x1A, 2, 1, 2},
    {0, 2, 5, 0x1A, 14, 1, 0x36},
    {2, 2, 15, 0x1A, 4, 15, 427},
    {2, 23, 9, 4, 4, 15, 531}, // YES/NO
    DUMMY_WIN_TEMPLATE
};

// Window Ids
enum
{
    WIN_TEXT_OPTION,
    WIN_OPTIONS
};

const u8 gSystemText_TerminatorS[] = _("{COLOR RED}$");

// HEADER
const u8 gSpeedchoiceTextHeader[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}SPEEDCHOICE MENU");
const u8 gSpeedchoiceCurrentVersion[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}v1.04");

// OPTION CHOICES
const u8 gSpeedchoiceTextYes[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}YES");
const u8 gSpeedchoiceTextNo[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}NO");
const u8 gSpeedchoiceTextOn[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}ON");
const u8 gSpeedchoiceTextOff[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}OFF");
const u8 gSpeedchoiceTextNerf[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}PURGE");
const u8 gSpeedchoiceTextKeep[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}KEEP");
const u8 gSpeedchoiceTextHell[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}HELL");
const u8 gSpeedchoiceTextSemi[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}SEMI");
const u8 gSpeedchoiceTextFull[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}FULL");
const u8 gSpeedchoiceTextStatic[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}SAME");
const u8 gSpeedchoiceTextRand[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}RAND");
const u8 gSpeedchoiceTextSane[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}SANE");

// PAGE 1
const u8 gSpeedchoiceOptionBWExp[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}B/W EXP");
const u8 gSpeedchoiceOptionPlotless[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}PLOTLESS");
const u8 gSpeedchoiceOptionInstantText[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}INSTANT TEXT");
const u8 gSpeedchoiceOptionSpinners[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}SPINNERS");
const u8 gSpeedchoiceOptionMaxVision[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}MAX VISION");

// PAGE 2
const u8 gSpeedchoiceOptionNerfRoxanne[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}NERF ROXANNE");
const u8 gSpeedchoiceOptionSuperBike[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}SUPER BIKE");
const u8 gSpeedchoiceOptionNewWildEnc[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}NEW WILD ENC.");
const u8 gSpeedchoiceOptionEarlyFly[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}EARLY FLY");
const u8 gSpeedchoiceOptionRunEverywhere[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}RUN EVERYWHERE");

// PAGE 3
const u8 gSpeedchoiceOptionMemeIsland[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}MEME ISLAND");
const u8 gSpeedchoiceOptionBetterMarts[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}BETTER MARTS");
const u8 gSpeedchoiceOptionGoodEarlyWilds[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}GOOD EARLY WILDS");
const u8 gSpeedchoiceOptionEarlySurf[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}EARLY SURF");

// CONSTANT OPTIONS
const u8 gSpeedchoiceOptionPage[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}PAGE");
const u8 gSpeedchoiceOptionStartGame[] = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}START GAME");

// ARROWS
const u8 gSpeedchoiceOptionLeftArrow[] = _("{COLOR RED}{SHADOW LIGHT_RED}{LEFT_ARROW}");
const u8 gSpeedchoiceOptionRightArrow[] = _("{COLOR RED}{SHADOW LIGHT_RED}{RIGHT_ARROW}");

// INTRODUCTION
const u8 gSpeedchoiceTooltipExplanation[] = _("This is the Speedchoice menu where\nvarious options can be selected.\pTo get an explanation of each option,\npress SELECT when over the option.");

// TOOLTIPS
const u8 gSpeedchoiceTooltipBWEXP[] = _("Replaces the current experience\nsystem in favor of\pBlack/White’s implementation.");
const u8 gSpeedchoiceTooltipPlotless[] = _("SEMI: Stops villain team events\nafter Mt. Chimney.\pFULL: Skips all the villain team\nevents. Also allows Dive to be used\pwithout Gym 7’s badge.");
const u8 gSpeedchoiceTooltipInstantText[] = _("Self-explanatory.\nHold A or B to mash.");
const u8 gSpeedchoiceTooltipSpinners[] = _("PURGE: Makes spinners on a static\nspinning pattern at a fixed rate.\pHELL: Rapidly spins\nevery spinner every frame.\pAlso fixes bag manip.");
const u8 gSpeedchoiceTooltipMaxVision[] = _("SANE: Will extend trainer vision\nto 8, but prevent trainers from\pwalking through walls or solid\nobjects.\pHELL: No collision or\nelevation detection.");
const u8 gSpeedchoiceTooltipNerfRoxanne[] = _("Nerfs Gym Leader Roxanne.\nRemoves both of her Potions.");
const u8 gSpeedchoiceTooltipSuperBike[] = _("While riding the bicycle, you\ncan switch between bikes with\pthe R button while you are\nstanding still.");
const u8 gSpeedchoiceTooltipNewWildEnc[] = _("Intended to be used with\nthe randomizer.\pTreats grass and fishing slots\nas 6 and 2 slots respectively.");
const u8 gSpeedchoiceTooltipEarlyFly[] = _("Recieve HM02 instead of\nItemfinder at Rival 2.\pAllows use of Fly without use of\nGym 6’s badge.");
const u8 gSpeedchoiceTooltipRunEverywhere[] = _("Allows the Running Shoes to\nbe used anywhere, including\pinside of houses.\pAlso allows bike in most places.");
const u8 gSpeedchoiceTooltipMemeIsland[] = _("Mirage Island always appears.");
const u8 gSpeedchoiceTooltipGlitchRod[] = _("Restores the old behavior\nof fishing from BETA 7 where\plevel is not accounted for\nby the rod type.");
const u8 gSpeedchoiceTooltipBetterMarts[] = _("Improves the item selections\nof many Pokemon marts.\pAdds repels to Oldale Mart.\pAdds repels and super repels to\nMauville Mart.\pAdds X Specials to Rustboro\nMart.");
const u8 gSpeedchoiceTooltipGoodEarlyWilds[] = _("SAME: Depending on the\nrandomizer check value, wild\pencounters in the grass for\npokemon below lv 10 will have\ptheir final evolution.\pRAND: If they have a branching\nevolution, it will be randomly\pgenerated instead of being static.");
const u8 gSpeedchoiceTooltipEarlySurf[] = _("Switches the locations of\nHM04 and HM03.\pUse of Surf requirement only needs\nWattson’s Gym Badge.\pIn addition, Steven post-Fortree\nwill not spawn until after GYM 5.");

// START GAME
const u8 gSpeedchoiceStartGameText[] = _("CV: {STR_VAR_1}\nStart the game?");

// MISC STRINGS
const u8 gSpeedchoiceEscapeText[] = _("ESCAPE");

const struct OptionChoiceConfig OptionChoiceConfigYesNo[MAX_CHOICES] = 
{
    { 120, (u8 *)&gSpeedchoiceTextYes },
    { 150, (u8 *)&gSpeedchoiceTextNo },
    { -1, NULL },
    { -1, NULL },
    { -1, NULL },
    { -1, NULL }
};

const struct OptionChoiceConfig OptionChoiceConfigOnOff[MAX_CHOICES] = 
{
    { 120, (u8 *)&gSpeedchoiceTextOn },
    { 150, (u8 *)&gSpeedchoiceTextOff },
    { -1, NULL },
    { -1, NULL },
    { -1, NULL },
    { -1, NULL }
};

const struct OptionChoiceConfig OptionChoiceConfigNerfKeep[MAX_CHOICES] = 
{
    { 120, (u8 *)&gSpeedchoiceTextNerf },
    { 150, (u8 *)&gSpeedchoiceTextKeep },
    { 180, (u8 *)&gSpeedchoiceTextHell },
    { -1, NULL },
    { -1, NULL },
    { -1, NULL }
};

const struct OptionChoiceConfig OptionChoiceConfigSemiFull[MAX_CHOICES] = 
{
    { 120, (u8 *)&gSpeedchoiceTextSemi },
    { 150, (u8 *)&gSpeedchoiceTextKeep },
    { 180, (u8 *)&gSpeedchoiceTextFull },
    { -1, NULL },
    { -1, NULL },
    { -1, NULL }
};

const struct OptionChoiceConfig OptionChoiceConfigOffRand[MAX_CHOICES] = 
{
    { 120, (u8 *)&gSpeedchoiceTextOff },
    { 150, (u8 *)&gSpeedchoiceTextStatic },
    { 180, (u8 *)&gSpeedchoiceTextRand },
    { -1, NULL },
    { -1, NULL },
    { -1, NULL }
};

const struct OptionChoiceConfig OptionChoiceConfigSaneHell[MAX_CHOICES] = 
{
    { 120, (u8 *)&gSpeedchoiceTextOff },
    { 150, (u8 *)&gSpeedchoiceTextSane },
    { 180, (u8 *)&gSpeedchoiceTextHell },
    { -1, NULL },
    { -1, NULL },
    { -1, NULL }
};

// this is totally weird, but in order to use ProcessGeneralInput, a struct is needed for page, so, I opt to have a dummy struct which only has the number of choices relevent to the calculation of the selection.
const struct OptionChoiceConfig OptionChoiceConfigPage[MAX_CHOICES] = 
{
    { -1, NULL },
    { -1, NULL },
    { -1, NULL },
    { -1, NULL },
    { -1, NULL },
    { -1, NULL }
};

// not a normal config struct, but used for the arrows for multi choice.
const struct OptionChoiceConfig Arrows[MAX_CHOICES] = 
{
    { 120, (u8 *)&gSpeedchoiceOptionLeftArrow },
    { 150, (u8 *)&gSpeedchoiceOptionRightArrow },
    { -1, NULL },
    { -1, NULL },
    { -1, NULL },
    { -1, NULL }
};

const struct SpeedchoiceOption SpeedchoiceOptions[CURRENT_OPTIONS_NUM + 1] = // plus one for page.
{
    { 2,         NORMAL, (u8 *)&gSpeedchoiceOptionBWExp, (struct OptionChoiceConfig *)OptionChoiceConfigOnOff, (u8 *)&gSpeedchoiceTooltipBWEXP, OFF, TRUE },
    { 3,         NORMAL, (u8 *)&gSpeedchoiceOptionPlotless, (struct OptionChoiceConfig *)OptionChoiceConfigSemiFull, (u8 *)&gSpeedchoiceTooltipPlotless, KEEP, TRUE },
    { 2,         NORMAL, (u8 *)&gSpeedchoiceOptionInstantText, (struct OptionChoiceConfig *)OptionChoiceConfigOnOff, (u8 *)&gSpeedchoiceTooltipInstantText, OFF, TRUE },
    { 3,         NORMAL, (u8 *)&gSpeedchoiceOptionSpinners, (struct OptionChoiceConfig *)OptionChoiceConfigNerfKeep, (u8 *)&gSpeedchoiceTooltipSpinners, KEEP, TRUE },
    { 3,         NORMAL, (u8 *)&gSpeedchoiceOptionMaxVision, (struct OptionChoiceConfig *)OptionChoiceConfigSaneHell, (u8 *)&gSpeedchoiceTooltipMaxVision, OFF_2, TRUE },
    { 2,         NORMAL, (u8 *)&gSpeedchoiceOptionNerfRoxanne, (struct OptionChoiceConfig *)OptionChoiceConfigYesNo, (u8 *)&gSpeedchoiceTooltipNerfRoxanne, OFF, TRUE },
    { 2,         NORMAL, (u8 *)&gSpeedchoiceOptionSuperBike, (struct OptionChoiceConfig *)OptionChoiceConfigOnOff, (u8 *)&gSpeedchoiceTooltipSuperBike, OFF, TRUE },
    { 2,         NORMAL, (u8 *)&gSpeedchoiceOptionNewWildEnc, (struct OptionChoiceConfig *)OptionChoiceConfigOnOff, (u8 *)&gSpeedchoiceTooltipNewWildEnc, OFF, TRUE },
    { 2,         NORMAL, (u8 *)&gSpeedchoiceOptionEarlyFly, (struct OptionChoiceConfig *)OptionChoiceConfigYesNo, (u8 *)&gSpeedchoiceTooltipEarlyFly, NO, TRUE },
    { 2,         NORMAL, (u8 *)&gSpeedchoiceOptionRunEverywhere, (struct OptionChoiceConfig *)OptionChoiceConfigOnOff, (u8 *)&gSpeedchoiceTooltipRunEverywhere, OFF, TRUE },
    { 2,         NORMAL, (u8 *)&gSpeedchoiceOptionMemeIsland, (struct OptionChoiceConfig *)OptionChoiceConfigYesNo, (u8 *)&gSpeedchoiceTooltipMemeIsland, NO, TRUE },
    { 2,         NORMAL, (u8 *)&gSpeedchoiceOptionBetterMarts, (struct OptionChoiceConfig *)OptionChoiceConfigOnOff, (u8 *)&gSpeedchoiceTooltipBetterMarts, OFF, TRUE },
    { 3,         NORMAL, (u8 *)&gSpeedchoiceOptionGoodEarlyWilds, (struct OptionChoiceConfig *)OptionChoiceConfigOffRand, (u8 *)&gSpeedchoiceTooltipGoodEarlyWilds, OFF_2, TRUE },
    { 2,         NORMAL, (u8 *)&gSpeedchoiceOptionEarlySurf, (struct OptionChoiceConfig *)OptionChoiceConfigOnOff, (u8 *)&gSpeedchoiceTooltipEarlySurf, OFF, TRUE },
    { MAX_PAGES, NORMAL, (u8 *)&gSpeedchoiceOptionPage, (struct OptionChoiceConfig *)OptionChoiceConfigPage, NULL, 1, TRUE } // see above comment.
};

// we need to extern the randomizer check value. If the ROM could see the value assigned (which is 0 by default), then it would be optimized out, but we need this location to be externally written to by the randomizer.
extern u32 gRandomizerCheckValue;

extern void sub_8032250(struct WindowTemplate *window);
extern void DrawMainMenuWindowBorder(struct WindowTemplate *template, u16 baseTileNum);
extern void task_new_game_prof_birch_speech_1(u8);
extern u16 gUnknown_02022D06;
extern const struct BgTemplate gUnknown_082FF0E8[];
extern const struct WindowTemplate gUnknown_085B1DDC;

EWRAM_DATA u8 gStoredPageNum = 0; // default is 0, only renders options again if it's different than the task data's page number.
EWRAM_DATA struct SpeedchoiceConfigStruct gLocalSpeedchoiceConfig = {0};
EWRAM_DATA struct MapObjectTimerBackup gMapObjectTimerBackup[MAX_SPRITES] = {0};
EWRAM_DATA bool8 gLastMenuWasSubmenu = {0};
EWRAM_DATA bool8 gPokedexAreaScreenFlag = {0};

static void DrawHeaderWindow(void);
static void sub_80BB154(void);
static void Task_SpeedchoiceMenuFadeIn(u8 taskId);
u8 GetPageDrawCount(u8 page);
void SetPageIndexFromTrueIndex(u8 taskId, s16 index);

void InitializeOptionChoicesAndConfig(u8 taskId)
{
    u8 i;

    // set the local config for the current menu.
    for(i = 0; i < CURRENT_OPTIONS_NUM; i++)
        gLocalSpeedchoiceConfig.optionConfig[i] = SpeedchoiceOptions[i].defaultOption;

    // this would be a for loop, but i want to use the fewest bits possible to avoid shifting RAM too much: hence the ugly per-option saving.
    gSaveBlock2Ptr->speedchoiceConfig.bwexp = SpeedchoiceOptions[BWEXP].defaultOption;
    gSaveBlock2Ptr->speedchoiceConfig.plotless = SpeedchoiceOptions[PLOTLESS].defaultOption;
    gSaveBlock2Ptr->speedchoiceConfig.instantText = SpeedchoiceOptions[INSTANTTEXT].defaultOption;
    gSaveBlock2Ptr->speedchoiceConfig.spinners = SpeedchoiceOptions[SPINNERS].defaultOption;
    gSaveBlock2Ptr->speedchoiceConfig.maxVision = SpeedchoiceOptions[MAXVISION].defaultOption;
    gSaveBlock2Ptr->speedchoiceConfig.nerfRoxanne = SpeedchoiceOptions[NERFROXANNE].defaultOption;
    gSaveBlock2Ptr->speedchoiceConfig.superbike = SpeedchoiceOptions[SUPERBIKE].defaultOption;
    gSaveBlock2Ptr->speedchoiceConfig.newwildencounters = SpeedchoiceOptions[NEWWILDENC].defaultOption;
    gSaveBlock2Ptr->speedchoiceConfig.earlyfly = SpeedchoiceOptions[EARLYFLY].defaultOption;
    gSaveBlock2Ptr->speedchoiceConfig.runEverywhere = SpeedchoiceOptions[RUN_EVERYWHERE].defaultOption;
    gSaveBlock2Ptr->speedchoiceConfig.memeIsland = SpeedchoiceOptions[MEME_ISLAND].defaultOption;
    gSaveBlock2Ptr->speedchoiceConfig.betterMarts = SpeedchoiceOptions[BETTER_MARTS].defaultOption;
    gSaveBlock2Ptr->speedchoiceConfig.goodEarlyWilds = SpeedchoiceOptions[GOOD_EARLY_WILDS].defaultOption;
    gSaveBlock2Ptr->speedchoiceConfig.earlysurf = SpeedchoiceOptions[EARLYSURF].defaultOption;
}

bool8 CheckSpeedchoiceOption(u8 option, u8 selection)
{
    switch(option)
    {
        case BWEXP:
            return gSaveBlock2Ptr->speedchoiceConfig.bwexp == selection;
        case PLOTLESS:
            return gSaveBlock2Ptr->speedchoiceConfig.plotless == selection;
        case INSTANTTEXT:
            return gSaveBlock2Ptr->speedchoiceConfig.instantText == selection;
        case SPINNERS:
            return gSaveBlock2Ptr->speedchoiceConfig.spinners == selection;
        case MAXVISION:
            return gSaveBlock2Ptr->speedchoiceConfig.maxVision == selection;
        case NERFROXANNE:
            return gSaveBlock2Ptr->speedchoiceConfig.nerfRoxanne == selection;
        case SUPERBIKE:
            return gSaveBlock2Ptr->speedchoiceConfig.superbike == selection;
        case NEWWILDENC:
            return gSaveBlock2Ptr->speedchoiceConfig.newwildencounters == selection;
        case EARLYFLY:
            return gSaveBlock2Ptr->speedchoiceConfig.earlyfly == selection;
        case RUN_EVERYWHERE:
            return gSaveBlock2Ptr->speedchoiceConfig.runEverywhere == selection;
        case MEME_ISLAND:
            return gSaveBlock2Ptr->speedchoiceConfig.memeIsland == selection;
        case BETTER_MARTS:
            return gSaveBlock2Ptr->speedchoiceConfig.betterMarts == selection;
        case GOOD_EARLY_WILDS:
            return gSaveBlock2Ptr->speedchoiceConfig.goodEarlyWilds == selection;
        case EARLYSURF:
            return gSaveBlock2Ptr->speedchoiceConfig.earlysurf == selection;
        default:
            return FALSE;
    }
}

static void DrawOptionMenuChoice(const u8 *text, u8 x, u8 y, u8 style)
{
    u8 dst[16];
    u16 i;

    for (i = 0; *text != EOS && i <= 14; i++)
        dst[i] = *(text++);

    if (style != 0)
    {
        dst[2] = 4;
        dst[5] = 5;
    }

    dst[i] = EOS;
    PrintTextOnWindow(WIN_OPTIONS, 1, dst, x, y, TEXT_SPEED_FF, NULL);
}

static u8 ProcessGeneralInput(struct SpeedchoiceOption *option, u8 selection, bool8 indexedToOne) // if indexedToOne is true (1), i can conveniently use it as the selection anchor.
{
    if(option->optionType == ARROW_SELECTABLE)
    {
        if(gMain.newKeys & L_BUTTON)
        {
            if(selection < 10) // will it underflow?
            {
                u8 remainder = (10 - selection); // get the remainder from selection to 10 to get the correct value to subtract from 200.
                selection = (option->optionCount - (!indexedToOne)) - remainder;
            }
            else if(selection == 10)
                selection = (option->optionCount - (!indexedToOne));
            else
                selection -= 10;
            if(option->string != gSpeedchoiceOptionPage)
                PlaySE(SE_SELECT);
            else
                PlaySE(SE_WIN_OPEN); // page scrolling.
        }
        else if(gMain.newKeys & R_BUTTON)
        {
            if(selection + 10 > (option->optionCount - (!indexedToOne)))
            {
                u8 remainder = (selection + 10) - (option->optionCount - (!indexedToOne));
                selection = remainder;
            }
            else
                selection += 10;
            if(option->string != gSpeedchoiceOptionPage)
                PlaySE(SE_SELECT);
            else
                PlaySE(SE_WIN_OPEN); // page scrolling.
        }
    }
    if(gMain.newKeys & DPAD_RIGHT)
    {
        if(option->enabled == FALSE)
        {
            PlaySE(SE_HAZURE);
            return selection;
        }
        if(selection == (option->optionCount - (!indexedToOne))) // i invert the option because when indexedToOne is set to true (or 1) it means i do not subtract 1 since it's not 0 indexed, so invert the boolean in both cases to get the correct modifier.
            selection = indexedToOne;
        else
            selection++;
        if(option->string != gSpeedchoiceOptionPage)
            PlaySE(SE_SELECT);
        else
            PlaySE(SE_WIN_OPEN); // page scrolling.
    }
    // i dont return immediately because emulators could hold both right and left down.
    if(gMain.newKeys & DPAD_LEFT)
    {
        if(option->enabled == FALSE)
        {
            PlaySE(SE_HAZURE);
            return selection;
        }
        if(selection == indexedToOne)
            selection = (option->optionCount - (!indexedToOne));
        else
            selection--;
        if(option->string != gSpeedchoiceOptionPage)
            PlaySE(SE_SELECT);
        else
            PlaySE(SE_WIN_OPEN); // page scrolling.
    }
    return selection;
}

// code
static void MainCB2(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void HighlightHeaderBox(void)
{
    SetGpuReg(REG_OFFSET_WIN1H, WIN_RANGE(17, 223));
    SetGpuReg(REG_OFFSET_WIN1V, WIN_RANGE(1, 31));
}

//This version uses addition '+' instead of OR '|'.
#define WIN_RANGE_(a, b) (((a) << 8) + (b))

static void HighlightOptionMenuItem(u8 index)
{
    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(16, 224));
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE_(index * 16 + 40, index * 16 + 56));
}

void CB2_InitSpeedchoice(void);
void DrawPageOptions(u8, u8);

// HACK!!!
void Task_InitSpeedchoiceMenu(u8 taskId)
{
    SetMainCallback2(CB2_InitSpeedchoice);
    DestroyTask(taskId);
}

void CB2_InitSpeedchoice(void)
{
    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankCallback(NULL);
        gMain.state++;
        break;
    case 1:
    {
        u8 *addr;
        u32 size;

        addr = (u8 *)VRAM;
        size = 0x18000;
        while (1)
        {
            DmaFill16(3, 0, addr, 0x1000);
            addr += 0x1000;
            size -= 0x1000;
            if (size <= 0x1000)
            {
                DmaFill16(3, 0, addr, size);
                break;
            }
        }
        DmaClear32(3, OAM, OAM_SIZE);
        DmaClear16(3, PLTT, PLTT_SIZE);
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sSpeedchoiceMenuBgTemplates, ARRAY_COUNT(sSpeedchoiceMenuBgTemplates));
        ChangeBgX(0, 0, 0);
        ChangeBgY(0, 0, 0);
        ChangeBgX(1, 0, 0);
        ChangeBgY(1, 0, 0);
        ChangeBgX(2, 0, 0);
        ChangeBgY(2, 0, 0);
        ChangeBgX(3, 0, 0);
        ChangeBgY(3, 0, 0);
        InitWindows(sSpeedchoiceMenuWinTemplates);
        DeactivateAllTextPrinters();
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, 5);
        SetGpuReg(REG_OFFSET_WINOUT, 39);
        SetGpuReg(REG_OFFSET_BLDCNT, 193);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 4);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        ShowBg(0);
        ShowBg(1);
        ShowBg(2);
        gMain.state++;
    }
        break;
    case 2:
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        gMain.state++;
        break;
    case 3:
        LoadBgTiles(1, GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->tiles, 0x120, 0x1A2);
        gMain.state++;
        break;
    case 4:
        LoadPalette(sUnknown_0855C6A0, 0, sizeof(sUnknown_0855C6A0));
        LoadPalette(GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->pal, 0x70, 0x20);
        gMain.state++;
        break;
    case 5:
        LoadPalette(sUnknown_0855C604, 0x10, sizeof(sUnknown_0855C604));
        LoadPalette(gMainMenuTextPal, 0xF0, sizeof(gMainMenuTextPal));
        gMain.state++;
        break;
    case 6:
        PutWindowTilemap(0);
        DrawHeaderWindow();
        gMain.state++;
        break;
    case 7:
        gMain.state++;
        break;
    case 8:
        PutWindowTilemap(1);
        //DrawOptionMenuTexts();
        gMain.state++;
    case 9:
        sub_80BB154();
        gMain.state++;
        break;
    case 10:
    {
        u8 taskId = CreateTask(Task_SpeedchoiceMenuFadeIn, 0);

        gStoredPageNum = 1;

        gLocalSpeedchoiceConfig.trueIndex = 0;
        gLocalSpeedchoiceConfig.pageIndex = 0;
        gLocalSpeedchoiceConfig.pageNum = 1;

        InitializeOptionChoicesAndConfig(taskId);

        DrawHeaderWindow();
        DrawPageOptions(taskId, gLocalSpeedchoiceConfig.pageNum);

        /*TextSpeed_DrawChoices(gTasks[taskId].data[TD_TEXTSPEED]);
        BattleScene_DrawChoices(gTasks[taskId].data[TD_BATTLESCENE]);
        BattleStyle_DrawChoices(gTasks[taskId].data[TD_BATTLESTYLE]);
        Sound_DrawChoices(gTasks[taskId].data[TD_SOUND]);
        ButtonMode_DrawChoices(gTasks[taskId].data[TD_BUTTONMODE]);
        FrameType_DrawChoices(gTasks[taskId].data[TD_FRAMETYPE]);
        HighlightOptionMenuItem(gTasks[taskId].data[TD_MENUSELECTION]);*/

        HighlightHeaderBox();
        HighlightOptionMenuItem(gLocalSpeedchoiceConfig.pageIndex);
        PlayBGM(MUS_CONLOBBY);
        gMain.state++;
        break;
    }
    case 11:
        BeginNormalPaletteFade(-1, 0, 0x10, 0, 0);
        SetVBlankCallback(VBlankCB);
        SetMainCallback2(MainCB2);
        return;
    }
}

#define CHAR_0 0xA1
#define CHAR_PERCENT 0x5B

#define NEWMENUOPTIONCOORDS(i)  ((i * 16) + 2)

static u8 *FormatPercentNumber(char *text, u8 selection, u8 x, u8 y, u8 style) // style is unused
{
    memcpy(text, gSystemText_TerminatorS, 3); // copy the palette control code.

    // there are no more than 10 pages, so format it as a single digit.
    text[3] = (selection / 100) + CHAR_0; // hundreds
    text[4] = ((selection % 100) / 10) + CHAR_0;    // tens
    text[5] = ((selection % 100) % 10) + CHAR_0; // ones
    text[6] = CHAR_PERCENT;
    text[7] = EOS;
}

static void DrawPageChoice(u8 selection)
{
    u8 text[5];

    memcpy(text, gSystemText_TerminatorS, 3);

    text[3] = selection + CHAR_0;
    text[4] = EOS;

    PrintTextOnWindow(SPD_WIN_OPTIONS, 1, text, 40, NEWMENUOPTIONCOORDS(5), TEXT_SPEED_FF, NULL);
}

// used for all but page.
static void DrawGeneralChoices(struct SpeedchoiceOption *option, u8 selection, u8 row, bool8 isPercent)
{
    u8 styles[MAX_CHOICES];
    u8 numChoices = option->optionCount;
    u8 i;

    if(numChoices < MAX_CHOICES)
    {
        for(i = 0; i < numChoices; i++)
            styles[i] = 0;

        styles[selection] = 1;
    }

    if(option->optionType == ARROW_SELECTABLE)
    {
        u8 text[8];
        s16 x_left = Arrows[0].x;
        s16 x_right = Arrows[1].x;
        s16 y = NEWMENUOPTIONCOORDS(row);

        DrawOptionMenuChoice(Arrows[0].string, x_left, y, 0); // left arrow
        DrawOptionMenuChoice(Arrows[1].string, x_right, y, 0); // right arrow

        // draw single option.
        FormatPercentNumber(text, selection, ((x_left + x_right) / 2) - 8, y, 0x8);
        DrawOptionMenuChoice(text, ((x_left + x_right) / 2) - 8, y, 0x8);        
    }
    else
    {
        for(i = 0; i < numChoices; i++)
        {
            s16 x = option->options[i].x;
            s16 y = NEWMENUOPTIONCOORDS(row);
            u8 *string = option->options[i].string;

            DrawOptionMenuChoice(string, x, y, styles[i]);
        }
    }
}

static void Task_SpeedchoiceMenuProcessInput(u8);
static void DrawTooltip(u8 taskId, const u8 *str, int speed, bool32 isYesNo);

EWRAM_DATA bool32 gFirstLoad = FALSE;

// WIP
static void Task_SpeedchoiceMenuFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        gTasks[taskId].func = Task_SpeedchoiceMenuProcessInput;
    }
}

// lastOrFirst, TRUE means last, FALSE means first available
u8 GetPageOptionTrueIndex(bool8 lastOrFirst, u8 page)
{
    if(lastOrFirst == LAST)
        return (OPTIONS_PER_PAGE * (page - 1)) + GetPageDrawCount(page) - 1;
    else
        return (OPTIONS_PER_PAGE * (page - 1));
}

// same as above, but return the page index.
u8 GetPageOptionPageIndex(bool8 lastOrFirst, u8 page)
{
    return (lastOrFirst) ? GetPageDrawCount(page) : 1;
}

static void Task_WaitForTooltip(u8 taskId)
{
    RunTextPrinters();

    if(!IsTextPrinterActive(SPD_WIN_TOOLTIP))
    {
        if(gMain.newKeys & A_BUTTON)
        {
            ClearWindowTilemap(SPD_WIN_TOOLTIP);
            sub_8032250((struct WindowTemplate *)&sSpeedchoiceMenuWinTemplates[SPD_WIN_TOOLTIP]);
            DrawPageOptions(taskId, gLocalSpeedchoiceConfig.pageNum);
            gTasks[taskId].func = Task_SpeedchoiceMenuProcessInput;
        }
    }
}

static void DrawTooltip(u8 taskId, const u8 *str, int speed, bool32 isYesNo)
{
    FillWindowPixelBuffer(SPD_WIN_TOOLTIP, 0x11);
    PrintTextOnWindow(SPD_WIN_TOOLTIP, 1, str, 0, 1, speed, NULL);
    //sub_8098858(SPD_WIN_TOOLTIP, 0x1D5, 0);
    DrawMainMenuWindowBorder((struct WindowTemplate *)&sSpeedchoiceMenuWinTemplates[SPD_WIN_TOOLTIP], 418);
    PutWindowTilemap(SPD_WIN_TOOLTIP);
    CopyWindowToVram(SPD_WIN_TOOLTIP, 3);
    if(isYesNo)
    {
        FillWindowPixelBuffer(3, 0x11);
        DrawMainMenuWindowBorder((struct WindowTemplate *)&sSpeedchoiceMenuWinTemplates[SPD_WIN_YESNO], 418);
        PutWindowTilemap(3);
        CopyWindowToVram(3, 3);
    }
    SetGpuReg(REG_OFFSET_WIN1H, WIN_RANGE(1, 241));
    SetGpuReg(REG_OFFSET_WIN1V, WIN_RANGE_(114, 160));
    if(!isYesNo)
        gTasks[taskId].func = Task_WaitForTooltip;
}

u32 CountLeadingZeros(u32 value)
{
    u32 result = 0;

    if (!value)
        return 32;

    while (value < 0x80000000)
    {
        result ++;
        value <<= 1;
    }

    return result;
}

u8 GetNumBitsUsed(u8 numOptions)
{
    return 32 - CountLeadingZeros(numOptions);
}

u32 CalculateCheckValue(u8 taskId)
{
    u32 checkValue;
    u8 i; // current option
    u8 totalBitsUsed;

    // do checkvalue increment for 32-bit value.
    for(checkValue = 0, i = 0, totalBitsUsed = 0; i < CURRENT_OPTIONS_NUM; i++)
    {
        totalBitsUsed += GetNumBitsUsed(SpeedchoiceOptions[i].optionCount);
        checkValue += gLocalSpeedchoiceConfig.optionConfig[i] << (i + (totalBitsUsed - 1));
    }

    // seed RNG with checkValue for more hash-like number.
    checkValue = 0x41c64e6d * checkValue + 0x00006073;

    // xor with randomizer value, if one is present.
    checkValue = checkValue ^ gRandomizerCheckValue;

    // get rid of sign extension.
    checkValue = abs(checkValue);

    return checkValue;
}

static void SaveSpeedchoiceOptions(u8 taskId)
{
    // once again i would prefer to use an extensible for loop here, but the options being bitfields means that it cannot currently be done.
    gSaveBlock2Ptr->speedchoiceConfig.bwexp = gLocalSpeedchoiceConfig.optionConfig[BWEXP];
    gSaveBlock2Ptr->speedchoiceConfig.plotless = gLocalSpeedchoiceConfig.optionConfig[PLOTLESS];
    gSaveBlock2Ptr->speedchoiceConfig.instantText = gLocalSpeedchoiceConfig.optionConfig[INSTANTTEXT];
    gSaveBlock2Ptr->speedchoiceConfig.spinners = gLocalSpeedchoiceConfig.optionConfig[SPINNERS];
    gSaveBlock2Ptr->speedchoiceConfig.maxVision = gLocalSpeedchoiceConfig.optionConfig[MAXVISION];
    gSaveBlock2Ptr->speedchoiceConfig.nerfRoxanne = gLocalSpeedchoiceConfig.optionConfig[NERFROXANNE];
    gSaveBlock2Ptr->speedchoiceConfig.superbike = gLocalSpeedchoiceConfig.optionConfig[SUPERBIKE];
    gSaveBlock2Ptr->speedchoiceConfig.newwildencounters = gLocalSpeedchoiceConfig.optionConfig[NEWWILDENC];
    gSaveBlock2Ptr->speedchoiceConfig.earlyfly = gLocalSpeedchoiceConfig.optionConfig[EARLYFLY];
    gSaveBlock2Ptr->speedchoiceConfig.runEverywhere = gLocalSpeedchoiceConfig.optionConfig[RUN_EVERYWHERE];
    gSaveBlock2Ptr->speedchoiceConfig.memeIsland = gLocalSpeedchoiceConfig.optionConfig[MEME_ISLAND];
    gSaveBlock2Ptr->speedchoiceConfig.betterMarts = gLocalSpeedchoiceConfig.optionConfig[BETTER_MARTS];
    gSaveBlock2Ptr->speedchoiceConfig.goodEarlyWilds = gLocalSpeedchoiceConfig.optionConfig[GOOD_EARLY_WILDS];
    gSaveBlock2Ptr->speedchoiceConfig.earlysurf = gLocalSpeedchoiceConfig.optionConfig[EARLYSURF];
}

static void Task_SpeedchoiceMenuFadeOut(u8 taskId)
{
    if(!gPaletteFade.active)
    {
        u8 *addr;
        u32 size;

        addr = (u8 *)VRAM;
        size = 0x18000;
        while (1)
        {
            DmaFill16(3, 0, addr, 0x1000);
            addr += 0x1000;
            size -= 0x1000;
            if (size <= 0x1000)
            {
                DmaFill16(3, 0, addr, size);
                break;
            }
        }
        DmaClear32(3, OAM, OAM_SIZE);
        DmaClear16(3, PLTT, PLTT_SIZE);
        gPlttBufferUnfaded[0] = 0;
        gPlttBufferFaded[0] = 0;
        /*ClearWindowTilemap(SPD_WIN_TEXT_OPTION);
        ClearWindowTilemap(SPD_WIN_OPTIONS);
        ClearWindowTilemap(SPD_WIN_TOOLTIP);
        ClearWindowTilemap(3);
        sub_8032250(&sSpeedchoiceMenuWinTemplates[SPD_WIN_TEXT_OPTION]);
        sub_8032250(&sSpeedchoiceMenuWinTemplates[SPD_WIN_OPTIONS]);
        sub_8032250(&sSpeedchoiceMenuWinTemplates[SPD_WIN_TOOLTIP]);
        sub_8032250(&sSpeedchoiceMenuWinTemplates[SPD_WIN_YESNO]);*/
        FreeAllWindowBuffers();
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        SetGpuReg(REG_OFFSET_BG2CNT, 0);
        SetGpuReg(REG_OFFSET_BG1CNT, 0);
        SetGpuReg(REG_OFFSET_BG0CNT, 0);
        SetGpuReg(REG_OFFSET_BG2HOFS, 0);
        SetGpuReg(REG_OFFSET_BG2VOFS, 0);
        SetGpuReg(REG_OFFSET_BG1HOFS, 0);
        SetGpuReg(REG_OFFSET_BG1VOFS, 0);
        SetGpuReg(REG_OFFSET_BG0HOFS, 0);
        SetGpuReg(REG_OFFSET_BG0VOFS, 0);
        ResetBgs();
        InitBgsFromTemplates(0, gUnknown_082FF0E8, 2);
        gTasks[taskId].func = task_new_game_prof_birch_speech_1;
    }
}

static void Task_AskToStartGame(u8 taskId)
{
    switch (ProcessMenuInputNoWrap_())
    {
    case 0:  // YES
        PlayBGM(MUS_STOP);
        PlaySE(SE_SELECT);
        SaveSpeedchoiceOptions(taskId);
        BeginNormalPaletteFade(-1, 0, 0, 0x10, 0);
        gTasks[taskId].func = Task_SpeedchoiceMenuFadeOut;
        break;
    case 1:  // NO
    case -1: // B button
        PlaySE(SE_SELECT);
        ClearWindowTilemap(SPD_WIN_TOOLTIP);
        ClearWindowTilemap(3);
        sub_8032250((struct WindowTemplate *)&sSpeedchoiceMenuWinTemplates[SPD_WIN_TOOLTIP]);
        sub_8032250((struct WindowTemplate *)&sSpeedchoiceMenuWinTemplates[SPD_WIN_YESNO]);
        DrawPageOptions(taskId, gLocalSpeedchoiceConfig.pageNum);
        gTasks[taskId].func = Task_SpeedchoiceMenuProcessInput;
        break;
    }
}

static void Task_SpeedchoiceMenuSave(u8 taskId)
{
    ConvertIntToHexStringN(gStringVar1, CalculateCheckValue(taskId), STR_CONV_MODE_LEADING_ZEROS, 8);
    StringExpandPlaceholders(gStringVar4, gSpeedchoiceStartGameText);
    DrawTooltip(taskId, gStringVar4, TEXT_SPEED_FF, TRUE); // a bit of a hack, but whatever.
    CreateYesNoMenu(&sSpeedchoiceMenuWinTemplates[SPD_WIN_YESNO], 418, 2, 0);

    gTasks[taskId].func = Task_AskToStartGame;
}

static void Task_SpeedchoiceMenuProcessInput(u8 taskId)
{
	if(!gFirstLoad)
	{
		DrawTooltip(taskId, gSpeedchoiceTooltipExplanation, GetPlayerTextSpeed(), FALSE);
		gFirstLoad = TRUE;
	}
    else if (gMain.newKeys & A_BUTTON)
    {
        if (gLocalSpeedchoiceConfig.trueIndex == START_GAME)
            gTasks[taskId].func = Task_SpeedchoiceMenuSave;
    }
    else if (gMain.newKeys & SELECT_BUTTON) // do tooltip.
    {
        if(gLocalSpeedchoiceConfig.trueIndex <= CURRENT_OPTIONS_NUM && SpeedchoiceOptions[gLocalSpeedchoiceConfig.trueIndex].tooltip != NULL)
            DrawTooltip(taskId, SpeedchoiceOptions[gLocalSpeedchoiceConfig.trueIndex].tooltip, GetPlayerTextSpeed(), FALSE);
    }
    else if (gMain.newKeys & DPAD_UP)
    {
        if(gLocalSpeedchoiceConfig.trueIndex == PAGE)
            gLocalSpeedchoiceConfig.trueIndex = GetPageOptionTrueIndex(LAST, gLocalSpeedchoiceConfig.pageNum); // set the entry to the last available option.
        else if(gLocalSpeedchoiceConfig.trueIndex > GetPageOptionTrueIndex(FIRST, gLocalSpeedchoiceConfig.pageNum))
            gLocalSpeedchoiceConfig.trueIndex--;
        else
            gLocalSpeedchoiceConfig.trueIndex = START_GAME;

        SetPageIndexFromTrueIndex(taskId, gLocalSpeedchoiceConfig.trueIndex);
        HighlightOptionMenuItem(gLocalSpeedchoiceConfig.pageIndex);
    }
    else if (gMain.newKeys & DPAD_DOWN)
    {
        if(gLocalSpeedchoiceConfig.trueIndex == GetPageOptionTrueIndex(LAST, gLocalSpeedchoiceConfig.pageNum))
            gLocalSpeedchoiceConfig.trueIndex = PAGE; // you are at the last option when you press down, go to page index.
        else if(gLocalSpeedchoiceConfig.trueIndex == START_GAME)
            gLocalSpeedchoiceConfig.trueIndex = GetPageOptionTrueIndex(FIRST, gLocalSpeedchoiceConfig.pageNum);
        else
            gLocalSpeedchoiceConfig.trueIndex++;

        SetPageIndexFromTrueIndex(taskId, gLocalSpeedchoiceConfig.trueIndex);
        HighlightOptionMenuItem(gLocalSpeedchoiceConfig.pageIndex);
    }
    else
    {
        u8 trueIndex = gLocalSpeedchoiceConfig.trueIndex;
        u8 selection = gLocalSpeedchoiceConfig.optionConfig[trueIndex];
        switch (trueIndex)
        {
            default:
                if(trueIndex < CURRENT_OPTIONS_NUM)
                {
                    // lol. I don't know why I hardcoded this in Sapphire.
                    //if(trueIndex == NERFROXANNE)
                    //    gLocalSpeedchoiceConfig.optionConfig[trueIndex] = ProcessGeneralInput((struct SpeedchoiceOption *)&SpeedchoiceOptions[trueIndex], selection, TRUE);
                    //else
                    u8 oldSelection = gLocalSpeedchoiceConfig.optionConfig[trueIndex];
                    gLocalSpeedchoiceConfig.optionConfig[trueIndex] = ProcessGeneralInput((struct SpeedchoiceOption *)&SpeedchoiceOptions[trueIndex], selection, FALSE);
                    DrawGeneralChoices((struct SpeedchoiceOption *)&SpeedchoiceOptions[trueIndex], gLocalSpeedchoiceConfig.optionConfig[trueIndex], gLocalSpeedchoiceConfig.pageIndex, FALSE);
                    if(oldSelection != gLocalSpeedchoiceConfig.optionConfig[trueIndex])
                        DrawPageOptions(taskId, gLocalSpeedchoiceConfig.pageNum); // HACK!!! The page has to redraw. But only redraw it if the selection changed, otherwise it lags.
                }
                break;
            case PAGE:
                gLocalSpeedchoiceConfig.pageNum = ProcessGeneralInput((struct SpeedchoiceOption *)&SpeedchoiceOptions[CURRENT_OPTIONS_NUM], gLocalSpeedchoiceConfig.pageNum, TRUE);
                //DrawPageChoice(gLocalSpeedchoiceConfig.pageNum); Depreciated.
                if(gLocalSpeedchoiceConfig.pageNum != gStoredPageNum) // only redraw if the page updates!
                {
                    DrawPageOptions(taskId, gLocalSpeedchoiceConfig.pageNum);
                    gStoredPageNum = gLocalSpeedchoiceConfig.pageNum; // update the page.
                }
                break;
            case START_GAME:
                break;
        }
    }
}

void DrawHeaderWindow(void)
{
    FillWindowPixelBuffer(WIN_TEXT_OPTION, 0x11);
    PrintTextOnWindow(WIN_TEXT_OPTION, 1, gSpeedchoiceTextHeader, 4, 1, TEXT_SPEED_FF, NULL);
    PrintTextOnWindow(WIN_TEXT_OPTION, 1, gSpeedchoiceCurrentVersion, 175, 1, TEXT_SPEED_FF, NULL);
    CopyWindowToVram(WIN_TEXT_OPTION, 3);
}

void DrawOptionsAndChoicesWindow(void)
{
    FillWindowPixelBuffer(WIN_OPTIONS, 0x11);
    CopyWindowToVram(WIN_OPTIONS, 3);
}

u8 GetPageDrawCount(u8 page)
{
    if ((page * OPTIONS_PER_PAGE) > CURRENT_OPTIONS_NUM)
        return CURRENT_OPTIONS_NUM % OPTIONS_PER_PAGE;

    return OPTIONS_PER_PAGE;
}

void DrawPageOptions(u8 taskId, u8 page)
{
    u8 i;
    u8 drawCount = GetPageDrawCount(page);

    FillWindowPixelBuffer(WIN_OPTIONS, 0x11);

    // print page options.
    for(i = 0; i < drawCount; i++)
    {
        struct SpeedchoiceOption *option = (struct SpeedchoiceOption *)&SpeedchoiceOptions[i + (OPTIONS_PER_PAGE * (page - 1))];
        u8 *string = option->string;

        PrintTextOnWindow(WIN_OPTIONS, 1, string, 4, NEWMENUOPTIONCOORDS(i), TEXT_SPEED_FF, NULL);
        // TODO: Draw on WIN_OPTIONS, if it's broken
        DrawGeneralChoices(option, gLocalSpeedchoiceConfig.optionConfig[i + ((page-1) * 5)], i, FALSE);
    }

    PrintTextOnWindow(WIN_OPTIONS, 1, gSpeedchoiceOptionPage, 4, NEWMENUOPTIONCOORDS(5), TEXT_SPEED_FF, NULL);
    PrintTextOnWindow(WIN_OPTIONS, 1, gSpeedchoiceOptionStartGame, 4, NEWMENUOPTIONCOORDS(6), TEXT_SPEED_FF, NULL);
    DrawPageChoice(gLocalSpeedchoiceConfig.pageNum);
    CopyWindowToVram(WIN_OPTIONS, 3);
}

void SetPageIndexFromTrueIndex(u8 taskId, s16 index) // data is s16.
{
    if(index == PAGE)
        gLocalSpeedchoiceConfig.pageIndex = 5;
    else if(index == START_GAME)
        gLocalSpeedchoiceConfig.pageIndex = 6;
    else
        gLocalSpeedchoiceConfig.pageIndex = (oldmin((index % OPTIONS_PER_PAGE), OPTIONS_PER_PAGE));
}

static void sub_80BB154(void)
{
    //                   bg, tileNum, x,    y,    width, height,  pal
    FillBgTilemapBufferRect(1, 0x1A2, 1,    0,      1,      1,      7);
    FillBgTilemapBufferRect(1, 0x1A3, 2,    0,      0x1B,   1,      7);
    FillBgTilemapBufferRect(1, 0x1A4, 28,   0,      1,      1,      7);
    FillBgTilemapBufferRect(1, 0x1A5, 1,    1,      1,      2,      7);
    FillBgTilemapBufferRect(1, 0x1A7, 28,   1,      1,      2,      7);
    FillBgTilemapBufferRect(1, 0x1A8, 1,    3,      1,      1,      7);
    FillBgTilemapBufferRect(1, 0x1A9, 2,    3,      0x1B,   1,      7);
    FillBgTilemapBufferRect(1, 0x1AA, 28,   3,      1,      1,      7);
    FillBgTilemapBufferRect(1, 0x1A2, 1,    4,      1,      1,      7);
    FillBgTilemapBufferRect(1, 0x1A3, 2,    4,      0x1A,   1,      7);
    FillBgTilemapBufferRect(1, 0x1A4, 28,   4,      1,      1,      7);
    FillBgTilemapBufferRect(1, 0x1A5, 1,    5,      1,      0x12,   7);
    FillBgTilemapBufferRect(1, 0x1A7, 28,   5,      1,      0x12,   7);
    FillBgTilemapBufferRect(1, 0x1A8, 1,    19,     1,      1,      7);
    FillBgTilemapBufferRect(1, 0x1A9, 2,    19,     0x1A,   1,      7);
    FillBgTilemapBufferRect(1, 0x1AA, 28,   19,     1,      1,      7);

    CopyBgTilemapBufferToVram(1);
}
