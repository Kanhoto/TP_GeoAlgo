#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/boost/graph/graph_traits_Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_3.h>

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <numeric>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;

typedef Polyhedron::Facet_const_iterator Facet_iterator;
typedef Polyhedron::Vertex_const_iterator Vertex_iterator;
typedef Polyhedron::Halfedge_const_iterator Halfedge_iterator;
typedef Polyhedron::Halfedge_around_facet_const_circulator Halfedge_facet_circulator;
typedef Kernel::Point_3 Point_3;

typedef std::map<Polyhedron::Facet_const_handle, double> Facet_double_map;
typedef std::map<Polyhedron::Facet_const_handle, int> Facet_int_map;


unsigned int vertsCount(Polyhedron & poly_i){
	unsigned int nbVerts = 0;
	for (Vertex_iterator i = poly_i.vertices_begin(); i != poly_i.vertices_end(); ++i) {
		++nbVerts;
	}
	std::cout << "Nombre de sommets: " << nbVerts << std::endl;

	return nbVerts;
}

unsigned int edgesCount(Polyhedron & poly_i){
	unsigned int nbEdges = 0;
	for (Halfedge_iterator i = poly_i.halfedges_begin(); i != poly_i.halfedges_end(); ++i) {
		++nbEdges;
	}
	nbEdges /= 2;
	std::cout << "Nombre d'arêtes: " << nbEdges << std::endl;

	return nbEdges;
}

unsigned int facesCount(Polyhedron & poly_i){
	unsigned int nbFaces = 0;
	for (Facet_iterator i = poly_i.facets_begin(); i != poly_i.facets_end(); ++i) {
		++nbFaces;
	}
	std::cout << "Nombre de faces: " << nbFaces << std::endl;

	return nbFaces;
}

void meshPerimeter(Polyhedron & poly_i){
	// Write polyhedron in Object File Format (OFF).
    CGAL::set_ascii_mode( std::cout);
    std::cout << "OFF" << std::endl << poly_i.size_of_vertices() << ' '
              << poly_i.size_of_facets() << " 0" << std::endl;
    std::copy( poly_i.points_begin(), poly_i.points_end(),
               std::ostream_iterator<Point_3>( std::cout, "\n"));
    for (  Facet_iterator i = poly_i.facets_begin(); i != poly_i.facets_end(); ++i) {
		float perimeter = 0;
		Halfedge_facet_circulator prev = i->facet_begin();
        Halfedge_facet_circulator curr = ++(i->facet_begin());
        // Facets in polyhedral surfaces are at least triangles.
        std::cout << CGAL::circulator_size(prev) << ' ';
        do {
            perimeter += CGAL::squared_distance(prev->vertex()->point(), curr->vertex()->point());
			++prev;
			++curr;
        } while ( prev != i->facet_begin());
        std::cout << perimeter << std::endl;
    }
}

/*
int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cerr << "Il manque un paramètre au programme. Veuillez lui donner en entrée un nom de fichier au format off." << std::endl;
		return 1;
	}
	
	Polyhedron mesh;
  	std::ifstream input(argv[1]);
	if (!input || !(input >> mesh) || mesh.is_empty()) {
    	std::cerr << "Le fichier donné n'est pas un fichier off valide." << std::endl;
    	return 1;
  	}
  
  	unsigned int nbVerts = vertsCount(mesh);
	unsigned int nbEdges = edgesCount(mesh);
	unsigned int nbFaces = facesCount(mesh);

	meshPerimeter(mesh);
	
	unsigned int euler = nbVerts - nbEdges + nbFaces;
	unsigned int genus = (2 - euler) / 2;
	std::cout << "En supposant que le maillage contienne une unique surface sans bord, alors son genre est de " << genus << std::endl;
  
  
	return 0;
}
*/