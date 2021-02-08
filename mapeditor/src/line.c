/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:22:30 by grinko            #+#    #+#             */
/*   Updated: 2021/02/08 15:51:23 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_line		*ft_line_new(size_t init_size)
{
	t_line	*result;

	result = (t_line *)malloc(sizeof(t_line));
	if (result)
	{
		result->string = (char *)malloc(init_size);
		if (!result->string)
		{
			free(result);
			return ((t_line *)0);
		}
		result->allocated = init_size;
		result->length = 0;
	}
	return (result);
}

void	ft_line_del(t_line *line)
{
	if (line)
	{
		free(line->string);
		free(line);
	}
}