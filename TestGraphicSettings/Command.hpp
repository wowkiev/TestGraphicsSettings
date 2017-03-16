//
//  Command.hpp
//  TestGraphicSettings
//
//  Created by Volodymyr Dyachenko on 3/15/17.
//  Copyright © 2017 Volodymyr Dyachenko. All rights reserved.
//

#ifndef Command_hpp
#define Command_hpp

#include "Common.hpp"

class Command
{
public:
    std::string _Setting;
    std::string _Value;
    std::string _PrevValue;
    
    void exec();
    void undo();
};

#endif /* Command_hpp */
