/*
 *  huffman.c -- functions do decompress files in mpq files which
 *               uses a modified huffman version.
 *
 *  Copyright (c) 2003-2008 Maik Broemme <mbroemme@plusserver.de>
 *
 *  Differences between C++ and C version:
 *
 *    - Removed the object oriented stuff.
 *    - Replaced the goto things with some better C code.
 *
 *  This source was adepted from the C++ version of huffman.cpp included
 *  in stormlib. The C++ version belongs to the following authors:
 *
 *  Ladislav Zezula <ladik@zezula.net>
 *  ShadowFlare <BlakFlare@hotmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/* generic includes. */
#include <stdlib.h>
#include <string.h>

/* libmpq main includes. */
#include "mpq.h"
#include "mpq-internal.h"

/* libmpq generic includes. */
#include "huffman.h"

/* tables for huffman tree. */
static const uint8_t table_1502A630[] = {

	/* data for compression type 0x00. */
	0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
	0x00, 0x00,

	/* data for compression type 0x01. */
	0x54, 0x16, 0x16, 0x0D, 0x0C, 0x08, 0x06, 0x05, 0x06, 0x05, 0x06, 0x03, 0x04, 0x04, 0x03, 0x05,
	0x0E, 0x0B, 0x14, 0x13, 0x13, 0x09, 0x0B, 0x06, 0x05, 0x04, 0x03, 0x02, 0x03, 0x02, 0x02, 0x02,
	0x0D, 0x07, 0x09, 0x06, 0x06, 0x04, 0x03, 0x02, 0x04, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x02,
	0x09, 0x06, 0x04, 0x04, 0x04, 0x04, 0x03, 0x02, 0x03, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x04,
	0x08, 0x03, 0x04, 0x07, 0x09, 0x05, 0x03, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02,
	0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x02, 0x01, 0x02, 0x02,
	0x06, 0x0A, 0x08, 0x08, 0x06, 0x07, 0x04, 0x03, 0x04, 0x04, 0x02, 0x02, 0x04, 0x02, 0x03, 0x03,
	0x04, 0x03, 0x07, 0x07, 0x09, 0x06, 0x04, 0x03, 0x03, 0x02, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02,
	0x0A, 0x02, 0x02, 0x03, 0x02, 0x02, 0x01, 0x01, 0x02, 0x02, 0x02, 0x06, 0x03, 0x05, 0x02, 0x03,
	0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x03, 0x01, 0x01, 0x01,
	0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x04, 0x04, 0x04, 0x07, 0x09, 0x08, 0x0C, 0x02,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x01, 0x01, 0x03,
	0x04, 0x01, 0x02, 0x04, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x01, 0x01, 0x01,
	0x04, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x01, 0x01, 0x02, 0x02, 0x02, 0x06, 0x4B,
	0x00, 0x00,

	/* data for compression type 0x02. */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x27, 0x00, 0x00, 0x23, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x01, 0x01, 0x06, 0x0E, 0x10, 0x04,
	0x06, 0x08, 0x05, 0x04, 0x04, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03, 0x01, 0x01, 0x02, 0x01, 0x01,
	0x01, 0x04, 0x02, 0x04, 0x02, 0x02, 0x02, 0x01, 0x01, 0x04, 0x01, 0x01, 0x02, 0x03, 0x03, 0x02,
	0x03, 0x01, 0x03, 0x06, 0x04, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x01, 0x02, 0x01, 0x01,
	0x01, 0x29, 0x07, 0x16, 0x12, 0x40, 0x0A, 0x0A, 0x11, 0x25, 0x01, 0x03, 0x17, 0x10, 0x26, 0x2A,
	0x10, 0x01, 0x23, 0x23, 0x2F, 0x10, 0x06, 0x07, 0x02, 0x09, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00,

	/* data for compression type 0x03. */
	0xFF, 0x0B, 0x07, 0x05, 0x0B, 0x02, 0x02, 0x02, 0x06, 0x02, 0x02, 0x01, 0x04, 0x02, 0x01, 0x03,
	0x09, 0x01, 0x01, 0x01, 0x03, 0x04, 0x01, 0x01, 0x02, 0x01, 0x01, 0x01, 0x02, 0x01, 0x01, 0x01,
	0x05, 0x01, 0x01, 0x01, 0x0D, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x02, 0x01, 0x01, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x01, 0x01, 0x01, 0x01,
	0x0A, 0x04, 0x02, 0x01, 0x06, 0x03, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x01, 0x01, 0x01,
	0x05, 0x02, 0x03, 0x04, 0x03, 0x03, 0x03, 0x02, 0x01, 0x01, 0x01, 0x02, 0x01, 0x02, 0x03, 0x03,
	0x01, 0x03, 0x01, 0x01, 0x02, 0x05, 0x01, 0x01, 0x04, 0x03, 0x05, 0x01, 0x03, 0x01, 0x03, 0x03,
	0x02, 0x01, 0x04, 0x03, 0x0A, 0x06, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x02, 0x02, 0x01, 0x0A, 0x02, 0x05, 0x01, 0x01, 0x02, 0x07, 0x02, 0x17, 0x01, 0x05, 0x01, 0x01,
	0x0E, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x06, 0x02, 0x01, 0x04, 0x05, 0x01, 0x01, 0x02, 0x01, 0x01, 0x01, 0x01, 0x02, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x07, 0x01, 0x01, 0x02, 0x01, 0x01, 0x01, 0x01,
	0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x11,
	0x00, 0x00,

	/* data for compression type 0x04. */
	0xFF, 0xFB, 0x98, 0x9A, 0x84, 0x85, 0x63, 0x64, 0x3E, 0x3E, 0x22, 0x22, 0x13, 0x13, 0x18, 0x17,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00,

	/* data for compression type 0x05. */
	0xFF, 0xF1, 0x9D, 0x9E, 0x9A, 0x9B, 0x9A, 0x97, 0x93, 0x93, 0x8C, 0x8E, 0x86, 0x88, 0x80, 0x82,
	0x7C, 0x7C, 0x72, 0x73, 0x69, 0x6B, 0x5F, 0x60, 0x55, 0x56, 0x4A, 0x4B, 0x40, 0x41, 0x37, 0x37,
	0x2F, 0x2F, 0x27, 0x27, 0x21, 0x21, 0x1B, 0x1C, 0x17, 0x17, 0x13, 0x13, 0x10, 0x10, 0x0D, 0x0D,
	0x0B, 0x0B, 0x09, 0x09, 0x08, 0x08, 0x07, 0x07, 0x06, 0x05, 0x05, 0x04, 0x04, 0x04, 0x19, 0x18,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00,

	/* data for compression type 0x06. */
	0xC3, 0xCB, 0xF5, 0x41, 0xFF, 0x7B, 0xF7, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xBF, 0xCC, 0xF2, 0x40, 0xFD, 0x7C, 0xF7, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x7A, 0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00,

	/* data for compression type 0x07. */
	0xC3, 0xD9, 0xEF, 0x3D, 0xF9, 0x7C, 0xE9, 0x1E, 0xFD, 0xAB, 0xF1, 0x2C, 0xFC, 0x5B, 0xFE, 0x17,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xBD, 0xD9, 0xEC, 0x3D, 0xF5, 0x7D, 0xE8, 0x1D, 0xFB, 0xAE, 0xF0, 0x2C, 0xFB, 0x5C, 0xFF, 0x18,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x70, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00,

	/* data for compression type 0x08. */
	0xBA, 0xC5, 0xDA, 0x33, 0xE3, 0x6D, 0xD8, 0x18, 0xE5, 0x94, 0xDA, 0x23, 0xDF, 0x4A, 0xD1, 0x10,
	0xEE, 0xAF, 0xE4, 0x2C, 0xEA, 0x5A, 0xDE, 0x15, 0xF4, 0x87, 0xE9, 0x21, 0xF6, 0x43, 0xFC, 0x12,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xB0, 0xC7, 0xD8, 0x33, 0xE3, 0x6B, 0xD6, 0x18, 0xE7, 0x95, 0xD8, 0x23, 0xDB, 0x49, 0xD0, 0x11,
	0xE9, 0xB2, 0xE2, 0x2B, 0xE8, 0x5C, 0xDD, 0x15, 0xF1, 0x87, 0xE7, 0x20, 0xF7, 0x44, 0xFF, 0x13,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x5F, 0x9E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00
};

