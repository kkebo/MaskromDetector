//
//  MaskromDriver.cpp
//  MaskromDriver
//
//  Created by Kenta Kubo on 4/17/23.
//

#include <os/log.h>

#include <USBDriverKit/IOUSBHostDevice.h>

#include "MaskromDriver.h"

struct MaskromDriver_IVars
{
    IOUSBHostDevice *device;
};

bool MaskromDriver::init()
{
    if (const auto ret = super::init(); !ret)
    {
        os_log(OS_LOG_DEFAULT, "MaskromDriver: init() - super::init failed with error: 0x%08x.", ret);
        return ret;
    }

    if (ivars = IONewZero(MaskromDriver_IVars, 1); ivars == nullptr)
    {
        return false;
    }

    os_log(OS_LOG_DEFAULT, "MaskromDriver: init() - Finished.");

    return true;
}

kern_return_t IMPL(MaskromDriver, Start)
{
    if (const auto ret = Start(provider, SUPERDISPATCH); ret != kIOReturnSuccess)
    {
        os_log(OS_LOG_DEFAULT, "MaskromDriver: Start() - super::Start failed with error: 0x%08x.", ret);
        Stop(provider, SUPERDISPATCH);
        return ret;
    }

    os_log(OS_LOG_DEFAULT, "MaskromDriver: Start() - super::Start succeeded.");

    if (ivars->device = OSDynamicCast(IOUSBHostDevice, provider); ivars->device == nullptr)
    {
        Stop(provider, SUPERDISPATCH);
        return kIOReturnNoDevice;
    }

    if (const auto *deviceDescriptor = ivars->device->CopyDeviceDescriptor(); deviceDescriptor != nullptr)
    {
        os_log(OS_LOG_DEFAULT, "MaskromDriver: Start() - VID: %04hx, PID: %04hx", deviceDescriptor->idVendor, deviceDescriptor->idProduct);
    }

    if (const auto ret = RegisterService(); ret != kIOReturnSuccess)
    {
        Stop(provider, SUPERDISPATCH);
        return ret;
    }

    os_log(OS_LOG_DEFAULT, "MaskromDriver: Start() - RegisterService succeeded.");

    return kIOReturnSuccess;
}

void MaskromDriver::free()
{
    OSSafeReleaseNULL(ivars->device);
    IOSafeDeleteNULL(ivars, MaskromDriver_IVars, 1);
    super::free();
}
