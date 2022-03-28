#pragma once

#include "common.h"

#include <vector>

struct SDL_Window;

struct StateSDL {
    int windowX = 1200;
    int windowY = 800;

    void * context = nullptr;
    SDL_Window * window = nullptr;

    bool initWindow(const char * windowTitle);
    bool initImGui(float fontScale, const std::vector<ImGui::FontInfo> & fonts);
    bool deinitWindow();
    bool deinitImGui();
};
