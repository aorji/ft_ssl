/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 13:03:37 by aorji             #+#    #+#             */
/*   Updated: 2019/08/21 17:41:11 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

enum mode	call_hashing_algorithm(t_input *input)
{
	return (*hashing_algorithm[input->cmd_opts - 1])(input);
}

static void run_hash_alg(t_input *input)
{
	validate_input(input);
	process_flags(input);
	if (input->error)
		return;
	process_stdin_files(input);
}

static void stdin_cmd(void)
{
	enum mode read_mode = CONTINUE;
	char	BUFF[g_buffsize];
	char    *resulting_str;
	char    *tmp;
	int total_size = 0;

	while(read_mode != FINISH )
	{
		write(1, "ft_ssl> ", 8);
		resulting_str = (char *)malloc(sizeof(char));
		while ( 1 )
		{
			int d = 0;
			int read_size = read(0, BUFF, g_buffsize);
			if (read_size > 0)
			{
				if (BUFF[read_size - 1] == '\n')
				{
					BUFF[read_size -1 ] = '\0';
					d = 1;
				}
				tmp = fstrjoin(resulting_str, BUFF, total_size, read_size);;
				ft_strdel(&resulting_str);
				resulting_str = tmp;
				if (d)
					break;
				total_size += read_size;
				continue;
			}
			break;
		}
		if (!ft_strcmp(resulting_str, "quit"))
		{
			read_mode = FINISH;
			ft_strdel(&resulting_str);
			continue;
		}
		tmp = ft_strjoin("ft_ssl ", resulting_str);
		ft_strdel(&resulting_str);
		resulting_str = tmp;

		char **av = ft_strsplit(resulting_str, ' ');
		int ac = ft_count_words(resulting_str, ' ');
		t_input *input = init_input(ac, av);
		run_hash_alg(input);


		ft_strdel(&resulting_str);
		free(input);
		input = NULL;
		int k = 0;
		while (k < ac)
			free(av[k++]);
		free(av);
	}
}

int				main(int ac, char **av)
{
	t_input *input = init_input(ac, av);
	g_buffsize = 64;
	g_max_message_len = 120;
	
	if (ac < 2)
		stdin_cmd();
	else
		run_hash_alg(input);
	// system ("leaks ft_ssl");
	return (0);
}
