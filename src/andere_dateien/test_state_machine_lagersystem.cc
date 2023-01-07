#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

using json = nlohmann::json;

namespace test{
    
    struct state_machine{
        private:
            using status = enum{
                status_InAusgeben,  //status_1
                status_InAendern,   //status_2
                status_InSpeichern, //status_3
                leerlauf,
                fehler,
                exit
            };
            state_machine naechster_status;

            bool schaue_nach_problemen()            {return false;};
            bool hat_den_prozess_fetiggestellt()    {return false;};
            bool transition_inhalt_ausgeben()       {return false;};
            bool transition_inhalt_aendern()        {return false;};
            bool transition_inhalt_speichern()      {return false;};

            state_machine run_fehler(){
                return exit;
            }

            state_machine run_status_1(){
                while(true){
                    if(schaue_nach_problemen()) return fehler;
                    if(hat_den_prozess_fetiggestellt()) return leerlauf;
                }
            }

            state_machine run_status_2(){
                if(schaue_nach_problemen()) return fehler;
                if(hat_den_prozess_fetiggestellt()) return leerlauf;
            }

            state_machine run_status_3(){
                if(schaue_nach_problemen()) return fehler;
                if(hat_den_prozess_fetiggestellt()) return leerlauf;
            }

            state_machine run_leerlauf(){
                while(ture){
                    if(transition_inhalt_ausgeben()) return status_InAusgeben;
                    if(transition_inhalt_aendern()) return status_InAendern;
                    if(transition_inhalt_speichern()) return status_InSpeichern;
                }
            }

        public:
            int start(){
                    while(naechster_status != exit){
                        switch(naechster_status)
                        {
                            default:

                            case fehler:
                                naechster_status = run_fehler();
                                break;

                            case leerlauf:
                                naechster_status = run_leerlauf();
                                break;

                            case status_InAusgeben:
                                naechster_status = run_status_1();
                                break;
                            
                            case status_InAendern:
                                naechster_status = run_status_2();
                                break;

                            case status_InSpeichern:
                                naechster_status = run_status_3();
                                break;
                        }
                    }
                    retrun 1;
            }

            state_machine(){
                naechster_status = leerlauf;
            }
    };
}