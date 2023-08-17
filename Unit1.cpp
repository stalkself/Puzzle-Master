//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;
int step,kolx,koly,tekx,teky,kolpr,dexx,ost,pnum,px,py,att,ix,iy,ptek,pazl[901][903],ptab[901],gatek[31][31],vatek[31][31];
Gdiplus::GraphicsPath* vpath[31][31];
Gdiplus::GraphicsPath* gpath[31][31];
Gdiplus::GraphicsPath* path;
Gdiplus::GraphicsPath* path1;
TBitmap*  bmp = new TBitmap;
TBitmap*  bmp1 = new TBitmap;
TBitmap*  scr = new TBitmap;
TBitmap*  sscr = new TBitmap;
TBitmap *im[31][31];
Gdiplus::PointF ind[31][31];
HRGN reg[31][31];
HBRUSH br1;
struct Pont {int X, Y;};
TRGBTriple *pop,*pop1,*pop2;//Для сканлайна
int filtr[16][4]={{-1,1,-1,1},{1,-1,1,-1},{-1,-1,-1,1},{-1,1,-1,-1},{1,1,-1,1},{-1,1,1,1},
  {1,-1,-1,-1},{1,1,1,-1},{1,-1,1,1},{-1,-1,1,-1},{1,-1,-1,1},{-1,1,1,-1},
  {-1,-1,-1,-1},{1,1,-1,-1},{1,1,1,1},{-1,-1,1,1}};
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

//Вспомогательные функции *******************************************************************************************************

//Функция перевода координат
Pont s(int x)
{
float i;
Pont point;
if (x<=kolx)
{
 point.X=x;
 point.Y=1;
} else
{
--x;
i=ceil(x/kolx)+1;
point.Y=i;
++x;
point.X=x-(i-1)*kolx;
}
return point;
}

//Поиск пазла на наличие конкретного тека
int inarray(int x)
{
int i,j;
for (i=1;i<=ost;++i)
 {
 j=2;
 while (pazl[ptab[i]][j]!=0)
  {
  if (pazl[ptab[i]][j]==x) return ptab[i];
  ++j;
  }
 }
}

//Функция вертикальных траекторий
Gdiplus::GraphicsPath* vertical(float x1,float x2,float x3,float x4)
{
Gdiplus::GraphicsPath* pth = new Gdiplus::GraphicsPath;
float k,n,k1,k2,dex,dey,dx,dy;
Gdiplus::PointF points[11];
ptek=0;
if (x1==0 or x1==tekx)
 {
 pth->AddLine(x1,x2,x3,x4);
 return pth;
 }
 else
 {
 //Строим первые две опорных точки по угловым точкам
 points[0].X=x1; points[0].Y=x2;
 points[10].X=x3; points[10].Y=x4;
 if (points[0].X!=points[10].X)
  {
  k=(points[0].Y-points[10].Y)/(points[0].X-points[10].X); //Угловой коэффициент прямой
  n=-1/k;//Угловой коэффициент нормали
  }
  else
  {
  k=0;
  n=0;
  }
 dex=points[10].X-points[0].X;//Истинная середина прямой, тогда как dexx - минимальная абсолютная, без учета искажений
 dey=points[10].Y-points[0].Y;
 //Строим две опорных точки перед шейкой, они плавающие и не зависят от абсолютной dexx
 k1=(1-2*round(rand()%2));
 dx=k1*dey*StrToInt(Form1->Edit6->Text)/100;
 dy=dx*n;
 points[1].X=points[0].X+dex*0.2+dx;
 points[1].Y=points[0].Y+dey*0.2+dy;
 points[9].X=points[0].X+dex*0.8+dx;
 points[9].Y=points[0].Y+dey*0.8+dy;
 //Строим опорные точки шейки
 dy=dexx*0.08;
 points[2].Y=points[0].Y+dey*0.5-dy;
 points[8].Y=points[0].Y+dey*0.5+dy;
 if (k!=0) dx=-dy/k; else dx=0;
 points[2].X=points[0].X+dex*0.5+dx;
 if (k!=0) dx=dy/k; else dx=0;
 points[8].X=points[0].X+dex*0.5+dx;
 //Строим опорные точки шейки
 dy=dexx*0.08;
 points[2].Y=points[0].Y+dey*0.5-dy;
 points[8].Y=points[0].Y+dey*0.5+dy;
 if (k!=0) dx=-dy/k; else dx=0;
 points[2].X=points[0].X+dex*0.5+dx;
 if (k!=0) dx=dy/k; else dx=0;
 points[8].X=points[0].X+dex*0.5+dx;
 //Строим удаленную точку головки
 if (Form1->CheckBox1->Checked) k1=-k1; else k1=(1-2*round(rand()%2));
 dx=k1*dexx/3.6;
 dy=dx*n;
 points[5].X=points[0].X+dex*0.5+dx;
 points[5].Y=points[0].Y+dey*0.5+dy;
 //Строим четыре опорных точки головки
 k2=dexx*0.12;
 dx=k1*dexx/4.5;
 dy=dx*n-k2;
 if (k!=0) dx=dx+dy/k;
 points[4].X=points[0].X+dex*0.5+dx;
 points[4].Y=points[0].Y+dey*0.5+dy;
 dx=k1*dexx/4.5;
 dy=dx*n+k2;
 if (k!=0) dx=dx+dy/k;
 points[6].X=points[0].X+dex*0.5+dx;
 points[6].Y=points[0].Y+dey*0.5+dy;
 k2=dexx*0.14;
 dx=k1*dexx/10;
 dy=dx*n-k2;
 if (k!=0) dx=dx+dy/k;
 points[3].X=points[0].X+dex*0.5+dx;
 points[3].Y=points[0].Y+dey*0.5+dy;
 dx=k1*dexx/10;
 dy=dx*n+k2;
 if (k!=0) dx=dx+dy/k;
 points[7].X=points[0].X+dex*0.5+dx;
 points[7].Y=points[0].Y+dey*0.5+dy;
 ptek=round(k1);
 pth->AddCurve(points,11,StrToFloat(Form1->E9->Text)/100);
 return pth;
 }
}

