#pragma once

/*****************
 * MENU SETTINGS *
 *****************/

// -- EXIT COURSE SETTINGS --

/**
 * Disables Exit Course.
 */
// #define DISABLE_EXIT_COURSE

/**
 * Decides whether you can exit course while moving (has no effect if you disable Exit Course).
 */
// #define EXIT_COURSE_WHILE_MOVING

/**
 * Decides whether to treat exiting course as if the player had died. 
 * If enabled, the player will get warped to the failure warp node when selecting EXIT COURSE. (Has no effect if you disable Exit Course)
 */
// #define DEATH_ON_EXIT_COURSE

/**
 * Enable a custom exit course warp using the 0xF4 warp id, so it can be different in each level
 */
#define CUSTOM_EXIT_COURSE

/**
 * Enable to reset a course using the pause menu, so it can be different in each level
 */
//#define ENABLE_RESET_COURSE

#define RESET_COURSE_AREA 0x01
#define RESET_COURSE_NODE 0x0A

/**
 * Decides which level, area and warp ID the "Exit Course" option takes you to (has no effect if you disable Exit Course or enable DEATH_ON_EXIT_COURSE).
 * Ensure that the warp exists, or else the game will crash.
 */
#define EXIT_COURSE_LEVEL LEVEL_CASTLE
#define EXIT_COURSE_AREA 0x01
#define EXIT_COURSE_NODE 0x1F