/* this function insert an item to a huffman tree. */
void libmpq__huffman_insert_item(struct huffman_tree_item_s **p_item, struct huffman_tree_item_s *item, uint32_t where, struct huffman_tree_item_s *item2) {

	/* EDI - next to the first item. */
	struct huffman_tree_item_s *next = item->next;

	/* ESI - prev to the first item. */
	struct huffman_tree_item_s *prev = item->prev;

	/* pointer to previous item. */
	struct huffman_tree_item_s *prev2;

	/* pointer to next item. */
	void* next2;

	/* check the first item already has next one. */
	if (next != 0) {

		/* check if previous item exist. */
		if (PTR_INT(prev) < 0) {

			/* return previous item. */
			prev = PTR_NOT(prev);
		} else {

			/* add item. */
			prev += (item - next->prev);
		}

		/* 150083C1 - remove the item from the tree. */
		prev->next = next;
		next->prev = prev;

		/* invalidate prev and next pointer. */
		item->next = 0;
		item->prev = 0;
	}

	/* EDX - check if the second item is not entered. */
	if (item2 == NULL) {

		/* take the first tree item. */
		item2 = PTR_PTR(&p_item[1]);
	}

	/* check if items should be switched or new one inserted. */
	switch (where) {
		case SWITCH_ITEMS:

			/* item2->next (pointer to pointer to first). */
			item->next        = item2->next;
			item->prev        = item2->next->prev;
			item2->next->prev = item;

			/* set the first item. */
			item2->next       = item;

			/* return from function. */
			return;
		case INSERT_ITEM:

			/* set next item (or pointer to pointer to first item) - insert as last item. */
			item->next = item2;

			/* set previous item (or last item in the tree). */
			item->prev = item2->prev;

			/* usually NULL. */
			next2      = (void*)PTR_INT(p_item[0]);

			/* previous item to the second (or last tree item). */
			prev2      = item2->prev;

			/* check if previous item is a valid pointer. */
			if (PTR_INT(prev2) < 0) {

				/* set values. */
				prev2       = PTR_NOT(prev);
				prev2->next = item;

				/* next after last item. */
				item2->prev = item;

				/* return from function. */
				return;
			}

			/* check if next item is empty. */
			if (next2 < 0) {

				/* set next item. */
				next2 =  (void*)(item2 - item2->next->prev);
			}

			/* add next item to previous one. */
			prev2       += (unsigned long long)next2;
			prev2->next  = item;

			/* set the next and last item. */
			item2->prev  = item;

			/* return from function. */
			return;
		default:

			/* nothing to do, so return from function. */
			return;
	}
}

