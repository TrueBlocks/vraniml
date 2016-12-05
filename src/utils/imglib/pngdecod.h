#ifndef __PNGDECOD_H
#define __PNGDECOD_H
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
//  Title:  PNG Decoder class definition
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//
//  Description:
//
//    This class is a decoder for PNG images
//

#include "bitimage.h"
#include "grexcept.h"
#include "png.h"

class PngHuffmanDecoder ;

class PngDecoder : public BitmapImageDecoder
{
public:
  PngDecoder () ;
  PngDecoder (const PngDecoder &) ;
  virtual ~PngDecoder () ;
  PngDecoder &operator=(PngDecoder &) ;

  virtual void ReadImage (inputStream &, BitmapImage &) ;

  void SetVerbose (bool) ;
  bool GetVerbose () const ;

private:
  void Initialize () ;
  void DoCopy (const PngDecoder &) ;

  struct InterlaceInfo
  {
    unsigned int row_interval ;
    unsigned int col_interval ;
    unsigned int start_row ;
    unsigned int start_col ;
  } ;

  // Function to read the PNG signature.
  void ReadSignature () ;
  // Function to read a single PNG chunk
  void ReadChunk () ;

  // Functions for processing chunks
  void ProcessHeader () ;
  void ProcessPalette () ;
  void ProcessBackground () ;
  void ProcessGamma () ;
  void ProcessData () ;
  void ProcessChromaticities () ;
  void ProcessHistogram () ;
  void ProcessPhysicalPixelDimensions () ;
  void ProcessSignificantBits () ;
  void ProcessTextualData () ;
  void ProcessImageTime () ;
  void ProcessTransparency () ;
  void ProcessCompressedText () ;

  void CallProgressFunction (unsigned int percent) ;

  // Raw Input Functions
  int GetBits (unsigned int count=1) ;
  UBYTE1 GetIDATByte () ;

  // Deflate Functions
  UBYTE1 DecodeByte () ;
  void StartNewDataSet () ;
  void CheckAdler () ;
  void ReadLengths (PngHuffmanDecoder &, unsigned int [], unsigned int) ;
  UBYTE1 DecodeLiteralByte () ;
  UBYTE1 DecodeCompressedByte () ;

  void FreeData () ;

  // Function for reading pixel data for the image.
  void ReadPixelData () ;
  void CopyNoninterlacedRowToImage (unsigned int row);
  void CopyInterlacedRowToImage (unsigned int row, unsigned int width) ;
  void ReadNoninterlaced () ;
  void ReadInterlaced () ;
  void FilterRow (unsigned int filter) ;

  // Background Color Values
  UBYTE1 background_red ;
  UBYTE1 background_green ;
  UBYTE1 background_blue ;
  UBYTE1 background_gray ;

  // Current chunk information
  UBYTE4 chunk_length ;
  UBYTE4 chunk_type ;
  UBYTE1 *chunk_data ;
  UBYTE4 chunk_data_size ;
  UBYTE4 chunk_crc ;

  // Deflate State Variables
  UBYTE4 stream_adler ;
  UBYTE1 *lz_window ;
  unsigned int window_position ;
  unsigned int copy_position ;
  unsigned int copy_count ;
  PngHuffmanDecoder *literal_table ;
  PngHuffmanDecoder *distance_table ;
  bool final_data_set ;        // Final data set read
  bool literal_mode ;          // true => Reading a literal stream
  unsigned int literal_count ; // Number remaining literal bytes

  inputStream *input_stream ;
  BitmapImage *current_image ;
//  bool verbose_flag ;
  unsigned int palette_size ;
  bool reading_pixel_data ;  // Set to true while reading IDAT blocks

  // IDAT read state
  unsigned int bit_offset ;    // Bit offset into current byte.
  unsigned int byte_offset ;   // Byte offset into current IDAT chunk
  UBYTE1 bit_buffer ;          // IDAT read state

  // Image information from the header
  UBYTE4 image_height ;
  UBYTE4 image_width ;
  UBYTE1 image_depth ;
  unsigned int image_color_type ;
  UBYTE1 image_compression_method ;
  UBYTE1 image_filter_method ;
  UBYTE1 image_interlace_method ;

  // Row input buffers
  UBYTE1 *row_buffers [2] ;
  int current_row_buffer ;
  unsigned int row_buffer_width ;

  unsigned int interlace_pass ;  // Current interlace pass
  double file_gamma ;  // Value from a gAMAchunk

  bool data_read ; // False until IDAT chunk read.
  bool palette_read ; // False until PLTE chunk read.
  bool header_read ; // False until IHDR chunk read.
  bool end_read ; // False until IEND chunk read.

  static const InterlaceInfo interlace_values [] ;

  friend class PngHuffmanDecoder ;
} ;

inline void PngDecoder::SetVerbose (bool value)
{
//  verbose_flag = value ;
  return ;
}

inline bool PngDecoder::GetVerbose () const
{
  return 0; //verbose_flag ;
}

#endif
