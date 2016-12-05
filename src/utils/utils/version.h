#ifndef _H_VERSIONINFO_UTIL
#define _H_VERSIONINFO_UTIL

/*----------------------------------------------------------------------
CLASS
	vrVersionInfo

	Used to return versioning information about the VRaniML library.

DESCRIPTION
	<ul>
	Use the vrGetVersion method to query the library about it's current version
	number and other version information.
	</ul>

NOTES
	<ul>
	None.
	</ul>

EXAMPLE CODE
	<pre>
	vrVersionInfo info;
	vrGetVersion(&info);

	dc << "Product: " << info.product << "\n";
	dc << "Vendor: " << info.vendor << "\n";
	dc << "Version Num: " << info.majorNum << "." << info.minorNum << "." << info.releaseNum << "\n";
	dc << "Build Date: " << info.buildDate << " -- " info.buildTime << "\n";

	// OUTPUT
	Product: VRaniML
	Vendor: Great Hill Corporation
	Version Num: 0.9.3
	Build Date: Nov 18, 1998 - 10:38am
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class UL_Interface vrVersionInfo
{
public:
  //<doc>------------------------------------------------------------
  // <dd>The name of this product.
	// [default:] "VRaniML"
	//
	SFString product;

  //<doc>------------------------------------------------------------
  // <dd>The vendor of this product.
	// [default:] "Great Hill Corporation"
	//
	SFString vendor;

  //<doc>------------------------------------------------------------
  // <dd>The major number of this release (i.e. the XX in XX.NN.NN)
	// [default:] Current release
	//
	SFInt32  majorNum;

  //<doc>------------------------------------------------------------
  // <dd>The minor number of this release (i.e. the XX in NN.XX.NN)
	// [default:] Current release
	//
	SFInt32  minorNum;

  //<doc>------------------------------------------------------------
  // <dd>The release number of this release (i.e. the XX in NN.NN.XX)
	// [default:] Current release
	//
	SFInt32  releaseNum;

  //<doc>------------------------------------------------------------
  // <dd>The date this release was created.
	//
	SFString buildDate;

  //<doc>------------------------------------------------------------
  // <dd>The time this release was created.
	//
	SFString buildTime;
};

//<doc>------------------------------------------------------------
// <dd>Call to retrieve release information about VRaniML.
void UL_Interface vrGetVersion(vrVersionInfo *info);

#endif