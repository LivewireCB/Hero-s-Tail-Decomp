#ifndef EXITEMPHYSICS_H
#define EXITEMPHYSICS_H

#include "types.h"
#include "EXItem.h"
#include "EXMalloc.h"

struct EXItemPhysics
{ // 0xc
    static EXRuntimeClass classEXItemPhysics;

protected:
    /* 0x0 */ EXItem* m_pItem;
    /* 0x4 */ u16 m_PhysicsFlags;
    /* 0x6 */ u16 m_CollisionFlags;

public:
    // /* 0x8 */ __vtbl_ptr_type* $vf1762;

    void* operator new(size_t size)
    {
        return _EXAlloc(size, 0);
    }

    void operator delete(void* ptr)
    {
        return EXFree(ptr);
    }

    // EXItemPhysics& operator=();
    EXItemPhysics();
    /* vtable[1] */ virtual Bool DoUpdate();
    /* vtable[2] */ virtual Bool Initialise();

protected:
    static EXRuntimeClass* _GetBaseClass(/* parameters unknown */);

public:
    /* vtable[3] */ virtual EXRuntimeClass* GetRuntimeClass() const;
    Bool IsKindOf();
    char* ClassName();
    static EXItemPhysics* CreateObject();
    // EXItemPhysics();
    /* vtable[4] */ virtual ~EXItemPhysics();
    void SetItem();
    EXItem* Item();
    /* vtable[5] */ virtual void DoCollisions();
    /* vtable[6] */ virtual Bool DoInterObjCollisions();
    /* vtable[7] */ virtual void DoInterObjCallback();
    u32 PhysicsFlags();
    void SetPhysicsFlags();
    void SetPhysicsFlagsOn();
    void SetPhysicsFlagsOff();
    void SetCollisionFlags();
    u16 CollisionFlags();
    /* vtable[8] */ virtual void DoCollision();
    /* vtable[9] */ virtual void DoMapCollisionCallBack();
};

struct EXItemPhysicsExt : /* 0x00 */ EXItemPhysics
{ // 0x50
    static EXRuntimeClass classEXItemPhysicsExt;
    /* 0x10 */ EXVector m_PlatformDeltaMove;
    /* 0x20 */ EXVector m_PlatformDeltaRotate;
    /* 0x30 */ EXVector m_DeltaMove;

protected:
    /* 0x40 */ u16 m_InterObjectGroup;
    /* 0x42 */ EXFlag16 m_InterObjectFlags;
    /* 0x44 */ EXFlag32 m_SupportFlags;

public:
    void* operator new(size_t size)
    {
        return _EXAlloc(size, 0);
    }

    // EXItemPhysicsExt& operator=();
    EXItemPhysicsExt();
    /* vtable[4] */ virtual ~EXItemPhysicsExt();

protected:
    static EXRuntimeClass* _GetBaseClass(/* parameters unknown */);

public:
    /* vtable[3] */ virtual EXRuntimeClass* GetRuntimeClass();
    Bool IsKindOf();
    char* ClassName();
    static EXItemPhysicsExt* CreateObject();
    // EXItemPhysicsExt();
    /* vtable[10] */ virtual Bool DoPostUpdate();
    /* vtable[11] */ virtual float Weight();
    /* vtable[12] */ virtual void* GetPhysicsInterface();
    /* vtable[13] */ virtual void SetCollisionItem();
    void SetInterObjectGroup();
    EXFlag16& InterObjectFlags();
    EXVector& DeltaMove();
    EXFlag32& SupportFlags();
    /* vtable[14] */ virtual Bool GetEnclosingCollisionObject();
    /* vtable[15] */ virtual Bool IsObjectStationary();
    /* vtable[16] */ virtual void SetVelocity();
    /* vtable[17] */ virtual EXVector GetVelocity();
    u16 GetInterObjectGroup();
};

#endif // EXITEMPHYSICS_H
