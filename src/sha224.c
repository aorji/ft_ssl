/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:00:02 by aorji             #+#    #+#             */
/*   Updated: 2019/08/21 16:30:44 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sha.h"

static void init_magic_num()
{
	H[0] = 0xc1059ed8;
	H[1] = 0x367cd507;
	H[2] = 0x3070dd17;
	H[3] = 0xf70e5939;
	H[4] = 0xffc00b31;
	H[5] = 0x68581511;
	H[6] = 0x64f98fa7;
	H[7] = 0xbefa4fa4;
}

/*
 * step 1
 */
static void append_padding(void *message, size_t from, size_t to)
{
    size_t i = from;
    while(from < to)
    {
        ((uint8_t *)message)[from] = PADDING[from - i];
        ++from;
    }
}

/*
 * step 2
 */
static void append_lenght(void *message, size_t from, size_t len)
{
    for(int i = 7; i >= 0; --i)
    {
        ((uint8_t *)message)[from + i] = (uint8_t)(len);
        len = len >> 8;
    }
}

static void convert_message(uint32_t W[64], uint32_t *message)
{
	int i = 0;
	while (i < 16)
	{
		W[i] = lit_to_bigendian(message[i]);//(0x000000ff & message[i]) << 24 | (0x0000ff00 & message[i]) << 8 | (0x00ff0000 & message[i]) >> 8 | (0xff000000 & message[i]) >> 24;
		i++;
	}
}

/*
 * step 3
 */
static void calculation_procedure(void *message, int times)
{
    int offset = 0;
	int t;
	uint32_t W[64] = {0};
	uint32_t T[2] = {0};

    while ( times-- )
    {
		convert_message(W, (uint32_t *)(message) + offset);
		t = 16;
		while ( t < 64)
		{
			W[t] = SSIG1(W[t-2]) + W[t-7] + SSIG0(W[t-15]) + W[t-16];
			t++;
		}
		HH[0] = H[0];
		HH[1] = H[1];
		HH[2] = H[2];
		HH[3] = H[3];
		HH[4] = H[4];
		HH[5] = H[5];
		HH[6] = H[6];
		HH[7] = H[7];
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
		H[0] = HH[0] + H[0];
		H[1] = HH[1] + H[1];
		H[2] = HH[2] + H[2];
		H[3] = HH[3] + H[3];
		H[4] = HH[4] + H[4];
		H[5] = HH[5] + H[5];
		H[6] = HH[6] + H[6];
		H[7] = HH[7] + H[7];
		offset += 16;
	}
}

/*
 * entry piont
 */
enum mode sha224(t_input *input)
{
	static enum mode hash_mode = START;
    (hash_mode == START) ? init_magic_num() : 0;
    if (input->message_size < n)
    {
        if (input->message_size >= a)
        {
            append_padding(input->message, input->message_size, g_max_message_len);
            append_lenght(input->message, g_max_message_len, input->total_size * BIT_NUM);
            calculation_procedure(input->message, 2);
            sha224_output(input, H);
            return hash_mode = FINISH;
        }
        append_padding(input->message, input->message_size, a);
        append_lenght(input->message, a, input->total_size * BIT_NUM);
        calculation_procedure(input->message, 1);
        sha224_output(input, H);
        return hash_mode = FINISH;
    }
    else
    {
        calculation_procedure(input->message, 1);
        return hash_mode = CONTINUE;
    }
}