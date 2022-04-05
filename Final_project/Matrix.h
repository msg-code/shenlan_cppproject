#ifndef MATRIX_H
#define MATRIX_H
#include<iostream>
#include<vector>
#include<type_traits>

namespace Eigen{

enum ConcatenateType{
    ROW = 1,
    COL = 2
};
// 动态存储
template<typename T>
struct MatrixDynamicData
{
    size_t row_ ;
    size_t col_ ;
    std::vector<T> elements_;
    MatrixDynamicData(){
        col_ = 1;
        row_ = 1;
        elements_.push_back(0);
    }
    MatrixDynamicData(size_t T_row, size_t T_col){
        row_ = T_row;
        col_ = T_col;
        for(size_t i = 0;i < T_col * T_row; ++i){
            elements_.push_back(0);
        }
        
    }
    MatrixDynamicData(std::initializer_list<T> l): elements_(l){
        row_ = 1;
        col_ = elements_.size();
    }
    typename std::vector<T>::iterator operator[](std::size_t idx){
        return elements_.begin() + (idx * col_);
    }
    auto& at(size_t idx){
        try 
        {
            return elements_.at(idx);
            // return *(elements_.begin() + idx);
        }
        catch(const std::exception& e)
        {
            std::cout << "访问过界" << std::endl; 
            std::cerr << e.what() << '\n';
        }
        // return elements_.at(idx);
    }
    void push_back(T t){
        elements_.push_back(t);
    }
    void reshape(size_t row, size_t col){
        size_t push_t = row*col - elements_.size();
        if(push_t < 0){
            for(size_t i = 0; i< -push_t; ++i){
                elements_.pop_back();
            }
        }else{
            for(size_t i = 0; i< push_t; ++i){
                elements_.push_back(0);
            }
        }
        col_ = col;
        row_ = row;
    }
    // auto operator+(MatrixDynamicData<T>& rhs){
    //     MatrixDynamicData<T> res(row_, col_);
    //     auto size = row_ * col_;
    //     for(size_t i = 0; i < size; ++i){
    //         res.at(i) = elements_.at(i) + rhs.at(i);
    //     }
    //     return res;
    // }

    // auto concatenate(MatrixDynamicData<T>& m1, MatrixDynamicData<T>& m2, enum type){
        
    //     MatrixDynamicData<T> res(m1.row_, m1.col_+ m2.col_);

