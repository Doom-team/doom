#ifndef DOOM_H
# define DOOM_H

# define XTEXT "x\": \""
# define YTEXT "y\": \""
# define ZTEXT "z\": \""


# define XLEN "xlen\": \""
# define YLEN "ylen\": \""

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// enum def
// {
// 	XTEXT = "x\": \"",
// 	YTEXT = "y\": \"",
// 	ZTEXT = "z\": \""
// }

typedef struct	t_map
{
	char		**xarr;
	char		**yarr;
	char		**zarr;
	int			*x;
	int			*y;
	int			*z;
	int			xlen;
	int			ylen;
	int			zlen;
}				t_map;


char		**ft_strsplit(char const *s, char c, int *n);

#endif