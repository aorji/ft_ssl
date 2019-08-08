/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:48:11 by aorji             #+#    #+#             */
/*   Updated: 2019/08/08 18:51:59 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/reader.h"

static size_t get_filesize(const char* filename)
{
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}
static size_t is_dir(const char* filename)
{
    struct stat st;
    stat(filename, &st);
    return S_ISDIR(st.st_mode);
}

static void hash_string(t_input *input, char *full_message)
{
    char *part_message = NULL;
    int start = 0;
    while (1)
    {
        input->total_size = ft_strlen(full_message);
        part_message = full_message + start;
        set_message(input, part_message, full_message, input->total_size - start);
        if (!call_hashing_algorithm(input))
            break;
        start += 64;
    }
}

void read_message_from_stdin(t_input *input __unused)
{
    char    buf[BUFFSIZE];
    size_t  input_size = 0;
    char    *resulting_str = (char *)malloc(sizeof(char));
    resulting_str[0] = '\0';
    
    while ( 1 )
    {
        if (fgets(buf, BUFFSIZE, stdin))
        {
            input_size += ft_strlen(buf);
            resulting_str = (char *)realloc(resulting_str, input_size); 
            ft_strcat(resulting_str, buf);
            continue;
        }
        break;
    }
    hash_string(input, resulting_str);
}

void read_message_from_string(t_input *input, int j)
{
    if ((input->av)[input->position][j + 1] == '\0')                        /* example: "-s" "string" */ 
    {
        if (!(input->av)[input->position + 1])
        {
            print_error(input->cmd_opts, NULL, "option requires an argument -- s\nusage: md5 [-pqrtx] [-s string] [files ...]");
            input->error = INVALIDE_FLAG;
            return;
        }
        (input->position)++;
        hash_string(input, input->av[input->position]);
    }
    else                                                                    /* example: "-sstring" */
        hash_string(input, ft_strsub(input->av[input->position], j + 1, ft_strlen(input->av[input->position]) - j - 1));
}

void read_message_from_file(t_input *input)
{
    char BUFF[BUFFSIZE];

    for (; input->position < input->ac; ++(input->position))
    {
        input->total_size = get_filesize((input->av)[input->position]);
        int fd = open((input->av)[input->position], O_RDONLY);

        if ( fd == -1 )
        {
            print_error(input->cmd_opts, (input->av)[input->position], strerror( errno ));
            continue;
        }
        if (is_dir((input->av)[input->position]))
        {
            print_error(input->cmd_opts, (input->av)[input->position], "Is a directory");
            continue;
        }
        while (1)
        {
            int read_size = read(fd, BUFF, BUFFSIZE);
            if (read_size != -1)
            {
                set_message(input, BUFF, (input->av)[input->position], read_size);
                if (!call_hashing_algorithm(input))
                    break;
            }
            else
            {
                print_error(input->cmd_opts, (input->av)[input->position], strerror( errno ));
                continue;
            }
            
        }
        close(fd);
    }
}

void process_stdin_files(t_input *input)
{
    if (input->read_from == STDIN && get_flag(input, 'p'))
        return;
    if(input->read_from == STDIN)
        read_message_from_stdin(input);
    if (input->read_from == FILE_STRING)
        read_message_from_file(input);
}
