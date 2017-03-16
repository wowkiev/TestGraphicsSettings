//
//  XMLSerializer.cpp
//  TestGraphicSettings
//
//  Created by Volodymyr Dyachenko on 3/16/17.
//  Copyright © 2017 Volodymyr Dyachenko. All rights reserved.
//

#include "XMLSerializer.hpp"

#include "tinyxml/tinyxml.h"

namespace  {
    const char VALUE_ATTRIBUTE[] = "Value";
}

void XMLSerializer::serialize(const SettingsMap& settings, const std::string& filename) const
{
    TiXmlDocument doc(filename.c_str());

    auto root = new TiXmlElement("GraphicsSettoints");
    doc.LinkEndChild(root);
    
    for(auto& pair : settings)
    {
        auto item = new TiXmlElement(pair.first.c_str());
        item->SetAttribute(VALUE_ATTRIBUTE, pair.second._Value.c_str());
        root->LinkEndChild(item);
    }
    
    doc.SaveFile();
}
