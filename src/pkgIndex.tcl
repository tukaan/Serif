package ifneeded Serif 1.0  [list apply { dir  {
	package require Tk 8.6
	
	set thisDir [file normalize ${dir}]

	set os $::tcl_platform(platform)
	switch -- $os {
		windows { set os win }
		unix    {
			switch -- $::tcl_platform(os) {
				Darwin { set os darwin }
				Linux  { set os linux  }
			}
		}
	}
	set tail_libFile serif[info sharedlibextension]
	# try to guess the tcl-interpreter architecture (32/64 bit) ...
	set arch $::tcl_platform(pointerSize)
	switch -- $arch {
		4 { set arch x32  }
		8 { set arch x64 }
		default { error "Serif: Unsupported architecture: Unexpected pointer-size $arch!!! "}
	}
	
	
	set dir_libFile [file join $thisDir ${os}-${arch}]
	if { ! [file isdirectory $dir_libFile ] } {
		error "Serif: Unsupported platform ${os}-${arch}"
	}

	set full_libFile [file join $dir_libFile $tail_libFile]			 
	load $full_libFile
	
	namespace eval Serif {}
	source [file join $thisDir serif.tcl]
	
	package provide Serif 1.0

}} $dir] ;# end of lambda apply


