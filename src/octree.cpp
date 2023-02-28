#include "sharedType.hpp"

typedef Polyhedron::Point_3 Point3;

/// @brief Axis-Aligned bounding box
struct AABB
{
	// TODO...
};

struct OctreeNode
{
	// TODO...
};

/// @brief Compute the bounding box of a mesh
/// @param mesh the mesh of interest
/// @return its bounding box
AABB computeBB(const Polyhedron &mesh)
{
	// TODO...
	return AABB{};
}

/// @brief add a level to the given parent Octree node, by creating 8 children with 8 bounding box,
/// sliced in the middle of the parent node
/// @param node the octree node to which 8 children will be added
void addOctreeLevel(OctreeNode &node)
{
	// TODO...
}

constexpr int MAX_POINT = 35; // for testing purposes, 
constexpr int MAX_DEPTH = 10; // it would be much better if these values were given to the function where the tree is being constructed.

/// @brief add one vertex to an octree, by following strictly the rules of maximum amount of point in a node, and maximum depth of the tree
/// @param root the root node of the tree
/// @param vert the vertex that will be added, as a Vertex_handle
void addVertexToOctree(OctreeNode &root, Polyhedron::Vertex_handle &vert)
{
	// TODO, this function can be recursive
}

/// @brief A function to generate an octree of the vertices of a mesh,
/// Each vertex will be stored in a node of the octree.
/// the octree shall follow two rules:
///    1- each node shall only contain MAX_POINT vertices
///    2- the depth of tree shall not exceed MAX_DEPTH
///	Remark: the depth of the root is 0
///	Remark: rule 2 wins over rule 1.
/// i.e. a node may contain more vertices than MAX_POINT if the maximum depth is reached.
/// @param mesh the mesh of interest
/// @return an octree node that is the root of the octree for the given mesh
OctreeNode generateOctree(Polyhedron &mesh/*, max number of point, max depth...*/)
{
	OctreeNode root{};
	// TODO...
	return root;
}

/// @brief find a specific vertex inside an octree (using a dichotomy algorithm)
/// @param vh the vertex handle to look for
/// @return the address of the node (not the prettiest way, feel free to handle it differently)
OctreeNode* findVertexInOctree(OctreeNode& root, Polyhedron::Vertex_const_handle &vh)
{
	// TODO....
	return &root;

}

/// @brief (optional) Utility function that takes an octree and apply a function (or more useful, a lambda !)
/// to each leaf of the Octree (each node containing vertices).
/// Can be useful to avoid declaring a new recursive function each time...
/// @param root the root node of the Octree of interest
/// @param func a lambda supposed to do something on a given Octree node.
void browseNodes(const OctreeNode &root, std::function<void(const OctreeNode&)> func)
{
	// if there are no vertices in the node we do nothing

	// if the nodes contains vertices, then "func" is called on the node

	// go through all the children of the current node and calls browseNodes recursively.
	// browseNodes(/*TODO*/, func);
}

void extractMeshFromOctree(const OctreeNode &root, const Polyhedron& mesh){

	std::vector<Point3> vertices;
	std::vector<std::vector<int>> faces;

	// TODO: fill "vertices" and "faces" by going through the octree

	std::ofstream out("octree_meshres.off");
	out << "OFF" << std::endl;
	out << vertices.size() << " " << faces.size() << " 0" << std::endl;
	for (const auto &v : vertices)
	{
		out << v.x() << " " << v.y() << " " << v.z() << std::endl;
	}
	for (const auto &f : faces)
	{
		out << f.size() << " ";
		for(auto fi : f){
			out << fi << " ";
		}
		out << std::endl;
	}

}
