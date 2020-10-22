# Spam Filter

This program replicates an email filtering system, in which spam is identified based on a "spam list" and is excluded from an output file that contains only non-spam emails. The program uses a C++ vector to input the data from the text files in order to perform certain operations.

## Usage

The program has four commands:

1. load [spam list file name].txt
2. display
3. check [single email string]
4. filter [emails file name].txt [new specified output file name].txt
5. \#

### load

```
Enter command or # to exit> load spamlist1.txt
Loading 'spamlist1.txt'
# of spam entries: 12
```
This will load the spamlist, in this case 'spamlist1.txt', into the program to use in other commands

### display

```
Enter command or # to exit> display
aaa.com:user
bestbuy.com:coupons
bestbuy.com:offers
groupon.com:*
groupon.com:reseller
important.com:dont_ignore
massemail.com:*
organicfoods.com:noreply
uic.edu:accc
uic.edu:chancellor
uic.edu:rewards
xyz.com:user1
```

This will display the contents of the spamlist, which in this case is'spamlist1.txt'

### check

```
Enter command or # to exit> check offers@groupon.com
offers@groupon.com is spam
```

This will check a particular email address, in this case 'offers@groupon.com', to see if it's spam

### check

```
Enter command or # to exit> filter emails1.txt output1.txt
# emails processed: 21
# non-spam emails: 11
```

This will filter an email list, in this case 'emails1.txt', with a spamlist, in this case 'spamlist1.txt', and output the resulting non-spam emails into a new file (which has its name specified by the user)

### \#

```
Enter command or # to exit> #
```

This will terminate the program

## Build/Compile (_with GNU C++ Compiler_)

A makefile has been provided for compilation and running.

First, `cd` into the project directory

```
make build
```

_This will compile main.cpp and create a corresponding object file, which will be linked as an executable

## Run

After building/compiling, the executable must be run within the same project directory

```
./build
```

_This will initiate your program


**_\*Note:_** An executable file `program.exe` has also been provided if the user would like to skip the Build/Compile and Run steps