/* 1500BC90 - remove item from huffman tree.*/
void libmpq__huffman_remove_item(struct huffman_tree_item_s *hi) {

	/* EDX - some common variables. */
	struct huffman_tree_item_s *temp;

	/* check if next item is not empty. */
	if (hi->next != NULL) {

		/* fetch previous item. */
		temp = hi->prev;

		/* check if previous item is a pointer. */
		if (PTR_INT(temp) <= 0) {
			temp = PTR_NOT(temp);
		} else {
			temp += (hi - hi->next->prev);
		}

		/* reorganize tree. */
		temp->next     = hi->next;
		hi->next->prev = hi->prev;
		hi->next       = hi->prev = NULL;
	}
}

/* get previous huffman tree item. */
struct huffman_tree_item_s *libmpq__huffman_previous_item(struct huffman_tree_item_s *hi, long value) {

	/* check if previous item exist. */
	if (PTR_INT(hi->prev) < 0) {

		/* return previous item. */
		return PTR_NOT(hi->prev);
	}

	/* check if something else should returned. */
	if (value < 0) {

		/* fetch previous item of next item. */
		value = hi - hi->next->prev;
	}

	/* return previous item with value. */
	return hi->prev + value;
}

/* get one bit from input stream. */
uint32_t libmpq__huffman_get_1bit(struct huffman_input_stream_s *is) {

	/* some common variables. */
	uint32_t bit = (is->bit_buf & 1);

	/* shift bit right by one. */
	is->bit_buf >>= 1;

	/* check if we should extract bits. */
	if (--is->bits == 0) {
		is->bit_buf  = *(uint32_t *)is->in_buf;
		is->in_buf  += sizeof(int32_t);
		is->bits     = 32;
	}

	/* return the bit. */
	return bit;
}

