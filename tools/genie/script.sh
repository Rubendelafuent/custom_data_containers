#!/bin/bash
[ -f genie.exe ] || wget https://github.com/bkaradzic/bx/raw/master/tools/bin/windows/genie.exe 
 chmod +x genie.exe && ./genie.exe vs2017 
