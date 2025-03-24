#include "program_info.hpp"
#include <iostream>
#include <stdio.h>
#include <locale>
#include <string>
#include <vector>
#include <format>
#include <unistd.h>

#ifdef _WIN32 
#include <windows.h> 
#include <tlhelp32.h>
#endif

using std::cout;
using std::cerr;
using std::string;
using std::vector;

#define TEMPSTR_LENGTH 2048
#define TEMPWSTR_LENGTH 2048

char cwd[2048];
char path_delimeter = '\\';
char program_name[2048];
char program_name_noext[2048];
char program_working_dir[2048];
char internal_program_name[2048] = {INTERNAL_PROGRAM_NAME};
wchar_t internal_program_name_wstr[2048] = {TEXT(INTERNAL_PROGRAM_NAME)};


vector<DWORD> GetProcessIds(const string& processName);
bool InjectDLL(DWORD processId, const string& dllPath);


int main(int argc, char **argv) {
    #ifdef _WIN32 
    HWND hwnd = GetConsoleWindow();
    SetConsoleOutputCP(CP_UTF8); 
    #endif
    setlocale(LC_ALL, "C.UTF-8");
    printf("%s\n\n", PROGRAM_INFO_STRING);

    char *p1 = NULL;
    char tempstr1[TEMPSTR_LENGTH];
    wchar_t tempwstr1[TEMPWSTR_LENGTH];
    wchar_t *pw1 = NULL, 
            *pw2 = NULL;

    string GameExecutableName = "Game.exe";
    vector<string> dlls = {
        "openvr_api.dll",
        "LuaVR.dll",
        "UEVRBackend.dll"
    };
    DWORD processId;


    printf("cmd=%s\n", argv[0]);
    

    // 获取程序文件名和程序所在目录。
    p1 = strrchr(argv[0], path_delimeter);
    if( p1 == NULL ){
        strcpy(program_name, argv[0]);
        sprintf(program_working_dir, ".\\");
    }
    else {
        strcpy(program_name, p1+1);
        strncpy(program_working_dir, argv[0], p1-argv[0]);
        program_working_dir[p1-argv[0]] = 0;
    }
    printf("program_name=%s\n", program_name);
    strcpy(tempstr1, program_working_dir);
    p1 = _fullpath(program_working_dir, tempstr1, 2048);
    if( p1 == NULL ){
        swprintf(tempwstr1, TEMPWSTR_LENGTH, L"错误：pwd绝对路径推算失败。");
        printf("%ls\n", tempwstr1);
        MessageBox(hwnd, (tempwstr1), (internal_program_name_wstr), MB_OK);
        return 0;
    }
    printf("program_working_dir=%s\n", program_working_dir);


    // 获取当前工作目录
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        strcpy(tempstr1, cwd);
        p1 = _fullpath(cwd, tempstr1, 2048);
        if( p1 == NULL ){
            swprintf(tempwstr1, TEMPWSTR_LENGTH, L"错误：cwd绝对路径推算失败。");
            printf("%ls\n", tempwstr1);
            MessageBox(hwnd, (tempwstr1), (internal_program_name_wstr), MB_OK);
            return 0;
        }
        printf("Current working directory=%s\n", cwd);
    } else {
        swprintf(tempwstr1, TEMPWSTR_LENGTH, L"错误：无法获取当前工作目录。");
        printf("%ls\n", tempwstr1);
        MessageBox(hwnd, (tempwstr1), (internal_program_name_wstr), MB_OK);
        return 0;
    }


    // 比较程序目录和当前工作目录
    if( strcmp(cwd, program_working_dir) ){
        printf("cwd != pwd\n");
        // 改变当前工作目录
        if (chdir(program_working_dir) == 0) {
            printf("Successfully changed directory to %s\n", program_working_dir);
        } else {
            swprintf(tempwstr1, TEMPWSTR_LENGTH, L"错误：无法更换当前工作目录到程序所在目录。");
            printf("%ls\n", tempwstr1);
            MessageBox(hwnd, (tempwstr1), (internal_program_name_wstr), MB_OK);
            return 0;
        } 
    }

    cout << format("Waiting for game process ({}) to start...\n", GameExecutableName);

    while (true) {
        std::vector<DWORD> processIds = GetProcessIds(GameExecutableName);

        if (!processIds.empty()) {
            for (DWORD processId : processIds) {

                for (const string& dll : dlls) {
                    string dllPath = format("{}\\{}", program_working_dir, dll);

                    if (access(dllPath.c_str(), F_OK)) {
                        if (InjectDLL(processId, dllPath)) {
                            cout << format("Successfully injected {} into process {} (pid: {}).\n", dll, GameExecutableName, processId);
                        }
                        else {
                            cerr << format("Failed to inject {} into process {} (pid: {}).\n", dll, GameExecutableName, processId);
                        }
                    }
                    else {
                        cerr << format("Skipping injection, DLL not found: {} (pid: {}).\n", dllPath, processId);
                    }
                }

            }
            break;
        }

        Sleep(10);
    }

    return 0;
}


wchar_t *convertCharToWChar(const char *message) {
    // 将 char 字符串转换为 wchar_t 字符串
    int len = MultiByteToWideChar(CP_UTF8, 0, message, -1, NULL, 0);
    wchar_t *wMessage = (wchar_t *)malloc(len * sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, message, -1, wMessage, len);
    return wMessage;
}


vector<DWORD> GetProcessIds(const string& processName) {
    vector<DWORD> processIds;
    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        printf("Failed to create process snapshot.\n");
        return processIds;
    }

    wchar_t *processName_w = convertCharToWChar(processName.c_str());
    std::wstring processName_wstr(processName_w, 0);

    if (Process32First(snapshot, &processEntry)) {
        do {
            if (processName_wstr == processEntry.szExeFile) {
                processIds.push_back(processEntry.th32ProcessID);
            }
        } while (Process32Next(snapshot, &processEntry));
    }

    free(processName_w);
    processName_w = nullptr;

    CloseHandle(snapshot);
    return processIds;
}


bool InjectDLL(DWORD processId, const string& dllPath) {
    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    if (!process) {
        cout << format("Failed to open process: {}\n", std::to_string(processId));
        return false;
    }

    LPVOID allocMem = VirtualAllocEx(process, nullptr, dllPath.size() * sizeof(wchar_t), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (!allocMem) {
        CloseHandle(process);
        cout << format("Failed to allocate memory in process: {}\n", std::to_string(processId));
        return false;
    }

    if (!WriteProcessMemory(process, allocMem, dllPath.c_str(), dllPath.size() * sizeof(wchar_t), nullptr)) {
        VirtualFreeEx(process, allocMem, 0, MEM_RELEASE);
        CloseHandle(process);
        cout << format("Failed to write memory in process: {}\n", std::to_string(processId));
        return false;
    }

    HANDLE thread = CreateRemoteThread(process, nullptr, 0, (LPTHREAD_START_ROUTINE)LoadLibraryW, allocMem, 0, nullptr);
    if (!thread) {
        VirtualFreeEx(process, allocMem, 0, MEM_RELEASE);
        CloseHandle(process);
        cout << format("Failed to create remote thread in process: {}\n", std::to_string(processId));
        return false;
    }

    WaitForSingleObject(thread, INFINITE);
    VirtualFreeEx(process, allocMem, 0, MEM_RELEASE);
    CloseHandle(thread);
    CloseHandle(process);

    cout << format("DLL injected successfully: {} into process {}\n", dllPath, std::to_string(processId));
    return true;
}
