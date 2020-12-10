# Design

### Motivations:
- work with C
- work with WebAssembly
- build a visual game

### Technology choices:

- **C**: I chose to program Katamino using C for the benefits of working close to the hardware; although many higher-level languages allow for greater abstraction for ease of implementation, I wanted to take the opportunity to challenge myself with the concepts learned through the CS50 course.

- **VSCode**: I wanted to set up a development for C on my local machine and chose this lightweight IDE for cross-platform ease, and great features such as Intellisense for development, and the extensive library of extensions available to support dev work.

- **SDL2**: To create the graphics for the game, I chose SDL2 because it's a cross-platform library with better portability on Windows that offers a range of low-level access to keyboard, mouse, audio and graphics.

- **WebAssembly**: As a relatively newer low-level binary format that can run natively in the browser, I chose to target the browser with C code as a demonstration of the huge portability that wasm files bring to the browser.

- **Emscripten**: Although there are other clang/LLVM toolchains to compile code to WebAssembly, Emscripten has been the de facto compiler of choice with its full  toolchain support and history of collaboration with the WebAssembly working group.

- **GCC**: The GCC is a popular C compiler and I chose this as it had full cross-platform support on OSX/Windows/Linux.

### Options considered:
- **OpenGL**: OpenGL is another popular graphics library I considered; however since the SDL2 API offered more functionality in the way of inputs, I chose to go with SDL2 as the graphics library to learn.

- **Visual Studio**, See "Mingw-w64/platform." I also considered this full-fledged IDE for troublshooting the SDL2_gfx issue I had on Windows; I ended up jumping to OSX afterwards.
- **CodeBlocks**:  See "Mingw-w64/platform". I also considered this open source IDE when trying to troubleshoot the SDL2_gfx issue on Windows; I ended up jumping to OSX afterwards.

- **Mingw-w64/Platform**: I started out on a Windows environment using mingw-w64, which minus a few bumps, was going rather well; however I ran into issues once I tried to incorporate the SDL2_gfx library, as it only supported a Win32 target, whereas I was targeting a x64 architecture. After a crippling amount of time spent trying as many ways around it as I could (Visual C++ compiler, all types of dlls, Windows Subsystem for Linux but I got blocked by x11 forwarding necessary for the display), I dusted off an old Macbook I had and went all in on a Unix based OS.

### Implementation details:

The program is adapted from [this](https://github.com/dashed/tetris-sdl-c) tetris game.

When the program starts, graphics are first initialized and then an infinite loop is started that polls for user events and updates the display until the program exits. To make this compatible for the wasm format, if the Emscripten preprocessor is detected, then we use the `emscripten_set_main_loop` function to simulate an infinite loop in the browser so as not to block the browser execution environment which would result in a stuck or hanging browser. This function implements an asynchronous loop so that control can return to the browser to manage other tasks.

For each iteration of the main loop, the program runs:
1. `prerender` - sets the SDL2 render target to itself to prepare for any potential paints to the display
2. `handle_user_events` - polls for any input events from the user; we are looking for keyboard events in this case
3. `update_game` - if there is a user event, we update the game based in the input, i.e., pentamino movements
4. `update_render` - this function will render any display updates and reset the boolean flag marking whether we need to update the display
5. `SDL_Delay` - this SDL2 function specifies the wait delay in milliseconds to keep the frame rate constant

If the user exits the program, we cleanup the renderer and window graphics and all SDL2 subsystems. Additionally, if the code has been preprocessed by Emscripten, we call the `emscripten_cancel_main_loop` function to cancel the main loop.

For the Katamino game itself, the pieces are stored as hexadecimal representations of binary digits. For example, a piece can be visualized as:
```
  ##
 ###

```
or as the binary digit `0000111011000000`, represented in a 4x4 matrix as following:
```
0000
0011
0111
0000

```
`0000111011000000` is the hexadecimal number `0xEC0` which is then stored as one of 4 possible rotations of the piece the `rotation` array in the `Pentamino` struct.

With this data, we can then assemble a Katamino game of 3 pieces, each with its own rotation array, color, and extensibly with an x and y coordinate as well as the current rotation index.

Central to the game updates is 