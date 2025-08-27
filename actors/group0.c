#include <ultra64.h>
#include "sm64.h"
#include "surface_terrains.h"
#include "geo_commands.h"

#include "make_const_nonconst.h"

// Note: This bin does not use bin IDs, unlike the other segmented bins.
#include "mario/model.inc.c"

#include "bubble/model.inc.c"

#include "walk_smoke/model.inc.c"

#include "burn_smoke/model.inc.c"

#include "small_water_splash/model.inc.c"

#include "water_wave/model.inc.c"

#include "sparkle/model.inc.c"

#include "water_splash/model.inc.c"

#include "white_particle_small/model.inc.c"

#include "sparkle_animation/model.inc.c"

#ifdef S2DEX_TEXT_ENGINE
#include "src/s2d_engine/s2d_config.h"
#include FONT_C_FILE
#endif

#include "turning_platform/collision.inc.c"
#include "turning_platform/model.inc.c"
#include "champi/collision.inc.c"
#include "champi/model.inc.c"
#include "plane/model.inc.c"
#include "fireball/model.inc.c"
#include "fireball/collision.inc.c"
#include "train/model.inc.c"
#include "train/collision.inc.c"

#include "lava_pique/model.inc.c"
#include "lava_pique/collision.inc.c"
#include "lava_bull/collision.inc.c"
#include "lava_bull/model.inc.c"
#include "grille/collision.inc.c"
#include "grille/model.inc.c"
#include "rotatingball/collision.inc.c"
#include "rotatingball/model.inc.c"
#include "ascenceur/collision.inc.c"
#include "ascenceur/model.inc.c"
#include "polebowser/collision.inc.c"
#include "polebowser/model.inc.c"
#include "rotstares/collision.inc.c"
#include "rotstares/model.inc.c"
#include "grillecircle/collision.inc.c"
#include "grillecircle/model.inc.c"
#include "platform_with_id/collision.inc.c"
#include "platform_with_id/model.inc.c"