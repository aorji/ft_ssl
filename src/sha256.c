/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:49:01 by aorji             #+#    #+#             */
/*   Updated: 2019/08/16 14:12:39 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sha256.h"

uint32_t lit_to_bigendian(uint32_t word)
{
	return (0x000000ff & word) << 24 | (0x0000ff00 & word) << 8 | (0x00ff0000 & word) >> 8 | (0xff000000 & word) >> 24;
}

static void init_magic_num()
{
	H[0] = 0x6a09e667;
	H[1] = 0xbb67ae85;
	H[2] = 0x3c6ef372;
	H[3] = 0xa54ff53a;
	H[4] = 0x510e527f;
	H[5] = 0x9b05688c;
	H[6] = 0x1f83d9ab;
	H[7] = 0x5be0cd19;
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
		convert_message(W, (uint32_t *)(message + offset));
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
		offset += 64;
	}
}

/*
 * entry piont
 */
enum hash_mode sha256(t_input *input)
{
	static enum hash_mode mode = START;
    (mode == START) ? init_magic_num() : 0;
    if (input->message_size < n)
    {
        if (input->message_size >= a)
        {
            append_padding(input->message, input->message_size, MAX_HASH_MESSAGE_LEN);
            append_lenght(input->message, MAX_HASH_MESSAGE_LEN, input->total_size * BIT_NUM);
            calculation_procedure(input->message, 2);
            sha256_output(input, H);
            return mode = FINISH;
        }
        append_padding(input->message, input->message_size, a);
        append_lenght(input->message, a, input->total_size * BIT_NUM);
        calculation_procedure(input->message, 1);
        sha256_output(input, H);
        return mode = FINISH;
    }
    else
    {
        calculation_procedure(input->message, 1);
        return mode = CONTINUE;
    }
}