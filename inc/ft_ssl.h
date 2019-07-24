/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:06:17 by aorji             #+#    #+#             */
/*   Updated: 2019/07/24 19:57:07 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

#include "../libft-ft_printf/ft_printf.h"
#include <fcntl.h>
#include <errno.h>
#include <math.h>

# define BUFSIZE 512

enum error_type 
{
    NO_ERROR = 0,
    NO_CMD = 1,
    INVALIDE_CMD = 2,
    INVALIDE_FILE = 3
};

enum cmd_type 
{
    NO_TYPE = 0,
    MD5 = 1,
    SHA256 = 2
};

typedef	struct		s_input
{
    int             ac;
    char            **av;
    t_list          *message;
	enum cmd_type   cmd_opts;
    enum error_type error;
}					t_input;

t_input     *read_message_from_stdin(t_input *);
t_input     *read_message_from_file(t_input *);

int         md5(t_input *);
int         sha256(t_input *);

t_input     *create_input(int ac, char **av);
void        validate_input(t_input *);

void        print_bitset(uint8_t *, size_t);

// queue simulation
void        push_back(t_list **, char *);
t_list      *pop_front(t_list **);

#endif