/* get 7 bits from the input stream. */
uint32_t libmpq__huffman_get_7bit(struct huffman_input_stream_s *is) {

	/* check if we should extract bits. */
	if (is->bits <= 7) {
		is->bit_buf |= *(uint16_t *)is->in_buf << is->bits;
		is->in_buf  += sizeof(int16_t);
		is->bits    += 16;
	}

	/* get 7 bits from input stream. */
	return (is->bit_buf & 0x7F);
}

/* get the whole byte from the input stream. */
uint32_t libmpq__huffman_get_8bit(struct huffman_input_stream_s *is) {

	/* some common variables. */
	uint32_t one_byte;

	/* check if we should extract bits. */
	if (is->bits <= 8) {
		is->bit_buf |= *(uint16_t *)is->in_buf << is->bits;
		is->in_buf  += sizeof(int16_t);
		is->bits    += 16;
	}

	/* fill values. */
	one_byte      = (is->bit_buf & 0xFF);
	is->bit_buf >>= 8;
	is->bits     -= 8;

	/* return the 8 bits. */
	return one_byte;
}

/* return struct for 1500E740. */
struct huffman_tree_item_s *libmpq__huffman_call_1500E740(struct huffman_tree_s *ht) {

	/* EDX */
	struct huffman_tree_item_s *p_item1 = ht->item3058;

	/* EAX */
	struct huffman_tree_item_s *p_item2;

	/* some common variables. */
	struct huffman_tree_item_s *p_next;
	struct huffman_tree_item_s *p_prev;
	struct huffman_tree_item_s **pp_item;

	/* check if item is empty. */
	if (PTR_INT(p_item1) <= 0 || (p_item2 = p_item1) == NULL) {

		/* check if item is not empty. */
		if ((p_item2 = &ht->items0008[ht->items++]) != NULL) {
			p_item1 = p_item2;
		} else {
			p_item1 = ht->first;
		}
	} else {
		p_item1 = p_item2;
	}

	/* set next item. */
	p_next = p_item1->next;

	/* check if next item is not empty. */
	if (p_next != NULL) {

		/* set previous item. */
		p_prev = p_item1->prev;

		/* check if previous item is a valid pointer. */
		if (PTR_INT(p_prev) <= 0) {
			p_prev = PTR_NOT(p_prev);
		} else {
			p_prev += (p_item1 - p_item1->next->prev);
		}

		/* fill values. */
		p_prev->next  = p_next;
		p_next->prev  = p_prev;
		p_item1->next = NULL;
		p_item1->prev = NULL;
	}

	/* ESI */
	pp_item       = &ht->first;
	p_item1->next = (struct huffman_tree_item_s *)pp_item;
	p_item1->prev = pp_item[1];

	/* EDI = ht->item305C - ECX */
	p_prev = pp_item[1];

	/* check if previous pointer is valid. */
	if (p_prev <= 0) {

		/* fill values. */
		p_prev          = PTR_NOT(p_prev);
		p_prev->next    = p_item1;
		p_prev->prev    = p_item2;
		p_item2->parent = NULL;
		p_item2->child  = NULL;
	} else {

		/* check if pointer is valid. */
		if (PTR_INT(ht->item305C) < 0) {
			p_prev += (struct huffman_tree_item_s *)pp_item - (*pp_item)->prev;
		} else {
			p_prev += PTR_INT(ht->item305C);
		}

		/* fill values. */
		p_prev->next    = p_item1;
		pp_item[1]      = p_item2;
		p_item2->parent = NULL;
		p_item2->child  = NULL;
	}

	/* return item. */
	return p_item2;
}

