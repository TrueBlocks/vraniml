//
// Copyright (c) 1997 Colosseum Builders, Inc.
// All rights reserved.
//
// Colosseum Builders, Inc. makes no warranty, expressed or implied
// with regards to this software. It is provided as is.
//
// Permission to use, redistribute, and copy this file is granted
// without a fee so long as as the following conditions are adhered to:
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
//  Title:  PNG Encoder Class Implementation
//
//  Author:  John M. Miano miano@colosseumbuilders.com
//

#include <limits.h>
#include <memory.h>
#include <string.h>

#include "pngencod.h"
#include "pngpvt.h"
#include "pngchksm.h"
#include "pnghuffe.h"

// Size definitions for the lookahead buffer.
const unsigned int LookaheadSize = (1 << 9) ; // 1st power of 2 greater than 258
const unsigned int LookaheadMask = LookaheadSize - 1 ;

// Hash Table size definitions.
const unsigned int HashBits = 5 ;
const unsigned int HashTableSize = 1 << (3 * HashBits) ;

// Size of the output buffer. This value defines the maximum size for
// IDAT block. This value must be larger than the size of any non-IDAT
// blocks used to write the image. Other than that the value can be
// selected arbitrarily.
const unsigned int OutputBufferSize = (1 << 13) ;

// End of image marker for the lookahead buffer.
const unsigned int ENDIMAGE = 0xFFFF ;

static inline Hash (UBYTE1 v1, UBYTE1 v2, UBYTE1 v3)
{
  const unsigned int mask = (1 << HashBits) - 1 ;
  unsigned int value = (v1 & mask )
                     | ((v2 & mask) << HashBits)
                     | ((v3 & mask) << (2 * HashBits)) ;
  return value ;

}

static void DistanceToCode (unsigned int distance, unsigned int &code,
                            unsigned int &extra, unsigned int &value)
{
  // maxvalue [n] is the maximum distance value for the code n.
  const unsigned int maxvalue [PngMaxDistanceCodes] =
    {
         1,     2,     3,     4,     6,     8,    12,    16,    24,    32,
        48,    64,    96,   128,   192,   256,   384,   512,   768,  1024,
      1536,  2048,  3072,  4096,  6144,  8192, 12288, 16384, 24576, 32768,
    } ;
  // extras [n] is the number of extra bits for the code n.
  const unsigned int extras [PngMaxDistanceCodes] =
    {
      0, 0,  0,  0,  1,  1,  2,  2,  3, 3,
      4, 4,  5,  5,  6,  6,  7,  7,  8, 8,
      9, 9, 10, 10, 11, 11, 12, 12, 13, 13,
    } ;

  // bases [n] is the smallest distance value for code n.
  const unsigned int bases [PngMaxDistanceCodes] =
    {
         1,    2,    3,    4,    5,    7,    9,    13,    17,    25,
        33,   49,   65,   97,  129,  193,  257,   385,   513,   769,
      1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577,
    } ;

  for (code = 0 ; code < PngMaxDistanceCodes ; ++ code)
  {
    if (distance <=  maxvalue [code])
      break ;
  }
  extra = extras [code] ;
  value = distance - bases [code] ;
  return ;
}

inline static void LengthToCode (unsigned int length, unsigned int &code,
                                 unsigned int &extra, unsigned int &value)
{
  // codes [n] is the length for for length n - 3.
  const UBYTE2 codes [PngLongestLength-2] =
    {
      257, 258, 259, 260, 261, 262, 263, 264,
      265, 265, 266, 266, 267, 267, 268, 268,
      269, 269, 269, 269, 270, 270, 270, 270,
      271, 271, 271, 271, 272, 272, 272, 272,
      273, 273, 273, 273, 273, 273, 273, 273,
      274, 274, 274, 274, 274, 274, 274, 274,
      275, 275, 275, 275, 275, 275, 275, 275,
      276, 276, 276, 276, 276, 276, 276, 276,
      277, 277, 277, 277, 277, 277, 277, 277,
      277, 277, 277, 277, 277, 277, 277, 277,
      278, 278, 278, 278, 278, 278, 278, 278,
      278, 278, 278, 278, 278, 278, 278, 278,
      279, 279, 279, 279, 279, 279, 279, 279,
      279, 279, 279, 279, 279, 279, 279, 279,
      280, 280, 280, 280, 280, 280, 280, 280,
      280, 280, 280, 280, 280, 280, 280, 280,
      281, 281, 281, 281, 281, 281, 281, 281,
      281, 281, 281, 281, 281, 281, 281, 281,
      281, 281, 281, 281, 281, 281, 281, 281,
      281, 281, 281, 281, 281, 281, 281, 281,
      282, 282, 282, 282, 282, 282, 282, 282,
      282, 282, 282, 282, 282, 282, 282, 282,
      282, 282, 282, 282, 282, 282, 282, 282,
      282, 282, 282, 282, 282, 282, 282, 282,
      283, 283, 283, 283, 283, 283, 283, 283,
      283, 283, 283, 283, 283, 283, 283, 283,
      283, 283, 283, 283, 283, 283, 283, 283,
      283, 283, 283, 283, 283, 283, 283, 283,
      284, 284, 284, 284, 284, 284, 284, 284,
      284, 284, 284, 284, 284, 284, 284, 284,
      284, 284, 284, 284, 284, 284, 284, 284,
      284, 284, 284, 284, 284, 284, 284, 285,
    } ;

  // extras [n] is the number of extra bits for code n.
  const UBYTE1 extras [PngMaxLengthCodes - PngFirstLengthCode] =
    {
      0, 0, 0, 0, 0, 0, 0, 0,
      1, 1, 1, 1, 2, 2, 2, 2,
      3, 3, 3, 3, 4, 4, 4, 4,
      5, 5, 5, 5, 0,
    } ;
  const UBYTE2 basevalues [PngMaxLengthCodes - PngFirstLengthCode] =
    {
        3,   4,   5,   6,   7,   8,   9,  10,
       11,  13,  15,  17,  19,  23,  27,  31,
       35,  43,  51,  59,  67,  83,  99, 115,
      131, 163, 195, 227, 258,
    } ;

  code = codes [length - 3] ;
  extra = extras [code - PngFirstLengthCode] ;
  value = length - basevalues [code - PngFirstLengthCode] ;
  return ;
}

