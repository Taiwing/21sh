/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_cursor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 20:14:36 by yforeau           #+#    #+#             */
/*   Updated: 2019/05/02 21:51:48 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_input.h"

int		*curs_pos_container(int *in)
{
	static int	*pos = NULL;

	if (in)
		pos = in;
	return (pos);
}

void	get_curs_pos(int *dest)
{
	size_t			i;
	unsigned char	pos[16];

	if (!dest)
		return ;
	i = 0;
	write(0, "\x1B[6n", 4);
	while (i < 15 && read(0, pos + i, 1) == 1 && pos[i++] != 'R')
		;
	pos[i] = 0;
	i = 0;
	while (pos[i] && !ft_isdigit(pos[i]))
		++i;
	dest[Y] = ft_atoi((char *)pos + i);
	while (pos[i] && pos[i] != ';')
		++i;
	dest[X] = pos[i] == ';' ? ft_atoi((char *)pos + i + 1) : 0;
}
