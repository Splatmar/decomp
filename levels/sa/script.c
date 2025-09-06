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
#include "levels/sa/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_sa_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _sa_segment_7SegmentRomStart, _sa_segment_7SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _inside_yay0SegmentRomStart, _inside_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0A, _cloud_floor_skybox_yay0SegmentRomStart, _cloud_floor_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0B, _effect_yay0SegmentRomStart, _effect_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group4_yay0SegmentRomStart, _group4_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group4_geoSegmentRomStart, _group4_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group12_yay0SegmentRomStart, _group12_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group12_geoSegmentRomStart, _group12_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_13), 
	LOAD_MODEL_FROM_GEO(MODEL_FIREBALL, fireball_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_FALLING_GRILL, falling_grill_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_ROTATING_BALL, rotatingball_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BOWSER_LAVA, lava_bowser_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_PLATFORM, turning_platform_geo), 
	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, sa_area_1),
		MARIO_POS(0x01, 0, -974, 685, 3540),
		OBJECT(MODEL_BOWSER, 0, -649, 0, 0, 0, 0, 0x00000000, bhvBowserCustom),
		OBJECT(MODEL_EXCLAMATION_BOX, 4324, 1597, -1851, 0, 0, 0, (15 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, 3570, 611, 2891, 0, 0, 0, (15 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -4679, 609, 145, 0, 0, 0, (15 << 16), bhvExclamationBox),
		OBJECT(MODEL_FALLING_GRILL, -4224, 647, -2068, 0, -21, 0, 0x00000000, bhv_falling_grill),
		OBJECT(MODEL_FALLING_GRILL, -3897, 760, -2852, 0, -45, 0, 0x00000000, bhv_falling_grill),
		OBJECT(MODEL_FALLING_GRILL, -3268, 882, -3542, 0, -45, 0, 0x00000000, bhv_falling_grill),
		OBJECT(MODEL_BOWSER_LAVA, 0, 0, -8, 0, 0, 0, 0x00000000, bhvBowserMoovingFloor),
		OBJECT(MODEL_NONE, 2049, 442, -4059, 0, 0, 0, (40 << 16), bhvPoleGrabbing),
		OBJECT(MODEL_NONE, -2147, 481, -3986, 0, 0, 0, (40 << 16), bhvPoleGrabbing),
		OBJECT(MODEL_ROTATING_BALL, 932, 1983, 3771, 0, 90, 0, 0x00000000, bhvSwingingBall),
		TERRAIN(sa_area_1_collision),
		MACRO_OBJECTS(sa_area_1_macro_objs),
		STOP_MUSIC(0),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),
	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, -974, 685, 3540),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};