// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

typedef struct _MYHOOKDATA
{
    int nType;
    HOOKPROC hkprc;
    HHOOK hhook;
} MYHOOKDATA;

enum Hooks
{
    IDM_CALLWND,
    IDM_MSGPROC,
    IDM_DEBUG,
    IDM_CBT,
    IDM_MOUSE,
    IDM_KEYBOARD,
    IDM_MSGFILTER,

    NUMHOOKS,
};


MYHOOKDATA myhookdata[NUMHOOKS];


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

LRESULT WINAPI CallWndProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode < 0)
    {
        return CallNextHookEx(myhookdata[IDM_CALLWND].hhook, nCode, wParam, lParam);
    }
    if (HC_ACTION == nCode)
    {
        // Do processing
    }
    return CallNextHookEx(myhookdata[IDM_CALLWND].hhook, nCode, wParam, lParam);
}

LRESULT WINAPI GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode < 0)
    {
        return CallNextHookEx(myhookdata[IDM_MSGPROC].hhook, nCode, wParam, lParam);
    }
    if (HC_ACTION == nCode)
    {
        // Do processing
    }
    return CallNextHookEx(myhookdata[IDM_MSGPROC].hhook, nCode, wParam, lParam);
}

LRESULT WINAPI DebugProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode < 0)
    {
        return CallNextHookEx(myhookdata[IDM_DEBUG].hhook, nCode, wParam, lParam);
    }
    if (HC_ACTION == nCode)
    {
        // Do processing
    }
    return CallNextHookEx(myhookdata[IDM_DEBUG].hhook, nCode, wParam, lParam);
}

LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode < 0)
    {
        return CallNextHookEx(myhookdata[IDM_CBT].hhook, nCode, wParam, lParam);
    }
    switch (nCode)
    {
    case HCBT_ACTIVATE:
        // TODO: write error handler
        break;

    case HCBT_CLICKSKIPPED:
        // TODO: write error handler
        break;

    case HCBT_CREATEWND:
        // TODO: write error handler
        break;

    case HCBT_DESTROYWND:
        // TODO: write error handler
        break;

    case HCBT_KEYSKIPPED:
        // TODO: write error handler
        break;

    case HCBT_MINMAX:
            // TODO: write error handler
        break;

    case HCBT_MOVESIZE:
            // TODO: write error handler
        break;

    case HCBT_QS:
            // TODO: write error handler
        break;

    case HCBT_SETFOCUS:
            // TODO: write error handler
        break;

    case HCBT_SYSCOMMAND:
            // TODO: write error handler
        break;

    default:
        {
            // TODO: write error handler
        }
        break;
    }
    return CallNextHookEx(myhookdata[IDM_CBT].hhook, nCode, wParam, lParam);
}

LRESULT WINAPI MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode < 0)
    {
        return CallNextHookEx(myhookdata[IDM_MOUSE].hhook, nCode, wParam, lParam);
    }
        // Do processing
    return CallNextHookEx(myhookdata[IDM_MOUSE].hhook, nCode, wParam, lParam);
}

LRESULT WINAPI KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode < 0)
    {
        return CallNextHookEx(myhookdata[IDM_KEYBOARD].hhook, nCode, wParam, lParam);
    }
    // Do processing
    return CallNextHookEx(myhookdata[IDM_KEYBOARD].hhook, nCode, wParam, lParam);
}

/****************************************************************
WH_MSGFILTER hook procedure
****************************************************************/

LRESULT CALLBACK MessageProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode < 0)  // do not process message 
        return CallNextHookEx(myhookdata[IDM_MSGFILTER].hhook, nCode, wParam, lParam);
    switch (nCode)
    {
    case MSGF_DIALOGBOX:
        {
            // TODO: write error handler
        }
        break;

    case MSGF_MENU:
        {
            // TODO: write error handler
        }
        break;

    case MSGF_SCROLLBAR:
        {
            // TODO: write error handler
        }
        break;

    default:
        break;
    }
    
    return CallNextHookEx(myhookdata[IDM_MSGFILTER].hhook, nCode, wParam, lParam);
}