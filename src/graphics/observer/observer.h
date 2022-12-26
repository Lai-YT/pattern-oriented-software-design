#ifndef SRC_GRAPHICS_OBSERVER_OBSERVER_H_
#define SRC_GRAPHICS_OBSERVER_OBSERVER_H_

class Observer {
 public:
  virtual void update() = 0;
  virtual ~Observer() = default;
};

#endif /* end of include guard: SRC_GRAPHICS_OBSERVER_OBSERVER_H_ */