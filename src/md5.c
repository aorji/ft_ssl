/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:47:21 by aorji             #+#    #+#             */
/*   Updated: 2019/08/08 16:26:28 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/md5.h"

static void init_magic_num()
{
    AA = 0x67452301;
    BB = 0xefcdab89;
    CC = 0x98badcfe;
    DD = 0x10325476;
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
static void calculation_procedure(void *message)
{
        uint32_t *X = ((uint32_t *)message);
        uint32_t A = AA;
        uint32_t B = BB;
        uint32_t C = CC;
        uint32_t D = DD;
        for (int j = 0; j < 64; ++j)
        {
            if (j < 16)
                A += F(B, C, D);
            else if (j < 32)
                A += G(B, C, D);
            else if (j < 48)
                A += H(B, C, D);
            else
                A += I(B, C, D);
            uint32_t tmp = A + T[j] + X[x[j]];
            A = D;
            D = C;
            C = B;
            B = B + ROTATE_LEFT(tmp, s[j]);
        }
        AA += A;
        BB += B;
        CC += C;
        DD += D;
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
        input->message = realloc(input->message, n);
        append_padding(input->message, input->message_size, 56);
        append_lenght(input->message, 56, input->total_size * BIT_NUM);
        calculation_procedure(input->message);
        print_result(input, AA, BB, CC, DD);
        free(input->message);
        return mode = FINISH;
    }
    else
    {
        calculation_procedure(input->message);
        free(input->message);
        return mode = CONTINUE;
    }
}