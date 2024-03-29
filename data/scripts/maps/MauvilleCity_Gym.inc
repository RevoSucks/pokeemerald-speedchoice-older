MauvilleCity_Gym_MapScripts:: @ 820DD6E
	map_script 1, MauvilleCity_Gym_MapScript1_20DD74
	.byte 0

MauvilleCity_Gym_MapScript1_20DD74: @ 820DD74
	checkflag FLAG_0x4F2
	goto_eq MauvilleCity_Gym_EventScript_20DEE7
	switch VAR_0x4093
	case 0, MauvilleCity_Gym_EventScript_20DDBA
	case 1, MauvilleCity_Gym_EventScript_20DEAF
	case 2, MauvilleCity_Gym_EventScript_20DEBD
	case 3, MauvilleCity_Gym_EventScript_20DECB
	case 4, MauvilleCity_Gym_EventScript_20DED9
	end

MauvilleCity_Gym_EventScript_20DDBA:: @ 820DDBA
	checkflag FLAG_0x063
	goto_eq MauvilleCity_Gym_EventScript_20DDC4
	end

MauvilleCity_Gym_EventScript_20DDC4:: @ 820DDC4
	setmetatile 3, 11, 577, 1
	setmetatile 3, 12, 585, 1
	setmetatile 3, 13, 592, 1
	setmetatile 4, 10, 546, 0
	setmetatile 5, 10, 547, 0
	setmetatile 4, 11, 554, 1
	setmetatile 5, 11, 555, 1
	setmetatile 7, 10, 546, 0
	setmetatile 8, 10, 547, 0
	setmetatile 7, 11, 554, 1
	setmetatile 8, 11, 555, 1
	setmetatile 4, 13, 560, 0
	setmetatile 5, 13, 561, 0
	setmetatile 4, 14, 568, 0
	setmetatile 5, 14, 569, 0
	setmetatile 1, 10, 560, 0
	setmetatile 2, 10, 561, 0
	setmetatile 1, 11, 568, 0
	setmetatile 2, 11, 569, 0
	setmetatile 6, 8, 578, 1
	setmetatile 6, 9, 538, 0
	setmetatile 6, 10, 593, 0
	setmetatile 4, 6, 560, 0
	setmetatile 5, 6, 561, 0
	setmetatile 4, 7, 568, 0
	setmetatile 5, 7, 569, 0
	end

MauvilleCity_Gym_EventScript_20DEAF:: @ 820DEAF
	setvar VAR_0x8004, 0
	special MauvilleGymSpecial1
	goto MauvilleCity_Gym_EventScript_20DDBA
	end

MauvilleCity_Gym_EventScript_20DEBD:: @ 820DEBD
	setvar VAR_0x8004, 1
	special MauvilleGymSpecial1
	goto MauvilleCity_Gym_EventScript_20DDBA
	end

MauvilleCity_Gym_EventScript_20DECB:: @ 820DECB
	setvar VAR_0x8004, 2
	special MauvilleGymSpecial1
	goto MauvilleCity_Gym_EventScript_20DDBA
	end

MauvilleCity_Gym_EventScript_20DED9:: @ 820DED9
	setvar VAR_0x8004, 3
	special MauvilleGymSpecial1
	goto MauvilleCity_Gym_EventScript_20DDBA
	end

MauvilleCity_Gym_EventScript_20DEE7:: @ 820DEE7
	special MauvilleGymSpecial3
	end

MauvilleCity_Gym_EventScript_20DEEB:: @ 820DEEB
	trainerbattle 1, TRAINER_WATTSON_1, 0, MauvilleCity_Gym_Text_20E602, MauvilleCity_Gym_Text_20E734, MauvilleCity_Gym_EventScript_20DF2B
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, 1
	goto_eq MauvilleCity_Gym_EventScript_20DFDE
	checkflag FLAG_0x0A7
	goto_if 0, MauvilleCity_Gym_EventScript_20DF8D
	compare VAR_0x40BA, 2
	goto_eq MauvilleCity_Gym_EventScript_20DFD4
	msgbox MauvilleCity_Gym_Text_20E8E3, 4
	release
	end

