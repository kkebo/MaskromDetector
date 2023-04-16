//
//  MyFirstDriver.cpp
//  MyFirstDriver
//
//  Created by Kenta Kubo on 4/17/23.
//

#include <os/log.h>

#include <DriverKit/IOUserServer.h>
#include <DriverKit/IOLib.h>

#include "MyFirstDriver.h"

kern_return_t
IMPL(MyFirstDriver, Start)
{
    kern_return_t ret;
    ret = Start(provider, SUPERDISPATCH);
    os_log(OS_LOG_DEFAULT, "Hello World");
    return ret;
}
