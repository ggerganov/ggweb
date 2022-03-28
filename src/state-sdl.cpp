#include "state-sdl.h"

#include <imgui/imgui.h>
#include <imgui-extra/imgui_impl.h>

#include <SDL.h>

bool StateSDL::initWindow(const char * windowTitle) {
    ImGui_PreInit();

    printf("Initializing SDL window '%s'\n", windowTitle);

#ifdef __EMSCRIPTEN__
    {
        SDL_Renderer * renderer;
        SDL_CreateWindowAndRenderer(windowX, windowY, SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_RENDERER_PRESENTVSYNC, &window, &renderer);
    }
#else
    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowX, windowY, SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
#endif
    if (window == nullptr) {
        fprintf(stderr, "Error: failed to create SDL error. Reason: %s\n", SDL_GetError());
        return false;
    }

    context = SDL_GL_CreateContext(window);
    if (context == nullptr) {
        fprintf(stderr, "Error: failed to create OpenGL context. Reason: %s\n", SDL_GetError());
        return false;
    }

    SDL_GL_MakeCurrent(window, context);
    SDL_GL_SetSwapInterval(1); // Enable vsyn

    return true;
}

bool StateSDL::initImGui(float fontScale, const std::vector<ImGui::FontInfo> & fonts) {
    ImGui_Init(window, context);

    ImGui::GetIO().IniFilename = nullptr;

    // initialize fonts
    {
        // default font
        {
            printf("Initializing default font\n");
            ImFontConfig cfg;
            cfg.SizePixels = 13.0f*fontScale;
            ImGui::GetIO().Fonts->AddFontDefault(&cfg);
        }

        for (const auto & font : fonts) {
            printf("Initializing font '%s'\n", font.filename.c_str());
            if (ImGui::TryLoadFont(font) == false) {
                fprintf(stderr, "Error: failed to load font '%s'\n", font.filename.c_str());
            }
        }
    }

    // dummy frame to initialize stuff
    ImGui::NewFrame(window);
    ImGui::EndFrame(window);

    return true;
}

bool StateSDL::deinitWindow() {
    printf("Deinitializing SDL\n");

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return true;
}

bool StateSDL::deinitImGui() {
    printf("Deinitializing ImGui\n");

    ImGui_Shutdown();
    ImGui::DestroyContext();

    return true;
}
