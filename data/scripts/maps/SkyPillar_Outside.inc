SkyPillar_Outside_MapScripts:: @ 82392A8
	map_script 3, SkyPillar_Outside_MapScript1_2392B8
	map_script 1, SkyPillar_Outside_MapScript1_2392DD
	map_script 2, SkyPillar_Outside_MapScript2_2392FA
	.byte 0

SkyPillar_Outside_MapScript1_2392B8: @ 82392B8
	compare VAR_0x405E, 3
	call_if 1, SkyPillar_Outside_EventScript_2392CF
	compare VAR_0x405E, 4
	call_if 4, SkyPillar_Outside_EventScript_2392D3
	end

SkyPillar_Outside_EventScript_2392CF:: @ 82392CF
	setflag FLAG_SPECIAL_FLAG_0x4000
	return

SkyPillar_Outside_EventScript_2392D3:: @ 82392D3
	checkflag FLAG_SYS_WEATHER_CTRL
	call_if 1, SkyPillar_Outside_EventScript_27207A
	return

SkyPillar_Outside_MapScript1_2392DD: @ 82392DD
	checkflag FLAG_0x137
	call_if 1, SkyPillar_Outside_EventScript_2392E7
	end

SkyPillar_Outside_EventScript_2392E7:: @ 82392E7
	setmetatile 14, 4, 682, 0
	setmetatile 14, 5, 690, 0
	return

SkyPillar_Outside_MapScript2_2392FA: @ 82392FA
	map_script_2 VAR_0x405E, 3, SkyPillar_Outside_EventScript_239304
	.2byte 0

SkyPillar_Outside_EventScript_239304:: @ 8239304
	checkspeedchoice PLOTLESS, SPD_KEEP
	goto_if FALSE, AfterSkyPillar1
	lockall
	applymovement 1, SkyPillar_Outside_Movement_2393D3
	waitmovement 0
	applymovement 255, SkyPillar_Outside_Movement_2725A4
	waitmovement 0
	msgbox SkyPillar_Outside_Text_239416, 4
	closemessage
	delay 30
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 3
	special sub_8139560
	waitstate
	delay 40
	msgbox SkyPillar_Outside_Text_2394BC, 4
	closemessage
	applymovement 255, SkyPillar_Outside_Movement_2393EB
	applymovement 1, SkyPillar_Outside_Movement_2393DE
	waitmovement 0
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 3
	setvar VAR_0x8006, 20
	setvar VAR_0x8007, 5
	special sub_8139560
	waitstate
	delay 20
	applymovement 1, SkyPillar_Outside_Movement_2725A4
	waitmovement 0
	delay 10
	applymovement 1, SkyPillar_Outside_Movement_2725A8
	waitmovement 0
	delay 20
	applymovement 1, SkyPillar_Outside_Movement_2725AA
	waitmovement 0
	delay 30
	msgbox SkyPillar_Outside_Text_23950C, 4
	closemessage
	setflag FLAG_SYS_WEATHER_CTRL
	setweather 15
	doweather
	special WaitWeather
	waitstate
	delay 30
	msgbox SkyPillar_Outside_Text_23953A, 4
	closemessage
	playse SE_KAIDAN
	fadescreenswapbuffers 1
	clearflag FLAG_SPECIAL_FLAG_0x4000
	setvar VAR_0x405E, 4
	removeobject 1
	clearflag FLAG_0x330
	fadescreenswapbuffers 0
	releaseall
	end
	
AfterSkyPillar1::
	end

SkyPillar_Outside_Movement_2393D3: @ 82393D3
	step_down
	step_down
	step_down
	step_down
	step_down
	step_down
	step_down
	step_right
	step_right
	step_right
	step_end

SkyPillar_Outside_Movement_2393DE: @ 82393DE
	step_left
	step_left
	step_left
	step_up
	step_up
	step_up
	step_up
	step_right
	step_up
	step_up
	step_up
	step_up
	step_end

SkyPillar_Outside_Movement_2393EB: @ 82393EB
	step_left
	step_left
	step_left
	step_left
	step_up
	step_up
	step_up
	step_up
	step_right
	step_up
	step_up
	step_up
	step_end

SkyPillar_Outside_EventScript_2393F8:: @ 82393F8
	end

SkyPillar_Outside_EventScript_2393F9:: @ 82393F9
	msgbox SkyPillar_Outside_Text_239402, 3
	end

SkyPillar_Outside_Text_239402: @ 8239402
	.string "The door is closed.$"

SkyPillar_Outside_Text_239416: @ 8239416
	.string "WALLACE: Oh, my, I’m terribly sorry!\p"
	.string "In my haste, I didn’t notice that\n"
	.string "I’d left you behind!\p"
	.string "I’ve opened the locked door of\n"
	.string "the SKY PILLAR.\p"
	.string "{PLAYER}{KUN}, let’s be on our way!$"

SkyPillar_Outside_Text_2394BC: @ 82394BC
	.string "WALLACE: It’s an earthquake!\p"
	.string "There’s not a moment to waste!\n"
	.string "We’ve got to hurry!$"

SkyPillar_Outside_Text_23950C: @ 823950C
	.string "WALLACE: Hmm…\n"
	.string "The situation is getting worse…$"

SkyPillar_Outside_Text_23953A: @ 823953A
	.string "WALLACE: This isn’t good…\p"
	.string "The weather distortion is spreading\n"
	.string "even here…\p"
	.string "{PLAYER}{KUN}.\p"
	.string "RAYQUAZA should be farther up\n"
	.string "from here.\p"
	.string "I’m worried about SOOTOPOLIS.\n"
	.string "I’ve got to go back.\p"
	.string "Everything is in your hands now.\n"
	.string "Don’t fail us!$"
