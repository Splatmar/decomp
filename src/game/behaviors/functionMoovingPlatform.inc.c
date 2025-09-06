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
void platform_move_forward(void) {
    

    // Détecte Mario proche
    if (o->oDistanceToMario <= 100 && o->oF4 == 0) {
        o->oF4 = 1;
        o->oTimer = 0;
        o->oVelY = 0.0f; // initialise la vitesse verticale
    }

    // Si déclenché, avance et incrémente le timer
    if (o->oF4 == 1) {
        o->oTimer++;

        // Avance horizontalement tant que le timer < 300
        if (o->oTimer < 1350) {
            o->oPosX += 7;
        }

        // Après 300 frames, commence à descendre progressivement
        if (o->oTimer >= 1350) {
            // applique une vitesse verticale progressive
            o->oVelY -= 0.5f;  // accélération vers le bas
            if (o->oVelY < -1.5f) o->oVelY = -1.5f; // limite vitesse max
            o->oPosY += o->oVelY;
        }
        if(o->oTimer >=1900){
            obj_mark_for_deletion(o);
        }
    }
}
void bhv_fake_meteorite_loop(void) {
    // Descend progressivement
    o->oPosY -= 70.0f;

    // Si en dessous d'une certaine hauteur, se supprime
    if (o->oPosY < -100.0f) {
        obj_mark_for_deletion(o);
    }
}
void bhv_fake_meteorite_spawn(void) {
    // Toutes les 30 frames
    if (o->oTimer % 60 == 0) {
        s16 randX, randZ;

        // X aléatoire en dehors du carré [-8500, +8500] mais pas trop loin
        if (random_float() < 0.5f) {
            // Partie gauche [-9000, -8500]
            randX = (random_u16() % 500) - 9000; 
        } else {
            // Partie droite [8500, 9000]
            randX = (random_u16() % 500) + 8500;
        }

        // Z aléatoire en dehors du carré [-8500, +8500] mais pas trop loin
        if (random_float() < 0.5f) {
            // Partie avant [-9000, -8500]
            randZ = (random_u16() % 500) - 9000;
        } else {
            // Partie arrière [8500, 9000]
            randZ = (random_u16() % 500) + 8500;
        }

        // Position absolue du spawn, hauteur 2000
        f32 spawnX = o->oPosX + randX;
        f32 spawnY = o->oPosY + 2000.0f;
        f32 spawnZ = o->oPosZ + randZ;

        // Spawn du fake météorite
        spawn_object_abs_with_rot(
            o, 0,
            MODEL_PLATFORM,       // modèle
            bhvFakeMeterorite,    // comportement
            spawnX, spawnY, spawnZ,
            0, 0, 0               // orientation
        );
    }
}









void bhv_moving_down_until_floor_bowser(void) {
    // Vérifie si l’objet est dans la zone spéciale (cercle de rayon 10000)
    f32 dx = o->oPosX;
    f32 dz = o->oPosZ;
    f32 dist2 = dx*dx + dz*dz; // distance² à l’origine
    f32 radius = 500.0f;

    // Mode spécial : dans la zone → descente 400 frames puis delete
    if (dist2 <= radius * radius) {
        if (o->oTimer < 400) {
            o->oPosY -= 60.5f;
        } else {
            obj_mark_for_deletion(o);
        }
        return; // on ne touche pas au reste
    }

    // Sinon → comportement normal (hors du cercle)
    switch (o->oAction) {
        case 0: // fall
            o->oPosY -= 60.5f;
            if (o->oPosY <= find_floor_height(o->oPosX, o->oPosY, o->oPosZ)) {
                o->oAction++;
            }
            break;

        case 1: // hit the ground
            cur_obj_play_sound_2(SOUND_OBJ_BOWSER_WALK);
            set_camera_shake_from_hit(SHAKE_LARGE_DAMAGE);
            o->oAction++;
            break;

        case 2: // wait on ground
            if (o->oTimer > 3000) {
                obj_mark_for_deletion(o);
            }
            break;
    }
}



void bhv_moving_down_until_floor(void) {
    switch (o->oAction) {
        case 0: //wait for mario
            if (o->oDistanceToMario <= 2500) {
                o->oAction++;
            }
            break;
    
        case 1 : // fall
            // apply falling speed to posY, then if the oPosY is below the ground, then stop
            o->oPosY -= 60.5;
            if (o->oPosY <= find_floor_height(o->oPosX, o->oPosY, o->oPosZ)){
                o->oAction++;
            }
            break;
        case 2 : //hit the ground
            cur_obj_play_sound_2(SOUND_OBJ_BOWSER_WALK);
            set_camera_shake_from_hit(SHAKE_LARGE_DAMAGE);
            o->oAction++;
            break;

        case 3 : //wait on ground, not moving
            
            break;
    }
}
void scale_up_animation() {
    // Vérifier si Mario est assez proche et si l'animation n'a pas déjà commencé
    if (o->oDistanceToMario < 150 && o->oF8 == 0) {
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