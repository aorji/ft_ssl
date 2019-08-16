/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorji <aorji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 12:40:57 by aorji             #+#    #+#             */
/*   Updated: 2019/08/16 14:21:40 by aorji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

#include "../inc/ft_ssl.h"

/* 
**	Rotate, shift macros
*/
#define ROTR(word, bits) (((word) >> (bits)) | ((word) << (32 - (bits))))
#define SHR(word, bits) ((word) >> (bits))

#define CH( x, y, z) (((x) & (y)) ^ ((~x) & (z)))
#define MAJ( x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

#define BSIG0(x) (ROTR((x), 2)	^ ROTR((x), 13) ^ ROTR((x), 22))
#define BSIG1(x) (ROTR((x), 6)	^ ROTR((x), 11) ^ ROTR((x), 25))
#define SSIG0(x) (ROTR((x), 7)	^ ROTR((x), 18) ^ SHR((x), 3))
#define SSIG1(x) (ROTR((x), 17) ^ ROTR((x), 19) ^ SHR((x), 10))

static const uint32_t K[] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static uint32_t H[] = {
	0,	0,	0,	0,	0,	0,	0,	0
};
static uint32_t HH[] = {
/*	a	b	c	d	e	f	g	h	*/
	0,	0,	0,	0,	0,	0,	0,	0
};

static uint8_t PADDING[] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*
** The message is "padded" (extended) so that its length (in bits) is congruent to 448, modulo 512
** len = 448 mod 512 (in bytes: len = 56 mod 64) => len = a mod n  
*/
static const int  n = 64;
static const int  a = 56;

/*
** A 64-bit representation of the length of the message before the padding bits were added
**  is appended to the result of step 1 ==> 8 bytre
*/
static const int LEN_SIZE = 8;

static const int BIT_NUM = 8;

uint32_t lit_to_bigendian(uint32_t word);

void sha256_output(t_input *input, uint32_t H[]);

#endif