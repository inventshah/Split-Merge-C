# Split and Merge Segmentation
Implementation of split and merge segmentation in C.

### How to Use
Dependencies: `png.h`

Clone: `git clone https://github.com/inventshah/Split-Merge-C.git`

Compile: `./build.sh`

Run: `./bin/main [source filename] [output filename] [tolerance]`

### Examples
Example of the split and merge steps using a tolerance of 200:

Split | Merge
:----:|:-----:
![split](images/split.png) | ![merge](images/t200.png)

Example of different tolerance values:

source | 50 | 100 | 150 | 200 | 250
:-----:|:--:|:---:|:---:|:---:|:--:
![source](images/source.png) | ![50](images/t50.png) | ![100](images/t100.png) | ![150](images/t150.png) | ![200](images/t200.png) | ![250](images/t250.png)

### Built With
* C