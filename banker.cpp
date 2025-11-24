#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

struct Process {
    std::vector<int> alloc;
    std::vector<int> max;
    int process_id;
};

int main() {
    std::ifstream in_file("input.txt");

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

        while (processes.size()) {
            bool all_unsafe = true;
            for (size_t p = 0; p < processes.size(); p++) {
                Process* process = &processes[p];
                bool unsafe = false;
                for (int i = 0; i < 3; i++) {

                    int need = process->max[i] - process->alloc[i];
                    if (need > avail[i]) {
                        unsafe = true;
                        break;
                    }
                }

                if (!unsafe) {
                    //std::cout << process->process_id << std::endl;
                    
                    for (int i = 0; i < 3; i++) {
                        avail[i] += process->alloc[i];
                    }
                    safe_sequence.push_back(*process);
                    processes.erase(processes.begin() + p);
                    all_unsafe = false;
                    break;
                }
            }
            if (all_unsafe) {
                std::cout << "The system is not in a safe state." << std::endl;
                break;
            }
        }

        if (processes.size() == 0) {
            std::cout << "The system is in a safe state. The safe sequence is: ";

            for (Process process : safe_sequence) {
                std::cout << "P" << process.process_id << " ";
            }
            std::cout << std::endl;
        }
        
        
    } else {
        std::cout << "ERROR: Could not read input file \"input.txt\". Ensure it exists at the program's running directory!" << std::endl;
        return -1;
    }


    return 0;
}