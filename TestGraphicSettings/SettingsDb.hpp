//
//  SettingsDb.hpp
//  TestGraphicSettings
//
//  Created by Volodymyr Dyachenko on 3/16/17.
//  Copyright © 2017 Volodymyr Dyachenko. All rights reserved.
//

#ifndef SettingsDb_hpp
#define SettingsDb_hpp

#include "Setting.hpp"

struct SettingInfo
{
    std::string name;
    std::string defaultValue;
    StrVector permitedValues;
    std::function<bool(SettingsEditor&, Setting&, const std::string&)> customHandler;
    
    static bool defaultHandler(SettingsEditor& editor, Setting& setting, const std::string& value);
};

extern const std::map<std::string, SettingInfo> settingsDb;

#endif /* SettingsDb_hpp */
