#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

struct Process {
    std::vector<int> alloc;
    std::vector<int> max;
    int process_id;
};

int main(int argc, char *argv[]) {
    if ((argc != 2)) {
        std::cout << "Usage: ./banker <input file>" << std::endl;
        return -1;
    } 
    char* file_name = argv[1];
    std::ifstream in_file(file_name);

    std::vector<Process> processes;
    std::vector<Process> safe_sequence;

    if (in_file.is_open()) {
        std::string line;
        getline(in_file, line);
        std::stringstream in_line(line);
        std::vector<int> avail;

        std::string num;
        while (in_line >> num) {
            int inum = std::stoi(num);
            avail.push_back(inum);
        }

        //Get resource type length
        int resource_types = avail.size();

        //Empty line
        getline(in_file, line);

        int process_id = 0;
        while (getline(in_file, line)) {
            in_line.str("");
            in_line.clear();
            in_line << line;

            std::vector<int> alloc;
            std::vector<int> max;
            
            Process process{alloc, max, process_id};
            
            while (in_line >> num) {
                int inum = std::stoi(num);
                process.alloc.push_back(inum);
            }
            getline(in_file, line);
            in_line.str("");
            in_line.clear();
            in_line << line;

            while (in_line >> num) {
                int inum = std::stoi(num);
                process.max.push_back(inum);
            }

            //Empty line
            getline(in_file, line);
            
            processes.push_back(process);
            process_id++;
        }

        //Iterate through all processes that are currently awaiting resources...
        //...until all are satisfied (processes.size() == 0)
        while (processes.size()) {
            //This check is set to false whenever a process is in a safe state.
            //If this check remains true after checking through all processes in the list,
            //the system is not in a safe state.
            bool all_unsafe = true;

            for (size_t p = 0; p < processes.size(); p++) {
                Process* process = &processes[p];
                bool unsafe = false; //This checks if the current process shall be placed in the safe sequence.
                for (int i = 0; i < resource_types; i++) {
                    //Perform the calculations needed to determine how much a process needs, and if
                    //the system has sufficient resources for it.
                    int need = process->max[i] - process->alloc[i];
                    if (need > avail[i]) {
                        //This process cannot go in the safe sequence yet, proceed to the next process in the queue
                        unsafe = true;
                        break;
                    }
                }

                if (!unsafe) { //A process is added to the safe sequence.                    
                    for (int i = 0; i < resource_types; i++) { //Replenish available resources.
                        avail[i] += process->alloc[i];
                    }
                    //Push to safe sequence, remove from queue of processes awaiting resources.
                    safe_sequence.push_back(*process);
                    processes.erase(processes.begin() + p);

                    //Run through the cycle of checking each process again
                    //(minus the one added to the safe sequence)
                    all_unsafe = false;
                    break;
                }
            }
            //The system is not in a safe state
            if (all_unsafe) {
                std::cout << "The system is not in a safe state." << std::endl;
                break;
            }
        }
        //If the program reaches this point, the system is in a safe state.
        //There are no more processes that would still be awaiting resources.
        //Proceed to print out the safe sequence.
        if (processes.size() == 0) {
            std::cout << "The system is in a safe state. The safe sequence is: ";

            for (Process process : safe_sequence) {
                std::cout << "P" << process.process_id << " ";
            }
            std::cout << std::endl;
        }
    } else {
        std::cout << "ERROR: Could not read input file" << file_name << "." << std::endl;
        return -1;
    }

    in_file.close();

    return 0;
}