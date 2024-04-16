#include "../header_files/internal_commands.h" // String, Vector
#include "../header_files/util.h" // String, Vector, Unistd.h
/*
@author: maria collon 
@date: 4/15/24
- implementing the shift comand, i am a bit confused on wich arguments are being passed 
- is it the external arguments, shifts argumnets or both ??? 
just for me 
user inputs  
    file.sh f1 f2 f3
    args    1  2  3 
insied of the file 
 shift 
 first case shift has no argument 
 second case 
 shift 2 
 this means that all argumnet are shifted by 2 

*/


std::string internal_shift(std::string args) {
     std::vector<std::string> input = split_string(args," "); // this gets the input form user and  puts it into a vector [f1,f2,f3,2] 
     int N = input.size(); // gives me the total size of vector size/ total number of argumnets 4 
      for (int i=0; i< N; i++){
        std::vector<std::string> n (input.at(i),input.end()); // this gets the final argumnet form the vector [2]
        if( n ='1'){
            std::string newargs = input.at(N+1);
        }else{
            //std::string newargs = input.at();
        }
      }
}