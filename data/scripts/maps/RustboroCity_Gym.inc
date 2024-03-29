RustboroCity_Gym_MapScripts:: @ 8212F30
	.byte 0

RustboroCity_Gym_EventScript_212F31:: @ 8212F31
	checkspeedchoice NERFROXANNE, SPD_YES
	goto_if TRUE, RustboroCity_Gym_NerfedRoxanne
	goto RustboroCity_Gym_NormalRoxanne

RustboroCity_Gym_NerfedRoxanne::
trainerbattle 1, TRAINER_ROXANNE_NERFED, 0, RustboroCity_Gym_Text_21362A, RustboroCity_Gym_Text_21370B, RustboroCity_Gym_EventScript_212F66
goto RustboroCity_Gym_AfterRoxanne

RustboroCity_Gym_NormalRoxanne::
trainerbattle 1, TRAINER_ROXANNE_1, 0, RustboroCity_Gym_Text_21362A, RustboroCity_Gym_Text_21370B, RustboroCity_Gym_EventScript_212F66

RustboroCity_Gym_AfterRoxanne::	
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, 1
	goto_eq RustboroCity_Gym_EventScript_212FC8
	checkflag FLAG_0x0A5
	goto_if 0, RustboroCity_Gym_EventScript_212FA4
	msgbox RustboroCity_Gym_Text_2139A7, 4
	release
	end

RustboroCity_Gym_EventScript_212F66:: @ 8212F66
	message RustboroCity_Gym_Text_2137EC
	waitmessage
	call RustboroCity_Gym_EventScript_27207E
	msgbox RustboroCity_Gym_Text_213816, 4
	setflag FLAG_0x4F0
	setflag FLAG_BADGE01_GET
	setvar VAR_0x405A, 1
	addvar VAR_0x4085, 1
	setvar VAR_0x8008, 1
	call RustboroCity_Gym_EventScript_271F43
	compare VAR_0x4085, 6
	call_if 1, RustboroCity_Gym_EventScript_271E84
	goto RustboroCity_Gym_EventScript_212FA4
	end

RustboroCity_Gym_EventScript_212FA4:: @ 8212FA4
	checkspeedchoice PLOTLESS, SPD_KEEP
	goto_if TRUE, RoxanneNoAqualess
	checkspeedchoice PLOTLESS, SPD_SEMI
	goto_if TRUE, RoxanneNoAqualess
	giveitem_std ITEM_LETTER
	@ give pokenav
	message RustboroCity_DevonCorp_3F_Text_212820
	waitfanfare
	setflag FLAG_SYS_POKENAV_GET
	setflag FLAG_0x0BC
	setflag FLAG_0x3E7
	setflag FLAG_HAS_MATCH_CALL
	setflag FLAG_0x130 @ this might fix match call...
	@ complete the pokenav tutorial
	setflag FLAG_0x34C
	setvar VAR_0x405A, 7
	@ move plot events up to the museum
	setflag 144
	setflag 732
	setvar 0x405a, 5
	setflag 2050
	setflag 188
	clearflag 142
	setflag 143
	setvar 0x4090, 1
	setflag 894
	clearflag 807
	clearflag 983
	clearflag 739	
	clearflag 881
	setvar 0x4096, 1
	clearflag 814
	setvar 0x408f, 1
RoxanneNoAqualess::

	giveitem_std ITEM_TM39
	compare VAR_RESULT, 0
	goto_eq RustboroCity_Gym_EventScript_272054
	setflag FLAG_0x0A5
	msgbox RustboroCity_Gym_Text_2138B1, 4
	release
	end

RustboroCity_Gym_EventScript_212FC8:: @ 8212FC8
	trainerbattle 7, TRAINER_ROXANNE_1, 0, RustboroCity_Gym_Text_213C2F, RustboroCity_Gym_Text_213CF9, RustboroCity_Gym_Text_213D93
	msgbox RustboroCity_Gym_Text_213D12, 6
	end

RustboroCity_Gym_EventScript_212FE3:: @ 8212FE3
	trainerbattle 0, TRAINER_JOSH, 0, RustboroCity_Gym_Text_2133E9, RustboroCity_Gym_Text_21342D
	msgbox RustboroCity_Gym_Text_213447, 6
	end

RustboroCity_Gym_EventScript_212FFA:: @ 8212FFA
	trainerbattle 0, TRAINER_TOMMY, 0, RustboroCity_Gym_Text_213486, RustboroCity_Gym_Text_2134C6
	msgbox RustboroCity_Gym_Text_2134E6, 6
	end

RustboroCity_Gym_EventScript_213011:: @ 8213011
	trainerbattle 0, TRAINER_MARC, 0, RustboroCity_Gym_Text_213533, RustboroCity_Gym_Text_213589
	msgbox RustboroCity_Gym_Text_2135C0, 6
	end

