/*!
  \brief
  Implements numerical images.
*/

#include "NumVolume.h"
#include <stdio.h>
#include <iostream>
#include <string.h>

//! Default constructor, everything to Null
NumVolume::NumVolume() : Volume(0,0,0)
{
    _datax = 0;
    _datay = 0;
    _dataz = 0;
    _dataw = 0;
    _sizex = 0;
    _sizey = 0;
    _sizez = 0;
}

//! Constructor with a size input.
NumVolume::NumVolume(int sizex, int sizey, int sizez): Volume(0,0,0), _sizex(sizex), _sizey(sizey),_sizez(sizez)
{
    _datax = new double[_sizex];
    _datay = new double[_sizey];
    _dataz = new double[_sizez];
    _dataw = new double**[_sizex];
    for(int i=0;i<_sizex;i++){
        _dataw[i] = new double*[_sizey];
        for(int j=0;j<_sizey;j++){
            _dataw[i][j] = new double[_sizez];
        }
    }
}

//! Constructor with a given array.
NumVolume::NumVolume(int sizex, double* x, int sizey, double* y, int sizez, double* z, double*** w)
: Volume(0,0,0), _sizex(sizex), _sizey(sizey), _sizez(sizez)
{
    double avgx = 0;		//!< x-direction, symmetrize the given array. Center them at 0.
    for(int i=0;i<_sizex;i++){avgx += x[i];}
    avgx /= _sizex;
    _datax = new double[_sizex]; _dataw = new double**[_sizex];
    for(int i=0;i<_sizex;i++){
        _datax[i] = x[i]-avgx; _dataw[i] = new double*[_sizey];
    }
    double avgy = 0;		//!< y-direction,symmetrize the given array. Center them at 0.
    for(int i=0;i<_sizey;i++){avgy += y[i];}
    avgy /= _sizey;
    _datay = new double[_sizey];
    for(int i=0;i<_sizey;i++){
        _datay[i] = y[i]-avgy;
    }
    double avgz = 0;		//!< z-direction,symmetrize the given array. Center them at 0.
    for(int i=0;i<_sizez;i++){avgz += z[i];}
    avgz /= _sizez;
    _dataz = new double[_sizez];
    for(int i=0;i<_sizez;i++){
        _dataz[i] = z[i]-avgz;
    }
    
    for(int i=0;i<_sizex;i++){
        for(int j=0;j<_sizey;j++){
            for(int k=0;k<_sizez;k++){
            _dataw[i][j][k] = w[i][j][k];
            }
        }
    }
    _rx = fabs(_datax[0]) > fabs(_datax[_sizex-1]) ? fabs(_datax[0]) : fabs(_datax[_sizex-1]);
    _ry = fabs(_datay[0]) > fabs(_datay[_sizey-1]) ? fabs(_datay[0]) : fabs(_datay[_sizey-1]);
    _rz = fabs(_dataz[0]) > fabs(_dataz[_sizez-1]) ? fabs(_dataz[0]) : fabs(_dataz[_sizez-1]);
    _r = sqrt(_rx*_rx+_ry*_ry);
}

//! Constructor with a given size, range and a set of z-values
NumVolume::NumVolume(int sizex, double rx, int sizey, double ry, int sizez, double rz, double*** w)
: Volume(rx,ry,rz), _sizex(sizex), _sizey(sizey),_sizez(sizez)
{
    _datax = new double[_sizex];
    _datay = new double[_sizey];
    _dataz = new double[_sizez];
    _dataw = new double**[_sizex];
    for(int i=0;i<_sizex;i++){
        _dataw[i] = new double*[_sizey];
        _datax[i] = -_rx + i*(2*_rx)/(_sizex-1);
    }
    for(int i=0;i<_sizex;i++){
        for(int j=0;j<_sizey;j++){
            _dataw[i][j] = new double[_sizez];
        }
    }
    for(int i=0;i<_sizey;i++){
        _datay[i] = -_ry + i*(2*_ry)/(_sizey-1);
    }
    for(int i=0;i<_sizez;i++){
        _dataz[i] = -_rz + i*(2*_rz)/(_sizez-1);
    }
    for(int i=0;i<_sizex;i++){
        for(int j=0;j<_sizey;j++){
            for(int k=0;k<_sizez;k++){
                _dataw[i][j][k] = w[i][j][k];
            }
        }
    }
}

