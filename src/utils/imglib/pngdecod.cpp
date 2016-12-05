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
//  Title:  PNG Decoder class implementation
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//
//  Description:
//
//    This class is a decoder for PNG images
//
//#include <iomanip>

#include <limits.h>

#include <memory.h>

#include "pngchksm.h"
#include "pngdecod.h"
#include "pngpvt.h"
#include "pnghuffd.h"

//#define VERYVERBOSE

//using namespace std ;

const unsigned int Max8BitSampleValue = 255 ;

// Number of passes in an interlaced image.
const unsigned int InterlacePasses = 7 ;

// Deflate Compression Types
enum CompressionType
{
  Uncompressed = 0,
  FixedHuffmanCodes = 1,
  DynamicHuffmanCodes = 2,
} ;

// These values define the Adam7 interlace pattern for each pass.
const PngDecoder::InterlaceInfo PngDecoder::interlace_values [InterlacePasses] =
  {
    { 8, 8, 0, 0, },
    { 8, 8, 0, 4, },
    { 8, 4, 4, 0, },
    { 4, 4, 0, 2, },
    { 4, 2, 2, 0, },
    { 2, 2, 0, 1, },
    { 2, 1, 1, 0, },
  } ;

//
// Class Constructor
//
// Nothing gets done here except initializing variables to a known state.
//
PngDecoder::PngDecoder ()
{
  Initialize () ;
  return ;
}
//
//  Copy Constructor
//
PngDecoder::PngDecoder (const PngDecoder &source)
{
  Initialize () ;
  DoCopy (source) ;
  return ;
}

//
// Class Destructor
//
PngDecoder::~PngDecoder ()
{
  FreeData () ;
  delete distance_table ;
  delete literal_table ;
  return ;
}

//
//  Description:
//
//    Assignment Operator
//
PngDecoder &PngDecoder::operator=(PngDecoder &source)
{
  DoCopy (source) ;
  return *this ;
}

//
//  Description:
//
//    Object initialization Function for use by constructors.
//
void PngDecoder::Initialize ()
{
  input_stream = NULL ;
  current_image = NULL ;
  row_buffers [0] = NULL ;
  row_buffers [1] = NULL ;
  MakeCrcTable () ;

  background_red = 0 ;
  background_green = 0 ;
  background_blue = 0 ;
  background_gray = 0 ;

  chunk_data = NULL ;
  chunk_data_size = 0 ;
  lz_window = NULL ;
//  verbose_flag = false ;

  literal_table = new PngHuffmanDecoder ;
  distance_table = new PngHuffmanDecoder ;
  return ;
}

//
//  Description:
//
//    Class copy function. Used by copy constructor and assignment operator
//    to copy data from an object to this one.
//
//  Parameters:
//    source:  The object to copy from.
//
void PngDecoder::DoCopy (const PngDecoder &source)
{
//  verbose_flag = source.verbose_flag ;
  background_red = source.background_red ;
  background_green = source.background_green ;
  background_blue = source.background_blue;
  background_gray = source.background_blue;
  BitmapImageDecoder::DoCopy (source) ;
  return ;
}
//
// Description:
//
//   This function frees all of the dynamically allocated data.
//
void PngDecoder::FreeData ()
{
  delete [] chunk_data ; chunk_data = NULL ;
  delete [] lz_window ; lz_window = NULL ;
  delete [] row_buffers [0] ; row_buffers [0] = NULL ;
  delete [] row_buffers [1] ; row_buffers [1] = NULL ;
  return ;
}

//
//  Description:
//
//    This function reads a PNG image.
//
//  Parameters:
//    strm:  The input stream
//    image:  The output image
//
void PngDecoder::ReadImage (inputStream &strm, BitmapImage &image)
{
  try
  {
    input_stream = &strm ;
    current_image = &image ;

    reading_pixel_data = false ;
    data_read = false ;
    header_read = false ;
    end_read = false ;
    palette_read = false ;

    palette_size = 0 ;

    lz_window = new UBYTE1 [PngWindowSize] ;
    memset (lz_window, 0, PngWindowSize) ;
    ReadSignature () ;

    ReadChunk () ;
    if (chunk_type != ChunkType ("IHDR"))
      throw EPngError ("Missing IHDR block") ;

    while (! input_stream->eof () && ! end_read)
    {
      ReadChunk () ;
    }

    FreeData () ;
  }
  catch (...)
  {
    FreeData () ;
    throw ;
  }

  if (! data_read)
    throw EPngError ("Image Contains no Pixel Data") ;
  return ;
}


//
// Description:
//
//  This function reads the PNG signature from the input stream. It
//  throws an exception if the stream does not have a valid signature.
//
void PngDecoder::ReadSignature ()
{
  UBYTE1 sigbuf [PngSignatureSize] ;

  input_stream->read ((char *) sigbuf, PngSignatureSize) ;
  if (memcmp (sigbuf, PngSignature, PngSignatureSize) != 0)
    throw EPngError ("Not a PNG file") ;
  return ;
}

//
//  Description:
//
//    This function reads a complete chunk from the input stream. A chunk
//    consists of:
//
//      Chunk Length:  4 Bytes
//      Chunk Type:    4 Bytes
//      Chunk Data:    "Chunk Length" Bytes
//      Chunk CRC:     4 Bytes
//
//    The chunk CRC value is calculated from the type and data fields.
//
//
void PngDecoder::ReadChunk ()
{
  // Read the chunk length.
  input_stream->read ((char *) &chunk_length, sizeof (chunk_length)) ;
  if (input_stream->eof ())
    return ;
  chunk_length = BigEndianToSystem (chunk_length) ;
  // Enforce the maximum chunk lenth specified in 3.2
  if (chunk_length > (UBYTE4) (1L << 31L) - 1L)
    throw EPngError ("Block length too large") ;

  // Read the chunk type.
  input_stream->read ((char *) &chunk_type, sizeof (chunk_type)) ;

  // Ensure that the data buffer is large enough to hold the chunk data
  // then read in the data.
  if (chunk_length > chunk_data_size)
  {
    delete [] chunk_data ;
    chunk_data = new UBYTE1 [chunk_length] ;
  }
  input_stream->read ((char *) chunk_data, chunk_length) ;

  // Read the CRC value.
  input_stream->read ((char *) &chunk_crc, sizeof (chunk_crc)) ;
  chunk_crc = BigEndianToSystem (chunk_crc) ;

  // At this point the entire chunk has been read.

  // Calculate the CRC value from the data.
  UBYTE4 crcvalue = 0xFFFFFFFFL ;
  crcvalue = CRC32 (crcvalue, &chunk_type, sizeof (chunk_type)) ;
  crcvalue = CRC32 (crcvalue, chunk_data, chunk_length) ;
  crcvalue ^= 0xFFFFFFFFL ;
  // The CRC is checked below to ensure that the data gets printed
  // if verbose_flag is set.

/*
  if (verbose_flag)
  {
    char type [5] = { 0, 0, 0, 0, 0, } ;
    memcpy (type, &chunk_type, sizeof (chunk_type)) ;
    cout << "{" << endl ;
    cout << " Block Type: " << type << endl ;
    cout << " Length: " << chunk_length << endl ;
    cout << " Block CRC: " << hex << chunk_crc << dec << endl ;
    cout << " Calculated CRC: " << hex << crcvalue << dec << endl ;
  }
*/

  //  Ensure that the CRC value in the data stream is the same is that CRC
  //  value calculated from the data. We do this after dumping the block.

  if (crcvalue != chunk_crc)
    throw EPngError ("Invalid CRC") ;

  // Here we process the data within the block. We handle a special case
  // here. Section 4.1.3 specifies that all IDAT chunks must be consecutive
  // with no intervening chunks.
  if (reading_pixel_data)
  {
    // The previous chunk was an IDAT chunk and we have not read all the
    // the pixel data. The only chunk permitted at this point is another
    // IDAT block.
    if (chunk_type != ChunkType ("IDAT"))
      throw EPngError ("IDAT Block Expected") ;

    ProcessData () ;
  }
  else
  {
    if (chunk_type == ChunkType ("IHDR")) ProcessHeader () ;
    else if (chunk_type == ChunkType ("IDAT")) ReadPixelData () ;
    else if (chunk_type == ChunkType ("PLTE")) ProcessPalette () ;
    else if (chunk_type == ChunkType ("IEND")) end_read = true ;
    else if (chunk_type == ChunkType ("bKGD")) ProcessBackground () ;
    else if (chunk_type == ChunkType ("gAMA")) ProcessGamma () ;
    else if (chunk_type == ChunkType ("cHRM")) ProcessChromaticities () ;
    else if (chunk_type == ChunkType ("hIST")) ProcessHistogram () ;
    else if (chunk_type == ChunkType ("sBIT")) ProcessSignificantBits () ;
    else if (chunk_type == ChunkType ("tRNS")) ProcessTransparency () ;
    else if (chunk_type == ChunkType ("pHYs")) ProcessPhysicalPixelDimensions () ;
    else if (chunk_type == ChunkType ("tIME")) ProcessImageTime () ;
    else if (chunk_type == ChunkType ("tEXt")) ProcessTextualData () ;
    else if (chunk_type == ChunkType ("zTXt")) ProcessCompressedText () ;
    else if ((chunk_type & (1 << 5)) == 0) 
      throw EPngError ("Unknown critical chunk") ;
  }

//  if (verbose_flag)
//    cout << "}" << endl ;
  return ;
}

