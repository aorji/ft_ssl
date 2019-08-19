/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:47:21 by aorji             #+#    #+#             */
/*   Updated: 2019/08/19 17:10:06 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/md5.h"

static void init_magic_num()
{
    H[0] = 0x67452301;
    H[1] = 0xefcdab89;
    H[2] = 0x98badcfe;
    H[3] = 0x10325476;
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
    for(int i = 0; i < 8; ++i)      /* 8 time by 8 bits => 64-bit of the length of the message is appended */
    {
        ((uint8_t *)message)[from + i] = (uint8_t)(len);
        len = len >> 8;
    }
}
    
/*
 * step 3
 */
static void calculation_procedure(void *message, int times)
{
    int offset = 0;
    while ( times-- )
    {
        uint32_t *X = (uint32_t *)(message) + offset;
        HH[0] = H[0];
        HH[1] = H[1];
        HH[2] = H[2];
        HH[3] = H[3];
        for (int j = 0; j < 64; ++j)
        {
            if (j < 16)
                HH[0] += F(HH[1], HH[2], HH[3]);
            else if (j < 32)
                HH[0] += G(HH[1], HH[2], HH[3]);
            else if (j < 48)
                HH[0] += H(HH[1], HH[2], HH[3]);
            else
                HH[0] += I(HH[1], HH[2], HH[3]);
            uint32_t tmp = HH[0] + T[j] + X[x[j]];
            HH[0] = HH[3];
            HH[3] = HH[2];
            HH[2] = HH[1];
            HH[1] = HH[1] + ROTATE_LEFT(tmp, s[j]);
        }
        H[0] += HH[0];
        H[1] += HH[1];
        H[2] += HH[2];
        H[3] += HH[3];
        offset += 16;
    }
}

/*
 * entry piont
 */
enum hash_mode md5(t_input *input)
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
            md5_output(input, H);
            return mode = FINISH;
        }
        append_padding(input->message, input->message_size, a);
        append_lenght(input->message, a, input->total_size * BIT_NUM);
        calculation_procedure(input->message, 1);
        md5_output(input, H);
        return mode = FINISH;
    }
    else
    {
        calculation_procedure(input->message, 1);
        return mode = CONTINUE;
    }
}