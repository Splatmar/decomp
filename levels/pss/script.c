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
#include "make_const_nonconst.h"
#include "levels/pss/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_pss_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _pss_segment_7SegmentRomStart, _pss_segment_7SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _mountain_yay0SegmentRomStart, _mountain_yay0SegmentRomEnd), 
	LOAD_MIO0(0x05, _group3_mio0SegmentRomStart, _group3_mio0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group3_geoSegmentRomStart, _group3_geoSegmentRomEnd),
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	LOAD_YAY0(0xb, _effect_yay0SegmentRomStart, _effect_yay0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_4), 
	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, pss_area_1),
		WARP_NODE(0x14, LEVEL_LLL, 0x02, 0x14, WARP_NO_CHECKPOINT),
		
		WARP_NODE(0x15, LEVEL_LLL, 0x03, 17, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_BOB, 0x01, 0x0B, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0C, LEVEL_SA, 0X01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0C, LEVEL_LLL, 0x03, 0x15, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_BREAKABLE_FLOOR_BOWSER, -147, 4226, 3519, 0, 0, 0, 0x00000000, bhvCrackedFloor),
		OBJECT(MODEL_PLAT_WITH_ID , 7621, -1417, -679, 0, 0, 0, 0x00020000, bhvPlatform_with_id),
		OBJECT(MODEL_NONE, 11471, -416, -470, 0, -90, 0, (16 << 16) | (64), bhvInstantActiveWarp),
		OBJECT(MODEL_GRILLECIRCLE, 6713, 3371, 5449, 0, -180, 0, 0x00000000, bhvRotatingPlatformGrille),
		OBJECT(MODEL_GRILLECIRCLE, 7240, 3817, 4410, 0, 0, 0, 0x00000000, bhvRotatingPlatformGrille),
		OBJECT(MODEL_NONE, 0, 0, -367, 0, 90, 0, (0x0B << 16) | (191), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 1675, 3497, 3349, 0, 0, 0, 0x01960200, bhvPoleGrabbing),
		OBJECT(MODEL_ASCENCEUR, 760, -322, -11583, 0, 0, 0, (10 << 24), bhvCustomElevator),
		OBJECT(MODEL_BREAKABLE_BOX, 11774, -737, -5130, 0, 0, 0, 0x00000000, bhvBreakableBox),
		OBJECT(MODEL_NONE, 2464, -419, -1524, 0, 0, 0, 0x00000000, bhvGoombaTripletSpawner),
		OBJECT(MODEL_NONE, 2464, -419, 531, 0, 0, 0, 0x00000000, bhvGoombaTripletSpawner),
		OBJECT(MODEL_GOOMBA, 716, -419, -4350, 0, 0, 0, 0x00000000, bhvGoomba),
		OBJECT(MODEL_LAVA_BULL, 894, -968, -8407, 0, 0, 0, 0x00000000, bhvlavaBull),
		OBJECT(MODEL_MOOVING_FLOOR, 3519, 2529, -458, 0, 0, 0, 0x00000000, bhvMoovingFloor),
		OBJECT(MODEL_POLEBOWSER, 4838, 1769, 6664, 0, 0, 0, 0x00000000, bhvStaticObject),
		OBJECT(MODEL_NONE, 12306, -685, -6647, 0, 0, 0, (40 << 16), bhvStaticObject),
		OBJECT(MODEL_NONE, 4836, 1778, 6654, 0, 0, 0, 0x00960200, bhvPoleGrabbing),
		OBJECT(MODEL_NONE, 5701, 2800, 6263, 0, 0, 0, 0x00990200, bhvPoleGrabbing),
		OBJECT(MODEL_NONE, 7159, 4535, 4460, 0, 0, 0, 0x00960200, bhvPoleGrabbing),
		OBJECT(MODEL_POLEBOWSER, 7159, 4529, 4460, 0, 0, 0, 0x00000000, bhvStaticObject),
		OBJECT(MODEL_POLEBOWSER, 5702, 2801, 6264, 0, 0, 0, 0x00000000, bhvStaticObject),
		OBJECT(MODEL_PURPLE_SWITCH, -152, 4161, 3515, 0, 90, 0, 0x00000000, bhvFloorSwitchHardcodedModel2),
		OBJECT(MODEL_PURPLE_SWITCH, 5789, 3195, 2119, 0, -180, 0, 0x00000000, bhvFloorSwitchHardcodedModel2),
		OBJECT(MODEL_ROTSTARE, 414, 59, 5435, 0, 0, 0, 0x00000000, bhvTurningPlatform),
		OBJECT(MODEL_ROTATING_BALL, 813, 4566, -5997, 0, 90, 0, (45 << 24), bhvSwingingBall),
		OBJECT(MODEL_ROTATING_BALL, 847, 4509, -7495, 0, 90, 0, (120 << 24), bhvSwingingBall),
		OBJECT(MODEL_ROTATING_BALL, 3307, 3922, -2969, 0, 90, 0, (9 << 24), bhvSwingingBall),
		OBJECT(MODEL_STATUE_BOWSER, 9941, -416, -1328, 0, -180, 0, 0x00000000, bhvPushableStatue),
		OBJECT(MODEL_STATUE_BOWSER, 9945, -416, 562, 0, 0, 0, 0x00000000, bhvPushableStatue),
		OBJECT(MODEL_ROTSTARE, 342, -332, 3894, 0, 0, 0, 0x00000000, bhvTurningPlatform),
		OBJECT(MODEL_NONE, 9881, -605, 637, 0, 0, 0, 0x10140000, bhvWarp),
		OBJECT(MODEL_NONE, 12294, -441, -493, 0, 0, 0, (40 << 24) | (0x15 << 16) | (100 << 8), bhvWarp),
		OBJECT(MODEL_NONE, 6677, 5319, 5460, 7, -105, -90, 0x00390000, bhvZipline),
		TERRAIN(pss_area_1_collision),
		MACRO_OBJECTS(pss_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_GRASS),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),
	AREA(2, pss_area_2),
		WARP_NODE(0x14, LEVEL_LLL, 0x01, 0x14, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 1487, 493, -1631, 0, 0, 0, 0x12140000, bhvWarp),
		OBJECT(MODEL_WOODEN_SIGNPOST, -774, 11, 900, 0, 117, 0, (45 << 24) | (45 << 16) | (45 << 8) | (45), bhvMessagePanel),
		TERRAIN(pss_area_2_collision),
		MACRO_OBJECTS(pss_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x01, SEQ_LEVEL_UNDERGROUND),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),
	AREA(3, pss_area_3),
		WARP_NODE(0x15, LEVEL_LLL, 0x01, 16, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_SA, 0x01, 0x0B, WARP_NO_CHECKPOINT),
		WARP_NODE(17, LEVEL_LLL, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_PSS, 0x03, 17, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -3927, -290, -312, 0, 90, 0, (17 << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 14755, -1124, -550, 0, 0, 0, (80 << 24) | (0x0B << 16), bhvWarp),
		OBJECT(MODEL_BLACK_BOBOMB, -3011, -303, -360, 0, 0, 0, 0x00000000, bhvBobomb),
		OBJECT(MODEL_FAKE_WALL, 10474, -305, -504, 0, 0, 0, 0x00000000, bhvFakeWall),
		OBJECT(MODEL_NONE, -378, -340, -345, 0, 90, 0, 0x00000000, bhvFlamethrower),
		OBJECT(MODEL_NONE, 629, -340, -1630, 0, 0, 0, 0x00000000, bhvFlamethrower),
		OBJECT(MODEL_NONE, 2615, -340, -1128, 0, 0, 0, 0x00000000, bhvFlamethrower),
		OBJECT(MODEL_NONE, 8812, -262, -931, 0, 0, 0, 0x00000000, bhvGoombaTripletSpawner),
		OBJECT(MODEL_NONE, 8613, -262, 43, 0, 0, 0, 0x00000000, bhvGoombaTripletSpawner),
		OBJECT(MODEL_KING_BOBOMB, 8687, -262, -428, 0, 0, 0, 0x00000000, bhvKingBobomb),
		OBJECT(MODEL_LAVA_BULL_BLUE, -2297, -591, 1351, 0, -90, 0, 0x00000000, bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL_BLUE, -2376, -549, 519, 0, -90, 0, 0x00000000, bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL_BLUE, -2366, -549, -271, 0, -90, 0, 0x00000000, bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL_BLUE, -2366, -549, -1136, 0, -90, 0, 0x00000000, bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL_BLUE, -2366, -549, -2005, 0, -90, 0, 0x00000000, bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL_BLUE, 3644, -591, -2084, 0, -90, 0, 0x00000000, bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL_BLUE, 3644, -591, -1215, 0, -90, 0, 0x00000000, bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL_BLUE, 3644, -591, -349, 0, -90, 0, 0x00000000, bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL_BLUE, 3635, -591, 441, 0, -90, 0, 0x00000000, bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL_BLUE, 3644, -591, 1272, 0, -90, 0, 0x00000000, bhvlavaBull),
		OBJECT(MODEL_NONE, -376, -353, 92, 0, 0, 0, 0x00000000, bhvFlamethrower),
		OBJECT(MODEL_WOODEN_SIGNPOST, -2874, -303, -1301, 0, -90, 0, (30 << 16), bhvMessagePanel),
		OBJECT(MODEL_NONE, -4725, -303, -335, 0, 90, 0, (60 << 24) | (0x15 << 16) | (100 << 8) | (191), bhvWarp),
		TERRAIN(pss_area_3_collision),
		MACRO_OBJECTS(pss_area_3_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_SNOW),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),
	FREE_LEVEL_POOL(),
	MARIO_POS(1, 0, 0, 0, 0),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};