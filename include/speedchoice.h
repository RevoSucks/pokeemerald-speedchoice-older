#ifndef GUARD_SPEEDCHOICE_H
#define GUARD_SPEEDCHOICE_H

// global speedchoice config
#define CURRENT_OPTIONS_NUM 14
#define MAX_CHOICES 6
#define OPTIONS_PER_PAGE 5
#define ALLOPTIONS_PER_PAGE OPTIONS_PER_PAGE + 2 // page + start game
#define MAX_PAGES 3

#define MENUOPTIONCOORDS(i) (5 + (2 * i))

#define SPINNER_HELL_TIMER 4 // once every 2 frames since the game runs at 60FPS.
#define MAX_VISION_RANGE 8
#define PURGE_SPINNER_TIMER 48
#define BATTLE_SPEED_FRACTION 4

// for a future version
#define GRASS_QUEUE_SIZE 20
#define WATER_QUEUE_SIZE 15
#define ROCKSMASH_QUEUE_SIZE 15
#define FISHING_QUEUE_SIZE 5

#define oldmin(a, b) (a < b ? a : b)
#define oldmax(a, b) (a > b ? a : b)

// options
enum
{
    BWEXP,
    PLOTLESS,
    INSTANTTEXT,
    SPINNERS,
    MAXVISION,
    NERFROXANNE,
    SUPERBIKE,
    NEWWILDENC,
    EARLYFLY,
    RUN_EVERYWHERE,
    MEME_ISLAND,
    BETTER_MARTS,
    GOOD_EARLY_WILDS,
    EARLYSURF,

    // STATIC OPTIONS
    PAGE,
    START_GAME
};

enum
{
    YES,
    NO
};

enum
{
    ON,
    OFF
};

enum
{
    PURGE,
    KEEP,
    HELL
};

enum
{
    SEMI,
    KEEP_2, // same as before but renamed to prevent conflict.
    FULL
};

enum
{
    FIRST,
    LAST
};

enum
{
    OFF_2,
    STATIC,
    RAND
};

enum
{
    // off_2 is taken up by 0.
    SANE = 1,
    // hell is taken up by 2.
};

// option types
enum
{
    NORMAL, // selectable
    ARROW_SELECTABLE
};

struct OptionChoiceConfig
{
    s16 x; // do not store the Y coordinate. Y is automatically calculated depending on the row the option is placed and therefore is not necessary.
    u8 *string; // can be null
};

// every 5 elements belongs to a page, page struct is unnecessary.
struct SpeedchoiceOption
{
    u8 optionCount; // needed for process general input, im sure there's a way to avoid using this
    u8 optionType;
    u8 *string;
    struct OptionChoiceConfig *options; // use a NULL for non existent ones, optional things in structs were introduced in C++ and this is limited.
    u8 *tooltip;
    u8 defaultOption;
    bool8 enabled;
}; 

struct SpeedchoiceConfigStruct
{
    u8 optionConfig[CURRENT_OPTIONS_NUM];
    u8 trueIndex;
    u8 pageIndex;
    u8 pageNum;
};

struct MapObjectTimerBackup
{
    bool8 backedUp;
    s16 timer;
};

void CB2_InitSpeedchoiceMenu(void);
bool8 CheckSpeedchoiceOption(u8, u8);

#endif // GUARD_SPEEDCHOICE_H
