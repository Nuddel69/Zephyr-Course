# 2. The Zephyr Project Structure

## Zephyr Workspace

Zephyr works with a tree structure. The workspace is the root. Here you'll find
the zephyr source code, and any external *modules* installed. Applications are
placed somewhere in this tree, allowing access to all the parent files,
including the aforementioned zephyr and modules. This structure ensures you only
need a single installation of the (rather large) zephyr operating system source
code. Within the root of this workspace you'll also need a python virtual
environment. This is to install the `west` tool discussed later in the course.

> [!NOTE]
>
> ### Intermission - Your First Application
>
> You'll now create your first application. From your `ZephyrWorkspace/` create
> a new directory and call it `Blinky/`. Within this add another directory
> called `src` and one called `boards`. This will be the foundation for
> everything we do during the course.

### Modules

Modules are extensions to the Zephyr RTOS. They add additional functionality
such as drivers, HALs or subsystems. Zephyr itself features quite a few optional
modules, while you can also add as many third-party modules as you wish. These
modules are stored in the workspace root, and installed upon calling `west
update`.

What modules to include is defined by a so-called manifest. You can either use
the default one provided by zephyr, installing all the native and a
cherry-picked selection of third-party modules, or you can write your own,
allowing you to choose what modules you need, however many or few, as well as
adding any of your own. The manifest is selected upon calling `west init`. The
command by itself uses the zephyr manifest, whereas you can pass a flag, `west
init -l <manifest-repository>` to have it use a custom of your choosing.

## Build system

Zephyr, like so many other projects written in C, employs the use of a build
system to link and compile its code. It uses the Ninja system, wrapped in the
meta-system CMake. Owning to its complexity, there are several custom CMake
commands defined by Zephyr, including, but not limited to, library
initialization, source-file inclusion and a command to actually locate the
zephyr source.

> [!NOTE]
>
> ### Intermission - Exporting the Custom CMake Commands
>
> We'll need to let CMake know about our custom zephyr commands. This can be
> done by calling
>
> ```bash
> west zephyr-export
> ```

CMake, while a complex topic on its own, can be boiled down to a basic purpose:
locate source and header files, decide which to use, set some preprocessor
variables and pass dynamic flags to the compiler. CMake works with the
assumption of a main target (an arbitrary CMake construct), and your task is to
recursively add all the necessary sources to the compilation unit of the target.
When all sources are located, you'll define an include-path, telling CMake where
all your header files are located. This include-path also needs to be added to
the target. Finally, we'll link any libraries we need and link the source file
containing the program entry point.

Zephyr defines a target for us. The target is called `app`, and contains all the
sources, headers, and libraries of zephyr, as well as the main entry point for the
entire operating system. This isn't something we need to understand. What *we*
need, is to add our own sources to the operating system. We'll create our own
CMake definition at the base of our application, set the minimum required
CMake-version (for good posterity, but mostly because CMake requires it…), and
define our project name. This last one is useful for setting CMake and
preprocessor variables, but not functionally as important as the target.
Furthermore, we'll tell CMake that we're using zephyr and that it'll add some
stuff for us, before adding our entry point to the target `app`. That's it.
Zephyr does a lot of the heavy lifting in terms of CMake. You could of course
add more sources and some include-paths, but this is all that's required for a
basic application.

While we could get away just using CMake, all the extra functionality added by
zephyr would make it a hassle. To avoid manually needing to add environment
variables an include paths, zephyr comes with a meta-tool called `west`. West is
a python tool wrapping the `cmake` command giving us quite a lot of neat
functionality. In this course we'll use two of west's many subcommands. `west
build` wraps CMake, and we'll look into the other in a later section (`west flash`).

The build subcommand is almost like an alias for a long and complicated CMake
command. It knows our zephyr path, and allows us to specify board and
application. We'll piece it together bit by bit during the course, but the final
command will be `west build -b nucleo_h753zi blinky -- -DDTC_OVERLAY_FILE=boards/nucleo_h753zi.overlay`.

> [!NOTE]
>
> ### Intermission - Creating the Application CMake Definition
>
> By now the update should be done. We'll need some additional python packages,
> so let's get these over with
>
> In your application directory (`Blinky/`) create a new file and call it
> `CMakeLists.txt` (both spelling and case are important here). In this file
> you'll add the four aforementioned lines. First define the minimum CMake
> version by adding `CMAKE_MINIMUM_REQUIRED(VERSION 3.20.0)`.
>
> Next we'll tell CMake to include zephyr, and that it'll add some stuff for us.
> Add the line `find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})` next.
> This might seem like magic at first: how does CMake know of zephyr? The key is
> environment variables. These are special variables visible to commands
> launched from the terminal, usually containing paths. One such environment
> variable is the `ZEPHYR_BASE` variable. This is defined to be the location of
> your current zephyr workspace, which, as we know, contains the zephyr source
> (as well as a script configuring CMake). West, like we just talked about,
> adds several environment-variables to the execution. One of these is the
> `ZEPHYR_BASE`.
>
> After finding zephyr we'll define our project. Add the line `project(blinky)`
> to create a scope for our variables.
>
> Finally, we'll add the sources. We don't have any source files yet, but we'll
> add what will be our entry point anyway. We'll link our future C source to
> the app target created by zephyr, by adding `target_sources(app PRIVATE
> src/main.c)`.

## Boards

Zephyr relies on the concept of a *board* to know the capabilities of the
hardware you're developing for. This is a devicetree file, separated out of the
application to avoid the intermingling of hardware and software. This board
definition specifies all capabilities of an SOC. It specifies the flash area,
peripheral controllers, timers, memory regions, pin-muxers and everything else.
It does however, *not*, necessarily enable every feature required by the
application.

In order to avoid polluting the global board definition, we use an override.
This is application specific and usually placed in a boards directory. This new
devicetree file, named after the board with a `.overlay` extension, redefines
any nodes we wish to change, modifying their default properties.

## Project Configuration

As we'll later cover, `Kconfig` is the language used to configure the kernel.
After building our application we can browse all the available Kconfig options
through a user interface by calling `west build -t menuconfig`. These options
are ephemeral, but a neat way of testing out functionality. To actually make
them persistent, we'll add them to an application-wide configuration file. This
file is called `prj.conf`, lives at the base of our application and contains all
the Kconfig-options used for our application. Different applications can have
different configurations, for different flavours of the zephyr kernel.

## Next Step: [[./3_os.md]]
