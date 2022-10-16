#include <tcl.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreText/CTFontManager.h>


static int Serif_LoadFont(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj* const objv[]) {
  if (objc != 2) {
    Tcl_WrongNumArgs(interp, 1, objv, "filename");
    return TCL_ERROR;
  }

  int len;
  const char *path = Tcl_GetStringFromObj(objv[1], &len);

  CFStringRef filenameStr = CFStringCreateWithCString(NULL, path, kCFStringEncodingUTF8);
  CFURLRef fileURL = CFURLCreateWithFileSystemPath(NULL, filenameStr, kCFURLPOSIXPathStyle, false);
  CFRelease(filenameStr);

  CFErrorRef error = nil;
  int res = CTFontManagerUnregisterFontsForURL(fileURL, kCTFontManagerScopeProcess, &error);
  CFRelease(fileURL);

  if (!res) {
    Tcl_SetObjResult(interp, Tcl_ObjPrintf("error %d - can't load font \"%s\"", res, path));
    return TCL_ERROR;
  }

  return TCL_OK;
}


static int Serif_UnloadFont(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj* const objv[]) {
  if (objc != 2) {
    Tcl_WrongNumArgs(interp, 1, objv, "filename");
    return TCL_ERROR;
  }

  int len;
  const char *path = Tcl_GetStringFromObj(objv[1], &len);

  CFStringRef filenameStr = CFStringCreateWithCString(NULL, path, kCFStringEncodingUTF8);
  CFURLRef fileURL = CFURLCreateWithFileSystemPath(NULL, filenameStr, kCFURLPOSIXPathStyle, false);
  CFRelease(filenameStr);

  CFErrorRef error = nil;
  int res = CTFontManagerUnregisterFontsForURL(fileURL, kCTFontManagerScopeProcess, &error);
  CFRelease(fileURL);

  if (!res) {
    Tcl_SetObjResult(interp, Tcl_ObjPrintf("error %d - can't unload font \"%s\"", res, path));
    return TCL_ERROR;
  }

  return TCL_OK;
}


int Serif_Init(Tcl_Interp *interp) {
  if (Tcl_InitStubs(interp, "8.6", 0) == NULL) {
    return TCL_ERROR;
  }

  Tcl_CreateObjCommand(interp, "Serif::load_fontfile", Serif_LoadFont, (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);
  Tcl_CreateObjCommand(interp, "Serif::unload_fontfile", Serif_UnloadFont, (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);

  if (Tcl_PkgProvide(interp, "Serif", "0.1") != TCL_OK) {
    return TCL_ERROR;
  }

  return TCL_OK;
}


int Serif_SafeInit(Tcl_Interp *interp) {
  return Serif_Init(interp);
}
