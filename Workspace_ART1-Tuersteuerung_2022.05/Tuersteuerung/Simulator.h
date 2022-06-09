//
// Created by dustin on 6/9/22.
//

#ifndef ART_TEST_SIMULATOR_H
#define ART_TEST_SIMULATOR_H
#include <thread>
#include <string>
#include <atomic>


class Simulator {
    public:
        static std::atomic<bool> quit_simulator_flag; // abbruch Bedingung für Simulator
        Simulator(bool show_ui);
        ~Simulator(void);

    void DIO_Read(const unsigned port, unsigned char *pins);


    /*
     * Ändert alle Pins eines Ausgabe-Ports.
     * port: Ausgabe-Port-Nummer
     * pins: die auszugebenden Kanäle des Ports
     */
    void DIO_Write(const unsigned port, const unsigned char pins);

    /*
     * Methode zum Anzeigen eines Strings in der Nachrichtenzeile eines Displays
     * s: auszugebender String (maximale Länge 50 alphanumerische Zeichen)
     * set debug string for showing in Simulation UI */
    void DebugString(const std::string s);

private:
    const bool show_ui;

    std::thread ui_thread;
    char debug_string[100];


    int channels;
    int sim_channels;

    void HandleSimUI(void);
    void InitNcurses(void);
    void ShowSimUI(void);
    void HandleSimInput(int c);


};


#endif //ART_TEST_SIMULATOR_H
