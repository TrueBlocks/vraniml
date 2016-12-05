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
//  Title:  PngHuffmanEncoder implementation
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//
//  Description:
//
//    This class handles Huffman Encoding for PNG images.
//

#include <memory.h>

#include "pnghuffe.h"
#include "pngencod.h"
#include "pngpvt.h"

//
//  Description:
//
//    Default Class Constructor
//
PngHuffmanEncoder::PngHuffmanEncoder ()
{
  frequencies = new unsigned int [PngMaxNumberOfHuffmanCodes] ;
  ehufsi = new UBYTE1 [PngMaxNumberOfHuffmanCodes] ;
  ehufco = new UBYTE2 [PngMaxNumberOfHuffmanCodes] ;

  Reset () ;
  return ;
}

//
//  Description:
//
//    Class Destructor
//
PngHuffmanEncoder::~PngHuffmanEncoder ()
{
  delete [] frequencies ; frequencies = NULL ;
  delete [] ehufsi ; ehufsi = NULL ;
  delete [] ehufco ; ehufco = NULL ;
  return ;
}

//
//  Description:
//
//    After Huffman codes have been generated the object is in a state
//    where it cannot be used to create a new set of code. This function
//    places the object in a state where it can be reused to generate a
//    new set of Huffman Codes.
//
void PngHuffmanEncoder::Reset ()
{
  memset (frequencies, 0, sizeof (*frequencies) * PngMaxNumberOfHuffmanCodes) ;
  return ;
}

//
//  Description:
//
//    Function to increment the frequency for a value.
//
//  Parameters:
//    value:  The value to increase the usage frequency of.
//
void PngHuffmanEncoder::IncrementFrequency (unsigned int value)
{
  if (value >= PngMaxNumberOfHuffmanCodes)
    throw EPngError ("Index out of range") ;

  ++ frequencies [value] ;
  return ;
}

