# Serif
Sometimes you need to load your own font file into the application at runtime to give it a custom look. While you can't do this in Tcl/Tk or in Tkinter by default, this C extension lets you do load such files in Tukaan really easily.
Serif is based on the [Extrafont](https://sourceforge.net/p/irrational-numbers/code/HEAD/tree/pkgs/extrafont-devkit/) package.

You probably don't need to use this yourself, as it is included in Tukaan, however I provide some development instructions here.

## Build

### Linux
You can just simply run `build.sh` to build Serif. A shared object file will be generated in the pkg folder. 

You may need to make the file executable: `chmod +x build.sh`

```bash
./build.sh x64
# or for x86 binaries:
./build.sh x32
```
If `build.sh x32` (on 64 bit Linux) exits with an error: `/usr/bin/ld cannot find  -lfontconfig`, then you should reinstall `fontconfig-32bit`
```
sudo apt-get install libfontconfig1-dev
```
then run `build.sh` again.


### MacOS
You can use the `build.sh` script, though I have no idea, whether it actually works.

```
build.sh x64
```

### Windows
To build Serif on Windows you'll need:
- Visual Studio 2019
- A Tcl installation

You can run `build.bat` to build the binaries.
```
build.bat x32
build.bat x64
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
