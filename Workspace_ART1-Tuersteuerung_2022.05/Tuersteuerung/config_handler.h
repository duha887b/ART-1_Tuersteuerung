//
// Created by supertrooper on 07.06.2022.
//

#ifndef CONFIG_HANDLER_HH
#define CONFIG_HANDLER_HH

class config_handler {

public:
    void run();
    static config_handler& get_instance();
    config_handler();

private:

    //~config_handler();

};

#endif // CONFIG_HANDLER_HH
