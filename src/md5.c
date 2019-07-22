/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:47:21 by aorji             #+#    #+#             */
/*   Updated: 2019/07/22 21:29:00 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

static unsigned char PADDING[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static void print_bitset(uint8_t *str, size_t len)
{
    size_t i = 0;
    while (i < len)
    {
        ft_printf("%s ", ft_itoa_base((int)(str[i]), 2));
        i++;
    }
    ft_printf("\n");
}

static int ft_padding_len(size_t message_len)
{
    int sub = message_len % 512;
    return ( sub < 448 ) ? (448 - sub) : (960 - sub);
}

static size_t append_padding_bits(t_list **message)
{
    size_t bit_len = (*message)->content_size * 8;
    int padding_bit_len = ft_padding_len(bit_len);
    size_t new_len = bit_len/8 + padding_bit_len/8;

    (*message)->content = realloc((*message)->content, new_len);
    size_t i = bit_len/8;
    while(i < new_len)
    {
        ((uint8_t *)((*message)->content))[i] = PADDING[i - bit_len/8];
        ++i;
    }
    return new_len;
}

static size_t appent_lenght(t_list **message, size_t new_len)
{
    size_t len = (*message)->content_size;
    (*message)->content = realloc((*message)->content, new_len + 8);        //64-bit representation of the length of the alignment data
    for(int j = 7; j >= 0; --j)
    {
        ((uint8_t *)((*message)->content))[new_len + j] = (uint8_t)len;
        len = len >> 8;
    }
    return 0;
}

int         md5(t_input *input)
{
    ft_printf("\n----------I AM md5----------\n");
    ft_printf("\n-------------RUN------------\n\n");

    //hash each file separately
    while (input->message)
    {
        t_list *curr_message = pop_front(&(input->message));
        ft_printf("\n%s\n", curr_message->content);
        print_bitset(curr_message->content, curr_message->content_size);
        
        //step 1
        ft_printf("step 1: ");
        size_t new_len = append_padding_bits(&curr_message);
        print_bitset(curr_message->content, new_len);

        // step 2
        ft_printf("step 2: ");
        appent_lenght(&curr_message, new_len);
        print_bitset(curr_message->content, new_len + 8);

    }
    return 1;
}