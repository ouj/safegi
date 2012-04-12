mkdir obj
mkdir obj\msvc10

cd obj\msvc10
cmake ..\..\ -G "Visual Studio 10"
cd ..\..\
