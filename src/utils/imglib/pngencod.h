#ifndef __PNGENCOD_H
#define __PNGENCOD_H
//
// Copyright (c) 1998 Colosseum Builders, Inc.
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
//  Title: PNG Encoder Class Definition
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//
//  Description:
//
//    This class implements PNG encoding.
//


#include <string.h>

#include "png.h"
#include "bitimage.h"

class PngHuffmanEncoder ;

class PngEncoder : public BitmapImageEncoder
{
public:
  PngEncoder () ;
  PngEncoder (const PngEncoder &) ;
  virtual ~PngEncoder () ;
  PngEncoder &operator=(const PngEncoder &) ;

  void WriteImage (outputStream &, BitmapImage &) ;

  // Property functions for predefined tEXt strings.
  void SetTitle (char *str) ;
  const char *GetTitle () const ;

  void SetAuthor (char *str) ;
  const char *GetAuthor () const ;

  void SetDescription (char *str) ;
  const char *GetDescription () const ;

  void SetCopyright (char *str) ;
  const char *GetCopyright () const ;

  void SetSoftware (char *str) ;
  const char *GetSoftware () const ;

  void SetDisclaimer (char *str) ;
  const char *GetDisclaimer () const ;

  void SetWarning (char *str) ;
  const char *GetWarning () const ;

  void SetSource (char *str) ;
  const char *GetSource () const ;

  void SetComment (char *str) ;
  const char *GetComment () const ;

  enum CompressionLevel
  {
    FastestCompression = 0,
    FastCompression = 1,
    DefaultCompression = 2,
    MaximumCompression = 3,
  } ;

  void SetCompressionLevel (CompressionLevel) ;
  CompressionLevel GetCompressionLevel () const ;
    
  void SetUseFilters (bool) ;
  bool GetUseFilters () const ;

  unsigned long GetBlockSize () const ;
  void SetBlockSize (unsigned long) ;

protected:
  void Initialize () ;
  void DoCopy (const PngEncoder &) ;

private:
  struct HashEntry
  {
    UBYTE2 index ;      // Index into the LZ Window
    HashEntry *next ;   // Next collision entry
    HashEntry *previous ;
  } ;
                   
  void LongestMatch (unsigned int &length,
                     unsigned int &offset) ;
  unsigned int HashValue (unsigned int) ;

  void MoveHashEntry (unsigned int entry, unsigned int hashvalue) ;

  HashEntry *hash_values ;
  HashEntry *hash_table ;

  BitmapImage *current_image ;
  outputStream *output_stream ;

  unsigned int search_limit ;

  PngHuffmanEncoder *distance_table ;
  PngHuffmanEncoder *length_table ;
  PngHuffmanEncoder *length_length_table ;

  typedef void (PngEncoder::*LENGTHFUNCTION) (unsigned int index,
                                              unsigned int code,
                                              unsigned int length,
                                              unsigned int extra) ;
  void GatherLengthCounts (unsigned int,
                           unsigned int code,
                           unsigned int,
                           unsigned int) ;
  void OutputLengthCounts (unsigned int index,
                           unsigned int code,
                           unsigned int extra,
                           unsigned int value) ;

  void FindLengthCodes (LENGTHFUNCTION, UBYTE1 lengths [], unsigned int count) ;

  bool ProcessImageData () ;

  UBYTE1 *output_buffer ;
  UBYTE4 chunk_type ;
  UBYTE4 byte_position ;
  unsigned int bit_position ;
  void StartChunk (const char type [5]) ;
  void WriteCurrentChunk () ;
  void OutputBlock (const void *data, unsigned int length) ;
  void OutputByte (UBYTE1) ;
  void OutputDataBits (unsigned int data, unsigned int length) ;
  void FlushBitBuffer () ;
  void OutputAdler () ;

  void FreeBuffers () ;
  void FillBuffer (unsigned int count) ;

  unsigned int row_width ;
  void WriteText (char *keyword, char *value) ;
  void WriteTextBlocks () ;

  void CallProgressFunction (unsigned int) ;

  char title_string[256];
  char author_string[256];
  char description_string[256];
  char copyright_string[256];
  char software_string[256];
  char disclaimer_string[256];
  char warning_string[256];
  char source_string[256];
  char comment_string[256];

  enum { FilterBufferCount = 5, } ;
  UBYTE1 *filter_buffers [FilterBufferCount] ;
  unsigned int current_filter ;
  unsigned int filter_mask ;
  unsigned int filter_width ;
  void FilterRow (unsigned int row) ;

  void DoWrite () ;

  CompressionLevel compression_level ;

  void InitializeHashTable () ;
  void InitializeLZWindow () ;
  void OutputDeflateHeader (bool lastblock) ;
  void OutputZLibHeader () ;
  void WriteImageData () ;

  UBYTE4 adler_value ;
  UBYTE1 *lz_window ;
  UBYTE2 *lookahead_buffer ;
  unsigned int lookahead_position  ;
  unsigned int lz_position ;
  int image_row ; // Must be Signed
  unsigned int image_col ;
  bool image_end ;

  UBYTE2 *block_buffer ;
  unsigned int block_buffer_size ;
  unsigned int block_buffer_count ;

  void OutputBlockData () ;
} ;

inline void PngEncoder::SetTitle (char *value)
{
  strncpy(title_string, value, 256);
  return ;
}

inline const char *PngEncoder::GetTitle () const
{
  return title_string ;
}

inline void PngEncoder::SetAuthor (char *value)
{
  strncpy(author_string, value, 256);
  return ;
}

inline const char *PngEncoder::GetAuthor () const
{
  return author_string ;
}

inline void PngEncoder::SetDescription (char *value)
{
  strncpy(description_string, value, 256);
  return ;
}

inline const char *PngEncoder::GetDescription () const
{
  return description_string ;
}

inline void PngEncoder::SetCopyright (char *value)
{
  strncpy(copyright_string, value, 256);
  return ;
}

inline const char *PngEncoder::GetCopyright () const
{
  return copyright_string ;
}

inline void PngEncoder::SetSoftware (char *value)
{
  strncpy(software_string, value, 256);
  return ;
}

inline const char *PngEncoder::GetSoftware () const
{
  return software_string ;
}

inline void PngEncoder::SetDisclaimer (char *value)
{
  strncpy(disclaimer_string, value, 256);
  return ;
}

inline const char *PngEncoder::GetDisclaimer () const
{
  return disclaimer_string ;
}

inline void PngEncoder::SetWarning (char *value)
{
  strncpy(warning_string, value, 256);
  return ;
}

inline const char *PngEncoder::GetWarning () const
{
  return warning_string ;
}

inline void PngEncoder::SetSource (char *value)
{
  strncpy(source_string, value, 256);
  return ;
}

inline const char *PngEncoder::GetSource () const 
{
  return source_string ;
}

inline void PngEncoder::SetComment (char *value)
{
  strncpy(comment_string, value, 256);
  return ;
}

inline const char *PngEncoder::GetComment () const
{
  return comment_string ;
}

inline unsigned long PngEncoder::GetBlockSize () const
{
  return block_buffer_size ;
}

inline void PngEncoder::SetBlockSize (unsigned long value)
{
  if (value < 500)
    block_buffer_size = 500 ;
  else
    block_buffer_size = value ;
  return ;
}


#endif


