#ifndef BASIC_INTERPRET_INTERFACE_LAYER_H
#define BASIC_INTERPRET_INTERFACE_LAYER_H

#include "types.h"

struct FinalCompile {
  u8 instr;
  u8 data1;
  u8 data2;
  u8 data3;
  s32 data4;
};

struct FinalVariable {
  s32 value;
};

struct BASIC_Main {
  u32 NumInstances;
  u32 Overall_Speed;
  u32 Error_ID;
  u16 NumLines;
  u8 NumVars;
  u8 NumGlobals;
  u8 NumProcs;
  u8 PollFrom;
  //   FinalVariable *Globals;
  //   FinalCompile *ScriptCode;
  //   FinalProc *ProcTable;
  // 	/* 0x20 */ char* name;
  // 	/* 0x24 */ u8* VTable;
  // 	/* 0x28 */ XSEItemHandler_Base* m_pOwner;
  // 	/* 0x2c */ BASIC_Instance GlobalInstance;
  // 	/* 0x80 */ BASIC_Instance *DynamicInstances[16];
  // 	/* 0xc0 */ BASIC_Instance *CurrentInstance;
  // public:
  // 	/* 0xc4 */ __vtbl_ptr_type *$vf14428;

  // 	BASIC_Main& operator=();
  // 	BASIC_Main();
  // protected:
  // 	void SetVariable();
  // 	s32 GetVariable();
  // 	s32 DoMaths();
  // 	u8 DoCompare();
  // 	u8 ProcessOneLine();
  // 	u32 InterpretExclusive();
  // 	u32 InterpretTimeSlice();
  // 	u32 InitiateScriptInstance();
  // 	void RemoveScriptInstance();
  // 	void RemoveScriptInstanceByEntry();
  // 	s32 FindScriptByName();
  // 	Bool UpdatePointers();
  // public:
  // 	BASIC_Main();
  // 	/* vtable[1] */ virtual BASIC_Main(BASIC_Main*, int, void);
  // 	Bool Init();
  // 	s32 PollScripts();
  // 	u32 RunScript();
  // 	u32 RunScript();
  // 	void SetArg();
  // 	s32 GetArg();
  // 	void SetReturn();
  // 	s32 GetReturn();
  // 	void SetWaitState(BASIC_Main*, int, void);
  // 	bool IsProcedureRunning();
  /* vtable[2] */ virtual u8 ProcessGameSpecificInstruction(FinalCompile *line,
                                                            u32 *lnum);
  /* vtable[3] */ virtual Bool CheckWaitState(int);
};

#endif // BASIC_INTERPRET_INTERFACE_LAYER_H
