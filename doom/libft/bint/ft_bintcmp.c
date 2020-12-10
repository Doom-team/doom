/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:24:22 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 21:53:21 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_bintcmp(char *arg1, char *arg2)
{
	int8_t	compare;

	arg1 = ft_strdup(arg1);
	arg2 = ft_strdup(arg2);
	if (!arg1 || !arg2)
		return (0);
	ft_bintprepr(&arg1, &arg2);
	if (!(arg1[0] == '-') && (arg2[0] == '-'))
		compare = 1;
	else if ((arg1[0] == '-') && !(arg2[0] == '-'))
		compare = -1;
	else if ((arg1[0] == '-') && (arg2[0] == '-'))
		compare = -ft_strcmp(arg1, arg2);
	else
		compare = ft_strcmp(arg1, arg2);
	ft_free("2", arg1, arg2);
	if (compare == 0)
		return (0);
	return ((compare > 0) ? 1 : -1);
}
