MtChimney_MapScripts:: @ 822EDC1
	map_script 5, MtChimney_MapScript1_22EDD2
	map_script 3, MtChimney_MapScript1_22EDCC
	.byte 0

MtChimney_MapScript1_22EDCC: @ 822EDCC
	setvar VAR_0x40BD, 1
	end

MtChimney_MapScript1_22EDD2: @ 822EDD2
	setstepcallback 1
	end

MtChimney_EventScript_22EDD5:: @ 822EDD5
	lock
	faceplayer
	checkflag FLAG_0x0DB
	call_if 0, MtChimney_EventScript_22EDF9
	checkflag FLAG_0x0DB
	call_if 1, MtChimney_EventScript_22EE02
	closemessage
	applymovement 1, MtChimney_Movement_2725A2
	waitmovement 0
	setflag FLAG_0x0DB
	release
	end

MtChimney_EventScript_22EDF9:: @ 822EDF9
	msgbox MtChimney_Text_22FAD2, 4
	return

MtChimney_EventScript_22EE02:: @ 822EE02
	msgbox MtChimney_Text_22FBC7, 4
	return

MtChimney_EventScript_22EE0B:: @ 822EE0B
	lockall
	playbgm MUS_MGM0, 0
	msgbox MtChimney_Text_22F26A, 4
	applymovement 2, MtChimney_Movement_27259E
	waitmovement 0
	playse SE_PIN
	applymovement 2, MtChimney_Movement_272598
	waitmovement 0
	applymovement 2, MtChimney_Movement_27259A
	waitmovement 0
	msgbox MtChimney_Text_22F32E, 4
	trainerbattle 3, TRAINER_MAXIE_2, 0, MtChimney_Text_22F5CF
	msgbox MtChimney_Text_22F5F7, 4
	closemessage
	delay 30
	fadescreen 1
	removeobject 2
	removeobject 29
	removeobject 3
	removeobject 22
	setflag FLAG_0x39F
	fadescreen 0
	setobjectxyperm 1, 10, 12
	addobject 1
	compare VAR_FACING, 4
	call_if 1, MtChimney_EventScript_22EEC7
	compare VAR_FACING, 2
	call_if 1, MtChimney_EventScript_22EED2
	applymovement 255, MtChimney_Movement_2725A4
	waitmovement 0
	msgbox MtChimney_Text_22FC3D, 4
	closemessage
	compare VAR_FACING, 4
	call_if 1, MtChimney_EventScript_22EEDD
	compare VAR_FACING, 2
	call_if 1, MtChimney_EventScript_22EEE8
	removeobject 1
	setflag FLAG_0x39E
	setflag FLAG_0x08B
	clearflag FLAG_0x3A0
	setflag FLAG_0x3AE
	clearflag FLAG_0x3E2
	@ we only need to do this for Semi, since the player can do gym 5 on Early Surf, and thus use the Weather Institute early.
	checkspeedchoice PLOTLESS, SPD_SEMI
	goto_if FALSE, AfterChimney
	setvar VAR_0x40B3, 2
	setflag 890
	clearflag 892
	setflag 893
AfterChimney::
	releaseall
	end

MtChimney_EventScript_22EEC7:: @ 822EEC7
	applymovement 1, MtChimney_Movement_22EF83
	waitmovement 0
	return

MtChimney_EventScript_22EED2:: @ 822EED2
	applymovement 1, MtChimney_Movement_22EF94
	waitmovement 0
	return

MtChimney_EventScript_22EEDD:: @ 822EEDD
	applymovement 1, MtChimney_Movement_22EF8B
	waitmovement 0
	return

MtChimney_EventScript_22EEE8:: @ 822EEE8
	applymovement 1, MtChimney_Movement_22EF9C
	waitmovement 0
	return

