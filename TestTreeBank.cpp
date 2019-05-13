//
// Created by Olcay Taner Yıldız on 2019-04-25.
//

#include <iostream>
#include "TreeBank.h"

int main(){
    TreeBank treeBank = TreeBank("../../../Penn-Treebank/English", "fileList.txt");
    cout << treeBank.size();
}