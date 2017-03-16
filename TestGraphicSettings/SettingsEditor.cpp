//
//  SettingsEditor.cpp
//  TestGraphicSettings
//
//  Created by Volodymyr Dyachenko on 3/15/17.
//  Copyright © 2017 Volodymyr Dyachenko. All rights reserved.
//

#include <iostream>
#include <regex>
#include <functional>
#include <map>
#include <memory>

#include "SettingsEditor.hpp"
#include "XMLSerializer.hpp"
#include "SettingsDb.hpp"

using std::placeholders::_1;

SettingsEditor::SettingsEditor() :
    _LineCommands
    {
        {"change", LineCommandEntry(2, std::bind(&SettingsEditor::execChange, this, _1))},
        {"get", LineCommandEntry(1, std::bind(&SettingsEditor::execGet, this, _1))},
        {"print", LineCommandEntry(0, std::bind(&SettingsEditor::execPrint, this, _1))},
        {"format", LineCommandEntry(1, std::bind(&SettingsEditor::execFormat, this, _1))},
        {"save", LineCommandEntry(1, std::bind(&SettingsEditor::execSave, this, _1))},
        {"exit", LineCommandEntry(0, std::bind(&SettingsEditor::execExit, this, _1))},
        {"undo",  LineCommandEntry(0, std::bind(&SettingsEditor::execUndo, this, _1))},
        {"redo",  LineCommandEntry(0, std::bind(&SettingsEditor::execRedo, this, _1))},
        // For debugging reason
        {"history",  LineCommandEntry(0, std::bind(&SettingsEditor::execHistory, this, _1))}
    }
{
    createDefault();
}

int SettingsEditor::mainLoop()
{
    while(!_ExitFlag)
    {
        std::string line;
        std::getline(std::cin, line);
        
        auto words = parseLine(line);
        processCommand(words);
    }
    return 0;
}

StrVector SettingsEditor::parseLine(const std::string& line) const
{
    std::regex word(R"--([^ ^\t]+)--");
    std::smatch m;
    std::string str = line;
    
    StrVector res;
    
    
    while (std::regex_search (str, m, word))
    {
        for (auto& x : m)
        {
            res.push_back(x);
        }
        str = m.suffix().str();
    }

    return res;
}

void SettingsEditor::processCommand(const StrVector& words)
{
    if(words.empty())
    {
        //empty input. Do nothing
        return;
    }
    
    std::string command;
    std::transform(std::begin(words[0]), std::end(words[0]), std::back_inserter(command), ::tolower);

    auto entry = _LineCommands.find(command);
    if(entry == _LineCommands.end())
    {
        std::cerr << "Command not found" << std::endl;
        return;
    }
    
    if(words.size() != entry->second.argsCount + 1)
    {
        std::cerr << "Wrong arguments count" << std::endl;
        return;
    }
    
    entry->second.handler(StrVector(std::begin(words)+1, std::end(words)));
}

void SettingsEditor::createDefault()
{
    _Settings.clear();
    for(const auto& si : settingsDb)
    {
        _Settings.insert(std::make_pair(si.first, Setting(si.second, si.second.defaultValue)));
    }
}

namespace  {
    Setting* findSetting(SettingsEditor& editor, const std::string& name)
    {
        auto& settings = editor.getSettings();
        auto foundIt = settings.find(name);
        if(foundIt == settings.end())
        {
            std::cerr << "setting " << name << " not exists" << std::endl;
            return nullptr;
        }
        return &foundIt->second;
    }
}

bool SettingsEditor::changeSetting(const std::string& name, const std::string& value)
{
    auto setting = findSetting(*this, name);
    if(setting == nullptr)
        return false;
    
    auto oldValue = setting->_Value;
    
    if(setting->change(*this, value))
    {
        _History.add(name, oldValue, setting->_Value );
        return true;
    }
    
    return false;
}


// Handlers

void SettingsEditor::execChange(const StrVector& args)
{
    if(changeSetting(args[0], args[1]))
    {
        std::cout << args[0] << " = " << args[1] << std::endl;
    }
}

void SettingsEditor::execGet(const StrVector& args)
{
    auto setting = findSetting(*this, args[0]);
    if(setting == nullptr)
        return;
    
    std::cout << args[0] << " = " << setting->_Value << std::endl;
}

void SettingsEditor::execPrint(const StrVector& args)
{
    for(auto& pair : _Settings)
    {
        std::cout << pair.first << " = " << pair.second._Value << std::endl;
    }
}

void SettingsEditor::execFormat(const StrVector& args)
{
    // enum Format to string
    static const StrVector formats = { "bin", "xml" };
    
    auto foundIt = std::find(std::begin(formats), std::end(formats), args[0]);
    if( foundIt == std::end(formats))
    {
        std::cerr << args[0] << ": Wrong format" << std::endl;
        return;
    }
    auto index = std::distance(std::begin(formats), foundIt);
    _Format = static_cast<SettingsEditor::Format>(index);
}

void SettingsEditor::execSave(const StrVector& args)
{
    std::unique_ptr<BaseSerializer> serializer;
    
    if(_Format == SettingsEditor::XML)
    {
        serializer.reset(new XMLSerializer());
    }
    else
    {
        // Binary serializer not implemented
    }
    if(serializer)
    {
        serializer->serialize(_Settings, args[0]);
    }
}

void SettingsEditor::execExit(const StrVector& args)
{
    exit();
}

void SettingsEditor::execUndo(const StrVector& args)
{
    _History.undo(*this);
}

void SettingsEditor::execRedo(const StrVector& args)
{
    _History.redo(*this);
}

void SettingsEditor::execHistory(const StrVector& args)
{
    _History.testPrint();
}