//
// Description:
//
//   This function processes an IHDR chuck. This chunk contians the image
//   header which defines the dimensions and color type.
//
//   The main functions here are to allocate space in the image object and
//   to create the color table for grayscale images.
//
#pragma warning (disable : 4018)
void PngDecoder::ProcessHeader ()
{
  if (header_read)
    throw EPngError ("Duplicate IHDR Block") ;
  header_read = true ;

  if (chunk_length != sizeof (PngImageHeader))
    throw EPngError ("Invalid Header Length") ;

  // Save the data from the image header.
  PngImageHeader *header = (PngImageHeader *) chunk_data ;
  image_height = BigEndianToSystem (header->height) ;
  image_width = BigEndianToSystem (header->width) ;
  image_depth = header->bitdepth ;
  image_color_type = (PngColorType) header->colortype ;
  image_compression_method = header->compressionmethod ;
  image_filter_method = header->filtermethod ;
  image_interlace_method = header->interlacemethod ;

/*
  if (verbose_flag)
  {
    cout << " Image Dimensions: " << image_height << " x "
         << image_width << endl ;
    cout << " Bit Depth: " << (int) image_depth << endl ;
    cout << " Color Type: (" << (int) image_color_type << ") " ;
    switch (image_color_type)
    {
    case Grayscale: cout << "grayscale" << endl ; break ;
    case RGB: cout << "RGB" << endl ; break ;
    case Palette: cout << "palette" << endl ; break ;
    case GrayscaleAlpha: cout << "grayscale/alpha" << endl ; break ;
    case RGBAlpha: cout << "RGB/alpha" << endl ; break ;
    default: cout << "invalid" << endl ; break ;
    }
    cout << " Compression Method: " << (int) image_compression_method << endl ;
    cout << " Filter Method: " << (int) image_filter_method << endl ;
    cout << " Interlace Method: (" << (int) image_interlace_method << ") " ;
    switch (image_interlace_method)
    {
    case 0: cout << "none" << endl ; break ;
    case 1: cout << "Adam7" << endl ; break ;
    default: cout << "unknown" << endl ; break ;
    }
  }
*/

  // Ensure the that the values in the image header are valid.
  if (image_compression_method != 0)
    throw EPngError ("Invalid Compression Method") ;

  if (image_filter_method != 0)
    throw EPngError ("Invalid Filter Method") ;

  if (image_interlace_method != 0 && image_interlace_method != 1)
    throw EPngError ("Invalid Compression Method") ;
  switch (image_depth)
  {
  case 1: case 2: case 4: case 8: case 16: break ;
  default: throw EPngError ("Invalid Bit Depth") ;
  }

  // Ensure that the color type and bit depth values are consistent.
  switch (image_color_type)
  {
  case Grayscale: break ; // All bit depths are legal for grayscale.
  case RGB: case RGBAlpha: case GrayscaleAlpha:
    if (image_depth != 8 && image_depth != 16)
      throw EPngError ("Invalid Bit Depth for Color Type") ;
    break ;
  case Palette:
    if (image_depth == 16)
      throw EPngError ("Invalid Bit Depth for Color Type") ;
    break ;
  default: throw EPngError ("Invalid Color Type") ;
  }

  // Allocate space space in the image object.
  if (image_color_type == RGB || image_color_type == RGBAlpha)
  {
    current_image->SetSize (0, 24, image_width, image_height) ;
  }
  else
  {
    // For an interlaced image use a full byte to represent each pixel to
    // simplify decoding. We do the same for 2-bit images since the
    // BitmapImage class does not support 2-bit images.
    if (image_interlace_method != 0 || image_depth == 2)
    {
      if (image_depth <= 8)
      {
        current_image->SetSize (1<<image_depth,
                                8,
                                image_width,
                                image_height) ;
      }
      else
      {
        current_image->SetSize (256,
                                8,
                                image_width,
                                image_height) ;
      }
    }
    else if (image_depth == 16)
    {
      current_image->SetSize (256,
                              8,
                              image_width,
                              image_height) ;
    }
    else
    {
      // Here we handle 1,4, and 8-bit palette and grayscale im
      current_image->SetSize (1<<image_depth,
                              image_depth,
                              image_width,
                              image_height) ;
    }

    // For grayscale images we need to create a colormap.
    if (image_color_type == Grayscale || image_color_type == GrayscaleAlpha)
    {
      switch (image_depth)
      {
      case 1: case 2: case 4:
        {
          for (unsigned int ii = 0 ; ii < (1<<image_depth) ; ++ ii)
          {
            UBYTE1 value = (ii * Max8BitSampleValue + (1<<image_depth) - 2)
                           / ((1<<image_depth) - 1) ;
            current_image->ColorMap (0).red = value ;
            current_image->ColorMap (0).green = value ;
            current_image->ColorMap (0).blue = value ;
          }
        }
        break ;
      case 8: case 16:
        {
          for (unsigned int ii = 0 ; ii <= Max8BitSampleValue ; ++ ii)
          {
            current_image->ColorMap (ii).red = ii ;
            current_image->ColorMap (ii).green = ii ;
            current_image->ColorMap (ii).blue = ii ;
          }
        }
        break ;
      default:
        throw EPngError ("Bad Bit Depth") ;
      }
    }
  }
  return ;
}

//
//  Description:
//
//    This function processes the data in a PLTE block. A PLTE block
//    defines the color palette for the image.
//
void PngDecoder::ProcessPalette ()
{
  // There can only be one palette for the image.
  if (palette_read)
    throw EPngError ("Duplicate PLTE block") ;
  palette_read = true ;

  // Grayscale images are not allowed to have an palette.
  if (image_color_type == Grayscale || image_color_type == GrayscaleAlpha)
    throw EPngError ("Grayscale image contains a PLTE block") ;

  // The palette size must be divisable by 3.
  if (chunk_length % 3 != 0)
    throw EPngError ("PLTE chunk length not divisible by 3") ;
  if (chunk_length > 3 * 256)
    throw EPngError ("PLTE chunk length too large") ;

  palette_size = chunk_length / 3 ;

  // PLTE chunks are permitted with RGB images to suggest colors
  // for quantization.  Our implementation does not do anything
  // with this information.
  if (image_color_type == RGB || image_color_type == RGBAlpha)
    return ;

  // Store the palette in the image.
  for (unsigned int ii = 0, jj = 0 ; ii < chunk_length / 3 ; ++ ii, jj += 3)
  {
    current_image->ColorMap (ii).red = chunk_data [jj] ;
    current_image->ColorMap (ii).green = chunk_data [jj+1] ;
    current_image->ColorMap (ii).blue = chunk_data [jj+2] ;
  }

  return ;
}

//
//  Description:
//
//    This function performs the processing for an IDAT chunk that is not
//    the first chuck in the IDAT block sequence.
//
//    The only processing here is to reset the data pointers.
//
void PngDecoder::ProcessData ()
{
  byte_offset = 0 ;
  bit_offset = CHAR_BIT ;
  return ;
}