RustboroCity_Gym_EventScript_213028:: @ 8213028
	lock
	faceplayer
	checkflag FLAG_0x4F0
	goto_eq RustboroCity_Gym_EventScript_21303D
	msgbox RustboroCity_Gym_Text_21309D, 4
	release
	end

RustboroCity_Gym_EventScript_21303D:: @ 821303D
	msgbox RustboroCity_Gym_Text_2132E2, 4
	release
	end

RustboroCity_Gym_EventScript_213047:: @ 8213047
	lockall
	checkflag FLAG_BADGE01_GET
	goto_eq RustboroCity_Gym_EventScript_213067
	goto RustboroCity_Gym_EventScript_213071
	end

RustboroCity_Gym_EventScript_213057:: @ 8213057
	lockall
	checkflag FLAG_BADGE01_GET
	goto_eq RustboroCity_Gym_EventScript_213067
	goto RustboroCity_Gym_EventScript_213071
	end

RustboroCity_Gym_EventScript_213067:: @ 8213067
	msgbox RustboroCity_Gym_Text_213A3B, 4
	releaseall
	end

RustboroCity_Gym_EventScript_213071:: @ 8213071
	msgbox RustboroCity_Gym_Text_213A21, 4
	releaseall
	end

RustboroCity_Gym_EventScript_21307B:: @ 821307B
	lockall
	pokenavcall RustboroCity_Gym_Text_213A76
	waitmessage
	delay 30
	playfanfare MUS_ME_TORE_EYE
	msgbox RustboroCity_Gym_Text_213C01, 4
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_0x1D3
	clearflag FLAG_0x080
	releaseall
	end

RustboroCity_Gym_Text_21309D: @ 821309D
	.string "Yo, how’s it going?\p"
	.string "Listen, my friend!\n"
	.string "Would you like to become the CHAMPION?\p"
	.string "I’m no TRAINER, not me, but I can\n"
	.string "sure give you winning advice.\p"
	.string "That’s settled, then! We’ll aim for the\n"
	.string "POKéMON CHAMPIONSHIP together!\p"
	.string "It’s your job as a TRAINER to collect\n"
	.string "GYM BADGES, am I right?\p"
	.string "But GYM LEADERS aren’t pushovers!\p"
	.string "And that’s where I come in!\n"
	.string "I’m here to provide expert advice!\p"
	.string "ROXANNE, the GYM LEADER, is a user\n"
	.string "of ROCK-type POKéMON.\p"
	.string "The ROCK type is very durable, but\n"
	.string "it can’t stand WATER-type and\l"
	.string "GRASS-type moves.\p"
	.string "Come see me afterwards, if you beat\n"
	.string "the GYM LEADER.\p"
	.string "Well, go for it!$"

RustboroCity_Gym_Text_2132E2: @ 82132E2
	.string "Whoa! What a breathtaking victory!\n"
	.string "My cheering must’ve worked!\p"
	.string "Great!\n"
	.string "Check your TRAINER CARD.\p"
	.string "The STONE BADGE you got should be\n"
	.string "properly recorded on it.\p"
	.string "In other words…\p"
	.string "You’ve climbed the first step on\n"
	.string "the stairs to the CHAMPIONSHIP!\p"
	.string "That’s got to feel awesome!$"

RustboroCity_Gym_Text_2133E9: @ 82133E9
	.string "Don’t take us GYM TRAINERS lightly!\n"
	.string "I’ll show you why we’re better!$"

RustboroCity_Gym_Text_21342D: @ 821342D
	.string "You were too good for me…$"

RustboroCity_Gym_Text_213447: @ 8213447
	.string "You haven’t seen anything of the ROCK\n"
	.string "type’s terrifying power!$"

RustboroCity_Gym_Text_213486: @ 8213486
	.string "If you can’t beat me, you won’t stand\n"
	.string "a chance against ROXANNE!$"

RustboroCity_Gym_Text_2134C6: @ 82134C6
	.string "Wow! You’ve got some potential!$"

RustboroCity_Gym_Text_2134E6: @ 82134E6
	.string "ROXANNE is stronger than me by\n"
	.string "several times.\p"
	.string "You’d better be on your guard!$"

RustboroCity_Gym_Text_213533: @ 8213533
	.string "We might be in the middle of town,\n"
	.string "but so what?\p"
	.string "My ROCK POKéMON need room to\n"
	.string "rampage!$"

RustboroCity_Gym_Text_213589: @ 8213589
	.string "Oh, man oh man!\n"
	.string "Our challenger is one feisty customer!$"

