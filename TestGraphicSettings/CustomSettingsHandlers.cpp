//
//  CustomSettingsHandlers.cpp
//  TestGraphicSettings
//
//  Created by Volodymyr Dyachenko on 3/15/17.
//  Copyright © 2017 Volodymyr Dyachenko. All rights reserved.
//

#include "CustomSettingsHandlers.hpp"
#include "SettingsEditor.hpp"
#include "SettingsDb.hpp" 

#include <iostream>

bool handleViewDistance(SettingsEditor& editor, Setting& setting, const std::string& value)
{
    const static int minDistance = 100;
    const static int maxDistance = 1000;
    
    int distance;
    try
    {
        distance = std::stoi(value);
    }
    catch(const std::exception& ex)
    {
        std::cerr << "view_distance not a number" << std::endl;
        return false;
    }
    
    if(distance < minDistance || distance > maxDistance)
    {
        std::cerr << "view_distance out of range";
        return false;
    }
    
    setting._Value = std::to_string(distance);
    
    return true;
}


namespace
{
    const std::map<std::string, std::map<std::string, std::string> > graphicQualityPresets =
    {
        {
            "Low",
            {
                {"texture_quality", "Low"},
                {"dynamic_lighting", "false"},
                {"shadow_quality", "Low"}
            }
        },
        {
            "Normal",
            {
                {"texture_quality", "Medium"},
                {"dynamic_lighting", "false"},
                {"shadow_quality", "Medium"}
            }
        },
        {
            "Hight",
            {
                {"texture_quality", "Hight"},
                {"dynamic_lighting", "true"},
                {"shadow_quality", "Hight"}
            }
        },
        
    };
}

bool updateGraphicQuality(SettingsEditor& editor, Setting& setting, const std::string& value)
{
    auto& settings = editor.getSettings();
    
    bool res = SettingInfo::defaultHandler(editor, setting, value);
    if(!res)
    {
        return false;
    }
    
    const auto& graphicsQualityIt = settings.find("graphics_quality");
    if(graphicsQualityIt == settings.end())
    {
        std::cerr << "Internal error" << std::endl;
        return false;
    }
    
    graphicsQualityIt->second._Value = "Custom";
    for(const auto& preset : graphicQualityPresets)
    {
        bool mismatch = false;
        for(const auto& pair : preset.second)
        {
            auto foundIt = settings.find(pair.first);
            if(foundIt == std::end(settings)
               || foundIt->second._Value != pair.second)
            {
                mismatch = true;
                break;
            }
        }
        if(!mismatch)
        {
            graphicsQualityIt->second._Value = preset.first;
            return true;
        }
    }
    
    return true;
}


bool handleGraphicQuality(SettingsEditor& editor, Setting& setting, const std::string& value)
{
    auto& settings = editor.getSettings();

    bool res = SettingInfo::defaultHandler(editor, setting, value);
    
    if(!res)
    {
        return false;
    }
    
    const auto& presetIt = graphicQualityPresets.find(value);
    if(presetIt == std::end(graphicQualityPresets))
    {
        std::cerr << "Internal error" << std::endl;
        return false;
    }
    
    for(const auto &pair : presetIt->second)
    {
        auto sIt = settings.find(pair.first);
        if(sIt == settings.end())
        {
            std::cout << "Error in preset" << std::endl;
            return false;
        }
        sIt->second._Value = pair.second;
    }
    
    return true;

}

