// CleanupLocalisation.cpp : Defines the entry point for the console application.

#include "stdafx.h"

int main()
{
    std::unordered_set<std::string> usedTags;

    std::vector<std::string> STNHFiles = {
        "Output\\STH_event_l_english.yml",
        "Output\\STH_l_english.yml"
    };

    std::regex keyExp("^ +(.+?):[0-9]+");
    std::regex emptystringExp("^( +.+?:[0-9]+ +)\\\"\\\"$");
    std::smatch matches;

    std::cout << " --- Loading Tags ---" << std::endl;

    for (std::string fileName : STNHFiles) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cout << "Error opening \"" << fileName << "\"!! :(" << std::endl;
            continue;
        }
        std::string line;
        while (!file.eof()) {
            std::getline(file, line);
            if (std::regex_search(line, matches, keyExp, std::regex_constants::match_continuous)) {
                usedTags.insert(matches[1]);
            }
        }
        file.close();
        std::cout << "Loaded " << fileName << std::endl;
    }
   
    WIN32_FIND_DATA data;
    HANDLE h = FindFirstFile(L"VanillaFiles\\*.*", &data);

    if (h != INVALID_HANDLE_VALUE) {
        std::cout << " --- Updating Files ---" << std::endl;
        do {
            if (!StrCmp(data.cFileName, _T(".")) || !StrCmp(data.cFileName, _T("..")))
                continue;

            std::wstring fileName = _T("VanillaFiles\\") + std::wstring(data.cFileName);
            bool fileChanged = false;

            std::ifstream file(fileName);
            std::vector<std::string> fileData;

            if (!file.is_open()) {
                std::wcout << "Error opening \"" << fileName << "\"!" << std::endl;
                continue;
            }

            std::string line;
            while (!file.eof()) {
                std::getline(file, line);
                if (std::regex_search(line, matches, keyExp, std::regex_constants::match_continuous)) {
                    if (usedTags.find(matches[1]) == usedTags.end()) {
                        fileData.push_back(line);
                    } else {
                        //std::cout << "Ignoring " << matches[1] << std::endl;
                        fileChanged = true;
                    }
                } else {
                    fileData.push_back(line);
                }
            }

            file.close();

            if (fileChanged) {
                fileName = _T("Output\\") + std::wstring(data.cFileName);
                std::ofstream outFile(fileName);
                for (std::string line : fileData)
                    outFile << std::regex_replace(line, emptystringExp, "$1\"\\n\"") << std::endl;
                outFile.close();
                std::wcout << "[UPDATED] \"" << fileName << "\"" << std::endl;
            } else {
                std::wcout << "[ignored] \"" << fileName << "\"" << std::endl;
            }
        } while (FindNextFile(h, &data));
    }
    else
        std::cout << "VanillaFiles folder missing!" << std::endl;

    FindClose(h);

    return 0;
}

