//
//  MyFirstDriver.cpp
//  MyFirstDriver
//
//  Created by Kenta Kubo on 4/17/23.
//

#include <os/log.h>

#include "MyFirstDriver.h"

kern_return_t IMPL(MyFirstDriver, Start)
{
    kern_return_t ret = Start(provider, SUPERDISPATCH);
    os_log(OS_LOG_DEFAULT, "Hello World");
    return ret;
}
