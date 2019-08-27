/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 17:51:47 by aorji             #+#    #+#             */
/*   Updated: 2019/08/27 12:54:42 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

void	output_after_checksum(t_input *input)
{
	if (!get_flag(input, 'p') && !get_flag(input, 'q') && get_flag(input, 'r'))
	{
		if (get_flag(input, 's'))
		{
			ft_printf(" \"%s\"", input->message_name);
			set_flag(input, 's', 0);
		}
		else
			ft_printf(" *%s", input->message_name);
	}
}

void	output_before_checksum(t_input *input, const char *cmd_name)
{
	if (!get_flag(input, 'p') && !get_flag(input, 'q') && !get_flag(input, 'r'))
	{
		if (get_flag(input, 's'))
		{
			ft_printf("%s(\"%s\") = ", cmd_name, input->message_name);
			set_flag(input, 's', 0);
		}
		else
			ft_printf("%s(%s) = ", cmd_name, input->message_name);
	}
}
