// #include "locality.cpp"
#include "locality.h"
#include <iostream>
#include <fstream>
#include <sstream>


/**
 * @brief get the arguments from user input
 *
 */
// void get_args(int argc, char *argv[]) {

//     int opt;
//     /* default parameters */
//     verbose_mode = false;
//     Setbits_s = 1;
//     NumLines_E = 1;  //-E
//     Blockbits_b = 4; //-b
//     trace_file = NULL;
//     while ((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
//         switch (opt) {
//         case 'h':
//             printf("Usage: ./csim [-hv] -s <s> -E <E> -b <b> -t <tracefile>\
//                 -h: Optional help flag that prints usage info\
//                 -v: Optional verbose flag that displays trace info\
//                 -s <s>: Number of set index bits \
//                 -E <E>: Associativity (number of lines per set)\
//                 -b <b>: Number of block bits \
//                 -t <tracefile>: Name of the memory trace to replay");
//             break;
//         case 'v':
//             // printf("dispaly trace set to true\n");
//             verbose_mode = true;
//             break;
//         case 's':
//             Setbits_s = (unsigned long)atoi(optarg);

//             break;
//         case 'E':
//             NumLines_E = (unsigned long)atoi(optarg);

//             break;
//         case 'b':
//             Blockbits_b = (unsigned long)atoi(optarg);

//             break;
//         case 't':
//             trace_file = fopen((const char *)optarg, "r");
//             // printf("trace file name:  %s\n", optarg);
//             break;
//         default:
//             printf("format not recoginzed, use -h option for help");
//         }
//     }
// }

int main(int argc, char *argv[]) {
    /* creating a locality monitor obj */
    locality locality_monitor;
    
    /* call this to record traces both store (W) and load (R)*/
    // Open the trace file
    std::ifstream trace_file("trace.txt");
    if (!trace_file.is_open()) {
        std::cerr << "Failed to open trace file!" << std::endl;
        return -1;
    }

    // Parse the trace and insert each memory access to the locality object
    std::string line;
    while (std::getline(trace_file, line)) {
        std::istringstream iss(line);
        uint64_t address, pc;
        char access_type;
        if (!(iss >> std::hex >> pc >> access_type >> std::hex >> address)) {
            
            std::cerr << "Failed to parse trace file line: " << line << std::endl;
            
            continue;
        }
        std::cout << "pc: " << pc << std::hex << std::endl;
        std::cout << "pc: " << pc << std::hex << std::endl;
        std::cout << "access_type: " << access_type << std::endl;
        std::cout << "address: " << address << std::hex << std::endl;
        locality_monitor.push_address(address, 8); // sizeof(address) = 8
    }
    
    

    /* finish */
    locality_monitor.calculate_locality();
    // spatial_l.set(locality_monitor.get_spatial_locality()*10000);
    // temporal_l.set(locality_monitor.get_temporal_locality()*10000);
    uint64_t spatial_locality = locality_monitor.get_spatial_locality();
    uint64_t temporal_locality = locality_monitor.get_temporal_locality();

    // Print the results
    std::cout << "Spatial locality: " << spatial_locality << std::endl;
    std::cout << "Temporal locality: " << temporal_locality << std::endl;


}

