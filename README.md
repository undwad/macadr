macadr
=====
crossplatform mac address reader for lua 5.2

WINDOWS:

macadr depends on lua 5.2 that can be downloaded from http://luabinaries.sourceforge.net/

also there is visual c++ project file macadr.vcxproj.

if you have incompatible version of visual studio then simply create new dynamic library project, 
add project source and header files, module definition file and libraries.
anyway CMakeLists.txt is provided so it is possible to use cmake.

LINUX:

macadr depends on lua5.2 and liblua5.2 that can be installed with apt-get.

anyway cmake will tell you what's missing.

unfortunately I don't how to configure cmake to produce libraries without lib prefix,
so after building libmacadr.so module you need either rename it to macadr.so or create appropriate symbolic link,
so that lua could find it. 

COMMON:

macadr has only one function named read that can be used like this:

require 'macadr'
mac = macadr.read{ip='192.168.10.101', port=80, attempts=100, timeout=1}
print(mac)

where port, attemps and timeout are not used in windows 

attempts is optional and defaults to 1000
timeout is optional and defaults to 5 

you can look through output/test.lua sample script for more detailed information.
 
2013.10.24 15.58.37 undwad, samara, russia