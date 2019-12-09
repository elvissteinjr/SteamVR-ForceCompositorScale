# SteamVR-ForceCompositorScale
Resets the GpuSpeed settings to match the custom super sample scale.

# What it does
- Automatically reset the GpuSpeed settings to match the custom super sample scale or custom value (at least for Valve Index)

# Why
SteamVR's compositor always runs at the recommended render resolution, even when the user decided to override it to a custom value. This causes the dashboard to run at a potentially lower resolution.  
On higher resolution/refresh rate HMDs coupled with not-quite-top-of-the-line GPUs this often results in a render target scale below 1.0 and thus slightly blurry overlays.

As Valve doesn't seem to have much interest in changing this behavior, this crude but working application aims to fix it automatically.

# Usage
Make sure SteamVR is running, then execute SteamVR-ForceCompositorScale.exe. As the changes only apply on SteamVR restart, you'll have to restart SteamVR to see the effect.

SteamVR-ForceCompositorScale will register itself as an overlay application to SteamVR and run automatically on following SteamVR launches. If you move the files of this application you'll have to repeat the first-run steps.

The compositor resolution appears to cap out at 1.5x super sample scale, so higher values do not increase the resolution any further.

## Using a custom compositor scale
You can use a custom scale value for the compositor separate from the application one. For that, add a *"supersampleScaleCompositor"* value in the *"steamvr"* section of steamvr.vrsettings.

For example:
    
    "steamvr" : {
      "supersampleManualOverride" : true,
	  "supersampleScaleCompositor" : 1.5
    }
	
Make sure to not break the JSON format or SteamVR will silently reset the entire file to default values. Backup recommended.

# Building
Just compile main.cpp and link it with openvr_api.dll.

For example: g++ -o SteamVR-ForceCompositorScale.exe main.cpp openvr_api.dll

# License
SteamVR-ForceCompositorScale is licensed under WTFPL 2.0.  
Do what you want with it.

For the OpenVR API header and library, see LICENSE-OpenVR.txt.