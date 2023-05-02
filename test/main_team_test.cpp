
//Cadmium Simulator headers
#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/dynamic_model.hpp>
#include <cadmium/modeling/dynamic_model_translator.hpp>
#include <cadmium/engine/pdevs_dynamic_runner.hpp>
#include <cadmium/logger/common_loggers.hpp>

//Time class header
#include <NDTime.hpp>

//Messages structures
#include "../data_structures/attribute.hpp"
#include "../data_structures/skill.hpp"
#include "../data_structures/skillinfo.hpp"
#include "../data_structures/heroinfo.hpp"
#include "../data_structures/event.hpp"
#include "../data_structures/teamcombo.hpp"

//Atomic model headers
#include <cadmium/basic_model/pdevs/iestream.hpp> //Atomic model for inputs
#include "../atomics/hero.hpp"
#include "../coupled/team.hpp"

//C++ libraries
#include <iostream>
#include <string>
#include <list>

using namespace std;
using namespace cadmium;
using namespace cadmium::basic_models::pdevs;

using TIME = NDTime;

/***** Define input port for coupled models *****/

/***** Define output ports for coupled model *****/
struct top_out: public out_port<string>{};

/****** Input Reader atomic model declaration *******************/
template<typename T>
class InputReader_String : public iestream_input<string,T> {
    public:
        InputReader_String () = default;
        InputReader_String (const char* file_path) : iestream_input<string,T>(file_path) {}
};

template<typename T>
class InputReader_Command : public iestream_input<Command,T> {
    public:
        InputReader_Command () = default;
        InputReader_Command (const char* file_path) : iestream_input<Command,T>(file_path) {}
};

int main(int argc, char ** argv){

    if (argc < 3) {
        cout << "Program used with wrong parameters. The program must be invoked as follow:";
        cout << argv[0] << " num1 num2" << endl;
        return 1; 
    }

    /****** Input Reader atomic model instantiation *******************/
    // const char * i_input_data = "../input_data/hero_input_test.txt";
    // const char * i_input_data2 = "../input_data/command_input_test.txt";
    // shared_ptr<dynamic::modeling::model> input_reader;
    // shared_ptr<dynamic::modeling::model> input_reader2;
    // input_reader = dynamic::translate::make_dynamic_atomic_model<InputReader_String, TIME, const char*>("input_reader", move(i_input_data));
    // input_reader2 = dynamic::translate::make_dynamic_atomic_model<InputReader_Command, TIME, const char*>("input_reader2", move(i_input_data2));
    
    string num1 = argv[1];
    string num2 = argv[2];
    int n1 = stoi(num1);
    int n2 = stoi(num2);
    list<int> team1 = combos[n1];
    list<int> team2 = combos[n2];
    

    /****** atomic model instantiation *******************/
    
    shared_ptr<dynamic::modeling::model> t1h1;
    shared_ptr<dynamic::modeling::model> t1h2;
    shared_ptr<dynamic::modeling::model> t1h3;
    shared_ptr<dynamic::modeling::model> t1h4;
    
    shared_ptr<dynamic::modeling::model> t2h1;
    shared_ptr<dynamic::modeling::model> t2h2;
    shared_ptr<dynamic::modeling::model> t2h3;
    shared_ptr<dynamic::modeling::model> t2h4;

    auto it = team1.begin();

    t1h1 = dynamic::translate::make_dynamic_atomic_model<Hero, TIME>(heroDB[*it].name, heroDB[*it]);
    advance(it,1);
    t1h2 = dynamic::translate::make_dynamic_atomic_model<Hero, TIME>(heroDB[*it].name, heroDB[*it]);
    advance(it,1);
    t1h3 = dynamic::translate::make_dynamic_atomic_model<Hero, TIME>(heroDB[*it].name, heroDB[*it]);
    advance(it,1);
    t1h4 = dynamic::translate::make_dynamic_atomic_model<Hero, TIME>(heroDB[*it].name, heroDB[*it]);
    advance(it,1);

    auto it2 = team2.begin();

    t2h1 = dynamic::translate::make_dynamic_atomic_model<Hero, TIME>(heroDB[*it2].name, heroDB[*it2]);
    advance(it2,1);
    t2h2 = dynamic::translate::make_dynamic_atomic_model<Hero, TIME>(heroDB[*it2].name, heroDB[*it2]);
    advance(it2,1);
    t2h3 = dynamic::translate::make_dynamic_atomic_model<Hero, TIME>(heroDB[*it2].name, heroDB[*it2]);
    advance(it2,1);
    t2h4 = dynamic::translate::make_dynamic_atomic_model<Hero, TIME>(heroDB[*it2].name, heroDB[*it2]);
    advance(it2,1);

    /*******TOP MODEL********/
    dynamic::modeling::Ports iports_TOP;
    iports_TOP = {};
    dynamic::modeling::Ports oports_TOP;
    oports_TOP = {typeid(top_out)};
    dynamic::modeling::Models submodels_TOP;
    submodels_TOP = {t1h1, t1h2, t1h3, t1h4, t2h1, t2h2, t2h3, t2h4};
    dynamic::modeling::EICs eics_TOP;
    eics_TOP = {};
    dynamic::modeling::EOCs eocs_TOP;
    eocs_TOP = {
        // dynamic::translate::make_EOC<Hero_ports_defs::command_out, top_out>(heroDB[HeroClass::druid].name)
    };
    dynamic::modeling::ICs ics_TOP;
    ics_TOP = {
        // dynamic::translate::make_IC<iestream_input_defs<string>::out, Hero_ports_defs::active_in>("input_reader", heroDB[HeroClass::druid].name),
        // dynamic::translate::make_IC<iestream_input_defs<Command>::out, Hero_ports_defs::command_in>("input_reader2", heroDB[HeroClass::druid].name)
    };
    shared_ptr<dynamic::modeling::coupled<TIME>> TOP;
    TOP = make_shared<dynamic::modeling::coupled<TIME>>(
        "TOP", submodels_TOP, iports_TOP, oports_TOP, eics_TOP, eocs_TOP, ics_TOP 
    );

    /*************** Loggers *******************/
    static ofstream out_messages("../simulation_results/team_test_output_messages.txt");
    struct oss_sink_messages{
        static ostream& sink(){          
            return out_messages;
        }
    };
    static ofstream out_state("../simulation_results/team_test_output_state.txt");
    struct oss_sink_state{
        static ostream& sink(){          
            return out_state;
        }
    };
    
    using state=logger::logger<logger::logger_state, dynamic::logger::formatter<TIME>, oss_sink_state>;
    using log_messages=logger::logger<logger::logger_messages, dynamic::logger::formatter<TIME>, oss_sink_messages>;
    using global_time_mes=logger::logger<logger::logger_global_time, dynamic::logger::formatter<TIME>, oss_sink_messages>;
    using global_time_sta=logger::logger<logger::logger_global_time, dynamic::logger::formatter<TIME>, oss_sink_state>;

    using logger_top=logger::multilogger<state, log_messages, global_time_mes, global_time_sta>;

    /************** Runner call ************************/ 
    dynamic::engine::runner<NDTime, logger_top> r(TOP, {0});
    r.run_until(NDTime("04:00:00:000"));
    return 0;
}