MauvilleCity_Gym_EventScript_20DF2B:: @ 820DF2B
	checkspeedchoice PLOTLESS, SPD_KEEP
	goto_if TRUE, WattsonAfter
	checkspeedchoice PLOTLESS, SPD_SEMI
	goto_if TRUE, WattsonAfter
	setflag 819
	setvar VAR_0x40BF, 1
	setflag 938
	setflag 244
	setflag 926
	setflag 927
	setflag 139
	clearflag 928
	setflag 942
	@ prevent weather institute from being required on Semi+Full and Early Surf since the player can surf there early. The other 3 instances of this were guards for older saves since I didn't feel like replaying the game for the 20th time.
	checkspeedchoice PLOTLESS, SPD_KEEP @ seems weird checking for keep since it was checked earlier, but im actually just checking for SEMI or FULL.
	goto_if TRUE, WattsonAfter
	setvar VAR_0x40B3, 2
	setflag 890
	clearflag 892
	setflag 893
WattsonAfter::
	message MauvilleCity_Gym_Text_20E77F
	waitmessage
	call MauvilleCity_Gym_EventScript_27207E
	msgbox MauvilleCity_Gym_Text_20E7AA, 4
	setvar VAR_0x40D2, 3
	clearflag FLAG_0x2FE
	setflag FLAG_0x4F2
	setflag FLAG_BADGE03_GET
	addvar VAR_0x4085, 1
	compare VAR_0x4085, 6
	call_if 1, MauvilleCity_Gym_EventScript_271E84
	setvar VAR_0x8008, 3
	call MauvilleCity_Gym_EventScript_271F43
	special MauvilleGymSpecial3
	special DrawWholeMapView
	playse SE_KI_GASYAN
	call MauvilleCity_Gym_EventScript_20DFB1
	closemessage
	delay 30
	playfanfare MUS_ME_TORE_EYE
	msgbox MauvilleCity_Gym_Text_20E8B5, 4
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_0x1D5
	release
	end

MauvilleCity_Gym_EventScript_20DF8D:: @ 820DF8D
	giveitem_std ITEM_TM34
	compare VAR_RESULT, 0
	goto_eq MauvilleCity_Gym_EventScript_272054
	msgbox MauvilleCity_Gym_Text_20E844, 4
	setflag FLAG_0x0A7
	release
	end

MauvilleCity_Gym_EventScript_20DFB1:: @ 820DFB1
	giveitem_std ITEM_TM34
	compare VAR_RESULT, 0
	goto_eq MauvilleCity_Gym_EventScript_27205E
	msgbox MauvilleCity_Gym_Text_20E844, 4
	setflag FLAG_0x0A7
	return

MauvilleCity_Gym_EventScript_20DFD4:: @ 820DFD4
	msgbox MauvilleCity_Gym_Text_20E925, 4
	release
	end

MauvilleCity_Gym_EventScript_20DFDE:: @ 820DFDE
	trainerbattle 7, TRAINER_WATTSON_1, 0, MauvilleCity_Gym_Text_20E9A7, MauvilleCity_Gym_Text_20EA42, MauvilleCity_Gym_Text_20EAFD
	msgbox MauvilleCity_Gym_Text_20EA5E, 6
	end

MauvilleCity_Gym_EventScript_20DFF9:: @ 820DFF9
	lockall
	checkflag FLAG_0x4F2
	goto_eq MauvilleCity_Gym_EventScript_20E0AD
	compare VAR_0x4093, 1
	goto_eq MauvilleCity_Gym_EventScript_20E0AD
	setvar VAR_0x4093, 1
	setvar VAR_0x8004, 0
	goto MauvilleCity_Gym_EventScript_20E08D
	end

