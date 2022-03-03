# SYS-MONITOR
A central monitoring system built using basic client-server model to collect system information from multiple nodes over a network. This system information is being sent periodically to a server to update about its state with following parameters:

* __System-name__

* __RAM usage__

* __CPU utilization__

* __System Idle window__

* __Disk utilization__

* __Processor Information etc.__

The user can access the system information by selecting the options from a menu driven program.


### How to Establish the Database Connection
1. Download and install MySQL Installer ​

2. Using MySQL Installer install: ​

     a. MySQL Community Server 8.0.11 ​

     b. MySQL Connector/C++ version 8.0.11 ​

3. Update the relevant include and lib directories in Visual Studio Community ​

    1. Go to Project Properties > C/C++ > General > Additional Include Directories and update​

         a. C:\Program Files\MySQL\Connector C++ 1.1\include ​

         b. C:\Program Files\MySQL\MySQL Server 8.0\include ​

    2. Go to Project Properties > Linker > General > Additional Library Directories and update​

        a. C:\Program Files\MySQL\Connector C++ 1.1\lib\opt ​

        b. C:\Program Files\MySQL\MySQL Server 8.0\lib ​

    3. Go to Project Properties > Linker > Input > Additional Dependencies and update​

        a. mysqlcppconn.lib ​

        b. libmysql.lib​

4. Code, build, run ​

   a. Copy libmysql.dll from C:\Program Files\MySQL\MySQL Server 8.0\lib to the executable directory ​

   b. Copy libcrypto-1_1-x64.dll and libssl-1_1-x64.dll from C:\Program Files\MySQL\MySQL Server 8.0\bin ​

       to the executable directory.

## STEPS TO USE:

* RUN THE SERVER.EXE FILE
* RUN THE CLIENT.EXE FILE
* ENTER THE UNIQUE CLIENT IDENTIFIER.
* SELECT THE OPTION FROM DISPLAY, ACCORDING TO THE DATA YOU WANT TO SEE.

Now, You are ready to sneak through some interesting system stats.


#### PROJECT CONTRIBUTORS:-
- ##### System Interaction Team
  - Gurjot Singh
  - Himanshu Sankhla
- ##### Socket Programming Team
  - Ashish Pawar
  - Pragyan Aditya Agrawal
  - Ravpreet Singh
- ##### Database Team
  - Ridhi Narula
