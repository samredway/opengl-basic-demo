# OpenGl Basic Demo

Playing around with OpenGL to satisfy an interest in low level GPU operations.

Whether it be OpenGl, frameworks like CUDA that are focussed on ai applications, or some other library GPU operations, when looked at closer to the machine all work in an essentially similar manner. We take small snippets of code and compile them to be sent to the GPU (in this case the snippets are written in GLSL - graphics library shader language). These functions can then be used over and over by multiple cores of the GPU to do thousands of parallel computations.

In this case for OpenGL the computations are primarily going to be vector transformations on 4 dimensional vectors (x, y, z, w) where x, y, z are positions in 3 dimensional space and w is the perspective division.

By compiling our transformation functions and sending them to the GPU it allows us to calculate transformations on thousands of coordinates in parallel - which is essential for high performance graphical rendering.

To see how the shaders are setup take a look in src/opengl_basic_demo/shaders.hpp and .cpp files.


# Running it yourself

To run it yourself you will need to git clone this repo locally and create a folder called `lib/` at the root of the project. Into this folder you need to download the GLFW lib binary which you can get here https://www.glfw.org/download. I used the latest for mac64 which is `libglfw.3.4.dylib`. I think the code should be cross platform but have only tested it on mac.

## building and running
The .vscode/ has tasks.json setup so on vscode you should be able to just click `Terminal` and `Run Task` to build the executable binary into `bin/basicdemo.out`.

If you do not have vscode you can copy the compiler flags I used and run them manually from the command line by checking in task.json at the `command` and `args` fields.

If you have run the code successfully you should see a window popup with some graphics rendered within :)
