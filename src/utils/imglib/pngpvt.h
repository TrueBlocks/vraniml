#ifndef __PNGPVT_H
#define __PNGPVT_H
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
//  Title:  PNG Encoder/Decoder private definitions
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//


//#include <string>

#include "datatype.h"

// Length of the PNG signature.
const int PngSignatureSize = 8 ;
extern const UBYTE1 PngSignature [PngSignatureSize] ;

const unsigned int PngLengthSize = 19 ;
extern const UBYTE1 PngLengthOrder [PngLengthSize] ;

const unsigned int PngMaxLengthCodes = 286 ;
const unsigned int PngMaxDistanceCodes = 30 ;
const unsigned int PngMaxNumberOfHuffmanCodes = PngMaxLengthCodes ;
const unsigned int PngFirstLengthCode = 257 ;
const unsigned int PngEndCode = 256 ;

// Maximum Huffman Code Sizes
const unsigned int PngMaxLengthLengthCodeSize = 7 ;
const unsigned int PngMaxDistanceCodeSize = 15 ;
const unsigned int PngMaxLengthCodeSize = 15 ;
enum PngColorType
{
  Grayscale = 0,
  RGB = 2,
  Palette = 3,
  GrayscaleAlpha = 4,
  RGBAlpha = 6,
} ;

  // Filter type defintiions
enum  PngFilterType
{
  FilterNone = 0,
  FilterSub = 1,
  FilterUp = 2,
  FilterAverage  = 3,
  FilterPaeth = 4,
} ;



// Physical layout of the IDAT header.
#pragma pack (1)
//#pragma option -a1
struct PngImageHeader
{
  UBYTE4 width ;
  UBYTE4 height ;
  UBYTE1 bitdepth ;
  UBYTE1 colortype ;
  UBYTE1 compressionmethod ;
  UBYTE1 filtermethod ;
  UBYTE1 interlacemethod ;
} ;
//#pragma option -a.

// Physical Layout of a cHRM chunk
//#pragma pack (1)
//#pragma option -a1
struct PngChromaticitiesData
{
  UBYTE4 whitepointx ;
  UBYTE4 whitepointy ;
  UBYTE4 redx ;
  UBYTE4 redy ;
  UBYTE4 greenx ;
  UBYTE4 greeny ;
  UBYTE4 bluex ;
  UBYTE4 bluey ;
} ;
//#pragma option -a.

// Physical layout of a pPYs chucnk
//#pragma pack (1)
//#pragma option -a1
struct PngPixelDimensions
{
  UBYTE4 pixelsx ;
  UBYTE4 pixelsy ;
  UBYTE1 unit ;
} ;
//#pragma option -a.

// Physical layout of a tIME chunk
//#pragma pack (1)
//#pragma option -a1
struct PngTimeData
{
  UBYTE2 year ;
  UBYTE1 month ;
  UBYTE1 day ;
  UBYTE1 hour ;
  UBYTE1 minute ;
  UBYTE1 second ;
} ;
//#pragma option -a.

#pragma pack (8)

const unsigned int PngWindowSize = (1 << 15) ;
const unsigned int PngWindowMask = PngWindowSize - 1 ;

const unsigned int PngLongestLength = 258 ;


static inline const char *Binary (int vv, int ll)
{
  static const char digit [2] = { '0', '1' } ;
  static char value [33] ;
  value [0] = '\000' ;
  for (unsigned int ii = ll , jj = 0 ; ii > 0 ; -- ii, ++ jj)
  {
    value [jj] = digit [(vv & (1 << (ii-1))) != 0 ] ;
    value [jj+1] = 0 ;
  }
  return value ;
}

//
//  Description:
//    Path predictor function defined in section 6.6 of the PNG standard.
//
//  Parameters:
//    left:  The pixel value for the value to the left of the current pixel.
//    above: The value for the pixel above the current pixel.
//    upperleft: The value for the pixel diagonally above and to the right
//                of the current pixel.
//
static inline unsigned int  PaethPredictor (UBYTE1 left,
                                            UBYTE1 above,
                                            UBYTE1 upperleft)
{
  int pp = left + above - upperleft ;
  int pa, pb, pc ;
  if (pp > left)
    pa = pp - left ;
  else
    pa = left - pp ;
  if (pp > above)
    pb = pp - above ;
  else
    pb = above - pp ;
  if (pp > upperleft)
    pc = pp - upperleft ;
  else
    pc = upperleft - pp ;

  if (pa <= pb && pa <= pc)
    return left ;
  else if (pb <= pc)
    return above ;
  else
    return upperleft ;
}


inline UBYTE4 ChunkType (const char type [5]) 
{
  UBYTE4 value = type [0] | (type [1] << 8) 
               | (type [2] << 16) | (type [3] << 24) ;
  return value ;
}

#endif
