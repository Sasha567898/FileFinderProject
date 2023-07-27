#include <iostream>
#include "FindAFile.h"
std::vector<std::wstring> directories;

std::mutex printMutex;
std::wstring fileNameToFind;

void workerThread() {

    while (true) {
        std::wstring directory;

        {
            std::unique_lock<std::mutex> lock(printMutex);
            if (directories.empty()) {

                return;
            }

            directory = directories.back();
            directories.pop_back();
        }

        searchFileInDirectory(directory, fileNameToFind);
    }
}

int main()
{

  std::wstring directoryPath = L"C:\\";
  std::vector<std::wstring> directories1 = { L"C:\\" };
  directories = listDirectories(directoryPath, directories1);

    const int numThreads = 7;

    std::vector<std::thread> threads;

    std::wcout << "Enter the file name to search for: ";
    std::wcin >> fileNameToFind;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(workerThread);
    }


    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}