MauvilleCity_Gym_EventScript_20E01E:: @ 820E01E
	lockall
	checkflag FLAG_0x4F2
	goto_eq MauvilleCity_Gym_EventScript_20E0AD
	compare VAR_0x4093, 2
	goto_eq MauvilleCity_Gym_EventScript_20E0AD
	setvar VAR_0x4093, 2
	setvar VAR_0x8004, 1
	goto MauvilleCity_Gym_EventScript_20E08D
	end

MauvilleCity_Gym_EventScript_20E043:: @ 820E043
	lockall
	checkflag FLAG_0x4F2
	goto_eq MauvilleCity_Gym_EventScript_20E0AD
	compare VAR_0x4093, 3
	goto_eq MauvilleCity_Gym_EventScript_20E0AD
	setvar VAR_0x4093, 3
	setvar VAR_0x8004, 2
	goto MauvilleCity_Gym_EventScript_20E08D
	end

MauvilleCity_Gym_EventScript_20E068:: @ 820E068
	lockall
	checkflag FLAG_0x4F2
	goto_eq MauvilleCity_Gym_EventScript_20E0AD
	compare VAR_0x4093, 4
	goto_eq MauvilleCity_Gym_EventScript_20E0AD
	setvar VAR_0x4093, 4
	setvar VAR_0x8004, 3
	goto MauvilleCity_Gym_EventScript_20E08D
	end

MauvilleCity_Gym_EventScript_20E08D:: @ 820E08D
	special MauvilleGymSpecial2
	special MauvilleGymSpecial1
	special DrawWholeMapView
	playse SE_KI_GASYAN
	checkflag FLAG_0x063
	goto_eq MauvilleCity_Gym_EventScript_20E0B4
	checkflag FLAG_0x063
	goto_if 0, MauvilleCity_Gym_EventScript_20E0AF
	releaseall
	end

MauvilleCity_Gym_EventScript_20E0AD:: @ 820E0AD
	releaseall
	end

MauvilleCity_Gym_EventScript_20E0AF:: @ 820E0AF
	setflag FLAG_0x063
	releaseall
	end

MauvilleCity_Gym_EventScript_20E0B4:: @ 820E0B4
	clearflag FLAG_0x063
	releaseall
	end

MauvilleCity_Gym_EventScript_20E0B9:: @ 820E0B9
	trainerbattle 0, TRAINER_KIRK, 0, MauvilleCity_Gym_Text_20E2BC, MauvilleCity_Gym_Text_20E2FC
	msgbox MauvilleCity_Gym_Text_20E336, 6
	end

MauvilleCity_Gym_EventScript_20E0D0:: @ 820E0D0
	trainerbattle 0, TRAINER_SHAWN, 0, MauvilleCity_Gym_Text_20E369, MauvilleCity_Gym_Text_20E3A7
	msgbox MauvilleCity_Gym_Text_20E3C1, 6
	end

MauvilleCity_Gym_EventScript_20E0E7:: @ 820E0E7
	trainerbattle 0, TRAINER_BEN, 0, MauvilleCity_Gym_Text_20E443, MauvilleCity_Gym_Text_20E469
	msgbox MauvilleCity_Gym_Text_20E47E, 6
	end

MauvilleCity_Gym_EventScript_20E0FE:: @ 820E0FE
	trainerbattle 0, TRAINER_VIVIAN, 0, MauvilleCity_Gym_Text_20E4BB, MauvilleCity_Gym_Text_20E4F4
	msgbox MauvilleCity_Gym_Text_20E50F, 6
	end

MauvilleCity_Gym_EventScript_20E115:: @ 820E115
	trainerbattle 0, TRAINER_ANGELO, 0, MauvilleCity_Gym_Text_20E593, MauvilleCity_Gym_Text_20E5A8
	msgbox MauvilleCity_Gym_Text_20E5C2, 6
	end

MauvilleCity_Gym_EventScript_20E12C:: @ 820E12C
	lock
	faceplayer
	checkflag FLAG_0x4F2
	goto_eq MauvilleCity_Gym_EventScript_20E141
	msgbox MauvilleCity_Gym_Text_20E17F, 4
	release
	end

