#include<bits/stdc++.h>
#include <algorithm>
#include<Eigen/Eigen>
using namespace std;
using namespace Eigen;
int main(){
    Eigen::Vector3i bounds;
    Eigen::Vector3i mapSize(50,50,5);
    Eigen::Vector3i step(1, mapSize(0), mapSize(1) * mapSize(0));
    bounds = (mapSize.array() - 1) * step.array();
    cout << bounds;
    return 0;
}
