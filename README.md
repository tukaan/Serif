# Serif
A cross-platform extension for Tcl/Tk to load fonts from files at runtime, without installing it. This extension is based on the [Extrafont](https://sourceforge.net/p/irrational-numbers/code/HEAD/tree/pkgs/extrafont-devkit/) package.

DO NOT USE this yourself! This project will be a `git submodule` in [Tukaan](https://github.com/tukaan/tukaan), that will interface with it.

## Build

### Linux
Using the standard GNU/C tool-chain

```
./build.sh x32
./build.sh x64
```
If `build.sh x32` (on 64 bit Linux) exits with an error: `/usr/bin/ld cannot find  -lfontconfig`, then you should reinstall `fontconfig-32bit`
```
sudo apt-get install libfontconfig1-dev
```
then run `build.sh` again.


### MacOS
Using the standard GNU/C tool-chain

```
build.sh x64
```

### Windows
Using Microsoft Visual Studio (Visual Studio 2015 Community Edition)
Support for x86/x64 target architecture.

```
ms-build x32
ms-build x64
```


## Credits
The [original license](https://sourceforge.net/p/irrational-numbers/code/HEAD/tree/pkgs/extrafont-devkit/tags/1.2.0.1/license.terms) of the extrafont package.

```
== Extrafont == 
A multi-platform binary package for loading "private fonts"

Copyright (c) 2017-2020 by A.Buratti <aldo.w.buratti@gmail.com> 

This library is free software; you can use, modify, and redistribute it
for any purpose, provided that existing copyright notices are retained
in all copies and that this notice is included verbatim in any
distributions.

This software is distributed WITHOUT ANY WARRANTY; without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```