/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:45 by clala             #+#    #+#             */
/*   Updated: 2020/10/24 21:01:34 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_MALLOC "Can't allocate memory"
# define ERR_MAP_NO_START "No player start position"
# define ERR_MAP_NOT_TXT "Map must be .txt file"
# define ERR_MAP_MULT_START "Multiple player start positions"
# define ERR_MAP_MULT_COIN "Multiple coin positions"
# define ERR_MAP_BORDER_COL "There must be a border texture at column %d"
# define ERR_MAP_BORDER_ROW "There must be a border texture at row %d"
# define ERR_MAP_BIG "Map is too big"
# define ERR_MAP_SMALL "Map is too small"
# define ERR_MAP_CHAR "Invalid char in map file: "
# define ERR_MAP_COL_NUM "Not enough columns at row "
# define ERR_MAP_ROW_NUM "Not enough rows at map"
# define ERR_MAP_NOT_RECT "Map is not rectangle"
# define ERR_FILE_OPEN "Can't open file %s"
# define ERR_FILE_READ "Can't read file %s"

# define ERR_INV_H "Screen height must be less or equal to width"
# define ERR_INV_RES "Screen resolution must be at least 384x384"
# define ERR_USAGE "Usage : ./wolf3d [map]"
# define ERR_H_MAX "Screen height cannot be more than "
# define ERR_W_MAX "Screen width cannot be more than "

#endif
