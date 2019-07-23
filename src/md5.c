/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:47:21 by aorji             #+#    #+#             */
/*   Updated: 2019/07/23 21:07:04 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/md5.h"

static int ft_padding_len(size_t message_len)
{
    int sub = message_len % n;
    return ( sub < a ) ? (a - sub) : (a + n - sub);
}

/*
 * step 1
 */
static void append_padding_bits(t_list **message, size_t from, size_t to)
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
static void append_lenght(t_list **message, size_t from, size_t len) //CHECK ORDER
{
    for(size_t i = (*message)->content_size - 1; i >= from; --i)
    {
        ((uint8_t *)((*message)->content))[i] = (uint8_t)len;
        len = len >> BIT_NUM;
    }
}

/*
 * step 3
 */
int T(int i)
{
    return (int)(4294967296 * ((int)sin(i)));
}

void func(t_list **message)
{
    N = (*message)->content_size / 4;   /* 
                                         * message_byte_len * 8 => message_bit len;
                                         * message_bit_len / 32 => num of 32-bit words in message;
                                         */

    uint32_t *X = (uint32_t *)malloc(sizeof(uint32_t) * 16);
    /* Process each 16-word block. */
    for (size_t i = 0; i < N/16; ++i)
    {
        /* Copy block of 16 32-bit words into X. */
        for (int j = 0; j < 16; ++j)
        {
            X[j] = ((uint32_t *)((*message)->content))[i * 16 + j];
        }
        int32_t AA = A;
        int32_t BB = B;
        int32_t CC = C;
        int32_t DD = D;

        /* Round 1 */
        int i = 0, j = 7;
        for (int k = 0; k < 16; ++k)
        {
            FF(A, B, C, D, X[i], j, T(i + 1));
        }
        ft_printf("T[1] = %ld    %ld", T(1), 0xd76aa478);
        ft_printf("T[1] = %ld    %ld", T(2), 0xe8c7b756);
        // FF (A, B, C, D, X[0], S11, 0xd76aa478); /* 1 */
        // FF (D, A, B, C, X[1], S12, 0xe8c7b756); /* 2 */
        // FF (C, D, A, B, X[2], S13, 0x242070db); /* 3 */
        // FF (B, C, D, A, X[3], S14, 0xc1bdceee); /* 4 */
        // FF (A, B, C, D, X[4], S11, 0xf57c0faf); /* 5 */
        // FF (D, A, B, C, X[5], S12, 0x4787c62a); /* 6 */
        // FF (C, D, A, B, X[6], S13, 0xa8304613); /* 7 */
        // FF (B, C, D, A, X[7], S14, 0xfd469501); /* 8 */
        // FF (A, B, C, D, X[8], S11, 0x698098d8); /* 9 */
        // FF (D, A, B, C, X[9], S12, 0x8b44f7af); /* 10 */
        // FF (C, D, A, B, X[10], S13, 0xffff5bb1); /* 11 */
        // FF (B, C, D, A, X[11], S14, 0x895cd7be); /* 12 */
        // FF (A, B, C, D, X[12], S11, 0x6b901122); /* 13 */
        // FF (D, A, B, C, X[13], S12, 0xfd987193); /* 14 */
        // FF (C, D, A, B, X[14], S13, 0xa679438e); /* 15 */
        // FF (B, C, D, A, X[15], S14, 0x49b40821); /* 16 */

        // /* Round 2 */
        // GG (A, B, C, D, X[1], S21, 0xf61e2562); /* 17 */
        // GG (D, A, B, C, X[6], S22, 0xc040b340); /* 18 */
        // GG (C, D, A, B, X[11], S23, 0x265e5a51); /* 19 */
        // GG (B, C, D, A, X[0], S24, 0xe9b6c7aa); /* 20 */
        // GG (A, B, C, D, X[5], S21, 0xd62f105d); /* 21 */
        // GG (D, A, B, C, X[10], S22,  0x2441453); /* 22 */
        // GG (C, D, A, B, X[15], S23, 0xd8a1e681); /* 23 */
        // GG (B, C, D, A, X[4], S24, 0xe7d3fbc8); /* 24 */
        // GG (A, B, C, D, X[9], S21, 0x21e1cde6); /* 25 */
        // GG (D, A, B, C, X[14], S22, 0xc33707d6); /* 26 */
        // GG (C, D, A, B, X[3], S23, 0xf4d50d87); /* 27 */
        // GG (B, C, D, A, X[8], S24, 0x455a14ed); /* 28 */
        // GG (A, B, C, D, X[13], S21, 0xa9e3e905); /* 29 */
        // GG (D, A, B, C, X[2], S22, 0xfcefa3f8); /* 30 */
        // GG (C, D, A, B, X[7], S23, 0x676f02d9); /* 31 */
        // GG (B, C, D, A, X[12], S24, 0x8d2a4c8a); /* 32 */

        // /* Round 3 */
        // HH (A, B, C, D, X[5], S31, 0xfffa3942); /* 33 */
        // HH (D, A, B, C, X[8], S32, 0x8771f681); /* 34 */
        // HH (C, D, A, B, X[11], S33, 0x6d9d6122); /* 35 */
        // HH (B, C, D, A, X[14], S34, 0xfde5380c); /* 36 */
        // HH (A, B, C, D, X[1], S31, 0xa4beea44); /* 37 */
        // HH (D, A, B, C, X[4], S32, 0x4bdecfa9); /* 38 */
        // HH (C, D, A, B, X[7], S33, 0xf6bb4b60); /* 39 */
        // HH (B, C, D, A, X[10], S34, 0xbebfbc70); /* 40 */
        // HH (A, B, C, D, X[13], S31, 0x289b7ec6); /* 41 */
        // HH (D, A, B, C, X[0], S32, 0xeaa127fa); /* 42 */
        // HH (C, D, A, B, X[3], S33, 0xd4ef3085); /* 43 */
        // HH (B, C, D, A, X[6], S34,  0x4881d05); /* 44 */
        // HH (A, B, C, D, X[9], S31, 0xd9d4d039); /* 45 */
        // HH (D, A, B, C, X[12], S32, 0xe6db99e5); /* 46 */
        // HH (C, D, A, B, X[15], S33, 0x1fa27cf8); /* 47 */
        // HH (B, C, D, A, X[2], S34, 0xc4ac5665); /* 48 */

        // /* Round 4 */
        // II (A, B, C, D, X[0], S41, 0xf4292244);
        // II (D, A, B, C, X[7], S42, 0x432aff97);
        // II (C, D, A, B, X[14], S43, 0xab9423a7);
        // II (B, C, D, A, X[5], S44, 0xfc93a039);
        // II (A, B, C, D, X[12], S41, 0x655b59c3);
        // II (D, A, B, C, X[3], S42, 0x8f0ccc92);
        // II (C, D, A, B, X[10], S43, 0xffeff47d);
        // II (B, C, D, A, X[1], S44, 0x85845dd1);
        // II (A, B, C, D, X[8], S41, 0x6fa87e4f);
        // II (D, A, B, C, X[15], S42, 0xfe2ce6e0);
        // II (C, D, A, B, X[6], S43, 0xa3014314);
        // II (B, C, D, A, X[13], S44, 0x4e0811a1);
        // II (A, B, C, D, X[4], S41, 0xf7537e82);
        // II (D, A, B, C, X[11], S42, 0xbd3af235);
        // II (C, D, A, B, X[2], S43, 0x2ad7d2bb);
        // II (B, C, D, A, X[9], S44, 0xeb86d391);

        A = A + AA;
        B = B + BB;
        C = C + CC;
        D = D + DD;
    }
    // for(int i =  0; i < 16; ++i)
    //     ft_printf("%d\n", X[i]);
    // print_bitset((uint8_t *)X, 4*16);
        ft_printf("%d\n", A + B + C + D);
}

