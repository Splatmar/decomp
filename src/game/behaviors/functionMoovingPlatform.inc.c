//functionMoovingPlatform.inc.c

void bhv_moving_platform_init(void){
    
    o->oF4 =GET_BPARAM1(o->oBehParams); //chopper les b param de l'objet , distance
    o->oF8 =GET_BPARAM2(o->oBehParams); //  vitesse
    o->o104 =GET_BPARAM3(o->oBehParams); // vitesse y en fonction du bparam2
    o->oFC = 0;
    o->o100 =0;

    if ( (o->oF8 == 0) && (o->oFC==0) ){ // condition pour platform avec allé retour uniquement .
    o->oForwardVel =10;
    o->oMoveAngleYaw = o->oFaceAngleYaw ;   
    }
    
    
}

void bhv_moving_platform_loop(void) {
    // Si boole == 0, l'objet se déplace vers l'avant
    
    if (o->oTimer >= o->oF4){
        o->oMoveAngleYaw += 0x8000 ;
        o->oTimer =0;
        }
    
    
}

void bhv_moving_forward_loop(void){
   if (o->oDistanceToMario <=2500  ){
        
          o->o100 = 1 ;
    }
    else if (o->o100 !=1){
        o->oTimer=0;
    }
   
   if ( o->o100 == 1){ 
    if (o->oTimer >= (o->oF4)*4 ){
                 o->oForwardVel =0;
                 
        if (o->oFC == 0){
            cur_obj_play_sound_2(SOUND_OBJ_BOWSER_WALK);
            set_camera_shake_from_hit(SHAKE_LARGE_DAMAGE);
            o->oFC =1; // avoir l'effet qu'une fois 
             
            
        }
        

     }
     else{
        o->oForwardVel = o->oF8;
         o->oPosY -= o->oForwardVel * (o->o104 + 0.5) ;
     }
   }
    }

void scale_up_animation() {
    // Vérifier si Mario est assez proche et si l'animation n'a pas déjà commencé
    if (o->oDistanceToMario < 150  && o->oF8 == 0) {
        o->oTimer = 0;
        o->oF8 = 1;
        cur_obj_scale(1);
    }
    
    // Réinitialiser l'animation si Mario s'éloigne
    if (o->oDistanceToMario > 400) {
        o->oF8 = 0;
        cur_obj_scale(1);
    }
    
    // Si l'animation est en cours
    if (o->oF8 == 1) {
           if (o->oTimer < 5) {
        cur_obj_scale(1.0 - 0.05 * o->oTimer); // Rétrécissement 
           }
           else {
                cur_obj_scale(1);
                cur_obj_play_sound_2(SOUND_OBJ_WATER_BOMB_BOUNCING);
           }
        
            
        
    }
}