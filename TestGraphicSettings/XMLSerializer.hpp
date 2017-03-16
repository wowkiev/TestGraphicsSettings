//
//  XMLSerializer.hpp
//  TestGraphicSettings
//
//  Created by Volodymyr Dyachenko on 3/16/17.
//  Copyright © 2017 Volodymyr Dyachenko. All rights reserved.
//

#ifndef XMLSerializer_hpp
#define XMLSerializer_hpp

#include "BaseSerializer.hpp"

class XMLSerializer : public BaseSerializer
{
public:
    XMLSerializer() {}
    
    void serialize(const SettingsMap& settings, const std::string& filename) const override;
};

#endif /* XMLSerializer_hpp */
