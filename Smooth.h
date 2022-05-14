#ifndef SMOOTHLATLONG_H
#define SMOOTHLATLONG_H

class smoothLatLong
{
  public:
    float MinAccuracy = 1;
    float Q_metres_per_second;
    long TimeStamp_milliseconds;
    double lat;
    double lng;
    float variance; // P matrix.  Negative means object uninitialised.  NB: units irrelevant, as long as same units used throughout


  public:
    smoothLatLong();
    smoothLatLong1(float Q_metres_per_second);
    long get_TimeStamp();
    double get_lat();
    double get_lng();
    float get_accuracy();
    void SetState(double lat, double lng, float accuracy, long TimeStamp_milliseconds);
    void Process(double lat_measurement, double lng_measurement, float accuracy, long TimeStamp_milliseconds);
};

#endif // SMOOTHLATLONG_H
