cd build
rm mymalloc.o
rm main.o
rm main
cd ../
gcc -c mymalloc.c -o build/mymalloc.o
gcc -c main.c -o build/main.o
cd build
gcc main.o mymalloc.o -o main
./main
exit
