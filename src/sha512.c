/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 16:07:51 by aorji             #+#    #+#             */
/*   Updated: 2019/08/21 16:30:44 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/sha384_512.h"


static void init_magic_num()
{
	H[0] = 0x6a09e667f3bcc908;
	H[1] = 0xbb67ae8584caa73b;
	H[2] = 0x3c6ef372fe94f82b;
	H[3] = 0xa54ff53a5f1d36f1;
	H[4] = 0x510e527fade682d1;
	H[5] = 0x9b05688c2b3e6c1f;
	H[6] = 0x1f83d9abfb41bd6b;
	H[7] = 0x5be0cd19137e2179;
}

/*
 * step 1
 */
static void append_padding(uint8_t message[240], size_t from, size_t to)
{
    size_t i = from;
    while(from < to)
    {
        message[from] = PADDING[from - i];
        ++from;
    }
}

/*
 * step 2
 */
static void append_lenght(uint8_t message[240], size_t from, size_t len)
{
	int i = LEN_SIZE - 1;
    while(i >= 0)
    {
        message[from + i] = (uint8_t)(len);
        len = len >> 8;
		--i;
    }
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

/*
 * step 3
 */
static void calculation_procedure(void *message, int times)
{
    int offset = 0;
	int t;
	uint64_t W[80] = {0};
	uint64_t T[2] = {0};

    while ( times-- )
    {
		convert_message(W, (uint64_t *)(message) + offset);
		t = 16;
		while ( t < 80)
		{
			W[t] =	SSIG1(W[t-2]) + W[t-7] + SSIG0(W[t-15]) + W[t-16];
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
enum mode sha512(t_input *input)
{
	static enum mode hash_mode = START;
    (hash_mode == START) ? init_magic_num() : 0;
    if (input->message_size < n)
    {
        if (input->message_size >= a)
        {
            append_padding(input->message, input->message_size, n);
            append_lenght(input->message, g_max_message_len, input->total_size * BIT_NUM);
            calculation_procedure(input->message, 2);
            sha512_output(input, H);
            return hash_mode = FINISH;
        }
        append_padding(input->message, input->message_size, a);
        append_lenght(input->message, a, input->total_size * BIT_NUM);
		calculation_procedure(input->message, 1);
        sha512_output(input, H);
        return hash_mode = FINISH;
    }
    else
    {
        calculation_procedure(input->message, 1);
        return hash_mode = CONTINUE;
    }
}