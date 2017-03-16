//
//  History.cpp
//  TestGraphicSettings
//
//  Created by Volodymyr Dyachenko on 3/16/17.
//  Copyright © 2017 Volodymyr Dyachenko. All rights reserved.
//

#include "History.hpp"
#include "SettingsEditor.hpp"

#include <iostream>

History::HistoryEntry::HistoryEntry(const std::string& name, const std::string& prev, const std::string& newVal) :
    settingName(name), prevValue(prev), newValue(newVal)
{
}


History::History() :
    _Pointer(_History.end())
{
}

void History::add(const std::string& settingName, const std::string& prevValue, const std::string& newValue)
{
    if(!_History.empty() && _Pointer < _History.end() - 1)
    {
        _History.erase(_Pointer + 1, std::end(_History));
    }
    
    _History.emplace_back(settingName, prevValue, newValue);
    if(_History.size() == 1)
    {
        _Pointer = std::begin(_History);
    }
    else
    {
        ++_Pointer;
    }
}

void History::undo(SettingsEditor& editor)
{
    if(_History.empty() || _Pointer == _History.end())
        return;
 
    auto& settings = editor.getSettings();
    auto foundIt = settings.find(_Pointer->settingName);
    if(foundIt == settings.end())
    {
        std::cerr << "Internal Error";
        return;
    }
    
    foundIt->second.change(editor, _Pointer->prevValue);

    if(_Pointer == std::begin(_History))
    {
        _Pointer = std::end(_History);
    }
    else
    {
        --_Pointer;
    }
}

void History::redo(SettingsEditor& editor)
{
    if(_History.empty() || _Pointer == _History.end() - 1)
        return;

    if(_Pointer == std::end(_History))
    {
        _Pointer = std::begin(_History);
    }
    else
    {
        ++_Pointer;
    }

    auto& settings = editor.getSettings();
    
    auto foundIt = settings.find(_Pointer->settingName);
    if(foundIt == settings.end())
    {
        std::cerr << "Internal Error";
        return;
    }
    
    foundIt->second.change(editor, _Pointer->newValue);
}

void History::testPrint()
{
    for(auto it = std::begin(_History); it != std::end(_History); ++it)
    {
        std::cout << it->settingName << " from " << it->prevValue << " to " << it->newValue;
        if(it == _Pointer)
        {
            std::cout << " <---";
        }
        std::cout << std::endl;
    }
}
