/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:19:47 by aorji             #+#    #+#             */
/*   Updated: 2019/08/01 17:37:41 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

void print_bitset(uint8_t *str, size_t len)
{
    size_t i = 0;
    while (i < len)
    {
        ft_printf("%s ", ft_itoa_base((int)(str[i]), 2));
        i++;
    }
    ft_printf("\n");
}

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
    if (get_flag(input, 'p'))
        ft_printf("%s", input->message_name);
    else if (input->read_from == FILE_STRING && !get_flag(input, 'q') && !get_flag(input, 'r'))
        ft_printf("MD5 (\"%s\") = ", input->message_name);

    int i = 16;
    while(i--)
    {
        ft_printf("%.2x", (uint8_t)A);
        A >>= 8;
        if (A == 0 && i <= 4) A = D;
        else if (A == 0 && i <= 8) A = C;
        if (A == 0 && i <= 12) A = B;
    }

    if (!get_flag(input, 'q') && !get_flag(input, 'p') && input->read_from == FILE_STRING && get_flag(input, 'r'))
        ft_printf(" \"%s\"", input->message_name);

    set_flag(input, 'p', 0);
    ft_printf("\n");
}
// void print_result(t_input *input, uint32_t A, uint32_t B, uint32_t C, uint32_t D)
// {
//     if (get_flag(input, 'p'))
//         ft_printf("%s", input->message_name);
//     else if (input->read_from == FILE_STRING && !get_flag(input, 'q') && !get_flag(input, 'r'))
//         ft_printf("MD5 (\"%s\") = ", input->message_name);

//     int i = 16;
//     while(i--)
//     {
//         ft_printf("%.2x", (uint8_t)A);
//         A >>= 8;
//         if (A == 0 && i <= 4) A = D;
//         else if (A == 0 && i <= 8) A = C;
//         if (A == 0 && i <= 12) A = B;
//     }
//     if (!get_flag(input, 'q') && !get_flag(input, 'p') && input->read_from == FILE_STRING && get_flag(input, 'r'))
//         ft_printf(" \"%s\"", input->message_name);

//     if (get_flag(input, 'p'))
//         set_flag(input, 'p', 0);
//     ft_printf("\n");
// }
