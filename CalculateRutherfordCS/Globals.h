#ifndef GLOBALS_H
#define GLOBALS_H

constexpr double MeV = 1.0;
constexpr double keV = 1.0e-3 * MeV;
constexpr double eV  = 1.0e-6 * MeV;

constexpr double mm = 1.0;
constexpr double cm = 10.0 * mm;
constexpr double m  = 1.0e3 * mm;
constexpr double um = 1.0e-3 * mm;
constexpr double nm = 1.0e-6 * mm;
constexpr double fm = 1.0e-13 * cm;

constexpr double cm2   = cm *cm;
constexpr double barn  = 1.0e-24 * cm2;
constexpr double mbarn = 1.0e-3 * barn;

#endif // GLOBALS_H
