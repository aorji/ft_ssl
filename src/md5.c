/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:47:21 by aorji             #+#    #+#             */
/*   Updated: 2019/07/18 20:55:34 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

// static void print_bitset(char *str, size_t len)
// {
//     size_t i = 0;
//     while (i < len)
//     {
//         ft_printf("%s ", ft_itoa_base((int)(str[i]), 2));
//         i++;
//     }
//     ft_printf("\n");
// }

// static int ft_padding_len(size_t message_len)
// {
//     int sub = message_len % 512;
//     return ( sub < 448 ) ? (448 - sub) : (960 - sub);
// }

static void append_padding_bits(t_input **input)
{
    input = NULL;
    // for (int i = 2; i < (*input)->ac; ++i)
    // {
    //     t_list *curr_message = pop_front(&((*input)->message));
    //     size_t bit_len = ft_strlen(curr_message->content) * 8;
    //     int bit_padding_len = ft_padding_len(bit_len);
    //     size_t with_padding_len = bit_len/8 + bit_padding_len/8;
    //     curr_message->content = realloc(curr_message->content, with_padding_len);
    //     ((char *)(curr_message->content))[bit_len/8] = 0; // not 0, but 0x80!!
    //     size_t i = bit_len/8 + 1;
    //     while(i < with_padding_len)
    //     {
    //         ((char *)(curr_message->content))[bit_len/8] = 0;
    //         ++i;
    //     }
    //     print_bitset((char *)(curr_message->content), with_padding_len);
    // }
}

int         md5(t_input *input)
{
    ft_printf("\n----------I AM md5----------\n");
    ft_printf("\n-------------RUN------------\n\n");
    append_padding_bits(&input);
    return 1;
}