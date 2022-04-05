#include<iostream>
#include<type_traits>
#include<assert.h>
#include"Matrix.h"
using namespace Eigen;
int main(){
    // 测试模板继承
    // Matrix<int> m1;
    // Matrix<int> m2{1,2,4};
    // Matrix<int> m3(2,2);

    // 基本功能测试
    // MatrixDynamicData<int> m3;
    // MatrixDynamicData<int> m4(2,2);
    Matrix<int> m3;
    Matrix<int> m4(2,2);
    std::cout<< m4.row_ << " " << m4.col_ << " "<<std::endl;
    m4[1][0] = 42;
    assert(m4.at(2) == 42);
    // m4.at(5);
    m4.at(1) = 1;
    std::cout<< m4.at(1)<< std::endl;
    m4.push_back(13);
    m4.push_back(14);
    assert(m4.at(4) == 13);
    assert(m4.at(5) == 14);
    m4.reshape(3,3);
    std::cout<< m4[0][2] << " " << m4[2][2] <<std::endl;
    // 测试加法、减法、乘法
    // MatrixDynamicData<int> mat3{1,2,3,4};
    // MatrixDynamicData<int> mat4{5,6,7,8};
    Matrix<int> mat3{1,2,3,4};
    Matrix<int> mat4{5,6,7,8};    
    mat3.reshape(2,3);
    mat4.reshape(2,3);
    std::cout << "Mat3:" << std::endl;
    std::cout<< mat3[0][0] << " " << mat3[0][1] << " " <<mat3[0][2] <<std::endl; 
    std::cout<< mat3[1][0] << " " << mat3[1][1] << " " <<mat3[1][2] <<std::endl;
    std::cout << "Mat4:" << std::endl;
    std::cout<< mat4[0][0] << " " << mat4[0][1] << " " <<mat4[0][2] <<std::endl; 
    std::cout<< mat4[1][0] << " " << mat4[1][1] << " " <<mat4[1][2] <<std::endl;
    auto res = mat3 + mat4;
    std::cout << "Mat3 + Mat4 :" << std::endl;
    std::cout<< res[0][0] << " " << res[0][1] << " " <<res[0][2] <<std::endl; 
    std::cout<< res[1][0] << " " << res[1][1] << " " <<res[1][2] <<std::endl;

    auto res2 = mat3 - mat4;
    std::cout << "Mat3 - Mat4 :" << std::endl;
    std::cout<< res2[0][0] << " " << res2[0][1] << " " <<res2[0][2] <<std::endl; 
    std::cout<< res2[1][0] << " " << res2[1][1] << " " <<res2[1][2] <<std::endl;
    mat3.reshape(3,3);
    mat4.reshape(3,3);
    std::cout << "reshape Mat3:" << std::endl;
    std::cout<< mat3[0][0] << " " << mat3[0][1] << " " <<mat3[0][2] <<std::endl; 
    std::cout<< mat3[1][0] << " " << mat3[1][1] << " " <<mat3[1][2] <<std::endl;
    std::cout<< mat3[2][0] << " " << mat3[2][1] << " " <<mat3[2][2] <<std::endl;
    std::cout << "reshape Mat4:" << std::endl;
    std::cout<< mat4[0][0] << " " << mat4[0][1] << " " <<mat4[0][2] <<std::endl; 
    std::cout<< mat4[1][0] << " " << mat4[1][1] << " " <<mat4[1][2] <<std::endl;
    std::cout<< mat4[2][0] << " " << mat4[2][1] << " " <<mat4[2][2] <<std::endl;
    auto res3 = mat3 * mat4;
    std::cout << "Mat3 * Mat4 :" << std::endl;
    std::cout<< res3[0][0] << " " << res3[0][1] << " " <<res3[0][2] <<std::endl; 
    std::cout<< res3[1][0] << " " << res3[1][1] << " " <<res3[1][2] <<std::endl;
    std::cout<< res3[2][0] << " " << res3[2][1] << " " <<res3[2][2] <<std::endl;
    std::cout << "  " << std::endl;
    // 测试静态数据
    // MatrixStaticData<int,2,3> mat1{1,2,3,4,5,6};
    // MatrixStaticData<int,3,2> mat2{1,0,0,1};
    Matrix<int, 2 , 3> mat1{1,2,3,4,5,6};
    Matrix<int, 3, 2> mat2{1,0,0,1};
    std::cout << "mat1:" << std::endl;
    std::cout<< mat1[0][0] << " " << mat1[0][1] << " " <<mat1[0][2] <<std::endl; 
    std::cout<< mat1[1][0] << " " << mat1[1][1] << " " <<mat1[1][2] <<std::endl;
    std::cout << "mat2:" << std::endl;
    std::cout<< mat2[0][0] << " " << mat2[0][1] <<std::endl; 
    std::cout<< mat2[1][0] << " " << mat2[1][1] <<std::endl;
    std::cout<< mat2[2][0] << " " << mat2[2][1] <<std::endl;
    auto res4 = mat1.reshape<3, 3>();
    std::cout<< "reshape mat1:"<< std::endl;
    std::cout<< res4[0][0] << " " << res4[0][1] << " " <<res4[0][2] <<std::endl; 
    std::cout<< res4[1][0] << " " << res4[1][1] << " " <<res4[1][2] <<std::endl;
    std::cout<< res4[2][0] << " " << res4[2][1] << " " <<res4[2][2] <<std::endl;
    Matrix<int, 3, 3> mat5{1,2,3,4,5,6};
    Matrix<int, 3, 3> mat6{1,0,0,1,1};
    auto res5 = mat5 + mat6;
    std::cout<< "res5:"<< std::endl;
    std::cout<< res5[0][0] << " " << res5[0][1] << " " <<res5[0][2] <<std::endl; 
    std::cout<< res5[1][0] << " " << res5[1][1] << " " <<res5[1][2] <<std::endl;
    std::cout<< res5[2][0] << " " << res5[2][1] << " " <<res5[2][2] <<std::endl;
    auto res6 = mat5 - mat6;
    // 静态乘法报错
    // auto res7 = mat5 * mat6;
    // 拓展二单独作为成员函数乘法测试没问题
    // MatrixStaticData<int, 2, 2> res = mat1 * mat2;
    // std::cout<< res.row_ << " " << res.col_ << std::endl;
    // std::cout<< res[0][0] << " " << res[0][1] <<std::endl; 
    // std::cout<< res[1][0] << " " << res[1][1] <<std::endl;
    // 拓展三
    Matrix<int> mat7{1,2,3,4};
    Matrix<int> mat8{1,1,1,1};
    mat7.reshape(2,2);
    mat8.reshape(2,2);
    Matrix<int> res7 = concatenate(mat7, mat8, ROW);
    std::cout<< res7.elements_.size() << std::endl;
    std::cout<< res7.row_ << " " << res7.col_<< std::endl;
    std::cout<< "concatenate res7:"<< std::endl;
    std::cout<< res7[0][0] << " " << res7[0][1] << " " <<res7[0][2] << " " << res7[0][3]<<std::endl; 
    std::cout<< res7[1][0] << " " << res7[1][1] << " " <<res7[1][2] <<" " << res7[1][3]<<std::endl;
    Matrix<int, 2, 2> mat9{1,2,3,4};
    Matrix<int, 2, 2> mat10{1,1,1,1};
    Matrix<int, 2, 4> res8 = concatenate<ROW>(mat9,mat10);
     std::cout<< "concatenate res8:"<< std::endl;
    std::cout<< res8[0][0] << " " << res8[0][1] << " " <<res8[0][2] << " " << res7[0][3]<<std::endl; 
    std::cout<< res8[1][0] << " " << res8[1][1] << " " <<res8[1][2] <<" " << res7[1][3]<<std::endl;

    return 0;
}