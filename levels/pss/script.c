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
		WARP_NODE(0x15, LEVEL_LLL, 0x01, 16, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_SA, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(17, LEVEL_LLL, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_LLL, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -3927, -290, -312, 0, 90, 0, (0x0A << 16) | (191), bhvInstantActiveWarp),
		OBJECT(MODEL_NONE, 14755, -1124, -550, 0, 0, 0, (80 << 24) | (0x0B << 16), bhvWarp),
		OBJECT(MODEL_BLACK_BOBOMB, -3321, -303, -454, 0, 0, 0, 0x00000000, bhvBobomb),
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
		TERRAIN(pss_area_1_collision),
		MACRO_OBJECTS(pss_area_1_macro_objs),
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