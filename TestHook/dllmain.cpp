// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <strsafe.h>
#include <Windows.h>

typedef struct _MYHOOKDATA
{
    int nType;
    HOOKPROC hkprc;
    HHOOK hhook;
} MYHOOKDATA;

enum Hooks
{
    HookCallWnd,
    HookCallWndProcRet,
    HookWhCbt,
    HookWhDebug,
    HookForegroundIdle,
    HookGetMsg,
    HookKeyboardLl,
    HookKeyboard,
    HooksCount,
};

MYHOOKDATA myhookdata_dll[HooksCount];


// If function does not call CallNextHookEx it should return 0.
LRESULT WINAPI CallWndProc_Dll(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        const bool messageSentByCurrentThread = wParam != 0;
        CWPSTRUCT* pInfo = (CWPSTRUCT*)lParam;
    }
    return CallNextHookEx(myhookdata_dll[HookCallWnd].hhook, nCode, wParam, lParam);
}

// If function does not call CallNextHookEx it should return 0.
LRESULT WINAPI CallWndRetProc_Dll(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        // Process the message
        CWPRETSTRUCT* pInfo = (CWPRETSTRUCT*)lParam;
        const bool messageSentByCurrentProcess = wParam != 0;
    }
    return CallNextHookEx(myhookdata_dll[HookCallWndProcRet].hhook, nCode, wParam, lParam);
}

LRESULT CALLBACK CBTProc_Dll(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode < 0)
    {
        return CallNextHookEx(myhookdata_dll[HookWhCbt].hhook, nCode, wParam, lParam);
    }
    switch (nCode)
    {
        // The system is about to activate window
    case HCBT_ACTIVATE:

        break;

        // The system has removed a mouse message from the system message queue.
    case HCBT_CLICKSKIPPED:
        break;

        // The window is about to be created. It is called before sending WM_CREATE, WM_NCCREATE message to a window.
        // If hook proc returns non 0 value, the system destroys the window. CreateWindow returns null, but WM_DESTROY is not sent.
        // Window already created but its final size and position may not have been established. It is possible to send messages to the
        // newly created window, although it has not yet received WM_NCCREATE or WM_CREATE messages. It is also possible to change the position
        // in the z-order of the newly created window by modifying the hwndInsertAfter.
    case HCBT_CREATEWND:
    {
        CBT_CREATEWND* pInfo = (CBT_CREATEWND*)lParam;
    }
    break;

    // A window is about to be destroyed.
    case HCBT_DESTROYWND:
        break;

        // The window has removed keyboard message from the system message queue. Upon receiving this hook code, a CBT application must install a WH_JOURNALPLAYBACK hook procedure in response to the keyboard message.
    case HCBT_KEYSKIPPED:
        break;

        // A window is about to be minimized or maximized.
    case HCBT_MINMAX:
        break;

        // A window is about to be moved or sized.
    case HCBT_MOVESIZE:
        break;

        // The system has retrieved a WM_QUEUESYNC message from the system message queue.
        // WM_QUEUESYNC - Sent by a computer-based training (CBT) application to separate user-input messages from other messages sent through the WH_JOURNALPLAYBACK procedure.
    case HCBT_QS:
        break;

        // A window is about to receive the keyboard focus.
    case HCBT_SETFOCUS:
        break;

        // A system command is about to be carried out.This allows a CBT application to prevent task switching by means of hot keys.
    case HCBT_SYSCOMMAND:
        break;

    default:
    {
        // TODO: write error handler
    }
    break;
    }
    return CallNextHookEx(myhookdata_dll[HookWhCbt].hhook, nCode, wParam, lParam);
}

LRESULT CALLBACK DebugProc_Dll(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        // Process message
        const DWORD dwHookType = (DWORD)nCode;
        switch (dwHookType)
        {
        case WH_CALLWNDPROC:
            break;
        case WH_CALLWNDPROCRET:
            break;
        case WH_CBT:
            break;
        case WH_DEBUG:
            break;
        case WH_GETMESSAGE:
            break;
        case WH_JOURNALPLAYBACK:
            break;
        case WH_JOURNALRECORD:
            break;
        case WH_KEYBOARD:
            break;
        case WH_MOUSE:
            break;
        case WH_MSGFILTER:
            break;
        case WH_SHELL:
            break;
        case WH_SYSMSGFILTER:
            break;
        default:
            break;
        }

        DEBUGHOOKINFO* pInfo = (DEBUGHOOKINFO*)wParam;

        // To prevent call into a hook - return non 0. Otherwise must call into CallNextHookEx

    }
    return CallNextHookEx(myhookdata_dll[HookWhDebug].hhook, nCode, wParam, lParam);

}

/* While processing this callback function, avoid calling any functions that retrieve window messages from the calling
thread's message queue. This includes GetMessage, PeekMessage, modal dialog box, and COM functions. Calling such
functions may result in the thread not returning from GetMessage or WaitMessage when there are messages in the calling
thread's message queue
*/
LRESULT CALLBACK ForegroundIdleProc_Dll(_In_ int code, WPARAM wParam, LPARAM lParam)
{
    if (code == HC_ACTION)
    {
        // Process 
    }

    return CallNextHookEx(myhookdata_dll[HookForegroundIdle].hhook, code, wParam, lParam);
}

