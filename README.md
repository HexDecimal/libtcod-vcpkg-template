# How to setup

* Make sure you have the correct tools ready.
  * For example on Windows:
    Make sure you install the C++ compiler tools from [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/),
    install the latest [CMake](https://cmake.org/download/),
    and install [Visual Studio Code](https://code.visualstudio.com/download).
* [Create a new repository from ths template](https://docs.github.com/en/github/creating-cloning-and-archiving-repositories/creating-a-repository-on-github/creating-a-repository-from-a-template#creating-a-repository-from-a-template).
* [Clone your new repository](https://docs.github.com/en/github/creating-cloning-and-archiving-repositories/cloning-a-repository-from-github/cloning-a-repository).
* Make sure to initilize the `vcpkg` [submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules).  If the `vcpkg` folder is empty then the build process will fail.
  * The command to do this is: `git submodule update --init --recursive`
* Load this project in VS Code and install any recommended plugins.
  Most importantly: *C/C++*, *C++ Intellisense*, and *CMake Tools*.
* Using the CMake Tools plugin you can now build and run this project.  Dependences will automatically be installed via Vcpkg.
  * On Windows, when CMake Tools asks for a toolkit you should select `Visual Studio Community ... - amd64`.
  * When CMake Tools asks for a project select `libtcod-vcpkg-template`.
* The project will now build and run with F5.
  You should edit the `CMakeLists.txt` script as needed to expand your project.

## Configuring submodules

After you run `git submodule update --init` you can setup the submodules by going into their initilzed submodule directories and checking out the desired commits.
See the [Git Documentation on Submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules).

To use the development versions of libtcod: change to the libtcod subdirectory and checkout the `develop` branch with `git checkout develop`.
After that you can pull any updates to libtcod with `git pull`.

The Vcpkg submodule is updated in the same way.
Checkout and pull the `master` branch to get the most recent ports.
