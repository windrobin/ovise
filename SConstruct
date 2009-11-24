# -*- python -*-
import os
import platform

myplatform = platform.system()

### Setting up environment
env = Environment(ENV = os.environ)

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
    wxconfigcmd = '/usr/local/bin/wx-config'
    wxconfigcxx = wxconfigcmd + ' --cxxflags'
    wxconfiglibs = wxconfigcmd + ' --libs'
    wxconfigoplibs = wxconfigcmd + ' --optional-libs propgrid aui'
elif(myplatform == 'Darwin'):
    wxflags_cmd = '/Users/martinloesch/Source/local/bin/wx-config --cxxflags --libs'
else:
    print 'Platform not yet supported.'
    Exit(1)
env.ParseConfig(wxconfigcxx)
env.ParseConfig(wxconfiglibs)
env.ParseConfig(wxconfigoplibs)

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

## System
if(myplatform == 'Linux'):
    linux_project_cc_flags = {'CCFLAGS':Split('''-c
                                                -Wno-non-virtual-dtor
                                                -Wno-reorder
                                                -MD
                                                -fno-common''')}
    env.MergeFlags(linux_project_cc_flags)

    linux_platform_include_paths = {'CPPPATH': Split('''/usr/include/gtk-2.0
                                                        /usr/lib/gtk-2.0/include
                                                        /usr/include/cairo
                                                        /usr/include/glib-2.0
                                                        /usr/lib/glib-2.0/include
                                                        /usr/include/pango-1.0
                                                        /usr/include/atk-1.0
                                                        /usr/lib/atk-1.0/include''')}
    env.MergeFlags(linux_platform_include_paths)

    linux_platform_libraries = {'LIBS':['gcc', 'GL']}
    env.MergeFlags(linux_platform_libraries)
elif(myplatform == 'Darwin'):
    mac_platform_include_paths = {'CPPPATH':['']}
    env.MergeFlags(mac_platform_include_paths)

    mac_platform_libraries = {'LIBS':['gcc', 'System', 'stdc++', 'SystemStubs']}
    env.MergeFlags(mac_platform_libraries)
else:
    print 'Platform not yet supported.'
    Exit(1)

# Debug builds
SConscript('OViSEdotSceneInterpreter/SConscript', variant_dir='build/OViSEdotSceneInterpreter/debug', duplicate=0, exports={'MODE':'debug', 'env':env})
SConscript('OViSEdotSceneBase/SConscript', variant_dir='build/OViSEdotSceneBase/debug', duplicate=0, exports={'MODE':'debug', 'env':env})
SConscript('OViSEAux/SConscript', variant_dir='build/OViSEAux/debug', duplicate=0, exports={'MODE':'debug', 'env':env})
SConscript('OViSE/SConscript', variant_dir='build/OViSE/debug', duplicate=0, exports={'MODE':'debug', 'env':env})
