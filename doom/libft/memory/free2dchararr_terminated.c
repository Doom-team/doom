/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2dchararr_terminated.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <ahusk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by ahusk             #+#    #+#             */
/*   Updated: 2020/02/15 21:53:21 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		free_2dchararr_terminated(char **arr)
{
	int		i;

	i = 0;
	while (arr[i] != 0)
		free(arr[i++]);
	free(arr);
	arr = NULL;
	return (1);
}
