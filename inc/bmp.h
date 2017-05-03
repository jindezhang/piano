//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/bmp.h
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-11
//  
//  Description: 处理BMP格式图像数据
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#ifndef __BMP_H_
#define __BMP_H_

#include <stdio.h>
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

#define LCD "/dev/fb0"

#define BACKGROUND "./res/bmp/background.bmp"
#define BAR        "./res/bmp/bar.bmp"
#define LOGO       "./res/bmp/logo.bmp"
#define KEYON      "./res/bmp/key_on.bmp"
#define KEYOFF     "./res/bmp/key_off.bmp"


struct bitmap_header
{
	int16_t type;
	int32_t size; // 图像文件大小
	int16_t reserved1;
	int16_t reserved2;
	int32_t offbits; // bmp图像数据偏移量
}__attribute__((packed));

struct bitmap_info
{
	int32_t size; // 本结构大小	
	int32_t width;
	int32_t height;
	int16_t planes; // 总为零

	int16_t bit_count; // 色深
	int32_t compression;
	int32_t size_img; // bmp数据大小，必须是4的整数倍
	int32_t X_pel;
	int32_t Y_pel;
	int32_t clrused;
	int32_t clrImportant;
}__attribute__((packed));

struct rgb_quad
{
	int8_t blue;
	int8_t green;
	int8_t red;
	int8_t reserved;
}__attribute__((packed));


struct image_info
{
	int width;
	int height;
	int pixel_size;
};

void bmp2lcd(char *bmpfile, char *FB,
			 struct fb_var_screeninfo *vinfo,
			 int xoffset, int yoffset);
void draw_piano(char *FB, struct fb_var_screeninfo *vinfo, char *backgound);
char *load_bmp (const char *bmpfile, struct image_info *imginfo);



#endif
