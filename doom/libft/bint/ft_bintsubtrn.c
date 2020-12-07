/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintsubtrn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:25:08 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 21:53:21 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_bintsubtrn(char *operand_1, char *operand_2)
{
	char	*str;
	int32_t	borrowed;
	int32_t	sum;
	int32_t	i;

	str = ft_strdup(operand_1);
	i = ft_strlen(str);
	borrowed = 0;
	while (--i >= 0)
	{
		if (str[i] == '.')
			i--;
		sum = ft_ctoi(operand_1[i]) - ft_ctoi(operand_2[i]) - borrowed;
		borrowed = sum < 0;
		if (sum < 0)
			sum += 10;
		str[i] = ft_itoc(sum % 10);
	}
	str = ft_bintfmt(str);
	return (str);
}
