#ifndef __PNGHUFFE_H
#define __PNGHUFFE_H
//
// Copyright (c) 1997,1998 Colosseum Builders, Inc.
// All rights reserved.
//
// Colosseum Builders, Inc. makes no warranty, expressed or implied
// with regards to this software. It is provided as is.
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
// o This GIF decoder may be distributed and used without license fee
//   to the authors. It is our understanding that GIF decoding is not
//   covered by patents (which is why there are non-LZW GIF encoders).
//   However, we are not lawyers. If you wish to encorporate this software
//   then you should get your own legal advice.
//

//
//  Title:  PNG Huffman Encoding Class
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//
//  Description:
//
//    This class implements the Huffman encoder for the PNG encoder.
//

#include "png.h"

class PngEncoder ;

class PngHuffmanEncoder
{
public:
  PngHuffmanEncoder () ;
  virtual ~PngHuffmanEncoder () ;

  // ENCODING FUNCTIONS

  // This function resets the table so that the object can be used
  // over again.
  void Reset () ;

  // This function increases the frequency for a huffman value.
  void IncrementFrequency (unsigned int value) ;

  // This function creates the Huffman codes from the code frequencies.
  void BuildTable (unsigned int maxlength) ;

  // This function returns the Huffman code and code length to encode the
  // specified value.
  void Encode (unsigned int value, UBYTE2 &code, UBYTE1 &size) const ;

private:
  PngHuffmanEncoder (const PngHuffmanEncoder &) ;
  PngHuffmanEncoder &operator=(const PngHuffmanEncoder &) ;

  // This function builds the structures needed for Huffman
  // decoding after the table data has been read.
  void MakeTable () ;

  // frequencies [n] is the number of times the value "n" needs to
  // be encoded.
  unsigned int *frequencies ;

  // Values used to encode values.
  //   ehufsi [n] is the number of bits required to code "n"
  //   ehufco [n] is the Huffman code for "n"
  UBYTE1 *ehufsi ;
  UBYTE2 *ehufco ;

  friend class PngEncoder ;
} ;

#endif
