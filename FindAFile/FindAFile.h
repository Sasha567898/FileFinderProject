#pragma once
#include <vector>
#include <mutex>
#include <string>
#include <iostream>


std::vector<std::wstring> listDirectories(const std::wstring& directoryPath, std::vector<std::wstring>& directories);


void searchFileInDirectory(const std::wstring& directory, std::wstring fileNameToFind);



void workerThread();