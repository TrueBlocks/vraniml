//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "BoolOp.h"
#include "BoolVertexClassify.h"

/*
// Implementation of the On-Edge reclassification rules

//********************************************************************************
void vrBoolVertVertClassifyRecord::VV_ReclassifyDoublyOnEdges(Uint32 i)
{
  // figure out the new classifications for the "on"-edges
  SFInt32  newAcl = (op == vrUNION) ? OUT : IN;
  SFInt32  newBcl = (op == vrUNION) ? IN  : OUT;
  
  Uint32 indexA  = sectors[i].indexA;
  Uint32 indexB  = sectors[i].indexB;
  Uint32 pIndexA = (indexA == 0) ? nNbrsA-1 : indexA-1;
  Uint32 pIndexB = (indexB == 0) ? nNbrsB-1 : indexB-1;
  
  VRTRACE("\t\tindexA: %d  indexB: %d  pIndexA: %d pIndexB: %d\n", indexA, indexB, pIndexA, pIndexB);
  VRTRACE("\t\tNew classifications for this sector: newAcl: %s  newBcl: %s\n", cla[newAcl+1], cla[newBcl+1]);

  VRTRACE("\t\tLook for other sectors in which we can use these new classifications\n");
  for (Uint32 j=0; j<nSectors; j++)
	{
		VRTRACE("\t\t====================================================\n");
		if(sectors[j].intersects)
		{
      VRTRACE("\t\tchecking sector[%d]: ", j);
      DEB(&sectors[j],"");VRTRACE("\n");

			// case 1
			if((sectors[j].indexA == indexA) && (sectors[j].indexB == indexB))
			{
        ASSERT(j==i);
        VRTRACE("\t\t\tfound common neighborhood -->\n\t\t\t\treclassify clNextA to %s and clNextB to %s\n", cla[newAcl+1], cla[newBcl+1]);
	    	sectors[j].clNextA = newAcl;
				sectors[j].clNextB = newBcl;
	  	}

	  	// case 2
			if((sectors[j].indexA == pIndexA) && (sectors[j].indexB == indexB))
			{
        VRTRACE("\t\t\tfound common neighborhood -->\n\t\t\t\treclassify clPrevA to %s and clNextB to %s\n", cla[newAcl+1], cla[newBcl+1]);
				sectors[j].clPrevA = newAcl;
				sectors[j].clNextB = newBcl;
			}

	  	// case 3
			if((sectors[j].indexA == indexA) && (sectors[j].indexB == pIndexB))
			{
        VRTRACE("\t\t\tfound common neighborhood -->\n\t\t\t\treclassify clNextA to %s and clPrevB to %s\n", cla[newAcl+1], cla[newBcl+1]);
	    	sectors[j].clNextA = newAcl;
				sectors[j].clPrevB = newBcl;
			}

	  	// case 4
			if((sectors[j].indexA == pIndexA) && (sectors[j].indexB == pIndexB))
			{
        VRTRACE("\t\t\tfound common neighborhood -->\n\t\t\t\treclassify clPrevA to %s and clPrevB to %s\n", cla[newAcl+1], cla[newBcl+1]);
				sectors[j].clPrevA = newAcl;
	    	sectors[j].clPrevB = newBcl;
			}

	  	if(sectors[j].clNextA == sectors[j].clPrevA && (sectors[j].clNextA == IN || sectors[j].clNextA == OUT))
			{
        VRTRACE("\t\t\tsolid A: classifications equal and ! equal to ON --> conclusive proof of no intersection --> intersects = FALSE");
				sectors[j].intersects = FALSE;
			}						

	  	if(sectors[j].clNextB == sectors[j].clPrevB && (sectors[j].clNextB == IN || sectors[j].clNextB == OUT))
			{
        VRTRACE("\t\t\tsolid B: classifications equal and ! equal to ON --> conclusive proof of no intersection --> intersects = FALSE");
				sectors[j].intersects = FALSE;
	  	}

				VRTRACE("\t\t\t*******---> (changed):  ");
				DEB(&sectors[j], "");VRTRACE("\n");

		} else
		{
      VRTRACE("\t\tsector[%d] does not intersect so forget it\n", j);
    }
    VRTRACE("\t\t====================================================\n");
  }
}

void vrBoolVertVertClassifyRecord::VV_ReclassifySinglyOnEdgesA(Uint32 i)
{
  Uint32 indexA = sectors[i].indexA;
  Uint32 indexB = sectors[i].indexB;
  Uint32 pIndexA = (indexA == 0) ? nNbrsA-1 : indexA-1;
  Uint32 pIndexB = (indexB == 0) ? nNbrsB-1 : indexB-1;

  SFInt32 newAcl = (op == vrUNION) ? OUT : IN;
  
  VRTRACE("\t\tindexA: %d  indexB: %d  pIndexA: %d pIndexB: %d\n", indexA, indexB, pIndexA, pIndexB);
  VRTRACE("\t\tNew classification for this sector: newAcl: %s\n", cla[newAcl+1]);

  VRTRACE("\t\tLook for other sectors in which we can use this new classification\n");
  for (Uint32 j=0; j<nSectors; j++)
	{
		VRTRACE("\t\t====================================================\n");
		if (sectors[j].intersects)
		{
			VRTRACE("\t\tchecking sector[%d]: ", j);
			DEB(&sectors[j],"");VRTRACE("\n");

			// case 1
			if((sectors[j].indexA == indexA) && (sectors[j].indexB == indexB))
			{
        ASSERT(i==j);
        VRTRACE("\t\t\tfound common neighborhood -->\n\t\t\t\treclassify clNextA to %s\n", cla[newAcl+1]);
				sectors[j].clNextA = newAcl;
	  	}

			// case 2
			if((sectors[j].indexA == pIndexA) && (sectors[j].indexB == indexB))
			{
        VRTRACE("\t\t\tfound common neighborhood -->\n\t\t\t\treclassify clPrevA to %s\n", cla[newAcl+1]);
				sectors[j].clPrevA = newAcl;
	  	}

	  	if(sectors[j].clNextA == sectors[j].clPrevA && (sectors[j].clNextA == IN || sectors[j].clNextA == OUT))
			{
        VRTRACE("\t\t\tsolid A: classifications equal and ! equal to ON --> conclusive proof of no intersection --> intersects = FALSE");
				sectors[j].intersects = FALSE;
			}

				VRTRACE("\t\t\t*******---> resulting sector[%d] (may or may not have changed):  ", j);
				DEB(&sectors[j], "");VRTRACE("\n");

		} else
		{
      VRTRACE("\t\tsector[%d] does not intersect so forget it\n", j);
    }
    VRTRACE("\t\t====================================================\n");
  }
}

void vrBoolVertVertClassifyRecord::VV_ReclassifySinglyOnEdgesB(Uint32 i)
{
  Uint32 indexA  = sectors[i].indexA;
  Uint32 indexB  = sectors[i].indexB;
  Uint32 pIndexA = (indexA == 0) ? nNbrsA-1 : indexA-1;
  Uint32 pIndexB = (indexB == 0) ? nNbrsB-1 : indexB-1;

  SFInt32 newBcl = (op == vrUNION) ? OUT : IN;
  
  VRTRACE("\t\tindexA: %d  indexB: %d  pIndexA: %d pIndexB: %d\n", indexA, indexB, pIndexA, pIndexB);
  VRTRACE("\t\tNew classification for this sector: newBcl: %s\n", cla[newBcl+1]);

  VRTRACE("\t\tLook for other sectors in which we can use this new classification\n");
  for (Uint32 j=0; j<nSectors; j++)
	{
		VRTRACE("\t\t====================================================\n");
		if (sectors[j].intersects)
		{
			VRTRACE("\t\tchecking sector[%d]: ", j);
			DEB(&sectors[j],"");VRTRACE("\n");

			// case 1
			if ((sectors[j].indexA == indexA) && (sectors[j].indexB == indexB))
			{
        VRTRACE("\t\t\tfound common neighborhood -->\n\t\t\t\treclassify clNextB to %s\n", cla[newBcl+1]);
				sectors[j].clNextB = newBcl;
	  	}

	  	// case 2
			if((sectors[j].indexA == indexA) && (sectors[j].indexB == pIndexB))
			{
        VRTRACE("\t\t\tfound common neighborhood -->\n\t\t\t\treclassify clPrevB to %s\n", cla[newBcl+1]);
				sectors[j].clPrevB = newBcl;
			}

			if(sectors[j].clNextB == sectors[j].clPrevB && (sectors[j].clNextB == IN || sectors[j].clNextB == OUT))
			{
        VRTRACE("\t\t\tsolid B: classifications equal and ! equal to ON --> conclusive proof of no intersection --> intersects = FALSE");
				sectors[j].intersects = FALSE;
	  	}

				VRTRACE("\t\t\t*******---> resulting sector[%d] (may or may not have changed):  ", j);
				DEB(&sectors[j], "");VRTRACE("\n");

		} else
		{
      VRTRACE("\t\tsector[%d] does not intersect so forget it\n", j);
    }
    VRTRACE("\t\t====================================================\n");
  }
}

void vrBoolVertVertClassifyRecord::VV_ReclassifyDegenerate(Uint32 i)
{
#if 0
	SFInt32 clNextA = sectors[i].clNextA;
	SFInt32 clPrevA = sectors[i].clPrevA;

	SFInt32 clNextB = sectors[i].clNextB;
	SFInt32 clPrevB = sectors[i].clPrevB;

	ASSERT(!(clPrevA==ON && clNextA==ON));
	ASSERT(!(clPrevB==ON && clNextB==ON));
	
	if (clPrevA == ON) { sectors[i].clPrevA = -clNextA; }
	if (clNextA == ON) { sectors[i].clNextA = -clPrevA; }

	if (clPrevB == ON) { sectors[i].clPrevB = -clNextB; }
	if (clNextB == ON) { sectors[i].clNextB = -clPrevB; }

		VRTRACE("Changed degenerate");
	// Note: I wrote this code to fix a bug
	// Note: I don't remember when this applies or why
	//       Perhaps this should never even be needed

	// If this is not a true crossing (ie. A is OUT to IN and B is IN to OUT (or visa-versa)
	if (!(((clNextA == OUT && clNextB == IN ) && 
		(clPrevA == IN  && clPrevB == OUT)) ||
		((clNextA == IN  && clNextB == OUT) && 
		(clPrevA == OUT && clPrevB == IN))))
	{
		VRTRACE("\t\tDegenerate Sector[%d]: clNextA: %d  clNextB: %d   clPrevA: %d   clPrevB: %d\n", i, clNextA, clNextB, clPrevA, clPrevB);
		VRTRACE("\t\tTurning off intersect flag!!!!!!!!\n");
		sectors[i].intersects=FALSE;
	}
#endif
}
*/
