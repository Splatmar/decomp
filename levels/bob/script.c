#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/level_update.h"

#include "levels/scripts.h"

#include "actors/common1.h"
#include "actors/common1.h"
#include "make_const_nonconst.h"
#include "levels/bob/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_bob_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _bob_segment_7SegmentRomStart, _bob_segment_7SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _generic_yay0SegmentRomStart, _generic_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0A, _bitfs_skybox_yay0SegmentRomStart, _bitfs_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group2_yay0SegmentRomStart, _group2_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group2_geoSegmentRomStart, _group2_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group14_yay0SegmentRomStart, _group14_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group14_geoSegmentRomStart, _group14_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	LOAD_YAY0(0xb, _effect_yay0SegmentRomStart, _effect_yay0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_3), 
	JUMP_LINK(script_func_global_15), 
	LOAD_MODEL_FROM_GEO(MODEL_TRAIN, train_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_LAVA_PIQUE, lava_pique_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_LAVA_BULL, lava_bull_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_GRILLE, grille_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_PLAT_LAVA_MOVING, platlavamoving_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_ROT_LAVA_PLAT, rotlavaplat_geo), 
	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, bob_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_LLL, 0x01, 0x0B, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_GRILLE, 14748, 2695, 7389, 0, 0, 0, 0x00000000, breaking_surface),
		OBJECT(MODEL_NONE, 3734, 2090, 0, 0, 0, 0, 0x00000000, bhvLavaWaveSpawner),
		OBJECT(MODEL_PLAT_LAVA_MOVING, 11010, 1740, -3278, 18, -105, -12, 0x00000000, bhvStaticObject),
		OBJECT(MODEL_LAVA_BULL, 9992, 1740, -1398, 0, 0, 0, 0x00000000, bhv_big_flame_talking),
		OBJECT(MODEL_BOBOMB_BUDDY, 14719, 1953, 7636, 0, 0, 0, 0x00000000, bhvMonkeyBreakGrill),
		OBJECT(MODEL_EXCLAMATION_BOX, 15332, 1998, -433, 0, 0, 0, (1 << 24) | (16 << 16) | (1 << 8) | (1), bhvExclamationBox),
		OBJECT(MODEL_BULLY, 8918, 2164, 2063, 0, 0, 0, 0x00000000, bhvSmallBully),
		OBJECT(MODEL_BULLY, 10129, 2162, 3287, 0, 0, 0, 0x00000000, bhvSmallBully),
		OBJECT(MODEL_BULLY, 1797, 2670, 7363, 0, 0, 0, 0x00000000, bhvSmallBully),
		OBJECT(MODEL_BOWLING_BALL, 374, 3057, 6594, 0, 0, 0, 0x00000000, bhvFireSpitter),
		OBJECT(MODEL_BOWLING_BALL, -409, 3057, 7286, 0, 0, 0, 0x00000000, bhvFireSpitter),
		OBJECT(MODEL_BOWLING_BALL, -579, 3057, 6044, 0, 0, 0, 0x00000000, bhvFireSpitter),
		OBJECT(MODEL_BOWLING_BALL, 479, 3057, 5540, 0, 0, 0, 0x00000000, bhvFireSpitter),
		OBJECT(MODEL_BLUE_FLAME, 10100, 2268, 3291, 0, 0, 0, (2 << 24), bhvFlameBigger),
		OBJECT(MODEL_RED_FLAME, 15374, 2548, 7993, 0, 1, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, 15276, 2582, 6644, 0, 1, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, 11287, 2294, 6792, 0, 0, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, 11300, 2297, 7783, 0, 0, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, 3582, 3396, 1169, 0, 0, 0, 0x00000000, bhvFlameBigger),
		OBJECT(MODEL_RED_FLAME, 7137, 3396, 1169, 0, 0, 0, 0x00000000, bhvFlameBigger),
		OBJECT(MODEL_RED_FLAME, 5355, 3396, 1169, 0, 0, 0, 0x00000000, bhvFlameBigger),
		OBJECT(MODEL_RED_FLAME, 3636, 3396, -879, 0, 0, 0, 0x00000000, bhvFlameBigger),
		OBJECT(MODEL_RED_FLAME, 5381, 3396, -879, 0, 0, 0, 0x00000000, bhvFlameBigger),
		OBJECT(MODEL_RED_FLAME, 7262, 3396, -918, 0, 0, 0, 0x00000000, bhvFlameBigger),
		OBJECT(MODEL_BLUE_FLAME, 8908, 2270, 2102, 0, 0, 0, (1 << 24), bhvFlameBigger),
		OBJECT(MODEL_NONE, 9215, 1903, 29, 0, 0, 0, 0x00000000, bhvGoombaTripletSpawner),
		OBJECT(MODEL_NONE, 9777, 1950, 6941, 0, 0, 0, 0x00000000, bhvGoombaTripletSpawner),
		OBJECT(MODEL_LAVA_BULL, 2593, 1683, -1058, 0, -118, 0, (1 << 24), bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL, 2593, 1683, 1065, 0, 142, 0, (15 << 24), bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL, 4470, 1683, 1065, 0, 142, 0, (25 << 24), bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL, 6413, 1683, 1065, 0, 142, 0, (35 << 24), bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL, 4821, 1683, -1058, 0, -118, 0, (24 << 24), bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL, 6638, 1683, -1058, 0, -118, 0, (30 << 24), bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL, 3195, 1916, 8333, 0, 0, 0, 0x00000000, bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL, 1991, 1837, 8190, 0, 0, 0, (120 << 24), bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL, 2513, 1837, 9255, 0, 0, 0, (180 << 24), bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL, 1782, 2046, 7390, 0, 0, 0, (240 << 24), bhvlavaBull),
		OBJECT(MODEL_NONE, -17, 2022, 0, 0, 90, 0, 0, bhvInstantActiveWarp),
		OBJECT(MODEL_TRAIN, 2613, 1806, 85, 0, 0, 0, (80 << 16), bhvPlatformMooving),
		OBJECT(MODEL_NONE, 11150, 1607, -1300, 0, 0, 0, (90 << 16), bhvplatformmanager),
		OBJECT(MODEL_NONE, 12240, 1607, -1416, 0, 0, 0, (120 << 16), bhvplatformmanager),
		OBJECT(MODEL_NONE, 13443, 1607, -1416, 0, 0, 0, (180 << 16), bhvplatformmanager),
		OBJECT(MODEL_ROT_LAVA_PLAT, 15315, 3306, -325, 0, 0, 0, 0x00000000, bhvTurningPlatformLava),
		OBJECT(MODEL_PLAT_LAVA_MOVING, 6525, 1740, -4037, -3, -156, 6, 0x00000000, bhvStaticObject),
		OBJECT(MODEL_PLAT_LAVA_MOVING, 2254, 1740, -4370, -30, 0, 14, 0x00000000, bhvStaticObject),
		OBJECT(MODEL_PLAT_LAVA_MOVING, 1066, 1683, 3547, 38, 45, 0, 0x00000000, bhvStaticObject),
		OBJECT(MODEL_NONE, 15739, 1953, 7387, 0, 0, 0, (30 << 24) | (0x0B << 16) | (100 << 8) | (0), bhvWarp),
		OBJECT(MODEL_WHOMP, 340, 3057, 6536, 0, 0, 0, 0x00000000, bhvWhompKingBoss),
		TERRAIN(bob_area_1_collision),
		MACRO_OBJECTS(bob_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_WATER),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),
	FREE_LEVEL_POOL(),
	MARIO_POS(1, -8192, 0, 2000, 0),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};