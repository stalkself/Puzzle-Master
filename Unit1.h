//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.ImageList.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.AppEvnts.hpp>
#include <cmath>
#include <mmsystem.h>
#include <jpeg.hpp>
#include <gdiplus.h>
#include <Vcl.AppEvnts.hpp>

//#include <memory>
//#include <gdiplusheaders.h>
//#pragma comment (lib,"Gdiplus.lib")
//#include <gdipluspath.h>
//#include <gdiplusimaging.h>
//#include <gdipluspixelformats.h >
//#include <wingdi.h>





//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *MPanel;
	TLabel *Label1;
	TSpeedButton *ib1;
	TSpeedButton *ib2;
	TSpeedButton *ib3;
	TSpeedButton *ib4;
	TSpeedButton *ib5;
	TSpeedButton *ib6;
	TSpeedButton *ib7;
	TSpeedButton *ib8;
	TSpeedButton *ib9;
	TSpeedButton *ib10;
	TSpeedButton *ib11;
	TSpeedButton *ib12;
	TSpeedButton *ib13;
	TSpeedButton *ib14;
	TSpeedButton *ib15;
	TSpeedButton *ib16;
	TSpeedButton *ib17;
	TSpeedButton *ib18;
	TSpeedButton *ib19;
	TSpeedButton *ib20;
	TSpeedButton *ib21;
	TSpeedButton *ib22;
	TSpeedButton *ib23;
	TSpeedButton *ib24;
	TSpeedButton *ib25;
	TSpeedButton *ib26;
	TPanel *Panel2;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *Edit3;
	TEdit *Edit4;
	TUpDown *UpDown4;
	TUpDown *UpDown3;
	TPanel *Panel3;
	TLabel *Label7;
	TLabel *Label8;
	TEdit *Edit5;
	TUpDown *UpDown5;
	TEdit *Edit6;
	TUpDown *UpDown6;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox7;
	TEdit *Edit1;
	TUpDown *UpDown1;
	TEdit *E9;
	TUpDown *UpDown2;
	TPanel *Panel4;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label5;
	TEdit *Edit7;
	TUpDown *UpDown7;
	TEdit *Edit8;
	TUpDown *UpDown8;
	TUpDown *UpDown9;
	TEdit *Edit2;
	TEdit *E1;
	TEdit *E2;
	TEdit *E3;
	TEdit *E4;
	TEdit *E5;
	TEdit *E6;
	TEdit *E7;
	TEdit *E8;
	TUpDown *U8;
	TUpDown *U7;
	TUpDown *U6;
	TUpDown *U5;
	TUpDown *U4;
	TUpDown *U3;
	TUpDown *U2;
	TUpDown *U1;
	TPanel *Panel1;
	TLabel *Label2;
	TSpeedButton *SB1;
	TSpeedButton *SB2;
	TSpeedButton *SB3;
	TSpeedButton *SB4;
	TSpeedButton *SB5;
	TPanel *Panel5;
	TCheckBox *CheckBox5;
	TCheckBox *CheckBox6;
	TEdit *E10;
	TEdit *E11;
	TUpDown *U10;
	TUpDown *U11;
	TImage *Original;
	TImage *Original1;
	TOpenPictureDialog *OPD;
	TImageList *IL2;
	TImageList *IL1;
	TApplicationEvents *ApplicationEvents1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ib4Click(TObject *Sender);
	void __fastcall CheckBox5Click(TObject *Sender);
	void __fastcall ib1Click(TObject *Sender);
	void __fastcall ApplicationEvents1Message(tagMSG &Msg, bool &Handled);
	void __fastcall benable();
	void __fastcall bdisable();
	void __fastcall ib26MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall ib26MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Edit2Change(TObject *Sender);
	void __fastcall FormMouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall FormMouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
    void __fastcall ostpaint();
	void __fastcall ib2Click(TObject *Sender);
	void __fastcall dark(int i, int j);
    void __fastcall light(int i, int j);
	void __fastcall ib3Click(TObject *Sender);
	void __fastcall normindex();
	void __fastcall ib10Click(TObject *Sender);
	void __fastcall ib5Click(TObject *Sender);
	void __fastcall ib6Click(TObject *Sender);
	void __fastcall ib7Click(TObject *Sender);
	void __fastcall ib8Click(TObject *Sender);
	void __fastcall ib9Click(TObject *Sender);
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
    void __fastcall attach(int x, int y);
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);


private:	// User declarations


public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};



//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
