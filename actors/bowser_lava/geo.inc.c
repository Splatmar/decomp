#include "src/game/envfx_snow.h"

const GeoLayout bowser_lava_geo[] = {
	GEO_CULLING_RADIUS(3000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bowser_lava_Cube_002_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
