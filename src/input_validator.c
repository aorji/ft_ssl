/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:36:40 by aorji             #+#    #+#             */
/*   Updated: 2019/08/16 19:32:31 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

void		error_output(enum cmd_type cmd, char *name, char *error_str)
{
	if (cmd == MD5)
		write(2, "md5: ", 5);
	else if (cmd == SHA256)
		write(2, "sha256: ", 8);
	else
		write(2, "ft_ssl: ", 8);
	if (name)
	{
		write(2, name, ft_strlen(name));
		write(2, ": ", 2);
	}
	write(2, error_str, ft_strlen(error_str));
	write(2, "\n", 1);
}

static void	cmd_options(t_input *input)
{
	if (input->error)
		return ;
	if (!ft_strcmp((input->av)[1], "md5"))
		input->cmd_opts = 1;
	else if (!ft_strcmp((input->av)[1], "sha256"))
		input->cmd_opts = 2;
	else
	{
		input->error = INVALIDE_CMD;
		error_output(input->cmd_opts, (input->av)[1],
		" is an invalid command.\nStandard commands:\n\n\
Message Digest commands:\nmd5\nsha256\n\nCipher commands:\n");
	}
}

static void	param_num(t_input *input)
{
	if (input->ac < 2)
	{
		input->error = NO_CMD;
		ft_printf("%s",\
"usage: ft_ssl command [command opts] [command args]\n");
	}
}

void		validate_input(t_input *input)
{
	param_num(input);
	cmd_options(input);
}
