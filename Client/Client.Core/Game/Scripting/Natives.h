#pragma once

namespace PLAYER
{
	static scrAny GET_PLAYER_PED(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x43A66C31C68491C0, p0); } // 43A66C31C68491C0 6E31E993
	static scrAny GET_PLAYER_PED_SCRIPT_INDEX(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x50FAC3A3E030A6E1, p0); } // 50FAC3A3E030A6E1 6AC64990
	static void SET_PLAYER_MODEL(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x00A1CADD00108836, p0, p1); } // 00A1CADD00108836 774A4C54
	static void CHANGE_PLAYER_PED(scrAny p0, scrAny p1, BOOL p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x048189FAC643DEEE, p0, p1, p2, p3); } // 048189FAC643DEEE BE515485
	static void GET_PLAYER_RGB_COLOUR(scrAny p0, scrAny *p1, scrAny *p2, scrAny *p3) { NativeInvoke::Invoke<scrVoid>(0xE902EF951DCE178F, p0, p1, p2, p3); } // E902EF951DCE178F 6EF43BBB
	static scrAny GET_NUMBER_OF_PLAYERS() { return NativeInvoke::Invoke<scrAny>(0x407C7F91DDB46C16); } // 407C7F91DDB46C16 4C1B8867
	static scrAny GET_PLAYER_TEAM(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x37039302F4E0A008, p0); } // 37039302F4E0A008 9873E404
	static void SET_PLAYER_TEAM(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x0299FA38396A4940, p0, p1); } // 0299FA38396A4940 725ADCF2
	static scrAny GET_PLAYER_NAME(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x6D0DE6A7B5DA71F8, p0); } // 6D0DE6A7B5DA71F8 406B4B20
	static float GET_WANTED_LEVEL_RADIUS(scrAny p0) { return NativeInvoke::Invoke<float>(0x085DEB493BE80812, p0); } // 085DEB493BE80812 1CF7D7DA
	static scrVector3 GET_PLAYER_WANTED_CENTRE_POSITION(scrAny p0) { return NativeInvoke::Invoke<scrVector3>(0x0C92BA89F1AF26F8, p0); } // 0C92BA89F1AF26F8 821F2D2C
	static void SET_PLAYER_WANTED_CENTRE_POSITION(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x520E541A97A13354, p0, p1, p2, p3); } // 520E541A97A13354 F261633A
	static scrAny GET_WANTED_LEVEL_THRESHOLD(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xFDD179EAF45B556C, p0); } // FDD179EAF45B556C D9783F6B
	static void SET_PLAYER_WANTED_LEVEL(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x39FF19C64EF7DA5B, p0, p1, p2); } // 39FF19C64EF7DA5B B7A0914B
	static void SET_PLAYER_WANTED_LEVEL_NO_DROP(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x340E61DE7F471565, p0, p1, p2); } // 340E61DE7F471565 ED6F44F5
	static void SET_PLAYER_WANTED_LEVEL_NOW(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xE0A7D1E497FFCD6F, p0, p1); } // E0A7D1E497FFCD6F AF3AFD83
	static BOOL ARE_PLAYER_FLASHING_STARS_ABOUT_TO_DROP(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xAFAF86043E5874E9, p0); } // AFAF86043E5874E9 E13A71C7
	static BOOL ARE_PLAYER_STARS_GREYED_OUT(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x0A6EB355EE14A2DB, p0); } // 0A6EB355EE14A2DB 5E72AB72
	static void SET_DISPATCH_COPS_FOR_PLAYER(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xDB172424876553F4, p0, p1); } // DB172424876553F4 48A18913
	static BOOL IS_PLAYER_WANTED_LEVEL_GREATER(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x238DB2A2C23EE9EF, p0, p1); } // 238DB2A2C23EE9EF 589A2661
	static void CLEAR_PLAYER_WANTED_LEVEL(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xB302540597885499, p0); } // B302540597885499 54EA5BCC
	static BOOL IS_PLAYER_DEAD(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x424D4687FA1E5652, p0); } // 424D4687FA1E5652 140CA5A8
	static BOOL IS_PLAYER_PRESSING_HORN(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xFA1E2BF8B10598F9, p0); } // FA1E2BF8B10598F9 ED1D1662
	static void SET_PLAYER_CONTROL(scrAny p0, BOOL p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x8D32347D6D4C40A2, p0, p1, p2); } // 8D32347D6D4C40A2 D17AFCD8
	static scrAny GET_PLAYER_WANTED_LEVEL(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xE28E54788CE8F12D, p0); } // E28E54788CE8F12D BDCDD163
	static void SET_MAX_WANTED_LEVEL(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xAA5F02DB48D704B9, p0); } // AA5F02DB48D704B9 665A06F5
	static void SET_POLICE_RADAR_BLIPS(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x43286D561B72B8BF, p0); } // 43286D561B72B8BF 8E114B10
	static void SET_POLICE_IGNORE_PLAYER(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x32C62AA929C2DA6A, p0, p1); } // 32C62AA929C2DA6A E6DE71B7
	static BOOL IS_PLAYER_PLAYING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x5E9564D8246B909A, p0); } // 5E9564D8246B909A E15D777F
	static void SET_EVERYONE_IGNORE_PLAYER(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x8EEDA153AD141BA4, p0, p1); } // 8EEDA153AD141BA4 C915285E
	static void SET_ALL_RANDOM_PEDS_FLEE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x056E0FE8534C2949, p0, p1); } // 056E0FE8534C2949 49EAE968
	static void SET_ALL_RANDOM_PEDS_FLEE_THIS_FRAME(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x471D2FF42A94B4F2, p0); } // 471D2FF42A94B4F2 BF974891
	static void _0xDE45D1A1EF45EE61(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xDE45D1A1EF45EE61, p0, p1); } // DE45D1A1EF45EE61 274631FE
	static void _0xC3376F42B1FACCC6(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xC3376F42B1FACCC6, p0); } // C3376F42B1FACCC6 02DF7AF4
	static void SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x596976B02B6B5700, p0, p1); } // 596976B02B6B5700 A3D675ED
	static void SET_WANTED_LEVEL_MULTIPLIER(float p0) { NativeInvoke::Invoke<scrVoid>(0x020E5F00CDA207BA, p0); } // 020E5F00CDA207BA 1359292F
	static void SET_WANTED_LEVEL_DIFFICULTY(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x9B0BB33B04405E7A, p0, p1); } // 9B0BB33B04405E7A B552626C
	static void RESET_WANTED_LEVEL_DIFFICULTY(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xB9D0DD990DC141DD, p0); } // B9D0DD990DC141DD A64C378D
	static void START_FIRING_AMNESTY(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xBF9BD71691857E48, p0); } // BF9BD71691857E48 5F8A22A6
	static void REPORT_CRIME(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xE9B09589827545E7, p0, p1, p2); } // E9B09589827545E7 D8EB3A44
	static void _0x9A987297ED8BD838(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x9A987297ED8BD838, p0, p1); } // 9A987297ED8BD838 59B5C2A2
	static void _0xBC9490CA15AEA8FB(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xBC9490CA15AEA8FB, p0); } // BC9490CA15AEA8FB 6B34A160
	static void _0x4669B3ED80F24B4E(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x4669B3ED80F24B4E, p0); } // 4669B3ED80F24B4E B9FB142F
	static void _0xAD73CE5A09E42D12(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xAD73CE5A09E42D12, p0); } // AD73CE5A09E42D12 85725848
	static void _0x36F1B38855F2A8DF(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x36F1B38855F2A8DF, p0); } // 36F1B38855F2A8DF 3A7E5FB6
	static void _0xDC64D2C53493ED12(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xDC64D2C53493ED12, p0); } // DC64D2C53493ED12 D15C4B1C
	static void _0xB45EFF719D8427A6(float p0) { NativeInvoke::Invoke<scrVoid>(0xB45EFF719D8427A6, p0); } // B45EFF719D8427A6 BF6993C7
	static void _0x0032A6DBA562C518() { NativeInvoke::Invoke<scrVoid>(0x0032A6DBA562C518); } // 0032A6DBA562C518 47CAB814
	static BOOL CAN_PLAYER_START_MISSION(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xDE7465A27D403C06, p0); } // DE7465A27D403C06 39E3CB3F
	static BOOL IS_PLAYER_READY_FOR_CUTSCENE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x908CBECC2CAA3690, p0); } // 908CBECC2CAA3690 BB77E9CD
	static BOOL IS_PLAYER_TARGETTING_ENTITY(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x7912F7FC4F6264B6, p0, p1); } // 7912F7FC4F6264B6 F3240B77
	static BOOL GET_PLAYER_TARGET_ENTITY(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x13EDE1A5DBF797C9, p0, p1); } // 13EDE1A5DBF797C9 F6AAA2D7
	static BOOL IS_PLAYER_FREE_AIMING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x2E397FD2ECD37C87, p0); } // 2E397FD2ECD37C87 1DEC67B7
	static BOOL IS_PLAYER_FREE_AIMING_AT_ENTITY(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x3C06B5C839B38F7B, p0, p1); } // 3C06B5C839B38F7B 7D80EEAA
	static BOOL _0x2975C866E6713290(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x2975C866E6713290, p0, p1); } // 2975C866E6713290 8866D9D0
	static void _0x29961D490E5814FD(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x29961D490E5814FD, p0, p1); } // 29961D490E5814FD 74D42C03
	static void SET_PLAYER_CAN_DO_DRIVE_BY(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x6E8834B52EC20C77, p0, p1); } // 6E8834B52EC20C77 F4D99685
	static void SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xD5E460AD7020A246, p0, p1); } // D5E460AD7020A246 71B305BB
	static void SET_PLAYER_CAN_USE_COVER(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xD465A8599DFF6814, p0, p1); } // D465A8599DFF6814 13CAFAFA
	static scrAny GET_MAX_WANTED_LEVEL() { return NativeInvoke::Invoke<scrAny>(0x462E0DB9B137DC5F); } // 462E0DB9B137DC5F 457F1E44
	static BOOL IS_PLAYER_TARGETTING_ANYTHING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x78CFE51896B6B8A4, p0); } // 78CFE51896B6B8A4 456DB50D
	static void SET_PLAYER_SPRINT(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xA01B8075D8B92DF4, p0, p1); } // A01B8075D8B92DF4 7DD7900C
	static void RESET_PLAYER_STAMINA(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA6F312FCCE9C1DFE, p0); } // A6F312FCCE9C1DFE C0445A9C
	static void RESTORE_PLAYER_STAMINA(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xA352C1B864CAFD33, p0, p1); } // A352C1B864CAFD33 62A93608
	static float _0x3F9F16F8E65A7ED7(scrAny p0) { return NativeInvoke::Invoke<float>(0x3F9F16F8E65A7ED7, p0); } // 3F9F16F8E65A7ED7 47017C90
	static float GET_PLAYER_SPRINT_TIME_REMAINING(scrAny p0) { return NativeInvoke::Invoke<float>(0x1885BC9B108B4C99, p0); } // 1885BC9B108B4C99 40E80543
	static float GET_PLAYER_UNDERWATER_TIME_REMAINING(scrAny p0) { return NativeInvoke::Invoke<float>(0xA1FCF8E6AF40B731, p0); } // A1FCF8E6AF40B731 1317125A
	static scrAny GET_PLAYER_GROUP(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x0D127585F77030AF, p0); } // 0D127585F77030AF A5EDCDE8
	static scrAny GET_PLAYER_MAX_ARMOUR(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x92659B4CE1863CB3, p0); } // 92659B4CE1863CB3 02A50657
	static BOOL IS_PLAYER_CONTROL_ON(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x49C32D60007AFA47, p0); } // 49C32D60007AFA47 618857F2
	static BOOL IS_PLAYER_SCRIPT_CONTROL_ON(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x8A876A65283DD7D7, p0); } // 8A876A65283DD7D7 61B00A84
	static BOOL IS_PLAYER_CLIMBING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x95E8F73DC65EFB9C, p0); } // 95E8F73DC65EFB9C 4A9E9AE0
	static BOOL IS_PLAYER_BEING_ARRESTED(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<BOOL>(0x388A47C51ABDAC8E, p0, p1); } // 388A47C51ABDAC8E 7F6A60D3
	static void _0x2D03E13C460760D6(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x2D03E13C460760D6, p0); } // 2D03E13C460760D6 453C7CAB
	static scrAny GET_PLAYERS_LAST_VEHICLE() { return NativeInvoke::Invoke<scrAny>(0xB6997A7EB3F5C8C0); } // B6997A7EB3F5C8C0 E2757AC1
	static scrAny GET_PLAYER_INDEX() { return NativeInvoke::Invoke<scrAny>(0xA5EDC40EF369B48D); } // A5EDC40EF369B48D 309BBDC1
	static scrAny INT_TO_PLAYERINDEX(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x41BD2A6B006AF756, p0); } // 41BD2A6B006AF756 98DD98F1
	static scrAny _0x9EC6603812C24710(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x9EC6603812C24710, p0); } // 9EC6603812C24710 98F3B274
	static scrAny GET_TIME_SINCE_PLAYER_HIT_VEHICLE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x5D35ECF3A81A0EE0, p0); } // 5D35ECF3A81A0EE0 6E9B8B9E
	static scrAny GET_TIME_SINCE_PLAYER_HIT_PED(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xE36A25322DC35F42, p0); } // E36A25322DC35F42 B6209195
	static scrAny GET_TIME_SINCE_PLAYER_DROVE_ON_PAVEMENT(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xD559D2BE9E37853B, p0); } // D559D2BE9E37853B 8836E732
	static scrAny GET_TIME_SINCE_PLAYER_DROVE_AGAINST_TRAFFIC(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xDB89591E290D9182, p0); } // DB89591E290D9182 9F27D00E
	static BOOL IS_PLAYER_FREE_FOR_AMBIENT_TASK(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xDCCFD3F106C36AB4, p0); } // DCCFD3F106C36AB4 85C7E232
	static scrPlayer PLAYER_ID() { return NativeInvoke::Invoke<scrAny>(0x4F8644AF03D0E0D6); } // 4F8644AF03D0E0D6 8AEA886C
	static scrPed PLAYER_PED_ID() { return NativeInvoke::Invoke<scrAny>(0xD80958FC74E988A6); } // D80958FC74E988A6 FA92E226
	static scrAny _0xEE68096F9F37341E() { return NativeInvoke::Invoke<scrAny>(0xEE68096F9F37341E); } // EE68096F9F37341E 8DD5B838
	static BOOL _0xC968670BFACE42D9(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xC968670BFACE42D9, p0); } // C968670BFACE42D9 4B37333C
	static void FORCE_CLEANUP(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xBC8983F38F78ED51, p0); } // BC8983F38F78ED51 FDAAEA2B
	static void _0x4C68DDDDF0097317(scrAny *p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x4C68DDDDF0097317, p0, p1); } // 4C68DDDDF0097317 04256C73
	static void _0xF745B37630DF176B(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xF745B37630DF176B, p0, p1); } // F745B37630DF176B 882D3EB3
	static scrAny _0x9A41CF4674A12272() { return NativeInvoke::Invoke<scrAny>(0x9A41CF4674A12272); } // 9A41CF4674A12272 39AA9FC8
	static void SET_PLAYER_MAY_ONLY_ENTER_THIS_VEHICLE(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x8026FF78F208978A, p0, p1); } // 8026FF78F208978A A454DD29
	static void _0x1DE37BBF9E9CC14A(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x1DE37BBF9E9CC14A, p0); } // 1DE37BBF9E9CC14A AF7AFCC4
	static BOOL GIVE_ACHIEVEMENT_TO_PLAYER(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xBEC7076D64130195, p0); } // BEC7076D64130195 822BC992
	static BOOL _0xC2AFFFDABBDC2C5C(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xC2AFFFDABBDC2C5C, p0, p1); } // C2AFFFDABBDC2C5C
	static BOOL HAS_ACHIEVEMENT_BEEN_PASSED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x867365E111A3B6EB, p0); } // 867365E111A3B6EB 136A5BE9
	static BOOL IS_PLAYER_ONLINE() { return NativeInvoke::Invoke<BOOL>(0xF25D331DC2627BBC); } // F25D331DC2627BBC 9FAB6729
	static scrAny IS_PLAYER_LOGGING_IN_NP() { return NativeInvoke::Invoke<scrAny>(0x74556E1420867ECA); } // 74556E1420867ECA 8F72FAD0
	static void DISPLAY_SYSTEM_SIGNIN_UI(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x94DD7888C10A979E, p0); } // 94DD7888C10A979E 4264CED2
	static BOOL IS_SYSTEM_UI_BEING_DISPLAYED() { return NativeInvoke::Invoke<BOOL>(0x5D511E3867C87139); } // 5D511E3867C87139 E495B6DA
	static void SET_PLAYER_INVINCIBLE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x239528EACDC3E7DE, p0, p1); } // 239528EACDC3E7DE DFB9A2A2
	static BOOL GET_PLAYER_INVINCIBLE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xB721981B2B939E07, p0); } // B721981B2B939E07 680C90EE
	static void _0xCAC57395B151135F(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xCAC57395B151135F, p0, p1); } // CAC57395B151135F 00563E0D
	static void REMOVE_PLAYER_HELMET(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xF3AC26D3CC576528, p0, p1); } // F3AC26D3CC576528 6255F3B4
	static void GIVE_PLAYER_RAGDOLL_CONTROL(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x3C49C870E66F0A28, p0, p1); } // 3C49C870E66F0A28 C7B4D7AC
	static void SET_PLAYER_LOCKON(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x5C8B2F450EE4328E, p0, p1); } // 5C8B2F450EE4328E 0B270E0F
	static void SET_PLAYER_TARGETING_MODE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xB1906895227793F3, p0); } // B1906895227793F3 61CAE253
	static BOOL _0xB9CF1F793A9F1BF1() { return NativeInvoke::Invoke<BOOL>(0xB9CF1F793A9F1BF1); } // B9CF1F793A9F1BF1
	static void CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_PED(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xF0B67A4DE6AB5F98, p0); } // F0B67A4DE6AB5F98 1D31CBBD
	static BOOL HAS_PLAYER_DAMAGED_AT_LEAST_ONE_PED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x20CE80B0C2BF4ACC, p0); } // 20CE80B0C2BF4ACC 14F52453
	static void _0x4AACB96203D11A31(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x4AACB96203D11A31, p0); } // 4AACB96203D11A31 7E3BFBC5
	static BOOL _0xE4B90F367BD81752(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xE4B90F367BD81752, p0); } // E4B90F367BD81752 A3707DFC
	static void SET_AIR_DRAG_MULTIPLIER_FOR_PLAYERS_VEHICLE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xCA7DC8329F0A1E9E, p0, p1); } // CA7DC8329F0A1E9E F20F72E5
	static void _SET_SWIM_SPEED_MULTIPLIER(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xA91C6F0FF7D16A13, p0, p1); } // A91C6F0FF7D16A13 B986FF47
	static void _SET_MOVE_SPEED_MULTIPLIER(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x6DB47AA77FD94E09, p0, p1); } // 6DB47AA77FD94E09 825423C2
	static scrAny GET_TIME_SINCE_LAST_ARREST() { return NativeInvoke::Invoke<scrAny>(0x5063F92F07C2A316); } // 5063F92F07C2A316 62824EF4
	static scrAny GET_TIME_SINCE_LAST_DEATH() { return NativeInvoke::Invoke<scrAny>(0xC7034807558DDFCA); } // C7034807558DDFCA 24BC5AC0
	static void ASSISTED_MOVEMENT_CLOSE_ROUTE() { NativeInvoke::Invoke<scrVoid>(0xAEBF081FFC0A0E5E); } // AEBF081FFC0A0E5E F23277F3
	static void ASSISTED_MOVEMENT_FLUSH_ROUTE() { NativeInvoke::Invoke<scrVoid>(0x8621390F0CDCFE1F); } // 8621390F0CDCFE1F D04568B9
	static void SET_PLAYER_FORCED_AIM(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x0FEE4F80AC44A726, p0, p1); } // 0FEE4F80AC44A726 94E42E2E
	static void SET_PLAYER_FORCED_ZOOM(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x75E7D505F2B15902, p0, p1); } // 75E7D505F2B15902 B0C576CB
	static void _0x7651BC64AE59E128(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x7651BC64AE59E128, p0, p1); } // 7651BC64AE59E128 374F42F0
	static void DISABLE_PLAYER_FIRING(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x5E6CC07646BBEAB8, p0, p1); } // 5E6CC07646BBEAB8 30CB28CB
	static void _0xB885852C39CC265D() { NativeInvoke::Invoke<scrVoid>(0xB885852C39CC265D); } // B885852C39CC265D
	static void _0x2E8AABFA40A84F8C(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x2E8AABFA40A84F8C, p0, p1); } // 2E8AABFA40A84F8C CCD937E7
	static void SET_PLAYER_MAX_ARMOUR(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x77DFCCF5948B8C71, p0, p1); } // 77DFCCF5948B8C71 C6C3C53B
	static void SPECIAL_ABILITY_DEACTIVATE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xD6A953C6D1492057, p0); } // D6A953C6D1492057 80C2AB09
	static void _0x9CB5CE07A3968D5A(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x9CB5CE07A3968D5A, p0); } // 9CB5CE07A3968D5A 0751908A
	static void SPECIAL_ABILITY_RESET(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x375F0E738F861A94, p0); } // 375F0E738F861A94 A7D8BCD3
	static void _0xC9A763D8FE87436A(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xC9A763D8FE87436A, p0); } // C9A763D8FE87436A 4136829A
	static void _0x2E7B9B683481687D(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x2E7B9B683481687D, p0, p1, p2); } // 2E7B9B683481687D 6F463F56
	static void _0xF113E3AA9BC54613(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xF113E3AA9BC54613, p0, p1, p2); } // F113E3AA9BC54613 AB55D8F3
	static void _0xF733F45FA4497D93(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xF733F45FA4497D93, p0, p1, p2); } // F733F45FA4497D93 F440C04D
	static void _0xED481732DFF7E997(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xED481732DFF7E997, p0, p1); } // ED481732DFF7E997 5FEE98A2
	static void _0xB7B0870EB531D08D(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xB7B0870EB531D08D, p0, p1, p2); } // B7B0870EB531D08D 72429998
	static void RESET_SPECIAL_ABILITY_CONTROLS_CINEMATIC(scrAny p0, float p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xA0696A65F009EE18, p0, p1, p2); } // A0696A65F009EE18 8C7E68C1
	static void _RECHARGE_SPECIAL_ABILITY(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x3DACA8DDC6FD4980, p0, p1); } // 3DACA8DDC6FD4980 B71589DA
	static void _0x1D506DBBBC51E64B(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x1D506DBBBC51E64B, p0, p1); } // 1D506DBBBC51E64B 9F80F6DF
	static void SPECIAL_ABILITY_LOCK(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x6A09D0D590A47D13, p0); } // 6A09D0D590A47D13 1B7BB388
	static void SPECIAL_ABILITY_UNLOCK(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xF145F3BE2EFA9A3B, p0); } // F145F3BE2EFA9A3B 1FDB2919
	static BOOL IS_SPECIAL_ABILITY_UNLOCKED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xC6017F6A6CDFA694, p0); } // C6017F6A6CDFA694 C9C75E82
	static BOOL IS_SPECIAL_ABILITY_ACTIVE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x3E5F7FC85D854E15, p0); } // 3E5F7FC85D854E15 1B17E334
	static BOOL IS_SPECIAL_ABILITY_METER_FULL(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x05A1FE504B7F2587, p0); } // 05A1FE504B7F2587 2E19D7F6
	static void ENABLE_SPECIAL_ABILITY(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x181EC197DAEFE121, p0, p1); } // 181EC197DAEFE121 C86C1B4E
	static BOOL IS_SPECIAL_ABILITY_ENABLED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xB1D200FE26AEF3CB, p0); } // B1D200FE26AEF3CB C01238CC
	static void SET_SPECIAL_ABILITY_MULTIPLIER(float p0) { NativeInvoke::Invoke<scrVoid>(0xA49C426ED0CA4AB7, p0); } // A49C426ED0CA4AB7 FF1BC556
	static void _0xFFEE8FA29AB9A18E(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xFFEE8FA29AB9A18E, p0); } // FFEE8FA29AB9A18E 5D0FE25B
	static BOOL _0x5FC472C501CCADB3(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x5FC472C501CCADB3, p0); } // 5FC472C501CCADB3 46E7E31D
	static BOOL _0xF10B44FD479D69F3(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xF10B44FD479D69F3, p0, p1); } // F10B44FD479D69F3 1E359CC8
	static BOOL _0xDD2620B7B9D16FF1(scrAny p0, float p1) { return NativeInvoke::Invoke<BOOL>(0xDD2620B7B9D16FF1, p0, p1); } // DD2620B7B9D16FF1 8CB53C9F
	static void START_PLAYER_TELEPORT(scrAny p0, float p1, float p2, float p3, float p4, BOOL p5, BOOL p6, BOOL p7) { NativeInvoke::Invoke<scrVoid>(0xAD15F075A4DA0FDE, p0, p1, p2, p3, p4, p5, p6, p7); } // AD15F075A4DA0FDE C552E06C
	static void STOP_PLAYER_TELEPORT() { NativeInvoke::Invoke<scrVoid>(0xC449EDED9D73009C); } // C449EDED9D73009C 86AB8DBB
	static BOOL IS_PLAYER_TELEPORT_ACTIVE() { return NativeInvoke::Invoke<BOOL>(0x02B15662D7F8886F); } // 02B15662D7F8886F 3A11D118
	static float GET_PLAYER_CURRENT_STEALTH_NOISE(scrAny p0) { return NativeInvoke::Invoke<float>(0x2F395D61F3A1F877, p0); } // 2F395D61F3A1F877 C3B02362
	static void _0x5DB660B38DD98A31(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x5DB660B38DD98A31, p0, p1); } // 5DB660B38DD98A31 45514731
	static void SET_PLAYER_WEAPON_DAMAGE_MODIFIER(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xCE07B9F7817AADA3, p0, p1); } // CE07B9F7817AADA3 B02C2F39
	static void _0x2D83BC011CA14A3C(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x2D83BC011CA14A3C, p0, p1); } // 2D83BC011CA14A3C AE446344
	static void _0x4A3DC7ECCC321032(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x4A3DC7ECCC321032, p0, p1); } // 4A3DC7ECCC321032 362E69AD
	static void _0xAE540335B4ABC4E2(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xAE540335B4ABC4E2, p0, p1); } // AE540335B4ABC4E2 9F3D577F
	static void SET_PLAYER_VEHICLE_DAMAGE_MODIFIER(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xA50E117CDDF82F0C, p0, p1); } // A50E117CDDF82F0C 823ECA63
	static void _0x4C60E6EFDAFF2462(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x4C60E6EFDAFF2462, p0, p1); } // 4C60E6EFDAFF2462 A16626C7
	static void SET_PLAYER_PARACHUTE_TINT_INDEX(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xA3D0E54541D9A5E5, p0, p1); } // A3D0E54541D9A5E5 8EA12EDB
	static void GET_PLAYER_PARACHUTE_TINT_INDEX(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x75D3F7A1B0D9B145, p0, p1); } // 75D3F7A1B0D9B145 432B0509
	static void _0xAF04C87F5DC1DF38(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xAF04C87F5DC1DF38, p0, p1); } // AF04C87F5DC1DF38 70689638
	static void _0xD5A016BC3C09CF40(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xD5A016BC3C09CF40, p0, p1); } // D5A016BC3C09CF40 77B8EF01
	static void _0x93B0FB27C9A04060(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x93B0FB27C9A04060, p0, p1); } // 93B0FB27C9A04060 D79D5D1B
	static void _0x6E9C742F340CE5A2(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x6E9C742F340CE5A2, p0, p1); } // 6E9C742F340CE5A2 4E418E13
	static void _0x7DDAB28D31FAC363(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x7DDAB28D31FAC363, p0); } // 7DDAB28D31FAC363 A3E4798E
	static BOOL _0x5DDFE2FF727F3CA3(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x5DDFE2FF727F3CA3, p0); } // 5DDFE2FF727F3CA3 30DA1DA1
	static void _0xF401B182DBA8AF53(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xF401B182DBA8AF53, p0, p1); } // F401B182DBA8AF53 832DEB7A
	static void _0x8217FD371A4625CF(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x8217FD371A4625CF, p0, p1, p2, p3); } // 8217FD371A4625CF 14FE9264
	static void _0xEF56DBABD3CD4887(scrAny p0, scrAny *p1, scrAny *p2, scrAny *p3) { NativeInvoke::Invoke<scrVoid>(0xEF56DBABD3CD4887, p0, p1, p2, p3); } // EF56DBABD3CD4887 F66E5CDD
	static void _0x11D5F725F0E780E0(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x11D5F725F0E780E0, p0, p1); } // 11D5F725F0E780E0 725C6174
	static void SET_PLAYER_NOISE_MULTIPLIER(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xDB89EF50FF25FCE9, p0, p1); } // DB89EF50FF25FCE9 15786DD1
	static void _0xB2C1A29588A9F47C(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xB2C1A29588A9F47C, p0, p1); } // B2C1A29588A9F47C 8D2D89C4
	static BOOL _0xF297383AA91DCA29(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xF297383AA91DCA29, p0, p1); } // F297383AA91DCA29 1C70B2EB
	static void SIMULATE_PLAYER_INPUT_GAIT(scrAny p0, float p1, scrAny p2, float p3, BOOL p4, BOOL p5) { NativeInvoke::Invoke<scrVoid>(0x477D5D63E63ECA5D, p0, p1, p2, p3, p4, p5); } // 477D5D63E63ECA5D 0D77CC34
	static void RESET_PLAYER_INPUT_GAIT(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x19531C47A2ABD691, p0); } // 19531C47A2ABD691 4A701EE1
	static void _0x9F343285A00B4BB6(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x9F343285A00B4BB6, p0, p1); } // 9F343285A00B4BB6 A97C2059
	static void _0xD2B315B6689D537D(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xD2B315B6689D537D, p0, p1); } // D2B315B6689D537D A25D767E
	static void _0x4E9021C1FCDD507A(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x4E9021C1FCDD507A, p0, p1); } // 4E9021C1FCDD507A 3D26105F
	static BOOL _0x690A61A6D13583F6(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x690A61A6D13583F6, p0); } // 690A61A6D13583F6 1D371529
	static void _0x9EDD76E87D5D51BA(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x9EDD76E87D5D51BA, p0); } // 9EDD76E87D5D51BA E30A64DC
	static void SET_PLAYER_SIMULATE_AIMING(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xC54C95DA968EC5B5, p0, p1); } // C54C95DA968EC5B5 F1E0CAFC
	static void _0x749FADDF97DFE930(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x749FADDF97DFE930, p0, p1); } // 749FADDF97DFE930 F7A0F00F
	static void _0x9F7BBA2EA6372500(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x9F7BBA2EA6372500, p0); } // 9F7BBA2EA6372500 B8209F16
	static void _0x14D913B777DFF5DA(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x14D913B777DFF5DA, p0); } // 14D913B777DFF5DA 8D9FD4D1
	static void _0xED51733DC73AED51(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7) { NativeInvoke::Invoke<scrVoid>(0xED51733DC73AED51, p0, p1, p2, p3, p4, p5, p6, p7); } // ED51733DC73AED51 ECD12E60
	static void _0x1DD5897E2FA6E7C9() { NativeInvoke::Invoke<scrVoid>(0x1DD5897E2FA6E7C9); } // 1DD5897E2FA6E7C9 96100EA4
	static BOOL _0xD705740BB0A1CF4C(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xD705740BB0A1CF4C, p0); } // D705740BB0A1CF4C 4A01B76A
	static BOOL _0x38D28DA81E4E9BF9(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x38D28DA81E4E9BF9, p0); } // 38D28DA81E4E9BF9 013B4F72
	static BOOL _0xBC0753C9CA14B506(scrAny p0, scrAny p1, BOOL p2) { return NativeInvoke::Invoke<BOOL>(0xBC0753C9CA14B506, p0, p1, p2); } // BC0753C9CA14B506 9DF75B2A
	static BOOL IS_PLAYER_RIDING_TRAIN(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x4EC12697209F2196, p0); } // 4EC12697209F2196 9765E71D
	static BOOL _0xD55DDFB47991A294(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xD55DDFB47991A294, p0); } // D55DDFB47991A294 FEA40B6C
	static void _0xFF300C7649724A0B(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xFF300C7649724A0B, p0, p1); } // FF300C7649724A0B AD8383FA
	static void _0xD9284A8C0D48352C(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0xD9284A8C0D48352C, p0, p1, p2, p3, p4); } // D9284A8C0D48352C 9254249D
	static void _0x0F4CC924CF8C7B21(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x0F4CC924CF8C7B21, p0); } // 0F4CC924CF8C7B21 FD60F5AB
	static void _0x977DB4641F6FC3DB(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x977DB4641F6FC3DB, p0, p1); } // 977DB4641F6FC3DB 5D382498
	static void _0x8753997EB5F6EE3F(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x8753997EB5F6EE3F, p0); } // 8753997EB5F6EE3F 6FF034BB
	static void _0xDC80A4C2F18A2B64(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xDC80A4C2F18A2B64, p0, p1); } // DC80A4C2F18A2B64 A877FF5E
	static void _0x10C54E4389C12B42(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x10C54E4389C12B42, p0); } // 10C54E4389C12B42 BB62AAC5
	static void _0xC142BE3BB9CE125F(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xC142BE3BB9CE125F, p0); } // C142BE3BB9CE125F 8C6E611D
	static void _0x2F7CEB6520288061(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x2F7CEB6520288061, p0); } // 2F7CEB6520288061 2849D4B2
	static void _0x5501B7A5CDB79D37(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x5501B7A5CDB79D37, p0); } // 5501B7A5CDB79D37
}

namespace ENTITY
{
	static BOOL DOES_ENTITY_EXIST(scrEntity p0) { return NativeInvoke::Invoke<BOOL>(0x7239B21A38F536BA, p0); } // 7239B21A38F536BA 3AC90869
	static BOOL _0xDDE6DF5AE89981D2(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<BOOL>(0xDDE6DF5AE89981D2, p0, p1); } // DDE6DF5AE89981D2 ACFEB3F9
	static BOOL DOES_ENTITY_HAVE_DRAWABLE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x060D6E96F8B8E48D, p0); } // 060D6E96F8B8E48D A5B33300
	static BOOL DOES_ENTITY_HAVE_PHYSICS(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xDA95EA3317CC5064, p0); } // DA95EA3317CC5064 9BCD2979
	static BOOL HAS_ENTITY_ANIM_FINISHED(scrAny p0, scrAny *p1, scrAny *p2, scrAny p3) { return NativeInvoke::Invoke<BOOL>(0x20B711662962B472, p0, p1, p2, p3); } // 20B711662962B472 1D9CAB92
	static BOOL HAS_ENTITY_BEEN_DAMAGED_BY_ANY_OBJECT(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x95EB9964FF5C5C65, p0); } // 95EB9964FF5C5C65 6B74582E
	static BOOL HAS_ENTITY_BEEN_DAMAGED_BY_ANY_PED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x605F5A140F202491, p0); } // 605F5A140F202491 53FD4A25
	static BOOL HAS_ENTITY_BEEN_DAMAGED_BY_ANY_VEHICLE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xDFD5033FDBA0A9C8, p0); } // DFD5033FDBA0A9C8 878C2CE0
	static BOOL HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(scrAny p0, scrAny p1, BOOL p2) { return NativeInvoke::Invoke<BOOL>(0xC86D67D52A707CF8, p0, p1, p2); } // C86D67D52A707CF8 07FC77E0
	static BOOL HAS_ENTITY_CLEAR_LOS_TO_ENTITY(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0xFCDFF7B72D23A1AC, p0, p1, p2); } // FCDFF7B72D23A1AC 53576FA7
	static BOOL HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x0267D00AF114F17A, p0, p1); } // 0267D00AF114F17A 210D87C8
	static BOOL HAS_ENTITY_COLLIDED_WITH_ANYTHING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x8BAD02F0368D9E14, p0); } // 8BAD02F0368D9E14 662A2F41
	static scrAny _0x5C3D0A935F535C4C(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x5C3D0A935F535C4C, p0); } // 5C3D0A935F535C4C C0E3AA47
	static scrVector3 _0xE465D4AB7CA6AE72(scrAny p0) { return NativeInvoke::Invoke<scrVector3>(0xE465D4AB7CA6AE72, p0); } // E465D4AB7CA6AE72 AB415C07
	static void _0x40FDEDB72F8293B2(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x40FDEDB72F8293B2, p0); } // 40FDEDB72F8293B2 58D9775F
	static float GET_ENTITY_ANIM_CURRENT_TIME(scrAny p0, scrAny *p1, scrAny *p2) { return NativeInvoke::Invoke<float>(0x346D81500D088F42, p0, p1, p2); } // 346D81500D088F42 83943F41
	static float GET_ENTITY_ANIM_TOTAL_TIME(scrAny p0, scrAny *p1, scrAny *p2) { return NativeInvoke::Invoke<float>(0x50BD2730B191E360, p0, p1, p2); } // 50BD2730B191E360 433A9D18
	static scrAny _0xFEDDF04D62B8D790(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xFEDDF04D62B8D790, p0, p1); } // FEDDF04D62B8D790
	static scrAny GET_ENTITY_ATTACHED_TO(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x48C2BED9180FE123, p0); } // 48C2BED9180FE123 FE1589F9
	static scrVector3 GET_ENTITY_COORDS(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<scrVector3>(0x3FEF770D40960D5A, p0, p1); } // 3FEF770D40960D5A 1647F1CB
	static scrVector3 GET_ENTITY_FORWARD_VECTOR(scrAny p0) { return NativeInvoke::Invoke<scrVector3>(0x0A794A5A57F8DF91, p0); } // 0A794A5A57F8DF91 84DCECBF
	static float GET_ENTITY_FORWARD_X(scrAny p0) { return NativeInvoke::Invoke<float>(0x8BB4EF4214E0E6D5, p0); } // 8BB4EF4214E0E6D5 49FAE914
	static float GET_ENTITY_FORWARD_Y(scrAny p0) { return NativeInvoke::Invoke<float>(0x866A4A5FAE349510, p0); } // 866A4A5FAE349510 9E2F917C
	static float GET_ENTITY_HEADING(scrAny p0) { return NativeInvoke::Invoke<float>(0xE83D4F9BA2A38914, p0); } // E83D4F9BA2A38914 972CC383
	static scrAny GET_ENTITY_HEALTH(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xEEF059FAD016D209, p0); } // EEF059FAD016D209 8E3222B7
	static scrAny GET_ENTITY_MAX_HEALTH(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x15D757606D170C3C, p0); } // 15D757606D170C3C C7AE6AA1
	static void SET_ENTITY_MAX_HEALTH(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x166E7CF68597D8B5, p0, p1); } // 166E7CF68597D8B5 96F84DF8
	static float GET_ENTITY_HEIGHT(scrAny p0, float p1, float p2, float p3, BOOL p4, BOOL p5) { return NativeInvoke::Invoke<float>(0x5A504562485944DD, p0, p1, p2, p3, p4, p5); } // 5A504562485944DD EE443481
	static float GET_ENTITY_HEIGHT_ABOVE_GROUND(scrAny p0) { return NativeInvoke::Invoke<float>(0x1DD55701034110E5, p0); } // 1DD55701034110E5 57F56A4D
	static void GET_ENTITY_MATRIX(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0xECB2FC7235A7D137, p0, p1, p2, p3, p4); } // ECB2FC7235A7D137 EB9EB001
	static scrAny GET_ENTITY_MODEL(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x9F47B058362C84B5, p0); } // 9F47B058362C84B5 DAFCB3EC
	static scrVector3 GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(scrAny p0, float p1, float p2, float p3) { return NativeInvoke::Invoke<scrVector3>(0x2274BC1C4885E333, p0, p1, p2, p3); } // 2274BC1C4885E333 6477EC9E
	static scrVector3 GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(scrAny p0, float p1, float p2, float p3) { return NativeInvoke::Invoke<scrVector3>(0x1899F328B0E12848, p0, p1, p2, p3); } // 1899F328B0E12848 ABCF043A
	static float GET_ENTITY_PITCH(scrAny p0) { return NativeInvoke::Invoke<float>(0xD45DC2893621E1FE, p0); } // D45DC2893621E1FE FCE6ECE5
	static void GET_ENTITY_QUATERNION(scrAny p0, scrAny *p1, scrAny *p2, scrAny *p3, scrAny *p4) { NativeInvoke::Invoke<scrVoid>(0x7B3703D2D32DFA18, p0, p1, p2, p3, p4); } // 7B3703D2D32DFA18 5154EC90
	static float GET_ENTITY_ROLL(scrAny p0) { return NativeInvoke::Invoke<float>(0x831E0242595560DF, p0); } // 831E0242595560DF 36610842
	static scrVector3 GET_ENTITY_ROTATION(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrVector3>(0xAFBD61CC738D9EB9, p0, p1); } // AFBD61CC738D9EB9 8FF45B04
	static scrVector3 GET_ENTITY_ROTATION_VELOCITY(scrAny p0) { return NativeInvoke::Invoke<scrVector3>(0x213B91045D09B983, p0); } // 213B91045D09B983 9BF8A73F
	static scrAny GET_ENTITY_SCRIPT(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<scrAny>(0xA6E9C38DB51D7748, p0, p1); } // A6E9C38DB51D7748 B7F70784
	static float GET_ENTITY_SPEED(scrAny p0) { return NativeInvoke::Invoke<float>(0xD5037BA82E12416F, p0); } // D5037BA82E12416F 9E1E4798
	static scrVector3 GET_ENTITY_SPEED_VECTOR(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<scrVector3>(0x9A8D700A51CB7B0D, p0, p1); } // 9A8D700A51CB7B0D 3ED2B997
	static float GET_ENTITY_UPRIGHT_VALUE(scrAny p0) { return NativeInvoke::Invoke<float>(0x95EED5A694951F9F, p0); } // 95EED5A694951F9F F4268190
	static scrVector3 GET_ENTITY_VELOCITY(scrAny p0) { return NativeInvoke::Invoke<scrVector3>(0x4805D2B1D8CF94A9, p0); } // 4805D2B1D8CF94A9 C14C9B6B
	static scrAny _0xD7E3B9735C0F89D6(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xD7E3B9735C0F89D6, p0); } // D7E3B9735C0F89D6 BC5A9C58
	static scrAny _0x04A2A40C73395041(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x04A2A40C73395041, p0); } // 04A2A40C73395041 C46F74AC
	static scrAny _0x4B53F92932ADFAC0(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x4B53F92932ADFAC0, p0); } // 4B53F92932ADFAC0 C69CF43D
	static scrVector3 _0x44A8FCB8ED227738(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrVector3>(0x44A8FCB8ED227738, p0, p1); } // 44A8FCB8ED227738 7C6339DF
	static scrAny GET_NEAREST_PLAYER_TO_ENTITY(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x7196842CB375CDB3, p0); } // 7196842CB375CDB3 CE17FDEC
	static scrAny _0x4DC9A62F844D9337(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x4DC9A62F844D9337, p0, p1); } // 4DC9A62F844D9337 B1808F56
	static scrAny GET_ENTITY_TYPE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x8ACD366038D14505, p0); } // 8ACD366038D14505 0B1BD08D
	static scrAny _0xF6F5161F4534EDFF(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xF6F5161F4534EDFF, p0); } // F6F5161F4534EDFF
	static BOOL IS_AN_ENTITY(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x731EC8A916BD11A1, p0); } // 731EC8A916BD11A1 D4B9715A
	static BOOL IS_ENTITY_A_PED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x524AC5ECEA15343E, p0); } // 524AC5ECEA15343E 55D33EAB
	static BOOL IS_ENTITY_A_MISSION_ENTITY(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x0A7B270912999B3C, p0); } // 0A7B270912999B3C 2632E124
	static BOOL IS_ENTITY_A_VEHICLE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x6AC7003FA6E5575E, p0); } // 6AC7003FA6E5575E BE800B01
	static BOOL IS_ENTITY_AN_OBJECT(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x8D68C8FD0FACA94E, p0); } // 8D68C8FD0FACA94E 3F52E561
	static BOOL IS_ENTITY_AT_COORD(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, BOOL p7, BOOL p8, scrAny p9) { return NativeInvoke::Invoke<BOOL>(0x20B60995556D004F, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 20B60995556D004F D749B606
	static BOOL IS_ENTITY_AT_ENTITY(scrAny p0, scrAny p1, float p2, float p3, float p4, BOOL p5, BOOL p6, scrAny p7) { return NativeInvoke::Invoke<BOOL>(0x751B70C3D034E187, p0, p1, p2, p3, p4, p5, p6, p7); } // 751B70C3D034E187 DABDCB52
	static BOOL IS_ENTITY_ATTACHED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xB346476EF1A64897, p0); } // B346476EF1A64897 EC1479D5
	static BOOL IS_ENTITY_ATTACHED_TO_ANY_OBJECT(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xCF511840CEEDE0CC, p0); } // CF511840CEEDE0CC 0B5DE340
	static BOOL IS_ENTITY_ATTACHED_TO_ANY_PED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xB1632E9A5F988D11, p0); } // B1632E9A5F988D11 9D7A609C
	static BOOL IS_ENTITY_ATTACHED_TO_ANY_VEHICLE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x26AA915AD89BFB4B, p0); } // 26AA915AD89BFB4B DE5C995E
	static BOOL IS_ENTITY_ATTACHED_TO_ENTITY(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xEFBE71898A993728, p0, p1); } // EFBE71898A993728 B0ABFEA8
	static BOOL IS_ENTITY_DEAD(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x5F9532F3B5CC2551, p0); } // 5F9532F3B5CC2551 B6F7CBAC
	static BOOL IS_ENTITY_IN_AIR(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x886E37EC497200B6, p0); } // 886E37EC497200B6 A4157987
	static BOOL IS_ENTITY_IN_ANGLED_AREA(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, BOOL p8, BOOL p9, scrAny p10) { return NativeInvoke::Invoke<BOOL>(0x51210CED3DA1C78A, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 51210CED3DA1C78A 883622FA
	static BOOL IS_ENTITY_IN_AREA(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, BOOL p7, BOOL p8, scrAny p9) { return NativeInvoke::Invoke<BOOL>(0x54736AA40E271165, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 54736AA40E271165 8C2DFA9D
	static BOOL IS_ENTITY_IN_ZONE(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0xB6463CF6AF527071, p0, p1); } // B6463CF6AF527071 45C82B21
	static BOOL IS_ENTITY_IN_WATER(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xCFB0A0D8EDD145A3, p0); } // CFB0A0D8EDD145A3 4C3C2508
	static float _0xE81AFC1BC4CC41CE(scrAny p0) { return NativeInvoke::Invoke<float>(0xE81AFC1BC4CC41CE, p0); } // E81AFC1BC4CC41CE 0170F68C
	static void _0x694E00132F2823ED(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x694E00132F2823ED, p0, p1); } // 694E00132F2823ED 40C84A74
	static BOOL IS_ENTITY_ON_SCREEN(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xE659E47AF827484B, p0); } // E659E47AF827484B C1FEC5ED
	static BOOL IS_ENTITY_PLAYING_ANIM(scrAny p0, scrAny *p1, scrAny *p2, scrAny p3) { return NativeInvoke::Invoke<BOOL>(0x1F0B79228E461EC9, p0, p1, p2, p3); } // 1F0B79228E461EC9 0D130D34
	static BOOL IS_ENTITY_STATIC(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x1218E6886D3D8327, p0); } // 1218E6886D3D8327 928E12E9
	static BOOL IS_ENTITY_TOUCHING_ENTITY(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x17FFC1B2BA35A494, p0, p1); } // 17FFC1B2BA35A494 6B931477
	static BOOL _0x0F42323798A58C8C(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x0F42323798A58C8C, p0, p1); } // 0F42323798A58C8C 307E7611
	static BOOL IS_ENTITY_UPRIGHT(scrAny p0, float p1) { return NativeInvoke::Invoke<BOOL>(0x5333F526F6AB19AA, p0, p1); } // 5333F526F6AB19AA 3BCDF4E1
	static BOOL IS_ENTITY_UPSIDEDOWN(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x1DBD58820FA61D71, p0); } // 1DBD58820FA61D71 5ACAA48F
	static BOOL IS_ENTITY_VISIBLE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x47D6F43D77935C75, p0); } // 47D6F43D77935C75 120B4ED5
	static BOOL IS_ENTITY_VISIBLE_TO_SCRIPT(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xD796CB5BA8F20E32, p0); } // D796CB5BA8F20E32 5D240E9D
	static BOOL IS_ENTITY_OCCLUDED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xE31C2C72B8692B64, p0); } // E31C2C72B8692B64 46BC5B40
	static BOOL _0xEE5D2A122E09EC42(scrAny p0, float p1, float p2, float p3, BOOL p4) { return NativeInvoke::Invoke<BOOL>(0xEE5D2A122E09EC42, p0, p1, p2, p3, p4); } // EE5D2A122E09EC42 EA127CBC
	static BOOL IS_ENTITY_WAITING_FOR_WORLD_COLLISION(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xD05BFF0C0A12C68F, p0); } // D05BFF0C0A12C68F 00AB7A4A
	static void _0x18FF00FC7EFF559E(scrAny p0, scrAny p1, float p2, float p3, float p4, scrAny p5, BOOL p6, BOOL p7, BOOL p8) { NativeInvoke::Invoke<scrVoid>(0x18FF00FC7EFF559E, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 18FF00FC7EFF559E 28924E98
	static void APPLY_FORCE_TO_ENTITY(scrAny p0, scrAny p1, float p2, float p3, float p4, float p5, float p6, float p7, scrAny p8, BOOL p9, BOOL p10, BOOL p11, BOOL p12, BOOL p13) { NativeInvoke::Invoke<scrVoid>(0xC5F68BE9613E2D18, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } // C5F68BE9613E2D18 C1C0855A
	static void ATTACH_ENTITY_TO_ENTITY(scrAny p0, scrAny p1, scrAny p2, float p3, float p4, float p5, float p6, float p7, float p8, BOOL p9, BOOL p10, BOOL p11, BOOL p12, scrAny p13, BOOL p14) { NativeInvoke::Invoke<scrVoid>(0x6B9BBD38AB0796DF, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); } // 6B9BBD38AB0796DF EC024237
	static void ATTACH_ENTITY_TO_ENTITY_PHYSICALLY(scrAny p0, scrAny p1, scrAny p2, scrAny p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12, float p13, BOOL p14, BOOL p15, BOOL p16, BOOL p17, scrAny p18) { NativeInvoke::Invoke<scrVoid>(0xC3675780C92F90F9, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18); } // C3675780C92F90F9 0547417F
	static void _0xF4080490ADC51C6F(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xF4080490ADC51C6F, p0); } // F4080490ADC51C6F 6909BA59
	static scrAny _0xFB71170B7E76ACBA(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<scrAny>(0xFB71170B7E76ACBA, p0, p1); } // FB71170B7E76ACBA E4ECAC22
	static void CLEAR_ENTITY_LAST_DAMAGE_ENTITY(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA72CD9CA74A5ECBA, p0); } // A72CD9CA74A5ECBA 2B83F43B
	static void DELETE_ENTITY(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xAE3CBE5BF394C9C9, p0); } // AE3CBE5BF394C9C9 FAA3D236
	static void DETACH_ENTITY(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x961AC54BF0613F5D, p0, p1, p2); } // 961AC54BF0613F5D C8EFCB41
	static void FREEZE_ENTITY_POSITION(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x428CA6DBD1094446, p0, p1); } // 428CA6DBD1094446 65C16D57
	static void _0x3910051CCECDB00C(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x3910051CCECDB00C, p0, p1); } // 3910051CCECDB00C D3850671
	static BOOL PLAY_ENTITY_ANIM(scrAny p0, scrAny *p1, scrAny *p2, float p3, BOOL p4, BOOL p5, BOOL p6, float p7, scrAny p8) { return NativeInvoke::Invoke<BOOL>(0x7FB218262B810701, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 7FB218262B810701 878753D5
	static BOOL PLAY_SYNCHRONIZED_ENTITY_ANIM(scrAny p0, scrAny p1, scrAny *p2, scrAny *p3, float p4, float p5, scrAny p6, float p7) { return NativeInvoke::Invoke<BOOL>(0xC77720A12FE14A86, p0, p1, p2, p3, p4, p5, p6, p7); } // C77720A12FE14A86 012760AA
	static BOOL _0xB9C54555ED30FBC4(float p0, float p1, float p2, float p3, scrAny p4, scrAny p5, scrAny *p6, scrAny *p7, float p8, float p9, scrAny p10, float p11) { return NativeInvoke::Invoke<BOOL>(0xB9C54555ED30FBC4, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // B9C54555ED30FBC4 EB4CBA74
	static BOOL _0x11E79CAB7183B6F5(float p0, float p1, float p2, float p3, scrAny p4, float p5) { return NativeInvoke::Invoke<BOOL>(0x11E79CAB7183B6F5, p0, p1, p2, p3, p4, p5); } // 11E79CAB7183B6F5 7253D5B2
	static scrAny STOP_ENTITY_ANIM(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0x28004F88151E03E0, p0, p1, p2, p3); } // 28004F88151E03E0 C4769830
	static BOOL STOP_SYNCHRONIZED_ENTITY_ANIM(scrAny p0, float p1, BOOL p2) { return NativeInvoke::Invoke<BOOL>(0x43D3807C077261E3, p0, p1, p2); } // 43D3807C077261E3 E27D2FC1
	static BOOL _0xEAF4CD9EA3E7E922(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xEAF4CD9EA3E7E922, p0, p1); } // EAF4CD9EA3E7E922 66571CA0
	static BOOL _0x07F1BE2BCCAA27A7(scrAny *p0, scrAny *p1, scrAny *p2, scrAny *p3, scrAny *p4) { return NativeInvoke::Invoke<BOOL>(0x07F1BE2BCCAA27A7, p0, p1, p2, p3, p4); } // 07F1BE2BCCAA27A7 C41DDA62
	static void SET_ENTITY_ANIM_CURRENT_TIME(scrAny p0, scrAny *p1, scrAny *p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x4487C259F0F70977, p0, p1, p2, p3); } // 4487C259F0F70977 99D90735
	static void SET_ENTITY_ANIM_SPEED(scrAny p0, scrAny *p1, scrAny *p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x28D1A16553C51776, p0, p1, p2, p3); } // 28D1A16553C51776 3990C90A
	static void SET_ENTITY_AS_MISSION_ENTITY(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xAD738C3085FE7E11, p0, p1, p2); } // AD738C3085FE7E11 5D1F9E0F
	static void SET_ENTITY_AS_NO_LONGER_NEEDED(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xB736A491E64A32CF, p0); } // B736A491E64A32CF ADF2267C
	static void SET_PED_AS_NO_LONGER_NEEDED(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x2595DD4236549CE3, p0); } // 2595DD4236549CE3 9A388380
	static void SET_VEHICLE_AS_NO_LONGER_NEEDED(scrVehicle *p0) { NativeInvoke::Invoke<scrVoid>(0x629BFA74418D6239, p0); } // 629BFA74418D6239 9B0E10BE
	static void SET_OBJECT_AS_NO_LONGER_NEEDED(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x3AE22DEB5BA5A3E6, p0); } // 3AE22DEB5BA5A3E6 3F6B949F
	static void SET_ENTITY_CAN_BE_DAMAGED(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x1760FFA8AB074D66, p0, p1); } // 1760FFA8AB074D66 60B6E744
	static void SET_ENTITY_CAN_BE_DAMAGED_BY_RELATIONSHIP_GROUP(scrAny p0, BOOL p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xE22D8FDE858B8119, p0, p1, p2); } // E22D8FDE858B8119 34165B5D
	static void SET_ENTITY_CAN_BE_TARGETED_WITHOUT_LOS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xD3997889736FD899, p0, p1); } // D3997889736FD899 3B13797C
	static void SET_ENTITY_COLLISION(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x1A9205C1B9EE827F, p0, p1, p2); } // 1A9205C1B9EE827F 139FD37D
	static BOOL _0xCCF1E97BEFDAE480(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xCCF1E97BEFDAE480, p0); } // CCF1E97BEFDAE480
	static void SET_ENTITY_COORDS(scrAny p0, float p1, float p2, float p3, BOOL p4, BOOL p5, BOOL p6, BOOL p7) { NativeInvoke::Invoke<scrVoid>(0x06843DA7060A026B, p0, p1, p2, p3, p4, p5, p6, p7); } // 06843DA7060A026B DF70B41B
	static void _0x621873ECE1178967(scrAny p0, float p1, float p2, float p3, BOOL p4, BOOL p5, BOOL p6, BOOL p7) { NativeInvoke::Invoke<scrVoid>(0x621873ECE1178967, p0, p1, p2, p3, p4, p5, p6, p7); } // 621873ECE1178967
	static void SET_ENTITY_COORDS_NO_OFFSET(scrAny p0, float p1, float p2, float p3, BOOL p4, BOOL p5, BOOL p6) { NativeInvoke::Invoke<scrVoid>(0x239A3351AC1DA385, p0, p1, p2, p3, p4, p5, p6); } // 239A3351AC1DA385 4C83DE8D
	static void SET_ENTITY_DYNAMIC(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x1718DE8E3F2823CA, p0, p1); } // 1718DE8E3F2823CA 236F525B
	static void SET_ENTITY_HEADING(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x8E2530AA8ADA980E, p0, p1); } // 8E2530AA8ADA980E E0FF064D
	static void SET_ENTITY_HEALTH(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x6B76DC1F3AE6E6A3, p0, p1); } // 6B76DC1F3AE6E6A3 FBCD1831
	static void SET_ENTITY_INVINCIBLE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x3882114BDE571AD4, p0, p1); } // 3882114BDE571AD4 C1213A21
	static void SET_ENTITY_IS_TARGET_PRIORITY(scrAny p0, BOOL p1, float p2) { NativeInvoke::Invoke<scrVoid>(0xEA02E132F5C68722, p0, p1, p2); } // EA02E132F5C68722 9729EE32
	static void SET_ENTITY_LIGHTS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x7CFBA6A80BDF3874, p0, p1); } // 7CFBA6A80BDF3874 E8FC85AF
	static void SET_ENTITY_LOAD_COLLISION_FLAG(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x0DC7CABAB1E9B67E, p0, p1); } // 0DC7CABAB1E9B67E C52F295B
	static BOOL _0xE9676F61BC0B3321(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xE9676F61BC0B3321, p0); } // E9676F61BC0B3321 851687F9
	static void SET_ENTITY_MAX_SPEED(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x0E46A3FCBDE2A1B1, p0, p1); } // 0E46A3FCBDE2A1B1 46AFFED3
	static void SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x79F020FF9EDC0748, p0, p1); } // 79F020FF9EDC0748 4B707F50
	static void SET_ENTITY_ONLY_DAMAGED_BY_RELATIONSHIP_GROUP(scrAny p0, BOOL p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x7022BD828FA0B082, p0, p1, p2); } // 7022BD828FA0B082 202237E2
	static void SET_ENTITY_PROOFS(scrAny p0, BOOL p1, BOOL p2, BOOL p3, BOOL p4, BOOL p5, BOOL p6, BOOL p7, BOOL p8) { NativeInvoke::Invoke<scrVoid>(0xFAEE099C6F890BB8, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // FAEE099C6F890BB8 7E9EAB66
	static void SET_ENTITY_QUATERNION(scrAny p0, float p1, float p2, float p3, float p4) { NativeInvoke::Invoke<scrVoid>(0x77B21BE7AC540F07, p0, p1, p2, p3, p4); } // 77B21BE7AC540F07 83B6046F
	static void SET_ENTITY_RECORDS_COLLISIONS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x0A50A1EEDAD01E65, p0, p1); } // 0A50A1EEDAD01E65 6B189A1A
	static void SET_ENTITY_ROTATION(scrAny p0, float p1, float p2, float p3, scrAny p4, BOOL p5) { NativeInvoke::Invoke<scrVoid>(0x8524A8B0171D5E07, p0, p1, p2, p3, p4, p5); } // 8524A8B0171D5E07 0A345EFE
	static void SET_ENTITY_VISIBLE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xEA1C610A04DB6BBB, p0, p1); } // EA1C610A04DB6BBB D043E8E1
	static void SET_ENTITY_VELOCITY(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x1C99BB7B6E96D16F, p0, p1, p2, p3); } // 1C99BB7B6E96D16F FF5A1988
	static void SET_ENTITY_HAS_GRAVITY(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x4A4722448F18EEF5, p0, p1); } // 4A4722448F18EEF5 E2F262BF
	static void SET_ENTITY_LOD_DIST(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x5927F96A78577363, p0, p1); } // 5927F96A78577363 D7ACC7AD
	static scrAny _0x4159C2762B5791D6(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x4159C2762B5791D6, p0); } // 4159C2762B5791D6 4DA3D51F
	static void SET_ENTITY_ALPHA(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x44A0870B7E92D7C0, p0, p1, p2); } // 44A0870B7E92D7C0 AE667CB0
	static scrAny GET_ENTITY_ALPHA(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x5A47B3B5E63E94C6, p0); } // 5A47B3B5E63E94C6 1560B017
	static void RESET_ENTITY_ALPHA(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x9B1E824FFBB7027A, p0); } // 9B1E824FFBB7027A 8A30761C
	static void _0x5C3B791D580E0BC2(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x5C3B791D580E0BC2, p0, p1); } // 5C3B791D580E0BC2
	static void _0xACAD101E1FB66689(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xACAD101E1FB66689, p0, p1); } // ACAD101E1FB66689 D8FF798A
	static void SET_ENTITY_RENDER_SCORCHED(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x730F5F8D3F0F2050, p0, p1); } // 730F5F8D3F0F2050 AAC9317B
	static void _0x57C5DB656185EAC4(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x57C5DB656185EAC4, p0, p1); } // 57C5DB656185EAC4 C47F5B91
	static void CREATE_MODEL_SWAP(float p0, float p1, float p2, float p3, scrAny p4, scrAny p5, BOOL p6) { NativeInvoke::Invoke<scrVoid>(0x92C47782FDA8B2A3, p0, p1, p2, p3, p4, p5, p6); } // 92C47782FDA8B2A3 0BC12F9E
	static void REMOVE_MODEL_SWAP(float p0, float p1, float p2, float p3, scrAny p4, scrAny p5, BOOL p6) { NativeInvoke::Invoke<scrVoid>(0x033C0F9A64E229AE, p0, p1, p2, p3, p4, p5, p6); } // 033C0F9A64E229AE CE0AA8BC
	static void CREATE_MODEL_HIDE(float p0, float p1, float p2, float p3, scrAny p4, BOOL p5) { NativeInvoke::Invoke<scrVoid>(0x8A97BCA30A0CE478, p0, p1, p2, p3, p4, p5); } // 8A97BCA30A0CE478 7BD5CF2F
	static void _0x3A52AE588830BF7F(float p0, float p1, float p2, float p3, scrAny p4, BOOL p5) { NativeInvoke::Invoke<scrVoid>(0x3A52AE588830BF7F, p0, p1, p2, p3, p4, p5); } // 3A52AE588830BF7F 07AAF22C
	static void REMOVE_MODEL_HIDE(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0xD9E3006FB3CBD765, p0, p1, p2, p3, p4, p5); } // D9E3006FB3CBD765 993DBC10
	static void CREATE_FORCED_OBJECT(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0x150E808B375A385A, p0, p1, p2, p3, p4, p5); } // 150E808B375A385A 335190A2
	static void REMOVE_FORCED_OBJECT(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x61B6775E83C0DB6F, p0, p1, p2, p3, p4); } // 61B6775E83C0DB6F AED73ADD
	static void SET_ENTITY_NO_COLLISION_ENTITY(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xA53ED5520C07654A, p0, p1, p2); } // A53ED5520C07654A 1E11BFE9
	static void SET_ENTITY_MOTION_BLUR(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x295D82A8559F9150, p0, p1); } // 295D82A8559F9150 E90005B8
	static void _0xE12ABE5E3A389A6C(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xE12ABE5E3A389A6C, p0, p1); } // E12ABE5E3A389A6C 44767B31
	static void _0xA80AE305E0A3044F(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xA80AE305E0A3044F, p0, p1); } // A80AE305E0A3044F E224A6A5
	static void _0x2C2E3DC128F44309(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x2C2E3DC128F44309, p0, p1); } // 2C2E3DC128F44309
	static void _0x1A092BB0C3808B96(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x1A092BB0C3808B96, p0, p1); } // 1A092BB0C3808B96
}

namespace PED
{
	static scrAny CREATE_PED(scrAny p0, scrAny p1, float p2, float p3, float p4, float p5, BOOL p6, BOOL p7) { return NativeInvoke::Invoke<scrAny>(0xD49F9B0955C367DE, p0, p1, p2, p3, p4, p5, p6, p7); } // D49F9B0955C367DE 0389EF71
	static void DELETE_PED(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x9614299DCB53E54B, p0); } // 9614299DCB53E54B 13EFB9A0
	static scrAny CLONE_PED(scrAny p0, BOOL p1, BOOL p2, BOOL p3) { return NativeInvoke::Invoke<scrAny>(0xEF29A16337FACADB, p0, p1, p2, p3); } // EF29A16337FACADB 8C8A8D6E
	static void _0xE952D6431689AD9A(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xE952D6431689AD9A, p0, p1); } // E952D6431689AD9A FC70EEC7
	static BOOL IS_PED_IN_VEHICLE(scrAny p0, scrAny p1, BOOL p2) { return NativeInvoke::Invoke<BOOL>(0xA3EE4A07279BB9DB, p0, p1, p2); } // A3EE4A07279BB9DB 7DA6BC83
	static BOOL IS_PED_IN_MODEL(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x796D90EFB19AA332, p0, p1); } // 796D90EFB19AA332 A6438D4B
	static BOOL IS_PED_IN_ANY_VEHICLE(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<BOOL>(0x997ABD671D25CA0B, p0, p1); } // 997ABD671D25CA0B 3B0171EE
	static BOOL IS_COP_PED_IN_AREA_3D(float p0, float p1, float p2, float p3, float p4, float p5) { return NativeInvoke::Invoke<BOOL>(0x16EC4839969F9F5E, p0, p1, p2, p3, p4, p5); } // 16EC4839969F9F5E B98DB96B
	static BOOL IS_PED_INJURED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x84A2DD9AC37C35C1, p0); } // 84A2DD9AC37C35C1 2530A087
	static BOOL IS_PED_HURT(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x5983BB449D7FDB12, p0); } // 5983BB449D7FDB12 69DFA0AF
	static BOOL IS_PED_FATALLY_INJURED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xD839450756ED5A80, p0); } // D839450756ED5A80 BADA0093
	static BOOL IS_PED_DEAD_OR_DYING(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<BOOL>(0x3317DEDB88C95038, p0, p1); } // 3317DEDB88C95038 CBDB7739
	static BOOL IS_CONVERSATION_PED_DEAD(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xE0A0AEC214B1FABA, p0); } // E0A0AEC214B1FABA 1FA39EFE
	static BOOL IS_PED_AIMING_FROM_COVER(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x3998B1276A3300E5, p0); } // 3998B1276A3300E5 DEBAB2AF
	static BOOL IS_PED_RELOADING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x24B100C68C645951, p0); } // 24B100C68C645951 961E1745
	static BOOL IS_PED_A_PLAYER(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x12534C348C6CB68B, p0); } // 12534C348C6CB68B 404794CA
	static scrAny CREATE_PED_INSIDE_VEHICLE(scrAny p0, scrAny p1, scrAny p2, scrAny p3, BOOL p4, BOOL p5) { return NativeInvoke::Invoke<scrAny>(0x7DD959874C1FD534, p0, p1, p2, p3, p4, p5); } // 7DD959874C1FD534 3000F092
	static void SET_PED_DESIRED_HEADING(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xAA5A7ECE2AA8FE70, p0, p1); } // AA5A7ECE2AA8FE70 961458F9
	static void _0xFF287323B0E2C69A(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xFF287323B0E2C69A, p0); } // FF287323B0E2C69A 290421BE
	static BOOL IS_PED_FACING_PED(scrAny p0, scrAny p1, float p2) { return NativeInvoke::Invoke<BOOL>(0xD71649DB0A545AA3, p0, p1, p2); } // D71649DB0A545AA3 0B775838
	static BOOL IS_PED_IN_MELEE_COMBAT(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x4E209B2C1EAD5159, p0); } // 4E209B2C1EAD5159 FD7814A5
	static BOOL IS_PED_STOPPED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x530944F6F4B8A214, p0); } // 530944F6F4B8A214 A0DC0B87
	static BOOL IS_PED_SHOOTING_IN_AREA(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, BOOL p7, BOOL p8) { return NativeInvoke::Invoke<BOOL>(0x7E9DFE24AC1E58EF, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 7E9DFE24AC1E58EF 741BF04F
	static BOOL IS_ANY_PED_SHOOTING_IN_AREA(float p0, float p1, float p2, float p3, float p4, float p5, BOOL p6, BOOL p7) { return NativeInvoke::Invoke<BOOL>(0xA0D3D71EA1086C55, p0, p1, p2, p3, p4, p5, p6, p7); } // A0D3D71EA1086C55 91833867
	static BOOL IS_PED_SHOOTING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x34616828CD07F1A1, p0); } // 34616828CD07F1A1 E7C3405E
	static void SET_PED_ACCURACY(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x7AEFB85C1D49DEB6, p0, p1); } // 7AEFB85C1D49DEB6 6C17122E
	static scrAny GET_PED_ACCURACY(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x37F4AD56ECBC0CD6, p0); } // 37F4AD56ECBC0CD6 0A2A0AA0
	static BOOL IS_PED_MODEL(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xC9D55B1A358A5BF7, p0, p1); } // C9D55B1A358A5BF7 5F1DDFCB
	static void EXPLODE_PED_HEAD(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x2D05CED3A38D0F3A, p0, p1); } // 2D05CED3A38D0F3A 05CC1380
	static void REMOVE_PED_ELEGANTLY(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xAC6D445B994DF95E, p0); } // AC6D445B994DF95E 4FFB8C6C
	static void ADD_ARMOUR_TO_PED(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x5BA652A0CD14DF2F, p0, p1); } // 5BA652A0CD14DF2F F686B26E
	static void SET_PED_ARMOUR(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xCEA04D83135264CC, p0, p1); } // CEA04D83135264CC 4E3A0CC4
	static void SET_PED_INTO_VEHICLE(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xF75B0D629E1C063D, p0, p1, p2); } // F75B0D629E1C063D 07500C79
	static void _0x3C028C636A414ED9(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x3C028C636A414ED9, p0, p1); } // 3C028C636A414ED9 58A80BD5
	static BOOL CAN_CREATE_RANDOM_PED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x3E8349C08E4B82E4, p0); } // 3E8349C08E4B82E4 F9ABE88F
	static scrAny CREATE_RANDOM_PED(float p0, float p1, float p2) { return NativeInvoke::Invoke<scrAny>(0xB4AC7D0CF06BFE8F, p0, p1, p2); } // B4AC7D0CF06BFE8F 5A949543
	static scrAny CREATE_RANDOM_PED_AS_DRIVER(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<scrAny>(0x9B62392B474F44A0, p0, p1); } // 9B62392B474F44A0 B927CE9A
	static BOOL CAN_CREATE_RANDOM_DRIVER() { return NativeInvoke::Invoke<BOOL>(0xB8EB95E5B4E56978); } // B8EB95E5B4E56978 99861609
	static BOOL _0xEACEEDA81751915C() { return NativeInvoke::Invoke<BOOL>(0xEACEEDA81751915C); } // EACEEDA81751915C 7018BE31
	static void SET_PED_MOVE_ANIMS_BLEND_OUT(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x9E8C908F41584ECD, p0); } // 9E8C908F41584ECD 20E01957
	static void SET_PED_CAN_BE_DRAGGED_OUT(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xC1670E958EEE24E5, p0, p1); } // C1670E958EEE24E5 AA7F1131
	static void _0xF2BEBCDFAFDAA19E(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xF2BEBCDFAFDAA19E, p0); } // F2BEBCDFAFDAA19E 6CD58238
	static BOOL IS_PED_MALE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x6D9F5FAA7488BA46, p0); } // 6D9F5FAA7488BA46 90950455
	static BOOL IS_PED_HUMAN(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xB980061DA992779D, p0); } // B980061DA992779D 194BB7B0
	static scrAny GET_VEHICLE_PED_IS_IN(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<scrAny>(0x9A9112A0FE9A4713, p0, p1); } // 9A9112A0FE9A4713 AFE92319
	static void RESET_PED_LAST_VEHICLE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xBB8DE8CF6A8DD8BB, p0); } // BB8DE8CF6A8DD8BB 5E3B5942
	static void SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(float p0) { NativeInvoke::Invoke<scrVoid>(0x95E3D6257B166CF2, p0); } // 95E3D6257B166CF2 039C82BB
	static void SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(float p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x7A556143A1C03898, p0, p1); } // 7A556143A1C03898 2909ABF0
	static void _0x5A7F62FDA59759BD() { NativeInvoke::Invoke<scrVoid>(0x5A7F62FDA59759BD); } // 5A7F62FDA59759BD B48C0C04
	static void _0x5086C7843552CF85(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x5086C7843552CF85, p0, p1, p2); } // 5086C7843552CF85 25EA2AA5
	static void SET_PED_NON_CREATION_AREA(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0xEE01041D559983EA, p0, p1, p2, p3, p4, p5); } // EE01041D559983EA 7A97283F
	static void CLEAR_PED_NON_CREATION_AREA() { NativeInvoke::Invoke<scrVoid>(0x2E05208086BA0651); } // 2E05208086BA0651 6F7043A3
	static void _0x4759CC730F947C81() { NativeInvoke::Invoke<scrVoid>(0x4759CC730F947C81); } // 4759CC730F947C81 8C555ADD
	static scrAny IS_PED_ON_MOUNT(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x460BC76A0E10655E, p0); } // 460BC76A0E10655E 43103006
	static scrAny GET_MOUNT(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xE7E11B8DCBED1058, p0); } // E7E11B8DCBED1058 DD31EC4E
	static BOOL IS_PED_ON_VEHICLE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x67722AEB798E5FAB, p0); } // 67722AEB798E5FAB A1AE7CC7
	static BOOL IS_PED_ON_SPECIFIC_VEHICLE(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xEC5F66E459AF3BB2, p0, p1); } // EC5F66E459AF3BB2 63CB4603
	static void SET_PED_MONEY(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xA9C8960E8684C1B5, p0, p1); } // A9C8960E8684C1B5 40D90BF2
	static scrAny GET_PED_MONEY(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x3F69145BBA87BAE7, p0); } // 3F69145BBA87BAE7 EB3C4C7E
	static void _0xFF4803BC019852D9(float p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xFF4803BC019852D9, p0, p1); } // FF4803BC019852D9 D41C9AED
	static void _0x6B0E6172C9A4D902(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x6B0E6172C9A4D902, p0); } // 6B0E6172C9A4D902 30B98369
	static void _0x9911F4A24485F653(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x9911F4A24485F653, p0); } // 9911F4A24485F653 02A080C8
	static void SET_PED_SUFFERS_CRITICAL_HITS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xEBD76F2359F190AC, p0, p1); } // EBD76F2359F190AC 6F6FC7E6
	static void _0xAFC976FD0580C7B3(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xAFC976FD0580C7B3, p0, p1); } // AFC976FD0580C7B3 1572022A
	static BOOL IS_PED_SITTING_IN_VEHICLE(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xA808AA1D79230FC2, p0, p1); } // A808AA1D79230FC2 DDDE26FA
	static BOOL IS_PED_SITTING_IN_ANY_VEHICLE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x826AA586EDB9FEF8, p0); } // 826AA586EDB9FEF8 0EA9CA03
	static BOOL IS_PED_ON_FOOT(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x01FEE67DB37F59B2, p0); } // 01FEE67DB37F59B2 C60D0785
	static BOOL IS_PED_ON_ANY_BIKE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x94495889E22C6479, p0); } // 94495889E22C6479 4D885B2E
	static BOOL IS_PED_PLANTING_BOMB(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xC70B5FAE151982D8, p0); } // C70B5FAE151982D8 0EDAC574
	static scrVector3 GET_DEAD_PED_PICKUP_COORDS(scrAny p0, float p1, float p2) { return NativeInvoke::Invoke<scrVector3>(0xCD5003B097200F36, p0, p1, p2); } // CD5003B097200F36 129F9DC1
	static BOOL IS_PED_IN_ANY_BOAT(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x2E0E1C2B4F6CB339, p0); } // 2E0E1C2B4F6CB339 1118A947
	static BOOL IS_PED_IN_ANY_SUB(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xFBFC01CCFB35D99E, p0); } // FBFC01CCFB35D99E E65F8059
	static BOOL IS_PED_IN_ANY_HELI(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x298B91AE825E5705, p0); } // 298B91AE825E5705 7AB5523B
	static BOOL IS_PED_IN_ANY_PLANE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x5FFF4CFC74D8FB80, p0); } // 5FFF4CFC74D8FB80 51BBCE7E
	static BOOL IS_PED_IN_FLYING_VEHICLE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x9134873537FA419C, p0); } // 9134873537FA419C CA072485
	static void SET_PED_DIES_IN_WATER(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x56CEF0AC79073BDE, p0, p1); } // 56CEF0AC79073BDE 604C872B
	static void SET_PED_DIES_IN_SINKING_VEHICLE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xD718A22995E2B4BC, p0, p1); } // D718A22995E2B4BC 8D4D9ABB
	static scrAny GET_PED_ARMOUR(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x9483AF821605B1D8, p0); } // 9483AF821605B1D8 2CE311A7
	static void SET_PED_STAY_IN_VEHICLE_WHEN_JACKED(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xEDF4079F9D54C9A1, p0, p1); } // EDF4079F9D54C9A1 B014A09C
	static void SET_PED_CAN_BE_SHOT_IN_VEHICLE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xC7EF1BA83230BA07, p0, p1); } // C7EF1BA83230BA07 5DB7B3A9
	static BOOL GET_PED_LAST_DAMAGE_BONE(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0xD75960F6BD9EA49C, p0, p1); } // D75960F6BD9EA49C AB933841
	static void CLEAR_PED_LAST_DAMAGE_BONE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x8EF6B7AC68E2F01B, p0); } // 8EF6B7AC68E2F01B 56CB715E
	static void SET_AI_WEAPON_DAMAGE_MODIFIER(float p0) { NativeInvoke::Invoke<scrVoid>(0x1B1E2A40A65B8521, p0); } // 1B1E2A40A65B8521 516E30EE
	static void RESET_AI_WEAPON_DAMAGE_MODIFIER() { NativeInvoke::Invoke<scrVoid>(0xEA16670E7BA4743C); } // EA16670E7BA4743C 6E965420
	static void _0x66460DEDDD417254(float p0) { NativeInvoke::Invoke<scrVoid>(0x66460DEDDD417254, p0); } // 66460DEDDD417254 0F9A401F
	static void _0x46E56A7CD1D63C3F() { NativeInvoke::Invoke<scrVoid>(0x46E56A7CD1D63C3F); } // 46E56A7CD1D63C3F 97886238
	static void _0x2F3C3D9F50681DE4(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x2F3C3D9F50681DE4, p0, p1); } // 2F3C3D9F50681DE4 CC9D7F1A
	static void SET_PED_CAN_BE_TARGETTED(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x63F58F7C80513AAD, p0, p1); } // 63F58F7C80513AAD 75C49F74
	static void SET_PED_CAN_BE_TARGETTED_BY_TEAM(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xBF1CA77833E58F2C, p0, p1, p2); } // BF1CA77833E58F2C B103A8E1
	static void SET_PED_CAN_BE_TARGETTED_BY_PLAYER(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x66B57B72E0836A76, p0, p1, p2); } // 66B57B72E0836A76 D050F490
	static void _0x061CB768363D6424(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x061CB768363D6424, p0, p1); } // 061CB768363D6424 7DA12905
	static void SET_TIME_EXCLUSIVE_DISPLAY_TEXTURE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xFD325494792302D7, p0, p1); } // FD325494792302D7 7F67671D
	static BOOL IS_PED_IN_ANY_POLICE_VEHICLE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x0BD04E29640C9C12, p0); } // 0BD04E29640C9C12 84FA790D
	static void _0x16E42E800B472221(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x16E42E800B472221, p0); } // 16E42E800B472221 A819680B
	static BOOL _0x7DCE8BDA0F1C1200(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x7DCE8BDA0F1C1200, p0); } // 7DCE8BDA0F1C1200 CD71F11B
	static BOOL IS_PED_FALLING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xFB92A102F1C4DFA3, p0); } // FB92A102F1C4DFA3 ABF77334
	static BOOL IS_PED_JUMPING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xCEDABC5900A0BF97, p0); } // CEDABC5900A0BF97 07E5BC0E
	static BOOL IS_PED_CLIMBING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x53E8CB4F48BFE623, p0); } // 53E8CB4F48BFE623 BCE03D35
	static BOOL _0x117C70D1F5730B5E(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x117C70D1F5730B5E, p0); } // 117C70D1F5730B5E C3169BDA
	static BOOL IS_PED_DIVING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x5527B8246FEF9B11, p0); } // 5527B8246FEF9B11 7BC5BF3C
	static BOOL _0x433DDFFE2044B636(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x433DDFFE2044B636, p0); } // 433DDFFE2044B636 B19215F6
	static scrAny GET_PED_PARACHUTE_STATE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x79CFD9827CC979B6, p0); } // 79CFD9827CC979B6 7D4BC475
	static scrAny _0x8B9F1FC6AE8166C0(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x8B9F1FC6AE8166C0, p0); } // 8B9F1FC6AE8166C0 01F3B035
	static void SET_PED_PARACHUTE_TINT_INDEX(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x333FC8DB079B7186, p0, p1); } // 333FC8DB079B7186 5AEFEC3A
	static void GET_PED_PARACHUTE_TINT_INDEX(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xEAF5F7E5AE7C6C9D, p0, p1); } // EAF5F7E5AE7C6C9D E9E7FAC5
	static void _0xE88DA0751C22A2AD(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xE88DA0751C22A2AD, p0, p1); } // E88DA0751C22A2AD 177EFC79
	static void SET_PED_DUCKING(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x030983CA930B692D, p0, p1); } // 030983CA930B692D B90353D7
	static BOOL IS_PED_DUCKING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xD125AE748725C6BC, p0); } // D125AE748725C6BC 9199C77D
	static BOOL IS_PED_IN_ANY_TAXI(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x6E575D6A898AB852, p0); } // 6E575D6A898AB852 16FD386C
	static void SET_PED_ID_RANGE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xF107E836A70DCE05, p0, p1); } // F107E836A70DCE05 EF3B4ED9
	static void _0x52D59AB61DDC05DD(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x52D59AB61DDC05DD, p0, p1); } // 52D59AB61DDC05DD 9A2180FF
	static void _0xEC4B4B3B9908052A(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xEC4B4B3B9908052A, p0, p1); } // EC4B4B3B9908052A F30658D2
	static void _0x733C87D4CE22BEA2(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x733C87D4CE22BEA2, p0); } // 733C87D4CE22BEA2 43709044
	static void SET_PED_SEEING_RANGE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xF29CF591C4BF6CEE, p0, p1); } // F29CF591C4BF6CEE 4BD72FE8
	static void SET_PED_HEARING_RANGE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x33A8F7F7D5F7F33C, p0, p1); } // 33A8F7F7D5F7F33C B32087E0
	static void SET_PED_VISUAL_FIELD_MIN_ANGLE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x2DB492222FB21E26, p0, p1); } // 2DB492222FB21E26 72E2E18B
	static void SET_PED_VISUAL_FIELD_MAX_ANGLE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x70793BDCA1E854D4, p0, p1); } // 70793BDCA1E854D4 0CEA0F9A
	static void SET_PED_VISUAL_FIELD_MIN_ELEVATION_ANGLE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x7A276EB2C224D70F, p0, p1); } // 7A276EB2C224D70F 5CC2F1B8
	static void SET_PED_VISUAL_FIELD_MAX_ELEVATION_ANGLE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x78D0B67629D75856, p0, p1); } // 78D0B67629D75856 39D9102F
	static void _0x9C74B0BC831B753A(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x9C74B0BC831B753A, p0, p1); } // 9C74B0BC831B753A FDF2F7C2
	static void _0x3B6405E8AB34A907(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x3B6405E8AB34A907, p0, p1); } // 3B6405E8AB34A907 E57202A1
	static void SET_PED_STEALTH_MOVEMENT(scrAny p0, BOOL p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0x88CBB5CEB96B7BD2, p0, p1, p2); } // 88CBB5CEB96B7BD2 67E28E1D
	static BOOL GET_PED_STEALTH_MOVEMENT(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x7C2AC9CA66575FBF, p0); } // 7C2AC9CA66575FBF 40321B83
	static scrAny CREATE_GROUP(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x90370EBE0FEE1A3D, p0); } // 90370EBE0FEE1A3D 8DC0368D
	static void SET_PED_AS_GROUP_LEADER(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x2A7819605465FBCE, p0, p1); } // 2A7819605465FBCE 7265BEA2
	static void SET_PED_AS_GROUP_MEMBER(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x9F3480FE65DB31B5, p0, p1); } // 9F3480FE65DB31B5 0EE13F92
	static void _0x2E2F4240B3F24647(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x2E2F4240B3F24647, p0, p1, p2); } // 2E2F4240B3F24647 D0D8BDBC
	static void REMOVE_GROUP(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x8EB2F69076AF7053, p0); } // 8EB2F69076AF7053 48D72B88
	static void REMOVE_PED_FROM_GROUP(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xED74007FFB146BC2, p0); } // ED74007FFB146BC2 82697713
	static BOOL IS_PED_GROUP_MEMBER(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x9BB01E3834671191, p0, p1); } // 9BB01E3834671191 876D5363
	static BOOL _0x1C86D8AEF8254B78(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x1C86D8AEF8254B78, p0); } // 1C86D8AEF8254B78 9678D4FF
	static void SET_GROUP_SEPARATION_RANGE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x4102C7858CFEE4E4, p0, p1); } // 4102C7858CFEE4E4 7B820CD5
	static void _0xFA0675AB151073FA(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xFA0675AB151073FA, p0, p1); } // FA0675AB151073FA 2F0D0973
	static BOOL IS_PED_PRONE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xD6A86331A537A7B9, p0); } // D6A86331A537A7B9 02C2A6C3
	static BOOL IS_PED_IN_COMBAT(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x4859F1FC66A6278E, p0, p1); } // 4859F1FC66A6278E FE027CB5
	static BOOL _0xEAD42DE3610D0721(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xEAD42DE3610D0721, p0, p1); } // EAD42DE3610D0721 CCD525E1
	static BOOL IS_PED_DOING_DRIVEBY(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xB2C086CC1BF8F2BF, p0); } // B2C086CC1BF8F2BF AC3CEB9C
	static BOOL IS_PED_JACKING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x4AE4FF911DFB61DA, p0); } // 4AE4FF911DFB61DA 3B321816
	static BOOL IS_PED_BEING_JACKED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x9A497FE2DF198913, p0); } // 9A497FE2DF198913 D45D605C
	static BOOL IS_PED_BEING_STUNNED(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x4FBACCE3B4138EE8, p0, p1); } // 4FBACCE3B4138EE8 0A66CE30
	static scrAny GET_PEDS_JACKER(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x9B128DC36C1E04CF, p0); } // 9B128DC36C1E04CF DE1DBB59
	static scrAny GET_JACK_TARGET(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x5486A79D9FBD342D, p0); } // 5486A79D9FBD342D 1D196361
	static BOOL IS_PED_FLEEING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xBBCCE00B381F8482, p0); } // BBCCE00B381F8482 85D813C6
	static BOOL IS_PED_IN_COVER(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<BOOL>(0x60DFD0691A170B88, p0, p1); } // 60DFD0691A170B88 972C5A8B
	static BOOL IS_PED_IN_COVER_FACING_LEFT(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x845333B3150583AB, p0); } // 845333B3150583AB B89DBB80
	static BOOL IS_PED_GOING_INTO_COVER(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x9F65DBC537E59AD5, p0); } // 9F65DBC537E59AD5 A3589628
	static scrAny SET_PED_PINNED_DOWN(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0xAAD6D1ACF08F4612, p0, p1, p2); } // AAD6D1ACF08F4612 CC78999D
	static scrAny _0x6F4C85ACD641BCD2(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x6F4C85ACD641BCD2, p0); } // 6F4C85ACD641BCD2 ACF162E0
	static scrAny _0x814FA8BE5449445D(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x814FA8BE5449445D, p0); } // 814FA8BE5449445D 99968B37
	static scrAny _0x93C8B64DEB84728C(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x93C8B64DEB84728C, p0); } // 93C8B64DEB84728C 84ADF9EB
	static scrAny GET_PED_CAUSE_OF_DEATH(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x16FFE42AB2D2DC59, p0); } // 16FFE42AB2D2DC59 63458C27
	static scrAny _0x5407B7288D0478B7(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x5407B7288D0478B7, p0); } // 5407B7288D0478B7 EF0B78E6
	static scrAny _0x336B3D200AB007CB(scrAny p0, float p1, float p2, float p3, float p4) { return NativeInvoke::Invoke<scrAny>(0x336B3D200AB007CB, p0, p1, p2, p3, p4); } // 336B3D200AB007CB FB18CB19
	static void SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xADB3F206518799E8, p0, p1); } // ADB3F206518799E8 423B7BA2
	static void SET_PED_RELATIONSHIP_GROUP_HASH(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xC80A74AC829DDD92, p0, p1); } // C80A74AC829DDD92 79F8C18C
	static void SET_RELATIONSHIP_BETWEEN_GROUPS(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xBF25EB89375A37AD, p0, p1, p2); } // BF25EB89375A37AD D4A215BA
	static void CLEAR_RELATIONSHIP_BETWEEN_GROUPS(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x5E29243FB56FC6D4, p0, p1, p2); } // 5E29243FB56FC6D4 994B8C2D
	static scrAny ADD_RELATIONSHIP_GROUP(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xF372BC22FCB88606, p0, p1); } // F372BC22FCB88606 8B635546
	static void REMOVE_RELATIONSHIP_GROUP(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xB6BA2444AB393DA2, p0); } // B6BA2444AB393DA2 4A1DC59A
	static scrAny GET_RELATIONSHIP_BETWEEN_PEDS(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xEBA5AD3A0EAF7121, p0, p1); } // EBA5AD3A0EAF7121 E254C39C
	static scrAny GET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x42FDD0F017B1E38E, p0); } // 42FDD0F017B1E38E 714BD6E4
	static scrAny GET_PED_RELATIONSHIP_GROUP_HASH(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x7DBDD04862D95F04, p0); } // 7DBDD04862D95F04 354F283C
	static scrAny GET_RELATIONSHIP_BETWEEN_GROUPS(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x9E6B70061662AE5C, p0, p1); } // 9E6B70061662AE5C 4E372FE2
	static void SET_PED_CAN_BE_TARGETED_WITHOUT_LOS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x4328652AE5769C71, p0, p1); } // 4328652AE5769C71 7FDDC0A6
	static void SET_PED_TO_INFORM_RESPECTED_FRIENDS(scrAny p0, float p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x112942C6E708F70B, p0, p1, p2); } // 112942C6E708F70B D78AC46C
	static BOOL IS_PED_RESPONDING_TO_EVENT(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x625B774D75C87068, p0, p1); } // 625B774D75C87068 7A877554
	static void SET_PED_FIRING_PATTERN(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x9AC577F5A12AD8A9, p0, p1); } // 9AC577F5A12AD8A9 B4629D66
	static void SET_PED_SHOOT_RATE(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x614DA022990752DC, p0, p1); } // 614DA022990752DC FB301746
	static void SET_COMBAT_FLOAT(scrAny p0, scrAny p1, float p2) { NativeInvoke::Invoke<scrVoid>(0xFF41B4B141ED981C, p0, p1, p2); } // FF41B4B141ED981C D8B7637C
	static float GET_COMBAT_FLOAT(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<float>(0x52DFF8A10508090A, p0, p1); } // 52DFF8A10508090A 511D7EF8
	static void GET_GROUP_SIZE(scrAny p0, scrAny *p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0x8DE69FE35CA09A45, p0, p1, p2); } // 8DE69FE35CA09A45 F7E1A691
	static BOOL DOES_GROUP_EXIST(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x7C6B0C22F9F40BBE, p0); } // 7C6B0C22F9F40BBE 935C978D
	static scrAny GET_PED_GROUP_INDEX(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xF162E133B4E7A675, p0); } // F162E133B4E7A675 134E0785
	static BOOL IS_PED_IN_GROUP(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x5891CAC5D4ACFF74, p0); } // 5891CAC5D4ACFF74 836D9795
	static scrAny _0x6A3975DEA89F9A17(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x6A3975DEA89F9A17, p0); } // 6A3975DEA89F9A17 DE7442EE
	static void SET_GROUP_FORMATION(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xCE2F5FC3AF7E8C1E, p0, p1); } // CE2F5FC3AF7E8C1E 08FAC739
	static void SET_GROUP_FORMATION_SPACING(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x1D9D45004C28C916, p0, p1, p2, p3); } // 1D9D45004C28C916 B1E086FF
	static void _0x63DAB4CCB3273205(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x63DAB4CCB3273205, p0); } // 63DAB4CCB3273205 267FCEAD
	static scrAny GET_VEHICLE_PED_IS_USING(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x6094AD011A2EA87D, p0); } // 6094AD011A2EA87D 6DE3AADA
	static scrAny SET_EXCLUSIVE_PHONE_RELATIONSHIPS(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xF92691AED837A5FC, p0); } // F92691AED837A5FC 56E0C163
	static void SET_PED_GRAVITY(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x9FF447B6B6AD960A, p0, p1); } // 9FF447B6B6AD960A 3CA16652
	static void APPLY_DAMAGE_TO_PED(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x697157CED63F18D4, p0, p1, p2); } // 697157CED63F18D4 4DC27FCF
	static void SET_PED_ALLOWED_TO_DUCK(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xDA1F1B7BE1A8766F, p0, p1); } // DA1F1B7BE1A8766F C4D122F8
	static void SET_PED_NEVER_LEAVES_GROUP(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x3DBFC55D5C9BB447, p0, p1); } // 3DBFC55D5C9BB447 0E038813
	static scrAny GET_PED_TYPE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xFF059E1E4C01E63C, p0); } // FF059E1E4C01E63C B1460D43
	static void SET_PED_AS_COP(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xBB03C38DD3FB7FFD, p0, p1); } // BB03C38DD3FB7FFD 84E7DE9F
	static void SET_PED_MAX_HEALTH(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xF5F6378C4F3419D3, p0, p1); } // F5F6378C4F3419D3 5533F60B
	static scrAny GET_PED_MAX_HEALTH(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x4700A416E8324EF3, p0); } // 4700A416E8324EF3 A45B6C8D
	static void SET_PED_MAX_TIME_IN_WATER(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x43C851690662113D, p0, p1); } // 43C851690662113D FE0A106B
	static void SET_PED_MAX_TIME_UNDERWATER(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x6BA428C528D9E522, p0, p1); } // 6BA428C528D9E522 082EF240
	static void _0x2735233A786B1BEF(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x2735233A786B1BEF, p0, p1); } // 2735233A786B1BEF 373CC405
	static void SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x7A6535691B477C48, p0, p1); } // 7A6535691B477C48 8A251612
	static BOOL _0x51AC07A44D4F5B8A(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x51AC07A44D4F5B8A, p0); } // 51AC07A44D4F5B8A C9D098B3
	static void KNOCK_PED_OFF_VEHICLE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x45BBCBA77C29A841, p0); } // 45BBCBA77C29A841 ACDD0674
	static void SET_PED_COORDS_NO_GANG(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x87052FE446E07247, p0, p1, p2, p3); } // 87052FE446E07247 9561AD98
	static scrAny GET_PED_AS_GROUP_MEMBER(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x51455483CF23ED97, p0, p1); } // 51455483CF23ED97 9AA3CC8C
	static void SET_PED_KEEP_TASK(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x971D38760FBC02EF, p0, p1); } // 971D38760FBC02EF A7EC79CE
	static void _0x49E50BDB8BA4DAB2(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x49E50BDB8BA4DAB2, p0, p1); } // 49E50BDB8BA4DAB2 397F06E3
	static BOOL IS_PED_SWIMMING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x9DE327631295B4C2, p0); } // 9DE327631295B4C2 7AB43DB8
	static BOOL IS_PED_SWIMMING_UNDER_WATER(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xC024869A53992F34, p0); } // C024869A53992F34 0E8D524F
	static void SET_PED_COORDS_KEEP_VEHICLE(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x9AFEFF481A85AB2E, p0, p1, p2, p3); } // 9AFEFF481A85AB2E D66AE1D3
	static void SET_PED_DIES_IN_VEHICLE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x2A30922C90C9B42C, p0, p1); } // 2A30922C90C9B42C 6FE1E440
	static void SET_CREATE_RANDOM_COPS(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x102E68B2024D536D, p0); } // 102E68B2024D536D 23441648
	static void _0x8A4986851C4EF6E7(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x8A4986851C4EF6E7, p0); } // 8A4986851C4EF6E7 82E548CC
	static void _0x444CB7D7DBE6973D(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x444CB7D7DBE6973D, p0); } // 444CB7D7DBE6973D EDC31475
	static BOOL CAN_CREATE_RANDOM_COPS() { return NativeInvoke::Invoke<BOOL>(0x5EE2CAFF7F17770D); } // 5EE2CAFF7F17770D AA73DAD9
	static void SET_PED_AS_ENEMY(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x02A0C9720B854BFA, p0, p1); } // 02A0C9720B854BFA AE620A1B
	static void SET_PED_CAN_SMASH_GLASS(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x1CCE141467FF42A2, p0, p1, p2); } // 1CCE141467FF42A2 149C60A8
	static BOOL IS_PED_IN_ANY_TRAIN(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x6F972C1AB75A1ED0, p0); } // 6F972C1AB75A1ED0 759EF63A
	static BOOL IS_PED_GETTING_INTO_A_VEHICLE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xBB062B2B5722478E, p0); } // BB062B2B5722478E 90E805AC
	static BOOL IS_PED_TRYING_TO_ENTER_A_LOCKED_VEHICLE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x44D28D5DDFE5F68C, p0); } // 44D28D5DDFE5F68C 46828B4E
	static void SET_ENABLE_HANDCUFFS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xDF1AF8B5D56542FA, p0, p1); } // DF1AF8B5D56542FA AC9BBA23
	static void SET_ENABLE_BOUND_ANKLES(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xC52E0F855C58FC2E, p0, p1); } // C52E0F855C58FC2E 9208D689
	static void _0xF99F62004024D506(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xF99F62004024D506, p0, p1); } // F99F62004024D506 7BF61471
	static void SET_CAN_ATTACK_FRIENDLY(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xB3B1CB349FF9C75D, p0, p1, p2); } // B3B1CB349FF9C75D 47C60963
	static scrAny GET_PED_ALERTNESS(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xF6AA118530443FD2, p0); } // F6AA118530443FD2 F83E4DAF
	static void SET_PED_ALERTNESS(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xDBA71115ED9941A6, p0, p1); } // DBA71115ED9941A6 2C32D9AE
	static void SET_PED_GET_OUT_UPSIDE_DOWN_VEHICLE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xBC0ED94165A48BC2, p0, p1); } // BC0ED94165A48BC2 89AD49FF
	static void SET_PED_MOVEMENT_CLIPSET(scrAny p0, scrAny *p1, float p2) { NativeInvoke::Invoke<scrVoid>(0xAF8A94EDE7712BEF, p0, p1, p2); } // AF8A94EDE7712BEF A817CDEB
	static void RESET_PED_MOVEMENT_CLIPSET(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xAA74EC0CB0AAEA2C, p0, p1); } // AA74EC0CB0AAEA2C B83CEE93
	static void SET_PED_STRAFE_CLIPSET(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x29A28F3F8CF6D854, p0, p1); } // 29A28F3F8CF6D854 0BACF010
	static void RESET_PED_STRAFE_CLIPSET(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x20510814175EA477, p0); } // 20510814175EA477 F1967A12
	static void SET_PED_WEAPON_MOVEMENT_CLIPSET(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x2622E35B77D3ACA2, p0, p1); } // 2622E35B77D3ACA2 F8BE54DC
	static void RESET_PED_WEAPON_MOVEMENT_CLIPSET(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x97B0DB5B4AA74E77, p0); } // 97B0DB5B4AA74E77 C60C9ACD
	static void _0xED34AB6C5CB36520(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xED34AB6C5CB36520, p0, p1); } // ED34AB6C5CB36520 D4C73595
	static void _0x4AFE3690D7E0B5AC(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x4AFE3690D7E0B5AC, p0); } // 4AFE3690D7E0B5AC AEC9163B
	static void SET_PED_IN_VEHICLE_CONTEXT(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x530071295899A8C6, p0, p1); } // 530071295899A8C6 27F25C0E
	static void RESET_PED_IN_VEHICLE_CONTEXT(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x22EF8FF8778030EB, p0); } // 22EF8FF8778030EB 3C94D88A
	static BOOL _0x6EC47A344923E1ED(scrAny p0, scrAny *p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0x6EC47A344923E1ED, p0, p1, p2); } // 6EC47A344923E1ED 3C30B447
	static void _0x6C60394CB4F75E9A(scrAny p0, scrAny *p1, scrAny *p2, float p3, BOOL p4) { NativeInvoke::Invoke<scrVoid>(0x6C60394CB4F75E9A, p0, p1, p2, p3, p4); } // 6C60394CB4F75E9A 895E1D67
	static void _0x8844BBFCE30AA9E9(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x8844BBFCE30AA9E9, p0, p1); } // 8844BBFCE30AA9E9 5736FB23
	static void SET_PED_ALTERNATE_MOVEMENT_ANIM(scrAny p0, scrAny p1, scrAny *p2, scrAny *p3, float p4, BOOL p5) { NativeInvoke::Invoke<scrVoid>(0x90A43CC281FFAB46, p0, p1, p2, p3, p4, p5); } // 90A43CC281FFAB46 BA84FD8C
	static void CLEAR_PED_ALTERNATE_MOVEMENT_ANIM(scrAny p0, scrAny p1, float p2) { NativeInvoke::Invoke<scrVoid>(0xD8D19675ED5FBDCE, p0, p1, p2); } // D8D19675ED5FBDCE 7A7F5BC3
	static void SET_PED_GESTURE_GROUP(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xDDF803377F94AAA8, p0, p1); } // DDF803377F94AAA8 170DA109
	static scrVector3 _0xBE22B26DD764C040(scrAny *p0, scrAny *p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, scrAny p9) { return NativeInvoke::Invoke<scrVector3>(0xBE22B26DD764C040, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // BE22B26DD764C040 C59D4268
	static scrVector3 _0x4B805E6046EE9E47(scrAny *p0, scrAny *p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, scrAny p9) { return NativeInvoke::Invoke<scrVector3>(0x4B805E6046EE9E47, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 4B805E6046EE9E47 5F7789E6
	static scrAny GET_PED_DRAWABLE_VARIATION(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x67F3780DD425D4FC, p0, p1); } // 67F3780DD425D4FC 29850FE2
	static scrAny GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x27561561732A7842, p0, p1); } // 27561561732A7842 9754C27D
	static scrAny GET_PED_TEXTURE_VARIATION(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x04A355E041E004E6, p0, p1); } // 04A355E041E004E6 C0A8590A
	static scrAny GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0x8F7156A3142A6BAD, p0, p1, p2); } // 8F7156A3142A6BAD 83D9FBE7
	static scrAny _0x5FAF9754E789FB47(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x5FAF9754E789FB47, p0, p1); } // 5FAF9754E789FB47 C9780B95
	static scrAny REMOVE_NIGHTVISION_MELEE(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0xA6E7F1CEB523E171, p0, p1, p2); } // A6E7F1CEB523E171 4892B882
	static BOOL GET_PED_PALETTE_VARIATION(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xE3DD5F2A84B42281, p0, p1); } // E3DD5F2A84B42281 EF1BC082
	static BOOL IS_PED_COMPONENT_VARIATION_VALID(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<BOOL>(0xE825F6B6CEA7671D, p0, p1, p2, p3); } // E825F6B6CEA7671D 952ABD9A
	static void SET_PED_COMPONENT_VARIATION(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x262B14F48D29DE80, p0, p1, p2, p3, p4); } // 262B14F48D29DE80 D4F7B05C
	static void SET_PED_RANDOM_COMPONENT_VARIATION(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xC8A9481A01E63C28, p0, p1); } // C8A9481A01E63C28 4111BA46
	static void SET_PED_RANDOM_PROPS(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xC44AA05345C992C6, p0); } // C44AA05345C992C6 E3318E0E
	static void SET_PED_DEFAULT_COMPONENT_VARIATION(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x45EEE61580806D63, p0); } // 45EEE61580806D63 C866A984
	static void SET_PED_BLEND_FROM_PARENTS(scrAny p0, scrAny p1, scrAny p2, float p3, float p4) { NativeInvoke::Invoke<scrVoid>(0x137BBD05230DB22D, p0, p1, p2, p3, p4); } // 137BBD05230DB22D 837BD370
	static void SET_PED_HEAD_BLEND_DATA(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, float p7, float p8, float p9, BOOL p10) { NativeInvoke::Invoke<scrVoid>(0x9414E18B9434C2FE, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 9414E18B9434C2FE 60746B88
	static BOOL _0x2746BD9D88C5C5D0(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x2746BD9D88C5C5D0, p0, p1); } // 2746BD9D88C5C5D0
	static void UPDATE_PED_HEAD_BLEND_DATA(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x723538F61C647C5A, p0, p1, p2, p3); } // 723538F61C647C5A 5CB76219
	static void _0x50B56988B170AFDF(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x50B56988B170AFDF, p0, p1); } // 50B56988B170AFDF
	static void SET_PED_HEAD_OVERLAY(scrAny p0, scrAny p1, scrAny p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x48F44967FA05CC1E, p0, p1, p2, p3); } // 48F44967FA05CC1E D28DBA90
	static scrAny _0xCF1CE768BB43480E(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xCF1CE768BB43480E, p0); } // CF1CE768BB43480E FF43C18D
	static void _0x71A5C1DBA060049E(scrAny p0, scrAny p1, float p2) { NativeInvoke::Invoke<scrVoid>(0x71A5C1DBA060049E, p0, p1, p2); } // 71A5C1DBA060049E
	static BOOL HAS_PED_HEAD_BLEND_FINISHED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x654CD0A825161131, p0); } // 654CD0A825161131 2B1BD9C5
	static void _0x4668D80430D6C299(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x4668D80430D6C299, p0); } // 4668D80430D6C299 894314A4
	static void _0xCC9682B8951C5229(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0xCC9682B8951C5229, p0, p1, p2, p3, p4); } // CC9682B8951C5229 57E5B3F9
	static void _0xA21C118553BBDF02(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA21C118553BBDF02, p0); } // A21C118553BBDF02 C6F36292
	static scrAny _0x68D353AB88B97E0C(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x68D353AB88B97E0C, p0); } // 68D353AB88B97E0C 211DEFEC
	static scrAny _0x5EF37013A6539C9D(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x5EF37013A6539C9D, p0); } // 5EF37013A6539C9D 095D3BD8
	static scrAny _0x39D55A620FCB6A3A(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0x39D55A620FCB6A3A, p0, p1, p2, p3); } // 39D55A620FCB6A3A 45F3BDFB
	static BOOL _0x66680A92700F43DF(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x66680A92700F43DF, p0); } // 66680A92700F43DF C6517D52
	static void _0x5AAB586FFEC0FD96(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x5AAB586FFEC0FD96, p0); } // 5AAB586FFEC0FD96 6435F67F
	static scrAny _0x2B16A3BFF1FBCE49(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0x2B16A3BFF1FBCE49, p0, p1, p2, p3); } // 2B16A3BFF1FBCE49 C0E23671
	static BOOL _0x784002A632822099(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x784002A632822099, p0); } // 784002A632822099 3B0CA391
	static void _0xF79F9DEF0AADE61A(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xF79F9DEF0AADE61A, p0); } // F79F9DEF0AADE61A FD103BA7
	static scrAny GET_PED_PROP_INDEX(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x898CC20EA75BACD8, p0, p1); } // 898CC20EA75BACD8 746DDAC0
	static void SET_PED_PROP_INDEX(scrAny p0, scrAny p1, scrAny p2, scrAny p3, BOOL p4) { NativeInvoke::Invoke<scrVoid>(0x93376B65A266EB5F, p0, p1, p2, p3, p4); } // 93376B65A266EB5F 0829F2E2
	static void KNOCK_OFF_PED_PROP(scrAny p0, BOOL p1, BOOL p2, BOOL p3, BOOL p4) { NativeInvoke::Invoke<scrVoid>(0x6FD7816A36615F48, p0, p1, p2, p3, p4); } // 6FD7816A36615F48 08D8B180
	static void CLEAR_PED_PROP(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x0943E5B8E078E76E, p0, p1); } // 0943E5B8E078E76E 2D23D743
	static void CLEAR_ALL_PED_PROPS(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xCD8A7537A9B52F06, p0); } // CD8A7537A9B52F06 81DF8B43
	static scrAny GET_PED_PROP_TEXTURE_INDEX(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xE131A28626F81AB2, p0, p1); } // E131A28626F81AB2 922A6653
	static void _0x1280804F7CFD2D6C(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x1280804F7CFD2D6C, p0); } // 1280804F7CFD2D6C 7BCD8991
	static void _0xB50EB4CCB29704AC(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xB50EB4CCB29704AC, p0); } // B50EB4CCB29704AC 080275EE
	static void SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x9F8AA94D6D97DBF4, p0, p1); } // 9F8AA94D6D97DBF4 DFE34E4A
	static void SET_PED_BOUNDS_ORIENTATION(scrAny p0, float p1, float p2, float p3, float p4, float p5) { NativeInvoke::Invoke<scrVoid>(0x4F5F651ACCC9C4CF, p0, p1, p2, p3, p4, p5); } // 4F5F651ACCC9C4CF CFA20D68
	static void REGISTER_TARGET(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x2F25D9AEFA34FBA2, p0, p1); } // 2F25D9AEFA34FBA2 50A95442
	static void REGISTER_HATED_TARGETS_AROUND_PED(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x9222F300BF8354FE, p0, p1); } // 9222F300BF8354FE 7F87559E
	static scrAny GET_RANDOM_PED_AT_COORD(float p0, float p1, float p2, float p3, float p4, float p5, scrAny p6) { return NativeInvoke::Invoke<scrAny>(0x876046A8E3A4B71C, p0, p1, p2, p3, p4, p5, p6); } // 876046A8E3A4B71C DC8239EB
	static BOOL GET_CLOSEST_PED(float p0, float p1, float p2, float p3, BOOL p4, BOOL p5, scrAny *p6, BOOL p7, BOOL p8, scrAny p9) { return NativeInvoke::Invoke<BOOL>(0xC33AB876A77F8164, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // C33AB876A77F8164 8F6C1F55
	static void SET_SCENARIO_PEDS_TO_BE_RETURNED_BY_NEXT_COMMAND(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x14F19A8782C8071E, p0); } // 14F19A8782C8071E 85615FD0
	static BOOL _0x03EA03AF85A85CB7(scrAny p0, BOOL p1, BOOL p2, BOOL p3, BOOL p4, BOOL p5, BOOL p6, BOOL p7, scrAny p8) { return NativeInvoke::Invoke<BOOL>(0x03EA03AF85A85CB7, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 03EA03AF85A85CB7 18DD76A1
	static void _0xDED5AF5A0EA4B297(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xDED5AF5A0EA4B297, p0, p1); } // DED5AF5A0EA4B297 6D55B3B3
	static void SET_DRIVER_ABILITY(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xB195FFA8042FC5C3, p0, p1); } // B195FFA8042FC5C3 AAD4012C
	static void SET_DRIVER_AGGRESSIVENESS(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xA731F608CA104E3C, p0, p1); } // A731F608CA104E3C 8B02A8FB
	static BOOL CAN_PED_RAGDOLL(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x128F79EDCECE4FD5, p0); } // 128F79EDCECE4FD5 C0EFB7A3
	static BOOL SET_PED_TO_RAGDOLL(scrAny p0, scrAny p1, scrAny p2, scrAny p3, BOOL p4, BOOL p5, BOOL p6) { return NativeInvoke::Invoke<BOOL>(0xAE99FB955581844A, p0, p1, p2, p3, p4, p5, p6); } // AE99FB955581844A 83CB5052
	static scrAny SET_PED_TO_RAGDOLL_WITH_FALL(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9, scrAny p10, scrAny p11, scrAny p12, scrAny p13) { return NativeInvoke::Invoke<scrAny>(0xD76632D99E4966C8, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } // D76632D99E4966C8 FA12E286
	static void SET_PED_RAGDOLL_ON_COLLISION(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xF0A4F1BBF4FA7497, p0, p1); } // F0A4F1BBF4FA7497 2654A0F4
	static BOOL IS_PED_RAGDOLL(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x47E4E977581C5B55, p0); } // 47E4E977581C5B55 C833BBE1
	static BOOL IS_PED_RUNNING_RAGDOLL_TASK(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xE3B6097CC25AA69E, p0); } // E3B6097CC25AA69E 44A153F2
	static void SET_PED_RAGDOLL_FORCE_FALL(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x01F6594B923B9251, p0); } // 01F6594B923B9251 20A5BDE0
	static void RESET_PED_RAGDOLL_TIMER(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x9FA4664CF62E47E8, p0); } // 9FA4664CF62E47E8 F2865370
	static void SET_PED_CAN_RAGDOLL(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xB128377056A54E2A, p0, p1); } // B128377056A54E2A CF1384C4
	static BOOL IS_PED_RUNNING_MOBILE_PHONE_TASK(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x2AFE52F782F25775, p0); } // 2AFE52F782F25775 FB2AFED1
	static BOOL _0xA3F3564A5B3646C0(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xA3F3564A5B3646C0, p0); } // A3F3564A5B3646C0 97353375
	static void _0x26695EC767728D84(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x26695EC767728D84, p0, p1); } // 26695EC767728D84 9C8F830D
	static void _0xD86D101FCFD00A4B(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xD86D101FCFD00A4B, p0, p1); } // D86D101FCFD00A4B 77CBA290
	static void SET_PED_ANGLED_DEFENSIVE_AREA(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, BOOL p8, BOOL p9) { NativeInvoke::Invoke<scrVoid>(0xC7F76DF27A5045A1, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // C7F76DF27A5045A1 3EFBDD9B
	static void SET_PED_SPHERE_DEFENSIVE_AREA(scrAny p0, float p1, float p2, float p3, float p4, BOOL p5, BOOL p6) { NativeInvoke::Invoke<scrVoid>(0x9D3151A373974804, p0, p1, p2, p3, p4, p5, p6); } // 9D3151A373974804 BD96D8E8
	static void _0xF9B8F91AAD3B953E(scrAny p0, scrAny p1, float p2, float p3, float p4, float p5, BOOL p6) { NativeInvoke::Invoke<scrVoid>(0xF9B8F91AAD3B953E, p0, p1, p2, p3, p4, p5, p6); } // F9B8F91AAD3B953E 40638BDC
	static void _0xE4723DB6E736CCFF(scrAny p0, scrAny p1, float p2, float p3, float p4, float p5, BOOL p6) { NativeInvoke::Invoke<scrVoid>(0xE4723DB6E736CCFF, p0, p1, p2, p3, p4, p5, p6); } // E4723DB6E736CCFF 4763B2C6
	static void SET_PED_DEFENSIVE_AREA_ATTACHED_TO_PED(scrAny p0, scrAny p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, BOOL p9, BOOL p10) { NativeInvoke::Invoke<scrVoid>(0x4EF47FE21698A8B6, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 4EF47FE21698A8B6 74BDA7CE
	static void _0x413C6C763A4AFFAD(scrAny p0, float p1, float p2, float p3, BOOL p4) { NativeInvoke::Invoke<scrVoid>(0x413C6C763A4AFFAD, p0, p1, p2, p3, p4); } // 413C6C763A4AFFAD B66B0C9A
	static void REMOVE_PED_DEFENSIVE_AREA(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x74D4E028107450A9, p0, p1); } // 74D4E028107450A9 34AAAFA5
	static scrVector3 GET_PED_DEFENSIVE_AREA_POSITION(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<scrVector3>(0x3C06B8786DD94CD1, p0, p1); } // 3C06B8786DD94CD1 CB65198D
	static void _0x8421EB4DA7E391B9(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x8421EB4DA7E391B9, p0, p1); } // 8421EB4DA7E391B9 F3B7EFBF
	static void _0xFDDB234CF74073D9(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xFDDB234CF74073D9, p0); } // FDDB234CF74073D9 A0134498
	static void REVIVE_INJURED_PED(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x8D8ACD8388CD99CE, p0); } // 8D8ACD8388CD99CE 14D3E6E3
	static void RESURRECT_PED(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x71BC8E838B9C6035, p0); } // 71BC8E838B9C6035 A4B82097
	static void SET_PED_NAME_DEBUG(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x98EFA132A4117BE1, p0, p1); } // 98EFA132A4117BE1 20D6273E
	static scrVector3 GET_PED_EXTRACTED_DISPLACEMENT(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<scrVector3>(0xE0AF41401ADF87E3, p0, p1); } // E0AF41401ADF87E3 5231F901
	static void SET_PED_DIES_WHEN_INJURED(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x5BA7919BED300023, p0, p1); } // 5BA7919BED300023 E94E24D4
	static void SET_PED_ENABLE_WEAPON_BLOCKING(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x97A790315D3831FD, p0, p1); } // 97A790315D3831FD 4CAD1A4A
	static void _0xF9ACF4A08098EA25(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xF9ACF4A08098EA25, p0, p1); } // F9ACF4A08098EA25 141CC936
	static void RESET_PED_VISIBLE_DAMAGE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x3AC1F7B898F30C05, p0); } // 3AC1F7B898F30C05 C4BC4841
	static void _0x816F6981C60BF53B(scrAny p0, scrAny p1, float p2, float p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x816F6981C60BF53B, p0, p1, p2, p3, p4); } // 816F6981C60BF53B 1E54DB12
	static void APPLY_PED_BLOOD(scrAny p0, scrAny p1, float p2, float p3, float p4, scrAny *p5) { NativeInvoke::Invoke<scrVoid>(0x83F7E01C7B769A26, p0, p1, p2, p3, p4, p5); } // 83F7E01C7B769A26 376CE3C0
	static void _0x3311E47B91EDCBBC(scrAny p0, scrAny p1, float p2, float p3, scrAny *p4) { NativeInvoke::Invoke<scrVoid>(0x3311E47B91EDCBBC, p0, p1, p2, p3, p4); } // 3311E47B91EDCBBC 8F3F3A9C
	static void _0xEF0D582CBF2D9B0F(scrAny p0, scrAny p1, float p2, float p3, float p4, float p5, scrAny p6, float p7, scrAny *p8) { NativeInvoke::Invoke<scrVoid>(0xEF0D582CBF2D9B0F, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // EF0D582CBF2D9B0F FC13CE80
	static void APPLY_PED_DAMAGE_DECAL(scrAny p0, scrAny p1, float p2, float p3, float p4, float p5, float p6, scrAny p7, BOOL p8, scrAny *p9) { NativeInvoke::Invoke<scrVoid>(0x397C38AA7B4A5F83, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 397C38AA7B4A5F83 8A13A41F
	static void APPLY_PED_DAMAGE_PACK(scrAny p0, scrAny *p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x46DF918788CB093F, p0, p1, p2, p3); } // 46DF918788CB093F 208D0CB8
	static void CLEAR_PED_BLOOD_DAMAGE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x8FE22675A5A45817, p0); } // 8FE22675A5A45817 F7ADC960
	static void _0x56E3B78C5408D9F4(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x56E3B78C5408D9F4, p0, p1); } // 56E3B78C5408D9F4 F210BE69
	static void _0x62AB793144DE75DC(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x62AB793144DE75DC, p0, p1, p2); } // 62AB793144DE75DC 0CB6C4ED
	static void _0x523C79AEEFCC4A2A(scrAny p0, scrAny p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0x523C79AEEFCC4A2A, p0, p1, p2); } // 523C79AEEFCC4A2A 70AA5B7D
	static scrAny _0x71EAB450D86954A1(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x71EAB450D86954A1, p0); } // 71EAB450D86954A1 47187F7F
	static void _0x2B694AFCF64E6994(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x2B694AFCF64E6994, p0, p1); } // 2B694AFCF64E6994
	static void CLEAR_PED_WETNESS(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x9C720776DAA43E7E, p0); } // 9C720776DAA43E7E 629F15BD
	static void SET_PED_WETNESS_HEIGHT(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x44CB6447D2571AA0, p0, p1); } // 44CB6447D2571AA0 7B33289A
	static void SET_PED_WETNESS_ENABLED_THIS_FRAME(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xB5485E4907B53019, p0); } // B5485E4907B53019 BDE749F7
	static void _0x6585D955A68452A5(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x6585D955A68452A5, p0); } // 6585D955A68452A5 A993915F
	static void SET_PED_SWEAT(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x27B0405F59637D1F, p0, p1); } // 27B0405F59637D1F 76A1DB9F
	static void _0x5F5D1665E352A839(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x5F5D1665E352A839, p0, p1, p2); } // 5F5D1665E352A839 70559AC7
	static scrAny _0x9FD452BFBE7A7A8B(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x9FD452BFBE7A7A8B, p0, p1); } // 9FD452BFBE7A7A8B 3543019E
	static void CLEAR_PED_DECORATIONS(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x0E5173C163976E38, p0); } // 0E5173C163976E38 D4496BF3
	static void _0xE3B27E70CEAB9F0C(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xE3B27E70CEAB9F0C, p0); } // E3B27E70CEAB9F0C EFD58EB9
	static BOOL WAS_PED_SKELETON_UPDATED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x11B499C1E0FF8559, p0); } // 11B499C1E0FF8559 F7E2FBAD
	static scrVector3 GET_PED_BONE_COORDS(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { return NativeInvoke::Invoke<scrVector3>(0x17C07FC640E86B4E, p0, p1, p2, p3, p4); } // 17C07FC640E86B4E 4579CAB1
	static void CREATE_NM_MESSAGE(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x418EF2A1BCE56685, p0, p1); } // 418EF2A1BCE56685 1CFBFD4B
	static void GIVE_PED_NM_MESSAGE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xB158DFCCC56E5C5B, p0); } // B158DFCCC56E5C5B 737C3689
	static scrAny ADD_SCENARIO_BLOCKING_AREA(float p0, float p1, float p2, float p3, float p4, float p5, BOOL p6, BOOL p7, BOOL p8, BOOL p9) { return NativeInvoke::Invoke<scrAny>(0x1B5C85C612E5256E, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 1B5C85C612E5256E A38C0234
	static void REMOVE_SCENARIO_BLOCKING_AREAS() { NativeInvoke::Invoke<scrVoid>(0xD37401D78A929A49); } // D37401D78A929A49 4DDF845F
	static void REMOVE_SCENARIO_BLOCKING_AREA(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x31D16B74C6E29D66, p0, p1); } // 31D16B74C6E29D66 4483EF06
	static void SET_SCENARIO_PEDS_SPAWN_IN_SPHERE_AREA(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x28157D43CF600981, p0, p1, p2, p3, p4); } // 28157D43CF600981 80EAD297
	static BOOL IS_PED_USING_SCENARIO(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x1BF094736DD62C2E, p0, p1); } // 1BF094736DD62C2E 0F65B0D4
	static BOOL IS_PED_USING_ANY_SCENARIO(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x57AB4A3080F85143, p0); } // 57AB4A3080F85143 195EF5B7
	static scrAny _0xFE07FF6495D52E2A(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0xFE07FF6495D52E2A, p0, p1, p2, p3); } // FE07FF6495D52E2A 59DE73AC
	static void _0x9A77DFD295E29B09(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x9A77DFD295E29B09, p0, p1); } // 9A77DFD295E29B09 C08FE5F6
	static scrAny _0x25361A96E0F7E419(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0x25361A96E0F7E419, p0, p1, p2, p3); } // 25361A96E0F7E419 58C0F6CF
	static scrAny _0xEC6935EBE0847B90(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0xEC6935EBE0847B90, p0, p1, p2, p3); } // EC6935EBE0847B90 761F8F48
	static void _0xA3A9299C4F2ADB98(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA3A9299C4F2ADB98, p0); } // A3A9299C4F2ADB98 033F43FA
	static void _0xF1C03A5352243A30(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xF1C03A5352243A30, p0); } // F1C03A5352243A30 4C684C81
	static scrAny _0xEEED8FAFEC331A70(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0xEEED8FAFEC331A70, p0, p1, p2, p3); } // EEED8FAFEC331A70 7B4C3E6F
	static void _0x425AECF167663F48(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x425AECF167663F48, p0, p1); } // 425AECF167663F48 5BC276AE
	static void _0x5B6010B3CBC29095(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x5B6010B3CBC29095, p0, p1); } // 5B6010B3CBC29095
	static void _0xCEDA60A74219D064(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xCEDA60A74219D064, p0, p1); } // CEDA60A74219D064
	static void PLAY_FACIAL_ANIM(scrAny p0, scrAny *p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0xE1E65CA8AC9C00ED, p0, p1, p2); } // E1E65CA8AC9C00ED 1F6CCDDE
	static void SET_FACIAL_IDLE_ANIM_OVERRIDE(scrAny p0, scrAny *p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0xFFC24B988B938B38, p0, p1, p2); } // FFC24B988B938B38 9BA19C13
	static void CLEAR_FACIAL_IDLE_ANIM_OVERRIDE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x726256CC1EEB182F, p0); } // 726256CC1EEB182F 5244F4E2
	static void SET_PED_CAN_PLAY_GESTURE_ANIMS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xBAF20C5432058024, p0, p1); } // BAF20C5432058024 E131E3B3
	static void SET_PED_CAN_PLAY_VISEME_ANIMS(scrAny p0, BOOL p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xF833DDBA3B104D43, p0, p1, p2); } // F833DDBA3B104D43 A2FDAF27
	static void _0x33A60D8BDD6E508C(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x33A60D8BDD6E508C, p0, p1); } // 33A60D8BDD6E508C ADB2511A
	static void SET_PED_CAN_PLAY_AMBIENT_ANIMS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x6373D1349925A70E, p0, p1); } // 6373D1349925A70E F8053081
	static void SET_PED_CAN_PLAY_AMBIENT_BASE_ANIMS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x0EB0585D15254740, p0, p1); } // 0EB0585D15254740 5720A5DD
	static void _0xC2EE020F5FB4DB53(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xC2EE020F5FB4DB53, p0); } // C2EE020F5FB4DB53 B7CD0A49
	static void _0x6C3B4D6D13B4C841(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x6C3B4D6D13B4C841, p0, p1); } // 6C3B4D6D13B4C841 343B4DE0
	static void SET_PED_CAN_HEAD_IK(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xC11C18092C5530DC, p0, p1); } // C11C18092C5530DC D3B04476
	static void SET_PED_CAN_LEG_IK(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x73518ECE2485412B, p0, p1); } // 73518ECE2485412B 9955BC6F
	static void _0xF2B7106D37947CE0(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xF2B7106D37947CE0, p0, p1); } // F2B7106D37947CE0 8E5D4EAB
	static void _0xF5846EDB26A98A24(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xF5846EDB26A98A24, p0, p1); } // F5846EDB26A98A24 7B0040A8
	static void _0x6647C5F6F5792496(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x6647C5F6F5792496, p0, p1); } // 6647C5F6F5792496 0FDA62DE
	static void SET_PED_CAN_USE_AUTO_CONVERSATION_LOOKAT(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xEC4686EC06434678, p0, p1); } // EC4686EC06434678 584C5178
	static BOOL IS_PED_HEADTRACKING_PED(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x5CD3CB88A7F8850D, p0, p1); } // 5CD3CB88A7F8850D 2A5DF721
	static BOOL IS_PED_HEADTRACKING_ENTITY(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x813A0A7C9D2E831F, p0, p1); } // 813A0A7C9D2E831F 233C9ACF
	static void SET_PED_PRIMARY_LOOKAT(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xCD17B554996A8D9E, p0, p1); } // CD17B554996A8D9E 6DEF6F1C
	static void _0x78C4E9961DB3EB5B(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x78C4E9961DB3EB5B, p0, p1); } // 78C4E9961DB3EB5B FC942D7C
	static void _0x82A3D6D9CC2CB8E3(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x82A3D6D9CC2CB8E3, p0, p1); } // 82A3D6D9CC2CB8E3 89EEE07B
	static void _0xA660FAF550EB37E5(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xA660FAF550EB37E5, p0, p1); } // A660FAF550EB37E5
	static void SET_PED_CONFIG_FLAG(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x1913FE4CBF41C463, p0, p1, p2); } // 1913FE4CBF41C463 9CFBE10D
	static void SET_PED_RESET_FLAG(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xC1E8A365BF3B29F2, p0, p1, p2); } // C1E8A365BF3B29F2 CFF6FF66
	static BOOL GET_PED_CONFIG_FLAG(scrAny p0, scrAny p1, BOOL p2) { return NativeInvoke::Invoke<BOOL>(0x7EE53118C892B513, p0, p1, p2); } // 7EE53118C892B513 ABE98267
	static BOOL GET_PED_RESET_FLAG(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xAF9E59B1B1FBF2A0, p0, p1); } // AF9E59B1B1FBF2A0 2FC10D11
	static void SET_PED_GROUP_MEMBER_PASSENGER_INDEX(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x0BDDB8D9EC6BCF3C, p0, p1); } // 0BDDB8D9EC6BCF3C 2AB3670B
	static void SET_PED_CAN_EVASIVE_DIVE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x6B7A646C242A7059, p0, p1); } // 6B7A646C242A7059 542FEB4D
	static BOOL IS_PED_EVASIVE_DIVING(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x414641C26E105898, p0, p1); } // 414641C26E105898 D82829DC
	static void SET_PED_SHOOTS_AT_COORD(scrAny p0, float p1, float p2, float p3, BOOL p4) { NativeInvoke::Invoke<scrVoid>(0x96A05E4FB321B1BA, p0, p1, p2, p3, p4); } // 96A05E4FB321B1BA FD64EAE5
	static void SET_PED_MODEL_IS_SUPPRESSED(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xE163A4BCE4DE6F11, p0, p1); } // E163A4BCE4DE6F11 7820CA43
	static void STOP_ANY_PED_MODEL_BEING_SUPPRESSED() { NativeInvoke::Invoke<scrVoid>(0xB47BD05FA66B40CF); } // B47BD05FA66B40CF 5AD7DC55
	static void SET_PED_CAN_BE_TARGETED_WHEN_INJURED(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x638C03B0F9878F57, p0, p1); } // 638C03B0F9878F57 6FD9A7CD
	static void SET_PED_GENERATES_DEAD_BODY_EVENTS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x7FB17BA2E7DECA5B, p0, p1); } // 7FB17BA2E7DECA5B E9B97A2B
	static void _0xE43A13C9E4CCCBCF(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xE43A13C9E4CCCBCF, p0, p1); } // E43A13C9E4CCCBCF FF1F6AEB
	static void SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xDF993EE5E90ABA25, p0, p1); } // DF993EE5E90ABA25 E9BD733A
	static void GIVE_PED_HELMET(scrAny p0, BOOL p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x54C7C4A94367717E, p0, p1, p2, p3); } // 54C7C4A94367717E 1862A461
	static void REMOVE_PED_HELMET(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xA7B2458D0AD6DED8, p0, p1); } // A7B2458D0AD6DED8 2086B1F0
	static void SET_PED_HELMET(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x560A43136EB58105, p0, p1); } // 560A43136EB58105 ED366E53
	static void SET_PED_HELMET_FLAG(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xC0E78D5C2CE3EB25, p0, p1); } // C0E78D5C2CE3EB25 12677780
	static void SET_PED_HELMET_PROP_INDEX(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x26D83693ED99291C, p0, p1); } // 26D83693ED99291C A316D13F
	static void SET_PED_HELMET_TEXTURE_INDEX(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xF1550C4BD22582E2, p0, p1); } // F1550C4BD22582E2 5F6C3328
	static BOOL IS_PED_WEARING_HELMET(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xF33BDFE19B309B19, p0); } // F33BDFE19B309B19 0D680D49
	static void _0x687C0B594907D2E8(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x687C0B594907D2E8, p0); } // 687C0B594907D2E8 24A1284E
	static scrAny _0x451294E859ECC018(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x451294E859ECC018, p0); } // 451294E859ECC018 8A3A3116
	static scrAny _0x9D728C1E12BF5518(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x9D728C1E12BF5518, p0); } // 9D728C1E12BF5518 74EB662D
	static BOOL _0xF2385935BFFD4D92(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xF2385935BFFD4D92, p0); } // F2385935BFFD4D92 FFF149FE
	static void SET_PED_TO_LOAD_COVER(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x332B562EEDA62399, p0, p1); } // 332B562EEDA62399 CF94BA97
	static void SET_PED_CAN_COWER_IN_COVER(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xCB7553CDCEF4A735, p0, p1); } // CB7553CDCEF4A735 5194658B
	static void SET_PED_CAN_PEEK_IN_COVER(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xC514825C507E3736, p0, p1); } // C514825C507E3736 C1DAE216
	static void SET_PED_PLAYS_HEAD_ON_HORN_ANIM_WHEN_DIES_IN_VEHICLE(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x94D94BF1A75AED3D, p0, p1); } // 94D94BF1A75AED3D 7C563CD2
	static void SET_PED_LEG_IK_MODE(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xC396F5B86FF9FEBD, p0, p1); } // C396F5B86FF9FEBD FDDB042E
	static void SET_PED_MOTION_BLUR(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x0A986918B102B448, p0, p1); } // 0A986918B102B448 A211A128
	static void SET_PED_CAN_SWITCH_WEAPON(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xED7F7EFE9FABF340, p0, p1); } // ED7F7EFE9FABF340 B5F8BA28
	static void SET_PED_DIES_INSTANTLY_IN_WATER(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xEEB64139BA29A7CF, p0, p1); } // EEB64139BA29A7CF FE2554FC
	static void _0x1A330D297AAC6BC1(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x1A330D297AAC6BC1, p0, p1); } // 1A330D297AAC6BC1 77BB7CB8
	static void STOP_PED_WEAPON_FIRING_WHEN_DROPPED(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xC158D28142A34608, p0); } // C158D28142A34608 4AC3421E
	static void SET_SCRIPTED_ANIM_SEAT_OFFSET(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x5917BBA32D06C230, p0, p1); } // 5917BBA32D06C230 7CEFFA45
	static void SET_PED_COMBAT_MOVEMENT(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x4D9CA1009AFBD057, p0, p1); } // 4D9CA1009AFBD057 12E62F9E
	static scrAny GET_PED_COMBAT_MOVEMENT(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xDEA92412FCAEB3F5, p0); } // DEA92412FCAEB3F5 F3E7730E
	static void SET_PED_COMBAT_ABILITY(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xC7622C0D36B2FDA8, p0, p1); } // C7622C0D36B2FDA8 6C23D329
	static void SET_PED_COMBAT_RANGE(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x3C606747B23E497B, p0, p1); } // 3C606747B23E497B 8818A959
	static scrAny GET_PED_COMBAT_RANGE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xF9D9F7F2DB8E2FA0, p0); } // F9D9F7F2DB8E2FA0 9B9B7163
	static void SET_PED_COMBAT_ATTRIBUTES(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x9F7794730795E019, p0, p1, p2); } // 9F7794730795E019 81D64248
	static void SET_PED_TARGET_LOSS_RESPONSE(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x0703B9079823DA4A, p0, p1); } // 0703B9079823DA4A CFA613FF
	static BOOL _0xDCCA191DF9980FD7(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xDCCA191DF9980FD7, p0); } // DCCA191DF9980FD7 139C0875
	static BOOL IS_PED_PERFORMING_STEALTH_KILL(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xFD4CCDBCC59941B7, p0); } // FD4CCDBCC59941B7 9ADD7B21
	static BOOL _0xEBD0EDBA5BE957CF(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xEBD0EDBA5BE957CF, p0); } // EBD0EDBA5BE957CF 9BE7C860
	static BOOL IS_PED_BEING_STEALTH_KILLED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x863B23EFDE9C5DF2, p0); } // 863B23EFDE9C5DF2 D044C8AF
	static scrAny _0x18A3E9EE1297FD39(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x18A3E9EE1297FD39, p0); } // 18A3E9EE1297FD39 AFEC26A4
	static BOOL WAS_PED_KILLED_BY_STEALTH(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xF9800AA1A771B000, p0); } // F9800AA1A771B000 2EA4B54E
	static BOOL WAS_PED_KILLED_BY_TAKEDOWN(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x7F08E26039C7347C, p0); } // 7F08E26039C7347C BDD3CE69
	static BOOL _0x61767F73EACEED21(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x61767F73EACEED21, p0); } // 61767F73EACEED21 3993092B
	static void SET_PED_FLEE_ATTRIBUTES(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x70A2D1137C8ED7C9, p0, p1, p2); } // 70A2D1137C8ED7C9 A717A875
	static void SET_PED_COWER_HASH(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xA549131166868ED3, p0, p1); } // A549131166868ED3 16F30DF4
	static void _0x2016C603D6B8987C(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x2016C603D6B8987C, p0, p1); } // 2016C603D6B8987C A6F2C057
	static void SET_PED_STEERS_AROUND_PEDS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x46F2193B3AD1D891, p0, p1); } // 46F2193B3AD1D891 797CAE4F
	static void SET_PED_STEERS_AROUND_OBJECTS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x1509C089ADC208BF, p0, p1); } // 1509C089ADC208BF 3BD9B0A6
	static void SET_PED_STEERS_AROUND_VEHICLES(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xEB6FB9D48DDE23EC, p0, p1); } // EB6FB9D48DDE23EC 533C0651
	static void _0xA9B61A329BFDCBEA(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xA9B61A329BFDCBEA, p0, p1); } // A9B61A329BFDCBEA 2276DE0D
	static void _0x570389D1C3DE3C6B(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x570389D1C3DE3C6B, p0); } // 570389D1C3DE3C6B 59C52BE6
	static void _0x576594E8D64375E2(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x576594E8D64375E2, p0, p1); } // 576594E8D64375E2 1D87DDC1
	static void _0xA52D5247A4227E14(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA52D5247A4227E14, p0); } // A52D5247A4227E14 B52BA5F5
	static BOOL IS_ANY_PED_NEAR_POINT(float p0, float p1, float p2, float p3) { return NativeInvoke::Invoke<BOOL>(0x083961498679DC9F, p0, p1, p2, p3); } // 083961498679DC9F FBD9B050
	static void _0x2208438012482A1A(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x2208438012482A1A, p0, p1, p2); } // 2208438012482A1A 187B9070
	static BOOL _0xFCF37A457CB96DC0(scrAny p0, float p1, float p2, float p3, float p4) { return NativeInvoke::Invoke<BOOL>(0xFCF37A457CB96DC0, p0, p1, p2, p3, p4); } // FCF37A457CB96DC0 45037B9B
	static void _0x7D7A2E43E74E2EB8(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x7D7A2E43E74E2EB8, p0); } // 7D7A2E43E74E2EB8 840D24D3
	static void GET_PED_FLOOD_INVINCIBILITY(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x2BC338A7B21F4608, p0, p1); } // 2BC338A7B21F4608 31C31DAA
	static void _0x75BA1CB3B7D40CAF(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x75BA1CB3B7D40CAF, p0, p1); } // 75BA1CB3B7D40CAF 9194DB71
	static BOOL IS_TRACKED_PED_VISIBLE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x91C8E617F64188AC, p0); } // 91C8E617F64188AC 33248CC1
	static scrAny _0x511F1A683387C7E2(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x511F1A683387C7E2, p0); } // 511F1A683387C7E2 5B1B70AA
	static BOOL IS_PED_TRACKED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x4C5E1F087CD10BB7, p0); } // 4C5E1F087CD10BB7 7EB613D9
	static BOOL HAS_PED_RECEIVED_EVENT(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x8507BCB710FA6DC0, p0, p1); } // 8507BCB710FA6DC0 ECD73DB0
	static BOOL _0x6CD5A433374D4CFB(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x6CD5A433374D4CFB, p0, p1); } // 6CD5A433374D4CFB 74A0F291
	static scrAny GET_PED_BONE_INDEX(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x3F428D08BE5AAE31, p0, p1); } // 3F428D08BE5AAE31 259C6BA2
	static scrAny GET_PED_RAGDOLL_BONE_INDEX(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x2057EF813397A772, p0, p1); } // 2057EF813397A772 849F0716
	static void SET_PED_ENVEFF_SCALE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xBF29516833893561, p0, p1); } // BF29516833893561 FC1CFC27
	static float GET_PED_ENVEFF_SCALE(scrAny p0) { return NativeInvoke::Invoke<float>(0x9C14D30395A51A3C, p0); } // 9C14D30395A51A3C A3421E39
	static void SET_ENABLE_PED_ENVEFF_SCALE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xD2C5AA0C0E8D0F1E, p0, p1); } // D2C5AA0C0E8D0F1E C70F4A84
	static void _0x110F526AB784111F(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x110F526AB784111F, p0, p1); } // 110F526AB784111F 3B882533
	static void _0xD69411AA0CEBF9E9(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0xD69411AA0CEBF9E9, p0, p1, p2, p3); } // D69411AA0CEBF9E9 87A0C174
	static void _0x1216E0BFA72CC703(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x1216E0BFA72CC703, p0, p1); } // 1216E0BFA72CC703 7BD26837
	static void _0x2B5AA717A181FB4C(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x2B5AA717A181FB4C, p0, p1); } // 2B5AA717A181FB4C 98E29ED0
	static scrAny CREATE_SYNCHRONIZED_SCENE(float p0, float p1, float p2, float p3, float p4, float p5, scrAny p6) { return NativeInvoke::Invoke<scrAny>(0x8C18E0F9080ADD73, p0, p1, p2, p3, p4, p5, p6); } // 8C18E0F9080ADD73 FFDDF8FA
	static scrAny _0x62EC273D00187DCA(float p0, float p1, float p2, float p3, scrAny p4) { return NativeInvoke::Invoke<scrAny>(0x62EC273D00187DCA, p0, p1, p2, p3, p4); } // 62EC273D00187DCA F3876894
	static scrAny IS_SYNCHRONIZED_SCENE_RUNNING(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x25D39B935A038A26, p0); } // 25D39B935A038A26 57A282F1
	static void SET_SYNCHRONIZED_SCENE_ORIGIN(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, scrAny p7) { NativeInvoke::Invoke<scrVoid>(0x6ACF6B7225801CD7, p0, p1, p2, p3, p4, p5, p6, p7); } // 6ACF6B7225801CD7 2EC2A0B2
	static void SET_SYNCHRONIZED_SCENE_PHASE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x734292F4F0ABF6D0, p0, p1); } // 734292F4F0ABF6D0 F5AB0D98
	static float GET_SYNCHRONIZED_SCENE_PHASE(scrAny p0) { return NativeInvoke::Invoke<float>(0xE4A310B1D7FA73CC, p0); } // E4A310B1D7FA73CC B0B2C852
	static void SET_SYNCHRONIZED_SCENE_RATE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xB6C49F8A5E295A5D, p0, p1); } // B6C49F8A5E295A5D F10112FD
	static float GET_SYNCHRONIZED_SCENE_RATE(scrAny p0) { return NativeInvoke::Invoke<float>(0xD80932D577274D40, p0); } // D80932D577274D40 89365F0D
	static void SET_SYNCHRONIZED_SCENE_LOOPED(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xD9A897A4C6C2974F, p0, p1); } // D9A897A4C6C2974F 32ED9F82
	static BOOL IS_SYNCHRONIZED_SCENE_LOOPED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x62522002E0C391BA, p0); } // 62522002E0C391BA 47D87A84
	static void _0x394B9CD12435C981(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x394B9CD12435C981, p0, p1); } // 394B9CD12435C981 2DE48DA1
	static BOOL _0x7F2F4F13AC5257EF(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x7F2F4F13AC5257EF, p0); } // 7F2F4F13AC5257EF 72CF2514
	static void ATTACH_SYNCHRONIZED_SCENE_TO_ENTITY(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x272E4723B56A3B96, p0, p1, p2); } // 272E4723B56A3B96 E9BA6189
	static void DETACH_SYNCHRONIZED_SCENE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x6D38F1F04CBB37EA, p0); } // 6D38F1F04CBB37EA 52A1CAB2
	static void _0xCD9CC7E200A52A6F(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xCD9CC7E200A52A6F, p0); } // CD9CC7E200A52A6F BF7F9035
	static BOOL FORCE_PED_MOTION_STATE(scrAny p0, scrAny p1, BOOL p2, scrAny p3, BOOL p4) { return NativeInvoke::Invoke<BOOL>(0xF28965D04F570DCA, p0, p1, p2, p3, p4); } // F28965D04F570DCA 164DDEFF
	static void SET_PED_MAX_MOVE_BLEND_RATIO(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x433083750C5E064A, p0, p1); } // 433083750C5E064A EAD0269A
	static void SET_PED_MIN_MOVE_BLEND_RATIO(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x01A898D26E2333DD, p0, p1); } // 01A898D26E2333DD 383EC364
	static void SET_PED_MOVE_RATE_OVERRIDE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x085BF80FA50A39D1, p0, p1); } // 085BF80FA50A39D1 900008C6
	static BOOL _0x46B05BCAE43856B0(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x46B05BCAE43856B0, p0, p1); } // 46B05BCAE43856B0 79543043
	static scrAny GET_PED_NEARBY_VEHICLES(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<scrAny>(0xCFF869CBFA210D82, p0, p1); } // CFF869CBFA210D82 CB716F68
	static scrAny GET_PED_NEARBY_PEDS(scrAny p0, scrAny *p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0x23F8F5FC7E8C4A6B, p0, p1, p2); } // 23F8F5FC7E8C4A6B 4D3325F4
	static BOOL _0x7350823473013C02(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x7350823473013C02, p0); } // 7350823473013C02 F9FB4B71
	static BOOL IS_PED_USING_ACTION_MODE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x00E73468D085F745, p0); } // 00E73468D085F745 5AE7EDA2
	static void SET_PED_USING_ACTION_MODE(scrAny p0, BOOL p1, scrAny p2, scrAny *p3) { NativeInvoke::Invoke<scrVoid>(0xD75ACCF5E0FB5367, p0, p1, p2, p3); } // D75ACCF5E0FB5367 8802F696
	static void SET_PED_CAPSULE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x364DF566EC833DE2, p0, p1); } // 364DF566EC833DE2 B153E1B9
	static scrAny REGISTER_PEDHEADSHOT(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x4462658788425076, p0); } // 4462658788425076 FFE2667B
	static scrAny _0x953563CE563143AF(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x953563CE563143AF, p0); } // 953563CE563143AF 4DD03628
	static void UNREGISTER_PEDHEADSHOT(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x96B1361D9B24C2FF, p0); } // 96B1361D9B24C2FF 0879AE45
	static BOOL IS_PEDHEADSHOT_VALID(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xA0A9668F158129A2, p0); } // A0A9668F158129A2 0B1080C4
	static BOOL IS_PEDHEADSHOT_READY(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x7085228842B13A67, p0); } // 7085228842B13A67 761CD02E
	static scrAny GET_PEDHEADSHOT_TXD_STRING(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xDB4EACD4AD0A5D6B, p0); } // DB4EACD4AD0A5D6B 76D28E96
	static BOOL _0xF0DAEF2F545BEE25(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xF0DAEF2F545BEE25, p0); } // F0DAEF2F545BEE25 10F2C023
	static void _0x5D517B27CF6ECD04(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x5D517B27CF6ECD04, p0); } // 5D517B27CF6ECD04 0DBB2FA7
	static scrAny _0xEBB376779A760AA8() { return NativeInvoke::Invoke<scrAny>(0xEBB376779A760AA8); } // EBB376779A760AA8 810158F8
	static scrAny _0x876928DDDFCCC9CD() { return NativeInvoke::Invoke<scrAny>(0x876928DDDFCCC9CD); } // 876928DDDFCCC9CD 05023F8F
	static scrAny _0xE8A169E666CBC541() { return NativeInvoke::Invoke<scrAny>(0xE8A169E666CBC541); } // E8A169E666CBC541 AA39FD6C
	static void _0xC1F6EBF9A3D55538(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xC1F6EBF9A3D55538, p0, p1); } // C1F6EBF9A3D55538 EF9142DB
	static void _0x600048C60D5C2C51(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x600048C60D5C2C51, p0); } // 600048C60D5C2C51 0688DE64
	static void _0x2DF9038C90AD5264(float p0, float p1, float p2, float p3, float p4, scrAny p5, float p6, scrAny p7) { NativeInvoke::Invoke<scrVoid>(0x2DF9038C90AD5264, p0, p1, p2, p3, p4, p5, p6, p7); } // 2DF9038C90AD5264 909A1D76
	static void _0xB2AFF10216DEFA2F(float p0, float p1, float p2, float p3, float p4, float p5, float p6, scrAny p7, float p8, scrAny p9) { NativeInvoke::Invoke<scrVoid>(0xB2AFF10216DEFA2F, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // B2AFF10216DEFA2F 4AAD0ECB
	static void _0xFEE4A5459472A9F8() { NativeInvoke::Invoke<scrVoid>(0xFEE4A5459472A9F8); } // FEE4A5459472A9F8 492C9E46
	static BOOL _0x3C67506996001F5E() { return NativeInvoke::Invoke<BOOL>(0x3C67506996001F5E); } // 3C67506996001F5E 814A28F4
	static BOOL _0xA586FBEB32A53DBB() { return NativeInvoke::Invoke<BOOL>(0xA586FBEB32A53DBB); } // A586FBEB32A53DBB 0B60D2BA
	static BOOL _0xF445DE8DA80A1792() { return NativeInvoke::Invoke<BOOL>(0xF445DE8DA80A1792); } // F445DE8DA80A1792 6B83ABDF
	static scrAny _0xA635C11B8C44AFC2() { return NativeInvoke::Invoke<scrAny>(0xA635C11B8C44AFC2); } // A635C11B8C44AFC2 F46B4DC8
	static void _0x280C7E3AC7F56E90(scrAny p0, scrAny *p1, scrAny *p2, scrAny *p3) { NativeInvoke::Invoke<scrVoid>(0x280C7E3AC7F56E90, p0, p1, p2, p3); } // 280C7E3AC7F56E90 36A4AC65
	static void _0xB782F8238512BAD5(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xB782F8238512BAD5, p0, p1); } // B782F8238512BAD5 BA699DDF
	static void SET_IK_TARGET(scrAny p0, scrAny p1, scrAny p2, scrAny p3, float p4, float p5, float p6, scrAny p7, scrAny p8, scrAny p9) { NativeInvoke::Invoke<scrVoid>(0xC32779C16FCEECD9, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // C32779C16FCEECD9 6FE5218C
	static void _0xED3C76ADFA6D07C4(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xED3C76ADFA6D07C4, p0); } // ED3C76ADFA6D07C4 FB4000DC
	static void REQUEST_ACTION_MODE_ASSET(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x290E2780BB7AA598, p0); } // 290E2780BB7AA598 572BA553
	static BOOL HAS_ACTION_MODE_ASSET_LOADED(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xE4B5F4BF2CB24E65, p0); } // E4B5F4BF2CB24E65 F7EB2BF1
	static void REMOVE_ACTION_MODE_ASSET(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x13E940F88470FA51, p0); } // 13E940F88470FA51 3F480F92
	static void REQUEST_STEALTH_MODE_ASSET(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x2A0A62FCDEE16D4F, p0); } // 2A0A62FCDEE16D4F 280A004A
	static BOOL HAS_STEALTH_MODE_ASSET_LOADED(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xE977FC5B08AF3441, p0); } // E977FC5B08AF3441 39245667
	static void REMOVE_STEALTH_MODE_ASSET(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x9219857D21F0E842, p0); } // 9219857D21F0E842 8C0B243A
	static void SET_PED_LOD_MULTIPLIER(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xDC2C5C242AAC342B, p0, p1); } // DC2C5C242AAC342B 1D2B5C70
	static void _0xE861D0B05C7662B8(scrAny p0, BOOL p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xE861D0B05C7662B8, p0, p1, p2); } // E861D0B05C7662B8 2F9550C2
	static void _0x129466ED55140F8D(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x129466ED55140F8D, p0, p1); } // 129466ED55140F8D 37DBC2AD
	static void _0xCB968B53FC7F916D(scrAny p0, BOOL p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0xCB968B53FC7F916D, p0, p1, p2, p3); } // CB968B53FC7F916D C0F1BC91
	static BOOL _0x68772DB2B2526F9F(scrAny p0, float p1, float p2, float p3, float p4) { return NativeInvoke::Invoke<BOOL>(0x68772DB2B2526F9F, p0, p1, p2, p3, p4); } // 68772DB2B2526F9F 1A464167
	static BOOL _0x06087579E7AA85A9(scrAny p0, scrAny p1, float p2, float p3, float p4, float p5) { return NativeInvoke::Invoke<BOOL>(0x06087579E7AA85A9, p0, p1, p2, p3, p4, p5); } // 06087579E7AA85A9 D0567D41
	static void _0xD8C3BE3EE94CAF2D(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0xD8C3BE3EE94CAF2D, p0, p1, p2, p3, p4); } // D8C3BE3EE94CAF2D 4BBE5E2C
	static void _0xD33DAA36272177C4(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xD33DAA36272177C4, p0); } // D33DAA36272177C4 A89A53F2
	static void _0x83A169EABCDB10A2(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x83A169EABCDB10A2, p0, p1); } // 83A169EABCDB10A2
	static void _0x288DF530C92DAD6F(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x288DF530C92DAD6F, p0, p1); } // 288DF530C92DAD6F
}

namespace VEHICLE
{
	static scrAny CREATE_VEHICLE(scrAny p0, float p1, float p2, float p3, float p4, BOOL p5, BOOL p6) { return NativeInvoke::Invoke<scrAny>(0xAF35D0D2583051B0, p0, p1, p2, p3, p4, p5, p6); } // AF35D0D2583051B0 DD75460A
	static void DELETE_VEHICLE(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xEA386986E786A54F, p0); } // EA386986E786A54F 9803AF60
	static void _0x7D6F9A3EF26136A0(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x7D6F9A3EF26136A0, p0, p1); } // 7D6F9A3EF26136A0 BB54ECCA
	static void _0x5D14D4154BFE7B2C(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x5D14D4154BFE7B2C, p0, p1); } // 5D14D4154BFE7B2C 8BAAC437
	static scrAny _0xE6B0E8CFC3633BF0(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xE6B0E8CFC3633BF0, p0); } // E6B0E8CFC3633BF0 FBDE9FD8
	static BOOL IS_VEHICLE_MODEL(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x423E8DE37D934D89, p0, p1); } // 423E8DE37D934D89 013B10B6
	static BOOL DOES_SCRIPT_VEHICLE_GENERATOR_EXIST(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xF6086BC836400876, p0); } // F6086BC836400876 F6BDDA30
	static scrAny CREATE_SCRIPT_VEHICLE_GENERATOR(float p0, float p1, float p2, float p3, float p4, float p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9, scrAny p10, BOOL p11, scrAny p12, scrAny p13, BOOL p14, BOOL p15, scrAny p16) { return NativeInvoke::Invoke<scrAny>(0x9DEF883114668116, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16); } // 9DEF883114668116 25A9A261
	static void DELETE_SCRIPT_VEHICLE_GENERATOR(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x22102C9ABFCF125D, p0); } // 22102C9ABFCF125D E4328E3F
	static void SET_SCRIPT_VEHICLE_GENERATOR(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xD9D620E0AC6DC4B0, p0, p1); } // D9D620E0AC6DC4B0 40D73747
	static void SET_ALL_VEHICLE_GENERATORS_ACTIVE_IN_AREA(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7) { NativeInvoke::Invoke<scrVoid>(0xC12321827687FE4D, p0, p1, p2, p3, p4, p5, p6, p7); } // C12321827687FE4D B4E0E69A
	static void SET_ALL_VEHICLE_GENERATORS_ACTIVE() { NativeInvoke::Invoke<scrVoid>(0x34AD89078831A4BC); } // 34AD89078831A4BC AB1FDD76
	static void SET_ALL_LOW_PRIORITY_VEHICLE_GENERATORS_ACTIVE(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x608207E7A8FB787C, p0); } // 608207E7A8FB787C 87F767F2
	static void _0x9A75585FB2E54FAD(float p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x9A75585FB2E54FAD, p0, p1, p2, p3); } // 9A75585FB2E54FAD 935A95DA
	static void _0x0A436B8643716D14() { NativeInvoke::Invoke<scrVoid>(0x0A436B8643716D14); } // 0A436B8643716D14 6C73E45A
	static BOOL SET_VEHICLE_ON_GROUND_PROPERLY(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x49733E92263139D1, p0); } // 49733E92263139D1 E14FDBA6
	static scrAny SET_ALL_VEHICLES_SPAWN(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0xE023E8AC4EF7C117, p0, p1, p2, p3); } // E023E8AC4EF7C117 A0909ADB
	static BOOL IS_VEHICLE_STUCK_ON_ROOF(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xB497F06B288DCFDF, p0); } // B497F06B288DCFDF 18D07C6C
	static void ADD_VEHICLE_UPSIDEDOWN_CHECK(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xB72E26D81006005B, p0); } // B72E26D81006005B 3A13D384
	static void REMOVE_VEHICLE_UPSIDEDOWN_CHECK(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xC53EB42A499A7E90, p0); } // C53EB42A499A7E90 F390BA1B
	static BOOL IS_VEHICLE_STOPPED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x5721B434AD84D57A, p0); } // 5721B434AD84D57A 655F072C
	static scrAny GET_VEHICLE_NUMBER_OF_PASSENGERS(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x24CB2137731FFE89, p0); } // 24CB2137731FFE89 1EF20849
	static scrAny GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xA7C4F2C6E744A550, p0); } // A7C4F2C6E744A550 0A2FC08C
	static scrAny _0x2AD93716F184EDA4(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x2AD93716F184EDA4, p0); } // 2AD93716F184EDA4 838F7BF7
	static BOOL _0xF7F203E31F96F6A1(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xF7F203E31F96F6A1, p0, p1); } // F7F203E31F96F6A1 769E5CF2
	static BOOL _0xE33FFA906CE74880(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xE33FFA906CE74880, p0, p1); } // E33FFA906CE74880
	static void SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float p0) { NativeInvoke::Invoke<scrVoid>(0x245A6883D966D537, p0); } // 245A6883D966D537 F4187E51
	static void SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float p0) { NativeInvoke::Invoke<scrVoid>(0xB3B3359379FE77D3, p0); } // B3B3359379FE77D3 543F712B
	static void SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float p0) { NativeInvoke::Invoke<scrVoid>(0xEAE6DCC7EEE3DB1D, p0); } // EAE6DCC7EEE3DB1D DD46CEBE
	static void _0xD4B8E3D1917BC86B(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xD4B8E3D1917BC86B, p0); } // D4B8E3D1917BC86B 09462665
	static void _0x90B6DA738A9A25DA(float p0) { NativeInvoke::Invoke<scrVoid>(0x90B6DA738A9A25DA, p0); } // 90B6DA738A9A25DA DAE2A2BE
	static void SET_FAR_DRAW_VEHICLES(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x26324F33423F3CC3, p0); } // 26324F33423F3CC3 9F019C49
	static void SET_NUMBER_OF_PARKED_VEHICLES(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xCAA15F13EBD417FF, p0); } // CAA15F13EBD417FF 206A58E8
	static void SET_VEHICLE_DOORS_LOCKED(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xB664292EAECF7FA6, p0, p1); } // B664292EAECF7FA6 4CDD35D0
	static void SET_PED_TARGETTABLE_VEHICLE_DESTROY(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xBE70724027F85BCD, p0, p1, p2); } // BE70724027F85BCD D61D182D
	static void DISABLE_VEHICLE_IMPACT_EXPLOSION_ACTIVATION(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xD8050E0EB60CF274, p0, p1); } // D8050E0EB60CF274 C54156A9
	static void SET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x517AAF684BB50CD1, p0, p1, p2); } // 517AAF684BB50CD1 49829236
	static BOOL GET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xF6AF6CB341349015, p0, p1); } // F6AF6CB341349015 1DC50247
	static void SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xA2F80B8D040727CC, p0, p1); } // A2F80B8D040727CC 891BA8A4
	static void _0x9737A37136F07E75(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x9737A37136F07E75, p0, p1); } // 9737A37136F07E75 E4EF6514
	static void SET_VEHICLE_DOORS_LOCKED_FOR_TEAM(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xB81F6D4A8F5EEBA8, p0, p1, p2); } // B81F6D4A8F5EEBA8 4F85E783
	static void EXPLODE_VEHICLE(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xBA71116ADF5B514C, p0, p1, p2); } // BA71116ADF5B514C BEDEACEB
	static void SET_VEHICLE_OUT_OF_CONTROL(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xF19D095E42D430CC, p0, p1, p2); } // F19D095E42D430CC 3764D734
	static void SET_VEHICLE_TIMED_EXPLOSION(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x2E0A74E1002380B1, p0, p1, p2); } // 2E0A74E1002380B1 DB8CB8E2
	static void _0x99AD4CCCB128CBC9(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x99AD4CCCB128CBC9, p0); } // 99AD4CCCB128CBC9 811373DE
	static BOOL _0x6ADAABD3068C5235() { return NativeInvoke::Invoke<BOOL>(0x6ADAABD3068C5235); } // 6ADAABD3068C5235 A4E69134
	static void _0xEF49CF0270307CBE() { NativeInvoke::Invoke<scrVoid>(0xEF49CF0270307CBE); } // EF49CF0270307CBE 65255524
	static BOOL _0xAE3FEE8709B39DCB(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xAE3FEE8709B39DCB, p0); } // AE3FEE8709B39DCB E39DAF36
	static void SET_TAXI_LIGHTS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x598803E85E8448D9, p0, p1); } // 598803E85E8448D9 68639D85
	static BOOL IS_TAXI_LIGHT_ON(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x7504C0F113AB50FC, p0); } // 7504C0F113AB50FC 6FC4924A
	static BOOL IS_VEHICLE_IN_GARAGE_AREA(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xCEE4490CD57BB3C2, p0, p1); } // CEE4490CD57BB3C2 A90EC257
	static void SET_VEHICLE_COLOURS(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x4F1D4BE3A7F24601, p0, p1, p2); } // 4F1D4BE3A7F24601 57F24253
	static void SET_VEHICLE_FULLBEAM(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x8B7FD87F0DDB421E, p0, p1); } // 8B7FD87F0DDB421E 9C49CC15
	static void STEER_UNLOCK_BIAS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x07116E24E9D1929D, p0, p1); } // 07116E24E9D1929D A59E3DCD
	static void SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x7141766F91D15BEA, p0, p1, p2, p3); } // 7141766F91D15BEA 8DF9F9BC
	static void GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(scrAny p0, scrAny *p1, scrAny *p2, scrAny *p3) { NativeInvoke::Invoke<scrVoid>(0xB64CF2CCA9D95F52, p0, p1, p2, p3); } // B64CF2CCA9D95F52 1C2B9FEF
	static void CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x55E1D2758F34E437, p0); } // 55E1D2758F34E437 51E1E33D
	static BOOL _DOES_VEHICLE_HAVE_SECONDARY_COLOUR(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xF095C0405307B21B, p0); } // F095C0405307B21B D7EC8760
	static void SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x36CED73BFED89754, p0, p1, p2, p3); } // 36CED73BFED89754 9D77259E
	static void GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(scrAny p0, scrAny *p1, scrAny *p2, scrAny *p3) { NativeInvoke::Invoke<scrVoid>(0x8389CD56CA8072DC, p0, p1, p2, p3); } // 8389CD56CA8072DC 3FF247A2
	static void CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x5FFBDEEC3E8E2009, p0); } // 5FFBDEEC3E8E2009 7CE00B29
	static BOOL _0x910A32E7AAD2656C(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x910A32E7AAD2656C, p0); } // 910A32E7AAD2656C 288AD228
	static void _0x3AFDC536C3D01674(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x3AFDC536C3D01674, p0, p1); } // 3AFDC536C3D01674 8332730C
	static float _0xA82819CAC9C4C403(scrAny p0) { return NativeInvoke::Invoke<float>(0xA82819CAC9C4C403, p0); } // A82819CAC9C4C403 D5F1EEE1
	static void SET_CAN_RESPRAY_VEHICLE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x52BBA29D5EC69356, p0, p1); } // 52BBA29D5EC69356 37677590
	static void _0x33506883545AC0DF(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x33506883545AC0DF, p0, p1); } // 33506883545AC0DF 54E9EE75
	static void _0xC59872A5134879C7(scrAny p0, BOOL p1, float p2, float p3, float p4) { NativeInvoke::Invoke<scrVoid>(0xC59872A5134879C7, p0, p1, p2, p3, p4); } // C59872A5134879C7 4A46E814
	static void SET_BOAT_ANCHOR(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x75DBEC174AEEAD10, p0, p1); } // 75DBEC174AEEAD10 A3906284
	static BOOL _0x26C10ECBDA5D043B(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x26C10ECBDA5D043B, p0); } // 26C10ECBDA5D043B
	static void _0xE3EBAAE484798530(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xE3EBAAE484798530, p0, p1); } // E3EBAAE484798530 0ED84792
	static void _0xB28B1FE5BFADD7F5(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xB28B1FE5BFADD7F5, p0, p1); } // B28B1FE5BFADD7F5 A739012A
	static void _0xE842A9398079BD82(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xE842A9398079BD82, p0, p1); } // E842A9398079BD82 66FA450C
	static void _0x8F719973E1445BA2(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x8F719973E1445BA2, p0, p1); } // 8F719973E1445BA2 35614622
	static void SET_VEHICLE_SIREN(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xF4924635A19EB37D, p0, p1); } // F4924635A19EB37D 4AC1EFC7
	static BOOL IS_VEHICLE_SIREN_ON(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x4C9BF537BE2634B2, p0); } // 4C9BF537BE2634B2 25EB5873
	static BOOL _0xB5CC40FBCB586380(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xB5CC40FBCB586380, p0); } // B5CC40FBCB586380
	static void SET_VEHICLE_STRONG(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x3E8C8727991A8A0B, p0, p1); } // 3E8C8727991A8A0B C758D19F
	static void REMOVE_VEHICLE_STUCK_CHECK(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x8386BFB614D06749, p0); } // 8386BFB614D06749 81594917
	static void GET_VEHICLE_COLOURS(scrAny p0, scrAny *p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0xA19435F193E081AC, p0, p1, p2); } // A19435F193E081AC 40D82D88
	static BOOL IS_VEHICLE_SEAT_FREE(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x22AC59A870E6A669, p0, p1); } // 22AC59A870E6A669 DAF42B02
	static scrAny GET_PED_IN_VEHICLE_SEAT(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xBB40DD2270B65366, p0, p1); } // BB40DD2270B65366 388FDE9A
	static scrAny _0x83F969AA1EE2A664(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x83F969AA1EE2A664, p0, p1); } // 83F969AA1EE2A664 F7C6792D
	static BOOL GET_VEHICLE_LIGHTS_STATE(scrAny p0, scrAny *p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0xB91B4C20085BD12F, p0, p1, p2); } // B91B4C20085BD12F 7C278621
	static BOOL IS_VEHICLE_TYRE_BURST(scrAny p0, scrAny p1, BOOL p2) { return NativeInvoke::Invoke<BOOL>(0xBA291848A0815CA9, p0, p1, p2); } // BA291848A0815CA9 48C80210
	static void SET_VEHICLE_FORWARD_SPEED(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xAB54A438726D25D5, p0, p1); } // AB54A438726D25D5 69880D14
	static void _0x260BE8F09E326A20(scrAny p0, float p1, scrAny p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x260BE8F09E326A20, p0, p1, p2, p3); } // 260BE8F09E326A20 CBC7D3C8
	static void _0x37EBBF3117BD6A25(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x37EBBF3117BD6A25, p0, p1); } // 37EBBF3117BD6A25 943A6CFC
	static BOOL SET_PED_ENABLED_BIKE_RINGTONE(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x57715966069157AD, p0, p1); } // 57715966069157AD 7FB25568
	static BOOL _0x62CA17B74C435651(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x62CA17B74C435651, p0); } // 62CA17B74C435651 593143B9
	static scrAny _0x375E7FC44F21C8AB(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x375E7FC44F21C8AB, p0); } // 375E7FC44F21C8AB 70DD5E25
	static BOOL _0x89D630CF5EA96D23(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x89D630CF5EA96D23, p0, p1); } // 89D630CF5EA96D23 FBF5536A
	static void _0x6A98C2ECF57FA5D4(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x6A98C2ECF57FA5D4, p0, p1); } // 6A98C2ECF57FA5D4 20AB5783
	static void _0x7C0043FDFF6436BC(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x7C0043FDFF6436BC, p0); } // 7C0043FDFF6436BC 0F11D01F
	static void _0x8AA9180DE2FEDD45(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x8AA9180DE2FEDD45, p0, p1); } // 8AA9180DE2FEDD45 AE040377
	static void _0x0A6A279F3AA4FD70(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x0A6A279F3AA4FD70, p0, p1); } // 0A6A279F3AA4FD70 4C0E4031
	static BOOL _0x634148744F385576(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x634148744F385576, p0); } // 634148744F385576 6346B7CC
	static void _0xE6F13851780394DA(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xE6F13851780394DA, p0, p1); } // E6F13851780394DA CCB41A55
	static void SET_VEHICLE_TYRE_BURST(scrAny p0, scrAny p1, BOOL p2, float p3) { NativeInvoke::Invoke<scrVoid>(0xEC6A202EE4960385, p0, p1, p2, p3); } // EC6A202EE4960385 89D28068
	static void SET_VEHICLE_DOORS_SHUT(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x781B3D62BB013EF5, p0, p1); } // 781B3D62BB013EF5 BB1FF6E7
	static void SET_VEHICLE_TYRES_CAN_BURST(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xEB9DC3C7D8596C46, p0, p1); } // EB9DC3C7D8596C46 A198DB54
	static BOOL GET_VEHICLE_TYRES_CAN_BURST(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x678B9BB8C3F58FEB, p0); } // 678B9BB8C3F58FEB 4D76CD2F
	static void SET_VEHICLE_WHEELS_CAN_BREAK(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x29B18B4FD460CA8F, p0, p1); } // 29B18B4FD460CA8F 829ED654
	static void SET_VEHICLE_DOOR_OPEN(scrAny p0, scrAny p1, BOOL p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x7C65DAC73C35C862, p0, p1, p2, p3); } // 7C65DAC73C35C862 BB75D38B
	static void REMOVE_VEHICLE_WINDOW(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xA711568EEDB43069, p0, p1); } // A711568EEDB43069 BB8104A3
	static void ROLL_DOWN_WINDOWS(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x85796B0549DDE156, p0); } // 85796B0549DDE156 51A16DC6
	static void ROLL_DOWN_WINDOW(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x7AD9E6CE657D69E3, p0, p1); } // 7AD9E6CE657D69E3 F840134C
	static void ROLL_UP_WINDOW(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x602E548F46E24D59, p0, p1); } // 602E548F46E24D59 83B7E06A
	static void SMASH_VEHICLE_WINDOW(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x9E5B5E4D2CCD2259, p0, p1); } // 9E5B5E4D2CCD2259 DDD9A8C2
	static void FIX_VEHICLE_WINDOW(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x772282EBEB95E682, p0, p1); } // 772282EBEB95E682 6B8E990D
	static void _0x6D645D59FB5F5AD3(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x6D645D59FB5F5AD3, p0); } // 6D645D59FB5F5AD3 CC95C96B
	static void _0xE38CB9D7D39FDBCC(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0xE38CB9D7D39FDBCC, p0, p1, p2, p3); } // E38CB9D7D39FDBCC FDA7B6CA
	static void SET_VEHICLE_LIGHTS(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x34E710FF01247C5A, p0, p1); } // 34E710FF01247C5A E8930226
	static void _0xC45C27EF50F36ADC(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xC45C27EF50F36ADC, p0, p1); } // C45C27EF50F36ADC 4221E435
	static void SET_VEHICLE_ALARM(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xCDE5E70C1DDB954C, p0, p1); } // CDE5E70C1DDB954C 24877D84
	static void START_VEHICLE_ALARM(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xB8FF7AB45305C345, p0); } // B8FF7AB45305C345 5B451FF7
	static BOOL IS_VEHICLE_ALARM_ACTIVATED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x4319E335B71FFF34, p0); } // 4319E335B71FFF34 F2630A4C
	static void SET_VEHICLE_INTERIORLIGHT(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xBC2042F090AF6AD3, p0, p1); } // BC2042F090AF6AD3 9AD1FE1E
	static void SET_VEHICLE_LIGHT_MULTIPLIER(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xB385454F8791F57C, p0, p1); } // B385454F8791F57C 48039D6A
	static void ATTACH_VEHICLE_TO_TRAILER(scrAny p0, scrAny p1, float p2) { NativeInvoke::Invoke<scrVoid>(0x3C7D42D58F770B54, p0, p1, p2); } // 3C7D42D58F770B54 2133977F
	static void _0x16B5E274BDE402F8(scrAny p0, scrAny p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11) { NativeInvoke::Invoke<scrVoid>(0x16B5E274BDE402F8, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 16B5E274BDE402F8 12AC1A16
	static void _0x374706271354CB18(scrAny p0, scrAny p1, float p2) { NativeInvoke::Invoke<scrVoid>(0x374706271354CB18, p0, p1, p2); } // 374706271354CB18 40C4763F
	static void DETACH_VEHICLE_FROM_TRAILER(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x90532EDF0D2BDD86, p0); } // 90532EDF0D2BDD86 B5DBF91D
	static BOOL IS_VEHICLE_ATTACHED_TO_TRAILER(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xE7CF3C4F9F489F0C, p0); } // E7CF3C4F9F489F0C E142BBCC
	static void _0x2A8F319B392E7B3F(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x2A8F319B392E7B3F, p0, p1); } // 2A8F319B392E7B3F E74E85CE
	static void _0x95CF53B3D687F9FA(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x95CF53B3D687F9FA, p0); } // 95CF53B3D687F9FA 06C47A6F
	static void SET_VEHICLE_TYRE_FIXED(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x6E13FC662B882D1D, p0, p1); } // 6E13FC662B882D1D A42EFA6B
	static void SET_VEHICLE_NUMBER_PLATE_TEXT(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x95A88F0B409CDA47, p0, p1); } // 95A88F0B409CDA47 400F9556
	static scrAny GET_VEHICLE_NUMBER_PLATE_TEXT(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x7CE1CCB9B293020E, p0); } // 7CE1CCB9B293020E E8522D58
	static scrAny GET_NUMBER_OF_VEHICLE_NUMBER_PLATES() { return NativeInvoke::Invoke<scrAny>(0x4C4D6B2644F458CB); } // 4C4D6B2644F458CB D24BC1AE
	static void SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x9088EB5A43FFB0A1, p0, p1); } // 9088EB5A43FFB0A1 A1A1890E
	static scrAny _0xF11BC2DD9A3E7195(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xF11BC2DD9A3E7195, p0); } // F11BC2DD9A3E7195 499747B6
	static void SET_RANDOM_TRAINS(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x80D9F74197EA47D9, p0); } // 80D9F74197EA47D9 D461CA7F
	static scrAny CREATE_MISSION_TRAIN(scrAny p0, float p1, float p2, float p3, BOOL p4) { return NativeInvoke::Invoke<scrAny>(0x63C6CCA8E68AE8C8, p0, p1, p2, p3, p4); } // 63C6CCA8E68AE8C8 D4C2EAFD
	static void SWITCH_TRAIN_TRACK(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xFD813BB7DB977F20, p0, p1); } // FD813BB7DB977F20 68BFDD61
	static void _0x21973BBF8D17EDFA(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x21973BBF8D17EDFA, p0, p1); } // 21973BBF8D17EDFA D5774FB7
	static void DELETE_ALL_TRAINS() { NativeInvoke::Invoke<scrVoid>(0x736A718577F39C7D); } // 736A718577F39C7D 83DE7ABF
	static void SET_TRAIN_SPEED(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xAA0BC91BE0B796E3, p0, p1); } // AA0BC91BE0B796E3 DFC35E4D
	static void SET_TRAIN_CRUISE_SPEED(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x16469284DB8C62B5, p0, p1); } // 16469284DB8C62B5 B507F51D
	static void SET_RANDOM_BOATS(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x84436EC293B1415F, p0); } // 84436EC293B1415F B505BD89
	static void SET_GARBAGE_TRUCKS(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x2AFD795EEAC8D30D, p0); } // 2AFD795EEAC8D30D D9ABB0FF
	static BOOL DOES_VEHICLE_HAVE_STUCK_VEHICLE_CHECK(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x57E4C39DE5EE8470, p0); } // 57E4C39DE5EE8470 5D91D9AC
	static scrAny GET_VEHICLE_RECORDING_ID(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<scrAny>(0x21543C612379DB3C, p0, p1); } // 21543C612379DB3C 328D601D
	static void REQUEST_VEHICLE_RECORDING(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xAF514CABE74CBF15, p0, p1); } // AF514CABE74CBF15 91AFEFD9
	static BOOL HAS_VEHICLE_RECORDING_BEEN_LOADED(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x300D614A4C785FC4, p0, p1); } // 300D614A4C785FC4 F52CD7F5
	static void REMOVE_VEHICLE_RECORDING(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xF1160ACCF98A3FC8, p0, p1); } // F1160ACCF98A3FC8 D3C05B00
	static scrVector3 _0x92523B76657A517D(scrAny p0, float p1) { return NativeInvoke::Invoke<scrVector3>(0x92523B76657A517D, p0, p1); } // 92523B76657A517D F31973BB
	static scrVector3 GET_POSITION_OF_VEHICLE_RECORDING_AT_TIME(scrAny p0, float p1, scrAny *p2) { return NativeInvoke::Invoke<scrVector3>(0xD242728AA6F0FBA2, p0, p1, p2); } // D242728AA6F0FBA2 7178558D
	static scrVector3 _0xF0F2103EFAF8CBA7(scrAny p0, float p1) { return NativeInvoke::Invoke<scrVector3>(0xF0F2103EFAF8CBA7, p0, p1); } // F0F2103EFAF8CBA7 4D1C15C2
	static scrVector3 GET_ROTATION_OF_VEHICLE_RECORDING_AT_TIME(scrAny p0, float p1, scrAny *p2) { return NativeInvoke::Invoke<scrVector3>(0x2058206FBE79A8AD, p0, p1, p2); } // 2058206FBE79A8AD D96DEC68
	static float GET_TOTAL_DURATION_OF_VEHICLE_RECORDING_ID(scrAny p0) { return NativeInvoke::Invoke<float>(0x102D125411A7B6E6, p0); } // 102D125411A7B6E6 7116785E
	static scrAny GET_TOTAL_DURATION_OF_VEHICLE_RECORDING(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x0E48D1C262390950, p0, p1); } // 0E48D1C262390950 5B35EEB7
	static float GET_POSITION_IN_RECORDING(scrAny p0) { return NativeInvoke::Invoke<float>(0x2DACD605FC681475, p0); } // 2DACD605FC681475 7DCD644C
	static float GET_TIME_POSITION_IN_RECORDING(scrAny p0) { return NativeInvoke::Invoke<float>(0x5746F3A7AB7FE544, p0); } // 5746F3A7AB7FE544 F8C3E4A2
	static void START_PLAYBACK_RECORDED_VEHICLE(scrAny p0, scrAny p1, scrAny *p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x3F878F92B3A7A071, p0, p1, p2, p3); } // 3F878F92B3A7A071 CF614CA8
	static void START_PLAYBACK_RECORDED_VEHICLE_WITH_FLAGS(scrAny p0, scrAny p1, scrAny *p2, scrAny p3, scrAny p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0x7D80FD645D4DA346, p0, p1, p2, p3, p4, p5); } // 7D80FD645D4DA346 4E721AD2
	static void _0x1F2E4E06DEA8992B(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x1F2E4E06DEA8992B, p0, p1); } // 1F2E4E06DEA8992B 01B91CD0
	static void STOP_PLAYBACK_RECORDED_VEHICLE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x54833611C17ABDEA, p0); } // 54833611C17ABDEA AE99C57C
	static void PAUSE_PLAYBACK_RECORDED_VEHICLE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x632A689BF42301B1, p0); } // 632A689BF42301B1 CCF54912
	static void UNPAUSE_PLAYBACK_RECORDED_VEHICLE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x8879EE09268305D5, p0); } // 8879EE09268305D5 59060F75
	static BOOL IS_PLAYBACK_GOING_ON_FOR_VEHICLE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x1C8A4C2C19E68EEC, p0); } // 1C8A4C2C19E68EEC 61F7650D
	static BOOL IS_PLAYBACK_USING_AI_GOING_ON_FOR_VEHICLE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xAEA8FD591FAD4106, p0); } // AEA8FD591FAD4106 63022C58
	static scrAny GET_CURRENT_PLAYBACK_FOR_VEHICLE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x42BC05C27A946054, p0); } // 42BC05C27A946054 A3F44390
	static void SKIP_TO_END_AND_STOP_PLAYBACK_RECORDED_VEHICLE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xAB8E2EDA0C0A5883, p0); } // AB8E2EDA0C0A5883 8DEA18C8
	static void SET_PLAYBACK_SPEED(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x6683AB880E427778, p0, p1); } // 6683AB880E427778 684E26E4
	static void START_PLAYBACK_RECORDED_VEHICLE_USING_AI(scrAny p0, scrAny p1, scrAny *p2, float p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x29DE5FA52D00428C, p0, p1, p2, p3, p4); } // 29DE5FA52D00428C 8DE8E24E
	static void SKIP_TIME_IN_PLAYBACK_RECORDED_VEHICLE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x9438F7AD68771A20, p0, p1); } // 9438F7AD68771A20 CF3EFA4B
	static void SET_PLAYBACK_TO_USE_AI(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xA549C3B37EA28131, p0, p1); } // A549C3B37EA28131 B536CCD7
	static void SET_PLAYBACK_TO_USE_AI_TRY_TO_REVERT_BACK_LATER(scrAny p0, scrAny p1, scrAny p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x6E63860BBB190730, p0, p1, p2, p3); } // 6E63860BBB190730 0C8ABAA4
	static void _0x5845066D8A1EA7F7(scrAny p0, float p1, float p2, float p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x5845066D8A1EA7F7, p0, p1, p2, p3, p4); } // 5845066D8A1EA7F7 943A58EB
	static void _0x796A877E459B99EA(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x796A877E459B99EA, p0, p1, p2, p3); } // 796A877E459B99EA 5C9F477C
	static void _0xFAF2A78061FD9EF4(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0xFAF2A78061FD9EF4, p0, p1, p2, p3); } // FAF2A78061FD9EF4 CD83C393
	static void _0x063AE2B2CC273588(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x063AE2B2CC273588, p0, p1); } // 063AE2B2CC273588 2EF8435C
	static void EXPLODE_VEHICLE_IN_CUTSCENE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x786A4EB67B01BF0B, p0, p1); } // 786A4EB67B01BF0B A85207B5
	static void ADD_VEHICLE_STUCK_CHECK_WITH_WARP(scrAny p0, float p1, scrAny p2, BOOL p3, BOOL p4, BOOL p5, scrAny p6) { NativeInvoke::Invoke<scrVoid>(0x2FA9923062DD396C, p0, p1, p2, p3, p4, p5, p6); } // 2FA9923062DD396C C8B789AD
	static void SET_VEHICLE_MODEL_IS_SUPPRESSED(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x0FC2D89AC25A5814, p0, p1); } // 0FC2D89AC25A5814 42A08C9B
	static scrAny GET_RANDOM_VEHICLE_IN_SPHERE(float p0, float p1, float p2, float p3, scrAny p4, scrAny p5) { return NativeInvoke::Invoke<scrAny>(0x386F6CE5BAF6091C, p0, p1, p2, p3, p4, p5); } // 386F6CE5BAF6091C 57216D03
	static scrAny GET_RANDOM_VEHICLE_FRONT_BUMPER_IN_SPHERE(float p0, float p1, float p2, float p3, scrAny p4, scrAny p5, scrAny p6) { return NativeInvoke::Invoke<scrAny>(0xC5574E0AEB86BA68, p0, p1, p2, p3, p4, p5, p6); } // C5574E0AEB86BA68 DCADEB66
	static scrAny GET_RANDOM_VEHICLE_BACK_BUMPER_IN_SPHERE(float p0, float p1, float p2, float p3, scrAny p4, scrAny p5, scrAny p6) { return NativeInvoke::Invoke<scrAny>(0xB50807EABE20A8DC, p0, p1, p2, p3, p4, p5, p6); } // B50807EABE20A8DC D6343F6B
	static scrAny GET_CLOSEST_VEHICLE(float p0, float p1, float p2, float p3, scrAny p4, scrAny p5) { return NativeInvoke::Invoke<scrAny>(0xF73EB622C4F1689B, p0, p1, p2, p3, p4, p5); } // F73EB622C4F1689B D7E26B2C
	static scrAny GET_TRAIN_CARRIAGE(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x08AAFD0814722BC3, p0, p1); } // 08AAFD0814722BC3 2544E7A6
	static void DELETE_MISSION_TRAIN(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x5B76B14AE875C795, p0); } // 5B76B14AE875C795 86C9497D
	static void SET_MISSION_TRAIN_AS_NO_LONGER_NEEDED(scrAny *p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xBBE7648349B49BE8, p0, p1); } // BBE7648349B49BE8 19808560
	static void SET_MISSION_TRAIN_COORDS(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x591CA673AA6AB736, p0, p1, p2, p3); } // 591CA673AA6AB736 D6D70803
	static BOOL IS_THIS_MODEL_A_BOAT(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x45A9187928F4B9E3, p0); } // 45A9187928F4B9E3 10F6085C
	static BOOL _0x9537097412CF75FE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x9537097412CF75FE, p0); } // 9537097412CF75FE
	static BOOL IS_THIS_MODEL_A_PLANE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xA0948AB42D7BA0DE, p0); } // A0948AB42D7BA0DE 3B3907BB
	static BOOL IS_THIS_MODEL_A_HELI(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xDCE4334788AF94EA, p0); } // DCE4334788AF94EA 8AF7F568
	static BOOL IS_THIS_MODEL_A_CAR(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x7F6DB52EEFC96DF8, p0); } // 7F6DB52EEFC96DF8 60E4C22F
	static BOOL IS_THIS_MODEL_A_TRAIN(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xAB935175B22E822B, p0); } // AB935175B22E822B F87DCFFD
	static BOOL IS_THIS_MODEL_A_BIKE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xB50C0B0CEDC6CE84, p0); } // B50C0B0CEDC6CE84 7E702CDD
	static BOOL IS_THIS_MODEL_A_BICYCLE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xBF94DD42F63BDED2, p0); } // BF94DD42F63BDED2 328E6FF5
	static BOOL IS_THIS_MODEL_A_QUADBIKE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x39DAC362EE65FA28, p0); } // 39DAC362EE65FA28 C1625277
	static void SET_HELI_BLADES_FULL_SPEED(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA178472EBB8AE60D, p0); } // A178472EBB8AE60D 033A9408
	static void SET_HELI_BLADES_SPEED(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xFD280B4D7F3ABC4D, p0, p1); } // FD280B4D7F3ABC4D 5C7D4EA9
	static void _0x99CAD8E7AFDB60FA(scrAny p0, float p1, float p2) { NativeInvoke::Invoke<scrVoid>(0x99CAD8E7AFDB60FA, p0, p1, p2); } // 99CAD8E7AFDB60FA 1128A45B
	static void SET_VEHICLE_CAN_BE_TARGETTED(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x3750146A28097A82, p0, p1); } // 3750146A28097A82 64B70B1D
	static void _0xDBC631F109350B8C(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xDBC631F109350B8C, p0, p1); } // DBC631F109350B8C 486C1280
	static void SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x4C7028F78FFD3681, p0, p1); } // 4C7028F78FFD3681 C5D94017
	static void _0x1AA8A837D2169D94(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x1AA8A837D2169D94, p0, p1); } // 1AA8A837D2169D94 009AB49E
	static void _0x2311DD7159F00582(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x2311DD7159F00582, p0, p1); } // 2311DD7159F00582 758C5E2E
	static scrAny GET_VEHICLE_DIRT_LEVEL(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x8F17BC8BA08DA62B, p0); } // 8F17BC8BA08DA62B FD15C065
	static void SET_VEHICLE_DIRT_LEVEL(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x79D3B596FE44EE8B, p0, p1); } // 79D3B596FE44EE8B 2B39128B
	static BOOL _0xBCDC5017D3CE1E9E(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xBCDC5017D3CE1E9E, p0); } // BCDC5017D3CE1E9E DAC523BC
	static BOOL IS_VEHICLE_DOOR_FULLY_OPEN(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x3E933CFF7B111C22, p0, p1); } // 3E933CFF7B111C22 C2385B6F
	static void SET_VEHICLE_ENGINE_ON(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x2497C4717C8B881E, p0, p1, p2); } // 2497C4717C8B881E 7FBC86F1
	static void SET_VEHICLE_UNDRIVEABLE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x8ABA6AF54B942B95, p0, p1); } // 8ABA6AF54B942B95 48D02A4E
	static void SET_VEHICLE_PROVIDES_COVER(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x5AFEEDD9BB2899D7, p0, p1); } // 5AFEEDD9BB2899D7 EFC01CA9
	static void SET_VEHICLE_DOOR_CONTROL(scrAny p0, scrAny p1, scrAny p2, float p3) { NativeInvoke::Invoke<scrVoid>(0xF2BFA0430F0A0FCB, p0, p1, p2, p3); } // F2BFA0430F0A0FCB 572DD360
	static void SET_VEHICLE_DOOR_LATCHED(scrAny p0, scrAny p1, BOOL p2, BOOL p3, BOOL p4) { NativeInvoke::Invoke<scrVoid>(0xA5A9653A8D2CAF48, p0, p1, p2, p3, p4); } // A5A9653A8D2CAF48 4EB7BBFC
	static float GET_VEHICLE_DOOR_ANGLE_RATIO(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<float>(0xFE3F9C29F7B32BD5, p0, p1); } // FE3F9C29F7B32BD5 0E399C26
	static void SET_VEHICLE_DOOR_SHUT(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x93D9BD300D7789E5, p0, p1, p2); } // 93D9BD300D7789E5 142606BD
	static void SET_VEHICLE_DOOR_BROKEN(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xD4D4F6A4AB575A33, p0, p1, p2); } // D4D4F6A4AB575A33 8147FEA7
	static void SET_VEHICLE_CAN_BREAK(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x59BF8C3D52C92F66, p0, p1); } // 59BF8C3D52C92F66 90A810D1
	static BOOL DOES_VEHICLE_HAVE_ROOF(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x8AC862B0B32C5B80, p0); } // 8AC862B0B32C5B80 DB817403
	static BOOL IS_BIG_VEHICLE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x9F243D3919F442FE, p0); } // 9F243D3919F442FE 9CDBA8DE
	static scrAny GET_NUMBER_OF_VEHICLE_COLOURS(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x3B963160CD65D41E, p0); } // 3B963160CD65D41E F2442EE2
	static void SET_VEHICLE_COLOUR_COMBINATION(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x33E8CD3322E2FE31, p0, p1); } // 33E8CD3322E2FE31 A557AEAD
	static scrAny GET_VEHICLE_COLOUR_COMBINATION(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x6A842D197F845D56, p0); } // 6A842D197F845D56 77AC1B4C
	static void SET_VEHICLE_IS_CONSIDERED_BY_PLAYER(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x31B927BBC44156CD, p0, p1); } // 31B927BBC44156CD 14413319
	static void _0xBE5C1255A1830FF5(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xBE5C1255A1830FF5, p0, p1); } // BE5C1255A1830FF5 A6D8D7A5
	static void _0x9BECD4B9FEF3F8A6(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x9BECD4B9FEF3F8A6, p0, p1); } // 9BECD4B9FEF3F8A6 ACAB8FF3
	static void _0x88BC673CA9E0AE99(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x88BC673CA9E0AE99, p0, p1); } // 88BC673CA9E0AE99 F0E5C41D
	static void _0xE851E480B814D4BA(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xE851E480B814D4BA, p0, p1); } // E851E480B814D4BA 2F98B4B7
	static void GET_RANDOM_VEHICLE_MODEL_IN_MEMORY(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x055BF0AC0C34F4FD, p0, p1, p2); } // 055BF0AC0C34F4FD E2C45631
	static scrAny GET_VEHICLE_DOOR_LOCK_STATUS(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x25BC98A59C2EA962, p0); } // 25BC98A59C2EA962 0D72CEF2
	static BOOL IS_VEHICLE_DOOR_DAMAGED(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xB8E181E559464527, p0, p1); } // B8E181E559464527 4999E3C3
	static void _0x2FA133A4A9D37ED8(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x2FA133A4A9D37ED8, p0, p1, p2); } // 2FA133A4A9D37ED8 065B92B3
	static BOOL _0x27B926779DEB502D(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<BOOL>(0x27B926779DEB502D, p0, p1); } // 27B926779DEB502D B3A2CC4F
	static BOOL IS_VEHICLE_BUMPER_BROKEN_OFF(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<BOOL>(0x468056A6BB6F3846, p0, p1); } // 468056A6BB6F3846 AF25C027
	static BOOL IS_COP_VEHICLE_IN_AREA_3D(float p0, float p1, float p2, float p3, float p4, float p5) { return NativeInvoke::Invoke<BOOL>(0x7EEF65D5F153E26A, p0, p1, p2, p3, p4, p5); } // 7EEF65D5F153E26A FB16C6D1
	static BOOL IS_VEHICLE_ON_ALL_WHEELS(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xB104CD1BABF302E2, p0); } // B104CD1BABF302E2 10089F8E
	static scrAny GET_VEHICLE_LAYOUT_HASH(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x28D37D4F71AC5C58, p0); } // 28D37D4F71AC5C58 E0B35187
	static void SET_RENDER_TRAIN_AS_DERAILED(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x317B11A312DF5534, p0, p1); } // 317B11A312DF5534 899D9092
	static void SET_VEHICLE_EXTRA_COLOURS(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x2036F561ADD12E33, p0, p1, p2); } // 2036F561ADD12E33 515DB2A0
	static void GET_VEHICLE_EXTRA_COLOURS(scrAny p0, scrAny *p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0x3BC4245933A166F7, p0, p1, p2); } // 3BC4245933A166F7 80E4659B
	static void STOP_ALL_GARAGE_ACTIVITY() { NativeInvoke::Invoke<scrVoid>(0x0F87E938BDF29D66); } // 0F87E938BDF29D66 17A0BCE5
	static void SET_VEHICLE_FIXED(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x115722B1B9C14C1C, p0); } // 115722B1B9C14C1C 17469AA1
	static void SET_VEHICLE_DEFORMATION_FIXED(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x953DA1E1B12C0491, p0); } // 953DA1E1B12C0491 DD2920C8
	static void _0x51BB2D88D31A914B(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x51BB2D88D31A914B, p0, p1); } // 51BB2D88D31A914B 88F0F7E7
	static void _0x192547247864DFDD(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x192547247864DFDD, p0, p1); } // 192547247864DFDD 90D6EE57
	static void _0x465BF26AB9684352(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x465BF26AB9684352, p0, p1); } // 465BF26AB9684352 C40192B5
	static void _0x37C8252A7C92D017(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x37C8252A7C92D017, p0, p1); } // 37C8252A7C92D017 AD3E05F2
	static void _0x91A0BD635321F145(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x91A0BD635321F145, p0, p1); } // 91A0BD635321F145 1784BA1A
	static void _0xC50CE861B55EAB8B(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xC50CE861B55EAB8B, p0, p1); } // C50CE861B55EAB8B 40C323AE
	static void _0x6EBFB22D646FFC18(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x6EBFB22D646FFC18, p0, p1); } // 6EBFB22D646FFC18 847F1304
	static void _0x25367DE49D64CF16(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x25367DE49D64CF16, p0, p1); } // 25367DE49D64CF16 CBD98BA1
	static void REMOVE_VEHICLES_FROM_GENERATORS_IN_AREA(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0x46A1E1A299EC4BBA, p0, p1, p2, p3, p4, p5); } // 46A1E1A299EC4BBA 42CC15E0
	static void SET_VEHICLE_STEER_BIAS(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x42A8EC77D5150CBE, p0, p1); } // 42A8EC77D5150CBE 7357C1EB
	static BOOL IS_VEHICLE_EXTRA_TURNED_ON(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xD2E6822DBFD6C8BD, p0, p1); } // D2E6822DBFD6C8BD 042098B5
	static void SET_VEHICLE_EXTRA(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x7EE3A3C5E4A40CC9, p0, p1, p2); } // 7EE3A3C5E4A40CC9 642D065C
	static BOOL DOES_EXTRA_EXIST(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x1262D55792428154, p0, p1); } // 1262D55792428154 409411CC
	static void SET_CONVERTIBLE_ROOF(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xF39C4F538B5124C2, p0, p1); } // F39C4F538B5124C2 C87B6A51
	static void LOWER_CONVERTIBLE_ROOF(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xDED51F703D0FA83D, p0, p1); } // DED51F703D0FA83D C5F72EAE
	static void RAISE_CONVERTIBLE_ROOF(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x8F5FB35D7E88FC70, p0, p1); } // 8F5FB35D7E88FC70 A4E4CBA3
	static scrAny GET_CONVERTIBLE_ROOF_STATE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xF8C397922FC03F41, p0); } // F8C397922FC03F41 1B09714D
	static BOOL IS_VEHICLE_A_CONVERTIBLE(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<BOOL>(0x52F357A30698BCCE, p0, p1); } // 52F357A30698BCCE 6EF54490
	static BOOL IS_VEHICLE_STOPPED_AT_TRAFFIC_LIGHTS(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x2959F696AE390A99, p0); } // 2959F696AE390A99 69200FA4
	static void SET_VEHICLE_DAMAGE(scrAny p0, float p1, float p2, float p3, float p4, float p5, BOOL p6) { NativeInvoke::Invoke<scrVoid>(0xA1DD317EA8FD4F29, p0, p1, p2, p3, p4, p5, p6); } // A1DD317EA8FD4F29 21B458B2
	static float GET_VEHICLE_ENGINE_HEALTH(scrAny p0) { return NativeInvoke::Invoke<float>(0xC45D23BAF168AAB8, p0); } // C45D23BAF168AAB8 8880038A
	static void SET_VEHICLE_ENGINE_HEALTH(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x45F6D8EEF34ABEF1, p0, p1); } // 45F6D8EEF34ABEF1 1B760FB5
	static float GET_VEHICLE_PETROL_TANK_HEALTH(scrAny p0) { return NativeInvoke::Invoke<float>(0x7D5DABE888D2D074, p0); } // 7D5DABE888D2D074 E41595CE
	static void SET_VEHICLE_PETROL_TANK_HEALTH(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x70DB57649FA8D0D8, p0, p1); } // 70DB57649FA8D0D8 660A3692
	static BOOL IS_VEHICLE_STUCK_TIMER_UP(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0x679BE1DAF71DA874, p0, p1, p2); } // 679BE1DAF71DA874 2FCF58C1
	static void RESET_VEHICLE_STUCK_TIMER(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xD7591B0065AFAA7A, p0, p1); } // D7591B0065AFAA7A EF2A6016
	static BOOL IS_VEHICLE_DRIVEABLE(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<BOOL>(0x4C241E39B23DF959, p0, p1); } // 4C241E39B23DF959 41A7267A
	static void SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x2B5F9D2AF1F1722D, p0, p1); } // 2B5F9D2AF1F1722D B4D3DBFB
	static void SET_VEHICLE_NEEDS_TO_BE_HOTWIRED(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xFBA550EA44404EE6, p0, p1); } // FBA550EA44404EE6 D8260751
	static void START_VEHICLE_HORN(scrAny p0, scrAny p1, scrAny p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x9C8C6504B5B63D2C, p0, p1, p2, p3); } // 9C8C6504B5B63D2C 0DF5ADB3
	static void _0x9D44FCCE98450843(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x9D44FCCE98450843, p0, p1); } // 9D44FCCE98450843 968E5770
	static void SET_VEHICLE_HAS_STRONG_AXLES(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x92F0CF722BC4202F, p0, p1); } // 92F0CF722BC4202F 0D1CBC65
	static scrAny GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xB215AAC32D25D019, p0); } // B215AAC32D25D019 EC86DF39
	static scrVector3 GET_VEHICLE_DEFORMATION_AT_POS(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<scrVector3>(0x4EC6CFBC7B2E9536, p0, p1, p2, p3); } // 4EC6CFBC7B2E9536 ABF02075
	static void SET_VEHICLE_LIVERY(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x60BF608F1B8CD1B6, p0, p1); } // 60BF608F1B8CD1B6 7AD87059
	static scrAny GET_VEHICLE_LIVERY(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x2BB9230590DA5E8A, p0); } // 2BB9230590DA5E8A EC82A51D
	static scrAny GET_VEHICLE_LIVERY_COUNT(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x87B63E25A529D526, p0); } // 87B63E25A529D526 FB0CA947
	static BOOL IS_VEHICLE_WINDOW_INTACT(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x46E571A0E20D01F1, p0, p1); } // 46E571A0E20D01F1 AC4EF23D
	static BOOL _0x11D862A3E977A9EF(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x11D862A3E977A9EF, p0); } // 11D862A3E977A9EF BB619744
	static BOOL _0x2D34FC3BC4ADB780(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x2D34FC3BC4ADB780, p0); } // 2D34FC3BC4ADB780 648E685A
	static void RESET_VEHICLE_WHEELS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x21D2E5662C1F6FED, p0, p1); } // 21D2E5662C1F6FED D5FFE779
	static BOOL IS_HELI_PART_BROKEN(scrAny p0, BOOL p1, BOOL p2, BOOL p3) { return NativeInvoke::Invoke<BOOL>(0xBC74B4BE25EB6C8A, p0, p1, p2, p3); } // BC74B4BE25EB6C8A F4E4C439
	static float _0xE4CB7541F413D2C5(scrAny p0) { return NativeInvoke::Invoke<float>(0xE4CB7541F413D2C5, p0); } // E4CB7541F413D2C5 F01E2AAB
	static float _0xAE8CE82A4219AC8C(scrAny p0) { return NativeInvoke::Invoke<float>(0xAE8CE82A4219AC8C, p0); } // AE8CE82A4219AC8C A41BC13D
	static float _0xAC51915D27E4A5F7(scrAny p0) { return NativeInvoke::Invoke<float>(0xAC51915D27E4A5F7, p0); } // AC51915D27E4A5F7 8A68388F
	static scrAny WAS_COUNTER_ACTIVATED(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x3EC8BF18AA453FE9, p0, p1); } // 3EC8BF18AA453FE9 2916D69B
	static void SET_VEHICLE_NAME_DEBUG(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xBFDF984E2C22B94F, p0, p1); } // BFDF984E2C22B94F A712FF5C
	static void SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x71B0892EC081D60A, p0, p1); } // 71B0892EC081D60A 38CC692B
	static void _0x3441CAD2F2231923(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x3441CAD2F2231923, p0, p1); } // 3441CAD2F2231923 C306A9A3
	static void _0x2B6747FAA9DB9D6B(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x2B6747FAA9DB9D6B, p0, p1); } // 2B6747FAA9DB9D6B 95A9ACCB
	static void _0xCFC8BE9A5E1FE575(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xCFC8BE9A5E1FE575, p0, p1); } // CFC8BE9A5E1FE575 24F873FB
	static scrAny _0x9B0F3DCA3DB0F4CD(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x9B0F3DCA3DB0F4CD, p0); } // 9B0F3DCA3DB0F4CD A6F02670
	static BOOL IS_ANY_VEHICLE_NEAR_POINT(float p0, float p1, float p2, float p3) { return NativeInvoke::Invoke<BOOL>(0x61E1DD6125A3EEE6, p0, p1, p2, p3); } // 61E1DD6125A3EEE6 2867A834
	static void REQUEST_VEHICLE_HIGH_DETAIL_MODEL(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA6E9FDCB2C76785E, p0); } // A6E9FDCB2C76785E 9DA21956
	static void REMOVE_VEHICLE_HIGH_DETAIL_MODEL(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x00689CDE5F7C6787, p0); } // 00689CDE5F7C6787 382BE070
	static BOOL IS_VEHICLE_HIGH_DETAIL(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x1F25887F3C104278, p0); } // 1F25887F3C104278 55D41928
	static void REQUEST_VEHICLE_ASSET(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x81A15811460FAB3A, p0, p1); } // 81A15811460FAB3A 902B4F06
	static BOOL HAS_VEHICLE_ASSET_LOADED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x1BBE0523B8DB9A21, p0); } // 1BBE0523B8DB9A21 8DAAC3CB
	static void REMOVE_VEHICLE_ASSET(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xACE699C71AB9DEB5, p0); } // ACE699C71AB9DEB5 9620E9C6
	static void _0xFE54B92A344583CA(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xFE54B92A344583CA, p0, p1); } // FE54B92A344583CA 88236E22
	static void ATTACH_VEHICLE_TO_TOW_TRUCK(scrAny p0, scrAny p1, scrAny p2, float p3, float p4, float p5) { NativeInvoke::Invoke<scrVoid>(0x29A16F8D621C4508, p0, p1, p2, p3, p4, p5); } // 29A16F8D621C4508 8151571A
	static void DETACH_VEHICLE_FROM_TOW_TRUCK(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xC2DB6B6708350ED8, p0, p1); } // C2DB6B6708350ED8 C666CF33
	static BOOL DETACH_VEHICLE_FROM_ANY_TOW_TRUCK(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xD0E9CE05A1E68CD8, p0); } // D0E9CE05A1E68CD8 3BF93651
	static BOOL IS_VEHICLE_ATTACHED_TO_TOW_TRUCK(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x146DF9EC4C4B9FD4, p0, p1); } // 146DF9EC4C4B9FD4 9699CFDC
	static scrAny GET_ENTITY_ATTACHED_TO_TOW_TRUCK(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xEFEA18DCF10F8F75, p0); } // EFEA18DCF10F8F75 11EC7844
	static scrAny SET_VEHICLE_AUTOMATICALLY_ATTACHES(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0x8BA6F76BC53A1493, p0, p1, p2); } // 8BA6F76BC53A1493 4273A8D3
	static void _0xF8EBCCC96ADB9FB7(scrAny p0, float p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xF8EBCCC96ADB9FB7, p0, p1, p2); } // F8EBCCC96ADB9FB7 ED23C8A3
	static void _0x56B94C6D7127DFBA(scrAny p0, float p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x56B94C6D7127DFBA, p0, p1, p2); } // 56B94C6D7127DFBA B1A52EF7
	static void _0x1093408B4B9D1146(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x1093408B4B9D1146, p0, p1); } // 1093408B4B9D1146 F30C566F
	static void _0x30D779DE7C4F6DD3(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x30D779DE7C4F6DD3, p0, p1); } // 30D779DE7C4F6DD3 A7DF64D7
	static void _0x9AA47FFF660CB932(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x9AA47FFF660CB932, p0, p1); } // 9AA47FFF660CB932 DD7936F5
	static scrAny _0xA4822F1CF23F4810(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8) { return NativeInvoke::Invoke<scrAny>(0xA4822F1CF23F4810, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // A4822F1CF23F4810 34E02FCD
	static void SET_VEHICLE_BURNOUT(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xFB8794444A7D60FB, p0, p1); } // FB8794444A7D60FB 9B6EF0EA
	static BOOL IS_VEHICLE_IN_BURNOUT(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x1297A88E081430EB, p0); } // 1297A88E081430EB 6632BC12
	static void SET_VEHICLE_REDUCE_GRIP(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x222FF6A823D122E2, p0, p1); } // 222FF6A823D122E2 90D3A0D9
	static void SET_VEHICLE_INDICATOR_LIGHTS(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xB5D45264751B7DF0, p0, p1, p2); } // B5D45264751B7DF0 A6073B5D
	static void SET_VEHICLE_BRAKE_LIGHTS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x92B35082E0B42F66, p0, p1); } // 92B35082E0B42F66 6D9BA11E
	static void SET_VEHICLE_HANDBRAKE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x684785568EF26A22, p0, p1); } // 684785568EF26A22 BA729A25
	static void _0x48ADC8A773564670() { NativeInvoke::Invoke<scrVoid>(0x48ADC8A773564670); } // 48ADC8A773564670 37BC6ACB
	static BOOL _0x91D6DD290888CBAB() { return NativeInvoke::Invoke<BOOL>(0x91D6DD290888CBAB); } // 91D6DD290888CBAB 71D898EF
	static void _0x51DB102F4A3BA5E0(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x51DB102F4A3BA5E0, p0); } // 51DB102F4A3BA5E0 0B0523B0
	static BOOL GET_VEHICLE_TRAILER_VEHICLE(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x1CDD6BADC297830D, p0, p1); } // 1CDD6BADC297830D AE84D758
	static void _0xCAC66558B944DA67(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xCAC66558B944DA67, p0, p1); } // CAC66558B944DA67 0B200CE2
	static void SET_VEHICLE_RUDDER_BROKEN(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x09606148B6C71DEF, p0, p1); } // 09606148B6C71DEF 3FAC3CD4
	static void _0x1A78AD3D8240536F(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x1A78AD3D8240536F, p0, p1); } // 1A78AD3D8240536F 0858678C
	static scrAny _0x53AF99BAA671CA47(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x53AF99BAA671CA47, p0); } // 53AF99BAA671CA47 7D1A0616
	static float GET_VEHICLE_MAX_BRAKING(scrAny p0) { return NativeInvoke::Invoke<float>(0xAD7E85FC227197C4, p0); } // AD7E85FC227197C4 03B926F6
	static float GET_VEHICLE_MAX_TRACTION(scrAny p0) { return NativeInvoke::Invoke<float>(0xA132FB5370554DB0, p0); } // A132FB5370554DB0 7E5A1587
	static float GET_VEHICLE_ACCELERATION(scrAny p0) { return NativeInvoke::Invoke<float>(0x5DD35C8D074E57AE, p0); } // 5DD35C8D074E57AE 00478321
	static float _0xF417C2502FFFED43(scrAny p0) { return NativeInvoke::Invoke<float>(0xF417C2502FFFED43, p0); } // F417C2502FFFED43 8F291C4A
	static float GET_VEHICLE_MODEL_MAX_BRAKING(scrAny p0) { return NativeInvoke::Invoke<float>(0xDC53FD41B4ED944C, p0); } // DC53FD41B4ED944C 7EF02883
	static float _0xBFBA3BA79CFF7EBF(scrAny p0) { return NativeInvoke::Invoke<float>(0xBFBA3BA79CFF7EBF, p0); } // BFBA3BA79CFF7EBF F3A7293F
	static float GET_VEHICLE_MODEL_MAX_TRACTION(scrAny p0) { return NativeInvoke::Invoke<float>(0x539DE94D44FDFD0D, p0); } // 539DE94D44FDFD0D 7F985597
	static float GET_VEHICLE_MODEL_ACCELERATION(scrAny p0) { return NativeInvoke::Invoke<float>(0x8C044C5C84505B6A, p0); } // 8C044C5C84505B6A 29CB3537
	static float _0x53409B5163D5B846(scrAny p0) { return NativeInvoke::Invoke<float>(0x53409B5163D5B846, p0); } // 53409B5163D5B846 37FBA7BC
	static float _0xC6AD107DDC9054CC(scrAny p0) { return NativeInvoke::Invoke<float>(0xC6AD107DDC9054CC, p0); } // C6AD107DDC9054CC 95BB67EB
	static float _0x5AA3F878A178C4FC(scrAny p0) { return NativeInvoke::Invoke<float>(0x5AA3F878A178C4FC, p0); } // 5AA3F878A178C4FC 87C5D271
	static scrAny _0x00C09F246ABEDD82(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x00C09F246ABEDD82, p0); } // 00C09F246ABEDD82 CE67162C
	static float GET_VEHICLE_CLASS_MAX_TRACTION(scrAny p0) { return NativeInvoke::Invoke<float>(0xDBC86D85C5059461, p0); } // DBC86D85C5059461 5B4FDC16
	static float GET_VEHICLE_CLASS_MAX_AGILITY(scrAny p0) { return NativeInvoke::Invoke<float>(0x4F930AD022D6DE3B, p0); } // 4F930AD022D6DE3B 45F2BD83
	static float GET_VEHICLE_CLASS_MAX_ACCELERATION(scrAny p0) { return NativeInvoke::Invoke<float>(0x2F83E7E45D9EA7AE, p0); } // 2F83E7E45D9EA7AE 3E220A9B
	static float GET_VEHICLE_CLASS_MAX_BRAKING(scrAny p0) { return NativeInvoke::Invoke<float>(0x4BF54C16EC8FEC03, p0); } // 4BF54C16EC8FEC03 D08CC1A5
	static scrAny _0x2CE544C68FB812A0(float p0, float p1, float p2, float p3, float p4, BOOL p5) { return NativeInvoke::Invoke<scrAny>(0x2CE544C68FB812A0, p0, p1, p2, p3, p4, p5); } // 2CE544C68FB812A0 D6685803
	static BOOL _0x1033371FC8E842A7(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x1033371FC8E842A7, p0); } // 1033371FC8E842A7 0C0332A6
	static void _0x87E7F24270732CB1(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x87E7F24270732CB1, p0); } // 87E7F24270732CB1 6574041D
	static void _0x3556041742A0DC74(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x3556041742A0DC74, p0); } // 3556041742A0DC74 F8EC5751
	static BOOL IS_VEHICLE_SEARCHLIGHT_ON(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xC0F97FCE55094987, p0); } // C0F97FCE55094987 ADAF3513
	static void SET_VEHICLE_SEARCHLIGHT(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x14E85C5EE7A4D542, p0, p1, p2); } // 14E85C5EE7A4D542 E2C0DD8A
	static BOOL _0x639431E895B9AA57(scrAny p0, scrAny p1, scrAny p2, BOOL p3, BOOL p4) { return NativeInvoke::Invoke<BOOL>(0x639431E895B9AA57, p0, p1, p2, p3, p4); } // 639431E895B9AA57 AB0E79EB
	static BOOL _0x30785D90C956BF35(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x30785D90C956BF35, p0, p1); } // 30785D90C956BF35 B3EB01ED
	static scrAny GET_NUM_MOD_KITS(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x33F2E3FE70EAAE1D, p0); } // 33F2E3FE70EAAE1D E4903AA0
	static void SET_VEHICLE_MOD_KIT(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x1F2AA07F00B3217A, p0, p1); } // 1F2AA07F00B3217A B8132158
	static scrAny GET_VEHICLE_MOD_KIT(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x6325D1A044AE510D, p0); } // 6325D1A044AE510D 9FE60927
	static scrAny GET_VEHICLE_MOD_KIT_TYPE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xFC058F5121E54C32, p0); } // FC058F5121E54C32 E5F76765
	static scrAny GET_VEHICLE_WHEEL_TYPE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xB3ED1BFB4BE636DC, p0); } // B3ED1BFB4BE636DC DA58D7AE
	static void SET_VEHICLE_WHEEL_TYPE(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x487EB21CC7295BA1, p0, p1); } // 487EB21CC7295BA1 64BDAAAD
	static scrAny _0xA551BE18C11A476D(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<scrAny>(0xA551BE18C11A476D, p0, p1); } // A551BE18C11A476D 73722CD9
	static void SET_VEHICLE_MOD_COLOR_1(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x43FEB945EE7F85B8, p0, p1, p2, p3); } // 43FEB945EE7F85B8 CBE9A54D
	static void SET_VEHICLE_MOD_COLOR_2(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x816562BADFDEC83E, p0, p1, p2); } // 816562BADFDEC83E C32613C2
	static void GET_VEHICLE_MOD_COLOR_1(scrAny p0, scrAny *p1, scrAny *p2, scrAny *p3) { NativeInvoke::Invoke<scrVoid>(0xE8D65CA700C9A693, p0, p1, p2, p3); } // E8D65CA700C9A693 E625510A
	static void GET_VEHICLE_MOD_COLOR_2(scrAny p0, scrAny *p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0x81592BE4E3878728, p0, p1, p2); } // 81592BE4E3878728 9B76BB8E
	static scrAny _0xB45085B721EFD38C(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<scrAny>(0xB45085B721EFD38C, p0, p1); } // B45085B721EFD38C 9A0840FD
	static scrAny _0x4967A516ED23A5A1(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x4967A516ED23A5A1, p0); } // 4967A516ED23A5A1 9BDC0B49
	static BOOL _0x9A83F5F9963775EF(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x9A83F5F9963775EF, p0); } // 9A83F5F9963775EF 112D637A
	static void SET_VEHICLE_MOD(scrAny p0, scrAny p1, scrAny p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x6AF0636DDEDCB6DD, p0, p1, p2, p3); } // 6AF0636DDEDCB6DD B52E5ED5
	static scrAny GET_VEHICLE_MOD(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x772960298DA26FDB, p0, p1); } // 772960298DA26FDB DC520069
	static scrAny GET_VEHICLE_MOD_VARIATION(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xB3924ECD70E095DC, p0, p1); } // B3924ECD70E095DC C1B92003
	static scrAny GET_NUM_VEHICLE_MODS(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xE38E9162A2500646, p0, p1); } // E38E9162A2500646 8A814FF9
	static void REMOVE_VEHICLE_MOD(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x92D619E420858204, p0, p1); } // 92D619E420858204 9CC80A43
	static void TOGGLE_VEHICLE_MOD(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x2A1F4F37F95BAD08, p0, p1, p2); } // 2A1F4F37F95BAD08 D095F811
	static BOOL IS_TOGGLE_MOD_ON(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x84B233A8C8FC8AE7, p0, p1); } // 84B233A8C8FC8AE7 F0E1689F
	static scrAny GET_MOD_TEXT_LABEL(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0x8935624F8C5592CC, p0, p1, p2); } // 8935624F8C5592CC 0BA39CA7
	static scrAny GET_MOD_SLOT_NAME(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x51F0FEB9F6AE98C0, p0, p1); } // 51F0FEB9F6AE98C0 5E113483
	static scrAny GET_LIVERY_NAME(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xB4C7A93837C91A1F, p0, p1); } // B4C7A93837C91A1F ED80B5BE
	static scrAny GET_VEHICLE_MOD_MODIFIER_VALUE(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0x90A38E9838E0A8C1, p0, p1, p2); } // 90A38E9838E0A8C1 73AE5505
	static scrAny _0x4593CF82AA179706(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0x4593CF82AA179706, p0, p1, p2); } // 4593CF82AA179706 94850968
	static void PRELOAD_VEHICLE_MOD(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x758F49C24925568A, p0, p1, p2); } // 758F49C24925568A 6EA5F4A8
	static BOOL HAS_PRELOAD_MODS_FINISHED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x06F43E5175EB6D96, p0); } // 06F43E5175EB6D96 A8A0D246
	static void RELEASE_PRELOAD_MODS(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x445D79F995508307, p0); } // 445D79F995508307 D442521F
	static void SET_VEHICLE_TYRE_SMOKE_COLOR(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0xB5BA80F839791C0F, p0, p1, p2, p3); } // B5BA80F839791C0F 3EDEC0DB
	static void GET_VEHICLE_TYRE_SMOKE_COLOR(scrAny p0, scrAny *p1, scrAny *p2, scrAny *p3) { NativeInvoke::Invoke<scrVoid>(0xB635392A4938B3C3, p0, p1, p2, p3); } // B635392A4938B3C3 75280015
	static void SET_VEHICLE_WINDOW_TINT(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x57C51E6BAD752696, p0, p1); } // 57C51E6BAD752696 497C8787
	static scrAny GET_VEHICLE_WINDOW_TINT(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x0EE21293DAD47C95, p0); } // 0EE21293DAD47C95 13D53892
	static scrAny _0x9D1224004B3A6707() { return NativeInvoke::Invoke<scrAny>(0x9D1224004B3A6707); } // 9D1224004B3A6707 625C7B66
	static void GET_VEHICLE_COLOR(scrAny p0, scrAny *p1, scrAny *p2, scrAny *p3) { NativeInvoke::Invoke<scrVoid>(0xF3CC740D36221548, p0, p1, p2, p3); } // F3CC740D36221548 03BC8F1B
	static scrAny _0xEEBFC7A7EFDC35B4(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xEEBFC7A7EFDC35B4, p0); } // EEBFC7A7EFDC35B4 749DEEA2
	static scrAny GET_VEHICLE_CAUSE_OF_DESTRUCTION(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xE495D1EF4C91FD20, p0); } // E495D1EF4C91FD20 7F8C20DD
	static BOOL _0x5EF77C9ADD3B11A3(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x5EF77C9ADD3B11A3, p0); } // 5EF77C9ADD3B11A3 A0777943
	static BOOL _0xA7ECB73355EB2F20(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xA7ECB73355EB2F20, p0); } // A7ECB73355EB2F20 F178390B
	static void _0x93A3996368C94158(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x93A3996368C94158, p0, p1); } // 93A3996368C94158 E943B09C
	static void _0x1CF38D529D7441D9(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x1CF38D529D7441D9, p0, p1); } // 1CF38D529D7441D9 DF594D8D
	static void _0x1F9FB66F3A3842D2(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x1F9FB66F3A3842D2, p0, p1); } // 1F9FB66F3A3842D2 4D840FC4
	static scrAny _0x54B0F614960F4A5F(float p0, float p1, float p2, float p3, float p4, float p5, float p6) { return NativeInvoke::Invoke<scrAny>(0x54B0F614960F4A5F, p0, p1, p2, p3, p4, p5, p6); } // 54B0F614960F4A5F 5AB26C2B
	static void _0xE30524E1871F481D(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xE30524E1871F481D, p0); } // E30524E1871F481D EF05F807
	static BOOL _0x291E373D483E7EE7(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x291E373D483E7EE7, p0); } // 291E373D483E7EE7 D656E7E5
	static void _0xB59E4BD37AE292DB(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xB59E4BD37AE292DB, p0, p1); } // B59E4BD37AE292DB 642DA5AA
	static void _0x0AD9E8F87FF7C16F(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x0AD9E8F87FF7C16F, p0, p1); } // 0AD9E8F87FF7C16F 04F5546C
	static void SET_VEHICLE_IS_WANTED(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xF7EC25A3EBEEC726, p0, p1); } // F7EC25A3EBEEC726 DAA388E8
	static void _0xF488C566413B4232(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xF488C566413B4232, p0, p1); } // F488C566413B4232 A25CCB8C
	static void _0xC1F981A6F74F0C23(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xC1F981A6F74F0C23, p0, p1); } // C1F981A6F74F0C23 00966934
	static void _0x0F3B4D4E43177236(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x0F3B4D4E43177236, p0, p1); } // 0F3B4D4E43177236 113DF5FD
	static float _0x6636C535F6CC2725(scrAny p0) { return NativeInvoke::Invoke<float>(0x6636C535F6CC2725, p0); } // 6636C535F6CC2725 7C8D6464
	static void DISABLE_PLANE_AILERON(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x23428FC53C60919C, p0, p1, p2); } // 23428FC53C60919C 7E84C45C
	static BOOL _0xAE31E7DF9B5B132E(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xAE31E7DF9B5B132E, p0); } // AE31E7DF9B5B132E 7DC6D022
	static void _0x1D97D1E3A70A649F(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x1D97D1E3A70A649F, p0, p1); } // 1D97D1E3A70A649F A03E42DF
	static void _0x9CFA4896C3A53CBB(scrAny p0, float p1, float p2) { NativeInvoke::Invoke<scrVoid>(0x9CFA4896C3A53CBB, p0, p1, p2); } // 9CFA4896C3A53CBB 15D40761
	static void _0xAB04325045427AAE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xAB04325045427AAE, p0, p1); } // AB04325045427AAE 1984F88D
	static void _0xCFD778E7904C255E(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xCFD778E7904C255E, p0); } // CFD778E7904C255E 3FBE904F
	static void _0xACFB2463CC22BED2(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xACFB2463CC22BED2, p0); } // ACFB2463CC22BED2 D1B71A25
	static scrAny _0xB2D06FAEDE65B577() { return NativeInvoke::Invoke<scrAny>(0xB2D06FAEDE65B577); } // B2D06FAEDE65B577 FEB0C0C8
	static void _0x02398B627547189C(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x02398B627547189C, p0, p1); } // 02398B627547189C 08CD58F9
	static void _0xB893215D8D4C015B(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xB893215D8D4C015B, p0, p1); } // B893215D8D4C015B 8C4B63E2
	static void SET_VEHICLE_LOD_MULTIPLIER(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x93AE6A61BE015BF1, p0, p1); } // 93AE6A61BE015BF1 569E5AE3
	static void _0x428BACCDF5E26EAD(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x428BACCDF5E26EAD, p0, p1); } // 428BACCDF5E26EAD 1604C2F5
	static scrAny _0x42A4BEB35D372407(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x42A4BEB35D372407, p0); } // 42A4BEB35D372407 8CDB0C09
	static scrAny _0x2C8CBFE1EA5FC631(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x2C8CBFE1EA5FC631, p0); } // 2C8CBFE1EA5FC631 ABC99E21
	static void _0x4D9D109F63FEE1D4(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x4D9D109F63FEE1D4, p0, p1); } // 4D9D109F63FEE1D4 900C878C
	static void _0x279D50DE5652D935(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x279D50DE5652D935, p0, p1); } // 279D50DE5652D935 B3200F72
	static void _0xE44A982368A4AF23(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xE44A982368A4AF23, p0, p1); } // E44A982368A4AF23 BAE491C7
	static void _0xF25E02CB9C5818F8() { NativeInvoke::Invoke<scrVoid>(0xF25E02CB9C5818F8); } // F25E02CB9C5818F8 F0E59BC1
	static void _0xBC3CCA5844452B06(float p0) { NativeInvoke::Invoke<scrVoid>(0xBC3CCA5844452B06, p0); } // BC3CCA5844452B06 929801C6
	static void SET_VEHICLE_SHOOT_AT_TARGET(scrAny p0, scrAny p1, float p2, float p3, float p4) { NativeInvoke::Invoke<scrVoid>(0x74CD9A9327A282EA, p0, p1, p2, p3, p4); } // 74CD9A9327A282EA 2343FFDF
	static BOOL _0x8F5EBAB1F260CFCE(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x8F5EBAB1F260CFCE, p0, p1); } // 8F5EBAB1F260CFCE 4A557117
	static void _0x97CE68CB032583F0(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x97CE68CB032583F0, p0, p1); } // 97CE68CB032583F0 E0FC6A32
	static void _0x182F266C2D9E2BEB(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x182F266C2D9E2BEB, p0, p1); } // 182F266C2D9E2BEB 7D0DE7EA
	static scrAny GET_VEHICLE_PLATE_TYPE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x9CCC9525BF2408E0, p0); } // 9CCC9525BF2408E0 65CA9286
	static void TRACK_VEHICLE_VISIBILITY(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x64473AEFDCF47DCA, p0); } // 64473AEFDCF47DCA 78122DC1
	static BOOL IS_VEHICLE_VISIBLE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xAA0A52D24FB98293, p0); } // AA0A52D24FB98293 7E0D6056
	static void SET_VEHICLE_GRAVITY(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x89F149B6131E57DA, p0, p1); } // 89F149B6131E57DA 07B2A6DC
	static void _0xE6C0C80B8C867537(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xE6C0C80B8C867537, p0); } // E6C0C80B8C867537 D2B8ACBD
	static scrAny _0x36492C2F0D134C56(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x36492C2F0D134C56, p0); } // 36492C2F0D134C56 A4A75FCF
	static void _0x06582AFF74894C75(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x06582AFF74894C75, p0, p1); } // 06582AFF74894C75 50F89338
	static void _0xDFFCEF48E511DB48(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xDFFCEF48E511DB48, p0, p1); } // DFFCEF48E511DB48 EB7D7C27
	static BOOL _0x8D474C8FAEFF6CDE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x8D474C8FAEFF6CDE, p0); } // 8D474C8FAEFF6CDE 5EB00A6A
	static void _0x983765856F2564F9(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x983765856F2564F9, p0, p1); } // 983765856F2564F9 081DAC12
	static void _0xF0E4BA16D1DB546C(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xF0E4BA16D1DB546C, p0, p1, p2); } // F0E4BA16D1DB546C 5BD8D82D
	static void _0xF87D9F2301F7D206(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xF87D9F2301F7D206, p0); } // F87D9F2301F7D206 450AD03A
	static BOOL _0x4198AB0022B15F87(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x4198AB0022B15F87, p0); } // 4198AB0022B15F87 BD085DCA
	static BOOL _0x755D6D5267CBBD7E(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x755D6D5267CBBD7E, p0); } // 755D6D5267CBBD7E ABBDD5C6
	static void _0x0CDDA42F9E360CA6(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x0CDDA42F9E360CA6, p0, p1); } // 0CDDA42F9E360CA6 9B581DE7
	static BOOL IS_VEHICLE_STOLEN(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x4AF9BD80EEBEB453, p0); } // 4AF9BD80EEBEB453 20B61DDE
	static void SET_VEHICLE_IS_STOLEN(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x67B2C79AA7FF5738, p0, p1); } // 67B2C79AA7FF5738 70912E42
	static void _0xAD2D28A1AFDFF131(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xAD2D28A1AFDFF131, p0, p1); } // AD2D28A1AFDFF131 ED159AE6
	static BOOL _0x5991A01434CE9677(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x5991A01434CE9677, p0); } // 5991A01434CE9677 AF8CB3DF
	static void _0xB264C4D2F2B0A78B(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xB264C4D2F2B0A78B, p0); } // B264C4D2F2B0A78B 45F72495
	static void DETACH_VEHICLE_FROM_CARGOBOB(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x0E21D3DF1051399D, p0, p1); } // 0E21D3DF1051399D 83D3D331
	static BOOL DETACH_VEHICLE_FROM_ANY_CARGOBOB(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xADF7BE450512C12F, p0); } // ADF7BE450512C12F 50E0EABE
	static BOOL IS_VEHICLE_ATTACHED_TO_CARGOBOB(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xD40148F22E81A1D9, p0, p1); } // D40148F22E81A1D9 5DEEC76C
	static scrAny GET_VEHICLE_ATTACHED_TO_CARGOBOB(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x873B82D42AC2B9E5, p0); } // 873B82D42AC2B9E5 301A1D24
	static void ATTACH_VEHICLE_TO_CARGOBOB(scrAny p0, scrAny p1, scrAny p2, float p3, float p4, float p5) { NativeInvoke::Invoke<scrVoid>(0x4127F1D84E347769, p0, p1, p2, p3, p4, p5); } // 4127F1D84E347769 607DC9D5
	static scrVector3 _0xCBDB9B923CACC92D(scrAny p0) { return NativeInvoke::Invoke<scrVector3>(0xCBDB9B923CACC92D, p0); } // CBDB9B923CACC92D
	static BOOL _0x1821D91AD4B56108(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x1821D91AD4B56108, p0); } // 1821D91AD4B56108 AF769B81
	static void _0x7BEB0C7A235F6F3B(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x7BEB0C7A235F6F3B, p0); } // 7BEB0C7A235F6F3B 4D3C9A99
	static void GET_CLOSEST_VEHICLE_TURNING_BLOODSPRAY(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x9768CF648F54C804, p0); } // 9768CF648F54C804 A8211EE9
	static void GET_VEHICLE_HAS_BACK_RECURSIVE(scrAny p0, float p1, float p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x877C1EAEAC531023, p0, p1, p2, p3); } // 877C1EAEAC531023 3A8AB081
	static BOOL DOES_VEHICLE_HAVE_WEAPONS(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x25ECB9F8017D98E0, p0); } // 25ECB9F8017D98E0 B2E1E1FB
	static void _0x2C4A1590ABF43E8B(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x2C4A1590ABF43E8B, p0, p1); } // 2C4A1590ABF43E8B 2EC19A8B
	static void DISABLE_VEHICLE_WEAPON(BOOL p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0xF4FC6A6F67D8D856, p0, p1, p2, p3); } // F4FC6A6F67D8D856 A688B7D1
	static void _0xE05DD0E9707003A3(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xE05DD0E9707003A3, p0, p1); } // E05DD0E9707003A3 123E5B90
	static void _0x21115BCD6E44656A(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x21115BCD6E44656A, p0, p1); } // 21115BCD6E44656A EBC225C1
	static scrAny GET_VEHICLE_CLASS(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x29439776AAA00A62, p0); } // 29439776AAA00A62 C025338E
	static scrAny GET_VEHICLE_CLASS_FROM_NAME(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xDEDF1C8BD47C2200, p0); } // DEDF1C8BD47C2200 EA469980
	static void SET_PLAYERS_LAST_VEHICLE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xBCDF8BAF56C87B6A, p0); } // BCDF8BAF56C87B6A DE86447D
	static void _0x300504B23BD3B711(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x300504B23BD3B711, p0, p1); } // 300504B23BD3B711 5130DB1E
	static void _0xE5810AC70602F2F5(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xE5810AC70602F2F5, p0, p1); } // E5810AC70602F2F5 B6BE07E0
	static void _0x068F64F2470F9656(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x068F64F2470F9656, p0, p1); } // 068F64F2470F9656 4BB5605D
	static void _0xB8FBC8B1330CA9B4(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xB8FBC8B1330CA9B4, p0, p1); } // B8FBC8B1330CA9B4 51E0064F
	static void _0x10655FAB9915623D(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x10655FAB9915623D, p0, p1); } // 10655FAB9915623D
	static void _0x79DF7E806202CE01(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x79DF7E806202CE01, p0, p1); } // 79DF7E806202CE01 AEF9611C
	static void _0x9007A2F21DC108D4(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x9007A2F21DC108D4, p0, p1); } // 9007A2F21DC108D4 585E49B6
	static void _0x6E0859B530A365CC(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x6E0859B530A365CC, p0, p1); } // 6E0859B530A365CC 6E67FD35
	static void SET_VEHICLE_FRICTION_OVERRIDE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x1837AF7C627009BA, p0, p1); } // 1837AF7C627009BA 32AFD42E
	static void SET_VEHICLE_MAX_STR_TRAP(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xA37B9A517B133349, p0, p1); } // A37B9A517B133349 670913A4
	static void GET_VEHICLE_DEFORMATION_GET_TREE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xA46413066687A328, p0, p1); } // A46413066687A328 98A10A86
	static void _0x5E569EC46EC21CAE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x5E569EC46EC21CAE, p0, p1); } // 5E569EC46EC21CAE BC649C49
	static void _0x6D6AF961B72728AE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x6D6AF961B72728AE, p0); } // 6D6AF961B72728AE 8DD9AA0C
	static scrAny DOES_VEHICLE_EXIST_WITH_DECORATOR(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0x956B409B984D9BF7, p0); } // 956B409B984D9BF7 39E68EDD
	static void _0x41062318F23ED854(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x41062318F23ED854, p0, p1); } // 41062318F23ED854 AA8BD440
	static void _0xB5C51B5502E85E83(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xB5C51B5502E85E83, p0, p1, p2); } // B5C51B5502E85E83
	static void _0x500873A45724C863(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x500873A45724C863, p0, p1); } // 500873A45724C863
	static void _0xB055A34527CB8FD7(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xB055A34527CB8FD7, p0, p1); } // B055A34527CB8FD7
	static void _0xF796359A959DF65D(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xF796359A959DF65D, p0); } // F796359A959DF65D B5CC548B
	static void _0x8E0A582209A62695(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x8E0A582209A62695, p0, p1, p2, p3); } // 8E0A582209A62695
	static void _0x7619EEE8C886757F(scrAny p0, scrAny *p1, scrAny *p2, scrAny *p3) { NativeInvoke::Invoke<scrVoid>(0x7619EEE8C886757F, p0, p1, p2, p3); } // 7619EEE8C886757F
	static void _0x2AA720E4287BF269(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x2AA720E4287BF269, p0, p1, p2); } // 2AA720E4287BF269
	static BOOL _0x8C4B92553E4766A5(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x8C4B92553E4766A5, p0, p1); } // 8C4B92553E4766A5
	static void _0x35E0654F4BAD7971(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x35E0654F4BAD7971, p0); } // 35E0654F4BAD7971
	static void _0xB088E9A47AE6EDD5(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xB088E9A47AE6EDD5, p0, p1); } // B088E9A47AE6EDD5
	static void _0xDBA3C090E3D74690(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xDBA3C090E3D74690, p0); } // DBA3C090E3D74690
	static float _0xF271147EB7B40F12(scrAny p0) { return NativeInvoke::Invoke<float>(0xF271147EB7B40F12, p0); } // F271147EB7B40F12 2B2FCC28
	static void _0xB77D05AC8C78AADB(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xB77D05AC8C78AADB, p0, p1); } // B77D05AC8C78AADB 920C2517
	static void _0xDF7E3EEB29642C38(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xDF7E3EEB29642C38, p0, p1, p2); } // DF7E3EEB29642C38
	static float _0x53952FD2BAA19F17(scrAny p0) { return NativeInvoke::Invoke<float>(0x53952FD2BAA19F17, p0); } // 53952FD2BAA19F17 B73A1486
	static void _0x84FD40F56075E816(float p0) { NativeInvoke::Invoke<scrVoid>(0x84FD40F56075E816, p0); } // 84FD40F56075E816
	static void _0xA7DCDF4DED40A8F4(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xA7DCDF4DED40A8F4, p0, p1); } // A7DCDF4DED40A8F4
}

namespace OBJECT
{
	static scrAny CREATE_OBJECT(scrAny p0, float p1, float p2, float p3, BOOL p4, BOOL p5, BOOL p6) { return NativeInvoke::Invoke<scrAny>(0x509D5878EB39E842, p0, p1, p2, p3, p4, p5, p6); } // 509D5878EB39E842 2F7AA05C
	static scrAny CREATE_OBJECT_NO_OFFSET(scrAny p0, float p1, float p2, float p3, BOOL p4, BOOL p5, BOOL p6) { return NativeInvoke::Invoke<scrAny>(0x9A294B2138ABB884, p0, p1, p2, p3, p4, p5, p6); } // 9A294B2138ABB884 58040420
	static void DELETE_OBJECT(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x539E0AE3E6634B9F, p0); } // 539E0AE3E6634B9F D6EF9DA7
	static BOOL PLACE_OBJECT_ON_GROUND_PROPERLY(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x58A850EAEE20FAA3, p0); } // 58A850EAEE20FAA3 8F95A20B
	static BOOL SLIDE_OBJECT(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, BOOL p7) { return NativeInvoke::Invoke<BOOL>(0x2FDFF4107B8C1147, p0, p1, p2, p3, p4, p5, p6, p7); } // 2FDFF4107B8C1147 63BFA7A0
	static void SET_OBJECT_TARGETTABLE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x8A7391690F5AFD81, p0, p1); } // 8A7391690F5AFD81 3F88CD86
	static void _0x77F33F2CCF64B3AA(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x77F33F2CCF64B3AA, p0, p1); } // 77F33F2CCF64B3AA 483C5C88
	static scrAny GET_CLOSEST_OBJECT_OF_TYPE(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { return NativeInvoke::Invoke<scrAny>(0xE143FA2249364369, p0, p1, p2, p3, p4, p5); } // E143FA2249364369 45619B33
	static BOOL HAS_OBJECT_BEEN_BROKEN(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x8ABFB70C49CC43E2, p0); } // 8ABFB70C49CC43E2 FE21F891
	static BOOL HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_BROKEN(float p0, float p1, float p2, float p3, scrAny p4, scrAny p5) { return NativeInvoke::Invoke<BOOL>(0x761B0E69AC4D007E, p0, p1, p2, p3, p4, p5); } // 761B0E69AC4D007E 6FC0353D
	static BOOL _0x46494A2475701343(float p0, float p1, float p2, float p3, scrAny p4, scrAny p5) { return NativeInvoke::Invoke<BOOL>(0x46494A2475701343, p0, p1, p2, p3, p4, p5); } // 46494A2475701343 7DB578DD
	static scrVector3 _0x163E252DE035A133(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6) { return NativeInvoke::Invoke<scrVector3>(0x163E252DE035A133, p0, p1, p2, p3, p4, p5, p6); } // 163E252DE035A133 87A42A12
	static scrAny _0x163F8B586BC95F2A(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7) { return NativeInvoke::Invoke<scrAny>(0x163F8B586BC95F2A, p0, p1, p2, p3, p4, p5, p6, p7); } // 163F8B586BC95F2A 65213FC3
	static void SET_STATE_OF_CLOSEST_DOOR_OF_TYPE(scrAny p0, float p1, float p2, float p3, BOOL p4, float p5, BOOL p6) { NativeInvoke::Invoke<scrVoid>(0xF82D8F1926A02C3D, p0, p1, p2, p3, p4, p5, p6); } // F82D8F1926A02C3D 38C951A4
	static void GET_STATE_OF_CLOSEST_DOOR_OF_TYPE(scrAny p0, float p1, float p2, float p3, scrAny *p4, scrAny *p5) { NativeInvoke::Invoke<scrVoid>(0xEDC1A5B84AEF33FF, p0, p1, p2, p3, p4, p5); } // EDC1A5B84AEF33FF 4B44A83D
	static void _0x9B12F9A24FABEDB0(scrAny p0, float p1, float p2, float p3, BOOL p4, float p5, float p6, float p7) { NativeInvoke::Invoke<scrVoid>(0x9B12F9A24FABEDB0, p0, p1, p2, p3, p4, p5, p6, p7); } // 9B12F9A24FABEDB0 4E0A260B
	static void _0x6F8838D03D1DC226(scrAny p0, scrAny p1, float p2, float p3, float p4, BOOL p5, BOOL p6, BOOL p7) { NativeInvoke::Invoke<scrVoid>(0x6F8838D03D1DC226, p0, p1, p2, p3, p4, p5, p6, p7); } // 6F8838D03D1DC226 9D2D778D
	static void _0x464D8E1427156FE4(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x464D8E1427156FE4, p0); } // 464D8E1427156FE4 00253286
	static void _0x6BAB9442830C7F53(scrAny p0, scrAny p1, BOOL p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x6BAB9442830C7F53, p0, p1, p2, p3); } // 6BAB9442830C7F53 DF83DB47
	static scrAny _0x160AA1B32F6139B8(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x160AA1B32F6139B8, p0); } // 160AA1B32F6139B8 D42A41C2
	static scrAny _0x4BC2854478F3A749(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x4BC2854478F3A749, p0); } // 4BC2854478F3A749 D649B7E1
	static void _0x03C27E13B42A0E82(scrAny p0, float p1, BOOL p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x03C27E13B42A0E82, p0, p1, p2, p3); } // 03C27E13B42A0E82 4F44AF21
	static void _0x9BA001CB45CBF627(scrAny p0, float p1, BOOL p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x9BA001CB45CBF627, p0, p1, p2, p3); } // 9BA001CB45CBF627 47531446
	static void _0xB6E6FBA95C7324AC(scrAny p0, float p1, BOOL p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0xB6E6FBA95C7324AC, p0, p1, p2, p3); } // B6E6FBA95C7324AC 34883DE3
	static float _0x65499865FCA6E5EC(scrAny p0) { return NativeInvoke::Invoke<float>(0x65499865FCA6E5EC, p0); } // 65499865FCA6E5EC B74C3BD7
	static void _0xC485E07E4F0B7958(scrAny p0, BOOL p1, BOOL p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0xC485E07E4F0B7958, p0, p1, p2, p3); } // C485E07E4F0B7958 B4A9A558
	static void _0xD9B71952F78A2640(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xD9B71952F78A2640, p0, p1); } // D9B71952F78A2640 ECE58AE0
	static void _0xA85A21582451E951(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xA85A21582451E951, p0, p1); } // A85A21582451E951 F736227C
	static BOOL _0xC153C43EA202C8C1(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xC153C43EA202C8C1, p0); } // C153C43EA202C8C1 5AFCD8A1
	static BOOL IS_DOOR_CLOSED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xC531EE8A1145A149, p0); } // C531EE8A1145A149 48659CD7
	static void _0xC7F29CA00F46350E(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xC7F29CA00F46350E, p0); } // C7F29CA00F46350E 9BF33E41
	static void _0x701FDA1E82076BA4() { NativeInvoke::Invoke<scrVoid>(0x701FDA1E82076BA4); } // 701FDA1E82076BA4 F592AD10
	static BOOL _0xDF97CDD4FC08FD34(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xDF97CDD4FC08FD34, p0); } // DF97CDD4FC08FD34 17FF9393
	static BOOL _0x589F80B325CC82C5(float p0, float p1, float p2, scrAny p3, scrAny *p4) { return NativeInvoke::Invoke<BOOL>(0x589F80B325CC82C5, p0, p1, p2, p3, p4); } // 589F80B325CC82C5 E9AE494F
	static BOOL IS_GARAGE_EMPTY(scrAny p0, BOOL p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0x90E47239EA1980B8, p0, p1, p2); } // 90E47239EA1980B8 A8B37DEA
	static BOOL _0x024A60DEB0EA69F0(scrAny p0, scrAny p1, float p2, scrAny p3) { return NativeInvoke::Invoke<BOOL>(0x024A60DEB0EA69F0, p0, p1, p2, p3); } // 024A60DEB0EA69F0 C33ED360
	static BOOL _0x1761DC5D8471CBAA(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0x1761DC5D8471CBAA, p0, p1, p2); } // 1761DC5D8471CBAA 41924877
	static BOOL _0x85B6C850546FDDE2(scrAny p0, BOOL p1, BOOL p2, BOOL p3, scrAny p4) { return NativeInvoke::Invoke<BOOL>(0x85B6C850546FDDE2, p0, p1, p2, p3, p4); } // 85B6C850546FDDE2 4BD59750
	static BOOL _0x673ED815D6E323B7(scrAny p0, BOOL p1, BOOL p2, BOOL p3, scrAny p4) { return NativeInvoke::Invoke<BOOL>(0x673ED815D6E323B7, p0, p1, p2, p3, p4); } // 673ED815D6E323B7 7B44D659
	static BOOL _0x372EF6699146A1E4(scrAny p0, scrAny p1, float p2, scrAny p3) { return NativeInvoke::Invoke<BOOL>(0x372EF6699146A1E4, p0, p1, p2, p3); } // 372EF6699146A1E4 142C8F76
	static BOOL _0xF0EED5A6BC7B237A(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0xF0EED5A6BC7B237A, p0, p1, p2); } // F0EED5A6BC7B237A 95A9AB2B
	static void _0x190428512B240692(scrAny p0, BOOL p1, BOOL p2, BOOL p3, BOOL p4) { NativeInvoke::Invoke<scrVoid>(0x190428512B240692, p0, p1, p2, p3, p4); } // 190428512B240692 A565E27E
	static void _0xF2E1A7133DD356A6(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xF2E1A7133DD356A6, p0, p1); } // F2E1A7133DD356A6 43BB7E48
	static void _0x66A49D021870FE88() { NativeInvoke::Invoke<scrVoid>(0x66A49D021870FE88); } // 66A49D021870FE88 6158959E
	static BOOL DOES_OBJECT_OF_TYPE_EXIST_AT_COORDS(float p0, float p1, float p2, float p3, scrAny p4, BOOL p5) { return NativeInvoke::Invoke<BOOL>(0xBFA48E2FF417213F, p0, p1, p2, p3, p4, p5); } // BFA48E2FF417213F 23FF2BA4
	static BOOL IS_POINT_IN_ANGLED_AREA(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, BOOL p10, BOOL p11) { return NativeInvoke::Invoke<BOOL>(0x2A70BAE8883E4C81, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 2A70BAE8883E4C81 73BCFFDC
	static void _0x4D89D607CB3DD1D2(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x4D89D607CB3DD1D2, p0, p1); } // 4D89D607CB3DD1D2 19B17769
	static void SET_OBJECT_PHYSICS_PARAMS(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11) { NativeInvoke::Invoke<scrVoid>(0xF6DF6E90DE7DF90F, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // F6DF6E90DE7DF90F E8D11C58
	static float GET_OBJECT_FRAGMENT_DAMAGE_HEALTH(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<float>(0xB6FBFD079B8D0596, p0, p1); } // B6FBFD079B8D0596 F0B330AD
	static void SET_ACTIVATE_OBJECT_PHYSICS_AS_SOON_AS_IT_IS_UNFROZEN(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x406137F8EF90EAF5, p0, p1); } // 406137F8EF90EAF5 3E263AE1
	static BOOL IS_ANY_OBJECT_NEAR_POINT(float p0, float p1, float p2, float p3, BOOL p4) { return NativeInvoke::Invoke<BOOL>(0x397DC58FF00298D1, p0, p1, p2, p3, p4); } // 397DC58FF00298D1 E9E46941
	static BOOL IS_OBJECT_NEAR_POINT(scrAny p0, float p1, float p2, float p3, float p4) { return NativeInvoke::Invoke<BOOL>(0x8C90FE4B381BA60A, p0, p1, p2, p3, p4); } // 8C90FE4B381BA60A 50A62C43
	static void _0x4A39DB43E47CF3AA(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x4A39DB43E47CF3AA, p0); } // 4A39DB43E47CF3AA E3261B35
	static void _0xE7E4C198B0185900(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xE7E4C198B0185900, p0, p1, p2); } // E7E4C198B0185900 1E82C2AE
	static void _0xF9C1681347C8BD15(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xF9C1681347C8BD15, p0); } // F9C1681347C8BD15
	static void TRACK_OBJECT_VISIBILITY(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xB252BC036B525623, p0); } // B252BC036B525623 46D06B9A
	static BOOL IS_OBJECT_VISIBLE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x8B32ACE6326A7546, p0); } // 8B32ACE6326A7546 F4FD8AE4
	static void _0xC6033D32241F6FB5(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xC6033D32241F6FB5, p0, p1); } // C6033D32241F6FB5 F4A1A14A
	static void _0xEB6F1A9B5510A5D2(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xEB6F1A9B5510A5D2, p0, p1); } // EB6F1A9B5510A5D2 AF016CC1
	static void _0xBCE595371A5FBAAF(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xBCE595371A5FBAAF, p0, p1); } // BCE595371A5FBAAF 3A68AA46
	static scrAny _0xB48FCED898292E52(float p0, float p1, float p2, float p3, scrAny *p4) { return NativeInvoke::Invoke<scrAny>(0xB48FCED898292E52, p0, p1, p2, p3, p4); } // B48FCED898292E52 A286DE96
	static void _0x5C29F698D404C5E1(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x5C29F698D404C5E1, p0, p1); } // 5C29F698D404C5E1 21F51560
	static scrAny _0x899BA936634A322E(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x899BA936634A322E, p0); } // 899BA936634A322E F1B8817A
	static BOOL _0x52AF537A0C5B8AAD(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x52AF537A0C5B8AAD, p0); } // 52AF537A0C5B8AAD E08C834D
	static float _0x260EE4FDBDF4DB01(scrAny p0) { return NativeInvoke::Invoke<float>(0x260EE4FDBDF4DB01, p0); } // 260EE4FDBDF4DB01 020497DE
	static scrAny CREATE_PICKUP(scrAny p0, float p1, float p2, float p3, scrAny p4, scrAny p5, BOOL p6, scrAny p7) { return NativeInvoke::Invoke<scrAny>(0xFBA08C503DD5FA58, p0, p1, p2, p3, p4, p5, p6, p7); } // FBA08C503DD5FA58 5E14DF68
	static scrAny CREATE_PICKUP_ROTATE(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, scrAny p7, scrAny p8, scrAny p9, BOOL p10, scrAny p11) { return NativeInvoke::Invoke<scrAny>(0x891804727E0A98B7, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 891804727E0A98B7 F015BFE2
	static scrAny CREATE_AMBIENT_PICKUP(scrAny p0, float p1, float p2, float p3, scrAny p4, scrAny p5, scrAny p6, BOOL p7, BOOL p8) { return NativeInvoke::Invoke<scrAny>(0x673966A0C0FD7171, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 673966A0C0FD7171 17B99CE7
	static scrAny CREATE_PORTABLE_PICKUP(scrAny p0, float p1, float p2, float p3, BOOL p4, scrAny p5) { return NativeInvoke::Invoke<scrAny>(0x2EAF1FDB2FB55698, p0, p1, p2, p3, p4, p5); } // 2EAF1FDB2FB55698 8C886BE5
	static scrAny _0x125494B98A21AAF7(scrAny p0, float p1, float p2, float p3, BOOL p4, scrAny p5) { return NativeInvoke::Invoke<scrAny>(0x125494B98A21AAF7, p0, p1, p2, p3, p4, p5); } // 125494B98A21AAF7 56A02502
	static void ATTACH_PORTABLE_PICKUP_TO_PED(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x8DC39368BDD57755, p0, p1); } // 8DC39368BDD57755 184F6AB3
	static void DETACH_PORTABLE_PICKUP_FROM_PED(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xCF463D1E9A0AECB1, p0); } // CF463D1E9A0AECB1 1D094562
	static void _0x0BF3B3BD47D79C08(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x0BF3B3BD47D79C08, p0, p1); } // 0BF3B3BD47D79C08 7EFBA039
	static void _0x78857FC65CADB909(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x78857FC65CADB909, p0); } // 78857FC65CADB909 A3CDF152
	static scrVector3 GET_SAFE_PICKUP_COORDS(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { return NativeInvoke::Invoke<scrVector3>(0x6E16BC2503FF1FF0, p0, p1, p2, p3, p4); } // 6E16BC2503FF1FF0 618B5F67
	static scrVector3 GET_PICKUP_COORDS(scrAny p0) { return NativeInvoke::Invoke<scrVector3>(0x225B8B35C88029B3, p0); } // 225B8B35C88029B3 C2E1E2C5
	static void REMOVE_ALL_PICKUPS_OF_TYPE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x27F9D613092159CF, p0); } // 27F9D613092159CF 40062C53
	static BOOL HAS_PICKUP_BEEN_COLLECTED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x80EC48E6679313F9, p0); } // 80EC48E6679313F9 0BE5CCED
	static void REMOVE_PICKUP(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x3288D8ACAECD2AB2, p0); } // 3288D8ACAECD2AB2 64A7A0E0
	static void CREATE_MONEY_PICKUPS(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0x0589B5E791CE9B2B, p0, p1, p2, p3, p4, p5); } // 0589B5E791CE9B2B 36C9A5EA
	static BOOL DOES_PICKUP_EXIST(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xAFC1CA75AD4074D1, p0); } // AFC1CA75AD4074D1 9C6DA0B3
	static BOOL DOES_PICKUP_OBJECT_EXIST(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xD9EFB6DBF7DAAEA3, p0); } // D9EFB6DBF7DAAEA3 E0B32108
	static scrAny _0x5099BC55630B25AE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x5099BC55630B25AE, p0); } // 5099BC55630B25AE 6052E62E
	static BOOL _0xF9C36251F6E48E33(scrAny p0, float p1, float p2, float p3, float p4) { return NativeInvoke::Invoke<BOOL>(0xF9C36251F6E48E33, p0, p1, p2, p3, p4); } // F9C36251F6E48E33 F139681B
	static void SET_PICKUP_REGENERATION_TIME(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x78015C9B4B3ECC9D, p0, p1); } // 78015C9B4B3ECC9D AB11267D
	static void _0x616093EC6B139DD9(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x616093EC6B139DD9, p0, p1, p2); } // 616093EC6B139DD9 7FADB4B9
	static void _0x88EAEC617CD26926(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x88EAEC617CD26926, p0, p1); } // 88EAEC617CD26926 3A8F1BF7
	static void SET_TEAM_PICKUP_OBJECT(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x53E0DF1A2A3CF0CA, p0, p1, p2); } // 53E0DF1A2A3CF0CA 77687DC5
	static void _0x92AEFB5F6E294023(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x92AEFB5F6E294023, p0, p1, p2); } // 92AEFB5F6E294023 CBB5F9B6
	static void _0xA08FE5E49BDC39DD(scrAny p0, float p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xA08FE5E49BDC39DD, p0, p1, p2); } // A08FE5E49BDC39DD 276A7807
	static scrAny _0xDB41D07A45A6D4B7(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xDB41D07A45A6D4B7, p0); } // DB41D07A45A6D4B7 000E92DC
	static void _0x318516E02DE3ECE2(float p0) { NativeInvoke::Invoke<scrVoid>(0x318516E02DE3ECE2, p0); } // 318516E02DE3ECE2 9879AC51
	static void _0x31F924B53EADDF65(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x31F924B53EADDF65, p0); } // 31F924B53EADDF65 DB18FA01
	static void _0xF92099527DB8E2A7(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xF92099527DB8E2A7, p0, p1); } // F92099527DB8E2A7 A7E936FD
	static void _0xA2C1F5E92AFE49ED() { NativeInvoke::Invoke<scrVoid>(0xA2C1F5E92AFE49ED); } // A2C1F5E92AFE49ED B241806C
	static void _0x762DB2D380B48D04(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x762DB2D380B48D04, p0); } // 762DB2D380B48D04 D1BAAFB7
	static void _0x3430676B11CDF21D(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x3430676B11CDF21D, p0, p1, p2, p3); } // 3430676B11CDF21D 63B02FAD
	static void _0xB2D0BDE54F0E8E5A(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xB2D0BDE54F0E8E5A, p0, p1); } // B2D0BDE54F0E8E5A 132B6D92
	static scrAny _0x08F96CA6C551AD51(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x08F96CA6C551AD51, p0); } // 08F96CA6C551AD51 EDD01937
	static void _0x971DA0055324D033(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x971DA0055324D033, p0, p1); } // 971DA0055324D033
	static scrAny _0x5EAAD83F8CFB4575(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x5EAAD83F8CFB4575, p0); } // 5EAAD83F8CFB4575 6AE36192
	static void SET_FORCE_OBJECT_THIS_FRAME(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0xF538081986E49E9D, p0, p1, p2, p3); } // F538081986E49E9D 3DA41C1A
	static void _0xADBE4809F19F927A(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xADBE4809F19F927A, p0); } // ADBE4809F19F927A 2048A7DD
}

namespace AI
{
	static void TASK_PAUSE(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xE73A266DB0CA9042, p0, p1); } // E73A266DB0CA9042 17A64668
	static void TASK_STAND_STILL(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x919BE13EED931959, p0, p1); } // 919BE13EED931959 6F80965D
	static void TASK_JUMP(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x0AE4086104E067B1, p0, p1); } // 0AE4086104E067B1 0356E3CE
	static void TASK_COWER(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x3EB1FE9E8E908E15, p0, p1); } // 3EB1FE9E8E908E15 9CF1C19B
	static void TASK_HANDS_UP(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0xF2EAB31979A7F910, p0, p1, p2, p3, p4); } // F2EAB31979A7F910 8DCC19C5
	static void _0xA98FCAFD7893C834(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xA98FCAFD7893C834, p0, p1); } // A98FCAFD7893C834 3AA39BE9
	static void TASK_OPEN_VEHICLE_DOOR(scrAny p0, scrAny p1, scrAny p2, scrAny p3, float p4) { NativeInvoke::Invoke<scrVoid>(0x965791A9A488A062, p0, p1, p2, p3, p4); } // 965791A9A488A062 8EE06BF4
	static void TASK_ENTER_VEHICLE(scrAny p0, scrAny p1, scrAny p2, scrAny p3, float p4, scrAny p5, scrAny *p6) { NativeInvoke::Invoke<scrVoid>(0xC20E50AA46D09CA8, p0, p1, p2, p3, p4, p5, p6); } // C20E50AA46D09CA8 B8689B4E
	static void TASK_LEAVE_VEHICLE(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xD3DBCE61A490BE02, p0, p1, p2); } // D3DBCE61A490BE02 7B1141C6
	static void TASK_SKY_DIVE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x601736CFE536B0A0, p0); } // 601736CFE536B0A0 D3874AFA
	static void TASK_PARACHUTE(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xD2F1C53C97EE81AB, p0, p1); } // D2F1C53C97EE81AB EC3060A2
	static void TASK_PARACHUTE_TO_TARGET(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0xB33E291AFA6BD03A, p0, p1, p2, p3); } // B33E291AFA6BD03A E0104D6C
	static void SET_PARACHUTE_TASK_TARGET(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0xC313379AF0FCEDA7, p0, p1, p2, p3); } // C313379AF0FCEDA7 6ED3AD81
	static void SET_PARACHUTE_TASK_THRUST(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x0729BAC1B8C64317, p0, p1); } // 0729BAC1B8C64317 D07C8AAA
	static void TASK_RAPPEL_FROM_HELI(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x09693B0312F91649, p0, p1); } // 09693B0312F91649 2C7ADB93
	static void TASK_VEHICLE_DRIVE_TO_COORD(scrAny p0, scrAny p1, float p2, float p3, float p4, float p5, scrAny p6, scrAny p7, scrAny p8, float p9, float p10) { NativeInvoke::Invoke<scrVoid>(0xE2A2AA2F659D77A7, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // E2A2AA2F659D77A7 E4AC0387
	static void TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(scrAny p0, scrAny p1, float p2, float p3, float p4, float p5, scrAny p6, float p7) { NativeInvoke::Invoke<scrVoid>(0x158BB33F920D360C, p0, p1, p2, p3, p4, p5, p6, p7); } // 158BB33F920D360C 1490182A
	static void TASK_VEHICLE_DRIVE_WANDER(scrAny p0, scrAny p1, float p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x480142959D337D00, p0, p1, p2, p3); } // 480142959D337D00 36EC0EB0
	static void TASK_FOLLOW_TO_OFFSET_OF_ENTITY(scrAny p0, scrAny p1, float p2, float p3, float p4, float p5, scrAny p6, float p7, BOOL p8) { NativeInvoke::Invoke<scrVoid>(0x304AE42E357B8C7E, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 304AE42E357B8C7E 2DF5A6AC
	static void TASK_GO_STRAIGHT_TO_COORD(scrAny p0, float p1, float p2, float p3, float p4, scrAny p5, float p6, float p7) { NativeInvoke::Invoke<scrVoid>(0xD76B57B44F1E6F8B, p0, p1, p2, p3, p4, p5, p6, p7); } // D76B57B44F1E6F8B 80A9E7A7
	static void TASK_GO_STRAIGHT_TO_COORD_RELATIVE_TO_ENTITY(scrAny p0, scrAny p1, float p2, float p3, float p4, float p5, scrAny p6) { NativeInvoke::Invoke<scrVoid>(0x61E360B7E040D12E, p0, p1, p2, p3, p4, p5, p6); } // 61E360B7E040D12E D26CAC68
	static void TASK_ACHIEVE_HEADING(scrAny p0, float p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x93B93A37987F1F3D, p0, p1, p2); } // 93B93A37987F1F3D 0A0E9B42
	static void TASK_FLUSH_ROUTE() { NativeInvoke::Invoke<scrVoid>(0x841142A1376E9006); } // 841142A1376E9006 34219154
	static void TASK_EXTEND_ROUTE(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x1E7889778264843A, p0, p1, p2); } // 1E7889778264843A 43271F69
	static void TASK_FOLLOW_POINT_ROUTE(scrAny p0, float p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x595583281858626E, p0, p1, p2); } // 595583281858626E B837C816
	static void TASK_GO_TO_ENTITY(scrAny p0, scrAny p1, scrAny p2, float p3, float p4, float p5, scrAny p6) { NativeInvoke::Invoke<scrVoid>(0x6A071245EB0D1882, p0, p1, p2, p3, p4, p5, p6); } // 6A071245EB0D1882 374827C2
	static void TASK_SMART_FLEE_COORD(scrAny p0, float p1, float p2, float p3, float p4, scrAny p5, BOOL p6, BOOL p7) { NativeInvoke::Invoke<scrVoid>(0x94587F17E9C365D5, p0, p1, p2, p3, p4, p5, p6, p7); } // 94587F17E9C365D5 B2E686FC
	static void TASK_SMART_FLEE_PED(scrAny p0, scrAny p1, float p2, scrAny p3, BOOL p4, BOOL p5) { NativeInvoke::Invoke<scrVoid>(0x22B0D0E37CCB840D, p0, p1, p2, p3, p4, p5); } // 22B0D0E37CCB840D E52EB560
	static void TASK_REACT_AND_FLEE_PED(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x72C896464915D1B1, p0, p1); } // 72C896464915D1B1 8A632BD8
	static void TASK_SHOCKING_EVENT_REACT(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x452419CBD838065B, p0, p1); } // 452419CBD838065B 9BD00ACF
	static void TASK_WANDER_IN_AREA(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6) { NativeInvoke::Invoke<scrVoid>(0xE054346CA3A0F315, p0, p1, p2, p3, p4, p5, p6); } // E054346CA3A0F315 C6981FB9
	static void TASK_WANDER_STANDARD(scrAny p0, float p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xBB9CE077274F6A1B, p0, p1, p2); } // BB9CE077274F6A1B AF59151A
	static void TASK_VEHICLE_PARK(scrAny p0, scrAny p1, float p2, float p3, float p4, float p5, scrAny p6, float p7, BOOL p8) { NativeInvoke::Invoke<scrVoid>(0x0F3E34E968EA374E, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0F3E34E968EA374E 5C85FF90
	static void TASK_STEALTH_KILL(scrAny p0, scrAny p1, scrAny p2, float p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0xAA5DC05579D60BD9, p0, p1, p2, p3, p4); } // AA5DC05579D60BD9 0D64C2FA
	static void TASK_PLANT_BOMB(scrAny p0, float p1, float p2, float p3, float p4) { NativeInvoke::Invoke<scrVoid>(0x965FEC691D55E9BF, p0, p1, p2, p3, p4); } // 965FEC691D55E9BF 33457535
	static void TASK_FOLLOW_NAV_MESH_TO_COORD(scrAny p0, float p1, float p2, float p3, float p4, scrAny p5, float p6, scrAny p7, float p8) { NativeInvoke::Invoke<scrVoid>(0x15D3A79D4E44B913, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 15D3A79D4E44B913 FE4A10D9
	static void _0x17F58B88D085DBAC(scrAny p0, float p1, float p2, float p3, float p4, scrAny p5, float p6, scrAny p7, float p8, float p9, float p10, float p11) { NativeInvoke::Invoke<scrVoid>(0x17F58B88D085DBAC, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 17F58B88D085DBAC 6BF6E296
	static void SET_PED_PATH_CAN_USE_CLIMBOVERS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x8E06A6FE76C9EFF4, p0, p1); } // 8E06A6FE76C9EFF4 B7B7D442
	static void SET_PED_PATH_CAN_USE_LADDERS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x77A5B103C87F476E, p0, p1); } // 77A5B103C87F476E 53A879EE
	static void SET_PED_PATH_CAN_DROP_FROM_HEIGHT(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xE361C5C71C431A4F, p0, p1); } // E361C5C71C431A4F 394B7AC9
	static void _0x88E32DB8C1A4AA4B(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x88E32DB8C1A4AA4B, p0, p1); } // 88E32DB8C1A4AA4B 55E06443
	static void SET_PED_PATHS_WIDTH_PLANT(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xF35425A4204367EC, p0, p1); } // F35425A4204367EC 9C606EE3
	static void SET_PED_PATH_PREFER_TO_AVOID_WATER(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x38FE1EC73743793C, p0, p1); } // 38FE1EC73743793C 0EA39A29
	static void SET_PED_PATH_AVOID_FIRE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x4455517B28441E60, p0, p1); } // 4455517B28441E60 DCC5B934
	static void _0x6C6B148586F934F7(float p0) { NativeInvoke::Invoke<scrVoid>(0x6C6B148586F934F7, p0); } // 6C6B148586F934F7 2AFB14B8
	static scrAny GET_NAVMESH_ROUTE_DISTANCE_REMAINING(scrAny p0, scrAny *p1, scrAny *p2) { return NativeInvoke::Invoke<scrAny>(0xC6F5C0BCDC74D62D, p0, p1, p2); } // C6F5C0BCDC74D62D D9281778
	static scrAny GET_NAVMESH_ROUTE_RESULT(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x632E831F382A0FA8, p0); } // 632E831F382A0FA8 96491602
	static void TASK_GO_TO_COORD_ANY_MEANS(scrAny p0, float p1, float p2, float p3, float p4, scrAny p5, BOOL p6, scrAny p7, float p8) { NativeInvoke::Invoke<scrVoid>(0x5BC448CB78FA3E88, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 5BC448CB78FA3E88 F91DF93B
	static void _0x1DD45F9ECFDB1BC9(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9, scrAny p10, scrAny p11) { NativeInvoke::Invoke<scrVoid>(0x1DD45F9ECFDB1BC9, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 1DD45F9ECFDB1BC9 094B75EF
	static void _0xB8ECD61F531A7B02(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9, scrAny p10, scrAny p11, scrAny p12) { NativeInvoke::Invoke<scrVoid>(0xB8ECD61F531A7B02, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // B8ECD61F531A7B02 86DC03F9
	static void TASK_PLAY_ANIM(scrAny p0, scrAny *p1, scrAny *p2, float p3, float p4, scrAny p5, scrAny p6, float p7, BOOL p8, scrAny p9, BOOL p10) { NativeInvoke::Invoke<scrVoid>(0xEA47FE3719165B94, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // EA47FE3719165B94 5AB552C6
	static void _0x83CDB10EA29B370B(scrAny p0, scrAny *p1, scrAny *p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, scrAny p11, scrAny p12, float p13, scrAny p14, scrAny p15) { NativeInvoke::Invoke<scrVoid>(0x83CDB10EA29B370B, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15); } // 83CDB10EA29B370B 3DDEB0E6
	static void STOP_ANIM_TASK(scrAny p0, scrAny *p1, scrAny *p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x97FF36A1D40EA00A, p0, p1, p2, p3); } // 97FF36A1D40EA00A 2B520A57
	static void TASK_SCRIPTED_ANIMATION(scrAny p0, scrAny *p1, scrAny *p2, scrAny *p3, float p4, float p5) { NativeInvoke::Invoke<scrVoid>(0x126EF75F1E17ABE5, p0, p1, p2, p3, p4, p5); } // 126EF75F1E17ABE5 FC2DCF47
	static void PLAY_ENTITY_SCRIPTED_ANIM(scrAny p0, scrAny *p1, scrAny *p2, scrAny *p3, float p4, float p5) { NativeInvoke::Invoke<scrVoid>(0x77A1EEC547E7FCF1, p0, p1, p2, p3, p4, p5); } // 77A1EEC547E7FCF1 02F72AE5
	static void STOP_ANIM_PLAYBACK(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xEE08C992D238C5D1, p0, p1, p2); } // EE08C992D238C5D1 E5F16398
	static void SET_ANIM_WEIGHT(scrAny p0, float p1, scrAny p2, scrAny p3, BOOL p4) { NativeInvoke::Invoke<scrVoid>(0x207F1A47C0342F48, p0, p1, p2, p3, p4); } // 207F1A47C0342F48 17229D98
	static void SET_ANIM_RATE(scrAny p0, float p1, scrAny p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x032D49C5E359C847, p0, p1, p2, p3); } // 032D49C5E359C847 6DB46584
	static void SET_ANIM_LOOPED(scrAny p0, BOOL p1, scrAny p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x70033C3CC29A1FF4, p0, p1, p2, p3); } // 70033C3CC29A1FF4 095D61A4
	static void _0x8FBB6758B3B3E9EC(scrAny p0, scrAny *p1, scrAny *p2, scrAny *p3, float p4, float p5, BOOL p6, BOOL p7) { NativeInvoke::Invoke<scrVoid>(0x8FBB6758B3B3E9EC, p0, p1, p2, p3, p4, p5, p6, p7); } // 8FBB6758B3B3E9EC 1582162C
	static void _0x3FA00D4F4641BFAE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x3FA00D4F4641BFAE, p0); } // 3FA00D4F4641BFAE
	static BOOL _0xB8EBB1E9D3588C10(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xB8EBB1E9D3588C10, p0); } // B8EBB1E9D3588C10 500B6805
	static float _0x47619ABE8B268C60(scrAny p0) { return NativeInvoke::Invoke<float>(0x47619ABE8B268C60, p0); } // 47619ABE8B268C60 7B72AFD1
	static float _0x1EE0F68A7C25DEC6(scrAny p0) { return NativeInvoke::Invoke<float>(0x1EE0F68A7C25DEC6, p0); } // 1EE0F68A7C25DEC6 EF8C3959
	static void TASK_VEHICLE_PLAY_ANIM(scrAny p0, scrAny *p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0x69F5C3BD0F3EBD89, p0, p1, p2); } // 69F5C3BD0F3EBD89 2B28F598
	static void TASK_LOOK_AT_COORD(scrAny p0, float p1, float p2, float p3, scrAny p4, scrAny p5, scrAny p6) { NativeInvoke::Invoke<scrVoid>(0x6FA46612594F7973, p0, p1, p2, p3, p4, p5, p6); } // 6FA46612594F7973 7B784DD8
	static void TASK_LOOK_AT_ENTITY(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x69F4BE8C8CC4796C, p0, p1, p2, p3, p4); } // 69F4BE8C8CC4796C 991D6619
	static void TASK_CLEAR_LOOK_AT(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x0F804F1DB19B9689, p0); } // 0F804F1DB19B9689 60EB4054
	static void OPEN_SEQUENCE_TASK(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xE8854A4326B9E12B, p0); } // E8854A4326B9E12B ABA6923E
	static void CLOSE_SEQUENCE_TASK(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x39E72BC99E6360CB, p0); } // 39E72BC99E6360CB 1A7CEBD0
	static void TASK_PERFORM_SEQUENCE(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x5ABA3986D90D8A3B, p0, p1); } // 5ABA3986D90D8A3B 4D9FBD11
	static void CLEAR_SEQUENCE_TASK(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x3841422E9C488D8C, p0); } // 3841422E9C488D8C 47ED03CE
	static void SET_SEQUENCE_TO_REPEAT(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x58C70CF3A41E4AE7, p0, p1); } // 58C70CF3A41E4AE7 CDDF1508
	static scrAny GET_SEQUENCE_PROGRESS(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x00A9010CFE1E3533, p0); } // 00A9010CFE1E3533 A3419909
	static BOOL GET_IS_TASK_ACTIVE(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xB0760331C7AA4155, p0, p1); } // B0760331C7AA4155 86FDDF55
	static scrAny GET_SCRIPT_TASK_STATUS(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x77F1BEB8863288D5, p0, p1); } // 77F1BEB8863288D5 B2477B23
	static scrAny _0x534AEBA6E5ED4CAB(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x534AEBA6E5ED4CAB, p0); } // 534AEBA6E5ED4CAB AFA914EF
	static void TASK_LEAVE_ANY_VEHICLE(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x504D54DF3F6F2247, p0, p1, p2); } // 504D54DF3F6F2247 DBDD79FA
	static void TASK_AIM_GUN_SCRIPTED(scrAny p0, scrAny p1, BOOL p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x7A192BE16D373D00, p0, p1, p2, p3); } // 7A192BE16D373D00 9D296BCD
	static void TASK_AIM_GUN_SCRIPTED_WITH_TARGET(scrAny p0, scrAny p1, float p2, float p3, float p4, scrAny p5, BOOL p6, BOOL p7) { NativeInvoke::Invoke<scrVoid>(0x8605AF0DE8B3A5AC, p0, p1, p2, p3, p4, p5, p6, p7); } // 8605AF0DE8B3A5AC FD517CE3
	static void _0x9724FB59A3E72AD0(scrAny p0, scrAny p1, float p2, float p3, float p4, BOOL p5) { NativeInvoke::Invoke<scrVoid>(0x9724FB59A3E72AD0, p0, p1, p2, p3, p4, p5); } // 9724FB59A3E72AD0 67E73525
	static scrAny _0x3A8CADC7D37AACC5(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x3A8CADC7D37AACC5, p0); } // 3A8CADC7D37AACC5 249EB4EB
	static void TASK_AIM_GUN_AT_ENTITY(scrAny p0, scrAny p1, scrAny p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x9B53BB6E8943AF53, p0, p1, p2, p3); } // 9B53BB6E8943AF53 BE32B3B6
	static void TASK_TURN_PED_TO_FACE_ENTITY(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x5AD23D40115353AC, p0, p1, p2); } // 5AD23D40115353AC 3C37C767
	static void TASK_AIM_GUN_AT_COORD(scrAny p0, float p1, float p2, float p3, scrAny p4, BOOL p5, BOOL p6) { NativeInvoke::Invoke<scrVoid>(0x6671F3EEC681BDA1, p0, p1, p2, p3, p4, p5, p6); } // 6671F3EEC681BDA1 FBF44AD3
	static void TASK_SHOOT_AT_COORD(scrAny p0, float p1, float p2, float p3, scrAny p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0x46A6CC01E0826106, p0, p1, p2, p3, p4, p5); } // 46A6CC01E0826106 601C22E3
	static void TASK_SHUFFLE_TO_NEXT_VEHICLE_SEAT(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x7AA80209BDA643EB, p0, p1); } // 7AA80209BDA643EB BEAF8F67
	static void CLEAR_PED_TASKS(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xE1EF3C1216AFF2CD, p0); } // E1EF3C1216AFF2CD DE3316AB
	static void CLEAR_PED_SECONDARY_TASK(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x176CECF6F920D707, p0); } // 176CECF6F920D707 A635F451
	static void TASK_EVERYONE_LEAVE_VEHICLE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x7F93691AB4B92272, p0); } // 7F93691AB4B92272 C1971F30
	static void TASK_GOTO_ENTITY_OFFSET(scrAny p0, scrAny p1, scrAny p2, float p3, float p4, float p5, scrAny p6) { NativeInvoke::Invoke<scrVoid>(0xE39B4FF4FDEBDE27, p0, p1, p2, p3, p4, p5, p6); } // E39B4FF4FDEBDE27 1A17A85E
	static void TASK_GOTO_ENTITY_OFFSET_XY(scrAny p0, scrAny p1, scrAny p2, float p3, float p4, float p5, float p6, scrAny p7) { NativeInvoke::Invoke<scrVoid>(0x338E7EF52B6095A9, p0, p1, p2, p3, p4, p5, p6, p7); } // 338E7EF52B6095A9 BC1E3D0A
	static void TASK_TURN_PED_TO_FACE_COORD(scrAny p0, float p1, float p2, float p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x1DDA930A0AC38571, p0, p1, p2, p3, p4); } // 1DDA930A0AC38571 30463D73
	static void TASK_VEHICLE_TEMP_ACTION(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0xC429DCEEB339E129, p0, p1, p2, p3); } // C429DCEEB339E129 0679DFB8
	static void TASK_VEHICLE_MISSION(scrAny p0, scrAny p1, scrAny p2, scrAny p3, float p4, scrAny p5, float p6, float p7, BOOL p8) { NativeInvoke::Invoke<scrVoid>(0x659427E0EF36BCDE, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 659427E0EF36BCDE 20609E56
	static void TASK_VEHICLE_MISSION_PED_TARGET(scrAny p0, scrAny p1, scrAny p2, scrAny p3, float p4, scrAny p5, float p6, float p7, BOOL p8) { NativeInvoke::Invoke<scrVoid>(0x9454528DF15D657A, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 9454528DF15D657A C81C4677
	static void TASK_VEHICLE_MISSION_COORS_TARGET(scrAny p0, scrAny p1, float p2, float p3, float p4, scrAny p5, float p6, scrAny p7, float p8, float p9, BOOL p10) { NativeInvoke::Invoke<scrVoid>(0xF0AF20AA7731F8C3, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // F0AF20AA7731F8C3 6719C109
	static void TASK_VEHICLE_ESCORT(scrAny p0, scrAny p1, scrAny p2, scrAny p3, float p4, scrAny p5, float p6, scrAny p7, float p8) { NativeInvoke::Invoke<scrVoid>(0x0FA6E4B75F302400, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 0FA6E4B75F302400 9FDCB250
	static void _0xFC545A9F0626E3B6(scrAny p0, scrAny p1, scrAny p2, float p3, scrAny p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0xFC545A9F0626E3B6, p0, p1, p2, p3, p4, p5); } // FC545A9F0626E3B6
	static void TASK_VEHICLE_CHASE(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x3C08A8E30363B353, p0, p1); } // 3C08A8E30363B353 55634798
	static void TASK_VEHICLE_HELI_PROTECT(scrAny p0, scrAny p1, scrAny p2, float p3, scrAny p4, float p5, scrAny p6, scrAny p7) { NativeInvoke::Invoke<scrVoid>(0x1E09C32048FEFD1C, p0, p1, p2, p3, p4, p5, p6, p7); } // 1E09C32048FEFD1C 0CB415EE
	static void _0xCC665AAC360D31E7(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xCC665AAC360D31E7, p0, p1, p2); } // CC665AAC360D31E7 2A83083F
	static void _0x639B642FACBE4EDD(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x639B642FACBE4EDD, p0, p1); } // 639B642FACBE4EDD 04FD3EE7
	static void TASK_HELI_CHASE(scrAny p0, scrAny p1, float p2, float p3, float p4) { NativeInvoke::Invoke<scrVoid>(0xAC83B1DB38D0ADA0, p0, p1, p2, p3, p4); } // AC83B1DB38D0ADA0 AC290A21
	static void TASK_PLANE_CHASE(scrAny p0, scrAny p1, float p2, float p3, float p4) { NativeInvoke::Invoke<scrVoid>(0x2D2386F273FF7A25, p0, p1, p2, p3, p4); } // 2D2386F273FF7A25 12FA1C28
	static void TASK_PLANE_LAND(scrAny p0, scrAny p1, float p2, float p3, float p4, float p5, float p6, float p7) { NativeInvoke::Invoke<scrVoid>(0xBF19721FA34D32C0, p0, p1, p2, p3, p4, p5, p6, p7); } // BF19721FA34D32C0 5F7E23EA
	static void TASK_HELI_MISSION(scrAny p0, scrAny p1, scrAny p2, scrAny p3, float p4, float p5, float p6, scrAny p7, float p8, float p9, float p10, scrAny p11, scrAny p12, float p13, scrAny p14) { NativeInvoke::Invoke<scrVoid>(0xDAD029E187A2BEB4, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); } // DAD029E187A2BEB4 0C143E97
	static void TASK_PLANE_MISSION(scrAny p0, scrAny p1, scrAny p2, scrAny p3, float p4, float p5, float p6, scrAny p7, float p8, float p9, float p10, scrAny p11, scrAny p12) { NativeInvoke::Invoke<scrVoid>(0x23703CD154E83B88, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 23703CD154E83B88 1D007E65
	static void TASK_BOAT_MISSION(scrAny p0, scrAny p1, scrAny p2, scrAny p3, float p4, float p5, float p6, scrAny p7, float p8, scrAny p9, float p10, scrAny p11) { NativeInvoke::Invoke<scrVoid>(0x15C86013127CE63F, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 15C86013127CE63F 5865B031
	static void TASK_DRIVE_BY(scrAny p0, scrAny p1, scrAny p2, float p3, float p4, float p5, float p6, scrAny p7, BOOL p8, scrAny p9) { NativeInvoke::Invoke<scrVoid>(0x2F8AF0E82773A171, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 2F8AF0E82773A171 2B84D1C4
	static void SET_DRIVEBY_TASK_TARGET(scrAny p0, scrAny p1, scrAny p2, float p3, float p4, float p5) { NativeInvoke::Invoke<scrVoid>(0xE5B302114D8162EE, p0, p1, p2, p3, p4, p5); } // E5B302114D8162EE DA6A6FC1
	static void _0xC35B5CDB2824CF69(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xC35B5CDB2824CF69, p0); } // C35B5CDB2824CF69 9B76F7E6
	static BOOL _0x8785E6E40C7A8818(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x8785E6E40C7A8818, p0); } // 8785E6E40C7A8818 B23F46E6
	static BOOL _0xDCFE42068FE0135A(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xDCFE42068FE0135A, p0); } // DCFE42068FE0135A 500D9244
	static void _0xCCD892192C6D2BB9(scrAny p0, scrAny p1, scrAny p2, float p3, float p4, float p5) { NativeInvoke::Invoke<scrVoid>(0xCCD892192C6D2BB9, p0, p1, p2, p3, p4, p5); } // CCD892192C6D2BB9 98713C68
	static BOOL _0xA320EF046186FA3B(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xA320EF046186FA3B, p0); } // A320EF046186FA3B 291E938C
	static void TASK_USE_MOBILE_PHONE(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xBD2A8EC3AF4DE7DB, p0, p1); } // BD2A8EC3AF4DE7DB 225A38C8
	static void TASK_USE_MOBILE_PHONE_TIMED(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x5EE02954A14C69DB, p0, p1); } // 5EE02954A14C69DB C99C19F5
	static void TASK_CHAT_TO_PED(scrAny p0, scrAny p1, scrAny p2, float p3, float p4, float p5, float p6, float p7) { NativeInvoke::Invoke<scrVoid>(0x8C338E0263E4FD19, p0, p1, p2, p3, p4, p5, p6, p7); } // 8C338E0263E4FD19 A2BE1821
	static void TASK_WARP_PED_INTO_VEHICLE(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x9A7D091411C5F684, p0, p1, p2); } // 9A7D091411C5F684 65D4A35D
	static void TASK_SHOOT_AT_ENTITY(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x08DA95E8298AE772, p0, p1, p2, p3); } // 08DA95E8298AE772 AC0631C9
	static void TASK_CLIMB(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x89D9FCC2435112F1, p0, p1); } // 89D9FCC2435112F1 90847790
	static void TASK_CLIMB_LADDER(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xB6C987F9285A3814, p0, p1); } // B6C987F9285A3814 35BB4EE0
	static void CLEAR_PED_TASKS_IMMEDIATELY(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xAAA34F8A7CB32098, p0); } // AAA34F8A7CB32098 BC045625
	static void TASK_PERFORM_SEQUENCE_FROM_PROGRESS(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x89221B16730234F0, p0, p1, p2, p3); } // 89221B16730234F0 FA60601B
	static void SET_NEXT_DESIRED_MOVE_STATE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xF1B9F16E89E2C93A, p0); } // F1B9F16E89E2C93A 4E937D57
	static void SET_PED_DESIRED_MOVE_BLEND_RATIO(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x1E982AC8716912C5, p0, p1); } // 1E982AC8716912C5 C65FC712
	static scrAny GET_PED_DESIRED_MOVE_BLEND_RATIO(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x8517D4A6CA8513ED, p0); } // 8517D4A6CA8513ED 5FEFAB72
	static void TASK_GOTO_ENTITY_AIMING(scrAny p0, scrAny p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0xA9DA48FAB8A76C12, p0, p1, p2, p3); } // A9DA48FAB8A76C12 F1C493CF
	static void TASK_SET_DECISION_MAKER(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xEB8517DDA73720DA, p0, p1); } // EB8517DDA73720DA 830AD50C
	static void TASK_SET_SPHERE_DEFENSIVE_AREA(scrAny p0, float p1, float p2, float p3, float p4) { NativeInvoke::Invoke<scrVoid>(0x933C06518B52A9A4, p0, p1, p2, p3, p4); } // 933C06518B52A9A4 9F3C5D6A
	static void TASK_CLEAR_DEFENSIVE_AREA(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x95A6C46A31D1917D, p0); } // 95A6C46A31D1917D 7A05BF0D
	static void TASK_PED_SLIDE_TO_COORD(scrAny p0, float p1, float p2, float p3, float p4, float p5) { NativeInvoke::Invoke<scrVoid>(0xD04FE6765D990A06, p0, p1, p2, p3, p4, p5); } // D04FE6765D990A06 225380EF
	static void TASK_PED_SLIDE_TO_COORD_HDG_RATE(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6) { NativeInvoke::Invoke<scrVoid>(0x5A4A6A6D3DC64F52, p0, p1, p2, p3, p4, p5, p6); } // 5A4A6A6D3DC64F52 38A995C1
	static scrAny ADD_COVER_POINT(float p0, float p1, float p2, float p3, scrAny p4, scrAny p5, scrAny p6, BOOL p7) { return NativeInvoke::Invoke<scrAny>(0xD5C12A75C7B9497F, p0, p1, p2, p3, p4, p5, p6, p7); } // D5C12A75C7B9497F A0AF0B98
	static void REMOVE_COVER_POINT(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xAE287C923D891715, p0); } // AE287C923D891715 0776888B
	static BOOL _0xA98B8E3C088E5A31(float p0, float p1, float p2) { return NativeInvoke::Invoke<BOOL>(0xA98B8E3C088E5A31, p0, p1, p2); } // A98B8E3C088E5A31 29F97A71
	static scrVector3 _0x594A1028FC2A3E85(scrAny p0) { return NativeInvoke::Invoke<scrVector3>(0x594A1028FC2A3E85, p0); } // 594A1028FC2A3E85 C6B6CCC1
	static void TASK_COMBAT_PED(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0xF166E48407BAC484, p0, p1, p2, p3); } // F166E48407BAC484 CB0D8932
	static void TASK_COMBAT_PED_TIMED(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x944F30DCB7096BDE, p0, p1, p2, p3); } // 944F30DCB7096BDE F5CA2A45
	static void TASK_SEEK_COVER_FROM_POS(scrAny p0, float p1, float p2, float p3, scrAny p4, BOOL p5) { NativeInvoke::Invoke<scrVoid>(0x75AC2B60386D89F2, p0, p1, p2, p3, p4, p5); } // 75AC2B60386D89F2 83F18EE9
	static void TASK_SEEK_COVER_FROM_PED(scrAny p0, scrAny p1, scrAny p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x84D32B3BEC531324, p0, p1, p2, p3); } // 84D32B3BEC531324 C1EC907E
	static void TASK_SEEK_COVER_TO_COVER_POINT(scrAny p0, scrAny p1, float p2, float p3, float p4, scrAny p5, BOOL p6) { NativeInvoke::Invoke<scrVoid>(0xD43D95C7A869447F, p0, p1, p2, p3, p4, p5, p6); } // D43D95C7A869447F 3D026B29
	static void TASK_SEEK_COVER_TO_COORDS(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, scrAny p7, BOOL p8) { NativeInvoke::Invoke<scrVoid>(0x39246A6958EF072C, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 39246A6958EF072C FFFE754E
	static void TASK_PUT_PED_DIRECTLY_INTO_COVER(scrAny p0, float p1, float p2, float p3, scrAny p4, BOOL p5, float p6, BOOL p7, BOOL p8, scrAny p9, BOOL p10) { NativeInvoke::Invoke<scrVoid>(0x4172393E6BE1FECE, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 4172393E6BE1FECE C9F00E68
	static void TASK_EXIT_COVER(scrAny p0, scrAny p1, float p2, float p3, float p4) { NativeInvoke::Invoke<scrVoid>(0x79B258E397854D29, p0, p1, p2, p3, p4); } // 79B258E397854D29 C829FAC9
	static void TASK_PUT_PED_DIRECTLY_INTO_MELEE(scrAny p0, scrAny p1, float p2, float p3, float p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0x1C6CD14A876FFE39, p0, p1, p2, p3, p4, p5); } // 1C6CD14A876FFE39 79E1D27D
	static void TASK_TOGGLE_DUCK(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xAC96609B9995EDF8, p0, p1); } // AC96609B9995EDF8 61CFBCBF
	static void TASK_GUARD_CURRENT_POSITION(scrAny p0, float p1, float p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x4A58A47A72E3FCB4, p0, p1, p2, p3); } // 4A58A47A72E3FCB4 2FB099E9
	static void _0xD2A207EEBDF9889B(scrAny p0, float p1, float p2, float p3, float p4, float p5, scrAny p6) { NativeInvoke::Invoke<scrVoid>(0xD2A207EEBDF9889B, p0, p1, p2, p3, p4, p5, p6); } // D2A207EEBDF9889B 7AF0133D
	static void TASK_GUARD_SPHERE_DEFENSIVE_AREA(scrAny p0, float p1, float p2, float p3, float p4, float p5, scrAny p6, float p7, float p8, float p9, float p10) { NativeInvoke::Invoke<scrVoid>(0xC946FE14BE0EB5E2, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // C946FE14BE0EB5E2 86B76CB7
	static void TASK_STAND_GUARD(scrAny p0, float p1, float p2, float p3, float p4, scrAny *p5) { NativeInvoke::Invoke<scrVoid>(0xAE032F8BBA959E90, p0, p1, p2, p3, p4, p5); } // AE032F8BBA959E90 D130F636
	static void SET_DRIVE_TASK_CRUISE_SPEED(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x5C9B84BD7D31D908, p0, p1); } // 5C9B84BD7D31D908 3CEC07B1
	static void SET_DRIVE_TASK_MAX_CRUISE_SPEED(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x404A5AA9B9F0B746, p0, p1); } // 404A5AA9B9F0B746 7FDF6131
	static void _0xDACE1BE37D88AF67(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xDACE1BE37D88AF67, p0, p1); } // DACE1BE37D88AF67 59C5FAD7
	static void ADD_COVER_BLOCKING_AREA(float p0, float p1, float p2, float p3, float p4, float p5, BOOL p6, BOOL p7, BOOL p8, BOOL p9) { NativeInvoke::Invoke<scrVoid>(0x45C597097DD7CB81, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 45C597097DD7CB81 3536946F
	static void REMOVE_ALL_COVER_BLOCKING_AREAS() { NativeInvoke::Invoke<scrVoid>(0xDB6708C0B46F56D8); } // DB6708C0B46F56D8 CF9221A7
	static void TASK_START_SCENARIO_IN_PLACE(scrAny p0, scrAny *p1, scrAny p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x142A02425FF02BD9, p0, p1, p2, p3); } // 142A02425FF02BD9 E50D6DDE
	static void TASK_START_SCENARIO_AT_POSITION(scrAny p0, scrAny *p1, float p2, float p3, float p4, float p5, scrAny p6, BOOL p7, BOOL p8) { NativeInvoke::Invoke<scrVoid>(0xFA4EFC79F69D4F07, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // FA4EFC79F69D4F07 AA2C4AC2
	static void TASK_USE_NEAREST_SCENARIO_TO_COORD(scrAny p0, float p1, float p2, float p3, float p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0x277F471BA9DB000B, p0, p1, p2, p3, p4, p5); } // 277F471BA9DB000B 9C50FBF0
	static void TASK_USE_NEAREST_SCENARIO_TO_COORD_WARP(scrAny p0, float p1, float p2, float p3, float p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0x58E2E0F23F6B76C3, p0, p1, p2, p3, p4, p5); } // 58E2E0F23F6B76C3 1BE9D65C
	static void TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD(scrAny p0, float p1, float p2, float p3, float p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0x9FDA1B3D7E7028B3, p0, p1, p2, p3, p4, p5); } // 9FDA1B3D7E7028B3 E32FFB22
	static void TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD_WARP(scrAny p0, float p1, float p2, float p3, float p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0x97A28E63F0BA5631, p0, p1, p2, p3, p4, p5); } // 97A28E63F0BA5631 BAB4C0AE
	static BOOL DOES_SCENARIO_EXIST_IN_AREA(float p0, float p1, float p2, float p3, BOOL p4) { return NativeInvoke::Invoke<BOOL>(0x5A59271FFADD33C1, p0, p1, p2, p3, p4); } // 5A59271FFADD33C1 FA7F5047
	static BOOL _0x0A9D0C2A3BBC86C1(float p0, float p1, float p2, scrAny *p3, float p4, BOOL p5) { return NativeInvoke::Invoke<BOOL>(0x0A9D0C2A3BBC86C1, p0, p1, p2, p3, p4, p5); } // 0A9D0C2A3BBC86C1 0FB138A5
	static BOOL IS_SCENARIO_OCCUPIED(float p0, float p1, float p2, float p3, BOOL p4) { return NativeInvoke::Invoke<BOOL>(0x788756D73AC2E07C, p0, p1, p2, p3, p4); } // 788756D73AC2E07C 697FC008
	static BOOL _0x295E3CCEC879CCD7(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x295E3CCEC879CCD7, p0); } // 295E3CCEC879CCD7 9BE9C691
	static void _0x748040460F8DF5DC(scrAny p0, scrAny *p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0x748040460F8DF5DC, p0, p1, p2); } // 748040460F8DF5DC 1984A5D1
	static BOOL DOES_SCENARIO_GROUP_EXIST(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xF9034C136C9E00D3, p0); } // F9034C136C9E00D3 5F072EB9
	static BOOL IS_SCENARIO_GROUP_ENABLED(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x367A09DED4E05B99, p0); } // 367A09DED4E05B99 90991122
	static void SET_SCENARIO_GROUP_ENABLED(scrAny *p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x02C8E5B49848664E, p0, p1); } // 02C8E5B49848664E 116997B1
	static void _0xDD902D0349AFAD3A() { NativeInvoke::Invoke<scrVoid>(0xDD902D0349AFAD3A); } // DD902D0349AFAD3A BF55025D
	static void SET_EXCLUSIVE_SCENARIO_GROUP(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x535E97E1F7FC0C6A, p0); } // 535E97E1F7FC0C6A 59DB8F26
	static void RESET_EXCLUSIVE_SCENARIO_GROUP() { NativeInvoke::Invoke<scrVoid>(0x4202BBCB8684563D); } // 4202BBCB8684563D 17F9DFE8
	static BOOL IS_SCENARIO_TYPE_ENABLED(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x3A815DB3EA088722, p0); } // 3A815DB3EA088722 AE37E969
	static void SET_SCENARIO_TYPE_ENABLED(scrAny *p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xEB47EC4E34FB7EE1, p0, p1); } // EB47EC4E34FB7EE1 DB18E5DE
	static void _0x0D40EE2A7F2B2D6D() { NativeInvoke::Invoke<scrVoid>(0x0D40EE2A7F2B2D6D); } // 0D40EE2A7F2B2D6D F58FDEB4
	static BOOL IS_PED_ACTIVE_IN_SCENARIO(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xAA135F9482C82CC3, p0); } // AA135F9482C82CC3 05038F1A
	static void TASK_COMBAT_HATED_TARGETS_IN_AREA(scrAny p0, float p1, float p2, float p3, float p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0x4CF5F55DAC3280A0, p0, p1, p2, p3, p4, p5); } // 4CF5F55DAC3280A0 DF099E18
	static void TASK_COMBAT_HATED_TARGETS_AROUND_PED(scrAny p0, float p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x7BF835BB9E2698C8, p0, p1, p2); } // 7BF835BB9E2698C8 2E7064E4
	static void TASK_COMBAT_HATED_TARGETS_AROUND_PED_TIMED(scrAny p0, float p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x2BBA30B854534A0C, p0, p1, p2, p3); } // 2BBA30B854534A0C F127AD6A
	static void TASK_THROW_PROJECTILE(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x7285951DBF6B5A51, p0, p1, p2, p3); } // 7285951DBF6B5A51 F65C20A7
	static void TASK_SWAP_WEAPON(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xA21C51255B205245, p0, p1); } // A21C51255B205245 DAF4F8FC
	static void TASK_RELOAD_WEAPON(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x62D2916F56B9CD2D, p0, p1); } // 62D2916F56B9CD2D CA6E91FD
	static BOOL IS_PED_GETTING_UP(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x2A74E1D5F2F00EEC, p0); } // 2A74E1D5F2F00EEC 320813E6
	static void TASK_WRITHE(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0xCDDC2B77CE54AC6E, p0, p1, p2, p3); } // CDDC2B77CE54AC6E 0FDC54FC
	static BOOL IS_PED_IN_WRITHE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xDEB6D52126E7D640, p0); } // DEB6D52126E7D640 09E61921
	static void OPEN_PATROL_ROUTE(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xA36BFB5EE89F3D82, p0); } // A36BFB5EE89F3D82 F33F83CA
	static void CLOSE_PATROL_ROUTE() { NativeInvoke::Invoke<scrVoid>(0xB043ECA801B8CBC1); } // B043ECA801B8CBC1 67305E59
	static void ADD_PATROL_ROUTE_NODE(scrAny p0, scrAny *p1, float p2, float p3, float p4, float p5, float p6, float p7, scrAny p8) { NativeInvoke::Invoke<scrVoid>(0x8EDF950167586B7C, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 8EDF950167586B7C 21B48F10
	static void ADD_PATROL_ROUTE_LINK(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x23083260DEC3A551, p0, p1); } // 23083260DEC3A551 D8761BB3
	static void CREATE_PATROL_ROUTE() { NativeInvoke::Invoke<scrVoid>(0xAF8A443CCC8018DC); } // AF8A443CCC8018DC 0A6C7864
	static void DELETE_PATROL_ROUTE(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x7767DD9D65E91319, p0); } // 7767DD9D65E91319 2A4E6706
	static void TASK_PATROL(scrAny p0, scrAny *p1, scrAny p2, BOOL p3, BOOL p4) { NativeInvoke::Invoke<scrVoid>(0xBDA5DF49D080FE4E, p0, p1, p2, p3, p4); } // BDA5DF49D080FE4E B92E5AF6
	static void TASK_STAY_IN_COVER(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xE5DA8615A6180789, p0); } // E5DA8615A6180789 A27A9413
	static void _0x5CF0D8F9BBA0DD75(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x5CF0D8F9BBA0DD75, p0, p1, p2, p3); } // 5CF0D8F9BBA0DD75 50779A2C
	static void ADD_VEHICLE_SUBTASK_ATTACK_PED(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x85F462BADC7DA47F, p0, p1); } // 85F462BADC7DA47F 80461113
	static void TASK_VEHICLE_SHOOT_AT_PED(scrAny p0, scrAny p1, float p2) { NativeInvoke::Invoke<scrVoid>(0x10AB107B887214D8, p0, p1, p2); } // 10AB107B887214D8 59677BA0
	static void TASK_VEHICLE_AIM_AT_PED(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xE41885592B08B097, p0, p1); } // E41885592B08B097 920AE6DB
	static void TASK_VEHICLE_SHOOT_AT_COORD(scrAny p0, float p1, float p2, float p3, float p4) { NativeInvoke::Invoke<scrVoid>(0x5190796ED39C9B6D, p0, p1, p2, p3, p4); } // 5190796ED39C9B6D A7AAA4D6
	static void TASK_VEHICLE_AIM_AT_COORD(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x447C1E9EF844BC0F, p0, p1, p2, p3); } // 447C1E9EF844BC0F 010F47CE
	static void TASK_VEHICLE_GOTO_NAVMESH(scrAny p0, scrAny p1, float p2, float p3, float p4, float p5, scrAny p6, float p7) { NativeInvoke::Invoke<scrVoid>(0x195AEEB13CEFE2EE, p0, p1, p2, p3, p4, p5, p6, p7); } // 195AEEB13CEFE2EE 55CF3BCD
	static void TASK_GO_TO_COORD_WHILE_AIMING_AT_COORD(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, BOOL p8, float p9, float p10, BOOL p11, scrAny p12, BOOL p13, scrAny p14) { NativeInvoke::Invoke<scrVoid>(0x11315AB3385B8AC0, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); } // 11315AB3385B8AC0 1552DC91
	static void TASK_GO_TO_COORD_WHILE_AIMING_AT_ENTITY(scrAny p0, float p1, float p2, float p3, scrAny p4, float p5, BOOL p6, float p7, float p8, BOOL p9, scrAny p10, BOOL p11, scrAny p12, scrAny p13) { NativeInvoke::Invoke<scrVoid>(0xB2A16444EAD9AE47, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } // B2A16444EAD9AE47 9BD52ABD
	static void TASK_GO_TO_COORD_AND_AIM_AT_HATED_ENTITIES_NEAR_COORD(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, BOOL p8, float p9, float p10, BOOL p11, scrAny p12, scrAny p13, scrAny p14) { NativeInvoke::Invoke<scrVoid>(0xA55547801EB331FC, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); } // A55547801EB331FC 3F91358E
	static void TASK_GO_TO_ENTITY_WHILE_AIMING_AT_COORD(scrAny p0, scrAny p1, float p2, float p3, float p4, float p5, BOOL p6, float p7, float p8, BOOL p9, BOOL p10, scrAny p11) { NativeInvoke::Invoke<scrVoid>(0x04701832B739DCE5, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 04701832B739DCE5 D896CD82
	static void TASK_GO_TO_ENTITY_WHILE_AIMING_AT_ENTITY(scrAny p0, scrAny p1, scrAny p2, float p3, BOOL p4, float p5, float p6, BOOL p7, BOOL p8, scrAny p9) { NativeInvoke::Invoke<scrVoid>(0x97465886D35210E9, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 97465886D35210E9 68E36B7A
	static void SET_HIGH_FALL_TASK(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x8C825BDC7741D37C, p0, p1, p2, p3); } // 8C825BDC7741D37C BBB26172
	static void REQUEST_WAYPOINT_RECORDING(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x9EEFB62EB27B5792, p0); } // 9EEFB62EB27B5792 AFABFB5D
	static BOOL _0xCB4E8BE8A0063C5D(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xCB4E8BE8A0063C5D, p0); } // CB4E8BE8A0063C5D 87125F5D
	static void REMOVE_WAYPOINT_RECORDING(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xFF1B8B4AA1C25DC8, p0); } // FF1B8B4AA1C25DC8 624530B0
	static BOOL _0x5343532C01A07234(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x5343532C01A07234, p0, p1); } // 5343532C01A07234 F5F9B71E
	static scrAny _0x2FB897405C90B361(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0x2FB897405C90B361, p0, p1, p2); } // 2FB897405C90B361 19266913
	static float _0x005622AEBC33ACA9(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<float>(0x005622AEBC33ACA9, p0, p1); } // 005622AEBC33ACA9 C765633A
	static BOOL _0xB629A298081F876F(scrAny *p0, float p1, float p2, float p3, scrAny *p4) { return NativeInvoke::Invoke<BOOL>(0xB629A298081F876F, p0, p1, p2, p3, p4); } // B629A298081F876F C4CD35AF
	static void TASK_FOLLOW_WAYPOINT_RECORDING(scrAny p0, scrAny *p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x0759591819534F7B, p0, p1, p2, p3, p4); } // 0759591819534F7B ADF9904D
	static BOOL IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_PED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xE03B3F2D3DC59B64, p0); } // E03B3F2D3DC59B64 85B7725F
	static scrAny GET_PED_WAYPOINT_PROGRESS(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x2720AAA75001E094, p0); } // 2720AAA75001E094 3595B104
	static float GET_PED_WAYPOINT_DISTANCE(scrAny p0) { return NativeInvoke::Invoke<float>(0xE6A877C64CAF1BC5, p0); } // E6A877C64CAF1BC5 084B35B0
	static scrAny SET_PED_WAYPOINT_ROUTE_OFFSET(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0xED98E10B0AFCE4B4, p0, p1, p2, p3); } // ED98E10B0AFCE4B4 F867F747
	static float _0xA5B769058763E497(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<float>(0xA5B769058763E497, p0, p1); } // A5B769058763E497 E8422AC4
	static BOOL WAYPOINT_PLAYBACK_GET_IS_PAUSED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x701375A7D43F01CB, p0); } // 701375A7D43F01CB A6BB5717
	static void WAYPOINT_PLAYBACK_PAUSE(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x0F342546AA06FED5, p0, p1, p2); } // 0F342546AA06FED5 FE39ECF8
	static void WAYPOINT_PLAYBACK_RESUME(scrAny p0, BOOL p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x244F70C84C547D2D, p0, p1, p2, p3); } // 244F70C84C547D2D 50F392EF
	static void WAYPOINT_PLAYBACK_OVERRIDE_SPEED(scrAny p0, float p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x7D7D2B47FA788E85, p0, p1, p2); } // 7D7D2B47FA788E85 23E6BA96
	static void WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x6599D834B12D0800, p0); } // 6599D834B12D0800 1BBB2CAC
	static void _0x5A353B8E6B1095B5(scrAny *p0, BOOL p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x5A353B8E6B1095B5, p0, p1, p2, p3); } // 5A353B8E6B1095B5 4DFD5FEC
	static void WAYPOINT_PLAYBACK_START_AIMING_AT_PED(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x20E330937C399D29, p0, p1, p2); } // 20E330937C399D29 75E60CF6
	static void WAYPOINT_PLAYBACK_START_AIMING_AT_COORD(scrAny p0, float p1, float p2, float p3, BOOL p4) { NativeInvoke::Invoke<scrVoid>(0x8968400D900ED8B3, p0, p1, p2, p3, p4); } // 8968400D900ED8B3 F120A34E
	static void WAYPOINT_PLAYBACK_START_SHOOTING_AT_COORD(scrAny p0, float p1, float p2, float p3, BOOL p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0x057A25CFCC9DB671, p0, p1, p2, p3, p4, p5); } // 057A25CFCC9DB671 CDDB44D5
	static void WAYPOINT_PLAYBACK_STOP_AIMING_OR_SHOOTING(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x47EFA040EBB8E2EA, p0); } // 47EFA040EBB8E2EA 6D7CF40C
	static void ASSISTED_MOVEMENT_REQUEST_ROUTE(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x817268968605947A, p0); } // 817268968605947A 48262EDA
	static void ASSISTED_MOVEMENT_REMOVE_ROUTE(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x3548536485DD792B, p0); } // 3548536485DD792B B3CEC06F
	static BOOL _0x60F9A4393A21F741(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x60F9A4393A21F741, p0); } // 60F9A4393A21F741 79B067AF
	static void _0xD5002D78B7162E1B(scrAny *p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xD5002D78B7162E1B, p0, p1); } // D5002D78B7162E1B 01CAAFCC
	static void _0x13945951E16EF912(float p0) { NativeInvoke::Invoke<scrVoid>(0x13945951E16EF912, p0); } // 13945951E16EF912 8FB923EC
	static void TASK_VEHICLE_FOLLOW_WAYPOINT_RECORDING(scrAny p0, scrAny p1, scrAny *p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, float p7, BOOL p8, float p9) { NativeInvoke::Invoke<scrVoid>(0x3123FAA6DB1CF7ED, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 3123FAA6DB1CF7ED 959818B6
	static BOOL IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_VEHICLE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xF5134943EA29868C, p0); } // F5134943EA29868C 80DD15DB
	static scrAny GET_VEHICLE_WAYPOINT_PROGRESS(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x9824CFF8FC66E159, p0); } // 9824CFF8FC66E159 D3CCF64E
	static scrAny GET_VEHICLE_WAYPOINT_TARGET_POINT(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x416B62AC8B9E5BBD, p0); } // 416B62AC8B9E5BBD 81049608
	static void VEHICLE_WAYPOINT_PLAYBACK_PAUSE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x8A4E6AC373666BC5, p0); } // 8A4E6AC373666BC5 7C00B415
	static void VEHICLE_WAYPOINT_PLAYBACK_RESUME(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xDC04FCAA7839D492, p0); } // DC04FCAA7839D492 BEB14C82
	static void VEHICLE_WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x5CEB25A7D2848963, p0); } // 5CEB25A7D2848963 923C3AA4
	static void VEHICLE_WAYPOINT_PLAYBACK_OVERRIDE_SPEED(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x121F0593E0A431D7, p0, p1); } // 121F0593E0A431D7 BE1E7BB4
	static void TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x90D2156198831D69, p0, p1); } // 90D2156198831D69 1B54FB6B
	static void TASK_FORCE_MOTION_STATE(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x4F056E1AFFEF17AB, p0, p1, p2); } // 4F056E1AFFEF17AB CAD2EF77
	static void _0x2D537BA194896636(scrAny p0, scrAny *p1, float p2, BOOL p3, scrAny *p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0x2D537BA194896636, p0, p1, p2, p3, p4, p5); } // 2D537BA194896636 6F5D215F
	static void _0xD5B35BEA41919ACB(scrAny p0, scrAny *p1, float p2, float p3, float p4, float p5, float p6, float p7, scrAny p8, float p9, BOOL p10, scrAny *p11, scrAny p12) { NativeInvoke::Invoke<scrVoid>(0xD5B35BEA41919ACB, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // D5B35BEA41919ACB 71A5C5DB
	static BOOL _0x921CE12C489C4C41(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x921CE12C489C4C41, p0); } // 921CE12C489C4C41 902656EB
	static BOOL _0x30ED88D5E0C56A37(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x30ED88D5E0C56A37, p0); } // 30ED88D5E0C56A37 92FDBAE6
	static scrAny _0xD01015C7316AE176(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xD01015C7316AE176, p0, p1); } // D01015C7316AE176 885724DE
	static scrAny _0x717E4D1F2048376D(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x717E4D1F2048376D, p0); } // 717E4D1F2048376D 96C0277B
	static void _0xD5BB4025AE449A4E(scrAny p0, scrAny *p1, float p2) { NativeInvoke::Invoke<scrVoid>(0xD5BB4025AE449A4E, p0, p1, p2); } // D5BB4025AE449A4E A79BE783
	static void _0xB0A6CFD2C69C1088(scrAny p0, scrAny *p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xB0A6CFD2C69C1088, p0, p1, p2); } // B0A6CFD2C69C1088 F3538041
	static BOOL _0xA7FFBA498E4AAF67(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0xA7FFBA498E4AAF67, p0, p1); } // A7FFBA498E4AAF67 1EBB6F3D
	static BOOL _0xB4F47213DF45A64C(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0xB4F47213DF45A64C, p0, p1); } // B4F47213DF45A64C 72FA5EF2
	static scrAny _0x349CE7B56DAFD95C(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x349CE7B56DAFD95C, p0); } // 349CE7B56DAFD95C E9DAF877
	static scrAny _0xF133BBBE91E1691F(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xF133BBBE91E1691F, p0); } // F133BBBE91E1691F D21639A8
	static scrAny _0xD4D8636C0199A939(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xD4D8636C0199A939, p0); } // D4D8636C0199A939 E76A2353
	static scrAny _0x24A2AD74FA9814E2(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x24A2AD74FA9814E2, p0); } // 24A2AD74FA9814E2 DD616893
	static BOOL IS_PED_STILL(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xAC29253EEF8F0180, p0); } // AC29253EEF8F0180 09E3418D
	static BOOL IS_PED_WALKING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xDE4C184B2B9B071A, p0); } // DE4C184B2B9B071A 4B865C4A
	static BOOL IS_PED_RUNNING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xC5286FFC176F28A2, p0); } // C5286FFC176F28A2 E9A5578F
	static BOOL IS_PED_SPRINTING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x57E457CD2C0FC168, p0); } // 57E457CD2C0FC168 4F3E0633
	static BOOL IS_PED_STRAFING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xE45B7F222DE47E09, p0); } // E45B7F222DE47E09 EFEED13C
	static void TASK_SYNCHRONIZED_SCENE(scrAny p0, scrAny p1, scrAny *p2, scrAny *p3, float p4, float p5, scrAny p6, scrAny p7, float p8, scrAny p9) { NativeInvoke::Invoke<scrVoid>(0xEEA929141F699854, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // EEA929141F699854 4F217E7B
	static void _0x2047C02158D6405A(scrAny p0, scrAny *p1, scrAny *p2, scrAny *p3, scrAny *p4, scrAny p5, scrAny p6, float p7, float p8) { NativeInvoke::Invoke<scrVoid>(0x2047C02158D6405A, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 2047C02158D6405A 4D210467
	static void _0xE4973DBDBE6E44B3(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xE4973DBDBE6E44B3, p0, p1); } // E4973DBDBE6E44B3 F65F0F4F
	static void _0x7AFE8FDC10BC07D2(scrAny p0, scrAny *p1, scrAny *p2, scrAny *p3, scrAny *p4, scrAny p5, float p6, float p7, float p8, float p9, float p10) { NativeInvoke::Invoke<scrVoid>(0x7AFE8FDC10BC07D2, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 7AFE8FDC10BC07D2 1683FE66
	static void _0xBB106883F5201FC4(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0xBB106883F5201FC4, p0, p1, p2, p3); } // BB106883F5201FC4 6345EC80
	static void TASK_ARREST_PED(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xF3B9A78A178572B1, p0, p1); } // F3B9A78A178572B1 BC0F153D
	static BOOL IS_PED_RUNNING_ARREST_TASK(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x3DC52677769B4AE0, p0); } // 3DC52677769B4AE0 6942DB7A
	static scrAny IS_PED_BEING_ARRESTED(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x90A09F3A45FED688, p0); } // 90A09F3A45FED688 5FF6C2ED
	static void UNCUFF_PED(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x67406F2C8F87FC4F, p0); } // 67406F2C8F87FC4F A23A1D61
	static BOOL IS_PED_CUFFED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x74E559B3BC910685, p0); } // 74E559B3BC910685 511CE741
}

namespace GAMEPLAY
{
	static scrAny _0x8B3CA62B1EF19B62() { return NativeInvoke::Invoke<scrAny>(0x8B3CA62B1EF19B62); } // 8B3CA62B1EF19B62 4E9CA30A
	static scrAny _0xFEAD16FC8F9DFC0F(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xFEAD16FC8F9DFC0F, p0); } // FEAD16FC8F9DFC0F 11A178B8
	static void SET_RANDOM_SEED(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x444D98F98C11F3EC, p0); } // 444D98F98C11F3EC DB3FEB5C
	static void SET_TIME_SCALE(float p0) { NativeInvoke::Invoke<scrVoid>(0x1D408577D440E81E, p0); } // 1D408577D440E81E A7F84694
	static void SET_MISSION_FLAG(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xC4301E5121A0ED73, p0); } // C4301E5121A0ED73 57592D52
	static BOOL GET_MISSION_FLAG() { return NativeInvoke::Invoke<BOOL>(0xA33CDCCDA663159E); } // A33CDCCDA663159E 95115F97
	static void SET_RANDOM_EVENT_FLAG(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x971927086CFD2158, p0); } // 971927086CFD2158 A77F31E8
	static scrAny GET_RANDOM_EVENT_FLAG() { return NativeInvoke::Invoke<scrAny>(0xD2D57F1D764117B1); } // D2D57F1D764117B1 794CC92C
	static scrAny _0x24DA7D7667FD7B09() { return NativeInvoke::Invoke<scrAny>(0x24DA7D7667FD7B09); } // 24DA7D7667FD7B09
	static void _0x4DCDF92BF64236CD(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x4DCDF92BF64236CD, p0, p1); } // 4DCDF92BF64236CD
	static void _0x31125FD509D9043F(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x31125FD509D9043F, p0); } // 31125FD509D9043F
	static void _0xEBD3205A207939ED(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xEBD3205A207939ED, p0); } // EBD3205A207939ED
	static void _0x97E7E2C04245115B(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x97E7E2C04245115B, p0); } // 97E7E2C04245115B
	static void _0xEB078CA2B5E82ADD(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xEB078CA2B5E82ADD, p0, p1); } // EB078CA2B5E82ADD
	static void _0x703CC7F60CBB2B57(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x703CC7F60CBB2B57, p0); } // 703CC7F60CBB2B57
	static void _0x8951EB9C6906D3C8() { NativeInvoke::Invoke<scrVoid>(0x8951EB9C6906D3C8); } // 8951EB9C6906D3C8
	static void _0xBA4B8D83BDC75551(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xBA4B8D83BDC75551, p0); } // BA4B8D83BDC75551
	static void _0x65D2EBB47E1CEC21(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x65D2EBB47E1CEC21, p0); } // 65D2EBB47E1CEC21
	static void _0x6F2135B6129620C1(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x6F2135B6129620C1, p0); } // 6F2135B6129620C1 8B2DE971
	static void _0x8D74E26F54B4E5C3(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x8D74E26F54B4E5C3, p0); } // 8D74E26F54B4E5C3 E77199F7
	static scrAny _0x564B884A05EC45A3() { return NativeInvoke::Invoke<scrAny>(0x564B884A05EC45A3); } // 564B884A05EC45A3 A8171E9E
	static scrAny _0x711327CD09C8F162() { return NativeInvoke::Invoke<scrAny>(0x711327CD09C8F162); } // 711327CD09C8F162 353E8056
	static BOOL IS_PREV_WEATHER_TYPE(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x44F28F86433B10A9, p0); } // 44F28F86433B10A9 250ADA61
	static BOOL IS_NEXT_WEATHER_TYPE(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x2FAA3A30BEC0F25D, p0); } // 2FAA3A30BEC0F25D 99CB167F
	static void SET_WEATHER_TYPE_PERSIST(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x704983DF373B198F, p0); } // 704983DF373B198F C6C04C75
	static void SET_WEATHER_TYPE_NOW_PERSIST(char *p0) { NativeInvoke::Invoke<scrVoid>(0xED712CA327900C8A, p0); } // ED712CA327900C8A C869FE97
	static void SET_WEATHER_TYPE_NOW(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x29B487C359E19889, p0); } // 29B487C359E19889 361E9EAC
	static void _0xFB5045B7C42B75BF(scrAny *p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xFB5045B7C42B75BF, p0, p1); } // FB5045B7C42B75BF 386F0D25
	static void SET_RANDOM_WEATHER_TYPE() { NativeInvoke::Invoke<scrVoid>(0x8B05F884CF7E8020); } // 8B05F884CF7E8020 E7AA1BC9
	static void CLEAR_WEATHER_TYPE_PERSIST() { NativeInvoke::Invoke<scrVoid>(0xCCC39339BEF76CF5); } // CCC39339BEF76CF5 6AB757D8
	static void _0xF3BBE884A14BB413(scrAny *p0, scrAny *p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0xF3BBE884A14BB413, p0, p1, p2); } // F3BBE884A14BB413 9A5C1D56
	static void _0x578C752848ECFA0C(scrAny p0, scrAny p1, float p2) { NativeInvoke::Invoke<scrVoid>(0x578C752848ECFA0C, p0, p1, p2); } // 578C752848ECFA0C 5CA74040
	static void SET_OVERRIDE_WEATHER(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xA43D5C6FE51ADBEF, p0); } // A43D5C6FE51ADBEF D9082BB5
	static void CLEAR_OVERRIDE_WEATHER() { NativeInvoke::Invoke<scrVoid>(0x338D2E3477711050); } // 338D2E3477711050 7740EA4E
	static void _0xB8F87EAD7533B176(float p0) { NativeInvoke::Invoke<scrVoid>(0xB8F87EAD7533B176, p0); } // B8F87EAD7533B176 625181DC
	static void _0xC3EAD29AB273ECE8(float p0) { NativeInvoke::Invoke<scrVoid>(0xC3EAD29AB273ECE8, p0); } // C3EAD29AB273ECE8 BEBBFDC8
	static void _0xA7A1127490312C36(float p0) { NativeInvoke::Invoke<scrVoid>(0xA7A1127490312C36, p0); } // A7A1127490312C36 6926AB03
	static void _0x31727907B2C43C55(float p0) { NativeInvoke::Invoke<scrVoid>(0x31727907B2C43C55, p0); } // 31727907B2C43C55 D447439D
	static void _0x405591EC8FD9096D(float p0) { NativeInvoke::Invoke<scrVoid>(0x405591EC8FD9096D, p0); } // 405591EC8FD9096D 584E9C59
	static void _0xF751B16FB32ABC1D(float p0) { NativeInvoke::Invoke<scrVoid>(0xF751B16FB32ABC1D, p0); } // F751B16FB32ABC1D 5656D578
	static void _0xB3E6360DDE733E82(float p0) { NativeInvoke::Invoke<scrVoid>(0xB3E6360DDE733E82, p0); } // B3E6360DDE733E82 0DE40C28
	static void _0x7C9C0B1EEB1F9072(float p0) { NativeInvoke::Invoke<scrVoid>(0x7C9C0B1EEB1F9072, p0); } // 7C9C0B1EEB1F9072 98C9138B
	static void _0x6216B116083A7CB4(float p0) { NativeInvoke::Invoke<scrVoid>(0x6216B116083A7CB4, p0); } // 6216B116083A7CB4 FB1A9CDE
	static void _0x9F5E6BB6B34540DA(float p0) { NativeInvoke::Invoke<scrVoid>(0x9F5E6BB6B34540DA, p0); } // 9F5E6BB6B34540DA 1C0CAE89
	static void _0xB9854DFDE0D833D6(float p0) { NativeInvoke::Invoke<scrVoid>(0xB9854DFDE0D833D6, p0); } // B9854DFDE0D833D6 4671AC2E
	static void _0xC54A08C85AE4D410(float p0) { NativeInvoke::Invoke<scrVoid>(0xC54A08C85AE4D410, p0); } // C54A08C85AE4D410 DA02F415
	static void _0xA8434F1DFF41D6E7(float p0) { NativeInvoke::Invoke<scrVoid>(0xA8434F1DFF41D6E7, p0); } // A8434F1DFF41D6E7 5F3DDEC0
	static void _0xC3C221ADDDE31A11(float p0) { NativeInvoke::Invoke<scrVoid>(0xC3C221ADDDE31A11, p0); } // C3C221ADDDE31A11 63A89684
	static void SET_WIND(float p0) { NativeInvoke::Invoke<scrVoid>(0xAC3A74E8384A9919, p0); } // AC3A74E8384A9919 C6294698
	static void SET_WIND_SPEED(float p0) { NativeInvoke::Invoke<scrVoid>(0xEE09ECEDBABE47FC, p0); } // EE09ECEDBABE47FC 45705F94
	static float GET_WIND_SPEED() { return NativeInvoke::Invoke<float>(0xA8CF1CC0AFCD3F12); } // A8CF1CC0AFCD3F12 098F0F3C
	static void SET_WIND_DIRECTION(float p0) { NativeInvoke::Invoke<scrVoid>(0xEB0F4468467B4528, p0); } // EB0F4468467B4528 381AEEE9
	static scrVector3 GET_WIND_DIRECTION() { return NativeInvoke::Invoke<scrVector3>(0x1F400FEF721170DA); } // 1F400FEF721170DA 89499A0D
	static void _0x643E26EA6E024D92(float p0) { NativeInvoke::Invoke<scrVoid>(0x643E26EA6E024D92, p0); } // 643E26EA6E024D92
	static float GET_RAIN_LEVEL() { return NativeInvoke::Invoke<float>(0x96695E368AD855F3); } // 96695E368AD855F3 C9F67F28
	static float GET_SNOW_LEVEL() { return NativeInvoke::Invoke<float>(0xC5868A966E5BE3AE); } // C5868A966E5BE3AE 1B09184F
	static void _0xF6062E089251C898() { NativeInvoke::Invoke<scrVoid>(0xF6062E089251C898); } // F6062E089251C898 DF38165E
	static void _0x11B56FBBF7224868(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x11B56FBBF7224868, p0); } // 11B56FBBF7224868 8727A4C5
	static void _0xFC4842A34657BFCB(scrAny *p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xFC4842A34657BFCB, p0, p1); } // FC4842A34657BFCB ED88FC61
	static void _0xA74802FB8D0B7814(scrAny *p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xA74802FB8D0B7814, p0, p1); } // A74802FB8D0B7814 C9FA6E07
	static void _0x957E790EA1727B64() { NativeInvoke::Invoke<scrVoid>(0x957E790EA1727B64); } // 957E790EA1727B64 2D7787BC
	static scrAny GET_GAME_TIMER() { return NativeInvoke::Invoke<scrAny>(0x9CD27B0045628463); } // 9CD27B0045628463 A4EA0691
	static float GET_FRAME_TIME() { return NativeInvoke::Invoke<float>(0x15C40837039FFAF7); } // 15C40837039FFAF7 96374262
	static scrAny GET_FRAME_COUNT() { return NativeInvoke::Invoke<scrAny>(0xFC8202EFC642E6F2); } // FC8202EFC642E6F2 B477A015
	static float GET_RANDOM_FLOAT_IN_RANGE(float p0, float p1) { return NativeInvoke::Invoke<float>(0x313CE5879CEB6FCD, p0, p1); } // 313CE5879CEB6FCD 0562C4D0
	static scrAny GET_RANDOM_INT_IN_RANGE(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xD53343AA4FB7DD28, p0, p1); } // D53343AA4FB7DD28 4051115B
	static BOOL GET_GROUND_Z_FOR_3D_COORD(float p0, float p1, float p2, float *p3) { return NativeInvoke::Invoke<BOOL>(0xC906A7DAB05C8D2B, p0, p1, p2, p3); } // C906A7DAB05C8D2B A1BFD5E0
	static scrAny _0x8BDC7BFC57A81E76(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { return NativeInvoke::Invoke<scrAny>(0x8BDC7BFC57A81E76, p0, p1, p2, p3, p4); } // 8BDC7BFC57A81E76 64D91CED
	static float ASIN(float p0) { return NativeInvoke::Invoke<float>(0xC843060B5765DCE7, p0); } // C843060B5765DCE7 998E5CAD
	static float ACOS(float p0) { return NativeInvoke::Invoke<float>(0x1D08B970013C34B6, p0); } // 1D08B970013C34B6 F4038776
	static float TAN(float p0) { return NativeInvoke::Invoke<float>(0x632106CC96E82E91, p0); } // 632106CC96E82E91 D320CE5E
	static float ATAN(float p0) { return NativeInvoke::Invoke<float>(0xA9D1795CD5043663, p0); } // A9D1795CD5043663 7A03CC8E
	static float ATAN2(float p0, float p1) { return NativeInvoke::Invoke<float>(0x8927CBF9D22261A4, p0, p1); } // 8927CBF9D22261A4 2508AC81
	static float GET_DISTANCE_BETWEEN_COORDS(float p0, float p1, float p2, float p3, float p4, float p5, BOOL p6) { return NativeInvoke::Invoke<float>(0xF1B760881820C952, p0, p1, p2, p3, p4, p5, p6); } // F1B760881820C952 F698765E
	static float GET_ANGLE_BETWEEN_2D_VECTORS(float p0, float p1, float p2, float p3) { return NativeInvoke::Invoke<float>(0x186FC4BE848E1C92, p0, p1, p2, p3); } // 186FC4BE848E1C92 DBF75E58
	static float GET_HEADING_FROM_VECTOR_2D(float p0, float p1) { return NativeInvoke::Invoke<float>(0x2FFB6B224F4B2926, p0, p1); } // 2FFB6B224F4B2926 D209D52B
	static float _0x7F8F6405F4777AF6(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, BOOL p9) { return NativeInvoke::Invoke<float>(0x7F8F6405F4777AF6, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 7F8F6405F4777AF6 89459F0A
	static scrVector3 _0x21C235BC64831E5A(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9) { return NativeInvoke::Invoke<scrVector3>(0x21C235BC64831E5A, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 21C235BC64831E5A CAECF37E
	static BOOL _0xF56DFB7B61BE7276(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, scrAny *p12) { return NativeInvoke::Invoke<BOOL>(0xF56DFB7B61BE7276, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // F56DFB7B61BE7276 C6CC812C
	static void SET_BIT(scrAny *p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x933D6A9EEC1BACD0, p0, p1); } // 933D6A9EEC1BACD0 4EFE7E6B
	static void CLEAR_BIT(scrAny *p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xE80492A9AC099A93, p0, p1); } // E80492A9AC099A93 8BC9E618
	static scrAny GET_HASH_KEY(char *p0) { return NativeInvoke::Invoke<scrAny>(0xD24D37CC275948CC, p0); } // D24D37CC275948CC 98EFF6F1
	static void _0xF2F6A2FA49278625(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, scrAny *p9, scrAny *p10, scrAny *p11, scrAny *p12) { NativeInvoke::Invoke<scrVoid>(0xF2F6A2FA49278625, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // F2F6A2FA49278625 87B92190
	static BOOL IS_AREA_OCCUPIED(float p0, float p1, float p2, float p3, float p4, float p5, BOOL p6, BOOL p7, BOOL p8, BOOL p9, BOOL p10, scrAny p11, BOOL p12) { return NativeInvoke::Invoke<BOOL>(0xA61B4DF533DCB56E, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // A61B4DF533DCB56E C013972F
	static BOOL IS_POSITION_OCCUPIED(float p0, float p1, float p2, float p3, BOOL p4, BOOL p5, BOOL p6, BOOL p7, BOOL p8, scrAny p9, BOOL p10) { return NativeInvoke::Invoke<BOOL>(0xADCDE75E1C60F32D, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // ADCDE75E1C60F32D 452E8D9E
	static BOOL IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(float p0, float p1, float p2, float p3, float p4, float p5, scrAny p6) { return NativeInvoke::Invoke<BOOL>(0xE54E209C35FFA18D, p0, p1, p2, p3, p4, p5, p6); } // E54E209C35FFA18D C161558D
	static void CLEAR_AREA(float p0, float p1, float p2, float p3, BOOL p4, BOOL p5, BOOL p6, BOOL p7) { NativeInvoke::Invoke<scrVoid>(0xA56F01F3765B93A0, p0, p1, p2, p3, p4, p5, p6, p7); } // A56F01F3765B93A0 854E9AB8
	static void _0x957838AAF91BD12D(float p0, float p1, float p2, float p3, BOOL p4, BOOL p5, BOOL p6, BOOL p7) { NativeInvoke::Invoke<scrVoid>(0x957838AAF91BD12D, p0, p1, p2, p3, p4, p5, p6, p7); } // 957838AAF91BD12D 20E4FFD9
	static void CLEAR_AREA_OF_VEHICLES(float p0, float p1, float p2, float p3, BOOL p4, BOOL p5, BOOL p6, BOOL p7, BOOL p8) { NativeInvoke::Invoke<scrVoid>(0x01C7B9B38428AEB6, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 01C7B9B38428AEB6 63320F3C
	static void CLEAR_ANGLED_AREA_OF_VEHICLES(float p0, float p1, float p2, float p3, float p4, float p5, float p6, BOOL p7, BOOL p8, BOOL p9, BOOL p10, BOOL p11) { NativeInvoke::Invoke<scrVoid>(0x11DB3500F042A8AA, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 11DB3500F042A8AA F11A3018
	static void CLEAR_AREA_OF_OBJECTS(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0xDD9B9B385AAC7F5B, p0, p1, p2, p3, p4); } // DD9B9B385AAC7F5B BB720FE7
	static void CLEAR_AREA_OF_PEDS(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0xBE31FD6CE464AC59, p0, p1, p2, p3, p4); } // BE31FD6CE464AC59 25BE7FA8
	static void CLEAR_AREA_OF_COPS(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x04F8FC8FCF58F88D, p0, p1, p2, p3, p4); } // 04F8FC8FCF58F88D 95C53824
	static void CLEAR_AREA_OF_PROJECTILES(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x0A1CB9094635D1A6, p0, p1, p2, p3, p4); } // 0A1CB9094635D1A6 18DB5434
	static void SET_SAVE_MENU_ACTIVE(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xC9BF75D28165FF77, p0); } // C9BF75D28165FF77 F5CCF164
	static scrAny _0x397BAA01068BAA96() { return NativeInvoke::Invoke<scrAny>(0x397BAA01068BAA96); } // 397BAA01068BAA96 39771F21
	static void SET_CREDITS_ACTIVE(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xB938B7E6D3C0620C, p0); } // B938B7E6D3C0620C EC2A0ECF
	static void _0xB51B9AB9EF81868C(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xB51B9AB9EF81868C, p0); } // B51B9AB9EF81868C 75B06B5A
	static scrAny _0x075F1D57402C93BA() { return NativeInvoke::Invoke<scrAny>(0x075F1D57402C93BA); } // 075F1D57402C93BA 2569C9A7
	static void TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x9DC711BC69C548DF, p0); } // 9DC711BC69C548DF 9F861FD4
	static void NETWORK_SET_SCRIPT_IS_SAFE_FOR_NETWORK_GAME() { NativeInvoke::Invoke<scrVoid>(0x9243BAC96D64C050); } // 9243BAC96D64C050 878486CE
	static scrAny ADD_HOSPITAL_RESTART(float p0, float p1, float p2, float p3, scrAny p4) { return NativeInvoke::Invoke<scrAny>(0x1F464EF988465A81, p0, p1, p2, p3, p4); } // 1F464EF988465A81 4F3E3104
	static void DISABLE_HOSPITAL_RESTART(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xC8535819C450EBA8, p0, p1); } // C8535819C450EBA8 09F49C72
	static scrAny ADD_POLICE_RESTART(float p0, float p1, float p2, float p3, scrAny p4) { return NativeInvoke::Invoke<scrAny>(0x452736765B31FC4B, p0, p1, p2, p3, p4); } // 452736765B31FC4B E96C29FE
	static void DISABLE_POLICE_RESTART(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x23285DED6EBD7EA3, p0, p1); } // 23285DED6EBD7EA3 0A280324
	static void _0x2C2B3493FBF51C71(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x2C2B3493FBF51C71, p0); } // 2C2B3493FBF51C71 296574AE
	static void IGNORE_NEXT_RESTART(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x21FFB63D8C615361, p0); } // 21FFB63D8C615361 DA13A4B6
	static void _0x4A18E01DF2C87B86(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x4A18E01DF2C87B86, p0); } // 4A18E01DF2C87B86 C9F6F0BC
	static void _0x1E0B4DC0D990A4E7(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x1E0B4DC0D990A4E7, p0); } // 1E0B4DC0D990A4E7 CB074B9D
	static void SET_FADE_IN_AFTER_DEATH_ARREST(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xDA66D2796BA33F12, p0); } // DA66D2796BA33F12 ACDE6985
	static void SET_FADE_IN_AFTER_LOAD(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xF3D78F59DFE18D79, p0); } // F3D78F59DFE18D79 6E00EB0B
	static scrAny REGISTER_SAVE_HOUSE(float p0, float p1, float p2, float p3, scrAny *p4, scrAny p5, scrAny p6) { return NativeInvoke::Invoke<scrAny>(0xC0714D0A7EEECA54, p0, p1, p2, p3, p4, p5, p6); } // C0714D0A7EEECA54 39C1849A
	static void SET_SAVE_HOUSE(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x4F548CABEAE553BC, p0, p1, p2); } // 4F548CABEAE553BC C3240BB4
	static scrAny OVERRIDE_SAVE_HOUSE(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7) { return NativeInvoke::Invoke<scrAny>(0x1162EA8AE9D24EEA, p0, p1, p2, p3, p4, p5, p6, p7); } // 1162EA8AE9D24EEA 47436C12
	static scrAny _0xA4A0065E39C9F25C(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0xA4A0065E39C9F25C, p0, p1, p2, p3); } // A4A0065E39C9F25C C4D71AB4
	static void DO_AUTO_SAVE() { NativeInvoke::Invoke<scrVoid>(0x50EEAAD86232EE55); } // 50EEAAD86232EE55 54C44B1A
	static BOOL _0x6E04F06094C87047() { return NativeInvoke::Invoke<BOOL>(0x6E04F06094C87047); } // 6E04F06094C87047 A8546914
	static BOOL IS_AUTO_SAVE_IN_PROGRESS() { return NativeInvoke::Invoke<BOOL>(0x69240733738C19A0); } // 69240733738C19A0 36F75399
	static scrAny _0x2107A3773771186D() { return NativeInvoke::Invoke<scrAny>(0x2107A3773771186D); } // 2107A3773771186D 78350773
	static void _0x06462A961E94B67C() { NativeInvoke::Invoke<scrVoid>(0x06462A961E94B67C); } // 06462A961E94B67C 5A45B11A
	static void BEGIN_REPLAY_STATS(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xE0E500246FF73D66, p0, p1); } // E0E500246FF73D66 17F4F44D
	static void _0x69FE6DC87BD2A5E9(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x69FE6DC87BD2A5E9, p0); } // 69FE6DC87BD2A5E9 81216EE0
	static void END_REPLAY_STATS() { NativeInvoke::Invoke<scrVoid>(0xA23E821FBDF8A5F2); } // A23E821FBDF8A5F2 CB570185
	static scrAny _0xD642319C54AADEB6() { return NativeInvoke::Invoke<scrAny>(0xD642319C54AADEB6); } // D642319C54AADEB6 C58250F1
	static scrAny _0x5B1F2E327B6B6FE1() { return NativeInvoke::Invoke<scrAny>(0x5B1F2E327B6B6FE1); } // 5B1F2E327B6B6FE1 50C39926
	static scrAny _0x2B626A0150E4D449() { return NativeInvoke::Invoke<scrAny>(0x2B626A0150E4D449); } // 2B626A0150E4D449 710E5D1E
	static scrAny _0xDC9274A7EF6B2867() { return NativeInvoke::Invoke<scrAny>(0xDC9274A7EF6B2867); } // DC9274A7EF6B2867 C7BD1AF0
	static scrAny _0x8098C8D6597AAE18(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x8098C8D6597AAE18, p0); } // 8098C8D6597AAE18 22BE2423
	static void CLEAR_REPLAY_STATS() { NativeInvoke::Invoke<scrVoid>(0x1B1AB132A16FDA55); } // 1B1AB132A16FDA55 C47DFF02
	static BOOL _0x72DE52178C291CB5() { return NativeInvoke::Invoke<BOOL>(0x72DE52178C291CB5); } // 72DE52178C291CB5 F62B3C48
	static BOOL _0x44A0BDC559B35F6E() { return NativeInvoke::Invoke<BOOL>(0x44A0BDC559B35F6E); } // 44A0BDC559B35F6E 3589452B
	static scrAny _0x2B5E102E4A42F2BF() { return NativeInvoke::Invoke<scrAny>(0x2B5E102E4A42F2BF); } // 2B5E102E4A42F2BF 144AAF22
	static BOOL IS_MEMORY_CARD_IN_USE() { return NativeInvoke::Invoke<BOOL>(0x8A75CE2956274ADD); } // 8A75CE2956274ADD 40CE4DFD
	static void SHOOT_SINGLE_BULLET_BETWEEN_COORDS(float p0, float p1, float p2, float p3, float p4, float p5, scrAny p6, BOOL p7, scrAny p8, scrAny p9, BOOL p10, BOOL p11, float p12) { NativeInvoke::Invoke<scrVoid>(0x867654CBC7606F2C, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 867654CBC7606F2C CB7415AC
	static void _0xE3A7742E0B7A2F8B(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9, scrAny p10, scrAny p11, scrAny p12, scrAny p13) { NativeInvoke::Invoke<scrVoid>(0xE3A7742E0B7A2F8B, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } // E3A7742E0B7A2F8B 52ACCB7B
	static void _0xBFE5756E7407064A(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9, scrAny p10, scrAny p11, scrAny p12, scrAny p13, scrAny p14, scrAny p15) { NativeInvoke::Invoke<scrVoid>(0xBFE5756E7407064A, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15); } // BFE5756E7407064A
	static void GET_MODEL_DIMENSIONS(scrAny p0, scrVector3 *p1, scrVector3 *p2) { NativeInvoke::Invoke<scrVoid>(0x03E8D3D5F549087A, p0, p1, p2); } // 03E8D3D5F549087A 91ABB8E0
	static void SET_FAKE_WANTED_LEVEL(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x1454F2448DE30163, p0); } // 1454F2448DE30163 85B1C9FA
	static scrAny _0x4C9296CBCD1B971E() { return NativeInvoke::Invoke<scrAny>(0x4C9296CBCD1B971E); } // 4C9296CBCD1B971E 0022A430
	static scrAny IS_BIT_SET(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xA921AA820C25702F, p0, p1); } // A921AA820C25702F 902E26AC
	static void USING_MISSION_CREATOR(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xF14878FC50BEC6EE, p0); } // F14878FC50BEC6EE 20AB0B6B
	static void _0xDEA36202FC3382DF(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xDEA36202FC3382DF, p0); } // DEA36202FC3382DF 082BA6F2
	static void SET_MINIGAME_IN_PROGRESS(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x19E00D7322C6F85B, p0); } // 19E00D7322C6F85B 348B9046
	static scrAny IS_MINIGAME_IN_PROGRESS() { return NativeInvoke::Invoke<scrAny>(0x2B4A15E44DE0F478); } // 2B4A15E44DE0F478 53A95E13
	static BOOL IS_THIS_A_MINIGAME_SCRIPT() { return NativeInvoke::Invoke<BOOL>(0x7B30F65D7B710098); } // 7B30F65D7B710098 7605EF6F
	static scrAny IS_SNIPER_INVERTED() { return NativeInvoke::Invoke<scrAny>(0x61A23B7EDA9BDA24); } // 61A23B7EDA9BDA24 5C3BF51B
	static BOOL _0xD3D15555431AB793() { return NativeInvoke::Invoke<BOOL>(0xD3D15555431AB793); } // D3D15555431AB793 BAF17315
	static scrAny GET_PROFILE_SETTING(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xC488FF2356EA7791, p0); } // C488FF2356EA7791 D374BEBC
	static scrAny ARE_STRINGS_EQUAL(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x0C515FAB3FF9EA92, p0, p1); } // 0C515FAB3FF9EA92 877C0BC5
	static scrAny COMPARE_STRINGS(scrAny *p0, scrAny *p1, BOOL p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0x1E34710ECD4AB0EB, p0, p1, p2, p3); } // 1E34710ECD4AB0EB FE25A58F
	static scrAny ABSI(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xF0D31AD191A74F87, p0); } // F0D31AD191A74F87 B44677C5
	static float ABSF(float p0) { return NativeInvoke::Invoke<float>(0x73D57CFFDD12C355, p0); } // 73D57CFFDD12C355 AF6F6E0B
	static BOOL IS_SNIPER_BULLET_IN_AREA(float p0, float p1, float p2, float p3, float p4, float p5) { return NativeInvoke::Invoke<BOOL>(0xFEFCF11B01287125, p0, p1, p2, p3, p4, p5); } // FEFCF11B01287125 0483715C
	static BOOL IS_PROJECTILE_IN_AREA(float p0, float p1, float p2, float p3, float p4, float p5, BOOL p6) { return NativeInvoke::Invoke<BOOL>(0x5270A8FBC098C3F8, p0, p1, p2, p3, p4, p5, p6); } // 5270A8FBC098C3F8 78E1A557
	static BOOL IS_PROJECTILE_TYPE_IN_AREA(float p0, float p1, float p2, float p3, float p4, float p5, scrAny p6, BOOL p7) { return NativeInvoke::Invoke<BOOL>(0x2E0DC353342C4A6D, p0, p1, p2, p3, p4, p5, p6, p7); } // 2E0DC353342C4A6D 2B73BCF6
	static BOOL IS_PROJECTILE_TYPE_IN_ANGLED_AREA(float p0, float p1, float p2, float p3, float p4, float p5, float p6, scrAny p7, BOOL p8) { return NativeInvoke::Invoke<BOOL>(0xF0BC12401061DEA0, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // F0BC12401061DEA0 D1AE2681
	static BOOL _0x34318593248C8FB2(float p0, float p1, float p2, scrAny p3, float p4, BOOL p5) { return NativeInvoke::Invoke<BOOL>(0x34318593248C8FB2, p0, p1, p2, p3, p4, p5); } // 34318593248C8FB2 BE81F1E2
	static scrAny _0x8D7A43EC6A5FEA45(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8) { return NativeInvoke::Invoke<scrAny>(0x8D7A43EC6A5FEA45, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 8D7A43EC6A5FEA45 1A40454B
	static scrAny _0xDFB4138EEFED7B81(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { return NativeInvoke::Invoke<scrAny>(0xDFB4138EEFED7B81, p0, p1, p2, p3, p4); } // DFB4138EEFED7B81 6BDE5CE4
	static scrAny _0x82FDE6A57EE4EE44(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { return NativeInvoke::Invoke<scrAny>(0x82FDE6A57EE4EE44, p0, p1, p2, p3, p4, p5); } // 82FDE6A57EE4EE44 507BC6F7
	static BOOL IS_BULLET_IN_ANGLED_AREA(float p0, float p1, float p2, float p3, float p4, float p5, float p6, BOOL p7) { return NativeInvoke::Invoke<BOOL>(0x1A8B5F3C01E2B477, p0, p1, p2, p3, p4, p5, p6, p7); } // 1A8B5F3C01E2B477 E2DB58F7
	static BOOL IS_BULLET_IN_AREA(float p0, float p1, float p2, float p3, BOOL p4) { return NativeInvoke::Invoke<BOOL>(0x3F2023999AD51C1F, p0, p1, p2, p3, p4); } // 3F2023999AD51C1F B54F46CA
	static BOOL IS_BULLET_IN_BOX(float p0, float p1, float p2, float p3, float p4, float p5, BOOL p6) { return NativeInvoke::Invoke<BOOL>(0xDE0F6D7450D37351, p0, p1, p2, p3, p4, p5, p6); } // DE0F6D7450D37351 AB73ED26
	static BOOL HAS_BULLET_IMPACTED_IN_AREA(float p0, float p1, float p2, float p3, BOOL p4, BOOL p5) { return NativeInvoke::Invoke<BOOL>(0x9870ACFB89A90995, p0, p1, p2, p3, p4, p5); } // 9870ACFB89A90995 902BC7D9
	static BOOL HAS_BULLET_IMPACTED_IN_BOX(float p0, float p1, float p2, float p3, float p4, float p5, BOOL p6, BOOL p7) { return NativeInvoke::Invoke<BOOL>(0xDC8C5D7CFEAB8394, p0, p1, p2, p3, p4, p5, p6, p7); } // DC8C5D7CFEAB8394 2C2618CC
	static scrAny IS_ORBIS_VERSION() { return NativeInvoke::Invoke<scrAny>(0xA72BC0B675B1519E); } // A72BC0B675B1519E 40282018
	static scrAny IS_DURANGO_VERSION() { return NativeInvoke::Invoke<scrAny>(0x4D982ADB1978442D); } // 4D982ADB1978442D 46FB06A5
	static scrAny IS_XBOX360_VERSION() { return NativeInvoke::Invoke<scrAny>(0xF6201B4DAF662A9D); } // F6201B4DAF662A9D 24005CC8
	static scrAny IS_PS3_VERSION() { return NativeInvoke::Invoke<scrAny>(0xCCA1072C29D096C2); } // CCA1072C29D096C2 4C0D5303
	static scrAny IS_PC_VERSION() { return NativeInvoke::Invoke<scrAny>(0x48AF36444B965238); } // 48AF36444B965238 4D5D9EE3
	static scrAny IS_AUSSIE_VERSION() { return NativeInvoke::Invoke<scrAny>(0x9F1935CA1F724008); } // 9F1935CA1F724008 944BA1DC
	static BOOL IS_STRING_NULL(BOOL p0) { return NativeInvoke::Invoke<BOOL>(0xF22B6C47C6EAB066, p0); } // F22B6C47C6EAB066 8E71E00F
	static scrAny IS_STRING_NULL_OR_EMPTY(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xCA042B6957743895, p0); } // CA042B6957743895 42E9F2CA
	static BOOL STRING_TO_INT(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x5A5F40FE637EB584, p0, p1); } // 5A5F40FE637EB584 590A8160
	static void SET_BITS_IN_RANGE(scrAny *p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x8EF07E15701D61ED, p0, p1, p2, p3); } // 8EF07E15701D61ED 32094719
	static scrAny GET_BITS_IN_RANGE(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0x53158863FCC0893A, p0, p1, p2); } // 53158863FCC0893A CA03A1E5
	static scrAny ADD_STUNT_JUMP(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12, float p13, float p14, scrAny p15, scrAny p16) { return NativeInvoke::Invoke<scrAny>(0x1A992DA297A4630C, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16); } // 1A992DA297A4630C B630E5FF
	static scrAny ADD_STUNT_JUMP_ANGLED(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12, float p13, float p14, float p15, float p16, scrAny p17, scrAny p18) { return NativeInvoke::Invoke<scrAny>(0xBBE5D803A5360CBF, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18); } // BBE5D803A5360CBF B9B7E777
	static void DELETE_STUNT_JUMP(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xDC518000E39DAE1F, p0); } // DC518000E39DAE1F 840CB5DA
	static void ENABLE_STUNT_JUMP_SET(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xE369A5783B866016, p0); } // E369A5783B866016 9D1E7785
	static void DISABLE_STUNT_JUMP_SET(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA5272EBEDD4747F6, p0); } // A5272EBEDD4747F6 644C9FA4
	static void _0xD79185689F8FD5DF(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xD79185689F8FD5DF, p0); } // D79185689F8FD5DF 3C806A2D
	static BOOL IS_STUNT_JUMP_IN_PROGRESS() { return NativeInvoke::Invoke<BOOL>(0x7A3F19700A4D0525); } // 7A3F19700A4D0525 F477D0B1
	static BOOL _0x2272B0A1343129F4() { return NativeInvoke::Invoke<BOOL>(0x2272B0A1343129F4); } // 2272B0A1343129F4 021636EE
	static scrAny _0x996DD1E1E02F1008() { return NativeInvoke::Invoke<scrAny>(0x996DD1E1E02F1008); } // 996DD1E1E02F1008 006F9BA2
	static void CANCEL_STUNT_JUMP() { NativeInvoke::Invoke<scrVoid>(0xE6B7B0ACD4E4B75E); } // E6B7B0ACD4E4B75E F43D9821
	static void SET_GAME_PAUSED(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x577D1284D6873711, p0); } // 577D1284D6873711 8230FF6C
	static void SET_THIS_SCRIPT_CAN_BE_PAUSED(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xAA391C728106F7AF, p0); } // AA391C728106F7AF A0C3CE29
	static void SET_THIS_SCRIPT_CAN_REMOVE_BLIPS_CREATED_BY_ANY_SCRIPT(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xB98236CAAECEF897, p0); } // B98236CAAECEF897 D06F1720
	static BOOL _0x071E2A839DE82D90(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x071E2A839DE82D90, p0, p1); } // 071E2A839DE82D90 FF6191E1
	static void _0x9BAE5AD2508DF078(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x9BAE5AD2508DF078, p0); } // 9BAE5AD2508DF078 721B2492
	static void _0xC5F0A8EBD3F361CE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xC5F0A8EBD3F361CE, p0); } // C5F0A8EBD3F361CE E202879D
	static scrAny IS_FRONTEND_FADING() { return NativeInvoke::Invoke<scrAny>(0x7EA2B6AF97ECA6ED); } // 7EA2B6AF97ECA6ED 8FF6232C
	static void POPULATE_NOW() { NativeInvoke::Invoke<scrVoid>(0x7472BB270D7B4F3E); } // 7472BB270D7B4F3E 72C20700
	static scrAny GET_INDEX_OF_CURRENT_LEVEL() { return NativeInvoke::Invoke<scrAny>(0xCBAD6729F7B1F4FC); } // CBAD6729F7B1F4FC 6F203C6E
	static void SET_GRAVITY_LEVEL(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x740E14FAD5842351, p0); } // 740E14FAD5842351 2D833F4A
	static void START_SAVE_DATA(scrAny *p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xA9575F812C6A7997, p0, p1, p2); } // A9575F812C6A7997 881A694D
	static void STOP_SAVE_DATA() { NativeInvoke::Invoke<scrVoid>(0x74E20C9145FB66FD); } // 74E20C9145FB66FD 3B1C07C8
	static scrAny _0xA09F896CE912481F(BOOL p0) { return NativeInvoke::Invoke<scrAny>(0xA09F896CE912481F, p0); } // A09F896CE912481F 9EF0BC64
	static void REGISTER_INT_TO_SAVE(scrAny *p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x34C9EE5986258415, p0, p1); } // 34C9EE5986258415 B930956F
	static void _0x10C2FA78D0E128A1(scrAny *p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x10C2FA78D0E128A1, p0, p1); } // 10C2FA78D0E128A1 9B38374A
	static void REGISTER_FLOAT_TO_SAVE(scrAny *p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x7CAEC29ECB5DFEBB, p0, p1); } // 7CAEC29ECB5DFEBB DB06F7AD
	static void REGISTER_BOOL_TO_SAVE(scrAny *p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xC8F4131414C835A1, p0, p1); } // C8F4131414C835A1 5417E0E0
	static void REGISTER_TEXT_LABEL_TO_SAVE(scrAny *p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xEDB1232C5BEAE62F, p0, p1); } // EDB1232C5BEAE62F 284352C4
	static void _0x6F7794F28C6B2535(scrAny *p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x6F7794F28C6B2535, p0, p1); } // 6F7794F28C6B2535 E2089749
	static void _0x48F069265A0E4BEC(scrAny *p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x48F069265A0E4BEC, p0, p1); } // 48F069265A0E4BEC F91B8C33
	static void _0x8269816F6CFD40F8(scrAny *p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x8269816F6CFD40F8, p0, p1); } // 8269816F6CFD40F8 74E8FAD9
	static void _0xFAA457EF263E8763(scrAny *p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xFAA457EF263E8763, p0, p1); } // FAA457EF263E8763 6B4335DD
	static void _0xBF737600CDDBEADD(scrAny *p0, scrAny p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0xBF737600CDDBEADD, p0, p1, p2); } // BF737600CDDBEADD FB45728E
	static void STOP_SAVE_STRUCT() { NativeInvoke::Invoke<scrVoid>(0xEB1774DF12BB9F12); } // EB1774DF12BB9F12 C2624A28
	static void _0x60FE567DF1B1AF9D(scrAny *p0, scrAny p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0x60FE567DF1B1AF9D, p0, p1, p2); } // 60FE567DF1B1AF9D 893A342C
	static void STOP_SAVE_ARRAY() { NativeInvoke::Invoke<scrVoid>(0x04456F95153C6BE4); } // 04456F95153C6BE4 0CAD8217
	static void _0xDC0F817884CDD856(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xDC0F817884CDD856, p0, p1); } // DC0F817884CDD856 0B710A51
	static void _0x9B2BD3773123EA2F(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x9B2BD3773123EA2F, p0, p1); } // 9B2BD3773123EA2F E0F0684F
	static scrAny _0xEB4A0C2D56441717(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xEB4A0C2D56441717, p0); } // EB4A0C2D56441717 3CE5BF6B
	static BOOL CREATE_INCIDENT(scrAny p0, float p1, float p2, float p3, scrAny p4, float p5, scrAny *p6) { return NativeInvoke::Invoke<BOOL>(0x3F892CAF67444AE7, p0, p1, p2, p3, p4, p5, p6); } // 3F892CAF67444AE7 FC5FF7B3
	static BOOL CREATE_INCIDENT_WITH_ENTITY(scrAny p0, scrAny p1, scrAny p2, float p3, scrAny *p4) { return NativeInvoke::Invoke<BOOL>(0x05983472F0494E60, p0, p1, p2, p3, p4); } // 05983472F0494E60 BBC35B03
	static void DELETE_INCIDENT(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x556C1AA270D5A207, p0); } // 556C1AA270D5A207 212BD0DC
	static BOOL IS_INCIDENT_VALID(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xC8BC6461E629BEAA, p0); } // C8BC6461E629BEAA 31FD0BA4
	static void _0xB08B85D860E7BA3C(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xB08B85D860E7BA3C, p0, p1, p2); } // B08B85D860E7BA3C 0242D88E
	static void _0xD261BA3E7E998072(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xD261BA3E7E998072, p0, p1); } // D261BA3E7E998072 1F38102E
	static scrAny FIND_SPAWN_POINT_IN_DIRECTION(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7) { return NativeInvoke::Invoke<scrAny>(0x6874E2190B0C1972, p0, p1, p2, p3, p4, p5, p6, p7); } // 6874E2190B0C1972 71AEFD77
	static scrAny _0x67F6413D3220E18D(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8) { return NativeInvoke::Invoke<scrAny>(0x67F6413D3220E18D, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 67F6413D3220E18D 42BF09B3
	static void _0xB129E447A2EDA4BF(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xB129E447A2EDA4BF, p0, p1); } // B129E447A2EDA4BF FBDBE374
	static void ENABLE_TENNIS_MODE(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x28A04B411933F8A6, p0, p1, p2); } // 28A04B411933F8A6 0BD3F9EC
	static BOOL IS_TENNIS_MODE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x5D5479D115290C3F, p0); } // 5D5479D115290C3F 04A947BA
	static void _0xE266ED23311F24D4(scrAny p0, scrAny *p1, scrAny *p2, float p3, float p4, BOOL p5) { NativeInvoke::Invoke<scrVoid>(0xE266ED23311F24D4, p0, p1, p2, p3, p4, p5); } // E266ED23311F24D4 C20A7D2B
	static BOOL _0x17DF68D720AA77F8(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x17DF68D720AA77F8, p0); } // 17DF68D720AA77F8 8501E727
	static BOOL _0x19BFED045C647C49(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x19BFED045C647C49, p0); } // 19BFED045C647C49 1A332D2D
	static BOOL _0xE95B0C7D5BA3B96B(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xE95B0C7D5BA3B96B, p0); } // E95B0C7D5BA3B96B
	static void _0x8FA9C42FC5D7C64B(scrAny p0, scrAny p1, float p2, float p3, float p4, BOOL p5) { NativeInvoke::Invoke<scrVoid>(0x8FA9C42FC5D7C64B, p0, p1, p2, p3, p4, p5); } // 8FA9C42FC5D7C64B 0C8865DF
	static void _0x54F157E0336A3822(scrAny p0, scrAny *p1, float p2) { NativeInvoke::Invoke<scrVoid>(0x54F157E0336A3822, p0, p1, p2); } // 54F157E0336A3822 49F977A9
	static void _0xD10F442036302D50(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xD10F442036302D50, p0, p1, p2); } // D10F442036302D50 6F009E33
	static void RESET_DISPATCH_IDEAL_SPAWN_DISTANCE() { NativeInvoke::Invoke<scrVoid>(0x77A84429DD9F0A15); } // 77A84429DD9F0A15 DA65ECAA
	static void SET_DISPATCH_IDEAL_SPAWN_DISTANCE(float p0) { NativeInvoke::Invoke<scrVoid>(0x6FE601A64180D423, p0); } // 6FE601A64180D423 6283BE32
	static void SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x44F7CBC1BEB3327D, p0, p1); } // 44F7CBC1BEB3327D ABADB709
	static void SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS_MULTIPLIER(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x48838ED9937A15D1, p0, p1); } // 48838ED9937A15D1 1C996BCD
	static scrAny _0x918C7B2D2FF3928B(float p0, float p1, float p2, float p3, float p4, float p5, float p6) { return NativeInvoke::Invoke<scrAny>(0x918C7B2D2FF3928B, p0, p1, p2, p3, p4, p5, p6); } // 918C7B2D2FF3928B F557BAF9
	static void REMOVE_DISPATCH_SPAWN_BLOCKING_AREA(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x264AC28B01B353A5, p0); } // 264AC28B01B353A5 A8D2FB92
	static void RESET_DISPATCH_SPAWN_BLOCKING_AREAS() { NativeInvoke::Invoke<scrVoid>(0xAC7BFD5C1D83EA75); } // AC7BFD5C1D83EA75 9A17F835
	static void _0xD9F692D349249528() { NativeInvoke::Invoke<scrVoid>(0xD9F692D349249528); } // D9F692D349249528 E0C9307E
	static void _0xE532EC1A63231B4F(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xE532EC1A63231B4F, p0, p1); } // E532EC1A63231B4F A0D8C749
	static void _0xB8721407EE9C3FF6(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xB8721407EE9C3FF6, p0, p1, p2); } // B8721407EE9C3FF6 24A4E0B2
	static void _0xB3CD58CCA6CDA852() { NativeInvoke::Invoke<scrVoid>(0xB3CD58CCA6CDA852); } // B3CD58CCA6CDA852 66C3C59C
	static void _0x2587A48BC88DFADF(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x2587A48BC88DFADF, p0); } // 2587A48BC88DFADF D9660339
	static void _0xCA78CFA0366592FE(scrAny p0, scrAny *p1, scrAny *p2, scrAny *p3, scrAny *p4, scrAny *p5, scrAny *p6, scrAny *p7, scrAny *p8, scrAny *p9, scrAny *p10, scrAny p11) { NativeInvoke::Invoke<scrVoid>(0xCA78CFA0366592FE, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // CA78CFA0366592FE D2688412
	static void DISPLAY_ONSCREEN_KEYBOARD(scrAny p0, scrAny *p1, scrAny *p2, scrAny *p3, scrAny *p4, scrAny *p5, scrAny *p6, scrAny p7) { NativeInvoke::Invoke<scrVoid>(0x00DC833F2568DBF6, p0, p1, p2, p3, p4, p5, p6, p7); } // 00DC833F2568DBF6 AD99F2CE
	static scrAny UPDATE_ONSCREEN_KEYBOARD() { return NativeInvoke::Invoke<scrAny>(0x0CF2B696BBF945AE); } // 0CF2B696BBF945AE 23D0A1CE
	static scrAny GET_ONSCREEN_KEYBOARD_RESULT() { return NativeInvoke::Invoke<scrAny>(0x8362B09B91893647); } // 8362B09B91893647 44828FB3
	static void _0x3ED1438C1F5C6612(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x3ED1438C1F5C6612, p0); } // 3ED1438C1F5C6612 3301EA47
	static void _0xA6A12939F16D85BE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xA6A12939F16D85BE, p0, p1); } // A6A12939F16D85BE 42B484ED
	static void _0x1EAE0A6E978894A2(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x1EAE0A6E978894A2, p0, p1); } // 1EAE0A6E978894A2 8F60366E
	static void SET_EXPLOSIVE_AMMO_THIS_FRAME(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA66C71C98D5F2CFB, p0); } // A66C71C98D5F2CFB 2EAFA1D1
	static void SET_FIRE_AMMO_THIS_FRAME(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x11879CDD803D30F4, p0); } // 11879CDD803D30F4 7C18FC8A
	static void SET_EXPLOSIVE_MELEE_THIS_FRAME(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xFF1BED81BFDC0FE0, p0); } // FF1BED81BFDC0FE0 96663D56
	static void SET_SUPER_JUMP_THIS_FRAME(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x57FFF03E423A4C0B, p0); } // 57FFF03E423A4C0B 86745EF3
	static scrAny _0x6FDDF453C0C756EC() { return NativeInvoke::Invoke<scrAny>(0x6FDDF453C0C756EC); } // 6FDDF453C0C756EC C3C10FCC
	static void _0xFB00CA71DA386228() { NativeInvoke::Invoke<scrVoid>(0xFB00CA71DA386228); } // FB00CA71DA386228 054EC103
	static scrAny _0x5AA3BEFA29F03AD4() { return NativeInvoke::Invoke<scrAny>(0x5AA3BEFA29F03AD4); } // 5AA3BEFA29F03AD4 46B5A15C
	static void _0xC0AA53F866B3134D() { NativeInvoke::Invoke<scrVoid>(0xC0AA53F866B3134D); } // C0AA53F866B3134D 5D209F25
	static void _0x0A60017F841A54F2(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x0A60017F841A54F2, p0, p1, p2, p3); } // 0A60017F841A54F2 2D33F15A
	static void _0x1FF6BF9A63E5757F() { NativeInvoke::Invoke<scrVoid>(0x1FF6BF9A63E5757F); } // 1FF6BF9A63E5757F DF99925C
	static void _0x1BB299305C3E8C13(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x1BB299305C3E8C13, p0, p1, p2, p3); } // 1BB299305C3E8C13 A27F4472
	static BOOL _0x8EF5573A1F801A5C(scrAny p0, scrAny *p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0x8EF5573A1F801A5C, p0, p1, p2); } // 8EF5573A1F801A5C 07FF553F
	static BOOL _0x684A41975F077262() { return NativeInvoke::Invoke<BOOL>(0x684A41975F077262); } // 684A41975F077262
	static scrAny _0xABB2FA71C83A1B72() { return NativeInvoke::Invoke<scrAny>(0xABB2FA71C83A1B72); } // ABB2FA71C83A1B72
	static void _0x4EBB7E87AA0DBED4(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x4EBB7E87AA0DBED4, p0); } // 4EBB7E87AA0DBED4
	static scrAny _0x9689123E3F213AA5() { return NativeInvoke::Invoke<scrAny>(0x9689123E3F213AA5); } // 9689123E3F213AA5
	static void _0x23227DF0B2115469() { NativeInvoke::Invoke<scrVoid>(0x23227DF0B2115469); } // 23227DF0B2115469
}

namespace AUDIO
{
	static void PLAY_PED_RINGTONE(scrAny *p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xF9E56683CA8E11A5, p0, p1, p2); } // F9E56683CA8E11A5 1D530E47
	static BOOL IS_PED_RINGTONE_PLAYING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x1E8E5E20937E3137, p0); } // 1E8E5E20937E3137 FE576EE4
	static void STOP_PED_RINGTONE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x6C5AE23EFA885092, p0); } // 6C5AE23EFA885092 FEEA107C
	static BOOL IS_MOBILE_PHONE_CALL_ONGOING() { return NativeInvoke::Invoke<BOOL>(0x7497D2CE2C30D24C); } // 7497D2CE2C30D24C 4ED1400A
	static BOOL _0xC8B1B2425604CDD0() { return NativeInvoke::Invoke<BOOL>(0xC8B1B2425604CDD0); } // C8B1B2425604CDD0 16FB88B5
	static void CREATE_NEW_SCRIPTED_CONVERSATION() { NativeInvoke::Invoke<scrVoid>(0xD2C91A0B572AAE56); } // D2C91A0B572AAE56 B2BC25F8
	static void ADD_LINE_TO_CONVERSATION(scrAny p0, scrAny *p1, scrAny *p2, scrAny p3, scrAny p4, BOOL p5, BOOL p6, BOOL p7, BOOL p8, scrAny p9, BOOL p10, BOOL p11, BOOL p12) { NativeInvoke::Invoke<scrVoid>(0xC5EF963405593646, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // C5EF963405593646 96CD0513
	static void ADD_PED_TO_CONVERSATION(scrAny p0, scrAny p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0x95D9F4BC443956E7, p0, p1, p2); } // 95D9F4BC443956E7 F8D5EB86
	static void _0x33E3C6C6F2F0B506(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x33E3C6C6F2F0B506, p0, p1, p2, p3); } // 33E3C6C6F2F0B506 73C6F979
	static void _0x892B6AB8F33606F5(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x892B6AB8F33606F5, p0, p1); } // 892B6AB8F33606F5 88203DDA
	static void SET_MICROPHONE_POSITION(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9) { NativeInvoke::Invoke<scrVoid>(0xB6AE90EDDE95C762, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // B6AE90EDDE95C762 AD7BB191
	static void _0x0B568201DD99F0EB(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x0B568201DD99F0EB, p0); } // 0B568201DD99F0EB 1193ED6E
	static void _0x61631F5DF50D1C34(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x61631F5DF50D1C34, p0); } // 61631F5DF50D1C34
	static void START_SCRIPT_PHONE_CONVERSATION(BOOL p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x252E5F915EABB675, p0, p1); } // 252E5F915EABB675 38E42D07
	static void PRELOAD_SCRIPT_PHONE_CONVERSATION(BOOL p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x6004BCB0E226AAEA, p0, p1); } // 6004BCB0E226AAEA 9ACB213A
	static void START_SCRIPT_CONVERSATION(BOOL p0, BOOL p1, BOOL p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x6B17C62C9635D2DC, p0, p1, p2, p3); } // 6B17C62C9635D2DC E5DE7D9D
	static void PRELOAD_SCRIPT_CONVERSATION(BOOL p0, BOOL p1, BOOL p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x3B3CAD6166916D87, p0, p1, p2, p3); } // 3B3CAD6166916D87 DDF5C579
	static void START_PRELOADED_CONVERSATION() { NativeInvoke::Invoke<scrVoid>(0x23641AFE870AF385); } // 23641AFE870AF385 A170261B
	static BOOL _0xE73364DB90778FFA() { return NativeInvoke::Invoke<BOOL>(0xE73364DB90778FFA); } // E73364DB90778FFA 336F3D35
	static BOOL IS_SCRIPTED_CONVERSATION_ONGOING() { return NativeInvoke::Invoke<BOOL>(0x16754C556D2EDE3D); } // 16754C556D2EDE3D CB8FD96F
	static BOOL IS_SCRIPTED_CONVERSATION_LOADED() { return NativeInvoke::Invoke<BOOL>(0xDF0D54BE7A776737); } // DF0D54BE7A776737 E1870EA9
	static scrAny GET_CURRENT_SCRIPTED_CONVERSATION_LINE() { return NativeInvoke::Invoke<scrAny>(0x480357EE890C295A); } // 480357EE890C295A 9620E41F
	static void PAUSE_SCRIPTED_CONVERSATION(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x8530AD776CD72B12, p0); } // 8530AD776CD72B12 E2C9C6F8
	static void RESTART_SCRIPTED_CONVERSATION() { NativeInvoke::Invoke<scrVoid>(0x9AEB285D1818C9AC); } // 9AEB285D1818C9AC 6CB24B56
	static scrAny STOP_SCRIPTED_CONVERSATION(BOOL p0) { return NativeInvoke::Invoke<scrAny>(0xD79DEEFB53455EBA, p0); } // D79DEEFB53455EBA AB77DA7D
	static void SKIP_TO_NEXT_SCRIPTED_CONVERSATION_LINE() { NativeInvoke::Invoke<scrVoid>(0x9663FE6B7A61EB00); } // 9663FE6B7A61EB00 85C98304
	static void INTERRUPT_CONVERSATION(scrAny p0, scrAny *p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0xA018A12E5C5C2FA6, p0, p1, p2); } // A018A12E5C5C2FA6 F3A67AF3
	static scrAny _0xAA19F5572C38B564(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0xAA19F5572C38B564, p0); } // AA19F5572C38B564 B58B8FF3
	static void _0xB542DE8C3D1CB210(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xB542DE8C3D1CB210, p0); } // B542DE8C3D1CB210 789D8C6C
	static void REGISTER_SCRIPT_WITH_AUDIO(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xC6ED9D5092438D91, p0); } // C6ED9D5092438D91 A6203643
	static void UNREGISTER_SCRIPT_WITH_AUDIO() { NativeInvoke::Invoke<scrVoid>(0xA8638BE228D4751A); } // A8638BE228D4751A 66728EFE
	static BOOL REQUEST_MISSION_AUDIO_BANK(scrAny *p0, BOOL p1) { return NativeInvoke::Invoke<BOOL>(0x7345BDD95E62E0F2, p0, p1); } // 7345BDD95E62E0F2 916E37CA
	static BOOL REQUEST_AMBIENT_AUDIO_BANK(scrAny *p0, BOOL p1) { return NativeInvoke::Invoke<BOOL>(0xFE02FFBED8CA9D99, p0, p1); } // FE02FFBED8CA9D99 23C88BC7
	static BOOL REQUEST_SCRIPT_AUDIO_BANK(scrAny *p0, BOOL p1) { return NativeInvoke::Invoke<BOOL>(0x2F844A8B08D76685, p0, p1); } // 2F844A8B08D76685 21322887
	static scrAny HINT_AMBIENT_AUDIO_BANK(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x8F8C0E370AE62F5C, p0, p1); } // 8F8C0E370AE62F5C F1850DDC
	static scrAny HINT_SCRIPT_AUDIO_BANK(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xFB380A29641EC31A, p0, p1); } // FB380A29641EC31A 41FA0E51
	static void RELEASE_MISSION_AUDIO_BANK() { NativeInvoke::Invoke<scrVoid>(0x0EC92A1BF0857187); } // 0EC92A1BF0857187 8E8824C7
	static void RELEASE_AMBIENT_AUDIO_BANK() { NativeInvoke::Invoke<scrVoid>(0x65475A218FFAA93D); } // 65475A218FFAA93D 8C938784
	static void RELEASE_NAMED_SCRIPT_AUDIO_BANK(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x77ED170667F50170, p0); } // 77ED170667F50170 16707ABC
	static void RELEASE_SCRIPT_AUDIO_BANK() { NativeInvoke::Invoke<scrVoid>(0x7A2D8AD0A9EB9C3F); } // 7A2D8AD0A9EB9C3F 22F865E5
	static void _0x19AF7ED9B9D23058() { NativeInvoke::Invoke<scrVoid>(0x19AF7ED9B9D23058); } // 19AF7ED9B9D23058 A58BBF4F
	static scrAny GET_SOUND_ID() { return NativeInvoke::Invoke<scrAny>(0x430386FE9BF80B45); } // 430386FE9BF80B45 6AE0AD56
	static void RELEASE_SOUND_ID(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x353FC880830B88FA, p0); } // 353FC880830B88FA 9C080899
	static void PLAY_SOUND(scrAny p0, scrAny *p1, scrAny *p2, BOOL p3, scrAny p4, BOOL p5) { NativeInvoke::Invoke<scrVoid>(0x7FF4944CC209192D, p0, p1, p2, p3, p4, p5); } // 7FF4944CC209192D B6E1917F
	static void PLAY_SOUND_FRONTEND(scrAny p0, char *p1, char *p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x67C540AA08E4A6F5, p0, p1, p2, p3); } // 67C540AA08E4A6F5 2E458F74
	static void _0xCADA5A0D0702381E(scrAny *p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xCADA5A0D0702381E, p0, p1); } // CADA5A0D0702381E C70E6CFA
	static void PLAY_SOUND_FROM_ENTITY(scrAny p0, scrAny *p1, scrAny p2, scrAny *p3, BOOL p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0xE65F427EB70AB1ED, p0, p1, p2, p3, p4, p5); } // E65F427EB70AB1ED 95AE00F8
	static void PLAY_SOUND_FROM_COORD(scrAny p0, scrAny *p1, float p2, float p3, float p4, scrAny *p5, BOOL p6, scrAny p7, BOOL p8) { NativeInvoke::Invoke<scrVoid>(0x8D8686B622B88120, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 8D8686B622B88120 CAD3E2D5
	static void STOP_SOUND(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA3B0C41BA5CC0BB5, p0); } // A3B0C41BA5CC0BB5 CD7F4030
	static scrAny GET_NETWORK_ID_FROM_SOUND_ID(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x2DE3F0A134FFBC0D, p0); } // 2DE3F0A134FFBC0D 2576F610
	static scrAny _0x75262FD12D0A1C84(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x75262FD12D0A1C84, p0); } // 75262FD12D0A1C84 D064D4DC
	static void SET_VARIABLE_ON_SOUND(scrAny p0, scrAny *p1, float p2) { NativeInvoke::Invoke<scrVoid>(0xAD6B3148A78AE9B6, p0, p1, p2); } // AD6B3148A78AE9B6 606EE5FA
	static void SET_VARIABLE_ON_STREAM(scrAny *p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x2F9D3834AEB9EF79, p0, p1); } // 2F9D3834AEB9EF79 F67BB44C
	static void OVERRIDE_UNDERWATER_STREAM(scrAny *p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xF2A9CDABCEA04BD6, p0, p1); } // F2A9CDABCEA04BD6 9A083B7E
	static void _0x733ADF241531E5C2(scrAny *p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x733ADF241531E5C2, p0, p1); } // 733ADF241531E5C2 62D026BE
	static BOOL HAS_SOUND_FINISHED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xFCBDCE714A7C88E5, p0); } // FCBDCE714A7C88E5 E85AEC2E
	static void _0x8E04FEDD28D42462(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x8E04FEDD28D42462, p0, p1, p2); } // 8E04FEDD28D42462 5C57B85D
	static void _0xC6941B4A3A8FBBB9(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xC6941B4A3A8FBBB9, p0, p1, p2); } // C6941B4A3A8FBBB9 444180DB
	static void _0x3523634255FC3318(scrAny p0, scrAny *p1, scrAny *p2, scrAny *p3, BOOL p4) { NativeInvoke::Invoke<scrVoid>(0x3523634255FC3318, p0, p1, p2, p3, p4); } // 3523634255FC3318 8386AE28
	static void _0xED640017ED337E45(scrAny *p0, scrAny *p1, float p2, float p3, float p4, scrAny *p5) { NativeInvoke::Invoke<scrVoid>(0xED640017ED337E45, p0, p1, p2, p3, p4, p5); } // ED640017ED337E45 A1A1402E
	static void OVERRIDE_TREVOR_RAGE(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x13AD665062541A7E, p0); } // 13AD665062541A7E 05B9B5CF
	static void RESET_TREVOR_RAGE() { NativeInvoke::Invoke<scrVoid>(0xE78503B10C4314E0); } // E78503B10C4314E0 E80CF0D4
	static void SET_PLAYER_ANGRY(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xEA241BB04110F091, p0, p1); } // EA241BB04110F091 782CA58D
	static void PLAY_PAIN(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xBC9AE166038A5CEC, p0, p1, p2); } // BC9AE166038A5CEC 874BD6CB
	static void _0xD01005D2BA2EB778(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xD01005D2BA2EB778, p0); } // D01005D2BA2EB778 59A3A17D
	static void _0xDDC635D5B3262C56(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xDDC635D5B3262C56, p0); } // DDC635D5B3262C56 0E387BFE
	static void SET_AMBIENT_VOICE_NAME(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x6C8065A3B780185B, p0, p1); } // 6C8065A3B780185B BD2EA1A1
	static void STOP_CURRENT_PLAYING_AMBIENT_SPEECH(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xB8BEC0CA6F0EDB0F, p0); } // B8BEC0CA6F0EDB0F BB8E64BF
	static BOOL IS_AMBIENT_SPEECH_PLAYING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x9072C8B49907BFAD, p0); } // 9072C8B49907BFAD 1972E8AA
	static BOOL IS_SCRIPTED_SPEECH_PLAYING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xCC9AA18DCC7084F4, p0); } // CC9AA18DCC7084F4 2C653904
	static BOOL IS_ANY_SPEECH_PLAYING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x729072355FA39EC9, p0); } // 729072355FA39EC9 2B74A6D6
	static BOOL _0x49B99BF3FDA89A7A(scrAny p0, scrAny *p1, BOOL p2) { return NativeInvoke::Invoke<BOOL>(0x49B99BF3FDA89A7A, p0, p1, p2); } // 49B99BF3FDA89A7A 8BD5F11E
	static BOOL IS_PED_IN_CURRENT_CONVERSATION(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x049E937F18F4020C, p0); } // 049E937F18F4020C 7B2F0743
	static void SET_PED_IS_DRUNK(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x95D2D383D5396B8A, p0, p1); } // 95D2D383D5396B8A D2EA77A3
	static void _0xEE066C7006C49C0A(scrAny p0, scrAny p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0xEE066C7006C49C0A, p0, p1, p2); } // EE066C7006C49C0A 498849F3
	static BOOL _0xC265DF9FB44A9FBD(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xC265DF9FB44A9FBD, p0); } // C265DF9FB44A9FBD 0CBAF2EF
	static void SET_ANIMAL_MOOD(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xCC97B29285B1DC3B, p0, p1); } // CC97B29285B1DC3B 3EA7C6CB
	static scrAny IS_MOBILE_PHONE_RADIO_ACTIVE() { return NativeInvoke::Invoke<scrAny>(0xB35CE999E8EF317E); } // B35CE999E8EF317E 6E502A5B
	static void SET_MOBILE_PHONE_RADIO_STATE(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xBF286C554784F3DF, p0); } // BF286C554784F3DF E1E0ED34
	static scrAny GET_PLAYER_RADIO_STATION_INDEX() { return NativeInvoke::Invoke<scrAny>(0xE8AF77C4C06ADC93); } // E8AF77C4C06ADC93 1C4946AC
	static scrAny GET_PLAYER_RADIO_STATION_NAME() { return NativeInvoke::Invoke<scrAny>(0xF6D733C32076AD03); } // F6D733C32076AD03 D909C107
	static scrAny GET_RADIO_STATION_NAME(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xB28ECA15046CA8B9, p0); } // B28ECA15046CA8B9 3DF493BC
	static scrAny GET_PLAYER_RADIO_STATION_GENRE() { return NativeInvoke::Invoke<scrAny>(0xA571991A7FE6CCEB); } // A571991A7FE6CCEB 872CF0EA
	static scrAny IS_RADIO_RETUNING() { return NativeInvoke::Invoke<scrAny>(0xA151A7394A214E65); } // A151A7394A214E65 CF29097B
	static void _0xFF266D1D0EB1195D() { NativeInvoke::Invoke<scrVoid>(0xFF266D1D0EB1195D); } // FF266D1D0EB1195D 53DB6994
	static void _0xDD6BCF9E94425DF9() { NativeInvoke::Invoke<scrVoid>(0xDD6BCF9E94425DF9); } // DD6BCF9E94425DF9 D70ECC80
	static void SET_RADIO_TO_STATION_NAME(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xC69EDA28699D5107, p0); } // C69EDA28699D5107 7B36E35E
	static void SET_VEH_RADIO_STATION(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x1B9C0099CB942AC6, p0, p1); } // 1B9C0099CB942AC6 E391F55F
	static void _0xC1805D05E6D4FE10(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xC1805D05E6D4FE10, p0); } // C1805D05E6D4FE10 7ABB89D2
	static void SET_EMITTER_RADIO_STATION(scrAny *p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xACF57305B12AF907, p0, p1); } // ACF57305B12AF907 87431585
	static void SET_STATIC_EMITTER_ENABLED(scrAny *p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x399D2D3B33F1B8EB, p0, p1); } // 399D2D3B33F1B8EB 91F72E92
	static void SET_RADIO_TO_STATION_INDEX(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA619B168B8A8570F, p0); } // A619B168B8A8570F 1D82766D
	static void SET_FRONTEND_RADIO_ACTIVE(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xF7F26C6E9CC9EBB8, p0); } // F7F26C6E9CC9EBB8 B1172075
	static void UNLOCK_MISSION_NEWS_STORY(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xB165AB7C248B2DC1, p0); } // B165AB7C248B2DC1 CCD9ABE4
	static scrAny GET_NUMBER_OF_PASSENGER_VOICE_VARIATIONS(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x66E49BF55B4B1874, p0); } // 66E49BF55B4B1874 27305D37
	static scrAny GET_AUDIBLE_MUSIC_TRACK_TEXT_ID() { return NativeInvoke::Invoke<scrAny>(0x50B196FC9ED6545B); } // 50B196FC9ED6545B A2B88CA7
	static void PLAY_END_CREDITS_MUSIC(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xCD536C4D33DCC900, p0); } // CD536C4D33DCC900 8E88B3CC
	static void SKIP_RADIO_FORWARD() { NativeInvoke::Invoke<scrVoid>(0x6DDBBDD98E2E9C25); } // 6DDBBDD98E2E9C25 10D36630
	static void FREEZE_RADIO_STATION(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x344F393B027E38C3, p0); } // 344F393B027E38C3 286BF543
	static void UNFREEZE_RADIO_STATION(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xFC00454CF60B91DD, p0); } // FC00454CF60B91DD 4D46202C
	static void SET_RADIO_AUTO_UNFREEZE(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xC1AA9F53CE982990, p0); } // C1AA9F53CE982990 A40196BF
	static void SET_INITIAL_PLAYER_STATION(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x88795F13FACDA88D, p0); } // 88795F13FACDA88D 9B069233
	static void SET_USER_RADIO_CONTROL_ENABLED(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x19F21E63AE6EAE4E, p0); } // 19F21E63AE6EAE4E 52E054CE
	static void SET_RADIO_TRACK(scrAny *p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xB39786F201FEE30B, p0, p1); } // B39786F201FEE30B 76E96212
	static void SET_VEHICLE_RADIO_LOUD(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xBB6F1CAEC68B0BCE, p0, p1); } // BB6F1CAEC68B0BCE 8D9EDD99
	static BOOL _0x032A116663A4D5AC(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x032A116663A4D5AC, p0); } // 032A116663A4D5AC CBA99F4A
	static void SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x1098355A16064BB3, p0); } // 1098355A16064BB3 990085F0
	static BOOL _0x109697E2FFBAC8A1() { return NativeInvoke::Invoke<BOOL>(0x109697E2FFBAC8A1); } // 109697E2FFBAC8A1 46B0C696
	static BOOL _0x5F43D83FD6738741() { return NativeInvoke::Invoke<BOOL>(0x5F43D83FD6738741); } // 5F43D83FD6738741 2A3E5E8B
	static void SET_VEHICLE_RADIO_ENABLED(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x3B988190C0AA6C0B, p0, p1); } // 3B988190C0AA6C0B 6F812CAB
	static void _0x4E404A9361F75BB2(scrAny *p0, scrAny *p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x4E404A9361F75BB2, p0, p1, p2); } // 4E404A9361F75BB2 128C3873
	static void _0x1654F24A88A8E3FE(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x1654F24A88A8E3FE, p0); } // 1654F24A88A8E3FE 1D766976
	static scrAny _0xF1620ECB50E01DE7() { return NativeInvoke::Invoke<scrAny>(0xF1620ECB50E01DE7); } // F1620ECB50E01DE7 CC91FCF5
	static scrAny FIND_RADIO_STATION_INDEX(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x8D67489793FF428B, p0); } // 8D67489793FF428B ECA1512F
	static void _0x774BD811F656A122(scrAny *p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x774BD811F656A122, p0, p1); } // 774BD811F656A122 B1FF7137
	static void _0x2C96CDB04FCA358E(float p0) { NativeInvoke::Invoke<scrVoid>(0x2C96CDB04FCA358E, p0); } // 2C96CDB04FCA358E C8B514E2
	static void _0x031ACB6ABA18C729(scrAny *p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x031ACB6ABA18C729, p0, p1); } // 031ACB6ABA18C729 BE998184
	static void _0xF3365489E0DD50F9(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xF3365489E0DD50F9, p0, p1); } // F3365489E0DD50F9 8AFC488D
	static void SET_AMBIENT_ZONE_STATE(scrAny *p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xBDA07E5950085E46, p0, p1, p2); } // BDA07E5950085E46 2849CAC9
	static void CLEAR_AMBIENT_ZONE_STATE(scrAny *p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x218DD44AAAC964FF, p0, p1); } // 218DD44AAAC964FF CDFF3C82
	static void SET_AMBIENT_ZONE_LIST_STATE(scrAny *p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x9748FA4DE50CCE3E, p0, p1, p2); } // 9748FA4DE50CCE3E BF80B412
	static void CLEAR_AMBIENT_ZONE_LIST_STATE(scrAny *p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x120C48C614909FA4, p0, p1); } // 120C48C614909FA4 38B9B8D4
	static void SET_AMBIENT_ZONE_STATE_PERSISTENT(scrAny *p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x1D6650420CEC9D3B, p0, p1, p2); } // 1D6650420CEC9D3B C1FFB672
	static void SET_AMBIENT_ZONE_LIST_STATE_PERSISTENT(scrAny *p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xF3638DAE8C4045E1, p0, p1, p2); } // F3638DAE8C4045E1 5F5A2605
	static BOOL IS_AMBIENT_ZONE_ENABLED(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x01E2817A479A7F9B, p0); } // 01E2817A479A7F9B BFABD872
	static void SET_CUTSCENE_AUDIO_OVERRIDE(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x3B4BF5F0859204D9, p0); } // 3B4BF5F0859204D9 CE1332B7
	static void GET_PLAYER_HEADSET_SOUND_ALTERNATE(scrAny *p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xBCC29F935ED07688, p0, p1); } // BCC29F935ED07688 D63CF33A
	static scrAny PLAY_POLICE_REPORT(scrAny *p0, float p1) { return NativeInvoke::Invoke<scrAny>(0xDFEBD56D9BD1EB16, p0, p1); } // DFEBD56D9BD1EB16 3F277B62
	static void BLIP_SIREN(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x1B9025BDA76822B6, p0); } // 1B9025BDA76822B6 C0EB6924
	static void OVERRIDE_VEH_HORN(scrAny p0, BOOL p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x3CDC1E622CCE0356, p0, p1, p2); } // 3CDC1E622CCE0356 2ACAB783
	static BOOL IS_HORN_ACTIVE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x9D6BFC12B05C6121, p0); } // 9D6BFC12B05C6121 20E2BDD0
	static void SET_AGGRESSIVE_HORNS(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x395BF71085D1B1D9, p0); } // 395BF71085D1B1D9 01D6EABE
	static void _0x02E93C796ABD3A97(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x02E93C796ABD3A97, p0); } // 02E93C796ABD3A97 3C395AEE
	static void _0x58BB377BEC7CD5F4(BOOL p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x58BB377BEC7CD5F4, p0, p1); } // 58BB377BEC7CD5F4 8CE63FA1
	static BOOL IS_STREAM_PLAYING() { return NativeInvoke::Invoke<BOOL>(0xD11FA52EB849D978); } // D11FA52EB849D978 F1F51A14
	static scrAny GET_STREAM_PLAY_TIME() { return NativeInvoke::Invoke<scrAny>(0x4E72BBDBCA58A3DB); } // 4E72BBDBCA58A3DB B4F0AD56
	static BOOL LOAD_STREAM(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x1F1F957154EC51DF, p0, p1); } // 1F1F957154EC51DF 0D89599D
	static BOOL LOAD_STREAM_WITH_START_OFFSET(scrAny *p0, scrAny p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0x59C16B79F53B3712, p0, p1, p2); } // 59C16B79F53B3712 E5B5745C
	static void _0x89049DD63C08B5D1(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x89049DD63C08B5D1, p0); } // 89049DD63C08B5D1 A1D7FABE
	static void PLAY_STREAM_FROM_VEHICLE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xB70374A758007DFA, p0); } // B70374A758007DFA F8E4BDA2
	static void PLAY_STREAM_FROM_OBJECT(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xEBAA9B64D76356FD, p0); } // EBAA9B64D76356FD C5266BF7
	static void PLAY_STREAM_FRONTEND() { NativeInvoke::Invoke<scrVoid>(0x58FCE43488F9F5F4); } // 58FCE43488F9F5F4 2C2A16BC
	static void SPECIAL_FRONTEND_EQUAL(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x21442F412E8DE56B, p0, p1, p2); } // 21442F412E8DE56B 6FE5D865
	static void STOP_STREAM() { NativeInvoke::Invoke<scrVoid>(0xA4718A1419D18151); } // A4718A1419D18151 D1E364DE
	static void STOP_PED_SPEAKING(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x9D64D7405520E3D3, p0, p1); } // 9D64D7405520E3D3 FF92B49D
	static void DISABLE_PED_PAIN_AUDIO(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xA9A41C1E940FB0E8, p0, p1); } // A9A41C1E940FB0E8 3B8E2D5F
	static BOOL IS_AMBIENT_SPEECH_DISABLED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x932C2D096A2C3FFF, p0); } // 932C2D096A2C3FFF 109D1F89
	static void SET_SIREN_WITH_NO_DRIVER(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x1FEF0683B96EBCF2, p0, p1); } // 1FEF0683B96EBCF2 77182D58
	static void _0x9C11908013EA4715(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x9C11908013EA4715, p0); } // 9C11908013EA4715 DE8BA3CD
	static void SET_HORN_ENABLED(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x76D683C108594D0E, p0, p1); } // 76D683C108594D0E 6EB92D05
	static void SET_AUDIO_VEHICLE_PRIORITY(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xE5564483E407F914, p0, p1); } // E5564483E407F914 271A9766
	static void _0x9D3AF56E94C9AE98(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x9D3AF56E94C9AE98, p0, p1); } // 9D3AF56E94C9AE98 2F0A16D1
	static void USE_SIREN_AS_HORN(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xFA932DE350266EF8, p0, p1); } // FA932DE350266EF8 C6BC16F3
	static void _0x4F0C413926060B38(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x4F0C413926060B38, p0, p1); } // 4F0C413926060B38 33B0B007
	static void _0xF1F8157B8C3F171C(scrAny p0, scrAny *p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0xF1F8157B8C3F171C, p0, p1, p2); } // F1F8157B8C3F171C 1C0C5E4C
	static void _0xD2DCCD8E16E20997(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xD2DCCD8E16E20997, p0); } // D2DCCD8E16E20997
	static BOOL _0x5DB8010EE71FDEF2(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x5DB8010EE71FDEF2, p0); } // 5DB8010EE71FDEF2 6E660D3F
	static void _0x59E7B488451F4D3A(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x59E7B488451F4D3A, p0, p1); } // 59E7B488451F4D3A 23BE6432
	static void _0x01BB4D577D38BD9E(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x01BB4D577D38BD9E, p0, p1); } // 01BB4D577D38BD9E E81FAC68
	static void _0x1C073274E065C6D2(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x1C073274E065C6D2, p0, p1); } // 1C073274E065C6D2 9365E042
	static void _0x2BE4BC731D039D5A(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x2BE4BC731D039D5A, p0, p1); } // 2BE4BC731D039D5A 2A60A90E
	static void SET_VEHICLE_BOOST_ACTIVE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x4A04DE7CAB2739A1, p0, p1); } // 4A04DE7CAB2739A1 072F15F2
	static void _0x6FDDAD856E36988A(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x6FDDAD856E36988A, p0, p1); } // 6FDDAD856E36988A 934BE749
	static void _0x06C0023BED16DD6B(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x06C0023BED16DD6B, p0, p1); } // 06C0023BED16DD6B E61110A2
	static void PLAY_VEHICLE_DOOR_OPEN_SOUND(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x3A539D52857EA82D, p0, p1); } // 3A539D52857EA82D 84930330
	static void PLAY_VEHICLE_DOOR_CLOSE_SOUND(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x62A456AA4769EF34, p0, p1); } // 62A456AA4769EF34 BA2CF407
	static void _0xC15907D667F7CFB2(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xC15907D667F7CFB2, p0, p1); } // C15907D667F7CFB2 563B635D
	static BOOL IS_GAME_IN_CONTROL_OF_MUSIC() { return NativeInvoke::Invoke<BOOL>(0x6D28DC1671E334FD); } // 6D28DC1671E334FD 7643170D
	static void SET_GPS_ACTIVE(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x3BD3F52BA9B1E4E8, p0); } // 3BD3F52BA9B1E4E8 0FC3379A
	static void PLAY_MISSION_COMPLETE_AUDIO(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xB138AAB8A70D3C69, p0); } // B138AAB8A70D3C69 3033EA1D
	static BOOL IS_MISSION_COMPLETE_PLAYING() { return NativeInvoke::Invoke<BOOL>(0x19A30C23F5827F8A); } // 19A30C23F5827F8A 939982A1
	static scrAny _0x6F259F82D873B8B8() { return NativeInvoke::Invoke<scrAny>(0x6F259F82D873B8B8); } // 6F259F82D873B8B8 CBE09AEC
	static void _0xF154B8D1775B2DEC(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xF154B8D1775B2DEC, p0); } // F154B8D1775B2DEC D2858D8A
	static BOOL START_AUDIO_SCENE(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x013A80FC08F6E4F2, p0); } // 013A80FC08F6E4F2 E48D757B
	static void STOP_AUDIO_SCENE(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xDFE8422B3B94E688, p0); } // DFE8422B3B94E688 A08D8C58
	static void STOP_AUDIO_SCENES() { NativeInvoke::Invoke<scrVoid>(0xBAC7FC81A75EC1A1); } // BAC7FC81A75EC1A1 F6C7342A
	static BOOL IS_AUDIO_SCENE_ACTIVE(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xB65B60556E2A9225, p0); } // B65B60556E2A9225 ACBED05C
	static void SET_AUDIO_SCENE_VARIABLE(scrAny *p0, scrAny *p1, float p2) { NativeInvoke::Invoke<scrVoid>(0xEF21A9EF089A2668, p0, p1, p2); } // EF21A9EF089A2668 19BB3CE8
	static void _0xA5F377B175A699C5(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA5F377B175A699C5, p0); } // A5F377B175A699C5 E812925D
	static void _0x153973AB99FE8980(scrAny p0, scrAny *p1, float p2) { NativeInvoke::Invoke<scrVoid>(0x153973AB99FE8980, p0, p1, p2); } // 153973AB99FE8980 2BC93264
	static void _0x18EB48CFC41F2EA0(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x18EB48CFC41F2EA0, p0, p1); } // 18EB48CFC41F2EA0 308ED0EC
	static BOOL AUDIO_IS_SCRIPTED_MUSIC_PLAYING() { return NativeInvoke::Invoke<BOOL>(0x845FFC3A4FEEFA3E); } // 845FFC3A4FEEFA3E 86E995D1
	static BOOL PREPARE_MUSIC_EVENT(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x1E5185B72EF5158A, p0); } // 1E5185B72EF5158A 534A5C1C
	static BOOL CANCEL_MUSIC_EVENT(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x5B17A90291133DA5, p0); } // 5B17A90291133DA5 89FF942D
	static BOOL TRIGGER_MUSIC_EVENT(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x706D57B0F50DA710, p0); } // 706D57B0F50DA710 B6094948
	static BOOL _0xA097AB275061FB21() { return NativeInvoke::Invoke<BOOL>(0xA097AB275061FB21); } // A097AB275061FB21 2705C4D5
	static scrAny GET_MUSIC_PLAYTIME() { return NativeInvoke::Invoke<scrAny>(0xE7A0D23DC414507B); } // E7A0D23DC414507B D633C809
	static void _0xFBE20329593DEC9D(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0xFBE20329593DEC9D, p0, p1, p2, p3); } // FBE20329593DEC9D 53FC3FEC
	static void _0xB32209EFFDC04913() { NativeInvoke::Invoke<scrVoid>(0xB32209EFFDC04913); } // B32209EFFDC04913 E6B033BF
	static void _0x70B8EC8FC108A634(BOOL p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x70B8EC8FC108A634, p0, p1); } // 70B8EC8FC108A634 95050CAD
	static void _0x149AEE66F0CB3A99(float p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x149AEE66F0CB3A99, p0, p1); } // 149AEE66F0CB3A99 E64F97A0
	static void _0x062D5EAD4DA2FA6A() { NativeInvoke::Invoke<scrVoid>(0x062D5EAD4DA2FA6A); } // 062D5EAD4DA2FA6A D87AF337
	static BOOL PREPARE_ALARM(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x9D74AE343DB65533, p0); } // 9D74AE343DB65533 084932E8
	static void START_ALARM(scrAny *p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x0355EF116C4C97B2, p0, p1); } // 0355EF116C4C97B2 703F524B
	static void STOP_ALARM(scrAny *p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xA1CADDCD98415A41, p0, p1); } // A1CADDCD98415A41 F987BE8C
	static void STOP_ALL_ALARMS(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x2F794A877ADD4C92, p0); } // 2F794A877ADD4C92 C3CB9DC6
	static BOOL IS_ALARM_PLAYING(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x226435CB96CCFC8C, p0); } // 226435CB96CCFC8C 9D8E1D23
	static scrAny GET_VEHICLE_DEFAULT_HORN(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x02165D55000219AC, p0); } // 02165D55000219AC E84ABC19
	static scrAny _0xACB5DCCA1EC76840(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xACB5DCCA1EC76840, p0); } // ACB5DCCA1EC76840 FD4B5B3B
	static void RESET_PED_AUDIO_FLAGS(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xF54BB7B61036F335, p0); } // F54BB7B61036F335 DF720C86
	static void _0xD2CC78CD3D0B50F9(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xD2CC78CD3D0B50F9, p0, p1); } // D2CC78CD3D0B50F9 C307D531
	static void _0x75773E11BA459E90(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x75773E11BA459E90, p0, p1); } // 75773E11BA459E90
	static void _0x552369F549563AD5(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x552369F549563AD5, p0); } // 552369F549563AD5 13EB5861
	static void _0x43FA0DFC5DF87815(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x43FA0DFC5DF87815, p0, p1); } // 43FA0DFC5DF87815 7BED1872
	static void SET_AUDIO_FLAG(scrAny *p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xB9EFD5C25018725A, p0, p1); } // B9EFD5C25018725A 1C09C9E0
	static scrAny PREPARE_SYNCHRONIZED_AUDIO_EVENT(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xC7ABCACA4985A766, p0, p1); } // C7ABCACA4985A766 E1D91FD0
	static BOOL PREPARE_SYNCHRONIZED_AUDIO_EVENT_FOR_SCENE(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x029FE7CD1B7E2E75, p0, p1); } // 029FE7CD1B7E2E75 7652DD49
	static BOOL PLAY_SYNCHRONIZED_AUDIO_EVENT(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x8B2FD4560E55DD2D, p0); } // 8B2FD4560E55DD2D 507F3241
	static BOOL STOP_SYNCHRONIZED_AUDIO_EVENT(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x92D6A88E64A94430, p0); } // 92D6A88E64A94430 ADEED2B4
	static void _0xC8EDE9BDBCCBA6D4(scrAny *p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0xC8EDE9BDBCCBA6D4, p0, p1, p2, p3); } // C8EDE9BDBCCBA6D4 55A21772
	static void _0x950A154B8DAB6185(scrAny *p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x950A154B8DAB6185, p0, p1); } // 950A154B8DAB6185 A17F9AB0
	static void _0x12561FCBB62D5B9C(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x12561FCBB62D5B9C, p0); } // 12561FCBB62D5B9C 62B43677
	static void _0x044DBAD7A7FA2BE5(scrAny *p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x044DBAD7A7FA2BE5, p0, p1); } // 044DBAD7A7FA2BE5 8AD670EC
	static void _0xB4BBFD9CD8B3922B(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xB4BBFD9CD8B3922B, p0); } // B4BBFD9CD8B3922B D24B4D0C
	static void _0xE4E6DD5566D28C82() { NativeInvoke::Invoke<scrVoid>(0xE4E6DD5566D28C82); } // E4E6DD5566D28C82 7262B5BA
	static scrAny _0x3A48AB4445D499BE() { return NativeInvoke::Invoke<scrAny>(0x3A48AB4445D499BE); } // 3A48AB4445D499BE 93A44A1F
	static void _0x4ADA3F19BE4A6047(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x4ADA3F19BE4A6047, p0); } // 4ADA3F19BE4A6047 13777A0B
	static void _0x0150B6FF25A9E2E5() { NativeInvoke::Invoke<scrVoid>(0x0150B6FF25A9E2E5); } // 0150B6FF25A9E2E5 1134F68B
	static void _0xBEF34B1D9624D5DD(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xBEF34B1D9624D5DD, p0); } // BEF34B1D9624D5DD E0047BFD
}

namespace CUTSCENE
{
	static void REQUEST_CUTSCENE(scrAny *p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x7A86743F475D9E09, p0, p1); } // 7A86743F475D9E09 B5977853
	static void _0xC23DE0E91C30B58C(scrAny *p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xC23DE0E91C30B58C, p0, p1, p2); } // C23DE0E91C30B58C D98F656A
	static void REMOVE_CUTSCENE() { NativeInvoke::Invoke<scrVoid>(0x440AF51A3462B86F); } // 440AF51A3462B86F 8052F533
	static scrAny HAS_CUTSCENE_LOADED() { return NativeInvoke::Invoke<scrAny>(0xC59F528E9AB9F339); } // C59F528E9AB9F339 F9998582
	static BOOL HAS_THIS_CUTSCENE_LOADED(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x228D3D94F8A11C3C, p0); } // 228D3D94F8A11C3C 3C5619F2
	static void _0x8D9DF6ECA8768583(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x8D9DF6ECA8768583, p0); } // 8D9DF6ECA8768583 25A2CABC
	static BOOL _0xB56BBBCC2955D9CB() { return NativeInvoke::Invoke<BOOL>(0xB56BBBCC2955D9CB); } // B56BBBCC2955D9CB DD8878E9
	static BOOL _0x71B74D2AE19338D0(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x71B74D2AE19338D0, p0); } // 71B74D2AE19338D0 7B93CDAA
	static void _0x4C61C75BEE8184C2(scrAny *p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x4C61C75BEE8184C2, p0, p1, p2); } // 4C61C75BEE8184C2 47DB08A9
	static void START_CUTSCENE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x186D5CB5E7B0FF7B, p0); } // 186D5CB5E7B0FF7B 210106F6
	static void START_CUTSCENE_AT_COORDS(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x1C9ADDA3244A1FBF, p0, p1, p2, p3); } // 1C9ADDA3244A1FBF 58BEA436
	static void STOP_CUTSCENE(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xC7272775B4DC786E, p0); } // C7272775B4DC786E 5EE84DC7
	static void STOP_CUTSCENE_IMMEDIATELY() { NativeInvoke::Invoke<scrVoid>(0xD220BDD222AC4A1E); } // D220BDD222AC4A1E F528A2AD
	static void SET_CUTSCENE_ORIGIN(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0xB812B3FD1C01CF27, p0, p1, p2, p3, p4); } // B812B3FD1C01CF27 B0AD7792
	static void _0x011883F41211432A(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6) { NativeInvoke::Invoke<scrVoid>(0x011883F41211432A, p0, p1, p2, p3, p4, p5, p6); } // 011883F41211432A
	static scrAny GET_CUTSCENE_TIME() { return NativeInvoke::Invoke<scrAny>(0xE625BEABBAFFDAB9); } // E625BEABBAFFDAB9 53F5B5AB
	static scrAny GET_CUTSCENE_TOTAL_DURATION() { return NativeInvoke::Invoke<scrAny>(0xEE53B14A19E480D4); } // EE53B14A19E480D4 0824EBE8
	static scrAny WAS_CUTSCENE_SKIPPED() { return NativeInvoke::Invoke<scrAny>(0x40C8656EDAEDD569); } // 40C8656EDAEDD569 C9B6949D
	static BOOL HAS_CUTSCENE_FINISHED() { return NativeInvoke::Invoke<BOOL>(0x7C0A893088881D57); } // 7C0A893088881D57 5DED14B4
	static scrAny IS_CUTSCENE_ACTIVE() { return NativeInvoke::Invoke<scrAny>(0x991251AFC3981F84); } // 991251AFC3981F84 CCE2FE9D
	static BOOL IS_CUTSCENE_PLAYING() { return NativeInvoke::Invoke<BOOL>(0xD3C2E180A40F031E); } // D3C2E180A40F031E A3A78392
	static scrAny GET_CUTSCENE_SECTION_PLAYING() { return NativeInvoke::Invoke<scrAny>(0x49010A6A396553D8); } // 49010A6A396553D8 1026F0D6
	static scrAny GET_ENTITY_INDEX_OF_CUTSCENE_ENTITY(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x0A2E9FDB9A8C62F6, p0, p1); } // 0A2E9FDB9A8C62F6 1D09ABC7
	static scrAny _0x583DF8E3D4AFBD98() { return NativeInvoke::Invoke<scrAny>(0x583DF8E3D4AFBD98); } // 583DF8E3D4AFBD98 5AE68AE6
	static void REGISTER_ENTITY_FOR_CUTSCENE(scrAny p0, scrAny *p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0xE40C1C56DF95C2E8, p0, p1, p2, p3, p4); } // E40C1C56DF95C2E8 7CBC3EC7
	static scrAny GET_ENTITY_INDEX_OF_REGISTERED_ENTITY(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xC0741A26499654CD, p0, p1); } // C0741A26499654CD 46D18755
	static void _0x7F96F23FA9B73327(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x7F96F23FA9B73327, p0); } // 7F96F23FA9B73327
	static void SET_CUTSCENE_TRIGGER_AREA(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0x9896CE4721BE84BA, p0, p1, p2, p3, p4, p5); } // 9896CE4721BE84BA 9D76D9DE
	static BOOL CAN_SET_ENTER_STATE_FOR_REGISTERED_ENTITY(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x645D0B458D8E17B5, p0, p1); } // 645D0B458D8E17B5 55C30B26
	static BOOL CAN_SET_EXIT_STATE_FOR_REGISTERED_ENTITY(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x4C6A6451C79E4662, p0, p1); } // 4C6A6451C79E4662 8FF5D3C4
	static BOOL CAN_SET_EXIT_STATE_FOR_CAMERA(BOOL p0) { return NativeInvoke::Invoke<BOOL>(0xB2CBCD0930DFB420, p0); } // B2CBCD0930DFB420 EDAE6C02
	static void _0xC61B86C9F61EB404(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xC61B86C9F61EB404, p0); } // C61B86C9F61EB404 35721A08
	static void SET_CUTSCENE_FADE_VALUES(BOOL p0, BOOL p1, BOOL p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x8093F23ABACCC7D4, p0, p1, p2, p3); } // 8093F23ABACCC7D4 D19EF0DD
	static void _0x2F137B508DE238F2(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x2F137B508DE238F2, p0); } // 2F137B508DE238F2 8338DA1D
	static void _0xE36A98D8AB3D3C66(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xE36A98D8AB3D3C66, p0); } // E36A98D8AB3D3C66 04377C10
	static BOOL _0x5EDEF0CF8C1DAB3C() { return NativeInvoke::Invoke<BOOL>(0x5EDEF0CF8C1DAB3C); } // 5EDEF0CF8C1DAB3C DBD88708
	static void _0x41FAA8FB2ECE8720(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x41FAA8FB2ECE8720, p0); } // 41FAA8FB2ECE8720 28D54A7F
	static void REGISTER_SYNCHRONISED_SCRIPT_SPEECH() { NativeInvoke::Invoke<scrVoid>(0x2131046957F31B04); } // 2131046957F31B04 B60CFBB9
	static void SET_CUTSCENE_PED_COMPONENT_VARIATION(scrAny *p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0xBA01E7B6DEEFBBC9, p0, p1, p2, p3, p4); } // BA01E7B6DEEFBBC9 6AF994A1
	static void _0x2A56C06EBEF2B0D9(scrAny *p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x2A56C06EBEF2B0D9, p0, p1, p2); } // 2A56C06EBEF2B0D9 1E7DA95E
	static BOOL DOES_CUTSCENE_ENTITY_EXIST(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x499EF20C5DB25C59, p0, p1); } // 499EF20C5DB25C59 58E67409
	static void _0x0546524ADE2E9723(scrAny *p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x0546524ADE2E9723, p0, p1, p2, p3, p4); } // 0546524ADE2E9723 22E9A9DE
	static BOOL _0x708BDD8CD795B043() { return NativeInvoke::Invoke<BOOL>(0x708BDD8CD795B043); } // 708BDD8CD795B043 4315A7C5
}

namespace INTERIOR
{
	static scrAny GET_INTERIOR_GROUP_ID(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xE4A84ABF135EF91A, p0); } // E4A84ABF135EF91A 09D6376F
	static scrVector3 GET_OFFSET_FROM_INTERIOR_IN_WORLD_COORDS(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<scrVector3>(0x9E3B3E6D66F6E22F, p0, p1, p2, p3); } // 9E3B3E6D66F6E22F 7D8F26A1
	static scrAny IS_INTERIOR_SCENE() { return NativeInvoke::Invoke<scrAny>(0xBC72B5D7A1CBD54D); } // BC72B5D7A1CBD54D 55226C13
	static scrAny IS_VALID_INTERIOR(BOOL p0) { return NativeInvoke::Invoke<scrAny>(0x26B0E73D7EAAF4D3, p0); } // 26B0E73D7EAAF4D3 39C0B635
	static void CLEAR_ROOM_FOR_ENTITY(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xB365FC0C4E27FFA7, p0); } // B365FC0C4E27FFA7 7DDADB92
	static void FORCE_ROOM_FOR_ENTITY(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x52923C4710DD9907, p0, p1, p2); } // 52923C4710DD9907 10BD4435
	static scrAny GET_ROOM_KEY_FROM_ENTITY(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x47C2A06D4F5F424B, p0); } // 47C2A06D4F5F424B E4ACF8C3
	static scrAny GET_KEY_FOR_ENTITY_IN_ROOM(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x399685DB942336BC, p0); } // 399685DB942336BC 91EA80EF
	static scrAny GET_INTERIOR_FROM_ENTITY(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x2107BA504071A6BB, p0); } // 2107BA504071A6BB 5C644614
	static void _0x82EBB79E258FA2B7(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x82EBB79E258FA2B7, p0, p1); } // 82EBB79E258FA2B7 E645E162
	static void _0x920D853F3E17F1DA(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x920D853F3E17F1DA, p0, p1); } // 920D853F3E17F1DA D79803B5
	static void _0xAF348AFCB575A441(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xAF348AFCB575A441, p0); } // AF348AFCB575A441 1F6B4B13
	static void _0x405DC2AEF6AF95B9(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x405DC2AEF6AF95B9, p0); } // 405DC2AEF6AF95B9 0E9529CC
	static scrAny _0xA6575914D2A0B450() { return NativeInvoke::Invoke<scrAny>(0xA6575914D2A0B450); } // A6575914D2A0B450 4FF3D3F5
	static void _0x23B59D8912F94246() { NativeInvoke::Invoke<scrVoid>(0x23B59D8912F94246); } // 23B59D8912F94246 617DC75D
	static scrAny GET_INTERIOR_AT_COORDS(float p0, float p1, float p2) { return NativeInvoke::Invoke<scrAny>(0xB0F7F8663821D9C3, p0, p1, p2); } // B0F7F8663821D9C3 A17FBF37
	static void ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x3F6167F351168730, p0, p1); } // 3F6167F351168730 A2A73564
	static void _0x2CA429C029CCF247(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x2CA429C029CCF247, p0); } // 2CA429C029CCF247 3ADA414E
	static void UNPIN_INTERIOR(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x261CCE7EED010641, p0); } // 261CCE7EED010641 FCFF792A
	static BOOL IS_INTERIOR_READY(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x6726BDCCC1932F0E, p0); } // 6726BDCCC1932F0E E1EF6450
	static scrAny _0x4C2330E61D3DEB56(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x4C2330E61D3DEB56, p0); } // 4C2330E61D3DEB56
	static scrAny _0x05B7A89BD78797FC(float p0, float p1, float p2, scrAny *p3) { return NativeInvoke::Invoke<scrAny>(0x05B7A89BD78797FC, p0, p1, p2, p3); } // 05B7A89BD78797FC 96525B06
	static BOOL _0xEEA5AC2EDA7C33E8(float p0, float p1, float p2) { return NativeInvoke::Invoke<BOOL>(0xEEA5AC2EDA7C33E8, p0, p1, p2); } // EEA5AC2EDA7C33E8 7762249C
	static scrAny GET_INTERIOR_FROM_COLLISION(float p0, float p1, float p2) { return NativeInvoke::Invoke<scrAny>(0xEC4CF9FCB29A4424, p0, p1, p2); } // EC4CF9FCB29A4424 7ED33DC1
	static void _0x55E86AF2712B36A1(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x55E86AF2712B36A1, p0, p1); } // 55E86AF2712B36A1 C80A5DDF
	static void _0x420BD37289EEE162(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x420BD37289EEE162, p0, p1); } // 420BD37289EEE162 DBA768A1
	static BOOL _0x35F7DD45E8C0A16D(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x35F7DD45E8C0A16D, p0, p1); } // 35F7DD45E8C0A16D 39A3CC6F
	static void REFRESH_INTERIOR(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x41F37C3427C75AE0, p0); } // 41F37C3427C75AE0 9A29ACE6
	static void _0xA97F257D0151A6AB(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA97F257D0151A6AB, p0); } // A97F257D0151A6AB 1F375B4C
	static void DISABLE_INTERIOR(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x6170941419D7D8EC, p0, p1); } // 6170941419D7D8EC 093ADEA5
	static BOOL IS_INTERIOR_DISABLED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xBC5115A5A939DD15, p0); } // BC5115A5A939DD15 81F34C71
	static void CAP_INTERIOR(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xD9175F941610DB54, p0, p1); } // D9175F941610DB54 34E735A6
	static BOOL IS_INTERIOR_CAPPED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x92BAC8ACF88CEC26, p0); } // 92BAC8ACF88CEC26 18B17C80
	static void _0x9E6542F0CE8E70A3(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x9E6542F0CE8E70A3, p0); } // 9E6542F0CE8E70A3 5EF9C5C2
}

namespace CAM
{
	static void RENDER_SCRIPT_CAMS(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x07E5B515DB0636FC, p0, p1, p2, p3, p4); } // 07E5B515DB0636FC 74337969
	static void _0xC819F3CBB62BF692(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xC819F3CBB62BF692, p0, p1, p2); } // C819F3CBB62BF692 D3C08183
	static scrAny CREATE_CAM(char *p0, BOOL p1) { return NativeInvoke::Invoke<scrAny>(0xC3981DCE61D9E13F, p0, p1); } // C3981DCE61D9E13F E9BF2A7D
	static scrAny CREATE_CAM_WITH_PARAMS(scrAny *p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, BOOL p8, scrAny p9) { return NativeInvoke::Invoke<scrAny>(0xB51194800B257161, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // B51194800B257161 23B02F15
	static scrAny CREATE_CAMERA(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<scrAny>(0x5E3CF89C6BCCA67D, p0, p1); } // 5E3CF89C6BCCA67D 5D6739AE
	static scrAny CREATE_CAMERA_WITH_PARAMS(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, BOOL p8, scrAny p9) { return NativeInvoke::Invoke<scrAny>(0x6ABFA3E16460F22D, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 6ABFA3E16460F22D 0688BE9A
	static void DESTROY_CAM(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x865908C81A2C22E9, p0, p1); } // 865908C81A2C22E9 C39302BD
	static void DESTROY_ALL_CAMS(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x8E5FB15663F79120, p0); } // 8E5FB15663F79120 10C151CE
	static BOOL DOES_CAM_EXIST(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xA7A932170592B50E, p0); } // A7A932170592B50E 1EF89DC0
	static void SET_CAM_ACTIVE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x026FB97D0A425F84, p0, p1); } // 026FB97D0A425F84 064659C2
	static BOOL IS_CAM_ACTIVE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xDFB2B516207D3534, p0); } // DFB2B516207D3534 4B58F177
	static BOOL IS_CAM_RENDERING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x02EC0AF5C5A49B7A, p0); } // 02EC0AF5C5A49B7A 6EC6B5B2
	static scrAny GET_RENDERING_CAM() { return NativeInvoke::Invoke<scrAny>(0x5234F9F10919EABA); } // 5234F9F10919EABA 0FCF4DF1
	static scrVector3 GET_CAM_COORD(scrAny p0) { return NativeInvoke::Invoke<scrVector3>(0xBAC038F7459AE5AE, p0); } // BAC038F7459AE5AE 7C40F09C
	static scrVector3 GET_CAM_ROT(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrVector3>(0x7D304C1C955E3E12, p0, p1); } // 7D304C1C955E3E12 DAC84C9F
	static float GET_CAM_FOV(scrAny p0) { return NativeInvoke::Invoke<float>(0xC3330A45CCCDB26A, p0); } // C3330A45CCCDB26A D6E9FCF5
	static float GET_CAM_NEAR_CLIP(scrAny p0) { return NativeInvoke::Invoke<float>(0xC520A34DAFBF24B1, p0); } // C520A34DAFBF24B1 CFCD35EE
	static float GET_CAM_FAR_CLIP(scrAny p0) { return NativeInvoke::Invoke<float>(0xB60A9CFEB21CA6AA, p0); } // B60A9CFEB21CA6AA 09F119B8
	static float GET_CAM_FAR_DOF(scrAny p0) { return NativeInvoke::Invoke<float>(0x255F8DAFD540D397, p0); } // 255F8DAFD540D397 98C5CCE9
	static void SET_CAM_PARAMS(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, scrAny p8, scrAny p9, scrAny p10, scrAny p11) { NativeInvoke::Invoke<scrVoid>(0xBFD8727AEA3CCEBA, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // BFD8727AEA3CCEBA 2167CEBF
	static void SET_CAM_COORD(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x4D41783FB745E42E, p0, p1, p2, p3); } // 4D41783FB745E42E 7A8053AF
	static void SET_CAM_ROT(scrAny p0, float p1, float p2, float p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x85973643155D0B07, p0, p1, p2, p3, p4); } // 85973643155D0B07 EE38B3C1
	static void SET_CAM_FOV(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xB13C14F66A00D047, p0, p1); } // B13C14F66A00D047 D3D5D74F
	static void SET_CAM_NEAR_CLIP(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xC7848EFCCC545182, p0, p1); } // C7848EFCCC545182 46DB13B1
	static void SET_CAM_FAR_CLIP(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xAE306F2A904BF86E, p0, p1); } // AE306F2A904BF86E 0D23E381
	static void SET_CAM_MOTION_BLUR_STRENGTH(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x6F0F77FBA9A8F2E6, p0, p1); } // 6F0F77FBA9A8F2E6 FD6E0D67
	static void SET_CAM_NEAR_DOF(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x3FA4BF0A7AB7DE2C, p0, p1); } // 3FA4BF0A7AB7DE2C F28254DF
	static void SET_CAM_FAR_DOF(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xEDD91296CD01AEE0, p0, p1); } // EDD91296CD01AEE0 58515E8E
	static void SET_CAM_DOF_STRENGTH(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x5EE29B4D7D5DF897, p0, p1); } // 5EE29B4D7D5DF897 3CC4EB3F
	static void SET_CAM_DOF_PLANES(scrAny p0, float p1, float p2, float p3, float p4) { NativeInvoke::Invoke<scrVoid>(0x3CF48F6F96E749DC, p0, p1, p2, p3, p4); } // 3CF48F6F96E749DC AD6C2B8F
	static void _0x16A96863A17552BB(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x16A96863A17552BB, p0, p1); } // 16A96863A17552BB 8306C256
	static void _0xA13B0222F3D94A94() { NativeInvoke::Invoke<scrVoid>(0xA13B0222F3D94A94); } // A13B0222F3D94A94 8BBF2950
	static void _0xF55E4046F6F831DC(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xF55E4046F6F831DC, p0, p1); } // F55E4046F6F831DC
	static void _0xE111A7C0D200CBC5(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xE111A7C0D200CBC5, p0, p1); } // E111A7C0D200CBC5
	static void _0x7DD234D6F3914C5B(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x7DD234D6F3914C5B, p0, p1); } // 7DD234D6F3914C5B
	static void _0xC3654A441402562D(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xC3654A441402562D, p0, p1); } // C3654A441402562D
	static void _0x2C654B4943BDDF7C(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x2C654B4943BDDF7C, p0, p1); } // 2C654B4943BDDF7C
	static void ATTACH_CAM_TO_ENTITY(scrAny p0, scrAny p1, float p2, float p3, float p4, BOOL p5) { NativeInvoke::Invoke<scrVoid>(0xFEDB7D269E8C60E3, p0, p1, p2, p3, p4, p5); } // FEDB7D269E8C60E3 AD7C45F6
	static void ATTACH_CAM_TO_PED_BONE(scrAny p0, scrAny p1, scrAny p2, float p3, float p4, float p5, BOOL p6) { NativeInvoke::Invoke<scrVoid>(0x61A3DBA14AB7F411, p0, p1, p2, p3, p4, p5, p6); } // 61A3DBA14AB7F411 506BB35C
	static void DETACH_CAM(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA2FABBE87F4BAD82, p0); } // A2FABBE87F4BAD82 F4FBF14A
	static void SET_CAM_INHERIT_ROLL_VEHICLE(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x45F1DE9C34B93AE6, p0, p1); } // 45F1DE9C34B93AE6 E4BD5342
	static void POINT_CAM_AT_COORD(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0xF75497BB865F0803, p0, p1, p2, p3); } // F75497BB865F0803 914BC21A
	static void POINT_CAM_AT_ENTITY(scrAny p0, scrAny p1, float p2, float p3, float p4, BOOL p5) { NativeInvoke::Invoke<scrVoid>(0x5640BFF86B16E8DC, p0, p1, p2, p3, p4, p5); } // 5640BFF86B16E8DC 7597A0F7
	static void POINT_CAM_AT_PED_BONE(scrAny p0, scrAny p1, scrAny p2, float p3, float p4, float p5, BOOL p6) { NativeInvoke::Invoke<scrVoid>(0x68B2B5F33BA63C41, p0, p1, p2, p3, p4, p5, p6); } // 68B2B5F33BA63C41 09F47049
	static void STOP_CAM_POINTING(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xF33AB75780BA57DE, p0); } // F33AB75780BA57DE 5435F6A5
	static void _0x8C1DC7770C51DC8D(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x8C1DC7770C51DC8D, p0, p1); } // 8C1DC7770C51DC8D 0C74F9AF
	static void _0x661B5C8654ADD825(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x661B5C8654ADD825, p0, p1); } // 661B5C8654ADD825 E1A0B2F1
	static void _0xA2767257A320FC82(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xA2767257A320FC82, p0, p1); } // A2767257A320FC82
	static void _0x271017B9BA825366(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x271017B9BA825366, p0, p1); } // 271017B9BA825366 43220969
	static void SET_CAM_DEBUG_NAME(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x1B93E0107865DD40, p0, p1); } // 1B93E0107865DD40 9B00DF3F
	static void ADD_CAM_SPLINE_NODE(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, scrAny p7, scrAny p8, scrAny p9) { NativeInvoke::Invoke<scrVoid>(0x8609C75EC438FB3B, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 8609C75EC438FB3B AD3C7EAA
	static void _0x0A9F2A468B328E74(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x0A9F2A468B328E74, p0, p1, p2, p3); } // 0A9F2A468B328E74 30510511
	static void _0x0FB82563989CF4FB(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x0FB82563989CF4FB, p0, p1, p2, p3); } // 0FB82563989CF4FB BA6C085B
	static void _0x609278246A29CA34(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x609278246A29CA34, p0, p1, p2); } // 609278246A29CA34 B4737F03
	static void SET_CAM_SPLINE_PHASE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x242B5874F0A4E052, p0, p1); } // 242B5874F0A4E052 F0AED233
	static float GET_CAM_SPLINE_PHASE(scrAny p0) { return NativeInvoke::Invoke<float>(0xB5349E36C546509A, p0); } // B5349E36C546509A 39784DD9
	static float GET_CAM_SPLINE_NODE_PHASE(scrAny p0) { return NativeInvoke::Invoke<float>(0xD9D0E694C8282C96, p0); } // D9D0E694C8282C96 7B9522F6
	static void SET_CAM_SPLINE_DURATION(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x1381539FEE034CDA, p0, p1); } // 1381539FEE034CDA 3E91FC8A
	static void _0xD1B0F412F109EA5D(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xD1B0F412F109EA5D, p0, p1); } // D1B0F412F109EA5D 15E141CE
	static scrAny GET_CAM_SPLINE_NODE_INDEX(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xB22B17DF858716A6, p0); } // B22B17DF858716A6 F8AEB6BD
	static void _0x83B8201ED82A9A2D(scrAny p0, scrAny p1, scrAny p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x83B8201ED82A9A2D, p0, p1, p2, p3); } // 83B8201ED82A9A2D 21D275DA
	static void _0xA6385DEB180F319F(scrAny p0, scrAny p1, float p2) { NativeInvoke::Invoke<scrVoid>(0xA6385DEB180F319F, p0, p1, p2); } // A6385DEB180F319F A3BD9E94
	static void OVERRIDE_CAM_SPLINE_VELOCITY(scrAny p0, scrAny p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x40B62FA033EB0346, p0, p1, p2, p3); } // 40B62FA033EB0346 326A17E2
	static void OVERRIDE_CAM_SPLINE_MOTION_BLUR(scrAny p0, scrAny p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x7DCF7C708D292D55, p0, p1, p2, p3); } // 7DCF7C708D292D55 633179E6
	static void _0x7BF1A54AE67AC070(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x7BF1A54AE67AC070, p0, p1, p2); } // 7BF1A54AE67AC070 C90B2DDC
	static BOOL IS_CAM_SPLINE_PAUSED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x0290F35C0AD97864, p0); } // 0290F35C0AD97864 60B34FF5
	static void SET_CAM_ACTIVE_WITH_INTERP(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x9FBDA379383A52A4, p0, p1, p2, p3, p4); } // 9FBDA379383A52A4 7983E7F0
	static BOOL IS_CAM_INTERPOLATING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x036F97C908C2B52C, p0); } // 036F97C908C2B52C 7159CB5D
	static void SHAKE_CAM(scrAny p0, scrAny *p1, float p2) { NativeInvoke::Invoke<scrVoid>(0x6A25241C340D3822, p0, p1, p2); } // 6A25241C340D3822 1D4211B0
	static void ANIMATED_SHAKE_CAM(scrAny p0, scrAny *p1, scrAny *p2, scrAny *p3, float p4) { NativeInvoke::Invoke<scrVoid>(0xA2746EEAE3E577CD, p0, p1, p2, p3, p4); } // A2746EEAE3E577CD E1168767
	static BOOL IS_CAM_SHAKING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x6B24BFE83A2BE47B, p0); } // 6B24BFE83A2BE47B 0961FD9B
	static void SET_CAM_SHAKE_AMPLITUDE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xD93DB43B82BC0D00, p0, p1); } // D93DB43B82BC0D00 60FF6382
	static void STOP_CAM_SHAKING(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xBDECF64367884AC3, p0, p1); } // BDECF64367884AC3 40D0EB87
	static void _0xF4C8CF9E353AFECA(scrAny *p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xF4C8CF9E353AFECA, p0, p1); } // F4C8CF9E353AFECA 2B0F05CD
	static void _0xC2EAE3FB8CDBED31(scrAny *p0, scrAny *p1, scrAny *p2, float p3) { NativeInvoke::Invoke<scrVoid>(0xC2EAE3FB8CDBED31, p0, p1, p2, p3); } // C2EAE3FB8CDBED31 CB75BD9C
	static BOOL _0xC912AF078AF19212() { return NativeInvoke::Invoke<BOOL>(0xC912AF078AF19212); } // C912AF078AF19212 6AEFE6A5
	static void _0x1C9D7949FA533490(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x1C9D7949FA533490, p0); } // 1C9D7949FA533490 26FCFB96
	static BOOL PLAY_CAM_ANIM(scrAny p0, scrAny *p1, scrAny *p2, float p3, float p4, float p5, float p6, float p7, float p8, scrAny p9, scrAny p10) { return NativeInvoke::Invoke<BOOL>(0x9A2D0FB2E7852392, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 9A2D0FB2E7852392 BCEFB87E
	static BOOL IS_CAM_PLAYING_ANIM(scrAny p0, scrAny *p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0xC90621D8A0CEECF2, p0, p1, p2); } // C90621D8A0CEECF2 B998CB49
	static void SET_CAM_ANIM_CURRENT_PHASE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x4145A4C44FF3B5A6, p0, p1); } // 4145A4C44FF3B5A6 3CB1D17F
	static float GET_CAM_ANIM_CURRENT_PHASE(scrAny p0) { return NativeInvoke::Invoke<float>(0xA10B2DB49E92A6B0, p0); } // A10B2DB49E92A6B0 345F72D0
	static BOOL PLAY_SYNCHRONIZED_CAM_ANIM(scrAny p0, scrAny p1, scrAny *p2, scrAny *p3) { return NativeInvoke::Invoke<BOOL>(0xE32EFE9AB4A9AA0C, p0, p1, p2, p3); } // E32EFE9AB4A9AA0C 9458459E
	static void _0x503F5920162365B2(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x503F5920162365B2, p0, p1, p2, p3); } // 503F5920162365B2 56F9ED27
	static void _0xF9D02130ECDD1D77(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xF9D02130ECDD1D77, p0, p1); } // F9D02130ECDD1D77 71570DBA
	static void _0xC91C6C55199308CA(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0xC91C6C55199308CA, p0, p1, p2, p3); } // C91C6C55199308CA 60B345DE
	static void _0xC8B5C4A79CC18B94(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xC8B5C4A79CC18B94, p0); } // C8B5C4A79CC18B94 44473EFC
	static BOOL _0x5C48A1D6E3B33179(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x5C48A1D6E3B33179, p0); } // 5C48A1D6E3B33179 DA931D65
	static BOOL IS_SCREEN_FADED_OUT() { return NativeInvoke::Invoke<BOOL>(0xB16FCE9DDC7BA182); } // B16FCE9DDC7BA182 9CAA05FA
	static BOOL IS_SCREEN_FADED_IN() { return NativeInvoke::Invoke<BOOL>(0x5A859503B0C08678); } // 5A859503B0C08678 4F37276D
	static BOOL IS_SCREEN_FADING_OUT() { return NativeInvoke::Invoke<BOOL>(0x797AC7CB535BA28F); } // 797AC7CB535BA28F 79275A57
	static BOOL IS_SCREEN_FADING_IN() { return NativeInvoke::Invoke<BOOL>(0x5C544BC6C57AC575); } // 5C544BC6C57AC575 C7C82800
	static void DO_SCREEN_FADE_IN(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xD4E8E24955024033, p0); } // D4E8E24955024033 66C1BDEE
	static void DO_SCREEN_FADE_OUT(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x891B5B39AC6302AF, p0); } // 891B5B39AC6302AF 89D01805
	static void SET_WIDESCREEN_BORDERS(BOOL p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xDCD4EA924F42D01A, p0, p1); } // DCD4EA924F42D01A 1A75DC9A
	static scrVector3 GET_GAMEPLAY_CAM_COORD() { return NativeInvoke::Invoke<scrVector3>(0x14D6F5678D8F1B37); } // 14D6F5678D8F1B37 9388CF79
	static scrVector3 GET_GAMEPLAY_CAM_ROT(scrAny p0) { return NativeInvoke::Invoke<scrVector3>(0x837765A25378F0BB, p0); } // 837765A25378F0BB 13A010B5
	static scrAny GET_GAMEPLAY_CAM_FOV() { return NativeInvoke::Invoke<scrAny>(0x65019750A0324133); } // 65019750A0324133 4D6B3BFA
	static void _0x487A82C650EB7799(float p0) { NativeInvoke::Invoke<scrVoid>(0x487A82C650EB7799, p0); } // 487A82C650EB7799 A6E73135
	static void _0x0225778816FDC28C(float p0) { NativeInvoke::Invoke<scrVoid>(0x0225778816FDC28C, p0); } // 0225778816FDC28C 1126E37C
	static float GET_GAMEPLAY_CAM_RELATIVE_HEADING() { return NativeInvoke::Invoke<float>(0x743607648ADD4587); } // 743607648ADD4587 CAF839C2
	static void SET_GAMEPLAY_CAM_RELATIVE_HEADING(float p0) { NativeInvoke::Invoke<scrVoid>(0xB4EC2312F4E5B1F1, p0); } // B4EC2312F4E5B1F1 20C6217C
	static float GET_GAMEPLAY_CAM_RELATIVE_PITCH() { return NativeInvoke::Invoke<float>(0x3A6867B4845BEDA2); } // 3A6867B4845BEDA2 FC5A4946
	static void SET_GAMEPLAY_CAM_RELATIVE_PITCH(float p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x6D0858B8EDFD2B7D, p0, p1); } // 6D0858B8EDFD2B7D 6381B963
	static void _0x103991D4A307D472(float p0) { NativeInvoke::Invoke<scrVoid>(0x103991D4A307D472, p0); } // 103991D4A307D472
	static void _0x759E13EBC1C15C5A(float p0) { NativeInvoke::Invoke<scrVoid>(0x759E13EBC1C15C5A, p0); } // 759E13EBC1C15C5A
	static void _0x469F2ECDEC046337(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x469F2ECDEC046337, p0); } // 469F2ECDEC046337
	static void SHAKE_GAMEPLAY_CAM(scrAny *p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xFD55E49555E017CF, p0, p1); } // FD55E49555E017CF F2EFE660
	static BOOL IS_GAMEPLAY_CAM_SHAKING() { return NativeInvoke::Invoke<BOOL>(0x016C090630DF1F89); } // 016C090630DF1F89 3457D681
	static void SET_GAMEPLAY_CAM_SHAKE_AMPLITUDE(float p0) { NativeInvoke::Invoke<scrVoid>(0xA87E00932DB4D85D, p0); } // A87E00932DB4D85D 9219D44A
	static void STOP_GAMEPLAY_CAM_SHAKING(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x0EF93E9F3D08C178, p0); } // 0EF93E9F3D08C178 FD569E4E
	static void _0x8BBACBF51DA047A8(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x8BBACBF51DA047A8, p0); } // 8BBACBF51DA047A8 7D3007A2
	static BOOL IS_GAMEPLAY_CAM_RENDERING() { return NativeInvoke::Invoke<BOOL>(0x39B5D1B10383F0C8); } // 39B5D1B10383F0C8 0EF276DA
	static BOOL _0x3044240D2E0FA842() { return NativeInvoke::Invoke<BOOL>(0x3044240D2E0FA842); } // 3044240D2E0FA842 C0B00C20
	static BOOL _0x705A276EBFF3133D() { return NativeInvoke::Invoke<BOOL>(0x705A276EBFF3133D); } // 705A276EBFF3133D 60C23785
	static void _0xDB90C6CCA48940F1(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xDB90C6CCA48940F1, p0); } // DB90C6CCA48940F1 20BFF6E5
	static void _0xEA7F0AD7E9BA676F() { NativeInvoke::Invoke<scrVoid>(0xEA7F0AD7E9BA676F); } // EA7F0AD7E9BA676F A61FF9AC
	static BOOL IS_GAMEPLAY_CAM_LOOKING_BEHIND() { return NativeInvoke::Invoke<BOOL>(0x70FDA869F3317EA9); } // 70FDA869F3317EA9 33C83F17
	static void _0x2AED6301F67007D5(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x2AED6301F67007D5, p0); } // 2AED6301F67007D5 2701A9AD
	static void _0x49482F9FCD825AAA(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x49482F9FCD825AAA, p0); } // 49482F9FCD825AAA C4736ED3
	static void _0xFD3151CD37EA2245(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xFD3151CD37EA2245, p0); } // FD3151CD37EA2245
	static void _0xDD79DF9F4D26E1C9() { NativeInvoke::Invoke<scrVoid>(0xDD79DF9F4D26E1C9); } // DD79DF9F4D26E1C9 6B0E9D57
	static BOOL IS_SPHERE_VISIBLE(float p0, float p1, float p2, float p3) { return NativeInvoke::Invoke<BOOL>(0xE33D59DA70B58FDF, p0, p1, p2, p3); } // E33D59DA70B58FDF DD1329E2
	static BOOL IS_FOLLOW_PED_CAM_ACTIVE() { return NativeInvoke::Invoke<BOOL>(0xC6D3D26810C8E0F9); } // C6D3D26810C8E0F9 9F9E856C
	static BOOL SET_FOLLOW_PED_CAM_CUTSCENE_CHAT(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x44A113DD6FFC48D1, p0, p1); } // 44A113DD6FFC48D1 1425F6AC
	static void _0x271401846BD26E92(BOOL p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x271401846BD26E92, p0, p1); } // 271401846BD26E92 8DC53629
	static void _0xC8391C309684595A() { NativeInvoke::Invoke<scrVoid>(0xC8391C309684595A); } // C8391C309684595A 1F9DE6E4
	static void _0x8F993D26E0CA5E8E(float p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x8F993D26E0CA5E8E, p0, p1); } // 8F993D26E0CA5E8E 749909AC
	static void _0xA516C198B7DCA1E1(float p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xA516C198B7DCA1E1, p0, p1); } // A516C198B7DCA1E1 FA3A16E7
	static void _0xDF2E1F7742402E81(float p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xDF2E1F7742402E81, p0, p1); } // DF2E1F7742402E81 77340650
	static void _0xE9EA16D6E54CDCA4(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xE9EA16D6E54CDCA4, p0, p1); } // E9EA16D6E54CDCA4 4B22C5CB
	static void _0xDE2EF5DA284CC8DF() { NativeInvoke::Invoke<scrVoid>(0xDE2EF5DA284CC8DF); } // DE2EF5DA284CC8DF
	static void _0x59424BD75174C9B1() { NativeInvoke::Invoke<scrVoid>(0x59424BD75174C9B1); } // 59424BD75174C9B1
	static scrAny GET_FOLLOW_PED_CAM_ZOOM_LEVEL() { return NativeInvoke::Invoke<scrAny>(0x33E6C8EFD0CD93E9); } // 33E6C8EFD0CD93E9 57583DF1
	static scrAny GET_FOLLOW_PED_CAM_VIEW_MODE() { return NativeInvoke::Invoke<scrAny>(0x8D4D46230B2C353A); } // 8D4D46230B2C353A A65FF946
	static void SET_FOLLOW_PED_CAM_VIEW_MODE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x5A4F9EDF1673F704, p0); } // 5A4F9EDF1673F704 495DBE8D
	static BOOL IS_FOLLOW_VEHICLE_CAM_ACTIVE() { return NativeInvoke::Invoke<BOOL>(0xCBBDE6D335D6D496); } // CBBDE6D335D6D496 8DD49B77
	static void _0x91EF6EE6419E5B97(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x91EF6EE6419E5B97, p0); } // 91EF6EE6419E5B97 9DB5D391
	static void _0x9DFE13ECDC1EC196(BOOL p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x9DFE13ECDC1EC196, p0, p1); } // 9DFE13ECDC1EC196 92302899
	static scrAny GET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL() { return NativeInvoke::Invoke<scrAny>(0xEE82280AB767B690); } // EE82280AB767B690 8CD67DE3
	static void SET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x19464CB6E4078C8A, p0); } // 19464CB6E4078C8A 8F55EBBE
	static scrAny GET_FOLLOW_VEHICLE_CAM_VIEW_MODE() { return NativeInvoke::Invoke<scrAny>(0xA4FF579AC0E3AAAE); } // A4FF579AC0E3AAAE A4B4DB03
	static void SET_FOLLOW_VEHICLE_CAM_VIEW_MODE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xAC253D7842768F48, p0); } // AC253D7842768F48 C4FBBBD3
	static scrAny _0xEE778F8C7E1142E2(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xEE778F8C7E1142E2, p0); } // EE778F8C7E1142E2 F3B148A6
	static void _0x2A2173E46DAECD12(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x2A2173E46DAECD12, p0, p1); } // 2A2173E46DAECD12 1DEBCB45
	static scrAny _0x19CAFA3C87F7C2FF() { return NativeInvoke::Invoke<scrAny>(0x19CAFA3C87F7C2FF); } // 19CAFA3C87F7C2FF
	static BOOL IS_AIM_CAM_ACTIVE() { return NativeInvoke::Invoke<BOOL>(0x68EDDA28A5976D07); } // 68EDDA28A5976D07 C24B4F6F
	static BOOL _0x74BD83EA840F6BC9() { return NativeInvoke::Invoke<BOOL>(0x74BD83EA840F6BC9); } // 74BD83EA840F6BC9 8F320DE4
	static BOOL IS_FIRST_PERSON_AIM_CAM_ACTIVE() { return NativeInvoke::Invoke<BOOL>(0x5E346D934122613F); } // 5E346D934122613F D6280468
	static void _0x1A31FE0049E542F6() { NativeInvoke::Invoke<scrVoid>(0x1A31FE0049E542F6); } // 1A31FE0049E542F6 1BAA7182
	static float _0x7EC52CC40597D170() { return NativeInvoke::Invoke<float>(0x7EC52CC40597D170); } // 7EC52CC40597D170 33951005
	static void _0x70894BD0915C5BCA(float p0) { NativeInvoke::Invoke<scrVoid>(0x70894BD0915C5BCA, p0); } // 70894BD0915C5BCA 9F4AF763
	static void _0xCED08CBE8EBB97C7(float p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xCED08CBE8EBB97C7, p0, p1); } // CED08CBE8EBB97C7 68BA0730
	static void _0x2F7F2B26DD3F18EE(float p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x2F7F2B26DD3F18EE, p0, p1); } // 2F7F2B26DD3F18EE 2F29F0D5
	static void _0xBCFC632DB7673BF0(float p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xBCFC632DB7673BF0, p0, p1); } // BCFC632DB7673BF0 76DAC96C
	static void _0x0AF7B437918103B3(float p0) { NativeInvoke::Invoke<scrVoid>(0x0AF7B437918103B3, p0); } // 0AF7B437918103B3 0E21069D
	static void _0x42156508606DE65E(float p0) { NativeInvoke::Invoke<scrVoid>(0x42156508606DE65E, p0); } // 42156508606DE65E 71E9C63E
	static void _0x4008EDF7D6E48175(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x4008EDF7D6E48175, p0); } // 4008EDF7D6E48175 D1EEBC45
	static scrVector3 _0xA200EB1EE790F448() { return NativeInvoke::Invoke<scrVector3>(0xA200EB1EE790F448); } // A200EB1EE790F448 9C84BDA0
	static scrVector3 _0x5B4E4C817FCC2DFB(scrAny p0) { return NativeInvoke::Invoke<scrVector3>(0x5B4E4C817FCC2DFB, p0); } // 5B4E4C817FCC2DFB 1FFBEFC5
	static scrVector3 _0x26903D9CD1175F2C(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrVector3>(0x26903D9CD1175F2C, p0, p1); } // 26903D9CD1175F2C ACADF916
	static float _0x80EC114669DAEFF4() { return NativeInvoke::Invoke<float>(0x80EC114669DAEFF4); } // 80EC114669DAEFF4 721B763B
	static float _0x5F35F6732C3FBBA0(scrAny p0) { return NativeInvoke::Invoke<float>(0x5F35F6732C3FBBA0, p0); } // 5F35F6732C3FBBA0 23E3F106
	static float _0xD0082607100D7193() { return NativeInvoke::Invoke<float>(0xD0082607100D7193); } // D0082607100D7193 457AE195
	static float _0xDFC8CBC606FDB0FC() { return NativeInvoke::Invoke<float>(0xDFC8CBC606FDB0FC); } // DFC8CBC606FDB0FC 46CB3A49
	static float _0xA03502FC581F7D9B() { return NativeInvoke::Invoke<float>(0xA03502FC581F7D9B); } // A03502FC581F7D9B 19297A7A
	static float _0x9780F32BCAF72431() { return NativeInvoke::Invoke<float>(0x9780F32BCAF72431); } // 9780F32BCAF72431 F24777CA
	static float _0x162F9D995753DC19() { return NativeInvoke::Invoke<float>(0x162F9D995753DC19); } // 162F9D995753DC19 38992E83
	static void SET_GAMEPLAY_COORD_HINT(float p0, float p1, float p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6) { NativeInvoke::Invoke<scrVoid>(0xD51ADCD2D8BC0FB3, p0, p1, p2, p3, p4, p5, p6); } // D51ADCD2D8BC0FB3 F27483C9
	static void SET_GAMEPLAY_PED_HINT(scrAny p0, float p1, float p2, float p3, BOOL p4, scrAny p5, scrAny p6, scrAny p7) { NativeInvoke::Invoke<scrVoid>(0x2B486269ACD548D3, p0, p1, p2, p3, p4, p5, p6, p7); } // 2B486269ACD548D3 7C27343E
	static void SET_GAMEPLAY_VEHICLE_HINT(scrAny p0, float p1, float p2, float p3, BOOL p4, scrAny p5, scrAny p6, scrAny p7) { NativeInvoke::Invoke<scrVoid>(0xA2297E18F3E71C2E, p0, p1, p2, p3, p4, p5, p6, p7); } // A2297E18F3E71C2E 2C9A11D8
	static void _0x83E87508A2CA2AC6(scrAny p0, float p1, float p2, float p3, BOOL p4, scrAny p5, scrAny p6, scrAny p7) { NativeInvoke::Invoke<scrVoid>(0x83E87508A2CA2AC6, p0, p1, p2, p3, p4, p5, p6, p7); } // 83E87508A2CA2AC6 2ED5E2F8
	static void SET_GAMEPLAY_ENTITY_HINT(scrAny p0, float p1, float p2, float p3, BOOL p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8) { NativeInvoke::Invoke<scrVoid>(0x189E955A8313E298, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 189E955A8313E298 66C32306
	static BOOL IS_GAMEPLAY_HINT_ACTIVE() { return NativeInvoke::Invoke<BOOL>(0xE520FF1AD2785B40); } // E520FF1AD2785B40 AD8DA205
	static void STOP_GAMEPLAY_HINT(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xF46C581C61718916, p0); } // F46C581C61718916 1BC28B7B
	static void _0xCCD078C2665D2973(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xCCD078C2665D2973, p0); } // CCD078C2665D2973 CAFEE798
	static void _0x247ACBC4ABBC9D1C(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x247ACBC4ABBC9D1C, p0); } // 247ACBC4ABBC9D1C
	static scrAny _0xBF72910D0F26F025() { return NativeInvoke::Invoke<scrAny>(0xBF72910D0F26F025); } // BF72910D0F26F025
	static void SET_GAMEPLAY_HINT_FOV(float p0) { NativeInvoke::Invoke<scrVoid>(0x513403FB9C56211F, p0); } // 513403FB9C56211F 96FD173B
	static void _0xF8BDBF3D573049A1(float p0) { NativeInvoke::Invoke<scrVoid>(0xF8BDBF3D573049A1, p0); } // F8BDBF3D573049A1 72E8CD3A
	static void _0xD1F8363DFAD03848(float p0) { NativeInvoke::Invoke<scrVoid>(0xD1F8363DFAD03848, p0); } // D1F8363DFAD03848 79472AE3
	static void _0x5D7B620DAE436138(float p0) { NativeInvoke::Invoke<scrVoid>(0x5D7B620DAE436138, p0); } // 5D7B620DAE436138 FC7464A0
	static void _0xC92717EF615B6704(float p0) { NativeInvoke::Invoke<scrVoid>(0xC92717EF615B6704, p0); } // C92717EF615B6704 3554AA0E
	static void GET_IS_MULTIPLAYER_BRIEF(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xE3433EADAAF7EE40, p0); } // E3433EADAAF7EE40 2F0CE859
	static void SET_CINEMATIC_BUTTON_ACTIVE(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x51669F7D1FB53D9F, p0); } // 51669F7D1FB53D9F 3FBC5D00
	static BOOL IS_CINEMATIC_CAM_RENDERING() { return NativeInvoke::Invoke<BOOL>(0xB15162CB5826E9E8); } // B15162CB5826E9E8 80471AD9
	static void SHAKE_CINEMATIC_CAM(scrAny *p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xDCE214D9ED58F3CF, p0, p1); } // DCE214D9ED58F3CF 61815F31
	static BOOL IS_CINEMATIC_CAM_SHAKING() { return NativeInvoke::Invoke<BOOL>(0xBBC08F6B4CB8FF0A); } // BBC08F6B4CB8FF0A 8376D939
	static void SET_CINEMATIC_CAM_SHAKE_AMPLITUDE(float p0) { NativeInvoke::Invoke<scrVoid>(0xC724C701C30B2FE7, p0); } // C724C701C30B2FE7 67510C4B
	static void STOP_CINEMATIC_CAM_SHAKING(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x2238E588E588A6D7, p0); } // 2238E588E588A6D7 71C12904
	static void _0xADFF1B2A555F5FBA() { NativeInvoke::Invoke<scrVoid>(0xADFF1B2A555F5FBA); } // ADFF1B2A555F5FBA 5AC6DAC9
	static void _0x62ECFCFDEE7885D6() { NativeInvoke::Invoke<scrVoid>(0x62ECFCFDEE7885D6); } // 62ECFCFDEE7885D6 837F8581
	static void _0x9E4CFFF989258472() { NativeInvoke::Invoke<scrVoid>(0x9E4CFFF989258472); } // 9E4CFFF989258472 65DDE8AF
	static void _0xF4F2C0D4EE209E20() { NativeInvoke::Invoke<scrVoid>(0xF4F2C0D4EE209E20); } // F4F2C0D4EE209E20 D75CDD75
	static BOOL _0xCA9D2AA3E326D720() { return NativeInvoke::Invoke<BOOL>(0xCA9D2AA3E326D720); } // CA9D2AA3E326D720 96A07066
	static BOOL _0x4F32C0D5A90A9B40() { return NativeInvoke::Invoke<BOOL>(0x4F32C0D5A90A9B40); } // 4F32C0D5A90A9B40
	static void CREATE_CINEMATIC_SHOT(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x741B0129D4560F31, p0, p1, p2, p3); } // 741B0129D4560F31 AC494E35
	static BOOL IS_CINEMATIC_SHOT_ACTIVE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xCC9F3371A7C28BC9, p0); } // CC9F3371A7C28BC9 A4049042
	static void STOP_CINEMATIC_SHOT(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x7660C6E75D3A078E, p0); } // 7660C6E75D3A078E D78358C5
	static void _0xA41BCD7213805AAC(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xA41BCD7213805AAC, p0); } // A41BCD7213805AAC FBB85E02
	static void _0xDC9DA9E8789F5246() { NativeInvoke::Invoke<scrVoid>(0xDC9DA9E8789F5246); } // DC9DA9E8789F5246 4938C82F
	static void SET_CINEMATIC_MODE_ACTIVE(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xDCF0754AC3D6FD4E, p0); } // DCF0754AC3D6FD4E 2009E747
	static BOOL _0x1F2300CB7FA7B7F6() { return NativeInvoke::Invoke<BOOL>(0x1F2300CB7FA7B7F6); } // 1F2300CB7FA7B7F6 6739AD55
	static void STOP_CUTSCENE_CAM_SHAKING() { NativeInvoke::Invoke<scrVoid>(0xDB629FFD9285FA06); } // DB629FFD9285FA06 F07D603D
	static void _0x12DED8CA53D47EA5(float p0) { NativeInvoke::Invoke<scrVoid>(0x12DED8CA53D47EA5, p0); } // 12DED8CA53D47EA5 067BA6F5
	static scrAny _0x89215EC747DF244A(float p0, scrAny p1, float p2, float p3, float p4, float p5, float p6, scrAny p7, scrAny p8) { return NativeInvoke::Invoke<scrAny>(0x89215EC747DF244A, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 89215EC747DF244A FD99BE2B
	static void _0x5A43C76F7FC7BA5F() { NativeInvoke::Invoke<scrVoid>(0x5A43C76F7FC7BA5F); } // 5A43C76F7FC7BA5F E206C450
	static void _0x80C8B1846639BB19(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x80C8B1846639BB19, p0); } // 80C8B1846639BB19 B06CCD38
	static void _0x5C41E6BABC9E2112(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x5C41E6BABC9E2112, p0); } // 5C41E6BABC9E2112
	static void _0x21E253A7F8DA5DFB(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x21E253A7F8DA5DFB, p0); } // 21E253A7F8DA5DFB
	static void _0x11FA5D3479C7DD47(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x11FA5D3479C7DD47, p0); } // 11FA5D3479C7DD47
}

namespace WEAPON
{
	static void ENABLE_LASER_SIGHT_RENDERING(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xC8B46D7727D864AA, p0); } // C8B46D7727D864AA E3438955
	static scrAny _0x0DB57B41EC1DB083(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x0DB57B41EC1DB083, p0); } // 0DB57B41EC1DB083 324FA47A
	static scrAny GET_WEAPONTYPE_MODEL(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xF46CDC33180FDA94, p0); } // F46CDC33180FDA94 44E1C269
	static scrAny GET_WEAPONTYPE_SLOT(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x4215460B9B8B7FA0, p0); } // 4215460B9B8B7FA0 2E3759AF
	static scrAny GET_WEAPONTYPE_GROUP(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xC3287EE3050FB74C, p0); } // C3287EE3050FB74C 5F2DE833
	static void SET_CURRENT_PED_WEAPON(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xADF692B254977C0C, p0, p1, p2); } // ADF692B254977C0C B8278882
	static BOOL GET_CURRENT_PED_WEAPON(scrAny p0, scrHash *p1, BOOL p2) { return NativeInvoke::Invoke<BOOL>(0x3A87E44BB9A01D54, p0, p1, p2); } // 3A87E44BB9A01D54 B0237302
	static scrAny _0x3B390A939AF0B5FC(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x3B390A939AF0B5FC, p0); } // 3B390A939AF0B5FC 5D73CD20
	static scrAny GET_BEST_PED_WEAPON(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<scrAny>(0x8483E98E8B888AE2, p0, p1); } // 8483E98E8B888AE2 B998D444
	static BOOL SET_CURRENT_PED_VEHICLE_WEAPON(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x75C55983C2C39DAA, p0, p1); } // 75C55983C2C39DAA 8E6F2AF1
	static BOOL GET_CURRENT_PED_VEHICLE_WEAPON(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x1017582BCD3832DC, p0, p1); } // 1017582BCD3832DC F26C5D65
	static BOOL IS_PED_ARMED(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x475768A975D5AD17, p0, p1); } // 475768A975D5AD17 0BFC892C
	static BOOL IS_WEAPON_VALID(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x937C71165CF334B3, p0); } // 937C71165CF334B3 38CA2954
	static BOOL HAS_PED_GOT_WEAPON(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0x8DECB02F88F428BC, p0, p1, p2); } // 8DECB02F88F428BC 43D2FA82
	static BOOL _0xB80CA294F2F26749(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xB80CA294F2F26749, p0); } // B80CA294F2F26749 02A32CB0
	static scrAny GET_PED_WEAPONTYPE_IN_SLOT(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xEFFED78E9011134D, p0, p1); } // EFFED78E9011134D 9BC64E16
	static scrAny GET_AMMO_IN_PED_WEAPON(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x015A522136D7F951, p0, p1); } // 015A522136D7F951 0C755733
	static void ADD_AMMO_TO_PED(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x78F0424C34306220, p0, p1, p2); } // 78F0424C34306220 7F0580C7
	static void SET_PED_AMMO(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x14E56BC5B5DB6A19, p0, p1, p2); } // 14E56BC5B5DB6A19 BF90DF1A
	static void SET_PED_INFINITE_AMMO(scrAny p0, BOOL p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x3EDCB0505123623B, p0, p1, p2); } // 3EDCB0505123623B 9CB8D278
	static void _0x183DADC6AA953186(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x183DADC6AA953186, p0, p1); } // 183DADC6AA953186 5A5E3B67
	static void GIVE_WEAPON_TO_PED(scrAny p0, scrAny p1, scrAny p2, BOOL p3, BOOL p4) { NativeInvoke::Invoke<scrVoid>(0xBF0FD6E56C964FCB, p0, p1, p2, p3, p4); } // BF0FD6E56C964FCB C4D88A85
	static void GIVE_DELAYED_WEAPON_TO_PED(scrAny p0, scrAny p1, scrAny p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0xB282DC6EBD803C75, p0, p1, p2, p3); } // B282DC6EBD803C75 5868D20D
	static void REMOVE_ALL_PED_WEAPONS(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xF25DF915FA38C5F3, p0, p1); } // F25DF915FA38C5F3 A44CE817
	static void REMOVE_WEAPON_FROM_PED(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x4899CB088EDF59B8, p0, p1); } // 4899CB088EDF59B8 9C37F220
	static void HIDE_PED_WEAPON_FOR_SCRIPTED_CUTSCENE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x6F6981D2253C208F, p0, p1); } // 6F6981D2253C208F 00CFD6E9
	static void SET_PED_CURRENT_WEAPON_VISIBLE(scrAny p0, BOOL p1, BOOL p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x0725A4CCFDED9A70, p0, p1, p2, p3); } // 0725A4CCFDED9A70 00BECD77
	static void SET_PED_DROPS_WEAPONS_WHEN_DEAD(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x476AE72C1D19D1A8, p0, p1); } // 476AE72C1D19D1A8 8A444056
	static BOOL HAS_PED_BEEN_DAMAGED_BY_WEAPON(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0x2D343D2219CD027A, p0, p1, p2); } // 2D343D2219CD027A CDFBBCC6
	static void CLEAR_PED_LAST_WEAPON_DAMAGE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x0E98F88A24C5F4B8, p0); } // 0E98F88A24C5F4B8 52C68832
	static BOOL HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0x131D401334815E94, p0, p1, p2); } // 131D401334815E94 6DAABB39
	static void CLEAR_ENTITY_LAST_WEAPON_DAMAGE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xAC678E40BE7C74D2, p0); } // AC678E40BE7C74D2 CEC2732B
	static void SET_PED_DROPS_WEAPON(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x6B7513D9966FBEC0, p0); } // 6B7513D9966FBEC0 3D3329FA
	static void SET_PED_DROPS_INVENTORY_WEAPON(scrAny p0, scrAny p1, float p2, float p3, float p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0x208A1888007FC0E6, p0, p1, p2, p3, p4, p5); } // 208A1888007FC0E6 81FFB874
	static scrAny GET_MAX_AMMO_IN_CLIP(scrAny p0, scrAny p1, BOOL p2) { return NativeInvoke::Invoke<scrAny>(0xA38DCFFCEA8962FA, p0, p1, p2); } // A38DCFFCEA8962FA 6961E2A4
	static BOOL GET_AMMO_IN_CLIP(scrAny p0, scrAny p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0x2E1202248937775C, p0, p1, p2); } // 2E1202248937775C 73C100C3
	static BOOL SET_AMMO_IN_CLIP(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0xDCD2A934D65CB497, p0, p1, p2); } // DCD2A934D65CB497 A54B0B10
	static BOOL GET_MAX_AMMO(scrAny p0, scrAny p1, int *p2) { return NativeInvoke::Invoke<BOOL>(0xDC16122C7A20C933, p0, p1, p2); } // DC16122C7A20C933 0B294796
	static void SET_PED_AMMO_BY_TYPE(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x5FD1E1F011E76D7E, p0, p1, p2); } // 5FD1E1F011E76D7E 311C52BB
	static scrAny GET_PED_AMMO_BY_TYPE(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x39D22031557946C1, p0, p1); } // 39D22031557946C1 54077C4D
	static void SET_PED_AMMO_TO_DROP(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xA4EFEF9440A5B0EF, p0, p1); } // A4EFEF9440A5B0EF 2386A307
	static void _0xE620FD3512A04F18(float p0) { NativeInvoke::Invoke<scrVoid>(0xE620FD3512A04F18, p0); } // E620FD3512A04F18 D6460EA2
	static scrAny _0x7FEAD38B326B9F74(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x7FEAD38B326B9F74, p0, p1); } // 7FEAD38B326B9F74 09337863
	static scrAny GET_PED_LAST_WEAPON_IMPACT_COORD(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x6C4D0409BA1A2BC2, p0, p1); } // 6C4D0409BA1A2BC2 9B266079
	static void SET_PED_GADGET(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xD0D7B1E680ED4A1A, p0, p1, p2); } // D0D7B1E680ED4A1A 8A256D0A
	static BOOL _0xF731332072F5156C(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xF731332072F5156C, p0, p1); } // F731332072F5156C 8DDD0B5B
	static scrAny GET_SELECTED_PED_WEAPON(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x0A6DB4965674D243, p0); } // 0A6DB4965674D243 D240123E
	static void EXPLODE_PROJECTILES(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xFC4BD125DE7611E4, p0, p1, p2); } // FC4BD125DE7611E4 35A0B955
	static void REMOVE_ALL_PROJECTILES_OF_TYPE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xFC52E0F37E446528, p0, p1); } // FC52E0F37E446528 A5F89919
	static float _0x840F03E9041E2C9C(scrAny p0) { return NativeInvoke::Invoke<float>(0x840F03E9041E2C9C, p0); } // 840F03E9041E2C9C 3612110D
	static float _0x814C9D19DFD69679(scrAny p0) { return NativeInvoke::Invoke<float>(0x814C9D19DFD69679, p0); } // 814C9D19DFD69679 B2B2BBAA
	static BOOL HAS_VEHICLE_GOT_PROJECTILE_ATTACHED(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<BOOL>(0x717C8481234E3B88, p0, p1, p2, p3); } // 717C8481234E3B88 A57E2E80
	static void GIVE_WEAPON_COMPONENT_TO_PED(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xD966D51AA5B28BB9, p0, p1, p2); } // D966D51AA5B28BB9 3E1E286D
	static void REMOVE_WEAPON_COMPONENT_FROM_PED(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x1E8BE90C74FB4C09, p0, p1, p2); } // 1E8BE90C74FB4C09 412AA00D
	static BOOL HAS_PED_GOT_WEAPON_COMPONENT(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0xC593212475FAE340, p0, p1, p2); } // C593212475FAE340 DC0FC145
	static BOOL IS_PED_WEAPON_COMPONENT_ACTIVE(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0x0D78DE0572D3969E, p0, p1, p2); } // 0D78DE0572D3969E 7565FB19
	static BOOL _0x8C0D57EA686FAD87(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x8C0D57EA686FAD87, p0); } // 8C0D57EA686FAD87 82EEAF0F
	static BOOL MAKE_PED_RELOAD(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x20AE33F3AC9C0033, p0); } // 20AE33F3AC9C0033 515292C2
	static void REQUEST_WEAPON_ASSET(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x5443438F033E29C3, p0, p1, p2); } // 5443438F033E29C3 65D139A5
	static BOOL HAS_WEAPON_ASSET_LOADED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x36E353271F0E90EE, p0); } // 36E353271F0E90EE 1891D5BB
	static void REMOVE_WEAPON_ASSET(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xAA08EF13F341C8FC, p0); } // AA08EF13F341C8FC 2C0DFE3C
	static scrAny CREATE_WEAPON_OBJECT(scrAny p0, scrAny p1, float p2, float p3, float p4, BOOL p5, float p6) { return NativeInvoke::Invoke<scrAny>(0x9541D3CF0D398F36, p0, p1, p2, p3, p4, p5, p6); } // 9541D3CF0D398F36 62F5987F
	static void GIVE_WEAPON_COMPONENT_TO_WEAPON_OBJECT(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x33E179436C0B31DB, p0, p1); } // 33E179436C0B31DB F7612A37
	static void REMOVE_WEAPON_COMPONENT_FROM_WEAPON_OBJECT(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xF7D82B0D66777611, p0, p1); } // F7D82B0D66777611 A6E7ED3C
	static BOOL HAS_WEAPON_GOT_WEAPON_COMPONENT(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x76A18844E743BF91, p0, p1); } // 76A18844E743BF91 1D368510
	static void GIVE_WEAPON_OBJECT_TO_PED(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xB1FA61371AF7C4B7, p0, p1); } // B1FA61371AF7C4B7 639AF3EF
	static BOOL _0x5CEE3DF569CECAB0(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x5CEE3DF569CECAB0, p0, p1); } // 5CEE3DF569CECAB0 B1817BAA
	static scrAny GET_WEAPON_OBJECT_FROM_PED(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<scrAny>(0xCAE1DC9A0E22A16D, p0, p1); } // CAE1DC9A0E22A16D DF939A38
	static void SET_PED_WEAPON_TINT_INDEX(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x50969B9B89ED5738, p0, p1, p2); } // 50969B9B89ED5738 EB2A7B23
	static scrAny GET_PED_WEAPON_TINT_INDEX(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x2B9EEDC07BD06B9F, p0, p1); } // 2B9EEDC07BD06B9F 3F9C90A7
	static void SET_WEAPON_OBJECT_TINT_INDEX(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xF827589017D4E4A9, p0, p1); } // F827589017D4E4A9 44ACC1DA
	static scrAny GET_WEAPON_OBJECT_TINT_INDEX(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xCD183314F7CD2E57, p0); } // CD183314F7CD2E57 D91D9576
	static scrAny GET_WEAPON_TINT_COUNT(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x5DCF6C5CAB2E9BF7, p0); } // 5DCF6C5CAB2E9BF7 99E4EAAB
	static BOOL GET_WEAPON_HUD_STATS(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0xD92C739EE34C9EBA, p0, p1); } // D92C739EE34C9EBA A9AD3D98
	static BOOL GET_WEAPON_COMPONENT_HUD_STATS(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0xB3CAF387AE12E9F8, p0, p1); } // B3CAF387AE12E9F8 BB5498F4
	static scrAny GET_WEAPON_CLIP_SIZE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x583BE370B1EC6EB4, p0); } // 583BE370B1EC6EB4 8D515E66
	static void _0x8378627201D5497D(scrAny p0, float p1, float p2) { NativeInvoke::Invoke<scrVoid>(0x8378627201D5497D, p0, p1, p2); } // 8378627201D5497D B4F44C6E
	static scrAny _0xB4C8D77C80C0421E(scrAny p0, float p1) { return NativeInvoke::Invoke<scrAny>(0xB4C8D77C80C0421E, p0, p1); } // B4C8D77C80C0421E EC2E5304
	static void _0x48164DBB970AC3F0(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x48164DBB970AC3F0, p0); } // 48164DBB970AC3F0 E3BD00F9
	static BOOL _0x65F0C5AE05943EC7(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x65F0C5AE05943EC7, p0); } // 65F0C5AE05943EC7 BAF7BFBE
	static BOOL SET_WEAPON_SMOKEGRENADE_ASSIGNED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x4B7620C47217126C, p0); } // 4B7620C47217126C 76876154
	static scrAny _0xCEA66DAD478CD39B(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xCEA66DAD478CD39B, p0); } // CEA66DAD478CD39B B0127EA7
	static void SET_WEAPON_ANIMATION_OVERRIDE(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x1055AC3A667F09D9, p0, p1); } // 1055AC3A667F09D9 A5DF7484
	static scrAny GET_WEAPON_DAMAGE_TYPE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x3BE0BB12D25FB305, p0); } // 3BE0BB12D25FB305 013AFC13
	static void _0xE4DCEC7FD5B739A5(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xE4DCEC7FD5B739A5, p0); } // E4DCEC7FD5B739A5 64646F1D
	static BOOL _0xBC7BE5ABC0879F74(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xBC7BE5ABC0879F74, p0); } // BC7BE5ABC0879F74 135E7AD4
}

namespace ITEMSET
{
	static scrAny CREATE_ITEMSET(BOOL p0) { return NativeInvoke::Invoke<scrAny>(0x35AD299F50D91B24, p0); } // 35AD299F50D91B24 0A113B2C
	static void DESTROY_ITEMSET(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xDE18220B1C183EDA, p0); } // DE18220B1C183EDA 83CE1A4C
	static BOOL IS_ITEMSET_VALID(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xB1B1EA596344DFAB, p0); } // B1B1EA596344DFAB D201FC29
	static BOOL ADD_TO_ITEMSET(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xE3945201F14637DD, p0, p1); } // E3945201F14637DD 6B0FE61B
	static void REMOVE_FROM_ITEMSET(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x25E68244B0177686, p0, p1); } // 25E68244B0177686 A9565228
	static scrAny GET_ITEMSET_SIZE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xD9127E83ABF7C631, p0); } // D9127E83ABF7C631 2B31F41A
	static scrAny GET_INDEXED_ITEM_IN_ITEMSET(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x7A197E2521EE2BAB, p0, p1); } // 7A197E2521EE2BAB 3F712874
	static BOOL IS_IN_ITEMSET(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x2D0FC594D1E9C107, p0, p1); } // 2D0FC594D1E9C107 0D4B9730
	static void CLEAN_ITEMSET(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x41BC0D722FC04221, p0); } // 41BC0D722FC04221 919A4858
}

namespace STREAMING
{
	static void LOAD_ALL_OBJECTS_NOW() { NativeInvoke::Invoke<scrVoid>(0xBD6E84632DD4CB3F); } // BD6E84632DD4CB3F C9DBDA90
	static void LOAD_SCENE(float x, float y, float z) { NativeInvoke::Invoke<scrVoid>(0x4448EB75B4904BDB, x, y, z); } // 4448EB75B4904BDB B72403F5
	static BOOL NETWORK_UPDATE_LOAD_SCENE() { return NativeInvoke::Invoke<BOOL>(0xC4582015556D1C46); } // C4582015556D1C46 C76E023C
	static void NETWORK_STOP_LOAD_SCENE() { NativeInvoke::Invoke<scrVoid>(0x64E630FAF5F60F44); } // 64E630FAF5F60F44 24857907
	static scrAny IS_NETWORK_LOADING_SCENE() { return NativeInvoke::Invoke<scrAny>(0x41CA5A33160EA4AB); } // 41CA5A33160EA4AB 6DCFC021
	static void SET_INTERIOR_ACTIVE(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xE37B76C387BE28ED, p0, p1); } // E37B76C387BE28ED E1013910
	static void REQUEST_MODEL(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x963D27A58DF860AC, p0); } // 963D27A58DF860AC FFF1B500
	static void _0xA0261AEF7ACFC51E(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA0261AEF7ACFC51E, p0); } // A0261AEF7ACFC51E 48CEB6B4
	static BOOL HAS_MODEL_LOADED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x98A4EB5D89A0C952, p0); } // 98A4EB5D89A0C952 62BFDB37
	static void _0x8A7A40100EDFEC58(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x8A7A40100EDFEC58, p0, p1); } // 8A7A40100EDFEC58 939243FB
	static void SET_MODEL_AS_NO_LONGER_NEEDED(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xE532F5D78798DAAB, p0); } // E532F5D78798DAAB AE0F069E
	static BOOL IS_MODEL_IN_CDIMAGE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x35B9E0803292B641, p0); } // 35B9E0803292B641 1094782F
	static BOOL IS_MODEL_VALID(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xC0296A2EDF545E92, p0); } // C0296A2EDF545E92 AF8F8E9D
	static BOOL IS_MODEL_A_VEHICLE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x19AAC8F07BFEC53E, p0); } // 19AAC8F07BFEC53E FFFC85D4
	static void REQUEST_COLLISION_AT_COORD(float p0, float p1, float p2) { NativeInvoke::Invoke<scrVoid>(0x07503F7948F491A7, p0, p1, p2); } // 07503F7948F491A7 CD9805E7
	static void REQUEST_COLLISION_FOR_MODEL(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x923CB32A3B874FCB, p0); } // 923CB32A3B874FCB 3930C042
	static BOOL HAS_COLLISION_FOR_MODEL_LOADED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x22CCA434E368F03A, p0); } // 22CCA434E368F03A 41A094F8
	static void REQUEST_ADDITIONAL_COLLISION_AT_COORD(float p0, float p1, float p2) { NativeInvoke::Invoke<scrVoid>(0xC9156DC11411A9EA, p0, p1, p2); } // C9156DC11411A9EA C2CC1DF2
	static BOOL _0x2DA49C3B79856961(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x2DA49C3B79856961, p0); } // 2DA49C3B79856961 CD31C872
	static void REQUEST_ANIM_DICT(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xD3BD40951412FEF6, p0); } // D3BD40951412FEF6 DCA96950
	static BOOL HAS_ANIM_DICT_LOADED(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xD031A9162D01088C, p0); } // D031A9162D01088C 05E6763C
	static void REMOVE_ANIM_DICT(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xF66A602F829E2A06, p0); } // F66A602F829E2A06 0AE050B5
	static void REQUEST_ANIM_SET(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x6EA47DAE7FAD0EED, p0); } // 6EA47DAE7FAD0EED 2988B3FC
	static BOOL HAS_ANIM_SET_LOADED(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xC4EA073D86FB29B0, p0); } // C4EA073D86FB29B0 4FFF397D
	static void REMOVE_ANIM_SET(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x16350528F93024B3, p0); } // 16350528F93024B3 D04A817A
	static void REQUEST_CLIP_SET(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xD2A71E1A77418A49, p0); } // D2A71E1A77418A49 546C627A
	static BOOL HAS_CLIP_SET_LOADED(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x318234F4F3738AF3, p0); } // 318234F4F3738AF3 230D5455
	static void REMOVE_CLIP_SET(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x01F73A131C18CD94, p0); } // 01F73A131C18CD94 1E21F7AA
	static void REQUEST_IPL(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x41B4893843BBDB74, p0); } // 41B4893843BBDB74 3B70D1DB
	static void REMOVE_IPL(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xEE6C5AD3ECE0A82D, p0); } // EE6C5AD3ECE0A82D DF7CBD36
	static BOOL IS_IPL_ACTIVE(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x88A741E44A2B3495, p0); } // 88A741E44A2B3495 B2C33714
	static void SET_STREAMING(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x6E0C692677008888, p0); } // 6E0C692677008888 27EF6CB2
	static void SET_GAME_PAUSES_FOR_STREAMING(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x717CD6E6FAEBBEDC, p0); } // 717CD6E6FAEBBEDC 9211A28A
	static void SET_REDUCE_PED_MODEL_BUDGET(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x77B5F9A36BF96710, p0); } // 77B5F9A36BF96710 AFCB2B86
	static void SET_REDUCE_VEHICLE_MODEL_BUDGET(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x80C527893080CCF3, p0); } // 80C527893080CCF3 CDB4FB7E
	static void SET_DITCH_POLICE_MODELS(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x42CBE54462D92634, p0); } // 42CBE54462D92634 3EA7FCE4
	static scrAny GET_NUMBER_OF_STREAMING_REQUESTS() { return NativeInvoke::Invoke<scrAny>(0x4060057271CEBC89); } // 4060057271CEBC89 C2EE9A02
	static void REQUEST_PTFX_ASSET() { NativeInvoke::Invoke<scrVoid>(0x944955FB2A3935C8); } // 944955FB2A3935C8 2C649263
	static BOOL HAS_PTFX_ASSET_LOADED() { return NativeInvoke::Invoke<BOOL>(0xCA7D9B86ECA7481B); } // CA7D9B86ECA7481B 3EFF96BE
	static void REMOVE_PTFX_ASSET() { NativeInvoke::Invoke<scrVoid>(0x88C6814073DD4A73); } // 88C6814073DD4A73 C10F178C
	static void _0xB80D8756B4668AB6(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xB80D8756B4668AB6, p0); } // B80D8756B4668AB6 CFEA19A9
	static BOOL _0x8702416E512EC454(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x8702416E512EC454, p0); } // 8702416E512EC454 9ACC6446
	static void SET_VEHICLE_POPULATION_BUDGET(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xCB9E1EB3BE2AF4E9, p0); } // CB9E1EB3BE2AF4E9 1D56993C
	static void SET_PED_POPULATION_BUDGET(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x8C95333CFC3340F3, p0); } // 8C95333CFC3340F3 D2D026CD
	static void CLEAR_FOCUS() { NativeInvoke::Invoke<scrVoid>(0x31B73D1EA9F01DA2); } // 31B73D1EA9F01DA2 34D91E7A
	static void _0xBB7454BAFF08FE25(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0xBB7454BAFF08FE25, p0, p1, p2, p3, p4, p5); } // BB7454BAFF08FE25 14680A60
	static void SET_FOCUS_ENTITY(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x198F77705FA0931D, p0); } // 198F77705FA0931D 18DB04AC
	static BOOL IS_ENTITY_FOCUS(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x2DDFF3FB9075D747, p0); } // 2DDFF3FB9075D747 B456D707
	static void _0x0811381EF5062FEC(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x0811381EF5062FEC, p0); } // 0811381EF5062FEC
	static void _0xAF12610C644A35C9(scrAny *p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xAF12610C644A35C9, p0, p1); } // AF12610C644A35C9 403CD434
	static void _0x4E52E752C76E7E7A(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x4E52E752C76E7E7A, p0); } // 4E52E752C76E7E7A A07BAEB9
	static scrAny _0x219C7B8D53E429FD(float p0, float p1, float p2, float p3, scrAny p4, scrAny p5) { return NativeInvoke::Invoke<scrAny>(0x219C7B8D53E429FD, p0, p1, p2, p3, p4, p5); } // 219C7B8D53E429FD 10B6AB36
	static scrAny _0x1F3F018BC3AFA77C(float p0, float p1, float p2, float p3, float p4, float p5, float p6, scrAny p7, scrAny p8) { return NativeInvoke::Invoke<scrAny>(0x1F3F018BC3AFA77C, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 1F3F018BC3AFA77C 72344191
	static scrAny _0x0AD9710CEE2F590F(float p0, float p1, float p2, float p3, float p4, float p5, scrAny p6) { return NativeInvoke::Invoke<scrAny>(0x0AD9710CEE2F590F, p0, p1, p2, p3, p4, p5, p6); } // 0AD9710CEE2F590F C0157255
	static void _0x1EE7D8DF4425F053(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x1EE7D8DF4425F053, p0); } // 1EE7D8DF4425F053 E80F8ABE
	static scrAny _0x7D41E9D2D17C5B2D(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x7D41E9D2D17C5B2D, p0); } // 7D41E9D2D17C5B2D 1B3521F4
	static scrAny _0x07C313F94746702C(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x07C313F94746702C, p0); } // 07C313F94746702C 42CFE9C0
	static scrAny _0xBC9823AB80A3DCAC() { return NativeInvoke::Invoke<scrAny>(0xBC9823AB80A3DCAC); } // BC9823AB80A3DCAC 56253356
	static BOOL NEW_LOAD_SCENE_START(float p0, float p1, float p2, float p3, float p4, float p5, float p6, scrAny p7) { return NativeInvoke::Invoke<BOOL>(0x212A8D0D2BABFAC2, p0, p1, p2, p3, p4, p5, p6, p7); } // 212A8D0D2BABFAC2 DF9C38B6
	static BOOL _0xACCFB4ACF53551B0(float p0, float p1, float p2, float p3, scrAny p4) { return NativeInvoke::Invoke<BOOL>(0xACCFB4ACF53551B0, p0, p1, p2, p3, p4); } // ACCFB4ACF53551B0 FA037FEB
	static void NEW_LOAD_SCENE_STOP() { NativeInvoke::Invoke<scrVoid>(0xC197616D221FF4A4); } // C197616D221FF4A4 7C05B1F6
	static scrAny IS_NEW_LOAD_SCENE_ACTIVE() { return NativeInvoke::Invoke<scrAny>(0xA41A05B6CB741B85); } // A41A05B6CB741B85 AD234B7F
	static BOOL IS_NEW_LOAD_SCENE_LOADED() { return NativeInvoke::Invoke<BOOL>(0x01B8247A7A8B9AD1); } // 01B8247A7A8B9AD1 3ECD839F
	static BOOL _0x71E7B2E657449AAD() { return NativeInvoke::Invoke<BOOL>(0x71E7B2E657449AAD); } // 71E7B2E657449AAD EAA51103
	static void START_PLAYER_SWITCH(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0xFAA23F2CBA159D67, p0, p1, p2, p3); } // FAA23F2CBA159D67 0829E975
	static void STOP_PLAYER_SWITCH() { NativeInvoke::Invoke<scrVoid>(0x95C0A5BBDC189AA1); } // 95C0A5BBDC189AA1 2832C010
	static BOOL STOP_PLAYER_REMAIN_ARCADE() { return NativeInvoke::Invoke<BOOL>(0xD9D2CFFF49FAB35F); } // D9D2CFFF49FAB35F 56135ACC
	static scrAny GET_PLAYER_SWITCH_TYPE() { return NativeInvoke::Invoke<scrAny>(0xB3C94A90D9FC9E62); } // B3C94A90D9FC9E62 280DC015
	static scrAny GET_IDEAL_PLAYER_SWITCH_TYPE(float p0, float p1, float p2, float p3, float p4, float p5) { return NativeInvoke::Invoke<scrAny>(0xB5D7B26B45720E05, p0, p1, p2, p3, p4, p5); } // B5D7B26B45720E05 D5A450F1
	static scrAny GET_PLAYER_SWITCH_STATE() { return NativeInvoke::Invoke<scrAny>(0x470555300D10B2A5); } // 470555300D10B2A5 39A0E1F2
	static scrAny GET_PLAYER_SHORT_SWITCH_STATE() { return NativeInvoke::Invoke<scrAny>(0x20F898A5D9782800); } // 20F898A5D9782800 9B7BA38F
	static void _0x5F2013F8BC24EE69(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x5F2013F8BC24EE69, p0); } // 5F2013F8BC24EE69 F0BD420D
	static scrAny _0x78C0D93253149435() { return NativeInvoke::Invoke<scrAny>(0x78C0D93253149435); } // 78C0D93253149435 02BA7AC2
	static void _0xC208B673CE446B61(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, scrAny p8) { NativeInvoke::Invoke<scrVoid>(0xC208B673CE446B61, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // C208B673CE446B61 47352E14
	static void _0x0FDE9DBFC0A6BC65(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x0FDE9DBFC0A6BC65, p0); } // 0FDE9DBFC0A6BC65 279077B0
	static void _0x43D1680C6D19A8E9() { NativeInvoke::Invoke<scrVoid>(0x43D1680C6D19A8E9); } // 43D1680C6D19A8E9 55CB21F9
	static void _0x74DE2E8739086740() { NativeInvoke::Invoke<scrVoid>(0x74DE2E8739086740); } // 74DE2E8739086740 1084F2F4
	static void _0x8E2A065ABDAE6994() { NativeInvoke::Invoke<scrVoid>(0x8E2A065ABDAE6994); } // 8E2A065ABDAE6994 5B1E995D
	static void _0xAD5FDF34B81BFE79() { NativeInvoke::Invoke<scrVoid>(0xAD5FDF34B81BFE79); } // AD5FDF34B81BFE79 4B4B9A13
	static BOOL _0xDFA80CB25D0A19B3() { return NativeInvoke::Invoke<BOOL>(0xDFA80CB25D0A19B3); } // DFA80CB25D0A19B3 408F7148
	static void _0xAAB3200ED59016BC(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xAAB3200ED59016BC, p0, p1, p2); } // AAB3200ED59016BC FB4D062D
	static void _0xD8295AF639FD9CB8(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xD8295AF639FD9CB8, p0); } // D8295AF639FD9CB8 2349373B
	static scrAny _0x933BBEEB8C61B5F4() { return NativeInvoke::Invoke<scrAny>(0x933BBEEB8C61B5F4); } // 933BBEEB8C61B5F4 74C16879
	static scrAny SET_PLAYER_INVERTED_UP() { return NativeInvoke::Invoke<scrAny>(0x08C2D6C52A3104BB); } // 08C2D6C52A3104BB 569847E3
	static scrAny _0x5B48A06DD0E792A5() { return NativeInvoke::Invoke<scrAny>(0x5B48A06DD0E792A5); } // 5B48A06DD0E792A5 C7A3D279
	static BOOL DESTROY_PLAYER_IN_PAUSE_MENU() { return NativeInvoke::Invoke<BOOL>(0x5B74EA8CFD5E3E7E); } // 5B74EA8CFD5E3E7E 90F64284
	static void _0x1E9057A74FD73E23() { NativeInvoke::Invoke<scrVoid>(0x1E9057A74FD73E23); } // 1E9057A74FD73E23
	static float _0x0C15B0E443B2349D() { return NativeInvoke::Invoke<float>(0x0C15B0E443B2349D); } // 0C15B0E443B2349D 7154B6FD
	static void _0xA76359FC80B2438E(float p0) { NativeInvoke::Invoke<scrVoid>(0xA76359FC80B2438E, p0); } // A76359FC80B2438E E5612C1A
	static void _0xBED8CA5FF5E04113(float p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0xBED8CA5FF5E04113, p0, p1, p2, p3); } // BED8CA5FF5E04113 9CD6A451
	static void _0x472397322E92A856() { NativeInvoke::Invoke<scrVoid>(0x472397322E92A856); } // 472397322E92A856 4267DA87
	static void _0x40AEFD1A244741F2(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x40AEFD1A244741F2, p0); } // 40AEFD1A244741F2 9FA4AF99
	static void _0x03F1A106BDA7DD3E() { NativeInvoke::Invoke<scrVoid>(0x03F1A106BDA7DD3E); } // 03F1A106BDA7DD3E
	static void _0x95A7DABDDBB78AE7(scrAny *p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x95A7DABDDBB78AE7, p0, p1); } // 95A7DABDDBB78AE7 9EF0A9CF
	static void _0x63EB2B972A218CAC() { NativeInvoke::Invoke<scrVoid>(0x63EB2B972A218CAC); } // 63EB2B972A218CAC F2CDD6A8
	static BOOL _0xFB199266061F820A() { return NativeInvoke::Invoke<BOOL>(0xFB199266061F820A); } // FB199266061F820A 17B0A1CD
	static void _0xF4A0DADB70F57FA6() { NativeInvoke::Invoke<scrVoid>(0xF4A0DADB70F57FA6); } // F4A0DADB70F57FA6 3DA7AA5D
	static scrAny _0x5068F488DDB54DD8() { return NativeInvoke::Invoke<scrAny>(0x5068F488DDB54DD8); } // 5068F488DDB54DD8 DAB4BAC0
	static void PREFETCH_SRL(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x3D245789CE12982C, p0); } // 3D245789CE12982C 37BE2FBB
	static BOOL IS_SRL_LOADED() { return NativeInvoke::Invoke<BOOL>(0xD0263801A4C5B0BB); } // D0263801A4C5B0BB 670FA2A6
	static void BEGIN_SRL() { NativeInvoke::Invoke<scrVoid>(0x9BADDC94EF83B823); } // 9BADDC94EF83B823 24F49427
	static void END_SRL() { NativeInvoke::Invoke<scrVoid>(0x0A41540E63C9EE17); } // 0A41540E63C9EE17 1977C56A
	static void SET_SRL_TIME(float p0) { NativeInvoke::Invoke<scrVoid>(0xA74A541C6884E7B8, p0); } // A74A541C6884E7B8 30F8A487
	static void _0xEF39EE20C537E98C(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0xEF39EE20C537E98C, p0, p1, p2, p3, p4, p5); } // EF39EE20C537E98C 814D0752
	static void _0xBEB2D9A1D9A8F55A(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0xBEB2D9A1D9A8F55A, p0, p1, p2, p3); } // BEB2D9A1D9A8F55A 62F02485
	static void _0x20C6C7E4EB082A7F(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x20C6C7E4EB082A7F, p0); } // 20C6C7E4EB082A7F A6459CAA
	static void _0xF8155A7F03DDFC8E(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xF8155A7F03DDFC8E, p0); } // F8155A7F03DDFC8E F8F515E4
	static void SET_HD_AREA(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0xB85F26619073E775, p0, p1, p2, p3); } // B85F26619073E775 80BAA035
	static void CLEAR_HD_AREA() { NativeInvoke::Invoke<scrVoid>(0xCE58B1CFB9290813); } // CE58B1CFB9290813 7CAC6FA0
	static void _0xB5A4DB34FE89B88A() { NativeInvoke::Invoke<scrVoid>(0xB5A4DB34FE89B88A); } // B5A4DB34FE89B88A E243B2AF
	static void _0xCCE26000E9A6FAD7() { NativeInvoke::Invoke<scrVoid>(0xCCE26000E9A6FAD7); } // CCE26000E9A6FAD7 897A510F
	static BOOL _0x0BC3144DEB678666(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x0BC3144DEB678666, p0); } // 0BC3144DEB678666 C0E83320
	static void _0xF086AD9354FAC3A3(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xF086AD9354FAC3A3, p0); } // F086AD9354FAC3A3 1C576388
	static float _0x3D3D8B3BE5A83D35() { return NativeInvoke::Invoke<float>(0x3D3D8B3BE5A83D35); } // 3D3D8B3BE5A83D35 3E9C4CBE
}

namespace SCRIPT
{
	static void REQUEST_SCRIPT(char *p0) { NativeInvoke::Invoke<scrVoid>(0x6EB5F71AA68F2E8E, p0); } // 6EB5F71AA68F2E8E E26B2666
	static void SET_SCRIPT_AS_NO_LONGER_NEEDED(char *p0) { NativeInvoke::Invoke<scrVoid>(0xC90D2DCACD56184C, p0); } // C90D2DCACD56184C 6FCB7795
	static BOOL HAS_SCRIPT_LOADED(char *p0) { return NativeInvoke::Invoke<BOOL>(0xE6CC9F3BA0FB9EF1, p0); } // E6CC9F3BA0FB9EF1 5D67F751
	static BOOL DOES_SCRIPT_EXIST(char *p0) { return NativeInvoke::Invoke<BOOL>(0xFC04745FBE67C19A, p0); } // FC04745FBE67C19A DEAB87AB
	static void _0xD62A67D26D9653E6(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xD62A67D26D9653E6, p0); } // D62A67D26D9653E6 1C68D9DC
	static void _0xC5BC038960E9DB27(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xC5BC038960E9DB27, p0); } // C5BC038960E9DB27 96C26F66
	static BOOL _0x5F0F0C783EB16C04(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x5F0F0C783EB16C04, p0); } // 5F0F0C783EB16C04 06674818
	static void TERMINATE_THREAD(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xC8B189ED9138BCD4, p0); } // C8B189ED9138BCD4 253FD520
	static BOOL IS_THREAD_ACTIVE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x46E9AE36D8FA6417, p0); } // 46E9AE36D8FA6417 78D7A5A0
	static scrAny _0x05A42BA9FC8DA96B(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x05A42BA9FC8DA96B, p0); } // 05A42BA9FC8DA96B BE7ACD89
	static void _0xDADFADA5A20143A8() { NativeInvoke::Invoke<scrVoid>(0xDADFADA5A20143A8); } // DADFADA5A20143A8 BB4E2F66
	static scrAny _0x30B4FA1C82DD4B9F() { return NativeInvoke::Invoke<scrAny>(0x30B4FA1C82DD4B9F); } // 30B4FA1C82DD4B9F 1E28B28F
	static scrAny GET_ID_OF_THIS_THREAD() { return NativeInvoke::Invoke<scrAny>(0xC30338E8088E2E21); } // C30338E8088E2E21 DE524830
	static void TERMINATE_THIS_THREAD() { NativeInvoke::Invoke<scrVoid>(0x1090044AD1DA76FA); } // 1090044AD1DA76FA 3CD9CBB7
	static scrAny _0x2C83A9DA6BFFC4F9(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x2C83A9DA6BFFC4F9, p0); } // 2C83A9DA6BFFC4F9 029D3841
	static scrAny GET_THIS_SCRIPT_NAME() { return NativeInvoke::Invoke<scrAny>(0x442E0A7EDE4A738A); } // 442E0A7EDE4A738A A40FD5D9
	static scrAny _0x8A1C8B1738FFE87E() { return NativeInvoke::Invoke<scrAny>(0x8A1C8B1738FFE87E); } // 8A1C8B1738FFE87E 2BEE1F45
	static scrAny GET_NUMBER_OF_EVENTS(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x5F92A689A06620AA, p0); } // 5F92A689A06620AA A3525D60
	static BOOL GET_EVENT_EXISTS(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x936E6168A9BCEDB5, p0, p1); } // 936E6168A9BCEDB5 A1B447B5
	static scrAny GET_EVENT_AT_INDEX(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xD8F66A3A60C62153, p0, p1); } // D8F66A3A60C62153 B49C1442
	static BOOL GET_EVENT_DATA(scrAny p0, scrAny p1, scrAny *p2, scrAny p3) { return NativeInvoke::Invoke<BOOL>(0x2902843FCD2B2D79, p0, p1, p2, p3); } // 2902843FCD2B2D79 4280F92F
	static void TRIGGER_SCRIPT_EVENT(scrAny p0, scrAny *p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x5AE99C571D5BBE5D, p0, p1, p2, p3); } // 5AE99C571D5BBE5D 54763B35
	static void SHUTDOWN_LOADING_SCREEN() { NativeInvoke::Invoke<scrVoid>(0x078EBE9809CCD637); } // 078EBE9809CCD637 A2826D17
	static void SET_NO_LOADING_SCREEN(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x5262CC1995D07E09, p0); } // 5262CC1995D07E09 C8055034
	static void _0xB1577667C3708F9B() { NativeInvoke::Invoke<scrVoid>(0xB1577667C3708F9B); } // B1577667C3708F9B B03BCCDF
}

namespace UI
{
	static void _0xABA17D7CE615ADBF(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xABA17D7CE615ADBF, p0); } // ABA17D7CE615ADBF CB7C8994
	static void _0xBD12F8228410D9B4(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xBD12F8228410D9B4, p0); } // BD12F8228410D9B4 903F5EE4
	static void _0x10D373323E5B9C0D() { NativeInvoke::Invoke<scrVoid>(0x10D373323E5B9C0D); } // 10D373323E5B9C0D 94119534
	static void _0xC65AB383CD91DF98() { NativeInvoke::Invoke<scrVoid>(0xC65AB383CD91DF98); } // C65AB383CD91DF98 71077FBD
	static BOOL _0xD422FCC5F239A915() { return NativeInvoke::Invoke<BOOL>(0xD422FCC5F239A915); } // D422FCC5F239A915 B8B3A5D0
	static void _0xAAE7CE1D63167423() { NativeInvoke::Invoke<scrVoid>(0xAAE7CE1D63167423); } // AAE7CE1D63167423
	static void _0x8DB8CFFD58B62552(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x8DB8CFFD58B62552, p0); } // 8DB8CFFD58B62552
	static void _0x6F1554B0CC2089FA(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x6F1554B0CC2089FA, p0); } // 6F1554B0CC2089FA A7C8594B
	static void _0x55598D21339CB998(float p0) { NativeInvoke::Invoke<scrVoid>(0x55598D21339CB998, p0); } // 55598D21339CB998 1DA7E41A
	static void _0x25F87B30C382FCA7() { NativeInvoke::Invoke<scrVoid>(0x25F87B30C382FCA7); } // 25F87B30C382FCA7 1E63088A
	static void _0xA8FDB297A8D25FBA() { NativeInvoke::Invoke<scrVoid>(0xA8FDB297A8D25FBA); } // A8FDB297A8D25FBA 5205C6F5
	static void _0xBE4390CB40B3E627(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xBE4390CB40B3E627, p0); } // BE4390CB40B3E627 ECA8ACB9
	static void _0xA13C11E1B5C06BFC() { NativeInvoke::Invoke<scrVoid>(0xA13C11E1B5C06BFC); } // A13C11E1B5C06BFC 520FCB6D
	static void _0x583049884A2EEE3C() { NativeInvoke::Invoke<scrVoid>(0x583049884A2EEE3C); } // 583049884A2EEE3C C8BAB2F2
	static void _0xFDB423997FA30340() { NativeInvoke::Invoke<scrVoid>(0xFDB423997FA30340); } // FDB423997FA30340 4D0449C6
	static void _0xE1CD1E48E025E661() { NativeInvoke::Invoke<scrVoid>(0xE1CD1E48E025E661); } // E1CD1E48E025E661 D3F40140
	static scrAny _0xA9CBFD40B3FA3010() { return NativeInvoke::Invoke<scrAny>(0xA9CBFD40B3FA3010); } // A9CBFD40B3FA3010 C5223796
	static void _0xD4438C0564490E63() { NativeInvoke::Invoke<scrVoid>(0xD4438C0564490E63); } // D4438C0564490E63 709B4BCB
	static void _0xB695E2CD0A2DA9EE() { NativeInvoke::Invoke<scrVoid>(0xB695E2CD0A2DA9EE); } // B695E2CD0A2DA9EE 4A4A40A4
	static scrAny _0x82352748437638CA() { return NativeInvoke::Invoke<scrAny>(0x82352748437638CA); } // 82352748437638CA 294405D4
	static void _0x56C8B608CFD49854() { NativeInvoke::Invoke<scrVoid>(0x56C8B608CFD49854); } // 56C8B608CFD49854 F881AB87
	static void _0xADED7F5748ACAFE6() { NativeInvoke::Invoke<scrVoid>(0xADED7F5748ACAFE6); } // ADED7F5748ACAFE6 1D6859CA
	static void _0x17430B918701C342(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x17430B918701C342, p0, p1, p2, p3); } // 17430B918701C342 CF14D7F2
	static void _0x17AD8C9706BDD88A(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x17AD8C9706BDD88A, p0); } // 17AD8C9706BDD88A 24A97AF8
	static void _0x4A0C7C9BB10ABB36(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x4A0C7C9BB10ABB36, p0); } // 4A0C7C9BB10ABB36 44018EDB
	static void _0xFDD85225B2DEA55E() { NativeInvoke::Invoke<scrVoid>(0xFDD85225B2DEA55E); } // FDD85225B2DEA55E A4524B23
	static void _0xFDEC055AB549E328() { NativeInvoke::Invoke<scrVoid>(0xFDEC055AB549E328); } // FDEC055AB549E328 AFA1148B
	static void _0x80FE4F3AB4E1B62A() { NativeInvoke::Invoke<scrVoid>(0x80FE4F3AB4E1B62A); } // 80FE4F3AB4E1B62A 3CD4307C
	static void _0x317EBA71D7543F52(scrAny *p0, scrAny *p1, scrAny *p2, scrAny *p3) { NativeInvoke::Invoke<scrVoid>(0x317EBA71D7543F52, p0, p1, p2, p3); } // 317EBA71D7543F52
	static void _SET_NOTIFICATION_TEXT_ENTRY(char *type) { NativeInvoke::Invoke<scrVoid>(0x202709F4C58A0424, type); } // 202709F4C58A0424 574EE85C
	static scrAny _0x2B7E9A4EAAA93C89(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6) { return NativeInvoke::Invoke<scrAny>(0x2B7E9A4EAAA93C89, p0, p1, p2, p3, p4, p5, p6); } // 2B7E9A4EAAA93C89 ED130FA1
	static scrAny _0x1CCD9A37359072CF(scrAny *p0, scrAny *p1, BOOL p2, scrAny p3, scrAny *p4, scrAny *p5) { return NativeInvoke::Invoke<scrAny>(0x1CCD9A37359072CF, p0, p1, p2, p3, p4, p5); } // 1CCD9A37359072CF E7E3C98B
	static scrAny _0x1E6611149DB3DB6B(scrAny *p0, scrAny *p1, BOOL p2, scrAny p3, scrAny *p4, scrAny *p5, float p6) { return NativeInvoke::Invoke<scrAny>(0x1E6611149DB3DB6B, p0, p1, p2, p3, p4, p5, p6); } // 1E6611149DB3DB6B 0EB382B7
	static scrAny _0x5CBF7BADE20DB93E(scrAny *p0, scrAny *p1, BOOL p2, scrAny p3, scrAny *p4, scrAny *p5, float p6, scrAny *p7) { return NativeInvoke::Invoke<scrAny>(0x5CBF7BADE20DB93E, p0, p1, p2, p3, p4, p5, p6, p7); } // 5CBF7BADE20DB93E 3E807FE3
	static scrAny _0x531B84E7DA981FB6(scrAny *p0, scrAny *p1, BOOL p2, scrAny p3, scrAny *p4, scrAny *p5, float p6, scrAny *p7, scrAny p8) { return NativeInvoke::Invoke<scrAny>(0x531B84E7DA981FB6, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 531B84E7DA981FB6 DEB491C8
	static scrAny _DRAW_NOTIFICATION(BOOL blink, BOOL p1) { return NativeInvoke::Invoke<scrAny>(0x2ED7843F8F801023, blink, p1); } // 2ED7843F8F801023 08F7AF78
	static scrAny _0x44FA03975424A0EE(BOOL p0, BOOL p1) { return NativeInvoke::Invoke<scrAny>(0x44FA03975424A0EE, p0, p1); } // 44FA03975424A0EE 57B8D0D4
	static scrAny _0x378E809BF61EC840(BOOL p0, BOOL p1) { return NativeInvoke::Invoke<scrAny>(0x378E809BF61EC840, p0, p1); } // 378E809BF61EC840 02BCAF9B
	static scrAny _0xAA295B6F28BD587D(scrAny *p0, scrAny *p1, scrAny p2, scrAny p3, scrAny *p4) { return NativeInvoke::Invoke<scrAny>(0xAA295B6F28BD587D, p0, p1, p2, p3, p4); } // AA295B6F28BD587D 02DED2B8
	static scrAny _0x97C9E4E7024A8F2C(BOOL p0, BOOL p1, scrAny *p2, scrAny p3, BOOL p4, BOOL p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9) { return NativeInvoke::Invoke<scrAny>(0x97C9E4E7024A8F2C, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 97C9E4E7024A8F2C A9CCEF66
	static scrAny _0x137BC35589E34E1E(BOOL p0, BOOL p1, scrAny *p2, scrAny p3, BOOL p4, BOOL p5, scrAny p6, scrAny *p7, scrAny p8, scrAny p9, scrAny p10) { return NativeInvoke::Invoke<scrAny>(0x137BC35589E34E1E, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 137BC35589E34E1E 88B9B909
	static scrAny _0x33EE12743CCD6343(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0x33EE12743CCD6343, p0, p1, p2); } // 33EE12743CCD6343 E05E7052
	static scrAny _0xC8F3AAF93D0600BF(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0xC8F3AAF93D0600BF, p0, p1, p2, p3); } // C8F3AAF93D0600BF 4FA43BA4
	static scrAny _0x7AE0589093A2E088(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { return NativeInvoke::Invoke<scrAny>(0x7AE0589093A2E088, p0, p1, p2, p3, p4, p5); } // 7AE0589093A2E088 8C90D22F
	static scrAny _0xF020C96915705B3A(BOOL p0, BOOL p1) { return NativeInvoke::Invoke<scrAny>(0xF020C96915705B3A, p0, p1); } // F020C96915705B3A 8E319AB8
	static scrAny _0xB6871B0555B02996(scrAny *p0, scrAny *p1, scrAny p2, scrAny *p3, scrAny *p4, scrAny p5) { return NativeInvoke::Invoke<scrAny>(0xB6871B0555B02996, p0, p1, p2, p3, p4, p5); } // B6871B0555B02996 5E93FBFA
	static void _0xB87A37EEB7FAA67D(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xB87A37EEB7FAA67D, p0); } // B87A37EEB7FAA67D F42C43C7
	static void _0x9D77056A530643F6(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x9D77056A530643F6, p0, p1); } // 9D77056A530643F6 38F82261
	static void _0x853648FD1063A213(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x853648FD1063A213, p0); } // 853648FD1063A213 DD524A11
	static BOOL _0x8A9BA1AB3E237613() { return NativeInvoke::Invoke<BOOL>(0x8A9BA1AB3E237613); } // 8A9BA1AB3E237613 672EFB45
	static void _SET_TEXT_ENTRY(char *p0) { NativeInvoke::Invoke<scrVoid>(0x25FBB336DF1804CB, p0); } // 25FBB336DF1804CB 3E35563E
	static void _DRAW_TEXT(float x, float y) { NativeInvoke::Invoke<scrVoid>(0xCD015E5BB0D96A57, x, y); } // CD015E5BB0D96A57 6F8350CE
	static void _0x54CE8AC98E120CAB(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x54CE8AC98E120CAB, p0); } // 54CE8AC98E120CAB 51E7A037
	static float _0x85F061DA64ED2F67(BOOL p0) { return NativeInvoke::Invoke<float>(0x85F061DA64ED2F67, p0); } // 85F061DA64ED2F67 D12A643A
	static void _0x521FB041D93DD0E4(char *p0) { NativeInvoke::Invoke<scrVoid>(0x521FB041D93DD0E4, p0); } // 521FB041D93DD0E4 94B82066
	static scrAny _0x9040DFB09BE75706(float p0, float p1) { return NativeInvoke::Invoke<scrAny>(0x9040DFB09BE75706, p0, p1); } // 9040DFB09BE75706 AA318785
	static void _0x8509B634FBE7DA11(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x8509B634FBE7DA11, p0); } // 8509B634FBE7DA11 B245FC10
	static void _0x238FFE5C7B0498A6(scrAny p0, BOOL p1, BOOL p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x238FFE5C7B0498A6, p0, p1, p2, p3); } // 238FFE5C7B0498A6 B59B530D
	static void _0x0A24DA3A41B718F5(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x0A24DA3A41B718F5, p0); } // 0A24DA3A41B718F5 00E20F2D
	static BOOL _0x10BDDBFC529428DD(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x10BDDBFC529428DD, p0); } // 10BDDBFC529428DD F63A13EC
	static void _0xF9113A30DE5C6670(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xF9113A30DE5C6670, p0); } // F9113A30DE5C6670 F4C211F6
	static void _0xBC38B49BCB83BC9B(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xBC38B49BCB83BC9B, p0); } // BC38B49BCB83BC9B E8E59820
	static void _0x23D69E0465570028(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x23D69E0465570028, p0); } // 23D69E0465570028 0E103475
	static void _0xCFDBDF5AE59BA0F4(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xCFDBDF5AE59BA0F4, p0); } // CFDBDF5AE59BA0F4 2944A6C5
	static void _0xE124FA80A759019C(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xE124FA80A759019C, p0); } // E124FA80A759019C 550665AE
	static void _0xFCC75460ABA29378() { NativeInvoke::Invoke<scrVoid>(0xFCC75460ABA29378); } // FCC75460ABA29378 67785AF2
	static void _0x8F9EE5687F8EECCD(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x8F9EE5687F8EECCD, p0); } // 8F9EE5687F8EECCD BF855650
	static void _0xA86911979638106F(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA86911979638106F, p0); } // A86911979638106F 6E7FDA1C
	static void ADD_TEXT_COMPONENT_INTEGER(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x03B504CF259931BC, p0); } // 03B504CF259931BC FE272A57
	static void ADD_TEXT_COMPONENT_FLOAT(float p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xE7DCB5B874BCD96E, p0, p1); } // E7DCB5B874BCD96E 24D78013
	static void _0xC63CD5D2920ACBE7(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xC63CD5D2920ACBE7, p0); } // C63CD5D2920ACBE7 DCE05406
	static void _0x17299B63C7683A2B(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x17299B63C7683A2B, p0); } // 17299B63C7683A2B 150E03B6
	static void _0x80EAD8E2E1D5D52E(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x80EAD8E2E1D5D52E, p0); } // 80EAD8E2E1D5D52E 5DE98F0A
	static void _ADD_TEXT_COMPONENT_STRING(char *p0) { NativeInvoke::Invoke<scrVoid>(0x6C188BE134E074AA, p0); } // 6C188BE134E074AA 27A244D8
	static void ADD_TEXT_COMPONENT_SUBSTRING_TIME(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x1115F16B8AB9E8BF, p0, p1); } // 1115F16B8AB9E8BF 135B3CD0
	static void _0x0E4C749FF9DE9CC4(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x0E4C749FF9DE9CC4, p0, p1); } // 0E4C749FF9DE9CC4 12929BDF
	static void _0x761B77454205A61D(scrAny *p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x761B77454205A61D, p0, p1); } // 761B77454205A61D 65E1D404
	static void _0x94CF4AC034C9C986(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x94CF4AC034C9C986, p0); } // 94CF4AC034C9C986 C736999E
	static void _0x5F68520888E69014(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x5F68520888E69014, p0); } // 5F68520888E69014 0829A799
	static void _0x39BBF623FC803EAC(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x39BBF623FC803EAC, p0); } // 39BBF623FC803EAC 6F1A1901
	static scrAny _0x169BD9382084C8C0(scrAny *p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0x169BD9382084C8C0, p0, p1, p2); } // 169BD9382084C8C0 34A396EE
	static scrAny _0xB2798643312205C5(scrAny *p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0xB2798643312205C5, p0, p1, p2, p3); } // B2798643312205C5 0183A66C
	static scrAny _0xCE94AEBA5D82908A(scrAny *p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0xCE94AEBA5D82908A, p0, p1, p2); } // CE94AEBA5D82908A FA6373BB
	static scrAny _0x7B5280EBA9840C72(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0x7B5280EBA9840C72, p0); } // 7B5280EBA9840C72 95C4B5AD
	static void CLEAR_PRINTS() { NativeInvoke::Invoke<scrVoid>(0xCC33FA791322B9D9); } // CC33FA791322B9D9 216CB1C5
	static void CLEAR_BRIEF() { NativeInvoke::Invoke<scrVoid>(0x9D292F73ADBD9313); } // 9D292F73ADBD9313 9F75A929
	static void CLEAR_ALL_HELP_MESSAGES() { NativeInvoke::Invoke<scrVoid>(0x6178F68A87A4D3A0); } // 6178F68A87A4D3A0 9E5D9198
	static void CLEAR_THIS_PRINT(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xCF708001E1E536DD, p0); } // CF708001E1E536DD 06878327
	static void CLEAR_SMALL_PRINTS() { NativeInvoke::Invoke<scrVoid>(0x2CEA2839313C09AC); } // 2CEA2839313C09AC A869A238
	static BOOL DOES_TEXT_BLOCK_EXIST(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x1C7302E725259789, p0); } // 1C7302E725259789 96F74838
	static void REQUEST_ADDITIONAL_TEXT(scrAny *p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x71A78003C8E71424, p0, p1); } // 71A78003C8E71424 9FA9175B
	static void _0x6009F9F1AE90D8A6(scrAny *p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x6009F9F1AE90D8A6, p0, p1); } // 6009F9F1AE90D8A6 F4D27EBE
	static BOOL HAS_ADDITIONAL_TEXT_LOADED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x02245FE4BED318B8, p0); } // 02245FE4BED318B8 B0E56045
	static void CLEAR_ADDITIONAL_TEXT(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x2A179DF17CCF04CD, p0, p1); } // 2A179DF17CCF04CD 518141E0
	static BOOL IS_STREAMING_ADDITIONAL_TEXT(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x8B6817B71B85EBF0, p0); } // 8B6817B71B85EBF0 F079E4EB
	static BOOL HAS_THIS_ADDITIONAL_TEXT_LOADED(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xADBF060E2B30C5BC, p0, p1); } // ADBF060E2B30C5BC 80A52040
	static BOOL IS_MESSAGE_BEING_DISPLAYED() { return NativeInvoke::Invoke<BOOL>(0x7984C03AA5CC2F41); } // 7984C03AA5CC2F41 6A77FE8D
	static BOOL DOES_TEXT_LABEL_EXIST(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xAC09CA973C564252, p0); } // AC09CA973C564252 6ECAE560
	static scrAny GET_LENGTH_OF_STRING_WITH_THIS_TEXT_LABEL(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0x801BD273D3A23F74, p0); } // 801BD273D3A23F74 A4CA7BE5
	static scrAny GET_LENGTH_OF_LITERAL_STRING(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0xF030907CCBB8A9FD, p0); } // F030907CCBB8A9FD 99379D55
	static scrAny _0x43E4111189E54F0E(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0x43E4111189E54F0E, p0); } // 43E4111189E54F0E 7DBC0764
	static scrAny GET_STREET_NAME_FROM_HASH_KEY(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xD0EF8A959B8A4CB9, p0); } // D0EF8A959B8A4CB9 1E8E310C
	static BOOL IS_HUD_PREFERENCE_SWITCHED_ON() { return NativeInvoke::Invoke<BOOL>(0x1930DFA731813EC4); } // 1930DFA731813EC4 C3BC1B4F
	static BOOL IS_RADAR_PREFERENCE_SWITCHED_ON() { return NativeInvoke::Invoke<BOOL>(0x9EB6522EA68F22FE); } // 9EB6522EA68F22FE 14AEAA28
	static BOOL IS_SUBTITLE_PREFERENCE_SWITCHED_ON() { return NativeInvoke::Invoke<BOOL>(0xAD6DACA4BA53E0A4); } // AD6DACA4BA53E0A4 63BA19F5
	static void DISPLAY_HUD(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xA6294919E56FF02A, p0); } // A6294919E56FF02A D10E4E31
	static void _0x7669F9E39DC17063() { NativeInvoke::Invoke<scrVoid>(0x7669F9E39DC17063); } // 7669F9E39DC17063 C380AC85
	static void _0x402F9ED62087E898() { NativeInvoke::Invoke<scrVoid>(0x402F9ED62087E898); } // 402F9ED62087E898 C47AB1B0
	static void DISPLAY_RADAR(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xA0EBB943C300E693, p0); } // A0EBB943C300E693 52816BD4
	static scrAny IS_HUD_HIDDEN() { return NativeInvoke::Invoke<scrAny>(0xA86478C6958735C5); } // A86478C6958735C5 40BADA1D
	static scrAny IS_RADAR_HIDDEN() { return NativeInvoke::Invoke<scrAny>(0x157F93B036700462); } // 157F93B036700462 1AB3B954
	static scrAny _0xAF754F20EB5CD51A() { return NativeInvoke::Invoke<scrAny>(0xAF754F20EB5CD51A); } // AF754F20EB5CD51A
	static void SET_BLIP_ROUTE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x4F7D8A9BFB0B43E9, p0, p1); } // 4F7D8A9BFB0B43E9 3E160C90
	static void SET_BLIP_ROUTE_COLOUR(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x837155CD2F63DA09, p0, p1); } // 837155CD2F63DA09 DDE7C65C
	static void ADD_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x60296AF4BA14ABC5, p0); } // 60296AF4BA14ABC5 B58B25BD
	static void _0x57D760D55F54E071(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x57D760D55F54E071, p0); } // 57D760D55F54E071 9854485F
	static void RESPONDING_AS_TEMP(float p0) { NativeInvoke::Invoke<scrVoid>(0xBD12C5EEE184C337, p0); } // BD12C5EEE184C337 DCA3F423
	static void SET_RADAR_ZOOM(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x096EF57A0C999BBA, p0); } // 096EF57A0C999BBA 2A50D1A6
	static void _0xF98E4B3E56AFC7B1(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xF98E4B3E56AFC7B1, p0, p1); } // F98E4B3E56AFC7B1 25EC28C0
	static void _0xCB7CC0D58405AD41(float p0) { NativeInvoke::Invoke<scrVoid>(0xCB7CC0D58405AD41, p0); } // CB7CC0D58405AD41 09CF1CE5
	static void _0xD2049635DEB9C375() { NativeInvoke::Invoke<scrVoid>(0xD2049635DEB9C375); } // D2049635DEB9C375 E8D3A910
	static void GET_HUD_COLOUR(scrAny p0, scrAny *p1, scrAny *p2, scrAny *p3, scrAny *p4) { NativeInvoke::Invoke<scrVoid>(0x7C9C91AB74A0360F, p0, p1, p2, p3, p4); } // 7C9C91AB74A0360F 63F66A0B
	static void _0xD68A5FF8A3A89874(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0xD68A5FF8A3A89874, p0, p1, p2, p3); } // D68A5FF8A3A89874 0E41E45C
	static void _0x16A304E6CB2BFAB9(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x16A304E6CB2BFAB9, p0, p1, p2, p3); } // 16A304E6CB2BFAB9 6BE3ACA8
	static void _0x1CCC708F0F850613(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x1CCC708F0F850613, p0, p1); } // 1CCC708F0F850613 3B216749
	static void _0xF314CF4F0211894E(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0xF314CF4F0211894E, p0, p1, p2, p3, p4); } // F314CF4F0211894E F6E7E92B
	static void FLASH_ABILITY_BAR(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x02CFBA0C9E9275CE, p0); } // 02CFBA0C9E9275CE 3648960D
	static void SET_ABILITY_BAR_VALUE(float p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x9969599CCFF5D85E, p0, p1); } // 9969599CCFF5D85E 24E53FD8
	static void FLASH_WANTED_DISPLAY(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xA18AFB39081B6A1F, p0); } // A18AFB39081B6A1F 629F866B
	static float _0xDB88A37483346780(float p0, int p1) { return NativeInvoke::Invoke<float>(0xDB88A37483346780, p0, p1); } // DB88A37483346780 3330175B
	static void SET_TEXT_SCALE(float p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x07C837F9A01C34C9, p0, p1); } // 07C837F9A01C34C9 B6E15B23
	static void SET_TEXT_COLOUR(int p0, int p1, int p2, int p3) { NativeInvoke::Invoke<scrVoid>(0xBE6B23FFA53FB442, p0, p1, p2, p3); } // BE6B23FFA53FB442 E54DD2C8
	static void SET_TEXT_CENTRE(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xC02F4DBFB51D988B, p0); } // C02F4DBFB51D988B E26D39A1
	static void SET_TEXT_RIGHT_JUSTIFY(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x6B3C4650BC8BEE47, p0); } // 6B3C4650BC8BEE47 45B60520
	static void _0x4E096588B13FFECA(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x4E096588B13FFECA, p0); } // 4E096588B13FFECA 68CDFA60
	static void SET_TEXT_WRAP(float p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x63145D9C883A1A70, p0, p1); } // 63145D9C883A1A70 6F60AB54
	static void SET_TEXT_LEADING(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xA50ABC31E3CDFAFF, p0); } // A50ABC31E3CDFAFF 98CE21D4
	static void SET_TEXT_PROPORTIONAL(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x038C1F517D7FDCF8, p0); } // 038C1F517D7FDCF8 F49D8A08
	static void SET_TEXT_FONT(int p0) { NativeInvoke::Invoke<scrVoid>(0x66E0276CC5F6B9DA, p0); } // 66E0276CC5F6B9DA 80BC530D
	static void SET_TEXT_DROP_SHADOW() { NativeInvoke::Invoke<scrVoid>(0x1CA3E9EAC9D93E5E); } // 1CA3E9EAC9D93E5E E2A11511
	static void SET_TEXT_DROPSHADOW(int p0, int p1, int p2, int p3, int p4) { NativeInvoke::Invoke<scrVoid>(0x465C84BC39F1C351, p0, p1, p2, p3, p4); } // 465C84BC39F1C351 E6587517
	static void SET_TEXT_OUTLINE() { NativeInvoke::Invoke<scrVoid>(0x2513DFB0FB8400FE); } // 2513DFB0FB8400FE C753412F
	static void SET_TEXT_EDGE(int p0, int p1, int p2, int p3, int p4) { NativeInvoke::Invoke<scrVoid>(0x441603240D202FA6, p0, p1, p2, p3, p4); } // 441603240D202FA6 3F1A5DAB
	static void SET_TEXT_RENDER_ID(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x5F15302936E07111, p0); } // 5F15302936E07111 C5C3B7F3
	static scrAny GET_DEFAULT_SCRIPT_RENDERTARGET_RENDER_ID() { return NativeInvoke::Invoke<scrAny>(0x52F0982D7FD156B6); } // 52F0982D7FD156B6 8188935F
	static BOOL REGISTER_NAMED_RENDERTARGET(scrAny *p0, BOOL p1) { return NativeInvoke::Invoke<BOOL>(0x57D9C12635E25CE3, p0, p1); } // 57D9C12635E25CE3 FAE5D6F0
	static BOOL IS_NAMED_RENDERTARGET_REGISTERED(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x78DCDC15C9F116B4, p0); } // 78DCDC15C9F116B4 284057F5
	static BOOL RELEASE_NAMED_RENDERTARGET(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xE9F6FFE837354DD4, p0); } // E9F6FFE837354DD4 D3F6C892
	static void LINK_NAMED_RENDERTARGET(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xF6C09E276AEB3F2D, p0); } // F6C09E276AEB3F2D 6844C4B9
	static scrAny GET_NAMED_RENDERTARGET_RENDER_ID(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0x1A6478B61C6BDC3B, p0); } // 1A6478B61C6BDC3B F9D7A401
	static BOOL IS_NAMED_RENDERTARGET_LINKED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x113750538FA31298, p0); } // 113750538FA31298 8B52601F
	static void CLEAR_HELP(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x8DFCED7A656F8802, p0); } // 8DFCED7A656F8802 E6D85741
	static BOOL IS_HELP_MESSAGE_ON_SCREEN() { return NativeInvoke::Invoke<BOOL>(0xDAD37F45428801AE); } // DAD37F45428801AE 4B3C9CA9
	static BOOL _0x214CD562A939246A() { return NativeInvoke::Invoke<BOOL>(0x214CD562A939246A); } // 214CD562A939246A 812CBE0E
	static BOOL IS_HELP_MESSAGE_BEING_DISPLAYED() { return NativeInvoke::Invoke<BOOL>(0x4D79439A6B55AC67); } // 4D79439A6B55AC67 A65F262A
	static BOOL IS_HELP_MESSAGE_FADING_OUT() { return NativeInvoke::Invoke<BOOL>(0x327EDEEEAC55C369); } // 327EDEEEAC55C369 3E50AE92
	static scrAny _0x4A9923385BDB9DAD() { return NativeInvoke::Invoke<scrAny>(0x4A9923385BDB9DAD); } // 4A9923385BDB9DAD 87871CE0
	static scrAny _GET_BLIP_INFO_ID_ITERATOR() { return NativeInvoke::Invoke<scrAny>(0x186E5D252FA50E7D); } // 186E5D252FA50E7D B9827942
	static scrAny GET_NUMBER_OF_ACTIVE_BLIPS() { return NativeInvoke::Invoke<scrAny>(0x9A3FF3DE163034E8); } // 9A3FF3DE163034E8 144020FA
	static scrAny GET_NEXT_BLIP_INFO_ID(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x14F96AA50D6FBEA7, p0); } // 14F96AA50D6FBEA7 9356E92F
	static scrAny GET_FIRST_BLIP_INFO_ID(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x1BEDE233E6CD2A1F, p0); } // 1BEDE233E6CD2A1F 64C0273D
	static scrVector3 GET_BLIP_INFO_ID_COORD(scrAny p0) { return NativeInvoke::Invoke<scrVector3>(0xFA7C7F0AADF25D09, p0); } // FA7C7F0AADF25D09 B7374A66
	static scrAny GET_BLIP_INFO_ID_DISPLAY(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x1E314167F701DC3B, p0); } // 1E314167F701DC3B D0FC19F4
	static scrAny GET_BLIP_INFO_ID_TYPE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xBE9B0959FFD0779B, p0); } // BE9B0959FFD0779B 501D7B4E
	static scrAny GET_BLIP_INFO_ID_ENTITY_INDEX(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x4BA4E2553AFEDC2C, p0); } // 4BA4E2553AFEDC2C A068C40B
	static scrAny GET_BLIP_INFO_ID_PICKUP_INDEX(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x9B6786E4C03DD382, p0); } // 9B6786E4C03DD382 86913D37
	static scrAny GET_BLIP_FROM_ENTITY(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xBC8DBDCA2436F7E8, p0); } // BC8DBDCA2436F7E8 005A2A47
	static scrAny ADD_BLIP_FOR_RADIUS(float p0, float p1, float p2, float p3) { return NativeInvoke::Invoke<scrAny>(0x46818D79B1F7499A, p0, p1, p2, p3); } // 46818D79B1F7499A 4626756C
	static scrAny ADD_BLIP_FOR_ENTITY(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x5CDE92C702A8FCE7, p0); } // 5CDE92C702A8FCE7 30822554
	static scrAny ADD_BLIP_FOR_PICKUP(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xBE339365C863BD36, p0); } // BE339365C863BD36 16693C3A
	static scrAny ADD_BLIP_FOR_COORD(float p0, float p1, float p2) { return NativeInvoke::Invoke<scrAny>(0x5A039BB0BCA604B6, p0, p1, p2); } // 5A039BB0BCA604B6 C6F43D0E
	static void _0x72DD432F3CDFC0EE(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x72DD432F3CDFC0EE, p0, p1, p2, p3, p4); } // 72DD432F3CDFC0EE BF25E7B2
	static void _0x60734CC207C9833C(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x60734CC207C9833C, p0); } // 60734CC207C9833C E7E1E32B
	static void SET_BLIP_COORDS(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0xAE2AF67E9D9AF65D, p0, p1, p2, p3); } // AE2AF67E9D9AF65D 680A34D4
	static scrVector3 GET_BLIP_COORDS(scrAny p0) { return NativeInvoke::Invoke<scrVector3>(0x586AFE3FF72D996E, p0); } // 586AFE3FF72D996E EF6FF47B
	static void SET_BLIP_SPRITE(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xDF735600A4696DAF, p0, p1); } // DF735600A4696DAF 8DBBB0B9
	static scrAny GET_BLIP_SPRITE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x1FC877464A04FC4F, p0); } // 1FC877464A04FC4F 72FF2E73
	static void SET_BLIP_NAME_FROM_TEXT_FILE(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xEAA0FFE120D92784, p0, p1); } // EAA0FFE120D92784 AC8A5461
	static void SET_BLIP_NAME_TO_PLAYER_NAME(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x127DE7B20C60A6A3, p0, p1); } // 127DE7B20C60A6A3 03A0B8F9
	static void SET_BLIP_ALPHA(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x45FF974EEE1C8734, p0, p1); } // 45FF974EEE1C8734 A791FCCD
	static scrAny GET_BLIP_ALPHA(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x970F608F0EE6C885, p0); } // 970F608F0EE6C885 297AF6C8
	static void SET_BLIP_FADE(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x2AEE8F8390D2298C, p0, p1, p2); } // 2AEE8F8390D2298C A5999031
	static void SET_BLIP_ROTATION(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xF87683CDF73C3F6E, p0, p1); } // F87683CDF73C3F6E 6B8F44FE
	static void SET_BLIP_FLASH_TIMER(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xD3CD6FD297AE87CC, p0, p1); } // D3CD6FD297AE87CC 8D5DF611
	static void SET_BLIP_FLASH_INTERVAL(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xAA51DB313C010A7E, p0, p1); } // AA51DB313C010A7E EAF67377
	static void SET_BLIP_COLOUR(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x03D7FB09E75D6B7E, p0, p1); } // 03D7FB09E75D6B7E BB3C5A41
	static void SET_BLIP_SECONDARY_COLOUR(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x14892474891E09EB, p0, p1, p2, p3); } // 14892474891E09EB C6384D32
	static scrAny GET_BLIP_COLOUR(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xDF729E8D20CF7327, p0); } // DF729E8D20CF7327 DD6A1E54
	static scrAny GET_BLIP_HUD_COLOUR(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x729B5F1EFBC0AAEE, p0); } // 729B5F1EFBC0AAEE E88B4BC2
	static BOOL IS_BLIP_SHORT_RANGE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xDA5F8727EB75B926, p0); } // DA5F8727EB75B926 1226765A
	static BOOL IS_BLIP_ON_MINIMAP(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xE41CA53051197A27, p0); } // E41CA53051197A27 258CBA3A
	static BOOL _0xDD2238F57B977751(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xDD2238F57B977751, p0); } // DD2238F57B977751 3E47F357
	static void _0x54318C915D27E4CE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x54318C915D27E4CE, p0, p1); } // 54318C915D27E4CE 43996428
	static void SET_BLIP_HIGH_DETAIL(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xE2590BC29220CEBB, p0, p1); } // E2590BC29220CEBB D5842BFF
	static void SET_BLIP_AS_MISSION_CREATOR_BLIP(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x24AC0137444F9FD5, p0, p1); } // 24AC0137444F9FD5 802FB686
	static BOOL IS_MISSION_CREATOR_BLIP(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x26F49BF3381D933D, p0); } // 26F49BF3381D933D 24ACC4E9
	static scrAny DISABLE_BLIP_NAME_FOR_VAR() { return NativeInvoke::Invoke<scrAny>(0x5C90988E7C8E1AF4); } // 5C90988E7C8E1AF4 FFD7476C
	static BOOL _0x4167EFE0527D706E() { return NativeInvoke::Invoke<BOOL>(0x4167EFE0527D706E); } // 4167EFE0527D706E C5EB849A
	static void _0xF1A6C18B35BCADE6(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xF1A6C18B35BCADE6, p0); } // F1A6C18B35BCADE6 A2CAAB4F
	static void SET_BLIP_FLASHES(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xB14552383D39CE3E, p0, p1); } // B14552383D39CE3E C0047F15
	static void SET_BLIP_FLASHES_ALTERNATE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x2E8D9498C56DD0D1, p0, p1); } // 2E8D9498C56DD0D1 1A81202B
	static BOOL IS_BLIP_FLASHING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xA5E41FD83AD6CEF0, p0); } // A5E41FD83AD6CEF0 52E111D7
	static void SET_BLIP_AS_SHORT_RANGE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xBE8BE4FE60E27B72, p0, p1); } // BE8BE4FE60E27B72 5C67725E
	static void SET_BLIP_SCALE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xD38744167B2FA257, p0, p1); } // D38744167B2FA257 1E6EC434
	static void SET_BLIP_PRIORITY(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xAE9FC9EF6A9FAC79, p0, p1); } // AE9FC9EF6A9FAC79 CE87DA6F
	static void SET_BLIP_DISPLAY(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x9029B2F3DA924928, p0, p1); } // 9029B2F3DA924928 2B521F91
	static void SET_BLIP_CATEGORY(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x234CDD44D996FD9A, p0, p1); } // 234CDD44D996FD9A EF72F533
	static void REMOVE_BLIP(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x86A652570E5F25DD, p0); } // 86A652570E5F25DD D8C3C1CD
	static void SET_BLIP_AS_FRIENDLY(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x6F6F290102C02AB4, p0, p1); } // 6F6F290102C02AB4 F290CFD8
	static void PULSE_BLIP(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x742D6FD43115AF73, p0); } // 742D6FD43115AF73 44253855
	static void SHOW_NUMBER_ON_BLIP(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xA3C0B359DCB848B6, p0, p1); } // A3C0B359DCB848B6 7BFC66C6
	static void HIDE_NUMBER_ON_BLIP(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x532CFF637EF80148, p0); } // 532CFF637EF80148 0B6D610D
	static void _0x75A16C3DA34F1245(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x75A16C3DA34F1245, p0, p1); } // 75A16C3DA34F1245 1D99F676
	static void _0x74513EA3E505181E(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x74513EA3E505181E, p0, p1); } // 74513EA3E505181E 3DCF0092
	static void _0x5FBCA48327B914DF(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x5FBCA48327B914DF, p0, p1); } // 5FBCA48327B914DF D1C3D71B
	static void _0xB81656BC81FE24D1(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xB81656BC81FE24D1, p0, p1); } // B81656BC81FE24D1 8DE82C15
	static void _0x23C3EB807312F01A(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x23C3EB807312F01A, p0, p1); } // 23C3EB807312F01A 4C8F02B4
	static void _0xDCFB5D4DB8BF367E(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xDCFB5D4DB8BF367E, p0, p1); } // DCFB5D4DB8BF367E ABBE1E45
	static void _0xC4278F70131BAA6D(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xC4278F70131BAA6D, p0, p1); } // C4278F70131BAA6D 6AA6A1CC
	static void _0x2B6D467DAB714E8D(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x2B6D467DAB714E8D, p0, p1); } // 2B6D467DAB714E8D C575F0BC
	static void _0x25615540D894B814(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x25615540D894B814, p0, p1); } // 25615540D894B814 40E25DB8
	static BOOL DOES_BLIP_EXIST(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xA6DB27D19ECBB7DA, p0); } // A6DB27D19ECBB7DA AE92DD96
	static void SET_WAYPOINT_OFF() { NativeInvoke::Invoke<scrVoid>(0xA7E4E2D361C2627F); } // A7E4E2D361C2627F B3496E1B
	static void _0xD8E694757BCEA8E9() { NativeInvoke::Invoke<scrVoid>(0xD8E694757BCEA8E9); } // D8E694757BCEA8E9 62BABF2C
	static void REFRESH_WAYPOINT() { NativeInvoke::Invoke<scrVoid>(0x81FA173F170560D1); } // 81FA173F170560D1 B395D753
	static BOOL IS_WAYPOINT_ACTIVE() { return NativeInvoke::Invoke<BOOL>(0x1DD1F58F493F1DA5); } // 1DD1F58F493F1DA5 5E4DF47B
	static void SET_NEW_WAYPOINT(float p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xFE43368D2AA4F2FC, p0, p1); } // FE43368D2AA4F2FC 8444E1F0
	static void SET_BLIP_BRIGHT(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xB203913733F27884, p0, p1); } // B203913733F27884 72BEE6DF
	static void SET_BLIP_SHOW_CONE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x13127EC3665E8EE1, p0, p1); } // 13127EC3665E8EE1 FF545AD8
	static void _0xC594B315EDF2D4AF(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xC594B315EDF2D4AF, p0); } // C594B315EDF2D4AF 41B0D022
	static scrAny SET_MINIMAP_COMPONENT(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x75A9A10948D1DEA6, p0, p1); } // 75A9A10948D1DEA6 419DCDC4
	static void _0x60E892BA4F5BDCA4() { NativeInvoke::Invoke<scrVoid>(0x60E892BA4F5BDCA4); } // 60E892BA4F5BDCA4
	static scrAny GET_MAIN_PLAYER_BLIP_ID() { return NativeInvoke::Invoke<scrAny>(0xDCD4EC3F419D02FA); } // DCD4EC3F419D02FA AB93F020
	static void _0x41350B4FC28E3941(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x41350B4FC28E3941, p0); } // 41350B4FC28E3941
	static void HIDE_LOADING_ON_FADE_THIS_FRAME() { NativeInvoke::Invoke<scrVoid>(0x4B0311D3CDC4648F); } // 4B0311D3CDC4648F 35087963
	static void SET_RADAR_AS_INTERIOR_THIS_FRAME(scrAny p0, float p1, float p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x59E727A1C9D3E31A, p0, p1, p2, p3, p4); } // 59E727A1C9D3E31A 6F2626E1
	static void SET_RADAR_AS_EXTERIOR_THIS_FRAME() { NativeInvoke::Invoke<scrVoid>(0xE81B7D2A3DAB2D81); } // E81B7D2A3DAB2D81 39ABB10E
	static void _0x77E2DD177910E1CF(float p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x77E2DD177910E1CF, p0, p1); } // 77E2DD177910E1CF 54E75C7D
	static scrAny _0x9049FE339D5F6F6F() { return NativeInvoke::Invoke<scrAny>(0x9049FE339D5F6F6F); } // 9049FE339D5F6F6F 199DED14
	static void _0x5FBAE526203990C9() { NativeInvoke::Invoke<scrVoid>(0x5FBAE526203990C9); } // 5FBAE526203990C9 1A4318F7
	static void _0x20FE7FDFEEAD38C0() { NativeInvoke::Invoke<scrVoid>(0x20FE7FDFEEAD38C0); } // 20FE7FDFEEAD38C0 CE36E3FE
	static void _0x6D14BFDC33B34F55() { NativeInvoke::Invoke<scrVoid>(0x6D14BFDC33B34F55); } // 6D14BFDC33B34F55 334EFD46
	static void SET_WIDESCREEN_FORMAT(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xC3B07BA00A83B0F1, p0); } // C3B07BA00A83B0F1 F016E08F
	static void DISPLAY_AREA_NAME(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x276B6CE369C33678, p0); } // 276B6CE369C33678 489FDD41
	static void DISPLAY_CASH(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x96DEC8D5430208B7, p0); } // 96DEC8D5430208B7 0049DF83
	static void _0x170F541E1CADD1DE(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x170F541E1CADD1DE, p0); } // 170F541E1CADD1DE
	static void _0x0772DF77852C2E30(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x0772DF77852C2E30, p0, p1); } // 0772DF77852C2E30
	static void DISPLAY_AMMO_THIS_FRAME(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xA5E78BA2B1331C55, p0); } // A5E78BA2B1331C55 60693CEE
	static void DISPLAY_SNIPER_SCOPE_THIS_FRAME() { NativeInvoke::Invoke<scrVoid>(0x73115226F4814E62); } // 73115226F4814E62 BC6C73CB
	static void HIDE_HUD_AND_RADAR_THIS_FRAME() { NativeInvoke::Invoke<scrVoid>(0x719FF505F097FD20); } // 719FF505F097FD20 B75D4AD2
	static void _0xE67C6DFD386EA5E7(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xE67C6DFD386EA5E7, p0); } // E67C6DFD386EA5E7 5476B9FD
	static void _0xC2D15BEF167E27BC() { NativeInvoke::Invoke<scrVoid>(0xC2D15BEF167E27BC); } // C2D15BEF167E27BC F4F3C796
	static void _0x95CF81BD06EE1887() { NativeInvoke::Invoke<scrVoid>(0x95CF81BD06EE1887); } // 95CF81BD06EE1887 7BFFE82F
	static void SET_MULTIPLAYER_BANK_CASH() { NativeInvoke::Invoke<scrVoid>(0xDD21B55DF695CD0A); } // DD21B55DF695CD0A 2C842D03
	static void REMOVE_MULTIPLAYER_BANK_CASH() { NativeInvoke::Invoke<scrVoid>(0xC7C6789AA1CFEDD0); } // C7C6789AA1CFEDD0 728B4EF4
	static void SET_MULTIPLAYER_HUD_CASH(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xFD1D220394BCB824, p0, p1); } // FD1D220394BCB824 A8DB435E
	static void REMOVE_MULTIPLAYER_HUD_CASH() { NativeInvoke::Invoke<scrVoid>(0x968F270E39141ECA); } // 968F270E39141ECA 07BF4A7D
	static void HIDE_HELP_TEXT_THIS_FRAME() { NativeInvoke::Invoke<scrVoid>(0xD46923FC481CA285); } // D46923FC481CA285 F3807BED
	static void DISPLAY_HELP_TEXT_THIS_FRAME(scrAny *p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x960C9FF8F616E41C, p0, p1); } // 960C9FF8F616E41C 18E3360A
	static void _0xEB354E5376BC81A7(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xEB354E5376BC81A7, p0); } // EB354E5376BC81A7 1EFFB02A
	static void _0x0AFC4AF510774B47() { NativeInvoke::Invoke<scrVoid>(0x0AFC4AF510774B47); } // 0AFC4AF510774B47 B26FED2B
	static scrAny _0xA48931185F0536FE() { return NativeInvoke::Invoke<scrAny>(0xA48931185F0536FE); } // A48931185F0536FE 22E9F555
	static void _0x72C1056D678BB7D8(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x72C1056D678BB7D8, p0); } // 72C1056D678BB7D8 83B608A0
	static scrAny _0xA13E93403F26C812(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xA13E93403F26C812, p0); } // A13E93403F26C812
	static void _0x14C9FDCC41F81F63(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x14C9FDCC41F81F63, p0); } // 14C9FDCC41F81F63 E70D1F43
	static void SET_GPS_FLAGS(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x5B440763A4C8D15B, p0, p1); } // 5B440763A4C8D15B 60539BAB
	static void CLEAR_GPS_FLAGS() { NativeInvoke::Invoke<scrVoid>(0x21986729D6A3A830); } // 21986729D6A3A830 056AFCE6
	static void _0x1EAC5F91BCBC5073(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x1EAC5F91BCBC5073, p0); } // 1EAC5F91BCBC5073 FB9BABF5
	static void CLEAR_GPS_RACE_TRACK() { NativeInvoke::Invoke<scrVoid>(0x7AA5B4CE533C858B); } // 7AA5B4CE533C858B 40C59829
	static void _0xDB34E8D56FC13B08(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xDB34E8D56FC13B08, p0, p1, p2); } // DB34E8D56FC13B08 7F93799B
	static void _0x311438A071DD9B1A(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x311438A071DD9B1A, p0, p1, p2); } // 311438A071DD9B1A EEBDFE55
	static void _0x900086F371220B6F(BOOL p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x900086F371220B6F, p0, p1, p2); } // 900086F371220B6F DA0AF00E
	static void _0xE6DE0561D9232A64() { NativeInvoke::Invoke<scrVoid>(0xE6DE0561D9232A64); } // E6DE0561D9232A64 CF2E3E24
	static void _0x3D3D15AF7BCAAF83(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x3D3D15AF7BCAAF83, p0, p1, p2); } // 3D3D15AF7BCAAF83 C3DCBEDB
	static void _0xA905192A6781C41B(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xA905192A6781C41B, p0, p1, p2); } // A905192A6781C41B FE485135
	static void _0x3DDA37128DD1ACA8(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x3DDA37128DD1ACA8, p0); } // 3DDA37128DD1ACA8 E87CBE4C
	static void _0x67EEDEA1B9BAFD94() { NativeInvoke::Invoke<scrVoid>(0x67EEDEA1B9BAFD94); } // 67EEDEA1B9BAFD94 0D9969E4
	static void CLEAR_GPS_PLAYER_WAYPOINT() { NativeInvoke::Invoke<scrVoid>(0xFF4FB7C8CDFA3DA7); } // FF4FB7C8CDFA3DA7 0B9C7FC2
	static void SET_GPS_FLASHES(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x320D0E0D936A0E9B, p0); } // 320D0E0D936A0E9B E991F733
	static void FLASH_MINIMAP_DISPLAY() { NativeInvoke::Invoke<scrVoid>(0xF2DD778C22B15BDA); } // F2DD778C22B15BDA B8359952
	static void _0x6B1DE27EE78E6A19(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x6B1DE27EE78E6A19, p0); } // 6B1DE27EE78E6A19 79A6CAF6
	static void TOGGLE_STEALTH_RADAR(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x6AFDFB93754950C7, p0); } // 6AFDFB93754950C7 C68D47C4
	static void KEY_HUD_COLOUR(BOOL p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x1A5CD7752DD28CD3, p0, p1); } // 1A5CD7752DD28CD3 D5BFCADB
	static void SET_MISSION_NAME(BOOL p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x5F28ECF5FC84772F, p0, p1); } // 5F28ECF5FC84772F 68DCAE10
	static void _0xE45087D85F468BC2(BOOL p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xE45087D85F468BC2, p0, p1); } // E45087D85F468BC2 8D9A1734
	static void _0x817B86108EB94E51(BOOL p0, scrAny *p1, scrAny *p2, scrAny *p3, scrAny *p4, scrAny *p5, scrAny *p6, scrAny *p7, scrAny *p8) { NativeInvoke::Invoke<scrVoid>(0x817B86108EB94E51, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 817B86108EB94E51 D2161E77
	static void SET_MINIMAP_BLOCK_WAYPOINT(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x58FADDED207897DC, p0); } // 58FADDED207897DC A41C3B62
	static void _0x9133955F1A2DA957(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x9133955F1A2DA957, p0); } // 9133955F1A2DA957 02F5F1D1
	static void _0xF8DEE0A5600CBB93(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xF8DEE0A5600CBB93, p0); } // F8DEE0A5600CBB93 D8D77733
	static float _0xE0130B41D3CF4574() { return NativeInvoke::Invoke<float>(0xE0130B41D3CF4574); } // E0130B41D3CF4574 A4098ACC
	static BOOL _0x6E31B91145873922(float p0, float p1, float p2) { return NativeInvoke::Invoke<BOOL>(0x6E31B91145873922, p0, p1, p2); } // 6E31B91145873922 65B705F6
	static void _0x0923DBF87DFF735E(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x0923DBF87DFF735E, p0, p1, p2); } // 0923DBF87DFF735E E010F081
	static void _0x71BDB63DBAF8DA59(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x71BDB63DBAF8DA59, p0); } // 71BDB63DBAF8DA59 5133A750
	static void _0x35EDD5B2E3FF01C0() { NativeInvoke::Invoke<scrVoid>(0x35EDD5B2E3FF01C0); } // 35EDD5B2E3FF01C0 20FD3E87
	static void LOCK_MINIMAP_ANGLE(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x299FAEBB108AE05B, p0); } // 299FAEBB108AE05B DEC733E4
	static void UNLOCK_MINIMAP_ANGLE() { NativeInvoke::Invoke<scrVoid>(0x8183455E16C42E3A); } // 8183455E16C42E3A 742043F9
	static void LOCK_MINIMAP_POSITION(float p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x1279E861A329E73F, p0, p1); } // 1279E861A329E73F B9632A91
	static void UNLOCK_MINIMAP_POSITION() { NativeInvoke::Invoke<scrVoid>(0x3E93E06DB8EF1F30); } // 3E93E06DB8EF1F30 5E8E6F54
	static void _0xD201F3FF917A506D(float p0) { NativeInvoke::Invoke<scrVoid>(0xD201F3FF917A506D, p0); } // D201F3FF917A506D 0308EDF6
	static void _0x3F5CC444DCAAA8F2(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x3F5CC444DCAAA8F2, p0, p1, p2); } // 3F5CC444DCAAA8F2 7FB6FB2A
	static void _0x975D66A0BC17064C(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x975D66A0BC17064C, p0); } // 975D66A0BC17064C F07D8CEF
	static void _0x06A320535F5F0248(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x06A320535F5F0248, p0); } // 06A320535F5F0248 827F14DE
	static void _0x231C8F89D0539D8F(BOOL p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x231C8F89D0539D8F, p0, p1); } // 231C8F89D0539D8F 08EB83D2
	static BOOL IS_HUD_COMPONENT_ACTIVE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xBC4C9EA5391ECC0D, p0); } // BC4C9EA5391ECC0D 6214631F
	static BOOL IS_SCRIPTED_HUD_COMPONENT_ACTIVE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xDD100EB17A94FF65, p0); } // DD100EB17A94FF65 2B86F382
	static void HIDE_SCRIPTED_HUD_COMPONENT_THIS_FRAME(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xE374C498D8BADC14, p0); } // E374C498D8BADC14 31ABA127
	static BOOL _0x09C0403ED9A751C2(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x09C0403ED9A751C2, p0); } // 09C0403ED9A751C2 E8C8E535
	static void HIDE_HUD_COMPONENT_THIS_FRAME(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x6806C51AD12B83B8, p0); } // 6806C51AD12B83B8 DB2D0762
	static void SHOW_HUD_COMPONENT_THIS_FRAME(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x0B4DF1FA60C0E664, p0); } // 0B4DF1FA60C0E664 95E1546E
	static void _0xA4DEDE28B1814289() { NativeInvoke::Invoke<scrVoid>(0xA4DEDE28B1814289); } // A4DEDE28B1814289 52746FE1
	static void RESET_RETICULE_VALUES() { NativeInvoke::Invoke<scrVoid>(0x12782CE0A636E9F0); } // 12782CE0A636E9F0 BE27AA3F
	static void RESET_HUD_COMPONENT_VALUES(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x450930E616475D0D, p0); } // 450930E616475D0D D15B46DA
	static void SET_HUD_COMPONENT_POSITION(scrAny p0, float p1, float p2) { NativeInvoke::Invoke<scrVoid>(0xAABB1F56E2A17CED, p0, p1, p2); } // AABB1F56E2A17CED 2F3A0D15
	static scrVector3 GET_HUD_COMPONENT_POSITION(scrAny p0) { return NativeInvoke::Invoke<scrVector3>(0x223CA69A8C4417FD, p0); } // 223CA69A8C4417FD 080DCED6
	static void _0xB57D8DD645CFA2CF() { NativeInvoke::Invoke<scrVoid>(0xB57D8DD645CFA2CF); } // B57D8DD645CFA2CF 5BBCC934
	static scrAny _0xF9904D11F1ACBEC3(float p0, float p1, float p2, scrAny *p3, scrAny *p4) { return NativeInvoke::Invoke<scrAny>(0xF9904D11F1ACBEC3, p0, p1, p2, p3, p4); } // F9904D11F1ACBEC3 FE9A39F8
	static void _0x523A590C1A3CC0D3() { NativeInvoke::Invoke<scrVoid>(0x523A590C1A3CC0D3); } // 523A590C1A3CC0D3 10DE5150
	static void _0xEE4C0E6DBC6F2C6F() { NativeInvoke::Invoke<scrVoid>(0xEE4C0E6DBC6F2C6F); } // EE4C0E6DBC6F2C6F 67649EE0
	static scrAny _0x9135584D09A3437E() { return NativeInvoke::Invoke<scrAny>(0x9135584D09A3437E); } // 9135584D09A3437E 9D2C94FA
	static BOOL _0x2432784ACA090DA4(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x2432784ACA090DA4, p0); } // 2432784ACA090DA4 45472FD5
	static void _0x7679CC1BCEBE3D4C(scrAny p0, float p1, float p2) { NativeInvoke::Invoke<scrVoid>(0x7679CC1BCEBE3D4C, p0, p1, p2); } // 7679CC1BCEBE3D4C 198F32D7
	static void _0x784BA7E0ECEB4178(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x784BA7E0ECEB4178, p0, p1, p2, p3); } // 784BA7E0ECEB4178 93045157
	static void _0xB094BC1DB4018240(scrAny p0, scrAny p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0xB094BC1DB4018240, p0, p1, p2, p3); } // B094BC1DB4018240 18B012B7
	static void _0x788E7FD431BD67F1(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0x788E7FD431BD67F1, p0, p1, p2, p3, p4, p5); } // 788E7FD431BD67F1 97852A82
	static void CLEAR_FLOATING_HELP(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x50085246ABD3FEFA, p0, p1); } // 50085246ABD3FEFA B181F88F
	static void _0x6DD05E9D83EFA4C9(scrAny p0, scrAny *p1, BOOL p2, BOOL p3, scrAny *p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8) { NativeInvoke::Invoke<scrVoid>(0x6DD05E9D83EFA4C9, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 6DD05E9D83EFA4C9 C969F2D0
	static BOOL _0x6E0EB3EB47C8D7AA() { return NativeInvoke::Invoke<BOOL>(0x6E0EB3EB47C8D7AA); } // 6E0EB3EB47C8D7AA EFD2564A
	static scrAny _0xBFEFE3321A3F5015(scrAny p0, scrAny *p1, BOOL p2, BOOL p3, scrAny *p4, scrAny p5) { return NativeInvoke::Invoke<scrAny>(0xBFEFE3321A3F5015, p0, p1, p2, p3, p4, p5); } // BFEFE3321A3F5015 F5CD2AA4
	static void _0x31698AA80E0223F8(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x31698AA80E0223F8, p0); } // 31698AA80E0223F8 3D081FE4
	static BOOL _0x4E929E7A5796FD26(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x4E929E7A5796FD26, p0); } // 4E929E7A5796FD26 60118951
	static BOOL ADD_TREVOR_RANDOM_MODIFIER(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x595B5178E412E199, p0); } // 595B5178E412E199 63959059
	static void _0x63BB75ABEDC1F6A0(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x63BB75ABEDC1F6A0, p0, p1, p2); } // 63BB75ABEDC1F6A0 D41DF479
	static void _0xEE76FF7E6A0166B0(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xEE76FF7E6A0166B0, p0, p1); } // EE76FF7E6A0166B0 767DED29
	static void _0xA67F9C46D612B6F1(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xA67F9C46D612B6F1, p0, p1); } // A67F9C46D612B6F1 B01A5434
	static void _0x613ED644950626AE(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x613ED644950626AE, p0, p1, p2); } // 613ED644950626AE 7E3AA40A
	static void _0x3158C77A7E888AB4(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x3158C77A7E888AB4, p0, p1); } // 3158C77A7E888AB4 5777EC77
	static void _0xD48FE545CD46F857(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xD48FE545CD46F857, p0, p1, p2); } // D48FE545CD46F857 F4418611
	static void _0xCF228E2AA03099C3(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xCF228E2AA03099C3, p0, p1); } // CF228E2AA03099C3 0EBB003F
	static void _0xDEA2B8283BAA3944(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xDEA2B8283BAA3944, p0, p1); } // DEA2B8283BAA3944 627A559B
	static BOOL _0xEB709A36958ABE0D(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xEB709A36958ABE0D, p0); } // EB709A36958ABE0D F11414C4
	static void _0x7B7723747CCB55B6(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x7B7723747CCB55B6, p0, p1); } // 7B7723747CCB55B6 939218AB
	static scrAny _0x01A358D9128B7A86() { return NativeInvoke::Invoke<scrAny>(0x01A358D9128B7A86); } // 01A358D9128B7A86 AB5B7C18
	static scrAny GET_CURRENT_WEBSITE_ID() { return NativeInvoke::Invoke<scrAny>(0x97D47996FC48CBAD); } // 97D47996FC48CBAD 42A55B14
	static scrAny _0xE3B05614DCE1D014(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xE3B05614DCE1D014, p0); } // E3B05614DCE1D014 D217EE7E
	static BOOL _0xAF42195A42C63BBA() { return NativeInvoke::Invoke<BOOL>(0xAF42195A42C63BBA); } // AF42195A42C63BBA
	static void SET_WARNING_MESSAGE(scrAny *p0, scrAny p1, scrAny *p2, BOOL p3, scrAny p4, scrAny *p5, scrAny *p6, BOOL p7) { NativeInvoke::Invoke<scrVoid>(0x7B1776B3B53F8D74, p0, p1, p2, p3, p4, p5, p6, p7); } // 7B1776B3B53F8D74 BE699BDE
	static void _0xDC38CC1E35B6A5D7(scrAny *p0, scrAny *p1, scrAny p2, scrAny *p3, BOOL p4, scrAny p5, scrAny *p6, scrAny *p7, BOOL p8) { NativeInvoke::Invoke<scrVoid>(0xDC38CC1E35B6A5D7, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // DC38CC1E35B6A5D7 2DB9EAB5
	static void SET_DANCE_MAPPERS(scrAny *p0, scrAny *p1, scrAny p2, scrAny *p3, BOOL p4, scrAny p5, scrAny p6, scrAny *p7, scrAny *p8, BOOL p9) { NativeInvoke::Invoke<scrVoid>(0x701919482C74B5AB, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 701919482C74B5AB 749929D3
	static BOOL _0x0C5A80A9E096D529(scrAny p0, scrAny *p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { return NativeInvoke::Invoke<BOOL>(0x0C5A80A9E096D529, p0, p1, p2, p3, p4, p5); } // 0C5A80A9E096D529
	static BOOL _0xDAF87174BE7454FF(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xDAF87174BE7454FF, p0); } // DAF87174BE7454FF
	static void _0x6EF54AB721DC6242() { NativeInvoke::Invoke<scrVoid>(0x6EF54AB721DC6242); } // 6EF54AB721DC6242
	static BOOL _0xE18B138FABC53103() { return NativeInvoke::Invoke<BOOL>(0xE18B138FABC53103); } // E18B138FABC53103 94C834AD
	static void _0x7792424AA0EAC32E() { NativeInvoke::Invoke<scrVoid>(0x7792424AA0EAC32E); } // 7792424AA0EAC32E 2F9A309C
	static void _0x5354C5BA2EA868A4(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x5354C5BA2EA868A4, p0); } // 5354C5BA2EA868A4 E4FD20D8
	static void _0x1EAE6DD17B7A5EFA(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x1EAE6DD17B7A5EFA, p0); } // 1EAE6DD17B7A5EFA 13E7A5A9
	static scrAny _0x551DF99658DB6EE8(float p0, float p1, float p2) { return NativeInvoke::Invoke<scrAny>(0x551DF99658DB6EE8, p0, p1, p2); } // 551DF99658DB6EE8 786CA0A2
	static void _0x2708FC083123F9FF() { NativeInvoke::Invoke<scrVoid>(0x2708FC083123F9FF); } // 2708FC083123F9FF CBEC9369
	static scrAny _0x1121BFA1A1A522A8() { return NativeInvoke::Invoke<scrAny>(0x1121BFA1A1A522A8); } // 1121BFA1A1A522A8 3F4AFB13
	static void _0x82CEDC33687E1F50(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x82CEDC33687E1F50, p0); } // 82CEDC33687E1F50 2F28F0A6
	static void _0x211C4EF450086857() { NativeInvoke::Invoke<scrVoid>(0x211C4EF450086857); } // 211C4EF450086857 801D0D86
	static void _0xBF4F34A85CA2970C() { NativeInvoke::Invoke<scrVoid>(0xBF4F34A85CA2970C); } // BF4F34A85CA2970C 317775DF
	static void ACTIVATE_FRONTEND_MENU(scrAny p0, BOOL p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xEF01D36B9C9D0C7B, p0, p1, p2); } // EF01D36B9C9D0C7B 01D83872
	static void RESTART_FRONTEND_MENU(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x10706DC6AD2D49C0, p0, p1); } // 10706DC6AD2D49C0 B07DAF98
	static scrAny _0x2309595AD6145265() { return NativeInvoke::Invoke<scrAny>(0x2309595AD6145265); } // 2309595AD6145265 33D6868F
	static void SET_PAUSE_MENU_ACTIVE(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xDF47FC56C71569CF, p0); } // DF47FC56C71569CF 1DCD878E
	static void DISABLE_FRONTEND_THIS_FRAME() { NativeInvoke::Invoke<scrVoid>(0x6D3465A73092F0E6); } // 6D3465A73092F0E6 D86A029E
	static void _0xBA751764F0821256() { NativeInvoke::Invoke<scrVoid>(0xBA751764F0821256); } // BA751764F0821256 7F349900
	static void _0xCC3FDDED67BCFC63() { NativeInvoke::Invoke<scrVoid>(0xCC3FDDED67BCFC63); } // CC3FDDED67BCFC63 630CD8EE
	static void SET_FRONTEND_ACTIVE(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x745711A75AB09277, p0); } // 745711A75AB09277 81E1AD32
	static BOOL IS_PAUSE_MENU_ACTIVE() { return NativeInvoke::Invoke<BOOL>(0xB0034A223497FFCB); } // B0034A223497FFCB D3600591
	static scrAny _0x2F057596F2BD0061() { return NativeInvoke::Invoke<scrAny>(0x2F057596F2BD0061); } // 2F057596F2BD0061 C85C4487
	static scrAny GET_PAUSE_MENU_STATE() { return NativeInvoke::Invoke<scrAny>(0x272ACD84970869C5); } // 272ACD84970869C5 92F50134
	static BOOL IS_PAUSE_MENU_RESTARTING() { return NativeInvoke::Invoke<BOOL>(0x1C491717107431C7); } // 1C491717107431C7 3C4CF4D9
	static void _0x2162C446DFDF38FD(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x2162C446DFDF38FD, p0); } // 2162C446DFDF38FD 2DFD35C7
	static void _0x77F16B447824DA6C(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x77F16B447824DA6C, p0); } // 77F16B447824DA6C 0A89336C
	static void _0xCDCA26E80FAECB8F() { NativeInvoke::Invoke<scrVoid>(0xCDCA26E80FAECB8F); } // CDCA26E80FAECB8F C84BE309
	static void _0xDD564BDD0472C936(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xDD564BDD0472C936, p0); } // DD564BDD0472C936 9FE8FD5E
	static void OBJECT_DECAL_TOGGLE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x444D8CF241EC25C5, p0); } // 444D8CF241EC25C5 0029046E
	static BOOL _0x84698AB38D0C6636(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x84698AB38D0C6636, p0); } // 84698AB38D0C6636 C51BC42F
	static BOOL _0x2A25ADC48F87841F() { return NativeInvoke::Invoke<BOOL>(0x2A25ADC48F87841F); } // 2A25ADC48F87841F 016D7AF9
	static void ENABLE_DEATHBLOOD_SEETHROUGH(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x4895BDEA16E7C080, p0); } // 4895BDEA16E7C080 15B24768
	static void _0xC78E239AC5B2DDB9(BOOL p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xC78E239AC5B2DDB9, p0, p1, p2); } // C78E239AC5B2DDB9 6C67131A
	static void _0xF06EBB91A81E09E3(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xF06EBB91A81E09E3, p0); } // F06EBB91A81E09E3 11D09737
	static BOOL _0x3BAB9A4E4F2FF5C7() { return NativeInvoke::Invoke<BOOL>(0x3BAB9A4E4F2FF5C7); } // 3BAB9A4E4F2FF5C7 D3BF3ABD
	static void _0xEC9264727EEC0F28() { NativeInvoke::Invoke<scrVoid>(0xEC9264727EEC0F28); } // EC9264727EEC0F28 C06B763D
	static void _0x14621BB1DF14E2B2() { NativeInvoke::Invoke<scrVoid>(0x14621BB1DF14E2B2); } // 14621BB1DF14E2B2 B9392CE7
	static BOOL _0x66E7CB63C97B7D20() { return NativeInvoke::Invoke<BOOL>(0x66E7CB63C97B7D20); } // 66E7CB63C97B7D20 92DAFA78
	static scrAny _0x593FEAE1F73392D4() { return NativeInvoke::Invoke<scrAny>(0x593FEAE1F73392D4); } // 593FEAE1F73392D4 22CA9F2A
	static scrAny _0x4E3CD0EF8A489541() { return NativeInvoke::Invoke<scrAny>(0x4E3CD0EF8A489541); } // 4E3CD0EF8A489541 DA7951A2
	static scrAny _0xF284AC67940C6812() { return NativeInvoke::Invoke<scrAny>(0xF284AC67940C6812); } // F284AC67940C6812 7D95AFFF
	static scrAny _0x2E22FEFA0100275E() { return NativeInvoke::Invoke<scrAny>(0x2E22FEFA0100275E); } // 2E22FEFA0100275E 96863460
	static void _0x36C1451A88A09630(scrAny *p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x36C1451A88A09630, p0, p1); } // 36C1451A88A09630 8543AAC8
	static void _0x7E17BE53E1AAABAF(scrAny *p0, scrAny *p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0x7E17BE53E1AAABAF, p0, p1, p2); } // 7E17BE53E1AAABAF 6025AA2F
	static BOOL _0xA238192F33110615(scrAny *p0, scrAny *p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0xA238192F33110615, p0, p1, p2); } // A238192F33110615 46794EB2
	static BOOL SET_USERIDS_UIHIDDEN(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0xEF4CED81CEBEDC6D, p0, p1); } // EF4CED81CEBEDC6D 4370999E
	static BOOL _0x90A6526CF0381030(scrAny p0, scrAny *p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<BOOL>(0x90A6526CF0381030, p0, p1, p2, p3); } // 90A6526CF0381030 D6CC4766
	static BOOL _0x5FBD7095FE7AE57F(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x5FBD7095FE7AE57F, p0, p1); } // 5FBD7095FE7AE57F 51972B04
	static BOOL _0x052991E59076E4E4(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x052991E59076E4E4, p0, p1); } // 052991E59076E4E4 D43BB56D
	static void CLEAR_PED_IN_PAUSE_MENU() { NativeInvoke::Invoke<scrVoid>(0x5E62BE5DC58E9E06); } // 5E62BE5DC58E9E06 28058ACF
	static void GIVE_PED_TO_PAUSE_MENU(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xAC0BFBDC3BE00E14, p0, p1); } // AC0BFBDC3BE00E14 2AD2C9CE
	static void _0x3CA6050692BC61B0(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x3CA6050692BC61B0, p0); } // 3CA6050692BC61B0 127310EB
	static void _0xECF128344E9FF9F1(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xECF128344E9FF9F1, p0); } // ECF128344E9FF9F1 8F45D327
	static void _0x805D7CBB36FD6C4C() { NativeInvoke::Invoke<scrVoid>(0x805D7CBB36FD6C4C); } // 805D7CBB36FD6C4C 19FCBBB2
	static BOOL _0xF13FE2A80C05C561() { return NativeInvoke::Invoke<BOOL>(0xF13FE2A80C05C561); } // F13FE2A80C05C561 850690FF
	static scrAny _0x6F72CD94F7B5B68C() { return NativeInvoke::Invoke<scrAny>(0x6F72CD94F7B5B68C); } // 6F72CD94F7B5B68C 9D4934F4
	static void _0x75D3691713C3B05A() { NativeInvoke::Invoke<scrVoid>(0x75D3691713C3B05A); } // 75D3691713C3B05A 57218529
	static void _0xD2B32BE3FC1626C6() { NativeInvoke::Invoke<scrVoid>(0xD2B32BE3FC1626C6); } // D2B32BE3FC1626C6 5F86AA39
	static void _0x9E778248D6685FE0(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x9E778248D6685FE0, p0); } // 9E778248D6685FE0 7AD67C95
	static scrAny _0xC406BE343FC4B9AF() { return NativeInvoke::Invoke<scrAny>(0xC406BE343FC4B9AF); } // C406BE343FC4B9AF D4DA14EF
	static void _0xCEF214315D276FD1(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xCEF214315D276FD1, p0); } // CEF214315D276FD1 FF06772A
	static void _0xD30C50DF888D58B5(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xD30C50DF888D58B5, p0, p1); } // D30C50DF888D58B5 96C4C4DD
	static BOOL _0x15B8ECF844EE67ED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x15B8ECF844EE67ED, p0); } // 15B8ECF844EE67ED 3BE1257F
	static void _0xE52B8E7F85D39A08(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xE52B8E7F85D39A08, p0, p1); } // E52B8E7F85D39A08 D8E31B1A
	static void HIDE_SPECIAL_ABILITY_LOCKON_OPERATION(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x3EED80DFF7325CAA, p0, p1); } // 3EED80DFF7325CAA 872C2CFB
	static void _0x0C4BBF625CA98C4E(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x0C4BBF625CA98C4E, p0, p1); } // 0C4BBF625CA98C4E FFDF46F0
	static void _0x97C65887D4B37FA9(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x97C65887D4B37FA9, p0, p1); } // 97C65887D4B37FA9 F9DC2AF7
	static scrAny _0x7CD934010E115C2C(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x7CD934010E115C2C, p0); } // 7CD934010E115C2C 06349065
	static scrAny _0x56176892826A4FE8(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x56176892826A4FE8, p0); } // 56176892826A4FE8 CA52CF43
}

namespace GRAPHICS
{
	static void SET_DEBUG_LINES_AND_SPHERES_DRAWING_ACTIVE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x175B6BFC15CDD0C5, p0); } // 175B6BFC15CDD0C5 1418CA37
	static void DRAW_DEBUG_LINE(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9) { NativeInvoke::Invoke<scrVoid>(0x7FDFADE676AA3CB0, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 7FDFADE676AA3CB0 ABF783AB
	static void DRAW_DEBUG_LINE_WITH_TWO_COLOURS(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9, scrAny p10, scrAny p11, scrAny p12, scrAny p13) { NativeInvoke::Invoke<scrVoid>(0xD8B9A8AC5608FF94, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } // D8B9A8AC5608FF94 E8BFF632
	static void DRAW_DEBUG_SPHERE(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7) { NativeInvoke::Invoke<scrVoid>(0xAAD68E1AB39DA632, p0, p1, p2, p3, p4, p5, p6, p7); } // AAD68E1AB39DA632 304D0EEF
	static void DRAW_DEBUG_BOX(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9) { NativeInvoke::Invoke<scrVoid>(0x083A2CA4F2E573BD, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 083A2CA4F2E573BD 8524A848
	static void _0x73B1189623049839(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7) { NativeInvoke::Invoke<scrVoid>(0x73B1189623049839, p0, p1, p2, p3, p4, p5, p6, p7); } // 73B1189623049839 B6DF3709
	static void DRAW_DEBUG_TEXT(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7) { NativeInvoke::Invoke<scrVoid>(0x3903E216620488E8, p0, p1, p2, p3, p4, p5, p6, p7); } // 3903E216620488E8 269B006F
	static void DRAW_DEBUG_TEXT_2D(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7) { NativeInvoke::Invoke<scrVoid>(0xA3BB2E9555C05A8F, p0, p1, p2, p3, p4, p5, p6, p7); } // A3BB2E9555C05A8F 528B973B
	static void DRAW_LINE(float p0, float p1, float p2, float p3, float p4, float p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9) { NativeInvoke::Invoke<scrVoid>(0x6B7256074AE34680, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 6B7256074AE34680 B3426BCC
	static void DRAW_POLY(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, scrAny p9, scrAny p10, scrAny p11, scrAny p12) { NativeInvoke::Invoke<scrVoid>(0xAC26716048436851, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // AC26716048436851 ABD19253
	static void _0xD3A9971CADAC7252(float p0, float p1, float p2, float p3, float p4, float p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9) { NativeInvoke::Invoke<scrVoid>(0xD3A9971CADAC7252, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // D3A9971CADAC7252 CD4D9DD5
	static void _0x23BA6B0C2AD7B0D3(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x23BA6B0C2AD7B0D3, p0); } // 23BA6B0C2AD7B0D3 C44C2F44
	static BOOL _0x1DD2139A9A20DCE8() { return NativeInvoke::Invoke<BOOL>(0x1DD2139A9A20DCE8); } // 1DD2139A9A20DCE8 BA9AD458
	static scrAny _0x90A78ECAA4E78453() { return NativeInvoke::Invoke<scrAny>(0x90A78ECAA4E78453); } // 90A78ECAA4E78453 ADBBA287
	static void _0x0A46AF8A78DC5E0A() { NativeInvoke::Invoke<scrVoid>(0x0A46AF8A78DC5E0A); } // 0A46AF8A78DC5E0A 9E553002
	static BOOL _0x4862437A486F91B0(scrAny *p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<BOOL>(0x4862437A486F91B0, p0, p1, p2, p3); } // 4862437A486F91B0 56C1E488
	static scrAny _0x1670F8D05056F257(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0x1670F8D05056F257, p0); } // 1670F8D05056F257 226B08EA
	static BOOL _0x7FA5D82B8F58EC06() { return NativeInvoke::Invoke<BOOL>(0x7FA5D82B8F58EC06); } // 7FA5D82B8F58EC06 1F3CADB0
	static scrAny _0x5B0316762AFD4A64() { return NativeInvoke::Invoke<scrAny>(0x5B0316762AFD4A64); } // 5B0316762AFD4A64 A9DC8558
	static void _0x346EF3ECAAAB149E() { NativeInvoke::Invoke<scrVoid>(0x346EF3ECAAAB149E); } // 346EF3ECAAAB149E 88EAF398
	static BOOL _0xA67C35C56EB1BD9D() { return NativeInvoke::Invoke<BOOL>(0xA67C35C56EB1BD9D); } // A67C35C56EB1BD9D 47B0C137
	static scrAny MELEE_SEETHROUGH_SKIPPED() { return NativeInvoke::Invoke<scrAny>(0x0D6CA79EEEBD8CA3); } // 0D6CA79EEEBD8CA3 65376C9B
	static void _0xD801CC02177FA3F1() { NativeInvoke::Invoke<scrVoid>(0xD801CC02177FA3F1); } // D801CC02177FA3F1 9CBA682A
	static scrAny _0x3DEC726C25A11BAC(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x3DEC726C25A11BAC, p0); } // 3DEC726C25A11BAC 3B15D33C
	static scrAny _0x0C0C4E81E1AC60A0() { return NativeInvoke::Invoke<scrAny>(0x0C0C4E81E1AC60A0); } // 0C0C4E81E1AC60A0 EC5D0317
	static BOOL _0x759650634F07B6B4(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x759650634F07B6B4, p0); } // 759650634F07B6B4 25D569EB
	static scrAny _0xCB82A0BF0E3E3265(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xCB82A0BF0E3E3265, p0); } // CB82A0BF0E3E3265 CFCDC518
	static void _0x6A12D88881435DCA() { NativeInvoke::Invoke<scrVoid>(0x6A12D88881435DCA); } // 6A12D88881435DCA 108F36CC
	static void _0x1072F115DAB0717E(BOOL p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x1072F115DAB0717E, p0, p1); } // 1072F115DAB0717E E9F2B68F
	static scrAny GET_MAXIMUM_NUMBER_OF_PHOTOS() { return NativeInvoke::Invoke<scrAny>(0x34D23450F028B0BF); } // 34D23450F028B0BF 727AA63F
	static scrAny _0xDC54A7AF8B3A14EF() { return NativeInvoke::Invoke<scrAny>(0xDC54A7AF8B3A14EF); } // DC54A7AF8B3A14EF 239272BD
	static scrAny _0x473151EBC762C6DA() { return NativeInvoke::Invoke<scrAny>(0x473151EBC762C6DA); } // 473151EBC762C6DA 21DBF0C9
	static scrAny _0x2A893980E96B659A(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x2A893980E96B659A, p0); } // 2A893980E96B659A 199FABF0
	static scrAny _0xF5BED327CEA362B1(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xF5BED327CEA362B1, p0); } // F5BED327CEA362B1 596B900D
	static void _0x4AF92ACD3141D96C() { NativeInvoke::Invoke<scrVoid>(0x4AF92ACD3141D96C); } // 4AF92ACD3141D96C C9EF81ED
	static scrAny _0xE791DF1F73ED2C8B(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xE791DF1F73ED2C8B, p0); } // E791DF1F73ED2C8B 9D84554C
	static scrAny _0xEC72C258667BE5EA(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xEC72C258667BE5EA, p0); } // EC72C258667BE5EA 9C106AD9
	static scrAny _0x40AFB081F8ADD4EE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x40AFB081F8ADD4EE, p0); } // 40AFB081F8ADD4EE 762E5C5F
	static void DRAW_LIGHT_WITH_RANGE(float p0, float p1, float p2, scrAny p3, scrAny p4, scrAny p5, float p6, float p7) { NativeInvoke::Invoke<scrVoid>(0xF2A1B2771A01DBD4, p0, p1, p2, p3, p4, p5, p6, p7); } // F2A1B2771A01DBD4 6A396E9A
	static void DRAW_SPOT_LIGHT(float p0, float p1, float p2, float p3, float p4, float p5, scrAny p6, scrAny p7, scrAny p8, float p9, float p10, float p11, float p12, float p13) { NativeInvoke::Invoke<scrVoid>(0xD0F64B265C8C8B33, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } // D0F64B265C8C8B33 BDBC410C
	static void _0x5BCA583A583194DB(float p0, float p1, float p2, float p3, float p4, float p5, scrAny p6, scrAny p7, scrAny p8, float p9, float p10, float p11, float p12, float p13, scrAny p14) { NativeInvoke::Invoke<scrVoid>(0x5BCA583A583194DB, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); } // 5BCA583A583194DB 32BF9598
	static void _0xC9B18B4619F48F7B(float p0) { NativeInvoke::Invoke<scrVoid>(0xC9B18B4619F48F7B, p0); } // C9B18B4619F48F7B 93628786
	static void _0xDEADC0DEDEADC0DE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xDEADC0DEDEADC0DE, p0); } // DEADC0DEDEADC0DE
	static void DRAW_MARKER(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12, scrAny p13, scrAny p14, scrAny p15, scrAny p16, BOOL p17, BOOL p18, scrAny p19, BOOL p20, scrAny *p21, scrAny *p22, BOOL p23) { NativeInvoke::Invoke<scrVoid>(0x28477EC23D892089, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23); } // 28477EC23D892089 48D84A02
	static scrAny CREATE_CHECKPOINT(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, scrAny p8, scrAny p9, scrAny p10, scrAny p11, scrAny p12) { return NativeInvoke::Invoke<scrAny>(0x0134F0835AB6BFCB, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0134F0835AB6BFCB F541B690
	static void _0x4B5B4DA5D79F1943(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x4B5B4DA5D79F1943, p0, p1); } // 4B5B4DA5D79F1943 80151CCF
	static void SET_CHECKPOINT_CYLINDER_HEIGHT(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x2707AAE9D9297D89, p0, p1, p2, p3); } // 2707AAE9D9297D89 FF0F9B22
	static void SET_CHECKPOINT_RGBA(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x7167371E8AD747F7, p0, p1, p2, p3, p4); } // 7167371E8AD747F7 EF9C8CB3
	static void _0xB9EA40907C680580(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0xB9EA40907C680580, p0, p1, p2, p3, p4); } // B9EA40907C680580 A5456DBB
	static void _0xF51D36185993515D(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6) { NativeInvoke::Invoke<scrVoid>(0xF51D36185993515D, p0, p1, p2, p3, p4, p5, p6); } // F51D36185993515D 20EABD0F
	static void _0x615D3925E87A3B26(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x615D3925E87A3B26, p0); } // 615D3925E87A3B26 1E3A3126
	static void DELETE_CHECKPOINT(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xF5ED37F54CD4D52E, p0); } // F5ED37F54CD4D52E B66CF3CA
	static void _0x22A249A53034450A(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x22A249A53034450A, p0); } // 22A249A53034450A 932FDB81
	static void _0xDC459CFA0CCE245B(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xDC459CFA0CCE245B, p0); } // DC459CFA0CCE245B 7E946E87
	static void REQUEST_STREAMED_TEXTURE_DICT(scrAny *p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xDFA2EF8E04127DD5, p0, p1); } // DFA2EF8E04127DD5 4C9B035F
	static BOOL HAS_STREAMED_TEXTURE_DICT_LOADED(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x0145F696AAAAD2E4, p0); } // 0145F696AAAAD2E4 3F436EEF
	static void SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xBE2CACCF5A8AA805, p0); } // BE2CACCF5A8AA805 F07DDA38
	static void DRAW_RECT(float p0, float p1, float p2, float p3, int p4, int p5, int p6, int p7) { NativeInvoke::Invoke<scrVoid>(0x3A618A217E5154F0, p0, p1, p2, p3, p4, p5, p6, p7); } // 3A618A217E5154F0 DD2BFC77
	static void _0xC6372ECD45D73BCD(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xC6372ECD45D73BCD, p0); } // C6372ECD45D73BCD F8FBCC25
	static void _0x61BB1D9B3A95D802(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x61BB1D9B3A95D802, p0); } // 61BB1D9B3A95D802 ADF81D24
	static void _0xB8A850F20A067EB6(BOOL p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xB8A850F20A067EB6, p0, p1); } // B8A850F20A067EB6 228A2598
	static void _0xE3A3DB414A373DAB() { NativeInvoke::Invoke<scrVoid>(0xE3A3DB414A373DAB); } // E3A3DB414A373DAB 3FE33BD6
	static void _0xF5A2C681787E579D(float p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0xF5A2C681787E579D, p0, p1, p2, p3); } // F5A2C681787E579D 76C641E4
	static void _0x6DD8F5AA635EB4B2(float p0, float p1, scrAny *p2, scrAny *p3) { NativeInvoke::Invoke<scrVoid>(0x6DD8F5AA635EB4B2, p0, p1, p2, p3); } // 6DD8F5AA635EB4B2
	static float _0xBAF107B6BB2C97F0() { return NativeInvoke::Invoke<float>(0xBAF107B6BB2C97F0); } // BAF107B6BB2C97F0 3F0D1A6F
	static void DRAW_SPRITE(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9, scrAny p10) { NativeInvoke::Invoke<scrVoid>(0xE7FFAE5EBF23D890, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // E7FFAE5EBF23D890 1FEC16B0
	static scrAny ADD_ENTITY_ICON(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<scrAny>(0x9CD43EEE12BF4DD0, p0, p1); } // 9CD43EEE12BF4DD0 F3027D21
	static void SET_ENTITY_ICON_VISIBILITY(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xE0E8BEECCA96BA31, p0, p1); } // E0E8BEECCA96BA31 D1D2FD52
	static void SET_ENTITY_ICON_COLOR(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x1D5F595CCAE2E238, p0, p1, p2, p3, p4); } // 1D5F595CCAE2E238 6EE1E946
	static void SET_DRAW_ORIGIN(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0xAA0008F3BBB8F416, p0, p1, p2, p3); } // AA0008F3BBB8F416 E10198D5
	static void CLEAR_DRAW_ORIGIN() { NativeInvoke::Invoke<scrVoid>(0xFF0B610F6BE0D7AF); } // FF0B610F6BE0D7AF DD76B263
	static void ATTACH_TV_AUDIO_TO_ENTITY(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x845BAD77CC770633, p0); } // 845BAD77CC770633 784944DB
	static void SET_TV_AUDIO_FRONTEND(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x113D2C5DC57E1774, p0); } // 113D2C5DC57E1774 2E0DFA35
	static scrAny LOAD_MOVIE_MESH_SET(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0xB66064452270E8F1, p0); } // B66064452270E8F1 9627905C
	static void RELEASE_MOVIE_MESH_SET(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xEB119AA014E89183, p0); } // EB119AA014E89183 4FA5501D
	static scrAny _0x9B6E70C5CEEF4EEB(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x9B6E70C5CEEF4EEB, p0); } // 9B6E70C5CEEF4EEB 9D5D9B38
	static void GET_SCREEN_RESOLUTION(int *p0, int *p1) { NativeInvoke::Invoke<scrVoid>(0x888D57E407E63624, p0, p1); } // 888D57E407E63624 29F3572F
	static float _0xB2EBE8CBC58B90E9() { return NativeInvoke::Invoke<float>(0xB2EBE8CBC58B90E9); } // B2EBE8CBC58B90E9
	static BOOL GET_IS_WIDESCREEN() { return NativeInvoke::Invoke<BOOL>(0x30CF4BDA4FCB1905); } // 30CF4BDA4FCB1905 EC717AEF
	static BOOL GET_IS_HIDEF() { return NativeInvoke::Invoke<BOOL>(0x84ED31191CC5D2C9); } // 84ED31191CC5D2C9 1C340359
	static void SET_NIGHTVISION(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x18F621F7A5B1F85D, p0); } // 18F621F7A5B1F85D D1E5565F
	static scrAny _0x2202A3F42C8E5F79() { return NativeInvoke::Invoke<scrAny>(0x2202A3F42C8E5F79); } // 2202A3F42C8E5F79 62619061
	static void _0xEF398BEEE4EF45F9(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xEF398BEEE4EF45F9, p0); } // EF398BEEE4EF45F9
	static void SET_NOISEOVERIDE(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xE787BF1C5CF823C9, p0); } // E787BF1C5CF823C9 D576F5DD
	static void SET_NOISINESSOVERIDE(float p0) { NativeInvoke::Invoke<scrVoid>(0xCB6A7C3BB17A0C67, p0); } // CB6A7C3BB17A0C67 046B62D9
	static BOOL _0x34E82F05DF2974F5(float p0, float p1, float p2, scrAny *p3, scrAny *p4) { return NativeInvoke::Invoke<BOOL>(0x34E82F05DF2974F5, p0, p1, p2, p3, p4); } // 34E82F05DF2974F5 1F950E4B
	static scrVector3 GET_TEXTURE_RESOLUTION(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<scrVector3>(0x35736EE65BD00C11, p0, p1); } // 35736EE65BD00C11 096DAA4D
	static void _0xE2892E7E55D7073A(float p0) { NativeInvoke::Invoke<scrVoid>(0xE2892E7E55D7073A, p0); } // E2892E7E55D7073A 455F1084
	static void SET_FLASH(float p0, float p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x0AB84296FED9CFC6, p0, p1, p2, p3, p4); } // 0AB84296FED9CFC6 7E55A1EE
	static void _0x3669F1B198DCAA4F() { NativeInvoke::Invoke<scrVoid>(0x3669F1B198DCAA4F); } // 3669F1B198DCAA4F 0DCC0B8B
	static void _0x1268615ACE24D504(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x1268615ACE24D504, p0); } // 1268615ACE24D504 AA2A0EAF
	static scrAny CREATE_TRACKED_POINT() { return NativeInvoke::Invoke<scrAny>(0xE2C9439ED45DEA60); } // E2C9439ED45DEA60 3129C31A
	static void SET_TRACKED_POINT_INFO(scrAny p0, float p1, float p2, float p3, float p4) { NativeInvoke::Invoke<scrVoid>(0x164ECBB3CF750CB0, p0, p1, p2, p3, p4); } // 164ECBB3CF750CB0 28689AA4
	static scrAny IS_TRACKED_POINT_VISIBLE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xC45CCDAAC9221CA8, p0); } // C45CCDAAC9221CA8 0BFC4F64
	static void DESTROY_TRACKED_POINT(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xB25DC90BAD56CA42, p0); } // B25DC90BAD56CA42 14AC675F
	static scrAny _0xBE197EAA669238F4(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0xBE197EAA669238F4, p0, p1, p2, p3); } // BE197EAA669238F4
	static void _0x61F95E5BB3E0A8C6(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x61F95E5BB3E0A8C6, p0); } // 61F95E5BB3E0A8C6
	static void _0xAE51BC858F32BA66(scrAny p0, float p1, float p2, float p3, float p4) { NativeInvoke::Invoke<scrVoid>(0xAE51BC858F32BA66, p0, p1, p2, p3, p4); } // AE51BC858F32BA66
	static void _0x649C97D52332341A(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x649C97D52332341A, p0); } // 649C97D52332341A
	static void _0x14FC5833464340A8() { NativeInvoke::Invoke<scrVoid>(0x14FC5833464340A8); } // 14FC5833464340A8
	static void _0x0218BA067D249DEA() { NativeInvoke::Invoke<scrVoid>(0x0218BA067D249DEA); } // 0218BA067D249DEA
	static void _0x1612C45F9E3E0D44() { NativeInvoke::Invoke<scrVoid>(0x1612C45F9E3E0D44); } // 1612C45F9E3E0D44
	static void _0x5DEBD9C4DC995692() { NativeInvoke::Invoke<scrVoid>(0x5DEBD9C4DC995692); } // 5DEBD9C4DC995692
	static void _0x6D955F6A9E0295B1(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6) { NativeInvoke::Invoke<scrVoid>(0x6D955F6A9E0295B1, p0, p1, p2, p3, p4, p5, p6); } // 6D955F6A9E0295B1
	static void _0x302C91AB2D477F7E() { NativeInvoke::Invoke<scrVoid>(0x302C91AB2D477F7E); } // 302C91AB2D477F7E
	static void _0x03FC694AE06C5A20() { NativeInvoke::Invoke<scrVoid>(0x03FC694AE06C5A20); } // 03FC694AE06C5A20 48F16186
	static void _0x5F0F3F56635809EF(float p0) { NativeInvoke::Invoke<scrVoid>(0x5F0F3F56635809EF, p0); } // 5F0F3F56635809EF 13D4ABC0
	static void _0x5E9DAF5A20F15908(float p0) { NativeInvoke::Invoke<scrVoid>(0x5E9DAF5A20F15908, p0); } // 5E9DAF5A20F15908 D2157428
	static void _0x36F6626459D91457(float p0) { NativeInvoke::Invoke<scrVoid>(0x36F6626459D91457, p0); } // 36F6626459D91457 C07C64C9
	static void _0x80ECBC0C856D3B0B(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x80ECBC0C856D3B0B, p0); } // 80ECBC0C856D3B0B FE903D0F
	static void _0x25FC3E33A31AD0C9(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x25FC3E33A31AD0C9, p0); } // 25FC3E33A31AD0C9
	static void _0xB11D94BC55F41932(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xB11D94BC55F41932, p0); } // B11D94BC55F41932 DE10BA1F
	static void _0x27CB772218215325() { NativeInvoke::Invoke<scrVoid>(0x27CB772218215325); } // 27CB772218215325
	static void _0x6DDBF9DFFC4AC080(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x6DDBF9DFFC4AC080, p0); } // 6DDBF9DFFC4AC080 9F470BE3
	static void _0xD39D13C9FEBF0511(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xD39D13C9FEBF0511, p0); } // D39D13C9FEBF0511 4A124267
	static void _0x02AC28F3A01FA04A(float p0) { NativeInvoke::Invoke<scrVoid>(0x02AC28F3A01FA04A, p0); } // 02AC28F3A01FA04A B19B2764
	static void _0x0AE73D8DF3A762B2(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x0AE73D8DF3A762B2, p0); } // 0AE73D8DF3A762B2 342FA2B4
	static void _0xA51C4B86B71652AE(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xA51C4B86B71652AE, p0); } // A51C4B86B71652AE 5D3BFFC9
	static void _0x312342E1A4874F3F(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, BOOL p8) { NativeInvoke::Invoke<scrVoid>(0x312342E1A4874F3F, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 312342E1A4874F3F D9653728
	static void _0x2485D34E50A22E84(float p0, float p1, float p2) { NativeInvoke::Invoke<scrVoid>(0x2485D34E50A22E84, p0, p1, p2); } // 2485D34E50A22E84 72BA8A14
	static void _0x12995F2E53FFA601(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9, scrAny p10, scrAny p11) { NativeInvoke::Invoke<scrVoid>(0x12995F2E53FFA601, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 12995F2E53FFA601 804F444C
	static void _0xDBAA5EC848BA2D46(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xDBAA5EC848BA2D46, p0, p1); } // DBAA5EC848BA2D46 BB1A1294
	static void _0xC0416B061F2B7E5E(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xC0416B061F2B7E5E, p0); } // C0416B061F2B7E5E 1A1A72EF
	static void _0xB1BB03742917A5D6(scrAny p0, float p1, float p2, float p3, float p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8) { NativeInvoke::Invoke<scrVoid>(0xB1BB03742917A5D6, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // B1BB03742917A5D6 3BB12B75
	static void _0x9CFDD90B2B844BF7(float p0, float p1, float p2, float p3, float p4) { NativeInvoke::Invoke<scrVoid>(0x9CFDD90B2B844BF7, p0, p1, p2, p3, p4); } // 9CFDD90B2B844BF7 4EA70FB4
	static void _0x06F761EA47C1D3ED(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x06F761EA47C1D3ED, p0); } // 06F761EA47C1D3ED 0D830DC7
	static float _0xA4819F5E23E2FFAD() { return NativeInvoke::Invoke<float>(0xA4819F5E23E2FFAD); } // A4819F5E23E2FFAD A08B46AD
	static scrVector3 _0xA4664972A9B8F8BA(scrAny p0) { return NativeInvoke::Invoke<scrVector3>(0xA4664972A9B8F8BA, p0); } // A4664972A9B8F8BA ECD470F0
	static void SET_SEETHROUGH(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x7E08924259E08CE0, p0); } // 7E08924259E08CE0 74D4995C
	static scrAny _0x44B80ABAB9D80BD3() { return NativeInvoke::Invoke<scrAny>(0x44B80ABAB9D80BD3); } // 44B80ABAB9D80BD3 1FE547F2
	static void _0xD7D0B00177485411(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xD7D0B00177485411, p0, p1); } // D7D0B00177485411 654F0287
	static void _0xB3C641F3630BF6DA(float p0) { NativeInvoke::Invoke<scrVoid>(0xB3C641F3630BF6DA, p0); } // B3C641F3630BF6DA F6B837F0
	static float _0xE59343E9E96529E7() { return NativeInvoke::Invoke<float>(0xE59343E9E96529E7); } // E59343E9E96529E7 D906A3A9
	static void _0xE63D7C6EECECB66B(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xE63D7C6EECECB66B, p0); } // E63D7C6EECECB66B D34A6CBA
	static void _0xE3E2C1B4C59DBC77(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xE3E2C1B4C59DBC77, p0); } // E3E2C1B4C59DBC77 D8CC7221
	static BOOL _0xA328A24AAA6B7FDC(float p0) { return NativeInvoke::Invoke<BOOL>(0xA328A24AAA6B7FDC, p0); } // A328A24AAA6B7FDC 5604B890
	static BOOL _0xEFACC8AEF94430D5(float p0) { return NativeInvoke::Invoke<BOOL>(0xEFACC8AEF94430D5, p0); } // EFACC8AEF94430D5 46617502
	static void _0xDE81239437E8C5A8() { NativeInvoke::Invoke<scrVoid>(0xDE81239437E8C5A8); } // DE81239437E8C5A8 DB7AECDA
	static float IS_PARTICLE_FX_DELAYED_BLINK() { return NativeInvoke::Invoke<float>(0x5CCABFFCA31DDE33); } // 5CCABFFCA31DDE33 EA432A94
	static BOOL _0x7B226C785A52A0A9() { return NativeInvoke::Invoke<BOOL>(0x7B226C785A52A0A9); } // 7B226C785A52A0A9 926B8734
	static void _0xDFC252D8A3E15AB7(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xDFC252D8A3E15AB7, p0); } // DFC252D8A3E15AB7 30ADE541
	static scrAny _0xEB3DAC2C86001E5E() { return NativeInvoke::Invoke<scrAny>(0xEB3DAC2C86001E5E); } // EB3DAC2C86001E5E
	static void _0xE1C8709406F2C41C() { NativeInvoke::Invoke<scrVoid>(0xE1C8709406F2C41C); } // E1C8709406F2C41C 0113EAE4
	static void _0x851CD923176EBA7C() { NativeInvoke::Invoke<scrVoid>(0x851CD923176EBA7C); } // 851CD923176EBA7C DCBA251B
	static void _0xBA3D65906822BED5(BOOL p0, BOOL p1, float p2, float p3, float p4, float p5) { NativeInvoke::Invoke<scrVoid>(0xBA3D65906822BED5, p0, p1, p2, p3, p4, p5); } // BA3D65906822BED5 513D444B
	static BOOL _0x7AC24EAB6D74118D(BOOL p0) { return NativeInvoke::Invoke<BOOL>(0x7AC24EAB6D74118D, p0); } // 7AC24EAB6D74118D B2410EAB
	static scrAny _0xBCEDB009461DA156() { return NativeInvoke::Invoke<scrAny>(0xBCEDB009461DA156); } // BCEDB009461DA156 5AB94128
	static BOOL _0x27FEB5254759CDE3(scrAny *p0, BOOL p1) { return NativeInvoke::Invoke<BOOL>(0x27FEB5254759CDE3, p0, p1); } // 27FEB5254759CDE3 D63FCB3E
	static BOOL START_PARTICLE_FX_NON_LOOPED_AT_COORD(scrAny *p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, BOOL p8, BOOL p9, BOOL p10) { return NativeInvoke::Invoke<BOOL>(0x25129531F77B9ED3, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 25129531F77B9ED3 DD79D679
	static scrAny START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(scrAny *p0, scrAny p1, float p2, float p3, float p4, float p5, float p6, float p7, scrAny p8, float p9, BOOL p10, BOOL p11, BOOL p12) { return NativeInvoke::Invoke<scrAny>(0x0E7E72961BA18619, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 0E7E72961BA18619 53DAEF4E
	static scrAny _0xA41B6A43642AC2CF(scrAny *p0, scrAny p1, float p2, float p3, float p4, float p5, float p6, float p7, scrAny p8, float p9, BOOL p10, BOOL p11, BOOL p12) { return NativeInvoke::Invoke<scrAny>(0xA41B6A43642AC2CF, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // A41B6A43642AC2CF 161780C1
	static BOOL START_PARTICLE_FX_NON_LOOPED_ON_ENTITY(scrAny *p0, scrAny p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, BOOL p9, BOOL p10, BOOL p11) { return NativeInvoke::Invoke<BOOL>(0x0D53A3B8DA0809D2, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 0D53A3B8DA0809D2 9604DAD4
	static void _0x26143A59EF48B262(float p0, float p1, float p2) { NativeInvoke::Invoke<scrVoid>(0x26143A59EF48B262, p0, p1, p2); } // 26143A59EF48B262 7B689E20
	static void SET_PARTICLE_FX_NON_LOOPED_ALPHA(float p0) { NativeInvoke::Invoke<scrVoid>(0x77168D722C58B2FC, p0); } // 77168D722C58B2FC 497EAFF2
	static void _0x8CDE909A0370BB3A(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x8CDE909A0370BB3A, p0); } // 8CDE909A0370BB3A
	static scrAny START_PARTICLE_FX_LOOPED_AT_COORD(scrAny *p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, BOOL p8, BOOL p9, BOOL p10, BOOL p11) { return NativeInvoke::Invoke<scrAny>(0xE184F4F0DC5910E7, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // E184F4F0DC5910E7 D348E3E6
	static scrAny START_PARTICLE_FX_LOOPED_ON_PED_BONE(scrAny *p0, scrAny p1, float p2, float p3, float p4, float p5, float p6, float p7, scrAny p8, float p9, BOOL p10, BOOL p11, BOOL p12) { return NativeInvoke::Invoke<scrAny>(0xF28DA9F38CD1787C, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // F28DA9F38CD1787C F8FC196F
	static scrAny START_PARTICLE_FX_LOOPED_ON_ENTITY(scrAny *p0, scrAny p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, BOOL p9, BOOL p10, BOOL p11) { return NativeInvoke::Invoke<scrAny>(0x1AE42C1660FD6517, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 1AE42C1660FD6517 0D06FF62
	static scrAny _0xC6EB449E33977F0B(scrAny *p0, scrAny p1, float p2, float p3, float p4, float p5, float p6, float p7, scrAny p8, float p9, BOOL p10, BOOL p11, BOOL p12) { return NativeInvoke::Invoke<scrAny>(0xC6EB449E33977F0B, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // C6EB449E33977F0B
	static scrAny _0x6F60E89A7B64EE1D(scrAny *p0, scrAny p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, BOOL p9, BOOL p10, BOOL p11) { return NativeInvoke::Invoke<scrAny>(0x6F60E89A7B64EE1D, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 6F60E89A7B64EE1D 110752B2
	static scrAny _0xDDE23F30CC5A0F03(scrAny *p0, scrAny p1, float p2, float p3, float p4, float p5, float p6, float p7, scrAny p8, float p9, BOOL p10, BOOL p11, BOOL p12) { return NativeInvoke::Invoke<scrAny>(0xDDE23F30CC5A0F03, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // DDE23F30CC5A0F03
	static void STOP_PARTICLE_FX_LOOPED(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x8F75998877616996, p0, p1); } // 8F75998877616996 D245455B
	static void REMOVE_PARTICLE_FX(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xC401503DFE8D53CF, p0, p1); } // C401503DFE8D53CF 6BA48C7E
	static void REMOVE_PARTICLE_FX_FROM_ENTITY(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xB8FEAEEBCC127425, p0); } // B8FEAEEBCC127425 CEDE52E9
	static void REMOVE_PARTICLE_FX_IN_RANGE(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0xDD19FA1C6D657305, p0, p1, p2, p3); } // DD19FA1C6D657305 7EB8F275
	static BOOL DOES_PARTICLE_FX_LOOPED_EXIST(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x74AFEF0D2E1E409B, p0); } // 74AFEF0D2E1E409B CBF91D2A
	static void SET_PARTICLE_FX_LOOPED_OFFSETS(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6) { NativeInvoke::Invoke<scrVoid>(0xF7DDEBEC43483C43, p0, p1, p2, p3, p4, p5, p6); } // F7DDEBEC43483C43 641F7790
	static void SET_PARTICLE_FX_LOOPED_EVOLUTION(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x5F0C4B5B1C393BE2, p0, p1, p2); } // 5F0C4B5B1C393BE2 1CBC1373
	static void SET_PARTICLE_FX_LOOPED_COLOUR(scrAny p0, float p1, float p2, float p3, BOOL p4) { NativeInvoke::Invoke<scrVoid>(0x7F8F65877F88783B, p0, p1, p2, p3, p4); } // 7F8F65877F88783B 5219D530
	static void SET_PARTICLE_FX_LOOPED_ALPHA(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x726845132380142E, p0, p1); } // 726845132380142E 5ED49BE1
	static void SET_PARTICLE_FX_LOOPED_SCALE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xB44250AAA456492D, p0, p1); } // B44250AAA456492D 099B8B49
	static void _0xDCB194B85EF7B541(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xDCB194B85EF7B541, p0, p1); } // DCB194B85EF7B541 233DE879
	static void SET_PARTICLE_FX_CAM_INSIDE_VEHICLE(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xEEC4047028426510, p0); } // EEC4047028426510 19EC0001
	static void _0xACEE6F360FC1F6B6(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xACEE6F360FC1F6B6, p0, p1); } // ACEE6F360FC1F6B6 6B125A02
	static void _0x96EF97DAEB89BEF5(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x96EF97DAEB89BEF5, p0); } // 96EF97DAEB89BEF5 D938DEE0
	static void SET_PARTICLE_FX_BLOOD_SCALE(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x5F6DF3D92271E8A1, p0); } // 5F6DF3D92271E8A1 18136DE0
	static void SET_CAMERA_ENDTIME(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xD821490579791273, p0); } // D821490579791273 C61C75E9
	static void _0x9DCE1F0F78260875(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x9DCE1F0F78260875, p0); } // 9DCE1F0F78260875 CE8B8748
	static void _0x27E32866E9A5C416(float p0) { NativeInvoke::Invoke<scrVoid>(0x27E32866E9A5C416, p0); } // 27E32866E9A5C416
	static void _0xBB90E12CAC1DAB25(float p0) { NativeInvoke::Invoke<scrVoid>(0xBB90E12CAC1DAB25, p0); } // BB90E12CAC1DAB25
	static void _0xCA4AE345A153D573(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xCA4AE345A153D573, p0); } // CA4AE345A153D573
	static void _0x54E22EA2C1956A8D(float p0) { NativeInvoke::Invoke<scrVoid>(0x54E22EA2C1956A8D, p0); } // 54E22EA2C1956A8D
	static void _0x949F397A288B28B3(float p0) { NativeInvoke::Invoke<scrVoid>(0x949F397A288B28B3, p0); } // 949F397A288B28B3
	static void _0x9B079E5221D984D3(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x9B079E5221D984D3, p0); } // 9B079E5221D984D3
	static void _0x6C38AF3693A69A91(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x6C38AF3693A69A91, p0); } // 6C38AF3693A69A91
	static void WASH_DECALS_IN_RANGE(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x9C30613D50A6ADEF, p0, p1, p2, p3, p4); } // 9C30613D50A6ADEF DEECBC57
	static void WASH_DECALS_FROM_VEHICLE(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x5B712761429DBC14, p0, p1); } // 5B712761429DBC14 2929F11A
	static void FADE_DECALS_IN_RANGE(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0xD77EDADB0420E6E0, p0, p1, p2, p3, p4); } // D77EDADB0420E6E0 F81E884A
	static void REMOVE_DECALS_IN_RANGE(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x5D6B2D4830A67C62, p0, p1, p2, p3); } // 5D6B2D4830A67C62 06A619A0
	static void REMOVE_DECALS_FROM_OBJECT(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xCCF71CBDDF5B6CB9, p0); } // CCF71CBDDF5B6CB9 8B67DCA7
	static void REMOVE_DECALS_FROM_OBJECT_FACING(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0xA6F6F70FDC6D144C, p0, p1, p2, p3); } // A6F6F70FDC6D144C F4999A55
	static void REMOVE_DECALS_FROM_VEHICLE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xE91F1B65F2B48D57, p0); } // E91F1B65F2B48D57 831D06CA
	static scrAny ADD_DECAL(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12, float p13, float p14, float p15, float p16, BOOL p17, BOOL p18, BOOL p19) { return NativeInvoke::Invoke<scrAny>(0xB302244A1839BDAD, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19); } // B302244A1839BDAD EAD0C412
	static scrAny ADD_PETROL_DECAL(float p0, float p1, float p2, float p3, float p4, float p5) { return NativeInvoke::Invoke<scrAny>(0x4F5212C7AD880DF8, p0, p1, p2, p3, p4, p5); } // 4F5212C7AD880DF8 1259DF42
	static void _0x99AC7F0D8B9C893D(float p0) { NativeInvoke::Invoke<scrVoid>(0x99AC7F0D8B9C893D, p0); } // 99AC7F0D8B9C893D E3938B0B
	static void _0x967278682CB6967A(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x967278682CB6967A, p0, p1, p2, p3); } // 967278682CB6967A BAEC6ADD
	static void SET_CAMERA_CAMERA_FORWARD() { NativeInvoke::Invoke<scrVoid>(0x0A123435A26C36CD); } // 0A123435A26C36CD CCCA6855
	static void REMOVE_DECAL(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xED3F346429CCD659, p0); } // ED3F346429CCD659 A4363188
	static BOOL IS_DECAL_ALIVE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xC694D74949CAFD0C, p0); } // C694D74949CAFD0C CDD4A61A
	static float GET_DECAL_WASH_LEVEL(scrAny p0) { return NativeInvoke::Invoke<float>(0x323F647679A09103, p0); } // 323F647679A09103 054448EF
	static void _0xD9454B5752C857DC() { NativeInvoke::Invoke<scrVoid>(0xD9454B5752C857DC); } // D9454B5752C857DC EAB6417C
	static void _0x27CFB1B1E078CB2D() { NativeInvoke::Invoke<scrVoid>(0x27CFB1B1E078CB2D); } // 27CFB1B1E078CB2D C2703B88
	static void _0x4B5CFC83122DF602() { NativeInvoke::Invoke<scrVoid>(0x4B5CFC83122DF602); } // 4B5CFC83122DF602 A706E84D
	static BOOL _0x2F09F7976C512404(float p0, float p1, float p2, float p3) { return NativeInvoke::Invoke<BOOL>(0x2F09F7976C512404, p0, p1, p2, p3); } // 2F09F7976C512404 242C6A04
	static void _0x8A35C742130C6080(scrAny p0, scrAny *p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0x8A35C742130C6080, p0, p1, p2); } // 8A35C742130C6080 335695CF
	static void _0xB7ED70C49521A61D(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xB7ED70C49521A61D, p0); } // B7ED70C49521A61D 7B786555
	static void MOVE_VEHICLE_DECALS(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x84C8D7C2D30D3280, p0, p1); } // 84C8D7C2D30D3280 CE9E6CF2
	static BOOL _0x428BDCB9DA58DA53(scrAny p0, scrAny p1, scrAny p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12, scrAny p13) { return NativeInvoke::Invoke<BOOL>(0x428BDCB9DA58DA53, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } // 428BDCB9DA58DA53 12077738
	static void _0xD2300034310557E4(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xD2300034310557E4, p0, p1); } // D2300034310557E4 667046A8
	static scrAny _0xFE26117A5841B2FF(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xFE26117A5841B2FF, p0, p1); } // FE26117A5841B2FF 4F4D76E8
	static BOOL _0x060D935D3981A275(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x060D935D3981A275, p0, p1); } // 060D935D3981A275 6D58F73B
	static void _0x0E4299C549F0D1F1(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x0E4299C549F0D1F1, p0); } // 0E4299C549F0D1F1 9BABCBA4
	static void _0x02369D5C8A51FDCF(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x02369D5C8A51FDCF, p0); } // 02369D5C8A51FDCF FDF6D8DA
	static void _0x46D1A61A21F566FC(float p0) { NativeInvoke::Invoke<scrVoid>(0x46D1A61A21F566FC, p0); } // 46D1A61A21F566FC 2056A015
	static void _0x2A2A52824DB96700(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x2A2A52824DB96700, p0); } // 2A2A52824DB96700 0F486429
	static void _0x1600FD8CF72EBC12(float p0) { NativeInvoke::Invoke<scrVoid>(0x1600FD8CF72EBC12, p0); } // 1600FD8CF72EBC12 D87CC710
	static void _0xEFB55E7C25D3B3BE() { NativeInvoke::Invoke<scrVoid>(0xEFB55E7C25D3B3BE); } // EFB55E7C25D3B3BE E29EE145
	static void _0xA44FF770DFBC5DAE() { NativeInvoke::Invoke<scrVoid>(0xA44FF770DFBC5DAE); } // A44FF770DFBC5DAE
	static void DISABLE_VEHICLE_DISTANTLIGHTS(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xC9F98AC1884E73A2, p0); } // C9F98AC1884E73A2 7CFAE36F
	static void _0x03300B57FCAC6DDB(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x03300B57FCAC6DDB, p0); } // 03300B57FCAC6DDB 60F72371
	static void SET_TIMECYCLE_MODIFIER(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x2C933ABF17A1DF41, p0); } // 2C933ABF17A1DF41 A81F3638
	static void SET_TIMECYCLE_MODIFIER_STRENGTH(float p0) { NativeInvoke::Invoke<scrVoid>(0x82E7FFCD5B2326B3, p0); } // 82E7FFCD5B2326B3 458F4F45
	static void SET_TRANSITION_TIMECYCLE_MODIFIER(scrAny *p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x3BCF567485E1971C, p0, p1); } // 3BCF567485E1971C BB2BA72A
	static void _0x1CBA05AE7BD7EE05(float p0) { NativeInvoke::Invoke<scrVoid>(0x1CBA05AE7BD7EE05, p0); } // 1CBA05AE7BD7EE05 56345F6B
	static void CLEAR_TIMECYCLE_MODIFIER() { NativeInvoke::Invoke<scrVoid>(0x0F07E7745A236711); } // 0F07E7745A236711 8D8DF8EE
	static scrAny GET_TIMECYCLE_MODIFIER_INDEX() { return NativeInvoke::Invoke<scrAny>(0xFDF3D97C674AFB66); } // FDF3D97C674AFB66 594FEEC4
	static scrAny _0x459FD2C8D0AB78BC() { return NativeInvoke::Invoke<scrAny>(0x459FD2C8D0AB78BC); } // 459FD2C8D0AB78BC 03C44E4B
	static void PUSH_TIMECYCLE_MODIFIER() { NativeInvoke::Invoke<scrVoid>(0x58F735290861E6B4); } // 58F735290861E6B4 7E082045
	static void POP_TIMECYCLE_MODIFIER() { NativeInvoke::Invoke<scrVoid>(0x3C8938D7D872211E); } // 3C8938D7D872211E 79D7D235
	static void _0xBBF327DED94E4DEB(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xBBF327DED94E4DEB, p0); } // BBF327DED94E4DEB 85BA15A4
	static void _0xBDEB86F4D5809204(float p0) { NativeInvoke::Invoke<scrVoid>(0xBDEB86F4D5809204, p0); } // BDEB86F4D5809204 9559BB38
	static void _0xBF59707B3E5ED531(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xBF59707B3E5ED531, p0); } // BF59707B3E5ED531 554BA16E
	static void _0x1A8E2C8B9CF4549C(scrAny *p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x1A8E2C8B9CF4549C, p0, p1); } // 1A8E2C8B9CF4549C E8F538B5
	static void _0x15E33297C3E8DC60(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x15E33297C3E8DC60, p0); } // 15E33297C3E8DC60 805BAB08
	static void _0x5096FD9CCB49056D(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x5096FD9CCB49056D, p0); } // 5096FD9CCB49056D 908A335E
	static void _0x92CCC17A7A2285DA() { NativeInvoke::Invoke<scrVoid>(0x92CCC17A7A2285DA); } // 92CCC17A7A2285DA 6776720A
	static scrAny _0xBB0527EC6341496D() { return NativeInvoke::Invoke<scrAny>(0xBB0527EC6341496D); } // BB0527EC6341496D
	static void _0x2BF72AD5B41AA739() { NativeInvoke::Invoke<scrVoid>(0x2BF72AD5B41AA739); } // 2BF72AD5B41AA739
	static scrAny REQUEST_SCALEFORM_MOVIE(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0x11FE353CF9733E6F, p0); } // 11FE353CF9733E6F C67E3DCB
	static scrAny _0xC514489CFB8AF806(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0xC514489CFB8AF806, p0); } // C514489CFB8AF806 7CC8057D
	static scrAny _0xBD06C611BB9048C2(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0xBD06C611BB9048C2, p0); } // BD06C611BB9048C2
	static BOOL HAS_SCALEFORM_MOVIE_LOADED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x85F01B8D5B90570E, p0); } // 85F01B8D5B90570E DDFB6448
	static BOOL _0x8217150E1217EBFD(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x8217150E1217EBFD, p0); } // 8217150E1217EBFD 1DFE8D8A
	static void SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x1D132D614DD86811, p0); } // 1D132D614DD86811 5FED3BA1
	static void _0x6D8EB211944DCE08(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x6D8EB211944DCE08, p0, p1); } // 6D8EB211944DCE08 18C9DE8D
	static void DRAW_SCALEFORM_MOVIE(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8) { NativeInvoke::Invoke<scrVoid>(0x54972ADAF0294A93, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 54972ADAF0294A93 48DA6A58
	static void _0x0DF606929C105BE1(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x0DF606929C105BE1, p0, p1, p2, p3, p4); } // 0DF606929C105BE1 7B48E696
	static void _0xCF537FDE4FBD4CE5(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0xCF537FDE4FBD4CE5, p0, p1, p2, p3, p4, p5); } // CF537FDE4FBD4CE5 9C59FC06
	static void _0x87D51D72255D4E78(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12, scrAny p13) { NativeInvoke::Invoke<scrVoid>(0x87D51D72255D4E78, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } // 87D51D72255D4E78 C4F63A89
	static void _0x1CE592FDC749D6F5(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12, scrAny p13) { NativeInvoke::Invoke<scrVoid>(0x1CE592FDC749D6F5, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } // 1CE592FDC749D6F5 899933C8
	static void _0xFBD96D87AC96D533(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xFBD96D87AC96D533, p0, p1); } // FBD96D87AC96D533 7AB77B57
	static void _0xD0837058AE2E4BEE(scrAny p0, scrAny *p1, float p2, float p3, float p4, float p5, float p6) { NativeInvoke::Invoke<scrVoid>(0xD0837058AE2E4BEE, p0, p1, p2, p3, p4, p5, p6); } // D0837058AE2E4BEE 557EDA1D
	static void _0x51BC1ED3CC44E8F7(scrAny p0, scrAny *p1, scrAny *p2, scrAny *p3, scrAny *p4, scrAny *p5, scrAny *p6) { NativeInvoke::Invoke<scrVoid>(0x51BC1ED3CC44E8F7, p0, p1, p2, p3, p4, p5, p6); } // 51BC1ED3CC44E8F7 91A7FCEB
	static void _0xEF662D8D57E290B1(scrAny p0, scrAny *p1, float p2, float p3, float p4, float p5, float p6, scrAny *p7, scrAny *p8, scrAny *p9, scrAny *p10, scrAny *p11) { NativeInvoke::Invoke<scrVoid>(0xEF662D8D57E290B1, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // EF662D8D57E290B1 6EAF56DE
	static BOOL _0x98C494FD5BDFBFD5(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x98C494FD5BDFBFD5, p0, p1); } // 98C494FD5BDFBFD5 5D66CE1E
	static BOOL _0xF6E48914C7A8694E(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0xF6E48914C7A8694E, p0, p1); } // F6E48914C7A8694E 215ABBE8
	static BOOL _0xAB58C27C2E6123C6(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xAB58C27C2E6123C6, p0); } // AB58C27C2E6123C6 F6015178
	static BOOL _0xB9449845F73F5E9C(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xB9449845F73F5E9C, p0); } // B9449845F73F5E9C 5E219B67
	static void _0xC6796A8FFA375E53() { NativeInvoke::Invoke<scrVoid>(0xC6796A8FFA375E53); } // C6796A8FFA375E53 02DBF2D7
	static scrAny _0xC50AA39A577AF886() { return NativeInvoke::Invoke<scrAny>(0xC50AA39A577AF886); } // C50AA39A577AF886 2F38B526
	static BOOL _0x768FF8961BA904D6(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x768FF8961BA904D6, p0); } // 768FF8961BA904D6 5CD7C3C0
	static scrAny _0x2DE7EFA66B906036(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x2DE7EFA66B906036, p0); } // 2DE7EFA66B906036 2CFB0E6D
	static scrAny SITTING_TV(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xE1E258829A885245, p0); } // E1E258829A885245 516862EB
	static void _0xC3D0841A0CC546A6(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xC3D0841A0CC546A6, p0); } // C3D0841A0CC546A6 716777CB
	static void _0xD69736AAE04DB51A(float p0) { NativeInvoke::Invoke<scrVoid>(0xD69736AAE04DB51A, p0); } // D69736AAE04DB51A 9A01FFDA
	static void _0xC58424BA936EB458(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xC58424BA936EB458, p0); } // C58424BA936EB458 0D4AE8CB
	static void _0x80338406F3475E55(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x80338406F3475E55, p0); } // 80338406F3475E55 3AC9CB55
	static void _0x362E2D3FE93A9959() { NativeInvoke::Invoke<scrVoid>(0x362E2D3FE93A9959); } // 362E2D3FE93A9959 386CE0B8
	static void _0xAE4E8157D9ECF087() { NativeInvoke::Invoke<scrVoid>(0xAE4E8157D9ECF087); } // AE4E8157D9ECF087 2E80DB52
	static void _0xBA7148484BD90365(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xBA7148484BD90365, p0); } // BA7148484BD90365 4DAAD55B
	static void _0xE83A3E3557A56640(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xE83A3E3557A56640, p0); } // E83A3E3557A56640 CCBF0334
	static scrAny _0x5E657EF1099EDD65(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x5E657EF1099EDD65, p0); } // 5E657EF1099EDD65 91A081A1
	static void _0xEC52C631A1831C03(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xEC52C631A1831C03, p0); } // EC52C631A1831C03 83A9811D
	static void _0x9304881D6F6537EA(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x9304881D6F6537EA, p0); } // 9304881D6F6537EA 7AF85862
	static BOOL _0xDF6E5987D2B4D140(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xDF6E5987D2B4D140, p0); } // DF6E5987D2B4D140 79B43255
	static void _0xF44A5456AC3F4F97(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xF44A5456AC3F4F97, p0); } // F44A5456AC3F4F97 03D87600
	static BOOL _0xD1C7CB175E012964(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xD1C7CB175E012964, p0); } // D1C7CB175E012964 E9183D3A
	static void SET_TV_CHANNEL(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xBAABBB23EB6E484E, p0); } // BAABBB23EB6E484E 41A8A627
	static scrAny GET_TV_CHANNEL() { return NativeInvoke::Invoke<scrAny>(0xFC1E275A90D39995); } // FC1E275A90D39995 6B96145A
	static void SET_TV_VOLUME(float p0) { NativeInvoke::Invoke<scrVoid>(0x2982BF73F66E9DDC, p0); } // 2982BF73F66E9DDC F3504F4D
	static float GET_TV_VOLUME() { return NativeInvoke::Invoke<float>(0x2170813D3DD8661B); } // 2170813D3DD8661B 39555CF0
	static void DRAW_TV_CHANNEL(float p0, float p1, float p2, float p3, float p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8) { NativeInvoke::Invoke<scrVoid>(0xFDDC2B4ED3C69DF0, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // FDDC2B4ED3C69DF0 8129EF89
	static void _0xF7B38B8305F1FE8B(scrAny p0, scrAny *p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xF7B38B8305F1FE8B, p0, p1, p2); } // F7B38B8305F1FE8B B262DE67
	static void _0x2201C576FACAEBE8(scrAny p0, scrAny *p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x2201C576FACAEBE8, p0, p1, p2); } // 2201C576FACAEBE8 78C4DCBE
	static void _0xBEB3D46BB7F043C0(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xBEB3D46BB7F043C0, p0); } // BEB3D46BB7F043C0 CBE7068F
	static BOOL _0x0AD973CA1E077B60(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x0AD973CA1E077B60, p0); } // 0AD973CA1E077B60 4D1EB0FB
	static void _0x74C180030FDE4B69(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x74C180030FDE4B69, p0); } // 74C180030FDE4B69 796DE696
	static void _0xD1C55B110E4DF534(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xD1C55B110E4DF534, p0); } // D1C55B110E4DF534 D99EC000
	static void ENABLE_MOVIE_SUBTITLES(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x873FA65C778AD970, p0); } // 873FA65C778AD970 C2DEBA3D
	static scrAny _0xD3A10FC7FD8D98CD() { return NativeInvoke::Invoke<scrAny>(0xD3A10FC7FD8D98CD); } // D3A10FC7FD8D98CD E40A0F1A
	static BOOL _0xF1CEA8A4198D8E9A(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xF1CEA8A4198D8E9A, p0); } // F1CEA8A4198D8E9A 2E7D9B98
	static BOOL _0x98C4FE6EC34154CA(scrAny *p0, scrAny p1, scrAny p2, float p3, float p4, float p5) { return NativeInvoke::Invoke<BOOL>(0x98C4FE6EC34154CA, p0, p1, p2, p3, p4, p5); } // 98C4FE6EC34154CA 9A0E3BFE
	static void _0x7A42B2E236E71415() { NativeInvoke::Invoke<scrVoid>(0x7A42B2E236E71415); } // 7A42B2E236E71415 431AA036
	static void _0x108BE26959A9D9BB(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x108BE26959A9D9BB, p0); } // 108BE26959A9D9BB 24A7A7F6
	static void _0xA356990E161C9E65(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xA356990E161C9E65, p0); } // A356990E161C9E65 A1CB6C94
	static void _0x1C4FC5752BCD8E48(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12) { NativeInvoke::Invoke<scrVoid>(0x1C4FC5752BCD8E48, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // 1C4FC5752BCD8E48 3B637AA7
	static void _0x5CE62918F8D703C7(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9, scrAny p10, scrAny p11) { NativeInvoke::Invoke<scrVoid>(0x5CE62918F8D703C7, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 5CE62918F8D703C7 DF552973
	static void _0x2206BF9A37B7F724(scrAny *p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x2206BF9A37B7F724, p0, p1, p2); } // 2206BF9A37B7F724 1D980479
	static void _0x068E835A1D0DC0E3(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x068E835A1D0DC0E3, p0); } // 068E835A1D0DC0E3 06BB5CDA
	static BOOL _0x36AD3E690DA5ACEB(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x36AD3E690DA5ACEB, p0); } // 36AD3E690DA5ACEB 089D5921
	static void _0xB4EDDC19532BFB85() { NativeInvoke::Invoke<scrVoid>(0xB4EDDC19532BFB85); } // B4EDDC19532BFB85 4E6D875B
	static void _0xD2209BE128B5418C(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xD2209BE128B5418C, p0); } // D2209BE128B5418C
}

namespace STATS
{
	static scrAny _0xEB0A72181D4AA4AD(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xEB0A72181D4AA4AD, p0); } // EB0A72181D4AA4AD 84BDD475
	static BOOL STAT_LOAD(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xA651443F437B1CE6, p0); } // A651443F437B1CE6 9E5629F4
	static BOOL STAT_SAVE(scrAny p0, BOOL p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0xE07BCA305B82D2FD, p0, p1, p2); } // E07BCA305B82D2FD E10A7CA4
	static void _0x5688585E6D563CD8(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x5688585E6D563CD8, p0); } // 5688585E6D563CD8 C62406A6
	static BOOL STAT_LOAD_PENDING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xA1750FFAFA181661, p0); } // A1750FFAFA181661 4E9AC983
	static BOOL STAT_SAVE_PENDING() { return NativeInvoke::Invoke<BOOL>(0x7D3A583856F2C5AC); } // 7D3A583856F2C5AC C3FD3822
	static BOOL _0xBBB6AD006F1BBEA3() { return NativeInvoke::Invoke<BOOL>(0xBBB6AD006F1BBEA3); } // BBB6AD006F1BBEA3 A3407CA3
	static scrAny STAT_DELETE_SLOT(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x49A49BED12794D70, p0); } // 49A49BED12794D70 2F171B94
	static BOOL _0x0D0A9F0E7BD91E3C(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x0D0A9F0E7BD91E3C, p0); } // 0D0A9F0E7BD91E3C 7A299C13
	static BOOL _0x7F2C4CDF2E82DF4C(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x7F2C4CDF2E82DF4C, p0); } // 7F2C4CDF2E82DF4C 0BF0F4B2
	static scrAny _0xE496A53BA5F50A56(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xE496A53BA5F50A56, p0); } // E496A53BA5F50A56 CE6B62B5
	static void _0xF434A10BA01C37D0(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xF434A10BA01C37D0, p0); } // F434A10BA01C37D0 CE7A2411
	static BOOL _0x7E6946F68A38B74F(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x7E6946F68A38B74F, p0); } // 7E6946F68A38B74F 22804C20
	static void _0xA8733668D1047B51(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA8733668D1047B51, p0); } // A8733668D1047B51 395D18B1
	static BOOL _0xECB41AC6AB754401() { return NativeInvoke::Invoke<BOOL>(0xECB41AC6AB754401); } // ECB41AC6AB754401 ED7000C8
	static void _0x9B4BD21D69B1E609() { NativeInvoke::Invoke<scrVoid>(0x9B4BD21D69B1E609); } // 9B4BD21D69B1E609
	static BOOL _0xC0E0D686DDFC6EAE() { return NativeInvoke::Invoke<BOOL>(0xC0E0D686DDFC6EAE); } // C0E0D686DDFC6EAE 099FCC86
	static BOOL STAT_SET_INT(scrAny p0, scrAny p1, BOOL p2) { return NativeInvoke::Invoke<BOOL>(0xB3271D7AB655B441, p0, p1, p2); } // B3271D7AB655B441 C9CC1C5C
	static BOOL STAT_SET_FLOAT(scrAny p0, float p1, BOOL p2) { return NativeInvoke::Invoke<BOOL>(0x4851997F37FE9B3C, p0, p1, p2); } // 4851997F37FE9B3C 6CEA96F2
	static BOOL STAT_SET_BOOL(scrAny p0, BOOL p1, BOOL p2) { return NativeInvoke::Invoke<BOOL>(0x4B33C4243DE0C432, p0, p1, p2); } // 4B33C4243DE0C432 55D79DFB
	static BOOL _0x17695002FD8B2AE0(scrAny p0, scrAny *p1, BOOL p2) { return NativeInvoke::Invoke<BOOL>(0x17695002FD8B2AE0, p0, p1, p2); } // 17695002FD8B2AE0 C1224AA7
	static BOOL STAT_SET_DATE(scrAny p0, scrAny *p1, scrAny p2, BOOL p3) { return NativeInvoke::Invoke<BOOL>(0x2C29BFB64F4FCBE4, p0, p1, p2, p3); } // 2C29BFB64F4FCBE4 36BE807B
	static BOOL STAT_SET_STRING(scrAny p0, scrAny *p1, BOOL p2) { return NativeInvoke::Invoke<BOOL>(0xA87B2335D12531D7, p0, p1, p2); } // A87B2335D12531D7 B1EF2E21
	static BOOL STAT_SET_POS(scrAny p0, float p1, float p2, float p3, BOOL p4) { return NativeInvoke::Invoke<BOOL>(0xDB283FDE680FE72E, p0, p1, p2, p3, p4); } // DB283FDE680FE72E 1192C9A3
	static BOOL STAT_SET_MASKED_INT(scrAny p0, scrAny p1, scrAny p2, scrAny p3, BOOL p4) { return NativeInvoke::Invoke<BOOL>(0x7BBB1B54583ED410, p0, p1, p2, p3, p4); } // 7BBB1B54583ED410 2CBAA739
	static BOOL STAT_SET_USER_ID(scrAny p0, scrAny *p1, BOOL p2) { return NativeInvoke::Invoke<BOOL>(0x8CDDF1E452BABE11, p0, p1, p2); } // 8CDDF1E452BABE11 DBE78ED7
	static BOOL _0xC2F84B7F9C4D0C61(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<BOOL>(0xC2F84B7F9C4D0C61, p0, p1); } // C2F84B7F9C4D0C61 A286F015
	static BOOL STAT_GET_INT(scrAny p0, int *p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0x767FBC2AC802EF3D, p0, p1, p2); } // 767FBC2AC802EF3D 1C6FE43E
	static BOOL STAT_GET_FLOAT(scrAny p0, scrAny *p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0xD7AE6C9C9C6AC54C, p0, p1, p2); } // D7AE6C9C9C6AC54C FCBDA612
	static BOOL STAT_GET_BOOL(scrAny p0, scrAny *p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0x11B5E6D2AE73F48E, p0, p1, p2); } // 11B5E6D2AE73F48E 28A3DD2B
	static BOOL STAT_GET_DATE(scrAny p0, scrAny *p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<BOOL>(0x8B0FACEFC36C824B, p0, p1, p2, p3); } // 8B0FACEFC36C824B D762D16C
	static scrAny STAT_GET_STRING(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xE50384ACC2C3DB74, p0, p1); } // E50384ACC2C3DB74 10CE4BDE
	static BOOL STAT_GET_POS(scrAny p0, scrAny *p1, scrAny *p2, scrAny *p3, scrAny p4) { return NativeInvoke::Invoke<BOOL>(0x350F82CCB186AA1B, p0, p1, p2, p3, p4); } // 350F82CCB186AA1B C846ECCE
	static BOOL STAT_GET_MASKED_INT(scrAny p0, scrAny *p1, scrAny p2, scrAny p3, scrAny p4) { return NativeInvoke::Invoke<BOOL>(0x655185A06D9EEAAB, p0, p1, p2, p3, p4); } // 655185A06D9EEAAB E9D9B70F
	static scrAny STAT_GET_USER_ID(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x2365C388E393BBE2, p0); } // 2365C388E393BBE2 E2E8B6BA
	static scrAny _0x5473D4195058B2E4(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x5473D4195058B2E4, p0); } // 5473D4195058B2E4 1544B29F
	static BOOL _0x69FF13266D7296DA(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x69FF13266D7296DA, p0, p1); } // 69FF13266D7296DA 3507D253
	static void STAT_INCREMENT(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x9B5A68C6489E9909, p0, p1); } // 9B5A68C6489E9909 DFC5F71E
	static BOOL _0x5A556B229A169402() { return NativeInvoke::Invoke<BOOL>(0x5A556B229A169402); } // 5A556B229A169402 46F21343
	static BOOL _0xB1D2BB1E1631F5B1() { return NativeInvoke::Invoke<BOOL>(0xB1D2BB1E1631F5B1); } // B1D2BB1E1631F5B1 02F283CE
	static BOOL _0xBED9F5693F34ED17(scrAny p0, scrAny p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0xBED9F5693F34ED17, p0, p1, p2); } // BED9F5693F34ED17 C4110917
	static void _0x26D7399B9587FE89(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x26D7399B9587FE89, p0); } // 26D7399B9587FE89 343B27E2
	static void _0xA78B8FA58200DA56(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA78B8FA58200DA56, p0); } // A78B8FA58200DA56 E3247582
	static scrAny _0xE0E854F5280FB769(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xE0E854F5280FB769, p0); } // E0E854F5280FB769 FD66A429
	static scrAny _0xF2D4B2FE415AAFC3(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xF2D4B2FE415AAFC3, p0); } // F2D4B2FE415AAFC3 9B431236
	static scrAny _0x7583B4BE4C5A41B5(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x7583B4BE4C5A41B5, p0); } // 7583B4BE4C5A41B5 347B4436
	static scrAny _0x2CE056FF3723F00B(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x2CE056FF3723F00B, p0); } // 2CE056FF3723F00B 2C1D6C31
	static void _0x68F01422BE1D838F(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x68F01422BE1D838F, p0, p1); } // 68F01422BE1D838F 24DD4929
	static scrAny _0xF4D8E7AC2A27758C(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xF4D8E7AC2A27758C, p0); } // F4D8E7AC2A27758C DFC25D66
	static scrAny _0x94F12ABF9C79E339(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x94F12ABF9C79E339, p0); } // 94F12ABF9C79E339 CA160BCC
	static scrAny _0x80C75307B1C42837(scrAny p0, BOOL p1, BOOL p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0x80C75307B1C42837, p0, p1, p2, p3); } // 80C75307B1C42837 B5BF87B2
	static scrAny _0x61E111E323419E07(scrAny p0, BOOL p1, BOOL p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0x61E111E323419E07, p0, p1, p2, p3); } // 61E111E323419E07 1F938864
	static scrAny _0xC4BB08EE7907471E(scrAny p0, BOOL p1, BOOL p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0xC4BB08EE7907471E, p0, p1, p2, p3); } // C4BB08EE7907471E 3F8E893B
	static scrAny _0xD16C2AD6B8E32854(scrAny p0, BOOL p1, BOOL p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0xD16C2AD6B8E32854, p0, p1, p2, p3); } // D16C2AD6B8E32854 FB93C5A2
	static BOOL STAT_GET_BOOL_MASKED(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0x10FE3F1B79F9B071, p0, p1, p2); } // 10FE3F1B79F9B071 6ACE1B7D
	static BOOL STAT_SET_BOOL_MASKED(scrAny p0, BOOL p1, scrAny p2, BOOL p3) { return NativeInvoke::Invoke<BOOL>(0x5BC62EC1937B9E5B, p0, p1, p2, p3); } // 5BC62EC1937B9E5B 7842C4D6
	static void _0x5009DFD741329729(scrAny *p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x5009DFD741329729, p0, p1); } // 5009DFD741329729 61ECC465
	static void PLAYSTATS_NPC_INVITE(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x93054C88E6AA7C44, p0); } // 93054C88E6AA7C44 598C06F3
	static void PLAYSTATS_AWARD_XP(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x46F917F6B4128FE4, p0, p1, p2); } // 46F917F6B4128FE4 8770017B
	static void PLAYSTATS_RANK_UP(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xC7F2DE41D102BFB4, p0); } // C7F2DE41D102BFB4 56AFB9F5
	static void _0x098760C7461724CD() { NativeInvoke::Invoke<scrVoid>(0x098760C7461724CD); } // 098760C7461724CD 896CDF8D
	static void _0xA071E0ED98F91286(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xA071E0ED98F91286, p0, p1); } // A071E0ED98F91286 1A66945F
	static void _0xC5BE134EC7BA96A0(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0xC5BE134EC7BA96A0, p0, p1, p2, p3, p4); } // C5BE134EC7BA96A0 C960E161
	static void PLAYSTATS_MISSION_STARTED(scrAny *p0, scrAny p1, scrAny p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0xC19A2925C34D2231, p0, p1, p2, p3); } // C19A2925C34D2231 3AAB699C
	static void PLAYSTATS_MISSION_OVER(scrAny *p0, scrAny p1, scrAny p2, BOOL p3, BOOL p4, BOOL p5) { NativeInvoke::Invoke<scrVoid>(0x7C4BB33A8CED7324, p0, p1, p2, p3, p4, p5); } // 7C4BB33A8CED7324 5B90B5FF
	static void PLAYSTATS_MISSION_CHECKPOINT(scrAny *p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0xC900596A63978C1D, p0, p1, p2, p3); } // C900596A63978C1D CDC52280
	static void _0x71862B1D855F32E1(scrAny *p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x71862B1D855F32E1, p0, p1, p2, p3); } // 71862B1D855F32E1 AC2C7C63
	static void _0x121FB4DDDC2D5291(scrAny p0, scrAny p1, scrAny p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x121FB4DDDC2D5291, p0, p1, p2, p3); } // 121FB4DDDC2D5291 413539BC
	static void PLAYSTATS_RACE_CHECKPOINT(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x9C375C315099DDE4, p0, p1, p2, p3, p4); } // 9C375C315099DDE4 580D5508
	static BOOL _0x6DEE77AFF8C21BD1(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x6DEE77AFF8C21BD1, p0, p1); } // 6DEE77AFF8C21BD1 489E27E7
	static void PLAYSTATS_MATCH_STARTED(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6) { NativeInvoke::Invoke<scrVoid>(0xBC80E22DED931E3D, p0, p1, p2, p3, p4, p5, p6); } // BC80E22DED931E3D 2BDE85C1
	static void PLAYSTATS_SHOP_ITEM(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x176852ACAAC173D1, p0, p1, p2, p3, p4); } // 176852ACAAC173D1 A4746384
	static void _0x1CAE5D2E3F9A07F0(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0x1CAE5D2E3F9A07F0, p0, p1, p2, p3, p4, p5); } // 1CAE5D2E3F9A07F0 6602CED6
	static void _0xCB00196B31C39EB1(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0xCB00196B31C39EB1, p0, p1, p2, p3); } // CB00196B31C39EB1 759E0EC9
	static void _0x2B69F5074C894811(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x2B69F5074C894811, p0, p1, p2, p3); } // 2B69F5074C894811 62073DF7
	static void _0x7EEC2A316C250073(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x7EEC2A316C250073, p0, p1, p2); } // 7EEC2A316C250073 30558CFD
	static void _0xADDD1C754E2E2914(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9) { NativeInvoke::Invoke<scrVoid>(0xADDD1C754E2E2914, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // ADDD1C754E2E2914 06CE3692
	static void _0x79AB33F0FBFAC40C(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x79AB33F0FBFAC40C, p0); } // 79AB33F0FBFAC40C 8D5C7B37
	static void _0xDDF24D535060F811(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xDDF24D535060F811, p0, p1); } // DDF24D535060F811 37D152BB
	static void PLAYSTATS_FRIEND_ACTIVITY(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x0F71DE29AB2258F1, p0, p1); } // 0F71DE29AB2258F1 D1FA1BDB
	static void PLAYSTATS_ODDJOB_DONE(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x69DEA3E9DB727B4C, p0, p1, p2); } // 69DEA3E9DB727B4C FE14A8EA
	static void PLAYSTATS_PROP_CHANGE(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0xBA739D6D5A05D6E7, p0, p1, p2, p3); } // BA739D6D5A05D6E7 25740A1D
	static void PLAYSTATS_CLOTH_CHANGE(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x34B973047A2268B9, p0, p1, p2, p3, p4); } // 34B973047A2268B9 3AFF9E58
	static void _0xE95C8A1875A02CA4(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xE95C8A1875A02CA4, p0, p1, p2); } // E95C8A1875A02CA4 79716890
	static void PLAYSTATS_CHEAT_APPLIED(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x6058665D72302D3F, p0); } // 6058665D72302D3F 345166F3
	static void _0xF8C54A461C3E11DC(scrAny *p0, scrAny *p1, scrAny *p2, scrAny *p3) { NativeInvoke::Invoke<scrVoid>(0xF8C54A461C3E11DC, p0, p1, p2, p3); } // F8C54A461C3E11DC 04181752
	static void _0xA736CF7FB7C5BFF4(scrAny *p0, scrAny *p1, scrAny *p2, scrAny *p3) { NativeInvoke::Invoke<scrVoid>(0xA736CF7FB7C5BFF4, p0, p1, p2, p3); } // A736CF7FB7C5BFF4 31002201
	static void _0x14E0B2D1AD1044E0(scrAny *p0, scrAny *p1, scrAny *p2, scrAny *p3) { NativeInvoke::Invoke<scrVoid>(0x14E0B2D1AD1044E0, p0, p1, p2, p3); } // 14E0B2D1AD1044E0 DDD1F1F3
	static void _0x90D0622866E80445(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x90D0622866E80445, p0, p1); } // 90D0622866E80445 66FEB701
	static void _0x5DA3A8DE8CB6226F(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x5DA3A8DE8CB6226F, p0); } // 5DA3A8DE8CB6226F 9E2B9522
	static scrAny LEADERBOARDS_GET_NUMBER_OF_COLUMNS(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x117B45156D7EFF2E, p0, p1); } // 117B45156D7EFF2E 0A56EE34
	static scrAny LEADERBOARDS_GET_COLUMN_ID(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0xC4B5467A1886EA7E, p0, p1, p2); } // C4B5467A1886EA7E 3821A334
	static scrAny LEADERBOARDS_GET_COLUMN_TYPE(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0xBF4FEF46DB7894D3, p0, p1, p2); } // BF4FEF46DB7894D3 6F2820F4
	static scrAny LEADERBOARDS_READ_CLEAR_ALL() { return NativeInvoke::Invoke<scrAny>(0xA34CB6E6F0DF4A0B); } // A34CB6E6F0DF4A0B 233E058A
	static scrAny LEADERBOARDS_READ_CLEAR(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0x7CCE5C737A665701, p0, p1, p2); } // 7CCE5C737A665701 7090012F
	static BOOL LEADERBOARDS_READ_PENDING(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0xAC392C8483342AC2, p0, p1, p2); } // AC392C8483342AC2 EEB8BF5C
	static BOOL _0xA31FD15197B192BD() { return NativeInvoke::Invoke<BOOL>(0xA31FD15197B192BD); } // A31FD15197B192BD 1789437B
	static BOOL LEADERBOARDS_READ_SUCCESSFUL(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0x2FB19228983E832C, p0, p1, p2); } // 2FB19228983E832C 3AC5B2F1
	static BOOL LEADERBOARDS2_READ_FRIENDS_BY_ROW(scrAny *p0, scrAny *p1, scrAny p2, BOOL p3, scrAny p4, scrAny p5) { return NativeInvoke::Invoke<BOOL>(0x918B101666F9CB83, p0, p1, p2, p3, p4, p5); } // 918B101666F9CB83 BD91B136
	static BOOL LEADERBOARDS2_READ_BY_HANDLE(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0xC30713A383BFBF0E, p0, p1); } // C30713A383BFBF0E 6B553408
	static BOOL LEADERBOARDS2_READ_BY_ROW(scrAny *p0, scrAny *p1, scrAny p2, scrAny *p3, scrAny p4, scrAny *p5, scrAny p6) { return NativeInvoke::Invoke<BOOL>(0xA9CDB1E3F0A49883, p0, p1, p2, p3, p4, p5, p6); } // A9CDB1E3F0A49883 CA931F34
	static BOOL LEADERBOARDS2_READ_BY_RANK(scrAny *p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0xBA2C7DB0C129449A, p0, p1, p2); } // BA2C7DB0C129449A 1B03F59F
	static BOOL LEADERBOARDS2_READ_BY_RADIUS(scrAny *p0, scrAny p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0x5CE587FB5A42C8C4, p0, p1, p2); } // 5CE587FB5A42C8C4 C5B7E685
	static BOOL LEADERBOARDS2_READ_BY_SCORE_INT(scrAny *p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0x7EEC7E4F6984A16A, p0, p1, p2); } // 7EEC7E4F6984A16A AC020C18
	static BOOL LEADERBOARDS2_READ_BY_SCORE_FLOAT(scrAny *p0, float p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0xE662C8B759D08F3C, p0, p1, p2); } // E662C8B759D08F3C C678B29F
	static BOOL _0xC38DC1E90D22547C(scrAny *p0, scrAny *p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0xC38DC1E90D22547C, p0, p1, p2); } // C38DC1E90D22547C 9BEC3401
	static BOOL _0xA0F93D5465B3094D(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xA0F93D5465B3094D, p0); } // A0F93D5465B3094D C977D6E2
	static void _0x71B008056E5692D6() { NativeInvoke::Invoke<scrVoid>(0x71B008056E5692D6); } // 71B008056E5692D6 F2DB6A82
	static BOOL _0x34770B9CE0E03B91(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x34770B9CE0E03B91, p0, p1); } // 34770B9CE0E03B91 766A74FE
	static scrAny _0x88578F6EC36B4A3A(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x88578F6EC36B4A3A, p0, p1); } // 88578F6EC36B4A3A 6B90E730
	static float _0x38491439B6BA7F7D(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<float>(0x38491439B6BA7F7D, p0, p1); } // 38491439B6BA7F7D 509A286F
	static BOOL LEADERBOARDS2_WRITE_DATA(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xAE2206545888AE49, p0); } // AE2206545888AE49 5F9DF634
	static void _0x0BCA1D2C47B0D269(scrAny p0, scrAny p1, float p2) { NativeInvoke::Invoke<scrVoid>(0x0BCA1D2C47B0D269, p0, p1, p2); } // 0BCA1D2C47B0D269 7524E27B
	static void _0x2E65248609523599(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x2E65248609523599, p0, p1, p2); } // 2E65248609523599 1C5CCC3A
	static BOOL LEADERBOARDS_CACHE_DATA_ROW(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xB9BB18E2C40142ED, p0); } // B9BB18E2C40142ED 44F7D82B
	static void LEADERBOARDS_CLEAR_CACHE_DATA() { NativeInvoke::Invoke<scrVoid>(0xD4B02A6B476E1FDC); } // D4B02A6B476E1FDC 87F498C1
	static void _0x8EC74CEB042E7CFF(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x8EC74CEB042E7CFF, p0); } // 8EC74CEB042E7CFF 88AE9667
	static BOOL LEADERBOARDS_GET_CACHE_EXISTS(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x9C51349BE6CDFE2C, p0); } // 9C51349BE6CDFE2C FC8A71F3
	static scrAny LEADERBOARDS_GET_CACHE_TIME(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xF04C1C27DA35F6C8, p0); } // F04C1C27DA35F6C8 EDF02302
	static scrAny _0x58A651CD201D89AD(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x58A651CD201D89AD, p0); } // 58A651CD201D89AD CE7CB520
	static BOOL LEADERBOARDS_GET_CACHE_DATA_ROW(scrAny p0, scrAny p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0x9120E8DBA3D69273, p0, p1, p2); } // 9120E8DBA3D69273 A11289EC
	static void _0x11FF1C80276097ED(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x11FF1C80276097ED, p0, p1, p2); } // 11FF1C80276097ED 4AC39C6C
	static void _0x30A6614C1F7799B8(scrAny p0, float p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x30A6614C1F7799B8, p0, p1, p2); } // 30A6614C1F7799B8 3E69E7C3
	static void _0x6483C25849031C4F(scrAny p0, scrAny p1, scrAny p2, scrAny *p3) { NativeInvoke::Invoke<scrVoid>(0x6483C25849031C4F, p0, p1, p2, p3); } // 6483C25849031C4F 2FFD2FA5
	static BOOL _0x5EAD2BF6484852E4() { return NativeInvoke::Invoke<BOOL>(0x5EAD2BF6484852E4); } // 5EAD2BF6484852E4 23D70C39
	static void _0xC141B8917E0017EC() { NativeInvoke::Invoke<scrVoid>(0xC141B8917E0017EC); } // C141B8917E0017EC 0AD43306
	static void _0xB475F27C6A994D65() { NativeInvoke::Invoke<scrVoid>(0xB475F27C6A994D65); } // B475F27C6A994D65 C7DE5C30
	static void _0xF1A1803D3476F215(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xF1A1803D3476F215, p0); } // F1A1803D3476F215 A3DAC790
	static void _0x38BAAA5DD4C9D19F(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x38BAAA5DD4C9D19F, p0); } // 38BAAA5DD4C9D19F 726FAE66
	static void _0x55384438FC55AD8E(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x55384438FC55AD8E, p0); } // 55384438FC55AD8E F03895A4
	static void _0x723C1CE13FBFDB67(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x723C1CE13FBFDB67, p0, p1); } // 723C1CE13FBFDB67 4C39CF10
	static void _0x0D01D20616FC73FB(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x0D01D20616FC73FB, p0, p1); } // 0D01D20616FC73FB 2180AE13
	static void _0x428EAF89E24F6C36(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x428EAF89E24F6C36, p0, p1); } // 428EAF89E24F6C36 EE292B91
	static void _0x047CBED6F6F8B63C() { NativeInvoke::Invoke<scrVoid>(0x047CBED6F6F8B63C); } // 047CBED6F6F8B63C A063CABD
	static BOOL _0xC980E62E33DF1D5C(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0xC980E62E33DF1D5C, p0, p1); } // C980E62E33DF1D5C 62C19A3D
	static void _0x6F361B8889A792A3() { NativeInvoke::Invoke<scrVoid>(0x6F361B8889A792A3); } // 6F361B8889A792A3 3B4EF322
	static void _0xC847B43F369AC0B5() { NativeInvoke::Invoke<scrVoid>(0xC847B43F369AC0B5); } // C847B43F369AC0B5
	static BOOL _0xA5C80D8E768A9E66(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xA5C80D8E768A9E66, p0); } // A5C80D8E768A9E66
	static scrAny _0x9A62EC95AE10E011() { return NativeInvoke::Invoke<scrAny>(0x9A62EC95AE10E011); } // 9A62EC95AE10E011
	static scrAny _0x4C89FE2BDEB3F169() { return NativeInvoke::Invoke<scrAny>(0x4C89FE2BDEB3F169); } // 4C89FE2BDEB3F169
	static BOOL _0xC6E0E2616A7576BB() { return NativeInvoke::Invoke<BOOL>(0xC6E0E2616A7576BB); } // C6E0E2616A7576BB
	static scrAny _0x5BD5F255321C4AAF(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x5BD5F255321C4AAF, p0); } // 5BD5F255321C4AAF
	static scrAny _0xDEAAF77EB3687E97(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<scrAny>(0xDEAAF77EB3687E97, p0, p1); } // DEAAF77EB3687E97
	static BOOL _0xC70DDCE56D0D3A99() { return NativeInvoke::Invoke<BOOL>(0xC70DDCE56D0D3A99); } // C70DDCE56D0D3A99 54E775E0
	static scrAny _0x886913BBEACA68C1(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0x886913BBEACA68C1, p0); } // 886913BBEACA68C1 E3F0D62D
	static void _0x98E2BC1CA26287C3() { NativeInvoke::Invoke<scrVoid>(0x98E2BC1CA26287C3); } // 98E2BC1CA26287C3
	static void _0x629526ABA383BCAA() { NativeInvoke::Invoke<scrVoid>(0x629526ABA383BCAA); } // 629526ABA383BCAA
}

namespace BRAIN
{
	static void ADD_SCRIPT_TO_RANDOM_PED(scrAny *p0, scrAny p1, scrAny p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x4EE5367468A65CCC, p0, p1, p2, p3); } // 4EE5367468A65CCC ECC76C3D
	static void REGISTER_OBJECT_SCRIPT_BRAIN(scrAny *p0, scrAny p1, scrAny p2, float p3, scrAny p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0x0BE84C318BA6EC22, p0, p1, p2, p3, p4, p5); } // 0BE84C318BA6EC22 B6BCC608
	static BOOL IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xCCBA154209823057, p0); } // CCBA154209823057 BA4CAA56
	static void REGISTER_WORLD_POINT_SCRIPT_BRAIN(scrAny *p0, float p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x3CDC7136613284BD, p0, p1, p2); } // 3CDC7136613284BD 725D91F7
	static BOOL IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE() { return NativeInvoke::Invoke<BOOL>(0xC5042CC6F5E3D450); } // C5042CC6F5E3D450 2CF305A0
	static void ENABLE_SCRIPT_BRAIN_SET(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x67AA4D73F0CFA86B, p0); } // 67AA4D73F0CFA86B 2765919F
	static void DISABLE_SCRIPT_BRAIN_SET(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x14D8518E9760F08F, p0); } // 14D8518E9760F08F FBD13FAD
	static void _0x0B40ED49D7D6FF84() { NativeInvoke::Invoke<scrVoid>(0x0B40ED49D7D6FF84); } // 0B40ED49D7D6FF84 19B27825
	static void _0x4D953DF78EBF8158() { NativeInvoke::Invoke<scrVoid>(0x4D953DF78EBF8158); } // 4D953DF78EBF8158 F3A3AB08
	static void _0x6D6840CEE8845831(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x6D6840CEE8845831, p0); } // 6D6840CEE8845831 949FE53E
	static void _0x6E91B04E08773030(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x6E91B04E08773030, p0); } // 6E91B04E08773030 29CE8BAA
}

namespace MOBILE
{
	static void CREATE_MOBILE_PHONE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA4E8E696C532FBC7, p0); } // A4E8E696C532FBC7 5BBC5E23
	static void DESTROY_MOBILE_PHONE() { NativeInvoke::Invoke<scrVoid>(0x3BC861DF703E5097); } // 3BC861DF703E5097 1A65037B
	static void SET_MOBILE_PHONE_SCALE(float p0) { NativeInvoke::Invoke<scrVoid>(0xCBDD322A73D6D932, p0); } // CBDD322A73D6D932 09BCF1BE
	static void SET_MOBILE_PHONE_ROTATION(float p0, float p1, float p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0xBB779C0CA917E865, p0, p1, p2, p3); } // BB779C0CA917E865 209C28CF
	static void GET_MOBILE_PHONE_ROTATION(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x1CEFB61F193070AE, p0, p1); } // 1CEFB61F193070AE 17A29F23
	static void SET_MOBILE_PHONE_POSITION(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x693A5C6D6734085B, p0, p1, p2); } // 693A5C6D6734085B 841800B3
	static void GET_MOBILE_PHONE_POSITION(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x584FDFDA48805B86, p0); } // 584FDFDA48805B86 B2E1E1A0
	static void SCRIPT_IS_MOVING_MOBILE_PHONE_OFFSCREEN(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xF511F759238A5122, p0); } // F511F759238A5122 29828690
	static scrAny CAN_PHONE_BE_SEEN_ON_SCREEN() { return NativeInvoke::Invoke<scrAny>(0xC4E2813898C97A4B); } // C4E2813898C97A4B 5F978584
	static void _0x95C9E72F3D7DEC9B(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x95C9E72F3D7DEC9B, p0); } // 95C9E72F3D7DEC9B
	static void _0x44E44169EF70138E(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x44E44169EF70138E, p0); } // 44E44169EF70138E
	static void CELL_CAM_ACTIVATE(BOOL p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xFDE8F069C542D126, p0, p1); } // FDE8F069C542D126 234C1AE9
	static void _0x015C49A93E3E086E(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x015C49A93E3E086E, p0); } // 015C49A93E3E086E 4479B304
	static void _0xA2CCBE62CD4C91A4(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xA2CCBE62CD4C91A4, p0); } // A2CCBE62CD4C91A4 C273BB4D
	static void _0x1B0B4AEED5B9B41C(float p0) { NativeInvoke::Invoke<scrVoid>(0x1B0B4AEED5B9B41C, p0); } // 1B0B4AEED5B9B41C
	static void _0x53F4892D18EC90A4(float p0) { NativeInvoke::Invoke<scrVoid>(0x53F4892D18EC90A4, p0); } // 53F4892D18EC90A4
	static void _0x3117D84EFA60F77B(float p0) { NativeInvoke::Invoke<scrVoid>(0x3117D84EFA60F77B, p0); } // 3117D84EFA60F77B
	static void _0x15E69E2802C24B8D(float p0) { NativeInvoke::Invoke<scrVoid>(0x15E69E2802C24B8D, p0); } // 15E69E2802C24B8D
	static void _0xAC2890471901861C(float p0) { NativeInvoke::Invoke<scrVoid>(0xAC2890471901861C, p0); } // AC2890471901861C
	static void _0xD6ADE981781FCA09(float p0) { NativeInvoke::Invoke<scrVoid>(0xD6ADE981781FCA09, p0); } // D6ADE981781FCA09
	static void _0xF1E22DC13F5EEBAD(float p0) { NativeInvoke::Invoke<scrVoid>(0xF1E22DC13F5EEBAD, p0); } // F1E22DC13F5EEBAD
	static void _0x466DA42C89865553(float p0) { NativeInvoke::Invoke<scrVoid>(0x466DA42C89865553, p0); } // 466DA42C89865553 66DCD9D2
	static BOOL CELL_CAM_IS_CHAR_VISIBLE_NO_FACE_CHECK(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x439E9BC95B7E7FBE, p0); } // 439E9BC95B7E7FBE BEA88097
	static void GET_MOBILE_PHONE_RENDER_ID(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xB4A53E05F68B6FA1, p0); } // B4A53E05F68B6FA1 88E4FECE
}

namespace APP
{
	static BOOL APP_DATA_VALID() { return NativeInvoke::Invoke<BOOL>(0x846AA8E7D55EE5B6); } // 846AA8E7D55EE5B6 72BDE002
	static scrAny APP_GET_INT(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0xD3A58A12C77D9D4B, p0); } // D3A58A12C77D9D4B 2942AAD2
	static float APP_GET_FLOAT(scrAny *p0) { return NativeInvoke::Invoke<float>(0x1514FB24C02C2322, p0); } // 1514FB24C02C2322 D87F3A1C
	static scrAny APP_GET_STRING(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0x749B023950D2311C, p0); } // 749B023950D2311C 849CEB80
	static void APP_SET_INT(scrAny *p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x607E8E3D3E4F9611, p0, p1); } // 607E8E3D3E4F9611 1B509C32
	static void APP_SET_FLOAT(scrAny *p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x25D7687C68E0DAA4, p0, p1); } // 25D7687C68E0DAA4 F3076135
	static void APP_SET_STRING(scrAny *p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x3FF2FCEC4B7721B4, p0, p1); } // 3FF2FCEC4B7721B4 23DF19A8
	static void APP_SET_APP(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xCFD0406ADAF90D2B, p0); } // CFD0406ADAF90D2B 8BAC4146
	static void APP_SET_BLOCK(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x262AB456A3D21F93, p0); } // 262AB456A3D21F93 C2D54DD9
	static void APP_CLEAR_BLOCK() { NativeInvoke::Invoke<scrVoid>(0x5FE1DF3342DB7DBA); } // 5FE1DF3342DB7DBA DAB86A18
	static void APP_CLOSE_APP() { NativeInvoke::Invoke<scrVoid>(0xE41C65E07A5F05FC); } // E41C65E07A5F05FC 03767C7A
	static void APP_CLOSE_BLOCK() { NativeInvoke::Invoke<scrVoid>(0xE8E3FCF72EAC0EF8); } // E8E3FCF72EAC0EF8 ED97B202
	static BOOL _0x71EEE69745088DA0() { return NativeInvoke::Invoke<BOOL>(0x71EEE69745088DA0); } // 71EEE69745088DA0 D368BA15
	static BOOL APP_HAS_SYNCED_DATA(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xCA52279A7271517F, p0); } // CA52279A7271517F 1DE2A63D
	static void APP_SAVE_DATA() { NativeInvoke::Invoke<scrVoid>(0x95C5D356CDA6E85F); } // 95C5D356CDA6E85F 84A3918D
	static scrAny _0xC9853A2BE3DED1A6() { return NativeInvoke::Invoke<scrAny>(0xC9853A2BE3DED1A6); } // C9853A2BE3DED1A6 784D550B
	static BOOL APP_DELETE_APP_DATA(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x44151AEA95C8A003, p0); } // 44151AEA95C8A003 2A2FBD1C
}

namespace TIME
{
	static void SET_CLOCK_TIME(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x47C3B5848C3E45D8, p0, p1, p2); } // 47C3B5848C3E45D8 26F6AF14
	static void PAUSE_CLOCK(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x4055E40BD2DBEC1D, p0); } // 4055E40BD2DBEC1D B02D6124
	static void _0xC8CA9670B9D83B3B(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xC8CA9670B9D83B3B, p0, p1, p2); } // C8CA9670B9D83B3B 57B8DA7C
	static void ADD_TO_CLOCK_TIME(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xD716F30D8C8980E2, p0, p1, p2); } // D716F30D8C8980E2 CC40D20D
	static scrAny GET_CLOCK_HOURS() { return NativeInvoke::Invoke<scrAny>(0x25223CA6B4D20B7F); } // 25223CA6B4D20B7F 7EF8316F
	static scrAny GET_CLOCK_MINUTES() { return NativeInvoke::Invoke<scrAny>(0x13D2B8ADD79640F2); } // 13D2B8ADD79640F2 94AAC486
	static scrAny GET_CLOCK_SECONDS() { return NativeInvoke::Invoke<scrAny>(0x494E97C2EF27C470); } // 494E97C2EF27C470 099C927E
	static void SET_CLOCK_DATE(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xB096419DF0D06CE7, p0, p1, p2); } // B096419DF0D06CE7 96891C94
	static scrAny GET_CLOCK_DAY_OF_WEEK() { return NativeInvoke::Invoke<scrAny>(0xD972E4BD7AEB235F); } // D972E4BD7AEB235F 84E4A289
	static scrAny GET_CLOCK_DAY_OF_MONTH() { return NativeInvoke::Invoke<scrAny>(0x3D10BC92A4DB1D35); } // 3D10BC92A4DB1D35 C7A5ACB7
	static scrAny GET_CLOCK_MONTH() { return NativeInvoke::Invoke<scrAny>(0xBBC72712E80257A1); } // BBC72712E80257A1 3C48A3D5
	static scrAny GET_CLOCK_YEAR() { return NativeInvoke::Invoke<scrAny>(0x961777E64BDAF717); } // 961777E64BDAF717 B8BECF15
	static scrAny _0x2F8B4D1C595B11DB() { return NativeInvoke::Invoke<scrAny>(0x2F8B4D1C595B11DB); } // 2F8B4D1C595B11DB 3B74095C
	static void GET_POSIX_TIME(scrAny *p0, scrAny *p1, scrAny *p2, scrAny *p3, scrAny *p4, scrAny *p5) { NativeInvoke::Invoke<scrVoid>(0xDA488F299A5B164E, p0, p1, p2, p3, p4, p5); } // DA488F299A5B164E E15A5281
	static void _0x8117E09A19EEF4D3(scrAny *p0, scrAny *p1, scrAny *p2, scrAny *p3, scrAny *p4, scrAny *p5) { NativeInvoke::Invoke<scrVoid>(0x8117E09A19EEF4D3, p0, p1, p2, p3, p4, p5); } // 8117E09A19EEF4D3
	static void GET_LOCAL_TIME(scrAny *p0, scrAny *p1, scrAny *p2, scrAny *p3, scrAny *p4, scrAny *p5) { NativeInvoke::Invoke<scrVoid>(0x50C7A99057A69748, p0, p1, p2, p3, p4, p5); } // 50C7A99057A69748 124BCFA2
}

namespace PATHFIND
{
	static void SET_ROADS_IN_AREA(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7) { NativeInvoke::Invoke<scrVoid>(0xBF1A602B5BA52FEE, p0, p1, p2, p3, p4, p5, p6, p7); } // BF1A602B5BA52FEE EBC7B918
	static void SET_ROADS_IN_ANGLED_AREA(float p0, float p1, float p2, float p3, float p4, float p5, float p6, BOOL p7, BOOL p8, BOOL p9) { NativeInvoke::Invoke<scrVoid>(0x1A5AA1208AF5DB59, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 1A5AA1208AF5DB59 BD088F4B
	static void SET_PED_PATHS_IN_AREA(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6) { NativeInvoke::Invoke<scrVoid>(0x34F060F4BF92E018, p0, p1, p2, p3, p4, p5, p6); } // 34F060F4BF92E018 2148EA84
	static scrAny GET_SAFE_COORD_FOR_PED(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { return NativeInvoke::Invoke<scrAny>(0xB61C8E878A4199CA, p0, p1, p2, p3, p4, p5); } // B61C8E878A4199CA B370270A
	static scrAny GET_CLOSEST_VEHICLE_NODE(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6) { return NativeInvoke::Invoke<scrAny>(0x240A18690AE96513, p0, p1, p2, p3, p4, p5, p6); } // 240A18690AE96513 6F5F1E6C
	static scrAny GET_CLOSEST_MAJOR_VEHICLE_NODE(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { return NativeInvoke::Invoke<scrAny>(0x2EABE3B06F58C1BE, p0, p1, p2, p3, p4, p5); } // 2EABE3B06F58C1BE 04B5F15B
	static scrAny GET_CLOSEST_VEHICLE_NODE_WITH_HEADING(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7) { return NativeInvoke::Invoke<scrAny>(0xFF071FB798B803B0, p0, p1, p2, p3, p4, p5, p6, p7); } // FF071FB798B803B0 8BD5759B
	static scrAny GET_NTH_CLOSEST_VEHICLE_NODE(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7) { return NativeInvoke::Invoke<scrAny>(0xE50E52416CCF948B, p0, p1, p2, p3, p4, p5, p6, p7); } // E50E52416CCF948B F125BFCC
	static scrAny GET_NTH_CLOSEST_VEHICLE_NODE_ID(float p0, float p1, float p2, scrAny p3, scrAny p4, float p5, float p6) { return NativeInvoke::Invoke<scrAny>(0x22D7275A79FE8215, p0, p1, p2, p3, p4, p5, p6); } // 22D7275A79FE8215 3F358BEA
	static scrAny GET_NTH_CLOSEST_VEHICLE_NODE_WITH_HEADING(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9) { return NativeInvoke::Invoke<scrAny>(0x80CA6A8B6C094CC4, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 80CA6A8B6C094CC4 7349C856
	static scrAny GET_NTH_CLOSEST_VEHICLE_NODE_ID_WITH_HEADING(float p0, float p1, float p2, scrAny p3, scrAny *p4, scrAny *p5, scrAny p6, float p7, float p8) { return NativeInvoke::Invoke<scrAny>(0x6448050E9C2A7207, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 6448050E9C2A7207 C1AEB88D
	static scrAny GET_NTH_CLOSEST_VEHICLE_NODE_FAVOUR_DIRECTION(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9, scrAny p10, scrAny p11) { return NativeInvoke::Invoke<scrAny>(0x45905BE8654AE067, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 45905BE8654AE067 928A4DEC
	static BOOL GET_VEHICLE_NODE_PROPERTIES(float p0, float p1, float p2, scrAny *p3, scrAny *p4) { return NativeInvoke::Invoke<BOOL>(0x0568566ACBB5DEDC, p0, p1, p2, p3, p4); } // 0568566ACBB5DEDC CC90110B
	static BOOL IS_VEHICLE_NODE_ID_VALID(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x1EAF30FCFBF5AF74, p0); } // 1EAF30FCFBF5AF74 57DFB1EF
	static void GET_VEHICLE_NODE_POSITION(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x703123E5E7D429C2, p0, p1); } // 703123E5E7D429C2 E38E252D
	static BOOL _0xA2AE5C478B96E3B6(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xA2AE5C478B96E3B6, p0); } // A2AE5C478B96E3B6 EE4B1219
	static BOOL _0x4F5070AA58F69279(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x4F5070AA58F69279, p0); } // 4F5070AA58F69279 56737A3C
	static scrAny GET_CLOSEST_ROAD(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9, scrAny p10) { return NativeInvoke::Invoke<scrAny>(0x132F52BBA570FE92, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 132F52BBA570FE92 567B0E11
	static BOOL LOAD_ALL_PATH_NODES(BOOL p0) { return NativeInvoke::Invoke<BOOL>(0x80E4A6EDDB0BE8D9, p0); } // 80E4A6EDDB0BE8D9 C66E28C3
	static void _0x228E5C6AD4D74BFD(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x228E5C6AD4D74BFD, p0); } // 228E5C6AD4D74BFD D6A3B458
	static BOOL _0xF7B79A50B905A30D(float p0, float p1, float p2, float p3) { return NativeInvoke::Invoke<BOOL>(0xF7B79A50B905A30D, p0, p1, p2, p3); } // F7B79A50B905A30D 86E80A17
	static BOOL _0x07FB139B592FA687(float p0, float p1, float p2, float p3) { return NativeInvoke::Invoke<BOOL>(0x07FB139B592FA687, p0, p1, p2, p3); } // 07FB139B592FA687 2CDA5012
	static void SET_ROADS_BACK_TO_ORIGINAL(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0x1EE7063B80FFC77C, p0, p1, p2, p3, p4, p5); } // 1EE7063B80FFC77C 86AC4A85
	static void SET_ROADS_BACK_TO_ORIGINAL_IN_ANGLED_AREA(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6) { NativeInvoke::Invoke<scrVoid>(0x0027501B9F3B407E, p0, p1, p2, p3, p4, p5, p6); } // 0027501B9F3B407E 9DB5D209
	static void _0x0B919E1FB47CC4E0(float p0) { NativeInvoke::Invoke<scrVoid>(0x0B919E1FB47CC4E0, p0); } // 0B919E1FB47CC4E0 3C5085E4
	static void _0xAA76052DDA9BFC3E(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6) { NativeInvoke::Invoke<scrVoid>(0xAA76052DDA9BFC3E, p0, p1, p2, p3, p4, p5, p6); } // AA76052DDA9BFC3E D0F51299
	static void SET_PED_PATHS_BACK_TO_ORIGINAL(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0xE04B48F2CC926253, p0, p1, p2, p3, p4, p5); } // E04B48F2CC926253 3F1ABDA4
	static scrAny GET_RANDOM_VEHICLE_NODE(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8) { return NativeInvoke::Invoke<scrAny>(0x93E0DB8440B73A7D, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 93E0DB8440B73A7D AD1476EA
	static void GET_STREET_NAME_AT_COORD(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x2EB41072B4C1E4C0, p0, p1, p2, p3, p4); } // 2EB41072B4C1E4C0 DEBEEFCF
	static scrAny GENERATE_DIRECTIONS_TO_COORD(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6) { return NativeInvoke::Invoke<scrAny>(0xF90125F1F79ECDF8, p0, p1, p2, p3, p4, p5, p6); } // F90125F1F79ECDF8 ED35C094
	static void SET_IGNORE_NO_GPS_FLAG(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x72751156E7678833, p0); } // 72751156E7678833 B72CF194
	static void _0x1FC289A0C3FF470F(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x1FC289A0C3FF470F, p0); } // 1FC289A0C3FF470F 90DF7A4C
	static void SET_GPS_DISABLED_ZONE(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0xDC20483CD3DD5201, p0, p1, p2, p3, p4, p5); } // DC20483CD3DD5201 720B8073
	static scrAny _0xBBB45C3CF5C8AA85() { return NativeInvoke::Invoke<scrAny>(0xBBB45C3CF5C8AA85); } // BBB45C3CF5C8AA85 4B770634
	static BOOL _0x869DAACBBE9FA006() { return NativeInvoke::Invoke<BOOL>(0x869DAACBBE9FA006); } // 869DAACBBE9FA006 286F82CC
	static scrAny _0x16F46FB18C8009E4(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { return NativeInvoke::Invoke<scrAny>(0x16F46FB18C8009E4, p0, p1, p2, p3, p4); } // 16F46FB18C8009E4 F6422F9A
	static BOOL IS_POINT_ON_ROAD(float p0, float p1, float p2, scrAny p3) { return NativeInvoke::Invoke<BOOL>(0x125BF4ABFC536B09, p0, p1, p2, p3); } // 125BF4ABFC536B09 CF198055
	static void ADD_NAVMESH_REQUIRED_REGION(float p0, float p1, float p2) { NativeInvoke::Invoke<scrVoid>(0x387EAD7EE42F6685, p0, p1, p2); } // 387EAD7EE42F6685 12B086EA
	static void REMOVE_NAVMESH_REQUIRED_REGIONS() { NativeInvoke::Invoke<scrVoid>(0x916F0A3CDEC3445E); } // 916F0A3CDEC3445E 637BB680
	static void DISABLE_NAVMESH_IN_AREA(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6) { NativeInvoke::Invoke<scrVoid>(0x4C8872D8CDBE1B8B, p0, p1, p2, p3, p4, p5, p6); } // 4C8872D8CDBE1B8B 6E37F132
	static BOOL ARE_ALL_NAVMESH_REGIONS_LOADED() { return NativeInvoke::Invoke<BOOL>(0x8415D95B194A3AEA); } // 8415D95B194A3AEA 34C4E789
	static BOOL IS_NAVMESH_LOADED_IN_AREA(float p0, float p1, float p2, float p3, float p4, float p5) { return NativeInvoke::Invoke<BOOL>(0xF813C7E63F9062A5, p0, p1, p2, p3, p4, p5); } // F813C7E63F9062A5 4C2BA99E
	static scrAny _0x01708E8DD3FF8C65(float p0, float p1, float p2, float p3, float p4, float p5) { return NativeInvoke::Invoke<scrAny>(0x01708E8DD3FF8C65, p0, p1, p2, p3, p4, p5); } // 01708E8DD3FF8C65
	static scrAny ADD_NAVMESH_BLOCKING_OBJECT(float p0, float p1, float p2, float p3, float p4, float p5, float p6, BOOL p7, scrAny p8) { return NativeInvoke::Invoke<scrAny>(0xFCD5C8E06E502F5A, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // FCD5C8E06E502F5A 2952BA56
	static void UPDATE_NAVMESH_BLOCKING_OBJECT(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, scrAny p8) { NativeInvoke::Invoke<scrVoid>(0x109E99373F290687, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 109E99373F290687 4E9776D0
	static void REMOVE_NAVMESH_BLOCKING_OBJECT(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x46399A7895957C0E, p0); } // 46399A7895957C0E 098602B0
	static BOOL _0x0EAEB0DB4B132399(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x0EAEB0DB4B132399, p0); } // 0EAEB0DB4B132399 4B67D7EE
	static float _0x29C24BFBED8AB8FB(float p0, float p1) { return NativeInvoke::Invoke<float>(0x29C24BFBED8AB8FB, p0, p1); } // 29C24BFBED8AB8FB 3FE8C5A0
	static float _0x8ABE8608576D9CE3(float p0, float p1, float p2, float p3) { return NativeInvoke::Invoke<float>(0x8ABE8608576D9CE3, p0, p1, p2, p3); } // 8ABE8608576D9CE3 3ED21C90
	static float _0x336511A34F2E5185(float p0, float p1) { return NativeInvoke::Invoke<float>(0x336511A34F2E5185, p0, p1); } // 336511A34F2E5185 A07C5B7D
	static float _0x3599D741C9AC6310(float p0, float p1, float p2, float p3) { return NativeInvoke::Invoke<float>(0x3599D741C9AC6310, p0, p1, p2, p3); } // 3599D741C9AC6310 76751DD4
	static float CALCULATE_TRAVEL_DISTANCE_BETWEEN_POINTS(float p0, float p1, float p2, float p3, float p4, float p5) { return NativeInvoke::Invoke<float>(0xADD95C7005C4A197, p0, p1, p2, p3, p4, p5); } // ADD95C7005C4A197 B114489B
}

namespace CONTROLS
{
	static BOOL IS_CONTROL_ENABLED(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x1CEA6BFDF248E5D9, p0, p1); } // 1CEA6BFDF248E5D9 9174AF84
	static BOOL IS_CONTROL_PRESSED(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xF3A21BCD95725A4A, p0, p1); } // F3A21BCD95725A4A 517A4384
	static BOOL IS_CONTROL_RELEASED(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x648EE3E7F38877DD, p0, p1); } // 648EE3E7F38877DD 1F91A06E
	static BOOL IS_CONTROL_JUST_PRESSED(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x580417101DDB492F, p0, p1); } // 580417101DDB492F 4487F579
	static BOOL IS_CONTROL_JUST_RELEASED(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x50F940259D3841E6, p0, p1); } // 50F940259D3841E6 2314444B
	static scrAny GET_CONTROL_VALUE(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xD95E79E8686D2C27, p0, p1); } // D95E79E8686D2C27 C526F3C6
	static float GET_CONTROL_NORMAL(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<float>(0xEC3C9B8D5327B563, p0, p1); } // EC3C9B8D5327B563 5DE226A5
	static float _0x5B84D09CEC5209C5(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<float>(0x5B84D09CEC5209C5, p0, p1); } // 5B84D09CEC5209C5 C49343BB
	static BOOL _0xE8A25867FBA3B05E(scrAny p0, scrAny p1, float p2) { return NativeInvoke::Invoke<BOOL>(0xE8A25867FBA3B05E, p0, p1, p2); } // E8A25867FBA3B05E
	static BOOL IS_DISABLED_CONTROL_PRESSED(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xE2587F8CBBD87B1D, p0, p1); } // E2587F8CBBD87B1D 32A93544
	static BOOL IS_DISABLED_CONTROL_JUST_PRESSED(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x91AEF906BCA88877, p0, p1); } // 91AEF906BCA88877 EE6ABD32
	static BOOL IS_DISABLED_CONTROL_JUST_RELEASED(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x305C8DCD79DA8B0F, p0, p1); } // 305C8DCD79DA8B0F D6A679E1
	static float GET_DISABLED_CONTROL_NORMAL(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<float>(0x11E65974A982637C, p0, p1); } // 11E65974A982637C 66FF4FAA
	static float _0x4F8A26A890FD62FB(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<float>(0x4F8A26A890FD62FB, p0, p1); } // 4F8A26A890FD62FB F2A65A4C
	static scrAny _0xD7D22F5592AED8BA(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xD7D22F5592AED8BA, p0); } // D7D22F5592AED8BA 0E8EF929
	static scrAny _0xA571D46727E2B718(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xA571D46727E2B718, p0); } // A571D46727E2B718
	static BOOL _0x13337B38DB572509(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x13337B38DB572509, p0); } // 13337B38DB572509
	static BOOL _0x23F09EADC01449D6(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x23F09EADC01449D6, p0); } // 23F09EADC01449D6
	static scrAny _0x6CD79468A1E595C6(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x6CD79468A1E595C6, p0); } // 6CD79468A1E595C6
	static scrAny _0x0499D7B09FC9B407(scrAny p0, scrAny p1, BOOL p2) { return NativeInvoke::Invoke<scrAny>(0x0499D7B09FC9B407, p0, p1, p2); } // 0499D7B09FC9B407 3551727A
	static scrAny _0x80C2FD58D720C801(scrAny p0, scrAny p1, BOOL p2) { return NativeInvoke::Invoke<scrAny>(0x80C2FD58D720C801, p0, p1, p2); } // 80C2FD58D720C801 3EE71F6A
	static void _0x8290252FFF36ACB5(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x8290252FFF36ACB5, p0, p1, p2, p3); } // 8290252FFF36ACB5
	static void _0xCB0360EFEFB2580D(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xCB0360EFEFB2580D, p0); } // CB0360EFEFB2580D 7715C03B
	static void SET_PAD_SHAKE(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x48B3886C1358D0D5, p0, p1, p2); } // 48B3886C1358D0D5 5D38BD2F
	static void _0x14D29BB12D47F68C(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { NativeInvoke::Invoke<scrVoid>(0x14D29BB12D47F68C, p0, p1, p2, p3, p4); } // 14D29BB12D47F68C
	static void STOP_PAD_SHAKE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x38C16A305E8CDC8D, p0); } // 38C16A305E8CDC8D 8F75657E
	static void _0xF239400E16C23E08(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xF239400E16C23E08, p0, p1); } // F239400E16C23E08 7D65EB6E
	static void _0xA0CEFCEA390AAB9B(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA0CEFCEA390AAB9B, p0); } // A0CEFCEA390AAB9B
	static BOOL IS_LOOK_INVERTED() { return NativeInvoke::Invoke<BOOL>(0x77B612531280010D); } // 77B612531280010D 313434B2
	static BOOL _0xE1615EC03B3BB4FD() { return NativeInvoke::Invoke<BOOL>(0xE1615EC03B3BB4FD); } // E1615EC03B3BB4FD
	static scrAny _0xBB41AFBBBC0A0287() { return NativeInvoke::Invoke<scrAny>(0xBB41AFBBBC0A0287); } // BB41AFBBBC0A0287 81802053
	static scrAny _0x59B9A7AF4C95133C() { return NativeInvoke::Invoke<scrAny>(0x59B9A7AF4C95133C); } // 59B9A7AF4C95133C
	static BOOL _0x0F70731BACCFBB96() { return NativeInvoke::Invoke<BOOL>(0x0F70731BACCFBB96); } // 0F70731BACCFBB96
	static BOOL _0xFC859E2374407556() { return NativeInvoke::Invoke<BOOL>(0xFC859E2374407556); } // FC859E2374407556
	static void SET_PLAYERPAD_SHAKES_WHEN_CONTROLLER_DISABLED(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x798FDEB5B1575088, p0); } // 798FDEB5B1575088 A86BD91F
	static void SET_INPUT_EXCLUSIVE(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xEDE476E5EE29EDB1, p0, p1); } // EDE476E5EE29EDB1 4E8E29E6
	static void DISABLE_CONTROL_ACTION(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xFE99B66D079CF6BC, p0, p1, p2); } // FE99B66D079CF6BC 3800C0DC
	static void ENABLE_CONTROL_ACTION(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x351220255D64C155, p0, p1, p2); } // 351220255D64C155 D2753551
	static void DISABLE_ALL_CONTROL_ACTIONS(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x5F4B6931816E599B, p0); } // 5F4B6931816E599B 16753CF4
	static void ENABLE_ALL_CONTROL_ACTIONS(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA5FFE9B05F199DE7, p0); } // A5FFE9B05F199DE7 FC2F119F
	static BOOL _0x3D42B92563939375(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x3D42B92563939375, p0); } // 3D42B92563939375 D2C80B2E
	static BOOL _0x4683149ED1DDE7A1(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x4683149ED1DDE7A1, p0); } // 4683149ED1DDE7A1 BBFC9050
	static void _0x643ED62D5EA3BEBD() { NativeInvoke::Invoke<scrVoid>(0x643ED62D5EA3BEBD); } // 643ED62D5EA3BEBD 42140FF9
	static void _0x7F4724035FDCA1DD(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x7F4724035FDCA1DD, p0); } // 7F4724035FDCA1DD 2CEDE6C5
}

namespace DATAFILE
{
	static void _0xAD6875BBC0FC899C(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xAD6875BBC0FC899C, p0); } // AD6875BBC0FC899C 621388FF
	static BOOL _0x22DA66936E0FFF37(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x22DA66936E0FFF37, p0); } // 22DA66936E0FFF37 B41064A4
	static BOOL _0x8F5EA1C01D65A100(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x8F5EA1C01D65A100, p0); } // 8F5EA1C01D65A100 9DB63CFF
	static BOOL _0xC84527E235FCA219(scrAny *p0, scrAny p1, scrAny *p2, scrAny *p3, scrAny *p4, scrAny *p5, BOOL p6) { return NativeInvoke::Invoke<BOOL>(0xC84527E235FCA219, p0, p1, p2, p3, p4, p5, p6); } // C84527E235FCA219 F09157B0
	static BOOL _0xA5EFC3E847D60507(scrAny *p0, scrAny *p1, scrAny *p2, scrAny *p3, BOOL p4) { return NativeInvoke::Invoke<BOOL>(0xA5EFC3E847D60507, p0, p1, p2, p3, p4); } // A5EFC3E847D60507 D96860FC
	static BOOL _0x648E7A5434AF7969(scrAny *p0, scrAny *p1, scrAny p2, scrAny *p3, scrAny *p4, scrAny *p5, scrAny *p6) { return NativeInvoke::Invoke<BOOL>(0x648E7A5434AF7969, p0, p1, p2, p3, p4, p5, p6); } // 648E7A5434AF7969 459F2683
	static BOOL _0x4645DE9980999E93(scrAny *p0, scrAny *p1, scrAny *p2, scrAny *p3, scrAny *p4) { return NativeInvoke::Invoke<BOOL>(0x4645DE9980999E93, p0, p1, p2, p3, p4); } // 4645DE9980999E93 DBB83E2B
	static BOOL _0x692D808C34A82143(scrAny *p0, float p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0x692D808C34A82143, p0, p1, p2); } // 692D808C34A82143 BB6321BD
	static BOOL _0xA69AC4ADE82B57A4(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xA69AC4ADE82B57A4, p0); } // A69AC4ADE82B57A4 E8D56DA2
	static BOOL _0x9CB0BFA7A9342C3D(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<BOOL>(0x9CB0BFA7A9342C3D, p0, p1); } // 9CB0BFA7A9342C3D CB6A351E
	static BOOL _0x52818819057F2B40(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x52818819057F2B40, p0); } // 52818819057F2B40 A4D1B30E
	static BOOL _0x01095C95CD46B624(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x01095C95CD46B624, p0); } // 01095C95CD46B624 B8515B2F
	static BOOL _0xC5238C011AF405E4(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xC5238C011AF405E4, p0); } // C5238C011AF405E4 660C468E
	static void DATAFILE_CREATE() { NativeInvoke::Invoke<scrVoid>(0xD27058A1CA2B13EE); } // D27058A1CA2B13EE 95F8A221
	static void DATAFILE_DELETE() { NativeInvoke::Invoke<scrVoid>(0x9AB9C1CFC8862DFB); } // 9AB9C1CFC8862DFB DEF31B0A
	static void _0x2ED61456317B8178() { NativeInvoke::Invoke<scrVoid>(0x2ED61456317B8178); } // 2ED61456317B8178 4E03F632
	static void _0xC55854C7D7274882() { NativeInvoke::Invoke<scrVoid>(0xC55854C7D7274882); } // C55854C7D7274882 F11F956F
	static scrAny PRELOAD_FIND() { return NativeInvoke::Invoke<scrAny>(0x906B778CA1DC72B6); } // 906B778CA1DC72B6 86DDF9C2
	static BOOL _0x83BCCE3224735F05(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x83BCCE3224735F05, p0); } // 83BCCE3224735F05 768CBB35
	static BOOL _0x4DFDD9EB705F8140(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x4DFDD9EB705F8140, p0); } // 4DFDD9EB705F8140 0B4087F7
	static BOOL _0xBEDB96A7584AA8CF() { return NativeInvoke::Invoke<BOOL>(0xBEDB96A7584AA8CF); } // BEDB96A7584AA8CF 5DCD0796
	static void _0x35124302A556A325(scrAny *p0, scrAny *p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x35124302A556A325, p0, p1, p2); } // 35124302A556A325 9B29D99B
	static void _0xE7E035450A7948D5(scrAny *p0, scrAny *p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xE7E035450A7948D5, p0, p1, p2); } // E7E035450A7948D5 EFCF554A
	static void _0xC27E1CC2D795105E(scrAny *p0, scrAny *p1, float p2) { NativeInvoke::Invoke<scrVoid>(0xC27E1CC2D795105E, p0, p1, p2); } // C27E1CC2D795105E E972CACF
	static void _0x8FF3847DADD8E30C(scrAny *p0, scrAny *p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0x8FF3847DADD8E30C, p0, p1, p2); } // 8FF3847DADD8E30C D437615C
	static void _0x4CD49B76338C7DEE(scrAny *p0, scrAny *p1, float p2, float p3, float p4) { NativeInvoke::Invoke<scrVoid>(0x4CD49B76338C7DEE, p0, p1, p2, p3, p4); } // 4CD49B76338C7DEE 75FC6C3C
	static scrAny _0xA358F56F10732EE1(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<scrAny>(0xA358F56F10732EE1, p0, p1); } // A358F56F10732EE1 96A8E05F
	static scrAny _0x5B11728527CA6E5F(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<scrAny>(0x5B11728527CA6E5F, p0, p1); } // 5B11728527CA6E5F 03939B8D
	static BOOL _0x1186940ED72FFEEC(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x1186940ED72FFEEC, p0, p1); } // 1186940ED72FFEEC 8876C872
	static scrAny _0x78F06F6B1FB5A80C(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<scrAny>(0x78F06F6B1FB5A80C, p0, p1); } // 78F06F6B1FB5A80C A6C68693
	static float _0x06610343E73B9727(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<float>(0x06610343E73B9727, p0, p1); } // 06610343E73B9727 A92C1AF4
	static scrAny _0x3D2FD9E763B24472(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<scrAny>(0x3D2FD9E763B24472, p0, p1); } // 3D2FD9E763B24472 942160EC
	static scrVector3 _0x46CD3CB66E0825CC(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<scrVector3>(0x46CD3CB66E0825CC, p0, p1); } // 46CD3CB66E0825CC E84A127A
	static scrAny _0xB6B9DDC412FCEEE2(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<scrAny>(0xB6B9DDC412FCEEE2, p0, p1); } // B6B9DDC412FCEEE2 C9C13D8D
	static scrAny _0x7A983AA9DA2659ED(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<scrAny>(0x7A983AA9DA2659ED, p0, p1); } // 7A983AA9DA2659ED 1F2F7D00
	static scrAny _0x031C55ED33227371(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<scrAny>(0x031C55ED33227371, p0, p1); } // 031C55ED33227371 2678342A
	static void _0xF8B0F5A43E928C76(scrAny *p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xF8B0F5A43E928C76, p0, p1); } // F8B0F5A43E928C76 08174B90
	static void _0xCABDB751D86FE93B(scrAny *p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xCABDB751D86FE93B, p0, p1); } // CABDB751D86FE93B F29C0B36
	static void _0x57A995FD75D37F56(scrAny *p0, float p1) { NativeInvoke::Invoke<scrVoid>(0x57A995FD75D37F56, p0, p1); } // 57A995FD75D37F56 E4302123
	static void _0x2F0661C155AEEEAA(scrAny *p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x2F0661C155AEEEAA, p0, p1); } // 2F0661C155AEEEAA F3C01350
	static void _0x407F8D034F70F0C2(scrAny *p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0x407F8D034F70F0C2, p0, p1, p2, p3); } // 407F8D034F70F0C2 16F464B6
	static scrAny _0x6889498B3E19C797(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0x6889498B3E19C797, p0); } // 6889498B3E19C797 C174C71B
	static BOOL _0x50C1B2874E50C114(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x50C1B2874E50C114, p0, p1); } // 50C1B2874E50C114 A2E5F921
	static scrAny _0x3E5AE19425CD74BE(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x3E5AE19425CD74BE, p0, p1); } // 3E5AE19425CD74BE BB120CFC
	static float FOCUS_USE_SPLINE(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<float>(0xC0C527B525D7CFB5, p0, p1); } // C0C527B525D7CFB5 08AD2CC2
	static scrAny OVERIDE_TEXTURENAMES(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xD3F2FFEB8D836F52, p0, p1); } // D3F2FFEB8D836F52 93F985A6
	static scrVector3 _0x8D2064E5B64A628A(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<scrVector3>(0x8D2064E5B64A628A, p0, p1); } // 8D2064E5B64A628A 80E3DA55
	static scrAny _0x8B5FADCC4E3A145F(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x8B5FADCC4E3A145F, p0, p1); } // 8B5FADCC4E3A145F ECE81278
	static scrAny _0x065DB281590CEA2D(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0x065DB281590CEA2D, p0); } // 065DB281590CEA2D A8A21766
	static scrAny _0x3A0014ADB172A3C5(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x3A0014ADB172A3C5, p0, p1); } // 3A0014ADB172A3C5 FA2402C8
}

namespace FIRE
{
	static scrAny START_SCRIPT_FIRE(float p0, float p1, float p2, scrAny p3, BOOL p4) { return NativeInvoke::Invoke<scrAny>(0x6B83617E04503888, p0, p1, p2, p3, p4); } // 6B83617E04503888 E7529357
	static void REMOVE_SCRIPT_FIRE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x7FF548385680673F, p0); } // 7FF548385680673F 6B21FE26
	static scrAny START_ENTITY_FIRE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xF6A9D9708F6F23DF, p0); } // F6A9D9708F6F23DF 8928428E
	static void STOP_ENTITY_FIRE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x7F0DD2EBBB651AFF, p0); } // 7F0DD2EBBB651AFF CE8C9066
	static BOOL IS_ENTITY_ON_FIRE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x28D3FED7190D3A0B, p0); } // 28D3FED7190D3A0B 8C73E64F
	static scrAny GET_NUMBER_OF_FIRES_IN_RANGE(float p0, float p1, float p2, float p3) { return NativeInvoke::Invoke<scrAny>(0x50CAD495A460B305, p0, p1, p2, p3); } // 50CAD495A460B305 654D93B7
	static void STOP_FIRE_IN_RANGE(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x056A8A219B8E829F, p0, p1, p2, p3); } // 056A8A219B8E829F 725C7205
	static scrAny GET_CLOSEST_FIRE_POS(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0x352A9F6BCF90081F, p0, p1, p2, p3); } // 352A9F6BCF90081F C4977B47
	static void ADD_EXPLOSION(float p0, float p1, float p2, scrAny p3, float p4, BOOL p5, BOOL p6, float p7) { NativeInvoke::Invoke<scrVoid>(0xE3AD2BDBAEE269AC, p0, p1, p2, p3, p4, p5, p6, p7); } // E3AD2BDBAEE269AC 10AF5258
	static void ADD_OWNED_EXPLOSION(scrAny p0, float p1, float p2, float p3, scrAny p4, float p5, BOOL p6, BOOL p7, float p8) { NativeInvoke::Invoke<scrVoid>(0x172AA1B624FA1013, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 172AA1B624FA1013 27EE0D67
	static void _0x36DD3FE58B5E5212(float p0, float p1, float p2, scrAny p3, scrAny p4, float p5, BOOL p6, BOOL p7, float p8) { NativeInvoke::Invoke<scrVoid>(0x36DD3FE58B5E5212, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 36DD3FE58B5E5212 CF358946
	static scrAny IS_EXPLOSION_IN_AREA(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6) { return NativeInvoke::Invoke<scrAny>(0x2E2EBA0EE7CED0E0, p0, p1, p2, p3, p4, p5, p6); } // 2E2EBA0EE7CED0E0 FB40075B
	static BOOL IS_EXPLOSION_IN_SPHERE(scrAny p0, float p1, float p2, float p3, float p4) { return NativeInvoke::Invoke<BOOL>(0xAB0F816885B0E483, p0, p1, p2, p3, p4); } // AB0F816885B0E483 D455A7F3
	static BOOL IS_EXPLOSION_IN_ANGLED_AREA(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7) { return NativeInvoke::Invoke<BOOL>(0xA079A6C51525DC4B, p0, p1, p2, p3, p4, p5, p6, p7); } // A079A6C51525DC4B 0128FED9
	static scrAny _0x14BA4BA137AF6CEC(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7) { return NativeInvoke::Invoke<scrAny>(0x14BA4BA137AF6CEC, p0, p1, p2, p3, p4, p5, p6, p7); } // 14BA4BA137AF6CEC AEC0D176
}

namespace DECISIONEVENT
{
	static void SET_DECISION_MAKER(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xB604A2942ADED0EE, p0, p1); } // B604A2942ADED0EE 19CEAC9E
	static void CLEAR_DECISION_MAKER_EVENT_RESPONSE(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x4FC9381A7AEE8968, p0, p1); } // 4FC9381A7AEE8968 07ABD94D
	static void BLOCK_DECISION_MAKER_EVENT(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xE42FCDFD0E4196F7, p0, p1); } // E42FCDFD0E4196F7 57506EA6
	static void UNBLOCK_DECISION_MAKER_EVENT(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xD7CD9CF34F2C99E8, p0, p1); } // D7CD9CF34F2C99E8 62A3161D
	static scrAny ADD_SHOCKING_EVENT_AT_POSITION(scrAny p0, float p1, float p2, float p3, float p4) { return NativeInvoke::Invoke<scrAny>(0xD9F8455409B525E9, p0, p1, p2, p3, p4); } // D9F8455409B525E9 0B30F779
	static scrAny ADD_SHOCKING_EVENT_FOR_ENTITY(scrAny p0, scrAny p1, float p2) { return NativeInvoke::Invoke<scrAny>(0x7FD8F3BE76F89422, p0, p1, p2); } // 7FD8F3BE76F89422 A81B5B71
	static BOOL IS_SHOCKING_EVENT_IN_SPHERE(scrAny p0, float p1, float p2, float p3, float p4) { return NativeInvoke::Invoke<BOOL>(0x1374ABB7C15BAB92, p0, p1, p2, p3, p4); } // 1374ABB7C15BAB92 2F98823E
	static BOOL REMOVE_SHOCKING_EVENT(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x2CDA538C44C6CCE5, p0); } // 2CDA538C44C6CCE5 F82D5A87
	static void REMOVE_ALL_SHOCKING_EVENTS(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xEAABE8FDFA21274C, p0); } // EAABE8FDFA21274C 64DF6282
	static void REMOVE_SHOCKING_EVENT_SPAWN_BLOCKING_AREAS() { NativeInvoke::Invoke<scrVoid>(0x340F1415B68AEADE); } // 340F1415B68AEADE A0CE89C8
	static void SUPPRESS_SHOCKING_EVENTS_NEXT_FRAME() { NativeInvoke::Invoke<scrVoid>(0x2F9A292AD0A3BD89); } // 2F9A292AD0A3BD89 4CC674B5
	static void SUPPRESS_SHOCKING_EVENT_TYPE_NEXT_FRAME(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x3FD2EC8BF1F1CF30, p0); } // 3FD2EC8BF1F1CF30 A0FDCB82
	static void SUPPRESS_AGITATION_EVENTS_NEXT_FRAME() { NativeInvoke::Invoke<scrVoid>(0x5F3B7749C112D552); } // 5F3B7749C112D552 80340396
}

namespace ZONE
{
	static scrAny GET_ZONE_AT_COORDS(float p0, float p1, float p2) { return NativeInvoke::Invoke<scrAny>(0x27040C25DE6CB2F4, p0, p1, p2); } // 27040C25DE6CB2F4 C9018181
	static scrAny _0x98CD1D2934B76CC1(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0x98CD1D2934B76CC1, p0); } // 98CD1D2934B76CC1 8EC68304
	static scrAny GET_ZONE_POPSCHEDULE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x4334BC40AA0CB4BB, p0); } // 4334BC40AA0CB4BB 20AB2FC9
	static scrAny GET_NAME_OF_ZONE(float p0, float p1, float p2) { return NativeInvoke::Invoke<scrAny>(0xCD90657D4C30E1CA, p0, p1, p2); } // CD90657D4C30E1CA 7875CE91
	static void SET_ZONE_ENABLED(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xBA5ECEEA120E5611, p0, p1); } // BA5ECEEA120E5611 04E21B03
	static scrAny GET_ZONE_SCUMMINESS(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x5F7B268D15BA0739, p0); } // 5F7B268D15BA0739 B2FB5C4C
	static void _0x5F7D596BAC2E7777(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x5F7D596BAC2E7777, p0, p1); } // 5F7D596BAC2E7777 3F0A3680
	static void _0x5C0DE367AA0D911C(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x5C0DE367AA0D911C, p0); } // 5C0DE367AA0D911C 7A72A24E
	static scrAny _0x7EE64D51E8498728(float p0, float p1, float p2) { return NativeInvoke::Invoke<scrAny>(0x7EE64D51E8498728, p0, p1, p2); } // 7EE64D51E8498728 B5C5C99B
}

namespace ROPE
{
	static scrAny ADD_ROPE(float p0, float p1, float p2, float p3, float p4, float p5, float p6, scrAny p7, float p8, float p9, float p10, BOOL p11, BOOL p12, BOOL p13, float p14, BOOL p15, scrAny *p16) { return NativeInvoke::Invoke<scrAny>(0xE832D760399EB220, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16); } // E832D760399EB220 A592EC74
	static void DELETE_ROPE(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x52B4829281364649, p0); } // 52B4829281364649 748D72AF
	static void DELETE_CHILD_ROPE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xAA5D6B1888E4DB20, p0); } // AA5D6B1888E4DB20 B19B4706
	static BOOL DOES_ROPE_EXIST(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xFD5448BE3111ED96, p0); } // FD5448BE3111ED96 66E4A3AC
	static void _0xF159A63806BB5BA8(scrAny *p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xF159A63806BB5BA8, p0, p1); } // F159A63806BB5BA8 51523B8C
	static void LOAD_ROPE_DATA(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xCBB203C04D1ABD27, p0, p1); } // CBB203C04D1ABD27 9E8F1644
	static void PIN_ROPE_VERTEX(scrAny p0, scrAny p1, float p2, float p3, float p4) { NativeInvoke::Invoke<scrVoid>(0x2B320CF14146B69A, p0, p1, p2, p3, p4); } // 2B320CF14146B69A AE1D101B
	static void UNPIN_ROPE_VERTEX(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x4B5AE2EEE4A8F180, p0, p1); } // 4B5AE2EEE4A8F180 B30B552F
	static scrAny GET_ROPE_VERTEX_COUNT(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x3655F544CD30F0B5, p0); } // 3655F544CD30F0B5 5131CD2C
	static void ATTACH_ENTITIES_TO_ROPE(scrAny p0, scrAny p1, scrAny p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, scrAny p10, scrAny p11, scrAny *p12, scrAny *p13) { NativeInvoke::Invoke<scrVoid>(0x3D95EC8B6D940AC3, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } // 3D95EC8B6D940AC3 7508668F
	static void ATTACH_ROPE_TO_ENTITY(scrAny p0, scrAny p1, float p2, float p3, float p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0x4B490A6832559A65, p0, p1, p2, p3, p4, p5); } // 4B490A6832559A65 B25D9536
	static void DETACH_ROPE_FROM_ENTITY(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xBCF3026912A8647D, p0, p1); } // BCF3026912A8647D 3E720BEE
	static void _0xC8D667EE52114ABA(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xC8D667EE52114ABA, p0); } // C8D667EE52114ABA EAF291A0
	static void _0xDC57A637A20006ED(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xDC57A637A20006ED, p0, p1); } // DC57A637A20006ED 80DB77A7
	static void _0x36CCB9BE67B970FD(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x36CCB9BE67B970FD, p0, p1); } // 36CCB9BE67B970FD C67D5CF6
	static BOOL _0x84DE3B5FB3E666F0(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x84DE3B5FB3E666F0, p0); } // 84DE3B5FB3E666F0 7A18BB9C
	static scrVector3 GET_ROPE_LAST_VERTEX_COORD(scrAny p0) { return NativeInvoke::Invoke<scrVector3>(0x21BB0FBD3E217C2D, p0); } // 21BB0FBD3E217C2D 91F6848B
	static scrVector3 GET_ROPE_VERTEX_COORD(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrVector3>(0xEA61CA8E80F09E4D, p0, p1); } // EA61CA8E80F09E4D 84374452
	static void _0x1461C72C889E343E(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x1461C72C889E343E, p0); } // 1461C72C889E343E 5187BED3
	static void _0xCB2D4AB84A19AA7C(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xCB2D4AB84A19AA7C, p0); } // CB2D4AB84A19AA7C 46826B53
	static void _0x538D1179EC1AA9A9(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x538D1179EC1AA9A9, p0); } // 538D1179EC1AA9A9 FC0DB4C3
	static void _0xFFF3A50779EFBBB3(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xFFF3A50779EFBBB3, p0); } // FFF3A50779EFBBB3 2EEDB18F
	static void _0x5389D48EFA2F079A(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x5389D48EFA2F079A, p0); } // 5389D48EFA2F079A 43E92628
	static void ROPE_LOAD_TEXTURES() { NativeInvoke::Invoke<scrVoid>(0x9B9039DBF2D258C1); } // 9B9039DBF2D258C1 BA97CE91
	static BOOL _0xF2D0E6A75CC05597() { return NativeInvoke::Invoke<BOOL>(0xF2D0E6A75CC05597); } // F2D0E6A75CC05597 5FDC1047
	static void ROPE_UNLOAD_TEXTURES() { NativeInvoke::Invoke<scrVoid>(0x6CE36C35C1AC8163); } // 6CE36C35C1AC8163 584463E0
	static void _0xBC0CE682D4D05650(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9, scrAny p10, scrAny p11, scrAny p12, scrAny p13) { NativeInvoke::Invoke<scrVoid>(0xBC0CE682D4D05650, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); } // BC0CE682D4D05650 106BA127
	static void _0xB1B6216CA2E7B55E(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xB1B6216CA2E7B55E, p0, p1, p2); } // B1B6216CA2E7B55E 7C6F7668
	static void _0xB743F735C03D7810(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xB743F735C03D7810, p0, p1); } // B743F735C03D7810 686672DD
	static float _0x73040398DFF9A4A6(scrAny p0) { return NativeInvoke::Invoke<float>(0x73040398DFF9A4A6, p0); } // 73040398DFF9A4A6 FD309DC8
	static void ROPE_FORCE_LENGTH(scrAny p0, float p1) { NativeInvoke::Invoke<scrVoid>(0xD009F759A723DB1B, p0, p1); } // D009F759A723DB1B ABF3130F
	static void ROPE_RESET_LENGTH(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xC16DE94D9BEA14A0, p0, p1); } // C16DE94D9BEA14A0 C8A423A3
	static void _0xE37F721824571784(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6) { NativeInvoke::Invoke<scrVoid>(0xE37F721824571784, p0, p1, p2, p3, p4, p5, p6); } // E37F721824571784 A2A5C9FE
	static void SET_DAMPING(scrAny p0, scrAny p1, float p2) { NativeInvoke::Invoke<scrVoid>(0xEEA3B200A6FEB65B, p0, p1, p2); } // EEA3B200A6FEB65B CFB37773
	static void ACTIVATE_PHYSICS(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x710311ADF0E20730, p0); } // 710311ADF0E20730 031711B8
	static void _0xD8FA3908D7B86904(scrAny p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0xD8FA3908D7B86904, p0, p1, p2, p3); } // D8FA3908D7B86904 59910AB2
	static scrVector3 _0x8214A4B5A7A33612(scrAny p0) { return NativeInvoke::Invoke<scrVector3>(0x8214A4B5A7A33612, p0); } // 8214A4B5A7A33612 49A11F0D
	static void _0xBE520D9761FF811F(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xBE520D9761FF811F, p0); } // BE520D9761FF811F A5B55421
	static void BREAK_ENTITY_GLASS(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, scrAny p9, BOOL p10) { NativeInvoke::Invoke<scrVoid>(0x2E648D16F6E308F3, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); } // 2E648D16F6E308F3 D0E0402F
	static void SET_DISABLE_BREAKING(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x5CEC1A84620E7D5B, p0, p1); } // 5CEC1A84620E7D5B EE77C326
	static void _0xCC6E963682533882(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xCC6E963682533882, p0); } // CC6E963682533882
	static void _0x01BA3AED21C16CFB(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x01BA3AED21C16CFB, p0, p1); } // 01BA3AED21C16CFB 97269DC8
}

namespace WATER
{
	static BOOL GET_WATER_HEIGHT(float p0, float p1, float p2, scrAny *p3) { return NativeInvoke::Invoke<BOOL>(0xF6829842C06AE524, p0, p1, p2, p3); } // F6829842C06AE524 D864E17C
	static BOOL GET_WATER_HEIGHT_NO_WAVES(float p0, float p1, float p2, scrAny *p3) { return NativeInvoke::Invoke<BOOL>(0x8EE6B53CE13A9794, p0, p1, p2, p3); } // 8EE6B53CE13A9794 262017F8
	static scrAny _0xFFA5D878809819DB(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6) { return NativeInvoke::Invoke<scrAny>(0xFFA5D878809819DB, p0, p1, p2, p3, p4, p5, p6); } // FFA5D878809819DB AA4AE00C
	static scrAny _0x8974647ED222EA5F(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7) { return NativeInvoke::Invoke<scrAny>(0x8974647ED222EA5F, p0, p1, p2, p3, p4, p5, p6, p7); } // 8974647ED222EA5F 4A962D55
	static scrAny _0x2B3451FA1E3142E2(float p0, float p1, float p2, scrAny p3, scrAny *p4) { return NativeInvoke::Invoke<scrAny>(0x2B3451FA1E3142E2, p0, p1, p2, p3, p4); } // 2B3451FA1E3142E2 4C71D143
	static void MODIFY_WATER(float p0, float p1, float p2, float p3) { NativeInvoke::Invoke<scrVoid>(0xC443FD757C3BA637, p0, p1, p2, p3); } // C443FD757C3BA637 C49E005A
	static scrAny _0xFDBF4CDBC07E1706(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { return NativeInvoke::Invoke<scrAny>(0xFDBF4CDBC07E1706, p0, p1, p2, p3, p4); } // FDBF4CDBC07E1706
	static void _0xB1252E3E59A82AAF(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xB1252E3E59A82AAF, p0); } // B1252E3E59A82AAF
}

namespace WORLDPROBE
{
	static scrAny _0x7EE9F5D83DD4F90E(float p0, float p1, float p2, float p3, float p4, float p5, scrAny p6, scrAny p7, scrAny p8) { return NativeInvoke::Invoke<scrAny>(0x7EE9F5D83DD4F90E, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 7EE9F5D83DD4F90E EFAF4BA6
	static scrAny _0x377906D8A31E5586(float p0, float p1, float p2, float p3, float p4, float p5, scrAny p6, scrAny p7, scrAny p8) { return NativeInvoke::Invoke<scrAny>(0x377906D8A31E5586, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 377906D8A31E5586 8251485D
	static scrAny _0x052837721A854EC7(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0x052837721A854EC7, p0, p1, p2); } // 052837721A854EC7 CEEAD94B
	static scrAny _0xFE466162C4401D18(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, scrAny p9, scrAny p10, scrAny p11, scrAny p12) { return NativeInvoke::Invoke<scrAny>(0xFE466162C4401D18, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); } // FE466162C4401D18 249BC876
	static scrAny _0x37181417CE7C8900(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0x37181417CE7C8900, p0, p1, p2); } // 37181417CE7C8900 13BC46C0
	static scrAny _0x28579D1B8F8AAC80(float p0, float p1, float p2, float p3, float p4, float p5, float p6, scrAny p7, scrAny p8, scrAny p9) { return NativeInvoke::Invoke<scrAny>(0x28579D1B8F8AAC80, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 28579D1B8F8AAC80 591EA833
	static scrAny _0xE6AC6C45FBE83004(float p0, float p1, float p2, float p3, float p4, float p5, float p6, scrAny p7, scrAny p8, scrAny p9) { return NativeInvoke::Invoke<scrAny>(0xE6AC6C45FBE83004, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // E6AC6C45FBE83004 4559460A
	static scrAny _0x3D87450E15D98694(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4) { return NativeInvoke::Invoke<scrAny>(0x3D87450E15D98694, p0, p1, p2, p3, p4); } // 3D87450E15D98694 F3C2875A
	static scrAny _0x65287525D951F6BE(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { return NativeInvoke::Invoke<scrAny>(0x65287525D951F6BE, p0, p1, p2, p3, p4, p5); } // 65287525D951F6BE 4301E10C
	static void _0x2B3334BCA57CD799(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x2B3334BCA57CD799, p0); } // 2B3334BCA57CD799 EC2AAF06
}

namespace NETWORK
{
	static BOOL NETWORK_IS_SIGNED_IN() { return NativeInvoke::Invoke<BOOL>(0x054354A99211EB96); } // 054354A99211EB96 ADD0B40F
	static BOOL NETWORK_IS_SIGNED_ONLINE() { return NativeInvoke::Invoke<BOOL>(0x1077788E268557C2); } // 1077788E268557C2 6E5BDCE2
	static scrAny _0xBD545D44CCE70597() { return NativeInvoke::Invoke<scrAny>(0xBD545D44CCE70597); } // BD545D44CCE70597
	static scrAny _0x74FB3E29E6D10FA9() { return NativeInvoke::Invoke<scrAny>(0x74FB3E29E6D10FA9); } // 74FB3E29E6D10FA9
	static BOOL _0x85443FF4C328F53B() { return NativeInvoke::Invoke<BOOL>(0x85443FF4C328F53B); } // 85443FF4C328F53B 3FB40673
	static BOOL NETWORK_IS_CLOUD_AVAILABLE() { return NativeInvoke::Invoke<BOOL>(0x9A4CF4F48AD77302); } // 9A4CF4F48AD77302 C7FF5AFC
	static BOOL _0x67A5589628E0CFF6() { return NativeInvoke::Invoke<BOOL>(0x67A5589628E0CFF6); } // 67A5589628E0CFF6 66EC713F
	static BOOL _0xBA9775570DB788CF() { return NativeInvoke::Invoke<BOOL>(0xBA9775570DB788CF); } // BA9775570DB788CF 358D1D77
	static BOOL NETWORK_IS_HOST() { return NativeInvoke::Invoke<BOOL>(0x8DB296B814EDDA07); } // 8DB296B814EDDA07 E46AC10F
	static BOOL _0xA306F470D1660581() { return NativeInvoke::Invoke<BOOL>(0xA306F470D1660581); } // A306F470D1660581
	static scrAny _0x4237E822315D8BA9() { return NativeInvoke::Invoke<scrAny>(0x4237E822315D8BA9); } // 4237E822315D8BA9
	static BOOL NETWORK_HAVE_ONLINE_PRIVILEGES() { return NativeInvoke::Invoke<BOOL>(0x25CB5A9F37BFD063); } // 25CB5A9F37BFD063 EF63BFDF
	static BOOL _0x1353F87E89946207() { return NativeInvoke::Invoke<BOOL>(0x1353F87E89946207); } // 1353F87E89946207
	static BOOL _0x72D918C99BCACC54(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x72D918C99BCACC54, p0); } // 72D918C99BCACC54 1F88819D
	static BOOL _0xAEEF48CDF5B6CE7C(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xAEEF48CDF5B6CE7C, p0, p1); } // AEEF48CDF5B6CE7C 2D817A5E
	static BOOL _0x78321BEA235FD8CD(scrAny p0, BOOL p1) { return NativeInvoke::Invoke<BOOL>(0x78321BEA235FD8CD, p0, p1); } // 78321BEA235FD8CD
	static BOOL _0x595F028698072DD9(scrAny p0, scrAny p1, BOOL p2) { return NativeInvoke::Invoke<BOOL>(0x595F028698072DD9, p0, p1, p2); } // 595F028698072DD9 BB54AA3D
	static BOOL _0x83F28CE49FBBFFBA(scrAny p0, scrAny p1, BOOL p2) { return NativeInvoke::Invoke<BOOL>(0x83F28CE49FBBFFBA, p0, p1, p2); } // 83F28CE49FBBFFBA
	static BOOL _0x76BF03FADBF154F5() { return NativeInvoke::Invoke<BOOL>(0x76BF03FADBF154F5); } // 76BF03FADBF154F5
	static scrAny _0x9614B71F8ADB982B() { return NativeInvoke::Invoke<scrAny>(0x9614B71F8ADB982B); } // 9614B71F8ADB982B
	static BOOL _0x5EA784D197556507() { return NativeInvoke::Invoke<BOOL>(0x5EA784D197556507); } // 5EA784D197556507
	static void _0x83FE8D7229593017() { NativeInvoke::Invoke<scrVoid>(0x83FE8D7229593017); } // 83FE8D7229593017
	static BOOL _0x580CE4438479CC61() { return NativeInvoke::Invoke<BOOL>(0x580CE4438479CC61); } // 580CE4438479CC61 60E1FEDF
	static void NETWORK_BAIL() { NativeInvoke::Invoke<scrVoid>(0x95914459A87EBA28); } // 95914459A87EBA28 87D79A04
	static void _0x283B6062A2C01E9B() { NativeInvoke::Invoke<scrVoid>(0x283B6062A2C01E9B); } // 283B6062A2C01E9B 96E28FE2
	static BOOL _0xAF50DA1A3F8B1BA4(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xAF50DA1A3F8B1BA4, p0); } // AF50DA1A3F8B1BA4 A520B982
	static BOOL _0x9747292807126EDA() { return NativeInvoke::Invoke<BOOL>(0x9747292807126EDA); } // 9747292807126EDA 05518C0F
	static BOOL NETWORK_CAN_ENTER_MULTIPLAYER() { return NativeInvoke::Invoke<BOOL>(0x7E782A910C362C25); } // 7E782A910C362C25 4A23B9C9
	static scrAny NETWORK_SESSION_ENTER(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { return NativeInvoke::Invoke<scrAny>(0x330ED4D05491934F, p0, p1, p2, p3, p4, p5); } // 330ED4D05491934F 543CD2BE
	static BOOL _0x2CFC76E0D087C994(scrAny p0, scrAny p1, scrAny p2, BOOL p3) { return NativeInvoke::Invoke<BOOL>(0x2CFC76E0D087C994, p0, p1, p2, p3); } // 2CFC76E0D087C994 4E53202A
	static BOOL _0x94BC51E9449D917F(scrAny p0, scrAny p1, scrAny p2, scrAny p3, BOOL p4) { return NativeInvoke::Invoke<BOOL>(0x94BC51E9449D917F, p0, p1, p2, p3, p4); } // 94BC51E9449D917F D7624E6B
	static BOOL _0xBE3E347A87ACEB82(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<BOOL>(0xBE3E347A87ACEB82, p0, p1, p2, p3); } // BE3E347A87ACEB82 3F75CC38
	static BOOL NETWORK_SESSION_HOST(scrAny p0, scrAny p1, BOOL p2) { return NativeInvoke::Invoke<BOOL>(0x6F3D4ED9BEE4E61D, p0, p1, p2); } // 6F3D4ED9BEE4E61D 6716460F
	static BOOL _0xED34C0C02C098BB7(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xED34C0C02C098BB7, p0, p1); } // ED34C0C02C098BB7 8AC9EA19
	static BOOL NETWORK_SESSION_HOST_FRIENDS_ONLY(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xB9CFD27A5D578D83, p0, p1); } // B9CFD27A5D578D83 26864403
	static BOOL _0xFBCFA2EA2E206890() { return NativeInvoke::Invoke<BOOL>(0xFBCFA2EA2E206890); } // FBCFA2EA2E206890 56E75FE4
	static BOOL _0x74732C6CA90DA2B4() { return NativeInvoke::Invoke<BOOL>(0x74732C6CA90DA2B4); } // 74732C6CA90DA2B4 A95299B9
	static BOOL _0xF3929C2379B60CCE() { return NativeInvoke::Invoke<BOOL>(0xF3929C2379B60CCE); } // F3929C2379B60CCE 3D2C1916
	static BOOL _0xCEF70AA5B3F89BA1() { return NativeInvoke::Invoke<BOOL>(0xCEF70AA5B3F89BA1); } // CEF70AA5B3F89BA1 DB67785D
	static BOOL NETWORK_SESSION_END(BOOL p0, BOOL p1) { return NativeInvoke::Invoke<BOOL>(0xA02E59562D711006, p0, p1); } // A02E59562D711006 BCACBEA2
	static void NETWORK_SESSION_KICK_PLAYER(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xFA8904DC5F304220, p0); } // FA8904DC5F304220 1E20138A
	static BOOL _0xD6D09A6F32F49EF1(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xD6D09A6F32F49EF1, p0); } // D6D09A6F32F49EF1 8A559D26
	static BOOL _0x59DF79317F85A7E0() { return NativeInvoke::Invoke<BOOL>(0x59DF79317F85A7E0); } // 59DF79317F85A7E0
	static BOOL _0xFFE1E5B792D92B34() { return NativeInvoke::Invoke<BOOL>(0xFFE1E5B792D92B34); } // FFE1E5B792D92B34
	static void _0x49EC8030F5015F8B(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x49EC8030F5015F8B, p0); } // 49EC8030F5015F8B 3C3E2AB6
	static void _0x8B6A4DD0AF9CE215(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x8B6A4DD0AF9CE215, p0, p1); } // 8B6A4DD0AF9CE215 5F29A7E0
	static scrAny _0x56CE820830EF040B(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x56CE820830EF040B, p0); } // 56CE820830EF040B 36EAD960
	static void _0xCAE55F48D3D7875C(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xCAE55F48D3D7875C, p0); } // CAE55F48D3D7875C 5BE529F7
	static void _0xF49ABC20D8552257(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xF49ABC20D8552257, p0); } // F49ABC20D8552257 454C7B67
	static void _0x4811BBAC21C5FCD5(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x4811BBAC21C5FCD5, p0); } // 4811BBAC21C5FCD5 E5961511
	static void _0x5539C3EBF104A53A(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x5539C3EBF104A53A, p0); } // 5539C3EBF104A53A AE396263
	static void _0x702BC4D605522539(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x702BC4D605522539, p0); } // 702BC4D605522539 913FD7D6
	static void _0x3F52E880AAF6C8CA(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x3F52E880AAF6C8CA, p0); } // 3F52E880AAF6C8CA B3D9A67F
	static void _0xF1EEA2DDA9FFA69D(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xF1EEA2DDA9FFA69D, p0); } // F1EEA2DDA9FFA69D 6CC062FC
	static void _0x1153FA02A659051C() { NativeInvoke::Invoke<scrVoid>(0x1153FA02A659051C); } // 1153FA02A659051C 57F9BC83
	static void _0xC19F6C8E7865A6FF(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xC19F6C8E7865A6FF, p0); } // C19F6C8E7865A6FF F3768F90
	static void _0x236406F60CF216D6(scrAny *p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x236406F60CF216D6, p0, p1); } // 236406F60CF216D6 0EC62629
	static void _0x058F43EC59A8631A() { NativeInvoke::Invoke<scrVoid>(0x058F43EC59A8631A); } // 058F43EC59A8631A 5E557307
	static void _0x6D03BFBD643B2A02(scrAny *p0, scrAny *p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0x6D03BFBD643B2A02, p0, p1, p2); } // 6D03BFBD643B2A02 74E8C53E
	static void _0x600F8CB31C7AAB6E(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x600F8CB31C7AAB6E, p0); } // 600F8CB31C7AAB6E 959E43A3
	static BOOL _0xE532D6811B3A4D2A(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xE532D6811B3A4D2A, p0); } // E532D6811B3A4D2A 7771AB83
	static BOOL _0xF7B2CFDE5C9F700D(scrAny p0, float p1, float p2, float p3) { return NativeInvoke::Invoke<BOOL>(0xF7B2CFDE5C9F700D, p0, p1, p2, p3); } // F7B2CFDE5C9F700D A13045D4
	static BOOL NETWORK_IS_FINDING_GAMERS() { return NativeInvoke::Invoke<BOOL>(0xDDDF64C91BFCF0AA); } // DDDF64C91BFCF0AA A6DAA79F
	static BOOL _0xF9B83B77929D8863() { return NativeInvoke::Invoke<BOOL>(0xF9B83B77929D8863); } // F9B83B77929D8863 BEDC4503
	static scrAny NETWORK_GET_NUM_FOUND_GAMERS() { return NativeInvoke::Invoke<scrAny>(0xA1B043EE79A916FB); } // A1B043EE79A916FB F4B80C7E
	static BOOL NETWORK_GET_FOUND_GAMER(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x9DCFF2AFB68B3476, p0, p1); } // 9DCFF2AFB68B3476 A08C9141
	static void NETWORK_CLEAR_FOUND_GAMERS() { NativeInvoke::Invoke<scrVoid>(0x6D14CCEE1B40381A); } // 6D14CCEE1B40381A 6AA9A154
	static BOOL _0x85A0EF54A500882C(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x85A0EF54A500882C, p0); } // 85A0EF54A500882C 42BD0780
	static BOOL _0x2CC848A861D01493() { return NativeInvoke::Invoke<BOOL>(0x2CC848A861D01493); } // 2CC848A861D01493 BEB98840
	static BOOL _0x94A8394D150B013A() { return NativeInvoke::Invoke<BOOL>(0x94A8394D150B013A); } // 94A8394D150B013A 08029970
	static BOOL _0x5AE17C6B0134B7F1() { return NativeInvoke::Invoke<BOOL>(0x5AE17C6B0134B7F1); } // 5AE17C6B0134B7F1 C871E745
	static BOOL _0x02A8BEC6FD9AF660(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x02A8BEC6FD9AF660, p0, p1); } // 02A8BEC6FD9AF660 B5ABC4B4
	static void _0x86E0660E4F5C956D() { NativeInvoke::Invoke<scrVoid>(0x86E0660E4F5C956D); } // 86E0660E4F5C956D 3F7EDBBD
	static void NETWORK_IS_PLAYER_ANIMATION_DRAWING_SYNCHRONIZED() { NativeInvoke::Invoke<scrVoid>(0xC6F8AB8A4189CF3A); } // C6F8AB8A4189CF3A 3D6360B5
	static void NETWORK_SESSION_CANCEL_INVITE() { NativeInvoke::Invoke<scrVoid>(0x2FBF47B1B36D36F9); } // 2FBF47B1B36D36F9 20317535
	static void _0xA29177F7703B5644() { NativeInvoke::Invoke<scrVoid>(0xA29177F7703B5644); } // A29177F7703B5644 3FD49D3B
	static BOOL NETWORK_HAS_PENDING_INVITE() { return NativeInvoke::Invoke<BOOL>(0xAC8C7B9B88C4A668); } // AC8C7B9B88C4A668 0C207D6E
	static scrAny _0xC42DD763159F3461() { return NativeInvoke::Invoke<scrAny>(0xC42DD763159F3461); } // C42DD763159F3461 FBBAC350
	static BOOL _0x62A0296C1BB1CEB3() { return NativeInvoke::Invoke<BOOL>(0x62A0296C1BB1CEB3); } // 62A0296C1BB1CEB3 0907A6BF
	static scrAny _0x23DFB504655D0CE4() { return NativeInvoke::Invoke<scrAny>(0x23DFB504655D0CE4); } // 23DFB504655D0CE4 6A0BEA60
	static void NETWORK_SESSION_GET_INVITER(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xE57397B4A3429DD0, p0); } // E57397B4A3429DD0 E9C6B3FD
	static BOOL _0xD313DE83394AF134() { return NativeInvoke::Invoke<BOOL>(0xD313DE83394AF134); } // D313DE83394AF134 3EA9D44C
	static void NETWORK_SUPPRESS_INVITE(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xA0682D67EF1FBA3D, p0); } // A0682D67EF1FBA3D 323DC78C
	static void NETWORK_BLOCK_INVITES(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x34F9E9049454A7A0, p0); } // 34F9E9049454A7A0 D156FD1A
	static void _0xF814FEC6A19FD6E0() { NativeInvoke::Invoke<scrVoid>(0xF814FEC6A19FD6E0); } // F814FEC6A19FD6E0 32B7A076
	static void _0x6B07B9CE4D390375(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x6B07B9CE4D390375, p0); } // 6B07B9CE4D390375 0FCE995D
	static void _0x7AC752103856FB20(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x7AC752103856FB20, p0); } // 7AC752103856FB20 A639DCA2
	static BOOL _0x74698374C45701D2() { return NativeInvoke::Invoke<BOOL>(0x74698374C45701D2); } // 74698374C45701D2 70ED476A
	static void _0x140E6A44870A11CE() { NativeInvoke::Invoke<scrVoid>(0x140E6A44870A11CE); } // 140E6A44870A11CE 50507BED
	static void NETWORK_SESSION_HOST_SINGLE_PLAYER(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xC74C33FCA52856D5, p0); } // C74C33FCA52856D5 F3B1CA85
	static void NETWORK_SESSION_LEAVE_SINGLE_PLAYER() { NativeInvoke::Invoke<scrVoid>(0x3442775428FD2DAA); } // 3442775428FD2DAA C692F86A
	static scrAny NETWORK_IS_GAME_IN_PROGRESS() { return NativeInvoke::Invoke<scrAny>(0x10FAB35428CCC9D7); } // 10FAB35428CCC9D7 09B88E3E
	static BOOL NETWORK_IS_SESSION_ACTIVE() { return NativeInvoke::Invoke<BOOL>(0xD83C2B94E7508980); } // D83C2B94E7508980 715CB8C4
	static BOOL NETWORK_IS_IN_SESSION() { return NativeInvoke::Invoke<BOOL>(0xCA97246103B63917); } // CA97246103B63917 4BC4105E
	static BOOL NETWORK_IS_SESSION_STARTED() { return NativeInvoke::Invoke<BOOL>(0x9DE624D2FC4B603F); } // 9DE624D2FC4B603F 9D854A37
	static BOOL NETWORK_IS_SESSION_BUSY() { return NativeInvoke::Invoke<BOOL>(0xF4435D66A8E2905E); } // F4435D66A8E2905E 8592152D
	static BOOL NETWORK_CAN_SESSION_END() { return NativeInvoke::Invoke<BOOL>(0x4EEBC3694E49C572); } // 4EEBC3694E49C572 E1FCCDBA
	static void _0x271CC6AB59EBF9A5(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x271CC6AB59EBF9A5, p0); } // 271CC6AB59EBF9A5 7017257D
	static scrAny _0xBA416D68C631496A() { return NativeInvoke::Invoke<scrAny>(0xBA416D68C631496A); } // BA416D68C631496A 4977AC28
	static void _0xA73667484D7037C3(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xA73667484D7037C3, p0); } // A73667484D7037C3 E6EEF8AF
	static void _0xB4AB419E0D86ACAE(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xB4AB419E0D86ACAE, p0, p1); } // B4AB419E0D86ACAE 6BB93227
	static void NETWORK_SESSION_VOICE_HOST() { NativeInvoke::Invoke<scrVoid>(0x9C1556705F864230); } // 9C1556705F864230 345C2980
	static void NETWORK_SESSION_VOICE_LEAVE() { NativeInvoke::Invoke<scrVoid>(0x6793E42BE02B575D); } // 6793E42BE02B575D E566C7DA
	static void _0xABD5E88B8A2D3DB2(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xABD5E88B8A2D3DB2, p0); } // ABD5E88B8A2D3DB2 9DFD89E6
	static void NETWORK_SET_KEEP_FOCUSPOINT(BOOL p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x7F8413B7FC2AA6B9, p0, p1); } // 7F8413B7FC2AA6B9 075321B5
	static void _0x5B8ED3DB018927B1(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x5B8ED3DB018927B1, p0); } // 5B8ED3DB018927B1 6EFC2FD0
	static BOOL _0x855BC38818F6F684() { return NativeInvoke::Invoke<BOOL>(0x855BC38818F6F684); } // 855BC38818F6F684 60AA4AA1
	static BOOL _0xEF0912DDF7C4CB4B() { return NativeInvoke::Invoke<BOOL>(0xEF0912DDF7C4CB4B); } // EF0912DDF7C4CB4B 132CA01E
	static BOOL _0x3A214F2EC889B100(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x3A214F2EC889B100, p0, p1); } // 3A214F2EC889B100 AFFEA720
	static void NETWORK_SET_ACTIVITY_SPECTATOR(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x75138790B4359A74, p0); } // 75138790B4359A74 FC9AD060
	static scrAny NETWORK_IS_ACTIVITY_SPECTATOR() { return NativeInvoke::Invoke<scrAny>(0x12103B9E0C9F92FB); } // 12103B9E0C9F92FB AF329720
	static void NETWORK_SET_ACTIVITY_SPECTATOR_MAX(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x9D277B76D1D12222, p0); } // 9D277B76D1D12222 74E0BC0A
	static scrAny NETWORK_GET_ACTIVITY_PLAYER_NUM(BOOL p0) { return NativeInvoke::Invoke<scrAny>(0x73E2B500410DA5A2, p0); } // 73E2B500410DA5A2 31F951FD
	static scrAny NETWORK_IS_ACTIVITY_SPECTATOR_FROM_HANDLE(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0x2763BBAA72A7BCB9, p0); } // 2763BBAA72A7BCB9 58F1DF7D
	static scrAny NETWORK_HOST_TRANSITION(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { return NativeInvoke::Invoke<scrAny>(0xA60BB5CE242BB254, p0, p1, p2, p3, p4, p5); } // A60BB5CE242BB254 146764FB
	static BOOL _0x71FB0EBCD4915D56(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<BOOL>(0x71FB0EBCD4915D56, p0, p1, p2, p3); } // 71FB0EBCD4915D56 2FF65C0B
	static BOOL _0xA091A5E44F0072E5(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<BOOL>(0xA091A5E44F0072E5, p0, p1, p2, p3); } // A091A5E44F0072E5 47D61C99
	static BOOL _0x9C4AB58491FDC98A(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny *p4, scrAny p5) { return NativeInvoke::Invoke<BOOL>(0x9C4AB58491FDC98A, p0, p1, p2, p3, p4, p5); } // 9C4AB58491FDC98A 5CE60A11
	static BOOL _0xA06509A691D12BE4() { return NativeInvoke::Invoke<BOOL>(0xA06509A691D12BE4); } // A06509A691D12BE4 0D7E5CF9
	static void _0xB13E88E655E5A3BC() { NativeInvoke::Invoke<scrVoid>(0xB13E88E655E5A3BC); } // B13E88E655E5A3BC 36A5F2DA
	static void _0x261E97AD7BCF3D40(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x261E97AD7BCF3D40, p0); } // 261E97AD7BCF3D40 7EF353E1
	static void _0x39917E1B4CB0F911(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x39917E1B4CB0F911, p0); } // 39917E1B4CB0F911 F60986FC
	static void NETWORK_SET_TRANSITION_CREATOR_HANDLE(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xEF26739BCD9907D5, p0); } // EF26739BCD9907D5 1DD01FE7
	static void NETWORK_CLEAR_TRANSITION_CREATOR_HANDLE() { NativeInvoke::Invoke<scrVoid>(0xFB3272229A82C759); } // FB3272229A82C759 8BB336F7
	static BOOL NETWORK_INVITE_GAMERS_TO_TRANSITION(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x4A595C32F77DFF76, p0, p1); } // 4A595C32F77DFF76 5332E645
	static void NETWORK_SET_GAMER_INVITED_TO_TRANSITION(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xCA2C8073411ECDB6, p0); } // CA2C8073411ECDB6 17F1C69D
	static scrAny NETWORK_LEAVE_TRANSITION() { return NativeInvoke::Invoke<scrAny>(0xD23A1A815D21DB19); } // D23A1A815D21DB19 3A3599B7
	static BOOL NETWORK_LAUNCH_TRANSITION() { return NativeInvoke::Invoke<BOOL>(0x2DCF46CB1A4F0884); } // 2DCF46CB1A4F0884 E3570BA2
	static void _0xEAA572036990CD1B() { NativeInvoke::Invoke<scrVoid>(0xEAA572036990CD1B); } // EAA572036990CD1B B59D74CA
	static BOOL NETWORK_DO_TRANSITION_TO_GAME(BOOL p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x3E9BB38102A589B0, p0, p1); } // 3E9BB38102A589B0 1B2114D2
	static BOOL NETWORK_DO_TRANSITION_TO_NEW_GAME(BOOL p0, scrAny p1, BOOL p2) { return NativeInvoke::Invoke<BOOL>(0x4665F51EFED00034, p0, p1, p2); } // 4665F51EFED00034 58AFBE63
	static BOOL NETWORK_DO_TRANSITION_TO_FREEMODE(scrAny *p0, scrAny p1, BOOL p2, scrAny p3) { return NativeInvoke::Invoke<BOOL>(0x3AAD8B2FCA1E289F, p0, p1, p2, p3); } // 3AAD8B2FCA1E289F C7CB8ADF
	static BOOL NETWORK_DO_TRANSITION_TO_NEW_FREEMODE(scrAny *p0, scrAny p1, scrAny p2, BOOL p3, BOOL p4) { return NativeInvoke::Invoke<BOOL>(0x9E80A5BA8109F974, p0, p1, p2, p3, p4); } // 9E80A5BA8109F974 AD13375E
	static scrAny NETWORK_IS_TRANSITION_TO_GAME() { return NativeInvoke::Invoke<scrAny>(0x9D7696D8F4FA6CB7); } // 9D7696D8F4FA6CB7 17146B2B
	static scrAny NETWORK_GET_TRANSITION_MEMBERS(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x73B000F7FBC55829, p0, p1); } // 73B000F7FBC55829 31F19263
	static void _0x521638ADA1BA0D18(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x521638ADA1BA0D18, p0, p1); } // 521638ADA1BA0D18 CEE79711
	static void _0xEBEFC2E77084F599(scrAny p0, scrAny *p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xEBEFC2E77084F599, p0, p1, p2); } // EBEFC2E77084F599 E0C28DB5
	static BOOL NETWORK_SEND_TRANSITION_GAMER_INSTRUCTION(scrAny *p0, scrAny *p1, scrAny p2, scrAny p3, BOOL p4) { return NativeInvoke::Invoke<BOOL>(0x31D1D2B858D25E6B, p0, p1, p2, p3, p4); } // 31D1D2B858D25E6B 468B0884
	static BOOL NETWORK_MARK_TRANSITION_GAMER_AS_FULLY_JOINED(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x5728BB6D63E3FF1D, p0); } // 5728BB6D63E3FF1D 03383F57
	static BOOL NETWORK_IS_TRANSITION_HOST() { return NativeInvoke::Invoke<BOOL>(0x0B824797C9BF2159); } // 0B824797C9BF2159 0C0900BC
	static BOOL NETWORK_IS_TRANSITION_HOST_FROM_HANDLE(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x6B5C83BA3EFE6A10, p0); } // 6B5C83BA3EFE6A10 0E2854C4
	static BOOL NETWORK_GET_TRANSITION_HOST(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x65042B9774C4435E, p0); } // 65042B9774C4435E 73098D40
	static scrAny NETWORK_IS_IN_TRANSITION() { return NativeInvoke::Invoke<scrAny>(0x68049AEFF83D8F0A); } // 68049AEFF83D8F0A C3CDB626
	static scrAny NETWORK_IS_TRANSITION_STARTED() { return NativeInvoke::Invoke<scrAny>(0x53FA83401D9C07FE); } // 53FA83401D9C07FE 7917E111
	static scrAny NETWORK_IS_TRANSITION_BUSY() { return NativeInvoke::Invoke<scrAny>(0x520F3282A53D26B7); } // 520F3282A53D26B7 A357A2C6
	static scrAny _0x292564C735375EDF() { return NativeInvoke::Invoke<scrAny>(0x292564C735375EDF); } // 292564C735375EDF 8262C70E
	static void _0x2B3A8F7CA3A38FDE() { NativeInvoke::Invoke<scrVoid>(0x2B3A8F7CA3A38FDE); } // 2B3A8F7CA3A38FDE C71E607B
	static void _0x43F4DBA69710E01E() { NativeInvoke::Invoke<scrVoid>(0x43F4DBA69710E01E); } // 43F4DBA69710E01E 82D32D07
	static BOOL _0x37A4494483B9F5C9() { return NativeInvoke::Invoke<BOOL>(0x37A4494483B9F5C9); } // 37A4494483B9F5C9 C901AA9F
	static void _0x30DE938B516F0AD2(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x30DE938B516F0AD2, p0); } // 30DE938B516F0AD2 CCA9C022
	static void _0xEEEDA5E6D7080987(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xEEEDA5E6D7080987, p0, p1); } // EEEDA5E6D7080987 1E5F6AEF
	static void _0x973D76AA760A6CB6(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x973D76AA760A6CB6, p0); } // 973D76AA760A6CB6 0532DDD2
	static BOOL NETWORK_HAS_PLAYER_STARTED_TRANSITION(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x9AC9CCBFA8C29795, p0); } // 9AC9CCBFA8C29795 4ABD1E59
	static BOOL _0x2615AA2A695930C1(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x2615AA2A695930C1, p0); } // 2615AA2A695930C1 CDEBCCE7
	static BOOL NETWORK_JOIN_TRANSITION(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x9D060B08CD63321A, p0); } // 9D060B08CD63321A B054EC4B
	static BOOL _0x7284A47B3540E6CF(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x7284A47B3540E6CF, p0); } // 7284A47B3540E6CF 4F41DF6B
	static BOOL NETWORK_IS_ACTIVITY_SESSION() { return NativeInvoke::Invoke<BOOL>(0x05095437424397FA); } // 05095437424397FA 577DAA8A
	static void _0x4A9FDE3A5A6D0437(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x4A9FDE3A5A6D0437, p0); } // 4A9FDE3A5A6D0437 18F03AFD
	static BOOL _0xC3C7A6AFDB244624(scrAny *p0, scrAny *p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<BOOL>(0xC3C7A6AFDB244624, p0, p1, p2, p3); } // C3C7A6AFDB244624 8B99B72B
	static BOOL _0xC116FF9B4D488291(scrAny *p0, scrAny *p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<BOOL>(0xC116FF9B4D488291, p0, p1, p2, p3); } // C116FF9B4D488291 877C0E1C
	static scrAny _0x742B58F723233ED9(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x742B58F723233ED9, p0); } // 742B58F723233ED9 5E832444
	static scrAny _0xCEFA968912D0F78D() { return NativeInvoke::Invoke<scrAny>(0xCEFA968912D0F78D); } // CEFA968912D0F78D 3FDA00F3
	static BOOL NETWORK_ACCEPT_PRESENCE_INVITE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xFA91550DF9318B22, p0); } // FA91550DF9318B22 E5DA4CED
	static BOOL _0xF0210268DB0974B1(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xF0210268DB0974B1, p0); } // F0210268DB0974B1 93C665FA
	static scrAny _0xDFF09646E12EC386(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xDFF09646E12EC386, p0); } // DFF09646E12EC386 D50DF46C
	static scrAny _0x4962CC4AA2F345B7(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x4962CC4AA2F345B7, p0); } // 4962CC4AA2F345B7 19EC65D9
	static BOOL NETWORK_GET_PRESENCE_INVITE_HANDLE(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x38D5B0FEBB086F75, p0, p1); } // 38D5B0FEBB086F75 B2451429
	static scrAny _0x26E1CD96B0903D60(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x26E1CD96B0903D60, p0); } // 26E1CD96B0903D60 C5E0C989
	static scrAny _0x24409FC4C55CB22D(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x24409FC4C55CB22D, p0); } // 24409FC4C55CB22D A4302183
	static scrAny _0xD39B3FFF8FFDD5BF(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xD39B3FFF8FFDD5BF, p0); } // D39B3FFF8FFDD5BF 51B2D848
	static scrAny _0x728C4CC7920CD102(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x728C4CC7920CD102, p0); } // 728C4CC7920CD102 4677C656
	static BOOL _0x3DBF2DF0AEB7D289(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x3DBF2DF0AEB7D289, p0); } // 3DBF2DF0AEB7D289 F5E3401C
	static BOOL _0x8806CEBFABD3CE05(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x8806CEBFABD3CE05, p0); } // 8806CEBFABD3CE05 7D593B4C
	static BOOL _0x76D9B976C4C09FDE() { return NativeInvoke::Invoke<BOOL>(0x76D9B976C4C09FDE); } // 76D9B976C4C09FDE E96CFE7D
	static BOOL _0xC88156EBB786F8D5() { return NativeInvoke::Invoke<BOOL>(0xC88156EBB786F8D5); } // C88156EBB786F8D5 AB969F00
	static BOOL _0x439BFDE3CD0610F6() { return NativeInvoke::Invoke<BOOL>(0x439BFDE3CD0610F6); } // 439BFDE3CD0610F6 3242F952
	static void _0xEBF8284D8CADEB53() { NativeInvoke::Invoke<scrVoid>(0xEBF8284D8CADEB53); } // EBF8284D8CADEB53 9773F36A
	static void NETWORK_REMOVE_TRANSITION_INVITE(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x7524B431B2E6F7EE, p0); } // 7524B431B2E6F7EE FDE84CB7
	static void _0x726E0375C7A26368() { NativeInvoke::Invoke<scrVoid>(0x726E0375C7A26368); } // 726E0375C7A26368 F7134E73
	static void _0xF083835B70BA9BFE() { NativeInvoke::Invoke<scrVoid>(0xF083835B70BA9BFE); } // F083835B70BA9BFE C47352E7
	static BOOL NETWORK_INVITE_GAMERS(scrAny *p0, scrAny p1, scrAny *p2, scrAny *p3) { return NativeInvoke::Invoke<BOOL>(0x9D80CD1D0E6327DE, p0, p1, p2, p3); } // 9D80CD1D0E6327DE 52FB8074
	static BOOL _0x4D86CD31E8976ECE(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x4D86CD31E8976ECE, p0); } // 4D86CD31E8976ECE EC651BC0
	static BOOL NETWORK_GET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x74881E6BCAE2327C, p0); } // 74881E6BCAE2327C 72BA00CE
	static BOOL NETWORK_SET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x7206F674F2A3B1BB, p0); } // 7206F674F2A3B1BB FD95899E
	static void _0x66F010A4B031A331(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x66F010A4B031A331, p0); } // 66F010A4B031A331
	static void _0x0D77A82DC2D0DA59(scrAny *p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x0D77A82DC2D0DA59, p0, p1); } // 0D77A82DC2D0DA59 0808D4CC
	static BOOL FILLOUT_PM_PLAYER_LIST(scrAny *p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0xCBBD7C4991B64809, p0, p1, p2); } // CBBD7C4991B64809 CE40F423
	static BOOL FILLOUT_PM_PLAYER_LIST_WITH_NAMES(scrAny *p0, scrAny *p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<BOOL>(0x716B6DB9D1886106, p0, p1, p2, p3); } // 716B6DB9D1886106 B8DF604E
	static BOOL USING_NETWORK_WEAPONTYPE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xE26CCFF8094D8C74, p0); } // E26CCFF8094D8C74 F49C1533
	static BOOL _0x2FC5650B0271CB57() { return NativeInvoke::Invoke<BOOL>(0x2FC5650B0271CB57); } // 2FC5650B0271CB57 A812B6CB
	static scrAny _0x01ABCE5E7CBDA196() { return NativeInvoke::Invoke<scrAny>(0x01ABCE5E7CBDA196); } // 01ABCE5E7CBDA196
	static scrAny _0x120364DE2845DAF8(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x120364DE2845DAF8, p0, p1); } // 120364DE2845DAF8 F30E5814
	static BOOL _0xFD8B834A8BA05048() { return NativeInvoke::Invoke<BOOL>(0xFD8B834A8BA05048); } // FD8B834A8BA05048 C6609191
	static BOOL _0x8DE9945BCC9AEC52(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x8DE9945BCC9AEC52, p0); } // 8DE9945BCC9AEC52 51367B34
	static scrAny NETWORK_IS_IN_PARTY() { return NativeInvoke::Invoke<scrAny>(0x966C2BC2A7FE3F30); } // 966C2BC2A7FE3F30 F9D7D67D
	static scrAny NETWORK_IS_PARTY_MEMBER(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x676ED266AADD31E0, p0); } // 676ED266AADD31E0 1D0C929D
	static BOOL _0x2BF66D2E7414F686() { return NativeInvoke::Invoke<BOOL>(0x2BF66D2E7414F686); } // 2BF66D2E7414F686 9156EFC0
	static BOOL _0x14922ED3E38761F0() { return NativeInvoke::Invoke<BOOL>(0x14922ED3E38761F0); } // 14922ED3E38761F0 8FA6EE0E
	static void _0xFA2888E3833C8E96() { NativeInvoke::Invoke<scrVoid>(0xFA2888E3833C8E96); } // FA2888E3833C8E96 7F70C15A
	static void _0x77FADDCBE3499DF7(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x77FADDCBE3499DF7, p0); } // 77FADDCBE3499DF7 8179C48A
	static void _0xF1B84178F8674195(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xF1B84178F8674195, p0); } // F1B84178F8674195 41702C8A
	static scrAny _0x599E4FA1F87EB5FF() { return NativeInvoke::Invoke<scrAny>(0x599E4FA1F87EB5FF); } // 599E4FA1F87EB5FF 208DD848
	static scrAny _0xE30CF56F1EFA5F43(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xE30CF56F1EFA5F43, p0, p1); } // E30CF56F1EFA5F43 F9B6426D
	static BOOL NETWORK_PLAYER_IS_CHEATER() { return NativeInvoke::Invoke<BOOL>(0x655B91F1495A9090); } // 655B91F1495A9090 A51DC214
	static scrAny _0x172F75B6EE2233BA() { return NativeInvoke::Invoke<scrAny>(0x172F75B6EE2233BA); } // 172F75B6EE2233BA 1720ABA6
	static BOOL _0x19D8DA0E5A68045A() { return NativeInvoke::Invoke<BOOL>(0x19D8DA0E5A68045A); } // 19D8DA0E5A68045A A19708E3
	static BOOL _0x46FB3ED415C7641C(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0x46FB3ED415C7641C, p0, p1, p2); } // 46FB3ED415C7641C F9A51B92
	static BOOL _0xEC5E3AF5289DCA81(scrAny *p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0xEC5E3AF5289DCA81, p0, p1, p2); } // EC5E3AF5289DCA81 4C2C6B6A
	static void _0xE66C690248F11150(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xE66C690248F11150, p0, p1); } // E66C690248F11150 4818ACD0
	static void NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(scrAny p0, BOOL p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x1CA59E306ECB80A5, p0, p1, p2); } // 1CA59E306ECB80A5 470810ED
	static BOOL _0xD1110739EEADB592(scrAny p0, BOOL p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0xD1110739EEADB592, p0, p1, p2); } // D1110739EEADB592
	static BOOL NETWORK_GET_THIS_SCRIPT_IS_NETWORK_SCRIPT() { return NativeInvoke::Invoke<BOOL>(0x2910669969E9535E); } // 2910669969E9535E D9BF6549
	static scrAny _0xA6C90FBC38E395EE() { return NativeInvoke::Invoke<scrAny>(0xA6C90FBC38E395EE); } // A6C90FBC38E395EE CCD8C02D
	static scrAny _0x18D0456E86604654() { return NativeInvoke::Invoke<scrAny>(0x18D0456E86604654); } // 18D0456E86604654 3E25A3C5
	static scrAny NETWORK_GET_SCRIPT_STATUS() { return NativeInvoke::Invoke<scrAny>(0x57D158647A6BFABF); } // 57D158647A6BFABF 2BE9235A
	static void NETWORK_REGISTER_HOST_BROADCAST_VARIABLES(scrAny *p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x3E9B2F01C50DF595, p0, p1); } // 3E9B2F01C50DF595 DAF3B0AE
	static void NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES(scrAny *p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x3364AA97340CA215, p0, p1); } // 3364AA97340CA215 BE3D32B4
	static void _0x64F62AFB081E260D() { NativeInvoke::Invoke<scrVoid>(0x64F62AFB081E260D); } // 64F62AFB081E260D A71A1D2A
	static BOOL _0x5D10B3795F3FC886() { return NativeInvoke::Invoke<BOOL>(0x5D10B3795F3FC886); } // 5D10B3795F3FC886 0B739F53
	static scrAny NETWORK_GET_PLAYER_INDEX(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x24FB80D107371267, p0); } // 24FB80D107371267 BE1C1506
	static scrAny NETWORK_GET_PARTICIPANT_INDEX(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x1B84DF6AF2A46938, p0); } // 1B84DF6AF2A46938 C4D91094
	static scrAny _0x6C0E2E0125610278(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x6C0E2E0125610278, p0); } // 6C0E2E0125610278 40DBF464
	static scrAny NETWORK_GET_NUM_CONNECTED_PLAYERS() { return NativeInvoke::Invoke<scrAny>(0xA4A79DD2D9600654); } // A4A79DD2D9600654 F7952E62
	static BOOL NETWORK_IS_PLAYER_CONNECTED(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x93DC1BE4E1ABE9D1, p0); } // 93DC1BE4E1ABE9D1 168EE2C2
	static scrAny _0xCF61D4B4702EE9EB() { return NativeInvoke::Invoke<scrAny>(0xCF61D4B4702EE9EB); } // CF61D4B4702EE9EB F4F13B06
	static BOOL NETWORK_IS_PARTICIPANT_ACTIVE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x6FF8FF40B6357D45, p0); } // 6FF8FF40B6357D45 4E2C348B
	static BOOL NETWORK_IS_PLAYER_ACTIVE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xB8DFD30D6973E135, p0); } // B8DFD30D6973E135 43657B17
	static BOOL NETWORK_IS_PLAYER_A_PARTICIPANT(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x3CA58F6CB7CBD784, p0); } // 3CA58F6CB7CBD784 B08B6992
	static BOOL NET_BUT() { return NativeInvoke::Invoke<BOOL>(0x83CD99A1E6061AB5); } // 83CD99A1E6061AB5 6970BA94
	static scrAny NETWORK_GET_HOST_OF_THIS_SCRIPT() { return NativeInvoke::Invoke<scrAny>(0xC7B4D79B01FA7A5C); } // C7B4D79B01FA7A5C 89EA7B54
	static scrAny NETWORK_GET_HOST_OF_SCRIPT(scrAny *p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0x1D6A14F1F9A736FC, p0, p1, p2); } // 1D6A14F1F9A736FC 9C95D0BB
	static void NETWORK_SET_MISSION_FINISHED() { NativeInvoke::Invoke<scrVoid>(0x3B3D11CD9FFCDFC9); } // 3B3D11CD9FFCDFC9 3083FAD7
	static BOOL NETWORK_IS_SCRIPT_ACTIVE(scrAny *p0, scrAny p1, BOOL p2, scrAny p3) { return NativeInvoke::Invoke<BOOL>(0x9D40DF90FAD26098, p0, p1, p2, p3); } // 9D40DF90FAD26098 4A65250C
	static scrAny _0x3658E8CD94FC121A(scrAny *p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0x3658E8CD94FC121A, p0, p1, p2); } // 3658E8CD94FC121A 8F7D9F46
	static scrAny _0x638A3A81733086DB() { return NativeInvoke::Invoke<scrAny>(0x638A3A81733086DB); } // 638A3A81733086DB DB8B5D71
	static BOOL _0x1AD5B71586B94820(scrAny p0, scrAny *p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0x1AD5B71586B94820, p0, p1, p2); } // 1AD5B71586B94820 CEA55F4C
	static void _0x2302C0264EA58D31() { NativeInvoke::Invoke<scrVoid>(0x2302C0264EA58D31); } // 2302C0264EA58D31 8DCFE77D
	static void _0x741A3D8380319A81() { NativeInvoke::Invoke<scrVoid>(0x741A3D8380319A81); } // 741A3D8380319A81 331D9A27
	static scrAny PARTICIPANT_ID() { return NativeInvoke::Invoke<scrAny>(0x90986E8876CE0A83); } // 90986E8876CE0A83 9C35A221
	static scrAny PARTICIPANT_ID_TO_INT() { return NativeInvoke::Invoke<scrAny>(0x57A3BDDAD8E5AA0A); } // 57A3BDDAD8E5AA0A 907498B0
	static scrAny NETWORK_GET_DESTROYER_OF_NETWORK_ID(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<scrAny>(0x7A1ADEEF01740A24, p0, p1); } // 7A1ADEEF01740A24 4FCA6436
	static BOOL _0x4CACA84440FA26F6(scrAny p0, scrAny p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0x4CACA84440FA26F6, p0, p1, p2); } // 4CACA84440FA26F6 28A45454
	static scrAny NETWORK_GET_ENTITY_KILLER_OF_PLAYER(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<scrAny>(0x42B2DAA6B596F5F8, p0, p1); } // 42B2DAA6B596F5F8 A7E7E04F
	static void NETWORK_RESURRECT_LOCAL_PLAYER(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { NativeInvoke::Invoke<scrVoid>(0xEA23C49EAA83ACFB, p0, p1, p2, p3, p4, p5); } // EA23C49EAA83ACFB F1F9D4B4
	static void NETWORK_SET_LOCAL_PLAYER_INVINCIBLE_TIME(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x2D95C7E2D7E07307, p0); } // 2D95C7E2D7E07307 FEA9B85C
	static BOOL NETWORK_IS_LOCAL_PLAYER_INVINCIBLE() { return NativeInvoke::Invoke<BOOL>(0x8A8694B48715B000); } // 8A8694B48715B000 8DE13B36
	static void _0x9DD368BF06983221(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x9DD368BF06983221, p0, p1); } // 9DD368BF06983221 8D27280E
	static void _0x524FF0AEFF9C3973(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x524FF0AEFF9C3973, p0); } // 524FF0AEFF9C3973 B72F086D
	static BOOL _0xB07D3185E11657A5(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xB07D3185E11657A5, p0); } // B07D3185E11657A5 EDA68956
	static scrAny NETWORK_GET_NETWORK_ID_FROM_ENTITY(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xA11700682F3AD45C, p0); } // A11700682F3AD45C 9E35DAB6
	static scrAny NETWORK_GET_ENTITY_FROM_NETWORK_ID(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xCE4E5D9B0A4FF560, p0); } // CE4E5D9B0A4FF560 5B912C3F
	static BOOL _0xC7827959479DCC78(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xC7827959479DCC78, p0); } // C7827959479DCC78 D7F934F4
	static BOOL NETWORK_GET_ENTITY_IS_LOCAL(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x0991549DE4D64762, p0); } // 0991549DE4D64762 813353ED
	static void _0x06FAACD625D80CAA(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x06FAACD625D80CAA, p0); } // 06FAACD625D80CAA 31A630A4
	static void _0x7368E683BB9038D6(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x7368E683BB9038D6, p0); } // 7368E683BB9038D6 5C645F64
	static BOOL NETWORK_DOES_NETWORK_ID_EXIST(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x38CE16C96BD11344, p0); } // 38CE16C96BD11344 B8D2C99E
	static BOOL NETWORK_DOES_ENTITY_EXIST_WITH_NETWORK_ID(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x18A47D074708FD68, p0); } // 18A47D074708FD68 1E2E3177
	static BOOL NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xA670B3662FAFFBD0, p0); } // A670B3662FAFFBD0 9262A60A
	static BOOL NETWORK_HAS_CONTROL_OF_NETWORK_ID(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x4D36070FE0215186, p0); } // 4D36070FE0215186 92E77D21
	static BOOL NETWORK_REQUEST_CONTROL_OF_ENTITY(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xB69317BF5E782347, p0); } // B69317BF5E782347 A05FEBD7
	static BOOL NETWORK_REQUEST_CONTROL_OF_DOOR(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x870DDFD5A4A796E4, p0); } // 870DDFD5A4A796E4 F60DAAF6
	static BOOL NETWORK_HAS_CONTROL_OF_ENTITY(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x01BF60A500E28887, p0); } // 01BF60A500E28887 005FD797
	static BOOL NETWORK_HAS_CONTROL_OF_PICKUP(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x5BC9495F0B3B6FA6, p0); } // 5BC9495F0B3B6FA6 F7784FC8
	static BOOL NETWORK_HAS_CONTROL_OF_DOOR(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xCB3C68ADB06195DF, p0); } // CB3C68ADB06195DF 136326EC
	static scrAny VEH_TO_NET(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xB4C94523F023419C, p0); } // B4C94523F023419C F17634EB
	static scrAny PED_TO_NET(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x0EDEC3C276198689, p0); } // 0EDEC3C276198689 86A0B759
	static scrAny OBJ_TO_NET(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x99BFDC94A603E541, p0); } // 99BFDC94A603E541 1E05F29F
	static scrAny NET_TO_VEH(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x367B936610BA360C, p0); } // 367B936610BA360C 7E02FAEA
	static scrAny NET_TO_PED(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xBDCD95FC216A8B3E, p0); } // BDCD95FC216A8B3E 87717DD4
	static scrAny NET_TO_OBJ(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xD8515F5FEA14CB3F, p0); } // D8515F5FEA14CB3F 27AA14D8
	static scrAny NET_TO_ENT(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xBFFEAB45A9A9094A, p0); } // BFFEAB45A9A9094A 5E149683
	static void NETWORK_GET_LOCAL_HANDLE(scrAny *p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xE86051786B66CD8E, p0, p1); } // E86051786B66CD8E 08023B16
	static void NETWORK_HANDLE_FROM_USER_ID(scrAny *p0, scrAny *p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xDCD51DD8F87AEC5C, p0, p1, p2); } // DCD51DD8F87AEC5C 74C2C1B7
	static void NETWORK_HANDLE_FROM_MEMBER_ID(scrAny *p0, scrAny *p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xA0FD21BED61E5C4C, p0, p1, p2); } // A0FD21BED61E5C4C 9BFC9FE2
	static void NETWORK_HANDLE_FROM_PLAYER(scrAny p0, scrAny *p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x388EB2B86C73B6B3, p0, p1, p2); } // 388EB2B86C73B6B3 D3498917
	static void NETWORK_HANDLE_FROM_FRIEND(scrAny p0, scrAny *p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xD45CB817D7E177D2, p0, p1, p2); } // D45CB817D7E177D2 3B0BB3A3
	static BOOL NETWORK_GAMERTAG_FROM_HANDLE_START(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x9F0C0A981D73FA56, p0); } // 9F0C0A981D73FA56 EBA00C2A
	static BOOL NETWORK_GAMERTAG_FROM_HANDLE_PENDING() { return NativeInvoke::Invoke<BOOL>(0xB071E27958EF4CF0); } // B071E27958EF4CF0 F000828E
	static BOOL NETWORK_GAMERTAG_FROM_HANDLE_SUCCEEDED() { return NativeInvoke::Invoke<BOOL>(0xFD00798DBA7523DD); } // FD00798DBA7523DD 89C2B5EA
	static scrAny NETWORK_GET_GAMERTAG_FROM_HANDLE(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0x426141162EBE5CDB, p0); } // 426141162EBE5CDB A18A1B26
	static scrAny _0xD66C9E72B3CC4982(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xD66C9E72B3CC4982, p0, p1); } // D66C9E72B3CC4982
	static scrAny _0x58CC181719256197(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0x58CC181719256197, p0, p1, p2); } // 58CC181719256197
	static BOOL NETWORK_ARE_HANDLES_THE_SAME(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x57DBA049E110F217, p0, p1); } // 57DBA049E110F217 45975AE3
	static BOOL NETWORK_IS_HANDLE_VALID(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x6F79B93B0A8E4133, p0, p1); } // 6F79B93B0A8E4133 F0996C6E
	static scrAny NETWORK_GET_PLAYER_FROM_GAMER_HANDLE(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0xCE5F689CF5A0A49D, p0); } // CE5F689CF5A0A49D 2E96EF1E
	static scrAny NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0xC82630132081BB6F, p0); } // C82630132081BB6F 62EF0A63
	static BOOL NETWORK_IS_GAMER_IN_MY_SESSION(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x0F10B05DDF8D16E9, p0); } // 0F10B05DDF8D16E9 59127716
	static void NETWORK_SHOW_PROFILE_UI(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x859ED1CEA343FCA8, p0); } // 859ED1CEA343FCA8 F00A20B0
	static scrAny NETWORK_PLAYER_GET_NAME(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x7718D2E2060837D2, p0); } // 7718D2E2060837D2 CE48F260
	static scrAny _0x4927FC39CD0869A0(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<scrAny>(0x4927FC39CD0869A0, p0, p1); } // 4927FC39CD0869A0 4EC0D983
	static BOOL NETWORK_PLAYER_IS_ROCKSTAR_DEV(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x544ABDDA3B409B6D, p0); } // 544ABDDA3B409B6D F6659045
	static BOOL _0x565E430DB3B05BEC(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x565E430DB3B05BEC, p0); } // 565E430DB3B05BEC D265B049
	static BOOL NETWORK_IS_INACTIVE_PROFILE(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x7E58745504313A2E, p0); } // 7E58745504313A2E 95481343
	static scrAny NETWORK_GET_MAX_FRIENDS() { return NativeInvoke::Invoke<scrAny>(0xAFEBB0D5D8F687D2); } // AFEBB0D5D8F687D2 048171BC
	static scrAny NETWORK_GET_FRIEND_COUNT() { return NativeInvoke::Invoke<scrAny>(0x203F1CFD823B27A4); } // 203F1CFD823B27A4 A396ACDE
	static scrAny NETWORK_GET_FRIEND_NAME(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xE11EBBB2A783FE8B, p0); } // E11EBBB2A783FE8B 97420B6D
	static scrAny _0x4164F227D052E293(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x4164F227D052E293, p0); } // 4164F227D052E293
	static BOOL NETWORK_IS_FRIEND_ONLINE(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x425A44533437B64D, p0); } // 425A44533437B64D E0A42430
	static BOOL _0x87EB7A3FFCB314DB(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x87EB7A3FFCB314DB, p0); } // 87EB7A3FFCB314DB
	static BOOL NETWORK_IS_FRIEND_IN_SAME_TITLE(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x2EA9A3BEDF3F17B8, p0); } // 2EA9A3BEDF3F17B8 C54365C2
	static BOOL NETWORK_IS_FRIEND_IN_MULTIPLAYER(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x57005C18827F3A28, p0); } // 57005C18827F3A28 400BDDD9
	static BOOL NETWORK_IS_FRIEND(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x1A24A179F9B31654, p0); } // 1A24A179F9B31654 2DA4C282
	static scrAny NETWORK_IS_PENDING_FRIEND(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x0BE73DA6984A6E33, p0); } // 0BE73DA6984A6E33 5C85FF81
	static BOOL NETWORK_IS_ADDING_FRIEND() { return NativeInvoke::Invoke<BOOL>(0x6EA101606F6E4D81); } // 6EA101606F6E4D81 BB7EC8C4
	static BOOL NETWORK_ADD_FRIEND(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x8E02D73914064223, p0, p1); } // 8E02D73914064223 20E5B3EE
	static scrAny CLEAR_PLAYER_BAILED_FROM_PLAYERICLE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xBAD8F2A42B844821, p0); } // BAD8F2A42B844821 94AE7172
	static BOOL GET_OBJ_ENTITY(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x82377B65E943F72D, p0); } // 82377B65E943F72D B802B671
	static BOOL NETWORK_CAN_SET_WAYPOINT() { return NativeInvoke::Invoke<BOOL>(0xC927EC229934AF60); } // C927EC229934AF60 009E68F3
	static scrAny _0xB309EBEA797E001F(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xB309EBEA797E001F, p0); } // B309EBEA797E001F 5C0AB2A9
	static BOOL _0x26F07DD83A5F7F98() { return NativeInvoke::Invoke<BOOL>(0x26F07DD83A5F7F98); } // 26F07DD83A5F7F98 9A176B6E
	static BOOL NETWORK_HAS_HEADSET() { return NativeInvoke::Invoke<BOOL>(0xE870F9F1F7B4F1FA); } // E870F9F1F7B4F1FA A7DC5657
	static void _0x7D395EA61622E116(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x7D395EA61622E116, p0); } // 7D395EA61622E116 5C05B7E1
	static BOOL NETWORK_GAMER_HAS_HEADSET(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xF2FD55CB574BCC55, p0); } // F2FD55CB574BCC55 D036DA4A
	static BOOL NETWORK_IS_GAMER_TALKING(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x71C33B22606CD88A, p0); } // 71C33B22606CD88A 99B58DBC
	static BOOL NETWORK_CAN_COMMUNICATE_WITH_GAMER(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xA150A4F065806B1F, p0); } // A150A4F065806B1F D05EB7F6
	static BOOL NETWORK_IS_GAMER_MUTED_BY_ME(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xCE60DE011B6C7978, p0); } // CE60DE011B6C7978 001B4046
	static BOOL _0xDF02A2C93F1F26DA(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xDF02A2C93F1F26DA, p0); } // DF02A2C93F1F26DA 7685B333
	static BOOL _0xE944C4F5AF1B5883(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xE944C4F5AF1B5883, p0); } // E944C4F5AF1B5883 3FDCC8D7
	static BOOL _0x15337C7C268A27B2(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x15337C7C268A27B2, p0); } // 15337C7C268A27B2 D19B312C
	static BOOL _0xB57A49545BA53CE7(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xB57A49545BA53CE7, p0); } // B57A49545BA53CE7
	static BOOL _0xCCA4318E1AB03F1F(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xCCA4318E1AB03F1F, p0); } // CCA4318E1AB03F1F
	static BOOL NETWORK_IS_PLAYER_TALKING(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x031E11F3D447647E, p0); } // 031E11F3D447647E DA9FD9DB
	static BOOL NETWORK_PLAYER_HAS_HEADSET(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x3FB99A8B08D18FD6, p0); } // 3FB99A8B08D18FD6 451FB6B6
	static BOOL NETWORK_IS_PLAYER_MUTED_BY_ME(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x8C71288AE68EDE39, p0); } // 8C71288AE68EDE39 7A21050E
	static BOOL NETWORK_AM_I_MUTED_BY_PLAYER(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x9D6981DFC91A8604, p0); } // 9D6981DFC91A8604 E128F2B0
	static BOOL NETWORK_IS_PLAYER_BLOCKED_BY_ME(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x57AF1F8E27483721, p0); } // 57AF1F8E27483721 AE4F4560
	static BOOL NETWORK_AM_I_BLOCKED_BY_PLAYER(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x87F395D957D4353D, p0); } // 87F395D957D4353D 953EF45E
	static float NETWORK_GET_PLAYER_LOUDNESS(scrAny p0) { return NativeInvoke::Invoke<float>(0x21A1684A25C2867F, p0); } // 21A1684A25C2867F F2F67014
	static void NETWORK_SET_TALKER_PROXIMITY(float p0) { NativeInvoke::Invoke<scrVoid>(0xCBF12D65F95AD686, p0); } // CBF12D65F95AD686 67555C66
	static float NETWORK_GET_TALKER_PROXIMITY() { return NativeInvoke::Invoke<float>(0x84F0F13120B4E098); } // 84F0F13120B4E098 19991ADD
	static void NETWORK_SET_VOICE_ACTIVE(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xBABEC9E69A91C57B, p0); } // BABEC9E69A91C57B 8011247F
	static void _0xCFEB46DCD7D8D5EB(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xCFEB46DCD7D8D5EB, p0); } // CFEB46DCD7D8D5EB 1A3EA6CD
	static void _0xAF66059A131AA269(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xAF66059A131AA269, p0); } // AF66059A131AA269 CAB21090
	static void NETWORK_SET_TEAM_ONLY_CHAT(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xD5B4883AC32F24C3, p0); } // D5B4883AC32F24C3 3813019A
	static void _0x6F697A66CE78674E(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x6F697A66CE78674E, p0, p1); } // 6F697A66CE78674E C8CC9E75
	static void NETWORK_SET_OVERRIDE_SPECTATOR_MODE(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x70DA3BF8DACD3210, p0); } // 70DA3BF8DACD3210 A0FD42D3
	static void _0x3C5C1E2C2FF814B1(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x3C5C1E2C2FF814B1, p0); } // 3C5C1E2C2FF814B1 C9DDA85B
	static void _0xF46A1E03E8755980(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xF46A1E03E8755980, p0); } // F46A1E03E8755980 D33AFF79
	static void _0x6A5D89D7769A40D8(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x6A5D89D7769A40D8, p0); } // 6A5D89D7769A40D8 4FFEFE43
	static void _0x3039AE5AD2C9C0C4(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x3039AE5AD2C9C0C4, p0, p1); } // 3039AE5AD2C9C0C4 74EE2D8B
	static void _0x57B192B4D4AD23D5(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x57B192B4D4AD23D5, p0); } // 57B192B4D4AD23D5 2F98B405
	static void _0xDDF73E2B1FEC5AB4(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xDDF73E2B1FEC5AB4, p0, p1); } // DDF73E2B1FEC5AB4 95F1C60D
	static void _0x0FF2862B61A58AF9(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x0FF2862B61A58AF9, p0); } // 0FF2862B61A58AF9 1BCD3DDF
	static void NETWORK_SET_VOICE_CHANNEL(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xEF6212C2EFEF1A23, p0); } // EF6212C2EFEF1A23 3974879F
	static void _0xE036A705F989E049() { NativeInvoke::Invoke<scrVoid>(0xE036A705F989E049); } // E036A705F989E049 9ECF722A
	static void IS_NETWORK_VEHICLE_BEEN_DAMAGED_BY_ANY_OBJECT(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xDBD2056652689917, p0, p1, p2); } // DBD2056652689917 F1E84832
	static void _0xF03755696450470C() { NativeInvoke::Invoke<scrVoid>(0xF03755696450470C); } // F03755696450470C 7F9B9052
	static void _0x5E3AA4CA2B6FB0EE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x5E3AA4CA2B6FB0EE, p0); } // 5E3AA4CA2B6FB0EE 7BBEA8CF
	static void _0xCA575C391FEA25CC(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xCA575C391FEA25CC, p0); } // CA575C391FEA25CC E797A4B6
	static void _0xADB57E5B663CCA8B(scrAny p0, scrAny *p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0xADB57E5B663CCA8B, p0, p1, p2); } // ADB57E5B663CCA8B 92268BB5
	static void SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME() { NativeInvoke::Invoke<scrVoid>(0x593850C16A36B692); } // 593850C16A36B692 92B7351C
	static void NETWORK_SET_FRIENDLY_FIRE_OPTION(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xF808475FA571D823, p0); } // F808475FA571D823 6BAF95FA
	static void NETWORK_SET_RICH_PRESENCE(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x1DCCACDCFC569362, p0, p1, p2, p3); } // 1DCCACDCFC569362 932A6CED
	static void _0x3E200C2BCF4164EB(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x3E200C2BCF4164EB, p0, p1); } // 3E200C2BCF4164EB 017E6777
	static scrAny _0x5ED0356A0CE3A34F() { return NativeInvoke::Invoke<scrAny>(0x5ED0356A0CE3A34F); } // 5ED0356A0CE3A34F E1F86C6A
	static void _0x9769F811D1785B03(scrAny p0, float p1, float p2, float p3, BOOL p4, BOOL p5) { NativeInvoke::Invoke<scrVoid>(0x9769F811D1785B03, p0, p1, p2, p3, p4, p5); } // 9769F811D1785B03 BE6A30C3
	static void _0xBF22E0F32968E967(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xBF22E0F32968E967, p0, p1); } // BF22E0F32968E967 22E03AD0
	static void _0x715135F4B82AC90D(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x715135F4B82AC90D, p0); } // 715135F4B82AC90D CEAE5AFC
	static BOOL _0x579CCED0265D4896() { return NativeInvoke::Invoke<BOOL>(0x579CCED0265D4896); } // 579CCED0265D4896 F5F4BD95
	static BOOL NETWORK_CLAN_PLAYER_IS_ACTIVE(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xB124B57F571D8F18, p0); } // B124B57F571D8F18 AB8319A3
	static BOOL NETWORK_CLAN_PLAYER_GET_DESC(scrAny *p0, scrAny p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0xEEE6EACBE8874FBA, p0, p1, p2); } // EEE6EACBE8874FBA 6EE4A282
	static scrAny _0x7543BB439F63792B(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x7543BB439F63792B, p0, p1); } // 7543BB439F63792B 54E79E9C
	static void _0xF45352426FF3A4F0(scrAny *p0, scrAny p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0xF45352426FF3A4F0, p0, p1, p2); } // F45352426FF3A4F0 F633805A
	static scrAny _0x1F471B79ACC90BEF() { return NativeInvoke::Invoke<scrAny>(0x1F471B79ACC90BEF); } // 1F471B79ACC90BEF 807B3450
	static BOOL _0x48DE78AF2C8885B8(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x48DE78AF2C8885B8, p0, p1); } // 48DE78AF2C8885B8 3369DD1F
	static BOOL NETWORK_CLAN_DOWNLOAD_MEMBERSHIP(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xA989044E70010ABE, p0); } // A989044E70010ABE 8E8CB520
	static BOOL NETWORK_CLAN_DOWNLOAD_MEMBERSHIP_PENDING(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x5B9E023DC6EBEDC0, p0); } // 5B9E023DC6EBEDC0 1FDB590F
	static BOOL _0xB3F64A6A91432477() { return NativeInvoke::Invoke<BOOL>(0xB3F64A6A91432477); } // B3F64A6A91432477 83ED8E08
	static BOOL _0xBB6E6FEE99D866B2(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0xBB6E6FEE99D866B2, p0); } // BB6E6FEE99D866B2 40202867
	static scrAny NETWORK_CLAN_GET_MEMBERSHIP_COUNT(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0xAAB11F6C4ADBC2C1, p0); } // AAB11F6C4ADBC2C1 25924010
	static BOOL NETWORK_CLAN_GET_MEMBERSHIP_VALID(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x48A59CF88D43DF0E, p0, p1); } // 48A59CF88D43DF0E 48914F6A
	static BOOL NETWORK_CLAN_GET_MEMBERSHIP(scrAny *p0, scrAny *p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0xC8BC2011F67B3411, p0, p1, p2); } // C8BC2011F67B3411 CDC4A590
	static scrAny NETWORK_CLAN_JOIN(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x9FAAA4F4FC71F87F, p0); } // 9FAAA4F4FC71F87F 79C916C5
	static BOOL _0x729E3401F0430686(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x729E3401F0430686, p0, p1); } // 729E3401F0430686 BDA90BAC
	static BOOL _0x2B51EDBEFC301339(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x2B51EDBEFC301339, p0, p1); } // 2B51EDBEFC301339 8E952B12
	static BOOL _0xC32EA7A2F6CA7557() { return NativeInvoke::Invoke<BOOL>(0xC32EA7A2F6CA7557); } // C32EA7A2F6CA7557 966C90FD
	static BOOL _0x5835D9CD92E83184(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x5835D9CD92E83184, p0, p1); } // 5835D9CD92E83184 BA672146
	static BOOL _0x13518FF1C6B28938(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x13518FF1C6B28938, p0); } // 13518FF1C6B28938 7963FA4D
	static BOOL _0xA134777FF7F33331(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0xA134777FF7F33331, p0, p1); } // A134777FF7F33331 88B13CDC
	static void _0x113E6E3E50E286B0(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x113E6E3E50E286B0, p0); } // 113E6E3E50E286B0 D6E3D5EA
	static scrAny _0x9AA46BADAD0E27ED() { return NativeInvoke::Invoke<scrAny>(0x9AA46BADAD0E27ED); } // 9AA46BADAD0E27ED E22445DA
	static void _0x042E4B70B93E6054() { NativeInvoke::Invoke<scrVoid>(0x042E4B70B93E6054); } // 042E4B70B93E6054 455DDF5C
	static BOOL _0xCE86D8191B762107(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xCE86D8191B762107, p0, p1); } // CE86D8191B762107 89DB0EC7
	static scrAny _0xB5074DB804E28CE7() { return NativeInvoke::Invoke<scrAny>(0xB5074DB804E28CE7); } // B5074DB804E28CE7 A4EF02F3
	static scrAny _0x5B4F04F19376A0BA() { return NativeInvoke::Invoke<scrAny>(0x5B4F04F19376A0BA); } // 5B4F04F19376A0BA 068A054E
	static BOOL _0xC080FF658B2E41DA(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0xC080FF658B2E41DA, p0, p1); } // C080FF658B2E41DA 9B8631EB
	static void SET_NETWORK_ID_CAN_MIGRATE(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x299EEB23175895FC, p0, p1); } // 299EEB23175895FC 47C8E5FF
	static void SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xE05E81A888FA63C8, p0, p1); } // E05E81A888FA63C8 68D486B2
	static void _0xA8A024587329F36A(scrAny p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xA8A024587329F36A, p0, p1, p2); } // A8A024587329F36A 4D15FDB1
	static void NETWORK_SET_ENTITY_CAN_BLEND(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xD830567D88A1E873, p0, p1); } // D830567D88A1E873 DE8C0DB8
	static void _0xF1CA12B18AEF5298(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xF1CA12B18AEF5298, p0, p1); } // F1CA12B18AEF5298 09CBC4B0
	static void SET_NETWORK_ID_VISIBLE_IN_CUTSCENE(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xA6928482543022B4, p0, p1, p2); } // A6928482543022B4 199E75EF
	static void _0x3FA36981311FA4FF(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x3FA36981311FA4FF, p0, p1); } // 3FA36981311FA4FF 00AE4E17
	static BOOL _0xA1607996431332DF(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xA1607996431332DF, p0); } // A1607996431332DF EA5176C0
	static void SET_LOCAL_PLAYER_VISIBLE_IN_CUTSCENE(BOOL p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xD1065D68947E7B6E, p0, p1); } // D1065D68947E7B6E 59F3479B
	static void SET_LOCAL_PLAYER_INVISIBLE_LOCALLY(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xE5F773C1A1D9D168, p0); } // E5F773C1A1D9D168 764F6222
	static void SET_LOCAL_PLAYER_VISIBLE_LOCALLY(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x7619364C82D3BF14, p0); } // 7619364C82D3BF14 324B56DB
	static void SET_PLAYER_INVISIBLE_LOCALLY(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x12B37D54667DB0B8, p0, p1); } // 12B37D54667DB0B8 18227209
	static void SET_PLAYER_VISIBLE_LOCALLY(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xFAA10F1FAFB11AF2, p0, p1); } // FAA10F1FAFB11AF2 BA2BB4B4
	static void FADE_OUT_LOCAL_PLAYER(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x416DBD4CD6ED8DD2, p0); } // 416DBD4CD6ED8DD2 8FA7CEBD
	static void NETWORK_FADE_OUT_ENTITY(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xDE564951F95E09ED, p0, p1, p2); } // DE564951F95E09ED 47EDEE56
	static void NETWORK_FADE_IN_ENTITY(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x1F4ED342ACEFE62D, p0, p1); } // 1F4ED342ACEFE62D 9B9FCD02
	static BOOL IS_PLAYER_IN_CUTSCENE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xE73092F4157CD126, p0); } // E73092F4157CD126 E0A619BD
	static void SET_ENTITY_VISIBLE_IN_CUTSCENE(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xE0031D3C8F36AB82, p0, p1, p2); } // E0031D3C8F36AB82 DBFB067B
	static void SET_ENTITY_LOCALLY_INVISIBLE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xE135A9FF3F5D05D8, p0); } // E135A9FF3F5D05D8 51ADCC5F
	static void SET_ENTITY_LOCALLY_VISIBLE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x241E289B5C059EDC, p0); } // 241E289B5C059EDC 235A57B3
	static BOOL IS_DAMAGE_TRACKER_ACTIVE_ON_NETWORK_ID(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x6E192E33AD436366, p0); } // 6E192E33AD436366 597063BA
	static void ACTIVATE_DAMAGE_TRACKER_ON_NETWORK_ID(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xD45B1FFCCD52FF19, p0, p1); } // D45B1FFCCD52FF19 95D07BA5
	static BOOL IS_SPHERE_VISIBLE_TO_ANOTHER_MACHINE(float p0, float p1, float p2, float p3) { return NativeInvoke::Invoke<BOOL>(0xD82CF8E64C8729D8, p0, p1, p2, p3); } // D82CF8E64C8729D8 23C5274E
	static BOOL IS_SPHERE_VISIBLE_TO_PLAYER(scrAny p0, float p1, float p2, float p3, float p4) { return NativeInvoke::Invoke<BOOL>(0xDC3A310219E5DA62, p0, p1, p2, p3, p4); } // DC3A310219E5DA62 E9FCFB32
	static void RESERVE_NETWORK_MISSION_OBJECTS(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x4E5C93BD0C32FBF8, p0); } // 4E5C93BD0C32FBF8 391DF4F3
	static void RESERVE_NETWORK_MISSION_PEDS(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xB60FEBA45333D36F, p0); } // B60FEBA45333D36F 54998C37
	static void RESERVE_NETWORK_MISSION_VEHICLES(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x76B02E21ED27A469, p0); } // 76B02E21ED27A469 5062875E
	static BOOL CAN_REGISTER_MISSION_OBJECTS(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x800DD4721A8B008B, p0); } // 800DD4721A8B008B 7F85DFDE
	static BOOL CAN_REGISTER_MISSION_PEDS(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xBCBF4FEF9FA5D781, p0); } // BCBF4FEF9FA5D781 CCAA5CE9
	static BOOL CAN_REGISTER_MISSION_VEHICLES(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x7277F1F2E085EE74, p0); } // 7277F1F2E085EE74 818B6830
	static BOOL CAN_REGISTER_MISSION_ENTITIES(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<BOOL>(0x69778E7564BADE6D, p0, p1, p2, p3); } // 69778E7564BADE6D 83794008
	static scrAny GET_NUM_RESERVED_MISSION_OBJECTS(BOOL p0) { return NativeInvoke::Invoke<scrAny>(0xAA81B5F10BC43AC2, p0); } // AA81B5F10BC43AC2 16A80CD6
	static scrAny GET_NUM_RESERVED_MISSION_PEDS(BOOL p0) { return NativeInvoke::Invoke<scrAny>(0x1F13D5AE5CB17E17, p0); } // 1F13D5AE5CB17E17 6C25975C
	static scrAny GET_NUM_RESERVED_MISSION_VEHICLES(BOOL p0) { return NativeInvoke::Invoke<scrAny>(0xCF3A965906452031, p0); } // CF3A965906452031 A9A308F3
	static scrAny _0x12B6281B6C6706C0(BOOL p0) { return NativeInvoke::Invoke<scrAny>(0x12B6281B6C6706C0, p0); } // 12B6281B6C6706C0 603FA104
	static scrAny _0xCB215C4B56A7FAE7(BOOL p0) { return NativeInvoke::Invoke<scrAny>(0xCB215C4B56A7FAE7, p0); } // CB215C4B56A7FAE7 D8FEC4F8
	static scrAny _0x0CD9AB83489430EA(BOOL p0) { return NativeInvoke::Invoke<scrAny>(0x0CD9AB83489430EA, p0); } // 0CD9AB83489430EA 20527695
	static scrAny _0xC7BE335216B5EC7C() { return NativeInvoke::Invoke<scrAny>(0xC7BE335216B5EC7C); } // C7BE335216B5EC7C 8687E285
	static scrAny _0x0C1F7D49C39D2289() { return NativeInvoke::Invoke<scrAny>(0x0C1F7D49C39D2289); } // 0C1F7D49C39D2289 744AC008
	static scrAny _0x0AFCE529F69B21FF() { return NativeInvoke::Invoke<scrAny>(0x0AFCE529F69B21FF); } // 0AFCE529F69B21FF C3A12135
	static scrAny _0xA72835064DD63E4C() { return NativeInvoke::Invoke<scrAny>(0xA72835064DD63E4C); } // A72835064DD63E4C 6A036061
	static scrAny GET_NETWORK_TIME() { return NativeInvoke::Invoke<scrAny>(0x7A5487FE9FAA6B48); } // 7A5487FE9FAA6B48 998103C2
	static scrAny _0x89023FBBF9200E9F() { return NativeInvoke::Invoke<scrAny>(0x89023FBBF9200E9F); } // 89023FBBF9200E9F 98AA48E5
	static BOOL _0x46718ACEEDEAFC84() { return NativeInvoke::Invoke<BOOL>(0x46718ACEEDEAFC84); } // 46718ACEEDEAFC84 4538C4A2
	static scrAny GET_TIME_OFFSET(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x017008CCDAD48503, p0, p1); } // 017008CCDAD48503 2E079AE6
	static scrAny _0xCB2CF5148012C8D0(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xCB2CF5148012C8D0, p0, p1); } // CB2CF5148012C8D0 50EF8FC6
	static scrAny _0xDE350F8651E4346C(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xDE350F8651E4346C, p0, p1); } // DE350F8651E4346C BBB6DF61
	static scrAny _0xF5BC95857BD6D512(BOOL p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xF5BC95857BD6D512, p0, p1); } // F5BC95857BD6D512 8B4D1C06
	static scrAny GET_TIME_DIFFERENCE(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xA2C6FC031D46FFF0, p0, p1); } // A2C6FC031D46FFF0 5666A837
	static scrAny _0x9E23B1777A927DAD(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x9E23B1777A927DAD, p0); } // 9E23B1777A927DAD 8218944E
	static scrAny _0x9A73240B49945C76() { return NativeInvoke::Invoke<scrAny>(0x9A73240B49945C76); } // 9A73240B49945C76 F2FDF2E0
	static void _0xAC97AF97FA68E5D5(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xAC97AF97FA68E5D5, p0, p1); } // AC97AF97FA68E5D5 BB7CCE49
	static void NETWORK_SET_IN_SPECTATOR_MODE(BOOL p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x423DE3854BB50894, p0, p1); } // 423DE3854BB50894 5C4C8458
	static void _0x419594E137637120(BOOL p0, scrAny p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x419594E137637120, p0, p1, p2); } // 419594E137637120 54058F5F
	static void _0xFC18DB55AE19E046(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xFC18DB55AE19E046, p0); } // FC18DB55AE19E046 A7E36020
	static void _0x5C707A667DF8B9FA(BOOL p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x5C707A667DF8B9FA, p0, p1); } // 5C707A667DF8B9FA 64235620
	static BOOL NETWORK_IS_IN_SPECTATOR_MODE() { return NativeInvoke::Invoke<BOOL>(0x048746E388762E11); } // 048746E388762E11 3EAD9DB8
	static void NETWORK_SET_IN_MP_CUTSCENE(BOOL p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x9CA5DE655269FEC4, p0, p1); } // 9CA5DE655269FEC4 8434CB43
	static scrAny NETWORK_IS_IN_MP_CUTSCENE() { return NativeInvoke::Invoke<scrAny>(0x6CC27C9FA2040220); } // 6CC27C9FA2040220 4BB33316
	static BOOL NETWORK_IS_PLAYER_IN_MP_CUTSCENE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x63F9EE203C3619F2, p0); } // 63F9EE203C3619F2 56F961E4
	static void SET_NETWORK_VEHICLE_RESPOT_TIMER(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xEC51713AB6EC36E8, p0, p1); } // EC51713AB6EC36E8 2C30912D
	static void _0x6274C4712850841E(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x6274C4712850841E, p0, p1); } // 6274C4712850841E EA235081
	static void USE_PLAYER_COLOUR_INSTEAD_OF_TEAM_COLOUR(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x5FFE9B4144F9712F, p0); } // 5FFE9B4144F9712F 4DD46DAE
	static BOOL _0x21D04D7BC538C146(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x21D04D7BC538C146, p0); } // 21D04D7BC538C146
	static void _0x77758139EC9B66C7(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x77758139EC9B66C7, p0); } // 77758139EC9B66C7
	static scrAny NETWORK_CREATE_SYNCHRONISED_SCENE(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5, scrAny p6, scrAny p7, scrAny p8, scrAny p9) { return NativeInvoke::Invoke<scrAny>(0x7CD6BC4C2BBDD526, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 7CD6BC4C2BBDD526 B06FE3FE
	static void NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(scrAny p0, scrAny p1, scrAny *p2, scrAny *p3, float p4, float p5, scrAny p6, scrAny p7, float p8, scrAny p9) { NativeInvoke::Invoke<scrVoid>(0x742A637471BCECD9, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // 742A637471BCECD9 B386713E
	static void NETWORK_ADD_ENTITY_TO_SYNCHRONISED_SCENE(scrAny p0, scrAny p1, scrAny *p2, scrAny *p3, float p4, float p5, scrAny p6) { NativeInvoke::Invoke<scrVoid>(0xF2404D68CBC855FA, p0, p1, p2, p3, p4, p5, p6); } // F2404D68CBC855FA 10DD636C
	static void _0xCF8BD3B0BD6D42D7(scrAny p0, scrAny *p1, scrAny *p2) { NativeInvoke::Invoke<scrVoid>(0xCF8BD3B0BD6D42D7, p0, p1, p2); } // CF8BD3B0BD6D42D7 BFFE8B5C
	static void NETWORK_ATTACH_SYNCHRONISED_SCENE_TO_ENTITY(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x478DCBD2A98B705A, p0, p1, p2); } // 478DCBD2A98B705A 3FE5B222
	static void NETWORK_START_SYNCHRONISED_SCENE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x9A1B3FCDB36C8697, p0); } // 9A1B3FCDB36C8697 A9DFDC40
	static void NETWORK_STOP_SYNCHRONISED_SCENE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xC254481A4574CB2F, p0); } // C254481A4574CB2F 97B1CDF6
	static scrAny _0x02C40BF885C567B6(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x02C40BF885C567B6, p0); } // 02C40BF885C567B6 16AED87B
	static scrAny _0xFB1F9381E80FA13F(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xFB1F9381E80FA13F, p0, p1); } // FB1F9381E80FA13F 0679CE71
	static BOOL _0x5A6FFA2433E2F14C(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, scrAny p8) { return NativeInvoke::Invoke<BOOL>(0x5A6FFA2433E2F14C, p0, p1, p2, p3, p4, p5, p6, p7, p8); } // 5A6FFA2433E2F14C C62E77B3
	static BOOL _0x4BA92A18502BCA61(scrAny p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, scrAny p11) { return NativeInvoke::Invoke<BOOL>(0x4BA92A18502BCA61, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); } // 4BA92A18502BCA61 74D6B13C
	static scrAny _0x3C891A251567DFCE(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0x3C891A251567DFCE, p0); } // 3C891A251567DFCE 90700C7D
	static void _0xFB8F2A6F3DF08CBE() { NativeInvoke::Invoke<scrVoid>(0xFB8F2A6F3DF08CBE); } // FB8F2A6F3DF08CBE 44BFB619
	static void NETWORK_GET_RESPAWN_RESULT(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x371EA43692861CF1, p0, p1, p2); } // 371EA43692861CF1 DDFE9FBC
	static scrAny _0x6C34F1208B8923FD(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x6C34F1208B8923FD, p0); } // 6C34F1208B8923FD 03287FD2
	static void _0x17E0198B3882C2CB() { NativeInvoke::Invoke<scrVoid>(0x17E0198B3882C2CB); } // 17E0198B3882C2CB 408A9436
	static void _0xFB680D403909DC70(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xFB680D403909DC70, p0, p1); } // FB680D403909DC70 FFB2ADA1
	static void NETWORK_END_TUTORIAL_SESSION() { NativeInvoke::Invoke<scrVoid>(0xD0AFAFF5A51D72F7); } // D0AFAFF5A51D72F7 BA57E53E
	static BOOL NETWORK_IS_IN_TUTORIAL_SESSION() { return NativeInvoke::Invoke<BOOL>(0xADA24309FE08DACF); } // ADA24309FE08DACF 34DD7B28
	static BOOL _0xB37E4E6A2388CA7B() { return NativeInvoke::Invoke<BOOL>(0xB37E4E6A2388CA7B); } // B37E4E6A2388CA7B 755A2B3E
	static BOOL _0x35F0B98A8387274D() { return NativeInvoke::Invoke<BOOL>(0x35F0B98A8387274D); } // 35F0B98A8387274D A003C40B
	static scrAny _0x3B39236746714134(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x3B39236746714134, p0); } // 3B39236746714134 5E1020CC
	static BOOL _0x9DE986FC9A87C474(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x9DE986FC9A87C474, p0, p1); } // 9DE986FC9A87C474 E66A0B40
	static void _0xBBDF066252829606(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0xBBDF066252829606, p0, p1); } // BBDF066252829606 72052DB3
	static BOOL _0x919B3C98ED8292F9(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x919B3C98ED8292F9, p0); } // 919B3C98ED8292F9 B0313590
	static void NETWORK_OVERRIDE_CLOCK_TIME(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0xE679E3E06E363892, p0, p1, p2); } // E679E3E06E363892 C077BCD6
	static void _0xD972DF67326F966E() { NativeInvoke::Invoke<scrVoid>(0xD972DF67326F966E); } // D972DF67326F966E C4AEAF49
	static BOOL _0xD7C95D322FF57522() { return NativeInvoke::Invoke<BOOL>(0xD7C95D322FF57522); } // D7C95D322FF57522 2465296D
	static scrAny NETWORK_ADD_ENTITY_AREA(float p0, float p1, float p2, float p3, float p4, float p5) { return NativeInvoke::Invoke<scrAny>(0x494C8FB299290269, p0, p1, p2, p3, p4, p5); } // 494C8FB299290269 51030E5B
	static scrAny _0x376C6375BA60293A(float p0, float p1, float p2, float p3, float p4, float p5, float p6) { return NativeInvoke::Invoke<scrAny>(0x376C6375BA60293A, p0, p1, p2, p3, p4, p5, p6); } // 376C6375BA60293A
	static scrAny _0x25B99872D588A101(float p0, float p1, float p2, float p3, float p4, float p5) { return NativeInvoke::Invoke<scrAny>(0x25B99872D588A101, p0, p1, p2, p3, p4, p5); } // 25B99872D588A101 4C2C2B12
	static BOOL NETWORK_REMOVE_ENTITY_AREA(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x93CF869BAA0C4874, p0); } // 93CF869BAA0C4874 EAB97F25
	static BOOL _0xE64A3CA08DFA37A9(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xE64A3CA08DFA37A9, p0); } // E64A3CA08DFA37A9 69956127
	static BOOL _0x4DF7CFFF471A7FB1(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x4DF7CFFF471A7FB1, p0); } // 4DF7CFFF471A7FB1 CB1CD6D3
	static BOOL _0x4A2D4E8BF4265B0F(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x4A2D4E8BF4265B0F, p0); } // 4A2D4E8BF4265B0F C6D53AA0
	static void _0x2B1813ABA29016C5(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x2B1813ABA29016C5, p0, p1); } // 2B1813ABA29016C5 155465EE
	static BOOL _0x924426BFFD82E915() { return NativeInvoke::Invoke<BOOL>(0x924426BFFD82E915); } // 924426BFFD82E915 29532731
	static void _0x42FB3B532D526E6C() { NativeInvoke::Invoke<scrVoid>(0x42FB3B532D526E6C); } // 42FB3B532D526E6C D760CAD5
	static scrAny _0x10BD227A753B0D84() { return NativeInvoke::Invoke<scrAny>(0x10BD227A753B0D84); } // 10BD227A753B0D84 231CFD12
	static BOOL NETWORK_DOES_TUNABLE_EXIST(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x85E5F8B9B898B20A, p0, p1); } // 85E5F8B9B898B20A 9FCE9C9A
	static BOOL _0x8BE1146DFD5D4468(scrAny *p0, scrAny *p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0x8BE1146DFD5D4468, p0, p1, p2); } // 8BE1146DFD5D4468 E4B3726A
	static BOOL _0xE5608CA7BC163A5F(scrAny *p0, scrAny *p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0xE5608CA7BC163A5F, p0, p1, p2); } // E5608CA7BC163A5F 41E8912A
	static BOOL _0xAA6A47A573ABB75A(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0xAA6A47A573ABB75A, p0, p1); } // AA6A47A573ABB75A 8A04E1FE
	static scrAny _0x187382F8A3E0A6C3(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x187382F8A3E0A6C3, p0); } // 187382F8A3E0A6C3 A78571CA
	static scrAny _0x7DB53B37A2F211A0() { return NativeInvoke::Invoke<scrAny>(0x7DB53B37A2F211A0); } // 7DB53B37A2F211A0 053BB329
	static void NETWORK_RESET_BODY_TRACKER() { NativeInvoke::Invoke<scrVoid>(0x72433699B4E6DD64); } // 72433699B4E6DD64 3914463F
	static scrAny _0xD38C4A6D047C019D() { return NativeInvoke::Invoke<scrAny>(0xD38C4A6D047C019D); } // D38C4A6D047C019D 17CBC608
	static BOOL _0x2E0BF682CC778D49(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x2E0BF682CC778D49, p0); } // 2E0BF682CC778D49 BFAA349B
	static BOOL _0x0EDE326D47CD0F3E(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x0EDE326D47CD0F3E, p0, p1); } // 0EDE326D47CD0F3E BEB7281A
	static scrAny NETWORK_EXPLODE_VEHICLE(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0x301A42153C9AD707, p0, p1, p2, p3); } // 301A42153C9AD707 0E1B38AE
	static void _0xCD71A4ECAB22709E(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xCD71A4ECAB22709E, p0); } // CD71A4ECAB22709E BC54371B
	static void _0xA7E30DE9272B6D49(scrAny p0, float p1, float p2, float p3, float p4) { NativeInvoke::Invoke<scrVoid>(0xA7E30DE9272B6D49, p0, p1, p2, p3, p4); } // A7E30DE9272B6D49 644141C5
	static void NETWORK_SET_PROPERTY_ID(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x1775961C2FBBCB5C, p0); } // 1775961C2FBBCB5C 5A74E873
	static void _0xC2B82527CA77053E() { NativeInvoke::Invoke<scrVoid>(0xC2B82527CA77053E); } // C2B82527CA77053E 38BC35C8
	static void _0x367EF5E2F439B4C6(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x367EF5E2F439B4C6, p0); } // 367EF5E2F439B4C6 53C9563C
	static void _0x94538037EE44F5CF(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x94538037EE44F5CF, p0); } // 94538037EE44F5CF 6B97075B
	static scrAny _0xF2EAC213D5EA0623() { return NativeInvoke::Invoke<scrAny>(0xF2EAC213D5EA0623); } // F2EAC213D5EA0623 965EA007
	static scrAny _0xEA14EEF5B7CD2C30() { return NativeInvoke::Invoke<scrAny>(0xEA14EEF5B7CD2C30); } // EA14EEF5B7CD2C30 EEFC8A55
	static void _0xB606E6CC59664972(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xB606E6CC59664972, p0); } // B606E6CC59664972 866D1B67
	static BOOL _0x1D4DC17C38FEAFF0() { return NativeInvoke::Invoke<BOOL>(0x1D4DC17C38FEAFF0); } // 1D4DC17C38FEAFF0 ED4A272F
	static scrAny _0x662635855957C411(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x662635855957C411, p0); } // 662635855957C411 4ACF110C
	static scrAny _0xB4271092CA7EDF48(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xB4271092CA7EDF48, p0); } // B4271092CA7EDF48 1AA3A0D5
	static scrAny _0xCA94551B50B4932C(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xCA94551B50B4932C, p0); } // CA94551B50B4932C 37877757
	static scrAny _0x2A7776C709904AB0(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x2A7776C709904AB0, p0); } // 2A7776C709904AB0 1CF89DA5
	static scrAny _0x6F44CBF56D79FAC0(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x6F44CBF56D79FAC0, p0, p1); } // 6F44CBF56D79FAC0 16E53875
	static void _0x58C21165F6545892(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x58C21165F6545892, p0, p1); } // 58C21165F6545892 365C50EE
	static BOOL _0x2EAC52B4019E2782() { return NativeInvoke::Invoke<BOOL>(0x2EAC52B4019E2782); } // 2EAC52B4019E2782 25E2DBA9
	static void SET_STORE_ENABLED(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x9641A9FF718E9C5E, p0); } // 9641A9FF718E9C5E C1F6443B
	static BOOL _0xA2F952104FC6DD4B(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xA2F952104FC6DD4B, p0); } // A2F952104FC6DD4B 1FDC75DC
	static void _0x72D0706CD6CCDB58() { NativeInvoke::Invoke<scrVoid>(0x72D0706CD6CCDB58); } // 72D0706CD6CCDB58 CA7A0A49
	static scrAny _0x722F5D28B61C5EA8(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x722F5D28B61C5EA8, p0); } // 722F5D28B61C5EA8 44A58B0A
	static BOOL _0x883D79C4071E18B3() { return NativeInvoke::Invoke<BOOL>(0x883D79C4071E18B3); } // 883D79C4071E18B3 D32FA11F
	static void _0x265635150FB0D82E() { NativeInvoke::Invoke<scrVoid>(0x265635150FB0D82E); } // 265635150FB0D82E A7FA70AE
	static void _0x444C4525ECE0A4B9() { NativeInvoke::Invoke<scrVoid>(0x444C4525ECE0A4B9); } // 444C4525ECE0A4B9 CC7DCE24
	static BOOL _0x59328EB08C5CEB2B() { return NativeInvoke::Invoke<BOOL>(0x59328EB08C5CEB2B); } // 59328EB08C5CEB2B 70F6D3AD
	static scrAny _0xC64DED7EF0D2FE37(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0xC64DED7EF0D2FE37, p0); } // C64DED7EF0D2FE37 2B7B57B3
	static BOOL _0x4C61B39930D045DA(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x4C61B39930D045DA, p0); } // 4C61B39930D045DA BAF52DD8
	static BOOL _0x3A3D5568AF297CD5(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x3A3D5568AF297CD5, p0); } // 3A3D5568AF297CD5 9B9AFFF1
	static void _0x4F18196C8D38768D() { NativeInvoke::Invoke<scrVoid>(0x4F18196C8D38768D); } // 4F18196C8D38768D C38E9DB0
	static BOOL _0xC7ABAC5DE675EE3B() { return NativeInvoke::Invoke<BOOL>(0xC7ABAC5DE675EE3B); } // C7ABAC5DE675EE3B 32A4EB22
	static scrAny _0x0B0CC10720653F3B() { return NativeInvoke::Invoke<scrAny>(0x0B0CC10720653F3B); } // 0B0CC10720653F3B 9262744C
	static scrAny _0x8B0C2964BA471961() { return NativeInvoke::Invoke<scrAny>(0x8B0C2964BA471961); } // 8B0C2964BA471961
	static scrAny _0x88B588B41FF7868E() { return NativeInvoke::Invoke<scrAny>(0x88B588B41FF7868E); } // 88B588B41FF7868E
	static scrAny _0x67FC09BC554A75E5() { return NativeInvoke::Invoke<scrAny>(0x67FC09BC554A75E5); } // 67FC09BC554A75E5
	static void _0x966DD84FB6A46017() { NativeInvoke::Invoke<scrVoid>(0x966DD84FB6A46017); } // 966DD84FB6A46017
	static BOOL _0x152D90E4C1B4738A(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x152D90E4C1B4738A, p0, p1); } // 152D90E4C1B4738A 08243B79
	static BOOL _0x9FEDF86898F100E9() { return NativeInvoke::Invoke<BOOL>(0x9FEDF86898F100E9); } // 9FEDF86898F100E9 798D6C27
	static BOOL _0x5E24341A7F92A74B() { return NativeInvoke::Invoke<BOOL>(0x5E24341A7F92A74B); } // 5E24341A7F92A74B E69E8D0D
	static BOOL _0x24E4E51FC16305F9() { return NativeInvoke::Invoke<BOOL>(0x24E4E51FC16305F9); } // 24E4E51FC16305F9 742075FE
	static scrAny _0xFBC5E768C7A77A6A() { return NativeInvoke::Invoke<scrAny>(0xFBC5E768C7A77A6A); } // FBC5E768C7A77A6A CE569932
	static scrAny _0xC55A0B40FFB1ED23() { return NativeInvoke::Invoke<scrAny>(0xC55A0B40FFB1ED23); } // C55A0B40FFB1ED23 82146BE9
	static void _0x17440AA15D1D3739() { NativeInvoke::Invoke<scrVoid>(0x17440AA15D1D3739); } // 17440AA15D1D3739 133FF2D5
	static BOOL _0x9BF438815F5D96EA(scrAny p0, scrAny p1, scrAny *p2, scrAny p3, scrAny p4, scrAny p5) { return NativeInvoke::Invoke<BOOL>(0x9BF438815F5D96EA, p0, p1, p2, p3, p4, p5); } // 9BF438815F5D96EA CBA7242F
	static BOOL _0x692D58DF40657E8C(scrAny p0, scrAny p1, scrAny p2, scrAny *p3, scrAny p4, BOOL p5) { return NativeInvoke::Invoke<BOOL>(0x692D58DF40657E8C, p0, p1, p2, p3, p4, p5); } // 692D58DF40657E8C
	static BOOL _0x158EC424F35EC469(scrAny *p0, BOOL p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0x158EC424F35EC469, p0, p1, p2); } // 158EC424F35EC469 DED82A6E
	static BOOL _0x6D4CB481FAC835E8(scrAny p0, scrAny p1, scrAny *p2, scrAny p3) { return NativeInvoke::Invoke<BOOL>(0x6D4CB481FAC835E8, p0, p1, p2, p3); } // 6D4CB481FAC835E8 40CF0783
	static BOOL _0xD5A4B59980401588(scrAny p0, scrAny p1, scrAny *p2, scrAny *p3) { return NativeInvoke::Invoke<BOOL>(0xD5A4B59980401588, p0, p1, p2, p3); } // D5A4B59980401588 4609D596
	static BOOL _0x3195F8DD0D531052(scrAny p0, scrAny p1, scrAny *p2, scrAny *p3) { return NativeInvoke::Invoke<BOOL>(0x3195F8DD0D531052, p0, p1, p2, p3); } // 3195F8DD0D531052 4C2C0D1F
	static BOOL _0xF9E1CCAE8BA4C281(scrAny p0, scrAny p1, scrAny *p2, scrAny *p3) { return NativeInvoke::Invoke<BOOL>(0xF9E1CCAE8BA4C281, p0, p1, p2, p3); } // F9E1CCAE8BA4C281 9EFBD5D1
	static BOOL _0x9F6E2821885CAEE2(scrAny p0, scrAny p1, scrAny p2, scrAny *p3, scrAny *p4) { return NativeInvoke::Invoke<BOOL>(0x9F6E2821885CAEE2, p0, p1, p2, p3, p4); } // 9F6E2821885CAEE2 A6D8B798
	static BOOL _0x678BB03C1A3BD51E(scrAny p0, scrAny p1, scrAny p2, scrAny *p3, scrAny *p4) { return NativeInvoke::Invoke<BOOL>(0x678BB03C1A3BD51E, p0, p1, p2, p3, p4); } // 678BB03C1A3BD51E 67E74842
	static BOOL SET_BALANCE_ADD_MACHINE(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x815E5E3073DA1D67, p0, p1); } // 815E5E3073DA1D67 E123C7AC
	static BOOL SET_BALANCE_ADD_MACHINES(scrAny *p0, scrAny p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0xB8322EEB38BE7C26, p0, p1, p2); } // B8322EEB38BE7C26 22C33603
	static BOOL _0xA7862BC5ED1DFD7E(scrAny p0, scrAny p1, scrAny *p2, scrAny *p3) { return NativeInvoke::Invoke<BOOL>(0xA7862BC5ED1DFD7E, p0, p1, p2, p3); } // A7862BC5ED1DFD7E 37F5BD93
	static BOOL _0x97A770BEEF227E2B(scrAny p0, scrAny p1, scrAny *p2, scrAny *p3) { return NativeInvoke::Invoke<BOOL>(0x97A770BEEF227E2B, p0, p1, p2, p3); } // 97A770BEEF227E2B 1CFB3F51
	static BOOL _0x5324A0E3E4CE3570(scrAny p0, scrAny p1, scrAny *p2, scrAny *p3) { return NativeInvoke::Invoke<BOOL>(0x5324A0E3E4CE3570, p0, p1, p2, p3); } // 5324A0E3E4CE3570 87D1E6BD
	static void _0xE9B99B6853181409() { NativeInvoke::Invoke<scrVoid>(0xE9B99B6853181409); } // E9B99B6853181409 021D5A94
	static BOOL _0xD53ACDBEF24A46E8() { return NativeInvoke::Invoke<BOOL>(0xD53ACDBEF24A46E8); } // D53ACDBEF24A46E8 4908A514
	static BOOL _0x02ADA21EA2F6918F() { return NativeInvoke::Invoke<BOOL>(0x02ADA21EA2F6918F); } // 02ADA21EA2F6918F 50296140
	static BOOL _0x941E5306BCD7C2C7() { return NativeInvoke::Invoke<BOOL>(0x941E5306BCD7C2C7); } // 941E5306BCD7C2C7 3970B0DA
	static BOOL _0xC87E740D9F3872CC() { return NativeInvoke::Invoke<BOOL>(0xC87E740D9F3872CC); } // C87E740D9F3872CC C1487110
	static scrAny _0xEDF7F927136C224B() { return NativeInvoke::Invoke<scrAny>(0xEDF7F927136C224B); } // EDF7F927136C224B CC2356E3
	static scrAny _0xE0A6138401BCB837() { return NativeInvoke::Invoke<scrAny>(0xE0A6138401BCB837); } // E0A6138401BCB837 2DE69817
	static scrAny _0x769951E2455E2EB5() { return NativeInvoke::Invoke<scrAny>(0x769951E2455E2EB5); } // 769951E2455E2EB5 81BD8D3B
	static scrAny _0x3A17A27D75C74887() { return NativeInvoke::Invoke<scrAny>(0x3A17A27D75C74887); } // 3A17A27D75C74887 8E1D8F78
	static void _0xBA96394A0EECFA65() { NativeInvoke::Invoke<scrVoid>(0xBA96394A0EECFA65); } // BA96394A0EECFA65 0D35DD93
	static scrAny _0xCD67AD041A394C9C(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xCD67AD041A394C9C, p0); } // CD67AD041A394C9C 8F3137E6
	static BOOL _0x584770794D758C18(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x584770794D758C18, p0, p1); } // 584770794D758C18
	static BOOL _0x8C8D2739BA44AF0F(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x8C8D2739BA44AF0F, p0); } // 8C8D2739BA44AF0F
	static scrAny _0x703F12425ECA8BF5(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x703F12425ECA8BF5, p0); } // 703F12425ECA8BF5 B9137BA7
	static BOOL _0xAEAB987727C5A8A4(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xAEAB987727C5A8A4, p0); } // AEAB987727C5A8A4 9FEEAA9C
	static scrAny _0xA7BAB11E7C9C6C5A(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xA7BAB11E7C9C6C5A, p0); } // A7BAB11E7C9C6C5A 5E8A7559
	static scrAny _0x55AA95F481D694D2(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x55AA95F481D694D2, p0); } // 55AA95F481D694D2 331AEABF
	static scrAny _0xC0173D6BFF4E0348(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xC0173D6BFF4E0348, p0); } // C0173D6BFF4E0348 0E5E8E5C
	static scrAny _0xBF09786A7FCAB582(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xBF09786A7FCAB582, p0); } // BF09786A7FCAB582 A5A0C695
	static scrAny _0x7CF0448787B23758(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x7CF0448787B23758, p0); } // 7CF0448787B23758 91534C6E
	static scrAny _0xBAF6BABF9E7CCC13(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xBAF6BABF9E7CCC13, p0, p1); } // BAF6BABF9E7CCC13 744A9EA5
	static void _0xCFD115B373C0DF63(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xCFD115B373C0DF63, p0, p1); } // CFD115B373C0DF63 A19A238D
	static scrAny _0x37025B27D9B658B1(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x37025B27D9B658B1, p0, p1); } // 37025B27D9B658B1 FF7D44E6
	static BOOL _0x1D610EB0FEA716D9(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x1D610EB0FEA716D9, p0); } // 1D610EB0FEA716D9
	static BOOL _0x7FCC39C46C3C03BD(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x7FCC39C46C3C03BD, p0); } // 7FCC39C46C3C03BD
	static scrAny _0x32DD916F3F7C9672(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x32DD916F3F7C9672, p0); } // 32DD916F3F7C9672 A2C5BD9D
	static BOOL _0x3054F114121C21EA(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x3054F114121C21EA, p0); } // 3054F114121C21EA A850DDE1
	static BOOL _0xA9240A96C74CCA13(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xA9240A96C74CCA13, p0); } // A9240A96C74CCA13 8F6754AE
	static scrAny _0x1ACCFBA3D8DAB2EE(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x1ACCFBA3D8DAB2EE, p0, p1); } // 1ACCFBA3D8DAB2EE 1E34953F
	static scrAny _0x759299C5BB31D2A9(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x759299C5BB31D2A9, p0, p1); } // 759299C5BB31D2A9 771FE190
	static scrAny _0x87E5C46C187FE0AE(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x87E5C46C187FE0AE, p0, p1); } // 87E5C46C187FE0AE 3276D9D3
	static scrAny _0x4E548C0D7AE39FF9(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x4E548C0D7AE39FF9, p0, p1); } // 4E548C0D7AE39FF9 41A0FB02
	static BOOL _0x70EA8DA57840F9BE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x70EA8DA57840F9BE, p0); } // 70EA8DA57840F9BE 11DC0F27
	static BOOL _0x993CBE59D350D225(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x993CBE59D350D225, p0); } // 993CBE59D350D225 0DEB3F5A
	static scrAny _0x171DF6A0C07FB3DC(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x171DF6A0C07FB3DC, p0, p1); } // 171DF6A0C07FB3DC 84315226
	static scrAny _0x7FD2990AF016795E(scrAny *p0, scrAny *p1, scrAny p2, scrAny p3, scrAny p4) { return NativeInvoke::Invoke<scrAny>(0x7FD2990AF016795E, p0, p1, p2, p3, p4); } // 7FD2990AF016795E 38FC2EEB
	static scrAny _0x5E0165278F6339EE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x5E0165278F6339EE, p0); } // 5E0165278F6339EE 1C4F9FDB
	static BOOL _0x2D5DC831176D0114(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x2D5DC831176D0114, p0); } // 2D5DC831176D0114 A69AE16C
	static BOOL _0xEBFA8D50ADDC54C4(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xEBFA8D50ADDC54C4, p0); } // EBFA8D50ADDC54C4 F50BC67A
	static BOOL _0x162C23CA83ED0A62(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x162C23CA83ED0A62, p0); } // 162C23CA83ED0A62 B3BBD241
	static scrAny _0x40F7E66472DF3E5C(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x40F7E66472DF3E5C, p0, p1); } // 40F7E66472DF3E5C 70A2845C
	static BOOL _0x5A34CD9C3C5BEC44(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x5A34CD9C3C5BEC44, p0); } // 5A34CD9C3C5BEC44 346B506C
	static void _0x68103E2247887242() { NativeInvoke::Invoke<scrVoid>(0x68103E2247887242); } // 68103E2247887242 0095DB71
	static BOOL _0x1DE0F5F50D723CAA(scrAny *p0, scrAny *p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0x1DE0F5F50D723CAA, p0, p1, p2); } // 1DE0F5F50D723CAA AD334B40
	static BOOL _0x274A1519DFC1094F(scrAny *p0, BOOL p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0x274A1519DFC1094F, p0, p1, p2); } // 274A1519DFC1094F 980D45D7
	static BOOL _0xD05D1A6C74DA3498(scrAny *p0, BOOL p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0xD05D1A6C74DA3498, p0, p1, p2); } // D05D1A6C74DA3498 48CCC328
	static BOOL _0x45E816772E93A9DB() { return NativeInvoke::Invoke<BOOL>(0x45E816772E93A9DB); } // 45E816772E93A9DB 8E664EFD
	static BOOL _0x299EF3C576773506() { return NativeInvoke::Invoke<BOOL>(0x299EF3C576773506); } // 299EF3C576773506 611E0BE2
	static BOOL _0x793FF272D5B365F4() { return NativeInvoke::Invoke<BOOL>(0x793FF272D5B365F4); } // 793FF272D5B365F4 F0211AC1
	static scrAny _0x5A0A3D1A186A5508() { return NativeInvoke::Invoke<scrAny>(0x5A0A3D1A186A5508); } // 5A0A3D1A186A5508 1F0DD8AF
	static void _0xA1E5E0204A6FCC70() { NativeInvoke::Invoke<scrVoid>(0xA1E5E0204A6FCC70); } // A1E5E0204A6FCC70 405ECA16
	static BOOL _0xB746D20B17F2A229(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0xB746D20B17F2A229, p0, p1); } // B746D20B17F2A229 9567392B
	static BOOL _0x63B406D7884BFA95() { return NativeInvoke::Invoke<BOOL>(0x63B406D7884BFA95); } // 63B406D7884BFA95 F79FFF3C
	static BOOL _0x4D02279C83BE69FE() { return NativeInvoke::Invoke<BOOL>(0x4D02279C83BE69FE); } // 4D02279C83BE69FE A7F3F82B
	static scrAny _0x597F8DBA9B206FC7() { return NativeInvoke::Invoke<scrAny>(0x597F8DBA9B206FC7); } // 597F8DBA9B206FC7 410C61D1
	static BOOL _0x5CAE833B0EE0C500(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x5CAE833B0EE0C500, p0); } // 5CAE833B0EE0C500 0D4F845D
	static void _0x61A885D3F7CFEE9A() { NativeInvoke::Invoke<scrVoid>(0x61A885D3F7CFEE9A); } // 61A885D3F7CFEE9A E13C1F7F
	static void _0xF98DDE0A8ED09323(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xF98DDE0A8ED09323, p0); } // F98DDE0A8ED09323 213C6D36
	static void _0xFD75DABC0957BF33(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xFD75DABC0957BF33, p0); } // FD75DABC0957BF33 511E6F50
	static BOOL _0xF53E48461B71EECB(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xF53E48461B71EECB, p0); } // F53E48461B71EECB B4668B23
	static BOOL _0x098AB65B9ED9A9EC(scrAny *p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0x098AB65B9ED9A9EC, p0, p1, p2); } // 098AB65B9ED9A9EC 30B51753
	static BOOL _0xDC48473142545431() { return NativeInvoke::Invoke<BOOL>(0xDC48473142545431); } // DC48473142545431 02DAD93F
	static BOOL _0x0AE1F1653B554AB9(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x0AE1F1653B554AB9, p0); } // 0AE1F1653B554AB9 2D947814
	static BOOL _0x62B9FEC9A11F10EF() { return NativeInvoke::Invoke<BOOL>(0x62B9FEC9A11F10EF); } // 62B9FEC9A11F10EF 37A28C26
	static BOOL _0xA75E2B6733DA5142() { return NativeInvoke::Invoke<BOOL>(0xA75E2B6733DA5142); } // A75E2B6733DA5142 11E8B5CD
	static BOOL _0x43865688AE10F0D7() { return NativeInvoke::Invoke<BOOL>(0x43865688AE10F0D7); } // 43865688AE10F0D7 429AEAB3
	static scrAny TEXTURE_DOWNLOAD_REQUEST(scrAny *p0, scrAny *p1, scrAny *p2, BOOL p3) { return NativeInvoke::Invoke<scrAny>(0x16160DA74A8E74A2, p0, p1, p2, p3); } // 16160DA74A8E74A2 AD546CC3
	static scrAny _0x0B203B4AFDE53A4F(scrAny *p0, scrAny *p1, BOOL p2) { return NativeInvoke::Invoke<scrAny>(0x0B203B4AFDE53A4F, p0, p1, p2); } // 0B203B4AFDE53A4F 1856D008
	static scrAny _0x308F96458B7087CC(scrAny *p0, scrAny p1, scrAny p2, scrAny p3, scrAny *p4, BOOL p5) { return NativeInvoke::Invoke<scrAny>(0x308F96458B7087CC, p0, p1, p2, p3, p4, p5); } // 308F96458B7087CC 68C9AF69
	static void TEXTURE_DOWNLOAD_RELEASE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x487EB90B98E9FB19, p0); } // 487EB90B98E9FB19 EE8D9E70
	static BOOL _0x5776ED562C134687(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x5776ED562C134687, p0); } // 5776ED562C134687 E4547765
	static scrAny TEXTURE_DOWNLOAD_GET_NAME(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x3448505B6E35262D, p0); } // 3448505B6E35262D A40EF65A
	static scrAny _0x8BD6C6DEA20E82C6(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x8BD6C6DEA20E82C6, p0); } // 8BD6C6DEA20E82C6 03225BA3
	static BOOL _0x60EDD13EB3AC1FF3() { return NativeInvoke::Invoke<BOOL>(0x60EDD13EB3AC1FF3); } // 60EDD13EB3AC1FF3 4DEBC227
	static BOOL _0xEFFB25453D8600F9() { return NativeInvoke::Invoke<BOOL>(0xEFFB25453D8600F9); } // EFFB25453D8600F9 5C065D55
	static BOOL _0x66B59CFFD78467AF() { return NativeInvoke::Invoke<BOOL>(0x66B59CFFD78467AF); } // 66B59CFFD78467AF 0CA1167F
	static BOOL _0x606E4D3E3CCCF3EB() { return NativeInvoke::Invoke<BOOL>(0x606E4D3E3CCCF3EB); } // 606E4D3E3CCCF3EB 424C6E27
	static BOOL _0x8020A73847E0CA7D() { return NativeInvoke::Invoke<BOOL>(0x8020A73847E0CA7D); } // 8020A73847E0CA7D D3BBE42F
	static BOOL _0xA0AD7E2AF5349F61() { return NativeInvoke::Invoke<BOOL>(0xA0AD7E2AF5349F61); } // A0AD7E2AF5349F61 BDBB5948
	static BOOL _0x5F91D5D0B36AA310() { return NativeInvoke::Invoke<BOOL>(0x5F91D5D0B36AA310); } // 5F91D5D0B36AA310 97287D68
	static BOOL _0x422D396F80A96547() { return NativeInvoke::Invoke<BOOL>(0x422D396F80A96547); } // 422D396F80A96547 C6EA802E
	static BOOL _0xA699957E60D80214(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xA699957E60D80214, p0); } // A699957E60D80214 FD261E30
	static BOOL _0xC22912B1D85F26B1(scrAny p0, scrAny *p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0xC22912B1D85F26B1, p0, p1, p2); } // C22912B1D85F26B1 8570DD34
	static scrAny _0x36391F397731595D(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x36391F397731595D, p0); } // 36391F397731595D
	static void _0x9465E683B12D3F6B() { NativeInvoke::Invoke<scrVoid>(0x9465E683B12D3F6B); } // 9465E683B12D3F6B 273C6180
	static void _0xB7C7F6AD6424304B() { NativeInvoke::Invoke<scrVoid>(0xB7C7F6AD6424304B); } // B7C7F6AD6424304B 371BBA08
	static void _0xC505036A35AFD01B(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xC505036A35AFD01B, p0); } // C505036A35AFD01B A100CC97
	static void _0x267C78C60E806B9A(scrAny p0, BOOL p1) { NativeInvoke::Invoke<scrVoid>(0x267C78C60E806B9A, p0, p1); } // 267C78C60E806B9A BB2D33D3
	static void _0x6BFF5F84102DF80A(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x6BFF5F84102DF80A, p0); } // 6BFF5F84102DF80A
	static void _0x5C497525F803486B() { NativeInvoke::Invoke<scrVoid>(0x5C497525F803486B); } // 5C497525F803486B
	static scrAny _0x6FB7BB3607D27FA2() { return NativeInvoke::Invoke<scrAny>(0x6FB7BB3607D27FA2); } // 6FB7BB3607D27FA2
}

namespace NETWORKCASH
{
	static void _0x3DA5ECD1A56CBA6D(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x3DA5ECD1A56CBA6D, p0, p1); } // 3DA5ECD1A56CBA6D 66DA9935
	static void NETWORK_DELETE_CHARACTER(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x05A50AF38947EB8D, p0, p1, p2); } // 05A50AF38947EB8D A9F7E9C3
	static void _0xA921DED15FDF28F5(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA921DED15FDF28F5, p0); } // A921DED15FDF28F5 19F0C471
	static void NETWORK_GIVE_PLAYER_JOBSHARE_CASH(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xFB18DF9CB95E0105, p0, p1); } // FB18DF9CB95E0105 C6047FDB
	static void NETWORK_RECEIVE_PLAYER_JOBSHARE_CASH(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x56A3B51944C50598, p0, p1); } // 56A3B51944C50598 4ED71C1A
	static BOOL _0x1C2473301B1C66BA() { return NativeInvoke::Invoke<BOOL>(0x1C2473301B1C66BA); } // 1C2473301B1C66BA A27B9FE8
	static void _0xF9C812CD7C46E817(scrAny p0, scrAny *p1, scrAny *p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0xF9C812CD7C46E817, p0, p1, p2, p3); } // F9C812CD7C46E817 07C92F21
	static BOOL _0x81404F3DC124FE5B(scrAny p0, BOOL p1, BOOL p2) { return NativeInvoke::Invoke<BOOL>(0x81404F3DC124FE5B, p0, p1, p2); } // 81404F3DC124FE5B 8474E6F0
	static BOOL _0x3A54E33660DED67F(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x3A54E33660DED67F, p0); } // 3A54E33660DED67F E3802533
	static void NETWORK_EARN_FROM_PICKUP(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xED1517D3AF17C698, p0); } // ED1517D3AF17C698 70A0ED62
	static void _0xA03D4ACE0A3284CE(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xA03D4ACE0A3284CE, p0); } // A03D4ACE0A3284CE 33C20BC4
	static void _0xF514621E8EA463D0(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xF514621E8EA463D0, p0); } // F514621E8EA463D0 30B3EC0A
	static void _0xB1CC1B9EC3007A2A(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0xB1CC1B9EC3007A2A, p0); } // B1CC1B9EC3007A2A EAF04923
	static void NETWORK_EARN_FROM_BETTING(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x827A5BA1A44ACA6D, p0, p1); } // 827A5BA1A44ACA6D A0F7F07C
	static void NETWORK_EARN_FROM_JOB(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xB2CC4836834E8A98, p0, p1); } // B2CC4836834E8A98 0B6997FC
	static void _0x61326EE6DF15B0CA(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x61326EE6DF15B0CA, p0, p1); } // 61326EE6DF15B0CA 5E81F55C
	static void _0x2B171E6B2F64D8DF(scrAny p0, scrAny *p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x2B171E6B2F64D8DF, p0, p1, p2); } // 2B171E6B2F64D8DF 2BEFB6C4
	static void NETWORK_EARN_FROM_BOUNTY(scrAny p0, scrAny *p1, scrAny *p2, scrAny p3) { NativeInvoke::Invoke<scrVoid>(0x131BB5DA15453ACF, p0, p1, p2, p3); } // 131BB5DA15453ACF 127F2DAE
	static void _0xF92A014A634442D6(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xF92A014A634442D6, p0, p1); } // F92A014A634442D6 F11FC458
	static void NETWORK_EARN_FROM_HOLDUPS(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x45B8154E077D9E4D, p0); } // 45B8154E077D9E4D E6B90E9C
	static void NETWORK_EARN_FROM_PROPERTY(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x849648349D77F5C5, p0, p1); } // 849648349D77F5C5 9BE4F7E1
	static void _0x515B4A22E4D3C6D7(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x515B4A22E4D3C6D7, p0, p1); } // 515B4A22E4D3C6D7 866004A8
	static void _0x4337511FA8221D36(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x4337511FA8221D36, p0); } // 4337511FA8221D36 CC068380
	static void NETWORK_EARN_FROM_ROCKSTAR(scrAny p0) { NativeInvoke::Invoke<scrVoid>(0x02CE1D6AC0FC73EA, p0); } // 02CE1D6AC0FC73EA 5A3733CC
	static void NETWORK_EARN_FROM_VEHICLE(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0xB539BD8A4C1EECF8, p0, p1); } // B539BD8A4C1EECF8 F803589D
	static void _0x3F4D00167E41E0AD(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x3F4D00167E41E0AD, p0, p1); } // 3F4D00167E41E0AD 96B8BEE8
	static BOOL _0xAB3CAA6B422164DA(scrAny p0, BOOL p1, BOOL p2, BOOL p3, scrAny p4) { return NativeInvoke::Invoke<BOOL>(0xAB3CAA6B422164DA, p0, p1, p2, p3, p4); } // AB3CAA6B422164DA 5AA379D9
	static void NETWORK_BUY_ITEM(scrAny p0, scrAny p1, scrAny p2, scrAny p3, BOOL p4, scrAny *p5, scrAny p6, scrAny p7, scrAny p8, BOOL p9) { NativeInvoke::Invoke<scrVoid>(0xF0077C797F66A355, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); } // F0077C797F66A355 A07B6368
	static void NETWORK_SPENT_TAXI(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x17C3A7D31EAE39F9, p0, p1, p2); } // 17C3A7D31EAE39F9 1F3DB3E3
	static void _0x5FD5ED82CBBE9989(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x5FD5ED82CBBE9989, p0, p1, p2); } // 5FD5ED82CBBE9989 BE70849B
	static void _0xAFE08B35EC0C9EAE(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xAFE08B35EC0C9EAE, p0, p1, p2); } // AFE08B35EC0C9EAE 451A2644
	static void _0x9346E14F2AF74D46(scrAny p0, scrAny *p1, BOOL p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x9346E14F2AF74D46, p0, p1, p2, p3); } // 9346E14F2AF74D46 224A3488
	static void NETWORK_SPENT_BETTING(scrAny p0, scrAny p1, scrAny *p2, BOOL p3, BOOL p4) { NativeInvoke::Invoke<scrVoid>(0x1C436FD11FFA692F, p0, p1, p2, p3, p4); } // 1C436FD11FFA692F F8A07513
	static void _0xEE99784E4467689C(scrAny p0, BOOL p1, scrAny p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0xEE99784E4467689C, p0, p1, p2, p3); } // EE99784E4467689C 8957038E
	static void NETWORK_BUY_HEALTHCARE(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xD9B067E55253E3DD, p0, p1, p2); } // D9B067E55253E3DD 832150E5
	static void NETWORK_BUY_AIRSTRIKE(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x763B4BD305338F19, p0, p1, p2); } // 763B4BD305338F19 40470683
	static void _0x81AA4610E3FD3A69(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x81AA4610E3FD3A69, p0, p1, p2); } // 81AA4610E3FD3A69 047547D4
	static void NETWORK_SPENT_AMMO_DROP(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xB162DC95C0A3317B, p0, p1, p2); } // B162DC95C0A3317B 4B643076
	static void NETWORK_BUY_BOUNTY(scrAny p0, scrAny p1, BOOL p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x7B718E197453F2D9, p0, p1, p2, p3); } // 7B718E197453F2D9 CB89CBE0
	static void NETWORK_BUY_PROPERTY(scrAny p0, scrAny p1, BOOL p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x650A08A280870AF6, p0, p1, p2, p3); } // 650A08A280870AF6 7D479AAB
	static void NETWORK_SPENT_HELI_PICKUP(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x7BF1D73DB2ECA492, p0, p1, p2); } // 7BF1D73DB2ECA492 27EEBCAB
	static void NETWORK_SPENT_BOAT_PICKUP(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x524EE43A37232C00, p0, p1, p2); } // 524EE43A37232C00 B241CABD
	static void _0xA6DD8458CE24012C(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xA6DD8458CE24012C, p0, p1, p2); } // A6DD8458CE24012C DE7D398C
	static void NETWORK_SPENT_CASH_DROP(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x289016EC778D60E0, p0, p1, p2); } // 289016EC778D60E0 87BD1D11
	static void _0xE404BFB981665BF0(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xE404BFB981665BF0, p0, p1, p2); } // E404BFB981665BF0 E792C4A5
	static void _0x995A65F15F581359(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x995A65F15F581359, p0, p1, p2); } // 995A65F15F581359 E6AAA0D5
	static void _0xE7B80E2BF9D80BD6(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xE7B80E2BF9D80BD6, p0, p1, p2); } // E7B80E2BF9D80BD6 99CF02C4
	static void NETWORK_SPENT_BUY_WANTEDLEVEL(scrAny p0, scrAny *p1, BOOL p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0xE1B13771A843C4F6, p0, p1, p2, p3); } // E1B13771A843C4F6 E7CB4F95
	static void _0xA628A745E2275C5D(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xA628A745E2275C5D, p0, p1, p2); } // A628A745E2275C5D 20DDCF2F
	static void _0x6E176F1B18BC0637(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x6E176F1B18BC0637, p0, p1, p2); } // 6E176F1B18BC0637 2F7836E2
	static void NETWORK_SPENT_CARWASH(scrAny p0, scrAny p1, scrAny p2, BOOL p3, BOOL p4) { NativeInvoke::Invoke<scrVoid>(0xEC03C719DB2F4306, p0, p1, p2, p3, p4); } // EC03C719DB2F4306 8283E028
	static void NETWORK_SPENT_CINEMA(scrAny p0, scrAny p1, BOOL p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x6B38ECB05A63A685, p0, p1, p2, p3); } // 6B38ECB05A63A685 1100CAF5
	static void NETWORK_SPENT_TELESCOPE(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x7FE61782AD94CC09, p0, p1, p2); } // 7FE61782AD94CC09 AE7FF044
	static void NETWORK_SPENT_HOLDUPS(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xD9B86B9872039763, p0, p1, p2); } // D9B86B9872039763 1B3803B1
	static void _0x6D3A430D1A809179(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x6D3A430D1A809179, p0, p1, p2); } // 6D3A430D1A809179 7E97C92C
	static void _0xB21B89501CFAC79E(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xB21B89501CFAC79E, p0, p1, p2); } // B21B89501CFAC79E 78436D07
	static void _0x812F5488B1B2A299(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x812F5488B1B2A299, p0, p1, p2); } // 812F5488B1B2A299 5AEE2FC1
	static void NETWORK_SPENT_PAY_VEHICLE_INSURANCE_PREMIUM(scrAny p0, scrAny p1, scrAny *p2, BOOL p3, BOOL p4) { NativeInvoke::Invoke<scrVoid>(0x9FF28D88C766E3E8, p0, p1, p2, p3, p4); } // 9FF28D88C766E3E8 4E665BB2
	static void NETWORK_SPENT_CALL_PLAYER(scrAny p0, scrAny *p1, BOOL p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0xACDE7185B374177C, p0, p1, p2, p3); } // ACDE7185B374177C 1A89B5FC
	static void NETWORK_SPENT_BOUNTY(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x29B260B84947DFCC, p0, p1, p2); } // 29B260B84947DFCC 3401FC96
	static void _0x6A445B64ED7ABEB5(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x6A445B64ED7ABEB5, p0, p1, p2); } // 6A445B64ED7ABEB5 54198922
	static scrAny _0x20194D48EAEC9A41(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x20194D48EAEC9A41, p0, p1); } // 20194D48EAEC9A41 C5D8B1E9
	static void _0x7C99101F7FCE2EE5(scrAny p0, scrAny p1, BOOL p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x7C99101F7FCE2EE5, p0, p1, p2, p3); } // 7C99101F7FCE2EE5 3D96A21C
	static void _0xD5BB406F4E04019F(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0xD5BB406F4E04019F, p0, p1, p2); } // D5BB406F4E04019F 2E51C61C
	static void _0x8204DA7934DF3155(scrAny p0, BOOL p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x8204DA7934DF3155, p0, p1, p2); } // 8204DA7934DF3155 D57A5125
	static void _0x8A7B3952DD64D2B5(scrAny p0, scrAny p1, BOOL p2, BOOL p3) { NativeInvoke::Invoke<scrVoid>(0x8A7B3952DD64D2B5, p0, p1, p2, p3); } // 8A7B3952DD64D2B5 D9622D64
	static scrAny _0x76EF28DA05EA395A() { return NativeInvoke::Invoke<scrAny>(0x76EF28DA05EA395A); } // 76EF28DA05EA395A 16184FB5
	static scrAny _0xA40F9C2623F6A8B5(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xA40F9C2623F6A8B5, p0); } // A40F9C2623F6A8B5 4F5B781C
	static scrAny _0x5CBAD97E059E1B94() { return NativeInvoke::Invoke<scrAny>(0x5CBAD97E059E1B94); } // 5CBAD97E059E1B94 ADF8F882
	static scrAny _0xA6FA3979BED01B81() { return NativeInvoke::Invoke<scrAny>(0xA6FA3979BED01B81); } // A6FA3979BED01B81
	static BOOL _0xDC18531D7019A535(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xDC18531D7019A535, p0, p1); } // DC18531D7019A535
	static scrAny NETWORK_CAN_RECEIVE_PLAYER_CASH(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0x5D17BE59D2123284, p0, p1, p2, p3); } // 5D17BE59D2123284 41F5F10E
	static scrAny _0xF70EFA14FE091429(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xF70EFA14FE091429, p0); } // F70EFA14FE091429 8B755993
	static BOOL _0xE260E0BB9CD995AC(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xE260E0BB9CD995AC, p0); } // E260E0BB9CD995AC 8F266745
	static scrAny _0xE154B48B68EF72BC(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xE154B48B68EF72BC, p0); } // E154B48B68EF72BC 531E4892
	static scrAny _0x6FCF8DDEA146C45B(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x6FCF8DDEA146C45B, p0); } // 6FCF8DDEA146C45B B96C7ABE
}

namespace DLC1
{
	static scrAny _0x278F76C3B0A8F109(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x278F76C3B0A8F109, p0); } // 278F76C3B0A8F109 71D0CF3E
	static BOOL _0xFF56381874F82086(scrAny p0, scrAny p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0xFF56381874F82086, p0, p1, p2); } // FF56381874F82086 2E9D628C
	static void INIT_SHOP_PED_COMPONENT(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x1E8C308FD312C036, p0); } // 1E8C308FD312C036 B818C7FC
	static void INIT_SHOP_PED_PROP(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xEB0A2B758F7B850F, p0); } // EB0A2B758F7B850F F5659E50
	static scrAny _0x50F457823CE6EB5F(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0x50F457823CE6EB5F, p0, p1, p2, p3); } // 50F457823CE6EB5F C937FF3D
	static scrAny _0x9BDF59818B1E38C1(scrAny p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { return NativeInvoke::Invoke<scrAny>(0x9BDF59818B1E38C1, p0, p1, p2, p3, p4, p5); } // 9BDF59818B1E38C1 594E862C
	static void GET_SHOP_PED_QUERY_COMPONENT(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x249E310B2D920699, p0, p1); } // 249E310B2D920699 C0718904
	static void GET_SHOP_PED_COMPONENT(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x74C0E2A57EC66760, p0, p1); } // 74C0E2A57EC66760 B39677C5
	static void GET_SHOP_PED_QUERY_PROP(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xDE44A00999B2837D, p0, p1); } // DE44A00999B2837D 1D3C1466
	static scrAny _0x0368B3A838070348(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0x0368B3A838070348, p0, p1, p2, p3); } // 0368B3A838070348 C8A4BF12
	static scrAny _0x5D6160275CAEC8DD(scrAny p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<scrAny>(0x5D6160275CAEC8DD, p0, p1, p2, p3); } // 5D6160275CAEC8DD 7D876DC0
	static scrAny _0xC17AD0E5752BECDA(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xC17AD0E5752BECDA, p0); } // C17AD0E5752BECDA 159751B4
	static void _0x6E11F282F11863B6(scrAny p0, scrAny p1, scrAny *p2, scrAny *p3, scrAny *p4) { NativeInvoke::Invoke<scrVoid>(0x6E11F282F11863B6, p0, p1, p2, p3, p4); } // 6E11F282F11863B6 E4FF7103
	static scrAny _0xC6B9DB42C04DD8C3(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xC6B9DB42C04DD8C3, p0); } // C6B9DB42C04DD8C3 CE70F183
	static void GET_FORCED_COMPONENT(scrAny p0, scrAny p1, scrAny *p2, scrAny *p3, scrAny *p4) { NativeInvoke::Invoke<scrVoid>(0x6C93ED8C2F74859B, p0, p1, p2, p3, p4); } // 6C93ED8C2F74859B 382C70BE
	static scrAny _0x341DE7ED1D2A1BFD(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0x341DE7ED1D2A1BFD, p0, p1, p2); } // 341DE7ED1D2A1BFD 8E2C7FD5
	static scrAny _0xF3FBE2D50A6A8C28(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0xF3FBE2D50A6A8C28, p0, p1); } // F3FBE2D50A6A8C28 1ECD23E7
	static void GET_SHOP_PED_QUERY_OUTFIT(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0x6D793F03A631FE56, p0, p1); } // 6D793F03A631FE56 2F8013A1
	static void _0xB7952076E444979D(scrAny p0, scrAny *p1) { NativeInvoke::Invoke<scrVoid>(0xB7952076E444979D, p0, p1); } // B7952076E444979D CAFE9209
	static scrAny _0x073CA26B079F956E(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x073CA26B079F956E, p0); } // 073CA26B079F956E 2798F56F
	static BOOL _0xA9F9C2E0FDE11CBB(scrAny p0, scrAny p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0xA9F9C2E0FDE11CBB, p0, p1, p2); } // A9F9C2E0FDE11CBB 6641A864
	static BOOL _0x19F2A026EDF0013F(scrAny p0, scrAny p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0x19F2A026EDF0013F, p0, p1, p2); } // 19F2A026EDF0013F 818534AC
	static scrAny _0xA7A866D21CD2329B() { return NativeInvoke::Invoke<scrAny>(0xA7A866D21CD2329B); } // A7A866D21CD2329B 8EAF9CF6
	static scrAny GET_DLC_VEHICLE_MODEL(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xECC01B7C5763333C, p0); } // ECC01B7C5763333C A2201E09
	static BOOL GET_DLC_VEHICLE_DATA(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x33468EDC08E371F6, p0, p1); } // 33468EDC08E371F6 CF428FA4
	static scrAny GET_DLC_VEHICLE_FLAGS(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x5549EE11FA22FCF2, p0); } // 5549EE11FA22FCF2 AB12738C
	static scrAny _0xEE47635F352DA367() { return NativeInvoke::Invoke<scrAny>(0xEE47635F352DA367); } // EE47635F352DA367 2B757E6C
	static BOOL GET_DLC_WEAPON_DATA(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x79923CD21BECE14E, p0, p1); } // 79923CD21BECE14E D88EC8EA
	static scrAny _0x405425358A7D61FE(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x405425358A7D61FE, p0); } // 405425358A7D61FE 476B23A9
	static BOOL GET_DLC_WEAPON_COMPONENT_DATA(scrAny p0, scrAny p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0x6CF598A2957C2BF8, p0, p1, p2); } // 6CF598A2957C2BF8 4B83FCAF
	static BOOL _0xD4D7B033C3AA243C(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xD4D7B033C3AA243C, p0); } // D4D7B033C3AA243C 06396058
	static BOOL _0x0564B9FF9631B82C(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x0564B9FF9631B82C, p0); } // 0564B9FF9631B82C 35BCA844
	static scrAny _0xC098810437312FFF(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xC098810437312FFF, p0); } // C098810437312FFF 59352658
}

namespace DLC2
{
	static BOOL IS_DLC_PRESENT(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x812595A0644CE1DE, p0); } // 812595A0644CE1DE 1F321943
	static scrAny _0xF2E07819EF1A5289() { return NativeInvoke::Invoke<scrAny>(0xF2E07819EF1A5289); } // F2E07819EF1A5289 881B1FDB
	static scrAny _0x9489659372A81585() { return NativeInvoke::Invoke<scrAny>(0x9489659372A81585); } // 9489659372A81585 C2169164
	static scrAny _0xA213B11DFF526300() { return NativeInvoke::Invoke<scrAny>(0xA213B11DFF526300); } // A213B11DFF526300 F79A97F5
	static scrAny _0x8D30F648014A92B5() { return NativeInvoke::Invoke<scrAny>(0x8D30F648014A92B5); } // 8D30F648014A92B5 F69B729C
	static BOOL _0x10D0A8F259E93EC9() { return NativeInvoke::Invoke<BOOL>(0x10D0A8F259E93EC9); } // 10D0A8F259E93EC9 517B601B
	static scrAny _0x46E2B844905BC5F0(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<scrAny>(0x46E2B844905BC5F0, p0, p1); } // 46E2B844905BC5F0 6087C10C
	static void _0xD7C10C4A637992C9() { NativeInvoke::Invoke<scrVoid>(0xD7C10C4A637992C9); } // D7C10C4A637992C9
	static void _0x0888C3502DBBEEF5() { NativeInvoke::Invoke<scrVoid>(0x0888C3502DBBEEF5); } // 0888C3502DBBEEF5
}

namespace DECORATOR
{
	static BOOL _0x95AED7B8E39ECAA4(scrAny p0, scrAny *p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0x95AED7B8E39ECAA4, p0, p1, p2); } // 95AED7B8E39ECAA4 BBAEEF94
	static BOOL _0x6B1E8E2ED1335B71(scrAny p0, scrAny *p1, BOOL p2) { return NativeInvoke::Invoke<BOOL>(0x6B1E8E2ED1335B71, p0, p1, p2); } // 6B1E8E2ED1335B71 8E101F5C
	static BOOL _0x0CE3AA5E1CA19E10(scrAny p0, scrAny *p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0x0CE3AA5E1CA19E10, p0, p1, p2); } // 0CE3AA5E1CA19E10 DB718B21
	static BOOL _0xDACE671663F2F5DB(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0xDACE671663F2F5DB, p0, p1); } // DACE671663F2F5DB DBCE51E0
	static scrAny _0xA06C969B02A97298(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<scrAny>(0xA06C969B02A97298, p0, p1); } // A06C969B02A97298 DDDE59B5
	static BOOL _0x05661B80A8C9165F(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x05661B80A8C9165F, p0, p1); } // 05661B80A8C9165F 74EF9C40
	static BOOL _0x00EE9F297C738720(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x00EE9F297C738720, p0, p1); } // 00EE9F297C738720 E0E2640B
	static void _0x9FD90732F56403CE(scrAny *p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x9FD90732F56403CE, p0, p1); } // 9FD90732F56403CE 68BD42A9
	static BOOL _0x4F14F9F870D6FBC8(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x4F14F9F870D6FBC8, p0, p1); } // 4F14F9F870D6FBC8 7CF0971D
	static void _0xA9D14EEA259F9248() { NativeInvoke::Invoke<scrVoid>(0xA9D14EEA259F9248); } // A9D14EEA259F9248 7F3F1C02
}

namespace UNK_SC
{
	static scrAny _0x03A93FF1A2CA0864() { return NativeInvoke::Invoke<scrAny>(0x03A93FF1A2CA0864); } // 03A93FF1A2CA0864 6BE5DF29
	static scrAny _0xBB8EA16ECBC976C4(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xBB8EA16ECBC976C4, p0); } // BB8EA16ECBC976C4 5ECF955D
	static BOOL _0x93028F1DB42BFD08(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x93028F1DB42BFD08, p0); } // 93028F1DB42BFD08 D1ED1D48
	static BOOL _0x2C015348CF19CA1D(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x2C015348CF19CA1D, p0); } // 2C015348CF19CA1D 19EE0CCB
	static BOOL SC_INBOX_MESSAGE_GET_DATA_INT(scrAny p0, scrAny *p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0xA00EFE4082C4056E, p0, p1, p2); } // A00EFE4082C4056E 88068C7C
	static BOOL SC_INBOX_MESSAGE_GET_DATA_STRING(scrAny p0, scrAny *p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0x7572EF42FC6A9B6D, p0, p1, p2); } // 7572EF42FC6A9B6D 15607620
	static BOOL _0x9A2C8064B6C1E41A(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x9A2C8064B6C1E41A, p0); } // 9A2C8064B6C1E41A EBE420A4
	static scrAny _0xF3E31D16CBDCB304(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0xF3E31D16CBDCB304, p0); } // F3E31D16CBDCB304 2C959AF9
	static void _0xDA024BDBD600F44A(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xDA024BDBD600F44A, p0); } // DA024BDBD600F44A 0B9A3512
	static void _0xA68D3D229F4F3B06(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0xA68D3D229F4F3B06, p0); } // A68D3D229F4F3B06 75324674
	static BOOL SC_INBOX_MESSAGE_GET_UGCDATA(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x69D82604A1A5A254, p0, p1); } // 69D82604A1A5A254 88CA3BFC
	static BOOL _0x6AFD2CD753FEEF83(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x6AFD2CD753FEEF83, p0); } // 6AFD2CD753FEEF83 628F489B
	static BOOL _0x87E0052F08BD64E6(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x87E0052F08BD64E6, p0, p1); } // 87E0052F08BD64E6 AB3346B5
	static void _0x2330C12A7A605D16(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x2330C12A7A605D16, p0); } // 2330C12A7A605D16 9A703A2B
	static void _0x55DF6DB45179236E() { NativeInvoke::Invoke<scrVoid>(0x55DF6DB45179236E); } // 55DF6DB45179236E D094F11A
	static void _0x116FB94DC4B79F17(scrAny *p0) { NativeInvoke::Invoke<scrVoid>(0x116FB94DC4B79F17, p0); } // 116FB94DC4B79F17 AF3C081B
	static void _0xBFA0A56A817C6C7D(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xBFA0A56A817C6C7D, p0); } // BFA0A56A817C6C7D 2FB9F53C
	static scrAny _0xBC1CC91205EC8D6E() { return NativeInvoke::Invoke<scrAny>(0xBC1CC91205EC8D6E); } // BC1CC91205EC8D6E 6C5738AB
	static scrAny _0xDF649C4E9AFDD788() { return NativeInvoke::Invoke<scrAny>(0xDF649C4E9AFDD788); } // DF649C4E9AFDD788 468668F0
	static BOOL _0x1F1E9682483697C7(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0x1F1E9682483697C7, p0, p1); } // 1F1E9682483697C7 90C74343
	static BOOL _0x287F1F75D2803595(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x287F1F75D2803595, p0, p1); } // 287F1F75D2803595 3ACE6D6B
	static BOOL _0x487912FD248EFDDF(scrAny p0, float p1) { return NativeInvoke::Invoke<BOOL>(0x487912FD248EFDDF, p0, p1); } // 487912FD248EFDDF 579B4510
	static BOOL _0x8416FE4E4629D7D7(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x8416FE4E4629D7D7, p0); } // 8416FE4E4629D7D7 DF45B2A7
	static BOOL _0x75632C5ECD7ED843(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x75632C5ECD7ED843, p0, p1); } // 75632C5ECD7ED843 DF084A6B
	static BOOL _0x1753344C770358AE(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x1753344C770358AE, p0); } // 1753344C770358AE FFED3676
	static scrAny _0x82E4A58BABC15AE7(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x82E4A58BABC15AE7, p0); } // 82E4A58BABC15AE7 A796D7A7
	static scrAny _0x85535ACF97FC0969(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x85535ACF97FC0969, p0); } // 85535ACF97FC0969 09497F31
	static scrAny _0x930DE22F07B1CCE3(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x930DE22F07B1CCE3, p0); } // 930DE22F07B1CCE3 4D8A6521
	static BOOL _0xF6BAAAF762E1BF40(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0xF6BAAAF762E1BF40, p0, p1); } // F6BAAAF762E1BF40 7AA36406
	static BOOL _0xF22CA0FD74B80E7A(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xF22CA0FD74B80E7A, p0); } // F22CA0FD74B80E7A F379DCE4
	static scrAny _0x9237E334F6E43156(scrAny p0) { return NativeInvoke::Invoke<scrAny>(0x9237E334F6E43156, p0); } // 9237E334F6E43156 65D84665
	static BOOL _0xFF8F3A92B75ED67A() { return NativeInvoke::Invoke<BOOL>(0xFF8F3A92B75ED67A); } // FF8F3A92B75ED67A C96456BA
	static scrAny _0x4A7D6E727F941747(scrAny *p0) { return NativeInvoke::Invoke<scrAny>(0x4A7D6E727F941747, p0); } // 4A7D6E727F941747 8E7AEEB7
	static BOOL _0x8CC469AB4D349B7C(scrAny p0, scrAny *p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0x8CC469AB4D349B7C, p0, p1, p2); } // 8CC469AB4D349B7C E778B2A7
	static BOOL _0x699E4A5C8C893A18(scrAny p0, scrAny *p1, scrAny *p2) { return NativeInvoke::Invoke<BOOL>(0x699E4A5C8C893A18, p0, p1, p2); } // 699E4A5C8C893A18 CE7D50A8
	static BOOL _0x19853B5B17D77BCA(scrAny p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x19853B5B17D77BCA, p0, p1); } // 19853B5B17D77BCA D26CCA46
	static BOOL _0x6BFB12CE158E3DD4(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x6BFB12CE158E3DD4, p0); } // 6BFB12CE158E3DD4 24D84334
	static BOOL _0xFE4C1D0D3B9CC17E(scrAny p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xFE4C1D0D3B9CC17E, p0, p1); } // FE4C1D0D3B9CC17E 8A023024
	static BOOL _0xD8122C407663B995() { return NativeInvoke::Invoke<BOOL>(0xD8122C407663B995); } // D8122C407663B995 1C65B038
	static BOOL _0x3001BEF2FECA3680() { return NativeInvoke::Invoke<BOOL>(0x3001BEF2FECA3680); } // 3001BEF2FECA3680 4D4C37B3
	static BOOL _0x92DA6E70EF249BD1(scrAny *p0, scrAny *p1) { return NativeInvoke::Invoke<BOOL>(0x92DA6E70EF249BD1, p0, p1); } // 92DA6E70EF249BD1 AED95A6F
	static void _0x675721C9F644D161() { NativeInvoke::Invoke<scrVoid>(0x675721C9F644D161); } // 675721C9F644D161 486867E6
	static scrAny _0x198D161F458ECC7F() { return NativeInvoke::Invoke<scrAny>(0x198D161F458ECC7F); } // 198D161F458ECC7F
	static BOOL _0x225798743970412B(scrAny *p0) { return NativeInvoke::Invoke<BOOL>(0x225798743970412B, p0); } // 225798743970412B
	static BOOL _0x418DC16FAE452C1C(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x418DC16FAE452C1C, p0); } // 418DC16FAE452C1C
}

namespace UNK
{
	static scrAny _0xF2CA003F167E21D2() { return NativeInvoke::Invoke<scrAny>(0xF2CA003F167E21D2); } // F2CA003F167E21D2 106C8317
	static BOOL _0xEF7D17BC6C85264C() { return NativeInvoke::Invoke<BOOL>(0xEF7D17BC6C85264C); } // EF7D17BC6C85264C D87F3A9E
	static void _0xB0C56BD3D808D863(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xB0C56BD3D808D863, p0); } // B0C56BD3D808D863 C0B971EA
	static BOOL _0x8AA464D4E0F6ACCD() { return NativeInvoke::Invoke<BOOL>(0x8AA464D4E0F6ACCD); } // 8AA464D4E0F6ACCD 94BCAC7C
	static void _0xFC309E94546FCDB5(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xFC309E94546FCDB5, p0); } // FC309E94546FCDB5 7D90EEE5
	static BOOL _0xC6DC823253FBB366() { return NativeInvoke::Invoke<BOOL>(0xC6DC823253FBB366); } // C6DC823253FBB366 734CFEDA
	static void _0xC7E7181C09F33B69(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xC7E7181C09F33B69, p0); } // C7E7181C09F33B69 8C227332
	static void _0xFA1E0E893D915215(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0xFA1E0E893D915215, p0); } // FA1E0E893D915215 5C350D78
}

namespace UNK1
{
	static void _0x48621C9FCA3EBD28(BOOL p0) { NativeInvoke::Invoke<scrVoid>(0x48621C9FCA3EBD28, p0); } // 48621C9FCA3EBD28
	static void _0x81CBAE94390F9F89() { NativeInvoke::Invoke<scrVoid>(0x81CBAE94390F9F89); } // 81CBAE94390F9F89
	static void _0x13B350B8AD0EEE10() { NativeInvoke::Invoke<scrVoid>(0x13B350B8AD0EEE10); } // 13B350B8AD0EEE10
	static void _0x293220DA1B46CEBC(float p0, float p1, BOOL p2) { NativeInvoke::Invoke<scrVoid>(0x293220DA1B46CEBC, p0, p1, p2); } // 293220DA1B46CEBC
	static void _0x208784099002BC30(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x208784099002BC30, p0, p1); } // 208784099002BC30
	static void _0xEB2D525B57F42B40() { NativeInvoke::Invoke<scrVoid>(0xEB2D525B57F42B40); } // EB2D525B57F42B40
	static void _0xF854439EFBB3B583() { NativeInvoke::Invoke<scrVoid>(0xF854439EFBB3B583); } // F854439EFBB3B583
	static void _0xAF66DCEE6609B148() { NativeInvoke::Invoke<scrVoid>(0xAF66DCEE6609B148); } // AF66DCEE6609B148
	static void _0x66972397E0757E7A(scrAny p0, scrAny p1, scrAny p2) { NativeInvoke::Invoke<scrVoid>(0x66972397E0757E7A, p0, p1, p2); } // 66972397E0757E7A
}

namespace UNK2
{
	static void _0x7E2BD3EF6C205F09(scrAny p0, scrAny p1) { NativeInvoke::Invoke<scrVoid>(0x7E2BD3EF6C205F09, p0, p1); } // 7E2BD3EF6C205F09
	static scrAny _0x95AB8B5C992C7B58() { return NativeInvoke::Invoke<scrAny>(0x95AB8B5C992C7B58); } // 95AB8B5C992C7B58
	static void _0x5AD3932DAEB1E5D3() { NativeInvoke::Invoke<scrVoid>(0x5AD3932DAEB1E5D3); } // 5AD3932DAEB1E5D3
}

namespace UNK3
{
	static scrAny _0xC27009422FCCA88D(scrAny p0, scrAny p1, scrAny p2) { return NativeInvoke::Invoke<scrAny>(0xC27009422FCCA88D, p0, p1, p2); } // C27009422FCCA88D
	static BOOL _0x3C4487461E9B0DCB() { return NativeInvoke::Invoke<BOOL>(0x3C4487461E9B0DCB); } // 3C4487461E9B0DCB
	static scrAny _0x85F6C9ABA1DE2BCF() { return NativeInvoke::Invoke<scrAny>(0x85F6C9ABA1DE2BCF); } // 85F6C9ABA1DE2BCF
	static BOOL _0x279F08B1A4B29B7E(scrAny *p0, scrAny p1, scrAny p2, scrAny p3) { return NativeInvoke::Invoke<BOOL>(0x279F08B1A4B29B7E, p0, p1, p2, p3); } // 279F08B1A4B29B7E
	static BOOL _0xA65568121DF2EA26() { return NativeInvoke::Invoke<BOOL>(0xA65568121DF2EA26); } // A65568121DF2EA26
	static BOOL _0xF30980718C8ED876(scrAny *p0, scrAny p1) { return NativeInvoke::Invoke<BOOL>(0xF30980718C8ED876, p0, p1); } // F30980718C8ED876
	static BOOL _0x27F76CC6C55AD30E() { return NativeInvoke::Invoke<BOOL>(0x27F76CC6C55AD30E); } // 27F76CC6C55AD30E
	static BOOL _0x39BE7CEA8D9CC8E6(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0x39BE7CEA8D9CC8E6, p0); } // 39BE7CEA8D9CC8E6
	static BOOL _0x3C5FD37B5499582E(scrAny *p0, scrAny p1, scrAny p2, scrAny p3, scrAny p4, scrAny p5) { return NativeInvoke::Invoke<BOOL>(0x3C5FD37B5499582E, p0, p1, p2, p3, p4, p5); } // 3C5FD37B5499582E
	static BOOL _0xE2A99A9B524BEFFF(scrAny p0) { return NativeInvoke::Invoke<BOOL>(0xE2A99A9B524BEFFF, p0); } // E2A99A9B524BEFFF
	static BOOL _0x51F1A8E48C3D2F6D(scrAny p0, BOOL p1, scrAny p2) { return NativeInvoke::Invoke<BOOL>(0x51F1A8E48C3D2F6D, p0, p1, p2); } // 51F1A8E48C3D2F6D
	static scrAny _0x0A6D923DFFC9BD89() { return NativeInvoke::Invoke<scrAny>(0x0A6D923DFFC9BD89); } // 0A6D923DFFC9BD89
}

namespace SYSTEM
{
	static int START_NEW_SCRIPT(LPSTR name, int stack) { return NativeInvoke::Invoke<int>(0xE81651AD79516E48, name, stack); } // E81651AD79516E48 3F166D0E
}
