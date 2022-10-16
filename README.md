# Serif
Serif is based on the [Extrafont](https://sourceforge.net/p/irrational-numbers/code/HEAD/tree/pkgs/extrafont-devkit/) package.

## Build
You can use GNU make to build Serif on Linux, macOS and Windows

```bash
make
```

### Build requirements

- Linux
  * `libfontconfig1-dev`

- Windows
  * MinGW (MSYS2) with `gcc` and `make` installed
  * An ActiveTcl installation in `C:\ActiveTcl`
  * `C:\msys64\mingw64\bin` and `C:\ActiveTcl\lib` should be in PATH

- macOS
  * Nothing 🎉




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
