#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/boost/graph/graph_traits_Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <iostream>
#include <fstream>
#include <CGAL/IO/Color.h>

#include <vector>
#include <algorithm>
#include <list>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef Polyhedron::Facet_const_iterator Facet_iterator;
typedef Polyhedron::Vertex_const_iterator Vertex_iterator;
typedef Polyhedron::Halfedge_const_iterator Halfedge_iterator;
typedef Polyhedron::Vertex_handle Vertex_handle;

typedef Polyhedron::Point_3 Point3;

constexpr int MAX_POINT = 10; // for testing purposes, 
constexpr int MAX_DEPTH = 20; // it would be much better if these values were given to the function where the tree is being constructed.

struct Point3D{
	double x,y,z;
};

/// @brief Axis-Aligned bounding box
struct AABB
{
	// TODO...
	Point3D minCorner;
	Point3D maxCorner;

	std::list<Point3> Vertices;

	void displaySize(){
		std::cout << "x : max = " << minCorner.x << " minX = " << maxCorner.x << std::endl;
		std::cout << "y : max = " << minCorner.y << " minY = " << maxCorner.y << std::endl;
		std::cout << "z : max = " << minCorner.z << " minZ = " << maxCorner.z << std::endl;
	}
};

struct Adress{
	bool x,y,z;
};

struct OctreeNode
{
	// TODO...
	AABB cube;
	std::vector<OctreeNode*> nodeChilds;
	std::list<Vertex_handle> vertexlist;
	Adress Adr;
	int depth = 0;

	void setAdr(int x, int y, int z){
		Adr.x = x;
		Adr.y = y;
		Adr.z = z;
	}

	OctreeNode* getChild(const int x, const int y, const int z) const{
		return nodeChilds[4*x + 2*y + z];
	}

	void DisplayNodeAdr() const{
		std::cout << Adr.x << Adr.y << Adr.z << std::endl;
	}

	void createChildsAABB(){
		for(auto it=nodeChilds.begin(); it!=nodeChilds.end(); ++it){
			
		}
	}
};

/// @brief Compute the bounding box of a mesh
/// @param mesh the mesh of interest
/// @return its bounding box
AABB computeBB(const Polyhedron &mesh)
{
	// TODO...
	Point3 f = mesh.vertices_begin()->point();
	AABB result {
		.minCorner{
			.x=f.x(),
			.y=f.y(),
			.z=f.z()
		},
		.maxCorner{
			.x=f.x(),
			.y=f.y(),
			.z=f.z()
		}
	};

	for(auto it=mesh.vertices_begin(); it != mesh.vertices_end(); ++it){
		Point3 pt = it->point();
		if(pt.x() < result.minCorner.x){
			result.minCorner.x = pt.x();
		}
		if(pt.x() > result.maxCorner.x){
			result.maxCorner.x = pt.x();
		}

		if(pt.y() < result.minCorner.y){
			result.minCorner.y = pt.y();
		}
		if(pt.y() > result.maxCorner.y){
			result.maxCorner.y = pt.y();
		}

		if(pt.z() < result.minCorner.z){
			result.minCorner.z = pt.z();
		}
		if(pt.z() > result.maxCorner.z){
			result.maxCorner.z = pt.z();
		}
		result.Vertices.push_back(pt);
	}

	return result;
}

void subdivideAABB(OctreeNode &nodeParent, OctreeNode &node){
	double midX = (nodeParent.cube.minCorner.x + nodeParent.cube.maxCorner.x) / 2.0;
	double midY = (nodeParent.cube.minCorner.y + nodeParent.cube.maxCorner.y) / 2.0;
	double midZ = (nodeParent.cube.minCorner.z + nodeParent.cube.maxCorner.z) / 2.0;

	node.cube.minCorner.x = node.Adr.x ? midX : nodeParent.cube.minCorner.x;
	node.cube.minCorner.y = node.Adr.y ? midY : nodeParent.cube.minCorner.y;
	node.cube.minCorner.z = node.Adr.z ? midZ : nodeParent.cube.minCorner.z;

	node.cube.maxCorner.x = node.Adr.x ? nodeParent.cube.maxCorner.x : midX;
	node.cube.maxCorner.y = node.Adr.y ? nodeParent.cube.maxCorner.y : midY;
	node.cube.maxCorner.z = node.Adr.z ? nodeParent.cube.maxCorner.z : midZ;
}