MtChimney_EventScript_22EEF3:: @ 822EEF3
	lock
	faceplayer
	showmoneybox 0, 0, 0
	msgbox MtChimney_Text_22FE04, 5
	compare VAR_RESULT, 0
	goto_eq MtChimney_EventScript_22EF69
	checkmoney 0xc8, 0
	compare VAR_RESULT, 0
	goto_eq MtChimney_EventScript_22EF76
	msgbox MtChimney_Text_22FE4D, 4
	checkitemspace ITEM_LAVA_COOKIE, 1
	compare VAR_RESULT, 1
	call_if 1, MtChimney_EventScript_22EF5E
	giveitem_std ITEM_LAVA_COOKIE
	compare VAR_RESULT, 0
	goto_eq MtChimney_EventScript_22EF51
	hidemoneybox
	nop
	nop
	release
	end

MtChimney_EventScript_22EF51:: @ 822EF51
	msgbox gUnknown_08272AD0, 4
	hidemoneybox
	nop
	nop
	release
	end

MtChimney_EventScript_22EF5E:: @ 822EF5E
	takemoney 0xc8, 0
	updatemoneybox 0, 0
	nop
	return

MtChimney_EventScript_22EF69:: @ 822EF69
	msgbox MtChimney_Text_22FE9B, 4
	hidemoneybox
	nop
	nop
	release
	end

MtChimney_EventScript_22EF76:: @ 822EF76
	msgbox MtChimney_Text_22FE5E, 4
	hidemoneybox
	nop
	nop
	release
	end

MtChimney_Movement_22EF83: @ 822EF83
	step_up
	step_up
	step_up
	step_up
	step_up
	step_up
	step_right
	step_end

MtChimney_Movement_22EF8B: @ 822EF8B
	step_left
	step_down
	step_down
	step_down
	step_down
	step_down
	step_down
	step_down
	step_end

MtChimney_Movement_22EF94: @ 822EF94
	step_up
	step_up
	step_up
	step_up
	step_up
	step_right
	step_right
	step_end

MtChimney_Movement_22EF9C: @ 822EF9C
	step_left
	step_left
	step_down
	step_down
	step_down
	step_down
	step_down
	step_down
	step_down
	step_end

MtChimney_Movement_22EFA6: @ 822EFA6
	step_down
	step_down
	step_down
	step_down
	step_down
	step_left
	step_left
	step_down
	step_down
	step_down
	step_down
	step_left
	step_left
	step_left
	step_left
	step_left
	step_down
	step_end

MtChimney_Movement_22EFB8: @ 822EFB8
	step_down
	step_down
	step_down
	step_down
	step_left
	step_left
	step_left
	step_down
	step_end

MtChimney_Movement_22EFC1: @ 822EFC1
	step_right
	step_down
	step_down
	step_down
	step_down
	step_left
	step_left
	step_left
	step_left
	step_left
	step_down
	step_down
	step_down
	step_down
	step_end

MtChimney_Movement_22EFD0: @ 822EFD0
	step_15
	step_15
	step_15
	step_15
	step_15
	step_15
	step_15
	step_15
	step_15
	step_left
	step_left
	step_down
	step_down
	step_down
	step_left
	step_left
	step_down
	step_down
	step_left
	step_left
	step_left
	step_left
	step_left
	step_down
	step_end

MtChimney_Movement_22EFE9: @ 822EFE9
	step_14
	step_14
	step_14
	step_down
	step_down
	step_down
	step_left
	step_left
	step_left
	step_down
	step_end

MtChimney_Movement_22EFF4: @ 822EFF4
	step_14
	step_left
	step_down
	step_down
	step_down
	step_down
	step_left
	step_left
	step_left
	step_left
	step_left
	step_down
	step_down
	step_down
	step_down
	step_end

MtChimney_Movement_22F004: @ 822F004
	step_14
	step_left
	step_left
	step_down
	step_down
	step_down
	step_left
	step_left
	step_down
	step_down
	step_left
	step_left
	step_left
	step_left
	step_left
	step_down
	step_end

