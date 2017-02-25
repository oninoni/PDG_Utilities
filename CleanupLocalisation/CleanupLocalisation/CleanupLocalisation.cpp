// CleanupLocalisation.cpp : Defines the entry point for the console application.

#include "stdafx.h"

int main()
{
    std::unordered_set<std::string> usedTags;

    std::vector<std::string> STNHFiles = {
        "Output\\STH_event_l_english.yml",
        "Output\\STH_tech_and_components_l_english.yml",
        "Output\\STH_text_l_english.yml"
    };

    std::regex regexer(" +(.+?):0");
    std::smatch matches;

    for (std::string fileName : STNHFiles) {
        std::cout << "Loading " << fileName << std::endl;
        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cout << "Error opening \"" << fileName << "\"!! :(" << std::endl;
            continue;
        }
        std::string line;
        while (!file.eof()) {
            std::getline(file, line);
            if (std::regex_search(line, matches, regexer, std::regex_constants::match_continuous)) {
                usedTags.insert(matches[1]);
            }
        }
        file.close();
        std::cout << "Loaded " << fileName << std::endl;
    }
    
    WIN32_FIND_DATA data;
    HANDLE h = FindFirstFile(L"VanillaFiles\\*.*", &data);

    if (h != INVALID_HANDLE_VALUE) {
        do {
            std::wstring fileName = _T("VanillaFiles\\") + std::wstring(data.cFileName);
            bool fileShouldOutput = false;

            std::wcout << "Loading " << fileName << std::endl;
            std::ifstream file(fileName);
            std::vector<std::string> fileData;

            if (!file.is_open()) {
                std::wcout << "Error opening \"" << fileName << "\"!! :(" << std::endl;
                continue;
            }

            std::string line;
            while (!file.eof()) {
                std::getline(file, line);
                if (std::regex_search(line, matches, regexer, std::regex_constants::match_continuous)) {
                    if (usedTags.find(matches[1]) == usedTags.end()) {
                        fileData.push_back(line);
                    } else {
                        std::cout << "Ignoring " << matches[1] << std::endl;
                        fileShouldOutput = true;
                    }
                } else {
                    fileData.push_back(line);
                }
            }

            file.close();
            std::wcout << "Loaded " << fileName << std::endl;

            if (fileShouldOutput) {
                fileName = _T("Output\\") + std::wstring(data.cFileName);
                std::ofstream outFile(fileName);
                for (std::string line : fileData) {
                    outFile << line << std::endl;
                }
                outFile.close();
                std::wcout << "Saved " << fileName << std::endl;
            } else {
                std::wcout << "Not writing \"" << fileName << "\", because it's not used." << std::endl;
            }
        } while (FindNextFile(h, &data));
    }
    else
        std::cout << "Error: No such folder." << std::endl;

    FindClose(h);

    return 0;
}