//
//  Description:
//  
//    Class Default Constructor
//
PngEncoder::PngEncoder ()
{
  Initialize () ;
  return ;
}

//
//  Description:
//
//    Class Copy Constructor
//
PngEncoder::PngEncoder (const PngEncoder &source)
{
  Initialize () ;
  DoCopy (source) ;
  return ;
}

//
//  Description:
//
//    Class Destructor
//
PngEncoder::~PngEncoder ()
{
  FreeBuffers () ;
  delete distance_table ;
  delete length_table ;
  delete length_length_table ;
  return ;
}

//
//  Descriptor:
//
//    Assignment Operator
//
//  Parameters:
//    source: The object to copy
//
PngEncoder &PngEncoder::operator=(const PngEncoder &source)
{
  DoCopy (source) ;
  return *this ;
}

//
//  Description:
//
//    Common class initialization function. This function is
//    called from constructors to initialize the object.
//
void PngEncoder::Initialize ()
{
  MakeCrcTable () ;
  strcpy(software_string, "Colosseum Builders Image Library");
  current_image = NULL ;
  compression_level = DefaultCompression ;

  filter_mask = 0x1 ;

  for (unsigned int ii = 0 ; ii < FilterBufferCount ; ++ ii)
    filter_buffers [ii] = NULL ;

  distance_table = new PngHuffmanEncoder ;
  length_table = new PngHuffmanEncoder ;
  length_length_table = new PngHuffmanEncoder ;

  lz_window = NULL ;
  lookahead_buffer = NULL ;

  block_buffer = NULL ;
  block_buffer_size = 0x4000 ;
  return ;
}

//
//  Description:
//
//    Class copy function. This function is called from the copy 
//    constructor and assignment operator.
//
//  Parameters:
//    source:  The object to copy
//
void PngEncoder::DoCopy (const PngEncoder &source)
{
  strcpy(title_string, source.title_string);
  strcpy(author_string, source.author_string);
  strcpy(description_string, source.description_string);
  strcpy(copyright_string, source.copyright_string);
  strcpy(software_string, source.software_string);
  strcpy(disclaimer_string, source.disclaimer_string);
  strcpy(warning_string, source.warning_string);
  strcpy(source_string, source.source_string);
  strcpy(comment_string, source.comment_string);
  compression_level = source.compression_level ;
  filter_mask = source.filter_mask ;
  block_buffer_size = source.block_buffer_size ;
  BitmapImageEncoder::DoCopy (source) ;
  return ;
}

//
//  Description:
//
//    This function writes an image to a PNG stream.
//
//  Parameters:
//    strm:  The output stream
//    image:  The image to outpu
//
void PngEncoder::WriteImage (outputStream &strm, BitmapImage &image)
{
  current_image = &image ;
  output_stream = &strm ;

  try
  {
    DoWrite () ;
  }
  catch (...)
  {
    FreeBuffers () ;
    throw ;
  }
  FreeBuffers () ;
  return ;
}

//
//  Description:
//
//    This function frees the buffers allowed during the encoding
//    process.
//
void PngEncoder::FreeBuffers ()
{
  current_image = NULL ;
  output_stream = NULL ;
  delete [] lz_window ; lz_window = NULL ;
  delete [] lookahead_buffer ; lookahead_buffer = NULL ;
  delete [] hash_values ; hash_values = NULL ;
  delete [] hash_table ; hash_table = NULL ;
  delete [] output_buffer ; output_buffer = NULL ;
  for (unsigned int ii = 0 ; ii < FilterBufferCount ; ++ ii)
  {
    delete [] filter_buffers [ii] ; filter_buffers [ii] = NULL ;
  }
  return ;
}

//
//  Description:
//
//    This function calculates the hash value from a location
//    in the input stream. We create the hash value by
//    extracting a fixed number of the low order bits from each
//    of the next three data values.
//
//  Parameters:
//    index: The index into the lookahead buffer
//
//  Return Value:
//    The hash value
//
#pragma warning (disable : 4244)
#pragma warning (disable : 4018)
unsigned int PngEncoder::HashValue (unsigned int index)
{
  unsigned int i1 = index & LookaheadMask ;
  unsigned int i2 = (index + 1) & LookaheadMask ;
  unsigned int i3 = (index + 2) & LookaheadMask ;

  return Hash (lookahead_buffer [i1],
               lookahead_buffer [i2],
               lookahead_buffer [i3]) ;
}

