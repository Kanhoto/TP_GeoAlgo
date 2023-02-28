#ifndef SHAREDTYPE_HPP
#define SHAREDTYPE_HPP

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

struct Color_t{
	double red=0;
	double green=0;
	double blue=0;
};

#endif