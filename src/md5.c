/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:47:21 by aorji             #+#    #+#             */
/*   Updated: 2019/07/19 18:05:36 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

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
    ((uint8_t *)((*message)->content))[bit_len/8] = 0x80;
    size_t i = bit_len/8 + 1;
    while(i < new_len)
    {
        ((uint8_t *)((*message)->content))[i] = 0;
        ++i;
    }
    return new_len;
}

// static size_t appent_lenght(t_list **message)
// {
//     void *len = (*message)->content_size;
//     print_bitset(len, (int)4);
//     return 0;
// }

int         md5(t_input *input)
{
    ft_printf("\n----------I AM md5----------\n");
    ft_printf("\n-------------RUN------------\n\n");

    //hash each file separately
    for (int i = 2; i < input->ac; ++i)
    {
        t_list *curr_message = pop_front(&(input->message));
        
        ft_printf("before step 1\n");
        print_bitset(curr_message->content, curr_message->content_size);
        
        //step 1
        size_t new_len = append_padding_bits(&curr_message);
        
        ft_printf("after step 1\n");
        print_bitset(curr_message->content, new_len);

        //step 2
        // appent_lenght(&curr_message);

    }
    return 1;
}