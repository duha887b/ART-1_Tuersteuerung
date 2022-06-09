//
// Created by dustin on 6/9/22.
//

#ifndef ART_TEST_USERINTERFACE_H
#define ART_TEST_USERINTERFACE_H

#include <thread>
#include <string>
#include <atomic>

class UserInterface {
public:
    static std::atomic<bool> quit_ui_flag;
    UserInterface();
    ~UserInterface(void);
    void refreshPinsbyPorts(const unsigned port, const unsigned char pins);

    void DebugString(const std::string s);


private:

    std::thread ui_thread;
    char debug_string[100];

    int channels;
    int sim_channels;

    void HandleSimUI(void);
    void InitNcurses(void);
    void ShowSimUI(void);
    void HandleSimInput(int c);


};


#endif //ART_TEST_USERINTERFACE_H
