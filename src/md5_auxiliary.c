/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_auxiliary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 18:08:14 by aorji             #+#    #+#             */
/*   Updated: 2019/08/28 18:17:58 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/md5.h"

static void	fill_working_variables(uint32_t hh[], uint32_t g_h[], char c)
{
	if (c == '<')
	{
		hh[0] = g_h[0];
		hh[1] = g_h[1];
		hh[2] = g_h[2];
		hh[3] = g_h[3];
	}
	else if (c == '>')
	{
		g_h[0] += hh[0];
		g_h[1] += hh[1];
		g_h[2] += hh[2];
		g_h[3] += hh[3];
	}
}

static void	calculate(uint32_t *w, uint32_t hh[])
{
	uint32_t	tmp;
	int			j;

	j = 0;
	while (j < 64)
	{
		if (j < 16)
			hh[0] += F(hh[1], hh[2], hh[3]);
		else if (j < 32)
			hh[0] += G(hh[1], hh[2], hh[3]);
		else if (j < 48)
			hh[0] += H(hh[1], hh[2], hh[3]);
		else
			hh[0] += I(hh[1], hh[2], hh[3]);
		tmp = hh[0] + g_t[j] + w[g_x[j]];
		hh[0] = hh[3];
		hh[3] = hh[2];
		hh[2] = hh[1];
		hh[1] = hh[1] + ROTATE_LEFT(tmp, g_s[j]);
		j++;
	}
}

/*
**	step 3
*/

void		calculation_procedure(void *message, int block_num, uint32_t g_h[])
{
	uint32_t	*w;
	int			offset;
	uint32_t	hh[4];

	offset = 0;
	while (block_num--)
	{
		w = (uint32_t *)(message) + offset;
		fill_working_variables(hh, g_h, '<');
		calculate(w, hh);
		fill_working_variables(hh, g_h, '>');
		offset += 16;
	}
}
