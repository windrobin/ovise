# Introduction #

This page lists everything you need to do in order to (hopefully) get OViSE up and running on your system.


## Prerequisites ##

### Windows ###

  * Download wxWidgets and put it in a folder (e.g. c:\wxWidgets-2.9.0). Then build wxWidgets using the provided project files (see the documentation in the [wiki](http://wiki.wxwidgets.org/Microsoft_Visual_C%2B%2B_Guide). Create an environment variable called **WX\_HOME** and point it to the root directory of wxWidgets.

  * Download and install Boost from www.boost.org. You'll need at least version 1.44.0, later versions might work, though are not tested. You should have an environment variable **BOOST\_ROOT** pointing to your Boost installation directory (there should be a include and a lib subdirectory)

  * Download and install the appropriate SDK for Ogre 1.7.3 "Cthuga". Try out some of the demos included. The installer should set a new environment variable called **OGRE\_HOME**. In case you get an error about missing dlls you'll probably need to install the Microsoft DirectX SDK, which you should get [here](http://www.microsoft.com/downloads/details.aspx?FamilyID=ea4894b5-e98d-44f6-842d-e32147237638&DisplayLang=en).

  * To run OViSE, you have to copy some .dll-files by hand into the /bin/Debug or /bin/Release directory. The following list is necessary for debug-build. In case of a release-build use the similar files without a 'd' or '_d' (for debug) at end of filename._| Package | To| From | Comment |
|:--------|:--|:-----|:--------|
| Ogre3D  | /bin/Debug |  /OGRE\_HOME/bin/Debug/cg.dll |         |
| Ogre3D  | /bin/Debug |  /OGRE\_HOME/bin/Debug/OgreMain\_d.dll |         |
| Ogre3D  | /bin/Debug |  /OGRE\_HOME/bin/Debug/Plugin\_BSPSceneManager\_d.dll |         |
| Ogre3D  | /bin/Debug |  /OGRE\_HOME/bin/Debug/Plugin\_CgProgramManager\_d.dll |         |
| Ogre3D  | /bin/Debug |  /OGRE\_HOME/bin/Debug/Plugin\_OctreeSceneManager\_d.dll |         |
| Ogre3D  | /bin/Debug |  /OGRE\_HOME/bin/Debug/Plugin\_ParticleFX\_d.dll |         |
| Ogre3D  | /bin/Debug |  /OGRE\_HOME/bin/Debug/RenderSystem\_Direct3D9\_d.dll |         |

  * _optional: ShaRoMe interface will need a build of ShaRoMe and a environment variable **SHAROME\_HOME** (point this to the installation directory of ShaRoMe)_

  * Enjoy!

### Linux ###

Here a short description how a Installation would work. For some libs (e.g. wxWidgets) you maybe have to solve some dependencies first.

  * Download and build wxWidgets http://www.wxwidgets.org. You will need the Version 2.9.0 or higher, which your distribution most likely won't provide currently, so you have to compile it on your own or use the wxwidgets apt repository. Check if 'wx-config --version' prints the correct version.

  * Download and build Ogre 1.7.3 "Cthuga" http://www.ogre3d.org. Your distribution may provide this, so try out to get it from your distribution (e.g. sudo apt-get install under Ubuntu). Check if `pkg-config --cflags OGRE` prints sane compiler flags. If you tried to build it locally, adapt the PKG\_CONFIG\_PATH variable to make this work

  * Check out OViSE source to a folder using mercurial (e.g. /home/MyUserName/OViSE).

## Building ##
OViSE uses CMake as a build system. You should make an out-of-source build, that is you create a separate build directory where everything will be built. That way it keeps the source tree clean.

  * Create a build directory (e.g. in OViSE/build)
  * Run CMake from that directory with source path to your OViSE folder
  * If CMake doesn't find all dependencies, here's what you can do:
    * Set environment variable BOOST\_ROOT to your boost installation
    * Set environment variable OGRE\_HOME to your Ogre installation
    * Set wx-config binary path to the correct wxWidgets version
  * When CMake configuration finishes successfully, generate Makefiles or project files for your preferred IDE
  * Open the project with your IDE or just run make to build OViSE

## Running ##
The executable for OViSE is called _Viewer_. If you start OViSE for the first time, you'll be asked for a Plugin path and a Media path. Plugin path should point to the Plugins folder in your build directory. Network and visualization plugins will be loaded from here. The media path is where your Ogre mesh and material files reside, usually this is the Media folder in the OViSE distribution. This is not mandatory, but OViSE will look for a resources.cfg in this folder and parse it accordingly.

Note: In Linux it can happen that the config dialog will not correctly save your paths. If this happens OViSE will not start correctly. Open the configuration file (.OViSE in your home folder) and edit the paths there manually.

Note: If you're running Ubuntu 10.10 you might get an error about a missing gdk-pixbuf header. This is because the location of this file changed in this distribution. Workaround: symlink the old location to the new one:

` sudo ln -s /usr/include/gdk-pixbuf-2.0/gdk-pixbuf /usr/include/gtk-2.0/gdk-pixbuf `

## Documentation ##
You can generate a API documentation using doxygen. A default configuration file is supplied.