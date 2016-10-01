//
//  xy_struct.hpp
//  PedestrianDM
//
//  Created by Daniel Weser on 10/01/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#ifndef xy_struct_hpp
#define xy_struct_hpp

#include "nanoflann.hpp"
using namespace std;
using namespace nanoflann;

struct XY
{
	struct Point
	{
		double  x,y;
	};

	std::vector<Point>  pts;

	// Must return the number of data points
	inline long kdtree_get_point_count() const { return pts.size(); }

	// Returns the distance between the vector "p1[0:size-1]" and the data point with index "idx_p2" stored in the class:
	inline double kdtree_distance(const double *p1, const long idx_p2, long /*size*/) const
	{
		const double d0=p1[0]-pts[idx_p2].x;
		const double d1=p1[1]-pts[idx_p2].y;
		return d0*d0+d1*d1;
	}

	// Returns the dim'th component of the idx'th point in the class:
	// Since this is inlined and the "dim" argument is typically an immediate value, the
	//  "if/else's" are actually solved at compile time.
	inline double kdtree_get_pt(const long idx, int dim) const
	{
		if (dim==0) return pts[idx].x;
		else return pts[idx].y;
	}

	// Optional bounding-box computation: return false to default to a standard bbox computation loop.
	//   Return true if the BBOX was already computed by the class and returned in "bb" so it can be avoided to redo it again.
	//   Look at bb.size() to find out the expected dimensionality (e.g. 2 or 3 for point clouds)
	template <class BBOX>
	bool kdtree_get_bbox(BBOX& /*bb*/) const { return false; }
};

#endif /* xy_struct_hpp */