bool isInsideAABB(AABB & box, Polyhedron::Vertex_handle &p){
	return (p->point().x() >= box.minCorner.x && p->point().x() <= box.maxCorner.x &&
			p->point().y() >= box.minCorner.y && p->point().y() <= box.maxCorner.y &&
			p->point().z() >= box.minCorner.z && p->point().z() <= box.maxCorner.z);
}

/// @brief add one vertex to an octree, by following strictly the rules of maximum amount of point in a node, and maximum depth of the tree
/// @param root the root node of the tree
/// @param vert the vertex that will be added, as a Vertex_handle
void addVertexToOctree(OctreeNode &root, Polyhedron::Vertex_handle &vert)
{
	// TODO, this function can be recursive
	root.vertexlist.push_back(vert);
}

void vertexFromParent(OctreeNode &parent, OctreeNode &child){
	for(auto vert : parent.vertexlist){
		if(isInsideAABB(child.cube, vert)){
			child.vertexlist.push_back(vert);
		}
	}
}

/// @brief add a level to the given parent Octree node, by creating 8 children with 8 bounding box,
/// sliced in the middle of the parent node
/// @param node the octree node to which 8 children will be added
void addOctreeLevel(OctreeNode &node, int depth = 1)
{
	//printf("\n\n");
	// TODO...
	for(int x=0; x<2; ++x){
		for(int y=0; y<2; ++y){
			for(int z=0; z<2; ++z){
				OctreeNode *child = new OctreeNode();
				child->setAdr(x,y,z);
				child->depth = depth;
				subdivideAABB(node,*child);
				vertexFromParent(node, *child);

				node.nodeChilds.push_back(child);
				if(child->vertexlist.size() >= MAX_POINT && depth <= MAX_DEPTH){
					addOctreeLevel(*child, depth++);
				}
			}
		}
	}

	node.vertexlist.clear();
}

