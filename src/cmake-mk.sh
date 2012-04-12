mkdir obj
mkdir obj/mk
cd obj/mk
cmake -Wdev -G "Unix Makefiles" ../..
make all
cd ../..
