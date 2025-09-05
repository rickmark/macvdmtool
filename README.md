# Apple Silicon to Apple Silicon VDM tool

This tool lets you send common Apple VDM messages from an Apple Sillicon Mac.  It can send messages to the T2 DFU port, the Apple M1 DFU port or any USB-C based iPad.  Currently it requires the sending device to be M1 based and the "DFU" port, but it should be possible to use any port and work from an Intel Mac (they have the same USB-C port controller) with some additonal patching.

`dfu` and `reboot` are confirmed to work on iPad and T2.  Serial can probably be adapted to work with checkra1n.

## Disclaimer

I have no idea what I'm doing with IOKit and CoreFoundation -marcan

## Copyright

This is based on portions of [ThunderboltPatcher](https://github.com/osy/ThunderboltPatcher) and licensed under Apache-2.0.

* Copyright (C) 2019 osy86. All rights reserved.
* Copyright (C) 2021 The Asahi Linux Contributors

Thanks to t8012.dev and mrarm for assistance with the VDM and Ace2 host interface commands.

<<<<<<< HEAD
=======
<<<<<<< HEAD
<<<<<<< HEAD
## Note about macOS 12

To have access to the serial console device on macOS Monterey (12), you need to disable the `AppleSerialShim` extension.

**Note:** This requires downgrading the system security and may cause problems with upgrades. Use it at your own risk!

Start by generating a new kernel cache, without the `AppleSerialShim` extension:

```
sudo kmutil create -n boot -a arm64e -B /Library/KernelCollections/kc.noshim.macho -V release  -k /System/Library/Kernels/kernel.release.<soc> -r /System/Library/Extensions -r /System/Library/DriverExtensions -x $(kmutil inspect -V release --no-header | awk '!/AppleSerialShim/ { print " -b "$1; }')
```

Replace `<soc>` with `t8101` on M1 Macs and `t6000` on M1 Pro/Max Macs. If you’re unsure, `uname -v` and look at the end of the version string (`RELEASE_ARM64_<soc>`).

Then, enter 1TR:

1. Power off your Mac
2. Press and hold the Power button until the boot menu appears
3. Select “Options”, then (if necessary) select your macOS volume and enter your administrative password.

Select Utilities>Startup security and switch the macOS installation to reduced security. Exit Startup security.

Select Utilities>Terminal and install your custom kernel:

```
kmutil configure-boot -c /Volume/<volume>/Library/KernelCollections/kc.noshim.macho -C -v /Volume/<volume>
```

Replace `<volume>` with the name of your boot volume.

You can now reboot: macOS should start as normal, and the serial device `/dev/cu.debug-console` should be available.

To revert back to the default kernel, enter 1TR again, access Utilities>Startup security and switch to full or reduced security.
=======
The documentation of the ACE and its USB-PD VPDs is here https://blog.t8012.dev/ace-part-1/
>>>>>>> b396565 (Added T2 and iPad data)
=======
The documentation of the ACE and its USB-PD VPDs is here https://blog.t8012.dev/ace-part-1/
>>>>>>> 239e733 (Added T2 and iPad data)

>>>>>>> 31c618f (README: Update for Monterey and new MBPs)
## Note about macOS 12

To have access to the serial console device on macOS Monterey (12), you need to disable the `AppleSerialShim` extension.

**Note:** This requires downgrading the system security and may cause problems with upgrades. Use it at your own risk!

Start by generating a new kernel cache, without the `AppleSerialShim` extension:

```
sudo kmutil create -n boot -a arm64e -B /Library/KernelCollections/kc.noshim.macho -V release  -k /System/Library/Kernels/kernel.release.<soc> -r /System/Library/Extensions -r /System/Library/DriverExtensions -x $(kmutil inspect -V release --no-header | awk '!/AppleSerialShim/ { print " -b "$1; }')
```

Replace `<soc>` with `t8101` on M1 Macs and `t6000` on M1 Pro/Max Macs. If you’re unsure, `uname -v` and look at the end of the version string (`RELEASE_ARM64_<soc>`).

Then, enter 1TR:

1. Power off your Mac
2. Press and hold the Power button until the boot menu appears
3. Select “Options”, then (if necessary) select your macOS volume and enter your administrative password.

Select Utilities>Startup security and switch the macOS installation to reduced security. Exit Startup security.

Select Utilities>Terminal and install your custom kernel:

```
kmutil configure-boot -c /Volume/<volume>/Library/KernelCollections/kc.noshim.macho -C -v /Volume/<volume>
```

Replace `<volume>` with the name of your boot volume.

You can now reboot: macOS should start as normal, and the serial device `/dev/cu.debug-console` should be available.

To revert back to the default kernel, enter 1TR again, access Utilities>Startup security and switch to full or reduced security.

## Building

Install the XCode commandline tools and type `make`.

## Usage

<<<<<<< HEAD
=======
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> 31c618f (README: Update for Monterey and new MBPs)
Connect the two devices via their DFU ports. That's:
 - the rear port on MacBook Air and 13" MacBook Pro
 - the port next to the MagSafe connector on the 14" and 16" MacBook Pro
 - the port nearest to the power plug on Mac Mini
<<<<<<< HEAD
=======
=======
Connect the two devices via their DFU ports. That's the furthest left port on M1 MacBooks, the closest left port on the T2, and the only port on the iPad.  See Apple's DFU recovery support articles to identify these ports on other models.
>>>>>>> b396565 (Added T2 and iPad data)
=======
Connect the two devices via their DFU ports. That's the furthest left port on M1 MacBooks, the closest left port on the T2, and the only port on the iPad.  See Apple's DFU recovery support articles to identify these ports on other models.
>>>>>>> 239e733 (Added T2 and iPad data)
=======
Connect the two devices via their DFU ports. That's:
 - the rear port on MacBook Air and 13" MacBook Pro (Apple M Series)
 - the port next to the MagSafe connector on the 14" and 16" MacBook Pro
 - the port nearest to the power plug on Mac Mini (Apple M Series)
 - the closest (to the user) USB port on T2 based MacBooks
 - the only port on the iPad / iPhone
>>>>>>> 567ee0e (README: Update for Monterey and new MBPs)
>>>>>>> 31c618f (README: Update for Monterey and new MBPs)

You need to use a *USB 3.0 compatible* (SuperSpeed) Type C cable. USB 2.0-only cables, including most cables meant for charging, will not work, as they do not have the required pins (USB CC1/CC2 where USB-PD are transmitted). Thunderbolt cables work too.

Run it as root (`sudo ./macvdmtool`) as root privledge is required to open the needed IOKit IOService.

```
Usage: ./macvdmtool <command>
Commands:
  serial - enter serial mode on both ends
  reboot - reboot the target
  reboot serial - reboot the target and enter serial mode
  dfu - put the target into DFU mode
  nop - do nothing
```

Use `/dev/cu.debug_console` on the local machine as your serial device. To use it with m1n1, `export M1N1DEVICE=/dev/cu.debug-console`.

For typical development, the command you want to use is `macvdmtool reboot serial`. This will reboot the target, and immediately put it back into serial mode, with the right timing to make it work.
