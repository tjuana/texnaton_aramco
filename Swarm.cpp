#include <stdio.h>
#include <time.h>
#include <math.h>

//in meeters
struct TPoint 
{ float X,Y;
  void Init(int x, int y) {X=x; Y=y;}
}; 

//in meeters
struct TRect 
{ float X0,Y0,X1,Y1;
  void Init(int x0, int y0, int x1, int y1) {X0=x0; Y0=y0; X1=x1; Y1=y1;}
}; 

struct TDrone
{ float RestFlyTime; //in seconds, when charge is full equals 30*60   
  TPoint Pos;        //current coordinates
  bool Charging;     //dron changes batarry
};

//Experiment with swarm and truk
struct TSwarm
{ TPoint AllDim;  //the range of all field = (10000,2000)
  TRect BlueRect;
  float DronSpeed,TrukSpeed; //m/s
  float MaxFlyTime; //30*60
  float ExperimentT; //10h
  float TruckD;  //50m
  int NX,NY;      //the number of vertical and gorizontal lines in midpoints grig
  float DX,DY;    //sizes of midpoints grid cell times 2
  TPoint Base;    //coordinates of the charging base
  TPoint Truck;   //coordinates of the truk in the next step 
  float StepT;    //truk moving time period in sec
  float MoveTime; //time in sec of moving
  bool* Reached;  //array of midpoints NX*NY - which points are already reached
  int MReached;   //NX*NY - the number of measurings 
  int NReached;   //the number of reached midpoins
  int AllCharges; //the number of drone charges in sum 
  float T;        //current time in seconds from begining of experiment
  int NStep;      //current number of the step
  int NDrones;    //the number of drones 
  TDrone* Drones; 
  float RestChargeT[2]; //the rest charge time for two charging places
  TPoint* AP;    //obtain all coordinates of the image of left bottom conner of the blue rect before experiment 
  int MStep;

  TSwarm(): Reached(0), Drones(0) {}
  ~TSwarm() {delete [] Reached; delete[] Drones; delete[] AP;} 
  void Init();   //default initialization given in the task 
  float RequiredTime(float dist); //required time for a fly between two points on the land on the distanse = dist
  int FindNearest(TPoint p0, TPoint ap0, TPoint& p1, float& dist); //Find the nearest point among not reached points. Returns the index in array Reached or -1.
  void OneStep(); //produce one step of the system  
  void Experiment(bool& stopByTime); //produce all experiment
};

TSwarm S;

void TSwarm::Init()
{ AllDim.Init(10000,2000);
  BlueRect.Init(4500,300,6500,900);
  MaxFlyTime=30*60;  
  DronSpeed=50*(10/36); TrukSpeed=5*(10/36);
  MoveTime=50/TrukSpeed; StepT=24+MoveTime;  
  ExperimentT=10*3600;
  TruckD=50;
  NX=41; NY=13;
  DX=2*(BlueRect.X1-BlueRect.X0)/(NX-1);
  DY=2*(BlueRect.Y1-BlueRect.Y0)/(NY-1);
  Base.Init(5000,1000);
  Truck.Init(0,50);  
  MReached=NX*NY;
  Reached=new bool[MReached];
  NReached=0;
  AllCharges=0;
  NStep=0;
  T=0;
  NDrones=5;  
  TPoint p;
  p.X=2*BlueRect.X0-Truck.X;
  p.Y=2*BlueRect.Y0-Truck.Y;
    //before truk begin vibrate we move drones in there first measure points 
  for(int n=0; n<NDrones; n++)
  { TDrone& d=Drones[n]; 
    d.Charging=0;
    d.RestFlyTime=MaxFlyTime;
    d.Pos=Base;
    float dist;
    int i=FindNearest(Base,p, d.Pos, dist);
    Reached[i]=1; 
    if(i>=0) 
    { NReached++;  
      float t=RequiredTime(dist);
      d.RestFlyTime-=t;
      if(T<t) T=t;  
    }  
  }  
  for(int n=0; n<2; n++) RestChargeT[n]=0;
  MStep=(ExperimentT-MoveTime)/StepT;
  AP=new TPoint[MStep];
  bool forw=1;
  float dx=AllDim.X*2;
  for(int n=0; n<MStep; n++)
  { AP[n]=p;
    if(forw) 
    { if(p.X<=dx-TruckD) p.X+=TruckD;
      else {p.Y+=TruckD; forw=0;} 
    }
    else
    { if(p.X>=TruckD) p.X-=TruckD;
      else {p.Y+=TruckD; forw=1;} 
    }
  }
}

float TSwarm::RequiredTime(float dist) {return dist/DronSpeed+4;}

int TSwarm::FindNearest(TPoint p0, TPoint ap, TPoint& p1, float& dist)
{ int i=-1;
  float d=1e10; //min square of distance 
  for(int nx=0; nx<NX; nx++)
  { float x=ap.X+nx*DX, dx=x-p0.X, dx2=dx*dx;
    for(int ny=0; ny<NY; ny++)  
    { float y=ap.Y+ny*DY, dy=y-p0.Y;
      float d2=dx2+dy*dy; 
      if(d>d2) {d=d2; p1.X=x; p1.Y=y; i=nx+NX*ny;}
    }
  } 
  if(i>=0) dist=sqrt(d);
  return i;
}

void TSwarm::OneStep()
{ TPoint* ap=AP+NStep;
  TPoint ap0=*ap;

}

void TSwarm::Experiment(bool& stopByTime)
{ stopByTime=0;
  while(1)
  { if(NReached>=MReached) return;
    if(T+StepT>ExperimentT) {stopByTime=1; return;}
    OneStep();
    NReached;
  }
}

int main()
{ time_t t0=time(0);
  S.Init();
  bool stopByTime;
  S.Experiment(stopByTime); 
  float dt=time(0)-t0;
  printf("Grid %dx%d=%d, ", S.NX, S.NY); 
  if(stopByTime) printf("Reached=%d", S.NReached);
  else printf("Time=%d", int(S.T+0.5));
  printf(", AllCharges=%d, S. t=%0.3f sec\n", S.AllCharges, dt);
}