//
//  Description:
//
//    This function returns the next uncompressed data byte within the IDAT
//    block data stream. The value returned is either the next byte in the
//    current IDAT block or the first byte in the next IDAT block in the
//    input stream.
//
UBYTE1 PngDecoder::GetIDATByte ()
{
  UBYTE1 value ;
  // See if there are any more bytes in this IDAT block.
  if (byte_offset >= chunk_length)
  {
    // We have consumed the current IDAT block. Advance to the next
    // IDAT block with data. It is possible to have a zero length IDAT
    // block.
    do
    {
      ReadChunk () ;
      if (input_stream->eof ())
        throw EPngError ("Premature End-Of-File") ;
    }
    while (byte_offset >= chunk_length) ;

  }
  value = chunk_data [byte_offset] ;
  ++ byte_offset ;
  bit_offset = CHAR_BIT ;
  return value ;
}

//
//  Description:
//
//    This function returns a number of uncompressed bits from the
//    IDAT block data stream.
//
//  Parameters:
//    count:  The number of bits to return.
//
int PngDecoder::GetBits (unsigned int count)
{
  unsigned int value = 0 ;
  for (unsigned int ii = 0 ; ii < count ; ++ ii)
  {
    // See if we have consumed all the bits in the current byte.
    if (bit_offset >= CHAR_BIT)
    {
      // Move to the next byte and see if we have used up all the data
      // in the current IDAT block.
      bit_buffer = GetIDATByte () ;
      bit_offset = 0 ;
    }
    if ((bit_buffer & (1<<bit_offset)) != 0)
      value |= (1<<ii) ;
    ++ bit_offset ;
  }
  return value ;
}

//
//  Description:
//
//    This function reads Huffman-encoded code lengths for another
//    Huffman table. The Huffman encoded values range from 0..18.
//    The values have the following meanings:
//
//      0..15=>A literal length value
//      16=>Repeat the last code N times. N is found by reading
//          the next 2 bits and adding 3.
//      17=>Set the N length codes to zero. N is found by reading the
//          next 3 bits and adding 3.
//      18=>Set the N length codes to zero. N is found by reading the
//          next 7 bits and adding 11.
//
//  Parameters:
//    ht:  The Huffman table used to decode the input stream.
//    lengths: The output length values
//    lengthcount:  The number of length values to read.
//
//
void PngDecoder::ReadLengths (PngHuffmanDecoder &ht,
                              unsigned int lengths [],
                              unsigned int lengthcount)
{
  for (unsigned int index = 0 ; index < lengthcount ;)
  {
    int command = ht.Decode (*this) ;
    if (command < 16)
    {
#if defined (VERYVERBOSE)
//      if (verbose_flag)
//        cout << index << " Literal: " << command << endl ;
#endif
      // Raw Length
      lengths [index] = command ;
      ++ index ;
    }
    else if (command == 16)
    {
      // Repeat previous
      int count = GetBits (2) + 3 ;
#if defined (VERYVERBOSE)
//      if (verbose_flag)
//        cout << index << " Repeat: " << count << endl ;
#endif
      for (unsigned int ii = 0 ; ii < count ; ++ ii)
      {
        if (index == lengthcount)
          throw EPngError ("Length Command Out of Range") ;
        lengths [index] = lengths [index - 1] ;
        ++ index ;
      }
    }
    else if (command == 17)
    {
      // Run of zeros
      int count = GetBits (3) + 3 ;
#if defined (VERYVERBOSE)
//      if (verbose_flag)
//        cout << index << " Zero Run: " << count << endl ;
#endif
      for (unsigned int ii = 0 ; ii < count ; ++ ii)
      {
        if (index == lengthcount)
          throw EPngError ("Length Command Out of Range") ;
        lengths [index] = 0 ;
        ++ index ;
      }
    }
    else if (command == 18)
    {
      // Longer run of zeros
      int count = GetBits (7) + 11 ;
#if defined (VERYVERBOSE)
//      if (verbose_flag)
//        cout << index << " Zero Run: " << count << endl ;
#endif
      for (unsigned int ii = 0 ; ii < count ; ++ ii)
      {
        if (index == lengthcount)
          throw EPngError ("Length Command Out of Range") ;
        lengths [index] = 0 ;
        ++ index ;
      }
    }
    else
    {
       throw EPngError ("Bad Code") ;
    }
  }
  return ;
}

//
//  Description:
//
//    This function returns the next byte in an uncompressed data set.
//
UBYTE1 PngDecoder::DecodeLiteralByte ()
{
  if (literal_count == 0)
  {
    if (final_data_set)
    {
      throw EPngError ("Premature End-Of-File") ;
    }
    else
    {
      StartNewDataSet () ;
      return DecodeByte () ;
    }
  }
  else
  {
     -- literal_count ;
     UBYTE1 value = GetIDATByte () ;
     stream_adler = Adler (stream_adler, value) ;
     return value ;
  }
  DUMMY_RETURN ; // MSVC++ is not smart enough to tell we can't get here.
}

//
//  Description:
//
//    This function decodes the next value in the input stream. The stream
//    format is:
//
//      huffman encoded length/literal value.
//           This value can be:  A data byte (0..255)
//           End Marker: 256
//           Length Code: 257..285
//
//      If the code is a length code then it is followed by 0..13 additional
//      literal bytes. This is followed by a huffman encodered distance value
//      with is followed by 0..13 literal bits.
//
//    This function assumes that it is only called when a data value is
//    in the compressed stream.
//

UBYTE1 PngDecoder::DecodeCompressedByte ()
{
  // See if we are still processing a copy operation.
  if (copy_count != 0)
  {
    // Copy the value in the LZ window.
    UBYTE1 value = lz_window [copy_position] ;
    lz_window [window_position] = value ;
    -- copy_count ;

    // Advance the copy and window positions.
    copy_position = (copy_position + 1) & 0x7FFF ;
    window_position = (window_position + 1) & 0x7FFF ;

    // Update the Adler checksum.
    stream_adler = Adler (stream_adler, value) ;
    return value ;
  }

  // The number of extra bits for code-257
  static const int length_extra [29] =
                     {
                       0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
                       1, 1, 2, 2, 2, 2, 3, 3, 3, 3,
                       4, 4, 4, 4, 5, 5, 5, 5, 0,
                     } ;
  // The smallest length value for code-257. The actual length value is
  // the sum of this value and the extra bits.
  static const int length_base [29] =
                     {
                       3,   4,   5,   6,   7,   8,   9,  10,  11,  13,
                      15,  17,  19,  23,  27,  31,  35,  43,  51,  59,
                      67,  83,  99, 115, 131, 163, 195, 227, 258
                     } ;
  // The number of extra bits for a distance code.
  static const int distance_extra [30] =
                     {
                      0,  0,  0,  0,  1,  1,  2,  2,  3,  3,
                      4,  4,  5,  5,  6,  6,  7,  7,  8,  8,
                      9,  9, 10, 10, 11, 11, 12, 12, 13, 13,
                     } ;
  // The smallest value for a distance code.
  static const int distance_base [30] =
                 {
                     1,    2,     3,     4,     5,
                     7,    9,    13,    17,    25,
                    33,   49,    65,    97,   129,
                   193,  257,   385,   513,   769,
                  1025, 1537,  2049,  3073,  4097,
                  6145, 8193, 12289, 16385, 24577,
                 } ;


  unsigned int value = literal_table->Decode (*this) ;
  unsigned int length ;
  unsigned int distance ;

  if (value < 256)
  {
    // This is a data value. Add the value to the LZ window and update the
    // Adler checksum.
    lz_window [window_position] = value ;

    window_position = (window_position + 1) & 0x7FFF ;
    stream_adler = Adler (stream_adler, value) ;
    return value ;
  }
  else if (value == 256)
  {
    // We just read the end marker. There should be another data set in the
    // input stream that contains the data value.
    if (final_data_set)
    {
      // The current data set end the final bit set. That means there should
      // be no more data sets in the stream.
      throw EPngError ("Premature End-Of-File") ;
    }
    else
    {
      // The data value is in the next data set.
      StartNewDataSet () ;
      return DecodeByte () ;
    }
  }
  else if (value < 286)
  {
    // The code specifies a length value. Read the extra bits
    // to find the actual length value.
    int extra = length_extra [value - 257] ;
    length = length_base [value - 257] ;
    if (extra != 0)
      length += GetBits (length_extra [value - 257]) ;

    // The length value is followed by the distance value. Decode the
    // value then add the extra bits to get the distance value.
    value = distance_table->Decode (*this) ;
    if (value > 29)
      throw EPngError ("Invalid Huffman Distance Value") ;

    extra = distance_extra [value] ;
    distance = distance_base [value] ;
    if (extra != 0)
      distance += GetBits (distance_extra [value]) ;

    // Set of the state variables that are used to find the following copied
    // bytes.
    copy_position = (PngWindowSize + window_position - distance) & 0x7FFF ;
    copy_count = length ;
    // Return the first copy byte.
    value = lz_window [copy_position] ;
    lz_window [window_position] = value ;

    copy_position = (copy_position + 1) & 0x7FFF ;
    window_position = (window_position + 1) & 0x7FFF ;
    -- copy_count ;
    stream_adler = Adler (stream_adler, value) ;
    return value ;
  }
  else
  {
    throw EPngError ("Invalid Huffman Literal Value") ;
  }
  DUMMY_RETURN ; // MSVC++ is not smart enough to tell that we can't get here.
}

