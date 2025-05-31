cmake_minimum_required(VERSION 3.31)
project(CP)

set(CMAKE_CXX_STANDARD 20)

add_executable(CP geo.cpp
        "Data Structure/DSU.cpp"
        Geometry/polar_angle.cpp
        Geometry/angle_between_vectors.cpp
        Geometry/area_polygon.cpp
        Geometry/area_triangle.cpp
        Geometry/bisector.cpp
        Geometry/dist_from_point_to_line.cpp
        Geometry/dist_from_point_to_seg.cpp
        Geometry/dist_between_2segment.cpp
        Geometry/intersec_between_2line.cpp
        Geometry/vector_length.cpp
        Geometry/equation_line_passing_through_2_points.cpp
        Geometry/equation_line_point_vector.cpp
        Geometry/Is_the_point_on_line.cpp
        Geometry/Is_the_point_on_ray.cpp
        Geometry/is_point_on_segment.cpp
        Geometry/is_2_point_on_same_side_of_line.cpp
        Geometry/distance_between_rays.cpp
        Graph/Bridges.cpp
        Graph/articulation_points.cpp
        Tree/diameter.cpp
        Graph/SCC_Kosaraju.cpp
        Graph/SCC_Tarjan's.cpp
        Tree/lca.cpp
        Graph/BCC.cpp
        Geometry/Location_of_Point_in_line.cpp
        Geometry/Is_2_segment_intersect.cpp
        Geometry/Point_Location_Relative_to_Polygon.
        Geometry/number_lattice_points_inside_polygon_and_on_its_boundary.cpp
        Geometry/polarSort.cpp
        Geometry/windingNumber.cpp
        Geometry/windingNumber_for_Integers.cpp
        Geometry/type_of_intersection_circle_Line.cpp
        Geometry/struct_line.cpp
        "Data Structure/Sparse_Table.cpp"
        Math/MatrixExpo.cpp
        Math/Fast_Power.cpp
        "Number Theory/linearSieve.cpp"
        Combinatorics/nCr.cpp
        Combinatorics/stars_and_bars.cpp
        "Number Theory/is_prime.cpp"
        "Data Structure/MonotonicStack.cpp"
        "Data Structure/order_set.cpp"
        Strings/KMP.cpp
        Strings/compute_automaton.cpp
        Strings/Trie01.cpp
        Strings/Trie.cpp
        Random/random_range.cpp
        "Data Structure/Segment_Tree.cpp"
        "Data Structure/Lazy_Segment.cpp"
        Strings/Hashing.cpp
        "Strings/Hashing2D.cpp"
)
