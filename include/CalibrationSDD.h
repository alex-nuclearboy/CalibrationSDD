#ifndef CALIBRATION_SDD_H
#define CALIBRATION_SDD_H

#include <string>
#include <TROOT.h>
#include "TH1.h"
#include "TFile.h"
#include "TStyle.h"

class CalibrationSDD {
public:
    CalibrationSDD(const std::string& file_path, const std::string& hist_name);
    ~CalibrationSDD();
    TH1D* GetHistogram() const;
    bool FileExists() const;
    TStyle* SetHistogramStyle(); 
    void DrawSpectrum(
        const TH1D* histo, const int& rebin_factor, const std::string bus_num, 
        const std::string sdd_num);
private:
    std::string file_path_;
    std::string hist_name_;
    TFile* file_;
    TH1D* histogram_;
};

#endif // CALIBRATION_SDD_H