MtChimney_Movement_22F015: @ 822F015
	step_14
	step_down
	step_left
	step_left
	step_left
	step_left
	step_25
	step_end

MtChimney_Movement_22F01D: @ 822F01D
	step_down
	step_down
	step_down
	step_down
	step_left
	step_left
	step_left
	step_left
	step_left
	step_down
	step_down
	step_down
	step_down
	step_end

MtChimney_Movement_22F02B: @ 822F02B
	step_down
	step_end

MtChimney_Movement_22F02D: @ 822F02D
	step_down
	step_down
	step_down
	step_down
	step_down
	step_down
	step_down
	step_end

MtChimney_Movement_22F035: @ 822F035
	step_14
	step_14
	step_27
	step_14
	step_down
	step_down
	step_down
	step_down
	step_down
	step_end

MtChimney_Movement_22F03F: @ 822F03F
	step_14
	step_14
	step_14
	step_14
	step_14
	step_14
	step_27
	step_14
	step_down
	step_down
	step_end

MtChimney_Movement_22F04A: @ 822F04A
	step_40
	step_17
	step_41
	step_03
	step_end

MtChimney_Movement_22F04F: @ 822F04F
	step_left
	step_28
	step_14
	step_end

MtChimney_EventScript_22F053:: @ 822F053
	msgbox MtChimney_Text_22FD1F, 3
	end

MtChimney_EventScript_22F05C:: @ 822F05C
	msgbox MtChimney_Text_22FD5B, 3
	end

MtChimney_EventScript_22F065:: @ 822F065
	msgbox MtChimney_Text_22FDA1, 3
	end

MtChimney_EventScript_22F06E:: @ 822F06E
	trainerbattle 0, TRAINER_TABITHA_2, 0, MtChimney_Text_22F6AA, MtChimney_Text_22F72C
	msgbox MtChimney_Text_22F76D, 6
	end

MtChimney_EventScript_22F085:: @ 822F085
	trainerbattle 0, TRAINER_GRUNT_31, 0, MtChimney_Text_22F7A2, MtChimney_Text_22F83A
	msgbox MtChimney_Text_22F859, 6
	end

MtChimney_EventScript_22F09C:: @ 822F09C
	msgbox MtChimney_Text_22F978, 3
	end

MtChimney_EventScript_22F0A5:: @ 822F0A5
	msgbox MtChimney_Text_22F9B2, 3
	end

MtChimney_EventScript_22F0AE:: @ 822F0AE
	msgbox MtChimney_Text_22F9D1, 3
	end

MtChimney_EventScript_22F0B7:: @ 822F0B7
	msgbox MtChimney_Text_22FA2F, 3
	end

MtChimney_EventScript_22F0C0:: @ 822F0C0
	msgbox MtChimney_Text_22FA8B, 3
	end

MtChimney_EventScript_22F0C9:: @ 822F0C9
	msgbox MtChimney_Text_22FAA5, 3
	end

MtChimney_EventScript_22F0D2:: @ 822F0D2
	msgbox MtChimney_Text_22FACB, 3
	end

MtChimney_EventScript_22F0DB:: @ 822F0DB
	msgbox MtChimney_Text_22FDFC, 3
	end

MtChimney_EventScript_22F0E4:: @ 822F0E4
	lockall
	checkflag FLAG_0x08B
	goto_if 0, MtChimney_EventScript_22F137
	checkflag FLAG_0x073
	goto_eq MtChimney_EventScript_22F12D
	msgbox MtChimney_Text_22FF12, 5
	compare VAR_RESULT, 0
	goto_eq MtChimney_EventScript_22F123
	msgbox MtChimney_Text_22FF66, 4
	giveitem_std ITEM_METEORITE
	setflag FLAG_0x073
	releaseall
	end

MtChimney_EventScript_22F123:: @ 822F123
	msgbox MtChimney_Text_22FF9C, 4
	releaseall
	end

