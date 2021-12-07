# NXPLPC1768_EmbeddedC

- Template to manage I/O in LCP1768 board. Differently from the assembly startup(which is still the base of the project) the C language is exploited to perform operations in a simpler way(less instructions). This is achieved thanks to:

   1. ARM assembly and C interoperability, exploting compiler and ABI compliancy
   2. Definition of constants that simplifies program writing. In particular, constants replace addresses(i.e. pointers in C) in the context of memory mapped I/O, which refer to peripheral registers. Note that pointers can be addresses referring a simple variable, or more complex data structures(in the case the address is the pointer to the head)
   3. Usage of libraries in order to  
       - actually perform I/O((e.g. LED_out()..)
       - initialize the board to the needed state (working frequency, all led off, i/o pins configuration to accept interrupts; same for IVT ecc..), and it is user defined; indeed initialization functions are called inside of the main. There is a standard initialization of the system which does not depend on the user, and is done at system startup, before jumping to the RESET_HANDLER through the IVT

- Note that given the definition of interrupts, in the exceptions domain, this part is really different from the assembly one. That was mainly focused on the cpu internal; now instead is related to the external world. The embedded C aim is to properly make a user, a machine, a sensor interact with the cpu.
