# Learning-Open-GL

using MSYS2 MINGW64 in Windows 11 `g++ main.cpp glad.c -o main -lglfw3 -lopengl32 && ./main`
using ubuntu `g++ main.cpp glad.c -o main -I../../include -lglfw && ./main` 
slightly different setup

WINDOWS          
LearnOpenGL                
  src
    glad.c
    main.cpp
    main.exe

UBUNTU
── include
│   ├── glad
│   │   └── glad.h
│   └── KHR
│       └── khrplatform.h
└── learningopengl
    └── src
        ├── glad.c
        ├── main
        └── main.cpp


5/9/25
left off at https://learnopengl.com/Getting-started/Shaders
have one orange triangle that changes alpha 
have one multi color triangle


![image](https://github.com/user-attachments/assets/3124bac2-1074-4252-bc88-97273ffc63d4)
