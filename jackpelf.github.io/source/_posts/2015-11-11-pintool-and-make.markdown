---
layout: post
title: "pintool&amp;make"
date: 2015-11-11 22:39:31 +0800
comments: true
categories: 
---
###pintool
pintool由main开始
如果程序使用符号，要调用PIN_InitSymbols()
初始化函数PIN_Init(argc,argv)

PIN tool分为

    INS_AddInstrumentFunction
    TRACE_AddInstrumentFunction
    IMG_AddInstrumentFunction
    RTN_AddInstrumentFunction

其中后两种需要PIN_InitSymbols

###linux include
g++找到头文件的路径
CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:/usr/include/libxml2:/MyLib
export CPLUS_INCLUDE_PATH

gcc找到头文件的路径
C_INCLUDE_PATH=/usr/include/libxml2:/MyLib
export C_INCLUDE_PATH

对所有用户有效在/etc/profile增加以下内容。只对当前用户有效在Home目录下的
.bashrc或.bash_profile里增加下面的内容


###make命令
make -f 描述性文件

###pin how to use
references:
https://software.intel.com/sites/landingpage/pintool/docs/71313/Pin/html/index.html#EXAMPLES


    To build all examples in a directory for ia32 architecture:
    $ make all TARGET=ia32

    To build all examples in a directory for intel64 architecture:
    $ make all TARGET=intel64
    
    To build and run a specific example (e.g., inscount0):
    $ make inscount0.test TARGET=intel64
    
    To build a specific example without running it (e.g., inscount0):
    $ make obj-intel64/inscount0.so TARGET=intel64
    
    The above applies to the Intel(R) 64 architecture. For the IA-32 architecture, use TARGET=ia32 instead.
    $ make obj-ia32/inscount0.so TARGET=ia32
    

###source

    
    /*BEGIN_LEGAL 
    Intel Open Source License 
    
    Copyright (c) 2002-2015 Intel Corporation. All rights reserved.
     
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are
    met:
    
    Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.  Redistributions
    in binary form must reproduce the above copyright notice, this list of
    conditions and the following disclaimer in the documentation and/or
    other materials provided with the distribution.  Neither the name of
    the Intel Corporation nor the names of its contributors may be used to
    endorse or promote products derived from this software without
    specific prior written permission.
     
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
    A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE INTEL OR
    ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
    END_LEGAL */
    #include <iostream>
    #include <fstream>
    #include "pin.H"
    
    ofstream OutFile;
    
    // The running count of instructions is kept here
    // make it static to help the compiler optimize docount
    static UINT64 icount = 0;
    
    // This function is called before every instruction is executed
    VOID docount() { icount++; }
        
    // Pin calls this function every time a new instruction is encountered
    VOID Instruction(INS ins, VOID *v)
    {
        // Insert a call to docount before every instruction, no arguments are passed
        INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)docount, IARG_END);
    }
    
    KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
        "o", "inscount.out", "specify output file name");
    
    // This function is called when the application exits
    VOID Fini(INT32 code, VOID *v)
    {
        // Write to a file since cout and cerr maybe closed by the application
        OutFile.setf(ios::showbase);
        OutFile << "Count " << icount << endl;
        OutFile.close();
    }
    
    /* ===================================================================== */
    /* Print Help Message                                                    */
    /* ===================================================================== */
    
    INT32 Usage()
    {
        cerr << "This tool counts the number of dynamic instructions executed" << endl;
        cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
        return -1;
    }
    
    /* ===================================================================== */
    /* Main                                                                  */
    /* ===================================================================== */
    /*   argc, argv are the entire command line: pin -t <toolname> -- ...    */
    /* ===================================================================== */
    
    int main(int argc, char * argv[])
    {
        // Initialize pin
        if (PIN_Init(argc, argv)) return Usage();
    
        OutFile.open(KnobOutputFile.Value().c_str());
    
        // Register Instruction to be called to instrument instructions
        INS_AddInstrumentFunction(Instruction, 0);
    
        // Register Fini to be called when the application exits
        PIN_AddFiniFunction(Fini, 0);
        
        // Start the program, never returns
        PIN_StartProgram();
        
        return 0;
    }

###compile
    
    make inscount0.test TARGET=intel64

###run

    ../../../pin.sh -t obj-intel64/inscount0.so -- ./a.out
    
    
###  result

    cat inscount.out
