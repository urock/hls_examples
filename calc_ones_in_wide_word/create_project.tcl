
open_project -reset calc_ones

add_files  ./src/fpga.cpp
add_files -tb ./src/main.cpp

set_top top

open_solution "solution1"
set_part {xczu9eg-ffvc900-1-e}
create_clock -period 3 -name default