/*
 * entry piont
 */
int         md5(t_input *input)
{
    ft_printf("\n----------I AM md5----------\n");
    ft_printf("\n-------------RUN------------\n\n");

    //hash each file separately
    while (input->message)
    {
        //get message from queue
        t_list *curr_message = pop_front(&(input->message));
        size_t message_len = curr_message->content_size;
        ft_printf("\n%s\n        ", curr_message->content);
        print_bitset(curr_message->content, curr_message->content_size);
        
        //realloc message->content to have enough memmory for step1 and step2 
        size_t message_bit_len = curr_message->content_size * BIT_NUM;
        int padding_bit_len = ft_padding_len(message_bit_len);
        curr_message->content = realloc(curr_message->content, curr_message->content_size + padding_bit_len/BIT_NUM + b/BIT_NUM);
        curr_message->content_size = curr_message->content_size + padding_bit_len/BIT_NUM + b/BIT_NUM;
        
        //step 1
        ft_printf("step 1: ");
        append_padding_bits(&curr_message, message_len, message_len + padding_bit_len/BIT_NUM);
        print_bitset(curr_message->content, curr_message->content_size - b/BIT_NUM);

        // step 2
        ft_printf("step 2: ");
        append_lenght(&curr_message, message_len + padding_bit_len/BIT_NUM, message_len);
        print_bitset(curr_message->content, curr_message->content_size);

        func(&curr_message);
    }
    return 1;
}