//! Constructor with a given size, range but z-values are unknown.
NumVolume::NumVolume(int sizex, double rx, int sizey, double ry, int sizez, double rz)
: Volume(rx,ry,rz), _sizex(sizex), _sizey(sizey),_sizez(sizez)
{
    _datax = new double[_sizex];
    _datay = new double[_sizey];
    _dataz = new double[_sizez];
    _dataw = new double**[_sizex];
    for(int i=0;i<_sizex;i++){
        _dataw[i] = new double*[_sizey];
        _datax[i] = -_rx + i*(2*_rx)/(_sizex-1);
    }
    for(int i=0;i<_sizex;i++){
        for(int j=0;j<_sizey;j++){
            _dataw[i][j] = new double[_sizez];
        }
    }
    for(int i=0;i<_sizey;i++){
        _datay[i] = -_ry + i*(2*_ry)/(_sizey-1);
    }
    for(int i=0;i<_sizez;i++){
        _dataz[i] = -_rz + i*(2*_rz)/(_sizez-1);
    }
}

//! Copy constructor that takes in the same type.
NumVolume::NumVolume(const NumVolume& f) : Volume(f._rx, f._ry, f._rz)
{
    _sizex = f._sizex; _sizey = f._sizey; _sizez = f._sizez;
    _datax = new double[_sizex]; _datay = new double[_sizey]; _dataz = new double[_sizez];
    _dataw = new double**[_sizex];
    for (int i=0;i<_sizex;i++){
        _datax[i] = f._datax[i];
        _dataw[i] = new double*[_sizey];
    }
    for(int i=0;i<_sizex;i++){
        for(int j=0;j<_sizey;j++){
            _dataw[i][j] = new double[_sizez];
        }
    }
    
    for (int i=0;i<_sizey;i++){
        _datay[i] = f._datay[i];
    }
    for (int i=0;i<_sizez;i++){
        _dataz[i] = f._dataz[i];
    }
    for(int i=0;i<_sizex;i++){
        for(int j=0;j<_sizey;j++){
            for(int k=0;k<_sizez;k++){
            _dataw[i][j][k] = f._dataw[i][j][k];
            }//!< Performs a deep copy.
        }
    }
}

//! Copy assignment, used when modifying existing objects.
NumVolume& NumVolume::operator=(const NumVolume& f)
{
    if(_datax!=0) delete [] _datax;
    if(_datay!=0) delete [] _datay;
    if(_dataz!=0) delete [] _dataz;
    if(_dataw!=0) delete [] _dataw;
    _sizex = f._sizex; _sizey = f._sizey; _sizez = f._sizez;
    _rx = f._rx; _ry = f._ry; _rz = f._rz; _r = f._r;
    _datax = new double[_sizex];
    _datay = new double[_sizey];
    _dataz = new double[_sizez];
    _dataw = new double**[_sizex];
    for (int i=0;i<_sizex;i++){
        _datax[i] = f._datax[i];
        _dataw[i] = new double*[_sizey];
    }
    for(int i=0;i<_sizex;i++){
        for(int j=0;j<_sizey;j++){
            _dataw[i][j] = new double[_sizez];
        }
    }
    for (int i=0;i<_sizey;i++){
        _datay[i] = f._datay[i];
    }
    for (int i=0;i<_sizez;i++){
        _dataz[i] = f._dataz[i];
    }
    for(int i=0;i<_sizex;i++){
        for(int j=0;j<_sizey;j++){
            for(int k=0;k<_sizez;k++){
                _dataw[i][j][k] = f._dataw[i][j][k];
            }//!< Performs a deep copy.
        }
    }
    return (*this);
}

