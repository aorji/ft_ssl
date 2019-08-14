/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ssl.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 18:12:54 by aorji             #+#    #+#             */
/*   Updated: 2019/08/14 20:33:20 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../libft-ft_printf/ft_printf.h"

enum    cmd_type
{
    MD5_42 = 0,
    MD5 = 1
};

const char *test_cases[][5] = {
	{"md5", "-s", "hello", NULL, NULL},
	{"md5", "-s", "hello", "test_files/67.txt", NULL},
	{"md5", "-s", "hello", "test_files/br.txt", NULL},
	{"md5", "-s", "hello", "test_files/chmod000", NULL},
	{"md5", "-s", "hello", "test_files/f1.txt", NULL},
	{"md5", "-s", "hello", "test_files/f2.txt", NULL},
	{"md5", "-s", "hello", "test_files/f3.txt", NULL},
	{"md5", "-s", "hello", "test_files/f5.txt", NULL},
	{"md5", "-s", "hellohellohellohellohellohel30", "-qs", "hellohellohellohellohellohello"},
	{"md5", "-qrs", "hello", "test_files/br.txt", "test_files/chmod000"},
	{"md5", "-rs", "hello", "-rq", "test_files/chmod000"},

	/*	bid file	*/
	{"md5", "-s", "hello", "../Xsizefile", NULL},

	/*	error cases	*/
	{"md5", NULL, "hello", "test_files/len64.txt", NULL},
	{"md5", NULL, "hello", "test_files/rich_poor_chapt1.txt", NULL},
	{"md5", NULL, "hello", "test_files/test_endian", NULL},
	{"md5", NULL, "hello", "test_files/test_with_newline.c", NULL},
	{"md5", NULL, "hello", "test_files/test_with_nonewline.c", NULL},
	{"md5", "-d", "hello", "test_files/test_with_nonewline.c", NULL},
	{"md5", "-sworld", "hello", NULL, NULL},
	{"md5", "-sworld", "-rq", "test_files/test_endian", NULL}
};