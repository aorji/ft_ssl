/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 15:30:17 by aorji             #+#    #+#             */
/*   Updated: 2019/08/12 15:35:58 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

size_t	get_filesize(const char *filename)
{
	struct stat st;

	stat(filename, &st);
	return (st.st_size);
}

size_t	is_dir(const char *filename)
{
	struct stat st;

	stat(filename, &st);
	return (S_ISDIR(st.st_mode));
}

int		validate_file(t_input *input, int fd)
{
	if (fd == -1)
	{
		error_output(input->cmd_opts, (input->av)[input->position],\
		strerror(errno));
		return (1);
	}
	if (is_dir((input->av)[input->position]))
	{
		error_output(input->cmd_opts, (input->av)[input->position],\
		"Is a directory");
		close(fd);
		return (1);
	}
	return (0);
}
