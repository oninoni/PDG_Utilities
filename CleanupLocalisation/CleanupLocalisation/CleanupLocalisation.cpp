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

    std::wstring deutschKorrektur = L"deutschkorrektur_l_german.yml";

    std::vector<std::wstring> STNHFiles = {
        L"Output\\localisation\\<lang>\\STH_events_l_<lang>.yml",
        L"Output\\localisation\\<lang>\\STH_l_<lang>.yml"
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
                    //if (matches[2] != "Description WIP") {
                        usedTags[language].insert(matches[1]);
                    //}
                    //else
                        //std::cout << matches[0] << " ignored! | " << matches[2] << std::endl;
                }
            }
            file.close();
            std::wcout << "Loaded " << filename << std::endl;
        }
    }
   
    std::cout << " --- Checking Deutschkorrektur ---" << std::endl;

    std::ifstream germanCorrection(L"Input\\" + deutschKorrektur);
    std::ofstream germanCorrectionOut(L"Output\\localisation\\german\\" + deutschKorrektur);

    if (germanCorrection.is_open() && germanCorrectionOut.is_open()) {
        std::string line;
        while (!germanCorrection.eof()) {
            std::getline(germanCorrection, line);
            if (std::regex_search(line, matches, keyExp, std::regex_constants::match_continuous)) {
                if (usedTags[L"german"].find(matches[1]) == usedTags[L"german"].end()) {
                    germanCorrectionOut << line << std::endl;
                    usedTags[L"german"].insert(matches[1]);
                }
                else {
                    std::cout << " !!! Warning found overlap with \"Deutschkorrektur\" at: " << matches[1] << "! line is not copied to output!" << std::endl;
                }
            }
            else {
                germanCorrectionOut << line << std::endl;
            }
        }
    }
    else {
        std::wcout << "Skipped \"" << deutschKorrektur << "\"" << std::endl;
    }

    germanCorrection.close();
    germanCorrectionOut.close();

    WIN32_FIND_DATA folderData;
    HANDLE folderH = FindFirstFile(L"VanillaFiles\\*.*", &folderData);
    if (folderH != INVALID_HANDLE_VALUE) {
        std::cout << " --- Updating Files ---" << std::endl;
        do {
            if (!StrCmp(folderData.cFileName, _T(".")) || !StrCmp(folderData.cFileName, _T("..")))
                continue;
            
            // Old Code

            WIN32_FIND_DATA data;
            std::wstring folderToSearch = (L"VanillaFiles\\" + std::wstring(folderData.cFileName) + L"\\");
            HANDLE h = FindFirstFile((folderToSearch + L"*.*").c_str(), &data);

            if (h != INVALID_HANDLE_VALUE) {
                do {
                    if (!StrCmp(data.cFileName, _T(".")) || !StrCmp(data.cFileName, _T("..")))
                        continue;

                    std::wstring filename = folderToSearch + std::wstring(data.cFileName);
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
                            } 
                            else {
                                //std::cout << "Ignoring " << matches[1] << std::endl;
                                fileChanged = true;
                            }
                        }
                        else {
                            fileData.push_back(line);
                        }
                    }

                    file.close();

                    std::wstring folderToExport = (L"Output\\localisation\\" + std::wstring(folderData.cFileName) + L"\\");
                    if (fileChanged) {
                        filename = folderToExport + std::wstring(data.cFileName);
                        std::ofstream outFile(filename);
                        for (std::string line : fileData)
                            outFile << std::regex_replace(line, emptystringExp, "$1\"\\n\"") << std::endl;
                        outFile.close();
                        std::wcout << "[UPDATED] \"" << filename << "\"" << std::endl;
                    }
                    else {
                        //std::wcout << "[ignored] \"" << filename << "\"" << std::endl;
                    }
                } while (FindNextFile(h, &data));
            }

            FindClose(h);

            // End of Old Code

        } while (FindNextFile(folderH, &folderData));

        FindClose(folderH);
    }else {
        std::cout << "VanillaFiles folder missing!" << std::endl;
    }

    

    return 0;
}

