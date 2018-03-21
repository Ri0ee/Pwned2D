#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "ETime.h"
#include "..\Game\Utility.h"

using std::string;

struct logqueue{
    public:
        string prefix;
        string text;
        logqueue();
        logqueue(string pref, string txt)
        {
            prefix = pref;
            text = txt;
        }
};

class TLogger
{
    public:
        TLogger();
        TLogger(string LogDirectory, string LogFileName);
        TLogger(string LogDirectory, string LogFileName, string LogTableName);
        virtual ~TLogger();

        void CreateLog(void);
        void PrintOut(void);
        void LogAddItem(int type, string text);

        std::vector<logqueue> LogQueue;
        std::fstream LogFile;
        std::fstream LogTable;

        string LogDirectory;
        string LogFileName;
        string LogTableName;
        int errorState;
        bool Created;
        bool TableCreated;
        float t;
};
