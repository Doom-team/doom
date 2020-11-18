// #include "../include/map.h"



// void		oneline(t_strc *strc, char *line)
// {
// 	char		**arr;

// 	if (!(arr = ft_strsplit(line, '\t')))
// 		printf("error");
// 	printf("%s\n", arr[0]);
// 	// if (ft_arrlen(arr) > 0)
// 	// {
// 	// 	if (!ft_strcmp(arr[0], "panel"))
// 	// 		sphere(strc, arr);
// 	// 	else if (!ft_strcmp(arr[0], "cylinder"))
// 	// 		cylinder(data, objects, arr);
// 	// 	else if (!ft_strcmp(arr[0], "cone"))
// 	// 		cone(data, objects, arr);
// 	// 	else if (!ft_strcmp(arr[0], "plane"))
// 	// 		plane(data, objects, arr);
// 	// 	else if (!ft_strcmp(arr[0], "camera"))
// 	// 		camera(objects, arr);
// 	// 	else if (!ft_strcmp(arr[0], "light"))
// 	// 		if (!ft_strcmp(arr[1], "AMBIENT") || !ft_strcmp(arr[1], "POINT")
// 	// 			|| !ft_strcmp(arr[1], "DIRECTIONAL"))
// 	// 			light(data, objects, arr);
// 	// 	ft_safe_free_arr(arr);
// 	// }
// }

// // void	init_interface(t_strc *strc)
// // {
// // 	int			fd;
// // 	char		*line;

// // 	fd = 0;
// // 	fd = open("interface.txt", "r");
// // 	// if (fd < 0)
// // 	// 	exit_free("Error: file doesn't exist\n", 1, data);
// // 	// if (fd == 0 || read(fd, NULL, 0) == -1)
// // 	// 	exit_free("Error: can't read file\n", 1, data);
// // 	read(fd, NULL, 0);
// // 	while (get_next_line(fd, &line))
// // 	{
// // 		// if (line[0] != '@' && ft_strlen(line) > 10)
// // 		printf("line : %s\n", line);
// // 		oneline(strc, line);
// // 		free(line);
// // 	}
// // 	close(fd);
// // }

// void	init_buttons(t_strc *strc)
// {
// 	strc->interface.b[BLOCKS].xpos = 20;
// 	strc->interface.b[BLOCKS].ypos = 20;
// 	strc->interface.b[BLOCKS].h = BHIE;
// 	strc->interface.b[BLOCKS].w = BWIDTH;
// 	strc->interface.b[BLOCKS].active = 1;
// 	strc->interface.b[BLOCKS].color = APPLEGREY;

// 	strc->interface.b[TEXTURES].xpos = 120;
// 	strc->interface.b[TEXTURES].ypos = 20;
// 	strc->interface.b[TEXTURES].h = BHIE;
// 	strc->interface.b[TEXTURES].w = BWIDTH;
// 	strc->interface.b[TEXTURES].active = 1;
// 	strc->interface.b[TEXTURES].color = APPLEGREY;

// 	strc->interface.b[OBJECTS].xpos = 220;
// 	strc->interface.b[OBJECTS].ypos = 20;
// 	strc->interface.b[OBJECTS].h = BHIE;
// 	strc->interface.b[OBJECTS].w = BWIDTH;
// 	strc->interface.b[OBJECTS].active = 1;
// 	strc->interface.b[OBJECTS].color = APPLEGREY;

// 	// strc->interface.b[HIDE].xpos = 305;
// 	// strc->interface.b[HIDE].ypos = 0;
// 	// strc->interface.b[HIDE].h = 20;
// 	// strc->interface.b[HIDE].w = 20;
// 	// strc->interface.b[HIDE].active = 1;
// 	// strc->interface.b[HIDE].color = ORANGE;

// 	// strc->b[4].xpos = 300;
// 	// strc->b[4].ypos = 130+500;
// 	// strc->b[4].h = 25;
// 	// strc->b[4].w = 50;
// 	// strc->b[4].active = 1;
// 	// strc->b[4].color = APPLEGREY;

// 	strc->interface.b[5].xpos = 0;
// 	strc->interface.b[5].ypos = 0;
// 	strc->interface.b[5].h = HEIGHT;
// 	strc->interface.b[5].w = 300;
// 	strc->interface.b[5].active = 1;
// 	strc->interface.b[5].color = WHITE;

// }

// void	init_interface(t_strc *strc)
// {
// 	init_buttons(strc);
// }