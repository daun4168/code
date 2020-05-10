#include <type_traits>
#include <iostream>
#include <concepts>

template< class T, class U >
concept SameHelper = std::is_same_v<T, U>;

// template< class T, class U >
// concept my_same_as = SameHelper<T, U>;

template < class T >
concept integral = std::is_integral_v<T>;

template< class T, class U >
concept my_same_as = SameHelper<T, U> && SameHelper<U, T>;

template< class T, class U> requires my_same_as<U, T>
void foo(T a, U b) {
    std::cout << "Not integral" << std::endl;
}

template< class T, class U> requires (my_same_as<T, U> && integral<T>)
void foo(T a, U b) {
    std::cout << "Integral" << std::endl;
}

int main() {
    foo(1, 2);
    return 0;
}