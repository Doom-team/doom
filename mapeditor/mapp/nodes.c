#include "map.h"

t_nod	*n_cr(short x1, short y1, short x2, short y2)
{
	t_nod *a;

	printf("x1 %d y1 %d x2 %d y2 %d\n", x1, y1, x2, y2);
	a = (t_nod*)malloc(sizeof(t_nod));
	a->x1 = x1;
	a->y1 = y1;
	a->x2 = x2;
	a->y2 = y2;
	a->nxt = NULL;
	return (a);
}

void add_node(t_map *mp, int x, int y)
{
	t_nod *n;
	t_nod *cur;

	n = n_cr(mp->x_clck - mp->z_x, mp->y_clck  - mp->z_y, x - mp->z_x, y - mp->z_y);
	if (mp->nod == NULL)
	{
		mp->nod = n;
		return;
	}
	else
	{
		cur = mp->nod;
		while (cur->nxt)
		{
			cur = cur->nxt;
		}
		cur->nxt = n;
	}
}