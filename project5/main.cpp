#include <iostream>
#include <type_traits>

template<unsigned...> class Cont{};

template<typename T>
struct  FirstBit;

template<unsigned T, unsigned... Rem>
struct FirstBit<Cont<T, Rem...>>
{
    constexpr static unsigned bit = T;
    using rem = Cont<Rem...>;
};
template<>
struct FirstBit<Cont<>>
{
    constexpr static unsigned bit = 0;
    using rem = Cont<>;
};

template<typename T>
struct PrintCont;

template<unsigned... vals>
struct PrintCont<Cont<vals...>>
{
    // get first bit and iterate print
    using fbi = FirstBit<Cont<vals...>>;
    static void print(){
        if constexpr (fbi::bit >= 10){
            std::cout << char('a' + fbi::bit - 10) ;
        }else{
            std::cout << fbi::bit;
        }
        PrintCont<typename fbi::rem>::print();
    }
};
template<>
struct PrintCont<Cont<>>
{
    static void print(){
        std::cout << std::endl;
    }
};

// 打印
// template<typename T>
// struct PrintCont_;

// template<unsigned T, unsigned... Rem>
// struct PrintCont_<Cont<T, Rem...>>
// {
//     constexpr static unsigned nowbit = T;
//     static void print(){
//         std::cout << T;
//         PrintCont_<Cont<Rem...>>::print();
//     }
// };
// template<>
// struct PrintCont_<Cont<>>
// {
//     static void print(){
//         std::cout << std::endl;
//     }
// };

// 别名模板打印
template<typename T>
void print(){
    PrintCont<T>::print();
}
template<>
void print<Cont<>>(){
    std::cout << 0 << std::endl;
}
// 利用递归的方式进行循环代码的编写从而实现逆置函数的实现,利用特化完成分支语句
template<typename T, typename Res>
struct InvertCont;

template<unsigned... vals, unsigned... Res>
struct InvertCont<Cont<vals...>, Cont<Res...>>
{
    using fbi = FirstBit<Cont<vals...>>;
    using type = typename InvertCont<typename fbi::rem, Cont<fbi::bit, Res...>>::type;
};
// 待处理数据空时，利用特化直接返回处理结果
template<unsigned... Res>
struct InvertCont<Cont<>, Cont<Res...>>
{
    using type = Cont<Res...>;
};
// 利用别名模板来简化书写
template<typename T>
struct invert
{
    using value = typename InvertCont<T, Cont<>>::type;
};

// 接收四个参数，两个待处理的数组，一个结果，一个进位，也可以把进位加入到Res第一位里面进行处理，为了更加清晰易懂把进位写到模板参数里面
template<typename T1, typename T2, typename Res, unsigned carry>
struct Sum;

template<unsigned... T1, unsigned... T2, unsigned... Res, unsigned carry>
struct Sum<Cont<T1...>, Cont<T2...>, Cont<Res...>, carry>
{
    using ffbi = FirstBit<Cont<T1...>>;
    using sfbi = FirstBit<Cont<T2...>>;
    constexpr static unsigned nowbit = ffbi::bit + sfbi::bit + carry;
    // 结果不需要在进行转置
    // using type = typename Sum<typename ffbi::rem, typename sfbi::rem, Cont<Res..., nowbit % 10>, nowbit / 10>::type;
    using type = typename Sum<typename ffbi::rem, typename sfbi::rem, Cont<nowbit % 10, Res...>, nowbit / 10>::type;
};

template<unsigned... Res, unsigned carry>
struct Sum<Cont<>, Cont<>, Cont<Res...>, carry>
{
    // using type = typename std::conditional<(carry >0), Cont<Res..., carry>, Cont<Res...>>::type;
    // 利用conditional来完成类似三元运算符数值的分支操作,并减少实例化
    // using type = typename std::conditional_t<(carry >0), Cont<Res..., carry>, Cont<Res...>>;
    using type = typename std::conditional_t<(carry >0), Cont<carry, Res...>, Cont<Res...>>;
};

