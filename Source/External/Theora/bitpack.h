﻿/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggTheora SOFTWARE CODEC SOURCE CODE.   *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggTheora SOURCE CODE IS (C) COPYRIGHT 1994-2009             *
 * by the Xiph.Org Foundation and contributors http://www.xiph.org/ *
 *                                                                  *
 ********************************************************************

  function: packing variable sized words into an octet stream
  last mod: $Id: bitwise.c 7675 2004-09-01 00:34:39Z xiphmont $

 ********************************************************************/
#if !defined(_bitpack_H)
#define _bitpack_H (1)
#include <limits.h>

typedef unsigned long      oc_pb_window;
typedef struct oc_pack_buf oc_pack_buf;

#define OC_PB_WINDOW_SIZE ((int)sizeof(oc_pb_window) * CHAR_BIT)
/*This is meant to be a large, positive constant that can still be efficiently
   loaded as an immediate (on platforms like ARM, for example).
  Even relatively modest values like 100 would work fine.*/
#define OC_LOTS_OF_BITS   (0x40000000)

struct oc_pack_buf
{
    oc_pb_window         window;
    const unsigned char* ptr;
    const unsigned char* stop;
    int                  bits;
    int                  eof;
};

void oc_pack_readinit(oc_pack_buf* _b, unsigned char* _buf, long _bytes);
int  oc_pack_look1(oc_pack_buf* _b);
void oc_pack_adv1(oc_pack_buf* _b);
/*Here we assume 0<=_bits&&_bits<=32.*/
long oc_pack_read(oc_pack_buf* _b, int _bits);
int  oc_pack_read1(oc_pack_buf* _b);
/* returns -1 for read beyond EOF, or the number of whole bytes available */
#ifndef _WIN64
long oc_pack_bytes_left(oc_pack_buf* _b);
#else
long long oc_pack_bytes_left(oc_pack_buf* _b);
#endif
/*These two functions are implemented locally in huffdec.c*/
/*Read in bits without advancing the bitptr.
  Here we assume 0<=_bits&&_bits<=32.*/
/*static int oc_pack_look(oc_pack_buf *_b,int _bits);*/
/*static void oc_pack_adv(oc_pack_buf *_b,int _bits);*/

#endif