MauvilleCity_Gym_EventScript_20E141:: @ 820E141
	msgbox MauvilleCity_Gym_Text_20E283, 4
	release
	end

MauvilleCity_Gym_EventScript_20E14B:: @ 820E14B
	lockall
	checkflag FLAG_BADGE03_GET
	goto_eq MauvilleCity_Gym_EventScript_20E16B
	goto MauvilleCity_Gym_EventScript_20E175
	end

MauvilleCity_Gym_EventScript_20E15B:: @ 820E15B
	lockall
	checkflag FLAG_BADGE03_GET
	goto_eq MauvilleCity_Gym_EventScript_20E16B
	goto MauvilleCity_Gym_EventScript_20E175
	end

MauvilleCity_Gym_EventScript_20E16B:: @ 820E16B
	msgbox MauvilleCity_Gym_Text_20E96C, 4
	releaseall
	end

MauvilleCity_Gym_EventScript_20E175:: @ 820E175
	msgbox MauvilleCity_Gym_Text_20E952, 4
	releaseall
	end

MauvilleCity_Gym_Text_20E17F: @ 820E17F
	.string "Hey, how’s it going, CHAMPION-\n"
	.string "bound {PLAYER}?\p"
	.string "WATTSON, the LEADER of MAUVILLE\n"
	.string "GYM, uses ELECTRIC-type POKéMON.\p"
	.string "If you challenge him with WATER-type\n"
	.string "POKéMON, he’ll zap them! Bzzt!\p"
	.string "And, he’s put in switch-controlled\n"
	.string "doors all over his GYM! Eccentric!\p"
	.string "Hey, go for it!$"

MauvilleCity_Gym_Text_20E283: @ 820E283
	.string "Whoa, you’re electrifying!\n"
	.string "You’ve powered the door open!$"

MauvilleCity_Gym_Text_20E2BC: @ 820E2BC
	.string "My electric soul, it’ll shatter your\n"
	.string "dreams whole, whoa-yeahah!$"

MauvilleCity_Gym_Text_20E2FC: @ 820E2FC
	.string "That was plugged in, amped up,\n"
	.string "over-driven electric, man!$"

MauvilleCity_Gym_Text_20E336: @ 820E336
	.string "POKéMON and rock, it’s all about heart,\n"
	.string "whoa-yeah!$"

MauvilleCity_Gym_Text_20E369: @ 820E369
	.string "I trained under WATTSON!\n"
	.string "There ain’t no way I’ll lose easily!$"

MauvilleCity_Gym_Text_20E3A7: @ 820E3A7
	.string "Unplugged and turned off…$"

MauvilleCity_Gym_Text_20E3C1: @ 820E3C1
	.string "WATTSON, our GYM LEADER, has been\n"
	.string "around for a long, long time.\p"
	.string "He was battling even before your\n"
	.string "daddy was born, that tough coot.$"

MauvilleCity_Gym_Text_20E443: @ 820E443
	.string "This GYM’s got puzzles!\n"
	.string "Isn’t it fun?$"

MauvilleCity_Gym_Text_20E469: @ 820E469
	.string "It’s no fun to lose…$"

MauvilleCity_Gym_Text_20E47E: @ 820E47E
	.string "WATTSON says he likes setting up\n"
	.string "little traps with switches.$"

MauvilleCity_Gym_Text_20E4BB: @ 820E4BB
	.string "With my charm and my POKéMON’s moves,\n"
	.string "you’ll be shocked!$"

MauvilleCity_Gym_Text_20E4F4: @ 820E4F4
	.string "I’m shocked by your power!$"

MauvilleCity_Gym_Text_20E50F: @ 820E50F
	.string "I’ve heard that MAUVILLE was founded\n"
	.string "by WATTSON.\p"
	.string "He was a TRAINER long before we\n"
	.string "became TRAINERS.\l"
	.string "He must know all sorts of things!$"

MauvilleCity_Gym_Text_20E593: @ 820E593
	.string "I love shiny things!$"