//
//  Description:
//
//    This function returns the next encoded byte in the deflate stream.
//    All we do here is determine if we are in a literal or compressed
//    data set then calls a function to handle the appropriate type.
//
UBYTE1 PngDecoder::DecodeByte ()
{
  // Handle the easy case of a literal mode data stream. Compressed
  // data sets are handled below.
  if (literal_mode)
  {
    return DecodeLiteralByte () ;
  }
  else
  {
    return DecodeCompressedByte () ;
  }

}

//
//  Description:
//
//    This function processes the start of a new data set within a compressed
//    stream. The start of a data set has the following format:
//
//      final: 1-bit (1 => this is the last data set)
//      compression type:  2-bits
//      The remainder depends upon the compression type.
//
//      Compression Type:  Uncompressed
//
//        Advance to the next byte boundary. The next two bytes is the
//        length of the uncompressed data. The following two bytes
//        are the ones complement of the length.  [length] uncompressed
//        bytes follow.
//
//      Compression Type:  Fixed Huffman Codes
//
//        The huffman encoded data bits immediately follow the type field. The
//        data is encoded using the huffman lengh codes defined in the deflate
//        specification.
//
//      Compression Type: Dynamic Huffman Codes
//
//        The trick here is that the literal and distance Huffman
//        tables are Huffman-encoded. The next values in the input
//        stream are:
//
//          number of literal codes: 5-bits + 257
//          number of distance codes: 5-bits + 1
//          number of code lengths: 4-bits + 4
//
//          Code Lengths: 3-bits * (code-lengths + 4)
//
//        The code lengths are used to create a huffman table that encodes
//        the literal table followed by the length table.
//
void PngDecoder::StartNewDataSet ()
{
  if (GetBits (1) == 0)
    final_data_set = false ;
  else
    final_data_set = true ;

  CompressionType compressiontype = (CompressionType) GetBits (2) ;
/*
  if (verbose_flag)
  {
    cout << " Final: " << final_data_set << endl ;
    cout << " Type:  (" << compressiontype << ") " ;
    switch (compressiontype)
    {
    case 0: cout << "none" ; break ;
    case 1: cout << "Fixed Huffman Codes" ; break ;
    case 2: cout << "Dynamic Huffman Codes" ; break ;
    default: cout << "unknown" ; break ;
    }
    cout << endl ;
  }
*/

  if (compressiontype == Uncompressed)
  {
    literal_mode = true ;
    literal_count = GetIDATByte () | (GetIDATByte () << CHAR_BIT) ;
    UBYTE2 testcount = GetIDATByte () | (GetIDATByte () << CHAR_BIT) ;
    if ((literal_count & 0xFFFF) != (~testcount & 0xFFFF))
      throw EPngError ("Invalid Literal Count") ;
  }
  else if (compressiontype == FixedHuffmanCodes)
  {
    // These are the length values that define the
    // literal huffman table.
    static const unsigned int literals [288] =
      {
        8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 8,
        9, 9, 9, 9, 9, 9, 9, 9,
        9, 9, 9, 9, 9, 9, 9, 9,
        9, 9, 9, 9, 9, 9, 9, 9,
        9, 9, 9, 9, 9, 9, 9, 9,
        9, 9, 9, 9, 9, 9, 9, 9,
        9, 9, 9, 9, 9, 9, 9, 9,
        9, 9, 9, 9, 9, 9, 9, 9,
        9, 9, 9, 9, 9, 9, 9, 9,
        9, 9, 9, 9, 9, 9, 9, 9,
        9, 9, 9, 9, 9, 9, 9, 9,
        9, 9, 9, 9, 9, 9, 9, 9,
        9, 9, 9, 9, 9, 9, 9, 9,
        9, 9, 9, 9, 9, 9, 9, 9,
        9, 9, 9, 9, 9, 9, 9, 9,
        7, 7, 7, 7, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 7,
        8, 8, 8, 8, 8, 8, 8, 8,
      } ;
    // These length values define the distance huffman table.
    static const unsigned int distances [32] =
      {
        5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5,
      } ;
    literal_table->MakeTable (288, literals) ;
    distance_table->MakeTable (32, distances) ;
    literal_mode = false ;
  }
  else if (compressiontype == DynamicHuffmanCodes)
  {

    unsigned int HLIT = GetBits (5) ;
    unsigned int HDIST = GetBits (5) ;
    unsigned int HCLEN = GetBits (4) ;

/*
    if (verbose_flag)
    {
      cout << " Literal Code Count: " << (HLIT + 257)
           << " (" <<  HLIT << ")" << endl ;
      cout << " Distance Codes: " << (HDIST + 1)
           << " (" << HDIST << ") " << endl ;
      cout << " Code Length Codes: " << (HCLEN + 4)
           << " (" << HCLEN << ")" << endl ;
    }
*/

    // Read the length codes used to huffman encode the literal and
    // distance tables. The unusual thing here is the Huffman values
    // are not in the order 0..18 but rather the order defined by
    // the lengthindices array.
    if (HCLEN + 4 > PngLengthSize)
      throw EPngError ("Invalid Huffman Code Length") ;
    unsigned int lengths [PngLengthSize] ;
    memset (lengths, 0, sizeof (lengths)) ;
    for (unsigned int ii = 0 ; ii < HCLEN + 4 ; ++ ii)
    {
      lengths [PngLengthOrder [ii]] = GetBits (3) ;
    }
    PngHuffmanDecoder ht ;
    ht.MakeTable (PngLengthSize, lengths) ;

#if defined (VERYVERBOSE)
/*
    if (verbose_flag)
    {
      cout << "  Lengths " << endl ;
      for (unsigned int ii = 0 ; ii < HCLEN + 4 ; ++ ii)
        cout << (int) PngLengthOrder [ii] << ") " << lengths [PngLengthOrder [ii]] << endl ;
    }
*/
#endif
    // Using the Huffman table we just created read the length/literals
    // and distances Huffman tables.
    unsigned int literals [288] ;
    ReadLengths (ht, literals, HLIT + 257) ;
    unsigned int distances [32] ;
    ReadLengths (ht, distances, HDIST + 1) ;

    literal_table->MakeTable (HLIT + 257, literals) ;
    distance_table->MakeTable (HDIST + 1, distances) ;
    literal_mode = false ;
  }
  else
  {
    throw EPngError ("Invalid Compression Type") ;
  }
  return ;
}

//
//  Description:
//
//    This function is called after all the image data is read to check the
//    the Adler checksum.
//
void PngDecoder::CheckAdler ()
{
  if (! literal_mode)
  {
    // When we arrive here we should have read the last data byte. The next
    // code in the stream should be the end marker.
    unsigned int value = literal_table->Decode (*this) ;
    if (value != 256)
      throw EPngError ("Missing End Marker") ;
  }

  // After the end marker the next 4 bytes should be the adler checksum
  UBYTE4 streamvalue = (GetIDATByte () << (3*CHAR_BIT))
                     | (GetIDATByte () << (2*CHAR_BIT))
                     | (GetIDATByte () << CHAR_BIT)
                     | GetIDATByte () ;
/*
  if (verbose_flag)
  {
    cout << "  Stream Adler Checksum: "
         << hex << BigEndianToSystem (streamvalue) << endl ;
    cout << "  Calculated Checksum: " << BigEndianToSystem (stream_adler)
         << endl << dec ;
  }
*/
  if (streamvalue != stream_adler)
    throw EPngError ("Stream Adler 32 Checksum error") ;

  return ;
}

