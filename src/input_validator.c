/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:36:40 by aorji             #+#    #+#             */
/*   Updated: 2019/08/27 14:33:40 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

void		error_output(char *name, char *error_str)
{
	write(2, "ft_ssl: ", 8);
	if (name)
	{
		write(2, name, ft_strlen(name));
		write(2, ": ", 2);
	}
	write(2, error_str, ft_strlen(error_str));
	write(2, "\n", 1);
}

void	validate_input(t_input *input)
{

	if (input->error)
		return ;
	int i = 0;
	while (i < NUM_OF_CMD - 1)
		if ( !hashing_algorithm[i++](input, (input->av)[1]) )
			input->cmd_opts = i;
	if (input->cmd_opts >= 4)
	{
		g_buffsize = 128;
		g_max_message_len = 240;
	}
	if (!(input->cmd_opts))
	{
		input->error = INVALIDE_CMD;
		error_output((input->av)[1],
		" is an invalid command.\nStandard commands:\n\n\
Message Digest commands:\nmd5\nsha256\nsha224\nsha384\nsha512\n\nCipher commands:\n");
	}
}
