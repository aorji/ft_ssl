/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_256_auxiliary.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 18:52:19 by aorji             #+#    #+#             */
/*   Updated: 2019/08/21 19:35:32 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sha224_256.h"

uint32_t lit_to_bigendian(uint32_t word)
{
	return (0x000000ff & word) << 24 | (0x0000ff00 & word) << 8 | (0x00ff0000 & word) >> 8 | (0xff000000 & word) >> 24;
}

static void convert_message(uint32_t W[64], uint32_t *message)
{
	int i = 0;
	while (i < 16)
	{
		W[i] = lit_to_bigendian(message[i]);
		i++;
	}
}

static void fill_working_variables(uint32_t HH[], uint32_t H[], char c)
{
	if (c == '<')
	{
		HH[0] = H[0];
		HH[1] = H[1];
		HH[2] = H[2];
		HH[3] = H[3];
		HH[4] = H[4];
		HH[5] = H[5];
		HH[6] = H[6];
		HH[7] = H[7];
	}
	else if (c == '>')
	{
		H[0] = HH[0] + H[0];
		H[1] = HH[1] + H[1];
		H[2] = HH[2] + H[2];
		H[3] = HH[3] + H[3];
		H[4] = HH[4] + H[4];
		H[5] = HH[5] + H[5];
		H[6] = HH[6] + H[6];
		H[7] = HH[7] + H[7];
	}
}

/*
 * step 3
 */
void calculation_procedure32(void *message, int times, uint32_t H[])
{
    int offset = 0;
	int t;
	uint32_t W[64] = {0};
	uint32_t T[2] = {0};

	uint32_t HH[] = {0,	0,	0,	0,	0,	0,	0,	0};

    while ( times-- )
    {
		convert_message(W, (uint32_t *)(message) + offset);
		t = 16;
		while ( t < 64)
		{
			W[t] = SSIG1(W[t-2]) + W[t-7] + SSIG0(W[t-15]) + W[t-16];
			t++;
		}
		fill_working_variables(HH, H, '<');
		t = 0;
		while (t < 64)
		{
			T[0] = HH[7] + BSIG1(HH[4]) + CH(HH[4], HH[5], HH[6]) + K[t] + W[t];
			T[1] = BSIG0(HH[0]) + MAJ(HH[0], HH[1], HH[2]);
			HH[7] = HH[6];
			HH[6] = HH[5];
			HH[5] = HH[4];
			HH[4] = HH[3] + T[0];
			HH[3] = HH[2];
			HH[2] = HH[1];
			HH[1] = HH[0];
			HH[0] = T[0] + T[1];
			t++;
		}
		fill_working_variables(HH, H, '>');
		offset += 16;
	}
}
