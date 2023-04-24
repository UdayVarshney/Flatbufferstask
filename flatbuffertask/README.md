# flatbuffer-task
1. First we will download the flatc compiler for the system , which you can download from the link provided

https://github.com/google/flatbuffers/releases

2. Now we will create the schema and after the schema is created we will compile the schema using flatc compiler using commands

(i) ./../flatc --cpp task1_schema.fbs

(ii) ./../flatc --python task1_schema.fbs



3. Encoder code can be compiled using compiler MinGW and the command used to run the code:

cd "c:\Users\'Username'\Downloads\Flatbufferstask-main\Flatbufferstask-main\flatbuffertask\" ; if ($?) { g++ encoder.cpp -o encoder } ; if ($?) { .\encoder }

//Mention your desktop name in place of 'Username'

5. Decoder code is written in python language and it will read the binary file and we can run the code using python compiler and the command used to run the code:

python -u "c:\Users\'Username'\Downloads\Flatbufferstask-main\Flatbufferstask-main\flatbuffertask\decoder.py"
