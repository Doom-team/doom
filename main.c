#include "doom.h"

///////////////////////////////////////////////////////////////////////////////////////////////////

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	if ((str = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	while (s[start] != '\0' && i < len)
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	ft_nbwords(char const *s, char c)
{
	int		nb_words;
	int		is_word;

	is_word = 1;
	nb_words = 0;
	while (*s != '\0')
	{
		if (is_word == 0 && *s == c)
			is_word = 1;
		if (is_word == 1 && *s != c)
		{
			is_word = 0;
			nb_words++;
		}
		s++;
	}
	return (nb_words);
}

static int	ft_wordlen(char const *s, char c)
{
	int		len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char		**ft_strsplit(char const *s, char c, int *n)
{
	char	**str;
	int		nb_words;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	nb_words = ft_nbwords(s, c);
	*n = ft_nbwords(s, c);
	if ((str = (char **)malloc(sizeof(char *) * (nb_words + 1))) == NULL)
		return (NULL);
	while (nb_words)
	{
		while (*s == c && *s != '\0')
			s++;
		if ((str[i] = ft_strsub(s, 0, ft_wordlen(s, c))) == NULL)
			return (NULL);
		s += ft_wordlen(s, c);
		i++;
		nb_words--;
	}
	str[i] = NULL;
	return (str);
}

char	*ft_strstr(const char *big, const char *little)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (little[j] == '\0')
		return ((char *)big);
	while (big[i] != '\0')
	{
		while (big[i + j] == little[j])
		{
			j++;
			if (little[j] == '\0')
				return ((char *)(&big[i]));
		}
		j = 0;
		i++;
	}
	return (NULL);
}

int	ft_atoi(const char *str)
{
	long long int	sign;
	long long int	temp;

	sign = 1;
	temp = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\v'
	|| *str == '\r' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		temp = (temp * 10) + (*str - '0');
		str++;
	}
	return (temp * sign);
}
size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_bzero(void *b, size_t n)
{
	unsigned char	*arr;

	arr = (unsigned char *)b;
	while (n--)
		*arr++ = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////


char *jsonkeyed(char *str, char *def)
{
	char *value;
	char *tmp;
	int i;
	int j;

	i = ft_strlen(def);
	j = 0;
	value = (char *)malloc(sizeof(char) * 100);
	tmp = ft_strstr(&str[0], def);
	while (tmp[i] != 34)
	{
		value[j] = tmp[i];
		i++;
		j++;
	}
	value[j + 1] = '\0';
	return (value);
}

// char **arrayinit(char **arr, int n, int m)
// {
// 	int i;

// 	i = 0;
// 	arr = (char **)malloc(sizeof(char *) * n);
// 	while (i < n)
// 	{
// 		arr[i] = (char *)malloc(sizeof(char) * m);
// 		i++;
// 	}
// 	return (arr);
// }


t_map *structinit(t_map *map, char *str)
{
	map->xlen = ft_atoi(jsonkeyed(str, XLEN));
	map->ylen = ft_atoi(jsonkeyed(str, YLEN));
	ft_bzero(&map->x, map->xlen);
	ft_bzero(&map->y, map->ylen);
	return (map);
}

int	*atoiall(char **arr, int i)
{
	int j;
	int *mas;

	j = 0;
	while (j < i)
	{
		mas[j] = ft_atoi(arr[j]);
		j++;
	}
	mas[j] = '\0';
	return (mas);
}

void	jsonreader(char *str)			// че за говоно блять?!
{
	t_map *map;
	char **tmp;
	int i;

	map = (t_map *)malloc(sizeof(t_map));
	map = structinit(map, str);
	tmp = ft_strsplit(jsonkeyed(str, XTEXT), ' ', &i);
	printf("\n");						// этот черт ломает сегу
	map->x = atoiall(tmp, i);
	printf("NUMX %d\n", map->x[0]);


	tmp = ft_strsplit(jsonkeyed(str, YTEXT), ' ', &i);
	printf("\n");
	map->y = atoiall(tmp, i);
	printf("NUMY %d\n", map->y[0]);


	tmp = ft_strsplit(jsonkeyed(str, ZTEXT), ' ', &i);
	printf("\n");
	map->z = atoiall(tmp, i);
	printf("NUMZ %d\n", map->z[0]);
}

int		main(int argc, char **argv)
{
	int i;
	FILE *fp;
	char buff[1000];

	fp = fopen("map.json", "r");
	fread(buff, 1000, 1, fp);
	buff[ft_strlen(buff) - 4] = '\0';
	fclose(fp);
	jsonreader(buff);
	printf("Json text:\n %s", buff);
}