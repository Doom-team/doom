#include "../include/map.h"
// Вангую что искомая точка лежит на отрезке (х1, у1, х2, у2).
// В этом случае длина исходного отрезка LL=sqrt((x2-x1)^2+(y2-y1)^2)
// И координаты искомой точки
// x=x1+(x2-x1)*L/LL
// y=y1+(y2-y1)*L/LL 

// void	draw_mapstairs(t_map *map, int x, int y, int i)
// {
// 	int x1;
// 	int y1;
// 	float nx;
// 	float ny;
// 	float tmp;
// 	int width = 15;
// 	float len;

// 	x1 = map->x_c ;
// 	y1 = map->y_c ;
	
// 	nx = (y1 - y);
// 	ny = (x - x1);
// 	nx /= sqrt(nx*nx + ny*ny);
// 	ny /= sqrt(nx*nx + ny*ny);
// 	nx *= width * 0.7;
// 	ny *= width * 0.7;
// 	len = sqrt((x - x1)* (x - x1) + (y - y1) * (y - y1));
// 	x = x1 + (x - x1) * 20 * i /** map->stclick*/ / len;
// 	y = y1 + (y - y1) * 20  * i/** map->stclick*/ / len;
// 	draw_floor_line(map, &(t_info){x1 - nx, (y1 - ny) , (x - nx) , (y - ny) });
// 	draw_floor_line(map, &(t_info){(x1 + nx) , (y1 + ny) , (x + nx) , (y + ny) });
// 	draw_floor_line(map, &(t_info){(x1 - nx), (y1 - ny) , (x1 + nx), (y1 + ny)});
// 	draw_floor_line(map, &(t_info){(x - nx) , (y - ny) , (x + nx) , (y + ny) });
// }

// void	draw_mapstairs(t_map *map, int x, int y, int i)
// {
// 	int x1;
// 	int y1;
// 	float nx;
// 	float ny;
// 	float tmp;
// 	int width = 15;
// 	float len;

// 	x1 = map->x_c ;
// 	y1 = map->y_c ;
	
// 	nx = (y1 - y);
// 	ny = (x - x1);
// 	nx /= sqrt(nx*nx + ny*ny);
// 	ny /= sqrt(nx*nx + ny*ny);
// 	nx *= width * 0.7;
// 	ny *= width * 0.7;
// 	len = sqrt((x - x1)* (x - x1) + (y - y1) * (y - y1));
// 	x = x1 + (x - x1) * 20 * i /** map->stclick*/ / len;
// 	y = y1 + (y - y1) * 20  * i/** map->stclick*/ / len;
// 	draw_floor_line(map, &(t_info){x1 - nx, (y1 - ny) , (x - nx) , (y - ny) });
// 	draw_floor_line(map, &(t_info){(x1 + nx) , (y1 + ny) , (x + nx) , (y + ny) });
// 	draw_floor_line(map, &(t_info){(x1 - nx), (y1 - ny) , (x1 + nx), (y1 + ny)});
// 	draw_floor_line(map, &(t_info){(x - nx) , (y - ny) , (x + nx) , (y + ny) });
	//draw_floor_line(map, &(t_info){(x/2 - nx) , (y/2 - ny), (x/2 + nx), (y/2 + ny) });
	// int i = 1;
	// int x_tmp = 0;
	// int y_tmp = 0;
	// x_tmp = x - x1;
	// 	y_tmp = y - y1;
	// while (i < map->stclick)
	// {
	// 	// tx = x1 + (x - x1) * 20 * map->stclick/i / len;
	// 	// ty = y1 + (y - y1) * 20 * map->stclick/i / len;
	// 	// draw_floor_line(map, &(t_info){(tx - nx) , (ty - ny) , (tx + nx) , (ty + ny) });
		
	// 	x_tmp /= sqrt(x_tmp*x_tmp + y_tmp*y_tmp);
	// 	y_tmp /= sqrt(x_tmp*x_tmp + y_tmp*y_tmp);
	// 	x1 = map->x_c  + x_tmp * 20 * i;
	// 	y1 = map->y_c  + y_tmp * 20 * i;
	// 	x = x1 + (x - x1) * 20 / len * i + 10;
	// 	y = y1 + (y - y1) * 20 / len * i + 10;
	// 	draw_floor_line(map, &(t_info){x1 - nx, (y1 - ny) , (x - nx) , (y - ny) });
	// 	draw_floor_line(map, &(t_info){(x1 + nx) , (y1 + ny) , (x + nx) , (y + ny) });
	// 	draw_floor_line(map, &(t_info){(x1 - nx), (y1 - ny) , (x1 + nx), (y1 + ny)});
	// 	draw_floor_line(map, &(t_info){(x - nx) , (y - ny) , (x + nx) , (y + ny) });
	// 	i++;
	// }
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// if (map->floor_x < 5)
	// {
	// 	// printf("h\n");
	// 	float x_tmp;
	// 	float y_tmp;

	// 	x_tmp = x - x1;
	// 	y_tmp = y - y1;
	// 	x_tmp /= sqrt(x_tmp*x_tmp + y_tmp*y_tmp);
	// 	y_tmp /= sqrt(x_tmp*x_tmp + y_tmp*y_tmp);
	// 	x1 = map->x_c  + x_tmp * 20;
	// 	y1 = map->y_c  + y_tmp * 20;
	// 	// map->x_c = map->x_c + x_tmp * 20;
	// 	// map->y_c = map->y_c + y_tmp * 20;
	// 	map->x_c = x;
	// 	map->y_c = y;
	// 	map->floor_x++;
	// 	draw_mapstairs(map, t_x, t_y);
	// }
	// float x_tmp;
	// float y_tmp;

	// x_tmp = x - x1;
	// y_tmp = y - y1;

	// x_tmp /= sqrt(x_tmp*x_tmp + y_tmp*y_tmp);
	// y_tmp /= sqrt(x_tmp*x_tmp + y_tmp*y_tmp);
	// x1 = map->x_c  + x_tmp * 20;
	// y1 = map->y_c  + y_tmp * 20;
	// printf("%f %f\n",x_tmp, y_tmp);

	// // nx = (y1 - y);
	// // ny = (x - x1);
	// // nx /= sqrt(nx*nx + ny*ny);
	// // ny /= sqrt(nx*nx + ny*ny);
	// // nx *= width;
	// // ny *= width;
	// len = sqrt((x - x1)* (x - x1) + (y - y1) * (y - y1));
	// 	printf("%f\n",len);
	// x = x1 + (x - x1) * 20 / len;
	// y = y1 + (y - y1) * 20 / len;
	// draw_floor_line(map, &(t_info){x1 - nx, (y1 - ny) , (x - nx) , (y - ny) });
	// draw_floor_line(map, &(t_info){(x1 + nx) , (y1 + ny) , (x + nx) , (y + ny) });
	// draw_floor_line(map, &(t_info){(x1 - nx), (y1 - ny) , (x1 + nx), (y1 + ny)});
	// draw_floor_line(map, &(t_info){(x - nx) , (y - ny) , (x + nx) , (y + ny) });

