

#ifndef __ANIMATED_VALUE_H__
#define __ANIMATED_VALUE_H__ (1)


class AnimatedValue {
  private:
    unsigned long duration;
    unsigned long millisStart;
    unsigned long millisEnd;

    long randomRange;
    
  public:
    AnimatedValue();
    
    void Kick();
    void Set( unsigned long _interval = 0);
    float Get();

  private:
    float vstart;
    float vend;
    
  public:
    // layer to add a value range
    void SetValRange( float startv, float endv );
    float GetVal();

    float GetValStart() { return this->vstart; }
    float GetValEnd() { return this->vend; }
};


#endif
