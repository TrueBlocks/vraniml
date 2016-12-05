#ifndef __UNDO_H3D
#define __UNDO_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

enum { MVFS, KVFS, MEV, KEV, MEF, KEF, KEMR, MEKR, KFMRH, MFKRH, 
	 RINGMV, MOVEFACE, REVERT, RENUMBER };

enum {FACE, EDGE, VERTEX};

#ifdef ENABLE_UNDO

class vrEulerOp : public xIntrusiveListNode<vrEulerOp *>
{

public:
  Uint32  opcode;
  Uint32  solidno;
  Uint32  i1, i2, i3, i4, i5, i6;
  SFFloat f1, f2, f3, f4;

public:

  vrEulerOp(Uint32 op, Uint32 s, 
	  Uint32 ii1, Uint32 ii2, Uint32 ii3, Uint32 ii4, Uint32 ii5, Uint32 ii6,
	  SFFloat ff1, SFFloat ff2, SFFloat ff3, SFFloat ff4)
  {
    opcode = op; solidno = s;
    i1 = ii1; i2 = ii2; i3 = ii3; i4 = ii4; i5 = ii5; i6 = ii6; 
    f1 = ff1; f2 = ff2; f3 = ff3; f4 = ff4;
  }
  vrEulerOp(FILE *); // same as Read
  void      Write     (FILE *fp) const;
  void      Apply     (vrSolid *s);
  ~vrEulerOp() { }

  friend class vrSolid;

#ifdef _DEBUG
  void Show(vrDumpContext& dc) const;
#endif
};
#ifdef ENABLE_ENDO
typedef vrIntrusiveList<vrEulerOp*> vrEulerOpList;
#endif

class vrTransactionLog
{

private:
  Uint32 log[MAX_UNDO_RECORDS];
  Uint32 top;
  Uint32 bottom;
  Uint32 depth;

public:
  vrTransactionLog() 
    { 
      top = bottom = depth = 0; 
    }
  ~vrTransactionLog() { }

  void Begin (Uint32 opCount);
  void End   (void);
  void Undo  (Uint32 opCount, vrSolid *s);

  friend class vrSolid;
};

#endif

#endif /* ENABLE_UNDO */
