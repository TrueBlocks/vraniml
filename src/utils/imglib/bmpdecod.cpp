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
// BMP Decoder Library.
//
// Title:   BmpDecoder Class Implementation
//
// Author: John M. Miano  miano@colosseumbuilders.com
//
//

#include <windows.h>

#include "bmpdecod.h"

//
//  Description:
//
//    Class default constructor
//

BmpDecoder::BmpDecoder ()
{
  return ;
}

//
//  Description:
//
//    Class Copy Constructor
//
BmpDecoder::BmpDecoder (const BmpDecoder &source)
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
BmpDecoder::~BmpDecoder ()
{
  return ;
}

//
//  Description:
//
//    Assignment operator.
//
//  Parameters:
//   source: The object to copy
//
BmpDecoder &BmpDecoder::operator=(const BmpDecoder &source)
{
  DoCopy (source) ;
  return *this ;
}

//
//  Description:
//
//    Common class initialization function for use by constructors.
//
void BmpDecoder::Initialize ()
{
  return ;
}

//
//  Description:
//
//    Common class copy function.
//
//  Parameters:
//    source:  The object to copy.
//
void BmpDecoder::DoCopy (const BmpDecoder &source)
{
  BitmapImageDecoder::DoCopy (source) ;
  return ;
}

//
//  Description:
//
//    This function reads an image from a Windows BMP stream.
//
//  Parameters:
//    strm: The input stream
//    image: The image to be read
//    
void BmpDecoder::ReadImage (inputStream &strm, BitmapImage &image)
{
  bool os2format ;

  // We need this because MSVC++ does not follow standard scoping
  // rules in for statements.
  unsigned int ii ;

  unsigned int bytesread = 0 ;

  BITMAPFILEHEADER fileheader ;
  strm.read ((char *) &fileheader, sizeof (fileheader)) ;
  if (strm.gcount () != sizeof(fileheader))
    throw EBmpFileReadError () ;
  bytesread += sizeof (fileheader) ;

  const UBYTE2 signature = 'B' | ('M' << 8) ;
  if (fileheader.bfType != signature)
    throw EBmpNotABmpFile () ;

  // The header can come in one of two flavors.  They both
  // begin with a DWORD headersize.

  DWORD headersize ;
  strm.read ((char *) &headersize, sizeof (headersize)) ;

  unsigned long width ;
  unsigned long height ;
  unsigned int bitcount ;
  unsigned int compression ;
  if (headersize == sizeof (BITMAPCOREHEADER))
  {
    // OS/2 Format Header

    BITMAPCOREHEADER header ;
    header.bcSize = headersize ;
    strm.read ((char *) &header.bcWidth,
          sizeof (header) - sizeof (headersize)) ;
    bytesread += sizeof (header) ;

    width = header.bcWidth ;
    height = header.bcHeight ;
    bitcount = header.bcBitCount ;

    compression = BI_RGB ;

    os2format = true ;
  }
  else if (headersize >= sizeof (BITMAPINFOHEADER))
  {
    BITMAPINFOHEADER header ;
    header.biSize = headersize ;
    strm.read ((char *) &header.biWidth,
           sizeof (header) - sizeof (headersize)) ;
    bytesread += sizeof (header) ;
    compression = header.biCompression ;

    width = header.biWidth ;
    height = header.biHeight ;
    bitcount = header.biBitCount ;

    for (unsigned int ii = 0 ;
         ii < headersize - sizeof (BITMAPINFOHEADER) ;
         ++ ii)
    {
      ++ bytesread ;
      UBYTE1 data ;
      strm.read ((char *) &data, 1) ;
    }
    os2format = false ;
  }
  else
  {
    throw EBmpCorruptFile () ;
  }

  // Calculate the number of colors and make sure that the
  // compression method is compatible.
  unsigned int colorcount ;
  switch (bitcount)
  {
  case 1:
    if (compression != BI_RGB)
      throw EBmpNotSupported () ;
    colorcount = 1 << bitcount ;
    break ;
  case 4:
    if (compression != BI_RGB && compression != BI_RLE4)
      throw EBmpNotSupported () ;
    colorcount = 1 << bitcount ;
    break ;
  case 8:
    if (compression != BI_RGB &&  compression != BI_RLE8)
      throw EBmpNotSupported () ;
    colorcount = 1 << bitcount ;
    break ;
  case 24:
    if (compression != BI_RGB)
      throw EBmpNotSupported () ;
    colorcount = 0 ;
    break ;
  default:
    throw EBmpNotSupported () ;
  }

  // Allocate storage for the image.
  image.SetSize (colorcount, bitcount, width, height) ;

  // Read the color map.
  if (os2format)
  {
    for (ii = 0 ; ii < colorcount ; ++ ii)
    {
      RGBTRIPLE color ;
      strm.read ((char *) &color, sizeof (color)) ;
      image.ColorMap (ii).red = color.rgbtRed ;
      image.ColorMap (ii).blue = color.rgbtBlue ;
      image.ColorMap (ii).green = color.rgbtGreen ;

      bytesread += sizeof (color) ;
    }
  }
  else
  {
    for (ii = 0 ; ii < colorcount ; ++ ii)
    {
      RGBQUAD color ;
      strm.read ((char *) &color, sizeof (color)) ;
      image.ColorMap (ii).red = color.rgbRed ;
      image.ColorMap (ii).blue = color.rgbBlue ;
      image.ColorMap (ii).green = color.rgbGreen ;

      bytesread += sizeof (color) ;
    }
  }

  // It is poss ible to have a file where the image data does not
  // immediately follow the color map (or headers). If there is
  // padding we skip over it.
  if (bytesread > fileheader.bfOffBits)
    throw EBmpCorruptFile () ;
  for (ii = bytesread ; ii < fileheader.bfOffBits ; ++ ii)
  {
    UBYTE1 data ;
    strm.read ((char *) &data, 1) ;
  }

  // Read the image data.
  CallProgressFunction (0) ;
  if (bitcount != 24)
  {
    // In this block we handle images that use a color map.

    if (compression == BI_RGB)
    {
      // Simplest case -- No compression. We can just read the
      // raw data from the file.

      // Number of bits required for each pixel row.
      unsigned int bitwidth = bitcount * width ;
      // Number of bytes need to store each pixel row.
      unsigned int rowwidth = (bitwidth + 7)/8 ;
      // Number of bytes used to store each row in the BMP file.
      // This is is rowwidth rounded up to the nearest 4 bytes.
      unsigned int physicalrowsize = (rowwidth + 0x3) & ~0x3 ;
      // The number of pad bytes for each row in the BMP file.
      unsigned int padsize = physicalrowsize -  rowwidth ;

      // Read in each row.
      for (unsigned int ii = 0 ; ii < height ; ++ ii)
      {
        CallProgressFunction (ii * 100 / height) ;

        // The pixel rows are stored in reverse order.
        unsigned int index = (height - ii - 1) ;
        strm.read ((char *)&image [index][0], rowwidth) ;
        if (strm.gcount () != rowwidth)
          throw EBmpFileReadError () ;

        // Skip over the pad bytes.
        static char pad [4] ;
        strm.read (pad, padsize) ;
      }
    } //
    else if (compression == BI_RLE8)
    {
      // Handle the case of 8-bit Run-Length Encoding.

      unsigned int row = height - 1 ;  // Current row
      unsigned int col = 0 ;           // Current column
      bool done = false ;
      while (! strm.eof () && ! done)
      {
        CallProgressFunction ((height - row - 1) * 100 / height) ;

        // Structure for reading RLE commands.
        struct
        {
          UBYTE1 count ;
          UBYTE1 command ;
        } opcode ;

        strm.read ((char *) &opcode, sizeof (opcode)) ;
        if (opcode.count == 0)
        {
          // A byte count of zero means that this is a special
          // instruction.
          switch (opcode.command)
          {
          case 0: // 0 => Move to next row
            -- row ;
            col = 0 ;
            break ;
          case 1: // 1 => Image is finished
            done = true ;
            break ;
          case 2: // 2 => Move to a new relative position.
            {
              // Read the relative position.
              UBYTE1 dx ;
              UBYTE1 dy ;
              strm.read ((char *) &dx, 1) ;
              strm.read ((char *) &dy, 1) ;
              col += dx ;
              row -= dy ;
            }
            break ;
          default:
            {
              // Store absolute data. The command code is the
              // number of absolute bytes to store.
              if (row >= height || col + opcode.command > width)
                  throw EBmpCorruptFile () ;
              UBYTE1 data ;
              for (unsigned int ii = 0 ; ii < opcode.command ; ++ ii)
              {
                strm.read ((char *) &data, 1) ;
                image [row][col] = data ;
                ++ col ;
              }
              // An odd number of bytes is followed by a pad byte.
              if ((opcode.command & 1) != 0)
                strm.read ((char *) &data, 1) ;
            }
            break ;
          }
        }
        else
        {
          // Store a run of the same color value.
          if (row >= height || col + opcode.count > width)
            throw EBmpCorruptFile () ;
          for (unsigned int ii = 0 ; ii < opcode.count ; ++ ii)
          {
            image [row][col] = opcode.command ;
            ++ col ;
          }
        }
      }
      if (! done)
        throw EBmpCorruptFile () ;
    }
    else if (compression == BI_RLE4)
    {
      // In this block we handle 4-bit Run-Length Encoded images.

      // The mechanism here is the same as for BI_RLE8 with two
      // exceptions. Here we are dealing with 4-bit nibbles rather
      // than whole bytes. This results in some extra work. In
      // addition, the coding of runs includes two color values.

      unsigned int row = height - 1 ;
      unsigned int col = 0 ;
      bool done = false ;
      while (! strm.eof () && ! done)
      {
        CallProgressFunction ((height - row - 1) * 100 / height) ;

        struct
        {
          UBYTE1 count ;
          UBYTE1 command ;
        } opcode ;

        strm.read ((char *) &opcode, sizeof (opcode)) ;
        if (opcode.count == 0)
        {
          switch (opcode.command)
          {
          case 0:    // Advance to next pixel row
            -- row ;
            col = 0 ;
            break ;
          case 1:    // Image complete
            done = true ;
            break ;
          case 2:   // Move to relative location the image.
            {
              UBYTE1 dx ;
              UBYTE1 dy ;
              strm.read ((char *) &dx, 1) ;
              strm.read ((char *) &dy, 1) ;
              col += dx ;
              row -= dy ;
            }
            break ;
          default:
            {
              UBYTE1 data ;
       		  UBYTE1 hi ;
              UBYTE1 lo ;
              if (row >= height || col + opcode.command > width)
                  throw EBmpCorruptFile () ;
              for (unsigned int ii = 0 ; ii < opcode.command ; ++ ii)
              {
                if ((ii & 1) == 0)
                {
                  strm.read ((char *) &data, 1) ;
                  lo = data & 0xF ;
                  hi = (data & 0xF0) >> 4 ;
                }
                if ((col & 1) == 0)
                {
                  if ((ii & 1) == 0)
                  {
                    image [row][col/2] = hi << 4 ;
                  }
                  else
                  {
                    image [row][col/2] = lo << 4 ;
                  }
                }
                else
                {
                  if ((ii & 1) == 0)
                  {
                   image [row][col/2] |= hi  ;
                  }
                  else
                  {
                    image [row][col/2] |= lo ;
                  }
                }
                ++ col ;
              }
              // If the number of bytes used in this instruction
              // is odd then there is a padding byte.
              switch (opcode.command & 0x3)
              {
              case 1: case 2:
                strm.read ((char *) &data, 1) ;
                break ;
              }
            }
            break ;
          }
        }
        else
        {
          // Process a run of the same color value pairs.
          UBYTE1 hi = opcode.command >> 4 ;
          UBYTE1 lo = opcode.command & 0xF ;
          if (row >= height || col + opcode.count > width)
            throw EBmpCorruptFile () ;

          for (unsigned int ii = 0 ; ii < opcode.count ; ++ ii)
          {
            if ((col & 1) == 0)
            {
              if ((ii & 1) == 0)
              {
                image [row][col/2] = hi << 4 ;
              }
              else
              {
                image [row][col/2] = lo << 4 ;
              }
            }
            else
            {
              if ((ii & 1) == 0)
              {
               image [row][col/2] |= hi  ;
              }
              else
              {
                image [row][col/2] |= lo ;
              }
            }
            ++ col ;
          }
        }
      }
      if (! done)
        throw EBmpCorruptFile () ;
    }
    else
    {
      // Invalid compression type
      throw EBmpCorruptFile () ;
    }
  }
  else
  {
//
// GREATHILLCHANGE
//
#if 0
    // Read the data for a 24-bit image.

    // Number of bytes used to store each pixel row in the
    // the file. This value is rounded up to the nearest
    // multiple of four.
    unsigned int physicalrowsize = (3 * width + 0x3) & ~0x3 ;
    // Size of the padding for each row.
    unsigned int padsize = physicalrowsize -  3 * width ;

    for (unsigned int yy = 0 ; yy < height ; ++ yy)
    {
      CallProgressFunction (yy * 100 / height) ;

      unsigned int index = height - yy - 1 ;
      // Have to read the sample values separately because the colors
      // are in reverse order: BGR. If you are on Windows you could
      // red the whole thing a row at a time.
      for (unsigned int xx = 0 ; xx < 3 * width ; xx += 3)
      {
        strm.read ((char *)&image[index][xx + BitmapImage::BlueOffset], 1) ;
        strm.read ((char *)&image[index][xx + BitmapImage::GreenOffset], 1) ;
        strm.read ((char *)&image[index][xx + BitmapImage::RedOffset], 1) ;
      }
      static char pad [4] ;
      strm.read (pad, padsize) ;
    }
#else
    //
    //
    // Great Hill: Changes made because Red and Blue were swapped.
    //
    //

    // Read the data for a 24-bit image.

    // Number of bytes need to store each pixel row.
    unsigned int rowwidth = 3 * width;

    // Number of bytes used to store each pixel row in the
    // the file. This value is rounded up to the nearest
    // multiple of four.
    unsigned int physicalrowsize = (rowwidth + 0x3) & ~0x3 ;

    // Size of the padding for each row.
    unsigned int padsize = physicalrowsize - rowwidth ;

    for (unsigned int yy = 0 ; yy < height ; ++ yy)
    {
      CallProgressFunction (yy * 100 / height) ;

      // The pixel rows are stored in reverse order.
      unsigned int index = (height - yy - 1) ;
      // Have to read the sample values separately because the colors
      // are in reverse order: BGR. If you are on Windows you could
      // red the whole thing a row at a time.
      for (unsigned int xx = 0 ; xx < rowwidth ; xx += 3)
      {
        strm.read ((char *)&image[index][xx + BitmapImage::RedOffset], 1) ;
        strm.read ((char *)&image[index][xx + BitmapImage::GreenOffset], 1) ;
        strm.read ((char *)&image[index][xx + BitmapImage::BlueOffset], 1) ;
      }
      static char pad [4] ;
      strm.read (pad, padsize) ;
    }
#endif
  }
  CallProgressFunction (100) ;
  return ;
}

//
//  Description:
//
//    This function is used to call the progres function.
//
//  Parameters:
//    percent:  The percent complete (0..100)
//
void BmpDecoder::CallProgressFunction (unsigned int percent)
{
  if (progress_function == NULL)
    return ;
  bool cancel = false ;
  progress_function (*this, progress_data, 1, 1, percent, cancel) ;
  if (cancel)
    throw EGraphicsAbort () ;
  return ;
}

