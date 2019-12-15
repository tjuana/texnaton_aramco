#include <vcl.h>
#pragma hdrstop

#include "MainUnit.h"
#include "TypeDefs.h"
#include <math.h>
#include <stdio.h>

#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;

char Str[1000];
TStringList* SS;

int AAA;
double VVV;

void Calc();

__fastcall TForm1::TForm1(TComponent* Owner)
  : TForm(Owner), Ch(0)
{ SS=new TStringList;
  Calc();
  Ed->Text=SS->Text;
}

void __fastcall TForm1::FormDestroy(TObject *Sender)
{ delete SS;
}

//in meters
struct QPoint
{ float X,Y;
  void Init(int x, int y) {X=x; Y=y;}
};

//in meters
struct QRect
{ float X0,Y0,X1,Y1;
  void Init(int x0, int y0, int x1, int y1) {X0=x0; Y0=y0; X1=x1; Y1=y1;}
};

struct TDrone
{ float RestFlyTime; //in seconds, when charge is full equals 30*60
  QPoint Pos;        //current coordinates
  bool Charging;     //dron changes batarry#include <new>
  float RestChargeT; //rest charge time
  int FlyDelay;      //number of steps to fly

  QPoint P[602];     //position by steps
  float D[602];      //distances by step
  bool NewMeasure[602]; //in step was new measure
  float RFlyTime[602];
};

//Experiment with swarm and truk
struct TSwarm
{ QPoint AllDim;  //the range of all field = (10000,2000)
  QRect BlueRect;
  float DronSpeed,TrukSpeed; //m/s
  float MaxFlyTime; //30*60
  float ExperimentT; //10h
  float ChargeT;  //10*60
  float TruckD;   //50m
  int NX,NY;      //the number of vertical and gorizontal lines in midpoints grig
  float DX,DY;    //sizes of midpoints grid cell times 2
  QPoint Base;    //coordinates of the charging base
  float StepT;    //truk moving time period in sec
  float MoveTime; //time in sec of moving
  bool* Reached;  //array of midpoints NX*NY - which points are already reached
  int MReached;   //NX*NY - the number of measurings
  int NReached;   //the number of reached midpoins
  int AllCharge;  //the number of drone charges in sum
  float T;        //current time in seconds from begining of experiment
  int NStep;      //current number of the step
  int NDrone;     //the number of drones
  TDrone* Drone;
  float RestChargeT[2]; //rest charging time on both charging places
  QPoint* AP;     //obtain all coordinates of the image of left bottom conner of the blue rect before experiment
  int MStep;
  QPoint* TrP;

  TSwarm() {memset(this,0, sizeof(*this));}
  ~TSwarm() {Clear();}
  void Clear() {delete[] Reached; delete[] Drone; delete[] AP; delete[] TrP; memset(this,0, sizeof(*this));}
  void Init();   //default initialization given in the task
  float RequiredTime(float dist); //required time for a fly between two points on the land on the distanse = dist
  int FindNearest(QPoint p0, QPoint ap0, QPoint& p1, float& dist); //Find the nearest point among not reached points. Returns the index in array Reached or -1.
  bool TryPoint(TDrone& d, QPoint ap, int flyDelay);
  void OneStep(); //produce one step of the system
  void Experiment(bool& stopByTime); //produce all experiment
  void Draw(int step);
};

TSwarm S;

bool Re[602][2500];

float GetDist(QPoint p0, QPoint p1)
{ float dx=p1.X-p0.X, dy=p1.Y-p0.Y;
  return sqrt(dx*dx+dy*dy);
}

void TSwarm::Init()
{ AllDim.Init(10000,2000);
  BlueRect.Init(4500,300,6500,900);
  MaxFlyTime=30*60;
  DronSpeed=50*(10.0/36); TrukSpeed=5*(10.0/36);
  float stayTime=24;
  MoveTime=50/TrukSpeed; StepT=stayTime+MoveTime;
  ExperimentT=10*3600;
  TruckD=50;
  ChargeT=10*60;
  if(!NX) NX=41;
  if(!NY) NY=13;
  DX=2*(BlueRect.X1-BlueRect.X0)/(NX-1);
  DY=2*(BlueRect.Y1-BlueRect.Y0)/(NY-1);
  Base.Init(5000,1000);
  MReached=NX*NY;
  Reached=new bool[MReached]; memset(Reached,0,MReached);
  NReached=0;
  AllCharge=0;
  NStep=1;
  T=0;
  NDrone=5;
  Drone=new TDrone[NDrone];
  memset(Drone,0, NDrone*sizeof(TDrone));
  QPoint truck;
  truck.Init(0,50);
  QPoint p;
  p.X=2*BlueRect.X0-truck.X;
  p.Y=2*BlueRect.Y0-truck.Y;
    //before truk begin vibrate we move drones in there first measure points
  for(int n=0; n<NDrone; n++)
  { TDrone& d=Drone[n];
    d.Charging=0;
    d.RestFlyTime=MaxFlyTime;
    d.RestChargeT=0;
    d.FlyDelay=0;
    d.Pos=d.P[0]=Base;
    float dist;
    QPoint p1;
    int i=FindNearest(Base,p,p1,dist);
    if(i>=0)
    { float t=RequiredTime(dist);
      Reached[i]=1; NReached++;
      d.Pos=p1; d.RestFlyTime-=t;
      if(T<t) T=t;
      d.NewMeasure[1]=1;
    }
    d.P[1]=d.Pos;
    d.D[1]=GetDist(d.Pos, Base);
    d.RFlyTime[1]=d.RestFlyTime;
  }
  T+=stayTime;
  for(int n=0; n<2; n++) RestChargeT[n]=0;
    //obtain images of trunk positions on all steps
  MStep=(ExperimentT+MoveTime)/StepT;
  AP=new QPoint[MStep+1];
  TrP=new QPoint[MStep+1];
  bool forw=1;
  float dx=AllDim.X;
  for(int n=0; n<=MStep; n++)
  { TrP[n]=truck;
    AP[n].Init(2*BlueRect.X0-truck.X, 2*BlueRect.Y0-truck.Y);
    if(forw)
    { if(truck.X<=dx-TruckD) truck.X+=TruckD;
      else {truck.Y+=TruckD; forw=0;}
    }
    else
    { if(truck.X>=TruckD) truck.X-=TruckD;
      else {truck.Y+=TruckD; forw=1;}
    }
  }
  memcpy(Re[1], Reached,MReached);
}

