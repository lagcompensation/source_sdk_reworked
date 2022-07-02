#pragma once
#include <Windows.h>
#include <minwindef.h>
#include <vector>
#include <intrin.h>
#include <cstdint>
#include <thread>
#include <chrono>
#include <string>
#include <fstream>

/* hooks */
#include "hooks\hooks.hpp"

/* menu */
#include "menu\menu.hpp"

/* sdk */
#include "sdk\interfaces\interfaces.hpp"
#include "sdk\netvar\netvar.hpp"

/* utils */
#include "utils\functions\globals\globals.hpp"
#include "utils\functions\math\math.hpp"
#include "utils\functions\render\render.hpp"
#include "utils\security\xorstr.hpp"
#include "utils\vfunc_hook\vfunc_hook.hpp"
#include "utils\color.hpp"
#include "utils\utils.hpp"

/* config system */
#include "config_system\config.hpp"
