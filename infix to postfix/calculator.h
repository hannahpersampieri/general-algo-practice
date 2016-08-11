#ifndef CALC_H
#define CALC_H

#include <iostream>
#include <string>
#include <cmath>
#include <stdio.h>
#include "stack.h"

using namespace std;

class calculator {

 public:

 calculator()
   : mInfixInput(""), mPostfixOutput("")
    {}

  void readInput();
  void convertInputIntoPostfix();
  void outputPostfix() const;
  void evaluatePostfixIntoResult();
  void outputResult() const;
  bool isStopCondition() const;

 private:

  // Helper functions
  bool hasHigherPrecedenceThan(int aLHS, int aRHS) const;

  bool isOperator(int c) const;
  
 private:
  string mInfixInput;
  string mPostfixOutput;
  int mResult;

};

bool calculator::isStopCondition() const
{
  return (mInfixInput == ".");
}

void calculator::readInput()
{
  mInfixInput.clear();
  mPostfixOutput.clear();
  cin >> mInfixInput;
}

void calculator::outputPostfix() const
{
  cout << "Postfix = "
       << mPostfixOutput 
       << endl;
}

void calculator::outputResult() const
{
  cout << "Result = "
       << mResult
       << endl;
}

// Returns true if aLHS has a higher precedence than aRHS.
// Otherwise, returns false.
bool calculator::hasHigherPrecedenceThan(int aLHS, int aRHS) const
{
  if ((aRHS == '+' || aRHS == '-') &&
      (aLHS == '*' || aLHS == '/' || aLHS == '^')) {
    return true;
  }
  if ((aRHS == '+' || aRHS == '-' || aRHS == '*' || aRHS == '/') &&
      (aLHS == '^')) {
    return true;
  }
  if (aLHS == '^' && aRHS == '^') {
    return true;
  }
  return false;
}

bool calculator::isOperator(int c) const
{
  return ((c == '+') ||
	  (c == '-') ||
	  (c == '*') ||
	  (c == '/') ||
	  (c == '^'));
}

void calculator::convertInputIntoPostfix()
{
	int len  = mInfixInput.length();
	stack s;
	for(int i = 0; i < len; i++){
		if(isOperator(mInfixInput[i]) == false){
			mPostfixOutput += mInfixInput[i];
		}
		else{
			int top_elem = 0;
			if(!s.isEmpty()){
			        top_elem = s.top();
			}
			while(!s.isEmpty() && !hasHigherPrecedenceThan(mInfixInput[i], top_elem)){
				mPostfixOutput += top_elem;
				s.pop();
		  		if(!s.isEmpty()){
					top_elem = s.top();
				}
			}
			s.push(mInfixInput[i]);
		}
	}
	while(!s.isEmpty()){
		int top_elem = s.top();
		mPostfixOutput += top_elem;
		s.pop();
	}
}

void calculator::evaluatePostfixIntoResult()
{
	int len = mPostfixOutput.length();
	stack s;
	for(int i = 0; i < len; i++){
		if(isOperator(mPostfixOutput[i]) == false){
			s.push(mPostfixOutput[i]);
		}
		else if(isOperator(mPostfixOutput[i])){
			int operand1 = s.top()-'0';
			s.pop();
			int operand2 = s.top()-'0';
			s.pop();
			if(mPostfixOutput[i] == '+'){
				int result = operand1 + operand2;
				s.push('0'+result);
			}
			else if(mPostfixOutput[i]== '-'){
				int result = operand2 - operand1;
				s.push('0'+result);
			}
			else if(mPostfixOutput[i] == '*'){
				int result = operand1 * operand2;
				s.push('0'+result);
			}
			else if(mPostfixOutput[i] == '/'){
				int result = operand2 / operand1;
				s.push('0'+result);
			}
			else if(mPostfixOutput[i] == '^'){
				int result = pow(operand2,operand1);
				s.push('0'+result);
			}
		}
	}			     	
	mResult = s.top()- '0';
}


#endif