float TSwarm::RequiredTime(float dist) {return dist/DronSpeed+4;}

int TSwarm::FindNearest(QPoint p0, QPoint ap, QPoint& p1, float& dist)
{ int im=-1;
  float d=1e10; //min square of distance
  for(int nx=0; nx<NX; nx++)
  { float x=ap.X+nx*DX;
    if(x<0) continue;
    if(x>AllDim.X) break;
    float dx=x-p0.X, dx2=dx*dx;
    for(int ny=0; ny<NY; ny++)
    { int i=nx+NX*ny;
      if(Reached[i]) continue;
      float y=ap.Y+ny*DY, dy=y-p0.Y;
      float d2=dx2+dy*dy;
      if(d>d2) {d=d2; p1.X=x; p1.Y=y; im=i;}
    }
  }
  if(im>=0) dist=sqrt(d);
  return im;
}

bool TSwarm::TryPoint(TDrone& d, QPoint ap, int flyDelay)
{ QPoint p1;
  float dist;
  int i=FindNearest(d.Pos, ap,p1,dist);
  if(i<0) return 0;
  float t=RequiredTime(dist);
  if(t>MoveTime+flyDelay*StepT) return 0;
  if(t+RequiredTime(GetDist(p1,Base))<=d.RestFlyTime)
  { Reached[i]=1; NReached++;
    d.Pos=p1; d.RestFlyTime-=t;
    d.FlyDelay=flyDelay;
    d.NewMeasure[NStep+1+flyDelay]=1;
    return 1;
  }
    //go to charging
  float& chT=RestChargeT[RestChargeT[1]<RestChargeT[0]];
  t=RequiredTime(GetDist(d.Pos, Base));
  d.Pos=Base; d.RestFlyTime-=t;
  d.RestChargeT=t+ChargeT; d.Charging=1;
  if(chT<t) chT=t;
  chT+=ChargeT;
  return 1;
}

void TSwarm::OneStep()
{ QPoint* ap=AP+NStep;
  QPoint ap0=*ap;
    //charging places
  for(int n=0; n<2; n++) if(RestChargeT[n]>0)
  { RestChargeT[n]-=StepT;
    if(RestChargeT[n]<0) RestChargeT[n]=0;
  }
    //drones
  for(int n=0; n<NDrone; n++)
  { TDrone& d=Drone[n];
    if(d.Charging)
    { d.RestChargeT-=StepT;
      if(d.RestChargeT<=0)
      { d.RestChargeT=0;
        d.Charging=0;
        d.RestFlyTime=MaxFlyTime;
        AllCharge++;
      }
      else continue;
    }
    if(d.FlyDelay) {d.FlyDelay--; continue;}
    if(TryPoint(d,ap0,0)) continue;
    for(int k=1; k<MStep-NStep; k++) if(TryPoint(d, ap[k], k)) break;
  }
  T+=StepT; NStep++;
  for(int n=0; n<NDrone; n++)
  { TDrone& d=Drone[n];
    d.P[NStep]=d.Pos;
    d.D[NStep]=GetDist(d.Pos, d.P[NStep-1]);
    d.RFlyTime[NStep]=d.RestFlyTime;
  }
  memcpy(Re[NStep], Reached,MReached);
}

void TSwarm::Experiment(bool& stopByTime)
{ stopByTime=0;
  while(1)
  { if(NReached>=MReached) return;
    if(NStep>=MStep) {stopByTime=1; return;}
    OneStep();
  }
}

int WX0=120, WY0=20, WL=5, WY1=WY0+200;
float W=0.1;

