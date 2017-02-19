#pragma once

#include "resource.h"

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

MYHOOKDATA myhookdata[HooksCount];

// If function does not call CallNextHookEx it should return 0.
LRESULT WINAPI CallWndProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        const bool messageSentByCurrentThread = wParam != 0;
        CWPSTRUCT* pInfo = (CWPSTRUCT*)lParam;
    }
    return CallNextHookEx(myhookdata[HookCallWnd].hhook, nCode, wParam, lParam);
}

// If function does not call CallNextHookEx it should return 0.
LRESULT WINAPI CallWndRetProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        // Process the message
        CWPRETSTRUCT* pInfo = (CWPRETSTRUCT*)lParam;
        const bool messageSentByCurrentProcess = wParam != 0;
    }
    return CallNextHookEx(myhookdata[HookCallWndProcRet].hhook, nCode, wParam, lParam);
}

LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode < 0)
    {
        return CallNextHookEx(myhookdata[HookWhCbt].hhook, nCode, wParam, lParam);
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
    return CallNextHookEx(myhookdata[HookWhCbt].hhook, nCode, wParam, lParam);
}

LRESULT CALLBACK DebugProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
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
    return CallNextHookEx(myhookdata[HookWhDebug].hhook, nCode, wParam, lParam);

}

/* While processing this callback function, avoid calling any functions that retrieve window messages from the calling
    thread's message queue. This includes GetMessage, PeekMessage, modal dialog box, and COM functions. Calling such
    functions may result in the thread not returning from GetMessage or WaitMessage when there are messages in the calling
    thread's message queue
*/
DWORD CALLBACK ForegroundIdleProc(_In_ int code, DWORD wParam, LONG lParam)
{
    if (code == HC_ACTION)
    {
        // Process 
    }

    return CallNextHookEx(myhookdata[HookForegroundIdle].hhook, code, wParam, lParam);
}

/*  The GetMsgProc hook procedure can examine or modify the message. After the hook procedure returns control to the system,
    the GetMessage or PeekMessage function returns the message, along with any modifications, to the application that originally called it.
*/
LRESULT CALLBACK GetMsgProc(_In_ int code, _In_ WPARAM wParam, _In_ LPARAM lParam)
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

    return CallNextHookEx(myhookdata[HookGetMsg].hhook, code, wParam, lParam);
}

/*
    This hook is called in the context of the thread that installed it. The call is made by sending a message to the thread 
    that installed the hook. Therefore, the thread that installed the hook must have a message loop.
    When this hook is called context switches to context of thread which installed this hook.

    The hook proc should process a message in less time than the data entry specified in the LowLEvelHooksTimeout value in the following registry key HKEY_CURRENT_USER\Control Panel\Desktop

*/
LRESULT CALLBACK LowLevelKeyboardProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
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
    return CallNextHookEx(myhookdata[HookKeyboardLl].hhook, nCode, wParam, lParam);
}

LRESULT CALLBACK KeyboardProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
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

    return CallNextHookEx(myhookdata[HookKeyboard].hhook, nCode, wParam, lParam);
}

void InitHooks()
{
    ZeroMemory(&myhookdata, sizeof(myhookdata));
    
    myhookdata[HookCallWnd].hkprc = CallWndProc;
    myhookdata[HookCallWnd].nType = WH_CALLWNDPROC;

    myhookdata[HookCallWndProcRet].hkprc = CallWndRetProc;
    myhookdata[HookCallWndProcRet].nType = WH_CALLWNDPROCRET;

    myhookdata[HookWhCbt].hkprc = CBTProc;
    myhookdata[HookWhCbt].nType = WH_CBT;

    myhookdata[HookWhDebug].hkprc = DebugProc;
    myhookdata[HookWhDebug].nType = WH_DEBUG;

    myhookdata[HookForegroundIdle].hkprc = ForegroundIdleProc;
    myhookdata[HookForegroundIdle].nType = WH_FOREGROUNDIDLE;

    myhookdata[HookGetMsg].hkprc = GetMsgProc;
    myhookdata[HookGetMsg].nType = WH_MSGFILTER;

    myhookdata[HookKeyboardLl].hkprc = LowLevelKeyboardProc;
    myhookdata[HookKeyboardLl].nType = WH_KEYBOARD_LL;

    myhookdata[HookKeyboard].hkprc = KeyboardProc;
    myhookdata[HookKeyboard].nType = WH_KEYBOARD;

    for (size_t i = 0; i < _countof(myhookdata); i++)
    {
        myhookdata[i].hhook = SetWindowsHookEx(myhookdata[i].nType, myhookdata[i].hkprc, 0, 0);
        ASSERT(myhookdata[i].hhook != NULL);
    }
}