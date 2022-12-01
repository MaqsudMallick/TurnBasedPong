import os
os.system('g++ main.cpp -o example.exe -Wall -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm')
os.system('example.exe')