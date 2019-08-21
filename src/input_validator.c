/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:36:40 by aorji             #+#    #+#             */
/*   Updated: 2019/08/21 16:33:42 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

static char *cmd_arr[] = { "md5", "sha224", "sha256", "sha384", "sha512" };

void		error_output(enum cmd_type cmd, char *name, char *error_str)
{
	if (cmd > 1 && cmd < 5)
		write(2, cmd_arr[cmd - 1], ft_strlen(cmd_arr[cmd - 1]));
	else
		write(2, "ft_ssl", 6);
	write(2, ": ", 2);
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
	int options_num = sizeof(cmd_arr) / sizeof(cmd_arr[0]);
	while (i < options_num)
		if (!ft_strcmp((input->av)[1], cmd_arr[i++]))
			input->cmd_opts = i;
	if (input->cmd_opts >= 4)
	{
		g_buffsize = 128;
		g_max_message_len = 240;
	}
	if (!(input->cmd_opts))
	{
		input->error = INVALIDE_CMD;
		error_output(input->cmd_opts, (input->av)[1],
		" is an invalid command.\nStandard commands:\n\n\
Message Digest commands:\nmd5\nsha256\nsha224\nsha384\nsha512\n\nCipher commands:\n");
	}
}

// static void	param_num(t_input *input)
// {
// 	if (input->ac < 2)
// 	{

// 		write(1, "ft_ssl> ", 8);
// 		char	BUFF[g_buffsize];
// 		char    *resulting_str;
// 		char    *tmp;
		
// 		resulting_str = (char *)malloc(sizeof(char));
// 		while ( 1 )
// 		{
// 			int read_size = read(0, BUFF, g_buffsize);
// 			if (read_size > 0)
// 			{
// 				tmp = ft_strjoin(resulting_str, BUFF);
// 				ft_strdel(&resulting_str);
// 				resulting_str = tmp;
// 				continue;
// 			}
// 			break;
// 		}
// 		tmp = ft_strjoin("ft_ssl ", resulting_str);
// 		ft_strdel(&resulting_str);
// 		resulting_str = tmp;

// 		input->ac = ft_count_words(resulting_str, ' ');
// 		input->av = ft_strsplit(resulting_str, ' ');
// 		ft_strdel(&resulting_str);
// 	}
// }

// void		validate_input(t_input *input)
// {
// 	param_num(input);
// 	cmd_options(input);
// }
