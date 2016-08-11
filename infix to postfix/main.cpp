#include <iostream>
#include <string>
#include "calculator.h"

using namespace std;

int main()
{
  calculator calc;
  while (true) {
    calc.readInput();
    if (calc.isStopCondition()) {
      // Encountering a . is a stopping condition
      break;
    }
    calc.convertInputIntoPostfix();
    calc.outputPostfix();
    calc.evaluatePostfixIntoResult();
    calc.outputResult();
  }
  return 0;
}