void TSwarm::Draw(int step)
{ TImage* im=Form1->Im;
  TCanvas& c=*im->Canvas;
  c.Brush->Color=clWhite;
  c.FillRect(TRect(0,0, im->Width, im->Height));
  c.Pen->Color=clBlack;
  c.Brush->Style=bsClear;
  c.Rectangle(WX0,WY0, WX0+W*AllDim.X, WY0+W*AllDim.Y);
  c.Brush->Style=bsSolid;
  c.Brush->Color=clAqua;
  c.Rectangle(WX0+W*BlueRect.X0, WY1-W*BlueRect.Y1, WX0+W*BlueRect.X1, WY1-W*BlueRect.Y0);

  c.Pen->Color=clBlack;
  c.Brush->Color=clLime;
  int x=WX0+W*Base.X, y=WY1-W*Base.Y;
  c.Ellipse(x-8, y-8, x+8, y+8);

  c.Brush->Color=clRed;
  QPoint trP=TrP[step-1];
  QPoint ap=AP[step-1];

  x=WX0+W*trP.X; y=WY1-W*trP.Y;
  c.Rectangle(x-4, y-4, x+6, y+6);

  float dx=W*DX, dy=W*DY;
  int x0=WX0+W*ap.X, y0=WY1-W*ap.Y, x1=x0+dx*(NX-1), y1=y0-dy*(NY-1);

  c.MoveTo(x,y); c.LineTo(x0,y0);

  c.Pen->Color=clSilver;
  for(int nx=0; nx<NX; nx++)
  { int x=x0+dx*nx;
    c.MoveTo(x,y0); c.LineTo(x,y1);
  }
  for(int ny=0; ny<NY; ny++)
  { int y=y0-dy*ny;
    c.MoveTo(x0,y); c.LineTo(x1,y);
  }
  c.Pen->Color=clBlack;
  c.Brush->Color=clGreen;
  bool* reached=Re[step];
  for(int nx=0; nx<NX; nx++) for(int ny=0; ny<NY; ny++)
  { int x=x0+dx*nx, y=y0-dy*ny;
    if(reached[nx+NX*ny]) c.Rectangle(x-2, y-2, x+4, y+4);
  }
  c.Brush->Color=clRed;
  SS->Clear();
  for(int n=0; n<NDrone; n++)
  { TDrone& d=Drone[n];
    QPoint p0=d.P[step-1], p1=d.P[step];
    x=WX0+W*p1.X; y=WY1-W*p1.Y;
    c.Rectangle(x-2, y-2, x+4, y+4);
    c.Pen->Width=3;
    c.MoveTo(WX0+W*p0.X, WY1-W*p0.Y);
    c.LineTo(x,y);
    c.Pen->Width=1;
    sprintf(Str, "Dron %d: LastDist=%0.1f, RestFlyTime=%0.1f", n+1, d.D[step], d.RFlyTime[step]);
    SS->Add(Str);
  }
  Form1->Ed->Text=SS->Text;
}

void Calc()
{ int t0=GetTickCount();
  S.Init();
  bool stopByTime;
  S.Experiment(stopByTime);
  float dt=(GetTickCount()-t0)*0.001;
  char* p=Str;
  p+=sprintf(p, "Grid %dx%d=%d, ", S.NX, S.NY, S.MReached);
  if(stopByTime) p+=sprintf(p, "Reached=%d", S.NReached);
  else p+=sprintf(p, "Time=%d", int(S.T+0.5));
  p+=sprintf(p, ", AllCharges=%d, CalcTime=%0.3f sec\n", S.AllCharge,  dt);
  Form1->ResE->Text=Str;
  Form1->StepSE->MaxValue=S.NStep;
  Form1->StepSE->Value=S.NStep;
  Form1->TB->Min=1; Form1->TB->Max=S.NStep;
  Form1->TB->Position=S.NStep;
//  S.Draw(S.NStep);
}

void __fastcall TForm1::StepSEChange(TObject *Sender)
{ S.Draw(StepSE->Value);
  if(TB->Position!=StepSE->Value) {Ch=1; TB->Position=StepSE->Value; Ch=0;}
}

void __fastcall TForm1::UD10Click(TObject *Sender, TUDBtnType Button)
{ if(Ch) return;
  TUpDown* ud=(TUpDown*)Sender;
  int d=ud->Tag;
  int v=StepSE->Value+((Button==btNext)? d: -d);
  if(v<1) v=1;
  if(v>600) v=600;
  StepSE->Value=v;
}

void __fastcall TForm1::ToFirstBtClick(TObject *Sender) {StepSE->Value=1;}
void __fastcall TForm1::ToLastBtClick(TObject *Sender)  {StepSE->Value=S.NStep;}

void __fastcall TForm1::TBChange(TObject *Sender)
{ if(Ch) return;
  StepSE->Value=TB->Position;
}

void __fastcall TForm1::RB0Click(TObject *Sender)
{ int x,y;
  switch(((TRadioButton*)Sender)->Tag)
  { case 0: x=40; y=12; break;
    case 1: x=80; y=24; break;
    case 2: x=120; y=36; break;
  }
  NXSE->Value=x; NYSE->Value=y;
  CalcBtClick(0);
}

void __fastcall TForm1::CalcBtClick(TObject *Sender)
{ S.Clear();
  S.NX=NXSE->Value; S.NY=NYSE->Value;
  Calc();
}
