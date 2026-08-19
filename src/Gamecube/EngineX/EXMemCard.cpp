#include <EngineX/EXMemcard.h>

EXBaseMemCard::EXBaseMemCard()
{
    m_pDlgClass = &EXMemCardDlg::classEXMemCardDlg;

    m_pMemCardDlg = 0;
    m_DlgData.MessageHash = -0x1;
    m_DlgData.OptHash.data[0] = -0x1; // 0xc
    m_DlgData.pMessage = "No Message"; // 0x28
    m_DlgData.pOpt.m_Data[0] = "OK"; // 0x2c
    m_DlgData.OptCount = 1;
    m_DlgData.DefaultOpt = 0;
    m_DlgData.pSlotName = "1";
    m_DlgData.MemRequired = 1;
    m_bMultiCardOpFlag = 0;
    m_bIgnoreNewMessages = false;
}

EXBaseMemCard::~EXBaseMemCard()
{
    if (m_pMemCardDlg != 0)
    {
        // need EXMemCardDlgWnd implemented
    }

    delete this;
}

Bool EXBaseMemCard::Init(EXSaveInfo& Info)
{
    return true;
}

s32 EXBaseMemCard::CardChanged(Bool& Changed)
{
    Changed = 0;
    return true;
}

s32 EXBaseMemCard::CheckSavePossible(u64 Flags)
{
    return true;
}

s32 EXBaseMemCard::CheckLoadPossible(u64 Flags)
{
    return true;
}

s32 EXBaseMemCard::SavesPresent(u8& SaveBits, u32 Flags)
{
    SaveBits = 0;
    return true;
}

s32 EXBaseMemCard::Save(u8 Save, void* pData, u64 Flags)
{
    return -1;
}

s32 EXBaseMemCard::Load(u8 Save, void* pData, u64 Flags, u64 Size)
{
    return -1;
}

Bool EXBaseMemCard::CheckHardDiskSpace()
{
    return -1;
}

char* EXBaseMemCard::Message(s64 Code) const
{
}

void EXBaseMemCard::SetDlgHashCodes(u64 MessageHash, u64 OptCount, u64 OptHash1, u64 OptHash2,
                                    u64 OptHash3, u64 OptHash4)
{
    if (m_bIgnoreNewMessages != 0)
    {
        return;
    }

    m_DlgData.MessageHash = MessageHash;
    m_DlgData.OptCount = OptCount;
    m_DlgData.OptHash.data[0] = OptHash1;
    m_DlgData.OptHash.data[1] = OptHash2;
    m_DlgData.OptHash.data[2] = OptHash3;
    m_DlgData.OptHash.data[3] = OptHash4;
}

void EXBaseMemCard::SetDlgMessages(char* Message, u64 OptCount, char* Opt1, char* Opt2, char* Opt3,
                                   char* Opt4)
{
    if (m_bIgnoreNewMessages != 0)
    {
        return;
    }

    m_DlgData.pMessage = Message;
    m_DlgData.OptCount = OptCount;
    m_DlgData.pOpt.m_Data[0] = Opt1;
    m_DlgData.pOpt.m_Data[1] = Opt2;
    m_DlgData.pOpt.m_Data[2] = Opt3;
    m_DlgData.pOpt.m_Data[3] = Opt4;
}

void EXBaseMemCard::ShowDlg(u64 DlgType, u64 DefaultOpt)
{
    if ((m_bIgnoreNewMessages == 0) && (m_pMemCardDlg == 0))
    {
        return;
    }

    m_DlgData.DlgType = DlgType;
    m_DlgData.DefaultOpt = DefaultOpt;
}

void EXBaseMemCard::HideDlg()
{
}

u32 EXBaseMemCard::DlgResult()
{
    if (m_pMemCardDlg != 0)
    {
    }
}

EXMemCardDlg* EXMemCardDlg::CreateObject()
{
    return new EXMemCardDlg();
}

EXMemCardDlg::EXMemCardDlg()
{
    paduntilthebelowisimplemented = 0;
}
