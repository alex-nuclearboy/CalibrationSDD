#include <iostream>

#include <TCanvas.h>

#include "CalibrationSDD.h"

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <file_name> <bus_num> <sdd_num>" 
              << std::endl;
    return 1;
  }
  
  const std::string file_path = 
      "/home/aleks/SIDDHARTA2/SpectrumAnalyser/output/rootfiles/" 
      + std::string(argv[1]);
  const std::string bus_num = std::string(argv[2]);
  const std::string sdd_num = std::string(argv[3]);
  const std::string hist_name = "h_adc_bus" + bus_num + "_sdd" + sdd_num;
  
  CalibrationSDD hist(file_path, hist_name);

  if (!hist.FileExists()) {
    std::cerr << "Error: file" << file_path << "not found." << std::endl;
    return 1;
  }
  
  TH1D* histogram = hist.GetHistogram();
  if (!histogram) {
    std::cerr << "Error: Failed to retrieve histogram " << hist_name 
              << " from file " << file_path << std::endl;
    return 1;
  }
 
  hist.DrawSpectrum(histogram, 4, bus_num, sdd_num);
  return 0;
}
