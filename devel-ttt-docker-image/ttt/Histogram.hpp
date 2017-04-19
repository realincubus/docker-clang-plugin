
#pragma once

#include <vector>
#include <limits>
#include <iostream>

template <typename T>
struct Histogram{

  Histogram( T _min, T _max, int number_of_bins ) :
    min(_min),
    max(_max)
  {
    bins.resize(number_of_bins);
  }

  void collect( T rval ) {
    auto val = rval - min;

    // collect min max
    if ( val < collect_min ) collect_min = val;
    if ( val > collect_max ) collect_max = val;

    // clamp to region
    if ( val > max ) val = max;
    if ( val < min ) val = min;

    int bin_idx = val / bins.size();    
    bins[bin_idx]++;
  }

  void print(){
    using namespace std;
    cout << collect_min << " " << collect_max << endl;
    cout << "| ";
    for( int i = 0 ; i < bins.size() ; i++ ) {
      cout << min + (( max-min ) / bins.size() ) * i << " | ";
    }
    cout << endl;

    cout << "| ";
    for( auto& bin : bins ) {
      cout << bin << " | ";
    }
    cout << endl;
  }

  T min;
  T max;
  T collect_min = std::numeric_limits<T>::min();
  T collect_max = std::numeric_limits<T>::max();
  std::vector<T> bins;
};
