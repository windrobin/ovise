Ogre Virtual Scene Framework (OViSE) Official README

1. License

The Ogre Virtual Scene Framework is licensed under

The MIT License (MIT)
Copyright (c) 2011 Alexander Kasper, Institute for Anthropomatics, Chair Prof. R. Dillmann, Karlsruhe
Institut of Technology (KIT)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and 
associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do 
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or 
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT 
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT 
OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


2. Startup
After extracting the archive, start Viewer.exe in the "bin" subfolder. You should be prompted with
a dialog selecting the "Plugins" and "Media" subfolders. This is so OViSE knows where to find the
resources and plugins. If you ever happen to move the directories, check your registry for the
OViSE-key and either change values there or delete the key (you'll be prompted with the dialog
again).

3. Notes
This precompiled version of OViSE is intended if you want a short "test drive" of what it looks
like. The default scene contains some sample entities and you should be able to load a simple 
PLY pointcloud file. Keep in mind though, that OViSE is intended as a development framework, so 
using the source and adapting the application to your needs is its real purpose. 

The provided DLLs are need for the Ogre3D engine and are bundled for convenience.

See also the separate license for the provided 3D models and textures.

4. Contact
If you have any questions, please contact Alexander Kasper (alexander.kasper@kit.edu)!
