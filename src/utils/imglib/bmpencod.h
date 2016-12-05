#ifndef __BMBENCOD_H
#define __BMPENCOD_H

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
//  Title:  Windows Bitmap Encoder Class
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//

//#include <iostream>

#include "bitimage.h"
#include "bmp.h"

class BmpEncoder : public BitmapImageEncoder
{
public:
  BmpEncoder () ;
  BmpEncoder (const BmpEncoder &) ;
  virtual ~BmpEncoder () ;
  BmpEncoder &operator=(const BmpEncoder &) ;
  virtual void WriteImage (outputStream &, BitmapImage &) ;
private:
  void Initialize () ;
  void DoCopy (const BmpEncoder &) ;
  void CallProgressFunction (unsigned int) ;
} ;

#endif
