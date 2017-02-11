//
//  main.cpp
//  lab9
//
//  Created by Vincent Lee on 11/25/15.
//  Copyright © 2015 10k Bulbs. All rights reserved.
//

#include <iostream>
#include <random>
#include <queue>

#define TIME 100
#define ARRIVAL_CHANCE 0.2f
#define DONE_CHANCE 0.3f

void runSingleQueueSimulation(int servers);
void runMultiQueueSimulation(int servers);

int main() {
    srand(time(0));
    
    int servers     = 0;
    
    while(true) {
        std::cout << "Enter the number of servers: ";
        std::cin >> servers;
        
        if(servers < 1) {
            std::cout << servers << " is not a valid number of servers. Try again." << std::endl;
            continue;
        }
        break;
    }
    
    runSingleQueueSimulation(servers);
    runMultiQueueSimulation(servers);
    
    return 0;
}


void runSingleQueueSimulation(int servers) {
    std::queue<int> q;
    int served      = 0;
    int timeClicks  = -1;
    int simTime     = 0;
    
    
    for(int i = 0; i < servers; i++) {
        q.push(0);
    }
    
    while (true) {
        timeClicks++;
        int arrivals = 0;
        float multiplier = (servers * ((-.001f)*(timeClicks - 60.0f)*(timeClicks - 60.0f) + 5));
        if(multiplier < 0) multiplier = 0;
        arrivals = (rand() % 3 + 1) * multiplier;
//        std::cout << "arrivals = " << arrivals << std::endl;
        
        for(int k = 0; k < arrivals; k++) {
            q.push(timeClicks);
        }
        
        if(!q.empty()) {
            int index = 0;
            while(index < servers && index < q.size()) {
                served++;
                simTime += timeClicks - q.front();
//                std::cout << "simTime = " << simTime << std::endl;
//                std::cout << "served = " << served << std::endl;
                q.pop();
                index++;
            }
            if(q.size() == 0) break;
        }
    }
    
    std::cout << "Average wait time for 1 queue = " << simTime/served << " time units." << std::endl;

}



void runMultiQueueSimulation(int servers) {
//    std::cout << "servers = " << servers << std::endl;
    
    std::queue<int> *lines[servers];
    int served      = 0;
    int timeClicks  = -1;
    int simTime     = 0;
    int wrappingIndex  = 0;
    
    for(int i = 0; i < servers; i++) {
        std::queue<int> *q = new std::queue<int>;
        lines[i] = q;
        lines[i]->push(0);
    }
    
loop:
    while (true) {
        timeClicks++;
//        std::cout << "timeClicks = " << timeClicks << std::endl;
        int arrivals = 0;
        float multiplier = (servers * ((-.001f)*(timeClicks - 60.0f)*(timeClicks - 60.0f) + 5));
        if(multiplier < 0) multiplier = 0;
        arrivals = (rand() % 3 + 1) * multiplier;
        
//        std::cout << "arrivals = " << arrivals << std::endl;
        
        for(int k = 0; k < arrivals; k++) {
            lines[wrappingIndex]->push(timeClicks);
            
//            std::cout << "lines[wrappingIndex]->front() " << lines[wrappingIndex]->front() << std::endl;
//            std::cout << "wrappingIndex = " << wrappingIndex << std::endl;

            
            if(wrappingIndex < servers - 1) {
                wrappingIndex++;
            } else {
                wrappingIndex = 0;
            }
        }
        
        for(int m = 0; m < servers; m++) {
            if(!lines[m]->empty()) {
//                std::cout << "lines[m] not empty " << std::endl;
                served++;
//                std::cout << "served = " << served << std::endl;
                simTime += timeClicks - lines[m]->front();
                lines[m]->pop();
            }
        }
        
        for(int z = 0; z < servers; z++) {
            if(lines[z]->size() != 0) {
                goto loop;
            }
        }

        break;
    }
    
    std::cout << "Average wait time for multiple queues = " << simTime/served << " time units." << std::endl;
    
}













