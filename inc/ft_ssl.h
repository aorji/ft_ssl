/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:06:17 by aorji             #+#    #+#             */
/*   Updated: 2019/07/31 17:46:26 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

#include "../libft-ft_printf/ft_printf.h"
#include <fcntl.h>
#include <errno.h>
#include <math.h>

# define BUFSIZE 512
# define no_arg_flag_num 4

// typedef long double		t_vector __attribute__((vector_size(sizeof(LD)*3))); 

enum input_type
{
    STDIN = 0,
    FILE_STRING = 1
}; 

enum error_type 
{
    NO_ERROR = 0,
    NO_CMD = 1,
    INVALIDE_CMD = 2,
    INVALIDE_FLAG = 3
};

enum cmd_type 
{
    NO_TYPE = 0,
    MD5 = 1,
    SHA256 = 2
};

typedef	struct		s_flag
{
    char    *flags_opt;
    char    *flags_set;
}					t_flag;

typedef	struct		s_input
{
    int             ac;
    char            **av;
    int             position;
	enum cmd_type   cmd_opts;
    enum error_type error;
    enum input_type read_from;
    t_list          *message;
    t_list          *message_name;
    t_flag          *flag;
}					t_input;

t_input     *create_input(int ac, char **av);
void        validate_input(t_input *);

int         md5(t_input *);
int         sha256(t_input *);

void        read_messages(t_input *);

// void        print_bitset(uint8_t *, size_t);
void        print_xset(uint8_t *, size_t);

// queue simulation
void        push_back(t_list **, char *);
t_list      *pop_front(t_list **);
void        realloc_queue_item(t_list **, size_t);

#endif