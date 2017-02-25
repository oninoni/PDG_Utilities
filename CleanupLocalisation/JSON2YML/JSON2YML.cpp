// JSON2YML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <Windows.h>

void setCursorVisible(bool visible)
{
    CONSOLE_CURSOR_INFO cursorinfo;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(handle, &cursorinfo);
    if (!cursorinfo.bVisible == visible)
    {
        cursorinfo.bVisible = visible;
        SetConsoleCursorInfo(handle, &cursorinfo);
    }
}

int main()
{
    WCHAR* test = L"hallo";
    std::string(test);

    setCursorVisible(false);          

    std::regex translationExp("\"[^(]+\\(([^)]+)\\)\" *: *\"( *[^:]+:0 *[^]*)\"");
    std::regex escapeExp("\\\\([^])");

    std::unordered_map<std::string, std::vector<std::string>> translations;

    std::smatch matches;

    std::ifstream inputfile("NewHorizons - Localization.json");

    if (!inputfile.is_open())
    {
        std::cout << "Could not find file!" << std::endl;
        return 0;
    }
      
    inputfile.seekg(0, std::ios::end);
    int64_t size = inputfile.tellg();
    inputfile.seekg(0, std::ios::beg);
    int64_t modvalue = size / 100;
    int64_t counter = 0;

    while (!inputfile.eof())
    {
        while (counter <= 0)
        {
            std::cout << "\rLoading: " << inputfile.tellg() * 100 / size << "%";
            counter += modvalue;
        }
        std::string line;
        std::getline(inputfile, line);
        counter -= line.size();

        if (std::regex_search(line, matches, translationExp))
        {
            std::string text = std::regex_replace(matches[2].str(), escapeExp, "$1");
            translations[matches[1]].push_back(text);
        }
    }   
    std::cout << "\rLoading: 100%" << std::endl;
    inputfile.close();   

    return 0;
}

