/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:47:21 by aorji             #+#    #+#             */
/*   Updated: 2019/07/26 16:07:49 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/md5.h"

static int padding_size(size_t message_size)
{
    int sub = message_size % n;
    return ( sub < a ) ? (a - sub) : (a + n - sub);
}

/*
 * step 1
 */
static void append_padding(t_list **message, size_t from, size_t to)
{
    size_t i = from;
    while(from < to)
    {
        ((uint8_t *)((*message)->content))[from] = PADDING[from - i];
        ++from;
    }
}

/*
 * step 2
 */
static void append_lenght(t_list **message, size_t from, size_t len)
{
    for(int i = 0; len != 0; ++i)
    {
        ((uint8_t *)(*message)->content)[from + i] = (uint8_t)(len);
        len = len >> 8;
    }
}
    
static void init_magic_num()
{
    A = 0x67452301;
    B = 0xefcdab89;
    C = 0x98badcfe;
    D = 0x10325476;
}

/*
 * step 3
 */
static void calculation_procedure(t_list **message)
{
    init_magic_num();
    uint32_t *X;                             /* storage for nth block of 16 32-bit words */
    size_t N = (*message)->content_size / 4;    /* byte_len * 8 => bit_len; bit_len / 32 => num of 32-bit words */

    for (size_t i = 0; i < N/16; ++i)           /* process each 16-word block. */
    {
        X = ((*message)->content) + (i * 16);       /* copy i-th block of 16 32-bit words into X */

        int32_t AA = A;
        int32_t BB = B;
        int32_t CC = C;
        int32_t DD = D;
        uint32_t res;

        for (int i = 0; i < 64; ++i)
        {
            if (i < 16)
                res = F(B, C, D);
            else if (i < 32)
                res = G(B, C, D);
            else if (i < 48)
                res = H(B, C, D);
            else
                res = I(B, C, D);
            res += A + T[i] + X[x[i]];
            A = D;
            D = C;
            C = B;
            B = B + ROTATE_LEFT(res, s[i]);
        }
        A += AA;
        B += BB;
        C += CC;
        D += DD;
        // ft_printf("b=%x    %x  %x  %x\n", A, B, C, D);
    }
}

/*
 * entry piont
 */
int         md5(t_input *input)
{
    int i = 2;
    while (input->message)                         /* hash each file separately */
    {
        t_list  *message = pop_front(&(input->message));
        size_t  message_size = message->content_size;
        int     padding = padding_size(message_size);
        size_t  final_size = message_size + padding + LEN_SIZE;

        realloc_queue_item(&message, final_size);
        
        append_padding(&message, message_size, message_size + padding);
        append_lenght(&message, message_size + padding, message_size * BIT_NUM);
        calculation_procedure(&message);
        ft_printf("MD5 (%s) = %x    %x  %x  %x\n", input->av[i], A, B, C, D);

        ++i;
    }
    return 0;
}