/*  The GetMsgProc hook procedure can examine or modify the message. After the hook procedure returns control to the system,
the GetMessage or PeekMessage function returns the message, along with any modifications, to the application that originally called it.
*/
LRESULT CALLBACK GetMsgProc_Dll(_In_ int code, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    if (code == HC_ACTION)
    {
        // Process 

        const DWORD dwRemoved = wParam;
        switch (dwRemoved)
        {
        case PM_NOREMOVE:
            break;
        case PM_REMOVE:
            break;
        }

        LPMSG pMsg = (LPMSG)lParam;
    }

    return CallNextHookEx(myhookdata_dll[HookGetMsg].hhook, code, wParam, lParam);
}

/*
This hook is called in the context of the thread that installed it. The call is made by sending a message to the thread
that installed the hook. Therefore, the thread that installed the hook must have a message loop.
When this hook is called context switches to context of thread which installed this hook.

The hook proc should process a message in less time than the data entry specified in the LowLEvelHooksTimeout value in the following registry key HKEY_CURRENT_USER\Control Panel\Desktop

*/
LRESULT CALLBACK LowLevelKeyboardProc_Dll(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        // Process 
        switch (wParam)
        {
        case WM_KEYDOWN:
            break;
        case WM_KEYUP:
            break;
        case WM_SYSKEYDOWN:
            break;
        case WM_SYSKEYUP:
            break;
        default:
            break;
        }

        KBDLLHOOKSTRUCT* pInfo = (KBDLLHOOKSTRUCT*)lParam;
    }
    return CallNextHookEx(myhookdata_dll[HookKeyboardLl].hhook, nCode, wParam, lParam);
}

LRESULT CALLBACK KeyboardProc_Dll(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        // The wParam and lParam parameters contain information about a keystroke message.
    }
    else if (nCode == HC_NOREMOVE)
    {
        // The wParam and lParam parameters contain information about a keystroke message, 
        // and the keystroke message has not been removed from the message queue. (An application 
        // called the PeekMessage function, specifying the PM_NOREMOVE flag.)

        const DWORD vk = wParam;
        const DWORD info = lParam;
    }

    return CallNextHookEx(myhookdata_dll[HookKeyboard].hhook, nCode, wParam, lParam);
}


void InitHooks(HMODULE hMod)
{
    ZeroMemory(&myhookdata_dll, sizeof(myhookdata_dll));

    myhookdata_dll[HookCallWnd].hkprc = CallWndProc_Dll;
    myhookdata_dll[HookCallWnd].nType = WH_CALLWNDPROC;

    myhookdata_dll[HookCallWndProcRet].hkprc = CallWndRetProc_Dll;
    myhookdata_dll[HookCallWndProcRet].nType = WH_CALLWNDPROCRET;

    myhookdata_dll[HookWhCbt].hkprc = CBTProc_Dll;
    myhookdata_dll[HookWhCbt].nType = WH_CBT;

    myhookdata_dll[HookWhDebug].hkprc = DebugProc_Dll;
    myhookdata_dll[HookWhDebug].nType = WH_DEBUG;

    myhookdata_dll[HookForegroundIdle].hkprc = ForegroundIdleProc_Dll;
    myhookdata_dll[HookForegroundIdle].nType = WH_FOREGROUNDIDLE;

    myhookdata_dll[HookGetMsg].hkprc = GetMsgProc_Dll;
    myhookdata_dll[HookGetMsg].nType = WH_MSGFILTER;

    /*  myhookdata_dll[HookKeyboardLl].hkprc = LowLevelKeyboardProc_Dll;
    myhookdata_dll[HookKeyboardLl].nType = WH_KEYBOARD_LL;*/

    myhookdata_dll[HookKeyboard].hkprc = KeyboardProc_Dll;
    myhookdata_dll[HookKeyboard].nType = WH_KEYBOARD;

    for (size_t i = 0; i < HooksCount; i++)
    {
        myhookdata_dll[i].hhook = SetWindowsHookEx(myhookdata_dll[i].nType, myhookdata_dll[i].hkprc, hMod, 0);
        if (myhookdata_dll[i].hhook == NULL)
        {
            DWORD dwError = GetLastError();
            LPVOID lpMsgBuf;
            LPVOID lpDisplayBuf;
            DWORD dw = GetLastError();

            FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                dw,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR)&lpMsgBuf,
                0, NULL);

            // Display the error message and exit the process

            lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
                (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)"ERROR") + 40) * sizeof(TCHAR));
            StringCchPrintf((LPTSTR)lpDisplayBuf,
                LocalSize(lpDisplayBuf) / sizeof(TCHAR),
                TEXT("%s failed with error %d: %s"),
                "Error", dwError, lpMsgBuf);
            MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

            LocalFree(lpMsgBuf);
            LocalFree(lpDisplayBuf);
        }
    }
}


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        InitHooks(hModule);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
    {
        for (size_t i = 0; i < HooksCount; i++)
        {
            UnhookWindowsHookEx(myhookdata_dll[i].hhook);
        }
    }
        break;
    }
    return TRUE;
}