//Функция горизонтальных траекторий
Gdiplus::GraphicsPath* gorizontal(float x1,float x2,float x3,float x4)
{
Gdiplus::GraphicsPath* pth = new Gdiplus::GraphicsPath;
float k,n,k1,k2,dex,dey,dx,dy;
Gdiplus::PointF points[11];
ptek=0;
if (x2==0 or x2==teky)
 {
 pth->AddLine(x1,x2,x3,x4);
 return pth;
 }
 else
 {
 //Строим первые две опорных точки по угловым точкам
 points[0].X=x1; points[0].Y=x2;
 points[10].X=x3; points[10].Y=x4;
 if (points[0].Y!=points[10].Y)
 {
 k=(points[0].X-points[10].X)/(points[0].Y-points[10].Y); //Угловой коэффициент прямой
 n=-1/k; //Угловой коэффициент нормали
 }
 else
 {
 k=0;
 n=0;
 }
 dex=points[10].X-points[0].X;//Истинная середина прямой, тогда как dexx - минимальная абсолютная, без учета искажений
 dey=points[10].Y-points[0].Y;
 //Строим две опорных точки перед шейкой, они плавающие и не зависят от абсолютной dexx
 k1=(1-2*round(rand()%2));
 dy=k1*dex*StrToInt(Form1->Edit6->Text)/100;
 dx=dy*n;
 points[1].X=points[0].X+dex*0.2+dx;
 points[1].Y=points[0].Y+dey*0.2+dy;
 points[9].X=points[0].X+dex*0.8+dx;
 points[9].Y=points[0].Y+dey*0.8+dy;
 //Строим опорные точки шейки
 dx=dexx*0.08;
 points[2].X=points[0].X+dex*0.5-dx;
 points[8].X=points[0].X+dex*0.5+dx;
 if (k!=0) dy=-dx/k; else dy=0;
 points[2].Y=points[0].Y+dey*0.5+dy;
 if (k!=0) dy=dx/k; else dy=0;
 points[8].Y=points[0].Y+dey*0.5+dy;
 //Строим удаленную точку головки
 if (Form1->CheckBox1->Checked) k1=-k1; else k1=(1-2*round(rand()%2));
 dy=k1*dexx/3.6;
 dx=dy*n;
 points[5].Y=points[0].Y+dey*0.5+dy;
 points[5].X=points[0].X+dex*0.5+dx;
 //Строим четыре опорных точки головки
 k2=dexx*0.12;
 dy=k1*dexx/4.5;
 dx=dy*n-k2;
 if (k!=0) dy=dy+dx/k;
 points[4].Y=points[0].Y+dey*0.5+dy;
 points[4].X=points[0].X+dex*0.5+dx;
 dy=k1*dexx/4.5;
 dx=dy*n+k2;
 if (k!=0) dy=dy+dx/k;
 points[6].Y=points[0].Y+dey*0.5+dy;
 points[6].X=points[0].X+dex*0.5+dx;
 k2=dexx*0.14;
 dy=k1*dexx/10;
 dx=dy*n-k2;
 if (k!=0) dy=dy+dx/k;
 points[3].Y=points[0].Y+dey*0.5+dy;
 points[3].X=points[0].X+dex*0.5+dx;
 dy=k1*dexx/10;
 dx=dy*n+k2;
 if (k!=0) dy=dy+dx/k;
 points[7].Y=points[0].Y+dey*0.5+dy;
 points[7].X=points[0].X+dex*0.5+dx;
 ptek=round(k1);
 pth->AddCurve(points,11,StrToFloat(Form1->E9->Text)/100);
 return pth;
 }
}

//Функция осветления границы паззла для объемной рамки
TRGBTriple lighter(TRGBTriple x, float y)
{
float i;TRGBTriple j;
i=x.rgbtBlue;
i=round(i+(255-i)*y/100);
if (i>254) j.rgbtBlue=254; else j.rgbtBlue=round(i);
i=x.rgbtGreen;
i=round(i+(255-i)*y/100);
if (i>254) j.rgbtGreen=254; else j.rgbtGreen=round(i);
i=x.rgbtRed;
i=round(i+(255-i)*y/100);
if (i>254) j.rgbtRed=254; else j.rgbtRed=round(i);
return j;
}

//Функция затемнения границы паззла для объемной рамки
TRGBTriple darker(TRGBTriple x, float y)
{
float i;TRGBTriple j;
i=x.rgbtBlue;
i=round(i-i*y/100);
if (i<0) j.rgbtBlue=2; else j.rgbtBlue=round(i);
i=x.rgbtGreen;
i=round(i-i*y/100);
if (i<0) j.rgbtGreen=2; else j.rgbtGreen=round(i);
i=x.rgbtRed;
i=round(i-i*y/100);
if (i<0) j.rgbtRed=2; else j.rgbtRed=round(i);
return j;
}

