import os
os.system('windres resources.rc lib/libres.a')
os.system('g++ main.cpp -o TurnPong.exe -mwindows -Wall -Wno-missing-braces -I include/ -L lib/ -lres -lraylib -lopengl32 -lgdi32 -lwinmm')
# os.system('TurnPong.exe')