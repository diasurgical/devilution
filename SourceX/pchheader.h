#pragma once

#include <assert.h>
#include <deque>
#include <dirent.h>
#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <set>
#include <map>
#include <stdarg.h>
#include <string>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL_mixer.h>
#include <SDL_thread.h>
#include <SDL_ttf.h>

#include <sodium.h>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <asio/ts/io_context.hpp>
#include <asio/ts/net.hpp>

#include "../types.h"
#include "stubs.h"
#include "asserts.h"
#include "miniwin_sdl.h"
#include "dvlnet/dvlnet.h"
