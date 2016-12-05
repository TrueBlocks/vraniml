//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#ifdef ENABLE_UNDO

#ifdef _DEBUG
void vrEulerOp::Show(vrDumpContext& dc) const
{
  char ops[][10] = { "MVFS", "KVFS", "MEV", "KEV", 
		     "MEF", "KEF", "KEMR", "MEKR", 
		     "KFMRH", "MFKRH", 
		     "RINGMV", "MOVEFACE", "REVERT", "RENUMBER" };

  VRTRACE("%10.10s(%4d) %4d %4d %4d %4d %4d %4d %4d %4.4f %4.4f %4.4f %4.4f\n",
	  ops[opcode], opcode, solidno,
	  i1, i2, i3, i4, i5, i6, 
	  f1, f2, f3, f4); 
}
#endif

void vrEulerOp::Write(FILE *fp) const
{
  ASSERT(fp);

  DEB(this, "Write");

  fwrite(this, sizeof(vrEulerOp), 1, fp);
  fflush(fp);
}

vrEulerOp::vrEulerOp(FILE *fp)
{
  ASSERT(fp);

  vrEulerOp *op;
  char *buff = (char *)malloc(sizeof(vrEulerOp));
  ASSERT(buff);
  Uint32 ret = fread(buff, sizeof(vrEulerOp), 1, fp);
  ASSERT(ret == 1);

  if (feof(fp)) {
    free(buff);
		buff = NULL;
  }

  op = (vrEulerOp *)buff;  

  DEB(op, "EulerOp::EulerOp");

  opcode = op->opcode;
  solidno = op->solidno;
  i1 = op->i1;
  i2 = op->i2;
  i3 = op->i3;
  i4 = op->i4;
  i5 = op->i5;
  i6 = op->i6;
  f1 = op->f1;
  f2 = op->f2;
  f3 = op->f3;
  f4 = op->f4;
  free(buff);
	buff=NULL;
}

void vrSolid::Invert(FILE *fp)
{
  SFBool save;
  int opCount_save;
  
  Renumber();

  DEB(this, "Invert");

  save = generateUndoLog;
  generateUndoLog = TRUE;
  opCount_save = undoLog.GetCount();
  
  RemoveEdges();
  DEB(this, "after removing edges");

  RemoveFaces();
  DEB(this, "after removing faces");
  
  lkvfs();


  SFInt32 i=0;
  while (undoLog.GetCount() > opCount_save) 
	{
    vrEulerOp *op = undoLog.GetHead();
    op->Write(fp);
    UndoEulerOp();
  }
  
  generateUndoLog = save;

  Renumber();

  DEB(this, "after Invert");
}

void vrSolid::RemoveEdges(void)
{
  vrLoop *l1, *l2;

  /* Don't use edge iterator because edges are being removed out from under us */
  vrEdge *e, *next;
  e = edges.GetHead();
  while (e) 
	{
    next = e->Next();
    VRTRACE("Removing: %d-%d\n", e->GetHe(HE1)->GetIndex(), e->GetHe(HE2)->GetIndex());

    l1 = e->GetHe(HE1)->GetLoop();
    l2 = e->GetHe(HE2)->GetLoop();
    
    if (l1 == l2) 
		{
      if (e->GetHe(HE1)->Next() == e->GetHe(HE2)) 
			{
				lkev(e->GetHe(HE2), e->GetHe(HE1));
      } else if (e->GetHe(HE2)->Next() == e->GetHe(HE1)) 
			{
				lkev(e->GetHe(HE1), e->GetHe(HE2));
      } else 
			{
				lkemr(e->GetHe(HE1), e->GetHe(HE2));
      }
    } else if (l1->GetFace() != l2->GetFace()) 
		{
      lkef(e->GetHe(HE1), e->GetHe(HE2));
    } else 
		{
      lmfkrh((l1 == l1->GetFace()->GetLoopOut()) ? l1 : l2);
    }
    DEB(this, "this after RemoveEdge");
    e = next;
  }
}

void vrSolid::RemoveFaces(void)
{
  vrFace *f1, *next;
  vrLoop *out;


  f1 = faces.GetHead();
  /* Don't use face iterator because faces are being removed out from under us */
  while (f1) {
    out = f1->GetLoopOut();
    vrLoop *ring = f1->GetFirstLoop();

    while (f1->GetSecondLoop()) {
      if (ring != out) {
      vrHalfEdge *rhe = ring->GetFirstHe();
	lmekr(out->GetFirstHe(), rhe);
	lkev(out->GetFirstHe(), rhe);
	ring = f1->GetFirstLoop();
      } else {
	ring = ring->Next();
      }
    }
    f1 = f1->Next();
  }

  f1 = faces.GetHead();
  next = f1->Next();
  while (next) {
    lkfmrh(f1, next);
    lmekr(f1->GetFirstHe(), f1->GetFirstHeFromSecondLoop());
    lkev (f1->GetFirstHe(), f1->GetFirstHeFromSecondLoop());
    f1 = next;
    next = f1->Next();
  }
}

#endif
