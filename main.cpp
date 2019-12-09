/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. */

#include <cstdio>
#include "openvr.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int main()
{
    //Init OpenVR
    vr::EVRInitError vr_error;
    vr::IVRSystem* vr_system = vr::VR_Init(&vr_error, vr::VRApplication_Background);

    if (!vr_system)
    {
        printf("Failed to load OpenVR: %s", vr::VR_GetVRInitErrorAsEnglishDescription(vr_error));
        return -1;
    }

    //Register application so it will be launched automagically next time
    if (!vr::VRApplications()->IsApplicationInstalled("elvissteinjr.ForceCompositorScale"))
    {
        //This is supposed to be just a simple crude application, so we'll make due with this for getting the application path (this likely won't work on unicode paths)
        DWORD length = GetCurrentDirectory(0, NULL);
        char* path   = new char[length];
        length       = GetCurrentDirectory(length, path);

        if (length != 0)
        {
            std::string path_str(path);
            path_str.append("\\manifest.vrmanifest");

            vr::EVRApplicationError app_error;
            app_error = vr::VRApplications()->AddApplicationManifest(path_str.c_str());

            if (app_error == vr::VRApplicationError_None)
            {
                vr::VRApplications()->SetApplicationAutoLaunch("elvissteinjr.ForceCompositorScale", true);
            }
        }

        delete[] path;
    }

    //Value based on Valve Index numbers, but small deviations shouldn't matter too much
    float rendertarget = vr::VRSettings()->GetFloat("steamvr", "supersampleScale");
    int gpuspeed = 6.834f * rendertarget * vr::VRSystem()->GetFloatTrackedDeviceProperty(vr::k_unTrackedDeviceIndex_Hmd, vr::Prop_DisplayFrequency_Float);
    //Override a bunch of GPU Speed settings
    char buffer[16];
    for (int i = 0; i < 10; ++i)
    {
        sprintf_s(buffer, 16, "gpuSpeed%d", i);
        vr::VRSettings()->SetInt32("GpuSpeed", buffer, gpuspeed);
    }
    vr::VRSettings()->SetInt32("GpuSpeed", "gpuSpeedHorsepower", gpuspeed);
    vr::VRSettings()->SetFloat("GpuSpeed", "gpuSpeedRenderTargetScale", rendertarget);
    vr::VRSettings()->Sync(true);

    vr::VR_Shutdown();

    return 0;
}
