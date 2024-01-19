// spawn_star.inc.c

static struct ObjectHitbox sCollectStarHitbox = {
    /* interactType:      */ INTERACT_STAR_OR_KEY,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 80,
    /* height:            */ 50,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

void bhv_collect_star_init(void) {
    u8 starId = GET_BPARAM1(o->oBehParams);
#ifdef GLOBAL_STAR_IDS
    u8 currentLevelStarFlags = save_file_get_star_flags((gCurrSaveFileNum - 1), COURSE_NUM_TO_INDEX(starId / 7));
    if (currentLevelStarFlags & (1 << (starId % 7))) {
#else
    u8 currentLevelStarFlags = save_file_get_star_flags((gCurrSaveFileNum - 1), COURSE_NUM_TO_INDEX(gCurrCourseNum));
    if (currentLevelStarFlags & (1 << starId)) {
#endif
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_TRANSPARENT_STAR];
    } else {
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_STAR];
    }

    obj_set_hitbox(o, &sCollectStarHitbox);
}

void bhv_collect_star_loop(void) {
    o->oFaceAngleYaw += 0x800;

    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        obj_mark_for_deletion(o);
        o->oInteractStatus = INT_STATUS_NONE;
    }
}

void bhv_star_spawn_init(void) {
    s16 yaw;
    vec3f_get_lateral_dist_and_yaw(&o->oPosVec, &o->oHomeVec, &o->oStarSpawnDisFromHome, &yaw);
    o->oMoveAngleYaw = yaw;
    o->oVelY = (o->oHomeY - o->oPosY) / 30.0f;
    o->oForwardVel = o->oStarSpawnDisFromHome / 30.0f;
    o->oStarSpawnVelY = o->oPosY;

#ifdef ENABLE_VANILLA_LEVEL_SPECIFIC_CHECKS
    if (o->oBehParams2ndByte == SPAWN_STAR_ARC_CUTSCENE_BP_DEFAULT_STAR || gCurrCourseNum == COURSE_BBH) {
#else
    if (o->oBehParams2ndByte == SPAWN_STAR_ARC_CUTSCENE_BP_DEFAULT_STAR) {
#endif
        cutscene_object(CUTSCENE_STAR_SPAWN, o);
    } else {
        cutscene_object(CUTSCENE_RED_COIN_STAR_SPAWN, o);
    }

    set_time_stop_flags(TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS);
    o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
    cur_obj_become_intangible();
}

void bhv_star_spawn_loop(void) {
    switch (o->oAction) {
        case SPAWN_STAR_ARC_CUTSCENE_ACT_START:
            o->oFaceAngleYaw += 0x1000;
            if (o->oTimer > 20) {
                o->oAction = SPAWN_STAR_ARC_CUTSCENE_ACT_GO_TO_HOME;
            }
            break;

        case SPAWN_STAR_ARC_CUTSCENE_ACT_GO_TO_HOME:
            obj_move_xyz_using_fvel_and_yaw(o);
            o->oStarSpawnVelY += o->oVelY;
            o->oPosY = o->oStarSpawnVelY + sins((o->oTimer * 0x8000) / 30) * 400.0f;
            o->oFaceAngleYaw += 0x1000;
            spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
            cur_obj_play_sound_1(SOUND_ENV_STAR);
            if (o->oTimer == 29) {
                o->oAction = SPAWN_STAR_ARC_CUTSCENE_ACT_BOUNCE;
                o->oForwardVel = 0;
                // Set to exact home coordinates
                vec3f_copy(&o->oPosVec, &o->oHomeVec);
                play_power_star_jingle();
            }
            break;

        case SPAWN_STAR_ARC_CUTSCENE_ACT_BOUNCE:
            if (o->oTimer < 20) {
                o->oVelY = 20 - o->oTimer;
            } else {
                o->oVelY = -10.0f;
            }

            spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
            obj_move_xyz_using_fvel_and_yaw(o);
            o->oFaceAngleYaw = o->oFaceAngleYaw - o->oTimer * 0x10 + 0x1000;
            cur_obj_play_sound_1(SOUND_ENV_STAR);

            if (o->oPosY < o->oHomeY) {
                cur_obj_play_sound_2(SOUND_GENERAL_STAR_APPEARS);
                cur_obj_become_tangible();
                o->oPosY = o->oHomeY;
                o->oAction = SPAWN_STAR_ARC_CUTSCENE_ACT_END;
            }
            break;

        case SPAWN_STAR_ARC_CUTSCENE_ACT_END:
            o->oFaceAngleYaw += 0x800;
            if (o->oTimer == 20) {
                gObjCutsceneDone = TRUE;
                clear_time_stop_flags(TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS);
                o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
            }

            if (o->oInteractStatus & INT_STATUS_INTERACTED) {
                obj_mark_for_deletion(o);
                o->oInteractStatus = INT_STATUS_NONE;
            }
            break;
    }
}

struct Object *spawn_star(struct Object *starObj, f32 x, f32 y, f32 z) {
    starObj = spawn_object_abs_with_rot(o, 0, MODEL_STAR, bhvStarSpawnCoordinates, o->oPosX, o->oPosY, o->oPosZ, 0, 0, 0);
    starObj->oBehParams = o->oBehParams;
    vec3f_set(&starObj->oHomeVec, x, y, z);
    starObj->oFaceAnglePitch = 0;
    starObj->oFaceAngleRoll = 0;
    return starObj;
}

//Drahnokks edit
//I optimized the spawn_X_star function, before there was 3 way to do :
// - spaw_default_star              -> set coordinate, camera follow the star during the arc movement to home but DON'T zoom on it, exit the level
// - spawn_red_coin_cutscene_star   -> set coordinate, camera "follow" but always used with o->oPosVec, so it always just bounce on place THEN zoom on it, exit the level
// - spawn_no_exit_star             -> set coordinate, camera "follow" but always used with o->oPosVec, so it always just bounce on place THEN zoom on it, don't exit the level
// 
// It was impossible to zoom on a not-hidden star (like stars from bosses), and the only difference between the last 2 was the "exiting level" case.
// So I bring to you spawn_star_cutscene where you can parametize if the star exit the level and which zoom policy to apply.

// I also redirect the spawn_default_star to the new one to avoid edit each occurence of it.
// and spawn_hidden_star so you dont have to remember the SPAWN_STAR_ARC_CUTSCENE_BP_DEFAULT_STAR & SPAWN_STAR_ARC_CUTSCENE_BP_HIDDEN_STAR #define is you want the star to exit the level
//
// linked with that, now the bhvBowserCourseRedCoinStar behavior redirect to bhvHiddenRedCoinStar who get new checks to handle old bhvBowserCourseRedCoinStar comportments (no marker and no exit)

void spawn_default_star(f32 x, f32 y, f32 z) {
    spawn_star_cutscene(x, y, z, TRUE, SPAWN_STAR_ARC_CUTSCENE_BP_DEFAULT_STAR);
}

void spawn_hidden_star(f32 x, f32 y, f32 z) {
    spawn_star_cutscene(x, y, z, TRUE, SPAWN_STAR_ARC_CUTSCENE_BP_HIDDEN_STAR);
}

void spawn_star_cutscene(f32 x, f32 y, f32 z, s32 exitLevel, s32 cutsceneStarType) {
    struct Object *starObj = NULL;
    starObj = spawn_star(starObj, x, y, z);
    starObj->oBehParams2ndByte = cutsceneStarType;
    if(exitLevel != TRUE){
        starObj->oInteractionSubtype |= INT_SUBTYPE_NO_EXIT;
    }
}

void bhv_hidden_red_coin_star_init(void) {
    struct Object *starObj = NULL;

#ifdef ENABLE_VANILLA_LEVEL_SPECIFIC_CHECKS
    if (gCurrCourseNum != COURSE_JRB) {
        spawn_object(o, MODEL_TRANSPARENT_STAR, bhvRedCoinStarMarker);
    }
#else
    if(!cur_obj_has_behavior(bhvBowserCourseRedCoinStar)){
        spawn_object(o, MODEL_TRANSPARENT_STAR, bhvRedCoinStarMarker);
    }
#endif

    // check if bparam2 specifies a total number of coins that should spawn the star
    if (o->oBehParams2ndByte != 0) {
        o->oHiddenStarTriggerTotal = o->oBehParams2ndByte;
        o->oHiddenStarTriggerCounter = gRedCoinsCollected;
        if (o->oHiddenStarTriggerCounter >= o->oHiddenStarTriggerTotal) {
            starObj = spawn_object_abs_with_rot(o, 0, MODEL_STAR, bhvStar, o->oPosX, o->oPosY, o->oPosZ, 0, 0, 0);
            starObj->oBehParams = o->oBehParams;
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        }
    }
    else {
        s16 numRedCoinsRemaining = count_objects_with_behavior(bhvRedCoin);
        if (numRedCoinsRemaining == 0) {
            starObj = spawn_object_abs_with_rot(o, 0, MODEL_STAR, bhvStar, o->oPosX, o->oPosY, o->oPosZ, 0, 0, 0);
            starObj->oBehParams = o->oBehParams;
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        }
        o->oHiddenStarTriggerTotal = numRedCoinsRemaining + gRedCoinsCollected;
        o->oHiddenStarTriggerCounter = o->oHiddenStarTriggerTotal - numRedCoinsRemaining;
    }
    
}

void bhv_hidden_red_coin_star_loop(void) {
    gRedCoinsCollected = o->oHiddenStarTriggerCounter;

    switch (o->oAction) {
        case HIDDEN_STAR_ACT_INACTIVE:
            if (o->oHiddenStarTriggerCounter == o->oHiddenStarTriggerTotal) {
                o->oAction = HIDDEN_STAR_ACT_ACTIVE;
            }
            break;

        case HIDDEN_STAR_ACT_ACTIVE:
            if (o->oTimer > 2) {
                s32 exitLevel = !cur_obj_has_behavior(bhvBowserCourseRedCoinStar);
                spawn_star_cutscene(o->oPosX, o->oPosY, o->oPosZ, exitLevel, SPAWN_STAR_ARC_CUTSCENE_BP_HIDDEN_STAR);
                spawn_mist_particles();
                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            }
            break;
    }
}
