#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <EGL/egl.h>
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
#include <libgen.h>
#include <cmath>
#include <math.h>
#include <dlfcn.h>
#include <deque>
#include <unordered_map>

#include "utilities/oxorany/oxorany_include.h"

#include "utilities/unity/Color.h"
#include "utilities/unity/Vector3.h"
#include "utilities/unity/Vector2.h"
#include "utilities/unity/Quaternion.h"

#include <utilities/a64/And64InlineHook.cpp>

#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_android.cpp"
#include "box_shadow.cpp"

#include "Includes/Fonts/raw/MontserratFont.h"
#include "Includes/Fonts/raw/MontserratFontBig.h"
#include "Includes/Fonts/raw/MontserratFontMed.h"
#include "Includes/Fonts/font-awesome.hpp"
#include "Includes/Fonts/font-awesome-helpers.hpp"

#include "utilities/KittyMemory/KittyMemory.cpp"
#include "utilities/KittyMemory/KittyScanner.cpp"
#include "utilities/KittyMemory/Kittyutils.cpp"
#include "utilities/KittyMemory/MemoryPatch.cpp"

#include "utilities/il2cpp/dlfcn_ex.cpp"
#include "utilities/il2cpp/il2cpp.cpp"

#include "qazaqdlc/utilities.cpp"
#include "qazaqdlc/toast.cpp"
#include "qazaqdlc/structures.hpp"
#include "qazaqdlc/debugmenu.cpp"
#include "qazaqdlc/weather.cpp"
#include "qazaqdlc/inputs.cpp"
#include "qazaqdlc/hooks/general.cpp"

