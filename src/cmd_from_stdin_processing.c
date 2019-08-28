/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_from_stdin_processing.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 18:47:18 by aorji             #+#    #+#             */
/*   Updated: 2019/08/28 18:33:25 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

static void	clean_up(char **resulting_str, char **av, int ac)
{
	int k;

	k = 0;
	ft_strdel(resulting_str);
	while (k < ac)
		free(av[k++]);
	free(av);
}

static int	quit_request(char **resulting_str, enum e_mode *read_mode)
{
	if (!ft_strcmp(*resulting_str, "quit"))
	{
		*read_mode = FINISH;
		ft_strdel(resulting_str);
		return (1);
	}
	return (0);
}

void		stdin_cmd_processing(void)
{
	t_input		*input;
	enum e_mode	read_mode;
	char		*resulting_str;
	char		**av;
	int			ac;

	read_mode = CONTINUE;
	while (read_mode != FINISH)
	{
		write(1, "ft_ssl> ", 8);
		resulting_str = (char *)malloc(sizeof(char));
		read_stdin_cmd(&resulting_str);
		if (quit_request(&resulting_str, &read_mode))
			continue;
		join_cover(ft_strjoin("ft_ssl ", resulting_str), &resulting_str);
		av = ft_strsplit(resulting_str, ' ');
		ac = ft_count_words(resulting_str, ' ');
		input = init_input(ac, av);
		run_hash_alg(input);
		clean_up(&resulting_str, av, ac);
		if (input->error)
			break ;
	}
}
