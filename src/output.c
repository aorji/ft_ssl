/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 13:27:24 by aorji             #+#    #+#             */
/*   Updated: 2019/08/19 14:19:59 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

void output_after_checksum(t_input *input)
{
    if (!get_flag(input, 'p') && !get_flag(input, 'q') && get_flag(input, 'r'))
    {
        if (get_flag(input, 's'))
        {
            ft_printf(" \"%s\"", input->message_name);;
            set_flag(input, 's', 0);   
        }
        else
            ft_printf(" *%s", input->message_name);
    }
}

void output_before_checksum(t_input *input, const char *cmd_name)
{
    if (!get_flag(input, 'p') && !get_flag(input, 'q') && !get_flag(input, 'r'))
    {
        if (get_flag(input, 's'))
        {
            ft_printf("%s(\"%s\") = ", cmd_name, input->message_name);;
            set_flag(input, 's', 0);   
        }
        else
            ft_printf("%s(%s) = ", cmd_name, input->message_name);
    }
}