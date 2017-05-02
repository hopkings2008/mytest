#include <png.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <coder.h>

int main(int argc, const char *argv[]){
    int ret = 0;
    std::string msg = "https://stage-res.shiqichuban.com/v1/image/get/7XREUL5TGgTcc_MvHVSAer9SlD7yZwSCuaBValMuOUQruIf3rwkGq0J4RTVcMcFZAt1mopDae8s5jPaWxcpM2Q";


    shiqi::cis::Coder coder;
    std::vector<unsigned char> out;
    coder.create((const unsigned char*)msg.c_str(), msg.length(), out);
    std::ofstream outfile ("out.png",std::ofstream::binary);
    outfile.write((const char *)out.data(), out.size());
    outfile.close();
    return ret;
}


