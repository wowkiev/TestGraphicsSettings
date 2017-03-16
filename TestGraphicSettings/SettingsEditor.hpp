//
//  SettingsEditor.hpp
//  TestGraphicSettings
//
//  Created by Volodymyr Dyachenko on 3/15/17.
//  Copyright © 2017 Volodymyr Dyachenko. All rights reserved.
//

#ifndef SettingsEditor_hpp
#define SettingsEditor_hpp

#include "Common.hpp"
#include "Setting.hpp"
#include "History.hpp"

class SettingsEditor
{
public:
    enum Format
    {
        BINARY, XML
    };
    
public:
    SettingsEditor();
    
    int mainLoop();
    void exit() { _ExitFlag = true; }
    
    void setFormat(Format format) { _Format = format; }
    Format getFormat() const { return _Format; }
    
    SettingsMap& getSettings() { return _Settings; }
    
    bool changeSetting(const std::string& name, const std::string& value);
private:
    typedef std::function<void(const StrVector&)> HandlerFunc;

    struct LineCommandEntry
    {
        LineCommandEntry(int ac, const HandlerFunc& h) :
        argsCount(ac), handler(h)
        {
        }
        
        int argsCount;
        HandlerFunc handler;
    };

    
    bool _ExitFlag = false;
    Format _Format = Format::XML;
    
    SettingsMap _Settings;
    History _History;
    
    const std::map<std::string, LineCommandEntry> _LineCommands;
    
private:
    StrVector parseLine(const std::string& line) const;
    void processCommand(const StrVector& words);

    void createDefault();
    
    //Handlers
    void execChange(const StrVector& args);
    void execGet(const StrVector& args);
    void execPrint(const StrVector& args);
    void execFormat(const StrVector& args);
    void execSave(const StrVector& args);
    void execExit(const StrVector& args);
    void execUndo(const StrVector& args);
    void execRedo(const StrVector& args);
    void execHistory(const StrVector& args);
};


#endif /* SettingsEditor_hpp */
