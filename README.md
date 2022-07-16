# charging-functionality-and-charging-management-for-cellular-service-providers.

## In General
This project is a multithreading program written in C++ with the purpose to handle CDR files that contain CDR records which contains cellular data 
about operations that had been done by the costumers.

## Description
In this project the program read row/files and write an aggregated data (that is calculated during the execution of the program) 
from the records into a 2 hash tables data structures - one for the costumers data and the other for the providers data. the read and write
operations done simultaneously. also there is thread pool mechanism to write simultaneously to the 2 hash tables.
