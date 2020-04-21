#include <iostream>
#include <cmath>

#include "Globals.h"

constexpr double alpha = 1.0 / 137;
constexpr double hc    = 200.0 * MeV * fm;

constexpr double md     = 1875.6 * MeV;
constexpr double mtitan = 44652.0 * MeV;

constexpr double Eded     = 10 * eV;
constexpr double Edetitan = 25 * eV;

const double CTF = 1.0/2.0*pow(3*M_PI/4, 2.0/3.0);
const double ec = sqrt(alpha);
const double me = 0.511 * MeV;
const double a0 = 1.0/me/ec/ec;

double GetRutherfordCSFromtminTotmax(double Tls, int z, double m, int Z, double M)
{
    const double pls2 = Tls * (2 * m + Tls);
    const double mr = m*M/(m+M);
    const double rat = m/M;
    const double rat2 = rat * rat;
    const double pcm2 = pls2 / (1.0 + rat2 + 2 * sqrt(rat2 + pls2/M/M));
    const double tmax = 4 * pcm2;
    double tmin=0.0;
    if(Z==1 && M==md)           tmin = 2 * md * Eded;
    else if(Z==22 && M==mtitan) tmin = 2 * mtitan * Edetitan;
    const double coef = 2*mr*alpha*hc*z*Z;
    const double COEF1 = coef * coef;
    const double COEF2 = M_PI/pcm2;
    const double cs = COEF2 * COEF1 * (1.0/tmin - 1.0/tmax);
    return cs;
}

double GetRutherfordCSFrom0TotmaxElectronScreening(double Tls, int z, double m, int Z, double M)
{
    const double pls2 = Tls * (2 * m + Tls);
    const double mr = m*M/(m+M);
    const double rat = m/M;
    const double rat2 = rat * rat;
    const double pcm2 = pls2 / (1.0 + rat2 + 2 * sqrt(rat2 + pls2/M/M));
    const double tmax = 4 * pcm2;
    double tmin=0.0;
    if(Z==1 && M==md)           tmin = 2 * md * Eded;
    else if(Z==22 && M==mtitan) tmin = 2 * mtitan * Edetitan;
    //
    auto const pcm=sqrt(pcm2);
    auto const aI=CTF*a0/sqrt(pow(z, 2.0/3.0) + pow(Z, 2.0/3.0));
    auto const beta_r=pcm/sqrt(m*m+pcm2);//=1.0;
    //beta_r!=1.0!!!!!!!!!
    auto const c12=alpha*z*Z/beta_r;
    auto const c122=c12*c12;
    auto const const1=1.0/2/aI/pcm;
    auto const const2=const1*const1;
    auto const AS=const2*(1.13+3.76*c122);
    auto const ca0=mr*alpha*z*Z;
    auto const pcm4=pcm2*pcm2;
    auto const ca=ca0*ca0*M_PI/4/pcm4/pcm2;
    auto const ASC1=tmax/4/pcm2+AS;
    auto const ASC=tmax/AS/ASC1;
    const double cs=ca*ASC*hc*hc;
    return cs;
}

int main(int argc, char *argv[])
{   
    const double Tls = 100 * keV;

    // D-Ti Rutherford cross section:
    const double CSDTi0 = GetRutherfordCSFromtminTotmax(Tls, 1, md, 22, mtitan);

    std::cout<<"CSDTi0="<<CSDTi0/mbarn<<" mbarn = "<<CSDTi0/barn<<" barn"<<std::endl;
    exit(0);

    const double CSDD = GetRutherfordCSFromtminTotmax(Tls, 1, md, 1, md);
    std::cout<<"CSDD="<<CSDD/mbarn<<std::endl;
    const double CSDTi = GetRutherfordCSFromtminTotmax(Tls, 1, md, 22, mtitan);
    std::cout<<"CSDTi="<<CSDTi/mbarn<<std::endl;
    const double CS = 2.0/3.0 * CSDD + 1.0/3.0 * CSDTi;
    std::cout<<"CS="<<CS/mbarn<<" mbarn"<<std::endl;
    std::cout<<"CS="<<CS/barn<<" barn"<<std::endl;
    const double ntid2 = 1.4e23/cm/cm/cm;
    const double l = 1.0/ntid2/CS;
    std::cout<<"l="<<l/um<<" um"<<std::endl;
    std::cout<<"-------------------------------------------"<<std::endl;
    const double CSDD1 = GetRutherfordCSFrom0TotmaxElectronScreening(Tls, 1, md, 1, md);
    std::cout<<"CSDD1="<<CSDD1/mbarn<<std::endl;
    const double CSDTi1 = GetRutherfordCSFrom0TotmaxElectronScreening(Tls, 1, md, 22, mtitan);
    std::cout<<"CSDTi1="<<CSDTi1/mbarn<<std::endl;
    const double CS1 = 2.0/3.0 * CSDD1 + 1.0/3.0 * CSDTi1;
    std::cout<<"CS1="<<CS1/mbarn<<" mbarn"<<std::endl;
    std::cout<<"CS1="<<CS1/barn<<" barn"<<std::endl;
    const double l1 = 1.0/ntid2/CS1;
    std::cout<<"l1="<<l1/um<<" um"<<std::endl;
    return 0;
}