RustboroCity_Gym_Text_2135C0: @ 82135C0
	.string "I have to hand it to our LEADER.\p"
	.string "It took smarts and sense for her to\n"
	.string "pick the ROCK type at her young age.$"

RustboroCity_Gym_Text_21362A: @ 821362A
	.string "Hello, I am ROXANNE, the RUSTBORO\n"
	.string "POKéMON GYM LEADER.\p"
	.string "I became a GYM LEADER so that I might\n"
	.string "apply what I learned at the POKéMON\l"
	.string "TRAINER’S SCHOOL in battle.\p"
	.string "Would you kindly demonstrate how you\n"
	.string "battle, and with which POKéMON?$"

RustboroCity_Gym_Text_21370B: @ 821370B
	.string "So…\n"
	.string "I lost…\p"
	.string "It seems that I still have much more\n"
	.string "to learn…\p"
	.string "I understand.\p"
	.string "The POKéMON LEAGUE’s rules state\n"
	.string "that TRAINERS are to be given this\l"
	.string "if they defeat a GYM LEADER.\p"
	.string "Please accept the official POKéMON\n"
	.string "LEAGUE STONE BADGE.$"

RustboroCity_Gym_Text_2137EC: @ 82137EC
	.string "{PLAYER} received the STONE BADGE\n"
	.string "from ROXANNE.$"

RustboroCity_Gym_Text_213816: @ 8213816
	.string "The STONE BADGE heightens the ATTACK\n"
	.string "power of your POKéMON.\p"
	.string "It also enables them to use the HM move\n"
	.string "CUT outside of battle.\p"
	.string "Please take this with you, too.$"

RustboroCity_Gym_Text_2138B1: @ 82138B1
	.string "That TECHNICAL MACHINE, TM39,\n"
	.string "contains ROCK TOMB.\p"
	.string "It not only inflicts damage by dropping\n"
	.string "rocks, it also lowers SPEED.\p"
	.string "If you use a TM, it instantly teaches\n"
	.string "the move to a POKéMON.\p"
	.string "Remember, a TM can be used only once,\n"
	.string "so think before you use it.$"

RustboroCity_Gym_Text_2139A7: @ 82139A7
	.string "Since you are so strong, you should\n"
	.string "challenge other GYM LEADERS.\p"
	.string "By battling many TRAINERS, you should\n"
	.string "learn many things.$"

RustboroCity_Gym_Text_213A21: @ 8213A21
	.string "RUSTBORO CITY POKéMON GYM$"

RustboroCity_Gym_Text_213A3B: @ 8213A3B
	.string "RUSTBORO CITY POKéMON GYM\p"
	.string "ROXANNE’S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"


RustboroCity_Gym_Text_213A76: @ 8213A76
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "ROXANNE: Oh, hello, {PLAYER}?\n"
	.string "This is ROXANNE of RUSTBORO CITY.\p"
	.string "I heard from BRAWLY that you’re\n"
	.string "moving up through the ranks of\l"
	.string "TRAINERS at an incredible clip.\p"
	.string "Well, I’d rather not think that\n"
	.string "I can’t beat you.\p"
	.string "I promise, I will shape up my GYM\n"
	.string "so that you may challenge us again.\p"
	.string "I hope you’ll be looking forward to\n"
	.string "that occasion as much as me!\p"
	.string "… … … … … …\n"
	.string "… … … … … Click!$"

RustboroCity_Gym_Text_213C01: @ 8213C01
	.string "Registered GYM LEADER ROXANNE\n"
	.string "in the POKéNAV.$"

RustboroCity_Gym_Text_213C2F: @ 8213C2F
	.string "ROXANNE: I’m so glad to see you again.\n"
	.string "I’m ROXANNE, the GYM LEADER here.\p"
	.string "I’m sure we’ve both experienced many\n"
	.string "battles since we last met.\p"
	.string "I would like to see how much better\n"
	.string "we’ve become. Let us battle!$"

RustboroCity_Gym_Text_213CF9: @ 8213CF9
	.string "Grr…\n"
	.string "Again, I have lost…$"

RustboroCity_Gym_Text_213D12: @ 8213D12
	.string "ROXANNE: I still have much to learn\n"
	.string "when it comes to battling POKéMON.\p"
	.string "That awareness makes me love battling\n"
	.string "all that much more!$"

RustboroCity_Gym_Text_213D93: @ 8213D93
	.string "ROXANNE: I’m so glad to see you again.\n"
	.string "I’m ROXANNE, the GYM LEADER here.\p"
	.string "I’m sure we’ve both experienced many\n"
	.string "battles since we last met.\p"
	.string "I would like to see how much better\n"
	.string "we’ve become…\p"
	.string "Oh, no…\n"
	.string "You only have one POKéMON with you?\p"
	.string "Please return with at least one more\n"
	.string "POKéMON.$"
