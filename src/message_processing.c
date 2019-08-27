/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:48:11 by aorji             #+#    #+#             */
/*   Updated: 2019/08/27 22:05:16 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

static void	hash_string(t_input *input, char *full_message, size_t size)
{
	int	start;
	int	part_size;

	start = 0;
	part_size = 0;
	input->total_size = size;
	while (1)
	{
		if (input->total_size - start < g_buffsize)
			part_size = input->total_size - start;
		else
			part_size = g_buffsize;
		set_message(input, full_message + start, full_message, part_size);
		if (call_hashing_algorithm(input, NULL) == FINISH)
			break ;
		start += g_buffsize;
	}
}

void		process_message_from_stdin(t_input *input)
{
	static int	visited = 0;
	char		buff[g_buffsize];
	char		*resulting_str;
	int			read_size;

	if (visited == 1)
		return ;
	resulting_str = (char *)malloc(sizeof(char));
	visited = 1;
	input->total_size = 0;
	while (1)
	{
		read_size = read(0, buff, g_buffsize);
		if (read_size > 0)
		{
			join_cover(fstrjoin(resulting_str, buff, input->total_size, read_size), &resulting_str);
			input->total_size += read_size;
			continue ;
		}
		break ;
	}
	if (get_flag(input, 'p'))
		write(1, resulting_str, input->total_size);
	hash_string(input, resulting_str, input->total_size);
	ft_strdel(&resulting_str);
}

void		process_message_from_string(t_input *input, int j)
{
	char *message;

	message = NULL;
	if ((input->av)[input->position][j + 1] == '\0')
	{
		if (!(input->av)[input->position + 1])
		{
			input->error = INVALIDE_FLAG;
			error_output(input, NULL, "option requires an argument -- s");
			write(2, usage, 67);
			return ;
		}
		(input->position)++;
		hash_string(input, input->av[input->position],\
		ft_strlen(input->av[input->position]));
	}
	else
	{
		message = ft_strsub(input->av[input->position], j + 1,\
		ft_strlen(input->av[input->position]) - j - 1);
		hash_string(input, message, ft_strlen(message));
		free(message);
	}
}

void		process_message_from_file(t_input *input)
{
	char	buff[g_buffsize];
	int		read_size;
	int		fd;

	for (; input->position < input->ac; ++(input->position))
	{
		input->total_size = get_filesize((input->av)[input->position]);
		fd = open((input->av)[input->position], O_RDONLY);
		if (validate_file(input, fd))
			continue ;
		while (1)
		{
			read_size = read(fd, buff, g_buffsize);
			if (read_size != -1)
			{
				set_message(input, buff, (input->av)[input->position], read_size);
				if (call_hashing_algorithm(input, NULL) == FINISH)
					break ;
			}
			else
			{
				input->error = INVALIDE_PARAM;
				error_output(input, (input->av)[input->position], strerror(errno));
				write(2, "\n", 1);
				close(fd);
				continue ;
			}
		}
		close(fd);
	}
}

void		process_stdin_files(t_input *input)
{
	if (input->read_from == STDIN)
		process_message_from_stdin(input);
	else if (input->read_from == FILE_STRING)
		process_message_from_file(input);
}
