/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:48:11 by aorji             #+#    #+#             */
/*   Updated: 2019/08/08 15:15:47 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/reader.h"

// static void print_error(t_input *input)
// {
//     if (input->cmd_opts == 1)
//         ft_printf("md5: ");
//     else
//         ft_printf("sha256: ");
//     ft_printf("%s: %s\n", (input->av)[input->position], strerror( errno ));
// }

// static size_t get_filesize(const char* filename)
// {
//     struct stat st;
//     stat(filename, &st);
//     return st.st_size;
// }
static size_t is_dir(const char* filename)
{
    struct stat st;
    stat(filename, &st);
    return S_ISDIR(st.st_mode);
}

void read_message_from_stdin(t_input *input)
{
    char    buf[BUFSIZE];
    size_t  input_size = 0;
    char    *resulting_str = (char *)malloc(sizeof(char));
    resulting_str[0] = '\0';

    while ( 1 )
    {
        if (fgets(buf, sizeof buf, stdin))
        {
            input_size += ft_strlen(buf);
            resulting_str = (char *)realloc(resulting_str, input_size); 
            ft_strcat(resulting_str, buf);
            continue;
        }
        break;
    }
    set_message(input, resulting_str, resulting_str);
    call_hashing_algorithm(input);
    free(resulting_str);
}

void read_message_from_file(t_input *input)
{
    char    buf[BUFSIZE + 1];
    size_t  input_size = 0;

    for (; input->position < input->ac; ++(input->position))
    {
        char    *resulting_str = (char *)malloc(sizeof(char));
        resulting_str[0] = '\0';
        FILE *file = fopen((input->av)[input->position], "r");

        if ( !file )
        {
            ft_printf("%s: %s: %s", "ft_ssl", (input->av)[input->position], "Error while opening the file\n");
            // input->error = INVALIDE_FILE;
            continue;
        }
        if (is_dir((input->av)[input->position])){
            ft_printf("%s: %s: %s", "ft_ssl", (input->av)[input->position], "Is a directory\n");
            continue;
        }
        while ( 1 )
        {
            if (fgets(buf, sizeof buf, file))
            {
                input_size += sizeof buf;
                resulting_str = (char *)realloc(resulting_str, input_size);
                ft_strcat(resulting_str, buf);
                if ( resulting_str[input_size - 1] == '\n')
                    break;
            }
            else
            {
                if (ferror(stdin))  //return 0 if an error occurred
                {
                    ft_printf("%s", "ft_ssl: Error while reading the file\n");
                    // input->error = INVALIDE_FILE;
                    continue;
                }
                break;
            }
        }
        set_message(input, resulting_str, (input->av)[input->position]);
        call_hashing_algorithm(input);
        free(resulting_str);
        fclose(file);
    }
}
 
void process_stdin_files(t_input *input)
{
    if(input->read_from == STDIN)
        read_message_from_stdin(input);
    if (input->read_from == FILE_STRING)
        read_message_from_file(input);
}