// 别名模板
template<typename T1, typename T2>
struct Add
{
    // using value = typename invert<typename Sum<typename invert<T1>::value, typename invert<T2>::value, Cont<>, 0>::type>::value;
    using value = typename Sum<typename invert<T1>::value, typename invert<T2>::value, Cont<>, 0>::type;
};

// 合并两个长整数数组
template <typename T1, typename T2>
struct Merge;

template <unsigned... R1, unsigned... R2>
struct Merge<Cont<R1...>, Cont<R2...>>
{
    using Res = Cont<R1..., R2...>;
};

// 长整数取余
template <typename T, unsigned BaseM, unsigned BaseN, unsigned remain>
struct Mod;

template <unsigned BaseM, unsigned BaseN, unsigned remain>
struct Mod<Cont<>, BaseM, BaseN, remain>
{
public:
    const static unsigned Remain = remain;
    using Res = Cont<>;
};

template <unsigned U, unsigned... N, unsigned BaseM, unsigned BaseN, unsigned remain>
struct Mod<Cont<U, N...>, BaseM, BaseN, remain>
{
public:
    const static unsigned tmp = U + remain * BaseM;
    const static unsigned Remain = Mod<Cont<N...>, BaseM, BaseN, tmp % BaseN>::Remain;
    using Res = typename Merge<Cont<tmp / BaseN>, typename Mod<Cont<N...>, BaseM, BaseN, tmp % BaseN>::Res>::Res;
};

// using res =  Mod<Cont<1, 2>, 10, 5, 0>::Res;

//长整数进制转换，利用除N取余法 
template <typename T1, unsigned BaseM, unsigned BaseN>
struct M2N;

template <unsigned BaseM, unsigned BaseN>
struct M2N<Cont<>, BaseM, BaseN>
{
    using Res = Cont<>;
};

template <unsigned BaseM, unsigned BaseN>
struct M2N<Cont<0>, BaseM, BaseN>
{
    using Res = Cont<>;
};

template <unsigned U, unsigned... N, unsigned BaseM, unsigned BaseN>
struct M2N<Cont<0, U, N...>, BaseM, BaseN>
{
    const static unsigned Out = Mod<Cont<U, N...>, BaseM, BaseN, 0>::Remain;
    using Res = typename Merge<typename M2N<typename Mod<Cont<U, N...>, BaseM, BaseN, 0>::Res, BaseM, BaseN>::Res, Cont<Out>>::Res;
};

template <unsigned U, unsigned... N, unsigned BaseM, unsigned BaseN>
struct M2N<Cont<U, N...>, BaseM, BaseN>
{
    const static unsigned Out = Mod<Cont<U, N...>, BaseM, BaseN, 0>::Remain;
    using Res = typename Merge<typename M2N<typename Mod<Cont<U, N...>, BaseM, BaseN, 0>::Res, BaseM, BaseN>::Res, Cont<Out>>::Res;
};
// 删除0 
template<typename T>
struct EraseZero;

template<unsigned T, unsigned ...processed>
struct EraseZero<Cont<T, processed...>>
{
    using value = Cont<T, processed...>;
};

template<unsigned ...processed>
struct EraseZero<Cont<0, processed...>>
{
    using value = typename EraseZero<Cont<processed...>>::value;
};
template<>
struct EraseZero<Cont<>>
{
    using value = Cont<0>;
};


int main() {
    using a1 = Cont<1,9,9>;
    using a2 = Cont<1>;
    std::cout<< "first num:";
    print<a1>();
    std::cout << "after invert:";
    print<invert<a1>::value>();
    std::cout << "second num:";
    print<a2>();
    std::cout << "after invert:";
    print<invert<a2>::value>();
    using res = Add<a1, a2>::value;
    std::cout << "sum: ";
    print<res>();
    // 测试进制转换
    std::cout << "10 to 16:";
    using ResM2N = EraseZero<M2N<res, 10, 16>::Res>::value;
    print<ResM2N>();
    using res2 = EraseZero<M2N<res, 10, 2>::Res>::value;
    std::cout << "10 to 2:";
    print<res2>();
}
