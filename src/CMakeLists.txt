add_executable (FightAgainstCovid19 main.cpp train.cpp predict.cpp utils.cpp formula.cpp) 
target_link_libraries(FightAgainstCovid19 ${OpenCV_LIBS})
