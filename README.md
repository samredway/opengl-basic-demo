# OpenGl Basic Demo

Playing around with OpenGL to satisfy an interest in low level GPU operations.

Whether it be OpenGl, frameworks like CUDA that are focussed on ai applications, or some other library GPU operations, when looked at closer to the machine all work in an essentially similar manner. We take small snippets of code and compile them to be sent to the GPU (in this case the snippets are written in GLSL - graphics library shader language). These functions can then be used over and over by multiple cores of the GPU to do thousands of parallel computations.

In this case for OpenGL the computations are primarily going to be vector transformations on 4 dimensional vectors (x, y, z, w) where x, y, z are positions in 3 dimensional space and w is the perspective division.

By compiling our transformation functions and sending them to the GPU it allows us to calculate transformations on thousands of coordinates in parallel - which is essential for high performance graphical rendering.

To see how the shaders are setup take a look in src/opengl_basic_demo/shaders.hpp and .cpp files.
