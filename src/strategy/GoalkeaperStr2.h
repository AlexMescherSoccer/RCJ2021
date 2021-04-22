#include "Strategy.h"
#include "../Defines.h"

#ifndef GOALKEAPER2_H
#define GOALKEAPER2_H

#define TIMER_DEL 500

class GoalkeaperStr2 : public Strategy {
private:
  unsigned long long prev;
  bool isGoOnBall;
  
public:

    GoalkeaperStr2(Hardware *hw) : Strategy(hw){
        prev = millis();
        isGoOnBall = false;
    }

    void doStrategy() override {
      //getMovement()->setSpeed(GK_SPEED);
      //


//Log::info("Angle", String(getCamSensor()->getCamAngle()));
//Log::info("Dist", String(getGoalDist()));
      static int prev = 0, state = 0;

      /*if(getGoalDist() < 23 && getGoalDist() > 15)
        getMovement()->setSpeed(0);*/

      if(getBallSensor()->isCanSee()){
        getMovement()->setDirection(getBallSensor()->getAngle() > 0? 
          90 + getCamSensor()->getCamAngle(): 
          -90 + getCamSensor()->getCamAngle()
        );
        getMovement()->setSpeed(GK_SPEED);
      }
      else
        getMovement()->setSpeed(0);

      if(abs(getBallSensor()->getAngle()) < 15){
        getMovement()->setSpeed(0);
        if(state == 0)
          state = 1, prev = millis();
      }
      else
        state == 0, prev = millis();

      if(abs(getCamSensor()->getCamAngle()) < 95){
        getMovement()->setDirection(0);
        getMovement()->setSpeed(GK_SPEED);
      }
      

      if(getCamSensor()->getCamDist() >= 20){
        getMovement()->setDirection(180);
        getMovement()->setSpeed(GK_SPEED);
      }

      if(getCamSensor()->getCamDist() < 15){
        getMovement()->setDirection(0);
        getMovement()->setSpeed(GK_SPEED);
      }

      if(millis() - prev > 2500 && state == 1) {
        getMovement()->setDirection(getBallSensor()->getAngle() * 1.3);
        getMovement()->setSpeed(GK_SPEED);
        if(getGoalDist >= 40)
          state = 0;
      }
      
    } 
      

    int getType() override {
        return 4;
    }

    ~GoalkeaperStr2(){

    }

    //  int takeTargetAngleFromTrajectory(){

    //   static int cta = getBallSensor()->getAngle(), ota = 0, cd = getBallSensor()->getDistance(), od = 0, p = millis();
      
    //   if(millis() - p > 10)
    //   {
    //     ota = cta;
    //     od = cd; 
    //   }
    //   else if(millis() - p > 500)
    //   {
        

    //     cta = getBallSensor()->getAngle();
    //     cd = getBallSensor()->getDistance();
    //     p = millis();
    //   }
    // }

    float getGoalDist(){
        return abs(getCamSensor()->getCamDist() * cos(radians(getCamSensor()->getCamAngle())));
    }

    float getAnotherGoalDist(){
        return abs(getCamSensor()->getAnotherCamDist() * cos(radians(getCamSensor()->getAnotherCamAngle())));
    }
};

#endif