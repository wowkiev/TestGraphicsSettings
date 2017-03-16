//
//  BaseSerializer.hpp
//  TestGraphicSettings
//
//  Created by Volodymyr Dyachenko on 3/16/17.
//  Copyright © 2017 Volodymyr Dyachenko. All rights reserved.
//

#ifndef BaseSerializer_hpp
#define BaseSerializer_hpp

#include "Setting.hpp"

class BaseSerializer
{
public:
    virtual void serialize(const SettingsMap& settings, const std::string& filename) const = 0;
};


#endif /* BaseSerializer_hpp */