MtChimney_EventScript_22F12D:: @ 822F12D
	msgbox MtChimney_Text_22FFC0, 4
	releaseall
	end

MtChimney_EventScript_22F137:: @ 822F137
	msgbox MtChimney_Text_22FEAA, 4
	releaseall
	end

MtChimney_EventScript_22F141:: @ 822F141
	msgbox MtChimney_Text_22FFFA, 3
	end

MtChimney_EventScript_22F14A:: @ 822F14A
	trainerbattle 2, TRAINER_SHELBY_1, 0, MtChimney_Text_23001D, MtChimney_Text_230076, MtChimney_EventScript_22F176
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, 1
	goto_eq MtChimney_EventScript_22F195
	msgbox MtChimney_Text_2300A2, 4
	release
	end

MtChimney_EventScript_22F176:: @ 822F176
	special sub_80B4808
	waitmovement 0
	msgbox MtChimney_Text_2300E3, 4
	setvar VAR_0x8004, 313
	special sub_81D1C20
	setorcopyvar VAR_0x8000, 313
	callstd 8
	release
	end

MtChimney_EventScript_22F195:: @ 822F195
	trainerbattle 5, TRAINER_SHELBY_1, 0, MtChimney_Text_230153, MtChimney_Text_2301BB
	msgbox MtChimney_Text_2301E7, 6
	end

MtChimney_EventScript_22F1AC:: @ 822F1AC
	trainerbattle 0, TRAINER_MELISSA, 0, MtChimney_Text_23022A, MtChimney_Text_23026D
	msgbox MtChimney_Text_230292, 6
	end

MtChimney_EventScript_22F1C3:: @ 822F1C3
	trainerbattle 0, TRAINER_SHEILA, 0, MtChimney_Text_2302BD, MtChimney_Text_230304
	msgbox MtChimney_Text_23033A, 6
	end

MtChimney_EventScript_22F1DA:: @ 822F1DA
	trainerbattle 0, TRAINER_SHIRLEY, 0, MtChimney_Text_2303DF, MtChimney_Text_230436
	msgbox MtChimney_Text_230463, 6
	end

MtChimney_EventScript_22F1F1:: @ 822F1F1
	trainerbattle 0, TRAINER_GRUNT_24, 0, MtChimney_Text_22F8B6, MtChimney_Text_22F921
	msgbox MtChimney_Text_22F93A, 6
	end

MtChimney_EventScript_22F208:: @ 822F208
	trainerbattle 2, TRAINER_SAWYER_1, 0, MtChimney_Text_2304B3, MtChimney_Text_2304F7, MtChimney_EventScript_22F234
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, 1
	goto_eq MtChimney_EventScript_22F253
	msgbox MtChimney_Text_230519, 4
	release
	end

MtChimney_EventScript_22F234:: @ 822F234
	special sub_80B4808
	waitmovement 0
	msgbox MtChimney_Text_230557, 4
	setvar VAR_0x8004, 1
	special sub_81D1C20
	setorcopyvar VAR_0x8000, 1
	callstd 8
	release
	end

MtChimney_EventScript_22F253:: @ 822F253
	trainerbattle 5, TRAINER_SAWYER_1, 0, MtChimney_Text_23059C, MtChimney_Text_2305E3
	msgbox MtChimney_Text_230614, 6
	end

MtChimney_Text_22F26A: @ 822F26A
	.string "The power contained in the METEORITE…\p"
	.string "By amplifying its power with this\n"
	.string "machine, MT. CHIMNEY’s volcanic\l"
	.string "activity will instantly intensify…\p"
	.string "Its energy will grow deep inside\n"
	.string "the crater and…\l"
	.string "Fufufu…$"

