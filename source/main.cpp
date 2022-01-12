#include "ppm.hpp"
#include "logger.hpp"

#include <iostream>
#include <string>

#include <json.hpp>
#include <Eigen/Core>
#include <Eigen/Dense>

#if defined(COURSE_SOLUTION) || defined(STUDENT_SOLUTION)
#include "src/RayTracer.h"
#endif

REGISTER_LOGGER()

int test_eigen() { return 0; }
int test_save_ppm() { return 0; }
int test_json(nlohmann::json& j) { return 0; }

int main(int argc, char const *argv[])
{
    if(argc!=2){
        std::cout<<"Invalid number of arguments"<<std::endl;
        std::cout<<"Usage: ./raytracer [scene] "<<std::endl;
        std::cout<<"Run sanity checks"<<std::endl;
        
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
        
        nlohmann::json j = nlohmann::json::parse(buffer.str());
        info("Scene \"" + scene_name + "\" parsed succesfully!");
        
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
  
    
    
    return 0;
}
