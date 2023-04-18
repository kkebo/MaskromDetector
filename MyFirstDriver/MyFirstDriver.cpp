//
//  MyFirstDriver.cpp
//  MyFirstDriver
//
//  Created by Kenta Kubo on 4/17/23.
//

#include <os/log.h>

#include "MyFirstDriver.h"

struct MyFirstDriver_IVars
{
    IOUSBHostDevice *device;
};

bool MyFirstDriver::init()
{
    if (const auto ret = super::init(); !ret)
    {
        os_log(OS_LOG_DEFAULT, "MyFirstDriver: init() - super::init failed with error: 0x%08x.", ret);
        return ret;
    }

    if (ivars = IONewZero(MyFirstDriver_IVars, 1); ivars == nullptr)
    {
        return false;
    }

    os_log(OS_LOG_DEFAULT, "MyFirstDriver: init() - Finished.");

    return true;
}

kern_return_t IMPL(MyFirstDriver, Start)
{
    if (const auto ret = Start(provider, SUPERDISPATCH); ret != kIOReturnSuccess)
    {
        os_log(OS_LOG_DEFAULT, "MyFirstDriver: Start() - super::Start failed with error: 0x%08x.", ret);
        Stop(provider, SUPERDISPATCH);
        return ret;
    }

    os_log(OS_LOG_DEFAULT, "MyFirstDriver: Start() - Hello World");

//    if (ivars->device = OSDynamicCast(IOUSBHostDevice, provider); ivars->device == nullptr)
//    {
//        Stop(provider, SUPERDISPATCH);
//        return kIOReturnNoDevice;
//    }

//    if (const auto *deviceDescriptor = ivars->device->CopyDeviceDescriptor(); deviceDescriptor != nullptr)
//    {
//        os_log(OS_LOG_DEFAULT, "MyFirstDriver: Start() - %04hx %04hx", deviceDescriptor->idVendor, deviceDescriptor->idProduct);
//    }

    RegisterService();

    os_log(OS_LOG_DEFAULT, "MyFirstDriver: Start() - Finished.");

    return kIOReturnSuccess;
}

void MyFirstDriver::free()
{
//    OSSafeReleaseNULL(ivars->device);
    IOSafeDeleteNULL(ivars, MyFirstDriver_IVars, 1);
    super::free();
}
