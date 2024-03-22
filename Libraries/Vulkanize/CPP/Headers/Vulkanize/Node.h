#pragma once

namespace VULKANIZE
{
  struct Node
  {
    Node* parent           = nullptr;
    Node* first_child      = nullptr;
    Node* last_child       = nullptr;
    Node* next_sibling     = nullptr;
    Node* previous_sibling = nullptr;

    virtual ~Node();
    virtual void destroy();

    virtual void on_destroy() {}

    virtual void add( Node* child );
    virtual void remove_child( Node* child );
  };
};
