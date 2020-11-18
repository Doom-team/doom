#include "../include/map.h"

void turn_btn(t_btn *b)
{
	(*b).active = !((*b).active);
}

int		press_b(t_btn b, int key, int x, int y)
{
	if (b.active && x < b.xpos + b.w && x > b.xpos && y < b.ypos + b.h && y > b.ypos)
		return (key);
	return (0);
}

int		mkey(int key, int x, int y, t_strc *strc)
{
	printf("key %d x %d y %d\n", key, x, y);
	if (press_b(strc->interface.b[0], key, x, y))
	{
		strc->plr.rypos -= 3;
	}
	if (press_b(strc->interface.b[1], key, x, y))
		strc->plr.rypos += 3;
	if (press_b(strc->interface.b[2], key, x, y))
		strc->plr.rxpos -= 3;
	if (press_b(strc->interface.b[3], key, x, y))
		strc->plr.rxpos += 3;
	if (press_b(strc->interface.b[4], key, x, y))
	{
		turn_btn(&strc->interface.b[0]);
		turn_btn(&strc->interface.b[1]);
		turn_btn(&strc->interface.b[2]);
		turn_btn(&strc->interface.b[3]);
	}
	draw(strc);
	return (0);
}