//
//  Description:
//
//    This function finds the longest string in the LZ
//    window that matches the data in the lookahead buffer.
//
//    Since the hash changes can get very long under certain
//    circumstances we use the search_limit to set a limit
//    to how far we search in the tree.
//
//  Parameters:
//    bestlength: The longest match found (0=>No match)
//    bestoffset: The location where the best match was found
//
void PngEncoder::LongestMatch (unsigned int &bestlength,
                               unsigned int &bestoffset)
{
  bestlength = 0 ;

  unsigned int hashvalue = HashValue (lookahead_position) ;
  if (hash_table [hashvalue].next == NULL)
    return ;

  unsigned int chain ;
  HashEntry *current ;
  for (chain = 0 , current = hash_table [hashvalue].next ;
       current != NULL && chain < search_limit ;
       current = current->next, ++ chain)
  {
    unsigned int src = lookahead_position ;
    unsigned int dest = current->index ;
    unsigned int len  ;
    for (len = 0 ;
         len < PngLongestLength
         && ((current->index + len) & PngWindowMask)
             != lz_position ;
         ++ len, dest = (dest + 1) & PngWindowMask,
         src = (src + 1) & LookaheadMask)
    {
      unsigned int lookahead = lookahead_buffer [src] ;
      unsigned int window = lz_window [dest] ;
      if (lookahead != window)
        break ;
    }
    // We only care about matches longer than 3
    if (len >= 3 && len > bestlength)
    {
      bestlength = len ;
      bestoffset = PngWindowSize
                - ((PngWindowSize + current->index - lz_position)
                    & PngWindowMask) ;
      if (bestlength == PngLongestLength)
        break ;
    }
  }
  return ;
}

//
//  Description:
//
//    This function reads data from the input stream into the
//    lookahead buffer.
//
//  Parameters:
//    count:  The number of bytes to read
//
void PngEncoder::FillBuffer (unsigned int count)
{
  if (image_end)
   return ;

  unsigned int index = (lookahead_position + LookaheadSize - count)
                       & LookaheadMask ;

  if (current_image->BitCount () != 24)
  {
    // This block handles images with 8-bits per pixel or fewer.
    for (unsigned int ii = 0 ;
         ii < count && ! image_end ;
         ++ ii, ++ index)
    {
      if (image_col >= row_width)
      {
        // We need to advance to the next row.
        image_col = 0 ;
        ++ image_row ;
        if (image_row >= (int) current_image->Height ())
        {
          // We have hit the end of the image.
          lookahead_buffer [index & LookaheadMask] = ENDIMAGE ;
          image_end = true ;
        }
        else
        {
          // Here we start a new row. The data value from this
          // block is the filter code.
          CallProgressFunction (100 * image_row/current_image->Height ()) ;

          FilterRow (image_row) ;
          lookahead_buffer [index & LookaheadMask]
              = current_filter ;
          adler_value
              = Adler (adler_value,
                       lookahead_buffer [index & LookaheadMask]) ;
        }
      }
      else
      {
        // Here we are processing the middle of a pixel row.
        lookahead_buffer [index & LookaheadMask]
            = filter_buffers [current_filter][image_col] ;
        adler_value
            = Adler (adler_value,
                     lookahead_buffer [index & LookaheadMask]) ;
        ++ image_col ;
      }
    }
  }
  else
  {
    // Here we handle 24-bits per pixel images.
    for (unsigned int ii = 0 ;
         ii < count && ! image_end ;
         ++ ii, ++ index)
    {
      if (image_col >= row_width)
      {
        // We have hit the end of the row.
        image_col = 0 ;
        ++ image_row ;
        if (image_row >= current_image->Height ())
        {
          // There is no more data in the image.
          lookahead_buffer [index & LookaheadMask] = ENDIMAGE ;
          image_end = true ;
        }
        else
        {
          // Here we are starting a new row. The value
          // we return from here is the filter value.
          CallProgressFunction (100 * image_row/current_image->Height ()) ;

          FilterRow (image_row) ;
          lookahead_buffer [index & LookaheadMask]
            = current_filter ;
          adler_value
              = Adler (adler_value,
                       lookahead_buffer [index & LookaheadMask]) ;
        }
      }
      else
      {
        // We are processing the middle of a pixel row.

        // We would not have to go through all the trouble we do here
        // if we knew the BitmapImage class stored colors in RGB order.
        // For windows, they have to be in BGR order.

        unsigned int color = image_col % 3 ;
        unsigned int col = image_col - color ;
        if (color == 0)
        {
          lookahead_buffer [index & LookaheadMask]
           = filter_buffers [current_filter][col + BitmapImage::RedOffset] ;
        }
        else if (color == 1)
        {
          lookahead_buffer [index & LookaheadMask]
           = filter_buffers [current_filter][col + BitmapImage::GreenOffset] ;
        }
        else
        {
          lookahead_buffer [index & LookaheadMask]
           = filter_buffers [current_filter][col + BitmapImage::BlueOffset] ;
        }
        adler_value
          = Adler (adler_value,
                   lookahead_buffer [index & LookaheadMask]) ;
        ++ image_col ;
      }
    }
  }
  return ;
}

//
//  Description:
//
//    This function moves a hash entry corresponding to a position
//    in the LZ window to a specified hash chain.
//
//  Parameter:
//    entry: The Hash Entry (index into the LZ window)
//    hashvalue:  The new hashvalue for the entry.
//
void PngEncoder::MoveHashEntry (unsigned int entry, unsigned int hashvalue)
{
  HashEntry *he = &hash_values [entry] ;
  if (he->previous != NULL)
    he->previous->next = he->next ;
  if (he->next != NULL)
    he->next->previous = he->previous ;

  he->next = hash_table [hashvalue].next ;
  he->previous = &hash_table [hashvalue] ;
  hash_table [hashvalue].next = he ;
  if (he->next != NULL)
    he->next->previous = he ;

  return ;
}

