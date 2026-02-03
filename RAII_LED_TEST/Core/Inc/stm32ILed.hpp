#ifndef ILED_HPP
#define ILED_HPP
/*Interface definition for LED control Abstraction class*/
class ILED
{
public:
/*Virtual destructor for each derived class*/
    virtual ~ILED() = default;
/*Pure virtual funtions,  mandatory to be implemented in derived classes*/
    virtual void On() = 0;
    virtual void Off() = 0;
    virtual void Toggle() = 0;
    virtual bool IsOn() const = 0;
};       



#endif