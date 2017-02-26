// CleanupLocalisation.cpp : Defines the entry point for the console application.

#include "stdafx.h"

int main()
{
    std::unordered_map<std::wstring, std::unordered_set<std::string>> usedTags;

    std::vector<std::wstring> languages = {
        L"braz_por",
        L"english",
        L"french",
        L"german",
        L"polish",
        L"russian",
        L"spanish"
    };

    std::unordered_map<std::wstring, std::wregex> languageExps;
    for (std::wstring language : languages)
        languageExps[language] = std::wregex(language);

    std::vector<std::wstring> STNHFiles = {
        L"Output\\STH_event_l_<lang>.yml",
        L"Output\\STH_l_<lang>.yml"
    };

    std::regex keyExp("^ +(.+?):[0-9]+ +\"([^\\\"]*)\"");
    std::regex emptystringExp("^( +.+?:[0-9]+ +)\\\"\\\"$");
    std::wregex languageExp(L"<lang>");

    std::smatch matches;

    std::cout << " --- Loading Tags ---" << std::endl;

    for (std::wstring language : languages)
    {    
        for (std::wstring filenameTemplate : STNHFiles) 
        {            
            std::wstring filename = std::regex_replace(filenameTemplate, languageExp, language);

            std::ifstream file(filename);
        if (!file.is_open()) {
                std::wcout << "Skipped \"" << filename << "\"" << std::endl;
            continue;
        }
        std::string line;
        while (!file.eof()) {
            std::getline(file, line);
            if (std::regex_search(line, matches, keyExp, std::regex_constants::match_continuous)) {
                    if (matches[2] != "Description WIP")
                        usedTags[language].insert(matches[1]);
                    // else
                    //     std::cout << matches[0] << " ignored!" << std::endl;
            }
        }
        file.close();
            std::wcout << "Loaded " << filename << std::endl;
        }
    }
   
    WIN32_FIND_DATA data;
    HANDLE h = FindFirstFile(L"VanillaFiles\\*.*", &data);

    if (h != INVALID_HANDLE_VALUE) {
        std::cout << " --- Updating Files ---" << std::endl;
        do {
            if (!StrCmp(data.cFileName, _T(".")) || !StrCmp(data.cFileName, _T("..")))
                continue;

            std::wstring filename = _T("VanillaFiles\\") + std::wstring(data.cFileName);
            bool fileChanged = false;

            std::ifstream file(filename);
            std::vector<std::string> fileData;

            if (!file.is_open()) {
                std::wcout << "Error opening \"" << filename << "\"!" << std::endl;
                continue;
            }

            std::wstring language;
            for (const std::pair<std::wstring, std::wregex>& entry : languageExps)
                if (std::regex_search(filename, entry.second))
                    language = entry.first;

            std::string line;
            while (!file.eof()) {
                std::getline(file, line);
                if (std::regex_search(line, matches, keyExp, std::regex_constants::match_continuous)) {
                    if (usedTags[language].find(matches[1]) == usedTags[language].end()) {
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
                filename = _T("Output\\") + std::wstring(data.cFileName);
                std::ofstream outFile(filename);
                for (std::string line : fileData) 
                    outFile << std::regex_replace(line, emptystringExp, "$1\"\\n\"") << std::endl;
                outFile.close();
                std::wcout << "[UPDATED] \"" << filename << "\"" << std::endl;
            } else {
                std::wcout << "[ignored] \"" << filename << "\"" << std::endl;
            }
        } while (FindNextFile(h, &data));
    }
    else
        std::cout << "VanillaFiles folder missing!" << std::endl;

    FindClose(h);

    return 0;
}

