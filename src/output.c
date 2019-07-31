/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:19:47 by aorji             #+#    #+#             */
/*   Updated: 2019/07/31 17:54:01 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

// void print_bitset(uint8_t *str, size_t len)
// {
//     size_t i = 0;
//     while (i < len)
//     {
//         ft_printf("%s ", ft_itoa_base((int)(str[i]), 2));
//         i++;
//     }
//     ft_printf("\n");
// }

void print_xset(uint8_t *str, size_t len)
{
    size_t i = 0;
    while (i < len)
    {
        ft_printf("%x ", (int)(str[i]));
        i++;
    }
    ft_printf("\n");
}

void print_result(t_input *input, uint32_t A, uint32_t B, uint32_t C, uint32_t D)
{
    if (input->message_name)
    {
        ft_printf("MD5 (%s) = ", input->message_name->content);
        input->message_name = input->message_name->next; 
    }
    int i = 16;
    while(i--)
    {
        ft_printf("%.2x", (uint8_t)A);
        A >>= 8;
        if (A == 0 && i <= 4) A = D;
        else if (A == 0 && i <= 8) A = C;
        if (A == 0 && i <= 12) A = B;
    }
    ft_printf("\n");
}