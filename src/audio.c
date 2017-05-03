#include "audio.h"

int vol = 0;

void *play_note(void *n)
{
	pthread_detach(pthread_self());

	char *cmd = calloc(1, 64);
	bzero(cmd, 64);

	// 拼凑恰当的mp3文件的名称
	sprintf(cmd, "%s %s/d%d.mp3 -a %d", MAD_PLAYER, NOTES_PATH, (int)n, vol);

	// 运行madplay来播放指定的mp3
	system("killall madplay");
	system(cmd);

	free(cmd);
}
