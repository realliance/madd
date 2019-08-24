#ifndef SYSTEM_H
#define SYSTEM_H

template <class T>
class System{
  public:
    virtual bool Init() = 0;
    virtual bool Deinit() = 0;
    virtual bool Register(T* component) = 0;
    virtual bool Deregister(T* component) = 0;
    virtual void Update() = 0;
};

#endif // !SYSTEM_H
