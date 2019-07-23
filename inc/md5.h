/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:51:30 by aorji             #+#    #+#             */
/*   Updated: 2019/07/23 17:55:59 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

#include "../inc/ft_ssl.h"

/*
 * Basic MD5 functions.
 */
#define F(x, y, z) (((x) & (y)) || ((!x) & (z)))
#define G(x, y, z) (((x) & (z)) || ((y) & (!z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (!z)))

/*
 * The message is "padded" (extended) so that its length (in bits) is congruent to 448, modulo 512
 * len = 448 mod 512 => len = a mod n
 */
static const int  n = 512;
static const int  a = 448;

/*
 * The message is extended so that it is just 64 bits shy of being a multiple of 512 bits long
 * 512 - 448 = 64 => b = n - a
 */
static const int b = n - a;

static unsigned char PADDING[b] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*
 * Magic constants
 */
// static const int32_t A = 0x67452301;
// static const int32_t B = 0xefcdab89;
// static const int32_t C = 0x98badcfe;
// static const int32_t D = 0x10325476;

static const int BIT_NUM = 8;

#endif