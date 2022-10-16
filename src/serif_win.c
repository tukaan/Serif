#include <tcl.h>
#include <Windows.h>
#include <Wingdi.h>


static int Serif_LoadFont(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj* const objv[]) {
  if (objc != 2) {
    Tcl_WrongNumArgs(interp, 1, objv, "filename");
    return TCL_ERROR;
  }

  int len;
  const char *path = Tcl_GetStringFromObj(objv[1], &len);

  Tcl_DString ds;
  Tcl_DStringInit(&ds);

  Tcl_Encoding unicode = Tcl_GetEncoding(interp, "unicode");
  Tcl_UtfToExternalDString(unicode, path, len, &ds);

  int res = AddFontResourceExW((LPCWSTR)Tcl_DStringValue(&ds), FR_PRIVATE, NULL);
  Tcl_DStringFree(&ds);
  Tcl_FreeEncoding(unicode);

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

  Tcl_DString ds;
  Tcl_DStringInit(&ds);

  Tcl_Encoding unicode = Tcl_GetEncoding(interp, "unicode");
  Tcl_UtfToExternalDString(unicode, path, len, &ds);

  int res = RemoveFontResourceExW((LPCWSTR)Tcl_DStringValue(&ds), FR_PRIVATE, NULL);
  Tcl_DStringFree(&ds);
  Tcl_FreeEncoding(unicode);

  if (!res) {
    Tcl_SetObjResult(interp, Tcl_ObjPrintf("error %d - cannot unload font \"%s\"", res, path));
    return TCL_ERROR;
  }

  return TCL_OK;
}



DLLEXPORT int Serif_Init(Tcl_Interp *interp) {
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


DLLEXPORT int Serif_SafeInit(Tcl_Interp *interp) {
  return Serif_Init(interp);
}