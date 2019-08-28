/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 13:03:37 by aorji             #+#    #+#             */
/*   Updated: 2019/08/28 16:31:31 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

enum e_mode	call_hashing_algorithm(t_input *input, char *func_name)
{
	return (*hashing_algorithm[input->cmd_opts - 1])(input, func_name);
}

void		run_hash_alg(t_input *input)
{
	validate_input(input);
	process_flags(input);
	if (input->error)
	{
		free(input);
		input = NULL;
		return ;
	}
	process_stdin_files(input);
	free(input);
	input = NULL;
}

/*
**	system("leaks ft_ssl");
*/

int			main(int ac, char **av)
{
	g_buffsize = 64;
	g_max_message_len = 120;
	if (ac < 2)
		stdin_cmd_processing();
	else
		run_hash_alg(init_input(ac, av));
	return (0);
}
