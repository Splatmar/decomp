
void bhv_small_jumping_chain_chomp_update(void) {
    s16 collisionFlags;
    f32 floorHeight;

    cur_obj_update_floor_and_walls();
    o->oVelY -= o->oGravity;

    switch(o->oAction){
        case 0: //wait on ground
            o->oForwardVel = 0.0f;
            o->oVelY = 0.0f;
            if(o->oTimer > 10){
                if(o->oDistanceToMario < 1000) 
                    o->oMoveAngleYaw = o->oAngleToMario;
                else 
                    o->oMoveAngleYaw = o->oAngleToMario + random_sign() * 0x2000;
                cur_obj_play_sound_2(SOUND_GENERAL_CHAIN_CHOMP1);
                o->oForwardVel = 20.0f;
                o->oVelY = 30.0f;
                o->oAction++;
            }
            break;
        case 1: //jump
            collisionFlags = object_simple_step(o);
            if (collisionFlags == OBJ_COL_FLAG_GROUNDED) {
                o->oAction--;
            }
            break;
    }
    
    //print_text_fmt_float(180, 180, "ACTN %f", o->oDistanceToMario);
    //print_text_fmt_float(180, 160, "VELY %f", o->oVelY);
    //print_text_fmt_float(180, 140, "FORW %f", o->oForwardVel);
    //print_text_fmt_float(180, 100, "POSY %f", o->oPosY);
}