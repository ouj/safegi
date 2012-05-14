#ifndef _DIMENSIONS_H_
#define _DIMENSIONS_H_

template<int d1, int d2, int d3, int d4, int d5, int d6, int d7, int d8>
struct dimension { };

template<typename D1, typename D2>
struct dimension_product { };

template<int da1, int da2, int da3, int da4, int da5, int da6, int da7, int da8,
         int db1, int db2, int db3, int db4, int db5, int db6, int db7, int db8>
struct dimension_product<dimension<da1,da2,da3,da4,da5,da6,da7,da8>,
                         dimension<db1,db2,db3,db4,db5,db6,db7,db8>> { 
    typedef dimension<da1+db1,da2+db2,da3+db3,da4+db4,da5+db5,da6+db6,da7+db7,da8+db8> type;
};

template<typename D1, typename D2>
struct dimension_division { };

template<int da1, int da2, int da3, int da4, int da5, int da6, int da7, int da8,
         int db1, int db2, int db3, int db4, int db5, int db6, int db7, int db8>
struct dimension_division<dimension<da1,da2,da3,da4,da5,da6,da7,da8>,
                          dimension<db1,db2,db3,db4,db5,db6,db7,db8>> { 
    typedef dimension<da1-db1,da2-db2,da3-db3,da4-db4,da5-db5,da6-db6,da7-db7,da8-db8> type;
};

template<typename D>
struct dimension_sqrt { };

template<int da1, int da2, int da3, int da4, int da5, int da6, int da7, int da8>
struct dimension_sqrt<dimension<da1,da2,da3,da4,da5,da6,da7,da8>> {
    typedef dimension<da1/2,da2/2,da3/2,da4/2,da5/2,da6/2,da7/2,da8/2> type;
};

typedef dimension<0,0,0,0,0,0,0,0> unit_d;
typedef dimension<1,0,0,0,0,0,0,0> length_d;
typedef dimension<0,1,0,0,0,0,0,0> time_d;
typedef dimension<0,0,1,0,0,0,0,0> energy_d;
typedef dimension<0,0,0,1,0,0,0,0> solidangle_d;
typedef dimension<0,0,0,0,1,0,0,0> angle_d;
typedef dimension<0,0,0,0,0,1,0,0> proj_d;

typedef dimension_division<unit_d,time_d>::type invtime_d;
typedef dimension_division<unit_d,solidangle_d>::type invsolidangle_d;
typedef dimension_division<unit_d,proj_d>::type invproj_d;
typedef dimension_product<length_d,length_d>::type area_d;
typedef dimension_product<proj_d,solidangle_d>::type projsolidangle_d;
typedef dimension_division<unit_d,area_d>::type invarea_d;
typedef dimension_product<invarea_d,invproj_d>::type invprojarea_d;
typedef dimension_product<energy_d,invtime_d>::type power_d;
typedef dimension_product<power_d,invarea_d>::type irradiance_d;
typedef dimension_product<power_d,invsolidangle_d>::type intensity_d;
typedef dimension_product<dimension_product<irradiance_d,invsolidangle_d>::type,invproj_d>::type radiance_d; // cos here
typedef dimension_division<radiance_d,irradiance_d>::type brdf_d;
typedef dimension_division<unit_d,radiance_d>::type invradiance_d;
typedef unit_d rho_d;

#endif
