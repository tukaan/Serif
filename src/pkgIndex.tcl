package ifneeded Serif 0.1  [list apply { dir  {
	package require Tk 8.6
	
	set this_dir [file normalize ${dir}]

	set os $::tcl_platform(platform)
	switch -- $os {
		windows { set os win }
		unix    {
			switch -- $::tcl_platform(os) {
				Darwin { set os darwin }
				Linux  { set os linux }
			}
		}
	}

	# Try to guess the Tcl-interpreter architecture (32/64 bit)
	set arch $::tcl_platform(pointerSize)
	switch -- $arch {
		4 { set arch x32  }
		8 { set arch x64 }
		default { error "Serif: Unexpected pointer-size $arch!"}
	}
	
	
	set lib_file_directory [file join $this_dir ${os}-${arch}]
	if { ! [file isdirectory $lib_file_directory ] } {
		error "Serif: Unsupported platform ${os}-${arch}"
	}

	load [file join $lib_file_directory serif[info sharedlibextension]]
	
	namespace eval Serif {}
	source [file join $this_dir serif.tcl]
	
	package provide Serif 0.1

}} $dir] ;# end of lambda apply


