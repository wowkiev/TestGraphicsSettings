//
//  Setting.cpp
//  TestGraphicSettings
//
//  Created by Volodymyr Dyachenko on 3/15/17.
//  Copyright © 2017 Volodymyr Dyachenko. All rights reserved.
//

#include "Setting.hpp"
#include "SettingsEditor.hpp"
#include "SettingsDb.hpp"


Setting::Setting(const SettingInfo& info, std::string value) :
    _SettingInfo(info), _Value(value)
{
    
}

Setting::Setting(const Setting& setting) :
    _SettingInfo(setting._SettingInfo), _Value(setting._Value)
{
}

bool Setting::change(SettingsEditor& editor, const std::string& value)
{
    bool result;
    
    if(_SettingInfo.customHandler)
    {
        result = _SettingInfo.customHandler(editor, *this, value);
    }
    else
    {
        result = _SettingInfo.defaultHandler(editor, *this, value);
    }
    return result;
}