//
//  Description:
//
//    This function finds the length encoding for
//    a length or distance table.
//
//  Parameters:
//    function: The function to process the code
//    lengths: lengths [n] = the length of the huffman code for n.
//    count: The number of coe lengths
//
void PngEncoder::FindLengthCodes (LENGTHFUNCTION function,
                                  UBYTE1 lengths [],
                                  unsigned int count)
{
  for (unsigned int ii = 0, jj ; ii < count ; ii = jj)
  {
    if (lengths [ii] != 0)
    {
      (this->*function) (ii, lengths [ii], 0, 0) ;
      jj = ii + 1 ;
    }
    else
    {
      // Attempt to compact runs of zero length codes.  
      // First find the number of consecutive zeros.
      for (jj = ii + 1;
           lengths [jj] == lengths [jj-1]
           && jj < count ;
           ++ jj)
      {
      }

      // We need at least 3 consecutive zeros to compact them.
      switch (jj - ii)
      {
      case 1:
        (this->*function) (ii, lengths [ii], 0, 0) ;
        break ;
      case 2:
        (this->*function) (ii, lengths [ii], 0, 0) ;
        (this->*function) (ii + 1, lengths [ii], 0, 0) ;
        break ;
      default:
        {
          // We have at least three zeros.

          int kk = jj - ii ;
          if (kk > 138)
          {
            kk = 138 ;
            jj = ii + kk ;
          }
          if (kk > 10)
          {
            (this->*function) (ii, 18, 7, kk - 11) ;
          }
          else
          {
            (this->*function) (ii, 17, 3, kk - 3) ;
          }
        }
        break ;
      }
    }
  }
  return ;
}


//
//  Description:
//
//    This function is passed as a parameter to FindLengthCodes.
//    It is use to find the frequency for each code.
//
//  Parameters:
//    code:  The code generated by FindLengthCodes
//
void PngEncoder::GatherLengthCounts (unsigned int,
                                     unsigned int code,
                                     unsigned int,
                                     unsigned int)
{
  length_length_table->IncrementFrequency (code) ;
  return ;
}

//
//  Description:
//
//    This function is passed as a parameter to FindLengthCodes.
//    It is use to encode and output the code to the output stream.
//
//  Parameters:
//    code:  The code generated by FindLengthCodes
//    extra:  The number of extra bits of data for the code
//    value:  The extra value
//
void PngEncoder::OutputLengthCounts (unsigned int,   // Index - Not used here
                                     unsigned int code,
                                     unsigned int extra,
                                     unsigned int value)
{
  UBYTE2 huffmancode ;
  UBYTE1 huffmansize ;
  length_length_table->Encode (code, huffmancode, huffmansize) ;

  OutputDataBits (huffmancode, huffmansize) ;
  if (extra != 0)
    OutputDataBits (value, extra) ;

  return ;
}

//
//  Description:
//
//    This function is called to start a new chunk.
//
//  Parameters:
//    type:  The PNG Chunk type (e.g. "IHDR", "IDAT")
//
void PngEncoder::StartChunk (const char type [5])
{
  chunk_type = ChunkType (type) ;
  bit_position = 0 ;
  byte_position = 0 ;
  output_buffer [0] = 0 ;
  return ;
}

//
//  Description:
//
//    This function outputs the current chunk.
//
void PngEncoder::WriteCurrentChunk ()
{
  // Calculate the CRC value for the chunk type and data
  UBYTE4 crc = 0xFFFFFFFFL ;
  crc = CRC32 (crc, &chunk_type, sizeof (chunk_type)) ;
  crc = CRC32 (crc, output_buffer, byte_position) ;
  crc ^= 0xFFFFFFFFL ;
  crc = SystemToBigEndian (crc) ;
  // Output the chunk. Length, type, data, CRC
  UBYTE4 length = SystemToBigEndian (byte_position) ;
  output_stream->write ((char *) &length, sizeof (length)) ;
  output_stream->write ((char *) &chunk_type, sizeof (chunk_type)) ;
  output_stream->write ((char *) output_buffer, byte_position) ;
  output_stream->write ((char *) &crc, sizeof (crc)) ;

  byte_position = 0 ;
  bit_position = 0 ;
  return ;
}

//
//  Description:
//
//    This function writes a block of data to the current chunk.
//
//  Parameters:
//    data: Pointer to the data to write
//    length: Number of bytes to write
//
void PngEncoder::OutputBlock (const void *data, unsigned int length)
{
  if (byte_position + length > OutputBufferSize)
    throw EPngError ("Output Buffer Overrun") ;

  memcpy (&output_buffer [byte_position], data, length) ;
  byte_position += length ;
  return;
}

//
//  Description:
//
//    This function writes the Adler value calculated for
//    the input data to the current chunk.
//    
void PngEncoder::OutputAdler ()
{
  FlushBitBuffer () ;
  adler_value = SystemToBigEndian (adler_value) ;
  UBYTE1 *buffer = (UBYTE1*) &adler_value ;
  for (unsigned int ii = 0 ; ii < sizeof (adler_value) ; ++ ii)
  {
    if (byte_position == OutputBufferSize)
      WriteCurrentChunk () ;

    output_buffer [byte_position] = buffer [ii] ;
    ++ byte_position ;
  }
  return ;
}

//
//  Description:
//
//    This function writes a number of data bits within an IDAT block.
//
//  Parameters:
//    data: The bits to output
//    length:  The number of bits to output
//
void PngEncoder::OutputDataBits (unsigned int data, unsigned int length)
{
  for (unsigned int ii = 0 ; ii < length ; ++ ii)
  {
    if (bit_position >= CHAR_BIT)
      FlushBitBuffer () ;

    if ((data & (1 << ii)) != 0)
    {
      output_buffer [byte_position] |= (1 << bit_position) ;
    }
    ++ bit_position ;
  }
  return ;
}

