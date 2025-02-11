/**
 * This file is part of the "libterminal" project
 *   Copyright (c) 2019 Christian Parpart <christian@parpart.family>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include "Config.h"
#include "Window.h"
#include "FileChangeWatcher.h"

#include <terminal/InputGenerator.h>

#include <glterminal/FontManager.h>
#include <glterminal/GLLogger.h>
#include <glterminal/GLTerminal.h>

#include <atomic>
#include <filesystem>
#include <fstream>
#include <functional>
#include <string>

class Contour {
  public:
    explicit Contour(Config const& _config);
    ~Contour();

    int main();

  private:
    void render();
    void onResize();
    void onKey(int _key, int _scanCode, int _action, int _mods);
    void onChar(char32_t _char);
    void onMouseScroll(double _xOffset, double _yOffset);
    void onContentScale(float _xs, float _ys);
    void onScreenUpdate();
    void onConfigReload(FileChangeWatcher::Event _event);
    bool reloadConfigValues();
    bool setFontSize(unsigned _fontSize, bool _resizeWindowIfNeeded);
    Font const& regularFont() const noexcept { return terminalView_.regularFont(); }

  private:
    std::ofstream loggingSink_;
    Config config_;
    GLLogger logger_;
    FontManager fontManager_;
    std::reference_wrapper<Font> regularFont_;
    Window window_;
    GLTerminal terminalView_;
    bool keyHandled_ = false;
    std::atomic<bool> configReloadPending_ = false;
    FileChangeWatcher configFileChangeWatcher_;
    terminal::Modifier modifier_{};
    bool screenDirty_ = true;
};