/* return struct for 1500E820. */
void libmpq__huffman_call_1500E820(struct huffman_tree_s *ht, struct huffman_tree_item_s *p_item) {

	/* EDI */
	struct huffman_tree_item_s *p_item1;

	/* EAX */
	struct huffman_tree_item_s *p_item2 = NULL;

	/* EDX */
	struct huffman_tree_item_s *p_item3;

	/* EBX */
	struct huffman_tree_item_s *p_prev;

	/* loop through parent items. */
	for (; p_item != NULL; p_item = p_item->parent) {

		/* increase byte counter. */
		p_item->byte_value++;

		/* loop through previous items. */
		for (p_item1 = p_item; ; p_item1 = p_prev) {

			/* set previous item. */
			p_prev = p_item1->prev;

			/* check if pointer is valid. */
			if (PTR_INT(p_prev) <= 0) {
				p_prev = NULL;
				break;
			}

			/* check if byte value of previous item is higher than actual item. */
			if (p_prev->byte_value >= p_item->byte_value) {
				break;
			}
		}

		/* check if previous item is same like actual item. */
		if (p_item1 == p_item) {
			continue;
		}

		/* check if next item is not empty, */
		if (p_item1->next != NULL) {

			/* fill values. */
			p_item2             = libmpq__huffman_previous_item(p_item1, -1);
			p_item2->next       = p_item1->next;
			p_item1->next->prev = p_item1->prev;
			p_item1->next       = NULL;
			p_item1->prev       = NULL;
		}

		/* fill values. */
		p_item2       = p_item->next;
		p_item1->next = p_item2;
		p_item1->prev = p_item2->prev;
		p_item2->prev = p_item1;
		p_item->next  = p_item1;

		/* check if both items are not empty. */
		if ((p_item2 = p_item1) != NULL) {

			/* fill values. */
			p_item2            = libmpq__huffman_previous_item(p_item, -1);
			p_item2->next      = p_item->next;
			p_item->next->prev = p_item->prev;
			p_item->next       = NULL;
			p_item->prev       = NULL;
		}

		/* check if previous item is empty. */
		if (p_prev == NULL) {
			p_prev = PTR_PTR(&ht->first);
		}

		/* fill values. */
		p_item2       = p_prev->next;
		p_item->next  = p_item2;
		p_item->prev  = p_item2->prev;
		p_item2->prev = p_item;
		p_prev->next  = p_item;
		p_item3       = p_item1->parent->child;
		p_item2       = p_item->parent;

		/* check if child item and parent item match. */
		if (p_item2->child == p_item) {
			p_item2->child = p_item1;
		}

		/* check if items match. */
		if (p_item3 == p_item1) {
			p_item1->parent->child = p_item;
		}

		/* fill values. */
		p_item2         = p_item->parent;
		p_item->parent  = p_item1->parent;
		p_item1->parent = p_item2;

		/* increase counter. */
		ht->offs0004++;
	}
}

/* this function initialize a huffman tree. */
void libmpq__huffman_tree_init(struct huffman_tree_s *ht, uint32_t cmp) {

	/* some common variables. */
	uint32_t count;
	struct huffman_tree_item_s *hi;

	/* clear links for all the items in the tree. */
	for (hi = ht->items0008, count = 0x203; count != 0; hi++, count--) {
		hi->next = hi->prev = NULL;
	}

	/* fill values. */
	ht->item3050 = NULL;
	ht->item3054 = PTR_PTR(&ht->item3054);
	ht->item3058 = PTR_NOT(ht->item3054);
	ht->item305C = NULL;
	ht->first    = PTR_PTR(&ht->first);
	ht->last     = PTR_NOT(ht->first);
	ht->offs0004 = 1;
	ht->items    = 0;

	/* clear all huffman decompress items, do this only if preparing for decompression. */
	if (cmp == LIBMPQ_HUFF_DECOMPRESS) {
		for (count = 0; count < sizeof(ht->qd3474) / sizeof(struct huffman_decompress_s); count++) {
			ht->qd3474[count].offs00 = 0;
		}
	}
}

