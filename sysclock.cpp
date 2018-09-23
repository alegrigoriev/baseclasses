//------------------------------------------------------------------------------
// File: SysClock.cpp
//
// Desc: DirectShow base classes - implements a system clock based on 
//       IReferenceClock.
//
// Copyright (c) 1992-2001 Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#include <streams.h>
#include <limits.h>


/* List of class IDs and creator functions for the class factory. This
   provides the link between the OLE entry point in the DLL and an object
   being created. The class factory will call the static CreateInstance
   function when it is asked to create a CLSID_SystemClock object */

CFactoryTemplate g_SystemClockTemplates[1] = {
    {L"System reference clock", &CLSID_SystemClock, CSystemClock::CreateInstance}
};

int g_cSystemClockTemplates = sizeof(g_SystemClockTemplates) / sizeof(g_SystemClockTemplates[0]);

/* This goes in the factory template table to create new instances */
CUnknown * WINAPI CSystemClock::CreateInstance(__inout_opt LPUNKNOWN pUnk, __inout HRESULT *phr)
{
    return new CSystemClock(NAME("System reference clock"),pUnk, phr);
}
#pragma comment(linker, "/ALTERNATENAME:?g_Templates@@3PAVCFactoryTemplate@@A=?g_SystemClockTemplates@@3PAVCFactoryTemplate@@A")
#pragma comment(linker, "/ALTERNATENAME:?g_cTemplates@@3HA=?g_cSystemClockTemplates@@3HA")


CSystemClock::CSystemClock(__in_opt LPCTSTR pName, __inout_opt LPUNKNOWN pUnk, __inout HRESULT *phr) :
    CBaseReferenceClock(pName, pUnk, phr)
{
}

STDMETHODIMP CSystemClock::NonDelegatingQueryInterface(
    REFIID riid,
    __deref_out void ** ppv)
{
    if (riid == IID_IPersist)
    {
        return GetInterface(static_cast<IPersist *>(this), ppv);
    }
    else if (riid == IID_IAMClockAdjust)
    {
        return GetInterface(static_cast<IAMClockAdjust *>(this), ppv);
    }
    else
    {
        return CBaseReferenceClock::NonDelegatingQueryInterface(riid, ppv);
    }
}

/* Return the clock's clsid */
STDMETHODIMP
CSystemClock::GetClassID(__out CLSID *pClsID)
{
    CheckPointer(pClsID,E_POINTER);
    ValidateReadWritePtr(pClsID,sizeof(CLSID));
    *pClsID = CLSID_SystemClock;
    return NOERROR;
}


STDMETHODIMP 
CSystemClock::SetClockDelta(REFERENCE_TIME rtDelta)
{
    return SetTimeDelta(rtDelta);
}
