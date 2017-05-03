//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ts.h
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-11
//  
//  Description: 触摸屏逻辑处理
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#ifndef __TS_H_
#define __TS_H_

#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <pthread.h>

#define TOUCH_PANEL "/dev/event0"

struct coordinate
{
	int x;
	int y;
};

void ts_trace(int ts, struct coordinate *coor, bool *released);

#endif
