#include <iostream>
#include <iomanip>
#include <sys/time.h>
#include <unistd.h> // usleep
#include <stdio.h> // getchar()
#include <math.h> // fabs
#include "keypress.h"

using namespace std;

struct timeval tv_zero,tv;
struct timezone tz;

#define RESOLUTION      1000     // usec


void inittime()
{
  tz.tz_minuteswest= -60; // set time zone
  gettimeofday(&tv_zero,&tz); // reset tv_zero
}


long get_currenttime()
{
  unsigned long secdiff,usecdiff;

  gettimeofday(&tv,&tz);
  secdiff= (tv.tv_sec - tv_zero.tv_sec) * 1000000 / RESOLUTION;
  usecdiff= (tv.tv_usec - tv_zero.tv_usec) / RESOLUTION;
  return secdiff+usecdiff;
} // get_currenttime()



int main()
{
char nextchar='@';
long interval=0;
double tempo=100,averagetempo=100;

  long prevtime=get_currenttime();

  init_keypress();

  while(nextchar != 'q'){
    if(keypressed())
    {
      nextchar = getchar(); // clear input buffer
      interval = get_currenttime() - prevtime;
      prevtime = get_currenttime();
    } // if
    else {
      usleep(5000);
      continue;
    } // else
    if(interval == 0) continue;
    tempo = 60000.0/interval;
    // adapt to large change immediately, otherwise use running average
    if(fabs(tempo-averagetempo)/averagetempo > 0.2) averagetempo=tempo;
    else averagetempo += 0.1*(tempo-averagetempo);
    cout << setw(5) << fixed << setprecision(1) << right << averagetempo << " BPM -- (" << interval << " msec)" << endl;
  }
  return 0;
}

