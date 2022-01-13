#include "ppm.hpp"
#include "logger.hpp"
#include "tests/tests.hpp"

#include <iostream>
#include <string>
#include <exception>

#include <json.hpp>
#include <Eigen/Core>
#include <Eigen/Dense>

#ifdef COURSE_SOLUTION
#include "RayTracer.h"
#endif

#ifdef STUDENT_SOLUTION
#include "raytracer.hpp"
#endif

REGISTER_LOGGER()

static void help(){
    std::cout << "Invalid number of arguments\nUsage: ./raytracer [scene]\nRun sanity checks\n";
}

int main(int argc, char const *argv[])
{
    nlohmann::json j;

    if(argc!=2){
        help();
        
        test_eigen();
        test_save_ppm();
        
    } else {
        std::string scene_name(argv[1]);

        info("Scene \"" + scene_name + "\"");
        
        std::ifstream t(argv[1]);
        if(!t){
            error("File \"" + scene_name + "\" does not exists");
            return EXIT_FAILURE;
        }
        
        std::stringstream buffer;
        buffer << t.rdbuf();
        
        try 
        {
            j = nlohmann::json::parse(buffer.str());
            info("Scene \"" + scene_name + "\" parsed succesfully!");
        }
        catch (const std::exception &e)
        {
            error("Cannot parse scene \"" + scene_name + "\": " + std::string(e.what()));
        }
        
#if defined(COURSE_SOLUTION)
        std::cout<<"Running course solution"<<std::endl;
        RT371::RayTracer<RT371::Kernelf> rt(j);
        std::cout<<"Running!"<<std::endl;
        rt.run();
        
#elif defined(STUDENT_SOLUTION)
        std::cout<<"Running studnt solution"<<std::endl;
        RayTracer rt(j);
        rt.run();
#else
        // GIven code - a bunch of test functions to showcase the funcitonality
        test_eigen();
        test_save_ppm();
        
        if(test_json(j)==0){
            
        } else {
            std::cout<<"Could not load file!"<<std::endl;
        }
        
#endif
    }
  
    return EXIT_SUCCESS;
}
