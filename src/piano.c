//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/piano.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-11
//  
//  Description: 音乐钢琴
//  程序调用接口：
//  ./piano 音量值[0-3] 0: 关闭音量，1：小音量，2：默认音量，3：大音量
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include "bmp.h"
#include "ts.h"
#include "audio.h"
#include <signal.h>
#include <pthread.h>

void catch_sig(int sig)
{
	exit(0);
}

char * init_lcd(struct fb_var_screeninfo *vinfo)
{
	int lcd = open(LCD, O_RDWR);

	bzero(vinfo, sizeof(struct fb_var_screeninfo));
	ioctl(lcd, FBIOGET_VSCREENINFO, vinfo);

	char *FB = mmap(NULL, vinfo->xres * vinfo->yres * 4,
					PROT_READ|PROT_WRITE,
					MAP_SHARED, lcd, 0);
	return FB;
}

void usage(const char *prog)
{
	printf("Usage: %s volume[0-3]\n", prog);
}

int main(int argc, char **argv)
{
	usage(argv[0]);

	if(argc == 2)
	{
		switch(atoi(argv[1]))	
		{
		case 0:
			vol =-175;break;
		case 1:
			vol = -15; break;
		case 2:
			vol = 0; break; // 这是默认的音量
		case 3:
			vol = 10;break;
		}
	}
	else
	{
		vol = 0;
	}

	signal(SIGINT, catch_sig);

	// 准备LCD
	struct fb_var_screeninfo vinfo;
	char *FB = init_lcd(&vinfo);
	bzero(FB, vinfo.xres * vinfo.yres * vinfo.bits_per_pixel/8);

	// 显示背景
	bmp2lcd(BACKGROUND, FB, &vinfo, 0, 0);

	// 显示琴键
	int i;
	for(i=0; i<12; i++)
	{
		bmp2lcd(KEYOFF, FB, &vinfo, 65*i + 10, 47);
	}

	// 显示标题栏和钢琴logo
	bmp2lcd(BAR,  FB, &vinfo, 0, 0);
	bmp2lcd(LOGO, FB, &vinfo, 229, 355);

	// 准备触摸屏
	int ts = open(TOUCH_PANEL, O_RDONLY);

	pthread_t tid;
	struct coordinate coor;

	int new_pos=0, old_pos=0;
	bool first_time = true;

	while(1)
	{
		old_pos = new_pos;

		// 等待手指触碰琴键
		bool released = false;
		ts_trace(ts, &coor, &released);

		if(released)
		{
			for(i=0; i<12; i++)
			{
				bmp2lcd(KEYOFF, FB, &vinfo, 65*i + 10, 47);
			}
			first_time = true;
			continue;
		}

		if(coor.x > 790 || coor.x < 10)
			continue;

		new_pos = 10 + (coor.x-10)/65*65;

		if(new_pos != old_pos || first_time)
		{
			// 1，更新琴键状态
			bmp2lcd(KEYON, FB, &vinfo, new_pos, 47);

			if(!first_time)
			{
				bmp2lcd(KEYOFF, FB, &vinfo, new_pos, 47);
			}
			else
				first_time = false;	

			// 2，使用madplay播放恰当的琴音
			pthread_create(&tid, NULL, play_note, (void *)((coor.x-10)/65+1));
		}
	}

	return 0;
}
