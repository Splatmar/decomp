
/**
 * Behavior for bhvFloorSwitchHardcodedModel, bhvFloorSwitchGrills, and
 * bhvFloorSwitchAnimatesObject.
 *
 * This controls the purple switches that Mario can step on to affect parts of
 * the environment.
 */

void bhv_purple_switch_loop(void) {
    switch (o->oAction) {

        /**
         * Set the switch's model and scale. If Mario is standing near the
         * switch's middle section, transition to the pressed state.
         */
        case PURPLE_SWITCH_ACT_IDLE:
            cur_obj_set_model(MODEL_PURPLE_SWITCH);
            cur_obj_scale(1.5f);
            if (
                gMarioObject->platform == o
                && !(gMarioStates[0].action & MARIO_NO_PURPLE_SWITCH)
                && lateral_dist_between_objects(o, gMarioObject) < 127.5f
            ) {
                o->oAction = PURPLE_SWITCH_ACT_PRESSED;
            }
            break;

        /**
         * Collapse the switch downward, play a sound, and shake the screen.
         * Immediately transition to the ticking state.
         */
        case PURPLE_SWITCH_ACT_PRESSED:
            cur_obj_scale_over_time(SCALE_AXIS_Y, 3, 1.5f, 0.2f);
            if (o->oTimer == 3) {
                cur_obj_play_sound_2(SOUND_GENERAL2_PURPLE_SWITCH);
                o->oAction = PURPLE_SWITCH_ACT_TICKING;
                cur_obj_shake_screen(SHAKE_POS_SMALL);

#if ENABLE_RUMBLE
                queue_rumble_data(5, 80);
#endif

                // === AJOUT CUSTOM : on affecte un autre objet ===
                struct Object *target = cur_obj_nearest_object_with_behavior(bhvPlatform_with_id);
                if (target != NULL) {
                    target->oBehParams2ndByte -= 1; // Réduit la valeur de l’objet cible
                }
            }
            break;

        /**
         * Play a continuous ticking sound that gets faster when time is almost
         * up. When time is up, move to a waiting-while-pressed state.
         */
        case PURPLE_SWITCH_ACT_TICKING:
            if (o->oBehParams2ndByte != 0) {
                if (o->oBehParams2ndByte == 1 && gMarioObject->platform != o) {
                    o->oAction++;
                } else {
                    if (o->oTimer < 360) {
                        play_sound(SOUND_GENERAL2_SWITCH_TICK_FAST, gGlobalSoundSource);
                    } else {
                        play_sound(SOUND_GENERAL2_SWITCH_TICK_SLOW, gGlobalSoundSource);
                    }
                    if (o->oTimer > 400) {
                        o->oAction = PURPLE_SWITCH_ACT_WAIT_FOR_MARIO_TO_GET_OFF;
                    }
                }
            }
            break;

        /**
         * Make the switch look unpressed again, and transition back to the
         * idle state.
         */
        case PURPLE_SWITCH_ACT_UNPRESSED:
            cur_obj_scale_over_time(SCALE_AXIS_Y, 3, 0.2f, 1.5f);
            if (o->oTimer == 3) {
                o->oAction = PURPLE_SWITCH_ACT_IDLE;
            }
            break;

        /**
         * Mario is standing on the switch, but time has expired. Wait for
         * him to get off the switch, and when he does so, transition to the
         * unpressed state.
         */
        case PURPLE_SWITCH_ACT_WAIT_FOR_MARIO_TO_GET_OFF:
            if (!cur_obj_is_mario_on_platform()) {
                o->oAction = PURPLE_SWITCH_ACT_UNPRESSED;
            }
            break;
    }
}
void bhv_purple_switch_special_loop(void) {
    switch (o->oAction) {

        /**
         * Switch au repos, attend que Mario marche dessus
         */
        case PURPLE_SWITCH_ACT_IDLE:
            cur_obj_set_model(MODEL_PURPLE_SWITCH);
            cur_obj_scale(1.5f);
            if (
                gMarioObject->platform == o
                && !(gMarioStates[0].action & MARIO_NO_PURPLE_SWITCH)
                && lateral_dist_between_objects(o, gMarioObject) < 127.5f
            ) {
                o->oAction = PURPLE_SWITCH_ACT_PRESSED;
            }
            break;

        /**
         * Quand Mario appuie dessus → le switch s’enfonce une fois,
         * joue un son, reste enfoncé et déclenche l’effet custom.
         */
        case PURPLE_SWITCH_ACT_PRESSED:
            cur_obj_scale_over_time(SCALE_AXIS_Y, 3, 1.5f, 0.2f);
            if (o->oTimer == 3) {
                cur_obj_play_sound_2(SOUND_GENERAL2_PURPLE_SWITCH);
                cur_obj_shake_screen(SHAKE_POS_SMALL);

#if ENABLE_RUMBLE
                queue_rumble_data(5, 80);
#endif

                // === AJOUT CUSTOM : affecter l’objet une seule fois ===
                struct Object *target = cur_obj_nearest_object_with_behavior(bhvPlatform_with_id);
                if (target != NULL) {
                    target->oBehParams2ndByte -= 1; // Réduit la valeur de l’objet cible
                }

                // 🔒 Verrouillage : le switch reste enfoncé pour toujours
                o->oAction = PURPLE_SWITCH_ACT_WAIT_FOR_MARIO_TO_GET_OFF;
            }
            break;

        /**
         * Attendre que Mario descende du switch.
         * Le switch NE SE RELÈVERA PAS → il reste enfoncé pour toujours.
         */
        case PURPLE_SWITCH_ACT_WAIT_FOR_MARIO_TO_GET_OFF:
            // Rien d’autre : juste figé enfoncé
            break;
    }
}
#define PLATFORM_ACT_WAITING     0
#define PLATFORM_ACT_DELAY       1
#define PLATFORM_ACT_MOVING_UP   2
#define PLATFORM_ACT_STOPPED     3

#define PLATFORM_MOVE_HEIGHT     10.0f
#define PLATFORM_DELAY_FRAMES    30
#define PLATFORM_MOVE_FRAMES     180

void bhv_platform_with_id_loop(void) {
    

    switch (o->oAction) {
        case PLATFORM_ACT_WAITING:
            if (o->oBehParams2ndByte <= 0) {
                o->oAction = PLATFORM_ACT_DELAY;
                o->oTimer = 0;
                gLakituState.mode = CAMERA_MODE_STUCK;
                set_mario_npc_dialog(MARIO_DIALOG_LOOK_FRONT);
            }
            break;

        case PLATFORM_ACT_DELAY:
            if (o->oTimer > PLATFORM_DELAY_FRAMES) {
                o->oAction = PLATFORM_ACT_MOVING_UP;
                o->oTimer = 0;
            }
            break;

        case PLATFORM_ACT_MOVING_UP:
            o->oPosY += PLATFORM_MOVE_HEIGHT; 
            o->oTimer++;

            if (o->oTimer > PLATFORM_MOVE_FRAMES) {
                play_puzzle_jingle();
                o->oAction = PLATFORM_ACT_STOPPED;
                gLakituState.mode = CAMERA_MODE_8_DIRECTIONS;
                gMarioState[0].action = ACT_IDLE;
            }
            break;

        case PLATFORM_ACT_STOPPED:
            break;
    }
}
