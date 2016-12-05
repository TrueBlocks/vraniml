Colosseum Builders C++ Image Library

Copyright 1997, 1998
All Rights Reserved

Legal:

THIS SOFTWARE IS PROVIDED AS IS. WE CAN'T TEST IT ON YOUR SYSTEM SO
USE AT YOUR OWN RISK. YOU HAVE THE SOURCE SO YOU HAVE NO EXCUSES.

Redistribution:

This software may be free redistributed as long as all copyright notices
remain unmodified and this file is included.

If you incorporate this software in another software package you should
acknowlege in your documentation that you used the Colosseum Builders C++
Image Library.

Licensing Fees:

o This software may be used without charge in software that is distributed
for free with the source code.

o This software may be used in shareware for a fee of $75. NJ customers
MUST include sales tax (6% = $4.50 as of 1-March-1998). Checks may be 
mailed to:

Colosseum Builders, Inc.
E101 103 Park Ave
Summit NJ 07901

o For other commercial use contact Colosseum Builders, Inc at
info@colosseumbuilders.com to discuss licensing terms.

o The GIF source code is provided for its educational value only and
may be freely distribed without fee to us. Due to patent issues use
GIF at your GIF at your own risk. GIF compression is patented by both
IBM and Unisys. If you want to incorporate GIF in your applications then
you may need to get licenses from IBM and/or Unisys. The only legal advice
we are giving is see your laywer before using GIF.

*************************************************************************
Release: 20 May 1998
Changes:
o Added XBM Format
o Bug Fixes to GIF, C++Builder
o GIF Decoder now uses LZ77 algorithm.

Release: 15 May 1998
Changes:

o Bug fixes to JPEG and PNG.

Release: 1 May 1998
Changes:

o Added a GIF encoder
o Added a PNG encoder
o Added a PNG decoder
o Added a C++Builder VCL Interface
o Made the files source compatible with MSVC++ (Except for GIF).
o Restructured the Source

Release: 2 March 1998
Changes:

o Added GIF Decoder
o 24 to 8 bit quantizer added to the BitmapImage class
o Added Progress Reporting for BMP files

Technical:

Due to the large number of requests for JPEG source code for C++Builder
I am making this source code available ahead of its time. Additions are
in the works as well as some documentation. 

Consider this an Alpha release.

At the heart of this library is the BitmapImage class which is used to 
represent a bitmap image class. It is intended to be as platform neutral
as possible while still being easy to use on Windows.

The VIEWER application shows how to display a BitmapImage object using the
Windows API.

Right now there are the the following Coders and Decoders:

BmpCoder - Windows BMP Coder
BmpDecoder - WIndows BMP Decoder
JpegCoder - JPEG Coder
JpegDecoder - JPEG Decoder
GifDecoder - GIF Decoder
GifEncoder - GIF Encoder 

All coders have a WriteImage method that writes a BitmapImage object to an I/O 
stream. All decoders have a ReadImage method that reads a BitmapImage object
from an I/O stream.

The basic usage is something like for a format conversion:

#include <fstream.h>
#include "xxxdecod.h"
#include "yyycoder.h"
...

ifstream in ("INPUT.XXX", ios::binary) ;
BitmapImage image ;

XXXDecoder decoder ;
decoder.ReadImage (in, image) ;
...
YYYCoder coder ;
ofstream out ("OUTPUT.YYY", iops::binary) ;
coder.WriteImage (out, image) ;

Be certain to open streams in BINARY mode.

Limitations:

The Windows Bitmap Coder/Decoder does not support compressed bitmaps.

The JPEG Coder/Decoder Supports:
o JFIF format
o Sequential and Progressive Huffman Frames

The JPEG Coder/Decoder does not support
o SPIFF format (who does?)
o Hierarchical
o Lossless JPEG (either format)
o DNL markers
o 12-bit data
o Fractional sampling
o Color Quantization 

Of these the last is the only one that should make any difference to 
anyone. If run this on a system that is not using a 24-bit display mode
you will not get good results.

Disk Map:

apps - The VIEWER application
bc - Build directory for Borland C++
bcbobj - Build directory for Borland C++Builder
cbuilder - Source code and project files specific to C++Builder
gif - Command Line GIF encoder and decoder
include - Include files
jpeg - Command Line JPEG encoder and decoder
msvc - MSVC++ build directory
png - Command Line PNG encoder and decoder
source - Source code
specs - Freely available file specifications

Compilers:

This stuff compiles on Borland C++ V5, Borland C++Bulder V3, and GNU C++ 
V 2.7.2, and MSVC++ V5.

The GIF source code compiles on MSVC++ but does not work.

Using With C++Builder:

The instructions are in the CBUILDER directory.
o Open the file ColImage.BPK.
o Compile the project
o Select COMPONENT|INSTALL PACKAGES|ADD
o Add the file COLIMAGE.BPL

Future Plans:

Documentation
OCX
C++Builder Custom Control

Send Questions or comments to

info@colosseumbuilders.com
