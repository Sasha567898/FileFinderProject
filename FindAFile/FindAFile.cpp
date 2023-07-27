#include "FindAFile.h"
#include <string>
#include <thread>
#include <condition_variable>
#include <windows.h>


using namespace std;

std::atomic<bool> fileFound(false);


std::vector<std::wstring> listDirectories(const std::wstring& directoryPath, vector<wstring>& directories) {
    std::wstring searchPath = directoryPath + L"\\*";

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(searchPath.c_str(), &findFileData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (wcscmp(findFileData.cFileName, L".") != 0 && wcscmp(findFileData.cFileName, L"..") != 0) {
                if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {

                    directories.push_back(L"C:\\" + std::wstring(findFileData.cFileName));
                }

            }
        } while (FindNextFile(hFind, &findFileData) != 0);

        FindClose(hFind);
    }
    else {
        std::wcerr << "Error finding files and directories in directory: " << directoryPath << std::endl;
    }
    return directories;
}


void searchFileInDirectory(const std::wstring& directory, std::wstring fileNameToFind) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((directory + L"\\*").c_str(), &findFileData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            std::wstring fileName = findFileData.cFileName;

            if (fileName != L"." && fileName != L"..") {
                if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {

                    searchFileInDirectory(directory + L"\\" + fileName, fileNameToFind);
                }
                else if (fileName == fileNameToFind) {
                    std::wcout << "File found in " << directory << L"\\" << fileName << std::endl;
                    fileFound = true;
                    return;
                }
            }
        } while (!fileFound && FindNextFile(hFind, &findFileData) != 0);

        FindClose(hFind);
    }
}




