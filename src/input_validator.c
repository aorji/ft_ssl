/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:36:40 by aorji             #+#    #+#             */
/*   Updated: 2019/08/28 17:51:55 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

static void	hash_fanctions_names(t_input *input)
{
	int i;

	i = 0;
	while (i < NUM_OF_CMD - 1)
	{
		hashing_algorithm[i++](input, "ERROR");
		write(2, "\n", 1);
	}
}

void		error_output(t_input *input, char *name, char *error_str)
{
	if (input->cmd_opts)
		hashing_algorithm[input->cmd_opts - 1](input, "ERROR");
	else
		write(2, "ft_ssl", 6);
	write(2, ": ", 2);
	if (name)
	{
		write(2, name, ft_strlen(name));
		write(2, ": ", 2);
	}
	write(2, error_str, ft_strlen(error_str));
}

void		validate_input(t_input *input)
{
	int i;

	i = 0;
	if (input->error)
		return ;
	while (i < NUM_OF_CMD - 1)
		if (!hashing_algorithm[i++](input, (input->av)[1]))
			input->cmd_opts = i;
	if (input->cmd_opts >= 4)
	{
		g_buffsize = 128;
		g_max_message_len = 240;
	}
	if (!(input->cmd_opts))
	{
		input->error = INVALIDE_CMD;
		error_output(input, (input->av)[1],
		"is an invalid command.\nStandard commands:\n\n\
Message Digest commands:\n");
		hash_fanctions_names(input);
		write(2, "\nCipher commands:\n\n", 19);
	}
}
