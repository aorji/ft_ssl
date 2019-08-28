/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384_512_auxiliary.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 17:54:44 by aorji             #+#    #+#             */
/*   Updated: 2019/08/28 17:59:23 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sha384_512.h"

uint64_t	lit_to_bigendian64(uint64_t word)
{
	uint32_t a;
	uint32_t b;

	a = word;
	b = word >> 32;
	return (((uint64_t)lit_to_bigendian(a) & 0x00000000ffffffff) << 32 |\
	((uint64_t)lit_to_bigendian(b) & 0x00000000ffffffff));
}

static void	convert_message(uint64_t w[64], uint64_t *message)
{
	int i;

	i = 0;
	while (i < 16)
	{
		w[i] = lit_to_bigendian64(message[i]);
		i++;
	}
}

static void	fill_working_variables(uint64_t hh[], uint64_t g_h[], char c)
{
	if (c == '<')
	{
		hh[0] = g_h[0];
		hh[1] = g_h[1];
		hh[2] = g_h[2];
		hh[3] = g_h[3];
		hh[4] = g_h[4];
		hh[5] = g_h[5];
		hh[6] = g_h[6];
		hh[7] = g_h[7];
	}
	else if (c == '>')
	{
		g_h[0] = hh[0] + g_h[0];
		g_h[1] = hh[1] + g_h[1];
		g_h[2] = hh[2] + g_h[2];
		g_h[3] = hh[3] + g_h[3];
		g_h[4] = hh[4] + g_h[4];
		g_h[5] = hh[5] + g_h[5];
		g_h[6] = hh[6] + g_h[6];
		g_h[7] = hh[7] + g_h[7];
	}
}

static void	calculate(uint64_t w[80], uint64_t hh[8])
{
	uint64_t	t[2];
	int			i;

	i = 0;
	while (i < 80)
	{
		t[0] = hh[7] + BSIG1(hh[4]) + CH(hh[4], hh[5], hh[6]) + g_k[i] + w[i];
		t[1] = BSIG0(hh[0]) + MAJ(hh[0], hh[1], hh[2]);
		hh[7] = hh[6];
		hh[6] = hh[5];
		hh[5] = hh[4];
		hh[4] = hh[3] + t[0];
		hh[3] = hh[2];
		hh[2] = hh[1];
		hh[1] = hh[0];
		hh[0] = t[0] + t[1];
		i++;
	}
}

/*
** step 3
*/

void		calculation_procedure_64(void *message,\
int block_num, uint64_t g_h[])
{
	int			offset;
	int			i;
	uint64_t	w[80];
	uint64_t	hh[8];

	offset = 0;
	while (block_num--)
	{
		i = 16;
		convert_message(w, (uint64_t *)(message) + offset);
		while (i < 80)
		{
			w[i] = SSIG1(w[i - 2]) + w[i - 7] + SSIG0(w[i - 15]) + w[i - 16];
			i++;
		}
		fill_working_variables(hh, g_h, '<');
		calculate(w, hh);
		fill_working_variables(hh, g_h, '>');
		offset += 16;
	}
}