//
//  Description:
//
//    This function flushes any partial bytes that have been
//    written. This allows us to start writing byte data or 
//    start the next data byte.
//
void PngEncoder::FlushBitBuffer ()
{
  if (bit_position == 0)
    return ;

  ++ byte_position ;
  if (byte_position >= OutputBufferSize)
  {
    WriteCurrentChunk () ;
    StartChunk ("IDAT") ;
  }
  output_buffer [byte_position] = 0 ;
  bit_position = 0 ;
  return ;
}

//
//  Description:
//
//    This function encodes the image data. Depending upon
//    the function arguments this function either gathers
//    Huffman usage statistics or Huffman-encodes the data.
//
//  Return Value:
//    true => All data in the image has been processed
//    false => More data remains
//
bool PngEncoder::ProcessImageData ()
{
  InitializeHashTable () ;
  // Here we loop until we either fill the block_buffer or
  // reach the end of the image.
  for (block_buffer_count = 0 ;
       block_buffer_count < block_buffer_size - 1
       && lookahead_buffer [lookahead_position]
          != ENDIMAGE ;
       ++ block_buffer_count)
  {
    // See if we can find a match for the input in the
    // LZ winow.
    unsigned int length ;
    unsigned int offset ;
    LongestMatch (length, offset) ;

    if (length == 0)
    {
      // There is no match of at least three. Encode this value a
      // literal value.
      UBYTE1 literal = lookahead_buffer [lookahead_position] ;

      unsigned int hashvalue = HashValue (lookahead_position) ;
      MoveHashEntry (lz_position, hashvalue) ;

      lz_window [lz_position] = literal ;

	   block_buffer [block_buffer_count] = literal ;
	   length_table->IncrementFrequency (literal) ;

	   lookahead_position
          = (lookahead_position + 1) & LookaheadMask ;
      lz_position = (lz_position + 1) & PngWindowMask ;

      FillBuffer (1) ;
    }
    else
    {
      // We have found a match.  First update the hash table and
      // copy the data in the LZ window.
      unsigned int source = (PngWindowSize + lz_position - offset)
                          & PngWindowMask ;
      for (unsigned int ii = 0 ; ii < length ; ++ ii, ++ source)
      {
        unsigned int hashvalue = HashValue (lookahead_position) ;
        MoveHashEntry (lz_position, hashvalue) ;

        lz_window [lz_position]
            = lz_window [source & PngWindowMask] ;
        lz_position
            = (lz_position + 1) & PngWindowMask ;
        lookahead_position
            = (lookahead_position + 1) & LookaheadMask ;
      }

	   block_buffer [block_buffer_count] = 256 + length ;
	   ++ block_buffer_count ;
	   block_buffer [block_buffer_count] = offset ;

      // Gather Huffman Statistics
      unsigned int code ;
      unsigned int extra ;
      unsigned int value ;
      LengthToCode (length, code, extra, value) ;
	   length_table->IncrementFrequency (code) ;
      DistanceToCode (offset, code, extra, value) ;
	   distance_table->IncrementFrequency (code) ;
      FillBuffer (length) ;
    }
  }
  length_table->IncrementFrequency (PngEndCode) ;
  if (lookahead_buffer [lookahead_position] == ENDIMAGE)
    return true ;
  else
    return false ;
}

//
//  Description:
//
//    This function outputs a single data byte.
//
//  Parameters:
//    value: The value to output
//
void PngEncoder::OutputByte (UBYTE1 value)
{
  output_buffer [byte_position] = value ;
  ++ byte_position ;
  return ;
}

//
//  Description:
//
//    This function calls the progress function if it has been
//    defined.
//
//  Parameters:
//    percent:  The completion percentage (0..100)
//
void PngEncoder::CallProgressFunction (unsigned int percent)
{
  if (progress_function == NULL)
    return ;

  if (percent > 100)
    percent = 100 ;

  bool cancel = false ;
  progress_function (*this, progress_data, 1, 1,
                     percent, cancel) ;
  return ;
}

//
//  Description:
// 
//    This function creates a tEXt chunk.
//
//  Parameters:
//    keyword:  The chunk keyword
//    value:  The keyword value
//
void PngEncoder::WriteText (char *keyword,
                            char *value)
{
//  if (keyword.length () > 79)
  if (strlen(keyword) > 79)
    throw EPngError ("tEXt Keyword Too Long") ;
//  if (value.length () + keyword.length () + 1 > OutputBufferSize)
  if (strlen(value) + strlen(keyword) + 1 > OutputBufferSize)
    throw EPngError ("tEXt Value Too Long") ;

  StartChunk ("tEXt") ;
//  OutputBlock (keyword.c_str (), keyword.length ()) ;
  OutputBlock (keyword, strlen(keyword)) ;
  OutputByte (0) ;
//  OutputBlock (value.c_str (), value.length ()) ;
  OutputBlock (value, strlen(value)) ;
  WriteCurrentChunk () ;
  return ;
}

//
//  Description:
//
//    This function outputs tEXt blocks for any keywords
//    that have values assigned to them.
//
void PngEncoder::WriteTextBlocks ()
{
  if (title_string) // != "")
    WriteText ("Title", title_string) ;
  if (author_string) // != "")
    WriteText ("Author", author_string) ;
  if (description_string) // != "")
    WriteText ("Description", description_string) ;
  if (copyright_string) // != "")
    WriteText ("Copyright", copyright_string) ;
  if (software_string) // != "")
    WriteText ("Software", software_string) ;
  if (disclaimer_string) // != "")
    WriteText ("Disclaimer", disclaimer_string) ;
  if (warning_string) // != "")
    WriteText ("Warning", warning_string) ;
  if (source_string) // != "")
    WriteText ("Source", source_string) ;
  if (comment_string) // != "")
    WriteText ("Comment", comment_string) ;
  return ;
}

