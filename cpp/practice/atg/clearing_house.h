#ifndef PNSEI_CLEARING_HOUSE_H
#define PNSEI_CLEARING_HOUSE_H

#include "henry.h"

namespace atg{

// https://interview.uberinternal.com/view/financial-clearing-house

struct transaction{
  string payer;
  string receiver;
  double amount;
};

vector<transaction> setup(){
  return {
      {"chase", "boa", 132},
      {"chase", "boa", 827},
      {"boa", "wf", 751},
      {"chase", "boa", 585},
      {"wf", "chase", 877},
      {"chase", "wf", 157},
      {"chase", "wf", 904},
      {"wf", "chase", 548},
      {"boa", "chase", 976},
      {"wf", "boa", 872},
      {"chase", "wf", 571}
  };
}

vector<transaction> setup_v2(){
  return {
      {"chase", "boa", 100},
      {"boa", "chase", 50},
      {"boa", "wf", 80},
      {"wf", "chase", 80}
  };
}

void financial_clearing_house(){
  vector<transaction> transactions = setup();
  // call your function + print final transactions
  map<pair<string,string>, double> m;
  for (auto& t: transactions){
    if (t.payer > t.receiver) {
      m[{t.payer, t.receiver}] += t.amount;
    } else if (t.payer < t.receiver){
      m[{t.receiver, t.payer}] -= t.amount;
    } else {
      cout << "data error" << endl;
    }
  }
  for(auto pr: m){
    printf("payer: %s, receiver: %s, amount: %.2f\n",
           pr.first.first.c_str(),
           pr.first.second.c_str(),
           pr.second);
  }
  /*
    payer: chase, receiver: boa, amount: 568.00
    payer: wf, receiver: boa, amount: 121.00
    payer: wf, receiver: chase, amount: -207.00
  */
}

void financial_clearing_house_v2(){
  vector<transaction> transactions = setup_v2();
  // call your function + print final transactions
  map<pair<string,string>, double> m;
  for (auto& t: transactions){
    if (t.payer > t.receiver) {
      m[{t.payer, t.receiver}] += t.amount;
    } else if (t.payer < t.receiver){
      m[{t.receiver, t.payer}] -= t.amount;
    } else {
      cout << "data error" << endl;
    }
  }
  for(auto pr: m){
    printf("payer: %s, receiver: %s, amount: %.2f\n",
           pr.first.first.c_str(),
           pr.first.second.c_str(),
           pr.second);
  }
  /*
payer: chase, receiver: boa, amount: 50.00
payer: wf, receiver: boa, amount: -80.00
payer: wf, receiver: chase, amount: 80.00
  */
}

}

#endif // PNSEI_CLEARING_HOUSE_H
