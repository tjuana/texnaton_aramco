#ifndef MainUnitH
#define MainUnitH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "cspin.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>

class TForm1 : public TForm
{
__published:	// IDE-managed Components
  TMemo *Ed;
  TPanel *Panel1;
  TImage *Im;
  TPanel *Panel2;
  TCSpinEdit *StepSE;
  TLabel *Label1;
  TLabel *Label2;
  TUpDown *UD10;
  TLabel *Label3;
  TUpDown *UpDown1;
  TLabel *Label4;
  TUpDown *UD100;
  TSpeedButton *ToFirstBt;
  TSpeedButton *ToLastBt;
  TTrackBar *TB;
  TLabel *Label5;
  TCSpinEdit *NXSE;
  TLabel *Label6;
  TCSpinEdit *NYSE;
  TSpeedButton *CalcBt;
  TRadioButton *RB0;
  TRadioButton *RB1;
  TRadioButton *RB2;
  TEdit *ResE;
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall StepSEChange(TObject *Sender);
  void __fastcall UD10Click(TObject *Sender, TUDBtnType Button);
  void __fastcall ToFirstBtClick(TObject *Sender);
  void __fastcall ToLastBtClick(TObject *Sender);
  void __fastcall TBChange(TObject *Sender);
  void __fastcall RB0Click(TObject *Sender);
  void __fastcall CalcBtClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TForm1(TComponent* Owner);

  bool Ch;
};

extern PACKAGE TForm1 *Form1;

#endif