MtChimney_Text_22F32E: @ 822F32E
	.string "MAXIE: Hm?\n"
	.string "Who are you?\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "I’d heard ARCHIE bemoaning a child\n"
	.string "who’s been meddling in TEAM AQUA’s\l"
	.string "affairs.\p"
	.string "It must be you he meant.\p"
	.string "Humph! So you’re thinking of\n"
	.string "interfering with us, TEAM MAGMA?\p"
	.string "Now you listen.\n"
	.string "Long ago, living things used the\l"
	.string "land to live and grow.\p"
	.string "That is why land is all important!\n"
	.string "It is the cradle of all!\p"
	.string "That is why TEAM MAGMA is dedicated\n"
	.string "to the expansion of the land mass.\p"
	.string "It is for further advancement of\n"
	.string "humankind and POKéMON!\p"
	.string "And for that, we need the power of\n"
	.string "what sleeps within this mountain…\p"
	.string "Oh! There was no need for you to\n"
	.string "learn that much.\p"
	.string "But, no matter!\n"
	.string "I’ll teach you the consequences of\l"
	.string "meddling in our grand design!$"

MtChimney_Text_22F5CF: @ 822F5CF
	.string "What?!\p"
	.string "I, MAXIE, was caught off guard?!$"

MtChimney_Text_22F5F7: @ 822F5F7
	.string "MAXIE: But, enough.\n"
	.string "I will back off this time.\p"
	.string "But don’t think that this is the last\n"
	.string "you’ve seen of TEAM MAGMA.\p"
	.string "Fufufu…\p"
	.string "Even without the METEORITE, if we\n"
	.string "obtain that ORB… Fufufu…$"

MtChimney_Text_22F6AA: @ 822F6AA
	.string "Hehehe!\p"
	.string "So you’ve come all the way here!\p"
	.string "But you’re too late!\n"
	.string "I’ve already delivered the METEORITE\l"
	.string "from METEOR FALLS to the BOSS!$"

MtChimney_Text_22F72C: @ 822F72C
	.string "Hehehe…\p"
	.string "Even though I’ve lost, if our leader\n"
	.string "awakens that thing…$"

MtChimney_Text_22F76D: @ 822F76D
	.string "BOSS, hurry!\n"
	.string "Give it the METEORITE’s energy!\p"
	.string "Hehehe…$"

MtChimney_Text_22F7A2: @ 822F7A2
	.string "We of TEAM MAGMA are working hard for\n"
	.string "everyone’s sake.\p"
	.string "Like, if that thing’s power made more\n"
	.string "land, there’d be more places to live.\p"
	.string "Everyone’d be happy!$"

MtChimney_Text_22F83A: @ 822F83A
	.string "Hunh?\n"
	.string "What do you mean I lost?$"

MtChimney_Text_22F859: @ 822F859
	.string "Our BOSS says, “It will make everyone\n"
	.string "happy.”\p"
	.string "But why does everyone keep getting\n"
	.string "in our way?$"

MtChimney_Text_22F8B6: @ 822F8B6
	.string "If there were more land, I’d be able\n"
	.string "to get a big house of my own!\p"
	.string "I’m going to build it on hardened lava!$"

MtChimney_Text_22F921: @ 822F921
	.string "My dream of a big house…$"

MtChimney_Text_22F93A: @ 822F93A
	.string "A kid like you, you ought to be\n"
	.string "splashing about in the waves!$"

MtChimney_Text_22F978: @ 822F978
	.string "That annoying TEAM AQUA…\n"
	.string "They always mess with our plans!$"

MtChimney_Text_22F9B2: @ 822F9B2
	.string "METEORITES pack amazing power!$"

MtChimney_Text_22F9D1: @ 822F9D1
	.string "You’d better not mess with us!\p"
	.string "We’re trying to awaken that thing\n"
	.string "for the benefit of everyone!$"

MtChimney_Text_22FA2F: @ 822FA2F
	.string "We’re TEAM MAGMA!\p"
	.string "They’re TEAM AQUA!\p"
	.string "It totally annoys me that they’d\n"
	.string "use a name like ours!$"

