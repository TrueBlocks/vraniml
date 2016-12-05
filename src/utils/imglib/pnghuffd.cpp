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
//  Title:  PngHuffmanDecoder implementation
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//
//  Description:
//
//    This class handles Huffman decoding for PNG images.
//

//#include <iostream.h>

#include <memory.h>

#include "pnghuffd.h"
#include "pngdecod.h"

const unsigned int BADCODE = 0xFFFFFFF ;

//
//  Description:
//
//    This function creates a Huffman table from an array of code lengths.
//
//  Parameters:
//    valuecount: The number of huffman values
//    codelengths: Array of code lengths [0..valuecount-1]
//
//    codelengths [n] is the length of the Huffman code for the value n.
//
void PngHuffmanDecoder::MakeTable (unsigned int valuecount,
                              const unsigned int codelengths [])
{
  // We need this because MSVC++ does not follow standard scoping rules
  // in for statements.
  unsigned int ii ;

  value_count = valuecount ;
  unsigned int huffsizes [PngMaxNumberOfHuffmanCodes + 1] ;
  memset (huffsizes, 0, sizeof (huffsizes)) ;
  // Set up arrays to associate codes with code lengths. We have to do a copy
  // because this function can be called using fixed Huffman codes.
  for (ii = 0 ; ii < valuecount ; ++ ii)
  {
    huff_values [ii] = ii ;
    huffsizes [ii] = codelengths [ii] ;
  }

  // Sort the values. Primary key is code size. Secondary key is value.
  for (ii = 0 ; ii < valuecount - 1 ; ++ ii)
  {
    for (unsigned int jj = ii + 1 ; jj < valuecount ; ++ jj)
    {
      if (huffsizes [jj] < huffsizes [ii]
          || (huffsizes [jj] == huffsizes [ii]
              && huff_values [jj] < huff_values [ii]))
      {
        unsigned int tmp ;
        tmp = huffsizes [jj] ;
        huffsizes [jj] = huffsizes [ii] ;
        huffsizes [ii] = tmp ;
        tmp = huff_values [jj] ;
        huff_values [jj] = huff_values [ii] ;
        huff_values [ii] = tmp ;
      }
    }
  }
  // These values in these arrays correspond to the elements of the
  // "values" array. The Huffman code for values [N] is huffcodes [N]
  // and the length of the code is huffsizes [N].

  UBYTE2 huffcodes [PngMaxNumberOfHuffmanCodes+1] ;
  memset (huffcodes, 0, sizeof (huffcodes)) ;
  unsigned int lastlen ;
  unsigned int code ;
  for (ii = 0, lastlen = 0, code = 0  ; ii < valuecount ; ++ ii)
  {
    while (lastlen != huffsizes [ii])
    {
      ++ lastlen ;
      code <<= 1 ;
    }

    if (lastlen != 0)
    {
      huffcodes [ii] = code ;
      ++ code ;
    }
  }

  // mincode [n] : The smallest Huffman code of length n + 1.
  // maxcode [n] : The largest Huffman code of length n + 1.
  // valptr [n] : Index into the values array. First value with a code
  //                    of length n + 1.
  for (ii = 0 ; ii < MaxHuffmanCodeLength ; ++ ii)
  {
    valptr [ii] = 0 ;
    mincode [ii] = BADCODE ;
    maxcode [ii] = -1 ;
  }

  unsigned int last ;
  for (ii = 0, last = 0 ; ii < valuecount ; ++ ii)
  {
    if (last != huffsizes [ii])
    {
       last = huffsizes [ii] ;
       valptr [last-1] = ii ;
       mincode [last-1] = huffcodes [ii] ;
    }
    if (last != 0)
      maxcode [last-1] = huffcodes [ii] ;
  }
  return ;
}

//
//  Description:
//
//    This function decodes the next Huffman-encoded value in the input
//    stream.
//
//  Parameters:
//    decoder:  The PNG Decoder object.
//
int PngHuffmanDecoder::Decode (PngDecoder &decoder)
{
   // This function decodes the next byte in the input stream using this
   // Huffman table.

   UBYTE2 code = decoder.GetBits (1) ;
   int codelength ; // Called I in the standard.

   // Here we are taking advantage of the fact that 1 bits are used as
   // a prefix to the longer codes.
   for (codelength = 0 ;
        (code > maxcode [codelength] && codelength <
         MaxHuffmanCodeLength) ;
        ++ codelength)
   {
      code = (UBYTE2) ((code << 1) | decoder.GetBits (1)) ;
   }

   if (codelength >= MaxHuffmanCodeLength)
    throw EPngError ("Bad Huffman Code Length") ;

   // Now we have a Huffman code of length (codelength + 1) that
   // is somewhere in the range
   // mincode [codelength]..maxcode [codelength].

   // This code is the (offset + 1)'th code of (codelength + 1) ;
   int offset = code - mincode [codelength] ;

   // valptr [codelength] is the first code of length (codelength + 1)
   // so now we can look up the value for the Huffman code in the table.
   int index = valptr [codelength] + offset ;
   return huff_values [index] ;
}

//
//  Description:
//
//    This is a debugging function for writing the contents of the Huffman
//    table to cout.
//
void PngHuffmanDecoder::Dump () const
{
/*
  // We need this because MSVC++ does not follow standard scoping rules
  // for variables declared in for statements.
  unsigned int ii ;

  cout << "   Code Values (" << (int) value_count << "): " << endl ;
  for (ii = 0 ; ii < value_count ; ++ ii)
  {
    cout << ::dec << " (" << ii << ") " << (UBYTE2) huff_values [ii]  ;
    if ((ii + 1) % 8 == 0)
      cout << endl ;
  }
  cout << endl ;
  cout << "Length" << "\t\t" << "Mincode" << "\t\t"
       << "Maxcode" << "\t\t" << "Valptr" << endl ;
  cout << "-------------------------------------------------------" << endl ;

  unsigned int firstcode ;
  unsigned int lastcode ;
  for (firstcode = 0 ;
       mincode [firstcode] == BADCODE ;
       ++ firstcode)
  {
    // NoOp
  }
  for (ii = firstcode + 1 ;
       ii < MaxHuffmanCodeLength ;
       ++ ii)
  {
    if (mincode [ii] != BADCODE)
      lastcode = ii + 1 ;
  }

  for (ii = firstcode ; ii < lastcode ; ++ ii)
  {
    if (mincode [ii] != BADCODE)
    {
      cout << ::dec << (ii + 1) << "\t\t" << Binary (mincode [ii], ii + 1)
           << "\t\t" << Binary (maxcode [ii], ii + 1) << "\t\t"
           << (int) valptr [ii] << endl ;
    }
  }
*/
  return ;
}