//
//  Description:
//
//    This function sets the compression level used.  The compression level
//    determines the depth to which hash chains are searched.
//
//  Parameters:
//    value:  The new compression level
//
void PngEncoder::SetCompressionLevel (PngEncoder::CompressionLevel value)
{
  if (value < 0 || value > 3)
    throw EPngError ("Invalid Compression Level") ;

  compression_level = value ;
  return ;
}

//
//  Description:
//
//    The function returns the current compression level.
//
//  Return Value:
//    The compresion level.
//
PngEncoder::CompressionLevel PngEncoder::GetCompressionLevel () const
{
  return compression_level ;
}

//
//  Description:
//
//    This function performs the actual output of the image.
//
void PngEncoder::DoWrite ()
{
  // Needed because MSVC++ does not follow standard scoping rules
  // in for statements.
  unsigned int ii ;

  if (current_image->BitCount () == 24)
  {
    row_width = 3 * current_image->Width () ;
    filter_width = 3 ;
  }
  else
  {
    row_width = (current_image->BitCount () * current_image->Width ()
                 + CHAR_BIT - 1) / CHAR_BIT ;
    filter_width = 1 ;
  }

  lz_window = new UBYTE1 [PngWindowSize] ;
  lookahead_buffer = new UBYTE2 [LookaheadSize] ;
  hash_values = new HashEntry [PngWindowSize] ;
  hash_table = new HashEntry [HashTableSize] ;
  output_buffer = new UBYTE1 [OutputBufferSize] ;

  for (ii = 0 ; ii < FilterBufferCount ; ++ ii)
  {
    if (((1 << ii) & filter_mask) != 0)
      filter_buffers [ii] = new UBYTE1 [row_width] ;
  }

  // Convert the compression level to the maximum depth hash
  // chains are searched.
  switch (compression_level)
  {
  case FastestCompression:
    search_limit = 1 ;
    break;
  case FastCompression:
    search_limit = 64 ;
    break ;
  case DefaultCompression:
    search_limit = 128 ;
    break ;
  case MaximumCompression:
    search_limit = UINT_MAX ;
    break ;
  default:
    throw EPngError ("Invalid Compression Level") ;
  }

  // Fill in the image header.
  PngImageHeader header ;
  header.width = SystemToBigEndian ((UBYTE4) current_image->Width ()) ;
  header.height = SystemToBigEndian ((UBYTE4) current_image->Height ()) ;
  header.bitdepth = current_image->BitCount () ;
  if (current_image->BitCount () != 24)
  {
    // Determine if the image is grayscale.
    bool isgrayscale = true ;
    for (unsigned int ii = 0 ; ii < current_image->ColorCount () ; ++ ii)
    {
      if (current_image->ColorMap (ii).red != current_image->ColorMap (ii).green
          ||
          current_image->ColorMap (ii).red != current_image->ColorMap (ii).blue)
      {
        isgrayscale = false ;
        break ;
      }
    }

    if (isgrayscale)
      header.colortype = Grayscale ;
    else
      header.colortype = Palette ;
  }
  else
  {
    header.bitdepth = 8 ;
    header.colortype = RGB ;
  }
  header.compressionmethod = 0 ;
  header.filtermethod = 0 ;
  header.interlacemethod = 0 ;

  // Output the PNG Signature and header.
  output_stream->write ((char *) PngSignature, PngSignatureSize) ;
  StartChunk ("IHDR") ;
  OutputBlock (&header, sizeof (header)) ;
  WriteCurrentChunk () ;

  // Output any text blocks with keywords defined.
  WriteTextBlocks () ;

  // Output the palette if it is required.
  if (header.colortype == Palette)
  {
    StartChunk ("PLTE") ;
    for (unsigned int ii = 0 ; ii < current_image->ColorCount () ; ++ ii)
    {
      OutputByte (current_image->ColorMap (ii).red) ;
      OutputByte (current_image->ColorMap (ii).green) ;
      OutputByte (current_image->ColorMap (ii).blue) ;
    }
	WriteCurrentChunk () ;
  }

  WriteImageData () ;

  // Write the IEND marker.
  StartChunk ("IEND") ;
  WriteCurrentChunk () ;

  return ;
}

