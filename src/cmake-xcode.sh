mkdir obj
mkdir obj/xcode
cd obj/xcode
cmake -Wdev -G "Xcode" ../..
open *.xcodeproj
cd ../..
