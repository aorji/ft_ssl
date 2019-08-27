/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 15:30:17 by aorji             #+#    #+#             */
/*   Updated: 2019/08/27 16:59:19 by aorji            ###   ########.fr       */
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
		input->error = INVALIDE_PARAM;
		error_output(input, (input->av)[input->position], strerror(errno));
		write(2, "\n", 1);
		return (1);
	}
	if (is_dir((input->av)[input->position]))
	{
		input->error = INVALIDE_PARAM;
		error_output(input, (input->av)[input->position], "Is a directory");
		write(2, "\n", 1);
		close(fd);
		return (1);
	}
	return (0);
}
