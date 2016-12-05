//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#ifdef ENABLE_UNDO


void vrSolid::AddUndoRecord(Uint32 op,
			  Uint32 i1, Uint32 i2, Uint32 i3, Uint32 i4, Uint32 i5, Uint32 i6, 
			  SFFloat f1, SFFloat f2, SFFloat f3, SFFloat f4)
{
  if (generateUndoLog) {
    static char ops[][10] = { "MVFS", "KVFS", "MEV", "KEV", 
			      "MEF", "KEF", "KEMR", "MEKR", 
			      "KFMRH", "MFKRH", 
			      "RINGMV", "MOVEFACE", "REVERT" };
    
    static char opposite_ops[][10] = { "KVFS", "MVFS", "KEV", "MEV", 
				       "KEF", "MEF", "MEKR", "KEMR", 
				       "MFKRH", "KFMRH", 
				       "RINGMV", "MOVEFACE", "REVERT" };
    
ASSERT(0);
    Uint32 s = 0; //GetIndex();
    
    vrEulerOp *record = new vrEulerOp(op, s, i1, i2, i3, i4, i5, i6, f1, f2, f3, f4);
    
    DEB(record, "AddUndoRecord");

    undoLog.AddHead(record);
  }
}
 
void vrSolid::BeginTransaction(void)
{
  transLog.Begin(undoLog.GetCount());
}

void vrSolid::EndTransaction(void)
{
  transLog.End();
}

void vrSolid::UndoTransaction(void)
{
  transLog.Undo(undoLog.GetCount(), this);
}

void vrSolid::UndoEulerOp(void)
{
  vrEulerOp *op;
  SFBool save = generateUndoLog;

  generateUndoLog = FALSE;
  
  op = undoLog.GetHead();
  
  if (op) 
	{
    undoLog.RemoveAt(op);
    op->Apply(this);
    delete op;
  }

  generateUndoLog = save;
}

void vrEulerOp::Apply(vrSolid *s)
{
  ASSERT(s);
  
  DEB(this, "Apply");

  switch (opcode) {
  case MVFS:
//    // What should I really do here? 
//    ASSERT(0);
//    s2 = new vrSolid(f1, f2, f3);
//    ASSERT(s->GetVertexList()->GetCount() == 1);
    s->GetFirstVertex()->SetLocation(SFVec3f(f1, f2, f3));
    s->GetFirstVertex()->SetIndex(i1);
    break;
  case KVFS:
    s->kvfs();
    break;
  case MEV:
    ASSERT(0);
		//s->verts.SetNextIndex(i6);
    if (i4 == i5) {
      s->smev(i1, i3, f1, f2, f3);
    } else {
      s->mev(i1, i2, i3, i4, i5, f1, f2, f3);
    }
    break;
  case KEV:
    s->kev(i1, i2, i3);
    break;
  case MEF:
    s->faces.SetNextIndex(i6);
    if (i3 == i4) {
      s->smef(i1, i2, i4);
    } else {
      s->mef(i1, i2, i3, i4, i5);
    }
    break;
  case KEF:
    s->kef(i1, i2, i3);
    break;
  case MEKR:
    s->mekr(i1, i2, i3, i4, i5);
    break;
  case KEMR:
    s->kemr(i1, i2, i3);
    if (i6) {
      /* The new loop should not be the outer loop */
      vrFace *f = s->findFace(i1);
      vrLoop *l = f->GetFirstLoop();
      while (l) 
			{
				/* 
				 * This finds any loop that is not the outer loop.  It should probably find
				 * the right loop -- it can do that if lmekr writes the index of the 
				 * approriate loop in one of the fields 
				 */
				if (l != f->GetLoopOut()) {
					f->SetLoopOut(l);
					break;
				}
				l = l->Next();
      }
    }
    break;
  case MFKRH:
    s->faces.SetFaceIndex(i6);
    s->mfkrh(i1, i2, i3);
    break;
  case KFMRH:
    s->kfmrh(i1, i2);
    break;
  case RINGMV:
    s->ringmv(i1, i2, i3, i4, (SFBool)i5);
    break;
  case MOVEFACE:
    {
//      wWorld *w = s->GetTopLevel();
//      ASSERT(w);
ASSERT(0);
      vrSolid *s2 = NULL; //(vrSolid *)w->FindObject(BY_INDEX, i2);
      ASSERT(!s2); ///This is a warnign to make me reconsider this code because it is wrong.
      s->MoveFace(s->findFace(i1), s2);
    }
    break;
  case REVERT:
    s->Revert();
    break;
  case RENUMBER:
    vrFace *f;
    vrEdge *e;
    vrVertex *v;
    switch (i1) {
    case FACE:
      f = s->findFace(i3);
      f->SetIndex(i2);
      break;
    case EDGE:
      e = s->findEdge(i3);
      e->SetIndex(i2);
      break;
    case VERTEX:
      v = s->findVertex(i3);
      v->SetIndex(i2);
      break;
    default:
      {
        Uint32 unknown_type=0;
        ASSERT(unknown_type);
      }
    }
  default:
    {
      Uint32 unknown_operator=0;
      ASSERT(unknown_operator);
    }
  }

  DEB(s, "s after undo");
}

/***********************************************************************/
void vrTransactionLog::Begin(Uint32 opCount)
{
  if (depth++ > 0) return;

  log[top] = opCount;
  top++;
  
  if (top == MAX_UNDO_RECORDS) {
    top = 0;
  }
  
  if (top == bottom) {
    bottom++;
    if (bottom == MAX_UNDO_RECORDS) {
      bottom = 0;
    }
  }
}

void vrTransactionLog::End(void)
{
  if (depth > 0) 
    depth--;
}

void vrTransactionLog::Undo(Uint32 opCount, vrSolid *s)
{
  Uint32 nops;

  if (top == bottom) 
    return;

  if (top == 0) {
    top = MAX_UNDO_RECORDS;
  } else {
    top--;
  }

  nops = log[top];
  
  while (opCount > nops) {
    s->UndoEulerOp();
  }
  depth = 0;
}

#if 0
vrSolid *ReadFromFile(const SFString& filename)
{
  FILE *fp = fopen(filename, "r");
  ASSERT(fp);

  EulerOp *op = new EulerOp(fp);
  
  vrSolid *s;
  while (op) {
    if (op->opcode == MVFS) {
      s = new vrSolid(op->f1, op->f2, op->f3);
      ASSERT(s);
    } else {
      ASSERT(s);
      op->Apply(s);
    }
    delete op;
    op = NULL;
    op = new EulerOp(fp);
  }

  return s;
}
#endif

#endif
