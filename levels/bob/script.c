#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"
#include "actors/lava_bull/geo_header.h"
#include "actors/lava_pique/geo_header.h"
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
	LOAD_YAY0(0x05, _group3_yay0SegmentRomStart, _group3_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group3_geoSegmentRomStart, _group3_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group14_yay0SegmentRomStart, _group14_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group14_geoSegmentRomStart, _group14_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	LOAD_MIO0(0x7, _bob_segment_7SegmentRomStart, _bob_segment_7SegmentRomEnd), 
	LOAD_MIO0(0xa, _bitfs_skybox_mio0SegmentRomStart, _bitfs_skybox_mio0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_4), 
	JUMP_LINK(script_func_global_15), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_BUBBLY_TREE, bubbly_tree_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_CHAIN_CHOMP_GATE, bob_geo_000440), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_SEESAW_PLATFORM, bob_geo_000458), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_BARS_GRILLS, bob_geo_000470), 
	LOAD_MODEL_FROM_GEO(MODEL_TRAIN, train_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_LAVA_PIQUE, lava_pique_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_LAVA_BULL, lava_bull_geo), 
	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, bob_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 3734, 72, 0, 0, 0, 0, 0x00000000, bhvLavaWaveSpawner),
		MARIO_POS(0x01, 0, -17, 4, 0),
		OBJECT(MODEL_RED_FLAME, 3582, 1378, 1169, 0, 0, 0, 0x00000000, bhvFlameBigger),
		OBJECT(MODEL_RED_FLAME, 7137, 1378, 1169, 0, 0, 0, 0x00000000, bhvFlameBigger),
		OBJECT(MODEL_RED_FLAME, 5355, 1378, 1169, 0, 0, 0, 0x00000000, bhvFlameBigger),
		OBJECT(MODEL_RED_FLAME, 3636, 1378, -879, 0, 0, 0, 0x00000000, bhvFlameBigger),
		OBJECT(MODEL_RED_FLAME, 5381, 1378, -879, 0, 0, 0, 0x00000000, bhvFlameBigger),
		OBJECT(MODEL_RED_FLAME, 7262, 1378, -918, 0, 0, 0, 0x00000000, bhvFlameBigger),
		OBJECT(MODEL_LAVA_BULL, 2593, -335, -1058, 0, -118, 0, (1 << 24), bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL, 2593, -335, 1065, 0, 142, 0, (15 << 24), bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL, 4470, -335, 1065, 0, 142, 0, (25 << 24), bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL, 6413, -335, 1065, 0, 142, 0, (35 << 24), bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL, 4821, -335, -1058, 0, -118, 0, (24 << 24), bhvlavaBull),
		OBJECT(MODEL_LAVA_BULL, 6638, -335, -1058, 0, -118, 0, (30 << 24), bhvlavaBull),
		OBJECT(MODEL_RED_FLAME, 15445, 671, 6403, 0, 0, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_RED_FLAME, 15445, 671, 7947, 0, 0, 0, 0x00000000, bhvFlame),
		OBJECT(MODEL_TRAIN, 2613, -211, 85, 0, 0, 0, (80 << 16), bhvPlatformMooving),
		TERRAIN(bob_area_1_collision),
		MACRO_OBJECTS(bob_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_GRASS),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),
	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, -17, 4, 0),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};