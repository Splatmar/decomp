void plane_stick_control(void){
    s16 stickX = gPlayer1Controller->rawStickX;

    // Deadzone
    if (stickX < 10 && stickX > -10) stickX = 0;

    // Contrôle du roll
    o->oMoveAngleRoll -= 10 * stickX;
}

#define WING_HITBOXES_OFFSET 320
#define HITBOXES_PER_WING 6
#define HITBOXES_INCREMENT_OFFSET_TO_PLANE_WING 55
void bhv_plane_init(void) {
    
    // left wing hitboxes
    for(int i = 1; i <= HITBOXES_PER_WING; i++) {
        struct Object *leftHitbox = spawn_object_relative(WING_HITBOXES_OFFSET * i, 0, 0, 0, o, MODEL_NONE, bhvPlaneHitboxes);
        leftHitbox->oF4 =  (HITBOXES_INCREMENT_OFFSET_TO_PLANE_WING * i);
    }

    // right wing hitboxs
    for(int i = 1; i <= HITBOXES_PER_WING; i++) {
        struct Object *rightHitbox = spawn_object_relative(-WING_HITBOXES_OFFSET * i, 0, 0, 0, o, MODEL_NONE, bhvPlaneHitboxes);
        rightHitbox->oF4 = (HITBOXES_INCREMENT_OFFSET_TO_PLANE_WING * i);
    }
}

void bhv_plane_hitboxes_loop(void) {
    s32 offsetFromAnchor = o->oBehParams2ndByte;
    s32 offsetToMatchWingShape = o->oF4;
    f32 yOffset = (offsetFromAnchor * sins(o->parentObj->oFaceAngleRoll));
    f32 xOffset = (offsetFromAnchor * coss(o->parentObj->oFaceAngleRoll));
    
    o->oPosX = o->parentObj->oPosX + xOffset - (offsetToMatchWingShape * sins(o->parentObj->oFaceAngleRoll));
    o->oPosY = o->parentObj->oPosY + yOffset + (offsetToMatchWingShape * coss(o->parentObj->oFaceAngleRoll));
    
    struct Object *meteorite = cur_obj_nearest_object_with_behavior(bhvFireball);
    if(meteorite != NULL && dist_between_objects(o, meteorite) < 450 && o->parentObj->oF8) {
    gMarioState->health -= 500;
    set_camera_shake_from_hit(SHAKE_LARGE_DAMAGE);
    play_sound(SOUND_MARIO_ATTACKED, gGlobalSoundSource);
    
    if (gMarioState->health <= 500) {
        gMarioState->health = 0;
        set_mario_action(gMarioState, ACT_DEATH_ON_BACK, 0);
    }

    // the plane cant take damage for the next 30 frames 
    o->parentObj->oF8 = 0;
    o->parentObj->oF4 = 30;
}

    


}

void bhv_rotate_plane_loop(void) {
    gMarioState->pos[0] = 0000.0f; // X
gMarioState->pos[1] = 0160.0f; // Y
gMarioState->pos[2] = 000.0f; // Z

gMarioState->marioObj->oPosX = gMarioState->pos[0];
gMarioState->marioObj->oPosY = gMarioState->pos[1];
gMarioState->marioObj->oPosZ = gMarioState->pos[2];

    // Timer debug
   

    // Contrôle du plane
    plane_stick_control();

    // Active le mode plane au début
    if(o->oTimer == 10) {
        gMarioState->usedObj = o;
        gLakituState.mode = CAMERA_MODE_PLANE;
    }

    // Spawn du warp **une seule fois** après un certain temps (sécurisé)
    if(o->oTimer == 300){  // exemple : frame 1000 
        initiate_warp(LEVEL_BOB & 0x7F, 1, 0x0A, WARP_FLAGS_NONE);
        play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 0x10, 0, 0, 0);
        level_set_transition(0x10, NULL);
    }

    // Toujours garder le dialogue (optionnel)
    set_mario_npc_dialog(MARIO_DIALOG_LOOK_FRONT);

    // if can't take damage and cooldown over, reset the damage
    if(o->oF8 == 0 && o->oF4 == 0) {
        o->oF8 = 1;
    } else {
        o->oF4--;
    }
}


#define TIMER_INDEX 3

