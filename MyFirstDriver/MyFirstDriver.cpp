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
    bool ret;

    ret = super::init();
    if (!ret) {
        os_log(OS_LOG_DEFAULT, "MyFirstDriver: init() - super::init failed with error: 0x%08x.", ret);
        return ret;
    }

    ivars = IONewZero(MyFirstDriver_IVars, 1);
    if (ivars == nullptr) {
        return false;
    }

    os_log(OS_LOG_DEFAULT, "MyFirstDriver: init() - Finished.");

    return ret;
}

kern_return_t IMPL(MyFirstDriver, Start)
{
    kern_return_t ret;

    ret = Start(provider, SUPERDISPATCH);
    if (ret != kIOReturnSuccess) {
        os_log(OS_LOG_DEFAULT, "MyFirstDriver: Start() - super::Start failed with error: 0x%08x.", ret);
        Stop(provider, SUPERDISPATCH);
        return ret;
    }

    os_log(OS_LOG_DEFAULT, "MyFirstDriver: Start() - Hello World");

//    ivars->device = OSDynamicCast(IOUSBHostDevice, provider);
//    if (ivars->device == nullptr) {
//        Stop(provider, SUPERDISPATCH);
//        return kIOReturnNoDevice;
//    }

//    const auto *deviceDescriptor = ivars->device->CopyDeviceDescriptor();
//    if (deviceDescriptor != nullptr) {
//        os_log(OS_LOG_DEFAULT, "MyFirstDriver: Start() - %04hx %04hx", deviceDescriptor->idVendor, deviceDescriptor->idProduct);
//    }

    RegisterService();

    os_log(OS_LOG_DEFAULT, "MyFirstDriver: Start() - Finished.");

    return ret;
}

void MyFirstDriver::free()
{
//    OSSafeReleaseNULL(ivars->device);
    IOSafeDeleteNULL(ivars, MyFirstDriver_IVars, 1);
    super::free();
}
