/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 18:30:25 by aorji             #+#    #+#             */
/*   Updated: 2019/08/28 18:31:51 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

void	read_stdin_cmd(char **resulting_str)
{
	char	buff[g_buffsize];
	int		line_end;
	int		read_size;
	int		total_size;
	char	*tmp;

	total_size = 0;
	while (1)
	{
		read_size = read(0, buff, g_buffsize);
		if (read_size > 0)
		{
			line_end = (buff[read_size - 1] == '\n') ? 1 : 0;
			(buff[read_size - 1] == '\n') ? buff[read_size - 1] = '\0' : 0;
			tmp = fstrjoin(*resulting_str, buff, total_size, read_size);
			ft_strdel(resulting_str);
			*resulting_str = tmp;
			total_size += read_size;
			if (line_end)
				break ;
			continue ;
		}
		break ;
	}
}

void	read_from_file(t_input *input, int fd, int pos)
{
	char	buff[g_buffsize];
	int		read_size;

	while (1)
	{
		read_size = read(fd, buff, g_buffsize);
		if (read_size != -1)
		{
			set_message(input, buff, (input->av)[pos], read_size);
			if (call_hashing_algorithm(input, NULL) == FINISH)
				break ;
		}
		else
		{
			input->error = INVALIDE_PARAM;
			error_output(input, (input->av)[pos], strerror(errno));
			write(2, "\n", 1);
			close(fd);
			continue ;
		}
	}
}
