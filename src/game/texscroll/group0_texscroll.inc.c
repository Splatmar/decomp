#include "actors/group0.h"
#include "actors/fireball/texscroll.inc.c"
#include "actors/mooving_floor/texscroll.inc.c"
#include "actors/lava_pique/texscroll.inc.c"
void scroll_textures_group0() {
	scroll_actor_geo_fireball();
		scroll_actor_geo_mooving_floor();
	scroll_actor_geo_lava_pique();
}
