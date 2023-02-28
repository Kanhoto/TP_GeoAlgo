#include "sharedType.hpp"

int CC_counter = 0;
int cpt = 0;

void segCC(Polyhedron & mesh, Facet_int_map::iterator & it_face, std::vector<bool> & visited){
    if(!visited[cpt]){
        ++CC_counter;
        it_face->second = CC_counter;
        segCC(mesh, ++it_face, visited);
    }
}

Facet_int_map segmentationParCC(Polyhedron & mesh,Facet_int_map & faceMap){
    std::vector<bool> visitedFaces;
    for(auto it = faceMap.begin(); it!= faceMap.end(); ++it){
        visitedFaces.push_back(false);
    }

    auto it = faceMap.begin();
    segCC(mesh, it, visitedFaces);
}
