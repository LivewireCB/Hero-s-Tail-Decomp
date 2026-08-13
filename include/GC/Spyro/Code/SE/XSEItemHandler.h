#ifndef XSEITEMHANDLER_H
#define XSEITEMHANDLER_H

#include "types.h"
#include "Spyro/Code/SE/XItem.h"

struct XSEItemHandler : /* 0x000 */ XItemHandler
{ // 0x250
    // private:
    //     /* 0x008 */ u32 m_UniqueID;

    // public:
    //     static EXRuntimeClass classXSEItemHandler;
    //     /* 0x00c */ TriggerTableEntry* m_pTriggerTable;
    //     /* 0x010 */ SE_Trigger* m_pTrigger;
    //     static u32 m_gNextUniqueID;
    //     /* 0x014 */ u32 m_SuspendedGroupFlags;
    //     /* 0x018 */ u32 m_SEHandlerListBitMask;
    //     /* 0x01c */ DLinkedTYPE<XSEItemHandler*> m_SEHandlerListLink[4];
    //     /* 0x05c */ s32 m_UpdateCounter;
    //     /* 0x060 */ XSEItem m_XSEItem;
    //     static char* m_pStateStrings[0];

    // private:
    //     /* 0x200 */ s32 m_SQDistUpdateCounter;
    //     /* 0x204 */ float m_SQDist;
    //     /* 0x208 */ XExtRenderInfo* m_pXExtRenderInfo;
    //     /* 0x20c */ List m_RenderCallback_List[2];
    //     /* 0x22c */ State m_State;

    // protected:
    //     /* 0x230 */ HashCodeList m_FileList;

    // public:
    //     /* 0x240 */ u32 m_SEFlags;
    //     static EXAnimatorScriptCallbacks m_ScriptCmdCallbackTable;

    //     XSEItemHandler& operator=();
    //     XSEItemHandler();
    //     /* vtable[4] */ virtual Bool DoUpdate();
    //     /* vtable[3] */ virtual Bool Initialise();

    // protected:
    //     static EXRuntimeClass* _GetBaseClass(/* parameters unknown */);

    // public:
    //     /* vtable[1] */ virtual EXRuntimeClass* GetRuntimeClass();
    //     Bool IsKindOf();
    //     char* ClassName();
    //     static XSEItemHandler* CreateObject(/* parameters unknown */);
    //     static XSEItemHandler* new_XSEItemHandler(/* parameters unknown */);
    //     void StartEXStats();
    //     void StopEXStats();
    //     float GetEXStatsMilliSecs();
    //     float GetEXStatsMilliSecsAv();
    //     float GetEXStatsMilliSecsMax();
    //     EXTimer* GetEXStats();
    //     u32 SetUniqueID();

    // private:
    //     static void gRenderCallback(/* parameters unknown */);
    //     /* vtable[10] */ virtual void v_RenderCallback();
    //     void AddRenderCallback();
    //     u32 SEUpdateLists();
    //     void SEUpdateLists();
    //     void SEAddToLists();
    //     void SERemoveFromLists();

    // public:
    //     void LoadGeo();
    //     void EnableRenderCallback();
    //     void DisableRenderCallback();
    //     void AddRenderCallback_PostCalcMatrix();
    //     void AddRenderCallback_AnimSkin();
    //     void SEAddToList();
    //     void SERemoveFromList();
    //     s32 SEIsInList();
    //     void AddToHeadTrackingList();
    //     void RemoveFromHeadTrackingList();
    //     u32 GetUniqueID();
    //     State SetState();
    //     State GetState();
    //     Bool SEUpdate();
    //     Bool SEKill();
    //     Bool SEInitialise();

    // private:
    //     void SEPreserveWrite();
    //     void SEPreserveRead();

    // protected:
    //     SE_BitHeap& GetPreserveBitHeap();
    //     void PreserveBytes();
    //     void Preserve();
    //     void Preserve();
    //     void Preserve();
    //     void Preserve();
    //     void Preserve();
    //     void Preserve();
    //     void Preserve();
    //     void Preserve();
    //     void Preserve();
    //     void Preserve();
    //     void Preserve();
    //     s32 PreserveBeenWritten();
    //     void SkipPreserveBytes();
    //     void SkipPreserve();
    //     void SkipPreserve();
    //     void SkipPreserve();
    //     void SkipPreserve();
    //     void SkipPreserve();
    //     void SkipPreserve();
    //     void SkipPreserve();
    //     void SkipPreserve();
    //     void SkipPreserve();
    //     void SkipPreserve();
    //     void SkipPreserve();

