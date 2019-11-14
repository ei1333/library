#!/bin/bash

python make.py > library.cpp
enscript --highlight=cpp --line-numbers --color --header='Shizuoka University (team: tapu)' library.cpp -o library.ps
pstopdf library.ps