//Процедура затемнения
void __fastcall TForm1::dark(int i, int j)
{
pop1[i]=darker(pop1[i],StrToFloat(E1->Text));
if (i<tekx-1 and j>0 and StrToInt(Edit1->Text)>1)
 {
 pop2=(TRGBTriple *)Original1->Picture->Bitmap->ScanLine[j-1];
 pop2[i+1]=darker(pop2[i+1],StrToFloat(E2->Text));
 }
if (i<tekx-2 and j>1 and StrToInt(Edit1->Text)>2)
 {
 pop2=(TRGBTriple *)Original1->Picture->Bitmap->ScanLine[j-2];
 pop2[i+2]=darker(pop2[i+2],StrToFloat(E3->Text));
 }
if (i<tekx-3 and j>2 and StrToInt(Edit1->Text)>3)
 {
 pop2=(TRGBTriple *)Original1->Picture->Bitmap->ScanLine[j-3];
 pop2[i+3]=darker(pop2[i+3],StrToFloat(E4->Text));
 }
if (i<tekx-4 and j>3 and StrToInt(Edit1->Text)>4)
 {
 pop2=(TRGBTriple *)Original1->Picture->Bitmap->ScanLine[j-4];
 pop2[i+4]=darker(pop2[i+4],StrToFloat(E10->Text));
 }
}

//Процедура осветления
void __fastcall TForm1::light(int i, int j)
{
pop1[i]=darker(pop1[i],StrToFloat(E5->Text));
if (i>0 and j<teky-1 and StrToInt(Edit1->Text)>1)
 {
 pop2=(TRGBTriple *)Original1->Picture->Bitmap->ScanLine[j+1];
 pop2[i-1]=lighter(pop2[i-1],StrToFloat(E6->Text));
 }
if (i>1 and j<teky-2 and StrToInt(Edit1->Text)>2)
 {
 pop2=(TRGBTriple *)Original1->Picture->Bitmap->ScanLine[j+2];
 pop2[i-2]=lighter(pop2[i-2],StrToFloat(E7->Text));
 }
if (i>2 and j<teky-3 and StrToInt(Edit1->Text)>3)
 {
 pop2=(TRGBTriple *)Original1->Picture->Bitmap->ScanLine[j+3];
 pop2[i-3]=lighter(pop2[i-3],StrToFloat(E8->Text));
 }
if (i>3 and j<teky-4 and StrToInt(Edit1->Text)>4)
 {
 pop2=(TRGBTriple *)Original1->Picture->Bitmap->ScanLine[j+4];
 pop2[i-4]=lighter(pop2[i-4],StrToFloat(E11->Text));
 }
}

//Инициализация компонентов и переменных ****************************************************************************************
void __fastcall TForm1::FormCreate(TObject *Sender)
{
//Определяем подсказки для клавиш
ib1->Hint = "Давай загрузим красивую картинку и сделаем из нее интересный пазл.\nРазмеры картинки можно изменять колесиком мышки.";
ib2->Hint = "Теперь, когда картинка загружена, можно посмотреть, как будет выглядеть готовый пазл.\nКоличество деталей-пазлов можно изменить в настройках.";
ib4->Hint = "В меню настроек можно изменить количество деталей-пазлов, их внешний вид.\nТакже есть и много других параметров, которые можно изменять.\nЧтобы скрыть панель настроек, достаточно нажать на кнопку еще раз.";
CheckBox1->Hint = "Направление изгиба границ противоположно направлению замков пазлов.";
Label7->Hint = "Процент отклонения угловых точек пазлов.";
Label8->Hint = "Процент отклонения изгиба боковых линий пазлов.";
Panel1->Hint = "Способ разобрать пазл - в стороны или равномерно.";
Panel2->Hint = "На сколько кусочков-пазлов разрезать картинку (по горизонтали и по вертикали).";
CheckBox7->Hint = "Объемная рамка выглядит красивей, но и ждать разметки придется дольше.";
Label9->Hint = "Чем ниже этот параметр, тем точнее придется совмещать кусочки-пазлы, играть будет сложнее.";
Label10->Hint = "Параметр определяет насколько пазлы могут выходить за пределы экрана.";
Edit1->Hint = "Толщина объемной рамки пазлов.";
ib3->Hint = "Просто нажми, чтобы начать игру.\nПеремещать пазл или переместить его поверх остальных можно левой кнопкой мыши.\nПри помощи правой - наоборот, убрать вниз.";
ib5->Hint = "Можно упростить игру, отобрав элементы, составляющие рамку пазла.\nЧтобы отделить их от остальных нажми на кнопку.\nИ еще раз, чтобы вернуть обратно.";
Application->HintHidePause = 5000;
step=0;
MPanel->Height=85;
kolx=0;
bmp->PixelFormat=pf24bit;
bmp1->PixelFormat=pf24bit;
br1 = CreateSolidBrush(RGB(0,0,0));
}
//---------------------------------------------------------------------------

//Процедуры кнопок меню *********************************************************************************************************

