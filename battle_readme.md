# Assignment 1
### COMP 345S, Dr. Ali Jannatpour, Winter 2015
### 6 February, 2015
Written by Matthew Mongrain, #26991793.

## 1. Compilation Instructions
The program files were compiled on Ubuntu Linux 14.04 using GCC, but they should be portable to any platform that can run GCC/G++. While working in the same directory as the files,
    g++ battle*.cc -o battle.o
will compile all the source files into an executable binary called "battle.o", which can be executed using
    ./battle.o

## 2. Design Rationale
My design for the "Battle" classes was driven primarily by two factors: a desire to keep the code as encapsulated and simply written as possible, and a concomitant desire to hew as closely as possible to C++ convention as I understand it.

Since the functions of the "Battle" systems are static by definition (since they will be called by "Country" objects and never independently), I elected to construct the system using free functions within a namespace rather than using more conventional data structures such as structs or classes. Since there is no data that needs to be persisted within a single battle, there is no need for data members, one of the primary feature of the above the data structures.

My initial design was done by writing a list of the functions (and their parameters) that I thought I would need in the header file, batlle.h. The initial functions I identified as necessary were attack_is_valid(), dice() and attack(), which were developed more or less in that order. I identified the attack_is_valid() as core to the logic of the battle system; since the function is called by the central function of the system (attack()) as well as in in the main() function, it would need verbose errors to make debugging as easy as possible. (Probably exceptions are the way to handle this correctly without just passing strings as parameters, but limited time means that's a feature for next time.). This allows other functionss to leave error reporting and detection aside and be as encapsulated as possible. As the ultimate arbiter on rules, I consulted the original 1959 rules of Risk!, available on the Internet at 

The dice() function came next. The initial implementation used arrays, but using vectors instead allowed me access to a number of useful functions, in particular sort(). (Since dice are compared "best-roll-first", outputting sorted vectors of die rolls greatly simplifies the process of determining the victor of a particular encounter.)

With those functions done, the attack() function was easy to implement. The need for all_in_attack() and victory() functions then became clear, and they were added to the program. Afterwards, "fixtures" (sort of) for the Country class were added so that the battle code could run on its own, and a (flavor-text heavy) main() function was written to demonstrate the mechanics of a single battle. Parameters before the main function allow you to change the number of armies in the attacking and defending countries to observe the behaviour of the system with different initial conditions.

##3. Further documentation

Further information (particularly on the functioning of individual functions), there are comment blocks before each function (and scattered around for particular lines).
