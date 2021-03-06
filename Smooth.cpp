#include "Smooth.h"
#include <math.h>


smoothLatLong::smoothLatLong()
{
}

smoothLatLong::smoothLatLong1(float Q_metres_per_second) {
  this->Q_metres_per_second = Q_metres_per_second;
  variance = -1;
}

long smoothLatLong::get_TimeStamp() {
  return TimeStamp_milliseconds;
}
double smoothLatLong::get_lat() {
  return lat;
}
double smoothLatLong::get_lng() {
  return lng;
}
float smoothLatLong::get_accuracy() {
  return (float) sqrt(variance);
}
void smoothLatLong::SetState(double lat, double lng, float accuracy, long TimeStamp_milliseconds) {
  this->lat = lat;
  this->lng = lng;
  variance = accuracy * accuracy;
  this->TimeStamp_milliseconds = TimeStamp_milliseconds;
}


void smoothLatLong::Process(double lat_measurement, double lng_measurement, float accuracy, long TimeStamp_milliseconds) {
  if (accuracy < MinAccuracy) accuracy = MinAccuracy;
  if (variance < 0) {
    // if variance < 0, object is unitialised, so initialise with current values
    this->TimeStamp_milliseconds = TimeStamp_milliseconds;
    lat = lat_measurement; lng = lng_measurement; variance = accuracy * accuracy;
  } else {
    // else apply Kalman filter methodology

    long TimeInc_milliseconds = TimeStamp_milliseconds - this->TimeStamp_milliseconds;
    if (TimeInc_milliseconds > 0) {
      // time has moved on, so the uncertainty in the current position increases
      variance += TimeInc_milliseconds * Q_metres_per_second * Q_metres_per_second / 1000;
      this->TimeStamp_milliseconds = TimeStamp_milliseconds;
      // TO DO: USE VELOCITY INFORMATION HERE TO GET A BETTER ESTIMATE OF CURRENT POSITION
    }

    // Kalman gain matrix K = Covarariance * Inverse(Covariance + MeasurementVariance)
    // NB: because K is dimensionless, it doesn't matter that variance has different units to lat and lng
    float K = variance / (variance + accuracy * accuracy);
    // apply K
    lat += K * (lat_measurement - lat);
    lng += K * (lng_measurement - lng);
    // new Covarariance  matrix is (IdentityMatrix - K) * Covarariance
    variance = (1 - K) * variance;
  }
}