//! Constructor with a size and a Volume object. Use operator () to initialize.
NumVolume::NumVolume(int sizex, int sizey, int sizez, const Volume& f) : Volume(0,0,0)
{
    _sizex = sizex;
    _sizey = sizey;
    _sizez = sizez;
    _rx = f.GetRangeX(); _ry = f.GetRangeY(); _rz = f.GetRangeZ();
    _r = sqrt(_rx*_rx+_ry*_ry);
    _datax = new double[_sizex];
    _datay = new double[_sizey];
    _dataz = new double[_sizez];
    _dataw = new double**[_sizex];
    for(int i=0;i<_sizex;i++){
        _dataw[i] = new double*[_sizey];
        _datax[i] = -_rx + i*(2*_rx)/(_sizex-1);
    }
    for(int i=0;i<_sizey;i++){
        _datay[i] = -_ry + i*(2*_ry)/(_sizey-1);
    }
    for(int i=0;i<_sizez;i++){
        _dataz[i] = -_rz + i*(2*_rz)/(_sizez-1);
    }
    for(int i=0;i<_sizex;i++){
        for(int j=0;j<_sizey;j++){
            _dataw[i][j] = new double[_sizez];
        }
    }
    for(int i=0;i<_sizex;i++){
        for(int j=0;j<_sizey;j++){
            for(int k=0;k<_sizez;k++){
            _dataw[i][j][k] = f(_datax[i],_datay[j],_dataz[k],0);
            }
        }
    }
}

//! Assignment operator for construction.
void NumVolume::Copy(int sizex, int sizey, int sizez, const Volume& f)
{
    if(_datax!=0) delete [] _datax;
    if(_datay!=0) delete [] _datay;
    if(_dataz!=0) delete [] _dataz;
    if(_dataw!=0) {
        for (int i = 0; i < _sizex; ++i) {
            for (int j = 0; j < _sizey; ++j)
                delete [] _dataw[i][j];
            delete [] _dataw[i];
        }
        delete [] _dataw;
    }
    _sizex = sizex; _sizey  = sizey; _sizez = sizez;
    _rx = f.GetRangeX(); _ry = f.GetRangeY();_rz = f.GetRangeZ();
    _datax = new double[_sizex]; _datay = new double[_sizey];
    _dataz = new double[_sizez]; _dataw = new double**[_sizex];
      
    for(int i=0;i<_sizex;i++){
        _dataw[i] = new double*[_sizey];
        _datax[i] = -_rx + i*(2*_rx)/(_sizex-1);
    }
    for(int i=0;i<_sizey;i++){
        _datay[i] = -_ry + i*(2*_ry)/(_sizey-1);
    }
    for(int i=0;i<_sizez;i++){
        _dataz[i] = -_rz + i*(2*_rz)/(_sizez-1);
    }
    for(int i=0;i<_sizex;i++){
        for(int j=0;j<_sizey;j++){
            _dataw[i][j] = new double[_sizez];
        }
    }
    for(int i=0;i<_sizex;i++){
        for(int j=0;j<_sizey;j++){
            for(int k=0;k<_sizez;k++){
                _dataw[i][j][k]= f(_datax[i],_datay[j],_dataz[k],0);
            }
        }
    }
}

//! Numerical Volume destructor, frees memory.
NumVolume::~NumVolume()
{
    if(_datax!=0) delete [] _datax;
    if(_datay!=0) delete [] _datay;
    if(_dataz!=0) delete [] _dataz;
    if(_dataw!=0){
    for (int i = 0; i < _sizex; ++i) {
        for (int j = 0; j < _sizey; ++j)
            delete [] _dataw[i][j];
        delete [] _dataw[i];
    }
    delete [] _dataw;
      }
}

//! Operator for returning value at a given point.
double NumVolume::operator()(double x, double y, double z, Interpolator* intpl) const
{
      intpl->set_values(_sizex,_sizey,_sizez,_datax,_datay,_dataz,_dataw);
      return intpl->Interpolate(x,y,z);
}

