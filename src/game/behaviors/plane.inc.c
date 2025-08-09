void plane_stick_control(void){
    s16 stickX = gPlayer1Controller->rawStickX;
    if (stickX < 10 && stickX > -10) stickX = 0;
    o->oMoveAngleRoll -= 10 * stickX;
}

void bhv_rotate_plane_loop(void){
    //display the control gif for a short time
    if(o->oTimer < 100) {
     //   render_plane_control_image(160, 160, 255, o->oTimer % 2);
    }

    plane_stick_control();
    if(o->oTimer == 10) {
        gMarioState->usedObj = o;
        gLakituState.mode = CAMERA_MODE_PLANE;
    }
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
    print_text(10,10,"CAILLOU");
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