//////////////////////
	// int x1;
	// int y1;
	// float nx;
	// float ny;
	// float tmp;
	// int width = 15;
	// float len;

	// x1 = map->x_c ;
	// y1 = map->y_c ;
	
	// nx = (y1 - y);
	// ny = (x - x1);
	// nx /= sqrt(nx*nx + ny*ny);
	// ny /= sqrt(nx*nx + ny*ny);
	// nx *= width * 0.7;
	// ny *= width * 0.7;
	// len = sqrt((x - x1)* (x - x1) + (y - y1) * (y - y1));
	// x = x1 + (x - x1) * 20 /** map->stclick*/ / len;
	// y = y1 + (y - y1) * 20 /** map->stclick*/ / len;
	// draw_floor_line(map, &(t_info){x1 - nx, (y1 - ny) , (x - nx) , (y - ny) });
	// draw_floor_line(map, &(t_info){(x1 + nx) , (y1 + ny) , (x + nx) , (y + ny) });
	// draw_floor_line(map, &(t_info){(x1 - nx), (y1 - ny) , (x1 + nx), (y1 + ny)});
	// draw_floor_line(map, &(t_info){(x - nx) , (y - ny) , (x + nx) , (y + ny) });
//}

// void	draw_mapstairs(t_map *map, int x, int y)
// {
// 	int x1;
// 	int y1;
// 	float nx;
// 	float ny;
// 	float tmp;
// 	int width = 15;
// 	float len;
// 	// int t_x = x;
// 	// int t_y = y;

// 	x1 = map->x_c ;
// 	y1 = map->y_c ;
	
// 	nx = (y1 - y);
// 	ny = (x - x1);
// 	nx /= sqrt(nx*nx + ny*ny);
// 	ny /= sqrt(nx*nx + ny*ny);
// 	nx *= width * 0.7;
// 	ny *= width * 0.7;
// 	len = sqrt((x - x1)* (x - x1) + (y - y1) * (y - y1));
// 	x = x1 + (x - x1) * 20 * map->stclick / len;
// 	y = y1 + (y - y1) * 20 * map->stclick / len;
// 	draw_floor_line(map, &(t_info){x1 - nx, (y1 - ny) , (x - nx) , (y - ny) });
// 	draw_floor_line(map, &(t_info){(x1 + nx) , (y1 + ny) , (x + nx) , (y + ny) });
// 	draw_floor_line(map, &(t_info){(x1 - nx), (y1 - ny) , (x1 + nx), (y1 + ny)});
// 	draw_floor_line(map, &(t_info){(x - nx) , (y - ny) , (x + nx) , (y + ny) });
// 	//draw_floor_line(map, &(t_info){(x/2 - nx) , (y/2 - ny), (x/2 + nx), (y/2 + ny) });
// 	int i = 1;
// 	int tx = x;
// 	int ty = y;
// 	while (i < map->stclick)
// 	{
// 		tx = x1 + (x - x1) * 20 * map->stclick/i / len;
// 		ty = y1 + (y - y1) * 20 * map->stclick/i / len;
// 		draw_floor_line(map, &(t_info){(tx - nx) , (ty - ny) , (tx + nx) , (ty + ny) });
// 		i++;
// 	}
// }