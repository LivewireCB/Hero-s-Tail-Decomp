#ifndef EXDEBUGWND_H
#define EXDEBUGWND_H

#include "types.h"

// struct EXWatchWnd : /* 0x0000 */ EXWnd
// { // 0x12d0
// protected:
//     /* 0x12b0 */ u16 m_StartRow;
//     /* 0x12b2 */ u16 m_Row;
//     /* 0x12b4 */ s16 m_MouseCol;
//     /* 0x12b6 */ s16 m_MouseRow;
//     /* 0x12b8 */ Bool m_MouseTop;
//     /* 0x12ba */ s16 m_RepMouseCol;
//     /* 0x12bc */ s16 m_RepMouseRow;
//     /* 0x12be */ Bool m_RepMouseTop;
//     /* 0x12c0 */ s16 m_RepeatCount;
//     /* 0x12c2 */ s16 m_ResetRepeatCount;
//     /* 0x12c4 */ Bool m_ScrollUp;
//     /* 0x12c5 */ Bool m_ScrollDown;

// public:
//     // EXWatchWnd& operator=();
//     EXWatchWnd();
//     // /* vtable[1] */ virtual EXWatchWnd(EXWatchWnd*, int, void);
//     // EXWatchWnd();
//     /* vtable[10] */ virtual Bool Update();
//     /* vtable[17] */ virtual Bool Draw();
//     Bool DrawSection();
//     void DrawItem();
//     void SaveState();
//     void LoadState();
//     /* vtable[20] */ virtual void Close();
//     /* vtable[21] */ virtual void ButtonDown();
//     /* vtable[22] */ virtual void ButtonUp();
// };

enum ViewType
{
    Millisecs = 0,
    PCFrame = 1,
    ScanLines = 2
};

enum TimerViewType
{
    Current = 0,
    Average = 1,
    Maximum = 2,
    Minimum = 3
};

// struct EXStatsWnd : /* 0x0000 */ EXWnd { // 0x12f0
// protected:
// 	/* 0x12b0 */ EXMenu *m_pGrpMenu;
// 	/* 0x12b4 */ s32 m_Group;
// 	/* 0x12b8 */ s32 m_GroupCount;
// 	/* 0x12bc */ u32 m_LastTimerCount;
// 	/* 0x12c0 */ u32 m_LastCounterCount;
// 	/* 0x12c4 */ u32 m_LastLimitCount;
// 	/* 0x12c8 */ u32 m_ValCol;
// 	/* 0x12cc */ ViewType m_ViewType;
// 	/* 0x12d0 */ TimerViewType m_TimerViewType;
// 	/* 0x12d4 */ u16 m_StartRow;
// 	/* 0x12d6 */ s16 m_MouseCol;
// 	/* 0x12d8 */ s16 m_MouseRow;
// 	/* 0x12da */ s16 m_RepeatCol;
// 	/* 0x12dc */ s16 m_RepeatRow;
// 	/* 0x12de */ Bool m_ScrollUp;
// 	/* 0x12df */ Bool m_ScrollDown;
// 	/* 0x12e0 */ u8 m_Precision;
// 	/* 0x12e1 */ u8 m_RepeatCount;

// public:
// 	EXStatsWnd& operator=();
// 	EXStatsWnd();
// 	/* vtable[1] */ virtual EXStatsWnd(EXStatsWnd*, int, void);
// protected:
// 	void FormatValue();
// public:
// 	EXStatsWnd();
// 	/* vtable[10] */ virtual Bool Update();
// 	/* vtable[17] */ virtual Bool Draw();
// 	/* vtable[27] */ virtual Bool MenuSelect();
// 	void UpdateGroupMenu();
// 	void SaveState();
// 	void LoadState();
// 	/* vtable[20] */ virtual void Close();
// 	void SetViewType();
// 	void SetTimerViewType();
// 	void SetGroup();
// 	/* vtable[21] */ virtual void ButtonDown();
// 	/* vtable[22] */ virtual void ButtonUp();
// };

#endif // EXDEBUGWND_H
