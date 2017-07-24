//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ts.c
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

#include "ts.h"


void ts_trace(int ts, struct coordinate *coor, bool *released)
{
	struct input_event buf;

	bool x_ready = false;
	bool y_ready = false;

	while(1)
	{
		bzero(&buf, sizeof(buf));
		read(ts, &buf, sizeof(buf));

		if(buf.type == EV_ABS &&
		   buf.code == ABS_Z &&
		   buf.value == 0)
		{
			*released = true;
			break;
		}

		if(buf.type == EV_ABS &&
		   buf.code == ABS_X)
		{
			coor->x = buf.value;
			x_ready = true;
		}

		if(buf.type == EV_ABS &&
		   buf.code == ABS_Y)
		{
			coor->y = buf.value;
			y_ready = true;
		}

		if(x_ready && y_ready)
			break;
	}
}
