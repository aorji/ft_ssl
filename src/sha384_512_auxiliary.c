/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384_512_auxiliary.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 17:54:44 by aorji             #+#    #+#             */
/*   Updated: 2019/08/21 19:31:35 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sha384_512.h"

uint64_t lit_to_bigendian64(uint64_t word)
{
	uint32_t a = word;
	uint32_t b = word >> 32;
	return (((uint64_t)lit_to_bigendian(a) & 0x00000000ffffffff) << 32 | ((uint64_t)lit_to_bigendian(b) & 0x00000000ffffffff));
}

static void convert_message(uint64_t W[64], uint64_t *message)
{
	int i = 0;
	while (i < 16)
	{
		W[i] = lit_to_bigendian64(message[i]);
		i++;
	}
}

static void fill_working_variables(uint64_t HH[], uint64_t H[], char c)
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
void calculation_procedure64(void *message, int times, uint64_t H[])
{
    int offset = 0;
	int t;
	uint64_t W[80] = {0};
	uint64_t T[2] = {0};

	uint64_t HH[] = {0,	0,	0,	0,	0,	0,	0,	0};

    while ( times-- )
    {
		convert_message(W, (uint64_t *)(message) + offset);
		t = 16;
		while ( t < 80)
		{
			W[t] =	SSIG1(W[t-2]) + W[t-7] + SSIG0(W[t-15]) + W[t-16];
			t++;
		}
		fill_working_variables(HH, H, '<');
		t = 0;
		while (t < 80)
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