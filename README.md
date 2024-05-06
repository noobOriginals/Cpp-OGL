This repo contains a project in c++, that uses OpenGL to make a tile-based game (at least that's the idea).

To be able to compile this project from the source code, you need to define a System Enviorment Variable called OPENGL_PATH, that points to the location of these files/folders on your computer:
    - GLFW/glfw3.h
    - glfw3.lib
    - glm/glm.hpp
    - glm/gtc/matrix_transform.hpp
    - glm/gtc/type_ptr.hpp
    - glad/glad.h
    - stb_image/stb_image.h

First, download cmake.
Then:

1. GLFW: https://www.glfw.org/download.html:
Download and compile using cmake.
Add the resulting glfw3.lib directly to your OPENGL_PATH and also add the GLFW folder from the include folder to your OPENGL_PATH.
There is a tutorial that's a bit more int-depth of how to do this here: https://learnopengl.com/Getting-started/Creating-a-window.

2. GLAD: https://glad.dav1d.de:
Set the Language to C/C++.
Set the specification to OpenGL.
Set the API to gl version 3.3 or higher with no gles.
No extensions.
Tick the 'generate a loder' option.
Click generate.
Then click on the generated .zip file to download it, extract its contents and add the glad folder to your OPENGL_PATH.

3. GLM: https://glm.g-truc.net/0.9.9/index.html:
Download, extract from the .zip and add the the second glm folder (the one that is inside the glm that's inside the folder you just decompressed) to your OPENGL_PATH.

4. Stb_image: https://github.com/nothings/stb/blob/master/stb_image.h:
Download the raw file 'stb_image.h'.
Inside your OPENGL_PATH, create a folder named "stb_image" and place the stb_image.h downloaded file inside it.

If you did everything right and inside your OPENGL_PATH the directories mentioned above exist, you're all set to open this project's .sln file and click run, and it should work!