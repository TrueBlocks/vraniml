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
// Title:  Windows Bitmap Coder
//
// Author: John M. Miano miano@colosseumbuilders.com
//

#include <windows.h>
//#include <iostream.h>
#include "bmpencod.h"

const UBYTE2 Signature = 'B'|('M'<<8) ;

//
//  Description:
//
//    Default class constructor
//
BmpEncoder::BmpEncoder ()
{
  Initialize () ;
  return ;
}

//
//  Description:
//
//    Class copy constructor
//
BmpEncoder::BmpEncoder (const BmpEncoder &source)
{
  Initialize () ;
  DoCopy (source) ;
  return ;
}

//
//  Descriptor:
//
//    Class destructor
//
BmpEncoder::~BmpEncoder ()
{
  return ;
}

//
//  Description:
//
//    Class assignment operator.
//
//  Parameters:
//    source:  The object to copy
//
BmpEncoder &BmpEncoder::operator=(const BmpEncoder &source)
{
  DoCopy (source) ;
  return *this ;
}

//
//  Description:
//
//    Common object initialization
//
void BmpEncoder::Initialize ()
{
  // For now, a NoOp.
  return ;
}

//
//  Description:
//
//    Common object copy function.
//
//  Parameters:
//    source:  The object to copy
//
void BmpEncoder::DoCopy (const BmpEncoder &source)
{
  BitmapImageEncoder::DoCopy (source) ;
  return ;
}

//
//  Description:
//
//    This function writes an image to a BMP stream.
//
//  Parameters:
//    strm:  The output stream
//    image:  The image to output
//
void BmpEncoder::WriteImage (outputStream &strm, BitmapImage &image)
{
  // We need this because MSVC++ does not follow standard scoping rules
  // in for statements
  unsigned int ii ;

  switch (image.BitCount ())
  {
  case 1: case 4: case 8: case 24:
    break ;
  default:
    throw EBmpNotSupported () ;
  }

  BITMAPFILEHEADER fileheader = {
          SystemToLittleEndian (Signature),
          0,
          0,
          0,
          0 } ;
  BITMAPINFOHEADER infoheader = {
          SystemToLittleEndian ((UBYTE4)sizeof (BITMAPINFOHEADER)),
          SystemToLittleEndian ((UBYTE4)image.Width ()),
          SystemToLittleEndian ((UBYTE4)image.Height ()),
          SystemToLittleEndian ((UBYTE2) 1), // Planes
          0,                // biBitCount
          SystemToLittleEndian ((UBYTE4) BI_RGB), // biCompression
          0,                // biXPelsPerMeter
          0,                // biYPelsPerMeter
          0,                // biClrUsed
          0,                // biClrImportant
          } ;
  unsigned int colorsize = sizeof (RGBQUAD)
                           * image.ColorCount () ;

  // Determine the amount of space required to store each
  // row of the image.
  unsigned int outputwidth ;
  if (image.BitCount () != 24)
  {
    unsigned int bitwidth = image.BitCount () * image.Width () ;
    outputwidth = (bitwidth + 7)/8 ;
  }
  else
  {
    outputwidth = sizeof (RGBTRIPLE) * image.Width () ;
  }

  // Find the amount of space required to pad the output rows to
  // a multiple of four bytes.
  unsigned int padsize = ((outputwidth + 0x3) & ~0x3) - outputwidth ;

  // Calulate the space required for the image.
  unsigned int datasize = image.Height () * (outputwidth + padsize) ;
  unsigned int spacerequired = sizeof (BITMAPFILEHEADER)
                             + sizeof (BITMAPINFOHEADER)
                             + colorsize + datasize ;

  // Fill in the remaining header fields.
  fileheader.bfOffBits = SystemToLittleEndian ((UBYTE4)sizeof (BITMAPFILEHEADER)
                         + sizeof (BITMAPINFOHEADER)
                         + colorsize) ;
  fileheader.bfSize = SystemToLittleEndian ((UBYTE4) spacerequired) ;
  infoheader.biBitCount = SystemToLittleEndian ((UBYTE2) image.BitCount ()) ;
  // Write the header.
  strm.write ((char *) &fileheader, sizeof (BITMAPFILEHEADER)) ;
  strm.write ((char *) &infoheader, sizeof (BITMAPINFOHEADER)) ;

  for (ii = 0 ; ii < image.ColorCount () ; ++ ii)
  {
    RGBQUAD data ;
    data.rgbRed = image.ColorMap (ii).red ;
    data.rgbGreen = image.ColorMap (ii).green ;
    data.rgbBlue = image.ColorMap (ii).blue ;
    data.rgbReserved = 0 ;
    strm.write ((char *) &data, sizeof (RGBQUAD)) ;
  }

  CallProgressFunction (0) ;
  if (image.BitCount () != 24)
  {
    for (ii = 0 ; ii < image.Height () ; ++ ii)
    {
      CallProgressFunction (ii * 100 /image.Height ()) ;
      static const char pad [4] = { 0, 0, 0, 0, } ;
      unsigned int index = image.Height () - ii - 1 ;
      strm.write ((char* ) &image [index][0], outputwidth) ;
      strm.write (pad, padsize) ;
    }
  }
  else
  {
    for (ii = 0 ; ii < image.Height () ; ++ ii)
    {
      CallProgressFunction (ii * 100 /image.Height ()) ;
      unsigned int index = image.Height () - ii - 1 ;
      for (unsigned int ii = 0 ; ii < 3 * image.Width () ; ii += 3)
      {
        // Remember BMP puts the colors in reverse order BGR.
        strm.write ((char *) &image [index][ii+BitmapImage::BlueOffset], 1) ;
        strm.write ((char *) &image [index][ii+BitmapImage::GreenOffset], 1) ;
        strm.write ((char *) &image [index][ii+BitmapImage::RedOffset], 1) ;
      }
      static const char pad [4] = { 0, 0, 0, 0, } ;
      strm.write (pad, padsize) ;
    }
  }
  CallProgressFunction (100) ;
  return ;
}

//
//  Description:
//
//    This function calls the progress function if it has been defined.
//
//  Parameters:
//    percent: The percent completed (0..100)
//    
void BmpEncoder::CallProgressFunction (unsigned int percent)
{
  if (progress_function == NULL)
    return ;
  bool cancel = false ;
  progress_function (*this, progress_data, 1, 1, percent, cancel) ;
  if (cancel)
    throw EGraphicsAbort () ;
  return ;
 }
