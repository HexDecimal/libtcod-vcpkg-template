#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <libtcod.hpp>

/// Return the data directory.
auto get_data_dir() -> std::filesystem::path {
  static auto root_directory = std::filesystem::path{"."};  // Begin at the working directory.
  while (!std::filesystem::exists(root_directory / "data")) {
    // If the current working directory is missing the data dir then it will assume it exists in any parent directory.
    root_directory /= "..";
    if (!std::filesystem::exists(root_directory)) {
      throw std::runtime_error("Could not find the data directory.");
    }
  }
  return root_directory / "data";
};

static constexpr auto WHITE = tcod::ColorRGB{255, 255, 255};

static tcod::Console g_console;  // The global console object.
static tcod::Context g_context;  // The global libtcod context.

static int player_x{};
static int player_y{};

// Called every frame
SDL_AppResult SDL_AppIterate(void*) {
  g_console.clear();
  tcod::print(g_console, {0, 0}, "Hello World", WHITE, std::nullopt);
  if (g_console.in_bounds({player_x, player_y})) {
    g_console.at({player_x, player_y}).ch = '@';
  }
  g_context.present(g_console);
  return SDL_APP_CONTINUE;
}
// Handle events
SDL_AppResult SDL_AppEvent(void*, SDL_Event* event) {
  switch (event->type) {
    case SDL_EVENT_KEY_DOWN:
      switch (event->key.key) {
        case SDLK_LEFT:  // Arrow key
        case SDLK_H:  // Vi key
        case SDLK_KP_4:  // Keypad
          player_x -= 1;
          break;
        case SDLK_RIGHT:
        case SDLK_L:
        case SDLK_KP_6:
          player_x += 1;
          break;
        case SDLK_UP:
        case SDLK_K:
        case SDLK_KP_8:
          player_y -= 1;
          break;
        case SDLK_DOWN:
        case SDLK_J:
        case SDLK_KP_2:
          player_y += 1;
          break;
        case SDLK_HOME:
        case SDLK_Y:
        case SDLK_KP_7:
          player_x -= 1;
          player_y -= 1;
          break;
        case SDLK_PAGEUP:
        case SDLK_U:
        case SDLK_KP_9:
          player_x += 1;
          player_y -= 1;
          break;
        case SDLK_END:
        case SDLK_B:
        case SDLK_KP_1:
          player_x -= 1;
          player_y += 1;
          break;
        case SDLK_PAGEDOWN:
        case SDLK_N:
        case SDLK_KP_3:
          player_x += 1;
          player_y += 1;
          break;
        case SDLK_PERIOD:
        case SDLK_CLEAR:
        case SDLK_KP_5:
          break;
      }
      break;
    case SDL_EVENT_QUIT:
      return SDL_APP_SUCCESS;
  }
  return SDL_APP_CONTINUE;
}
// Main entry point
SDL_AppResult SDL_AppInit(void**, int argc, char** argv) {
  auto params = TCOD_ContextParams{};
  params.argc = argc;
  params.argv = argv;
  params.renderer_type = TCOD_RENDERER_SDL2;
  params.vsync = 1;
  params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
  params.window_title = "Libtcod Template Project";

  auto tileset = tcod::load_tilesheet(get_data_dir() / "dejavu16x16_gs_tc.png", {32, 8}, tcod::CHARMAP_TCOD);
  params.tileset = tileset.get();

  g_console = tcod::Console{80, 40};
  player_x = g_console.get_width() / 2;
  player_y = g_console.get_height() / 2;
  params.console = g_console.get();

  g_context = tcod::Context(params);

  return SDL_APP_CONTINUE;
}
// Called before existing
void SDL_AppQuit(void*, SDL_AppResult) {}
