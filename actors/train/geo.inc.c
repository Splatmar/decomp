#include "src/game/envfx_snow.h"

const GeoLayout train_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, train_Cube_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, train_Cube_mesh_layer_5),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
