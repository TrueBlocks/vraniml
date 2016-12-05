//
// Copyright (c) 1997,1998 Colosseum Builders, Inc.
// All rights reserved.
//
// Colosseum Builders, Inc. makes no warranty, expressed or implied
// with regards to this software. It is provided as is.
//
// See the README.TXT file that came with this software for information
// on redistribution or send E-mail to info@colosseumbuilders.com
//
// o The user assumes all risk for using this software. The authors of this
//   software shall be liable for no damages of any kind.
//
// o If the source code is distributed then this copyright notice must
//   remain unaltered and any modification must be noted.
//
// o If this code is shipped in binary format the accompanying documentation
//   should state that "this software is based, in part, on the work of
//   Colosseum Builders, Inc."
//

//
//  Title:  PNG Checksum functions
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//
//  Description:
//
//    PNG uses two check sums. CRC32 is used on PNG chunks. Adler32 is use
//    on Deflate-compressed data.
//
//    CRC32 is performed using a lookup table. The lookup table must be
//    initialized before any CRC32 values are calculated. The initial
//    CRC32 value should be 0xFFFFFFFF.
//
//    The initial Adler32 value should be 1.
//

#include "pngchksm.h"
#include "datatype.h"

static UBYTE4 crc_table [256] ;  // Precomputed CRC lookup tables
static bool table_made = false ;

//
//  Description:
//
//    This function creates the CRC32 lookup table.
//
void MakeCrcTable ()
{
  if (table_made)
    return ;

  table_made = true ;
  for (unsigned int ii = 0 ; ii < 256 ; ++ ii)
  {
    crc_table [ii] = ii ;
    for (unsigned int jj = 0 ; jj < 8 ; ++ jj)
    {
      if ((crc_table [ii] & 1) == 0)
      {
        crc_table [ii] >>= 1 ;
      }
      else
      {
        crc_table [ii] = 0xEDB88320L ^ (crc_table [ii] >> 1) ;
      }
    }
  }
  return ;
}

//
//  Description:
//
//    This function updates the CRC32 value using a string of data.
//
//    This implementation is taken from the PNG standard.
//
//  Parameters:
//    crc:  The initial CRC32 value.
//    buffer:  The data buffer to add to the CRC value
//    length:  The data buffer length
//
//  Return Value:
//    The updated CRC value.
//
UBYTE4 CRC32 (UBYTE4 crc, void *buffer, unsigned int length)
{
  UBYTE4 result = crc ;

  for (UBYTE4 ii = 0 ; ii < length ; ++ ii)
  {
    result = crc_table [(result ^ ((char *) buffer) [ii]) & 0xFF] ^ (result >> 8) ;
  }
  return result ;
}

//
//  Description:
//
//    This function updates an Adler32 checksum using a buffer. This
//    implementation is from the Deflate standard.
//
//  Parameters:
//    adler:  The input adler 32 value.
//    value:  The data buffer
//
UBYTE4 Adler (UBYTE4 adler, UBYTE1 value) 
{
  static const UBYTE4 prime = 65521 ;

  UBYTE4 lo = adler & 0xFFFF ;
  UBYTE4 hi = (adler >> 16) & 0xFFFF ;

  lo = (lo + value) % prime ;
  hi = (lo + hi) % prime ;
  return (hi << 16) | lo ;
}
