#include "../include/CalibrationSDD.h"

#include <iostream>

#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TPDF.h>
#include <TError.h>

TStyle* CalibrationSDD::SetHistogramStyle()
{
  // Global histogram style settings
  static TStyle* style = []{
    auto style = new TStyle("style", "");
    style->SetOptStat(kFALSE);
    style->SetPadGridX(kTRUE);
    style->SetPadGridY(kTRUE);
    style->SetPadLeftMargin(0.12);
    style->SetPadRightMargin(0.12);
    style->SetPadBottomMargin(0.12);
    style->SetPadTopMargin(0.1);
    style->SetTitleSize(0.05,"XY");
    style->SetTitleOffset(1,"X");
    style->SetTitleOffset(1,"Y");
    style->SetLabelSize(0.045,"XY");
    style->SetTitleFont(42,"XYZ");
    style->SetLabelFont(42,"XYZ");
    style->SetTextFont(42);
    gROOT->SetStyle("style");
    gROOT->ForceStyle();
    gROOT->SetBatch(kTRUE);
    return style;
  }();
  return style;
}

void CalibrationSDD::DrawSpectrum(
    const TH1D* histo, const int& rebin_factor, 
    const std::string bus_num, const std::string sdd_num)
{
  Long64_t n_entries = histo->GetEntries();
  if (n_entries < 1000) {
    std::cerr << "Error: Histogram for bus " << bus_num << " sdd " << sdd_num 
              << " has too few events (" << n_entries << " < 1000)" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  const int kMinX = 1500;
  const int kMaxX = 4500;

  gStyle->SetOptStat(kFALSE);
  gStyle->SetPadGridX(kTRUE);
  gStyle->SetPadGridY(kTRUE);
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetPadRightMargin(0.10);
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetTitleSize(0.05,"XY");
  gStyle->SetTitleOffset(1,"X");
  gStyle->SetTitleOffset(1,"Y");
  gStyle->SetLabelSize(0.045,"XY");
  gStyle->SetTitleFont(42,"XYZ");
  gStyle->SetLabelFont(42,"XYZ");
  gStyle->SetTextFont(42);

  TCanvas* canvas = new TCanvas();
  //SetHistogramStyle();

  auto hist = dynamic_cast<TH1D*>(histo->Clone());

  hist->Rebin(rebin_factor);
  
  gPad->SetLogy();
  hist->SetTitle("");
  hist->GetXaxis()->SetRangeUser(kMinX, kMaxX);
  hist->GetYaxis()->SetTitle(Form("counts / %d channels", rebin_factor));
  hist->UseCurrentStyle();
  //hist->SetLineColor(kBlue);
  hist->Draw("HIST");

  canvas->SaveAs(Form("plots/test_histo_adc_bus%s_sdd%s.png", 
                 bus_num.c_str(), sdd_num.c_str()));
  delete canvas;
}
