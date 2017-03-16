//
//  Setting.hpp
//  TestGraphicSettings
//
//  Created by Volodymyr Dyachenko on 3/15/17.
//  Copyright © 2017 Volodymyr Dyachenko. All rights reserved.
//

#ifndef Setting_hpp
#define Setting_hpp

#include "Common.hpp"

#include <map>
#include <functional>

class SettingsEditor;

struct SettingInfo;

struct Setting
{
    const SettingInfo& _SettingInfo;
    std::string _Value;
    
    Setting(const SettingInfo& info, std::string value);
    Setting(const Setting& setting);
    
    bool change(SettingsEditor& editor, const std::string& value);
};


typedef std::map<std::string, Setting> SettingsMap;


#endif /* Setting_hpp */