/* this function build a huffman tree, called with the first 8 bits loaded from input stream. */
void libmpq__huffman_tree_build(struct huffman_tree_s *ht, uint32_t cmp_type) {

	/* [ESP+10] - the greatest character found in table. */
	uint32_t max_byte;

	/* [ESP+1C] - pointer to uint8_t in table_1502A630. */
	const uint8_t *byte_array;

	/* thats needed to replace the goto stuff from original source. :) */
	uint32_t found;

	/* [ESP+14] - Pointer to Huffman tree item pointer array. */
	struct huffman_tree_item_s **p_item;
	struct huffman_tree_item_s *child1;

	/* some common variables. */
	uint32_t i;

	/* ESI - loop while pointer has a negative value (last entry). */
	while (PTR_INT(ht->last) > 0) {

		/* EAX */
		struct huffman_tree_item_s *temp;

		/* ESI->next */
		if (ht->last->next != NULL) {
			libmpq__huffman_remove_item(ht->last);
		}

		/* [EDI+4] */
		ht->item3058   = PTR_PTR(&ht->item3054);

		/* EAX */
		ht->last->prev = ht->item3058;
		temp           = libmpq__huffman_previous_item(PTR_PTR(&ht->item3054), PTR_INT(&ht->item3050));
		temp->next     = ht->last;
		ht->item3054   = ht->last;
	}

	/* clear all pointers in huffman tree item array. */
	memset(ht->items306C, 0, sizeof(ht->items306C));

	/* greatest character found init to zero. */
	max_byte    = 0;

	/* pointer to current entry in huffman tree item pointer array. */
	p_item      = (struct huffman_tree_item_s **)&ht->items306C;

	/* ensure we have low 8 bits only. */
	cmp_type   &= 0xFF;

	/* EDI also. */
	byte_array  = table_1502A630 + cmp_type * 258;

	/* loop to build huffman tree. */
	for (i = 0; i < 0x100; i++, p_item++) {

		/* item to be created. */
		struct huffman_tree_item_s *item    = ht->item3058;
		struct huffman_tree_item_s *p_item3 = ht->item3058;
		uint8_t one_byte                  = byte_array[i];

		/* skip all the bytes which are zero. */
		if (byte_array[i] == 0) {
			continue;
		}

		/* if not valid pointer, take the first available item in the array. */
		if (PTR_INT(item) <= 0) {
			item = &ht->items0008[ht->items++];
		}

		/* insert this item as the top of the tree. */
		libmpq__huffman_insert_item(&ht->item305C, item, SWITCH_ITEMS, NULL);

		/* invalidate child and parent. */
		item->parent     = NULL;
		item->child      = NULL;

		/* store pointer into pointer array. */
		*p_item          = item;

		/* store counter. */
		item->dcmp_byte  = i;

		/* store byte value. */
		item->byte_value = one_byte;

		/* check if byte is to big. */
		if (one_byte >= max_byte) {

			/* set max byte to highest value. */
			max_byte = one_byte;

			/* continue loop. */
			continue;
		}

		/* find the first item which has byte value greater than current one byte. */
		found = 0;

		/* EDI - Pointer to the last item. */
		if (PTR_INT((p_item3 = ht->last)) > 0) {

			/* 15006AF7 */
			if (p_item3 != NULL) {

				/* 15006AFB */
				do {

					/* check if we found item. */
					if (p_item3->byte_value >= one_byte) {
						found = 1;
						break;
					}

					/* switch to previous item. */
					p_item3 = p_item3->prev;
				} while (PTR_INT(p_item3) > 0);
			}
		}

		/* check if item was not found. */
		if (found == 0) {
			p_item3 = NULL;
		}

		/* 15006B09 */
		if (item->next != NULL) {
			libmpq__huffman_remove_item(item);
		}

		/* 15006B15 */
		if (p_item3 == NULL) {
			p_item3 = PTR_PTR(&ht->first);
		}

		/* 15006B1F */
		item->next          = p_item3->next;
		item->prev          = p_item3->next->prev;
		p_item3->next->prev = item;
		p_item3->next       = item;
	}

	/* 15006B4A */
	for (; i < 0x102; i++) {

		/* EDI */
		struct huffman_tree_item_s **p_item2 = &ht->items306C[i];

		/* 15006B59 - ESI */
		struct huffman_tree_item_s *item2 = ht->item3058;

		/* check if item is a valid pointer. */
		if (PTR_INT(item2) <= 0) {
			item2 = &ht->items0008[ht->items++];
		}

		/* insert the item into tree. */
		libmpq__huffman_insert_item(&ht->item305C, item2, INSERT_ITEM, NULL);

		/* 15006B89 */
		item2->dcmp_byte  = i;
		item2->byte_value = 1;
		item2->parent     = NULL;
		item2->child      = NULL;
		*p_item2++        = item2;
	}

	/* 15006BAA - EDI - last item (first child to item). */
	if (PTR_INT((child1 = ht->last)) > 0) {

		/* EBP */
		struct huffman_tree_item_s *child2;

		/* ESI */
		struct huffman_tree_item_s *item;

		/* 15006BB8 */
		while (PTR_INT((child2 = child1->prev)) > 0) {
			if (PTR_INT((item = ht->item3058)) <= 0) {
				item = &ht->items0008[ht->items++];
			}

			/* 15006BE3 */
			libmpq__huffman_insert_item(&ht->item305C, item, SWITCH_ITEMS, NULL);

			/* 15006BF3 */
			item->parent = NULL;
			item->child  = NULL;

			/*
			 * EDX = child2->byte_value + child1->byte_value;
			 * EAX = child1->byte_value;
			 * ECX = max_byte; (the greatest character (0xFF usually))
			 *       item->byte_value (0x02 usually)
			 */
			item->byte_value = child1->byte_value + child2->byte_value;

			/* previous item in the tree. */
			item->child      = child1;
			child1->parent   = item;
			child2->parent   = item;

			/* EAX = item->byte_value */
			if (item->byte_value >= max_byte) {
				max_byte = item->byte_value;
			} else {

				/* EDI */
				struct huffman_tree_item_s *p_item2 = child2->prev;
				found = 0;

				/* check if item is a valid pointer. */
				if (PTR_INT(p_item2) > 0) {

					/* 15006C2D */
					do {

						/* check if we found item. */
						if (p_item2->byte_value >= item->byte_value) {
							found = 1;
							break;
						}

						/* switch to previous item. */
						p_item2 = p_item2->prev;
					} while (PTR_INT(p_item2) > 0);
				}

				/* check if item was not found. */
				if (found == 0) {
					p_item2 = NULL;
				}

				/* check if next item exist. */
				if (item->next != 0) {

					/* some common variables. */
					struct huffman_tree_item_s *temp4 = libmpq__huffman_previous_item(item, -1);

					/* zhe first item changed. */
					temp4->next                     = item->next;

					/* first->prev changed to negative value. */
					item->next->prev                = item->prev;
					item->next                      = NULL;
					item->prev                      = NULL;
				}

				/* 15006C62 */
				if (p_item2 == NULL) {
					p_item2 = PTR_PTR(&ht->first);
				}

				/* set item with 0x100 byte value. */
				item->next          = p_item2->next;

				/* set item with 0x17 byte value. */
				item->prev          = p_item2->next->prev;

				/* changed prev of item with. */
				p_item2->next->prev = item;
				p_item2->next       = item;
			}

			/* 15006C7B */
			if (PTR_INT((child1 = child2->prev)) <= 0) {
				break;
			}
		}
	}

	/* 15006C88 */
	ht->offs0004 = 1;
}

