# GGWeb

Template for making a GUI app with C++ / Dear ImGui / SDL / OpenGL / Emscripten that can run both natively and in the
browser.

Example: https://ggweb.ggerganov.com

## Description

This is a startup project for creating C++ GUI applications that can run both as a native app and as a web app. This is
achieved by compiling the C++ code to WebAssembly using Emscripten. The project uses Dear ImGui + OpenGL backend to draw
stuff on the screen. The project provides basic functionality needed for most apps:

- Create and initialize an SDL window with OpenGL context
- Basic single-threaded Render/Update loop
- Basic HTML boilerplate for running the app in a web page
- Interface for passing data between C++ and Javascript
- Open a URL in new tab
- Copy text to clipboard
- Mechanism for frame throttling when the application is idle to reduce CPU
- etc.

When running natively, the app creates an SDL window and renders stuff using OpenGL. When running as a web app, it runs
in a WebGL canvas.

The code is structured in a way that is comfortable for me to use and think about the application state. It is
definitely not ideal and does not scale well. Probably with time I will try to improve it and document it better. The
main purpose of this repo is to be able to quickly bootstrap a simple cross-platform app with the described stack.

## Why?

I like writing C++ GUI apps using [Dear ImGui](https://github.com/ocornut/imgui). I often port the applications to the
web for demonstration purposes. I find it very useful that with this stack I can run the same C++ application across
a large variety of platforms and devices.

## Build native

```bash
# clone repo and build
git clone https://github.com/ggerganov/ggweb --recursive
cd ggweb && mkdir build && cd build
cmake ..
make -j4

# run the app
./bin/ggweb-app
```

## Build web

```bash
# init emscripten
source /path/to/emsdk/emsdk_env.sh

# clone repo and build
git clone https://github.com/ggerganov/ggweb --recursive
cd ggweb && mkdir build-em && cd build-em
emcmake cmake ..
make -j4

# update web server
cp ./bin/ggweb-app.*        /path/to/www/html/
cp ./bin/ggweb-app-public/* /path/to/www/html/
```

## Examples

Here are few applications that I have created using this stack. Each of these applications can be started either as a
native app or as a web application.

App | Preview
-----|--------
**Tweet2Doom State Tree Explorer** <br><br> An interactive explorer of the State Tree of the [@tweet2doom](https://twitter.com/tweet2doom) bot. Visualizes all nodes that have ever been created by players using the bot on Twitter <br><br> ➡️ [Try Online](https://tweet2doom.github.io) <br> ➡️ [Github Repo](https://github.com/ggerganov/tweet2doom-data) | <img width="1000px" src="https://user-images.githubusercontent.com/1991296/139575872-af594c30-e77a-4655-9de0-9dad25a4cf39.gif"></img>
**Wordle-bg** <br><br> A wordle clone in Bulgarian <br><br> ➡️ [Try Online](https://wordle-bg.ggerganov.com) <br> ➡️ [Github Repo](https://github.com/ggerganov/wordle-bg) | <img src="https://user-images.githubusercontent.com/1991296/149661701-62093ce4-c97a-43b9-b9bf-5641fd6a9474.png" style="display: inline-block; overflow: hidden; width: 99%;"></img>
**GGMorse** <br><br> Real-time Morse code audio decoder <br><br> ➡️ [Try Online](https://ggmorse.ggerganov.com) <br> ➡️ [Github Repo](https://github.com/ggerganov/ggmorse) | <video src="https://user-images.githubusercontent.com/1991296/128624314-9bca1f73-9575-40f5-aa6e-0b4fb2b31d29.mp4"></video>
**Spectrogram** <br><br> Real-time audio spectrum visualizer <br><br> ➡️ [Try Online](https://spectrogram.ggerganov.com) <br> ➡️ [Github Repo](https://github.com/ggerganov/ggwave/tree/master/examples/spectrogram) | ![image](https://user-images.githubusercontent.com/1991296/109423222-50817600-79e7-11eb-9373-0e50aaf6376b.png)
**Waver** <br><br> Data-over-sound tool - send and receive text messages through sound <br><br> ➡️ [Try Online](https://waver.ggerganov.com) <br> ➡️ [Github Repo](https://github.com/ggerganov/ggwave/tree/master/examples/waver) | <a href="https://user-images.githubusercontent.com/1991296/109400988-a48f4a80-7954-11eb-9211-3640fc41568b.mp4"><img width="100%" src="https://user-images.githubusercontent.com/1991296/109401710-d7d3d880-7958-11eb-9b7e-364be0b4cf55.gif"></img></a>
**Keytap** <br><br> Proof-of-concept for acoustic keyboard eavesdropping <br><br> ➡️ [Try Online](https://keytap.ggerganov.com) <br> ➡️ [Github Repo](https://github.com/ggerganov/kbd-audio) | <p align="center"><a href="https://youtu.be/2OjzI9m7W10"><img alt="Keytap demo" src="https://camo.githubusercontent.com/09496b376b4e1aed862406b0fdb2b829211b170f0285113a0282c68ffb344269/68747470733a2f2f692e696d6775722e636f6d2f465861363050722e676966"></img></a><br><i>Click to watch a Youtube video</i></p>
**Keytap2** <br><br> Acoustic keyboard eavesdropping based on language n-gram frequencies <br><br> ➡️ [Try Online](https://keytap2.ggerganov.com) <br> ➡️ [Github Repo](https://github.com/ggerganov/kbd-audio) | <p align="center"><a href="https://www.youtube.com/watch?v=jNtw17S6SR0"><img width="99%" alt="Keytap2 demo" src="https://user-images.githubusercontent.com/1991296/102075434-eb1de000-3e0e-11eb-9029-e2f03216c3e0.gif"></img></a><br><i>Click to watch a Youtube video</i></p>
**wave-gui** <br><br> Yet another data-over-sound tool <br><br> ➡️ [Try Online](https://wave-gui.ggerganov.com) <br> ➡️ [Github Repo](https://github.com/ggerganov/wave-gui) | ![image](https://user-images.githubusercontent.com/1991296/160249176-fc1c629a-9055-4f36-a1c9-fbe03b444424.png)
