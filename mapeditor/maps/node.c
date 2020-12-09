/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 13:56:34 by grinko            #+#    #+#             */
/*   Updated: 2020/10/18 16:06:57 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_nod	*n_cr(int x, int y, int z)
{
	t_nod *a;

	a = (t_nod*)malloc(sizeof(t_nod));
	a->x = x;
	a->y = y;
	a->z = z;
	a->r = NULL;
	a->d = NULL;
	return (a);
}

int		retx(t_nod *a, t_read *b)
{
	if (b->pepe == 1)
		return ((int)round(b->sl * (cos(b->angl * R) * a->x -\
		cos((60 - b->angl) * R) * a->y)) + b->movx);
	else if (b->pepe == 2)
		return ((int)round(a->x * cos(b->angl * R)\
		* b->sl - b->sl * a->y * sin(b->angl * R) + b->movx));
	else
		return (0);
}

int		rety(t_nod *a, t_read *b)
{
	if (b->pepe == 1)
		return ((int)round(b->sl * (sin(b->angl * R) * a->x + \
		sin((60 - b->angl) * R) * a->y) - b->amp * b->sl * a->z) + b->movy);
	else if (b->pepe == 2)
		return ((int)round(a->y * cos(b->angl * R) * b->sl + sin(b->angl\
		* R) * a->x * b->sl + b->movy));
	else
		return (0);
}

void	create_map(t_read *q)
{
	t_nod	*cur;
	t_nod	*nxt;
	t_nod	*str;

	cur = n_cr(q->j, q->i, q->arr[q->i][q->j]);
	q->nod = cur;
	str = q->nod;
	while (++q->j < q->column)
		cur = piupiu(cur, q);
	while (++q->i < q->row)
	{
		q->j = 0;
		nxt = str->r;
		str->d = n_cr(q->j * 1, q->i * 1, q->arr[q->i][q->j] * 1);
		cur = str->d;
		while (q->j < q->column - 1)
		{
			q->j++;
			cur->r = n_cr(q->j * 1, q->i * 1, q->arr[q->i][q->j] * 1);
			cur = cur->r;
			nxt->d = cur;
			nxt = nxt->r;
		}
		str = str->d;
	}
}

void	printmap(t_read *f)
{
	t_nod	*i;
	t_nod	*j;
	int		sc;

	sc = round(f->row * f->sl);
	i = f->nod;
	window(f);
	while (i)
	{
		j = i;
		while (j)
		{
			if (j->d)
				prl(j, j->d, f, sc);
			if (j->r)
				prl(j, j->r, f, sc);
			j = j->r;
		}
		i = i->d;
	}
}
