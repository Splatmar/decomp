#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "config.h"
#include "macros.h"
#include "types.h"
#include "game/ingame_menu.h"
#include "game/puppyprint.h"

#include "make_const_nonconst.h"

//Graphics data gif
ALIGNED8 u8 plane_control_gif_images[2][2048] = {
     {
     #include "textures/gif/stick_droit.rgba16.inc.c"
     },
     {
     #include "textures/gif/stick_gauche.rgba16.inc.c"
     },
};

void render_plane_control_image(u16 x, u16 y, u8 alpha, u8 index) {

    //gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, alpha);
    //create_dl_translation_matrix(MENU_MTX_PUSH, x, y, 0);
//
	//gDPPipeSync(gDisplayListHead++);
    //gDPSetTextureFilter(gDisplayListHead++,G_TF_POINT);
	//gDPSetTextureImage(gDisplayListHead++,G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, &plane_control_gif_images[index]);
	//gDPSetTile(gDisplayListHead++,G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0);
	//gDPLoadBlock(gDisplayListHead++,7, 0, 0, 1023, 256);
//
    ////gSPDisplayList(gDisplayListHead++,ability_ability_mesh);
    //
    //gDPSetTextureFilter(gDisplayListHead++,G_TF_BILERP);
    //gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}