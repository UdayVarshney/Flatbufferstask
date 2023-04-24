# flatbuffer-task
First we will create the schema and after the schema is created we will compile the schema using flatc compiler 
./../flatc --cpp task1_schema.fbs
./../flatc --python task1_schema.fbs

To compile the encoder, a file path is given to the bin file which will be generated to that directory and we will compile the encoder code using compiler 
C:\MinGW\bin\g++.exe

The same file path is given to the binary file in decoder and we can run the decoder code 
