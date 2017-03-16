//
//  CustomSettingsHandlers.hpp
//  TestGraphicSettings
//
//  Created by Volodymyr Dyachenko on 3/15/17.
//  Copyright © 2017 Volodymyr Dyachenko. All rights reserved.
//

#ifndef CustomSettingsHandlers_hpp
#define CustomSettingsHandlers_hpp

#include "Setting.hpp"

class SettingsEditor;

extern bool handleViewDistance(SettingsEditor& editor, Setting& setting, const std::string& value);
extern bool updateGraphicQuality(SettingsEditor& editor, Setting& setting, const std::string& value);
extern bool handleGraphicQuality(SettingsEditor& editor, Setting& setting, const std::string& value);

#endif /* CustomSettingsHandlers_hpp */
