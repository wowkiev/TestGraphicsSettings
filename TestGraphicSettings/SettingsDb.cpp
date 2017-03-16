//
//  SettingsDb.cpp
//  TestGraphicSettings
//
//  Created by Volodymyr Dyachenko on 3/16/17.
//  Copyright © 2017 Volodymyr Dyachenko. All rights reserved.
//

#include "SettingsDb.hpp"
#include "CustomSettingsHandlers.hpp"

#include <iostream>


bool SettingInfo::defaultHandler(SettingsEditor& editor, Setting& setting, const std::string& value)
{
    const auto& si = setting._SettingInfo;
    auto foundIt = std::find(std::begin(si.permitedValues), std::end(si.permitedValues), value);
    if(foundIt == std::end(si.permitedValues))
    {
        std::cerr << "Value " << value << " not permited for " << si.name << std::endl;
        return false;
    }
    setting._Value = value;
    return true;
}

namespace
{
    const char RESOLUTION_SETTING[] = "resolution";
    const char FULLSCREEN_SETTING[] = "full-screen_mode";
    const char ANTIALIASING_SETTING[] = "antialiasing";
    const char VIEW_DISTANCE_SETTING[] = "view_distance";
    const char TEXTURE_QUALITY_SETTING[] = "texture_quality";
    const char DYNAMIC_LIGHTING_SETTING[] = "dynamic_lighting";
    const char SHADOW_QUALITY_SETTING[] = "shadow_quality";
    const char GRAPHICS_QUALITY_SETTING[] = "graphics_quality";
    
    const char K640_480_VALUE[] = "640*480";
    const char K1024_768_VALUE[] = "1024*768";
    const char K1920_1080_VALUE[] = "1920*1080";
    const char TRUE_VALUE[] = "true";
    const char FALSE_VALUE[] = "false";
    const char MULTISAMPLE_NONE_VALUE[] = "MULTISAMPLE_NONE";
    const char MULTISAMPLE_2_VALUE[] = "MULTISAMPLE_2";
    const char MULTISAMPLE_4_VALUE[] = "MULTISAMPLE_4";
    const char LOW_VALUE[] = "Low";
    const char MEDIUM_VALUE[] = "Medium";
    const char HIGHT_VALUE[] = "Hight";
    const char NORMAL_VALUE[] = "Normal";
    const char CUSTOM_VALUE[] = "Custom";
}

const std::map<std::string, SettingInfo> settingsDb =
{
    {RESOLUTION_SETTING, {RESOLUTION_SETTING, K640_480_VALUE, { K640_480_VALUE, K1024_768_VALUE, K1920_1080_VALUE}}},
    
    {FULLSCREEN_SETTING, {FULLSCREEN_SETTING, TRUE_VALUE, {TRUE_VALUE, FALSE_VALUE}}},
    
    {ANTIALIASING_SETTING, {ANTIALIASING_SETTING, MULTISAMPLE_NONE_VALUE, {MULTISAMPLE_NONE_VALUE, MULTISAMPLE_2_VALUE, MULTISAMPLE_4_VALUE}}},
    
    {VIEW_DISTANCE_SETTING, {VIEW_DISTANCE_SETTING, "500", {}, handleViewDistance }},
    
    {TEXTURE_QUALITY_SETTING, {TEXTURE_QUALITY_SETTING, MEDIUM_VALUE, {LOW_VALUE, MEDIUM_VALUE, HIGHT_VALUE}, updateGraphicQuality}},
    
    {DYNAMIC_LIGHTING_SETTING, {DYNAMIC_LIGHTING_SETTING, FALSE_VALUE, {TRUE_VALUE, FALSE_VALUE},  updateGraphicQuality}},
    
    {SHADOW_QUALITY_SETTING, {SHADOW_QUALITY_SETTING, MEDIUM_VALUE, {LOW_VALUE, MEDIUM_VALUE, HIGHT_VALUE}, updateGraphicQuality}},
    
    {GRAPHICS_QUALITY_SETTING, {GRAPHICS_QUALITY_SETTING, NORMAL_VALUE, {LOW_VALUE, NORMAL_VALUE, HIGHT_VALUE, CUSTOM_VALUE}, handleGraphicQuality}}
};
