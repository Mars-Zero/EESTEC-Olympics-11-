#include <iostream>
#include <fstream>
#include <cmath>

#define MONTEN 6

double detectEcryption(char *filePath)
{
  long byteCount[256];
  long totalc = 0;
  long monte[MONTEN];
  int monteCounter = 0;
  double mcount, montex, montey, incircle, inmonte;
  inmonte = mcount = 0;
  incircle = pow(pow(256.0, (MONTEN / 2.0)) - 1, 2.0);

  for (int i = 0; i < 256; i++)
  {
    byteCount[i] = 0;
  }

  std::ifstream fin(filePath, std::ios::binary);
  if (fin.is_open())
  {
      while (true)
      {
        unsigned char oc;
        fin.read(reinterpret_cast<char *>(&oc), sizeof(oc));
        if (!fin) {
          break;
        }
        totalc += 1;
        byteCount[oc]++;

        monte[monteCounter++] = oc;
        if (monteCounter >= MONTEN)
        {
          int montej;

          monteCounter = 0;
          mcount++;
          montex = montey = 0;
          for (montej = 0; montej < MONTEN / 2; montej++)
          {
            montex = (montex * 256.0) + monte[montej];
            montey = (montey * 256.0) + monte[(MONTEN / 2) + montej];
          }
          if ((montex * montex + montey * montey) <= incircle)
          {
            inmonte++;
          }
        }
      }
    }
  else
  {
    return 0;
  }

  double percent = 0;
  double montepi = 4.0 * (((double)inmonte) / mcount);
  double monteErrRate = 100.0 * (fabs(M_PI - montepi) / M_PI);
  if (monteErrRate < 0.01)
  {
    percent += 95;
  }
  double expecti = (double)totalc / 256.0;
  double t = 0;
  for (int i = 0; i < 256; i++)
  {
    double diff = byteCount[i] - expecti;
    t += (diff * diff) / expecti;
  }
  double chisq = t;
  if (chisq > 300 && monteErrRate < 0.03)
  {
    percent += 75;
  }
  if (chisq < 300 && monteErrRate > 0.03)
  {
    percent += 60;
  }
  if (chisq > 2000 && monteErrRate > 20)
  {
    percent = 0;
  }
  if (percent >= 100)
  {
    percent = 99;
  }
  return percent;
}

int main(int argc, char *argv[])
{
  for (int i = 1; i < argc; i++)
  {
    std::cout << argv[i] << " ";
    double value = detectEcryption(argv[i]);
    std::cout << value << " ";
  }
  return 0;
}

