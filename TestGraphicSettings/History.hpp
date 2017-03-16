//
//  History.hpp
//  TestGraphicSettings
//
//  Created by Volodymyr Dyachenko on 3/16/17.
//  Copyright © 2017 Volodymyr Dyachenko. All rights reserved.
//

#ifndef History_hpp
#define History_hpp

#include "History.hpp"
#include "Setting.hpp"

#include <deque>
#include <string>

class History
{
public:
    History();
    
    void add(const std::string& settingName, const std::string& prevValue, const std::string& newValue);
    
    void undo(SettingsEditor& editor);
    void redo(SettingsEditor& editor);
    
    void testPrint();

private:
    struct HistoryEntry
    {
        std::string settingName;
        std::string prevValue;
        std::string newValue;
        
        HistoryEntry(const std::string& name, const std::string& prev, const std::string& newVal);
        
    };
    
    std::deque<HistoryEntry> _History;
    std::deque<HistoryEntry>::iterator _Pointer;
    
};
#endif /* History_hpp */
