/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:47:21 by aorji             #+#    #+#             */
/*   Updated: 2019/07/24 18:47:29 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/md5.h"

static int ft_padding_len(size_t message_len)
{
    int sub = message_len % n;
    return ( sub < a ) ? (a - sub) : (a + n - sub);
}

static void append_padding_bits(t_list **message, size_t from, size_t to)
{
    size_t i = from;
    while(from < to)
    {
        ((uint8_t *)((*message)->content))[from] = PADDING[from - i];
        ++from;
    }
}

static void round_1(uint32_t X[16])
{
    FF(A, B, C, D, X[ 0], S11, T[1]);
    FF(D, A, B, C, X[ 1], S12, T[2]);
    FF(C, D, A, B, X[ 2], S13, T[3]);
    FF(B, C, D, A, X[ 3], S14, T[4]);
    FF(A, B, C, D, X[ 4], S11, T[5]);
    FF(D, A, B, C, X[ 5], S12, T[6]);
    FF(C, D, A, B, X[ 6], S13, T[7]);
    FF(B, C, D, A, X[ 7], S14, T[8]);
    FF(A, B, C, D, X[ 8], S11, T[9]);
    FF(D, A, B, C, X[ 9], S12, T[10]);
    FF(C, D, A, B, X[10], S13, T[11]);
    FF(B, C, D, A, X[11], S14, T[12]);
    FF(A, B, C, D, X[12], S11, T[13]);
    FF(D, A, B, C, X[13], S12, T[14]);
    FF(C, D, A, B, X[14], S13, T[15]);
    FF(B, C, D, A, X[15], S14, T[16]); 
}

static void round_2(uint32_t X[16])
{
    GG(A, B, C, D, X[ 1], S21, T[17]);
    GG(D, A, B, C, X[ 6], S22, T[18]);
    GG(C, D, A, B, X[11], S23, T[19]);
    GG(B, C, D, A, X[ 0], S24, T[20]);
    GG(A, B, C, D, X[ 5], S21, T[21]);
    GG(D, A, B, C, X[10], S22, T[22]);
    GG(C, D, A, B, X[15], S23, T[23]);
    GG(B, C, D, A, X[ 4], S24, T[24]);
    GG(A, B, C, D, X[ 9], S21, T[25]);
    GG(D, A, B, C, X[14], S22, T[26]);
    GG(C, D, A, B, X[ 3], S23, T[27]);   
    GG(B, C, D, A, X[ 8], S24, T[28]);
    GG(A, B, C, D, X[13], S21, T[29]);
    GG(D, A, B, C, X[ 2], S22, T[30]);
    GG(C, D, A, B, X[ 7], S23, T[31]);
    GG(B, C, D, A, X[12], S24, T[32]); 
}

static void round_3(uint32_t X[16])
{
    HH(A, B, C, D, X[ 5], S31, T[33]);
    HH(D, A, B, C, X[ 8], S32, T[34]);
    HH(C, D, A, B, X[11], S33, T[35]);
    HH(B, C, D, A, X[14], S34, T[36]);
    HH(A, B, C, D, X[ 1], S31, T[37]);
    HH(D, A, B, C, X[ 4], S32, T[38]);
    HH(C, D, A, B, X[ 7], S33, T[39]);
    HH(B, C, D, A, X[10], S34, T[40]);
    HH(A, B, C, D, X[13], S31, T[41]);
    HH(D, A, B, C, X[ 0], S32, T[42]);
    HH(C, D, A, B, X[ 3], S33, T[43]);
    HH(B, C, D, A, X[ 6], S34, T[44]);
    HH(A, B, C, D, X[ 9], S31, T[45]);
    HH(D, A, B, C, X[12], S32, T[46]);
    HH(C, D, A, B, X[15], S33, T[47]);
    HH(B, C, D, A, X[ 2], S34, T[48]);
}

static void round_4(uint32_t X[16])
{
    II(A, B, C, D, X[ 0], S41, T[49]);
    II(D, A, B, C, X[ 7], S42, T[50]);
    II(C, D, A, B, X[14], S43, T[51]);
    II(B, C, D, A, X[ 5], S44, T[52]);
    II(A, B, C, D, X[12], S41, T[53]);
    II(D, A, B, C, X[ 3], S42, T[54]);
    II(C, D, A, B, X[10], S43, T[55]);
    II(B, C, D, A, X[ 1], S44, T[56]);
    II(A, B, C, D, X[ 8], S41, T[57]);
    II(D, A, B, C, X[15], S42, T[58]);
    II(C, D, A, B, X[ 6], S43, T[59]);
    II(B, C, D, A, X[13], S44, T[60]);
    II(A, B, C, D, X[ 4], S41, T[61]);
    II(D, A, B, C, X[11], S42, T[62]);
    II(C, D, A, B, X[ 2], S43, T[63]);
    II(B, C, D, A, X[ 9], S44, T[64]);
}

/*
 * step 3
 */
static void calculation_procedure(t_list **message)
{
    size_t N = (*message)->content_size / 4;    /* byte_len * 8 => bit_len; bit_len / 32 => num of 32-bit words */

    uint32_t X[16];                             /* storage for nth block of 16 32-bit words */
    for (size_t i = 0; i < N/16; ++i)           /* process each 16-word block. */
    {
        int32_t AA = A;
        int32_t BB = B;
        int32_t CC = C;
        int32_t DD = D;

        for (int j = 0; j < 16; ++j)            /* copy block of 16 32-bit words into X */
        {
            X[j] = ((uint32_t *)((*message)->content))[i * 16 + j];
        }

        round_1(X);                             /* Round 1 */
        round_2(X);                             /* Round 2 */
        round_3(X);                             /* Round 3 */
        round_4(X);                             /* Round 4 */
        
        A = A + AA;
        B = B + BB;
        C = C + CC;
        D = D + DD;
    }
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
        size_t final_len = curr_message->content_size + padding_bit_len/BIT_NUM + b/BIT_NUM;
        curr_message->content = realloc(curr_message->content, final_len);
        curr_message->content_size = final_len;
        
        /* step 1 */
        ft_printf("step 1: ");
        append_padding_bits(&curr_message, message_len, message_len + padding_bit_len/BIT_NUM);
        print_bitset(curr_message->content, curr_message->content_size - b/BIT_NUM);

        /*
         * step 2
         * append lenght 
         */
        ft_printf("step 2: ");
        ft_memcpy(curr_message->content + message_len + padding_bit_len/8, &message_len, 8);
        print_bitset(curr_message->content, curr_message->content_size);

        /* step 3 */
        ft_printf("step 3: ");
        A = A_;                                                     /* init magic numbers */
        B = B_;
        C = C_;
        D = D_;
        calculation_procedure(&curr_message);
        ft_printf("%x %x  %x  %x\n", A, B, C, D);
    }
    return 1;
}