//! Operator returning a reference to the data at the specified index.
double& NumVolume::operator()(int indexX, int indexY, int indexZ)
{
    if(indexX < 0 || indexX >_sizex-1 || indexY <0 || indexY >_sizey-1|| indexZ <0 || indexZ >_sizez-1)
    printf("Index out of range");
    return _dataw[indexX][indexY][indexZ];
}
    
//! Default print method.
void NumVolume::Print()
{
    for (int k=0;k<_sizez;k++){
        for(int j=_sizey-1;j>=0;j--){
            for(int i=0;i<_sizex;i++){
                printf("%.9f\t",_dataw[i][j][k]);
            }
            printf("\n");
        }
    }

}

//! Print data in the range.
void NumVolume::Print(double xi, double xf, int Nx, double yi, double yf, int Ny){}




double* NumVolume::GetXPtr()
{
    return _datax;
}

double* NumVolume::GetYPtr()
{
    return _datay;
}

double* NumVolume::GetZPtr()
{
    return _dataz;
}

int NumVolume::GetSizeX()
{
    return _sizex;
}

int NumVolume::GetSizeY()
{
    return _sizey;
}

int NumVolume::GetSizeZ()
{
    return _sizez;
}
double*** NumVolume::GetWPtr()
{
    return _dataw;
}

#ifdef USE_HDF
//! DO NOT include 'output/' in string 'file'.

//! Export data to HDF5 file. DO NOT include 'output/' in string 'file'.
void NumVolume::ExportHDF(const char* file, double xi, double xf, int Nx, double yi, double yf, int Ny){}