    // public:
    //     void SetDoesntHeatRender();
    //     void ClearDoesntHeatRender();
    //     s32 DoesHeatRender();
    //     void SetDoesntNeedMapRunning();
    //     void ClearDoesntNeedMapRunning();
    //     s32 DoesntNeedMapRunning();
    //     s32 NeedsMapRunning();
    //     void SetForceUpdate();
    //     void ClearForceUpdate();
    //     s32 GetForceUpdate();
    //     /* vtable[11] */ virtual void v_SetCueFlag();
    //     s32 IsCueing();
    //     s32 IsCued();
    //     /* vtable[12] */ virtual void v_CueGo();
    //     void SetIsCued();
    //     s32 GotLinkedTrigger();
    //     SE_Trigger* GetLinkedTrigger();
    //     /* vtable[13] */ virtual RCode v_TriggerUpdateActivated();
    //     void TriggerDebounce();
    //     XSEItemHandler* GetLinkedHandler();
    //     void Init();
    //     s32 GetUpdateCounter();
    //     float GetSQDist();
    //     s32 GetSQDistTime();
    //     void SetSQDist();
    //     void DoSuspend();
    //     void DoKill();
    //     XSEItemHandler();
    //     /* vtable[2] */ virtual XSEItemHandler(XSEItemHandler*, int, void);
    //     XSEItem* AddXSEItem();
    //     XSEItem* AddXSEItem();
    //     XSEItem* GetXSEItem();
    //     XSEItem* GetItem();
    //     /* vtable[14] */ virtual RCode InitialiseStart();
    //     /* vtable[15] */ virtual RCode InitialiseStart();
    //     /* vtable[16] */ virtual RCode InitialiseUpdate();
    //     /* vtable[17] */ virtual RCode Update();
    //     /* vtable[18] */ virtual RCode v_UpdateSuspended();
    //     /* vtable[19] */ virtual RCode Delete();
    //     /* vtable[20] */ virtual void DrawBodyCollision();
    //     SE_Map* GetTriggersSE_Map();
    //     SE_Map* GetTriggerMap();
    //     s32 GetTriggersMapListIndex();
    //     XSEItemEnv* GetItemEnv();
    //     SE_Trigger* GetTrigger();
    //     s32 GetTriggersIndex();
    //     void SetTrigger();
    //     EXHashCode GetPrimaryHashCode();
    //     EXHashCode GetSubHashCode();
    //     TriggerTableEntry* GetTriggerTable();
    //     EXItemAnimator* GetAnimator();
    //     EXItemAnimator_Script* GetScriptAnimator();
    //     void AddAnimator();
    //     EXItemAnimator* AddAnimator();
    //     EXItemAnimator* AddTriggerAnimator();
    //     void SetSuspended();
    //     void ClearSuspended();
    //     s32 IsSuspended();
    //     void SetUpdateOrder();
    //     UpdateOrder GetUpdateOrder();
    //     /* vtable[21] */ virtual void v_Preserve();
    //     /* vtable[22] */ virtual float v_GetPlayerDistance();
    //     /* vtable[23] */ virtual s32 v_GetPosition();
    //     EXGeoPath* GetPath();
    //     /* vtable[24] */ virtual void v_ScriptCmd_SOUND();
    //     /* vtable[25] */ virtual void v_ScriptCmd_TEXT();
    //     /* vtable[7] */ virtual u32 DoScriptCmdObject();
    //     void SetAnimatorFlags();
    //     void DisplayOn();
    //     void DisplayOff();
    //     void Debug_Check();
    //     static s32 OnTriggerCreate(/* parameters unknown */);
    //     void SetXExtRenderInfo();
    //     XExtRenderInfo* GetXExtRenderInfo();
    //     void SetExtRenderInfo();
    //     void SetDoesntPause();
    //     void ClearDoesntPause();
    //     s32 DoesntPause();
    //     s32 DoesPause();
    //     static XSEItemHandler* GetHandler(/* parameters unknown */);
    //     static u32 ScriptCmdCallback_PreCreate(/* parameters unknown */);
    //     static void ScriptCmdCallback_Delete(/* parameters unknown */);
    //     static void ScriptCmdCallback_PostCreateCamera(/* parameters unknown */);
    //     static void ScriptCmdCallback_CmdSound(/* parameters unknown */);
    //     /* vtable[26] */ virtual u32 v_DoScriptCmd_PreCreate();
    //     /* vtable[27] */ virtual void v_DoScriptCmd_Delete();
    //     /* vtable[28] */ virtual void v_DoScriptCmd_PostCreateCamera();
    //     /* vtable[29] */ virtual void v_DoScriptCmd_CmdSound();
    //     XSEItemHandler* CreateXSEItemHandler();
    //     void TriggerSetUseMapOn();
    //     void TriggerClearUseMapOn();
    //     s32 IsTriggerMapRestart();
    //     s32 IsTriggerFirstInit();
    //     /* vtable[30] */ virtual DLinkedTypeRCode v_OnPauseOn();
    //     /* vtable[31] */ virtual DLinkedTypeRCode v_OnPauseOff();
    //     /* vtable[32] */ virtual DLinkedTypeRCode v_OnPause();
    //     EXMapOn GetTriggersMapOn();
};

#endif