    // }
    inline auto get_row(){
        return row_;
    }
    inline auto get_col(){
        return col_;
    }
};

// 静态存储    
template<typename T, size_t T_row, size_t T_col>
struct MatrixStaticData
{
    static constexpr size_t row_ = T_row;
    static constexpr size_t col_ = T_col;
    std::vector<T> elements_;
    MatrixStaticData(){
        for(size_t i =0;i < row_ * col_; ++i){
            elements_.push_back(0);
        }
    }
    MatrixStaticData(std::initializer_list<T> l): elements_(l){
        size_t l_size = l.size();
        if (row_* col_ > l_size){
            for(size_t i = 0; i< (row_ * col_ - l_size); ++i){
                elements_.push_back(0);
            }
        }else{

        }
    }
    typename std::vector<T>::iterator operator[](std::size_t idx){
        return elements_.begin() + (idx * col_);
    }
    auto& at(size_t idx){
        try 
        {
            return elements_.at(idx);
            // return *(elements_.begin() + idx);
        }
        catch(const std::exception& e)
        {
            std::cout << "访问过界" << std::endl; 
            std::cerr << e.what() << '\n';
        }
    }
    template<size_t T1, size_t T2>
    auto reshape(){
        MatrixStaticData<T, T1, T2> res; 
        std::cout << row_ << " " << col_ <<std::endl;
        if(row_ * col_ < T1 * T2){
            for(size_t i = 0; i< row_ * col_; ++i){
                res.elements_.at(i) = elements_.at(i);
            }
            for(size_t i = row_ * col_; i < T1*T2; ++i){
                res.elements_.at(i) = 0;
            }
        }else{
            for(size_t i = 0; i< T1 * T2; ++i){
                res.elements_.at(i) = elements_.at(i);
            }
        }
        return res;
    }
    // 拓展二单独测试没问题
    // template <size_t T1, size_t T2>
    // auto operator*(MatrixStaticData<T, T1, T2>& rhs){
    //     if(col_ != T1){
    //         std::cout << "不满足乘法规则" << std::endl; 
    //     }
    //     MatrixStaticData<T, row_, T2> res;
    //     for(size_t i = 0; i < row_; ++i){
    //         for(size_t j = 0; j < rhs.col_; ++j){
    //             for(size_t r = 0; r< col_;++r){
    //                 res[i][j] += this->at(i*col_+r) * rhs.at(r*rhs.col_ +j);
    //             }
    //         }
    //     }
    //     return res;
    // }
    inline auto get_row(){
        return row_;
    }
    inline auto get_col(){
        return col_;
    }
};
    
//  // 2.模板继承 模板类继承模板参数给出的基类 第一个参数是类名称，第二个是类型
template<class T, typename Tt>
struct MatrixBase : public T
{
    MatrixBase() : T(){

    }
    MatrixBase(size_t row, size_t col) : T(row,col){
    }
    MatrixBase(std::initializer_list<Tt> l) : T(l){
    }
    template<class T1, class T2>
    void add(const T1& rhs, T2& res){
        for(size_t i =0; i < T::row_ * T::col_; ++i){
            res.elements_[i] = T::elements_[i] + rhs.elements_[i];
        }
    }
    template<class T1, class T2>
    void sub(const T1& rhs, T2& res){
        for(size_t i = 0; i < T::row_ * T::col_; ++i){
            res.elements_[i] = T::elements_[i] - rhs.elements_[i];
        }
    }
    template<class T1, class T2>
    void multi(T1& rhs, T2& res){
        for(size_t i = 0; i < T::row_; ++i){
            for(size_t j = 0; j < rhs.col_; ++j){
                for(size_t r = 0; r< T::col_;++r){
                    res[i][j] += T::at(i* T::col_+r) * rhs.at(r*rhs.col_ +j);
                }
            }
        }
    }

};
template<typename T, size_t... sizes> struct Matrix;

template<typename T>
struct Matrix<T> 
    : public MatrixBase<MatrixDynamicData<T>, T>{
    Matrix() : MatrixBase<MatrixDynamicData<T>, T>(){

    }
    Matrix(size_t row, size_t col) : MatrixBase<MatrixDynamicData<T>, T>(row,col){
    }
    Matrix(std::initializer_list<T> l) : MatrixBase<MatrixDynamicData<T>, T>(l){
    }
    Matrix operator+(const Matrix &rhs){
        Matrix res(this->get_row(), this->get_col());
        this->add(rhs, res);
        return res;
    }
    Matrix operator-(const Matrix &rhs){
        Matrix res(this->get_row(), this->get_col());
        this->sub(rhs, res);
        return res;
    }
    Matrix operator*(Matrix &rhs){
        if(this->get_col()!= rhs.row_){
            std::cout<< "Matrix size no mathing~!" << std::endl;
        }else{
            Matrix res(this->get_row(), rhs.col_);
            this->multi(rhs, res);
            return res;
        }
    }
    
};

template<typename T, size_t T_row, size_t T_col>
struct Matrix<T, T_row, T_col>
    : public MatrixBase<MatrixStaticData<T, T_row, T_col>, T>
{
    Matrix() : MatrixBase<MatrixStaticData<T, T_row, T_col>, T>(){}
    Matrix(std::initializer_list<T> l) : MatrixBase<MatrixStaticData<T, T_row, T_col>, T>(l){
    }
    Matrix operator+(const Matrix &rhs){
        Matrix res;
        this->add(rhs, res);
        return res;
    }
    Matrix operator-(const Matrix &rhs){
        Matrix res;
        this->sub(rhs, res);
        return res;
    }
    // 静态类型乘法报错，报错原因没看懂
    Matrix operator*(const Matrix &rhs){
        if(this->get_col()!= rhs.row_){
            std::cout<< "Matrix size no mathing~!" << std::endl;
        }else{
            constexpr size_t r = this->row_;
            constexpr size_t c = rhs.col_;
            Matrix<T, r, c> res;
            this->multi(rhs, res);
            return res;
        }
    }
};

// template<typename T> concept Addable = requires(T a, T b) {a + b;};

// friend auto operator +(const Matrix<T> &lm, const Matrix<T> &rm){
//     static_assert(Addable<T>, "is not add able");
// }

  
template<typename T>   
auto concatenate(Matrix<T> &m1, Matrix<T> &m2, enum ConcatenateType type){
    Matrix<T> res;
        switch (type)
        {
        case ROW:
            res.reshape(m1.get_row(), m1.get_col() + m2.get_col());
            for(size_t i =0;i<m1.row_;++i){
                for(size_t j =0; j<m1.col_;++j){
                    res[i][j] = m1[i][j];
                }
                for(size_t j = m1.col_;j<m1.col_ + m2.col_;++j){
                    res[i][j] = m2[i][j-m1.col_];
                }
            }
            break;
        case COL:
            res.reshape(m1.get_row() + m2.get_row(), m1.get_col());
            for(size_t i =0;i<m1.row_;++i){
                for(size_t j =0; j<m1.col_;++j){
                    res[i][j] = m1[i][j];
                }
            }
            for(size_t i = m1.row_;i<m1.row_ + m2.row_; i++){
                for(size_t j =0; j<m1.col_;++j){
                    res[i][j] = m2[i-m1.row_][j];
                }
            }
            break;
        default:
            break;
        }
        return res;

    }

template<enum ConcatenateType type,typename T,size_t T_row1,size_t T_col1,size_t T_row2,size_t T_col2>   
auto concatenate(Matrix<T, T_row1,T_col1> &m1, Matrix<T, T_row2,T_col2> &m2){
    if constexpr (type == ROW){
        constexpr size_t r = T_row1;
        constexpr size_t c = T_col2 + T_col1;
        Matrix<T, r, c> res;
        for(size_t i =0;i<m1.row_;++i){
            for(size_t j =0; j<m1.col_;++j){
                res[i][j] = m1[i][j];
            }
            for(size_t j = m1.col_;j<m1.col_ + m2.col_;++j){
                res[i][j] = m2[i][j-m1.col_];
            }
        }
        return res;
    }else{
        constexpr size_t r = T_row1 + T_row2;
        constexpr size_t c = T_col1;
        Matrix<T, r, c> res;
        for(size_t i =0;i<m1.row_;++i){
            for(size_t j =0; j<m1.col_;++j){
                res[i][j] = m1[i][j];
            }
        }
        for(size_t i = m1.row_;i<m1.row_ + m2.row_; i++){
            for(size_t j =0; j<m1.col_;++j){
                res[i][j] = m2[i-m1.row_][j];
            }
        }
        return res;
    }
}
}
#endif