//! Export data to HDF5 file. DO NOT include 'output/' in string 'file'.
void NumVolume::ExportHDF(const char* file)
{
    char fname[strlen(file)+11];
    strcpy(fname, "output/"); //!< Automatically export to directory 'output/'
    strcat(fname, file);
//! 3D array _dataw incompatible with HDF5. 1D array 'data' needed for bridging.
    double *data;
    data = new double[_sizez*_sizey*_sizex];
    for (int i = 0; i<_sizex; i++){
        for (int j = 0; j<_sizey; j++){
            for (int k = 0; k <_sizez; k++){
//! The indexing is meant for consistency with python, VisIt, etc.
                data[i+(j+k*_sizey)*_sizex] = _dataw[i][j][k];
            }
        }
    }
//! Create file and save data
    hid_t file_id;
    hsize_t dims[Dim3];
    dims[0] = _sizez;
    dims[1] = _sizey;
    dims[2] = _sizex;
    hsize_t dimx[Dim1];
    dimx[0] = _sizex;
    hsize_t dimy[Dim1];
    dimy[0] = _sizey;
    hsize_t dimz[Dim1];
    dimz[0] = _sizez;
    herr_t status;
    file_id = H5Fcreate(fname, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
//! Number of grids saved as attributes. Coodrinates saved as 1D arrays since the mesh is rectilinear. Data saved as 3D array.
    status = H5LTmake_dataset_double(file_id,"/x",Dim1,dimx,_datax);
    status = H5LTmake_dataset_double(file_id,"/y",Dim1,dimy,_datay);
    status = H5LTmake_dataset_double(file_id,"/z",Dim1,dimz,_dataz);
    status = H5LTmake_dataset_double(file_id,"/data",Dim3,dims,data);
    status = H5LTset_attribute_int(file_id, "/x", "size of x", &_sizex, 1);
    status = H5LTset_attribute_int(file_id, "/y", "size of y", &_sizey, 1);
    status = H5LTset_attribute_int(file_id, "/z", "size of z", &_sizez, 1);
    status = H5Fclose(file_id);
//! Clear up memory
    delete [] data;
//! Create XMDF file that accompanies HDF5 file so as to enable VisIt reading.
    strcat(fname, ".xmf");
    FILE *xmf = 0;
    xmf = fopen(fname, "w");
    fprintf(xmf, "<?xml version=\"1.0\" ?>\n");
    fprintf(xmf, "<!DOCTYPE Xdmf SYSTEM \"Xdmf.dtd\" []>\n");
    fprintf(xmf, "<Xdmf Version=\"2.0\">\n");
    fprintf(xmf, " <Domain>\n");
    fprintf(xmf, "   <Grid Name=\"mesh\" GridType=\"Uniform\">\n");
    fprintf(xmf, "     <Topology TopologyType=\"3DRectMesh\" NumberOfElements=\"%d %d %d\"/>\n", _sizez, _sizey, _sizex);
    fprintf(xmf, "     <Geometry GeometryType=\"VXVYVZ\">\n");
    fprintf(xmf, "       <DataItem Dimensions=\"%d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", _sizex);
    fprintf(xmf, "        %s:/x\n", file);
    fprintf(xmf, "       </DataItem>\n");
    fprintf(xmf, "       <DataItem Dimensions=\"%d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", _sizey);
    fprintf(xmf, "        %s:/y\n", file);
    fprintf(xmf, "       </DataItem>\n");
    fprintf(xmf, "       <DataItem Dimensions=\"%d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", _sizez);
    fprintf(xmf, "        %s:/z\n", file);
    fprintf(xmf, "       </DataItem>\n");
    fprintf(xmf, "     </Geometry>\n");
    fprintf(xmf, "     <Attribute Name=\"data\" AttributeType=\"Scalar\" Center=\"Node\">\n");
fprintf(xmf, "       <DataItem Dimensions=\"%d %d %d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", _sizez, _sizey, _sizex);
    fprintf(xmf, "        %s:/data\n", file);
    fprintf(xmf, "       </DataItem>\n");
    fprintf(xmf, "     </Attribute>\n");
    fprintf(xmf, "   </Grid>\n");
    fprintf(xmf, " </Domain>\n");
    fprintf(xmf, "</Xdmf>\n");
    fclose(xmf);
}

//! Constructor from a HDF5 file.
NumVolume::NumVolume(const char* file): Volume(0, 0, 0)
{
//! Open target file, which needs to be in the same format as the exported .h5 file: Number of grids as attributes. Coodrinates as 1D arrays since the mesh is rectilinear. Data as 3D array.
    hid_t file_id;
    herr_t status;
    file_id = H5Fopen(file, H5F_ACC_RDONLY, H5P_DEFAULT);
//! Read in number of grids
    status = H5LTget_attribute_int(file_id, "/x", "size of x", &_sizex);
    status = H5LTget_attribute_int(file_id, "/y", "size of y", &_sizey);
    status = H5LTget_attribute_int(file_id, "/z", "size of z", &_sizez);
//! Allocate memory
    _datax = new double[_sizex];
    _datay = new double[_sizey];
    _dataz = new double[_sizez];
//! 3D array _dataw incompatible with HDF5. 1D array 'data' needed for bridging.
    double *data;
    data = new double[_sizez*_sizey*_sizex];
//! Read in data
    status = H5LTread_dataset_double(file_id,"/x",_datax);
    status = H5LTread_dataset_double(file_id,"/y",_datay);
    status = H5LTread_dataset_double(file_id,"/z",_dataz);
    status = H5LTread_dataset_double(file_id,"/data",data);
//! Move data to _dataw
    _dataw = new double**[_sizex];
    for (int i=0;i<_sizex;i++){
        _dataw[i] = new double*[_sizey];
        for (int j = 0; j<_sizey; j++){
            _dataw[i][j] = new double[_sizez];
            for (int k = 0; k<_sizez; k++){
                _dataw[i][j][k] = data[i+(j+k*_sizey)*_sizex];
            }
        }
    }
    status = H5Fclose(file_id);
//! Clear up memory
    delete [] data;
//! Initialize ranges
    _rx = -_datax[0];
    _ry = -_datay[0];
    _rz = -_dataz[0];
    _r = sqrt(_rx*_rx+_ry*_ry);
}
#endif
