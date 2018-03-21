#include "Logger.h"

TLogger::TLogger()
{
    this->errorState = 0;
}

TLogger::TLogger(string LogDirectory, string LogFileName)
{
    if(!this->Created)
    {
        this->LogDirectory = LogDirectory;
        this->LogFileName = LogFileName;
        string str = LogDirectory + LogFileName;
        this->LogFile.open(str.c_str(), std::fstream::out | std::fstream::trunc);
        if(this->LogFile.is_open() != true)
        {
            this->errorState = 2;
        }
        else
        {
            this->errorState = 1;
            this->Created = true;
            this->t = GetTime();
        }
    }
}

TLogger::TLogger(string LogDirectory, string LogFileName, string LogTableName)
{
    if(!this->Created)
    {
        this->LogDirectory = LogDirectory;
        this->LogFileName = LogFileName;
        this->LogTableName = LogTableName;
        string str = LogDirectory + LogFileName;
        this->LogFile.open(str.c_str(), std::fstream::out | std::fstream::trunc);
        if(this->LogFile.is_open() != true)
        {
            this->errorState = 2;
        }
        else
        {
            this->errorState = 1;
            this->Created = true;

            str = LogDirectory + LogTableName;
            this->LogTable.open(str.c_str(), std::fstream::out | std::fstream::trunc);
            if(this->LogTable.is_open() != true)
            {
                this->errorState = 3;
            }
            else
            {
                this->TableCreated = true;
                this->LogTable << "Time from last; Time from start; Type; Message" << std::endl;
            }
            this->t = GetTime();
        }
    }
}

TLogger::~TLogger()
{
    if(this->LogFile.is_open())
        this->LogFile.close();
}

void TLogger::CreateLog(void)
{
    if(!this->Created)
    {
        this->LogDirectory = LogDirectory;
        this->LogFileName = LogFileName;
        this->LogTableName = LogTableName;
        string str = LogDirectory + LogFileName;
        this->LogFile.open(str.c_str(), std::fstream::out | std::fstream::trunc);
        if(this->LogFile.is_open() != true)
        {
            this->errorState = 2;
        }
        else
        {
            this->errorState = 1;
            this->Created = true;

            if(!LogTableName.empty())
            {
                str = LogDirectory + LogTableName;
                this->LogTable.open(str.c_str(), std::fstream::out | std::fstream::trunc);
                if(this->LogTable.is_open() != true)
                {
                    this->errorState = 3;
                }
                else
                {
                    this->TableCreated = true;
                    this->LogTable << "Time from last; Time from start; Type; Message\n";
                }
            }
            this->t = GetTime();
        }
    }
}

void TLogger::LogAddItem(int type, string text)
{
    string prefix;
    switch (type){
        case 1:
        {
            prefix = "[Info]";
            break;
        }
        case 2:
        {
            prefix = "[Exception]";
            break;
        }
        case 3:
        {
            prefix = "[Collision]";
            break;
        }
        case 4:
        {
            prefix = "[Polygon]";
            break;
        }
        case 5:
        {
            prefix = "[Minkowski_Set]";
            break;
        }
        default:
        {
            prefix = "[]";
        }
    }
    this->LogQueue.insert(this->LogQueue.end(), logqueue(prefix, text));
}

void TLogger::PrintOut(void)
{
    if(this->Created)
    {
        if(this->LogQueue.size() > 0)
        {
            float startTime = GetTime();
            float passedTime = startTime - this->t;
            this->t = GetTime();

            this->LogFile << "Next: " << to_string(passedTime / TIME_ONE_SECOND) << "s after previous action || " << to_string(t / TIME_ONE_SECOND) << "s passed since the start" << std::endl;
            for(unsigned int i = 0; i < this->LogQueue.size(); i++)
            this->LogFile << this->LogQueue[i].prefix << " " << this->LogQueue[i].text << std::endl;
            this->LogFile << "------" << std::endl;

            if(this->TableCreated)
            {
                for(unsigned int i = 0; i < this->LogQueue.size(); i++)
                    this->LogTable << to_string(passedTime / TIME_ONE_SECOND) << ";" << to_string(t / TIME_ONE_SECOND) << ";" << this->LogQueue[i].prefix << ";" << this->LogQueue[i].text << std::endl;
            }
            this->LogQueue.clear();
        }
    }
}
