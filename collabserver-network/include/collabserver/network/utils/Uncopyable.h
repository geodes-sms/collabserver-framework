#pragma once

namespace collabserver {

/**
 * Uncopyable interface.
 * Any class that inherits from Uncopyable cannot be copied anymore.
 * (Disable copy constructor and copy operator.)
 *
 *
 * \code{.cpp}
 * class A : private Uncopyable<A> {
 *     // Your code
 * };
 * \endcode
 */
template <class T>
class Uncopyable {
   public:
    Uncopyable() = default;
    virtual ~Uncopyable() = default;

   private:
    Uncopyable(Uncopyable<T> const& other) = delete;
    Uncopyable<T>& operator=(Uncopyable<T> const& other) = delete;
};

}  // namespace collabserver
