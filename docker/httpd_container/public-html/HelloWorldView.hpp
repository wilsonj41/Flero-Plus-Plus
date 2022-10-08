#ifndef HELLO_WORLD_VIEW_HPP
#define HELLO_WORLD_VIEW_HPP

#include "IView.hpp"

class HelloWorldView : public IView {
  public:
    HelloWorldView() = default;
    ~HelloWorldView() = default;
    void generate(std::ostream &os) override;
};

#endif /* HELLO_WORLD_VIEW_HPP */