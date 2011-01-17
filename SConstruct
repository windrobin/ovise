# -*- python -*-
import os
import platform
import sys

myplatform = platform.system()

# Setting up the configuration file
variables = Variables("custom.py")
variables.Add(PathVariable('WXCONFIG',
                           'Path to wx-config',
                           '/usr/local/bin/'))
variables.Add(BoolVariable('OGRE_PKG',
                           'Set to True if Ogre flags shall be retrieved via pkg-config',
                           'True'))
variables.Add(PathVariable('OGRE_PATH',
                           'Path to Ogre directory (only used if OGRE_PKG is 0)',
                           ''))

### Setting up environment
colors = {}
colors['cyan']   = '\033[96m'
colors['purple'] = '\033[95m'
colors['blue']   = '\033[94m'
colors['green']  = '\033[92m'
colors['yellow'] = '\033[93m'
colors['red']    = '\033[91m'
colors['end']    = '\033[0m'

#If the output is not a terminal, remove the colors
if not sys.stdout.isatty():
   for key, value in colors.iteritems():
      colors[key] = ''

compile_source_message = '%sCompiling %s==> %s$SOURCE%s' % \
   (colors['blue'], colors['purple'], colors['yellow'], colors['end'])

compile_shared_source_message = '%sCompiling shared %s==> %s$SOURCE%s' % \
   (colors['blue'], colors['purple'], colors['yellow'], colors['end'])

link_program_message = '%sLinking Program %s==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

link_library_message = '%sLinking Static Library %s==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

ranlib_library_message = '%sRanlib Library %s==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

link_shared_library_message = '%sLinking Shared Library %s==> %s$TARGET%s' % \
   (colors['red'], colors['purple'], colors['yellow'], colors['end'])

env = Environment( ENV = os.environ,
  CXXCOMSTR = compile_source_message,
  CCCOMSTR = compile_source_message,
  SHCCCOMSTR = compile_shared_source_message,
  SHCXXCOMSTR = compile_shared_source_message,
  ARCOMSTR = link_library_message,
  RANLIBCOMSTR = ranlib_library_message,
  SHLINKCOMSTR = link_shared_library_message,
  LINKCOMSTR = link_program_message,
  variables = variables
)
#env = Environment(variables = variables, ENV = os.environ)
Help(variables.GenerateHelpText(env))

conf = Configure(env)
env = conf.Finish()

## wxWidgets
# command for include flags
if myplatform == 'Linux' or myplatform == 'Darwin':
    wxconfigcmd = os.path.join(env['WXCONFIG'], 'wx-config')
    wxconfigcxx = wxconfigcmd + ' --cxxflags'
    wxconfiglibs = wxconfigcmd + ' --libs std'
    wxconfigoplibs = wxconfigcmd + ' --optional-libs propgrid aui'
else:
    print 'Platform not yet supported.'
    Exit(1)
env.ParseConfig(wxconfigcxx)
env.ParseConfig(wxconfiglibs)
env.ParseConfig(wxconfigoplibs)

## Ogre3D
if myplatform == 'Linux':
    if env['OGRE_PKG'] == True:
        env.ParseConfig('pkg-config --cflags OGRE')
        env.ParseConfig('pkg-config --libs OGRE')
    else:
        ogre_include_path = {'CCFLAGS':['-I/usr/local/include', '-I' + os.path.join(env['OGRE_PATH'], 'include'), '-DOGRE_GUI_GLX', '-DOGRE_CONFIG_LITTLE_ENDIAN']}
        env.MergeFlags(ogre_include_path)
        ogre_libs = {'LIBS':['-L' + os.path.join(env['OGRE_PATH'], 'lib'), '-lOgreMain']}
        env.MergeFlags(ogre_libs)
elif(myplatform == 'Darwin'):
    mac_ogre_include_path = {'CCFLAGS':['-F' + env['OGRE_PATH']]}
    env.MergeFlags(mac_ogre_include_path)
    mac_ogre_lib_flags = {'LIBS':['-framework Ogre', '-framework Cg', '-framework Carbon']}
    env.MergeFlags(mac_ogre_lib_flags)
else:
    print 'Platform not yet supported.'
    Exit(1)
    
## Xerces
xerces_lib = {'LIBS':['xerces-c']}
env.MergeFlags(xerces_lib)
    
## Boost
env.MergeFlags( {'LIBS':['boost_system']} )

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
SConscript('Core/SConscript', variant_dir='build/Debug/Core', duplicate=0, exports={'MODE':'debug', 'env':env})
SConscript('SimplePlugin/SConscript', variant_dir='build/Debug/SimplePlugin', duplicate=0, exports={'MODE':'debug', 'env':env})
SConscript('RobotPlugin/SConscript', variant_dir='build/Debug/RobotPlugin', duplicate=0, exports={'MODE':'debug', 'env':env})
SConscript('OViSEdotSceneInterpreter/SConscript', variant_dir='build/Debug/OViSEdotSceneInterpreter', duplicate=0, exports={'MODE':'debug', 'env':env})
SConscript('OViSEdotSceneBase/SConscript', variant_dir='build/Debug/OViSEdotSceneBase', duplicate=0, exports={'MODE':'debug', 'env':env})
SConscript('OViSEAux/SConscript', variant_dir='build/Debug/OViSEAux', duplicate=0, exports={'MODE':'debug', 'env':env})
SConscript('OViSE/SConscript', variant_dir='build/Debug/OViSE', duplicate=0, exports={'MODE':'debug', 'env':env})
