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
//  Title:  PNG Private Definitions
//
//  Author:  John M. Miano miano@colosseumbuilders.com
//
#include "pngpvt.h"

// PNG File Signature
extern const UBYTE1 PngSignature [PngSignatureSize] =
  {
    137, 80, 78, 71, 13, 10, 26, 10,
  } ;

// The order that length length codes are stored.
extern const UBYTE1 PngLengthOrder [PngLengthSize] =
  {
    16, 17, 18,  0,  8,
     7,  9,  6, 10,  5,
    11,  4, 12,  3, 13,
     2, 14,  1, 15,
  } ;
