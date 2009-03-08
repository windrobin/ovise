# -*- python -*-

import os
import platform

myplatform = platform.system()

### Setting up environment

env = Environment()
if ARGUMENTS.get('verbose') != "1":
    env['CCCOMSTR'] = "Compiling $TARGET"
    env['LINKCOMSTR'] = "Linking $TARGET"

mode = ARGUMENTS.get('mode', "debug")

Help("""\nUsage:
        'scons' or 'scons mode=debug' to build debug configuration.\n
        'scons mode=release' to build release configuration.\n""")

conf = Configure(env)
if not env.GetOption('clean'):
    if(myplatform == 'Linux'):
        if not conf.CheckLib('OgreMain'):
            Exit(1)
        if not conf.CheckLib('xerces-c'):
            Exit(1)
env = conf.Finish()

## wxWidgets
# command for include flags
if(myplatform == 'Linux'):
    wxflags_cmd = '/usr/bin/wx-config --cxxflags --libs'
elif(myplatform == 'Darwin'):
    wxflags_cmd = '/Users/martinloesch/Source/local/bin/wx-config --cxxflags --libs'
else:
    print 'Platform not yet supported.'
    Exit(1)
env.ParseConfig(wxflags_cmd)

## Ogre3D
if(myplatform == 'Linux'):
    env.ParseConfig('pkg-config --cflags OGRE')
    env.ParseConfig('pkg-config --libs OGRE')
elif(myplatform == 'Darwin'):
    mac_ogre_include_path = {'CCFLAGS':['-F/org/opt/OgreSDK/Dependencies']}
    env.MergeFlags(mac_ogre_include_path)
    mac_ogre_lib_flags = {'LIBS':['-framework Ogre', '-framework Cg', '-framework Carbon']}
    env.MergeFlags(mac_ogre_lib_flags)
else:
    print 'Platform not yet supported.'
    Exit(1)

## Xerces
xerces_lib = {'LIBS':['xerces-c']}
env.MergeFlags(xerces_lib)

## PropertyGrid
if(myplatform == 'Linux'):
    property_grid_lib = {'LIBS':['wxcode_gtk2u_propgrid-2.8']}
elif(myplatform == 'Darwin'):
    property_grid_lib = {'LIBS':['']}
else:
    print 'Platform not yet supported.'
    Exit(1)
env.MergeFlags(property_grid_lib)

Export('env', 'myplatform')

SConscript('OViSEAux/SConscript', export='env')
SConscript('OViSE/SConscript', export='env')


### Debug and optimised environments
#optenv = env.Clone(CCFLAGS = '-O2')
#dbgenv = env.Clone(CCFLAGS = '-g')

### Build
#if mode == "debug":
 #   print "Building in debug configuration..."
   # OViSEDbg = dbgenv.Program('OViSE-dbg', input_files)
#elif mode == "release":
   # print "Building in release configuration..."
    #OViSEOpt = optenv.Program('/OViSE-opt', input_files)




