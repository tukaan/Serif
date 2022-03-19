# Copyright (c) 2017-2018 by A.Buratti
#
# This library is free software; you can use, modify, and redistribute it
# for any purpose, provided that existing copyright notices are retained
# in all copies and that this notice is included verbatim in any
# distributions.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.


namespace eval Serif {
	# FFFD-table is the core data structure holding all the relations between
	# font-files, font-familiies, font-fullnames and font-details.
	# They first three components FFF (font-file, font-familiy, font-fullname)
	# gives you a primary key for the D component (the font-detail dictionary)

	variable _FFFD_Table    ;# array: key is (file, family, fullname)
							;#        value is the font-detail
	
	array unset _FFFD_Table

	namespace eval fontMetadata {
		# Load the metadata submodule
		source [file join [file dirname [info script]] metadata.tcl]
	}

	# When Tk is destroyed (e.g on exit), then do a cleanup
	trace add command "." delete {apply { {args} {Serif::cleanUp} } }
}


proc Serif::load {fontfile} {
	# Expects a fontfile-name, that is already copied to tempdir, thus I've removed futmp.tcl

	# Load the fonts contained in $fontfile
	# Returns the preferred (primary) family from font file

	variable _FFFD_Table
			
	set fontfile [file normalize $fontfile]
	set orig_fontfile $fontfile
	if {[array names _FFFD_Table $orig_fontfile,*] != {}} {
		# Don't raise an error, simply return instead
		return
	}

	core::load $fontfile

	set fontsInfo {}
	catch {  ;# If getFontMetadata fails, use an empty list
		set fontsInfo [fontMetadata::getFontMetadata $fontfile]
	}
	set FamList {}

	foreach fontInfo $fontsInfo {
		set family [dict get $fontInfo "family"]
		set fullname [dict get $fontInfo "full_name"]
		set _FFFD_Table($orig_fontfile,$family,$fullname) $fontInfo
		lappend FamList $family
	}

	set preferredFamily $family
	catch {  ;# Try to get preferredFamily from font metadata
		set preferredFamily [dict get $fontInfo "preferred_family"]
	}

	return preferredFamily
} 


proc Serif::unload {fontfile} {
	# Unloads the previously loaded font $filename
	# Be careful: since this proc could be called when app exits,
	# you can't rely on other packages (e.g. vfs), since they could have been destroyed before.
	# Therefore DO NOT use within this proc code from other packages

	variable _FFFD_Table
	
	set fontfile [file normalize $fontfile]

	if { [query files -file $fontfile]  == {}  } {
		# If font isn't loaded, simply return
		return
	}

	core::unload $fontfile
	array unset _FFFD_Table $fontfile,*
}


proc Serif::query { kind args } {
	# query _kind_ ?selector value?"

	variable _FFFD_Table

	set allowedValues {files families fullnames details}
	if { $kind ni $allowedValues } {
		error "bad kind \"$kind\": must be [join $allowedValues ","]"
	}

	if { $args == {} } {
		set selector "(empty)"  ;# dummy selector
	} elseif { [llength $args] == 2 } {
		lassign $args selector selectorVal
		set allowedValues {-file -family -fullname}
		if { $selector ni $allowedValues } {
			error "bad selector \"$selector\": must be [join $allowedValues ","]"
		}			
	} else {
		error "wrong params: query _kind_ ?selector value?"
	}

	switch -- $selector {
		(empty)		{ set pattern "*" }
		-file		{ set pattern "$selectorVal,*,*" }
		-family		{ set pattern "*,$selectorVal,*"	}
		-fullname	{ set pattern "*,*,$selectorVal" }		
	}	

	set L {}
	foreach { key detail } [array get _FFFD_Table $pattern] {
		lassign [split $key ","] fontfile family fullname 
		switch -- $kind {
			files	{ lappend L $fontfile }
			families {	lappend L $family }
			fullnames { lappend L $fullname}
			details {lappend L $detail }  
		} 
	}
	lsort -unique $L 
}


proc Serif::getFontMetadata {fontfile} {
	# Return font metadata as a dictionary

	variable _FFFD_Table
			
	set fontfile [file normalize $fontfile]
	set res [query details -file $fontfile]  ;# Font already loaded, return cached metadata
	if {$res == {}} {
		set res [fontMetadata::getFontMetadata $fontfile]
	}
	return $res
}


proc Serif::cleanUp {} {
	# Unload all loaded fonts

	foreach fontfile [query files] {
		catch {unload $fontfile}
	}
}