//
//  Description:
//
//    This function processes an IDAT data stream. It decompresses the
//    pixel data and stores it in the image.
//
//    The Deflate compression system supports many options that are not
//    permitted in PNG. This is the reason for checking for specific
//    parameter values.
//
void PngDecoder::ReadPixelData ()
{
  // Ensure that we only have one IDAT stream in an image stream.
  if (data_read)
    throw EPngError ("Image Contains Multiple Data Segments") ;
  data_read = true ;

  // If the image requires a palette then it must have been read by
  // the time we get here.
  if (image_color_type == Palette && ! palette_read)
    throw EPngError ("PLTE block must occur before IDAT") ;

  // This flag isused to ensure that the stream of IDAT chucks is not
  // interrupted by other block types.
  reading_pixel_data = true ;

  ProcessData () ;  // Common IDAT block processing.

  stream_adler = 1 ;  // Initialize the IDAT counter.

  // Initialize the LZ compression state variables.
  window_position = 0 ;
  copy_position = 0 ;
  copy_count = 0 ;

  // Read the copressed stream header.
  UBYTE1 data1 = GetIDATByte () ;
  int CM = (data1 & 0x0F) ; // Compression Method
  int CINFO = (data1 & 0xF0) >> 4 ;
  int windowsize = (1 << (CINFO + 8)) ;

  UBYTE1 data2 = GetIDATByte () ;
  bool FDICT = (data2 & (1 << 5)) != 0 ;
  int FLEVEL = (data2 & 0xC0) >> 6 ;
  // The header values are checked below after they have been printed out.

/*
  if (verbose_flag)
  {
    cout << " Compression Method: " << (int) CM << endl ;
    cout << " WindowSize: " << windowsize << endl ;
    cout << " Preset Dictionary: " ;
    if (FDICT != 0)
      cout << "true" << endl ;
    else
       cout << "false" << endl ;
    cout << " Compression Level: " << FLEVEL << endl ;
  }
*/

  // Make sure the header values are valid for PNG.
  if (CM != 8)
    throw EPngError ("Invalid Compression Method - Not (8) Deflate") ;

  if ((data2 | (data1 << 8)) % 31 != 0)
    throw EPngError ("Invalid IDAT flags") ;

  if (windowsize != (1 << 15))
    throw EPngError ("Invalid Compression Window") ;

  if (FDICT)
    throw EPngError ("Preset dictionary flag set") ;

  // Read the start of the new Deflate data set.
  StartNewDataSet () ;

  // This block determines the number of bytes needed to store each
  // data row of the image. Then allocate two buffers to hold row
  // data.  We need to row buffers to support filtering.
  unsigned int rowbits ; // The number of bits of data per row.
  switch (image_color_type)
  {
  case Grayscale: case Palette:
    rowbits = image_width * image_depth ;
    row_buffer_width = (rowbits + CHAR_BIT - 1) / CHAR_BIT ;
    break ;
  case GrayscaleAlpha:
    row_buffer_width = 2 * image_width * image_depth / CHAR_BIT ;
    break;
  case RGB:
    row_buffer_width = image_width * 3 * image_depth / CHAR_BIT ;
    break ;
  case RGBAlpha:
    row_buffer_width = image_width * 4 * image_depth / CHAR_BIT ;
    break ;
  default:
    throw EPngError ("Invalid Color Type") ;
  }
  row_buffers [0] = new UBYTE1 [row_buffer_width] ;
  row_buffers [1] = new UBYTE1 [row_buffer_width] ;

  // Read the image data.
  if (image_interlace_method == 0)
  {
    ReadNoninterlaced () ;
  }
  else
  {
    CallProgressFunction (0) ;
    for (interlace_pass = 0 ;
         interlace_pass < InterlacePasses ;
         ++ interlace_pass)
    {
      ReadInterlaced () ;
    }
    CallProgressFunction (100) ;
  }

  // Make sure that Adler checksum for the compressed data is correct.
  CheckAdler () ;

  reading_pixel_data = false ;
  return ;
}

//
//  Description:
//
//    This function filters a row of data.
//
//  Parameters:
//    filter:  The type of filter
//
void PngDecoder::FilterRow (unsigned int filter)
{
  int lastrow = ! current_row_buffer ; // Index of the previous row
  int col ;                            // Current Column
  int offset ;                         // Pixel width

  // Filtering is done on corresponding items within a record. Determine
  // the number of bytes between corresponding items.
  switch (image_color_type)
  {
  case Grayscale: case Palette:
    offset = 1 ;
    break ;
  case RGB:
    offset = 3 * image_depth / CHAR_BIT ;
    break ;
  case GrayscaleAlpha:
    offset = 2 * image_depth / CHAR_BIT ;
    break ;
  case RGBAlpha:
    offset = 4 * image_depth / CHAR_BIT ;
    break ;
  default:
    throw EPngError ("Invalid Color Type") ;
  }

  // Filter the row based upon the filter type.
  switch (filter)
  {
  case FilterNone:
    break ;

  case FilterSub:
    // The value is the difference from the value to the left.
    for (col = offset ; col < row_buffer_width ; ++ col)
    {
      row_buffers [current_row_buffer][col] =
           (row_buffers [current_row_buffer][col] +
            row_buffers [current_row_buffer][col-offset]) & 0xFF ;
    }
    break ;

  case FilterUp:
    // The value is the difference from the value in the previous row.
    for (col = 0 ; col < row_buffer_width ; ++ col)
    {
      row_buffers [current_row_buffer][col] =
           (row_buffers [current_row_buffer][col]
            + row_buffers [lastrow][col]) & 0xFF ;
    }
    break ;

  case FilterAverage:
    for (col = 0 ; col < row_buffer_width ; ++ col)
    {
      int left ;
      int above = row_buffers [lastrow][col] ;
      if (col < offset)
        left = 0 ;
      else
        left = row_buffers [current_row_buffer][col-offset] ;

      row_buffers [current_row_buffer][col] =
            (row_buffers [current_row_buffer][col]
             + (left + above) / 2) & 0xFF ;
    }
    break ;

  case FilterPaeth:
    for (col = 0 ; col < row_buffer_width ; ++ col)
    {
      UBYTE1 left, above, aboveleft ;
      above = row_buffers [lastrow][col] ;
      if (col < offset)
      {
        left = 0 ;
        aboveleft = 0 ;
      }
      else
      {
        left = row_buffers [current_row_buffer][col-offset] ;
        aboveleft = row_buffers [lastrow][col-offset] ;
      }
      int vv = (int) row_buffers [current_row_buffer][col] ;
      int pp = PaethPredictor (left, above, aboveleft) ;
      row_buffers [current_row_buffer][col] = (pp + vv) & 0xFF ;
    }
    break ;

  default:
    throw EPngError ("Invalid Filter Method") ;
  }
  return ;
}

