void plane_stick_control(void){
    s16 stickX = gPlayer1Controller->rawStickX;

    // Deadzone
    if (stickX < 10 && stickX > -10) stickX = 0;

    // Contrôle du roll
    o->oMoveAngleRoll -= 10 * stickX;
}

void bhv_rotate_plane_loop(void){
    // Timer debug
   

    // Contrôle du plane
    plane_stick_control();

    // Active le mode plane au début
    if(o->oTimer == 10) {
        gMarioState->usedObj = o;
        gLakituState.mode = CAMERA_MODE_PLANE;
    }

    // Spawn du warp **une seule fois** après un certain temps (sécurisé)
    if(o->oTimer == 1000){  // exemple : frame 1000
        struct Object *warpObj = spawn_object_abs_with_rot(
            gMarioObject, 0, MODEL_NONE, bhvInstantActiveWarp,
            gMarioState->pos[0], gMarioState->pos[1] + 20, gMarioState->pos[2],
            0, 0, 0
        );
        warpObj->oBehParams = (0x0A << 16); // doit correspondre au WARP_NODE
    }

    // Toujours garder le dialogue (optionnel)
    set_mario_npc_dialog(MARIO_DIALOG_LOOK_FRONT);
}


#define TIMER_INDEX 3

s32 sObstacleCoordList[][4] = {
    {1000, 100, -20 ,60}, // caillou 1
    {1000, 1100, -20 ,80}, // caillou 2
    {1000, 100, -20,}, // caillou 3
    {-1000, 1400, -20 ,1}, // {x, y, z, timer}
    {-1000, 500, -20 ,10},
    {300, -900, -20 ,45},
    {-300, -900, -20 ,1},
    {1000, 200, -20 ,140},
    {1000, -800, -20 ,5},
    {-1000, 0, -20 ,2},
    {1000, 900, -20 ,110},
    {1000, 1000, -20 ,100},
    {-1000, 0, -20 ,100},
    {-1000, 1400, -20 ,190},
    {-1000, 1600, -20 ,220},
    {1000, 1700, -20 ,350},
};

void bhv_obstacle_manager_init(void) {
    o->oF4 = 0; // index pour parcourir le tableau
}

void bhv_obstacle_manager_loop(void) {
    s32 timer = sObstacleCoordList[o->oF4][TIMER_INDEX];
    if(o->oTimer >= timer) {
        s32 x = sObstacleCoordList[o->oF4][0];
        s32 y = sObstacleCoordList[o->oF4][1];
        s32 z = sObstacleCoordList[o->oF4][2];
        spawn_object_abs_with_rot(o, 0, MODEL_FIREBALL, bhvFireball, x, y, 8000, 0, 0, 0);
        o->oTimer = 0;
        o->oF4++;
    }
}
static Vec3f lava_positions[5] = {   
    {7500, -700, 0},
    {7500, -700,  -400},
    {7500, -700, 400},
    {7500, -700, -200},
    {7500, -700, 200},
};

void spawn_multiple_fireballs(void) {
    s32 SPAWN_INTERVAL = 150;

  if (o->oTimer >= SPAWN_INTERVAL) {
        int nextIndex = random_u16() % 5;
       Vec3f pos;
       vec3f_copy(pos,lava_positions[nextIndex]); // pointeur vers la position
        spawn_object_abs_with_rot(o, 0, MODEL_LAVA_PIQUE,  bhvLavaWave, pos[0], pos[1], pos[2], 0, 0, 0);
        o->oTimer = 0;
    }
}
void bhv_lavaBulle_loop(void) {
    if (o->oTimer == 0 && o->oAction == 0) {
        o->o10C = (random_u16() % 31); // délai aléatoire 0-30 frames

        // mémoriser position et rotation initiales
        o->oF4 = o->oPosX;
        o->o100 = o->oPosY;
        o->oF8 = o->oPosZ;

        o->oFC = o->oFaceAnglePitch;
        o->o104 = o->oFaceAngleYaw;
        o->o110 = o->oFaceAngleRoll;
    }

    // Phase 0 : attente du délai
    if (o->oAction == 0) {
        if (o->oTimer > o->o10C) {
            o->oAction++;
            o->oTimer = 0;  // reset timer au début de l'action 1
        }
        return; // on ne fait rien d'autre tant que le délai n'est pas passé
    }

    // Ici, on est dans les phases 1 à 4, on peut utiliser o->oTimer directement

    switch (o->oAction) {
        case 1:
            o->oPosY += 45;
            if (o->oTimer > 11) {
                o->oAction++;
                o->oTimer = 0;
            }
            break;

        case 2:
            o->oFaceAnglePitch += 2020;
            o->oPosY += 14;
            if (o->oTimer >= 7) {
                o->oAction++;
                o->oTimer = 0;
            }
            break;

        case 3:
            o->oFaceAnglePitch += 2020;
            o->oPosY -= 14;
            if (o->oTimer >= 7) {
                o->oAction++;
                o->oTimer = 0;
            }
            break;

        case 4:
            o->oPosY -= 40;
            if (o->oTimer > 75) {
                o->oAction = 0;
                o->oTimer = 0;

                // reset position initiale
                o->oPosX = o->oF4;
                o->oPosY = o->o100;
                o->oPosZ = o->oF8;

                // reset rotation initiale
                o->oFaceAnglePitch = o->oFC;
                o->oFaceAngleYaw = o->o104;
                o->oFaceAngleRoll = o->o110;

                // reset vitesse
                o->oVelX = 0;
                o->oVelY = 0;
                o->oVelZ = 0;
            }
            break;
    }
}

void bhv_lavawave_loop(void){
    switch(o->oAction){
        case 0 :
        o->oPosY += 12;
        o->oPosX -= 5;
        if(o->oTimer > 45){
            o->oAction++ ;
        }
        break;
        case 1 :
        o->oPosX -= 15;
        if(o->oTimer > 200){
            o->oAction++ ;
        }
        break;
        case 2:
        o->oPosY -= 5;
        o->oPosX -= 5;
        if(o->oTimer > 100){
            obj_mark_for_deletion(o);
        }
        break;
    }
    
}

void bhv_gif_loop(void){
    s32 time = o->oBehParams2ndByte ;
    s32 nb_img = GET_BPARAM1(o->oBehParams);
    if(o->oTimer >= time ){
        o->oTimer=0 ;
        o->oAnimState++;
        if(o->oAnimState > nb_img -1){
            o->oAnimState =0 ;
        }
    }
}   
void bhv_fireball_loop(void) {
    o->oPosZ -= 100.0f;

    
}

void bhv_move_plan(void){   
     if (o->oTimer%50 ==0 && o->oF4==0){
        o->oPosZ-=10.0f ;
        o->oF4=1;
        o->oTimer=0;
        }
    if (o->oTimer%50 ==0 && o->oF4==1){
        o->oPosZ+=10.0f ;
        o->oF4=0;
        o->oTimer=0;
        }
}