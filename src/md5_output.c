/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:19:47 by aorji             #+#    #+#             */
/*   Updated: 2019/08/14 19:56:20 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

static void after_checksum(t_input *input)
{
    if (!get_flag(input, 'p') && !get_flag(input, 'q') && get_flag(input, 'r'))
    {
        if (get_flag(input, 's'))
        {
            ft_printf(" \"%s\"", input->message_name);;
            set_flag(input, 's', 0);   
        }
        else
            ft_printf(" %s", input->message_name);
    }
}

static void before_checksum(t_input *input)
{
    if (!get_flag(input, 'p') && !get_flag(input, 'q') && !get_flag(input, 'r'))
    {
        if (get_flag(input, 's'))
        {
            ft_printf("MD5 (\"%s\") = ", input->message_name);;
            set_flag(input, 's', 0);   
        }
        else
            ft_printf("MD5 (%s) = ", input->message_name);
    }
}

void md5_output(t_input *input, uint32_t A, uint32_t B, uint32_t C, uint32_t D)
{
    before_checksum(input);
    int i = 16;
    while(i--)
    {
        ft_printf("%.2x", (uint8_t)A);
        A >>= 8;
        if (i == 4) A = D;
        else if (i == 8) A = C;
        else if (i == 12) A = B;
    }
    after_checksum(input);
    ft_printf("\n");
}