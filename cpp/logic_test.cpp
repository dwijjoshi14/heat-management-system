#include <iostream>
using namespace std;

// Standalone logic test — validates threshold decisions
// independent of Arduino hardware

string getFanLevel(float temp) {
  if (temp > 85) return "MAX (100%)";
  if (temp > 60) return "HIGH (70%)";
  if (temp > 30) return "LOW (47%)";
  return "OFF (0%)";
}

string getLEDColor(float temp) {
  if (temp > 85) return "RED    — Critical";
  if (temp > 60) return "YELLOW — Hot";
  if (temp > 30) return "GREEN  — Warm";
  return "BLUE   — Safe";
}

int main() {
  float temp;
  cout << "Enter temperature (C): ";
  cin >> temp;
  cout << "\nFan Level : " << getFanLevel(temp) << endl;
  cout << "LED Color : " << getLEDColor(temp) << endl;
  return 0;
}
