# Mini Katamino on the Web

A puzzle game written in C compiled to [WebAssembly](https://webassembly.org/) for the browser.

Play by moving a set of pentaminos into complete rectangle.

Inspired by the Katamino [board game](https://en.gigamic.com/game/katamino) and adapted from [this](https://github.com/dashed/tetris-sdl-c) tetris game.

## Getting Started

---

### Prerequisites
- [Python](https://www.python.org/)
- [Emscripten](https://emscripten.org/index.html#)
- [SDL2](https://www.libsdl.org/download-2.0.php)
- [SDL2_gfx](https://www.ferzkopp.net/Software/SDL2_gfx/Docs/html/index.html)
- [Mingw-w64](http://mingw-w64.org/doku.php) (Windows)
- [Xcode](https://apps.apple.com/us/app/xcode/id497799835?mt=12) and XCode command line tools (OSX) 

---

### Setup environment
#### OSX
1. Download Xcode: [Link](https://apps.apple.com/us/app/xcode/id497799835?mt=12)
2. Install Xcode command line tools:
``` console
  xcode-select --install
```
3. Install SDL prerequisite libraries (using [Homebrew](https://brew.sh/)):
  ```console
  brew install sdl2
  brew install sdl2_gfx

  ```

4. Install the Emscripten SDK by following the doanload and install instructions [here](https://emscripten.org/docs/getting_started/downloads.html)

---

### Build and run:
#### <ins>Desktop</ins>
- To build the game for desktop, run this command from the root folder:
```console
make
```
- Run the game by running the executable:
```console
./katamino
```
#### <ins>Browser</ins>
- To build the game for the browser, run this command from the root folder:
```console
make wasm
```
- Run the game by running a local server such as python's http server:
```console
python -m http.server 8080
```

# Play

Goal: fit the pieces together to make a perfect rectangle


Move pieces according to the following keyboard keys:

| Action | Key |
| --- | --- |
| Move up | Up or W key |
| Move left | Left or A key |
| Move down | Down or S key | 
| Move right | Right or D key |
| Rotate piece | Space bar |
| Select next piece | Tab key |
| Reset game | R key |



# Acknowledgements
This game was adapted from https://github.com/dashed/tetris-sdl-c
# Resources
- [SDL Wiki](https://www.libsdl.org/)
- [Emscripten Docs](https://emscripten.org/index.html)
- [VSCode GCC Setup for Windows](https://code.visualstudio.com/docs/cpp/config-mingw)
- [Beginning Game Programming v2.0](https://lazyfoo.net/tutorials/SDL/index.php)
- [Gigi Labs SDL2 Tutorials](https://gigi.nullneuron.net/gigilabs/writing/sdl2-tutorials/)