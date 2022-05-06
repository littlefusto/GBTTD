//
// Created by fusto on 06.05.22.
//

#include "TextureHandler.h"
#include <dirent.h>
#include <Domain.h>

TextureHandler::TextureHandler() {
    DIR *dp;
    int i = 0;
    struct dirent *ep;
    dp = opendir("01_Graphics/tiles/");
    if(dp != NULL){
        while(ep = readdir(dp))
            i++;
        (void) closedir(dp);
    }
    TileTexturePaths.resize(i);
    TileTexturePaths[0] = std::string(textures::tiles + "tile" + ".png");
    TileTexturePaths[1] = std::string(textures::tiles + "tile2" + ".png");

}