import sys
from pathlib import Path

from tukaan._tcl import Tcl

os = {"linux": "linux", "darwin": "mac", "win32": "windows"}[sys.platform]


def load() -> None:
    system = os

    system += "_x64" if sys.maxsize > 2**32 else "_x32"
    ext = Tcl.call(str, "info", "sharedlibextension")

    libfilename = "serif_" + system + ext
    Tcl.call(None, "load", Path(__file__).parent / "pkg" / libfilename, "Serif")
