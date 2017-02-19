#pragma once
#include <Windows.h>

HHOOK msgFilterHook = NULL;

//////////////////////////////////////////////////////////////////////////
// This hook proc is used by WH_MSGFILTER and WHSYSMSGFILTER hooks. Allows to monitor messages which
// are about to be processed by a menu, scrollbar, message box or dialog box and to detect when a different
// window is about to be activated as the result of ALT+TAB or ALT+ESC keys. 
// WH_MSGFILTER - monitors messages passed to application which installed this hook.
// WH_SYSMSGFILTER - monitors messages systemwide for all apps.
// App can preview messages using PeekMessage and GetMessage functions before passing them into DispatchMessage
// function. During modal loop system dispatches messages wihtout allowing an application the chance to filter the
// messages in its main message loop. If an app installs WH_MSGFILTER or WH_SYSMSGFILTER - the system calls the proc
// during the modal loop.
// App can call this hook proc directly by calling CallMsgFilter func between calls into GetMessage and DispatchMessage.
// while (GetMessage(&msg, (HWND) NULL, 0, 0)) 
// {
//      if (!CallMsgFilter(&qmsg, 0))
//      DispatchMessage(&qmsg);
// }
// The last argument passed to the hook procedure. The hook proc can determine where the procedure was called from by defining 
// a constance MSGF_MAINLOOP.
// This function processes the messages forwarded to:
// - menu
// - scrollbar
// - message box
// - dialog box
// - when another window is about to be activated by ALT+TAB or ALT+ESC
// If the app should process this value - return value is 0, otherwise is non 0.
//////////////////////////////////////////////////////////////////////////

#ifndef MSGF_MAINLOOP
#define MSGF_MAINLOOP 456
#else 
#error MSGF already defined.
#endif

LRESULT CALLBACK MessageProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode < 0)  // do not process message 
        return CallNextHookEx(msgFilterHook, nCode, wParam, lParam);
    switch (nCode)
    {
    case MSGF_MAINLOOP:
        break;
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

    }

    return CallNextHookEx(msgFilterHook, nCode, wParam, lParam);
}

