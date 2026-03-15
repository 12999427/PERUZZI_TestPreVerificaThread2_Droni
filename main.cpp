#include <atomic>
#include <cmath>
#include <iostream>
#include <time.h>
#include <bits/this_thread_sleep.h>
#include <fstream>
#include <thread>

#include "MappaDati.h"

#define BASE_FILE_PATH "fileDrone"
#define NUM_DRONES 8

std::atomic<bool> shouldProgramRun = true;
time_t starting_time;
MappaDati mappa_dati(NUM_DRONES);

std::mutex console;

int getDroneData(float * latitudine, float * longitudine, float * altitudine) {
    time_t current_time = time(NULL);
    int numDoneOra = rand() % NUM_DRONES;

    *latitudine = numDoneOra + sin((current_time - starting_time) * 0.4f)*0.5f;
    *longitudine = numDoneOra + sin((current_time - starting_time) * 0.4f)*0.5f;
    *altitudine = numDoneOra + sin((current_time - starting_time) * 0.4f)*0.5f;

    return numDoneOra;
}

void ObtainInformationThread() {
    while (shouldProgramRun) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        float latitudine; float longitudine; float altitudine; int nDrone;
        nDrone = getDroneData(&latitudine, &longitudine, &altitudine);
        if (nDrone == -1)
            exit(-1);

        mappa_dati.InserisciDato(nDrone, latitudine, longitudine, altitudine);
    }
}

void ReadCollectedInformationThread(int nDrone) {
    std::ofstream File(BASE_FILE_PATH + std::to_string(nDrone) + std::string(".csv"));
    while (shouldProgramRun) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        SingoloDato sd = mappa_dati.LeggiDati(nDrone);
        time_t time_now = time(NULL);
        std::string current_time = ctime(&time_now);
        current_time.pop_back();

        if (sd.GetIsDatoReady()) {
            std::string information = current_time + std::string(", ") + sd.ToString();
            File << information << std::endl;
            console.lock();
            std::cout << std::string("Drone " + std::to_string(nDrone) + " > ") << information << std::endl;
            console.unlock();
        } else {
            std::string information = current_time + std::string(", DATO NON PRONTO");
            File << information << std::endl;
            console.lock();
            std::cout << std::string("Drone " + std::to_string(nDrone) + " > ") << information << std::endl;
            console.unlock();
        }
    }

    File.close(); //RICORDO !!
}

int main() {
    srand(time(NULL));
    starting_time = time(NULL);

    std::cout << "Program started at: " << ctime(&starting_time);

    std::thread threadScrittore(ObtainInformationThread);

    std::vector<std::thread> threadLettori;

    for (int i = 0; i<NUM_DRONES; i++) {
        threadLettori.push_back(std::thread(ReadCollectedInformationThread, i));
    }

    std::this_thread::sleep_for(std::chrono::seconds(10));

    shouldProgramRun = false;

    threadScrittore.join();

    for (int i = 0; i<NUM_DRONES; i++) {
        threadLettori[i].join();
    }

    std::cout << "Program terminated";

    return 0;
}