MtChimney_Text_22FA8B: @ 822FA8B
	.string "Yeah!\n"
	.string "Douse them in fire!$"

MtChimney_Text_22FAA5: @ 822FAA5
	.string "We’re going to keep making more land!$"

MtChimney_Text_22FACB: @ 822FACB
	.string "Bufoh!$"

MtChimney_Text_22FAD2: @ 822FAD2
	.string "ARCHIE: Grr, {PLAYER}!\n"
	.string "I should’ve guessed you’d show up!\p"
	.string "See for yourself what the fanatics\n"
	.string "of TEAM MAGMA are up to!\p"
	.string "They’re trying to inject the stolen\n"
	.string "METEORITE’s power into the volcano!\p"
	.string "Doing something like that will cause\n"
	.string "the volcano’s eruption!$"

MtChimney_Text_22FBC7: @ 822FBC7
	.string "ARCHIE: Grrr…\p"
	.string "I want to stop that MAXIE,\n"
	.string "but I can’t!\p"
	.string "Not when I have my hands full battling\n"
	.string "three opponents at once!$"

MtChimney_Text_22FC3D: @ 822FC3D
	.string "ARCHIE: {PLAYER}!\n"
	.string "Thank you!\p"
	.string "With your help, we thwarted TEAM\n"
	.string "MAGMA’s destructive plan!\p"
	.string "But… You…\n"
	.string "Whose side are you on?\p"
	.string "Ah, it doesn’t matter.\p"
	.string "We will remain vigilant and keep up\n"
	.string "our pursuit of TEAM MAGMA.\p"
	.string "{PLAYER}, we shall meet again!$"

MtChimney_Text_22FD1F: @ 822FD1F
	.string "Darn… TEAM MAGMA outnumbers us!\n"
	.string "We can’t keep up with them!$"

MtChimney_Text_22FD5B: @ 822FD5B
	.string "If they expand the land, there’ll be\n"
	.string "less habitats for WATER POKéMON!$"

MtChimney_Text_22FDA1: @ 822FDA1
	.string "We’re TEAM AQUA!\p"
	.string "They’re TEAM MAGMA!\p"
	.string "It burns me up that they’d use such\n"
	.string "a confusing name!$"

MtChimney_Text_22FDFC: @ 822FDFC
	.string "Bushaa!$"

MtChimney_Text_22FE04: @ 822FE04
	.string "LAVA COOKIES are MT. CHIMNEY’s local\n"
	.string "specialty.\p"
	.string "Try one. It’s just ¥200.$"

MtChimney_Text_22FE4D: @ 822FE4D
	.string "Thank you, dear!$"

MtChimney_Text_22FE5E: @ 822FE5E
	.string "Oh, dear. You can’t buy a thing if\n"
	.string "you’ve not got the money.$"

MtChimney_Text_22FE9B: @ 822FE9B
	.string "Oh, fine then.$"

MtChimney_Text_22FEAA: @ 822FEAA
	.string "A METEORITE is fitted on a mysterious\n"
	.string "machine…\p"
	.string "The machine seems to be storing\n"
	.string "energy in the METEORITE.$"

MtChimney_Text_22FF12: @ 822FF12
	.string "A METEORITE is fitted on a mysterious\n"
	.string "machine…\p"
	.string "Do you want to remove the METEORITE?$"

MtChimney_Text_22FF66: @ 822FF66
	.string "{PLAYER} removed the METEORITE from\n"
	.string "the mysterious machine.$"

MtChimney_Text_22FF9C: @ 822FF9C
	.string "{PLAYER} left the METEORITE where\n"
	.string "it was.$"

MtChimney_Text_22FFC0: @ 822FFC0
	.string "This mysterious machine…\n"
	.string "It makes no response whatsoever.$"

