#ifndef BASIC_INTERPRET_INTERFACE_LAYER_H
#define BASIC_INTERPRET_INTERFACE_LAYER_H

#include "types.h"

struct BASIC_Main { // 0xc8
// protected:
// 	/* 0x00 */ u32 NumInstances;
// 	/* 0x04 */ u32 Overall_Speed;
// 	/* 0x08 */ u32 Error_ID;
// 	/* 0x0c */ u16 NumLines;
// 	/* 0x0e */ u8 NumVars;
// 	/* 0x0f */ u8 NumGlobals;
// 	/* 0x10 */ u8 NumProcs;
// 	/* 0x11 */ u8 PollFrom;
// 	/* 0x14 */ FinalVariable* Globals;
// 	/* 0x18 */ FinalCompile* ScriptCode;
// 	/* 0x1c */ FinalProc* ProcTable;
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
// 	/* vtable[2] */ virtual u8 ProcessGameSpecificInstruction();
	/* vtable[3] */ virtual Bool CheckWaitState(int);
};

#endif // BASIC_INTERPRET_INTERFACE_LAYER_H