/* this function did the real decompression. */
int32_t libmpq__do_decompress_huffman(struct huffman_tree_s *ht, struct huffman_input_stream_s *is, uint8_t *out_buf, uint32_t out_length) {

	/* some common variables. */
	uint32_t dcmp_byte = 0;
	uint8_t *out_pos = out_buf;
	uint32_t bit_count;
	struct huffman_decompress_s *qd;
	struct huffman_tree_item_s *p_item1;
	struct huffman_tree_item_s *p_item2;

	/* 8 bits loaded from input stream. */
	uint32_t n8bits;

	/* 7 bits loaded from input stream. */
	uint32_t n7bits;

	/* thats needed to replace the goto stuff from original source. :) */
	uint32_t found;

	/* can we use quick decompression */
	uint32_t has_qd;

	/* test the output length, must not be non zero. */
	if (out_length == 0) {
		return 0;
	}

	/* get the compression type from the input stream. */
	n8bits = libmpq__huffman_get_8bit(is);

	/* build the Huffman tree. */
	libmpq__huffman_tree_build(ht, n8bits);

	/* compression 8 bit or not? */
	ht->cmp0 = (n8bits == 0) ? TRUE : FALSE;

	/* loop until break. */
	for(;;) {

		/* get 7 bits from input stream. */
		n7bits = libmpq__huffman_get_7bit(is);

		/* try to use quick decompression, check huffman decompress struct for corresponding item. */
		qd = &ht->qd3474[n7bits];

		/* if there is a quick-pass possible (ebx). */
		has_qd = (qd->offs00 >= ht->offs0004) ? TRUE : FALSE;

		/* if we can use quick decompress, use it. */
		if (has_qd) {
			found = 0;
			if (qd->bits > 7) {
				is->bit_buf >>= 7;
				is->bits     -= 7;
				p_item1       = qd->p_item;
				found         = 1;
			}
			if (found == 0) {
				is->bit_buf >>= qd->bits;
				is->bits     -= qd->bits;
				dcmp_byte     = qd->dcmp_byte;
			}
		} else {
			found = 1;
			p_item1 = ht->first->next->prev;
			if (PTR_INT(p_item1) <= 0) {
				p_item1 = NULL;
			}
		}

		/* check if item was found. */
		if (found == 1) {
			bit_count = 0;
			p_item2   = NULL;

			/* loop until tree has no deeper level. */
			do {

				/* move down by one level. */
				p_item1 = p_item1->child;

				/* check if current bit is set, move to previous. */
				if (libmpq__huffman_get_1bit(is)) {
					p_item1 = p_item1->prev;
				}

				/* check if we are at 7th bit, save current huffman tree item. */
				if (++bit_count == 7) {
					p_item2 = p_item1;
				}
			} while (p_item1->child != NULL);

			/* no quick decompression. :( */
			if (has_qd == FALSE) {

				/* check bit counter. */
				if (bit_count > 7) {
					qd->offs00 = ht->offs0004;
					qd->bits   = bit_count;
					qd->p_item = p_item2;
				} else {
					uint32_t index = n7bits & (0xFFFFFFFF >> (32 - bit_count));
					uint32_t add   = (1 << bit_count);

					/* loop through compression. */
					for (qd = &ht->qd3474[index]; index <= 0x7F; index += add, qd += add) {
						qd->offs00    = ht->offs0004;
						qd->bits      = bit_count;
						qd->dcmp_byte = p_item1->dcmp_byte;
					}
				}
			}

			/* set compression byte. */
			dcmp_byte = p_item1->dcmp_byte;
		}

		/* check if huffman tree needs to be modified. */
		if (dcmp_byte == 0x101)	{

			/* fill values. */
			n8bits                            = libmpq__huffman_get_8bit(is);
			p_item1                           = (ht->last <= 0) ? NULL : ht->last;
			p_item2                           = libmpq__huffman_call_1500E740(ht);
			p_item2->parent                   = p_item1;
			p_item2->dcmp_byte                = p_item1->dcmp_byte;
			p_item2->byte_value               = p_item1->byte_value;
			ht->items306C[p_item2->dcmp_byte] = p_item2;
			p_item2                           = libmpq__huffman_call_1500E740(ht);
			p_item2->parent                   = p_item1;
			p_item2->dcmp_byte                = n8bits;
			p_item2->byte_value               = 0;
			ht->items306C[p_item2->dcmp_byte] = p_item2;
			p_item1->child                    = p_item2;

			/* call 1500E820. */
			libmpq__huffman_call_1500E820(ht, p_item2);

			/* check if compression is not set. */
			if (ht->cmp0 == 0) {
				libmpq__huffman_call_1500E820(ht, ht->items306C[n8bits]);
			}

			/* set compression byte. */
			dcmp_byte = n8bits;
		}

		/* check for compression. */
		if (dcmp_byte == 0x100) {
			break;
		}

		/* increase position by compression byte. */
		*out_pos++ = (uint8_t)dcmp_byte;
		if (--out_length == 0) {
			break;
		}

		/* check if compression is not set. */
		if (ht->cmp0) {
			libmpq__huffman_call_1500E820(ht, ht->items306C[dcmp_byte]);
		}
	}

	/* return copied bytes. */
	return (out_pos - out_buf);
}
