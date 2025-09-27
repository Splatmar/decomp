/*
void scroll_titre_titlescreen_mesh_vtx_4() {
    int i = 0;
    int count = 242;
    int width = 32 * 0x20;

    static int currentX = 0;
    int deltaX;
    Vtx *vertices = segmented_to_virtual(titre_titlescreen_mesh_vtx_4);

    deltaX = (int)(0.20000000298023224 * (float)0x20) % width;

    if (absi(currentX) > width) {
        deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
    }

    for (i = 0; i < count; i++) {
        vertices[i].n.tc[0] += deltaX;
    }
    currentX += deltaX;
}

void scroll_actor_dl_titre() {
    scroll_titre_titlescreen_mesh_vtx_4();
};*/