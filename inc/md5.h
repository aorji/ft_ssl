/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:51:30 by aorji             #+#    #+#             */
/*   Updated: 2019/07/23 20:58:56 by aorji            ###   ########.fr       */
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
 * Round 1
 */
#define FF(a, b, c, d, x, s, t) { \
        (a) += F((b), (c), (d)) + (x) + (t);    \
        (a) = (a) << (s);               \
}
// /*
//  * Round 2
//  */
// #define GG(a, b, c, d, x, s, t) b + ((a + G(b,c,d) + x + t) <<< s)
// /*
//  * Round 3
//  */
// #define HH(a, b, c, d, x, s, t) b + ((a + H(b,c,d) + x + t) <<< s)
// /*
//  * Round 4
//  */
// #define II(a, b, c, d, x, s, t) b + ((a + I(b,c,d) + x + t) <<< s)

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
static int32_t A = 0x67452301;
static int32_t B = 0xefcdab89;
static int32_t C = 0x98badcfe;
static int32_t D = 0x10325476;

static const int BIT_NUM = 8;

static size_t N = 0;
// extern uint32_t X[16];

#endif