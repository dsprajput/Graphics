#include "MtlParser.h"

MtlParser::MtlParser(std::string file, std::string mtl){
    using namespace std;

    mtlName = mtl;
    ifstream infile;
    infile.open(file.c_str());
    // cout << file << endl;
    if(!infile.good()){
        throw invalid_argument("Failed to open MTL file.");
    }

    string line;
    while(getline(infile, line)){
        if(line == "newmtl " + mtlName){
            cout << line << endl;
            while(getline(infile, line)){
                if(line[0]=='#'){
                    continue;
                }
                if(line.substr(0,3) == "Ka "){
                    float x, y, z;
                    istringstream vs(line.substr(3));
                    vs>>x, vs>>y, vs>>z;
                    // cout << x << endl;
                    // cout << y << endl;
                    // cout << z << endl;
                    mat_amb[0]=x;
                    mat_amb[1]=y;
                    mat_amb[2]=z;
                    mat_amb[3]=1.0f;
                }else if(line.substr(0,3) == "Kd "){
                    float x, y, z;
                    istringstream vs(line.substr(3));
                    vs>>x, vs>>y, vs>>z;
                    // cout << x << endl;
                    // cout << y << endl;
                    // cout << z << endl;
                    mat_dif[0]=x;
                    mat_dif[1]=y;
                    mat_dif[2]=z;
                    mat_dif[3]=1.0f;
                }else if(line.substr(0,3) == "Ks "){
                    float x, y, z;
                    istringstream vs(line.substr(3));
                    vs>>x, vs>>y, vs>>z;
                    // cout << x << endl;
                    // cout << y << endl;
                    // cout << z << endl;
                    mat_spe[0]=x;
                    mat_spe[1]=y;
                    mat_spe[2]=z;
                    mat_spe[3]=1.0f;
                }else if(line.substr(0,3) == "Ns "){
                    shin[0] = stof(line.substr(3));
                    break;
                }
            }
        }
    }

    // for(int i=0; i<4; i++){
    //     std::cout << mat_amb[i];
    // }
    // std::cout<<std::endl;
    // for(int i=0; i<4; i++){
    //     std::cout << mat_dif[i];
    // }
    // std::cout<<std::endl;
    // for(int i=0; i<4; i++){
    //     std::cout << mat_spe[i];
    // }
    // std::cout<<std::endl;
    // std::cout<<shin[0]<<std::endl;
}

void MtlParser::applyMaterial(){

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spe);
    glMaterialfv(GL_FRONT, GL_SHININESS, shin);
}