void __fastcall TForm1::ApplicationEvents1Message(tagMSG &Msg, bool &Handled)
{
if (Msg.message==WM_NCMOUSEMOVE)
if (MPanel->Visible==false and Mouse->CursorPos.Y-Form1->Top<=30) MPanel->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ib4Click(TObject *Sender)
{
if (MPanel->Height==85) MPanel->Height=315; else MPanel->Height=85;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox5Click(TObject *Sender)
{
MPanel->ShowHint=CheckBox5->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::benable()
{
for (int i=6;i<=26;++i)
 {
 TSpeedButton *sb = static_cast<TSpeedButton*>(FindComponent("ib"+IntToStr(i)));
 sb->Enabled=true;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::bdisable()
{
for (int i=6;i<=26;++i)
 {
 TSpeedButton *sb = static_cast<TSpeedButton*>(FindComponent("ib"+IntToStr(i)));
 sb->Enabled=false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ib26MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
Original1->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ib26MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
Original1->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit2Change(TObject *Sender)
{
float r;
if (step==3)
 {
 Original1->AutoSize=true;
 Original1->AutoSize=false;
 r=Original1->Height/Original->Width;
 if (Original1->Width>Width)
  {
  Original1->Width=round(Width*StrToInt(Edit2->Text)/100);
  Original1->Height=round(Original1->Width*r);
  }
 if (Original1->Height>Height)
  {
  Original1->Height=round(Height*StrToInt(Edit2->Text)/100);
  Original1->Width=round(Original1->Height/r);
  }
 Original1->Left=round(ClientWidth/2-Original1->Width/2);
 Original1->Top=round(ClientHeight/2-Original1->Height/2);
 }
}
//---------------------------------------------------------------------------

//Загружаем картинку для пазла *************************************************************************************************

void __fastcall TForm1::ib1Click(TObject *Sender)
{
if (OPD->Execute() and FileExists(OPD->FileName))
 {
 scr->Canvas->FillRect(Rect(0,0,scr->Width,scr->Height));
 Form1->Repaint();
 Original->AutoSize=true;
 Original->Stretch=false;
 Original->Picture->LoadFromFile(OPD->FileName);
 Original->AutoSize=false;
 Original->Stretch=true;
 Original->Left=round(ClientWidth/2-Original->Width/2);
 Original->Top=round(ClientHeight/2-Original->Height/2);
 Original->Visible=true;
 Original1->Visible=false;
 step=1;
 ib2->Enabled=true;
 ib3->Enabled=false;
 ib5->ImageIndex=12;
 ib5->HotImageIndex=13;
 ib5->Enabled=false;
 bdisable();
 }
}
//---------------------------------------------------------------------------

//Уменьшаем или увеличиваем картинку колесиком мышки

void __fastcall TForm1::FormMouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
if (step!=1 or Original->Width<400 or Original->Height<300) return void();
Original->Width=round(Original->Width*0.97);
Original->Height=round(Original->Height*0.97);
FormResize(Original);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
if (step!=1 or Original->Width>Screen->Width or Original->Height>Screen->Height) return void();
Original->Width=round(Original->Width*1.03);
Original->Height=round(Original->Height*1.03);
FormResize(Original);
}
//---------------------------------------------------------------------------

//Процедуры отрисовки окна и элементов  *****************************************************************************************

void __fastcall TForm1::FormPaint(TObject *Sender)
{
if (step==3) Canvas->Draw(0,0,scr);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormResize(TObject *Sender)
{
float r;int i,k;
if (step==1 or step==2)
 {
 Original->Left=round(ClientWidth/2-Original->Width/2);
 Original->Top=round(ClientHeight/2-Original->Height/2);
 Original1->Top=Original->Top;
 Original1->Left=Original->Left;
 }
if (step==3)
 {
 Original1->AutoSize=true;
 Original1->AutoSize=false;
 r=float(Original1->Height)/float(Original->Width);
 if (Original1->Width>Width)
  {
  Original1->Width=round(Width*StrToInt(Edit2->Text)/100);
  Original1->Height=round(Original1->Width*r);
  }
 if (Original1->Height>Height)
  {
  Original1->Height=round(Height*StrToInt(Edit2->Text)/100);
  Original1->Width=round(Original1->Height/r);
  }
 Original1->Left=round(ClientWidth/2-Original1->Width/2);
 Original1->Top=round(ClientHeight/2-Original1->Height/2);
 scr->Width=ClientWidth;
 scr->Height=ClientHeight;
 sscr->Width=ClientWidth;
 sscr->Height=ClientHeight;
 for (k=1;k<=ost;++k)
  {
  i=ptab[k];
  if (pazl[i][2]!=0) scr->Canvas->Draw(pazl[i][0],pazl[i][1],im[s(i).X][s(i).Y]);
  }
 Canvas->Draw(0,0,scr);
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ostpaint()
{
int i;
scr->Canvas->FillRect(Rect(0,0,scr->Width,scr->Height));
for (int j=1; j<=ost; ++j)
 {
 i=ptab[j];
 if (pazl[i][2]!=0) scr->Canvas->Draw(pazl[i][0],pazl[i][1],im[s(i).X][s(i).Y]);
 }
Canvas->Draw(0,0,scr);
}

//Нарезаем картинку на элементы-пазлы, создаем массивы точек и регионов ********************************************************

void __fastcall TForm1::ib2Click(TObject *Sender)
{
int i,j;
//Чистим регионы, если это повторный вызов процедуры
if (kolx!=0)
 {
 for (i=1;i<=30;++i)
  for (j=1;j<=30;++j)
   DeleteObject(reg[i][j]);
 for (i=1;i<=900;++i)
  for (j=1;j<=902;++j)
   pazl[i][j]=0;
 }
//Готовим переменные и изображения
step=2;
kolx=StrToInt(Edit3->Text);
koly=StrToInt(Edit4->Text);
kolpr=StrToInt(Edit5->Text);
tekx=Original->Width;
teky=Original->Height;
bmp->Width=tekx;
bmp->Height=teky;
bmp1->Width=tekx;
bmp1->Height=teky;
Original->Visible=false;
Original1->Left=Original->Left;
Original1->Top=Original->Top;
Original1->Width=Original->Width;
Original1->Height=Original->Height;
Original1->Visible=true;
bmp->Canvas->StretchDraw(Rect(0,0,bmp->Width,bmp->Height),Original->Picture->Graphic);
//Убираем черный цвет
bmp1->Canvas->Brush->Color=(TColor)RGB(1,1,1);
bmp1->Canvas->FillRect(Rect(0,0,bmp1->Width,bmp1->Height));
BitBlt(bmp->Canvas->Handle,0,0,tekx,teky,bmp1->Canvas->Handle,0,0,SRCPAINT);
//Убираем белый цвет
bmp1->Canvas->Brush->Color=(TColor)RGB(255,255,254);
bmp1->Canvas->FillRect(Rect(0,0,tekx,teky));
BitBlt(bmp->Canvas->Handle,0,0,tekx,teky,bmp1->Canvas->Handle,0,0,SRCAND);
Original1->Picture->Bitmap=bmp;
//Создаем и заполняем массив угловых точек
dexx=round(min(tekx/kolx,teky/koly));//Находим минимальную дельту для пазла
for (j=0;j<=koly;++j)
  for (i=0;i<=kolx;++i)
   {
	if (i<kolx and i>0) ind[i][j].X=round(i*tekx/kolx+(1-2*(rand()%1))*(rand()%tekx/kolx*kolpr/100));
	if (j<koly and j>0) ind[i][j].Y=round(j*teky/koly+(1-2*(rand()%1))*(rand()%teky/koly*kolpr/100));
	//Заполняем края точными значениями, чтобы исключить влияние округления
	if (i==kolx) ind [kolx][j].X=tekx;
	if (j==koly) ind [i][koly].Y=teky;
	}
//Рисуем вертикальные линии
for (j=0;j<=koly-1;++j)
 for (i=0;i<=kolx;++i)
  {
  vpath[i][j]=vertical(ind[i][j].X,ind[i][j].Y,ind[i][j+1].X,ind[i][j+1].Y);
  vatek[i][j]=ptek;
  }
//Рисуем горизонтальные линии
for (i=0;i<=kolx-1;++i)
 for (j=0;j<=koly;++j)
  {
  gpath[i][j]=gorizontal(ind[i][j].X,ind[i][j].Y,ind[i+1][j].X,ind[i+1][j].Y);
  gatek[i][j]=ptek;
  }
//Создаем регионы пазлов
Gdiplus::Graphics graphics(Form1->Canvas->Handle);
for (i=1;i<=kolx;++i)
 for (j=1;j<=koly;++j)
  {
   path=vpath[i-1][j-1];
   path->AddPath(gpath[i-1][j],true);
   path1=gpath[i-1][j-1];
   path1->AddPath(vpath[i][j-1],true);
   path1->Reverse();
   path->AddPath(path1,true);
   Gdiplus::Region vreg(path);
   reg[i][j]=vreg.GetHRGN(&graphics);
   path->Reset();
   path1->Reset();
   //vreg.Free;
  FrameRgn(bmp->Canvas->Handle,reg[i][j],br1,1,1);
  }
//Рисуем границы пазлов - объемные или обычные
 if (CheckBox7->Checked)
 {
  for (j=0;j<=teky-1;++j)
  {
  pop=(TRGBTriple *)bmp->ScanLine[j];
  pop1=(TRGBTriple *)Original1->Picture->Bitmap->ScanLine[j];
  for (i=0;i<=tekx-1;++i)
  if (pop[i].rgbtBlue==0 and pop[i].rgbtGreen==0 and pop[i].rgbtRed==0)
   {
   if (i==0 or j==teky-1)
	{
	dark(i,j);
	continue;
	}
   if (j==0 or i==tekx-1)
	{
	light(i,j);
	continue;
	}
   pop2=(TRGBTriple *)bmp->ScanLine[j+1];
   if (pop2[i-1].rgbtBlue==0 and pop2[i-1].rgbtGreen==0 and pop2[i-1].rgbtRed==0)
	{
	dark(i,j);
	continue;
	}
   pop2=(TRGBTriple *)bmp->ScanLine[j-1];
   if (pop2[i+1].rgbtBlue==0 and pop2[i+1].rgbtGreen==0 and pop2[i+1].rgbtRed==0)
	{
	light(i,j);
	continue;
	}
   }
  }
 } else Original1->Picture->Bitmap=bmp;
 ib3->Enabled=true;
}

//Процедура нарезки и разбрасывания пазлов *************************************************************************************

void __fastcall TForm1::ib3Click(TObject *Sender)
{
int i,j,k;
RECT rec;
TBitmap*  buf = new TBitmap;
float r;
step=3;
ib2->Enabled=false;
ib3->Enabled=false;
ib5->Enabled=true;
benable();
//Режем
Original1->Visible=false;
Form1->Repaint();
scr->Width=ClientWidth;
scr->Height=ClientHeight;
scr->Canvas->FillRect(Rect(0,0,scr->Width,scr->Height));
sscr->Width=scr->Width;
sscr->Height=scr->Height;
buf->Width=tekx;
buf->Height=teky;
for (j=1;j<=koly;++j)
for (i=1;i<=kolx;++i)
 {
 buf->Canvas->Brush->Bitmap=NULL;
 buf->Canvas->Brush->Color=clWhite;
 buf->Canvas->FillRect(Rect(0,0,tekx,teky));
 buf->Canvas->Brush->Bitmap=Original1->Picture->Bitmap;
 GetRgnBox(reg[i][j],&rec);
 im[i][j] = new TBitmap;
 im[i][j]->Width=rec.right-rec.left;
 im[i][j]->Height=rec.bottom-rec.top;
 PaintRgn (buf->Canvas->Handle,reg[i][j]);
 im[i][j]->Canvas->Draw(-rec.left,-rec.top,buf);
 im[i][j]->PixelFormat=pf24bit;
 im[i][j]->TransparentColor=clWhite;
 im[i][j]->Transparent=true;
 }
 //Заполняем основной массив пазлов и разбрасываем их в выбранном порядке
 k=0;
 for (j=1;j<=koly;++j)
 for (i=1;i<=kolx;++i)
 {
 ++k;
 //Размешиваем равномерно
 if (SB5->Down)
  {
  pazl[k][0]=rand()%(ClientWidth-im[i][j]->Width);
  pazl[k][1]=rand()%(ClientHeight-im[i][j]->Height);
  }
 //Размешиваем слева
 if (SB2->Down)
  {
  pazl[k][0]=rand()%(ClientWidth/3-im[i][j]->Width);
  pazl[k][1]=rand()%(ClientHeight-im[i][j]->Height);
  }
 //Размешиваем справа
 if (SB3->Down)
  {
  pazl[k][0]=ClientWidth-ClientWidth/3+rand()%(ClientWidth/3-im[i][j]->Width);
  pazl[k][1]=rand()%(ClientHeight-im[i][j]->Height);
  }
 //Размешиваем вверх
 if (SB1->Down)
  {
  pazl[k][0]=rand()%(ClientWidth-im[i][j]->Width);
  pazl[k][1]=rand()%(ClientHeight/3-im[i][j]->Height);
  }
 //Размешиваем вниз
 if (SB4->Down)
  {
  pazl[k][0]=rand()%(ClientWidth-im[i][j]->Width);
  pazl[k][1]=ClientHeight-ClientHeight/3+rand()%(ClientHeight/3-im[i][j]->Height);
  }
 pazl[k][2]=k;
 scr->Canvas->Draw(pazl[k][0],pazl[k][1],im[i][j]);
 ptab[k]=k;
 }
Canvas->Draw(0,0,scr);
Original->Picture->Bitmap->Free();
bmp->Free();
bmp1->Free();
ost=kolx*koly;
att=StrToInt(Edit7->Text);
Original1->Stretch=true;
r=float(Original1->Height)/float(Original1->Width);
if (Original1->Width>Width)
 {
 Original1->Width=round(Width*StrToInt(Edit2->Text)/100);
 Original1->Height=round(Original1->Width*r);

 }
if (Original1->Height>Height)
 {
 Original1->Height=round(Height*StrToInt(Edit2->Text)/100);
 Original1->Width=round(Original1->Height/r);
 }
 Original1->Left=round(ClientWidth/2-Original1->Width/2);
 Original1->Top=round(ClientHeight/2-Original1->Height/2);
}

//Процедуры для выбора и перемещения пазлов ************************************************************************************

//Нажатие на форму или пазл мышкой
void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
int i,j,k;
if (step!=3) return void();
//Ищем пазл под мышкой
for (k=ost;k>=0;--k)
 {
 if (k==0) return void();   //Если не найдено ни одного паззла, то выход
 i=ptab[k];
 if (X>pazl[i][0] and X<pazl[i][0]+im[s(i).X][s(i).Y]->Width)
  if (Y>pazl[i][1] and Y<pazl[i][1]+im[s(i).X][s(i).Y]->Height)
   if (im[s(i).X][s(i).Y]->Canvas->Pixels[X-pazl[i][0]][Y-pazl[i][1]]!=clWhite) break;
 }
 //Если нажата правая кнопка, выводим пазл вниз топа
if (Button==mbRight)
 {
 //Выводим пазл вниз
 if (ptab[1]!=i)
  {
  for (j=k;j>=2;--j) ptab[j]=ptab[j-1];
  ptab[1]=i;
  }
 //Рисуем топ пазлов и завершаем процедуру
 scr->Canvas->FillRect(Rect(0,0,scr->Width,scr->Height));
 for (k=1;k<=ost;++k)
  {
  i=ptab[k];
  if (pazl[i][2]!=0) scr->Canvas->Draw(pazl[i][0],pazl[i][1],im[s(i).X][s(i).Y]);
  }
 Canvas->Draw(0,0,scr);
 return void();
 }
//Если жмем левую клавишу - то пазл уходит в топ
 if (Button==mbLeft)
 {
 step=4;
 //Выводим пазл в топ
 if (ptab[ost]!=i)
  {
  for (j=k;j<=ost-1;++j) ptab[j]=ptab[j+1];
  ptab[ost]=i;
  }
  //Рисуем топ пазлов кроме выбранного под номером pnum
 pnum=i;
 scr->Canvas->FillRect(Rect(0,0,scr->Width,scr->Height));
 for (k=1;k<=ost;++k)
  {
  i=ptab[k];
  if (i!=pnum and pazl[i][2]!=0)
  scr->Canvas->Draw(pazl[i][0],pazl[i][1],im[s(i).X][s(i).Y]);
  }
  Canvas->Draw(0,0,scr);
  //Отдельно рисуем пазл под номером pnum
  Canvas->Draw(pazl[pnum][0],pazl[pnum][1],im[s(pnum).X][s(pnum).Y]);
  px=X-pazl[pnum][0];
  py=Y-pazl[pnum][1];
 }
}

//Отпускаем мышку
void __fastcall TForm1::FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
 if (step==4)
 {
 step=3;
 scr->Canvas->Draw(pazl[pnum][0],pazl[pnum][1],im[s(pnum).X][s(pnum).Y]);
 }
}

//Перемещение пазлов по форме
void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)

{
int i,j,k,tek;
RECT r,r1;
if (!Shift.Contains(ssLeft))
 {
 if (step>2)
  {
  MPanel->Height=85;
  MPanel->Visible=false;
  }
 return void();
 }
 //Если был Attach
if (step==5)
 {
 px=px+ix;
 py=py+iy;
 step=4;
 }
if (step!=4) return void();
GetRgnBox(reg[s(pnum).X][s(pnum).Y],&r);
//Чтобы пазлы не выходили за рамки окна
i=round((r.right-r.left)*StrToInt(Edit8->Text)/100);
j=round((r.bottom-r.top)*StrToInt(Edit8->Text)/100);
if (X-px+i<0) X=px-i;
if (Y-py+j<=0) Y=py-j;
if (X-px+r.right-r.left-i>ClientWidth) X=ClientWidth-(r.right-r.left)+px+i;
if (Y-py+r.bottom-r.top-j>ClientHeight) Y=ClientHeight-(r.bottom-r.top)+py+j;
//Двигаем пазл с перерисовкой
pazl[pnum][0]=X-px;
pazl[pnum][1]=Y-py;
sscr->Canvas->FillRect(Rect(0,0,sscr->Width,sscr->Height));
sscr->Canvas->Draw(0,0,scr);
sscr->Canvas->Draw(pazl[pnum][0],pazl[pnum][1],im[s(pnum).X][s(pnum).Y]);
Canvas->Draw(0,0,sscr);
//Ищем совместимые детали пазла по набору теков в группе
k=2;
while (pazl[pnum][k]!=0)
 {
 tek=pazl[pnum][k];
 //Проверяем возможных соседей справа
 if (tek%kolx!=0)
  {
  i=inarray(tek+1);
  if (i!=pnum)
   {
   GetRgnBox(reg[s(i).X][s(i).Y],&r1);
   if (abs(pazl[pnum][0]-r.left-pazl[i][0]+r1.left)<=att
	   and abs(pazl[pnum][1]-r.top-pazl[i][1]+r1.top)<=att)
	{
	attach(pnum,i);
	break;
	}
   }
  }
 //Проверяем возможных соседей слева
 if (tek%kolx!=1)
  {
  i=inarray(tek-1);
  if (i!=pnum)
   {
   GetRgnBox(reg[s(i).X][s(i).Y],&r1);
   if (abs(pazl[pnum][0]-r.left-pazl[i][0]+r1.left)<=att
	   and abs(pazl[pnum][1]-r.top-pazl[i][1]+r1.top)<=att)
	{
	attach(pnum,i);
	break;
	}
   }
  }
 //Проверяем возможных соседей сверху
 if (tek>kolx)
  {
  i=inarray(tek-kolx);
  if (i!=pnum)
   {
   GetRgnBox(reg[s(i).X][s(i).Y],&r1);
   if (abs(pazl[pnum][0]-r.left-pazl[i][0]+r1.left)<=att
	   and abs(pazl[pnum][1]-r.top-pazl[i][1]+r1.top)<=att)
	{
	attach(pnum,i);
	break;
    }
   }
  }
 //Проверяем возможных соседей снизу
 if (tek<=kolx*koly-kolx)
  {
  i=inarray(tek+kolx);
  if (i!=pnum)
   {
   GetRgnBox(reg[s(i).X][s(i).Y],&r1);
   if (abs(pazl[pnum][0]-r.left-pazl[i][0]+r1.left)<=att
	   and abs(pazl[pnum][1]-r.top-pazl[i][1]+r1.top)<=att)
	{
	attach(pnum,i);
	break;
	}
   }
  }
 ++k;
 }
}

//Основной модуль присоединения пазлов друг к другу
void __fastcall TForm1::attach(int x, int y)
{
int i,j,i1,j1;
RECT r;
TBitmap*  b = new TBitmap;
//Стыкуем точно
pazl[y][0]=pazl[x][0]-round(ind[s(x).X-1][s(x).Y-1].X)+round(ind[s(y).X-1][s(y).Y-1].X);
pazl[y][1]=pazl[x][1]-round(ind[s(x).X-1][s(x).Y-1].Y)+round(ind[s(y).X-1][s(y).Y-1].Y);
//Щелчок
if (CheckBox6->Checked) PlaySoundA((LPCSTR)"W1", NULL, SND_RESOURCE | SND_ASYNC);
//Объединяем группы
i1=pazl[x][2];
j1=pazl[y][2];
GetRgnBox(reg[s(i1).X][s(i1).Y],&r);
ix=r.left;
iy=r.top;
i=3;
while (pazl[x][i]!=0) ++i;
j=2;
while (pazl[y][j]!=0)
 {
 pazl[x][i]=pazl[y][j];
 pazl[y][j]=0;
 ++i;++j;
 }
//Делаем новую картинку пазла
//b:=tbitmap.Create;
b->Width=tekx;b->Height=teky;
b->Canvas->Brush->Color=clWhite;
b->PixelFormat=pf24bit;
b->TransparentColor=clWhite;
b->Transparent=true;
b->Canvas->FillRect(Rect(0,0,tekx,teky));
b->Canvas->Brush->Bitmap=Original1->Picture->Bitmap;
CombineRgn(reg[s(i1).X][s(i1).Y],reg[s(i1).X][s(i1).Y],reg[s(j1).X][s(j1).Y],RGN_OR);
PaintRgn(b->Canvas->Handle,reg[s(i1).X][s(i1).Y]);
GetRgnBox(reg[s(i1).X][s(i1).Y],&r);
im[s(x).X][s(x).Y]->Width=r.right-r.left;
im[s(x).X][s(x).Y]->Height=r.bottom-r.top;
im[s(x).X][s(x).Y]->Canvas->FillRect(Rect(0,0,r.right-r.left,r.bottom-r.top));
im[s(x).X][s(x).Y]->Canvas->Draw(-r.left,-r.top,b);
if (r.left<ix) ix=ix-r.left; else ix=0;
if (r.top<iy) iy=iy-r.top; else iy=0;
//Убираем ненужное и рисуем новое
//Чистим топ пазлов ptab
for (i=1;i<=ost;++i)
 if (ptab [i]==y) break;
for (j=i;j<=ost-1;++j) ptab[j]=ptab[j+1];
--ost;
im[s(y).X][s(y).Y]->Free();
DeleteObject(reg[s(y).X][s(y).Y]);
b->Free();
step=5;
scr->Canvas->FillRect(Rect(0,0,scr->Width,scr->Height));
for (i1=1;i1<=ost;++i1)
 {
 i=ptab[i1];
 if (i!=y and i!=x and pazl[i][2]!=0)
 scr->Canvas->Draw(pazl[i][0],pazl[i][1],im[s(i).X][s(i).Y]);
 }
//Завершение игры, если пазл собран полностью
if (pazl[x][kolx*koly+1]!=0)
 if (CheckBox6->Checked) PlaySoundA((LPCSTR)"W2", NULL, SND_RESOURCE | SND_ASYNC);
}

//Вспомогательные функции *******************************************************************************************************

//Перемещение одиночных пазлов в нужную сторону

//Вправо
void __fastcall TForm1::ib6Click(TObject *Sender)
{
int i;
normindex();
for (i=1;i<=kolx*koly;++i)
if (pazl[i][2]!=0 and pazl[i][3]==0)
 {
 pazl[i][0]=ClientWidth-ClientWidth/3+rand()%(ClientWidth/3-im[s(i).X][s(i).Y]->Width);
 pazl[i][1]=rand()%(ClientHeight-im[s(i).X][s(i).Y]->Height);
 }
ostpaint();
ib5->ImageIndex=12;
}

//Влево
void __fastcall TForm1::ib7Click(TObject *Sender)
{
int i;
normindex();
for (i=1;i<=kolx*koly;++i)
if (pazl[i][2]!=0 and pazl[i][3]==0)
 {
 pazl[i][0]=rand()%(ClientWidth/3-im[s(i).X][s(i).Y]->Width);
 pazl[i][1]=rand()%(ClientHeight-im[s(i).X][s(i).Y]->Height);
 }
ostpaint();
ib5->ImageIndex=12;
}

//Вверх
void __fastcall TForm1::ib8Click(TObject *Sender)
{
int i;
normindex();
for (i=1;i<=kolx*koly;++i)
if (pazl[i][2]!=0 and pazl[i][3]==0)
 {
 pazl[i][0]=rand()%(ClientWidth-im[s(i).X][s(i).Y]->Width);;
 pazl[i][1]=rand()%(ClientHeight/3-im[s(i).X][s(i).Y]->Height);
 }
ostpaint();
ib5->ImageIndex=12;
}

//Вниз
void __fastcall TForm1::ib9Click(TObject *Sender)
{
int i;
normindex();
for (i=1;i<=kolx*koly;++i)
if (pazl[i][2]!=0 and pazl[i][3]==0)
 {
 pazl[i][0]=rand()%(ClientWidth-im[s(i).X][s(i).Y]->Width);;
 pazl[i][1]=ClientHeight-ClientHeight/3+rand()%(ClientHeight/3-im[s(i).X][s(i).Y]->Height);
 }
ostpaint();
ib5->ImageIndex=12;
}
//---------------------------------------------------------------------------

//Возвращение пазлов на место после фильтрации
void __fastcall TForm1::normindex()
{
int i;
for (i=1;i<=ost;++i)
if (pazl[ptab[i]][1]<(-10000)) pazl[ptab[i]][1]=pazl[ptab[i]][1]+100000;
for (i=10;i<=25;++i)
 {
 TSpeedButton *sb = static_cast<TSpeedButton*>(FindComponent("ib"+IntToStr(i)));
 sb->ImageIndex=(i*3)-18;
 }
ib5->ImageIndex=12;
}

//Фильтрация одиночных пазлов по типу
void __fastcall TForm1::ib10Click(TObject *Sender)
{
int t,i;
TSpeedButton *sb = static_cast<TSpeedButton*>(Sender);
t=sb->Tag;
if (sb->ImageIndex==9+t*3)
 {
 normindex();
 sb->ImageIndex=10+t*3;
 for (i=1;i<=ost;++i)
 if (pazl[ptab[i]][2]!=0 and pazl[ptab[i]][3]==0)
  if (vatek[s(ptab[i]).X-1][s(ptab[i]).Y-1]!=filtr[t-1][0] or vatek[s(ptab[i]).X][s(ptab[i]).Y-1]!=filtr[t-1][1]
		or gatek[s(ptab[i]).X-1][s(ptab[i]).Y-1]!=filtr[t-1][2] or gatek[s(ptab[i]).X-1][s(ptab[i]).Y]!=filtr[t-1][3])
		  pazl[ptab[i]][1]=pazl[ptab[i]][1]-100000;
 } else normindex();
ostpaint();
}
//---------------------------------------------------------------------------

//Отбираем элементы рамки
void __fastcall TForm1::ib5Click(TObject *Sender)
{
int i,j;
if (ib5->ImageIndex==12)
 {
 normindex();
 ib5->ImageIndex=13;
 for (i=1;i<=kolx*koly;++i)
 if (s(i).X!=1 and s(i).X!=kolx and s(i).Y!=1 and s(i).Y!=koly)
 if (pazl[i][3]==0) pazl[i][1]=pazl[i][1]-100000;
 }
  else
 {
 normindex();
 for (i=1;i<=ost;++i)
 if (pazl[ptab[i]][1]<(-10000) and pazl[ptab[i]][3]==0) pazl[ptab[i]][1]=pazl[ptab[i]][1]+100000;
 }
 ostpaint();
}
//---------------------------------------------------------------------------



