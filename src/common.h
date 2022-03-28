#pragma once

#include <imgui/imgui.h>

#include <string>

struct SDL_Window;

// various common functions and structures

namespace ImGui {

struct FontInfo {
    const std::string filename; // use empty string to load default font
    const float size;
    const bool merge;
    const uint32_t rangeMin;
    const uint32_t rangeMax;
    const float glyphOffsetX = 0.0f;
    const float glyphOffsetY = 0.0f;
};

bool TryLoadFont(const FontInfo& fontInfo);

// call at the start and end of each frame
bool NewFrame(SDL_Window * window);
bool EndFrame(SDL_Window * window);

// set default sytle
bool SetStyle();

// create a window without a border and no padding
bool BeginBorderless(const char* name, bool* p_open = NULL, ImGuiWindowFlags flags = 0);

bool IsMouseJustPressed(ImGuiMouseButton button);

// RAII-based font switching
struct FontSentry {
    FontSentry(int idx, float scale = -1.0f);
    ~FontSentry();
};

}