void VertexFromMesh(Polyhedron &mesh, OctreeNode & node){
	for(auto it=mesh.vertices_begin(); it != mesh.vertices_end(); ++it){
		node.vertexlist.push_back(it);
	}
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

Point3 averagePoint(Point3 &lv, Point3 &rv){
	Point3 result(lv.x() + rv.x(), lv.y() + rv.y(), lv.z() + rv.z());

	return result;
}

struct PointMoy3D{
	Point3 pt;
	std::list<Vertex_handle> vertexlist;
};

std::vector<PointMoy3D> listPoints;
std::vector<std::vector<int>> faces;

void SimplifyMesh(const OctreeNode &node){
	double x=0, y=0, z=0;
	for(auto vt : node.vertexlist){
		x+=vt->point().x();
		y+=vt->point().y();
		z+=vt->point().z();
	}
	Point3 average = Point3(x/node.vertexlist.size(), y/node.vertexlist.size(), z/node.vertexlist.size());

	listPoints.push_back({
		.pt=average, 
		.vertexlist = node.vertexlist});
}

void traverse_octree(const OctreeNode& node, std::vector<AABB> &BBoxes)
{
  if (node.nodeChilds.size()==0) {
    if (node.vertexlist.size()>0)
	{	
		BBoxes.push_back(node.cube);
		SimplifyMesh(node);
	}
    return;
  }

  for(int x=0; x<2; ++x){
		for(int y=0; y<2; ++y){
			for(int z=0; z<2; ++z){
				OctreeNode* child_node = node.getChild(x, y ,z);
				
				traverse_octree(*child_node, BBoxes);
			}
		}
    }
}

/*
Vertex_handle isInArray(Vertex_handle &lv, Vertex_handle &rv){
	return lv
}
*/

void WriteOFFsimplified(const Polyhedron &mesh){
	std::vector<int> temp;
	for(auto it=mesh.vertex_handles().begin(); it!= mesh.vertex_handles().end(); ++it){
		for(int i=0; i<listPoints.size(); ++i){
			for(auto vert : listPoints[i].vertexlist){
				if(*it == vert){
					if(std::find(temp.begin(), temp.end(), i) == temp.end()){
						temp.push_back(i);
					}
					if(temp.size()>2){
						faces.push_back(temp);
						temp.clear();
					}
					break;
				}
			}
		}
	}

	std::ofstream out("octree_meshresSimplified.off");
	out << "OFF" << std::endl;
	out << listPoints.size() << " " << faces.size() << " 0" << std::endl;
	for(auto point : listPoints){
		out << point.pt.x() << " " << point.pt.y() << " " << point.pt.z() << "\n";
	}
	for(auto face : faces){
		out << face.size() << " ";
		for(auto fi : face){
			out << fi << " ";
		}
		out << std::endl;
	}
}

void extractMeshFromOctree(const OctreeNode &root, const Polyhedron& mesh){

	std::vector<AABB> BBoxes;
	std::vector<Point3> Vertexs;

	// TODO: fill "vertices" and "faces" by going through the octree
	traverse_octree(root, BBoxes);

	std::ofstream out("octree_meshres.off");
	out << "OFF" << std::endl;
    out << 8*BBoxes.size()<<" "<<12*BBoxes.size()<<" "<< 6*BBoxes.size()<<"\n";

    // out << "4 0 1 2 3\n";
    // out << "4 7 6 5 4\n";
    // out << "4 0 4 5 1\n";
    // out << "4 1 5 6 2\n";
    // out << "4 2 6 7 3\n";
    // out << "4 3 7 4 0\n";

	for (const auto &bb : BBoxes)
	{
		out << bb.minCorner.x << " " << bb.minCorner.y << " " << bb.minCorner.z << "\n";
		out << bb.maxCorner.x << " " << bb.minCorner.y << " " << bb.minCorner.z << "\n";
		out << bb.maxCorner.x << " " << bb.maxCorner.y << " " << bb.minCorner.z << "\n";
		out << bb.minCorner.x << " " << bb.maxCorner.y << " " << bb.minCorner.z << "\n";
		out << bb.minCorner.x << " " << bb.minCorner.y << " " << bb.maxCorner.z << "\n";
		out << bb.maxCorner.x << " " << bb.minCorner.y << " " << bb.maxCorner.z << "\n";
		out << bb.maxCorner.x << " " << bb.maxCorner.y << " " << bb.maxCorner.z << "\n";
		out << bb.minCorner.x << " " << bb.maxCorner.y << " " << bb.maxCorner.z << "\n";
	}
	int min = 0;
	for (const auto &f : BBoxes)
	{
		out << "4 "<< min << " " << min+1 << " " << min+2 << " " << min+3 <<" \n";
		out << "4 "<< min+7 << " " << min+6 << " " << min+5 << " " << min+4 <<" \n";
		out << "4 "<< min << " " << min+4 << " " << min+5 << " " << min+1 <<" \n";
		out << "4 "<< min+1 << " " << min+5 << " " << min+6 << " " << min+2 <<" \n";
		out << "4 "<< min+2 << " " << min+6 << " " << min+7 << " " << min+3 <<" \n";
		out << "4 "<< min+3 << " " << min+7 << " " << min+4 << " " << min <<" \n";
		min += 8;
	}
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
OctreeNode generateOctree(Polyhedron &mesh)
{
	OctreeNode root{};
	VertexFromMesh(mesh, root);
	root.cube = computeBB(mesh);

	if(root.vertexlist.size() > MAX_POINT){
		addOctreeLevel(root);
	}

	WriteOFFsimplified(mesh);
	/*
	for(auto child:root.nodeChilds){
		child->DisplayNodeAdr();
		child->getChild(0,0,0)->DisplayNodeAdr();
	}
	*/
	// TODO...
	return root;
}

/*
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr << "Il manque un paramètre au programme. Veuillez lui donner en entrée un nom de fichier au format off." << std::endl;
		return 1;
	}

	Polyhedron mesh;
	std::ifstream input(argv[1]);
	if (!input || !(input >> mesh) || mesh.is_empty())
	{
		std::cerr << "Le fichier donné n'est pas un fichier off valide." << std::endl;
		return 1;
	}

	unsigned int nbVerts = 0;
	for (Vertex_iterator i = mesh.vertices_begin(); i != mesh.vertices_end(); ++i)
	{
		++nbVerts;
	}
	std::cout << "Nombre de sommets: " << nbVerts << std::endl;

	unsigned int nbEdges = 0;
	for (Halfedge_iterator i = mesh.halfedges_begin(); i != mesh.halfedges_end(); ++i)
	{
		++nbEdges;
	}
	nbEdges /= 2;
	std::cout << "Nombre d'arêtes: " << nbEdges << std::endl;

	unsigned int nbFaces = 0;
	for (Facet_iterator i = mesh.facets_begin(); i != mesh.facets_end(); ++i)
	{
		++nbFaces;
	}
	std::cout << "Nombre de faces: " << nbFaces << std::endl;

	const auto octree = generateOctree(mesh);

	extractMeshFromOctree(octree,mesh);

	return 0;
}
*/