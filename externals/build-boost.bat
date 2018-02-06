cd "boost-1.66.0"
b2.exe -j 4 toolset=msvc-14.0 address-model=64 threading=multi link=static runtime-link=shared --build-type=complete stage
cd ..