s32 sObstacleCoordList[][4] = {
    {1000, 100, -20 ,60},   // caillou 1
    {1000, 1100, -20 ,80},  // caillou 2
    {1000, 100, -20,1},      // caillou 3
    {-1000, 1400, -20 ,1},  // {x, y, z, timer entre chaque boule } 
    {-1000, 500, -20 ,10},
    {300, -900, -20 ,45},
    {-300, -900, -20 ,1},
    {1000, 200, -20 ,140},
    {1000, -800, -20 ,5},
    {-1000, 0, -20 ,2},

    // Ajout des 10 suivants (Y proches des tiens, timers <= 40)
    {1000, 900, -20 ,15},
    {0, 1000, -20 ,20},
    {1000, 1100, -20 ,25},
    {-1000, 1400, -20 ,30},
    {1000, 0, -20 ,5},
    {1000, -900, -20 ,35},
    {-1000, 1700, -20 ,40},
    {0, 2000, -20 ,12},
    {-1000, 500, -20 ,18},
    {1000, 800, -20 ,22},
    {-1000, 0, -20 ,28},

    // 10 nouveaux
    {1000, 1600, -20 ,8},
    {-1000, 100, -20 ,14},
    {0, -900, -20 ,20},
    {1000, 2000, -20 ,26},
    {-1000, -800, -20 ,32},
    {1000, 1100, -20 ,10},
    {-1000, 500, -20 ,18},
    {0, 1400, -20 ,24},
    {1000, 1700, -20 ,30},
    {-1000, 0, -20 ,36},
    {1000, 0, -20 ,36},
        // Suite pour atteindre ~1 minute
        {1000, 900, -20 ,33},
    {-1000, 100, -20 ,25},
    {0, -900, -20 ,21},
    {1000, 1400, -20 ,43},
    {-1000, 200, -20 ,18},

    {1000, 500, -20 ,31},
    {-1000, 800, -20 ,38},
    {0, 1700, -20 ,29},
    {1000, 1100, -20 ,23},
    {-1000, 0, -20 ,35},

    {1000, -800, -20 ,15},
    {0, 1600, -20 ,41},
    {-1000, 2000, -20 ,28},
    {1000, 1000, -20 ,21},
    {-1000, -1500, -20 ,43},

    {0, -2000, -20 ,17},
    {1000, 1400, -20 ,39},
    {-1000, -900, -20 ,25},
    {1000, 0, -20 ,33},
    {0, 1400, -20 ,31},

    {-1000, 100, -20 ,21},
    {1000, 1700, -20 ,43},
    {0, -1500, -20 ,27},
    {-1000, 900, -20 ,35},
    {1000, 1100, -20 ,29},


};





void bhv_obstacle_manager_init(void) {
    o->oF4 = 0; // index pour parcourir le tableau
}
void bhv_spawn_manager_loop(void) {
    // Vérifie si Bowser existe encore
    struct Object *bowser = cur_obj_nearest_object_with_behavior(bhvBowserCustom);

    if (bowser == NULL || bowser->oHealth <= 0) {
        // Si Bowser est mort ou introuvable → supprime le manager
        obj_mark_for_deletion(o);
        return;
    }

    // Toutes les 120 frames → spawn
    if (o->oTimer % 120 == 0) {
        // Offset aléatoire pour éviter spawn direct sur Mario
        f32 offsetX = (random_float() * 200.0f) - 100.0f; // [-100, +100]
        f32 offsetZ = (random_float() * 200.0f) - 100.0f; // [-100, +100]

        // Position relative à Mario
        f32 spawnX = gMarioObject->oPosX + offsetX;
        f32 spawnY = 4000; // même hauteur que le manager
        f32 spawnZ = gMarioObject->oPosZ + offsetZ;

        // Spawn de l’objet cible
        spawn_object_abs_with_rot(
            o, 0,
            MODEL_PLATFORM,           // modèle
            bhvBowserMoovingForward,  // comportement
            spawnX, spawnY, spawnZ,
            0, 0, 0                   // orientation
        );
    }
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
    {7500, -700, -400},
    {7500, -700, 400},
    {7500, -700, -200},
    {7500, -700, 200},
};

void spawn_multiple_fireballs(void) {
    s32 SPAWN_INTERVAL = 150;
    static int lastIndex = -1; // pour stocker la dernière position utilisée

    if (o->oTimer >= SPAWN_INTERVAL) {
        int nextIndex;
        do {
            nextIndex = random_u16() % 5;
        } while (nextIndex == lastIndex); // on évite de prendre le même deux fois de suite

        Vec3f pos;
        vec3f_copy(pos, lava_positions[nextIndex]);
        spawn_object_abs_with_rot(o, 0, MODEL_LAVA_PIQUE, bhvLavaWave,
                                  pos[0], 1350, pos[2], 0, 0, 0);

        lastIndex = nextIndex; // mémorise le dernier
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
void bhvFireball_bowser_loop(void) {
    // Avancer selon l'angle
    o->oPosX += sins(o->oMoveAngleYaw) * 20.0f;
    o->oPosZ += coss(o->oMoveAngleYaw) * 20.0f;
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