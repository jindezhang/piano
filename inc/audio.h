//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/audio.h
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-11
//  
//  Description: 处理音频数据
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#ifndef __AUDIO_H
#define __AUDIO_H

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

#define MAD_PLAYER "./bin/madplay"
#define NOTES_PATH "./res/notes"

extern int vol;

void *play_note(void *arg);

#endif
