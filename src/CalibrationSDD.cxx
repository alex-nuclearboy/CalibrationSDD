#include "CalibrationSDD.h"
#include <iostream>
#include <fstream>
#include "TFile.h"

CalibrationSDD::CalibrationSDD(
    const std::string& file_path, const std::string& hist_name) 
    : file_path_(file_path), hist_name_(hist_name), histogram_(nullptr), 
      file_(nullptr)
{
    file_ = new TFile(file_path_.c_str(), "READ");
    if (!file_ || file_->IsZombie()) {
        std::cerr << "Error: could not open file " << file_path_ << std::endl;
        delete file_;
        return;
    }

    file_->cd();
    if(file_->GetListOfKeys()->Contains(hist_name_.c_str())) {
      histogram_ = dynamic_cast<TH1D*>(file_->Get(hist_name_.c_str()));
    }
    
    else{
      std::cerr << "Error: Could not find the histogram" << std::endl;
    exit(1);
    }

}

CalibrationSDD::~CalibrationSDD()
{
    if (file_) {
        file_->Close();
        delete file_;
    }
}

TH1D* CalibrationSDD::GetHistogram() const
{
    return histogram_;
}

bool CalibrationSDD::FileExists() const 
{
    std::ifstream infile(file_path_);
    return infile.good();
}

