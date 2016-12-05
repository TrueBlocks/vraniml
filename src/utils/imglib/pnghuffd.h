#ifndef __PNGHUFFD_H
#define __PNGHUFFD_H
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
//  Title:  PngHuffmanDecoder definition
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//
//  Description:
//
//    This class handles Huffman decoding for PNG images.
//

#include "datatype.h"
#include "pngpvt.h"

class PngDecoder ;

class PngHuffmanDecoder
{
public:
  PngHuffmanDecoder () {}
  virtual ~PngHuffmanDecoder () {}

  // DECODING FUNCTIONS
  void MakeTable (unsigned int lengthcount, const unsigned int huffbits []) ;

  // This is a debugging function that writes the Huffman table
  // to cout.
  void Dump () const ;

  int Decode (PngDecoder &) ;
private:
  PngHuffmanDecoder (const PngHuffmanDecoder &) ;
  PngHuffmanDecoder &operator=(const PngHuffmanDecoder &) ;

  enum { MaxHuffmanCodeLength = 15, } ;
 
  // Maximum Huffman code value of length N
  int maxcode [MaxHuffmanCodeLength] ;
  // Minimum Huffman code value of length N
  int mincode [MaxHuffmanCodeLength] ;
  // Index into "values" for minimum code of length N
  UBYTE2 valptr [MaxHuffmanCodeLength] ;
  // Huffman values
  UBYTE2 huff_values [PngMaxNumberOfHuffmanCodes] ;

  unsigned int value_count ;
} ;

#endif