//
//  Description:
//
//    This function generates the Huffman Codes using the frequency data. 
//
//    The outputs from this function are the following member variables:
//
//     ehufsi [n] : The length of the Huffman Code for value "n"
//     ehufco [n] : The Huffman Code for value "n"
//
//    The first two arrays are used to encode Huffman values. The last two
//    are for writing the table to the output file.
//
//    The code generation process is:
//
//    1. Arrange the Huffman Values into a binary tree so that the most
//       frequently used codes are closest to the root of the tree. At the end
//       of this process the temporary array codesize [n] contains the length
//       of the pure Huffman code for the value "n"
//
//    2. Determine the number of Huffman Codes of for each code length. This
//       step places the number of codes of length "n+1" in huffbits[].
//
//    3. The Default places limites on the size of Huffman Codes. If
//       codes longer that the specified limits were generated in the 
//       previous steps then we need to reduce the maximum depth of the 
//       tree created in step 1. The input and output to this step is the
//       array huffbits[] created in the previous step.
//
//    4. Sort the Huffman values in code length order. codesize [n] is the
//       input to this step and huffvalues [n] is the output. At this point
//       all the information needed to write the Huffman Table to the output
//       stream has been found.
//
//    5. Determine the code size for each value. At the end of this step
//       the temporary array huffsizes [n] is the Huffman code length for
//       huffvalues [n].
//
//    6. Determine the Huffman code for each value. The temporary array
//       huffcodes [n] is the Huffman Code of length huffsizes [n] for
//       the value huffvalue [n].
//
//    7. Using huffsizes [] and huffcodes created in steps 6 and 7 create
//       the arrays ehufco [n] and ehufsi [n] giving the Huffman Code and
//       Code Size for n.
//
//  Parameters:
//    maxlength:  The maximum code length to generate
//
void PngHuffmanEncoder::BuildTable (unsigned int maxlength)
{
  bool codestoolong = false ;

  // We need these because MSVC++ does not follow standard
  // scoping rules with for statements.
  unsigned int ii, kk, si ;

  memset (ehufsi, 0, sizeof (UBYTE1) * PngMaxNumberOfHuffmanCodes) ;
  memset (ehufco, 0, sizeof (UBYTE2) * PngMaxNumberOfHuffmanCodes) ;

  // The tmp array is used for validating the integrity of the Huffman code
  // table. We need a temporary array since frequencies [] gets trashed
  // during the code generation process.
  unsigned int tmp [PngMaxNumberOfHuffmanCodes] ;

  for (ii = 0 ; ii < PngMaxNumberOfHuffmanCodes ; ++ ii)
   	tmp [ii] = frequencies [ii] ;

  // Build the Huffman Code Length Lists
  int others [PngMaxNumberOfHuffmanCodes ] ;
  for (ii = 0 ; ii < PngMaxNumberOfHuffmanCodes ; ++ ii)
    others [ii] = -1 ;

  unsigned int codesize [PngMaxNumberOfHuffmanCodes] ;
  memset (codesize, 0, sizeof (codesize)) ;
  while (true)
  {
    // Find the two smallest non-zero values
    int v1 = -1 ;
    int v2 = -1 ;
    for (unsigned int ii = 0 ; ii < PngMaxNumberOfHuffmanCodes ; ++ ii)
    {
      if (frequencies [ii] != 0)
      {
        if (v1 < 0 || frequencies [ii] <= frequencies [v1])
        {
          v2 = v1 ;
          v1 = ii ;
        }
        else if (v2 < 0 || frequencies [ii] <= frequencies [v2])
        {
          v2 = ii ;
        }
      }
    }
    if (v2 < 0)
    {
      if (v1 < 0)
        return ; // No codes defined

      if (codesize [v1] == 0)
        codesize [v1] = 1 ;  // Only one code defined
      break ;
    }
    // Join the two tree nodes.
    frequencies [v1] = frequencies [v1] + frequencies [v2] ;
    frequencies [v2] = 0 ;

    for (++ codesize [v1] ; others [v1] >= 0 ; ++ codesize [v1])
      v1 = others [v1] ;

    others [v1] = v2 ;

    for (++ codesize [v2] ; others [v2] >= 0 ; ++ codesize [v2])
      v2 = others [v2] ;
  }

  // Determine the number of codes of length [n]
  unsigned int huffbits [30] ; // 2x needed for encoding only.
  memset (huffbits, 0, sizeof (huffbits)) ;
  for (ii = 0 ; ii < PngMaxNumberOfHuffmanCodes ; ++ ii)
  {
    if (codesize [ii] != 0)
    {
      ++ huffbits [codesize [ii] - 1] ;
    }
  }

  // Ensure that no code is longer than maxlength.
  for (ii = 2 * maxlength -  1 ;
       ii >= maxlength ;
       -- ii)
  {
    while (huffbits [ii] != 0)
    {
      codestoolong = true ; // Remember that we had to reorder the tree

      unsigned int jj = ii - 1 ;
      do
      {
        -- jj ;
      }
      while (huffbits [jj] == 0) ;

      huffbits [ii] -= 2 ;
      ++ huffbits [ii - 1] ;
      huffbits [jj + 1] += 2 ;
      -- huffbits [jj] ;
    }
  }

  // Make sure that the total number of symbols is correct.
  unsigned int count = 0 ;
  for (ii = 0 ; ii < maxlength ; ++ ii)
  {
    count += huffbits [ii] ;
  }
  if (count >= PngMaxNumberOfHuffmanCodes)
    throw EPngError ("INTERNAL ERROR - Too many codes defined") ;

  // Sort the values in order of code length
  UBYTE2 huffvalues [PngMaxNumberOfHuffmanCodes] ;
  memset (huffvalues, 0, sizeof (huffvalues)) ;
  for (ii = 1, kk = 0 ; ii < 2 * maxlength ; ++ ii)
  {
    for (unsigned int jj = 0 ; jj < PngMaxNumberOfHuffmanCodes ; ++ jj)
    {
      if (codesize [jj]  == ii)
      {
        huffvalues [kk] = jj ;
        ++ kk ;
      }
    }
  }

  // Convert the array "huffbits" containing the count of codes for each
  // length 1..maxlength into an array containing the length for each code.
  unsigned int huffsizes [PngMaxNumberOfHuffmanCodes] ;
  memset (huffsizes, 0, sizeof (huffsizes)) ;
  for (ii = 0, kk = 0 ; ii < maxlength ; ++ ii)
  {
     for (unsigned int jj = 0 ; jj < huffbits [ii] ; ++ jj)
     {
        huffsizes [kk] = ii + 1 ;
        ++ kk ;
     }
     huffsizes [kk] = 0 ;
  }

  // Calculate the Huffman code for each Huffman value.
  UBYTE2 code = 0 ;
  unsigned int huffcodes [PngMaxNumberOfHuffmanCodes] ;
  memset (huffcodes, 0, sizeof (huffcodes)) ;
  for (kk = 0, si = huffsizes [0] ;
       huffsizes [kk] != 0  ;
       ++ si, code <<= 1)
  {
     for ( ; huffsizes [kk] == si ; ++ code, ++ kk)
     {
        huffcodes [kk] = code ;
     }
  }

  memset (ehufco, 0, sizeof (ehufco)) ;
  memset (ehufsi, 0, sizeof (ehufsi)) ;
  for (kk = 0 ; kk < PngMaxNumberOfHuffmanCodes ; ++ kk)
  {
    if (huffsizes [kk] != 0)
    {
      unsigned int ii = huffvalues [kk] ;
      ehufco [ii] = huffcodes [kk] ;
      ehufsi [ii] = huffsizes [kk] ;
      if (ehufsi [ii] > maxlength)
        throw EPngError ("Invalid Huffman Code Generated") ;
    }
  }

  // If the pure Huffman code generation created codes longer than the
  // maximum the it is possible that the order got screwed up. Such a
  // situation could occur if the maximum code length is 15 and during the
  // pure process we the value 150 got assigned a length of 13, 100 a length
  // of 15 and 200 a length of 17. During the process of reducing the code
  // length for 200 it is possible that 150 would have its code length
  // increased to 14 and 100 would have its code length reduced to 14.
  // Unfortunately the Huffman codes would be assigned using the old
  // order so that 150 would get assigned a smaller Huffman code than
  // 100.  Here we fix that and ensure that if ehufsi [ii] == ehufsi [jj]
  //  and ii < jj then ehufco [ii] < ehufco [jj].
  if (codestoolong)
  {
    for (unsigned int ii = 0 ; ii < PngMaxNumberOfHuffmanCodes - 1 ; ++ ii)
    {
      for (unsigned int jj = ii + 1 ; jj < PngMaxNumberOfHuffmanCodes ; ++ jj)
      {
        if (ehufsi [ii] == ehufsi [jj] && ehufco [ii] > ehufco [jj])
        {
          // The codes got out of order so switch them.
          UBYTE2 tmp = ehufco [jj] ;
          ehufco [jj] = ehufco [ii] ;
          ehufco [ii] = tmp ;
        }
      }
    }
  }
  // Validations
  // This remaining code is not necessary other than to ensure the
  // integrity of the Huffman table that is generated.

  // Make sure each value is used exactly once.
  for (ii = 0 ; ii < PngMaxNumberOfHuffmanCodes ; ++ ii)
  {
    int count = 0 ;
    if (tmp [ii] != 0)
    {
      if (ehufsi [ii] == 0)
        throw EPngError ("INTERNAL ERROR - Missing Huffman Code Size") ;

      for (unsigned int jj = 0 ; jj < PngMaxNumberOfHuffmanCodes ; ++ jj)
      {
        if (ii == huffvalues [jj] && huffsizes [jj] != 0)
          ++ count ;
        if (count > 1)
          throw EPngError ("INTERNAL ERROR - Duplicate Huffman Value") ;
      }
      if (count == 0)
        throw EPngError ("INTERNAL ERROR - Missing Huffman Value") ;
    }
  }

  // Ensure that each huffman code is used once annd that the values
  // are in range.
  for (ii = 0 ; ii < PngMaxNumberOfHuffmanCodes ; ++ ii)
  {
    if (ehufsi [ii] != 0)
    {
      if (ehufsi [ii] > maxlength)
        throw EPngError ("INTERNAL ERROR - Invalid Huffman Range") ;

      for (unsigned int jj = ii + 1 ; jj < PngMaxNumberOfHuffmanCodes ; ++ jj)
      {
        if (ehufco [ii] == ehufco [jj] && ehufsi [jj] != 0)
          throw EPngError ("INTERNAL ERROR - Duplicate Huffman Code") ;
      }
    }
  }

  //
  // In PNG the Huffman codes are stored backwards. Here we reverse
  // each code.
  for (ii = 0 ; ii < PngMaxNumberOfHuffmanCodes ; ++ ii)
  {
    unsigned int value = 0 ;
    unsigned int code = ehufco [ii] ;
    unsigned int size = ehufsi [ii] ;
    for (unsigned int jj = 0 ; jj < ehufsi [ii] ; ++ jj)
    {
      unsigned int bit = (code & (1 << jj)) >> jj ;
      value |= bit << (size - jj - 1) ;
    }
    ehufco [ii] = value ;
  }

  return ;
}

//
//  Description:
//
//    This function returns the Huffman Code and Code Size for a given value.
//
//  Parameters:
//    value:  The value to encode
//    code:   The Huffman Code
//    size:   The Huffman Code Length
//
void PngHuffmanEncoder::Encode (unsigned int value,
                                UBYTE2 &code,
                                UBYTE1 &size) const
{
  if (value >= PngMaxNumberOfHuffmanCodes)
    throw EPngError ("Index Out of Range") ;

  if (ehufsi [value] == 0)
    throw EPngError ("INTERNAL ERROR - Missing Huffman Code") ;

  code = ehufco [value] ;
  size = ehufsi [value] ;
  return ;
}



