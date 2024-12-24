//
//  Main.cpp
//  Warlock-macOS
//
//  Created by Abe Pralle on 1/22/24.
//

#include <cstdio>

#import "RogueInterface.h"

#include <iostream>
using namespace std;

#include <SDL2/SDL.h>
//SDL_Window *window;
//const char* window_name = "example SDL2 Vulkan application";


//#include <bgfx/bgfx.h>
//#include <bgfx/platform.h>
//#include <bx/math.h>

//#include <glm/mat4x4.hpp>
//#include <glm/vec3.hpp>
//#include <glm/vec4.hpp>
//using namespace glm;

/*
struct WarlockEventHandler : EventHandler
{
  bool begin_render( Window* window, unsigned char** render_data, int* count )
  {
    RogueByteList* list = WarlockWarlock__begin_render__RogueInt_RogueInt_RogueInt(
      window->index, window->width, window->height
    );
    if ( !list ) return false;
    *render_data = list->as_bytes;
    *count = (int)list->count;
    return true;
  }

  void end_render( Window* window )
  {
    WarlockWarlock__end_render__RogueInt( window->index );
    Rogue_check_gc();
  }
};
*/

bool handle_events()
{
  SDL_Event e;
  while(SDL_PollEvent(&e))
  {
    switch (e.type)
    {
      case SDL_QUIT:
        return false;

/*
      case SDL_WINDOWEVENT:
      {
        Window* window = find_window( e.window.windowID );
        if (window)
        {
          switch (e.window.event)
          {
            case SDL_WINDOWEVENT_MINIMIZED:
            case SDL_WINDOWEVENT_HIDDEN:
              window->rendering_paused = true;
              break;

            case SDL_WINDOWEVENT_RESTORED:
            case SDL_WINDOWEVENT_SHOWN:
              window->rendering_paused = false;
              break;

            case SDL_WINDOWEVENT_FOCUS_GAINED:
              // TODO
              break;
          }
        }
        break;
      }
*/

      /*
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
      {
        auto w = plasmacore_get_window(e.button.windowID);
        if (!w) break;
        int which;
        switch (e.button.button)
        {
          case SDL_BUTTON_LEFT:
            which = 0;
            break;
          case SDL_BUTTON_RIGHT:
            which = 1;
            break;
          default:
            return;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN)
          w->on_mouse_down(e.button.x, e.button.y, which);
        else
          w->on_mouse_up(e.button.x, e.button.y, which);
        break;
      }

      case SDL_MOUSEMOTION:
      {
        auto w = plasmacore_get_window(e.motion.windowID);
        if (!w) break;
        w->on_mouse_move(e.motion.x, e.motion.y);
        break;
      }

      case SDL_MOUSEWHEEL:
      {
        auto w = plasmacore_get_window(e.motion.windowID);
        if (!w) break;
        w->on_scroll(-e.wheel.x, e.wheel.y);
        break;
      }

      case SDL_KEYDOWN:
      {
        auto w = plasmacore_get_window(e.key.windowID);
        if (!w) break;
        w->on_key_event( e.key.keysym.scancode, true, !!e.key.repeat );
        break;
      }

      case SDL_KEYUP:
      {
        auto w = plasmacore_get_window(e.key.windowID);
        if (!w) break;
        w->on_key_event( e.key.keysym.scancode, false, false );
        break;
      }
      */

    }
  }
  return true;
}


// Vertex structure
struct PosColorVertex {
    float x, y, z;
    uint32_t abgr;
    static void init() {
        ms_layout.begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
            .end();
    }
    static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout PosColorVertex::ms_layout;

// Vertex data
static PosColorVertex vertices[] = {
    {-0.5f, -0.5f, 0.0f, 0xff0000ff},
    { 0.5f, -0.5f, 0.0f, 0xff00ff00},
    { 0.0f,  0.5f, 0.0f, 0xffff0000},
};

// Index data
static const uint16_t indices[] = {
    0, 1, 2,
};

void init_bgfx(SDL_Window* window) {
/*
    // Get SDL window size
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    // Initialize bgfx
    bgfx::Init init;
    init.type = bgfx::RendererType::Count; // Automatically choose renderer
    init.resolution.width = static_cast<uint32_t>(windowWidth);
    init.resolution.height = static_cast<uint32_t>(windowHeight);
    init.resolution.reset = BGFX_RESET_VSYNC;

    // Set the platform data for bgfx
    bgfx::PlatformData pd{};
    pd.nwh = SDL_GetWindowFromID(SDL_GetWindowID(window));
    init.platformData = pd;

    bgfx::init(init);
    bgfx::reset(windowWidth, windowHeight, BGFX_RESET_VSYNC);

    // Setup view
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff);
    bgfx::setViewRect(0, 0, 0, static_cast<uint16_t>(windowWidth), static_cast<uint16_t>(windowHeight));
*/
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Create SDL window
    SDL_Window* window = SDL_CreateWindow(
        "bgfx Triangle",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

/*
    // Initialize bgfx
    init_bgfx(window);

    // Initialize vertex layout
    PosColorVertex::init();

    // Create vertex buffer
    bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(
        bgfx::makeRef(vertices, sizeof(vertices)),
        PosColorVertex::ms_layout
    );

    // Create index buffer
    bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(
        bgfx::makeRef(indices, sizeof(indices))
    );

    // Load shaders (replace with your own shaders)
    bgfx::ShaderHandle vs = bgfx::createShader(bgfx::makeRef(vs_code, sizeof(vs_code)));
    bgfx::ShaderHandle fs = bgfx::createShader(bgfx::makeRef(fs_code, sizeof(fs_code)));
    bgfx::ProgramHandle program = bgfx::createProgram(vs, fs, true);

    // Main loop
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Set view transform
        float view[16];
        float proj[16];
        bx::mtxIdentity(view);
        bx::mtxOrtho(proj, -1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 100.0f, 0.0f, bgfx::getCaps()->homogeneousDepth);
        bgfx::setViewTransform(0, view, proj);

        // Submit triangle
        bgfx::setVertexBuffer(0, vbh);
        bgfx::setIndexBuffer(ibh);
        bgfx::submit(0, program);

        // Frame
        bgfx::frame();
    }

    // Cleanup
    bgfx::destroy(vbh);
    bgfx::destroy(ibh);
    bgfx::destroy(program);
    bgfx::shutdown();
*/

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

//int main(int argc, char *argv[])
//{
/*
  Balefire balefire( new FrameworkSDLVulkan() );
  WarlockEventHandler event_handler;
  balefire.event_handler = &event_handler;

  RogueInterface_configure( argc, argv );
  RogueInterface_launch();

  while (balefire.handle_events()) balefire.render();
*/
  //while (handle_events()) {}


  //SDL_Quit();
  //return 0;
//}
