#ifndef DETECT_H
#define DETECT_H
/********************************************************************
    This class is an abstract class, we can redefine the function
in the dericed class so that we can provide different method to compute
the checking.
********************************************************************/
class Detect
{

public:
    Detect() {}
    virtual ~Detect() {}
    virtual void startDetect(int , char **) = 0;
};


#endif //DETECT_H
