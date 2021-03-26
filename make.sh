g++ main.cc
echo "running"
./a.exe > output.ppm
echo; echo "converting"
magick convert output.ppm output.png
code output.png
