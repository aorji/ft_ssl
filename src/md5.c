/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:47:21 by aorji             #+#    #+#             */
/*   Updated: 2019/07/30 15:27:30 by aorji            ###   ########.fr       */
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
    AA = 0x67452301;
    BB = 0xefcdab89;
    CC = 0x98badcfe;
    DD = 0x10325476;
}

/*
 * step 3
 */
static void calculation_procedure(t_list **message)
{
    init_magic_num();
    uint32_t *X;                                    /* storage for nth block of 16 32-bit words */
    size_t N = (*message)->content_size / 4;        /* num of 32 bit words in message. should me multip of 16 */
    for (size_t offset = 0; offset < N; offset += 16)
    {
        X = ((uint32_t *)(*message)->content) + offset;
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
}

/*
 * entry piont
 */
int         md5(t_input *input)
{
    int i = 2;
    while (input->message)                              /* hash each file separately */
    {
        t_list  *message = pop_front(&(input->message));
        size_t  message_size = message->content_size;
        int     padding = padding_size(message_size);
        size_t  final_size = message_size + padding + LEN_SIZE;

        realloc_queue_item(&message, final_size);
        append_padding(&message, message_size, message_size + padding);
        append_lenght(&message, message_size + padding, message_size * BIT_NUM);
        calculation_procedure(&message);
        // ft_printf("%x   %x  %x  %x", AA, BB, CC, DD);
        print_result(input->av[i], AA, BB, CC, DD);
        ++i;
    }
    return 0;
}