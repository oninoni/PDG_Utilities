// CleanupLocalisation.cpp : Defines the entry point for the console application.
//

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
            char*   nPtr = new char[lstrlen(data.cFileName) + 1];
            for (int i = 0; i < lstrlen(data.cFileName); i++)
                nPtr[i] = char(data.cFileName[i]);

            nPtr[lstrlen(data.cFileName)] = '\0';

            std::string fileName = "VanillaFiles\\" + std::string(nPtr);
            bool fileShouldOutput = false;

            std::cout << "Loading " << fileName << std::endl;
            std::ifstream file(fileName);
            std::vector<std::string> fileData;

            if (!file.is_open()) {
                std::cout << "Error opening \"" << fileName << "\"!! :(" << std::endl;
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
            std::cout << "Loaded " << fileName << std::endl;


            if (fileShouldOutput) {
                fileName = "Output\\" + std::string(nPtr);
                std::ofstream outFile(fileName);
                for (std::string line : fileData) {
                    outFile << line << std::endl;
                }
                outFile.close();
                std::cout << "Saved " << fileName << std::endl;
            } else {
                std::cout << "Not writing \"" << fileName << "\", because it's not used." << std::endl;
            }
        } while (FindNextFile(h, &data));
    }
    else
        std::cout << "Error: No such folder." << std::endl;

    FindClose(h);

    return 0;
}

