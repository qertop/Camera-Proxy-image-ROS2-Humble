1.Na swoje urządzenie do katalogu domowego skopiuj plik fastdds_config.xml który znajdziesz w repozytorium 

2.Na końcu pliku który znajdziesz pod ~/.bashrc wklej następujące linie:
export RMW_IMPLEMENTATION=rmw_fastrtps_cpp
export FASTRTPS_DEFAULT_PROFILES_FILE=~/fastdds_config.xml