//
//  Description:
//
//    This function copies the data from a non-interlaced row to the image.
//
//  Parameters:
//    row:  The output row number
//
void PngDecoder::CopyNoninterlacedRowToImage (unsigned int row)
{
  switch (image_color_type)
  {
  case Grayscale:
  case Palette:
    {
      switch (image_depth)
      {
      case 1: case 4: case 8:
        {
          for (unsigned int ii = 0 ; ii < row_buffer_width ; ++ ii)
            (*current_image)[row][ii] = row_buffers [current_row_buffer][ii] ;
        }
        break ;
      case 2:
        {
          for (unsigned int ii = 0 ; ii < image_width ; ++ ii)
          {
            int byteoffset = ii / 4 ;
            int bitoffset = ii % 4 ;

            int rawvalue = row_buffers [current_row_buffer][byteoffset] ;
            (*current_image) [row][ii]
               = (rawvalue >> 2 * (3 - bitoffset)) & 0x3 ;
          }
        }
        break ;
      case 16:
        {
          for (unsigned int ii = 0 ; ii < row_buffer_width ; ii += 2)
            (*current_image)[row][ii/2] = row_buffers [current_row_buffer][ii] ;
        }
        break ;
      default:
        throw EPngError ("Invalid Bit Depth") ;
      }
    }
    break ;
  case RGB:
    {
      for (unsigned int ii = 0, col = 0 ; ii < image_width ; ++ ii)
      {
        UBYTE1 red = row_buffers [current_row_buffer][col] ;
        col += image_depth/CHAR_BIT ;
        UBYTE1 green = row_buffers [current_row_buffer][col] ;
        col += image_depth/CHAR_BIT ;
        UBYTE1 blue = row_buffers [current_row_buffer][col] ;
        col += image_depth/CHAR_BIT ;

        (*current_image)[row][3*ii + BitmapImage::RedOffset] = red ;
        (*current_image)[row][3*ii + BitmapImage::GreenOffset] = green ;
        (*current_image)[row][3*ii + BitmapImage::BlueOffset] = blue ;
      }
    }
    break ;
  case GrayscaleAlpha:
    {
      // For 8-bit samples each sample interval is 2 bytes. For 16-bit
      // samples it is four bytes.
      unsigned int interval = 2 * image_depth / CHAR_BIT ;
      for (unsigned int ii = 0 ; ii < image_width ; ++ ii)
      {
        UBYTE1 alpha = row_buffers [current_row_buffer][interval * ii + 1] ;
        (*current_image)[row][ii]
          = (alpha * row_buffers [current_row_buffer][interval * ii]
             + (Max8BitSampleValue - alpha) * background_gray)
               / Max8BitSampleValue ;
      }
    }
    break ;
  case RGBAlpha:
    {
      for (unsigned int ii = 0, col = 0 ; ii < image_width ; ++ ii)
      {

        UBYTE1 inred = row_buffers [current_row_buffer][col] ;
        col += image_depth / CHAR_BIT ;
        UBYTE1 ingreen = row_buffers [current_row_buffer][col] ;
        col += image_depth / CHAR_BIT ;
        UBYTE1 inblue = row_buffers [current_row_buffer][col] ;
        col += image_depth / CHAR_BIT ;
        UBYTE1 alpha = row_buffers [current_row_buffer][col] ;
        col += image_depth / CHAR_BIT ;

        UBYTE1 outred = (alpha * inred
                         + (Max8BitSampleValue - alpha) * background_red)
                        / Max8BitSampleValue ;
        UBYTE1 outgreen = (alpha * ingreen
                           + (Max8BitSampleValue - alpha) * background_green)
                          / Max8BitSampleValue ;
        UBYTE1 outblue = (alpha * inblue
                          + (Max8BitSampleValue - alpha) * background_blue)
                         / Max8BitSampleValue ;
        (*current_image)[row][3*ii+BitmapImage::RedOffset] = outred ;
        (*current_image)[row][3*ii+BitmapImage::GreenOffset] = outgreen ;
        (*current_image)[row][3*ii+BitmapImage::BlueOffset] = outblue ;
      }
    }
    break ;
  default:
    throw EPngError ("Invalid Color Type") ;
  }
  return ;
}

//
//  Description:
//
//    This function reads the pixel data for a non-interlaced image.
//
void PngDecoder::ReadNoninterlaced ()
{
  // Initialize the input buffers.
  current_row_buffer = 0 ;
  memset (row_buffers [0], 0, row_buffer_width) ;
  memset (row_buffers [1], 0, row_buffer_width) ;

  CallProgressFunction (0) ;
  for (unsigned int row = 0 ; row < image_height ; ++ row)
  {
    PngFilterType filter = (PngFilterType) DecodeByte () ;
    for (unsigned int col = 0 ; col < row_buffer_width ; ++ col)
    {
      int value = DecodeByte () ;
      row_buffers [current_row_buffer][col] = value ;
    }

    FilterRow (filter) ;
    CopyNoninterlacedRowToImage (row) ;
    current_row_buffer = ! current_row_buffer ; // Switch buffers
    CallProgressFunction (100 * row / image_height) ;
  }
  CallProgressFunction (100) ;
  return ;
}

//
//  Description:
//
//    This function reads all the rows for an interlaced pass.
//
void PngDecoder::ReadInterlaced ()
{
  const InterlaceInfo *info = &interlace_values [interlace_pass] ;

  // If the image is too small we may not have to do any work this small.
  if (info->start_row >= image_height || info->start_col  >= image_width)
    return ;

  current_row_buffer = 0 ;
  memset (row_buffers [0], 0, row_buffer_width) ;
  memset (row_buffers [1], 0, row_buffer_width) ;

  unsigned int pixelsthisrow = (image_width - info->start_col
                                + info->col_interval - 1)
                               / info->col_interval ;
  unsigned int rowbytes ;
  switch (image_color_type)
  {
  case Grayscale: case Palette:
    rowbytes = (pixelsthisrow * image_depth + CHAR_BIT - 1) / CHAR_BIT ;
    break ;
  case RGB:
    rowbytes = pixelsthisrow * 3 * image_depth / CHAR_BIT ;
    break ;
  case RGBAlpha:
    rowbytes = pixelsthisrow * 4 * image_depth / CHAR_BIT ;
    break ;
  case GrayscaleAlpha:
    rowbytes = pixelsthisrow * 2 * image_depth / CHAR_BIT ;
    break ;
  default:
    throw EPngError ("Invalid Color Type") ;
  }

  for (unsigned int row = 0, destrow = info->start_row ;
       destrow < image_height ;
       ++ row, destrow += info->row_interval)
  {
    // The filter type precedes the row data.
    PngFilterType filter = (PngFilterType) DecodeByte () ;
    // Read the row data.
    for (unsigned int col = 0 ; col < rowbytes ; ++ col)
      row_buffers [current_row_buffer][col] = DecodeByte () ;

    // Filter the data
    FilterRow (filter) ;

    CopyInterlacedRowToImage (destrow, rowbytes) ;

    CallProgressFunction (100 * interlace_pass * destrow / image_height / 6) ;
    current_row_buffer = ! current_row_buffer ;  // Switch buffers
  }
  return ;
}

