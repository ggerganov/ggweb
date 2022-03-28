#include "state-core.h"

#include "icons-font-awesome.h"

#include <cmath>

namespace {

using TColor = uint32_t;

}

//
// Rendering
//

void Rendering::init() {
    T = ImGui::GetTime();
    isAnimating = false;
    wSize = ImGui::GetContentRegionAvail();
}

void Rendering::animation(float i) {
    isAnimating |= (i != 0.0f && i < 1.0f);
}

//
// StateCore
//

void StateCore::onWindowResize() {
}

void StateCore::updateDataDummy() {
    dataDummy = "foo bar";
}

//
// UI methods
//

void StateCore::init(float fontScale) {
    //const float T = ImGui::GetTime();

    this->fontScale = fontScale;

    printf("Initialized the application state\n");
    isInitialized = true;
}

void StateCore::render() {
    // shortcuts
    const auto & T     = rendering.T;
    const auto & wSize = rendering.wSize;

    if (rendering.isFirstFrame) {
        ImGui::SetStyle();

        rendering.isFirstFrame = false;
    }

    // full-screen window with the scene
    {
        ImGui::SetNextWindowPos({ 0.0f, 0.0f });
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::BeginBorderless("background", NULL,
                               ImGuiWindowFlags_NoNav |
                               ImGuiWindowFlags_NoNavFocus |
                               ImGuiWindowFlags_NoBringToFrontOnFocus |
                               ImGuiWindowFlags_NoResize |
                               ImGuiWindowFlags_NoDecoration);

        // call after creating the main window
        rendering.init();

        auto drawList = ImGui::GetWindowDrawList();

        // draw a moving circle
        if (showCircle) {
            const ImVec2 pos = {
                (0.5f + 0.25f*std::sin(2.0f*T       ))*wSize.x,
                (0.5f + 0.35f*std::sin(3.0f*T + 1.0f))*wSize.y,
            };

            const float radius = 4.0f + 16.0f*std::fabs(std::sin(T));
            const TColor color = ImGui::ColorConvertFloat4ToU32({ 0.0f, 1.0f, 0.1f, 0.8f, });

            drawList->AddCircleFilled(pos, radius, color);

            rendering.isAnimating = true;
        }

        // animation indicator in the lower-left corner of the screen
        if (rendering.isAnimating) {
            drawList->AddRectFilled({ 0.0f, wSize.y - 6.0f, }, { 6.0f, wSize.y, }, ImGui::ColorConvertFloat4ToU32({ 1.0f, 1.0f, 0.0f, 1.0f, }));
        }
    }

    // layer with controls
    {
        ImGui::SetNextWindowPos({ 0.0f, 0.0f });
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("main", NULL,
                     ImGuiWindowFlags_NoNav |
                     ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoDecoration |
                     ImGuiWindowFlags_NoBackground);

        {
            // select font
            ImGui::FontSentry sentry(0, 1.0f/fontScale);

            ImGui::Text("Window size: %6.3f %6.3f\n", wSize.x, wSize.y);
            ImGui::Text("Mouse down duration: %g\n", ImGui::GetIO().MouseDownDuration[0]);
            ImGui::Text("FA ICON COG: " ICON_FA_COG);

            ImGui::Checkbox("Show circle", &showCircle);

            ImGui::Button("Push data to JS", { 200.0f, 24.0f });
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_None) && ImGui::IsMouseJustPressed(0)) {
                updateDataDummy();
            }

            ImGui::Button("Copy to clipboard", { 200.0f, 24.0f });
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_None) && ImGui::IsMouseJustPressed(0)) {
                dataClipboard = "Some clipboard data from the native app";
            }

            ImGui::Button("Open https://google.com", { 200.0f, 24.0f });
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_None) && ImGui::IsMouseJustPressed(0)) {
                dataURL = "https://google.com";
            }
        }

        ImGui::End();
    }

    ImGui::End();
}

bool StateCore::updatePre() {
    //const float T = ImGui::GetTime();

#ifndef EMSCRIPTEN
    if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape))) {
        printf("Escape pressed - exiting\n");
        return false;
    }
#endif

    return true;
}

bool StateCore::updatePost() {
    return true;
}

void StateCore::deinitMain() {
}
