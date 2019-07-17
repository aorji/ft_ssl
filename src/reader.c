/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:48:11 by aorji             #+#    #+#             */
/*   Updated: 2019/07/17 13:01:43 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

t_input *read_message_from_stdin(t_input *input)
{
    char    buf[BUFSIZE];
    size_t  input_size = 0;
    char    *resulting_str = (char *)malloc(sizeof(char) * input_size);
    resulting_str[0] = '\0';

    while ( 1 )
    {
        if (fgets(buf, sizeof buf, stdin))
        {
            input_size += ft_strlen(buf);
            resulting_str = (char *)realloc(resulting_str, input_size); 
            ft_strcat(resulting_str, buf);
            if ( resulting_str[input_size - 1] == '\n')
                break;
            continue;
        }
        else
        {
            write(1, "error: reader.c : line 28", 5);
        }
    }
    // resulting_str[input_size - 1] = '\0';  DO WE NEED \n AT THE END OF THE LINE?
    input->message = resulting_str;
    return input;
}

t_input *read_message_from_file(t_input *input, char *filename)
{
    char    buf[BUFSIZE + 1];
    size_t  input_size = 0;
    char    *resulting_str = (char *)malloc(sizeof(char) * input_size);
    resulting_str[0] = '\0';

    FILE *file;
    
    file = fopen(filename, "r");
    if ( !file )
    {
        ft_printf("%s%s\n", "ft_ssl: Error while opening the file");
        input->error = INVALIDE_FILE;
        return input;
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
                ft_printf("%s%s\n", "ft_ssl: Error while reading the file");
                input->error = INVALIDE_FILE;
                return input;
            }
            break;
        }
    }
    input->message = resulting_str;
    fclose(file);
    return input;
}






    // char    buf[1];
    // size_t  input_size = 1;
    // char    *resulting_str = (char *)malloc(sizeof(char) * input_size);
    // resulting_str[0] = '\0';
    // int filedesc = open(filename, O_RDONLY);

    // if (filedesc < 0)
    // {
    //     ft_printf("%s%s\n", "ft_ssl: Error opening file: ", strerror( errno ));
    //     input->error = INVALIDE_FILE;
    //     return input;
    // }

    // while ( 1 )
    // {
    //     if (read(filedesc, buf, 1))
    //     {
    //         input_size += ft_strlen(buf);
    //         resulting_str = (char *)realloc(resulting_str, input_size); //input_size - 1 - str + 1 - \0  
    //         ft_strcat(resulting_str, buf);
    //         ft_printf("%s%d\n", buf, ft_strlen(buf));
    //         if ( resulting_str[input_size - 1] == '\n')
    //             break;
    //         continue;
    //     }
    //     else
    //     {
    //         write(1, "error: reader.c : line 28", 5);
    //     }
    // }
    // close(filedesc);
    // input->message = resulting_str;
    // return input;