//
//  Description:
//
//    This function copies an interlaced row to the output image.
//
//  Parameters:
//    row: The output row number
//    rowwidth: The number of bytes of data in the row
//
void PngDecoder::CopyInterlacedRowToImage (unsigned int row,
                                           unsigned int rowwidth)
{
  const InterlaceInfo *info = &interlace_values [interlace_pass] ;

  switch (image_color_type)
  {
  case Grayscale: case Palette:
    switch (image_depth)
    {
    case 1:
      {
        for (unsigned int col = 0, destcol = info->start_col ;
             col < rowwidth ;
             ++ col)
        {
          for (int ii = CHAR_BIT - 1 ;
               ii >= 0 && destcol < image_width ;
               -- ii, destcol += info->col_interval)
          {
            UBYTE1 value = (row_buffers [current_row_buffer][col] >> ii) & 0x1 ;
            (*current_image)[row][destcol] = value ;
          }
        }
      }
      break ;
    case 2:
      {
        for (unsigned int col = 0, destcol = info->start_col ;
             col < rowwidth ;
             ++ col)
        {
          for (int ii = 3 * CHAR_BIT/4 ;
               ii >= 0 && destcol < image_width ;
               ii -= CHAR_BIT/4 , destcol += info->col_interval)
          {
            (*current_image)[row][destcol]
              = (row_buffers [current_row_buffer][col] >> ii) & 0x3 ;
          }
        }
      }
      break ;
    case 4:
      {
        for (unsigned int col = 0, destcol = info->start_col ;
             col < rowwidth ;
             ++ col)
        {
          for (int ii = CHAR_BIT/2 ;
               ii >= 0 && destcol < image_width ;
               ii -= CHAR_BIT/2, destcol += info->col_interval)
          {
            (*current_image)[row][destcol]
              = (row_buffers [current_row_buffer][col] >> ii) & 0xF ;
          }
        }
      }
      break ;
    case 8:
      {
        for (unsigned int col = 0, destcol = info->start_col ;
             col < rowwidth ;
             ++ col, destcol += info->col_interval)
        {
          (*current_image)[row][destcol]
            = row_buffers [current_row_buffer][col] ;
        }
      }
      break ;
    case 16:
      {
        for (unsigned int col = 0, destcol = info->start_col ;
             col < rowwidth ;
             col += 2, destcol += info->col_interval)
        {
          (*current_image)[row][destcol]
            = row_buffers [current_row_buffer][col] ;
        }
      }
      break ;
    default:
      throw EPngError ("Invalid Image Depth") ;
    }
    break ;
  case RGB:
    {
      for (unsigned int col = 0, destcol = 3 * info->start_col ;
           col < rowwidth ;
           destcol += 3 * info->col_interval)
      {
        UBYTE1 red = row_buffers [current_row_buffer][col] ;
        col += image_depth / CHAR_BIT ;
        UBYTE1 green = row_buffers [current_row_buffer][col] ;
        col += image_depth / CHAR_BIT ;
        UBYTE1 blue = row_buffers [current_row_buffer][col] ;
        col += image_depth / CHAR_BIT ;

        (*current_image)[row][destcol + BitmapImage::RedOffset] = red ;
        (*current_image)[row][destcol + BitmapImage::GreenOffset] = green ;
        (*current_image)[row][destcol + BitmapImage::BlueOffset] = blue ;
      }
    }
    break ;
  case RGBAlpha:
    {
      for (unsigned int col = 0, destcol = 3 * info->start_col ;
           col < rowwidth ;
           destcol += 3 * info->col_interval)
      {
        UBYTE1 inred = row_buffers [current_row_buffer][col] ;
        col += image_depth / CHAR_BIT ;
        UBYTE1 ingreen = row_buffers [current_row_buffer][col] ;
        col += image_depth / CHAR_BIT ;
        UBYTE1 inblue = row_buffers [current_row_buffer][col] ;
        col += image_depth / CHAR_BIT ;
        UBYTE1 alpha = row_buffers [current_row_buffer][col] ;
        col += image_depth / CHAR_BIT ;

        UBYTE1 outred = (alpha * inred
                         + (Max8BitSampleValue - alpha) * background_red)
                        / Max8BitSampleValue ;
        UBYTE1 outgreen = (alpha * ingreen
                           + (Max8BitSampleValue - alpha) * background_green)
                          / Max8BitSampleValue ;
        UBYTE1 outblue = (alpha * inblue
                          + (Max8BitSampleValue - alpha) * background_blue)
                         / Max8BitSampleValue ;

        (*current_image)[row][destcol + BitmapImage::RedOffset] = outred ;
        (*current_image)[row][destcol + BitmapImage::GreenOffset] = outgreen ;
        (*current_image)[row][destcol + BitmapImage::BlueOffset] = outblue ;
      }
    }
    break ;
  case GrayscaleAlpha:
    {
      for (unsigned int col = 0, destcol = info->start_col ;
           col < rowwidth ;
           destcol += info->col_interval)
      {
        UBYTE1 invalue = row_buffers [current_row_buffer][col] ;
        col += image_depth / CHAR_BIT ;
        UBYTE1 alpha = row_buffers [current_row_buffer][col] ;
        col += image_depth / CHAR_BIT ;

        UBYTE1 outvalue = (alpha * invalue
                           + (Max8BitSampleValue - alpha) * background_gray)
                          / Max8BitSampleValue ;
        (*current_image)[row][destcol] = outvalue ;
      }
    }
    break ;
  default:
    throw EPngError ("Invalid Color Type") ;
  }
  return ;
}

//
//  Description:
//
//    This function processes a bKGN chuck. This chunk defines the background
//    color for the image. We only use this for Alpha channel processing.
//
void PngDecoder::ProcessBackground ()
{
  UBYTE1 index ;

  switch (image_color_type)
  {
  case Grayscale: case GrayscaleAlpha:
    if (chunk_length == 0)
      throw EPngError ("bKGN Chunk too small") ;
    index = chunk_data [0] ;
    if (index >= (1<<image_depth))
      throw EPngError ("bKGN palette index too large") ;
    background_gray = index ;
/*
    if (verbose_flag)
    {
      cout << "Background Grayscale: " << background_gray << endl ;
    }
*/
    break ;

  case Palette:
    if (chunk_length == 0)
      throw EPngError ("bKGN Chunk too small") ;
    index = chunk_data [0] ;
    if (index >= (1<<image_depth))
      throw EPngError ("bKGN palette index too large") ;
    background_red = current_image->ColorMap (index).red ;
    background_green = current_image->ColorMap (index).green ;
    background_blue = current_image->ColorMap (index).blue ;
/*
    if (verbose_flag)
    {
      cout << "Background RGB: " << background_red << " "
           << background_green << background_blue << endl ;
    }
*/
    break ;

  case RGB: case RGBAlpha:
    if (chunk_length < 6)
      throw EPngError ("bKGN Chunk too small") ;
    background_red = chunk_data [0] ;
    background_green = chunk_data [2] ;
    background_blue = chunk_data [4] ;
/*
    if (verbose_flag)
    {
      cout << "Background RGB: " << background_red << " " << background_green
           << background_blue << endl ;
    }
*/
    break ;

  default:
    throw EPngError ("Invalid Color Type") ;
  }
  return ;
}

//
//  Description:
//    This function processes a gAMA chunk. The game value is stored
//    as a 4-byte integer which is the Gamma value times 100,000.
//
void PngDecoder::ProcessGamma ()
{
  if (palette_read)
    throw EPngError ("gAMA chunk may not occur before PLTE") ;
  if (data_read)
    throw EPngError ("gAMA chunk may not occur before IDAT") ;

  UBYTE4 value ;
  if (chunk_length < 4)
    throw EPngError ("gAMA chunk too small") ;
  value = chunk_data [0] | (chunk_data [1] << CHAR_BIT)
        | (chunk_data [2] << (2*CHAR_BIT))
        | (chunk_data [3] << (3*CHAR_BIT)) ;
  value = BigEndianToSystem (value) ;
  file_gamma = (double) value / 100000.0 ;
//  if (verbose_flag)
//    cout << " Gamma: " << file_gamma << endl ;
  return ;
}

//
//  Description:
//
//    This function processes a CHRM chunk. This chunk defines
//    precise color values for the image.
//
//    We do nothing with this chunk but dump its contents.
//
void PngDecoder::ProcessChromaticities ()
{
  if (palette_read)
    throw EPngError ("cHRM chunk may not occur after PLTE") ;
  if (data_read)
    throw EPngError ("cHRM chunk may not occur after IDAT") ;

  if (chunk_length != sizeof (PngChromaticitiesData))
    throw EPngError ("Invalid cHRM chunk length") ;

  PngChromaticitiesData *data = (PngChromaticitiesData *) chunk_data ;

  data->whitepointx = BigEndianToSystem (data->whitepointx) ;
  data->whitepointy = BigEndianToSystem (data->whitepointy) ;
  data->redx = BigEndianToSystem (data->redx) ;
  data->redy = BigEndianToSystem (data->redy) ;
  data->greenx = BigEndianToSystem (data->greenx) ;
  data->greeny = BigEndianToSystem (data->greeny) ;
  data->bluex = BigEndianToSystem (data->bluex) ;
  data->bluey = BigEndianToSystem (data->bluey) ;

/*
  cout << "  White Point X: " << (double) data->whitepointx / 100000.0
       << endl ;
  cout << "  White Point y: " << (double) data->whitepointx / 100000.0
       << endl ;
  cout << "  Red X: " << (double) data->redx / 100000.0 << endl ;
  cout << "  Red Y: " << (double) data->redy / 100000.0 << endl ;
  cout << "  Green X: " << (double) data->greenx / 100000.0 << endl ;
  cout << "  Green Y: " << (double) data->greenx / 100000.0 << endl ;
  cout << "  Blue X: " << (double) data->bluex / 100000.0 << endl ;
  cout << "  Blue Y: " << (double) data->bluex / 100000.0 << endl ;
*/

  return ;
}

