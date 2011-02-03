#ifndef _ANIMATE_FRAMES_H_
#define _ANIMATE_FRAMES_H_
#include "animate_frames_bin.h"

#define DEFAULT_DELAY 0

typedef struct _anim_sequence {
        const char *data;
        int size;
        float delay;
} anim_sequence;

static anim_sequence seq[] = {
        { VID_FRAME_0, VID_FRAME_0_SIZE, DEFAULT_DELAY },
	{ VID_FRAME_1, VID_FRAME_1_SIZE, DEFAULT_DELAY },
	{ VID_FRAME_2, VID_FRAME_2_SIZE, DEFAULT_DELAY },
	{ VID_FRAME_3, VID_FRAME_3_SIZE, DEFAULT_DELAY },
	{ VID_FRAME_4, VID_FRAME_4_SIZE, DEFAULT_DELAY },
	{ VID_FRAME_5, VID_FRAME_5_SIZE, DEFAULT_DELAY },
	{ VID_FRAME_6, VID_FRAME_6_SIZE, DEFAULT_DELAY },
	{ VID_FRAME_7, VID_FRAME_7_SIZE, DEFAULT_DELAY },
	{ VID_FRAME_8, VID_FRAME_8_SIZE, DEFAULT_DELAY },
	{ VID_FRAME_9, VID_FRAME_9_SIZE, DEFAULT_DELAY },
	{ VID_FRAME_9, VID_FRAME_9_SIZE, 100000 },
	{ NULL, 0, 0 }
};

#endif

