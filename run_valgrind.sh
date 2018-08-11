tput reset; 
#valgrind --leak-check=yes --show-possibly-lost=no   --suppressions=valgrind/qt.suppr --gen-suppressions=yes ./mzterm
valgrind --leak-check=yes --show-possibly-lost=no   --suppressions=valgrind/qt.suppr ./mzterm

