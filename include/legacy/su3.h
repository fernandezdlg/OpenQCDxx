// This corresponds to the implementation of the su3 matrix and algebra in the OpenQCD program.
// I have templated it for float and double types, but the structure remains as in the original.

#ifndef SU3_H
#define SU3_H


template<typename T>
struct Complex {
    T re, im;
};


template<typename T>
struct SU3 {
    Complex<T> c11, c12, c13, c21, c22, c23, c31, c32, c33;
};


template<typename T>
struct SU3Alg {
    T c1, c2, c3, c4, c5, c6, c7, c8;
};


// This jumps several abstractions (matrix as struct -> complex as struct -> float type ops) in one
// step, def. not super maintainable and modernizing to std::complex and mdarray<T> could
// be better.
template<typename T>
SU3<T> multiply_SU3(const SU3<T>& v1, const SU3<T>& v2) {
    SU3<T> result;
    // Real part
    result.c11.re = v1.c11.re * v2.c11.re + v1.c12.re * v2.c21.re + v1.c13.re * v2.c31.re  \
                  -(v1.c11.im * v2.c11.im + v1.c12.im * v2.c21.im + v1.c13.im * v2.c31.im);

    result.c12.re = v1.c11.re * v2.c12.re + v1.c12.re * v2.c22.re + v1.c13.re * v2.c32.re  \
                  -(v1.c11.im * v2.c12.im + v1.c12.im * v2.c22.im + v1.c13.im * v2.c32.im);

    result.c13.re = v1.c11.re * v2.c13.re + v1.c12.re * v2.c23.re + v1.c13.re * v2.c33.re  \
                  -(v1.c11.im * v2.c13.im + v1.c12.im * v2.c23.im + v1.c13.im * v2.c33.im);

    result.c21.re = v1.c21.re * v2.c11.re + v1.c22.re * v2.c21.re + v1.c23.re * v2.c31.re  \
                  -(v1.c21.im * v2.c11.im + v1.c22.im * v2.c21.im + v1.c23.im * v2.c31.im);

    result.c22.re = v1.c21.re * v2.c12.re + v1.c22.re * v2.c22.re + v1.c23.re * v2.c32.re  \
                  -(v1.c21.im * v2.c12.im + v1.c22.im * v2.c22.im + v1.c23.im * v2.c32.im);

    result.c23.re = v1.c21.re * v2.c13.re + v1.c22.re * v2.c23.re + v1.c23.re * v2.c33.re  \
                  -(v1.c21.im * v2.c13.im + v1.c22.im * v2.c23.im + v1.c23.im * v2.c33.im);

    result.c31.re = v1.c31.re * v2.c11.re + v1.c32.re * v2.c21.re + v1.c33.re * v2.c31.re  \
                  -(v1.c31.im * v2.c11.im + v1.c32.im * v2.c21.im + v1.c33.im * v2.c31.im);

    result.c32.re = v1.c31.re * v2.c12.re + v1.c32.re * v2.c22.re + v1.c33.re * v2.c32.re  \
                  -(v1.c31.im * v2.c12.im + v1.c32.im * v2.c22.im + v1.c33.im * v2.c32.im);

    result.c33.re = v1.c31.re * v2.c13.re + v1.c32.re * v2.c23.re + v1.c33.re * v2.c33.re  \
                  -(v1.c31.im * v2.c13.im + v1.c32.im * v2.c23.im + v1.c33.im * v2.c33.im);

    // Imaginary part
    result.c11.im = v1.c11.re * v2.c11.im + v1.c12.re * v2.c21.im + v1.c13.re * v2.c31.im  \
                  +(v1.c11.im * v2.c11.re + v1.c12.im * v2.c21.re + v1.c13.im * v2.c31.re);

    result.c12.im = v1.c11.re * v2.c12.im + v1.c12.re * v2.c22.im + v1.c13.re * v2.c32.im  \
                  +(v1.c11.im * v2.c12.re + v1.c12.im * v2.c22.re + v1.c13.im * v2.c32.re);

    result.c13.im = v1.c11.re * v2.c13.im + v1.c12.re * v2.c23.im + v1.c13.re * v2.c33.im  \
                  +(v1.c11.im * v2.c13.re + v1.c12.im * v2.c23.re + v1.c13.im * v2.c33.re);

    result.c21.im = v1.c21.re * v2.c11.im + v1.c22.re * v2.c21.im + v1.c23.re * v2.c31.im  \
                  +(v1.c21.im * v2.c11.re + v1.c22.im * v2.c21.re + v1.c23.im * v2.c31.re);

    result.c22.im = v1.c21.re * v2.c12.im + v1.c22.re * v2.c22.im + v1.c23.re * v2.c32.im  \
                  +(v1.c21.im * v2.c12.re + v1.c22.im * v2.c22.re + v1.c23.im * v2.c32.re);

    result.c23.im = v1.c21.re * v2.c13.im + v1.c22.re * v2.c23.im + v1.c23.re * v2.c33.im  \
                  +(v1.c21.im * v2.c13.re + v1.c22.im * v2.c23.re + v1.c23.im * v2.c33.re);

    result.c31.im = v1.c31.re * v2.c11.im + v1.c32.re * v2.c21.im + v1.c33.re * v2.c31.im  \
                  +(v1.c31.im * v2.c11.re + v1.c32.im * v2.c21.re + v1.c33.im * v2.c31.re);

    result.c32.im = v1.c31.re * v2.c12.im + v1.c32.re * v2.c22.im + v1.c33.re * v2.c32.im  \
                  +(v1.c31.im * v2.c12.re + v1.c32.im * v2.c22.re + v1.c33.im * v2.c32.re);

    result.c33.im = v1.c31.re * v2.c13.im + v1.c32.re * v2.c23.im + v1.c33.re * v2.c33.im  \
                  +(v1.c31.im * v2.c13.re + v1.c32.im * v2.c23.re + v1.c33.im * v2.c33.re);

    return result;
}


template<typename T>
SU3<T> multiply_4_SU3(const SU3<T>& v1, const SU3<T>& v2, const SU3<T>& v3, const SU3<T>& v4) {
    SU3<T> result;
    // TODO:
    // This could be optimized with a solution like in Google's Eigen::Tensor, where computations are
    // actually performed only when result is accessed. Otherwise, maybe std::span can do something
    // similar in a standard way, and execution policies for parallel v1 * v2, and v3 * v4, then tmp1
    // and tpm2.
    result = multiply_SU3(multiply_SU3(multiply_SU3(v1, v2), v3), v4);
}


template<typename T>
Complex<T> trace_su3(const SU3<T>& v1) {
    Complex<T> result;
    result.re = v1.c11.re + v1.c22.re + v1.c33.re;
    result.im = v1.c11.im + v1.c22.im + v1.c33.im;
    return result;
}


// Instantiate the template for float and double
template struct Complex<float>;
template struct Complex<double>;
template struct SU3<float>;
template struct SU3<double>;


#endif // SU3_H