//
//  Description:
//
//    This function filters an image row.
//
//  Parameters:
//    row: The row to filter (1..imageheight - 1)
//
void PngEncoder::FilterRow (unsigned int row)
{
  // We need this because MSVC++ does not follow standard
  // scoping rules in for statements.
  unsigned int ii ;
  if (filter_mask == 0)
    throw EPngError ("INTERNAL ERROR - No Filters Selected") ;

  unsigned int mask = (1 << FilterNone) ;

  // Filter None
  for (ii = 0 ; ii < row_width ; ++ ii)
  {
    filter_buffers [FilterNone][ii] = (*current_image) [row][ii] ;
  }

  // Filter for each type in the filter_mask.
  if ((filter_mask & (1 << FilterSub)) != 0)
  {
    mask |= (1 << FilterSub) ;

    UBYTE1 last ;
    for (unsigned int ii = 0 ; ii < row_width ; ++ ii)
    {
      if (ii >= filter_width)
        last = (*current_image)[row][ii-filter_width] ;
      else
        last = 0 ;

      filter_buffers [FilterSub][ii] = (*current_image) [row][ii] - last ;
    }
  }

  if ((filter_mask & (1 << FilterUp)) != 0 && row > 0)
  {
    mask |= (1 << FilterUp) ;

    for (unsigned int ii = 0 ; ii < row_width ; ++ ii)
    {
      UBYTE1 above ;
      if (row == 0)
        above = 0 ;
      else
        above = (*current_image)[row-1][ii] ;
      filter_buffers [FilterUp][ii] = (*current_image) [row][ii] - above ;
    }
  }

  if ((filter_mask & (1 << FilterAverage)) != 0 && row > 0)
  {
    mask |= (1 << FilterAverage) ;

    UBYTE1 last ;
    UBYTE1 above ;
    for (unsigned int ii = 0 ; ii < row_width ; ++ ii)
    {
      if (ii >= filter_width)
        last = (*current_image)[row][ii - filter_width] ;
      else
        last = 0 ;
      if (row == 0)
        above = 0 ;
      else
        above = (*current_image) [row-1][ii] ;

      filter_buffers [FilterAverage][ii] =
        (*current_image) [row][ii] - (above + last) / 2 ;
    }
  }

  if ((filter_mask & (1 << FilterPaeth)) != 0 && row > 0)
  {
    mask |= (1 << FilterPaeth) ;

    UBYTE1 last ;
    UBYTE1 lastabove ;
    UBYTE1 above ;
    for (unsigned int ii = 0 ; ii < row_width ; ++ ii)
    {
      if (ii >= filter_width)
      {
        last = (*current_image)[row][ii-filter_width] ;
        if (row != 0)
          lastabove = (*current_image)[row-1][ii - filter_width] ;
        else
          lastabove = 0 ;
      }
      else
      {
        last = 0 ;
        lastabove = 0 ;
      }
      if (row == 0)
        above = 0 ;
      else
        above = (*current_image)[row-1][ii] ;
      filter_buffers [FilterPaeth][ii] = (*current_image) [row][ii]
                   - PaethPredictor (last, above, lastabove) ;
    }
  }

  // If we only performed FilterNone then we do not need to proceed
  // any further.  
  current_filter = FilterNone ;
  if (mask == (1 << FilterNone))
    return ;

  // Find the best filter. We do a simple test for the
  // longest runs of the same value.

  for (ii = 0 ; ii < FilterBufferCount ; ++ ii)
  {
    unsigned int longestrun = 0 ;
    if ((mask & (1<<ii)) != 0)
    {
      unsigned int run = 0 ;
      for (unsigned int jj = 4 ; jj < row_width ; ++ jj)
      {
        if (filter_buffers [ii][jj] == filter_buffers [ii][jj-1]
            && filter_buffers [ii][jj] == filter_buffers [ii][jj-2]
            && filter_buffers [ii][jj] == filter_buffers [ii][jj-3]
            && filter_buffers [ii][jj] == filter_buffers [ii][jj-4])
        {
          ++ run ;
        }
      }

      if (run > longestrun)
      {
        current_filter = ii ;
        longestrun = run ;
      }
    }
  }
  return ;
}

//
//  Description:
//
//    This function specifies whether or not filters are used.
//
//  Parameters:
//    value: true=>Use Filters, false=>Don't use filters
//
void PngEncoder::SetUseFilters (bool value)
{
  if (value)
    filter_mask = 0xFFFFFFFF ;
  else
    filter_mask = 0x1 ;
}

//
//  Description:
//
//   This function tells if filters are being used.
//
//  Return Value:
//    true=>Filters are being used
//    false=>Filters are not being used
//
bool PngEncoder::GetUseFilters () const
{
  if (filter_mask == 0x1)
    return false ;
  else
    return true ;
}

//
//  Description:
//
//    This function initializes the Hash Table.
//
//
void PngEncoder::InitializeHashTable ()
{
  int ii ;
  memset (hash_values, 0, sizeof (HashEntry) * PngWindowSize) ;
  memset (hash_table, 0, sizeof (HashEntry) * (1 << (3 * HashBits))) ;

  for (ii = 0 ; ii < PngWindowSize ; ++ ii)
    hash_values [ii].index = ii ;

  // Initialize the hash table to allow initial zero runs. Here we are
  // setting up the hash table so that it appears that we have read
  // 258 zero values before the actual compression begins. This way
  // if the first 258 data bytes contains a run of zeros then we already
  // have a code to compress them with.
  hash_table [Hash (0, 0, 0)].next = &hash_values [PngWindowSize - 1] ;
  hash_values [PngWindowSize - 1].next = &hash_table [0] ;

  for (ii = PngWindowSize - 2 ;
       ii > PngWindowSize - PngLongestLength - 1 ;
       -- ii)
  {
    hash_values [ii + 1].next = &hash_values [ii]  ;
    hash_values [ii].previous = &hash_values [ii + 1] ;
  }
  return ;
}

//
//  Description:
//
//    This function initializes the LZ77 Windows
//
void PngEncoder::InitializeLZWindow ()
{
  image_row = -1 ;
  image_col = 0xFFFFFFFFL ;
  image_end = false ;

  memset (lz_window, 0, PngWindowSize) ;

  lookahead_position = 0 ;
  lz_position = 0 ;
  // Final step: Fill the lookahead buffer.
  FillBuffer (LookaheadSize) ;
  FilterRow (0) ;
  return ;
}

