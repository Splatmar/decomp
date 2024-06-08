//functionMoovingPlatform.inc.c

void bhv_moving_platform_init(void){
    o->oF4 =GET_BPARAM1(o->oBehParams); //chopper le b param de l'objet
    o->oForwardVel =10;
    o->oMoveAngleYaw = o->oFaceAngleYaw ;
}

void bhv_moving_platform_loop(void) {
    // Si boole == 0, l'objet se déplace vers la droite
    
    if (o->oTimer >= o->oF4){
        o->oMoveAngleYaw += 0x8000 ;
        o->oTimer =0;
        }
    
    
}