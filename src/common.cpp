// ImGui helpers

#include "common.h"

#include <imgui/imgui.h>
#include <imgui-extra/imgui_impl.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include <fstream>
#include <vector>
#include <array>

namespace ImGui {

namespace {

ImFontConfig getFontConfig(const FontInfo& fontInfo) {
    ImFontConfig config;

    config.MergeMode = true;
    config.GlyphOffset = { fontInfo.glyphOffsetX, fontInfo.glyphOffsetY };

    return config;
}

}

bool TryLoadFont(const FontInfo & fontInfo) {
    {
        std::ifstream f(fontInfo.filename);

        if (f.good() == false) {
            return false;
        }
    }

    // we need to keep the glyph ranges alive since for some reason Dear ImGui doesn't do it
    static thread_local std::vector<std::array<ImWchar, 3>> glyphRanges;
    if (glyphRanges.empty()) {
        glyphRanges.reserve(128);
    }
    if (glyphRanges.size() == glyphRanges.capacity()) {
        return false;
    }
    glyphRanges.push_back({{ (ImWchar) fontInfo.rangeMin, (ImWchar) fontInfo.rangeMax, 0, }});

    if (fontInfo.merge) {
        const ImFontConfig config = getFontConfig(fontInfo);
        ImGui::GetIO().Fonts->AddFontFromFileTTF(fontInfo.filename.c_str(), fontInfo.size, &config, glyphRanges.back().data());
    } else {
        ImGui::GetIO().Fonts->AddFontFromFileTTF(fontInfo.filename.c_str(), fontInfo.size, NULL, glyphRanges.back().data());
    }

    return true;
}


bool NewFrame(SDL_Window * window) {
    ImGui_NewFrame(window);
    ImGui::NewFrame();

    return true;
}

bool EndFrame(SDL_Window * window) {
    // Rendering
    int display_w, display_h;
    SDL_GetWindowSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui::Render();
    ImGui_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(window);

    ImGui::EndFrame();

    return true;
}

bool SetStyle() {
    ImGuiStyle & style = ImGui::GetStyle();

    style.AntiAliasedFill = true;
    style.AntiAliasedLines = true;
    style.WindowRounding = 0.0f;

    style.WindowPadding = ImVec2(8, 8);
    style.WindowRounding = 0.0f;
    style.FramePadding = ImVec2(4, 3);
    style.FrameRounding = 0.0f;
    style.ItemSpacing = ImVec2(8, 4);
    style.ItemInnerSpacing = ImVec2(4, 4);
    style.IndentSpacing = 21.0f;
    style.ScrollbarSize = 16.0f;
    style.ScrollbarRounding = 9.0f;
    style.GrabMinSize = 10.0f;
    style.GrabRounding = 3.0f;

    //style.Colors[ImGuiCol_Text]     = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);

    style.ScaleAllSizes(1.0f);

    return true;
}

bool BeginBorderless(const char* name, bool* p_open, ImGuiWindowFlags flags) {
    auto & style = ImGui::GetStyle();

    const auto saveWindowPadding = style.WindowPadding;
    const auto saveWindowBorderSize = style.WindowBorderSize;

    style.WindowPadding.x = 0.0f;
    style.WindowPadding.y = 0.0f;
    style.WindowBorderSize = 0.0f;

    bool result = ImGui::Begin(name, p_open, flags);

    style.WindowPadding = saveWindowPadding;
    style.WindowBorderSize = saveWindowBorderSize;

    return result;
}

bool IsMouseJustPressed(ImGuiMouseButton button) {
    return ImGui::GetIO().MouseDownDuration[button] == 0.0f;
}

FontSentry::FontSentry(int idx, float scale) {
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[idx]);
    if (scale > 0.0f) {
        ImGui::SetWindowFontScale(scale);
    }
}

FontSentry::~FontSentry() {
    ImGui::PopFont();
}

}
