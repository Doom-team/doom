#include "maps.h"

double sq(double x1, double y1, double x2, double y2)
{
	return ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void	find_coord(t_map *mp, double *x, double *y)
{
	double x1;
	double y1;
	double abs;
	double abs1;
	t_nod *nod;

	nod = mp->nod;
	x1 = *x + 5;
	y1 = *y + 5;
	abs = 50.;
	if (!nod)
		return;
	while (nod)
	{
		if (fabs(nod->x1 - *x) < 0.3 && fabs(nod->y1 - *y) < 0.3)
		{
			abs1 = sq(*x, *y, nod->x1, nod->y1);
			if (abs1 < abs)
			{
				abs = abs1;
				x1 = nod->x1;
				y1 = nod->y1;
			}
		}
		if (fabs(nod->x2 - *x) < 0.3 && fabs(nod->y2 - *y) < 0.3)
		{
			abs1 = sq(*x, *y, nod->x2, nod->y2);
			if (abs1 < abs)
			{
				abs = abs1;
				x1 = nod->x2;
				y1 = nod->y2;
			}
		}
		nod = nod->nxt;
	}
	if (abs < 0.5)
	{
		*x = x1;
		*y = y1;
	}
}

t_nod	*n_cr(double x1, double y1, double x2, double y2)
{
	t_nod *a;

	a = (t_nod*)malloc(sizeof(t_nod));
	a->x1 = x1;
	a->y1 = y1;
	a->x2 = x2;
	a->y2 = y2;
	a->nxt = NULL;
	return (a);
}

void add_node(t_map *mp, double x, double y)
{
	t_nod *n;
	t_nod *cur;

	n = n_cr(mp->x_c, mp->y_c, x, y);
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
