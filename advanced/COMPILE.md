## Compiling on CLI
`g++ <file.cpp>` or `g++ <file.cpp> -o <filename.out>`.

The first command will output an file `./a.out`, the latter will output `/filename.out`.
Actually, for `-o <file>`, it will place the primary output in file <file>. This applies to whatever sort of output is being produced, whether it be an executable file, an object file, an assembler file or preprocessed C code.

### Run the output file
Simply type `./a.out` or `./<filename>.out` on CLI.

For linux, if you have an input file, you can do file redirecting `./a.out < input > output`, for example `./a.out < in.txt > out.txt`.

![](https://github.com/a22057916w/Data-Structure/blob/main/advanced/.meta/comple_exp.png)