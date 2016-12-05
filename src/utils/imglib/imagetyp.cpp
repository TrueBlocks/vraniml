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
//  Title:  Image Type Functions
//
//  Author:  John M. Miano miano@colosseumbuilders.com
//
//#include <stdlib.h>

#include <memory.h>

#include "imagetyp.h"

#include "jpegdeco.h"
#include "pngdecod.h"
//#include "gifdecod.h"
#include "bmpdecod.h"

//
//  Description:
//
//    This function determines the type of image stored in a stream.
//
//  Parameters:
//    strm:  The image stream
//
//  Return Value:
//    An enumeration that identifies the stream type
//
ImageType GetStreamImageType (inputStream &strm)
{
  long startpos = strm.tellg () ;
  
  ImageType result = UnknownImage ;

  char buffer [10] ;
  strm.read (buffer, sizeof (buffer)) ;
  if (strm.gcount () == sizeof (buffer))
  {
    if (memcmp (buffer, "GIF87a", 6) == 0)
    {
      result = GifImage ;
    }
    else if (memcmp (buffer, "GIF89a", 6) == 0)
    {
      result = GifImage ;
    }
    else if (memcmp (buffer, "\211PNG\r\n\032\n", 8) == 0)
    {
      result = PngImage ;
    }
    else if (memcmp (buffer, "\xFF\xD8\xFF\xE0", 4) == 0
             && memcmp (&buffer [6], "JFIF", 4) == 0)
    {
      result = JpegImage ;
    }
    else if (memcmp (buffer, "BM", 2) == 0)
    {
      result = BmpImage ;
    }
  }
  strm.seekg (startpos) ;

  return result ;
}

ImageType ReadImage (inputStream &strm,
                BitmapImage &image,
                PROGRESSFUNCTION function,
                void *data)
{
  ImageType type = GetStreamImageType (strm) ;
  if (type == UnknownImage)
    return type ;

  BmpDecoder bmpdecoder ;
//  GifDecoder gifdecoder ;
  JpegDecoder jpegdecoder ;
  PngDecoder pngdecoder ;
  BitmapImageDecoder *decoder ;
  switch (type)
  {
  case BmpImage:
    decoder = &bmpdecoder ;
    break ;
//  case GifImage:
//    decoder = &gifdecoder ;
//    break ;
  case PngImage:
    decoder = &pngdecoder ;
    break ;
  case JpegImage:
    decoder = &jpegdecoder ;
    break ;
  }

  decoder->SetProgressFunction (function, data) ;
  decoder->ReadImage (strm, image) ;
  return type ;
}
