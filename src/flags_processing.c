/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 14:41:54 by aorji             #+#    #+#             */
/*   Updated: 2019/08/28 18:00:09 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

static void		error(t_input *input, char flag)
{
	error_output(input, NULL, "illegal option -- ");
	write(2, &flag, 1);
	write(2, USAGE, ft_strlen(USAGE));
}

static void		add_flag(t_input *input)
{
	size_t	j;
	char	flag;

	j = 1;
	flag = (input->av)[input->position][j];
	while (flag)
	{
		if (flag < input->flags_opt[0] || flag > input->flags_opt[FLAG_NUM - 1])
		{
			input->error = INVALIDE_FLAG;
			error(input, flag);
			return ;
		}
		set_flag(input, flag, 1);
		if (flag == 's')
		{
			input->read_from = FILE_STRING;
			process_message_from_string(input, j);
			return ;
		}
		else if (flag == 'p')
			process_message_from_stdin(input);
		j++;
		flag = (input->av)[input->position][j];
	}
}

void			process_flags(t_input *input)
{
	while (input->position < input->ac && \
	(input->av)[input->position][0] == '-' && !(input->error))
	{
		add_flag(input);
		input->position++;
	}
	if (input->position < input->ac)
		input->read_from = FILE_STRING;
}