//
//  Description:
//
//    This function writes a Deflate block header and Huffman table
//    descriptions to the output stream.
//
//  Parameters:
//    lastblock: true => This is the last block in the image
//               false => There are more blocks to come
//
void PngEncoder::OutputDeflateHeader (bool lastblock)
{
  // Determine the count of length/literal and distances that
  // are used.
  unsigned int lengthcount ;
  for (lengthcount = PngMaxLengthCodes ;
       lengthcount > 0 ;
       -- lengthcount)
  {
    if (length_table->ehufsi [lengthcount - 1] != 0)
      break ;
  }

  unsigned int distancecount ;
  for (distancecount = PngMaxLengthCodes ;
       distancecount > 0 ;
       -- distancecount)
  {
    if (distance_table->ehufsi [distancecount - 1] != 0)
      break ;
  }

  // Gather the Huffman statistics for encoding the
  // lengths then create the Huffman table for doing so.
  length_length_table->Reset () ;
  FindLengthCodes (&PngEncoder::GatherLengthCounts,
                   length_table->ehufsi,
                   lengthcount) ;
  FindLengthCodes (&PngEncoder::GatherLengthCounts,
                   distance_table->ehufsi,
                   distancecount) ;
  length_length_table->BuildTable (PngMaxLengthLengthCodeSize) ;

  // Count the number of lengths we have to output.
  unsigned int hclen ;
  for (hclen = 19 ; hclen > 0 ; -- hclen)
  {
    if (length_length_table->ehufsi [PngLengthOrder [hclen-1]] != 0)
      break ;
  }

  // Write the Deflate header to the IDAT bock.
  if (lastblock)
    OutputDataBits (1, 1) ;
  else
    OutputDataBits (0, 1) ;

  OutputDataBits (2, 2) ; // Dynamic Huffman Codes
  OutputDataBits (lengthcount - 257, 5) ;
  OutputDataBits (distancecount - 1, 5) ;
  OutputDataBits (hclen - 4, 4) ;
  // Output the data for the Huffman table that encodes the Huffman tables
  for (unsigned int ii = 0 ; ii < hclen ; ++ ii)
    OutputDataBits (length_length_table->ehufsi [PngLengthOrder [ii]], 3) ;

   // Huffman encode the lengths for the Length/Literal and Distance
  // Huffman tables.
  FindLengthCodes (&PngEncoder::OutputLengthCounts,
                   length_table->ehufsi,
                   lengthcount) ;
  FindLengthCodes (&PngEncoder::OutputLengthCounts,
                   distance_table->ehufsi,
                   distancecount) ;
  return ;
}

//
//  Description:
//
//    This function writes a ZLIB header to the output stream.
//
void PngEncoder::OutputZLibHeader ()
{
  UBYTE1 cmf = 0x78 ;  // 7=>32K Sliding Window, 8=> Deflate Compression
  UBYTE1 flg = compression_level << 6 ;
  UBYTE2 check = (cmf << 8) | flg ;
  flg |= 31 - (check % 31) ;
  OutputDataBits (cmf, 8) ;
  OutputDataBits (flg, 8) ;
  return ;
}

//
//  Description:
//
//    This function writes the image data to a series of IDAT blocks.
//
void PngEncoder::WriteImageData ()
{
  // Write the IDAT blocks.
  StartChunk ("IDAT") ;

  adler_value = 1 ;

  block_buffer = new UBYTE2 [block_buffer_size] ;

  InitializeLZWindow () ;
  OutputZLibHeader () ;

  CallProgressFunction (0) ;

  // What we are doing here is outputing the image into a series of
  // Deflate compressed blocks.
  for (bool nomoredata = false ; ! nomoredata ;)
  {
    // Save the input state
    length_table->Reset () ;
    distance_table->Reset () ;
    nomoredata = ProcessImageData () ;
    // Create the Huffman tables for length/literals and
    // distances.
    length_table->BuildTable (PngMaxLengthCodeSize) ;
    distance_table->BuildTable (PngMaxDistanceCodeSize) ;

    OutputDeflateHeader (nomoredata) ;
    OutputBlockData () ;
  }

  CallProgressFunction (100) ;
  OutputAdler () ;
  WriteCurrentChunk () ;

  return ;
}

//
//  Description:
//
//    This function Huffman encodes and outputs the buffered data.
//
//    The buffer is encoded so that
//
//      0..255  is a literal byte
//      256-514 is a length code of N-256
//
//    Each length code is followed by a distance code.
//
void PngEncoder::OutputBlockData ()
{
  UBYTE2 huffmancode ;
  UBYTE1 huffmansize ;
  unsigned int code ;
  unsigned int extra ;
  unsigned int value ;
  unsigned int limit = block_buffer_count ;
  for (unsigned int ii = 0 ; ii < limit ; ++ ii)
  {
    if (block_buffer [ii] < 256)
    {
      length_table->Encode (block_buffer [ii], huffmancode, huffmansize) ;
      OutputDataBits (huffmancode, huffmansize) ;
    }
    else
    {
      unsigned int length = block_buffer [ii] - 256 ;
      ++ ii ;
      unsigned int distance = block_buffer [ii] ;
      LengthToCode (length, code, extra, value) ;
      length_table->Encode (code, huffmancode, huffmansize) ;

      OutputDataBits (huffmancode, huffmansize) ;
      if (extra != 0)
        OutputDataBits (value, extra) ;

      DistanceToCode (distance, code, extra, value) ;
      distance_table->Encode (code, huffmancode, huffmansize) ;

      OutputDataBits (huffmancode, huffmansize) ;
      if (extra != 0)
        OutputDataBits (value, extra) ;
    }
  }
  length_table->Encode (PngEndCode, huffmancode, huffmansize) ;
  OutputDataBits (huffmancode, huffmansize) ;
  return ;
}