MauvilleCity_Gym_Text_20E5A8: @ 820E5A8
	.string "Oh…\n"
	.string "My eyes are frazzled…$"

MauvilleCity_Gym_Text_20E5C2: @ 820E5C2
	.string "MAUVILLE GYM’s WATTSON has a shiny\n"
	.string "forehead. It makes me happy!$"

MauvilleCity_Gym_Text_20E602: @ 820E602
	.string "I’ve given up on my plans to convert\n"
	.string "the city, I have.\p"
	.string "And so, I put my time into making\n"
	.string "door traps in my GYM.\p"
	.string "Oh? Now, what are you doing here?\p"
	.string "What’s that? You say you’ve gotten\n"
	.string "past all my rigged doors?\p"
	.string "Wahahahah!\n"
	.string "Now, that is amusing!\p"
	.string "Then, I, WATTSON, the LEADER of\n"
	.string "MAUVILLE GYM, shall electrify you!$"

MauvilleCity_Gym_Text_20E734: @ 820E734
	.string "Wahahahah!\n"
	.string "Fine, I lost!\p"
	.string "You ended up giving me a thrill!\n"
	.string "Take this BADGE!$"

MauvilleCity_Gym_Text_20E77F: @ 820E77F
	.string "{PLAYER} received the DYNAMO BADGE\n"
	.string "from WATTSON.$"

MauvilleCity_Gym_Text_20E7AA: @ 820E7AA
	.string "With the DYNAMO BADGE, POKéMON can\n"
	.string "use ROCK SMASH out of battle.\p"
	.string "And, it will make your POKéMON a little\n"
	.string "bit faster, too.\p"
	.string "Hmm…\n"
	.string "You should take this, too!$"

MauvilleCity_Gym_Text_20E844: @ 820E844
	.string "That TM34 there contains SHOCK WAVE.\p"
	.string "It’s a trustworthy move that never\n"
	.string "misses! You can count on it!\p"
	.string "… … … … … …$"

MauvilleCity_Gym_Text_20E8B5: @ 820E8B5
	.string "Registered GYM LEADER WATTSON\n"
	.string "in the POKéNAV.$"

MauvilleCity_Gym_Text_20E8E3: @ 820E8E3
	.string "I swell with optimism, seeing a promising\n"
	.string "young TRAINER like you!$"

MauvilleCity_Gym_Text_20E925: @ 820E925
	.string "Wahahahah!\n"
	.string "Go forth and endeavor, youngster!$"

MauvilleCity_Gym_Text_20E952: @ 820E952
	.string "MAUVILLE CITY POKéMON GYM$"

MauvilleCity_Gym_Text_20E96C: @ 820E96C
	.string "MAUVILLE CITY POKéMON GYM\p"
	.string "WATTSON’S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"

MauvilleCity_Gym_Text_20E9A7: @ 820E9A7
	.string "WATTSON: Ah-ha! Here at last!\n"
	.string "I know what you want.\l"
	.string "You want to battle my POKéMON!\p"
	.string "Wahahahaha!\p"
	.string "I’ll make sparks fly from you!\n"
	.string "Don’t say I didn’t warn you!$"

MauvilleCity_Gym_Text_20EA42: @ 820EA42
	.string "Oof…\n"
	.string "Our batteries ran dry…$"

MauvilleCity_Gym_Text_20EA5E: @ 820EA5E
	.string "WATTSON: We’ll have to recharge our\n"
	.string "batteries again.\p"
	.string "When we’re fully charged up, we’ll\n"
	.string "gladly accept your challenge.\p"
	.string "So, come back again sometime,\n"
	.string "won’t you?$"

MauvilleCity_Gym_Text_20EAFD: @ 820EAFD
	.string "WATTSON: Ah-ha! Here at last!\n"
	.string "I know what you want.\l"
	.string "You want to battle my POKéMON!\p"
	.string "Wahahahaha!\p"
	.string "Oops! Wait!\n"
	.string "You’ve only one POKéMON with you!\p"
	.string "Come see me with two or more\n"
	.string "POKéMON, all right?$"

