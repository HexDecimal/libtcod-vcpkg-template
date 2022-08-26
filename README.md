## How this works

This is a CMake project which uses Vcpkg for dependency management.

You need CMake and a compiler which CMake can recognize.
Vcpkg is setup as a submodule and does not need to be installed separately.

Compiling this program from an IDE such as VSCode will invoke CMake which in turn invokes Vcpkg.
Vcpkg fetches and builds all dependencies required by the project and CMake will compile and link them.
This means you do not have to manually handle dependencies as they are all handled by the toolchain.

The [src/](src/) directory holds a hello world program.
CMake has been configured to compile all `*.cpp` files in this directory to create a new program.
You should edit or replace the sources in this directory to create your program.
If you do not want to use this directory then you can modify which files are collected in [CMakeLists.txt](CMakeLists.txt).

A workflow exists at [.github/workflows/cmake.yml](.github/workflows/cmake.yml) which automatically compiles the program for Windows, macOS, and Ubuntu Linux.
The workflow simply invokes CMake directly, since this setup does not depend on a specific IDE to work.
Actions which pass without fail will provide archived executables to test with, these are temporary and are downloaded from the passing action under *automated-builds*.
To permanently publish these builds you can push an annotated tag named after the version of the build, such as `1.0.0` or `2000.12.30`.

## How to setup

* Make sure you have the correct tools ready.
  * For example on Windows:
    Make sure you install the C++ compiler tools from [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/),
    install the latest [CMake](https://cmake.org/download/),
    and install [Visual Studio Code](https://code.visualstudio.com/download).
* [Create a new repository from ths template](https://docs.github.com/en/github/creating-cloning-and-archiving-repositories/creating-a-repository-on-github/creating-a-repository-from-a-template#creating-a-repository-from-a-template).  **You do not use the GitHub fork button unless you're contributing.**
* [Clone your new repository](https://docs.github.com/en/github/creating-cloning-and-archiving-repositories/cloning-a-repository-from-github/cloning-a-repository).
* Make sure to initialize the `vcpkg` [submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules).  If the `vcpkg` folder is empty or missing then the build process will fail.
  * The command to do this is: `git submodule update --init --recursive`
* Load this project in VS Code and install any recommended plugins.
  Most importantly: *C/C++*, *C++ Intellisense*, and *CMake Tools*.
* Using the CMake Tools plugin you can now build and run this project.  Dependencies will automatically be installed via Vcpkg.
  * On Windows, when CMake Tools asks for a toolkit you should select `Visual Studio Community ... - amd64`.
  * When CMake Tools asks for a project select `libtcod-vcpkg-template`.
* The project will now build and run with F5.
  You should edit the `CMakeLists.txt` script as needed to expand your project.

Now that you know the template works you'll want to take care the following:

* Replace the license in [LICENSE.txt](LICENSE.txt) with your own, see [choosealicense.com](https://choosealicense.com/).
* Modify [vcpkg.json](vcpkg.json) to include any libraries [from Vcpkg](https://vcpkg.info/) that you want to use such as the popular [fmt](https://fmt.dev/latest/index.html) library.
  You'll need to add these libraries to [CMakeLists.txt](CMakeLists.txt) to link them.
* Change `libtcod-vcpkg-template` in [CMakeLists.txt](CMakeLists.txt) and [.github/workflows/cmake.yml](.github/workflows/cmake.yml) to the name of your game.
  You may want to edit other parts of the CMake script as well, such as the included source files.
* Verify the style settings in [.clang-format](.clang-format) and [.editorconfig](.editorconfig).

## Configuring submodules

After you run `git submodule update --init` you can setup the submodules by going into their initialized submodule directories and checking out the desired commits.
See the [Git Documentation on Submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules).

To update SDL, libtcod, or any other dependency fetched with `vcpkg` you should go into the `vcpkg` folder and then checkout and pull its `master` branch to get the most recent ports.
