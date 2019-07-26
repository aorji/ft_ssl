/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:51:30 by aorji             #+#    #+#             */
/*   Updated: 2019/07/26 13:34:34 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

#include "../inc/ft_ssl.h"

/*
 * Constants for MD5Tr calculation_procedure
 */
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

/* 
 * ROTATE_LEFT rotates x left n bits.
 */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

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
#define FF(a, b, c, d, x, s, t) {             \
        (a) += F((b), (c), (d)) + (x) + (t);  \
        (a) = ROTATE_LEFT((a), (s));          \
        (a) += (b);                           \
}
// /*
//  * Round 2
//  */
#define GG(a, b, c, d, x, s, t) {             \
        (a) += G((b), (c), (d)) + (x) + (t);  \
        (a) = ROTATE_LEFT((a), (s));          \
        (a) += (b);                           \
}
// /*
//  * Round 3
//  */
#define HH(a, b, c, d, x, s, t) {             \
        (a) += H((b), (c), (d)) + (x) + (t);  \
        (a) = ROTATE_LEFT((a), (s));          \
        (a) += (b);                           \
}
// /*
//  * Round 4
//  */
#define II(a, b, c, d, x, s, t) {             \
        (a) += I((b), (c), (d)) + (x) + (t);  \
        (a) = ROTATE_LEFT((a), (s));          \
        (a) += (b);                           \
}

static const uint32_t T[] = { 0,
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static uint8_t PADDING[] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*
 * Magic constants
 */
static int32_t A_ = 0x67452301;
static int32_t B_ = 0xefcdab89;
static int32_t C_ = 0x98badcfe;
static int32_t D_ = 0x10325476;

static int32_t A = 0;
static int32_t B = 0;
static int32_t C = 0;
static int32_t D = 0;

/*
 * The message is "padded" (extended) so that its length (in bits) is congruent to 448, modulo 512
 * len = 448 mod 512 (in bytes: len = 56 mod 64) => len = a mod n  
 */
static const int  n = 64;
static const int  a = 56;

/*
 * A 64-bit representation of the length of the message before the padding bits were added
 *  is appended to the result of step 1 ==> 8 bytre
 */
static const int LEN_SIZE = 8;

static const int BIT_NUM = 8;


// void  append_padding_bits(t_list **, size_t, size_t);
// void  append_lenght(t_list **, size_t, size_t, size_t);
// void  append_lenght(t_list **, size_t, size_t);
// void  calculation_procedure(t_list **message);

// void round_1(uint32_t X[16]);
// void round_2(uint32_t X[16]);
// void round_3(uint32_t X[16]);
// void round_4(uint32_t X[16]);
#endif