//
//  Description:
//
//    Tais function processes an hIST chunk. This chunk defines the frequency
//    that each color in the palette is used within the imamge. This
//    information can be used to assist in quantization.
//
//    We do nothing with this chunk but dump its contents.
//
void PngDecoder::ProcessHistogram ()
{
  if (! palette_read)
    throw EPngError ("hIST chunk may not appear before PLTE") ;
  if (data_read)
    throw EPngError ("hIST chunk must appear before IDAT") ;

  if (chunk_length  != 2 * palette_size)
    throw ("Bad size for hIST chunk") ;

  UBYTE2 *values = (UBYTE2 *) chunk_data ;

/*
  if (verbose_flag)
  {
    for (unsigned int ii = 0 ; ii < palette_size ; ++ ii)
    {
      cout << "  " << ii << ") " << values [ii] << endl ;
    }
  }
*/

  return ;
}

//
//  Description:
//
//    This function processes the pHYs chunk. This chunk defines the
//    dimensions for the image pixels.
//
//    We do nothing with this chunk except print its contents.
//
void PngDecoder::ProcessPhysicalPixelDimensions ()
{
  if (data_read)
    throw EPngError ("pHYS chunk must come before IDAT chunks") ;

  if (chunk_length != sizeof (PngPixelDimensions))
    throw EPngError ("pHYs chunk size invalid") ;

  PngPixelDimensions *pd = (PngPixelDimensions *) chunk_data ;
  if (pd->unit > 1)
    throw EPngError ("pHYs contains an invalid unit") ;

  static const char *unitstrings [2] = { "unknown unit", "meter" } ;
/*
  if (verbose_flag)
  {
    cout << "  " << pd->pixelsx << " per " << unitstrings [pd->unit] << endl ;
    cout << "  " << pd->pixelsy << " per " << unitstrings [pd->unit] << endl ;
    cout << "  Unit: " << pd->unit << endl ;
  }
*/
  return ;
}

//
//  Description:
//
//    This function processes the sBIT chunk. This chunk can be used to
//    set the number of significant bits used in color values.
//
//    We do nothing with this chunk but print its contents.
//
void PngDecoder::ProcessSignificantBits ()
{
  if (data_read)
    throw EPngError ("sBIT chunk must occur before IDAT chunks") ;
  if (palette_read)
    throw EPngError ("sBIT chunk must occur before PTLE chunk") ;

  switch (image_color_type)
  {
  case Grayscale:
    {
      if (chunk_length < 1)
        throw EPngError ("sBIT chunk length invalid") ;

//      if (verbose_flag)
//        cout << "  Significant Bits: " << chunk_data [0] << endl ;
    }
    break ;
  case Palette: case RGB:
    {
      if (chunk_length < 3)
        throw EPngError ("sBIT chunk length invalid") ;

/*
      if (verbose_flag)
      {
        cout << " Significant Red Bits: " << chunk_data [0] << endl ;
        cout << " Significant Green Bits: " << chunk_data [1] << endl ;
        cout << " Significant Blue Bits: " << chunk_data [2] << endl ;
      }
*/
    }
    break ;
  case GrayscaleAlpha:
    {
      if (chunk_length < 2)
        throw EPngError ("sBIT chunk length invalid") ;

/*
      if (verbose_flag)
      {
        cout << " Significant Bits: " << chunk_data [0] << endl ;
        cout << " Significant Alpha Bits: " << chunk_data [1] << endl ;
      }
*/
    }
    break ;
  case RGBAlpha:
    {
      if (chunk_length < 4)
        throw EPngError ("sBIT chunk length invalid") ;

/*
      if (verbose_flag)
      {
        cout << " Significant Red Bits: " << chunk_data [0] << endl ;
        cout << " Significant Green Bits: " << chunk_data [1] << endl ;
        cout << " Significant Blue Bits: " << chunk_data [2] << endl ;
        cout << " Significant Alpha Bits: " << chunk_data [3] << endl ;
      }
*/
    }
    break ;
  default:
    throw EPngError ("Invalid Color Type") ;
  }
  return ;
}

//
//  Description:
//
//    This function processes the tEXt chunk. This chunk stores text
//    informationin the image.
//
//    We do nothing with the chunk except print its contents.
//
void PngDecoder::ProcessTextualData ()
{
  bool end_found = false ;
  unsigned int offset ;
  for (offset = 0 ;
       offset < chunk_length && offset < 80 ;
       ++ offset)
  {
    if (chunk_data [offset] == '\000')
    {
      end_found = true ;
      break ;
    }
  }
  if (! end_found)
    throw EPngError ("tEXt keyword not found") ;

/*
  if (verbose_flag)
  {
    cout << " Keyword: '" << chunk_data << "'" << endl ;
    cout << " Value: '" ;
    for (unsigned int ii = offset + 1 ; ii < chunk_length ; ++ ii)
      cout << chunk_data [ii] ;
    cout << "'" << endl ;
  }
*/
  return ;
}

//
//  Description:
//
//    This function processes the tIME chunk. This chunk stores the last time
//    the image was modified.
//
//    We do nothing with the chunk except print its contents.
//
void PngDecoder::ProcessImageTime ()
{
  if (chunk_length != sizeof (PngTimeData))
    throw EPngError ("tIME chunk size invalid") ;

/*
  if (verbose_flag)
  {
    PngTimeData *td = (PngTimeData *) chunk_data ;

    cout << "  Year: " << td->year << endl ;
    cout << "  Month: " << td->month << endl ;
    cout << "  Day: " << td->day << endl ;
    cout << "  Hour: " << td->hour << endl ;
    cout << "  Minute: " << td->minute << endl ;
    cout << "  Second: " << td->second << endl ;
  }
*/
  return ;
}

//
//  Description:
//
//    This function processes the tRNS chunk. This chunk allows transparency
//    to be define for color types without an alpha channel.
//
//    We do nothing with the chunk except print its contents.
//
void PngDecoder::ProcessTransparency ()
{
  if (data_read)
    throw EPngError ("tRNS chunk cannot occur before IDAT chunks") ;
  if (! palette_read)
    throw EPngError ("tRNS chunk must occur after PLTE chunk") ;

/*
  if (verbose_flag)
  {
    switch (image_color_type)
    {
    case Palette:
      {
        if (palette_size != chunk_length)
          throw EPngError ("tRNS block length invalid") ;

        for (unsigned int ii = 0 ; ii < chunk_length ; ++ ii)
          cout << ii << ") " << chunk_data [ii] << endl ;
      }
      break ;
    case Grayscale:
      {
        if (chunk_length < 2)
          throw EPngError ("tRNS chunk length invalid") ;
        UBYTE2 *value = (UBYTE2 *) chunk_data ;
        cout << "  Transparency: " << BigEndianToSystem (*value) << endl ;
      }
      break ;
    case RGB:
      {
        if (chunk_length < 6)
          throw EPngError ("tRNS chunk length invalid") ;
        UBYTE2 *value = (UBYTE2 *) chunk_data ;
        cout << "  Red Transparency: "
             << BigEndianToSystem (value [0]) << endl ;
        cout << "  Green Transparency: "
             << BigEndianToSystem (value [1]) << endl ;
        cout << "  Blue Transparency: "
             << BigEndianToSystem (value [2]) << endl ;
      }
      break ;
    default:
      throw EPngError ("Invalid Color Type of tRNS chunk") ;
    }
  }
*/
  return ;
}

//
//  Description:
//
//    This function processes the zTXt chunk. This chunk stores text
//     information.  This chunk is similar to a tEXt chunk except that the
//    data is compressed.
//
//    We do nothing with the chunk except print its contents.
//
void PngDecoder::ProcessCompressedText ()
{
  bool end_found = false ;
  unsigned int offset ;
  for (offset = 0 ;
       offset < chunk_length && offset < 80 ;
       ++ offset)
  {
    if (chunk_data [offset] != '\000')
    {
      end_found = true ;
      break ;
    }
  }
  if (! end_found)
    throw EPngError ("ZEXt keyword not found") ;

/*
  if (verbose_flag)
  {
    cout << "Keyword: '" << chunk_data << "'" << endl ;
    cout << "Compression Method: " << chunk_data [offset + 1] << endl ;
  }
*/
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
void PngDecoder::CallProgressFunction (unsigned int percent)
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