MtChimney_Text_22FFFA: @ 822FFFA
	.string "{0x7A} JAGGED PATH\n"
	.string "LAVARIDGE TOWN AHEAD$"

MtChimney_Text_23001D: @ 823001D
	.string "I’ve been to the hot springs and\n"
	.string "refreshed my tired bones.\l"
	.string "Right now I’m feeling strong!$"

MtChimney_Text_230076: @ 8230076
	.string "Oh, my goodness.\n"
	.string "Now, aren’t you something!$"

MtChimney_Text_2300A2: @ 82300A2
	.string "Well, well, I’ve lost. I can’t call\n"
	.string "myself an EXPERT now, can I?$"

MtChimney_Text_2300E3: @ 82300E3
	.string "Thank you, child. It was fun, as if\n"
	.string "I were battling my own grandchild.\p"
	.string "Please, come see me again for\n"
	.string "a rematch.$"

MtChimney_Text_230153: @ 8230153
	.string "If you can mesh your heart with those\n"
	.string "of your POKéMON, why, you should be\l"
	.string "able to achieve great things.$"

MtChimney_Text_2301BB: @ 82301BB
	.string "Oh, my goodness.\n"
	.string "Now, aren’t you something!$"

MtChimney_Text_2301E7: @ 82301E7
	.string "Perhaps your heart has become one\n"
	.string "with the hearts of your POKéMON.$"

MtChimney_Text_23022A: @ 823022A
	.string "I’ve got the fire in me, baby.\n"
	.string "I can’t stand it! I have to battle!$"

MtChimney_Text_23026D: @ 823026D
	.string "Ooh, that was a scorching-hot match!$"

MtChimney_Text_230292: @ 8230292
	.string "The heat of MT. CHIMNEY warms\n"
	.string "me up, baby!$"

MtChimney_Text_2302BD: @ 82302BD
	.string "I’ve finally made it to MT. CHIMNEY.\n"
	.string "I want to make my POKéMON battle!$"

MtChimney_Text_230304: @ 8230304
	.string "The way you battle…\n"
	.string "It’s like a MT. CHIMNEY eruption!$"

MtChimney_Text_23033A: @ 823033A
	.string "Like I said, I’ve finally made it to\n"
	.string "MT. CHIMNEY. It would be a shame if\l"
	.string "I only do a little sightseeing…\p"
	.string "I want to get in some battles and buy\n"
	.string "COOKIES as souvenirs.$"

MtChimney_Text_2303DF: @ 82303DF
	.string "Since I bathed in the hot springs,\n"
	.string "I’ve been feeling great!\l"
	.string "I’m sure I’m going to win!$"

MtChimney_Text_230436: @ 8230436
	.string "Yowch!\n"
	.string "I’m getting a chill out of the water.$"

MtChimney_Text_230463: @ 8230463
	.string "I’ll have to take another dip in the\n"
	.string "hot springs. Want to join me?\p"
	.string "Just joking!$"

MtChimney_Text_2304B3: @ 82304B3
	.string "This is one fine mountain! Plenty of\n"
	.string "hot people around for company!$"

MtChimney_Text_2304F7: @ 82304F7
	.string "Oh, you’re a real firebrand, too!$"

MtChimney_Text_230519: @ 8230519
	.string "I think I need a dip in LAVARIDGE\n"
	.string "HOT SPRING with the locals!$"

MtChimney_Text_230557: @ 8230557
	.string "I like little fireballs like you.\n"
	.string "Let me register you in my POKéNAV.$"

MtChimney_Text_23059C: @ 823059C
	.string "I’m happily surrounded by hot people\n"
	.string "around these parts. I won’t lose!$"

MtChimney_Text_2305E3: @ 82305E3
	.string "Gosh, you’re still the same\n"
	.string "firebrand as before!$"

MtChimney_Text_230614: @ 8230614
	.string "Actually, it really is hot here.\n"
	.string "I’m overdressed for these parts.$"

