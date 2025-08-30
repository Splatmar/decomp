#include "src/game/envfx_snow.h"

const GeoLayout mooving_floor_geo[] = {
	GEO_CULLING_RADIUS(3000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, mooving_floor_mooving_floor_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
