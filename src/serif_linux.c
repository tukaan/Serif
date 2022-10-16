#include <tcl.h>
#include <stdlib.h>
#include <string.h>
#include <fontconfig/fontconfig.h>


static int Serif_LoadFont(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj* const objv[]) {
  if (objc != 2) {
    Tcl_WrongNumArgs(interp, 1, objv, "filename");
    return TCL_ERROR;
  }

  int len;
  const char *path = Tcl_GetStringFromObj(objv[1], &len);

  int res = FcConfigAppFontAddFile(NULL, path);

  if (!res) {
    Tcl_SetObjResult(interp, Tcl_ObjPrintf("error %d - can't load font \"%s\"", res, path));
    return TCL_ERROR;
  }

  return TCL_OK;
}


static FcBool Custom_FcConfigAppFontRemoveFile(FcConfig *config, const FcChar8 *filename) {
  // Currently Fontconfig (2.12.4) doesn't have the inverse of FcConfigAppFontAddFile,
  // a function to unload fonts, so this function is a workaround based on internal code hacking
  // WARNING: This isn't documented/supported in Fontconfig

  FcFontSet *set = FcConfigGetFonts(config, FcSetApplication);
  if (!set) {
    return FcFalse;
  }

  int found = 0;

  // Scan the set->fonts array, and copy all the elements but those with matching 'filename'.
  // Finally substitute the new (reduced) array to set->fonts.
  if (set->nfont == 0) {
    return FcFalse;
  }

  FcPattern **newFonts = (FcPattern **)calloc(set->sfont, sizeof(FcPattern *));
  FcPattern **newP = newFonts;

  for (int i = 0; i < set->nfont; ++i) {
    FcChar8 *strRef = NULL;
    FcPatternGetString(set->fonts[i], FC_FILE, 0, &strRef);

    if (strRef && strcmp(strRef, filename) == 0) {
      ++found;
      FcPatternDestroy(set->fonts[i]);
    } else {
      *newP++ = set->fonts[i];
    }
  }

  if (found > 0) {
      // Free just the array of pointers; don't free the pointed objects (they have been copied in newFonts)
      free(set->fonts);
      // set newFonts as the new set->fonts
      set->fonts = newFonts;
      set->nfont -= found;

      return FcTrue;
  } else {
    free (newFonts);  // Free just the array 
    return FcFalse;
  }

  return FcFalse;
}


static int Serif_UnloadFont(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj* const objv[]) {
  if (objc != 2) {
    Tcl_WrongNumArgs(interp, 1, objv, "filename");
    return TCL_ERROR;
  }

  int len;
  const char *path = Tcl_GetStringFromObj(objv[1], &len);

  int res = Custom_FcConfigAppFontRemoveFile(NULL, path) ? 1 : 0;

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
